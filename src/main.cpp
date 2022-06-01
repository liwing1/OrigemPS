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

#define ADVANCE_SIMU    1
#define HALT_SIMU       0

#define TIME_STAMP_1_SEC    1
#define TIME_STAMP_1_MIN    (60 * TIME_STAMP_1_SEC)
#define TIME_STAMP_30_MIN   (30 * TIME_STAMP_1_MIN)

#define TIME_STAMP_INIT_CHARGE_CP_4 (6 * TIME_STAMP_1_MIN + 40 * TIME_STAMP_1_SEC)
#define TIME_STAMP_INIT_CHARGE_CP_5 (10 * TIME_STAMP_1_MIN)
#define TIME_STAMP_INIT_CHARGE_CP_6 (13 * TIME_STAMP_1_MIN + 20 * TIME_STAMP_1_SEC)


using namespace std;
using std::vector;

typedef enum{
    SIMU_STATE_SIX_CICLES,
    SIMU_STATE_FOUR_CICLES,
    SIMU_STATE_ACCEL,
    SIMU_STATE_BREAK,
    SIMU_STATE_END
}simulation_states_t;

typedef struct{
    simulation_states_t state;
    int timeOutAccel;
    int timeOutBreak;
    int timeOutPrint;
    int timeStamp;
    int cicleCounter;
}simulation_t;

int cont = 0;

int simulation_advance(simulation_t* , Moto* p_moto);
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
    Battery battery_moto = Battery(000, 85, NULL);
    moto.attatchBattery(&battery_moto);

    /* Iniciar Simulacao */
    simulation_t simulation = {
        .state = SIMU_STATE_SIX_CICLES,
        .timeOutAccel = 0,
        .timeOutBreak = 0,
        .timeOutPrint = 0,
        .timeStamp = 0,
        .cicleCounter = 0
    };

    while(simulation.timeStamp < (TIME_STAMP_30_MIN + 10 * TIME_STAMP_1_SEC)) //Simulacao roda ate 30:10
    {
        if(simulation_advance(&simulation, &moto))
        {
            if(simulation.timeStamp == TIME_STAMP_INIT_CHARGE_CP_4)
            {
                etb.initChgBattOnCP(4);
            }
            else if(simulation.timeStamp == TIME_STAMP_INIT_CHARGE_CP_5)
            {
                etb.initChgBattOnCP(5);
            }
            else if(simulation.timeStamp == TIME_STAMP_INIT_CHARGE_CP_6)
            {
                etb.initChgBattOnCP(6);
            }

            else if(simulation.timeStamp == TIME_STAMP_30_MIN)
            {
                //Momento de troca de bateria
                moto.detatchBattery();
                etb.dttBattToCP(1);

                etb.attBattToCP(&battery_moto, 1);
                etb.initChgBattOnCP(1);
            }

            else if(simulation.timeStamp == TIME_STAMP_30_MIN + 10 * TIME_STAMP_1_SEC)
            {
                moto.attatchBattery(&battery1);
            }

            simulation.timeStamp++;
            simulation.timeOutPrint++;

            moto.updateAttributes();
            etb.updateAttributes();

            if(simulation.timeOutPrint == (10 * TIME_STAMP_1_SEC))
            {
                simulation.timeOutPrint = 0;
                print_log(&moto, &etb);
            }

        }
    }

    return 0;
}


int simulation_advance(simulation_t* p_simulation, Moto* p_moto)
{
    switch (p_simulation->state)
    {
        case SIMU_STATE_SIX_CICLES:
        {
            if(p_simulation->timeOutBreak == 0 && p_simulation->timeOutAccel == 0)
            {
                p_simulation->timeOutAccel = 180;
                p_simulation->timeOutBreak = 10;
                p_simulation->cicleCounter++;
            }

            if(p_simulation->cicleCounter > 6)
            {
                p_simulation->timeOutAccel = 0;
                p_simulation->timeOutBreak = 0;
                p_simulation->cicleCounter = 0;
                p_simulation->state = SIMU_STATE_FOUR_CICLES;
                return HALT_SIMU;
            }

            if(p_simulation->timeOutAccel)
            {  
                p_moto->setAccelerator(true);
                p_simulation->timeOutAccel--;
            }
            else if(p_simulation->timeOutBreak)
            {
                p_moto->setBreaker(true);
                p_simulation->timeOutBreak--;
            }
            
            break;   
        }
        
        case SIMU_STATE_FOUR_CICLES:
        {
            if(p_simulation->timeOutBreak == 0 && p_simulation->timeOutAccel == 0)
            {
                p_simulation->timeOutAccel = 120;
                p_simulation->timeOutBreak = 12;
                p_simulation->cicleCounter++;
            }

            if(p_simulation->cicleCounter > 4)
            {
                p_simulation->timeOutAccel = 0;
                p_simulation->timeOutBreak = 0;
                p_simulation->cicleCounter = 0;
                p_simulation->state = SIMU_STATE_ACCEL;
                return HALT_SIMU;
            }

            if(p_simulation->timeOutAccel)
            {  
                p_moto->setAccelerator(true);
                p_simulation->timeOutAccel--;
            }
            else if(p_simulation->timeOutBreak)
            {
                p_moto->setBreaker(true);
                p_simulation->timeOutBreak--;
            }
            
            break;   
        }

        case SIMU_STATE_ACCEL:
        {
            if(p_simulation->timeOutBreak == 0 && p_simulation->timeOutAccel == 0)
            {
                p_simulation->timeOutAccel = 100;
                p_simulation->timeOutBreak = 0;
                p_simulation->cicleCounter++;
            }

            if(p_simulation->cicleCounter > 1)
            {
                p_simulation->timeOutAccel = 0;
                p_simulation->timeOutBreak = 0;
                p_simulation->cicleCounter = 0;
                p_simulation->state = SIMU_STATE_BREAK;
                return HALT_SIMU;
            }

            if(p_simulation->timeOutAccel)
            {  
                p_moto->setAccelerator(true);
                p_simulation->timeOutAccel--;
            }
            
            
            break;   
        }

        case SIMU_STATE_BREAK:
        {
            if(p_simulation->timeOutBreak == 0 && p_simulation->timeOutAccel == 0)
            {
                p_simulation->timeOutAccel = 0;
                p_simulation->timeOutBreak = 32;
                p_simulation->cicleCounter++;
            }

            if(p_simulation->cicleCounter > 1)
            {
                p_simulation->timeOutAccel = 0;
                p_simulation->timeOutBreak = 0;
                p_simulation->cicleCounter = 0;
                p_simulation->state = SIMU_STATE_END;
                return HALT_SIMU;
            }

            if(p_simulation->timeOutBreak)
            {
                p_moto->setBreaker(true);
                p_simulation->timeOutBreak--;
            }
            
            break;   
        }

        case SIMU_STATE_END:
        {
            return ADVANCE_SIMU;
            break;
        }

        default:
            return HALT_SIMU;
            break;
    }
    return ADVANCE_SIMU;

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
        if(CP_EMPTY != p_etb->getBattStateofCP(i))
        {
            printf("CP %d: [UID %04lld | SoC %05.2f | charging: %s]\n",
            i,
            p_etb->getBattUidOfCP(i),
            p_etb->getBattSocOfCP(i),
            p_etb->getBattStateofCP(i) == CP_CHARGING ? "YES" : "NO");
        }
        else
        {
            printf("CP %d: [UID NONE | SoC NONE | charging: NO]", i);
        }
    }
    cout << endl;
}