/*
//MOTO
*/
#ifndef MOTO_HPP
#define MOTO_HPP

#include <string>
#include "battery.hpp"
#include "host.hpp"

using namespace std;

typedef enum{
    STAND_BY,
    ON
}stateMoto_t;

class Battery;

class Moto : public Host{
    private:
        string plate;
        float speed;
        stateMoto_t state;

    public:
        Moto( string _plate, float _speed, Battery* _battery);
        ~Moto( void );

        int turnOn( void );
        int turnOff( void );

        void attatchBattery( Battery* _battery );
        void detatchBattery( void );

        int toggleAccelerator( void );
        int toggleBreaker( void );

        long long int getBattUid( void );
        float getBattSoc( void );

        int setPlate( string _plate );
        int setSpeed( float _speed );
        string getPlate( void );
        float getSpeed( void );
        Battery* getBattery( void );

};

#endif