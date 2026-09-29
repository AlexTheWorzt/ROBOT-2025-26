#include <Adafruit_BNO055.h>
#include "imu.h"

/*                                       VARIABILI GLOBALI
    Dichiariamo delle variabili globali che useremo per il codice, quali un timer per gli intervalli
    di lettura della bussola, le variabili in cui salveremo i valori degli angoli letti dalla bussola
    e settiamo delle macro direttamente dalla libreria di Adafruit
    
*/
Adafruit_BNO055 bno = Adafruit_BNO055 (55, 0x28);

unsigned long imu_timer{0};
int angolo{0};
int angoloAss;
int angoloRel;

//                                              INIZIALIZZAZIONE

void init_imu(){

    // Questo primo while controlla se la bussola sta leggendo e perciò funzionando, se la bussola non va stampa a schermo
    // che non l'ha trovata e non va avanti con la lettura
    while(!(bno.begin(OPERATION_MODE_IMUPLUS))){
        Serial.println("Bussola non trovata!");
    }

    // Congigura la bussola 
    bno.setExtCrystalUse(true);

    // Imposta il timer per le letture della bussola
    imu_timer=millis();

    // Un delay per fare in modo che la bussola venga configurata prima di cominciare la lettura, se non ci fosse leggerebbe
    // dati prima di essere configurata il che li renderebbe corrotti
    delay(500);

    // Imposta la funzione che fa leggere effettivamente la bussola
    imu::Vector<3>euler=bno.getVector(Adafruit_BNO055::VECTOR_EULER);

    /*                                          LETTURA BUSSOLA 0° VERSO LA PORTA
    
        La bussola che usiamo è come una bussola magnetica, punta verso un Nord e questo Nord non può essere spostato chiaramente.
       Noi abbiamo bisogno che il robot abbia lo 0° davanti come punto di riferimento, quindi o si sposta il campo in modo che la
       porta che il robot attacca si trovi all'angolo 0 della bussola, o semplicemente facciamo una sottrazione in modo che, anche
       se la porta di attacco si trova ad esempio a 300° rispetto allo 0°, sottraendo a ciò che legge 300° avrà davanti a sè 0°
       e di conseguenza tutti gli altri angoli saranno giusti.

       Chiaramente un problema sorge se, quando la bussola legge ad esempio 200° e noi ne sottraiamo 300°, andiamo sotto lo 0,
       lo risolviamo dopo è molto semplice*/

    // Per cominciare questa procedura prendiamo l'angolo assoluto della porta, ossia il vero angolo che la bussola legge davanti
    // a sè verso la porta. E' nel setup perciò lo legge 1 sola volta e non cambierà mai.
    angoloAss= (int) euler.x();
}

/* Questa è la funzione principale che legge la bussola e fa gli aggiustamenti che ci servono*/
int read_imu(){

    // Imposta il timer per ogni lettura che fa la bussola
    if (millis()-imu_timer>=20){

        // Legge l'angolo in tempo reale
        imu::Vector<3>euler=bno.getVector(Adafruit_BNO055::VECTOR_EULER);
        angolo= (int) euler.x();

        // Fa la sottrazione di cui è stato parlato prima, tra l'angolo letto in quel momento e l'angolo assoluto della porta
        // preso in considerazione prima. L'angolo relativo ricavato è ciò su cui lavoreremo veramente
        angoloRel=angolo-angoloAss;

        // Se l'angolo è minore di zero gli aggiunge 360°, quindi avremo sempre angoli positivi e corrispondenti ai veri angoli
        // che ci servono
        if(angoloRel<0){
            angoloRel+=360;
        }
        
        // Serve per far continuare il timer di letture col millis
        imu_timer = millis();
    }
    // Returna il valore dell'angolo relativo da poter utilizzare nel resto del codice
    return angoloRel;
}

// Test per vedere se la bussola legge correttamente
void test_imu()
{
    angoloRel = read_imu();
    Serial.println(angoloRel);
}