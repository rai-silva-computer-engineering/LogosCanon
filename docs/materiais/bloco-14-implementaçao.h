
#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include <stdbool.h>

#define ETAPAS_CONSTRUCAO 4

#define MADEIRA_FUNDACAO 100
#define MADEIRA_ESTRUTURA 200
#define MADEIRA_PAREDES 150
#define MADEIRA_COBERTURA 100

typedef enum {
    FUNDACAO,
    ESTRUTURA,
    PAREDES,
    COBERTURA,
    CONSTRUCAO_FINALIZADA
} EtapaConstrucao;

typedef struct {
    EtapaConstrucao etapa_atual;

    int madeira_utilizada;
    int madeira_necessaria;

    float progresso;

    bool fundacao_concluida;
    bool estrutura_concluida;
    bool paredes_concluidas;
    bool cobertura_concluida;

    bool construcao_finalizada;

} Construcao;

void inicializar_construcao(Construcao *obra);

bool construir_etapa(
    Construcao *obra,
    int *madeira_disponivel
);

float calcular_progresso_construcao(
    const Construcao *obra
);

bool verificar_construcao_finalizada(
    const Construcao *obra
);

#endif
