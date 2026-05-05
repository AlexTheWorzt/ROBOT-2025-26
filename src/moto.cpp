#include <QuickPID.h>
#include <Arduino.h>
#include <math.h>
#include "moto.h"
#include "imu.h"
#include "motori.h"
#include "ball.h"
#include "mouth.h"
#include "cam.h"

float input=0;
float output=0;
float setpoint=0;

static QuickPID ctrlOrient(&input, &output, &setpoint, 
    KP, KI, KD, 
    QuickPID::pMode::pOnError, 
    QuickPID::dMode::dOnMeas, 
    QuickPID::iAwMode::iAwCondition, 
    QuickPID::Action::reverse);



void init_DriverCtrl()
{
    ctrlOrient.SetSampleTimeUs(20'000);       
    ctrlOrient.SetOutputLimits(-255.0f,255.0f);
    ctrlOrient.SetMode(QuickPID::Control::automatic);
}

void loopDriverCtrl(int alfa, int velocita){

    int vx = velocita * cos(radians(alfa));
    int vy =  velocita * sin(radians(alfa));
    // if (mouth_sens() == true)
    // {
    //     Serial.println(mouth_sens());
    //     unsigned long tempo = millis();
    //     float distortion;
    //     if (millis() - tempo > 50)
    //     {
    //         distortion = get_angolo_porta_attacco();
    //         tempo = millis();
    //     }
    //     while (millis() - tempo <= 500)
    //     {
    //         setpoint = distortion;
    //         tempo = millis();
    //     }
    // }
    // else
    // {
    setpoint = 0;
    // }
    int angle, angle2; float orient_mot;
    angle = read_imu();
    angle2 = (angle > 180) ? angle - 360 : angle; //se angolo > 180, lo portiamo in [-180, 180]
    input=angle2;
    if (!ctrlOrient.Compute()) return;

    orient_mot = 0;
        // velocità calcolate per ogni motore
        // scriverle una per una va bene, sono poche
        int v1 = -vx * sin(radians(315) + orient_mot) + vy * cos(radians(315) + orient_mot) - output;
        int v2 = -vx * sin(radians(45) + orient_mot) + vy * cos(radians(45) + orient_mot) - output;
        int v3 = -vx * sin(radians(135) + orient_mot) + vy * cos(radians(135) + orient_mot) - output;
        int v4 = -vx * sin(radians(225) + orient_mot) + vy * cos(radians(225) + orient_mot) - output;
        
        // comando ai motori
        motori_Mov(0, -v1); 
        motori_Mov(1, -v2); 
        motori_Mov(2, -v3); 
        motori_Mov(3, -v4); 

        // test formula motori
    
        Serial.println("VX");
        Serial.println(vx);
        Serial.println("VY");
        Serial.println(vy);
        Serial.println("Velocità per motore");
        Serial.println(-v1);
        Serial.println(-v2);
        Serial.println(-v3);
        Serial.println(-v4);
        Serial.print("Angolo porta passato: ");
        Serial.println(get_angolo_porta_attacco());
        Serial.print("Setpoint: ");
        Serial.println(setpoint);
        Serial.print("output PID: ");
        Serial.println(output);
}


//while (mouth_sens()){
//  setpoint = get_angolo_porta_attacco();
// tutto il resto del codice
//}

void loopDriverCtrl_distortion(int alfa, int velocita){

    unsigned long tempo = millis();
    float distortion = get_angolo_porta_attacco();

    if (distortion >= -90 && distortion <=90)
    {
        while (millis() - tempo <= 1000000)
        {
            if (distortion >= 2 && distortion <= 5)
            {
                setpoint = distortion * 7;
            }
            else if (distortion >= 6 && distortion <= 10)
            {
                setpoint = distortion * 5;
            }
            else
            {
                setpoint = distortion;
            }
            int vx = velocita * cos(radians(alfa));
    int vy =  velocita * sin(radians(alfa));
    int angle, angle2; float orient_mot;
    angle = read_imu();
    angle2 = (angle > 180) ? angle - 360 : angle; //se angolo > 180, lo portiamo in [-180, 180]
    input=angle2;
    setpoint = get_angolo_porta_attacco();
    if (!ctrlOrient.Compute()) return;

    orient_mot = 0;
        // velocità calcolate per ogni motore
        // scriverle una per una va bene, sono poche
        int v1 = -vx * sin(radians(315) + orient_mot) + vy * cos(radians(315) + orient_mot) - output;
        int v2 = -vx * sin(radians(45) + orient_mot) + vy * cos(radians(45) + orient_mot) - output;
        int v3 = -vx * sin(radians(135) + orient_mot) + vy * cos(radians(135) + orient_mot) - output;
        int v4 = -vx * sin(radians(225) + orient_mot) + vy * cos(radians(225) + orient_mot) - output;
        
        // comando ai motori
        motori_Mov(0, -v1); 
        motori_Mov(1, -v2); 
        motori_Mov(2, -v3); 
        motori_Mov(3, -v4); 

        // test formula motori
    
        Serial.println("VX");
        Serial.println(vx);
        Serial.println("VY");
        Serial.println(vy);
        Serial.println("Velocità per motore");
        Serial.println(-v1);
        Serial.println(-v2);
        Serial.println(-v3);
        Serial.println(-v4);
        Serial.print("Angolo porta passato: ");
        Serial.println(get_angolo_porta_attacco());
        Serial.print("Setpoint: ");
        Serial.println(setpoint);
        Serial.print("output PID: ");
        Serial.println(output);
            tempo = millis();
        }
    }
    else
    {
        int vx = velocita * cos(radians(alfa));
    int vy =  velocita * sin(radians(alfa));
    setpoint = 0;
    int angle, angle2; float orient_mot;
    angle = read_imu();
    angle2 = (angle > 180) ? angle - 360 : angle; //se angolo > 180, lo portiamo in [-180, 180]
    input=angle2;
    if (!ctrlOrient.Compute()) return;

    orient_mot = 0;
        // velocità calcolate per ogni motore
        // scriverle una per una va bene, sono poche
        int v1 = -vx * sin(radians(315) + orient_mot) + vy * cos(radians(315) + orient_mot) - output;
        int v2 = -vx * sin(radians(45) + orient_mot) + vy * cos(radians(45) + orient_mot) - output;
        int v3 = -vx * sin(radians(135) + orient_mot) + vy * cos(radians(135) + orient_mot) - output;
        int v4 = -vx * sin(radians(225) + orient_mot) + vy * cos(radians(225) + orient_mot) - output;
        
        // comando ai motori
        motori_Mov(0, -v1); 
        motori_Mov(1, -v2); 
        motori_Mov(2, -v3); 
        motori_Mov(3, -v4); 

        // test formula motori
    
        Serial.println("VX");
        Serial.println(vx);
        Serial.println("VY");
        Serial.println(vy);
        Serial.println("Velocità per motore");
        Serial.println(-v1);
        Serial.println(-v2);
        Serial.println(-v3);
        Serial.println(-v4);
        Serial.print("Angolo porta passato: ");
        Serial.println(get_angolo_porta_attacco());
        Serial.print("Setpoint: ");
        Serial.println(setpoint);
        Serial.print("output PID: ");
        Serial.println(output);
    }
    
    
}

        


void test_inter_imu(){
    int angle, angle2;
    angle = read_imu();
    angle2 = (angle >= 180) ? angle - 360 : angle; //se angolo > 180, lo portiamo in [-180, 180]
    Serial.println(angle2);
}

void test_diagonali()
{
    unsigned long tempo=0;
    unsigned long ritardo=500;

    tempo = millis();
    while(millis() - tempo < ritardo) loopDriverCtrl(45, 200);
    tempo = millis();
    while(millis() - tempo < ritardo) loopDriverCtrl(-135, 200);
    tempo = millis();
    while(millis() - tempo < ritardo) loopDriverCtrl(-45, 200);
    tempo = millis();
    while(millis() - tempo < ritardo) loopDriverCtrl(135, 200);
    tempo = millis();
}

void test_quadrato()
{
    unsigned long tempo=0;
    unsigned long ritardo=1000;

    tempo = millis();
    while(millis() - tempo < ritardo) loopDriverCtrl(0, 200);
    tempo = millis();
    while(millis() - tempo < ritardo) loopDriverCtrl(90, 200);
    tempo = millis();
    while(millis() - tempo < ritardo) loopDriverCtrl(180, 200);
    tempo = millis();
    while(millis() - tempo < ritardo) loopDriverCtrl(-90, 200);
    tempo = millis();
}