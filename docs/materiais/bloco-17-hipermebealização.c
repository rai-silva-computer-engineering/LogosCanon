
#include "bloco-15-impermeabilizacao.h"

void inicializar_impermeabilizacao(
    Impermeabilizacao *impermeabilizacao
) {
    if (impermeabilizacao == NULL) {
        return;
    }

    impermeabilizacao->betume_interno_aplicado = 0;
    impermeabilizacao->betume_externo_aplicado = 0;

    impermeabilizacao->betume_total_necessario =
        BETUME_INTERNO_NECESSARIO +
        BETUME_EXTERNO_NECESSARIO;

    impermeabilizacao->betume_total_aplicado = 0;

    impermeabilizacao->progresso = 0.0f;

    impermeabilizacao->parte_interna_finalizada = false;
    impermeabilizacao->parte_externa_finalizada = false;
    impermeabilizacao->impermeabilizacao_finalizada = false;
}

int aplicar_betume(
    Impermeabilizacao *impermeabilizacao,
    Material *betume,
    const Construcao *construcao,
    int quantidade
) {
    if (
        impermeabilizacao == NULL ||
        betume == NULL ||
        construcao == NULL ||
        quantidade <= 0
    ) {
        return 0;
    }

    // A impermeabilização exige a construção completa.
    if (!construcao->construcao_finalizada) {
        return 0;
    }

    // Verifica se o material é betume e está disponível.
    if (
        betume->tipo != MATERIAL_BETUME ||
        !betume->disponivel ||
        betume->quantidade <= 0
    ) {
        return 0;
    }

    int quantidade_aplicavel = quantidade;

    // Não permite utilizar mais betume do que o disponível.
    if (quantidade_aplicavel > betume->quantidade) {
        quantidade_aplicavel = betume->quantidade;
    }

    int restante_interno =
        BETUME_INTERNO_NECESSARIO -
        impermeabilizacao->betume_interno_aplicado;

    int restante_externo =
        BETUME_EXTERNO_NECESSARIO -
        impermeabilizacao->betume_externo_aplicado;

    int aplicado = 0;

    // Primeiro impermeabiliza a parte interna.
    if (restante_interno > 0) {
        int usar = quantidade_aplicavel;

        if (usar > restante_interno) {
            usar = restante_interno;
        }

        impermeabilizacao->betume_interno_aplicado += usar;
        quantidade_aplicavel -= usar;
        aplicado += usar;
    }

    // Depois impermeabiliza a parte externa.
    if (quantidade_aplicavel > 0 && restante_externo > 0) {
        int usar = quantidade_aplicavel;

        if (usar > restante_externo) {
            usar = restante_externo;
        }

        impermeabilizacao->betume_externo_aplicado += usar;
        aplicado += usar;
    }

    // Atualiza o estoque de betume.
    betume->quantidade -= aplicado;

    if (betume->quantidade <= 0) {
        betume->quantidade = 0;
        betume->disponivel = false;
    }

    impermeabilizacao->betume_total_aplicado += aplicado;

    impermeabilizacao->parte_interna_finalizada =
        impermeabilizacao->betume_interno_aplicado >=
        BETUME_INTERNO_NECESSARIO;

    impermeabilizacao->parte_externa_finalizada =
        impermeabilizacao->betume_externo_aplicado >=
        BETUME_EXTERNO_NECESSARIO;

    impermeabilizacao->progresso =
        calcular_progresso_impermeabilizacao(impermeabilizacao);

    verificar_impermeabilizacao_finalizada(impermeabilizacao);

    return aplicado;
}

float calcular_progresso_impermeabilizacao(
    const Impermeabilizacao *impermeabilizacao
) {
    if (impermeabilizacao == NULL) {
        return 0.0f;
    }

    if (impermeabilizacao->betume_total_necessario <= 0) {
        return 0.0f;
    }

    return (
        (float)impermeabilizacao->betume_total_aplicado /
        impermeabilizacao->betume_total_necessario
    ) * 100.0f;
}

bool verificar_impermeabilizacao_finalizada(
    Impermeabilizacao *impermeabilizacao
) {
    if (impermeabilizacao == NULL) {
        return false;
    }

    impermeabilizacao->impermeabilizacao_finalizada =
        impermeabilizacao->parte_interna_finalizada &&
        impermeabilizacao->parte_externa_finalizada;

    return impermeabilizacao->impermeabilizacao_finalizada;
}
