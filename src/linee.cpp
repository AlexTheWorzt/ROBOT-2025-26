#include <Arduino.h>
#include "pins.h"
#include "linee.h"
#include "motori.h"
#include "ball.h"
#include "moto.h"

int color[8];
int line_Sens[8];
int line_Sens_Ang[8] = {180, 180, -90, -90, 0, 0, 90, 90};
void line_init()
{
    Serial.begin(9600);

    pinMode(S1IN,INPUT);
    pinMode(S1ES,INPUT);
    pinMode(S2IN,INPUT);
    pinMode(S2ES,INPUT);
    pinMode(S3IN,INPUT);
    pinMode(S3ES,INPUT);
    pinMode(S4IN,INPUT);
    pinMode(S4ES,INPUT);

    color[0] = (600);
    color[1] = (600); 
    color[2] = (500); 
    color[3] = (500);
    color[4] = (700);
    color[5] = (960);
    color[6] = (600);
    color[7] = (600);
}

void test_line()
{
    unsigned long tempo = 0;
    unsigned int ritardo = 275;
    if (millis() - tempo > ritardo)
    {
    Serial.print("NORD INTERNO: ");
    line_Sens[0] = analogRead(S1IN);
    Serial.println(line_Sens[0]);
    Serial.print("NORD ESTERNO: ");
    line_Sens[1] = analogRead(S1ES);
    Serial.println(line_Sens[1]);
    Serial.print("EST INTERNO: ");
    line_Sens[2] = analogRead(S2IN);
    Serial.println(line_Sens[2]);
    Serial.print("EST ESTERNO: ");
    line_Sens[3] = analogRead(S2ES);
    Serial.println(line_Sens[3]);
    Serial.print("SUD INTERNO: ");
    line_Sens[4] = analogRead(S3IN);
    Serial.println(line_Sens[4]);
    Serial.print("SUD ESTERNO: ");
    line_Sens[5] = analogRead(S3ES);
    Serial.println(line_Sens[5]);
    Serial.print("OVEST INTERNO: ");
    line_Sens[6] = analogRead(S4IN);
    Serial.println(line_Sens[6]);
    Serial.print("OVEST ESTERNO: ");
    line_Sens[7] = analogRead(S4ES);
    Serial.println(line_Sens[7]);
    Serial.println("--------------------");
    delay(10000);
    tempo = millis();
    }
}


