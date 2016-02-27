#ifndef TINYSP_HH
#define TINYSP_HH

#include <string>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <deque>
#include <exception>
#include <poll.h>
#include "serialport.hh"


#define MAX_BUF 64

struct PckException :
    public std::exception
{
};

struct PckDecodeError :
    public PckException
{
};

struct PckWrongData :
    public PckException
{
};

struct PckNoPacketsReady :
    public PckException
{
};

class PckIOError :
    public PckException
{
    private:
        std::string _s;
    public:
        PckIOError(const std::string &);
        virtual ~PckIOError() throw ();
        std::string str() const;
};


struct Packet
{
    unsigned char id;
    size_t len;
    unsigned char buf[MAX_BUF];
    Packet(unsigned char *, int);
    Packet(unsigned char, const std::deque<unsigned char> &);
    Packet(unsigned char);
};

enum COMM
{
    SERIAL = 0,
    BLUETOOTH = 1
};

class TinySP
{
    public:
        struct Stats
        {
            unsigned rxpkt;
            unsigned rxbytes;
            unsigned txpkt;
            unsigned txbytes;
            unsigned rxerr;
            Stats() : rxpkt(0), rxbytes(0), txpkt(0), txbytes(0), rxerr(0) { }
        };


    private:
        COMM _comm;
        bool _connected;

        unsigned char _buf[MAX_BUF];
        unsigned char _read_byte();
        int _decode_byte();
        int _state;
        int _ctr;
        Stats _commStat;
        struct pollfd _fds[1];

        // Serial port
        SerialPort _serialport;

        // Bluetooth
        std::string _mac;
        int _socket;
        struct sockaddr_rc _loc_addr;


    public:
        TinySP(std::string);
        TinySP(std::string, int);
        ~TinySP();

        std::string get_mac(void);
        std::string get_serial_port(void);
        void start_connection(void);
        void close_connection(void);
        bool get_connection_status(void);

        Packet read_packet();
        void send_packet(const Packet &);
        TinySP::Stats get_stats() const;
};

#endif
