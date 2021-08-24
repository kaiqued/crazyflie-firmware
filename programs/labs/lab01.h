#include "mbed.h"
#include "crazyflie.h"
#include "USBSerial.h"

// Define all LEDs as digital output objects
DigitalOut led_1(LED_GREEN_L,!false);
DigitalOut led_2(LED_GREEN_R,!false);
DigitalOut led_3(LED_RED_L,!false);
DigitalOut led_4(LED_RED_R,!false);
DigitalOut led_5(LED_BLUE_L,!false);

USBSerial serial;

// Define all motors as PWM objects
PwmOut Mot1(MOTOR1);
PwmOut Mot2(MOTOR2);
PwmOut Mot3(MOTOR3);
PwmOut Mot4(MOTOR4);
int Toca_Agora = 1;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


// change this to make the song slower or faster
int tempo = 200;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {
NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
  NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
  NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
  NOTE_G4,2,
  
  NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
  NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
  NOTE_F4,8, NOTE_E4,8, NOTE_D4,8, NOTE_C4,8,
  NOTE_C4,2,

  NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
  NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
  NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
  NOTE_G4,2,

  NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
  NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
  NOTE_F4,8, NOTE_E4,8, NOTE_D4,8, NOTE_C4,8,
  NOTE_C4,16, NOTE_D5,8, NOTE_D5,16, NOTE_D5,16, NOTE_D5,8, NOTE_D5,16,

  NOTE_D5,16, NOTE_D5,8, NOTE_D5,16, NOTE_C5,8, NOTE_E5,-8,
  NOTE_C5,8, NOTE_C5,16, NOTE_E5,16, NOTE_E5,8, NOTE_C5,16,
  NOTE_F5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,-8,
  NOTE_C5,8, NOTE_D5,16, NOTE_E5,16, NOTE_D5,8, NOTE_C5,16,

  NOTE_F5,8, NOTE_F5,8, NOTE_A5,8, NOTE_G5,-8,//21
  NOTE_G5,8, NOTE_C5,16, NOTE_C5,16, NOTE_C5,8, NOTE_C5,16,
  NOTE_F5,-8, NOTE_E5,16, NOTE_D5,8, NOTE_C5,4,
  NOTE_C5,16, NOTE_C5,16, NOTE_C5,16, NOTE_C5,16,

  NOTE_F5,8, NOTE_F5,16, NOTE_A5,8, NOTE_G5,-8,//25
  NOTE_G5,8, NOTE_C5,16, NOTE_C5,16, NOTE_C5,8, NOTE_C5,16,
  NOTE_F5,16, NOTE_E5,8, NOTE_D5,16, NOTE_C5,8, NOTE_E5,-8,
  NOTE_C5,8, NOTE_D5,16, NOTE_E5,16, NOTE_D5,8, NOTE_C5,16,
 
  NOTE_F5,8, NOTE_F5,16, NOTE_A5,8, NOTE_G5,-8,//29
  NOTE_G5,8, NOTE_C5,16, NOTE_C5,16, NOTE_C5,8, NOTE_C5,16,
  NOTE_F5,8, NOTE_E5,16, NOTE_D5,8, NOTE_C5,8,
  NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,

  NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
  NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
  NOTE_G4,2,
  NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,

  NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
  NOTE_F4,8, NOTE_E4,8, NOTE_D4,8, NOTE_C4,-2,
  NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,

  NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
  NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
  NOTE_G4,2,
  NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,

  NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
  NOTE_F4,8, NOTE_E4,8, NOTE_D4,8, NOTE_C4,-2,
  NOTE_C4,16, NOTE_C4,8, NOTE_C4,16, NOTE_E4,16, NOTE_E4,8, NOTE_E4,16,
  NOTE_F4,16, NOTE_F4,8, NOTE_F4,16, NOTE_FS4,16, NOTE_FS4,8, NOTE_FS4,16,

  NOTE_G4,8, REST,8, NOTE_AS4,8, NOTE_C5,1,

};


// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;
void Play(float PERIODO, float TEMPO)
{   
    if (Toca_Agora == 1)
    {
        Mot1.period(1.0/PERIODO);
        Mot1 = 0.1;
        wait_ms(TEMPO);
        Toca_Agora = 2;
    }

    else if (Toca_Agora == 2) 
    {
        Mot2.period(1.0/PERIODO);
        Mot2 = 0.1;
        wait_ms(TEMPO);
        Toca_Agora = 3;
    }

    else if (Toca_Agora == 3) 
    {
        Mot3.period(1.0/PERIODO);
        Mot3 = 0.1;
        wait_ms(TEMPO);
        Toca_Agora = 4;
    }
    
    else if (Toca_Agora == 4) 
    {
        Mot4.period(1.0/PERIODO);
        Mot4 = 0.1;
        wait_ms(TEMPO);
        Toca_Agora = 1;
    }
}

// Main program
int main()
{
    // // Blink blue LED indicating inicialization (5 seconds)
    // led_5 = 1;
    // // wait(5);
    // led_5 = 0;
    
    // // Turn on red LEDs indicating motors are armed
    // led_3 = 0;
    // led_4 = 0;
    
    // // Test all motors with different frequencies (to make different noises)
    // Play(528, 0.2); // Dó
    // Play(592, 0.2); // Ré
    // Play(665, 0.2); // Mi
    // Play(704, 0.2); // Fá
    // Play(704, 0.2); // Fá
    // Play(704, 0.2); // Fá
    // Play(528, 0.2); // Dó
    // Play(592, 0.2); // Ré
    // Play(528, 0.2); // Dó
    // Play(592, 0.2); // Ré
    // Play(592, 0.2); // Ré
    // Play(592, 0.2); // Ré
    // Play(528, 0.2); // Dó
    // Play(790, 0.2); // Sol
    // Play(704, 0.2); // Fá
    // Play(665, 0.2); // Mi
    // Play(665, 0.2); // Mi
    // Play(665, 0.2); // Mi
    // Play(528, 0.2); // Dó
    // Play(592, 0.2); // Ré
    // Play(665, 0.2); // Mi
    // Play(704, 0.2); // Fá
    // Play(704, 0.2); // Fá
    // Play(704, 0.2); // Fá
    
    // Play(888, 0.2); // Lá
    // Play(996, 0.2); // Si
    // Play(1056, 0.2);// Dó

    // // Mot2.period(1.0/600);
    // // Mot2 = 0.2;
    // // wait(0.2);
    // // Mot2 = 0;

    // // Mot3.period(1.0/800.0);
    // // Mot3 = 0.2;
    // // wait(0.2);
    // // Mot3 = 0;

    // // Mot4.period(1.0/1000.0);
    // // Mot4 = 0.2;
    // // wait(0.2);
    // // Mot4 = 0;

    // // Mot1.period(1.0/1000.0);
    // // Mot1 = 0.2;
    // // wait(0.2);
    // // Mot1 = 0;

    // // Mot2.period(1.0/800.0);
    // // Mot2 = 0.2;
    // // wait(0.2);
    // // Mot2 = 0;

    // // Mot3.period(1.0/600.0);
    // // Mot3 = 0.2;
    // // wait(0.2);
    // // Mot3 = 0;

    // // Mot4.period(1.0/400.0);
    // // Mot4 = 0.2;
    // // wait(0.2);
    // // Mot4 = 0;
    
    // // Turn off red LEDs indicating motors are disarmed
    // led_3 = 1;
    // led_4 = 1;
    
    // // Blink green LEDs indicating end of program
    // led_1 = 0;
    // led_2 = 0;
    // wait(0.2);
    // led_1 = 1;
    // led_2 = 1;
    wait(1);
    while(true)
    {   
        // iterate over the notes of the melody.
        // Remember, the array is twice the number of notes (notes + durations)
        for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
            
            serial.printf("%d\n",thisNote);
            // calculates the duration of each note
            divider = melody[thisNote + 1];
            if (divider > 0) {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
            } else if (divider < 0) {
            // dotted notes are represented with negative durations!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
            }
            serial.printf("%d\n",melody[thisNote + 1]);
            // we only play the note for 90% of the duration, leaving 10% as a pause
            Play(melody[thisNote], noteDuration*0.9);
            serial.printf("Primeira\n");
            // Wait for the specief duration before playing the next note.
            wait_ms(noteDuration);
            Mot1 = 0;
            Mot2 = 0;
            Mot3 = 0;
            Mot4 = 0;
            serial.printf("Segunda\n");
        }

    }
}

