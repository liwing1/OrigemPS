/*
//MOTO
*/
#ifndef MOTO_HPP
#define MOTO_HPP

#include <string>
#include "battery.hpp"
#include "host.hpp"

#define MAX_SPEED   60

using namespace std;

typedef enum{
    MOTO_STATE_SB,
    MOTO_STATE_ON,
    MOTO_STATE_ACCEL,
    MOTO_STATE_BREAK
}stateMoto_t;

class Battery;

class Moto : public Host{
    private:
        string plate;
        float speed;
        stateMoto_t state;

    public:
        Moto(string _plate, float _speed, Battery* _battery);
        ~Moto(void);

        int turnOn(void);
        int turnOff(void);

        void attatchBattery(Battery* _battery);
        void detatchBattery(void);

        int setAccelerator(bool set);
        int setBreaker(bool set);

        long long int getBattUid(void);
        float getBattSoc(void);

        int setPlate(string _plate);
        int setSpeed(float _speed);
        string getPlate(void);
        float getSpeed(void);
        Battery* getBattery(void);
        stateMoto_t getState(void);

        void updateAttributes(void);

};

#endif