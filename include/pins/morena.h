#ifdef MORENA
#ifndef MORENA_H
#define MORENA_H

//motore 1
#define MOT1_PWM 4
#define MOT1_A 10 //9
#define MOT1_B 9 //10

//motore 2
#define MOT2_PWM 5
#define MOT2_A 12 //11
#define MOT2_B 11 //12

//motore 3
#define MOT3_PWM 2
#define MOT3_A 30 //29
#define MOT3_B 29 //30

//motore 4
#define MOT4_PWM 3
#define MOT4_A 32 //31
#define MOT4_B 31 //32


//sensori linee
#define S1IN A7
#define S1ES A6

#define S2IN A3
#define S2ES A2

#define S3IN A1
#define S3ES A0

#define S4IN A9
#define S4ES A8

//palla
#define SENSORE_BOCCA A13
#define SERIAL_PALLA Serial2

//telecamera
#define swtch_porta A15
#define SERIAL_CAM Serial6

#define KICKER_PIN 28

#endif
#endif