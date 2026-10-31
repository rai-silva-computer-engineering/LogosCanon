#ifndef DILUVIO_H
#define DILUVIO_H

#include <stdbool.h>
#include "bloco-16-flutuabilidade.h"

typedef struct {
    float nivel_agua;
    float nivel_anterior;

    float velocidade_elevacao;
    float profundidade_agua;

    float tempo_decorrido;
    float duracao_diluvio;

    bool diluvio_ativo;
    bool nivel_maximo_atingido;
    bool arca_sobrevivendo;

} Diluvio;

void inicializar_diluvio(
    Diluvio *diluvio,
    float velocidade_elevacao,
    float duracao_diluvio
);

void iniciar_diluvio(Diluvio *diluvio);

void atualizar_diluvio(
    Diluvio *diluvio,
    float tempo,
    Flutuabilidade *flutuabilidade
);

bool verificar_nivel_maximo(
    Diluvio *diluvio
);

bool verificar_sobrevivencia(
    Diluvio *diluvio,
    const Flutuabilidade *flutuabilidade
);

#endif
