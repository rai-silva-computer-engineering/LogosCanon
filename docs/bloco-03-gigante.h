#ifndef GIGANTE_H
#define GIGANTE_H

#include <stdbool.h>

#define RAIO_DE_VISAO 15.0f
#define VELOCIDADE_GIGANTE 6.0f
#define DISTANCIA_DE_ATAQUE 1.5f

typedef struct {
    float pos_x;
    float pos_y;
    bool perseguindo_jogador;
} Nefilim;

float calcular_distancia(
    float x1, float y1,
    float x2, float y2
);

void atualizar_gigante(
    Nefilim *gigante,
    float noe_x,
    float noe_y,
    float delta_tempo,
    bool *noe_vivo
);

#endif
