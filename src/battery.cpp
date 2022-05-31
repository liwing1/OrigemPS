#include <iostream>
#include "battery.hpp"

using namespace std;

class Host;

Battery::Battery( long long int _uid, float _soc , Host* _host) : host(_host)
{
    uid = _uid;
    soc = _soc;
    host = _host;
}

Battery::~Battery( void )
{
    return;
}

int Battery::setUid( long long int _uid )
{
    this->uid = _uid;
    return 0;
}


int Battery::setSoc( float _soc )
{
    if( _soc < 0 )
    {
        _soc = 0;
    }
    else if( _soc > 100 )
    {
        _soc = 100;
    }
    this->soc = _soc;
    return 0;
}


int Battery::setHost( Host* _host )
{
    this->host = _host;
    return 0;
}


long long int Battery::getUid( void )
{
    return this->uid;
}


float Battery::getSoc( void )
{
    return this->soc;
}


Host* Battery::getHost( void )
{
    return this->host;
}