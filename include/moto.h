#ifndef PID_H
#define PID_H

#define KP 2
#define KI 0
#define KD 0.12

//int theta[4] = {DtoR(45), DtoR(135), DtoR(225), DtoR(315)};
//int theta[4] = {45, 135, 225, 315};


void loopDriverCtrl(int alfa, int velocita);
void loopDriverCtrl_distortion(int alfa, int velocita);
void init_DriverCtrl(void);
void test_inter_imu();
void test_diagonali();
void test_quadrato ();

#endif