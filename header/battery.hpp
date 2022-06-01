/*
//BATERIA
*/
#ifndef BATTERY_HPP
#define BATTERY_HPP


#include "moto.hpp"
#include "cp.hpp"

class Host;

class Battery{
    private:
        long long int uid;
        float soc;
        Host* host;

    public:
        Battery(long long int _uid, float _soc, Host* _host);
        ~Battery(void);

        int setUid(long long int _uid);
        int setSoc(float _soc);
        int setHost(Host* host);

        long long int getUid(void);
        float getSoc(void);
        Host* getHost(void);
};


#endif