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

// Variáveis do PID
float Kp = 1.2;  // Ganho Proporcional
float Ki = 0.0;  // Ganho Integral
float Kd = 0.8;  // Ganho Derivativo

int erro = 0;
int erro_anterior = 0;
int integral = 0;
int derivativo = 0;

int velocidade_esquerda, velocidade_direita;

/* Calibração */
int preto = 200;
int velocidade_base = 10;  // Velocidade base dos motores (aumentada para melhor movimento)
int velocidade_max = 200;

void setup() {
  pinMode(MOTOR_ESQUERDO_FRENTE, OUTPUT);
  pinMode(MOTOR_ESQUERDO_TRAS, OUTPUT);
  pinMode(MOTOR_DIREITO_FRENTE, OUTPUT);
  pinMode(MOTOR_DIREITO_TRAS, OUTPUT);

  Serial.begin(9600);
}

/** @brief Função principal do robô.
 * Lê os valores dos sensores de linha e determina a ação apropriada para o robô:
 * - Se todos os sensores detectam preto, o robô para.
 * - Se algum sensor da esquerda detecta preto, o robô corrige sua direção para a esquerda.
 * - Se algum sensor da direita detecta preto, o robô corrige sua direção para a direita.
 * - Se nenhum sensor detecta preto, o robô gira no lugar para encontrar a linha.
 * - Se nenhum sensor detecta preto, o robô se move em linha reta.
 * 
 * A correção da direção é feita utilizando um controlador PID (Proporcional, Integral, Derivativo).
 * 
 * Variáveis:
 * - valor_extremo_esquerdo: Valor lido do sensor extremo esquerdo.
 * - valor_esquerdo: Valor lido do sensor esquerdo.
 * - valor_centro: Valor lido do sensor central.
 * - valor_direito: Valor lido do sensor direito.
 * - valor_extremo_direito: Valor lido do sensor extremo direito.
 * - todos_preto: Indica se todos os sensores detectam preto.
 * - nenhum_preto: Indica se nenhum sensor detecta preto.
 * - algum_esquerda_preto: Indica se algum sensor da esquerda detecta preto.
 * - algum_direita_preto: Indica se algum sensor da direita detecta preto.
 * - erro: Diferença entre os valores dos sensores principais (esquerdo e direito).
 * - erro_anterior: Erro calculado na iteração anterior.
 * - correcao: Valor de correção calculado pelo controlador PID.
 * - velocidade_esquerda: Velocidade do motor esquerdo.
 * - velocidade_direita: Velocidade do motor direito.
 * 
 * Constantes:
 * - preto: Valor limite para considerar que um sensor detecta preto.
 * - velocidade_base: Velocidade base dos motores.
 * - velocidade_max: Velocidade máxima permitida para os motores.
 */

void loop() {
  int valor_extremo_esquerdo = analogRead(SENSOR_EXTREMO_ESQUERDO);
  int valor_esquerdo = analogRead(SENSOR_ESQUERDO);
  int valor_centro = analogRead(SENSOR_CENTRO);
  int valor_direito = analogRead(SENSOR_DIREITO);
  int valor_extremo_direito = analogRead(SENSOR_EXTREMO_DIREITO);

  bool todos_preto = (valor_extremo_esquerdo <= preto && valor_esquerdo <= preto && valor_centro <= preto && valor_direito <= preto && valor_extremo_direito <= preto);
  bool nenhum_preto = (valor_extremo_esquerdo > preto && valor_esquerdo > preto && valor_centro > preto && valor_direito > preto && valor_extremo_direito > preto);
  bool algum_esquerda_preto = (valor_extremo_esquerdo <= preto || valor_esquerdo <= preto);
  bool algum_direita_preto = (valor_extremo_direito <= preto || valor_direito <= preto);

  if (todos_preto) {
    Serial.println("Estão todos vendo preto - Parando o robô");
    analogWrite(MOTOR_ESQUERDO_FRENTE, 0);
    analogWrite(MOTOR_DIREITO_FRENTE, 0);
    delay(150);
  } else if (algum_esquerda_preto) {
    Serial.println("Algum sensor da esquerda está vendo preto, fazendo correção");
    if (valor_extremo_esquerdo <= preto) {
      Serial.println("Curva acentuada para a esquerda detectada");
      velocidade_esquerda = velocidade_base - 100;  // Ajuste esses valores conforme necessário
      velocidade_direita = velocidade_base + 100;
    } else {
      // Calcula o erro (diferença entre os sensores principais)
      erro = valor_esquerdo - valor_direito;
      // Calcula o termo integral
      integral += erro;

      // Calcula o termo derivativo
      derivativo = erro - erro_anterior;

      // Calcula a correção do PID
      int correcao = Kp * erro + Ki * integral + Kd * derivativo;

      // Ajusta as velocidades dos motores
      velocidade_esquerda = velocidade_base - correcao;
      velocidade_direita = velocidade_base + correcao;

      // Limita as velocidades dos motores
      velocidade_esquerda = constrain(velocidade_esquerda, 0, 255);
      velocidade_direita = constrain(velocidade_direita, 0, 255);
    }
  } else if (algum_direita_preto) {
    Serial.println("Algum sensor da direita está vendo preto, fazendo correção");
    if (valor_extremo_direito <= preto) {
      Serial.println("Curva acentuada para a direita detectada");
      velocidade_esquerda = velocidade_base + 100;  // Ajuste esses valores conforme necessário
      velocidade_direita = velocidade_base - 100;
    } else {
      // Calcula o erro (diferença entre os sensores principais)
      erro = valor_esquerdo - valor_direito;
      // Calcula o termo integral
      integral += erro;

      // Calcula o termo derivativo
      derivativo = erro - erro_anterior;

      // Calcula a correção do PID
      int correcao = Kp * erro + Ki * integral + Kd * derivativo;

      // Ajusta as velocidades dos motores
      velocidade_esquerda = velocidade_base - correcao;
      velocidade_direita = velocidade_base + correcao;

      // Limita as velocidades dos motores
      velocidade_esquerda = constrain(velocidade_esquerda, 0, velocidade_max);
      velocidade_direita = constrain(velocidade_direita, 0, velocidade_max);
    }
  } else if (nenhum_preto) {
    Serial.println("Linha perdida - Girando no lugar para encontrar a linha");
    analogWrite(MOTOR_ESQUERDO_FRENTE, 100);
    analogWrite(MOTOR_DIREITO_FRENTE, 0);
    delay(500); 
    return;
  } else {
    // Nenhum sensor detectando preto - Movimento reto
    Serial.println("Nenhum sensor detectando preto - Movimento reto");
    velocidade_esquerda = velocidade_base;
    velocidade_direita = velocidade_base;
  }

  // Aplica as velocidades aos motores
  analogWrite(MOTOR_ESQUERDO_FRENTE, velocidade_esquerda);
  analogWrite(MOTOR_ESQUERDO_TRAS, 0);
  analogWrite(MOTOR_DIREITO_FRENTE, velocidade_direita);
  analogWrite(MOTOR_DIREITO_TRAS, 0);

  // Atualiza o erro anterior
  erro_anterior = erro;

  // Pequeno delay para estabilidade
  delay(10);
}