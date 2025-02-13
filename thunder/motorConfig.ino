int diametro = 8;

void curvaEsquerda90Graus() {
  float raio = diametro / 2.0;
  float comprimentoArco = (90 * M_PI * raio) / 180.0;  // Comprimento do arco para 90 graus
  
  reiniciarEncoders();
  int posicaoInicial = lerEncoder();
  
  while ((lerEncoder() - posicaoInicial) < comprimentoArco) {
    analogWrite(MOTOR_ESQUERDO_FRENTE, 0);
    analogWrite(MOTOR_ESQUERDO_TRAS, velocidade_base);
    analogWrite(MOTOR_DIREITO_FRENTE, velocidade_base);
    analogWrite(MOTOR_DIREITO_TRAS, 0);
  }

  // Para os motores após a curva
  analogWrite(MOTOR_ESQUERDO_FRENTE, 0);
  analogWrite(MOTOR_ESQUERDO_TRAS, 0);
  analogWrite(MOTOR_DIREITO_FRENTE, 0);
  analogWrite(MOTOR_DIREITO_TRAS, 0);
}

void curvaDireita90Graus() {
  float raio = diametro / 2.0;
  float comprimentoArco = (90 * M_PI * raio) / 180.0;  // Comprimento do arco para 90 graus
  
  reiniciarEncoders();
  int posicaoInicial = lerEncoder();
  
  while ((lerEncoder() - posicaoInicial) < comprimentoArco) {
    analogWrite(MOTOR_ESQUERDO_FRENTE, velocidade_base);
    analogWrite(MOTOR_ESQUERDO_TRAS, 0);
    analogWrite(MOTOR_DIREITO_FRENTE, 0);
    analogWrite(MOTOR_DIREITO_TRAS, velocidade_base);
  }

  // Para os motores após a curva
  analogWrite(MOTOR_ESQUERDO_FRENTE, 0);
  analogWrite(MOTOR_ESQUERDO_TRAS, 0);
  analogWrite(MOTOR_DIREITO_FRENTE, 0);
  analogWrite(MOTOR_DIREITO_TRAS, 0);
}

void meiaVolta() {
  float raio = diametro / 2.0;
  float comprimentoArco = (180 * M_PI * raio) / 180.0;  // Comprimento do arco para 90 graus
  
  reiniciarEncoders();
  int posicaoInicial = lerEncoder();
  
  while ((lerEncoder() - posicaoInicial) < comprimentoArco) {
    analogWrite(MOTOR_ESQUERDO_FRENTE, velocidade_base);
    analogWrite(MOTOR_ESQUERDO_TRAS, 0);
    analogWrite(MOTOR_DIREITO_FRENTE, 0);
    analogWrite(MOTOR_DIREITO_TRAS, velocidade_base);
  }

  // Para os motores após a curva
  analogWrite(MOTOR_ESQUERDO_FRENTE, 0);
  analogWrite(MOTOR_ESQUERDO_TRAS, 0);
  analogWrite(MOTOR_DIREITO_FRENTE, 0);
  analogWrite(MOTOR_DIREITO_TRAS, 0);
}