#include <iostream>

#include "tinysp.hh"
#include "stringify.hh"
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <cerrno>

PckIOError::PckIOError(const std::string & s) :
    _s(s)
{
}

PckIOError::~PckIOError() throw ()
{
}

std::string PckIOError::str() const
{
    return _s;
}


Packet::Packet(unsigned char *b, int n) :
    id(b[0]),
    len(n - 1)
{
    memcpy(buf, b + 1, len);
}

Packet::Packet(unsigned char iid, const std::deque<unsigned char> & p) :
    id(iid),
    len(p.size())
{
    std::copy(p.begin(), p.end(), buf);
}

Packet::Packet(unsigned char iid) :
    id(iid),
    len(0)
{
}

enum
{
    ST_BEFOREPKT,
    ST_INPKTID,
    ST_INPKT,
    ST_BYTESTUFF,
    ST_PKTDONE,
    ST_PKTERR,
    ST_PKTERR_END,
};

enum
{
    CONTROL1 = 0x10,
    CONTROL2 = 0x03,
};

TinySP::TinySP (std::string st) :
    _connected(0),
    _state(ST_BEFOREPKT),
    _ctr(0)
{
    _comm = BLUETOOTH;
    _fds[0].events = POLLIN;
    _mac = st;
}

TinySP::TinySP (std::string st, int s) :
    _connected(0),
    _state(ST_BEFOREPKT),
    _ctr(0),
    _serialport(SerialPortOptions().with_dev(st).with_speed(s))
{
    _comm = SERIAL;
    _fds[0].events = POLLIN;
    _fds[0].fd = _serialport.get_fd();
}


TinySP::~TinySP()
{
}

std::string TinySP::get_mac(void)
{
       return _mac;
}

void TinySP::start_connection(void)
{
    if(!_connected)
    {
        switch(_comm){
            case BLUETOOTH:
                _socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
                str2ba(_mac.c_str(), &_loc_addr.rc_bdaddr);
                _loc_addr.rc_family = AF_BLUETOOTH;
                _loc_addr.rc_channel = 1;

                if(connect(_socket, (struct sockaddr *)&_loc_addr,
                            sizeof(_loc_addr)) == 0)
                    _connected = 1;

                _fds[0].fd = _socket;
                break;

            default:
                break;
        }

    }
}

void TinySP::close_connection(void)
{
    if(_connected)
        close(_fds[0].fd);
}

bool TinySP::get_connection_status(void)
{
    return _connected;
}

unsigned char TinySP::_read_byte()
{
    unsigned char r;

    int ret(poll(_fds, 1, 250));
    if (ret == 0)
        throw PckNoPacketsReady();
    else if (ret == -1)
        throw PckIOError(stringify("poll() failed: ") + 
                ::strerror(errno));

    int n(read(_fds[0].fd, &r, 1));
    if (n == -1)
        throw PckIOError(stringify("read() failed: ") + 
                ::strerror(errno));
    else if (n == 0)
        throw PckIOError(stringify("read() failed: EOF"));

    _commStat.rxbytes += n;

    return r;
}

Packet TinySP::read_packet()
{
    _state = ST_BEFOREPKT;
    _ctr = 0;
    while (0 == _decode_byte())
        /* EMPTY */;
    Packet ret(_buf, _ctr);
    _commStat.rxpkt++;
    return ret;
}

int TinySP::_decode_byte()
{
    unsigned char ch(_read_byte());
    switch (_state)
    {
        case ST_BEFOREPKT:
            if (ch == CONTROL1)
                _state = ST_INPKTID;
            break;
        case ST_INPKTID:
            _buf[_ctr++] = ch;
            _state = ST_INPKT;
            break;
        case ST_INPKT:
            if (ch == CONTROL1)
                _state = ST_BYTESTUFF;
            else
                _buf[_ctr++] = ch;
            break;
        case ST_BYTESTUFF:
            if (ch == CONTROL1)
            {
                _buf[_ctr++] = ch;
                _state = ST_INPKT;
            }
            else
                _state = ch == CONTROL2 ? ST_PKTDONE : ST_PKTERR;
            break;
        case ST_PKTERR:
            _state = ch == CONTROL1 ? ST_PKTERR_END : ST_PKTERR;
            break;
        case ST_PKTERR_END:
            _state = ch == CONTROL2 ? ST_BEFOREPKT : ST_PKTERR;
            break;
        default:
            _state = ST_PKTERR;
            break;
    }

    if (_state == ST_PKTERR
            || _state == ST_PKTERR_END)
    {
        _commStat.rxerr++;
        throw PckDecodeError();
    }

    if (_state == ST_PKTDONE)
    {
        _state = ST_BEFOREPKT;
        return _ctr;
    }

    return 0;
}

void TinySP::send_packet(const Packet & p)
{
    if (p.len + 4 >= MAX_BUF)
        throw PckWrongData();

    unsigned char pkt[MAX_BUF];

    unsigned i(0);
    int j(0);

    pkt[j++] = CONTROL1;
    pkt[j++] = p.id;

    while (i < p.len)
    {
        if (p.buf[i] == CONTROL1)
            pkt[j++] = CONTROL1;
        pkt[j++] = p.buf[i++];
    }

    pkt[j++] = CONTROL1;
    pkt[j++] = CONTROL2;

    if (write(_fds[0].fd, pkt, j) != j)
        throw PckIOError(::strerror(errno));

    _commStat.txbytes += j + 1;
    _commStat.txpkt++;
}

TinySP::Stats TinySP::get_stats() const
{
    return _commStat;
}
