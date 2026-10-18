#ifndef JOGADOR_H
#define JOGADOR_H

#include <stdbool.h>

// Estrutura do jogador e declaração da função
typedef struct {
    int qtd_madeira;
    int qtd_betume;
    float peso_total;
    float velocidade_atual;
    bool vivo;
} Jogador;

void calcular_peso_e_velocidade(Jogador *noe);

#endif // JOGADOR_H
  
