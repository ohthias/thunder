// Sensores
#define LDR_esquerda A0
#define LDR_direita A1

enum class Flags_verde {
  curvaDireita,
  curvaEsquerda,
  beco,
  nenhum
};

Flags_verde flags = Flags_verde::nenhum;

//Calibração
int verde = 50;

void setup() {
  Serial.begin(9600);
}

void loop() {
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

  //Flags de curva
  switch(flags) {
    case Flags_verde::curvaDireita:
      Serial.println("Curva para a direita detectada");
      break;

    case Flags_verde::curvaEsquerda:
      Serial.println("Curva para a esquerda detectada");
      break;

    case Flags_verde::beco:
      Serial.println("Beco detectado");
      break;

    case Flags_verde::nenhum:
      Serial.println("Nenhuma curva ou beco detectado");
      break;
  }
  delay(100);
}