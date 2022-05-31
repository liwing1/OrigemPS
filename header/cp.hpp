#ifndef CP_HPP
#define CP_HPP

#include "battery.hpp"
#include "host.hpp"

class Battery;

class CP : public Host{
    Battery* battery;
    int state;

    public:
    CP( int _state );
    ~CP( void );
};

#endif