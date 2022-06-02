#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <stdio.h>
#include <cmath>
#include "battery.hpp"
#include "moto.hpp"
#include "etb.hpp"
#include "cp.hpp"
#include "simulation.hpp"

#define TIME_STAMP_1_SEC    1
#define TIME_STAMP_1_MIN    (60 * TIME_STAMP_1_SEC)
#define TIME_STAMP_30_MIN   (30 * TIME_STAMP_1_MIN)

#define TIME_STAMP_INIT_CHARGE_CP_4 (6 * TIME_STAMP_1_MIN + 40 * TIME_STAMP_1_SEC)
#define TIME_STAMP_INIT_CHARGE_CP_5 (10 * TIME_STAMP_1_MIN)
#define TIME_STAMP_INIT_CHARGE_CP_6 (13 * TIME_STAMP_1_MIN + 20 * TIME_STAMP_1_SEC)

using namespace std;
using std::vector;

int cont = 0;

void print_log(Moto* p_moto, ETB* p_etb);

int main() {

    /* Iniciaza CP, ETB, e as baterias*/
    CP* cps = new CP[8];
    ETB etb = ETB(789, cps);

    Battery battery1 = Battery(111, 100, NULL);
    cps[1].attatchBattery(&battery1);
    etb.initChgBattOnCP(1);

    Battery battery2 = Battery(222, 100, NULL);
    cps[2].attatchBattery(&battery2);
    etb.initChgBattOnCP(2);

    Battery battery3 = Battery(333, 100, NULL);
    cps[3].attatchBattery(&battery3);
    etb.initChgBattOnCP(3);

    Battery battery4 = Battery(444, 0, NULL);
    cps[4].attatchBattery(&battery4);

    Battery battery5 = Battery(555, 0, NULL);
    cps[5].attatchBattery(&battery5);

    Battery battery6 = Battery(666, 0, NULL);
    cps[6].attatchBattery(&battery6);


    /* Inicializa Moto e a bateria*/
    Moto moto = Moto("ASD-4567", 60, NULL);
    Battery battery_moto = Battery(999, 85, NULL);
    moto.attatchBattery(&battery_moto);

    /* Iniciar Simulacao */
    Simulation simulation = Simulation(SIMU_STATE_SIX_CICLES, 0, 0, 0, 0, 0);

    while(simulation.getTimeStamp() < (TIME_STAMP_30_MIN + 10 * TIME_STAMP_1_SEC)) //Simulacao roda ate 30:10
    {
        if(simulation.Advance(&simulation, &moto))
        {
            if(TIME_STAMP_INIT_CHARGE_CP_4 == simulation.getTimeStamp())
            {
                etb.initChgBattOnCP(4);
            }
            else if(TIME_STAMP_INIT_CHARGE_CP_5 == simulation.getTimeStamp())
            {
                etb.initChgBattOnCP(5);
            }
            else if(TIME_STAMP_INIT_CHARGE_CP_6 == simulation.getTimeStamp())
            {
                etb.initChgBattOnCP(6);
            }

            else if(TIME_STAMP_30_MIN == simulation.getTimeStamp())
            {
                //Momento de troca de bateria
                moto.detatchBattery();
                etb.dttBattToCP(1);

                etb.attBattToCP(&battery_moto, 1);
                etb.initChgBattOnCP(1);
            }

            else if((TIME_STAMP_30_MIN + 10 * TIME_STAMP_1_SEC) == simulation.getTimeStamp())
            {
                moto.attatchBattery(&battery1);
            }

            simulation.setTimeStamp(simulation.getTimeStamp() + 1);
            simulation.setTimeOutPrint(simulation.getTimeOutPrint() + 1);

            moto.updateAttributes();
            etb.updateAttributes();

            if((10 * TIME_STAMP_1_SEC) == simulation.getTimeOutPrint())
            {
                simulation.setTimeOutPrint(0);
                print_log(&moto, &etb);
            }

        }
    }

    return 0;
}


void print_log(Moto* p_moto, ETB* p_etb)
{
    cout << "Motorcycle plate: " << p_moto->getPlate() << endl;
    printf("Speed: %02.0f\n", p_moto->getSpeed());
    if(p_moto->getBattery() != NULL)
    {
        printf("Attatched Battery UID: %04lld\n", p_moto->getBattUid());
        printf("Motorcycle battery: %05.2f%%\n", p_moto->getBattSoc());
    }
    else
    {
        printf("Attatched Battery UID: NONE\n");
        printf("Motorcycle battery: NONE\n");
    }
    cout << endl;

    printf("ETB ID: %03ld\n", p_etb->getUid());

    for(int i = 1; i < 7; i++)
    {
        if(CP_STATE_EMPTY != p_etb->getBattStateofCP(i))
        {
            printf("CP %d: [UID %04lld | SoC %05.2f | charging: %s]\n",
            i,
            p_etb->getBattUidOfCP(i),
            p_etb->getBattSocOfCP(i),
            p_etb->getBattStateofCP(i) == CP_STATE_CHARGING ? "YES" : "NO");
        }
        else
        {
            printf("CP %d: [UID NONE | SoC NONE | charging: NO]", i);
        }
    }
    cout << endl;
}