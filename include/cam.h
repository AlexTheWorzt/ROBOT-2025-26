#ifndef CAM_H
#define CAM_H

#define lunghezza_campo 93
#define VAL_ERR 999


void init_cam();
void assegnaRuoli();
void leggi_telecamera();
void distanze_porte();
void dove_sono();

float get_angolo_porta_attacco();
float get_distanza_porta_attacco();
float get_angolo_porta_difesa();
float get_distanza_porta_difesa();
float get_posizione_robot();

void test_porta();

#endif