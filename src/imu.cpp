#include <Adafruit_BNO055.h>
#include "imu.h"

Adafruit_BNO055 bno = Adafruit_BNO055 (55, 0x28);

unsigned long imu_timer{0};
int angolo{0};
int angoloAss;
int angoloRel;

void init_imu(){
    while(!(bno.begin(OPERATION_MODE_IMUPLUS))){
        Serial.println("Bussola non trovata!");
    }

    bno.setExtCrystalUse(true);
    imu_timer=millis();

    delay(500);

    imu::Vector<3>euler=bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    angoloAss= (int) euler.x();
}

int read_imu(){
    if (millis()-imu_timer>=20){
        imu::Vector<3>euler=bno.getVector(Adafruit_BNO055::VECTOR_EULER);
        angolo= (int) euler.x();

        angoloRel=angolo-angoloAss;
        if(angoloRel<0){
            angoloRel+=360;
        }
        
        imu_timer = millis();
    }
    return angoloRel;
}

void test_imu()
{
    angoloRel = read_imu();
    Serial.println(angoloRel);
}