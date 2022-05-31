#include <iostream>
#include <string>
#include <vector>
#include "battery.hpp"
#include "moto.hpp"
#include "etb.hpp"
#include "cp.hpp"

using namespace std;
using std::vector;


int main() {

    Battery battery = Battery( 123, 85, NULL);
    Moto moto = Moto("ASD-4567", 60, NULL);
    CP* cps = new CP[6];
    ETB etb = ETB(789, cps);

    moto.attatchBattery(&battery);
    moto.detatchBattery();

    etb.attBattToCP(&battery, 1);
    etb.initChgBattOnCP(1);

    cout << etb.getAmountOfBattCharging() << endl;

    if(battery.getHost())
    {
        std::cout << "Bateria tem Host!\n";
    }

    return 0;
}