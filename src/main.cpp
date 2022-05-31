#include <iostream>
#include <string>
#include "battery.hpp"
#include "moto.hpp"
#include "etb.hpp"
#include "cp.hpp"

using namespace std;


int main() {

    Moto moto = Moto("ASD", 60, NULL);

    Battery battery = Battery( 123, 85, &moto);

    moto.attBatt(&battery);

    cout << moto.getBattUid();

    
    std::cout << "Hello World!\n";

    return 0;
}