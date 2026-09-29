#include <Arduino.h>
#include <stdbool.h>
#include "ball.h"
#include "pins.h"

int angolo_palla;
int distanza_palla;
bool palla = false;

/*                                                       INIZIALIZZAZIONE                                                                 */

void init_palla() {
    SERIAL_PALLA.begin(9600);
}

/*                                                  FUNZIONE PRINCIPALE LETTURA PALLA

    Riceviamo i valori di distanza e angolo nello stesso momento, perciò abbiamo bisogno di un modo per riconoscerli:
        - L'angolo ha sempre l'ultimo bit uguale a 0
        - La distanza ha sempre l'ultimo bit uguale a 1

    In questo modo avremo sempre angoli pari e distanza dispari, ma non è un grosso problema dato che la precisione è abbastanza
    Questo sistema ha 2 pro:
        - Riuscire a riconoscere la differenza tra i due
        - Riuscire ad inserire gli angoli in 1 solo byte, infatti gli angoli vanno da [0;360], ma dividendo per 2
          vanno da [0;180] e entrano in 1 byte che contiene fino a 255
    
    La distanza è molto imprecisa e non viene mai utilizzata, invece l'angolo è fondamentale ma ricaviamo comunque entrambe
    */
void leggi_palla () {

    // Funziona affinchè la seriale riceve
    while (SERIAL_PALLA.available()) {

    /* Inseriamo in messaggio ciò che arriva dalla seriale, sia distanza che angolo
        uint8_t è un tipo di variabile intera, senza segno e al massimo 1 byte
        L'ATmega divide già i valori dell'angolo per 2, perciò arrivano già fino a 180 e entrano 
        in mesaggio che è massimo 1 byte
    */
    uint8_t messaggio = SERIAL_PALLA.read();

    char LSB = messaggio & 1; // Ricaviamo l'ultimo bit per capire se è distanza o angolo

    // Controllo dell'ultimo bit, se è 1 in messaggio abbiamo la distanza, se no è l'angolo
    if (LSB==1) { 
        distanza_palla = messaggio;
        if(distanza_palla > 1) // Controllo se la distanza è minore di 1 significa che non legge la palla e diventa falsa
            palla=true;
        else
            palla=false;
        }
        else {
            angolo_palla = messaggio*2; // Moltiplica l'angolo per 2 rientrando da [0;180] a [0;360] ma abbiamo comunque solo angoli pari
        }
     }
}

// Funzioni che permettono il passaggio dei valori quando servono 

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

// Test se il robot vede la palla, se la vede stampa sia l'angolo che la distanza
void test_palla() {

     leggi_palla();
   
    if(palla){
        Serial.println(String("anglo della palla: ") + angolo_palla);
        Serial.println(String("distanza della palla: ") + distanza_palla);
    }
    else Serial.println("non si vede la palla");
     delay(500);
}