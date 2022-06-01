#include <iostream>
#include "etb.hpp"
#include "battery.hpp"

using namespace std;


ETB::ETB(long int _uid, CP* _cps){
    uid = _uid;
    cps = _cps;
}

ETB::~ETB(void)
{
    return;
}

int ETB::attBattToCP(Battery* _battery, int idx_cp)
{
    this->cps[idx_cp].attatchBattery(_battery);
    this->cps[idx_cp].setState(CP_STATE_ATTATCHED);
    return 0;
}

int ETB::dttBattToCP(int idx_cp)
{
    this->cps[idx_cp].setState(CP_STATE_EMPTY);
    this->cps[idx_cp].detatchBattery();
    return 0;
}

int ETB::getAmountOfBattTotal(void)
{
    int amountOfBatteries = 0;
    for(int i = 0; i < 8; i++)
    {
        if(this->cps[i].getState())
        {
            amountOfBatteries++;
        }
    }
    return amountOfBatteries;
}

int ETB::getAmountOfBattCharging(void)
{
    int amountOfBatteries = 0;
    for(int i = 0; i < 6; i++)
    {
        if(CP_STATE_CHARGING == this->cps[i].getState())
        {
            amountOfBatteries++;
        }
    }
    return amountOfBatteries;
}

int ETB::setUid(long int _uid)
{
    this->uid = _uid;
    return 0;
}

int ETB::setCp(CP _cp, int _idx_cp)
{
    this->cps[_idx_cp] = _cp;
    return 0;
}

long int ETB::getUid(void)
{
    return this->uid;
}

CP ETB::getCp(int idx_cp)
{
    return this->cps[idx_cp];
}

int ETB::initChgBattOnCP(int idx_cp)
{
    if(CP_STATE_ATTATCHED == this->cps[idx_cp].getState())
    {
        this->cps[idx_cp].setState(CP_STATE_CHARGING);
    }
    else
    {
        return 1;
    }
    return 0;
}

int ETB::endChgBattOnCP(int idx_cp)
{
    if(CP_STATE_CHARGING == this->cps[idx_cp].getState())
    {
        this->cps[idx_cp].setState(CP_STATE_ATTATCHED);
    }
    else
    {
        return 1;
    }
    return 0;
}


long long int ETB::getBattUidOfCP(int idx_cp)
{
    return this->cps[idx_cp].getBattUid();
}


float ETB::getBattSocOfCP(int idx_cp)
{
    return this->cps[idx_cp].getBattSoc();
}


stateCP_t ETB::getBattStateofCP(int idx_cp)
{
    return this->cps[idx_cp].getState();
}


void ETB::updateAttributes(void)
{
    for(int i = 1; i < 7; i++)
    {
        if(CP_STATE_CHARGING == this->cps[i].getState())
        {
            this->cps[i].setBattSoc(this->cps[i].getBattSoc() + 0.05);
        }
        else if(CP_STATE_ATTATCHED == this->cps[i].getState())
        {
            this->cps[i].setBattSoc(this->cps[i].getBattSoc() - 0.01);
        }
    }
}