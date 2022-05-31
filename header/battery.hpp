/*
//BATERIA
*/
#ifndef BATTERY_HPP
#define BATTERY_HPP


class Battery{
    protected:
        long long int uid;
        float soc;
        int host;

    public:
        Battery( long long int _uid, float _soc, int _host );
        ~Battery( void );

        int setUid( long long int _uid );
        int setSoc( float _soc );
        int setHost( int _host );

        long long int getUid( void );
        float getSoc( void );
        int getHost( void );
};

#endif