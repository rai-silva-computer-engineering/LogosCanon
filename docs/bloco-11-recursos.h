#ifndef RECURSOS_H
#define RECURSOS_H

#include <stdbool.h>
#include "jogador.h"

typedef enum {
    MADEIRA_GOFER,
    BETUME
} TipoRecurso;

bool coletar_recurso(
    Jogador *noe,
    TipoRecurso recurso,
    int quantidade
);

#endif
