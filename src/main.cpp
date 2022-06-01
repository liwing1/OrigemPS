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

#define ADVANCE_SIMU    1;
#define HALT_SIMU       0;

using namespace std;
using std::vector;

typedef enum{
    STATE_SIX_CICLES,
    STATE_FOUR_CICLES,
    STATE_ACCEL,
    STATE_BREAK,
    STATE_END_SIM
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

int simulation_advance( simulation_t* , Moto* p_moto );
void print_log( Moto* p_moto, ETB* p_etb );

int main() {

    /* Iniciaza CP, ETB, e as baterias*/
    CP* cps = new CP[8];
    ETB etb = ETB(789, cps);

    Battery battery1 = Battery( 111, 100, NULL);
    cps[1].attatchBattery(&battery1);
    etb.initChgBattOnCP(1);

    Battery battery2 = Battery( 222, 100, NULL);
    cps[2].attatchBattery(&battery2);
    etb.initChgBattOnCP(2);

    Battery battery3 = Battery( 333, 100, NULL);
    cps[3].attatchBattery(&battery3);
    etb.initChgBattOnCP(3);

    Battery battery4 = Battery( 444, 0, NULL);
    cps[4].attatchBattery(&battery4);

    Battery battery5 = Battery( 555, 0, NULL);
    cps[5].attatchBattery(&battery5);

    Battery battery6 = Battery( 666, 0, NULL);
    cps[6].attatchBattery(&battery6);


    /* Inicializa Moto e a bateria*/
    Moto moto = Moto("ASD-4567", 60, NULL);
    Battery battery = Battery( 000, 85, NULL);
    moto.attatchBattery(&battery);

    /* Iniciar Simulacao */
    simulation_t simulation = {
        .state = STATE_SIX_CICLES,
        .timeOutAccel = 0,
        .timeOutBreak = 0,
        .timeOutPrint = 0,
        .timeStamp = 0,
        .cicleCounter = 0
    };

    while(simulation.timeStamp < 1800)
    {
        if(simulation_advance(&simulation, &moto))
        {
            if( simulation.timeStamp == 400 )
            {
                etb.initChgBattOnCP(4);
            }
            else if( simulation.timeStamp == 600 )
            {
                etb.initChgBattOnCP(5);
            }
            else if( simulation.timeStamp == 800 )
            {
                etb.initChgBattOnCP(6);
            }

            simulation.timeStamp++;
            simulation.timeOutPrint++;

            moto.updateAttributes();
            etb.updateAttributes();

            if(simulation.timeOutPrint == 10)
            {
                simulation.timeOutPrint = 0;
                print_log( &moto, &etb );
            }

        }
    }

    //Momento de troca de bateria
    moto.detatchBattery();
    etb.dttBattToCP(1);

    etb.attBattToCP(&battery, 1);
    etb.initChgBattOnCP(1);

    //Passa 10 segundos
    simulation.timeStamp += 10;

    moto.attatchBattery(&battery1);

    print_log( &moto, &etb );

    return 0;
}


int simulation_advance( simulation_t* p_simulation, Moto* p_moto )
{
    switch (p_simulation->state)
    {
        case STATE_SIX_CICLES:
        {
            if( p_simulation->timeOutBreak == 0 && p_simulation->timeOutAccel == 0 )
            {
                p_simulation->timeOutAccel = 180;
                p_simulation->timeOutBreak = 10;
                p_simulation->cicleCounter++;
            }

            if( p_simulation->cicleCounter > 6 )
            {
                p_simulation->timeOutAccel = 0;
                p_simulation->timeOutBreak = 0;
                p_simulation->cicleCounter = 0;
                p_simulation->state = STATE_FOUR_CICLES;
                return HALT_SIMU;
            }

            if( p_simulation->timeOutAccel )
            {  
                p_moto->setAccelerator(true);
                p_simulation->timeOutAccel--;
            }
            else if( p_simulation->timeOutBreak )
            {
                p_moto->setBreaker(true);
                p_simulation->timeOutBreak--;
            }
            
            break;   
        }
        
        case STATE_FOUR_CICLES:
        {
            if( p_simulation->timeOutBreak == 0 && p_simulation->timeOutAccel == 0 )
            {
                p_simulation->timeOutAccel = 120;
                p_simulation->timeOutBreak = 12;
                p_simulation->cicleCounter++;
            }

            if( p_simulation->cicleCounter > 4 )
            {
                p_simulation->timeOutAccel = 0;
                p_simulation->timeOutBreak = 0;
                p_simulation->cicleCounter = 0;
                p_simulation->state = STATE_ACCEL;
                return HALT_SIMU;
            }

            if( p_simulation->timeOutAccel )
            {  
                p_moto->setAccelerator(true);
                p_simulation->timeOutAccel--;
            }
            else if( p_simulation->timeOutBreak )
            {
                p_moto->setBreaker(true);
                p_simulation->timeOutBreak--;
            }
            
            break;   
        }

        case STATE_ACCEL:
        {
            if( p_simulation->timeOutBreak == 0 && p_simulation->timeOutAccel == 0 )
            {
                p_simulation->timeOutAccel = 100;
                p_simulation->timeOutBreak = 0;
                p_simulation->cicleCounter++;
            }

            if( p_simulation->cicleCounter > 1 )
            {
                p_simulation->timeOutAccel = 0;
                p_simulation->timeOutBreak = 0;
                p_simulation->cicleCounter = 0;
                p_simulation->state = STATE_BREAK;
                return HALT_SIMU;
            }

            if( p_simulation->timeOutAccel )
            {  
                p_moto->setAccelerator(true);
                p_simulation->timeOutAccel--;
            }
            
            
            break;   
        }

        case STATE_BREAK:
        {
            if( p_simulation->timeOutBreak == 0 && p_simulation->timeOutAccel == 0 )
            {
                p_simulation->timeOutAccel = 0;
                p_simulation->timeOutBreak = 32;
                p_simulation->cicleCounter++;
            }

            if( p_simulation->cicleCounter > 1 )
            {
                p_simulation->timeOutAccel = 0;
                p_simulation->timeOutBreak = 0;
                p_simulation->cicleCounter = 0;
                p_simulation->state = STATE_END_SIM;
                return HALT_SIMU;
            }

            if( p_simulation->timeOutBreak )
            {
                p_moto->setBreaker(true);
                p_simulation->timeOutBreak--;
            }
            
            break;   
        }

        case STATE_END_SIM:
        {
            return HALT_SIMU;
            break;
        }

        default:
            return HALT_SIMU;
            break;
    }
    return ADVANCE_SIMU;

}


void print_log( Moto* p_moto, ETB* p_etb )
{
    cout << "Motorcycle plate: " << p_moto->getPlate() << endl;
    printf("Speed: %02.0f\n", p_moto->getSpeed());
    printf("Attatched Battery UID: %04lld\n", p_moto->getBattUid());
    printf("Motorcycle battery: %05.2f\n", p_moto->getBattSoc());
    cout << endl;

    printf("ETB ID: %03ld\n", p_etb->getUid());

    for(int i = 1; i < 7; i++)
    {
        printf("CP %d: [UID %04lld| SoC %05.2f | charging : %s]\n",
        i,
        p_etb->getBattUidOfCP(i),
        p_etb->getBattSocOfCP(i),
        p_etb->getBattStateofCP(i) == CP_CHARGING ? "YES" : "NO" );
    }
    cout << endl;
}