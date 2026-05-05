#include <Arduino.h>
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



void setup(){
  Serial.begin(9600);
  init_palla();
  motori_init();
  init_imu();
  init_DriverCtrl();
  line_init();
  init_cam();
  init_mouth();
  init_kicker();
  buzzer_init();
}

void loop(){




  // MOT_test_4ruote();
  //MOT_test_diagonali();
  //MOT_test_quadrato();
  //Serial.println(read_imu());
  //Serial.println("oooo");
  //loopDriverCtrl(0, 100);
  // test_imu();
  // test_inter_imu();
  //read_imu();
  // test_diagonali();
  //test_quadrato();
  // test_Ball();
  // test_test_Ball();
  // line_Read_val();
  // test_line();
  Get_Out_Line();
  // loopDriverCtrl(0, 200);
  // test_palla();
  attacker();
  // test_porta();
  // leggi_telecamera();
  // test_mouth();
  // mouth_sens();
  // kicker_test(); 
  // kicker_test_mouth()
  // loopDriverCtrl_distortion(0, 0);
}


/*                                                 CAMBIAMENTI EFFETTUATI
                                      Messo la distanza al kicker prima di tirare
                                       diminuita soglia kicker






*/