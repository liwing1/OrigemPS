#include <iostream>
#include <string>
#include "battery.hpp"
#include "moto.hpp"
#include "etb.hpp"
#include "cp.hpp"

using namespace std;


int main() {

    Battery battery = Battery( 123, 85, NULL);

    Moto moto = Moto("ASD", 60, NULL);

    moto.attatchBattery(&battery);

    cout << moto.getBattUid() << endl;

    if(battery.getHost())
    {
        std::cout << "Hello World!\n";
    }

    return 0;
}