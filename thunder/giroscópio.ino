/**
 * Lê o ângulo do eixo Z do sensor giroscópio.
 * 
 * @return O ângulo do eixo Z como um inteiro.
 */
int angleZ() {
  return (int)gyro.readFloatZ();
}

/**
 * Lê o ângulo do eixo Y do sensor giroscópio.
 * 
 * @return O ângulo do eixo Y como um inteiro.
 */
int angleY() {
  return (int)gyro.readFloatY();
}

/**
 * Imprime os ângulos dos eixos Z e Y no monitor Serial.
 * O formato de saída é "Z: <angleZ> Y: <angleY>".
 */
void printAngle() {
  Serial.print("Z: ");
  Serial.print(angleZ());
  Serial.print(" Y: ");
  Serial.println(angleY());
}