#include <iostream>
#include <string>
#include "battery.hpp"
#include "moto.hpp"

using namespace std;


int main() {

    Battery battery = Battery( 123, 85, 2 );

    Moto moto = Moto("ASD", 60, &battery);
    
    std::cout << "Hello World!\n";

    return 0;
}