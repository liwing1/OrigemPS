#include <iostream>
#include "etb.hpp"

using namespace std;

        // ETB( long int _uid, CP _cps[6] );
        // ~ETB( void );

        // int attBattToCP( Battery* _battery, int idx_cp );
        // int dttBattToCP( int idx_cp );

        // int initChgBattOnCP( int idx_cp );
        // int endChgBattOnCP( int idx_cp );

        // int getAmountBattTotal( void );
        // int getAmountBattChargin( void );

        // int getTimeToFinishCharging( int idx_cp );
        
        // int setUid(long int _uid);
        // int setCp(CP _cp, int idx_cp);

        // long int getUid( void );
        // CP getCp(int idx_cp);

ETB::ETB( long int _uid ) : uid(_uid), cps{0}{}

ETB::~ETB( void )
{
    cout << "ETB Destruido" << endl;
}