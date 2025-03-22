/**
 * Função para calibrar leituras de sensores para superfícies pretas e verdes.
 * Ela lê os valores dos sensores quando botões específicos são pressionados, ordena os valores,
 * e calcula a média dos 25% menores leituras.
 */
 void calibragem() {
    const int tamanho = 100; // Quantidade de leituras armazenadas
    unsigned int valoresPreto[tamanho];
    unsigned int valoresVerde[tamanho];
    int index = 0;

    if (digitalRead(button_left) == HIGH) {
        unsigned long tempoInicial = millis();
        while (millis() - tempoInicial < 1500 && index < tamanho) {
            valoresPreto[index++] = analogRead(SENSOR_EXTREMO_ESQUERDO);
            valoresPreto[index++] = analogRead(SENSOR_ESQUERDO);
            valoresPreto[index++] = analogRead(SENSOR_CENTRO);
            valoresPreto[index++] = analogRead(SENSOR_DIREITO);
            valoresPreto[index++] = analogRead(SENSOR_EXTREMO_DIREITO);
        }

        ordenar(valoresPreto, index);  // Ordena os valores do menor para o maior
        float mediaPreto = calcularMediaMenores(valoresPreto, index);

        Serial.println("Média dos menores valores pretos: ");
        Serial.println(mediaPreto);
    } 
    
    else if (digitalRead(button_right) == HIGH) {
        index = 0;
        unsigned long tempoInicial = millis();
        while (millis() - tempoInicial < 1500 && index < tamanho) {
            valoresVerde[index++] = analogRead(LDR_esquerda);
            valoresVerde[index++] = analogRead(LDR_direita);
        }

        ordenar(valoresVerde, index);  // Ordena os valores do menor para o maior
        float mediaVerde = calcularMediaMenores(valoresVerde, index);

        Serial.println("Média dos menores valores verdes: ");
        Serial.println(mediaVerde);
    }

    delay(5000);
}

/**
 * Ordena um array de inteiros sem sinal em ordem crescente usando o algoritmo Bubble Sort.
 * 
 * @param array O array a ser ordenado.
 * @param tamanho O número de elementos no array.
 */
// Função para ordenar os valores (Bubble Sort)
void ordenar(unsigned int array[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // Troca os valores
                unsigned int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

/**
 * Calcula a média dos 25% menores valores em um array.
 * 
 * @param array O array contendo os valores.
 * @param tamanho O número de elementos no array.
 * @return A média dos 25% menores valores.
 */
float calcularMediaMenores(unsigned int array[], int tamanho) {
    int qtdMenores = tamanho / 4;  // Seleciona os 25% menores valores
    float soma = 0;
    for (int i = 0; i < qtdMenores; i++) {
        soma += array[i];
    }
    return soma / qtdMenores;
}