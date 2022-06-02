#include "simulation.hpp"

#define ADVANCE_SIMU    1
#define HALT_SIMU       0

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