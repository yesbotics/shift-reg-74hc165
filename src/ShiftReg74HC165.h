#ifndef SHIFT_REG_74HC165_H
#define SHIFT_REG_74HC165_H

#include <Arduino.h>

class ShiftReg74HC165 {


private:
    int pinParallelLoad_;
    int pinClockEnable_;
    int pinData_;
    int pinClock_;


public:
    ShiftReg74HC165(int pinParallelLoad, int pinClockEnable, int pinData, int pinClock);

    void begin();

    byte read();
};


#endif //SHIFT_REG_74HC165_H
