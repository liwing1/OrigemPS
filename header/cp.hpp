#ifndef CP_HPP
#define CP_HPP

#include "battery.hpp"
#include "host.hpp"

typedef enum{
    CP_EMPTY,
    CP_ATTATCHED,
    CP_CHARGING,
}stateCP_t;

class Battery;

class CP : public Host{
    stateCP_t state;

    public:
    CP() = default;
    ~CP( void );

    void attatchBattery( Battery* _battery );
    void detatchBattery( void );

    void setState( stateCP_t _state );
    stateCP_t getState( void );

    void setBattUid( long long int _uid );
    void setBattSoc( long _soc );
    long long int getBattUid( void );
    float getBattSoc( void );
};

#endif