
#include "construcao.h"

void inicializar_construcao(Construcao *obra) {

    if (obra == 0)
        return;

    obra->etapa_atual = FUNDACAO;

    obra->madeira_utilizada = 0;
    obra->madeira_necessaria =
        MADEIRA_FUNDACAO +
        MADEIRA_ESTRUTURA +
        MADEIRA_PAREDES +
        MADEIRA_COBERTURA;

    obra->progresso = 0.0f;

    obra->fundacao_concluida = false;
    obra->estrutura_concluida = false;
    obra->paredes_concluidas = false;
    obra->cobertura_concluida = false;

    obra->construcao_finalizada = false;
}

bool construir_etapa(
    Construcao *obra,
    int *madeira_disponivel
) {

    if (obra == 0 || madeira_disponivel == 0)
        return false;

    if (obra->construcao_finalizada)
        return true;

    if (*madeira_disponivel < 0)
        return false;

    int quantidade_necessaria = 0;

    switch (obra->etapa_atual) {

        case FUNDACAO:
            quantidade_necessaria = MADEIRA_FUNDACAO;
            break;

        case ESTRUTURA:
            quantidade_necessaria = MADEIRA_ESTRUTURA;
            break;

        case PAREDES:
            quantidade_necessaria = MADEIRA_PAREDES;
            break;

        case COBERTURA:
            quantidade_necessaria = MADEIRA_COBERTURA;
            break;

        default:
            return false;
    }

    if (*madeira_disponivel < quantidade_necessaria)
        return false;

    *madeira_disponivel -= quantidade_necessaria;

    obra->madeira_utilizada += quantidade_necessaria;

    switch (obra->etapa_atual) {

        case FUNDACAO:
            obra->fundacao_concluida = true;
            obra->etapa_atual = ESTRUTURA;
            break;

        case ESTRUTURA:
            obra->estrutura_concluida = true;
            obra->etapa_atual = PAREDES;
            break;

        case PAREDES:
            obra->paredes_concluidas = true;
            obra->etapa_atual = COBERTURA;
            break;

        case COBERTURA:
            obra->cobertura_concluida = true;
            obra->etapa_atual = CONSTRUCAO_FINALIZADA;
            obra->construcao_finalizada = true;
            break;

        default:
            return false;
    }

    obra->progresso =
        calcular_progresso_construcao(obra);

    return true;
}

float calcular_progresso_construcao(
    const Construcao *obra
) {

    if (obra == 0 ||
        obra->madeira_necessaria <= 0)
        return 0.0f;

    return
        ((float)obra->madeira_utilizada /
        obra->madeira_necessaria) * 100.0f;
}

bool verificar_construcao_finalizada(
    const Construcao *obra
) {

    if (obra == 0)
        return false;

    return
        obra->fundacao_concluida &&
        obra->estrutura_concluida &&
        obra->paredes_concluidas &&
        obra->cobertura_concluida &&
        obra->construcao_finalizada;
}
