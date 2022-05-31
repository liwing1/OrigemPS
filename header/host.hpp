#ifndef HOST_HPP
#define HOST_HPP

#include "battery.hpp"

class Battery;

class Host{
    protected:
        Battery* battery;

    public:
        void attatchBattery();
        void detatchBattery();
};

#endif