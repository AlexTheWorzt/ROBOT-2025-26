#include <QuickPID.h>
#include <Arduino.h>
#include <math.h>
#include "moto.h"
#include "imu.h"
#include "motori.h"
#include "ball.h"
#include "mouth.h"
#include "cam.h"

/*                                                    MOTO e PID

    Il moto definisce quanto ogni singolo motore debba spingere e il loro verso per fare in modo che il robot raggiunga un angolo
    indicato. Dato che abbiamo 4 ruote olonomiche a 45°, possiamo avvalerci di calcoli vettoriali.

    Il PID è il controllo che fa il robot per mantenere lo 0° verso la porta. Ogni volta che il robot si muove
    il PID interviene sui motori per correggere uno storcimento.

    PID e moto sono una cosa sola, il PID è sempre presente nel calcolo del moto: anche quando non c'è uno storcimento
    e il valore del PID è 0, questo viene sommato a tutti gli altri calcoli dei motori
*/

/*
    Le variabili che utilizza il PID per fare i calcoli:
    l'input è l'angolo della porta, il PID farà in modo che il robot sia sempre orientato verso quello
    L'output è il valore che da a ogni motore per correggere lo storcimento quando lo trova
    Il setpoint è quando si vuole invece indurre lo storcimento ad esempio verso la porta quando il robot ha la palla
*/
float input=0;
float output=0;
float setpoint=0;

// Configurazione del PID a seconda delle nostre esigenze, si possono scegliere diverse modalità (queste vanno bene)
static QuickPID ctrlOrient(&input, &output, &setpoint, 
    KP, KI, KD, 
    QuickPID::pMode::pOnError, 
    QuickPID::dMode::dOnMeas, 
    QuickPID::iAwMode::iAwCondition, 
    QuickPID::Action::reverse);




/*                                                  INIZIALIZZAZIONE                                                                            */

void init_DriverCtrl()
{
    ctrlOrient.SetSampleTimeUs(20'000);       
    ctrlOrient.SetOutputLimits(-255.0f,255.0f);
    ctrlOrient.SetMode(QuickPID::Control::automatic);
}



/*                                               FUNZIONE PRINCIPALE DEL MOTO

    Dati un angolo verso cui si vuole mandare il robot e la velocità a cui si vuole mandare, le calcola per ogni singolo motore
    attraverso calcoli vettorali. L'angolo è visto come la direzione del vettore, la velocità come il modulo
*/
void loopDriverCtrl(int alfa, int velocita){

    // Scompone il vettore principale del movimento del robot nelle sue componenti cartesiane
    int vx = velocita * cos(radians(alfa));
    int vy =  velocita * sin(radians(alfa));


    /*                                        DIVERSE PROVE CON LA TELECAMERA IGNORARE                                       */


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
    //setpoint = 0;
    // }
    /*                                                  FINE PROVE                                                             */



    
    // Setpoint a 0 perchè per il momento non c'è la telecamera
    setpoint = 0;

    // Assegna nell'input l'angolo relativo letto dalla bussola. Per il moto utilizziamo angoli nell'intervallo [-180;180]
    // e non [0;360], perciò viene modificato.
    int angle, angle2; float orient_mot;
    angle = read_imu();
    angle2 = (angle > 180) ? angle - 360 : angle; // Trasforma in [-180;180]
    input=angle2;

    // Controlla se il PID funziona, se non funziona non fa muovere il robot
    if (!ctrlOrient.Compute()) return;

    // orient_mot è una variabile utilizzata se il robot ha problemi con lo 0° alla porta, se non serve si mette a 0
    orient_mot = 0;

        /*                                         FORMULA PRINCIPALE DEL MOTO

            E' la formula che calcola velocità e verso per ogni motore.
            Ogni motore ha la ruota posizionata a un angolo differente, che è il numero tra parentesi
            ad esempio MOT1 ha le ruote a 315°, MOT2 a 45° ecc.
            
            Somma le componenti cartesiane e sottrae l'output del PID ogni volta.
        */
        int v1 = -vx * sin(radians(315) + orient_mot) + vy * cos(radians(315) + orient_mot) - output;
        int v2 = -vx * sin(radians(45) + orient_mot) + vy * cos(radians(45) + orient_mot) - output;
        int v3 = -vx * sin(radians(135) + orient_mot) + vy * cos(radians(135) + orient_mot) - output;
        int v4 = -vx * sin(radians(225) + orient_mot) + vy * cos(radians(225) + orient_mot) - output;
        
        // Dopo aver calcolato le singole velocità, da il comando ai singoli motori
        motori_Mov(0, -v1); 
        motori_Mov(1, -v2); 
        motori_Mov(2, -v3); 
        motori_Mov(3, -v4); 



        /*                                            PICCOLO TEST DELLA FORMULA                                               
        
            Test da scommentare per vedere ogni valore che il robot sta calcolando
        */
        // test formula motori
    
        // Serial.println("VX");
        // Serial.println(vx);
        // Serial.println("VY");
        // Serial.println(vy);
        // Serial.println("Velocità per motore");
        // Serial.println(-v1);
        // Serial.println(-v2);
        // Serial.println(-v3);
        // Serial.println(-v4);
        // Serial.print("Angolo porta passato: ");
        // Serial.println(get_angolo_porta_attacco());
        // Serial.print("Setpoint: ");
        // Serial.println(setpoint);
        // Serial.print("output PID: ");
        // Serial.println(output);
}






/*                                              ALTRE PROVE PER TELECAMERA IGNORARE                                         */

// void loopDriverCtrl(int alfa, int velocita)
// {
    // int vx = velocita * cos(radians(alfa));
    // int vy =  velocita * sin(radians(alfa));
// while (mouth_sens()){
// float distortion = get_angolo_porta_attacco();
// if (distortion >= -90 && distortion <=90)
// {
    // setpoint = distortion;
    
    // int angle, angle2; float orient_mot;
    // angle = read_imu();
    // angle2 = (angle > 180) ? angle - 360 : angle; //se angolo > 180, lo portiamo in [-180, 180]
    // input=angle2;
    // if (!ctrlOrient.Compute()) return;
    // orient_mot = 0;
     // velocità calcolate per ogni motore
        // scriverle una per una va bene, sono poche
        // int v1 = -vx * sin(radians(315) + orient_mot) + vy * cos(radians(315) + orient_mot) - output;
        // int v2 = -vx * sin(radians(45) + orient_mot) + vy * cos(radians(45) + orient_mot) - output;
        // int v3 = -vx * sin(radians(135) + orient_mot) + vy * cos(radians(135) + orient_mot) - output;
        // int v4 = -vx * sin(radians(225) + orient_mot) + vy * cos(radians(225) + orient_mot) - output;
        
        // // comando ai motori
        // motori_Mov(0, -v1); 
        // motori_Mov(1, -v2); 
        // motori_Mov(2, -v3); 
        // motori_Mov(3, -v4); 
// 
//
//}

// }

/*                                                     FINE PROVE                                                          */




/*                                PRIMO PROTOTIPO DI STORCIMENTO CON TELECAMERA (da sistemare)                                */

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

    }
    
    
}

        

// Test per l'intervallo [-180;180]
void test_inter_imu(){
    int angle, angle2;
    angle = read_imu();
    angle2 = (angle >= 180) ? angle - 360 : angle; //se angolo > 180, lo portiamo in [-180, 180]
    Serial.println(angle2);
}

// Test delle diagonali dato l'angolo, a differenza del test brutale coi motori
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

// Test del quadrato dato l'angolo
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
