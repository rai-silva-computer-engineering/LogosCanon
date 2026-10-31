
#ifndef IMPERMEABILIZACAO_H
#define IMPERMEABILIZACAO_H

#include <stdbool.h>
#include "materiais.h"
#include "bloco-14-construcao.h"

#define BETUME_INTERNO_NECESSARIO 100
#define BETUME_EXTERNO_NECESSARIO 100

typedef struct {
    int betume_interno_aplicado;
    int betume_externo_aplicado;

    int betume_total_necessario;
    int betume_total_aplicado;

    float progresso;

    bool parte_interna_finalizada;
    bool parte_externa_finalizada;
    bool impermeabilizacao_finalizada;

} Impermeabilizacao;

void inicializar_impermeabilizacao(Impermeabilizacao *impermeabilizacao);

int aplicar_betume(
    Impermeabilizacao *impermeabilizacao,
    Material *betume,
    const Construcao *construcao,
    int quantidade
);

float calcular_progresso_impermeabilizacao(
    const Impermeabilizacao *impermeabilizacao
);

bool verificar_impermeabilizacao_finalizada(
    Impermeabilizacao *impermeabilizacao
);

#endif
