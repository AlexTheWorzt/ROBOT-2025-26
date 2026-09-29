#include <Arduino.h>
#include <math.h>
#include "cam.h"
#include "pins.h"

static unsigned long tempo_giallo = 0;
static unsigned long tempo_blu = 0;

// Porta gialla
static float angoloPortaGialla = VAL_ERR;
static float distanzaPortaGialla = 0;
static float ultimo_angologiallo = VAL_ERR;

// Porta blu
static float angoloPortaBlu = VAL_ERR;
static float distanzaPortaBlu = 0;
static float ultimo_angoloblu = VAL_ERR;

// Output logica robot
float angolo_porta_difesa = VAL_ERR;
float angolo_porta_attacco = VAL_ERR;
float distanza_porta_difesa = VAL_ERR;
float distanza_porta_attacco = VAL_ERR;

float angolo_robot = VAL_ERR;
float posizione_robot = VAL_ERR;

int valore_switch = 0;



void init_cam() {
  pinMode(swtch_porta, INPUT_PULLUP);
  SERIAL_CAM.begin(19200);
  SERIAL_CAM.setTimeout(10);  
  valore_switch = digitalRead(swtch_porta);
}

void leggi_telecamera() {

  if (SERIAL_CAM.available()) {

    char line[64];
    int len = SERIAL_CAM.readBytesUntil('\n', line, sizeof(line) - 1);
    if (len > 0) {
      line[len] = '\0';
      char *ptr = line;
      
      // Trova Y
      char *y_start = strchr(ptr, 'Y');
      if (y_start) {
        int angolo, area;
        if (sscanf(y_start, "Y%d,%dy", &angolo, &area) == 2) {
          if (angolo >= 0 && angolo <= 359 && area >= 0) {
            ultimo_angologiallo = angolo;
            tempo_giallo = millis();
          }
        }
      }
      
      // Trova B
      char *b_start = strchr(ptr, 'B');
      if (b_start) {
        int angolo, area;
        if (sscanf(b_start, "B%d,%db", &angolo, &area) == 2) {
          if (angolo >= 0 && angolo <= 359 && area >= 0) {
            ultimo_angoloblu = angolo;
            tempo_blu = millis();
          }
        }
      }
    }
  }

  // Aggiorna valori correnti (con timeout 500ms)
  if (millis() - tempo_giallo < 500) {
    angoloPortaGialla = ultimo_angologiallo;
    distanzaPortaGialla = distanzaPortaGialla; // mantieni l'area ricevuta
  } else {
    angoloPortaGialla = VAL_ERR;
  }
  
  if (millis() - tempo_blu < 500) {
    angoloPortaBlu = ultimo_angoloblu;
    distanzaPortaBlu = distanzaPortaBlu;
  } else {
    angoloPortaBlu = VAL_ERR;
  }

  // Leggi switch
  valore_switch = digitalRead(swtch_porta);
  
  // Assegna ruoli
  assegnaRuoli();
  
  // Calcolo angolo robot 
  if (angolo_porta_attacco != VAL_ERR && angolo_porta_difesa != VAL_ERR) {
    angolo_robot = 180.0 - angolo_porta_attacco - angolo_porta_difesa;
    angolo_robot = fmod(angolo_robot, 360.0);
    if (angolo_robot < 0) angolo_robot += 360.0;
  } else {
    angolo_robot = VAL_ERR;
  }
}

void assegnaRuoli() {
  if (valore_switch == LOW) {
    // GIALLO = ATTACCO
    angolo_porta_attacco = /*ultimo_angologiallo;*/(ultimo_angologiallo > 90) ? ultimo_angologiallo - 360 : ultimo_angologiallo;
    angolo_porta_difesa  = /*ultimo_angoloblu;*/(ultimo_angoloblu > 90) ? ultimo_angoloblu - 180 : ultimo_angoloblu;
    angolo_porta_attacco = angolo_porta_attacco;
    angolo_porta_difesa = angolo_porta_difesa;
  } else {
    // BLU = ATTACCO
    angolo_porta_attacco = /*ultimo_angoloblu;*/(ultimo_angoloblu > 90) ? ultimo_angologiallo - 180 : ultimo_angoloblu;
    angolo_porta_difesa  = /*ultimo_angologiallo;*/(ultimo_angologiallo > 90) ? ultimo_angologiallo - 360 : ultimo_angologiallo;
    angolo_porta_attacco = -angolo_porta_attacco;
    angolo_porta_difesa = -angolo_porta_difesa;
  }
}

void distanze_porte() {
  if (angolo_porta_attacco == VAL_ERR || angolo_porta_difesa == VAL_ERR) {
    distanza_porta_attacco = VAL_ERR;
    distanza_porta_difesa  = VAL_ERR;
    return;
  }

  float delta = fabs(angolo_porta_attacco - angolo_porta_difesa);
  if (delta < 5 || delta > 355) {
    distanza_porta_attacco = VAL_ERR;
    distanza_porta_difesa  = VAL_ERR;
    return;
  }

  float sin_r = sin(radians(angolo_robot));
  if (fabs(sin_r) < 0.01) {
    distanza_porta_attacco = VAL_ERR;
    distanza_porta_difesa  = VAL_ERR;
    return;
  }

  distanza_porta_attacco = (lunghezza_campo / sin_r) * sin(radians(angolo_porta_difesa));
  distanza_porta_difesa  = (lunghezza_campo / sin_r) * sin(radians(angolo_porta_attacco));
}

void dove_sono() {
  if (angolo_porta_attacco == VAL_ERR || angolo_porta_difesa == VAL_ERR) {
    posizione_robot = VAL_ERR;
  } else {
    posizione_robot = sin(radians(angolo_porta_attacco)) * distanza_porta_difesa;
  }
}

float get_angolo_porta_attacco() {
  leggi_telecamera();
  assegnaRuoli(); 
  return angolo_porta_attacco;}
float get_distanza_porta_attacco() {
  leggi_telecamera();
  assegnaRuoli(); 
  return distanza_porta_attacco;}
float get_angolo_porta_difesa() {
  leggi_telecamera();
  assegnaRuoli(); 
  return angolo_porta_difesa;}
float get_distanza_porta_difesa() {
  leggi_telecamera();
  assegnaRuoli(); 
  return distanza_porta_difesa;}
float get_posizione_robot() {
  leggi_telecamera();
  assegnaRuoli(); 
  return posizione_robot;}

void test_porta() {
  leggi_telecamera();
  distanze_porte();
  dove_sono();

  Serial.print("SWITCH: "); Serial.println(valore_switch);
  Serial.print("POSIZIONE: "); Serial.println(posizione_robot);
  Serial.print("ANGOLO DIFESA: "); Serial.println(angolo_porta_difesa);
  Serial.print("ANGOLO ATTACCO: "); Serial.println(angolo_porta_attacco);
  Serial.print("DIST ATTACCO: "); Serial.println(distanza_porta_attacco);
  Serial.print("DIST DIFESA: "); Serial.println(distanza_porta_difesa);
  Serial.println("---------------------------");

  delay(200);
}