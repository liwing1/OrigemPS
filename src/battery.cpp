#include <iostream>
#include "battery.hpp"

using namespace std;

Battery::Battery( long long int _uid, float _soc, int _host )
{
    uid = _uid;
    soc = _soc;
    host = _host;
}

Battery::~Battery( void )
{
    cout << "Bateria destruida!" << endl;
}
    // int setUid( long long int uid );
    // int setSoc( float soc );
    // int setHost( int host );

    // long long int getUid( void );
    // float getSoc( void );
    // int getHost( void );

int Battery::setUid( long long int _uid )
{
    Battery::uid = _uid;
    return 0;
}


int Battery::setSoc( float _soc )
{
    Battery::soc = _soc;
    return 0;
}


int Battery::setHost( int _host )
{
    Battery::host = _host;
    return 0;
}


long long int Battery::getUid( void )
{
    return Battery::uid;
}


float Battery::getSoc( void )
{
    return Battery::soc;
}


int Battery::getHost( void )
{
    return Battery::host;
}