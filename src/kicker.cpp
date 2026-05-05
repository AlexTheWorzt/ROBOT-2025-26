#include <Arduino.h>
#include "pins.h"
#include "mouth.h"
#include "kicker.h"

void init_kicker(){
    pinMode(KICKER_PIN, OUTPUT);
    //  digitalWrite(KICKER_PIN, LOW);
}   


void kicker_fire() {
    static unsigned long lastChangeTime = 0;
    static bool isHigh = false;  // false = LOW, true = HIGH
    unsigned long t = millis();
    
    // Se è in stato HIGH e sono passati 1000ms
    if (isHigh && (t - lastChangeTime >= 200)) {
        digitalWrite(KICKER_PIN, LOW);    // Spegni
        isHigh = false;                   // Aggiorna stato
        lastChangeTime = t;             // Reset timer
    }
    // Se è in stato LOW e sono passati 1000ms
    else if (!isHigh && (t - lastChangeTime >= 500)) {
        digitalWrite(KICKER_PIN, HIGH);   // Accendi
        isHigh = true;                    // Aggiorna stato
        lastChangeTime = t;             // Reset timer
    }
}


void kicker_test(){
    digitalWrite(KICKER_PIN, HIGH);
    delay(1000);
    digitalWrite(KICKER_PIN, LOW);
    delay(1000);
}

void kicker_test_mouth()
{
    if (mouth_sens())
    {
        kicker_fire();
    }
}