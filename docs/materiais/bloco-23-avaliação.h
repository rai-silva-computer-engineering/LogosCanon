#ifndef AVALIACAO_H
#define AVALIACAO_H

#include <stdbool.h>

#include "bloco-14-construcao.h"
#include "bloco-15-impermeabilizacao.h"
#include "bloco-16-flutuabilidade.h"
#include "bloco-17-estabilidade.h"
#include "bloco-18-diluvio.h"

typedef enum {
    FASE_EM_ANDAMENTO,
    FASE_VITORIA,
    FASE_DERROTA
} ResultadoFase;

typedef struct {
    bool construcao_aprovada;
    bool impermeabilizacao_aprovada;
    bool flutuabilidade_aprovada;
    bool estabilidade_aprovada;
    bool sobrevivencia_aprovada;

    int requisitos_concluidos;
    float percentual_conclusao;

    ResultadoFase resultado;

} AvaliacaoFase;

void inicializar_avaliacao(AvaliacaoFase *avaliacao);

void avaliar_construcao(
    AvaliacaoFase *avaliacao,
    const Construcao *construcao
);

void avaliar_impermeabilizacao(
    AvaliacaoFase *avaliacao,
    const Impermeabilizacao *impermeabilizacao
);

void avaliar_flutuabilidade(
    AvaliacaoFase *avaliacao,
    const Flutuabilidade *flutuabilidade
);

void avaliar_estabilidade(
    AvaliacaoFase *avaliacao,
    const Estabilidade *estabilidade
);

void avaliar_sobrevivencia(
    AvaliacaoFase *avaliacao,
    const Diluvio *diluvio
);

void atualizar_avaliacao(AvaliacaoFase *avaliacao);

ResultadoFase verificar_resultado_fase(
    AvaliacaoFase *avaliacao,
    const Diluvio *diluvio
);

#endif
