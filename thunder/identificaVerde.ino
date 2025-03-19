/**
 * Função identificaVerde
 * 
 * Esta função é responsável por identificar a presença de uma cor verde utilizando sensores LDR.
 * Ela lê os valores dos sensores LDR e define a flag correspondente à situação detectada.
 * 
 * Lógica:
 * - Se ambos os sensores LDR detectarem verde, a flag é definida como Flags_verde::beco.
 * - Se apenas o sensor LDR da direita detectar verde, a flag é definida como Flags_verde::curvaDireita.
 * - Se apenas o sensor LDR da esquerda detectar verde, a flag é definida como Flags_verde::curvaEsquerda.
 * - Caso contrário, a flag é definida como Flags_verde::nenhum.
 * 
 * Sensores utilizados:
 * - LDR_esquerda
 * - LDR_direita
 * 
 * Variáveis globais utilizadas:
 * - verde: valor de referência para a cor verde
 * - flags: variável que armazena a flag correspondente à situação detectada
 * 
 * A função também utiliza a função delay para criar uma pausa no código.
 */
 
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