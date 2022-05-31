#ifndef CP_HPP
#define CP_HPP

#include "battery.hpp"
#include "host.hpp"

class Battery;

class CP : public Host{
    int state;

    public:
    CP( int _state );
    ~CP( void );

    void attatchBattery( Battery* _battery );
    void detatchBattery( void );
};

#endif