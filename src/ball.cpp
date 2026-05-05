#include <Arduino.h>
#include <stdbool.h>

#include "ball.h"
#include "pins.h"

int angolo_palla;
int distanza_palla;
bool palla = false;

void init_palla() {
    SERIAL_PALLA.begin(9600);
}

void leggi_palla () {
    while (SERIAL_PALLA.available()) {
   uint8_t messaggio = SERIAL_PALLA.read();
        char LSB= messaggio & 1;
        if (LSB==1) {
            distanza_palla = messaggio;
            if(distanza_palla > 1)
                palla=true;
            else
                palla=false;
        }
        else {
            angolo_palla = messaggio*2;
        }
     }
}

int passa_angolo_palla (){
    return angolo_palla;
}

int passa_distanza_palla (){
    return distanza_palla;
}
bool palla_Vista(){
    return palla;
}
bool palla_nonvista(){
    palla=false;
    return palla;
}

void test_palla() {

     leggi_palla();
   
    if(palla){
        Serial.println(String("anglo della palla: ") + angolo_palla);
        Serial.println(String("distanza della palla: ") + distanza_palla);
    }
    else Serial.println("non si vede la palla");
     delay(500);
}