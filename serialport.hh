/* vim: set sw=4 sts=4 et : */

#ifndef SERIALPORT_HH
#define SERIALPORT_HH 1

// #include <base/util/attributes.hh>

#include <string>
#include <termios.h>

struct SerialPortOptions
{
    std::string dev;
    unsigned speed;

    SerialPortOptions();
    SerialPortOptions & with_dev(const std::string &);
    SerialPortOptions & with_speed(unsigned);
};

class SerialPort
{
    private:
        const SerialPortOptions & _opts;
        int _fd;
        struct termios _oldtio;

    public:
        SerialPort(const SerialPortOptions & = SerialPortOptions());
        ~SerialPort();

        void open_port();
        void configure_port();
        int get_fd() const;
};

#endif
