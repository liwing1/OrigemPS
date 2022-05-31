#include <iostream>
#include "cp.hpp"

class Battery;


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
    this->battery->setHost(NULL);
    this->battery = NULL;
}

void CP::setState( stateCP_t _state )
{
    this->state = _state;
}

stateCP_t CP::getState( void )
{
    return this->state;
}