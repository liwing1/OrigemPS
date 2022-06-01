#include <iostream>
#include "host.hpp"

class Battery;

void Host::attatchBattery(Battery* _battery)
{
    this->battery = _battery;
}

void Host::detatchBattery(void)
{
    this->battery = NULL;
}