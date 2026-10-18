#include "jogador.h"

void calcular_peso_e_velocidade(Jogador *noe) {
    noe->peso_total =
        noe->qtd_madeira * PESO_MADEIRA_GOFER +
        noe->qtd_betume * PESO_BALDE_BETUME;

    if (noe->peso_total > CAPACIDADE_MAXIMA) {
        noe->velocidade_atual = VELOCIDADE_BASE * 0.2f;
    } else {
        noe->velocidade_atual =
            VELOCIDADE_BASE - noe->peso_total * 0.1f;
    }

    if (noe->velocidade_atual < 0.0f) {
        noe->velocidade_atual = 0.0f;
    }
}
