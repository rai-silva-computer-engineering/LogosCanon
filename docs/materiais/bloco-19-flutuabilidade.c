
#include "bloco-16-flutuabilidade.h"

void inicializar_flutuabilidade(
    Flutuabilidade *flutuabilidade,
    float comprimento,
    float largura,
    float altura,
    float massa_arca
) {
    if (flutuabilidade == NULL) {
        return;
    }

    flutuabilidade->comprimento = comprimento;
    flutuabilidade->largura = largura;
    flutuabilidade->altura = altura;

    flutuabilidade->volume_maximo =
        comprimento * largura * altura;

    flutuabilidade->volume_submerso = 0.0f;

    flutuabilidade->massa_arca = massa_arca;
    flutuabilidade->massa_carga = 0.0f;

    flutuabilidade->empuxo = 0.0f;
    flutuabilidade->peso_total = massa_arca * GRAVIDADE;

    flutuabilidade->percentual_submerso = 0.0f;

    flutuabilidade->flutuando = false;
    flutuabilidade->afundando = false;
}

void atualizar_peso_total(
    Flutuabilidade *flutuabilidade,
    float massa_carga
) {
    if (flutuabilidade == NULL || massa_carga < 0.0f) {
        return;
    }

    flutuabilidade->massa_carga = massa_carga;

    flutuabilidade->peso_total =
        (flutuabilidade->massa_arca +
         flutuabilidade->massa_carga) * GRAVIDADE;
}

float calcular_empuxo(
    const Flutuabilidade *flutuabilidade
) {
    if (flutuabilidade == NULL) {
        return 0.0f;
    }

    return DENSIDADE_AGUA *
           GRAVIDADE *
           flutuabilidade->volume_submerso;
}

float calcular_peso(
    const Flutuabilidade *flutuabilidade
) {
    if (flutuabilidade == NULL) {
        return 0.0f;
    }

    return (
        flutuabilidade->massa_arca +
        flutuabilidade->massa_carga
    ) * GRAVIDADE;
}

void atualizar_flutuabilidade(
    Flutuabilidade *flutuabilidade,
    float profundidade_submersa
) {
    if (
        flutuabilidade == NULL ||
        profundidade_submersa < 0.0f
    ) {
        return;
    }

    if (profundidade_submersa > flutuabilidade->altura) {
        profundidade_submersa = flutuabilidade->altura;
    }

    flutuabilidade->volume_submerso =
        flutuabilidade->comprimento *
        flutuabilidade->largura *
        profundidade_submersa;

    flutuabilidade->empuxo =
        calcular_empuxo(flutuabilidade);

    flutuabilidade->peso_total =
        calcular_peso(flutuabilidade);

    flutuabilidade->percentual_submerso =
        (profundidade_submersa /
         flutuabilidade->altura) * 100.0f;

    flutuabilidade->flutuando =
        flutuabilidade->empuxo >=
        flutuabilidade->peso_total;

    flutuabilidade->afundando =
        flutuabilidade->empuxo <
        flutuabilidade->peso_total;
}
