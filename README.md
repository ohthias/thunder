# Thunder

Projeto de um robô seguidor de linha desenvolvido em C++, utilizando controle PID e lógica de flags. Ideal para iniciativas de robótica, competições escolares ou ensino de algoritmos de controle.

## Techs

- Linguagem: C++
- Plataforma: Arduino (.ino + C++)
- Controle: PID
- Gerência de estado: uso de flags para o fluxo de operação

## Componentes

## 🧩 Componentes Utilizados

| **Componente**                      | **Descrição**                                                     | **Quantidade** |
|-------------------------------------|-------------------------------------------------------------------|----------------|
| **Arduino Mega**                    | Microcontrolador principal para processamento e controle         | 1              |
| **Sensor de Linha (IR Array)**      | Módulo com sensores infravermelhos para detecção da linha        | 1              |
| **LDR**                             | Sensor de luminosidade para detecção de contraste ou ambiente    | 2              |
| **Motores DC**                      | Motores responsáveis pela movimentação do robô                   | 2              |
| **Driver Ponte H (L298N ou L293D)** | Controle da velocidade e direção dos motores                     | 1              |
| **HC-SR04**                         | Sensor ultrassônico para medição de distância                    | 1              |
| **Bateria**                         | Fonte de alimentação (ex.: pack de 7.4V LiPo ou 9V)              | 1              |
| **Push Button**                     | Botão para entrada de comandos e controle                        | 3              |


## Instalação & Uso

1. Clone este repositório:

```bash
  git clone https://github.com/ohthias/thunder.git
  cd thunder/thunder
```
 
2. Abra o arquivo .ino no Arduino IDE.
3. Ajuste, se necessário, os parâmetros de PID e pinos.
4. Carregue o código na placa Arduino conectada ao robô.
5. Posicione o robô sobre uma pista com linha contrastante e execute.
