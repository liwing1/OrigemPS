#include <iostream>
#include <string>
#include "moto.hpp"
#include "battery.hpp"


using namespace std;


Moto::Moto( string _plate, float _speed, Battery* _battery)
{
    plate = _plate;
    speed = _speed;
    battery = _battery;
    if(this->battery != NULL)
    {
        this->battery->setHost(this);
    }
}


Moto::~Moto( void )
{
    return;
}


void Moto::attatchBattery( Battery* _battery )
{
    this->battery = _battery;
    this->battery->setHost(this);
}


void Moto::detatchBattery( void )
{
    this->battery->setHost(NULL);
    this->battery = NULL;
}


long long int Moto::getBattUid( void )
{
    return this->battery->getUid();
}


float Moto::getBattSoc( void )
{
    return this->battery->getSoc();
}


int Moto::setPlate( string _plate )
{
    this->plate = _plate;
    return 0;
}

int Moto::setSpeed( float _speed )
{
    if( _speed > MAX_SPEED )
    {
        _speed = MAX_SPEED;
    }
    else if ( _speed < 0 )
    {
        _speed = 0;
    }

    if( _speed > this->speed )  // Velocidade so aumenta se tiver bateria
    {
        if( this->battery->getSoc() > 0)
        {
            this->speed = _speed;
        }
    }
    else
    {
        this->speed = _speed;
    }
    
    return 0;
}

string Moto::getPlate( void )
{
    return this->plate;
}

float Moto::getSpeed( void )
{
    return this->speed;
}

Battery* Moto::getBattery( void )
{
    return this->battery;
}

int Moto::turnOn( void )
{
    if(this->state == MOTO_STATE_SB)
    {
        this->state = MOTO_STATE_ON;
    }
    else
    {
        return 1;
    }
    return 0;
}

int Moto::turnOff( void )
{
    if(this->state != MOTO_STATE_SB)
    {
        this->state = MOTO_STATE_SB;
    }
    else
    {
        return 1;
    }
    return 0;
}

int Moto::setAccelerator( bool set )
{
    if(this->state != MOTO_STATE_SB)    // Verifica se esta ligada
    {
        if(set)
        {
            this->state = MOTO_STATE_ACCEL;
        }
        else
        {
            this->state = MOTO_STATE_ON;
        }
    }
    else
    {
        return 1;
    }
    return 0;
}

int Moto::setBreaker( bool set )
{
    if(this->state != MOTO_STATE_SB)    // Verifica se esta ligada
    {
        if(set)
        {
            this->state = MOTO_STATE_BREAK;
        }
        else
        {
            this->state = MOTO_STATE_ON;
        }
    }
    else
    {
        return 1;
    }
    return 0;
}

stateMoto_t Moto::getState( void )
{
    return this->state;
}