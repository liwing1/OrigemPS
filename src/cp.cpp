#include <iostream>
#include "cp.hpp"

class Battery;

CP::CP(int _state)
{
    state = _state;
}

CP::~CP( void )
{
    return;
}

void CP::attatchBattery( Battery* _battery )
{
    this->battery = _battery;
    this->battery->setHost(this);
}

void CP::detatchBattery( void )
{
    this->battery = NULL;
    this->battery->setHost(NULL);
}