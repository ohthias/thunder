#include <HCSR04.h>
#include "/class/dualMotors.h"

DualMotor motoresRobo(2, 3, 4, 5);

// Sensores Refletância
#define SENSOR_EXTREMO_ESQUERDO A0
#define SENSOR_ESQUERDO A1
#define SENSOR_CENTRO A2
#define SENSOR_DIREITO A3
#define SENSOR_EXTREMO_DIREITO A4

// Sensores LDR
#define LDR_esquerda A7
#define LDR_direita A8

// Botões
#define button_center 6
#define button_right 7
#define button_left 8

// Flags Verde
enum class Flags_verde {
  curvaDireita,
  curvaEsquerda,
  beco,
  nenhum
};
Flags_verde flags = Flags_verde::nenhum;

/* PID */
float Kp = 1.2;  // Ganho Proporcional
float Ki = 0.0;  // Ganho Integral
float Kd = 0.8;  // Ganho Derivativo

int erro = 0;
int erro_anterior = 0;
int integral = 0;
int derivativo = 0;

bool flagObstaculo = false;
int distancia_frente = 0;
#define T_PIN_frente 24
#define E_PIN_frente 25
UltraSonicDistanceSensor ultra_frente(T_PIN_frente, E_PIN_frente);

/* Calibração */
int preto = 200;
int verde = 50;

/* Velocidade */
int velocidade_esquerda, velocidade_direita;
int velocidade_base = 10;  // Velocidade base dos motores (aumentada para melhor movimento)
int velocidade_max = 200;

void setup() {
  pinMode(button_center, INPUT);
  pinMode(button_right, INPUT);
  pinMode(button_left, INPUT);

  motoresRobo.off();
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(button_center) == HIGH) {
    calibragem();
  } else if(digitalRead(button_right) == HIGH) {
    distancia_frente = ultra_frente.measureDistanceCm();
    distancia_frente <= 15 ? flagObstaculo = true : flagObstaculo = false;

    while (flags == Flags_verde::nenhum) {
      segueLinha();
      if(flagObstaculo) {
        desvioObstaculo();
      }
    }

    //Flags de curva
    switch(flags) {
      case Flags_verde::curvaDireita:
        Serial.println("Curva para a direita detectada");
        while(tempoCurva < 1000) {
          motoresRobo.curvaDireita(velocidade_base);
          tempoCurva++;
        }
        flags = Flags_verde::nenhum;
        break;

      case Flags_verde::curvaEsquerda:
        Serial.println("Curva para a esquerda detectada");
        while(tempoCurva < 1000) {
          motoresRobo.curvaEsquerda(velocidade_base);
          tempoCurva++;
        }
        delay(1000);
        flags = Flags_verde::nenhum;
        break;

      case Flags_verde::beco:
        Serial.println("Beco detectado");
        while(tempoCurva < 2000) {
          motoresRobo.curvaEsquerda(velocidade_base);
          tempoCurva++;
        }
        delay(1000);
        flags = Flags_verde::nenhum;
        break;

      case Flags_verde::nenhum:
        Serial.println("Nenhuma curva ou beco detectado");
        break;
    }
    delay(100);
}
}