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
#include "buzzer.h"


void attacker()
{
     leggi_palla();
     int attack_angle = passa_angolo_palla();
     bool ball_in_mouth = mouth_sens();
     bool ball_is_real = palla_Vista();
     float goal_angle = get_angolo_porta_attacco();

     if (ball_is_real == false)
     {
          loopDriverCtrl(180, 150);
     }
     else
     {
        if (ball_in_mouth)
          {
               // unsigned long tempo = millis();
               loopDriverCtrl_distortion(goal_angle, speed);
               // if (millis() - tempo > 50)
               // {
                    // float dist_attack_goal = get_distanza_porta_attacco();
                    // if (dist_attack_goal > 200)
                    // {
                         kicker_fire();
               // }
               // }
          }
       
          else 
          {
               if (attack_angle >= 339 || attack_angle <= 15)
               {
                    loopDriverCtrl(attack_angle, speed);
               }
               else if (attack_angle >= 16 && attack_angle <= 90)
               {
                    attack_angle *= 1.8;
                    loopDriverCtrl(attack_angle, speed);
               }
               else if (attack_angle >= 91 && attack_angle <= 150)
               {
                    attack_angle *= 1.3;
                    loopDriverCtrl (attack_angle, speed);
               }
               else if (attack_angle >= 151 && attack_angle <= 210)
               {
                    attack_angle *= 1.2;
                    loopDriverCtrl (attack_angle, speed);
               }
               else if (attack_angle >= 211 && attack_angle <= 270)
               {
                    attack_angle /= 1.3;
                    loopDriverCtrl (attack_angle, speed);
               }
               else if (attack_angle >= 271 && attack_angle <= 338)
               {
                    attack_angle /= 1.15;
                    loopDriverCtrl (attack_angle, speed);
               }
          else loopDriverCtrl(attack_angle, speed);
          }
          Serial.println(attack_angle);  
     }
}