#ifndef HOST_HPP
#define HOST_HPP


class Battery;

class Host{
    protected:
        Battery* battery;
    public:
        void attatchBattery(Battery* _battery);
        void detatchBattery(void);
};

#endif