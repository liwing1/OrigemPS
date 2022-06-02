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

class Simulation{
    private:
            simulation_states_t state;
            int timeOutAccel;
            int timeOutBreak;
            int timeOutPrint;
            int timeStamp;
            int cicleCounter;

    public:
        Simulation(
            simulation_states_t state,
            int timeOutAccel,
            int timeOutBreak,
            int timeOutPrint,
            int timeStamp,
            int cicleCounter
        );
        ~Simulation(void);

        void setState(simulation_states_t _state);
        void setTimeOutAccel(int _timeOutAccel);
        void setTimeOutBreak(int _timeOutBreak);
        void setTimeOutPrint(int _timeOutPrint);
        void setTimeStamp(int _timeStamp);
        void setCicleCounter(int _cicleCounter);

        simulation_states_t getState(void);
        int getTimeOutAccel(void);
        int getTimeOutBreak(void);
        int getTimeOutPrint(void);
        int getTimeStamp(void);
        int getCicleCounter(void);

        int Advance(Simulation* p_simulation, Moto* p_moto);

};

#endif