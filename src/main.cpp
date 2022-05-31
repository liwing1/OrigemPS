#include <iostream>
#include <string>
#include <vector>
#include "battery.hpp"
#include "moto.hpp"
#include "etb.hpp"
#include "cp.hpp"

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
    int timeOutSimul;
    int cicleCounter;
}simulation_t;

int cont = 0;

void simulation_state_mng( simulation_t* , Moto* p_moto );
void process_dynamic_model( void );

int main() {

    /* Iniciaza CP, ETB, e as baterias*/
    CP* cps = new CP[8];
    ETB etb = ETB(789, cps);

    Battery battery1 = Battery( 111, 100, NULL);
    cps[1].attatchBattery(&battery1);

    Battery battery2 = Battery( 222, 100, NULL);
    cps[2].attatchBattery(&battery2);

    Battery battery3 = Battery( 333, 100, NULL);
    cps[3].attatchBattery(&battery3);

    Battery battery4 = Battery( 444, 70, NULL);
    cps[4].attatchBattery(&battery4);

    Battery battery5 = Battery( 555, 60, NULL);
    cps[5].attatchBattery(&battery5);

    Battery battery6 = Battery( 666, 50, NULL);
    cps[6].attatchBattery(&battery6);


    /* Inicializa Moto e a bateria*/
    Moto moto = Moto("ASD-4567", 60, NULL);
    Battery battery = Battery( 000, 85, NULL);
    moto.attatchBattery(&battery);

    /* Iniciar Simulacao */
    simulation_t simulation = {
        .state = STATE_SIX_CICLES,
        .timeOutAccel = 180,
        .timeOutBreak = 10,
        .timeOutSimul = 1800,
        .cicleCounter = 0
    };

    while(simulation.timeOutSimul--)
    {
        simulation_state_mng(&simulation, &moto);
        // process_dynamic_model();
    }

    return 0;
}


void simulation_state_mng( simulation_t* p_simulation, Moto* p_moto )
{
    switch (p_simulation->state)
    {
        case STATE_SIX_CICLES:
        {
            if( p_simulation->timeOutAccel )
            {
                p_moto->setAccelerator(true);
                p_simulation->timeOutAccel--;
            }
            else if( p_simulation->timeOutBreak )
            {
                p_moto->setAccelerator(false);
                p_simulation->timeOutBreak--;
            }
            else
            {
                p_simulation->timeOutAccel = 180;
                p_simulation->timeOutBreak = 10;
                p_simulation->cicleCounter++;
            }


            if( p_simulation->cicleCounter == 6 )
            {
                p_simulation->cicleCounter = 0;
                p_simulation->state = STATE_FOUR_CICLES;
            }
            
            break;   
        }
        
        case STATE_FOUR_CICLES:
        {
            if( p_simulation->timeOutAccel )
            {
                p_moto->setAccelerator(true);
                p_simulation->timeOutAccel--;
            }
            else if( p_simulation->timeOutBreak )
            {
                p_moto->setAccelerator(false);
                p_simulation->timeOutBreak--;
                cont += 1;
            }
            else
            {
                p_simulation->timeOutAccel = 120;
                p_simulation->timeOutBreak = 12;
                p_simulation->cicleCounter++;
            }


            if( p_simulation->cicleCounter == 4 )
            {
                p_simulation->cicleCounter = 0;
                p_simulation->state = STATE_ACCEL;
            }

            break;   
        }

        case STATE_ACCEL:
        {
            break;   
        }

        case STATE_BREAK:
        {
            break;   
        }

        case STATE_END_SIM:
        {
            break;
        }

        default:
            break;
    }

}