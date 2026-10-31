
#ifndef FLUTUABILIDADE_H
#define FLUTUABILIDADE_H

#include <stdbool.h>

#define GRAVIDADE 9.81f
#define DENSIDADE_AGUA 1000.0f

typedef struct {
    float comprimento;
    float largura;
    float altura;

    float volume_submerso;
    float volume_maximo;

    float massa_arca;
    float massa_carga;

    float empuxo;
    float peso_total;

    float percentual_submerso;

    bool flutuando;
    bool afundando;

} Flutuabilidade;

void inicializar_flutuabilidade(
    Flutuabilidade *flutuabilidade,
    float comprimento,
    float largura,
    float altura,
    float massa_arca
);

void atualizar_peso_total(
    Flutuabilidade *flutuabilidade,
    float massa_carga
);

float calcular_empuxo(
    const Flutuabilidade *flutuabilidade
);

float calcular_peso(
    const Flutuabilidade *flutuabilidade
);

void atualizar_flutuabilidade(
    Flutuabilidade *flutuabilidade,
    float profundidade_submersa
);

#endif
