#include "mbed.h"
#include "crazyflie.h"
#include "USBSerial.h"

// Define all LEDs as digital output objects
DigitalOut led_1(LED_GREEN_L,!false);
DigitalOut led_2(LED_GREEN_R,!false);
DigitalOut led_3(LED_RED_L,!false);
DigitalOut led_4(LED_RED_R,!false);
DigitalOut led_5(LED_BLUE_L,!false);

// Define all motors as PWM objects
PwmOut Mot1(MOTOR1);
PwmOut Mot2(MOTOR2);
PwmOut Mot3(MOTOR3);
PwmOut Mot4(MOTOR4);

// Main program
int main()
{
    // Blink blue LED indicating inicialization (5 seconds)
    led_5 = 1;
    wait(5);
    led_5 = 0;
    // Turn on red LEDs indicating motors are armed
    led_3 = 1;
    led_4 = 1;
    // Test all motors with different frequencies (to make different noises)
    Mot1 = 0.2;
    Mot1.period(1/400);
    wait(1);
    Mot1 = 0;

    Mot2 = 0.2;
    Mot2.period(1/600);
    wait(1);
    Mot2 = 0;

    Mot3 = 0.2;
    Mot3.period(1/800);
    wait(1);
    Mot3 = 0;

    Mot4 = 0.2;
    Mot4.period(1/1000);
    wait(1);
    Mot4 = 0;
    
    // Turn off red LEDs indicating motors are disarmed
    led_3 = 1;
    led_4 = 1;
    // Blink green LEDs indicating end of program
    led_5 = 1;
    wait(5);
    led_5 = 0;
    while(true)
    {   
        

    }
}
