#ifndef GIGANTE_H
#define GIGANTE_H

#include <stdbool.h>

typedef struct {
    float pos_x;
    float pos_y;
    bool perseguindo_jogador;
} Nefilim;

// Funções de distância e perseguição
float calcular_distancia(float x1, float y1, float x2, float y2);

void atualizar_gigante(
    Nefilim *gigante,
    float noe_x,
    float noe_y,
    float velocidade_noe,
    bool *noe_vivo
);

#endif // GIGANTE_H
