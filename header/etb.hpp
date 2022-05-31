#ifndef ETB_HPP
#define ETB_HPP

#include "battery.hpp"
#include "cp.hpp"

class ETB{
    private:
        long int uid;
        CP* cps;

    public:
        ETB( long int _uid );
        ~ETB( void );

        int attBattToCP( Battery* _battery, int idx_cp );
        int dttBattToCP( int idx_cp );

        int initChgBattOnCP( int idx_cp );
        int endChgBattOnCP( int idx_cp );

        int getAmountBattTotal( void );
        int getAmountBattChargin( void );

        int getTimeToFinishCharging( int idx_cp );
        
        int setUid(long int _uid);
        int setCp(CP _cp, int idx_cp);

        long int getUid( void );
        CP getCp(int idx_cp);
};

#endif