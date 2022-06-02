#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "moto.hpp"

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

int simulation_advance(simulation_t* p_simulation, Moto* p_moto);

#endif