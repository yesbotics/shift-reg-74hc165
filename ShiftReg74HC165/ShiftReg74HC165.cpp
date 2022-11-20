#include <Arduino.h>
#include "ShiftReg74HC165.h"

const int DATA_WIDTH = 8; // Width of data (how many ext lines)
const int PULSE_WIDTH_USEC = 5; // Width of pulse to trigger the shift register to read and latc

ShiftReg74HC165::ShiftReg74HC165(int pinParallelLoad, int pinClockEnable, int pinData, int pinClock) :
        pinParallelLoad_{pinParallelLoad},
        pinClockEnable_{pinClockEnable},
        pinData_{pinData},
        pinClock_{pinClock} {}

void ShiftReg74HC165::begin() {
    pinMode(this->pinParallelLoad_, OUTPUT);
    pinMode(this->pinClockEnable_, OUTPUT);
    pinMode(this->pinClock_, OUTPUT);
    pinMode(this->pinData_, INPUT);
    digitalWrite(this->pinClock_, LOW);
    digitalWrite(this->pinParallelLoad_, HIGH);
}

byte ShiftReg74HC165::read() {
    long bitVal;
    byte byteVal = 0;

    //  Trigger a parallel Load to latch the state of the data lines,
    digitalWrite(this->pinClockEnable_, HIGH);
    digitalWrite(this->pinParallelLoad_, LOW);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(this->pinClockEnable_, LOW);

    // Loop to read each bit value from the serial out line of the ShiftReg74HC165
    for (int i = 0; i < DATA_WIDTH; i++) {
        bitVal = digitalRead(this->pinData_);
        // Set the corresponding bit in bytesVal.
        byteVal |= (bitVal << ((DATA_WIDTH - 1) - i));
        // Pulse the Clock (rising edge shifts the next bit).
        digitalWrite(this->pinClock_, HIGH);
        delayMicroseconds(PULSE_WIDTH_USEC);
        digitalWrite(this->pinClock_, LOW);
    }
    return (byteVal);
}
