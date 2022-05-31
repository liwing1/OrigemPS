#ifndef ETB_HPP
#define ETB_HPP

#include "battery.hpp"
#include "cp.hpp"

class ETB{
    protected:
        long int uid;
        CP* cps;

    public:
        ETB( long int _uid, CP* _cps );
        ~ETB( void );

        int attBattToCP( Battery* _battery, int idx_cp );
        int dttBattToCP( int idx_cp );

        int initChgBattOnCP( int idx_cp );
        int endChgBattOnCP( int idx_cp );

        int getAmountOfBattTotal( void );
        int getAmountOfBattCharging( void );

        long long int getBattUidOfCP( int idx_cp );
        float getBattSocOfCP( int idx_cp );
        stateCP_t getBattStateofCP( int idx_cp );

        int getTimeToFinishCharging( int idx_cp );
        
        int setUid(long int _uid);
        int setCp(CP _cp, int _idx_cp);

        long int getUid( void );
        CP getCp(int idx_cp);
};

#endif