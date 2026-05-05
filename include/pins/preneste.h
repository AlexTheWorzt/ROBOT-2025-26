#ifdef PRENESTE
#ifndef PRENESTE_H
#define PRENESTE_H

//motore 1
#define MOT1_A 11
#define MOT1_B 12
#define MOT1_PWM 4

//motore 2
#define MOT2_A 24
#define MOT2_B 25
#define MOT2_PWM 5

//motore 3
#define MOT3_A 26
#define MOT3_B 27
#define MOT3_PWM 2

//motore 4
#define MOT4_A 29
#define MOT4_B 28
#define MOT4_PWM 3


//sensori linee
#define S1IN A6
#define S1ES A7
#define S2IN A9 
#define S2ES A8 
#define S3IN A0
#define S3ES A1
#define S4IN A3
#define S4ES A2

//palla
#define SENSORE_BOCCA A13
#define SERIAL_PALLA Serial2

//telecamera
#define swtch_porta A15
#define SERIAL_CAM Serial6

#define KICKER_PIN 28

#endif
#endif