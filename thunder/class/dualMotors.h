#include "motor.h"

class DualMotor {
private:
  Motor motorEsquerdo;
  Motor motorDireito;

public:
  /**
   * @brief Construtor da classe DualMotor
   * @param motorEsqPin1: pino 1 do motor esquerdo
   * @param motorEsqPin2: pino 2 do motor esquerdo
   * @param motorDirPin1: pino 1 do motor direito
   * @param motorDirPin2: pino 2 do motor direito
   */
  DualMotor(byte motorEsqPin1, byte motorEsqPin2, byte motorDirPin1, byte motorDirPin2)
    : motorEsquerdo(motorEsqPin1, motorEsqPin2), motorDireito(motorDirPin1, motorDirPin2) {}

  /**
   * @brief Liga os dois motores no sentido horário
   */
  void on() {
    motorEsquerdo.on();
    motorDireito.on();
  }

  /**
   * @brief Desliga os dois motores
   */
  void off() {
    motorEsquerdo.off();
    motorDireito.off();
  }

  /**
   * @brief Controla a velocidade dos dois motores
   * @param moveEsq: velocidade do motor esquerdo
   * @param moveDir: velocidade do motor direito
   */
  void run(int moveEsq, int moveDir) {
    motorEsquerdo.run(moveEsq);
    motorDireito.run(moveDir);
  }

  void frente(int velocidade) {
    motorEsquerdo.run(velocidade);
    motorDireito.run(velocidade);
  }

  void reverso(int velocidade) {
    motorEsquerdo.run(-velocidade);
    motorDireito.run(-velocidade);
  }

  void curvaEsquerda(int velocidade) {
    motorEsquerdo.run(velocidade / 2);  // Reduzindo a velocidade para curva suave
    motorDireito.run(velocidade);
  }

  void curvaDireita(int velocidade) {
    motorEsquerdo.run(velocidade);
    motorDireito.run(velocidade / 2);  // Reduzindo a velocidade para curva suave
  }

  void girarEsquerdaTempo(int velocidade, int tempo) {
    motorEsquerdo.run(velocidade);
    motorDireito.run(-velocidade);
    delay(tempo);
  }

  void girarDireitaTempo(int velocidade, int tempo) {
    motorEsquerdo.run(-velocidade);
    motorDireito.run(velocidade);
    delay(tempo);
  }
};