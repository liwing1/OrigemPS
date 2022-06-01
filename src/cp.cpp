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
    this->setState(CP_ATTATCHED);
}

void CP::detatchBattery( void )
{
    this->setState(CP_EMPTY);
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

long long int CP::getBattUid( void )
{
    return this->battery->getUid();
}

float CP::getBattSoc( void )
{
    return this->battery->getSoc();
}

void CP::setBattUid( long long int _uid )
{
    this->battery->setUid( _uid );
}

void CP::setBattSoc( float _soc )
{
    this->battery->setSoc( _soc );
}