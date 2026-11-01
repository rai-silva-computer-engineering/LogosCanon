#ifndef INTEGRACAO_FASE_ARCA_H
#define INTEGRACAO_FASE_ARCA_H

#include <stdbool.h>

#include "bloco-14-construcao.h"
#include "bloco-15-impermeabilizacao.h"
#include "bloco-16-flutuabilidade.h"
#include "bloco-17-estabilidade.h"
#include "bloco-18-diluvio.h"
#include "bloco-19-avaliacao.h"

typedef struct {
    Construcao construcao;
    Impermeabilizacao impermeabilizacao;
    Flutuabilidade flutuabilidade;
    Estabilidade estabilidade;
    Diluvio diluvio;
    AvaliacaoFase avaliacao;

    Material betume;

    bool inicializado;

} EstadoFaseArca;

void inicializar_fase_arca(
    EstadoFaseArca *estado,
    float comprimento,
    float largura,
    float altura,
    float massa_arca,
    float velocidade_agua,
    float duracao_diluvio,
    int quantidade_betume
);

int integracao_aplicar_betume(
    EstadoFaseArca *estado,
    int quantidade
);

void integracao_iniciar_diluvio(
    EstadoFaseArca *estado
);

ResultadoFase integracao_atualizar(
    EstadoFaseArca *estado,
    float tempo,
    float limite_deslocamento
);

#endif
