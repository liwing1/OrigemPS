/*
//MOTO
*/
#include <string>
#include "battery.hpp"

using namespace std;

typedef enum{
    STAND_BY,
    ON
}stateMoto_t;

class Moto{
    private:
        string plate;
        float speed;
        stateMoto_t state;
        Battery* battery;

    public:
        Moto( string _plate, float _speed, Battery* _battery);
        ~Moto( void );

        int turnOn( void );
        int turnOff( void );

        int attBatt( Battery* _battery );
        int dttBatt( void );

        int triggerAccelerator( void );
        int triggerBreaker( void );
        int releaseBreaker( void );

};