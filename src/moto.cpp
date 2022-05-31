#include <iostream>
#include <string>
#include "moto.hpp"
#include "battery.hpp"


using namespace std;

enum HOST{
    ATT_TO_NONE,
    ATT_TO_MOTO,
    ATT_TO_ETB
};

Moto::Moto( string _plate, float _speed, Battery* _battery)
{
    plate = _plate;
    speed = _speed;
    battery = _battery;
}


Moto::~Moto( void )
{
    cout << "Moto Destruida!" << endl;
}


int Moto::turnOn( void )
{
    if( Moto::battery != NULL )
    {
        if( Moto::battery->getSoc() > 0 && Moto::battery->getSoc() <= 100 )
        {
            Moto::state = ON;   
        }
        else
        {
            cout << "Bateria < 0 ou > 100!" << endl;
            return 1;
        }
    }
    return 0;
}


int Moto::turnOff( void )
{
    Moto::state = STAND_BY;
    return 0;
}


int Moto::attBatt( Battery* _battery )
{
    Moto::battery = _battery;
    return 0;
}


int Moto::dttBatt( void )
{
    this->battery = NULL;
    return 0;
}


long long int Moto::getBattUid( void )
{
    return this->battery->getUid();
}


float Moto::getBattSoc( void )
{
    return this->battery->getSoc();
}