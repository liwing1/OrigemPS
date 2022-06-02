#include "simulation.hpp"

#define ADVANCE_SIMU    1
#define HALT_SIMU       0

Simulation::Simulation(
    simulation_states_t _state,
    int _timeOutAccel,
    int _timeOutBreak,
    int _timeOutPrint,
    int _timeStamp,
    int _cicleCounter
    )
{
    state = _state;
    timeOutAccel = _timeOutAccel;
    timeOutBreak = _timeOutBreak;
    timeOutPrint = _timeOutPrint;
    timeStamp = _timeStamp;
    cicleCounter = _cicleCounter;
}

Simulation::~Simulation(void)
{
    return;
}

void Simulation::setState(simulation_states_t _state)
{
    this->state = _state;
}

void Simulation::setTimeOutAccel(int _timeOutAccel)
{
    this->timeOutAccel = _timeOutAccel;
}

void Simulation::setTimeOutBreak(int _timeOutBreak)
{
    this->timeOutBreak = _timeOutBreak;
}

void Simulation::setTimeOutPrint(int _timeOutPrint)
{
    this->timeOutPrint = _timeOutPrint;
}

void Simulation::setTimeStamp(int _timeStamp)
{
    this->timeStamp = _timeStamp;
}

void Simulation::setCicleCounter(int _cicleCounter)
{
    this->cicleCounter = _cicleCounter;
}

simulation_states_t Simulation::getState(void)
{
    return this->state;
}

int Simulation::getTimeOutAccel(void)
{
    return this->timeOutAccel;
}

int Simulation::getTimeOutBreak(void)
{
    return this->timeOutBreak;
}

int Simulation::getTimeOutPrint(void)
{
    return this->timeOutPrint;
}

int Simulation::getTimeStamp(void)
{
    return this->timeStamp;
}

int Simulation::getCicleCounter(void)
{
    return this->cicleCounter;
}

int Simulation::Advance(Simulation* p_simulation, Moto* p_moto)
{
    switch (p_simulation->getState())
    {
        case SIMU_STATE_SIX_CICLES:
        {
            if(p_simulation->getTimeOutBreak() == 0 && p_simulation->getTimeOutAccel() == 0)
            {
                p_simulation->setTimeOutAccel(180);
                p_simulation->setTimeOutBreak(10);
                p_simulation->setCicleCounter(p_simulation->getCicleCounter() + 1);
            }

            if(p_simulation->getCicleCounter() > 6)
            {
                p_simulation->setTimeOutAccel(0);
                p_simulation->setTimeOutBreak(0);
                p_simulation->setCicleCounter(0);
                p_simulation->setState(SIMU_STATE_FOUR_CICLES); 
                return HALT_SIMU;
            }

            if(p_simulation->getTimeOutAccel())
            {  
                p_moto->setAccelerator(true);
                p_simulation->setTimeOutAccel(p_simulation->getTimeOutAccel() - 1);
            }
            else if(p_simulation->getTimeOutBreak())
            {
                p_moto->setBreaker(true);
                p_simulation->setTimeOutBreak(p_simulation->getTimeOutBreak() - 1);
            }
            
            break;   
        }
        
        case SIMU_STATE_FOUR_CICLES:
        {
            if(p_simulation->getTimeOutBreak() == 0 && p_simulation->getTimeOutAccel() == 0)
            {
                p_simulation->setTimeOutAccel(120);
                p_simulation->setTimeOutBreak(12);
                p_simulation->setCicleCounter(p_simulation->getCicleCounter() + 1);
            }

            if(p_simulation->getCicleCounter() > 4)
            {
                p_simulation->setTimeOutAccel(0);
                p_simulation->setTimeOutBreak(0);
                p_simulation->setCicleCounter(0);
                p_simulation->setState(SIMU_STATE_ACCEL); 
                return HALT_SIMU;
            }

            if(p_simulation->getTimeOutAccel())
            {  
                p_moto->setAccelerator(true);
                p_simulation->setTimeOutAccel(p_simulation->getTimeOutAccel() - 1);
            }
            else if(p_simulation->getTimeOutBreak())
            {
                p_moto->setBreaker(true);
                p_simulation->setTimeOutBreak(p_simulation->getTimeOutBreak() - 1);
            }
            
            break;   
        }

        case SIMU_STATE_ACCEL:
        {
            if(p_simulation->getTimeOutBreak() == 0 && p_simulation->getTimeOutAccel() == 0)
            {
                p_simulation->setTimeOutAccel(100);
                p_simulation->setTimeOutBreak(0);
                p_simulation->setCicleCounter(p_simulation->getCicleCounter() + 1);
            }

            if(p_simulation->getCicleCounter() > 1)
            {
                p_simulation->setTimeOutAccel(0);
                p_simulation->setTimeOutBreak(0);
                p_simulation->setCicleCounter(0);
                p_simulation->setState(SIMU_STATE_BREAK); 
                return HALT_SIMU;
            }

            if(p_simulation->getTimeOutAccel())
            {  
                p_moto->setAccelerator(true);
                p_simulation->setTimeOutAccel(p_simulation->getTimeOutAccel() - 1);
            }
            
            break;   
        }

        case SIMU_STATE_BREAK:
        {
            if(p_simulation->getTimeOutBreak() == 0 && p_simulation->getTimeOutAccel() == 0)
            {
                p_simulation->setTimeOutAccel(0);
                p_simulation->setTimeOutBreak(32);
                p_simulation->setCicleCounter(p_simulation->getCicleCounter() + 1);
            }

            if(p_simulation->getCicleCounter() > 1)
            {
                p_simulation->setTimeOutAccel(0);
                p_simulation->setTimeOutBreak(0);
                p_simulation->setCicleCounter(0);
                p_simulation->setState(SIMU_STATE_BREAK); 
                return HALT_SIMU;
            }

            if(p_simulation->getTimeOutBreak())
            {  
                p_moto->setBreaker(true);
                p_simulation->setTimeOutBreak(p_simulation->getTimeOutBreak() - 1);
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