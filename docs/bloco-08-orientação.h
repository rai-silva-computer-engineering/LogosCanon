
Esse bloco define o caminho que Noé precisa seguir para buscar os materiais nas terras de 
goffer;


#ifndef ORIENTACAO_H
#define ORIENTACAO_H

#include <stdbool.h>

#define MAX_PONTOS_ROTA 20

typedef struct {
    float x;
    float y;
} Ponto;

typedef struct {
    Ponto pontos[MAX_PONTOS_ROTA];
    int quantidade;
    int trecho_atual;
    float tolerancia;
    bool concluida;
} Rota;

bool inicializar_rota(
    Rota *rota,
    const Ponto *pontos,
    int quantidade,
    float tolerancia
);

bool validar_posicao_rota(
    Rota *rota,
    float x,
    float y,
    bool *noe_vivo
);

#endif
