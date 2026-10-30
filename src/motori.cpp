#include <Arduino.h>
#include "pins.h"
#include "motori.h"

/*                                     PIN MOTORI NEGLI ARRAY
    Inseriamo i pin in A, i pin in B e i pin del PWM all'interno di un array ciascuno, questo sarà molto utile per sfruttarli
    attraverso i cicli for.
*/

int motori_A[4] = {MOT1_A, MOT2_A, MOT3_A, MOT4_A};
int motori_B[4] = {MOT1_B, MOT2_B, MOT3_B, MOT4_B};
int motori_PWM[4] = {MOT1_PWM, MOT2_PWM, MOT3_PWM, MOT4_PWM};


/*                                     INIZIALIZZAZIONE
    Inizializza i motori
*/

void motori_init()
{
    for(int i = 0; i < 4; i++)
  {
    pinMode(motori_A[i], OUTPUT);
    pinMode(motori_B[i], OUTPUT);
    pinMode(motori_PWM[i], OUTPUT);
  }
  
}

/*                                          FAR MUOVERE I MOTORI
    Questa funzione è lo scheletro del motore, fa muovere il motore corrispondente tramite l'indice e la velocità
    La velocità va da -255 a 255, con l'if facciamo in modo che se la velocità è <0 gira in senso antiorario
    se è >0 in senso orario
*/

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

/*                                          TEST PER OGNI MOTORE
    Fa muovere ogni motore per 1 secondo prima in senso orario poi in senso antiorario, utile quando bisogna controllare
    se i pin di ogni motore sono giusti
*/

void MOT_test_4ruote(){

  for (int i=0; i<4; i++){
  motori_Mov(i, 255);
  delay(1000);
  motori_Mov(i, -255);
  delay(1000);
  motori_Mov(i, 0);
  }
}


/*                                          TEST BRUTALE DELLE DIAGONALI
    Fa muovere il robot nelle 4 diagonali dando i comandi direttamente ai singoli motori.
    "Brutale" perchè da un impulso diretto ai motori, mentre c'è un'altro test delle diagonali migliore che 
    sfrutta la formula del moto. Questo test è poco utilizzato, solo quando si ha problemi col moto
    
*/
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

}

/*                                           TEST BRUTALE QUADRATO
    Stesso test delle diagonali, solo che fa muovere il robot come un quadrato
    Anche di questo c'è un test migliore dopo nel moto
*/
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

  //dritto a sinistra
  for(int i = 1; i < 4; i+=2)
  {
    if(i==1 || i==3){
      motori_Mov(i, -50);
    }
    else motori_Mov(i, 50);
  }
  delay(1000); 
} 

/*                                          TEST PER FAR ANDARE IL ROBOT PIANO
    Fa girare i motori lenti per vedere se il problema sono i motori o le ruote fisiche
*/
void MOT_testLento()
{
  for(int i = 0; i < 4; i++)
  {
    motori_Mov(i, 75);
  }
}

void MOT_test_triangolo()
{
  // diagonale in alto a destra
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

  // diagonale in basso a destra
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

  //dritto a sinistra
  for(int i = 1; i < 4; i+=2)
  {
    if(i==1 || i==3){
      motori_Mov(i, -50);
    }
    else motori_Mov(i, 50);
  }
  delay(1000);
}
