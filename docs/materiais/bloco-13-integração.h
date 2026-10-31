
#ifndef INTEGRACAO_H
#define INTEGRACAO_H

#include <stdbool.h>

#include "jogador.h"
#include "gigante.h"
#include "materiais.h"
#include "orientacao.h"

typedef struct {
    float x;
    float y;
    float alcance_coleta;

    Jogador *noe;
    Nefilim *gigante;
    Rota *rota;

    Material *materiais;
    int quantidade_materiais;

} EstadoJogo;

bool atualizar_coleta(
    EstadoJogo *estado
);

bool atualizar_orientacao(
    EstadoJogo *estado
);

#endif
