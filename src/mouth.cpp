#include <Arduino.h>
#include <stdbool.h>

#include "mouth.h"
#include "pins.h"

int valore;

void init_mouth(){
    pinMode(SENSORE_BOCCA,INPUT);
}

bool mouth_sens(){
    valore = analogRead(SENSORE_BOCCA);
    bool valoreb = (valore < 1000) ?  true : false;
    // Serial.println(valoreb);
    return valoreb;
}

void test_mouth(){
    valore=analogRead(SENSORE_BOCCA);
    Serial.print("valore: ");
    Serial.println(valore);
    Serial.println("-----------------------------");
    Serial.print("esito: ");
    Serial.println(mouth_sens());
    delay(500);
}