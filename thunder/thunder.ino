// Sentidos
#define MOTOR_ESQUERDO_FRENTE 5
#define MOTOR_ESQUERDO_TRAS 6
#define MOTOR_DIREITO_FRENTE 9
#define MOTOR_DIREITO_TRAS 10

// Sensores
#define SENSOR_EXTREMO_ESQUERDO A0
#define SENSOR_ESQUERDO A1
#define SENSOR_CENTRO A2
#define SENSOR_DIREITO A3
#define SENSOR_EXTREMO_DIREITO A4
#define LDR_esquerda A5
#define LDR_direita A6

void setup() {
  pinMode(MOTOR_ESQUERDO_FRENTE, OUTPUT);
  pinMode(MOTOR_ESQUERDO_TRAS, OUTPUT);
  pinMode(MOTOR_DIREITO_FRENTE, OUTPUT);
  pinMode(MOTOR_DIREITO_TRAS, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  //embreve
}