
#include <stdbool.h>
#include <math.h>
#include "orientacao.h"

bool inicializar_rota(
    Rota *rota,
    const Ponto *pontos,
    int quantidade,
    float tolerancia
) {
    if (rota == NULL || pontos == NULL ||
        quantidade <= 0 ||
        quantidade > MAX_PONTOS_ROTA ||
        tolerancia <= 0.0f) {
        return false;
    }

    for (int i = 0; i < quantidade; i++) {
        rota->pontos[i] = pontos[i];
    }

    rota->quantidade = quantidade;
    rota->trecho_atual = 0;
    rota->tolerancia = tolerancia;
    rota->concluida = false;

    return true;
}

bool validar_posicao_rota(
    Rota *rota,
    float x,
    float y,
    bool *noe_vivo
) {
    if (rota == NULL || noe_vivo == NULL ||
        !*noe_vivo ||
        rota->quantidade <= 0 ||
        rota->quantidade > MAX_PONTOS_ROTA ||
        rota->trecho_atual < 0 ||
        rota->trecho_atual >= rota->quantidade ||
        rota->tolerancia <= 0.0f) {
        return false;
    }

    if (rota->concluida) {
        return true;
    }

    Ponto alvo = rota->pontos[rota->trecho_atual];

    float dx = alvo.x - x;
    float dy = alvo.y - y;

    float distancia = sqrtf(dx * dx + dy * dy);

    if (distancia <= rota->tolerancia) {
        rota->trecho_atual++;

        if (rota->trecho_atual >= rota->quantidade) {
            rota->concluida = true;
        }
    }

    return rota->concluida;
}
