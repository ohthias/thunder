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
    analogWrite(MOTOR_ESQUERDO_FRENTE, 0);
    analogWrite(MOTOR_DIREITO_FRENTE, 0);
    delay(150);
    identificaVerde();
  } else if (algum_esquerda_preto) {
    Serial.println("Algum sensor da esquerda está vendo preto, fazendo correção");
    if (valor_extremo_esquerdo <= preto) {
      Serial.println("Curva acentuada para a esquerda detectada");
      velocidade_esquerda = velocidade_base - 100;  // Ajuste esses valores conforme necessário
      velocidade_direita = velocidade_base + 100;
    } else {
      erro = valor_esquerdo - valor_direito;
      integral += erro;

      derivativo = erro - erro_anterior;

      int correcao = Kp * erro + Ki * integral + Kd * derivativo;

      velocidade_esquerda = velocidade_base - correcao;
      velocidade_direita = velocidade_base + correcao;
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

  analogWrite(MOTOR_ESQUERDO_FRENTE, velocidade_esquerda);
  analogWrite(MOTOR_ESQUERDO_TRAS, 0);
  analogWrite(MOTOR_DIREITO_FRENTE, velocidade_direita);
  analogWrite(MOTOR_DIREITO_TRAS, 0);

  erro_anterior = erro;

  delay(10);
}

void identificaVerde() {
  int valor_LDR_esquerda = analogRead(LDR_esquerda);
  int valor_LDR_direita = analogRead(LDR_direita);

  if (valor_LDR_esquerda < verde && valor_LDR_direita < verde) {
    flags = Flags_verde::beco;
  } else if (valor_LDR_direita < verde) {
    flags = Flags_verde::curvaDireita;
  } else if (valor_LDR_esquerda < verde) {
    flags = Flags_verde::curvaEsquerda;
  } else {
    flags = Flags_verde::nenhum;
  }
  delay(1500);
}