void Get_Out_Line()
{
    int ball_ang = passa_angolo_palla();
    // bool line_got[8];
    line_Sens[0] = analogRead(S1IN);
    line_Sens[1] = analogRead(S1ES);
    line_Sens[2] = analogRead(S2IN);
    line_Sens[3] = analogRead(S2ES);
    line_Sens[4] = analogRead(S3IN);
    line_Sens[5] = analogRead(S3ES);
    line_Sens[6] = analogRead(S4IN);
    line_Sens[7] = analogRead(S4ES);

    // Robot bloccato SUD palla a destra
    if ((line_Sens[4] >= color[4] || line_Sens[5] >= color[5]) && ball_ang >= 91 && ball_ang <= 150 )
    {
         unsigned long tempo = millis();
        while (millis() - tempo <= 150)
        {
            loopDriverCtrl(45, 255);
        }
    }

    // Robot bloccato SUD palla a sinistra
    else if ((line_Sens[4] >= color[4] || line_Sens[5] >= color[5]) && ball_ang >= 211 && ball_ang <= 270 )
    {
         unsigned long tempo = millis();
        while (millis() - tempo <= 150)
        {
            loopDriverCtrl(315, 255);
        }
    }


    // Linee NORD, EST, OVEST
    else if (line_Sens[2] >= color[2] && line_Sens[3] >= color[3] && line_Sens[6] >= color[6] && line_Sens[7] >= color[7] && line_Sens[0] >= color[0] && line_Sens[1] >= color[1])
    {
        unsigned long tempo = millis();
        while (millis() - tempo <= 200)
        {
            loopDriverCtrl(180, 255);
        }
    }

    // Linee EST e OVEST
    else if (line_Sens[3] >= color[3] && line_Sens[2] >= color[2] && line_Sens[6] >= color[6] && line_Sens[7] >= color[7])
    {
        unsigned long tempo = millis();
        while (millis() - tempo <= 200)
        {
            loopDriverCtrl(180, 255);
        }
    }

    // Linee NORD e EST INT.
    else if (line_Sens[0] >= color[0] && line_Sens[2] >= color[2])
        {
            unsigned long tempo = millis();
            while (millis() - tempo <= 200)
            {
                loopDriverCtrl(135, 220);
            }
        }

    // Linee NORD e EST EST.
    else if (line_Sens[1] >= color[1] && line_Sens[3] >= color[3])
    {
        unsigned long tempo = millis();
        while (millis() - tempo <= 200)
        {
            loopDriverCtrl(135, 180);
        }
    }

    // Linee NORD e OVEST INT.
    else if (line_Sens[0] >= color[0] && line_Sens[6] >= color[6])
    {
        unsigned long tempo = millis();
        while (millis() - tempo <= 200)
        {
            loopDriverCtrl(225, 220);
        }
    }

    // Linee NORD e OVEST EST.
    else if (line_Sens[1] >= color[1] && line_Sens[7] >= color[7])
    {
        unsigned long tempo = millis();
        while (millis() - tempo <= 200)
        {
            loopDriverCtrl(225, 180);
        }
    }
    // Linee SUD e EST INT.
    else if (line_Sens[4] >= color[4] && line_Sens[2] >= color[2])
        {
            unsigned long tempo = millis();
            while (millis() - tempo <= 200)
            {
                loopDriverCtrl(315, 220);
            }
        }

    // Linee SUD e EST EST.
    else if (line_Sens[5] >= color[5] && line_Sens[3] >= color[3])
    {
        unsigned long tempo = millis();
        while (millis() - tempo <= 200)
        {
            loopDriverCtrl(315, 180);
        }
    }

    // Linee SUD e OVEST INT.
    else if (line_Sens[4] >= color[4] && line_Sens[6] >= color[6])
    {
        unsigned long tempo = millis();
        while (millis() - tempo <= 200)
        {
            loopDriverCtrl(45, 220);
        }
    }

    // Linee SUD e OVEST EST.
    else if (line_Sens[5] >= color[5] && line_Sens[7] >= color[7])
    {
        unsigned long tempo = millis();
        while (millis() - tempo <= 200)
        {
            loopDriverCtrl(45, 180);
        }
    }

    // Linee EST e OVEST
    else if (line_Sens[2] >= color[2] && line_Sens[3] >= color[3] && line_Sens[6] >= color[6] && line_Sens[7] >= color[7])
    {
        unsigned long tempo = millis();
        while (millis() - tempo <= 200)
        {
            loopDriverCtrl(180, 255);
        }
    }





    /* Linee generali SINGOLE
        I sensori EST e OVEST hanno velocità di fuga più brevi da 75ms
        I sensori NORD e SUD da 200ms

        I sensori interni hanno velocità di fuga più alte a 255 PWM
        I sensori esterni a 180 PWM
     */
    else if (line_Sens[0] >= color[0])
    {
        unsigned long tempo = millis();
                while (millis() - tempo <= 100)
                {
                    loopDriverCtrl(line_Sens_Ang[0], 255);
                }
    }
    else if (line_Sens[1] >= color[1])
    {
        unsigned long tempo = millis();
                while (millis() - tempo <= 100)
                {
                    loopDriverCtrl(line_Sens_Ang[1], 180);
                }
    }
    else if (line_Sens[2] >= color[2])
    {
        unsigned long tempo = millis();
                while (millis() - tempo <= 75)
                {
                    loopDriverCtrl(line_Sens_Ang[2], 255);
                }
    }
    else if (line_Sens[3] >= color[3])
    {
        unsigned long tempo = millis();
                while (millis() - tempo <= 75)
                {
                    loopDriverCtrl(line_Sens_Ang[3], 180);
                }
    }
    else if (line_Sens[4] >= color[4])
    {
        unsigned long tempo = millis();
                while (millis() - tempo <= 200)
                {
                    loopDriverCtrl(line_Sens_Ang[4], 255);
                }
    }
    else if (line_Sens[5] >= color[5])
    {
        unsigned long tempo = millis();
                while (millis() - tempo <= 200)
                {
                    loopDriverCtrl(line_Sens_Ang[5], 180);
                }
    }
    else if (line_Sens[6] >= color[6])
    {
        unsigned long tempo = millis();
                while (millis() - tempo <= 200)
                {
                    loopDriverCtrl(line_Sens_Ang[6], 255);
                }
    }
    else if (line_Sens[7] >= color[7])
    {
        unsigned long tempo = millis();
                while (millis() - tempo <= 200)
                {
                    loopDriverCtrl(line_Sens_Ang[7], 180);
                }
    }
    

        //  TEST LINEA PER LINEA
        // for (int i = 0; i < 8; i++)
        // {
        //     if (line_Sens[i] >= color[i])
        // {
        //     line_got[i] = true;
        //     Serial.print("Sensore ");
        //     Serial.print(i);
        //     Serial.print(" ");
        //     Serial.print(line_Sens[i]);
        //     Serial.print(" ");
        //     Serial.println(line_got[i]?1:0 );
        //     loopDriverCtrl(line_Sens_Ang[i], 255);
        // }
        // }
        
}

