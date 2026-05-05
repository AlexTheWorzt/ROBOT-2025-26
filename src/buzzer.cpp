#include <Arduino.h>
#include <stdbool.h>
#include "pins.h"
#include "motori.h"
#include "imu.h"
#include "moto.h"
#include "ball.h"
#include "linee.h"
#include "attacker.h"
#include "cam.h"
#include "mouth.h"
#include "kicker.h"

void buzzer_init()
{
    pinMode (BUZZER_PIN, OUTPUT);
}

void buzzer_fire()
{
    analogWrite(BUZZER_PIN, 100);
}