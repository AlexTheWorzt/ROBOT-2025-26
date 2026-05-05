#ifndef MOTORI_H
#define MOTORI_H

#define generic_pwm 75

void motori_init();
void motori_Mov(int ind, int pwm);
void MOT_test_4ruote();
void MOT_test_diagonali();
void MOT_test_quadrato();
void MOT_testLento();

#endif