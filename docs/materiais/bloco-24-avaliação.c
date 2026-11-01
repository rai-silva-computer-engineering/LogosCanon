#include "bloco-19-avaliacao.h"

void inicializar_avaliacao(AvaliacaoFase *avaliacao) {
    if (avaliacao == NULL) {
        return;
    }

    avaliacao->construcao_aprovada = false;
    avaliacao->impermeabilizacao_aprovada = false;
    avaliacao->flutuabilidade_aprovada = false;
    avaliacao->estabilidade_aprovada = false;
    avaliacao->sobrevivencia_aprovada = false;

    avaliacao->requisitos_concluidos = 0;
    avaliacao->percentual_conclusao = 0.0f;

    avaliacao->resultado = FASE_EM_ANDAMENTO;
}

void avaliar_construcao(
    AvaliacaoFase *avaliacao,
    const Construcao *construcao
) {
    if (avaliacao == NULL || construcao == NULL) {
        return;
    }

    avaliacao->construcao_aprovada =
        construcao->construcao_finalizada;
}

void avaliar_impermeabilizacao(
    AvaliacaoFase *avaliacao,
    const Impermeabilizacao *impermeabilizacao
) {
    if (avaliacao == NULL || impermeabilizacao == NULL) {
        return;
    }

    avaliacao->impermeabilizacao_aprovada =
        impermeabilizacao->impermeabilizacao_finalizada;
}

void avaliar_flutuabilidade(
    AvaliacaoFase *avaliacao,
    const Flutuabilidade *flutuabilidade
) {
    if (avaliacao == NULL || flutuabilidade == NULL) {
        return;
    }

    avaliacao->flutuabilidade_aprovada =
        flutuabilidade->flutuando &&
        !flutuabilidade->afundando;
}

void avaliar_estabilidade(
    AvaliacaoFase *avaliacao,
    const Estabilidade *estabilidade
) {
    if (avaliacao == NULL || estabilidade == NULL) {
        return;
    }

    avaliacao->estabilidade_aprovada =
        estabilidade->estavel &&
        !estabilidade->risco_tombamento;
}

void avaliar_sobrevivencia(
    AvaliacaoFase *avaliacao,
    const Diluvio *diluvio
) {
    if (avaliacao == NULL || diluvio == NULL) {
        return;
    }

    avaliacao->sobrevivencia_aprovada =
        diluvio->nivel_maximo_atingido &&
        diluvio->arca_sobrevivendo;
}

void atualizar_avaliacao(AvaliacaoFase *avaliacao) {
    if (avaliacao == NULL) {
        return;
    }

    avaliacao->requisitos_concluidos = 0;

    if (avaliacao->construcao_aprovada) {
        avaliacao->requisitos_concluidos++;
    }

    if (avaliacao->impermeabilizacao_aprovada) {
        avaliacao->requisitos_concluidos++;
    }

    if (avaliacao->flutuabilidade_aprovada) {
        avaliacao->requisitos_concluidos++;
    }

    if (avaliacao->estabilidade_aprovada) {
        avaliacao->requisitos_concluidos++;
    }

    if (avaliacao->sobrevivencia_aprovada) {
        avaliacao->requisitos_concluidos++;
    }

    avaliacao->percentual_conclusao =
        (avaliacao->requisitos_concluidos / 5.0f) * 100.0f;
}

ResultadoFase verificar_resultado_fase(
    AvaliacaoFase *avaliacao,
    const Diluvio *diluvio
) {
    if (avaliacao == NULL || diluvio == NULL) {
        return FASE_EM_ANDAMENTO;
    }

    atualizar_avaliacao(avaliacao);

    // Se o Dilúvio terminou e a Arca não sobreviveu,
    // o jogador perdeu a fase.
    if (
        diluvio->nivel_maximo_atingido &&
        !diluvio->arca_sobrevivendo
    ) {
        avaliacao->resultado = FASE_DERROTA;
        return avaliacao->resultado;
    }

    // A vitória exige todos os requisitos concluídos.
    if (
        avaliacao->construcao_aprovada &&
        avaliacao->impermeabilizacao_aprovada &&
        avaliacao->flutuabilidade_aprovada &&
        avaliacao->estabilidade_aprovada &&
        avaliacao->sobrevivencia_aprovada
    ) {
        avaliacao->resultado = FASE_VITORIA;
        return avaliacao->resultado;
    }

    avaliacao->resultado = FASE_EM_ANDAMENTO;

    return avaliacao->resultado;
}
