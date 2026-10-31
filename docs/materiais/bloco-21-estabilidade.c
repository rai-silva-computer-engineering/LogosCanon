
#include "bloco-17-estabilidade.h"
#include <math.h>

void inicializar_estabilidade(
    Estabilidade *estabilidade,
    float massa_arca
) {
    if (estabilidade == NULL || massa_arca <= 0.0f) {
        return;
    }

    estabilidade->massa_arca = massa_arca;

    estabilidade->centro_massa_x = 0.0f;
    estabilidade->centro_massa_y = 0.0f;
    estabilidade->centro_massa_z = 0.0f;

    estabilidade->momento_x = 0.0f;
    estabilidade->momento_y = 0.0f;
    estabilidade->momento_z = 0.0f;

    estabilidade->massa_total = massa_arca;

    estabilidade->deslocamento_x = 0.0f;
    estabilidade->deslocamento_y = 0.0f;

    estabilidade->angulo_inclinacao = 0.0f;

    estabilidade->estavel = true;
    estabilidade->risco_tombamento = false;
}

bool adicionar_carga_estabilidade(
    Estabilidade *estabilidade,
    const CargaEstabilidade *carga
) {
    if (
        estabilidade == NULL ||
        carga == NULL ||
        carga->massa <= 0.0f
    ) {
        return false;
    }

    estabilidade->momento_x +=
        carga->massa * carga->posicao_x;

    estabilidade->momento_y +=
        carga->massa * carga->posicao_y;

    estabilidade->momento_z +=
        carga->massa * carga->posicao_z;

    estabilidade->massa_total += carga->massa;

    calcular_centro_massa(estabilidade);

    return true;
}

void calcular_centro_massa(
    Estabilidade *estabilidade
) {
    if (
        estabilidade == NULL ||
        estabilidade->massa_total <= 0.0f
    ) {
        return;
    }

    estabilidade->centro_massa_x =
        estabilidade->momento_x /
        estabilidade->massa_total;

    estabilidade->centro_massa_y =
        estabilidade->momento_y /
        estabilidade->massa_total;

    estabilidade->centro_massa_z =
        estabilidade->momento_z /
        estabilidade->massa_total;
}

void atualizar_estabilidade(
    Estabilidade *estabilidade,
    float limite_deslocamento
) {
    if (
        estabilidade == NULL ||
        limite_deslocamento <= 0.0f
    ) {
        return;
    }

    estabilidade->deslocamento_x =
        estabilidade->centro_massa_x;

    estabilidade->deslocamento_y =
        estabilidade->centro_massa_y;

    float deslocamento =
        sqrtf(
            estabilidade->deslocamento_x *
            estabilidade->deslocamento_x +
            estabilidade->deslocamento_y *
            estabilidade->deslocamento_y
        );

    estabilidade->angulo_inclinacao =
        atan2f(
            estabilidade->deslocamento_y,
            estabilidade->deslocamento_x
        ) * (180.0f / 3.14159265f);

    estabilidade->risco_tombamento =
        deslocamento >= limite_deslocamento;

    estabilidade->estavel =
        !estabilidade->risco_tombamento;
}
