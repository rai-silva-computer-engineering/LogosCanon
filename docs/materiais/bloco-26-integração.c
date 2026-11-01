#include "bloco-20-integracao.h"

void inicializar_fase_arca(
    EstadoFaseArca *estado,
    float comprimento,
    float largura,
    float altura,
    float massa_arca,
    float velocidade_agua,
    float duracao_diluvio,
    int quantidade_betume
) {
    if (
        estado == NULL ||
        comprimento <= 0.0f ||
        largura <= 0.0f ||
        altura <= 0.0f ||
        massa_arca <= 0.0f ||
        velocidade_agua <= 0.0f ||
        duracao_diluvio <= 0.0f ||
        quantidade_betume < 0
    ) {
        return;
    }

    inicializar_construcao(&estado->construcao);

    inicializar_impermeabilizacao(
        &estado->impermeabilizacao
    );

    inicializar_flutuabilidade(
        &estado->flutuabilidade,
        comprimento,
        largura,
        altura,
        massa_arca
    );

    inicializar_estabilidade(
        &estado->estabilidade,
        massa_arca
    );

    inicializar_diluvio(
        &estado->diluvio,
        velocidade_agua,
        duracao_diluvio
    );

    inicializar_avaliacao(
        &estado->avaliacao
    );

    estado->betume.x = 0.0f;
    estado->betume.y = 0.0f;
    estado->betume.tipo = MATERIAL_BETUME;
    estado->betume.quantidade = quantidade_betume;
    estado->betume.disponivel = quantidade_betume > 0;

    estado->inicializado = true;
}

int integracao_aplicar_betume(
    EstadoFaseArca *estado,
    int quantidade
) {
    if (
        estado == NULL ||
        !estado->inicializado
    ) {
        return 0;
    }

    return aplicar_betume(
        &estado->impermeabilizacao,
        &estado->betume,
        &estado->construcao,
        quantidade
    );
}

void integracao_iniciar_diluvio(
    EstadoFaseArca *estado
) {
    if (
        estado == NULL ||
        !estado->inicializado
    ) {
        return;
    }

    iniciar_diluvio(&estado->diluvio);
}

ResultadoFase integracao_atualizar(
    EstadoFaseArca *estado,
    float tempo,
    float limite_deslocamento
) {
    if (
        estado == NULL ||
        !estado->inicializado ||
        tempo <= 0.0f ||
        limite_deslocamento <= 0.0f
    ) {
        return FASE_EM_ANDAMENTO;
    }

    // Atualiza a estabilidade da embarcação.
    atualizar_estabilidade(
        &estado->estabilidade,
        limite_deslocamento
    );

    // Atualiza o nível da água e a flutuabilidade.
    atualizar_diluvio(
        &estado->diluvio,
        tempo,
        &estado->flutuabilidade
    );

    // Reúne os resultados dos módulos.
    avaliar_construcao(
        &estado->avaliacao,
        &estado->construcao
    );

    avaliar_impermeabilizacao(
        &estado->avaliacao,
        &estado->impermeabilizacao
    );

    avaliar_flutuabilidade(
        &estado->avaliacao,
        &estado->flutuabilidade
    );

    avaliar_estabilidade(
        &estado->avaliacao,
        &estado->estabilidade
    );

    avaliar_sobrevivencia(
        &estado->avaliacao,
        &estado->diluvio
    );

    atualizar_avaliacao(&estado->avaliacao);

    // Determina o resultado da fase.
    return verificar_resultado_fase(
        &estado->avaliacao,
        &estado->diluvio
    );
}
