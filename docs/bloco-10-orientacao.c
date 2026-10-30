#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "bloco-08-orientacao.h"
#include "jogador.h"
#include "gigante.h"

bool mover_noe(
    Jogador *noe,
    Nefilim *gigante,
    float *noe_x,
    float *noe_y,
    float destino_x,
    float destino_y,
    float delta_tempo
) {
    if (!noe || !gigante || !noe_x || !noe_y ||
        !noe->vivo || delta_tempo <= 0.0f) {
        return false;
    }

    float dx = destino_x - *noe_x;
    float dy = destino_y - *noe_y;

    float distancia = calcular_distancia(
        *noe_x, *noe_y,
        destino_x, destino_y
    );

    if (distancia <= 0.01f)
        return true;

    float passo = noe->velocidade_atual * delta_tempo;

    if (passo > distancia)
        passo = distancia;

    *noe_x += (dx / distancia) * passo;
    *noe_y += (dy / distancia) * passo;

    atualizar_gigante(
        gigante,
        *noe_x,
        *noe_y,
        delta_tempo,
        &noe->vivo
    );

    return noe->vivo;
}
