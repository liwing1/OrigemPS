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

    /* Iniciaza CP, ETB, e as baterias*/
    CP* cps = new CP[8];
    ETB etb = ETB(789, cps);

    Battery battery1 = Battery( 111, 100, NULL);
    cps[1].attatchBattery(&battery1);

    Battery battery2 = Battery( 222, 100, NULL);
    cps[2].attatchBattery(&battery2);

    Battery battery3 = Battery( 333, 100, NULL);
    cps[3].attatchBattery(&battery3);

    Battery battery4 = Battery( 444, 70, NULL);
    cps[4].attatchBattery(&battery4);

    Battery battery5 = Battery( 555, 60, NULL);
    cps[5].attatchBattery(&battery5);

    Battery battery6 = Battery( 666, 50, NULL);
    cps[6].attatchBattery(&battery6);

    /* Inicializa Moto e a bateria*/
    Moto moto = Moto("ASD-4567", 60, NULL);
    Battery battery = Battery( 111, 100, &moto);

    cout << etb.getAmountOfBattTotal() << endl;

    if(battery.getHost())
    {
        std::cout << "Bateria tem Host!\n";
    }

    return 0;
}