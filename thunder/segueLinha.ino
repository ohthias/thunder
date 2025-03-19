/**
 * Função segueLinha
 * 
 * Esta função é responsável por controlar o movimento do robô seguindo uma linha preta.
 * Ela lê os valores dos sensores de linha e ajusta a velocidade dos motores para manter o robô na linha.
 * 
 * Lógica:
 * - Se todos os sensores detectarem preto, o robô para e chama a função identificaVerde.
 * - Se algum sensor da esquerda detectar preto, o robô corrige sua trajetória para a esquerda.
 * - Se algum sensor da direita detectar preto, o robô corrige sua trajetória para a direita.
 * - Se nenhum sensor detectar preto, o robô gira no lugar para encontrar a linha.
 * - Caso contrário, o robô continua em linha reta.
 * 
 * A função utiliza um controlador PID para ajustar a velocidade dos motores e manter o robô na linha.
 * 
 * Sensores utilizados:
 * - SENSOR_EXTREMO_ESQUERDO
 * - SENSOR_ESQUERDO
 * - SENSOR_CENTRO
 * - SENSOR_DIREITO
 * - SENSOR_EXTREMO_DIREITO
 * 
 * Variáveis globais utilizadas:
 * - preto: valor de referência para a cor preta
 * - velocidade_base: velocidade base dos motores
 * - velocidade_correção: valor de correção de velocidade
 * - velocidade_max: velocidade máxima dos motores
 * - Kp, Ki, Kd: constantes do controlador PID
 * - erro, erro_anterior, integral, derivativo: variáveis do controlador PID
 * - motoresRobo: objeto que controla os motores do robô
 * 
 * A função também utiliza a função delay para criar pausas no código.
 */

void segueLinha() {
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
    motoresRobo.off();
    delay(150);
    identificaVerde();
  } else if (algum_esquerda_preto) {
    Serial.println("Algum sensor da esquerda está vendo preto, fazendo correção");
    if (valor_extremo_esquerdo <= preto) {
      Serial.println("Curva acentuada para a esquerda detectada");
      velocidade_esquerda = velocidade_base - velocidade_correção;
      velocidade_direita = velocidade_base + velocidade_correção;
    } else {
      erro = valor_esquerdo - valor_direito;
      integral += erro;

      derivativo = erro - erro_anterior;

      int correcao = Kp * erro + Ki * integral + Kd * derivativo;

      velocidade_esquerda = velocidade_base - correcao;
      velocidade_direita = velocidade_base + correcao;
      velocidade_esquerda = constrain(velocidade_esquerda, 0, velocidade_max);
      velocidade_direita = constrain(velocidade_direita, 0, velocidade_max);
    }
  } else if (algum_direita_preto) {
    Serial.println("Algum sensor da direita está vendo preto, fazendo correção");
    if (valor_extremo_direito <= preto) {
      Serial.println("Curva acentuada para a direita detectada");
      velocidade_esquerda = velocidade_base + velocidade_correção; 
      velocidade_direita = velocidade_base - velocidade_correção;
    } else {
      erro = valor_esquerdo - valor_direito;
      integral += erro;
      derivativo = erro - erro_anterior;

      int correcao = Kp * erro + Ki * integral + Kd * derivativo;

      velocidade_esquerda = velocidade_base - correcao;
      velocidade_direita = velocidade_base + correcao;
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
    Serial.println("Nenhum sensor detectando preto - Movimento reto");
    velocidade_esquerda = velocidade_base;
    velocidade_direita = velocidade_base;
  }

  motoresRobo.run(velocidade_esquerda, velocidade_direita);

  erro_anterior = erro;

  delay(10);
}