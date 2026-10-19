|[&larr; Voltar](./bloco-01-jogador.h)  | [avançar &rarr;](./bloco-02-jogador.c)|
|:---------|------------:|


#ifndef JOGADOR_H
#define JOGADOR_H

#include <stdbool.h>

#define PESO_MADEIRA_GOFER 5.0f
#define PESO_BALDE_BETUME 2.0f
#define CAPACIDADE_MAXIMA 50.0f
#define VELOCIDADE_BASE 10.0f

typedef struct {
    int qtd_madeira;
    int qtd_betume;
    float peso_total;
    float velocidade_atual;
    bool vivo;
} Jogador;

void calcular_peso_e_velocidade(Jogador *noe);

#endif



|[&larr; Voltar](./bloco-01-jogador.h)  | [avançar &rarr;](./bloco-02-jogador.c)|
|:---------|------------:
