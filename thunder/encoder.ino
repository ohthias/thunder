// Interrupção para contar os pulsos do encoder esquerdo
void contarPulsosEsquerdo() {
  contagemEncoderEsquerdo++;
}

// Interrupção para contar os pulsos do encoder direito
void contarPulsosDireito() {
  contagemEncoderDireito++;
}

// Inicializa os encoders
void iniciarEncoders() {
  attachInterrupt(digitalPinToInterrupt(PINO_ENCODER_ESQUERDO), contarPulsosEsquerdo, RISING);
  attachInterrupt(digitalPinToInterrupt(PINO_ENCODER_DIREITO), contarPulsosDireito, RISING);
}

// Reinicia a contagem dos encoders
void reiniciarEncoders() {
  contagemEncoderEsquerdo = 0;
  contagemEncoderDireito = 0;
}

// Retorna a média da contagem dos encoders para medir a distância percorrida
int lerEncoder() {
  return (contagemEncoderEsquerdo + contagemEncoderDireito) / 2;
}
