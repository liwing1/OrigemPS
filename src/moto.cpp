#include <iostream>
#include <string>
#include "moto.hpp"


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

    // int triggerAccelerator( void );
    // int triggerBreaker( void );
    // int releaseBreaker( void );

int Moto::turnOn( void )
{
    if( Moto::battery->getHost() == ATT_TO_MOTO )
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