#include <math.h>
#include "gigante.h"

float calcular_distancia(
    float x1, float y1,
    float x2, float y2
) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    return sqrtf(dx * dx + dy * dy);
}

void atualizar_gigante(
    Nefilim *gigante,
    float noe_x,
    float noe_y,
    float delta_tempo,
    bool *noe_vivo
) {
    float dx = noe_x - gigante->pos_x;
    float dy = noe_y - gigante->pos_y;
    float distancia = calcular_distancia(
        gigante->pos_x, gigante->pos_y,
        noe_x, noe_y
    );

    if (distancia > RAIO_DE_VISAO &&
        !gigante->perseguindo_jogador) {
        return;
    }

    gigante->perseguindo_jogador = true;

    if (distancia <= DISTANCIA_DE_ATAQUE) {
        *noe_vivo = false;
        return;
    }

    if (distancia > 0.0f) {
        float movimento = VELOCIDADE_GIGANTE * delta_tempo;

        if (movimento > distancia) {
            movimento = distancia;
        }

        gigante->pos_x += (dx / distancia) * movimento;
        gigante->pos_y += (dy / distancia) * movimento;
    }

    distancia = calcular_distancia(
        gigante->pos_x, gigante->pos_y,
        noe_x, noe_y
    );

    if (distancia <= DISTANCIA_DE_ATAQUE) {
        *noe_vivo = false;
    }
}
