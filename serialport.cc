/* vim: set sw=4 sts=4 et : */

#include "serialport.hh"
#include "stringify.hh"

#include <string>
#include <cerrno>
#include <cstring>

#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

#include <iostream>

SerialPortOptions::SerialPortOptions() :
    dev("/dev/null"),
    speed(0)
{
}

SerialPortOptions & SerialPortOptions::with_dev(const std::string & d)
{
    dev = d;
    return *this;
}

SerialPortOptions & SerialPortOptions::with_speed(unsigned s)
{
    speed = s;
    return *this;
}

SerialPort::SerialPort(const SerialPortOptions & o) :
    _opts(o)
{
    open_port();
    configure_port();
}

SerialPort::~SerialPort()
{
}

void SerialPort::open_port()
{
    _fd = open(_opts.dev.c_str(), O_RDWR | O_NDELAY | O_NOCTTY);

    if (_fd == -1){
        std::cout << "Failed in opening serial port " << _opts.dev.c_str() << std::endl;
        return;
    }

    tcflush(_fd, TCIOFLUSH);
    int n(fcntl(_fd, F_GETFL, 0));
    fcntl(_fd, F_SETFL, n & ~O_NDELAY);
    tcgetattr(_fd, &_oldtio);
}

/* XXX Throw if stuff goes wrong */
void SerialPort::configure_port()
{
    struct termios ptio;

    tcgetattr(_fd, &ptio);

    cfsetispeed(&ptio, _opts.speed);
    cfsetospeed(&ptio, _opts.speed);

    ptio.c_cflag |= CLOCAL | CREAD;
    ptio.c_cflag &= ~(PARENB | CSIZE | CSTOPB);
    ptio.c_cflag |= CS8;
    ptio.c_cflag &= ~CRTSCTS;

    ptio.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);

    ptio.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK
            | INPCK | ISTRIP | IXON);

    ptio.c_oflag &= ~OPOST;

    ptio.c_cc[VTIME] = 0;
    ptio.c_cc[VMIN] = 1;

    tcsetattr(_fd, TCSANOW, &ptio);

    int mcs(0);
    ioctl(_fd, TIOCMGET, &mcs);
    mcs |= TIOCM_RTS;
    ioctl(_fd, TIOCMSET, &mcs);

    tcgetattr(_fd, &ptio);

    ptio.c_cflag &= ~CRTSCTS;

    tcsetattr(_fd, TCSANOW, &ptio);
}

int SerialPort::get_fd() const
{
    return _fd;
}
