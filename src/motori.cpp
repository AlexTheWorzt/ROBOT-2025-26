#include <Arduino.h>
#include "pins.h"
#include "motori.h"

int motori_A[4] = {MOT1_A, MOT2_A, MOT3_A, MOT4_A};
int motori_B[4] = {MOT1_B, MOT2_B, MOT3_B, MOT4_B};
int motori_PWM[4] = {MOT1_PWM, MOT2_PWM, MOT3_PWM, MOT4_PWM};

void motori_init()
{
  for(int i = 0; i < 4; i++)
  {
    pinMode(motori_A[i], OUTPUT);
    pinMode(motori_B[i], OUTPUT);
    pinMode(motori_PWM[i], OUTPUT);
  }
  
}

void motori_Mov(int ind /*indice del motore*/, int pwm /*pwm del motore*/)
{
  if(pwm > 0)
  {
    digitalWrite(motori_A[ind], HIGH);
    digitalWrite(motori_B[ind], LOW);
    analogWrite(motori_PWM[ind], pwm);
  }
  else
  {
    digitalWrite(motori_A[ind], LOW);
    digitalWrite(motori_B[ind], HIGH);
    analogWrite(motori_PWM[ind], abs(pwm));
  }
}

void MOT_test_4ruote(){

  for (int i=0; i<4; i++){
  motori_Mov(i, 255);
  delay(1000);
  motori_Mov(i, -255);
  delay(1000);
  motori_Mov(i, 0);
  }
}

void MOT_test_diagonali(){
   //diagonale in alto a destra
  for(int i = 0; i < 4; i+=2)
  {
    if(i==0){
      motori_Mov(i, -100);
    }
    else if(i==2){
      motori_Mov(i, 100);
    }
    else motori_Mov(i, 0); 
  }
  delay(1000);

  //diagonale in basso a sinistra 
  for(int i = 1; i < 4; i+=2)
  {
    if(i==0){
      motori_Mov(i, 100);
    }
    else if(i==2){
      motori_Mov(i, -100);
    }
    else motori_Mov(i, 0); 
  }
  delay(1000);

  //diagonale in altro a sinistra
  for(int i = 0; i < 4; i+=2)
  {
    if(i==1){
      motori_Mov(i, -100);
    }
    else if(i==3){
      motori_Mov(i, 100);
    }
    else motori_Mov(i, 0); 
  }
  delay(1000);

  //diagonale in basso a destra
  for(int i = 1; i < 4; i+=2)
  {
    if(i==1){
      motori_Mov(i, 100);
    }
    else if(i==3){
      motori_Mov(i, -100);
    }
    else motori_Mov(i, 0); 
  }
  delay(1000);

  /*for(int i = 0; i < 2; i++)
  {
    motori_Mov(i, generic_pwm);
    motori_Mov(i + 2, generic_pwm * -1);
    delay(1000);
    motori_Mov(i, 0);
    motori_Mov(i + 2, 0);
  }
  delay(1000);
  for(int i = 0; i < 2; i++)
  {
    motori_Mov(i, generic_pwm * -1);
    motori_Mov(i + 2, generic_pwm);
    delay(1000);
    motori_Mov(i, 0);
    motori_Mov(i + 2, 0);
  }
  delay(1000);*/
}

void MOT_test_quadrato(){

  //dritto in alto
  for(int i = 0; i < 4; i+=2)
  {
    if (i==0 || i==1){
      motori_Mov(i, -50);
    }
    else motori_Mov(i, 50);
  }
  delay(1000);

  //dritto a destra
  for(int i = 1; i < 4; i+=2)
  {
    if(i==0 || i==3){
      motori_Mov(i, -50);
    }
    else motori_Mov(i, 50);
  }
  delay(1000);

  //dritto indietro
  for(int i = 0; i < 4; i+=2)
  {
    if(i==0 || i==1){
      motori_Mov(i, 50);
    }
    else motori_Mov(i, -50);
  }
  delay(1000);

  //diagonale in basso a destra
  for(int i = 1; i < 4; i+=2)
  {
    if(i==0 || i==2){
      motori_Mov(i, 50);
    }
    else motori_Mov(i, -50);
  }
  delay(1000); 

   /* int d;
  for(int i = 0; i <= 2; i += 2)
  {
    if(i == 0){
      d = 1; 
    }
    else
    {
      d = -1;
    }
    motori_Mov(i, generic_pwm * d);
    motori_Mov(i + 1, generic_pwm * d);

  }*/

} 

void MOT_testLento()
{
  for(int i = 0; i < 4; i++)
  {
    motori_Mov(i, 25);
  }
}

