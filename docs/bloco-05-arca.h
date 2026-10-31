
#ifndef ARCA_H
#define ARCA_H

#include <stdbool.h>

#define COMPRIMENTO_EXATO 300.0f
#define LARGURA_EXATA 50.0f
#define ALTURA_EXATA 30.0f

/* Cada etapa usa 10 toras e 1 balde de betume. */
#define TORAS_POR_ETAPA 10
#define TOTAL_ETAPAS_ARCA 20

typedef struct {
    int etapas_concluidas;
    float comprimento_construido;
    float largura_construida;
    float altura_construida;
    bool feita_de_gofer;
} Arca;

void inicializar_arca(Arca *obra);

/*
 * Conclui etapas completas usando 10 toras de gôfer e 1 balde de betume
 * por etapa. Materiais insuficientes permanecem no inventário.
 */
int adicionar_materiais_na_obra(
    Arca *obra,
    int *madeira_do_noe,
    int *betume_do_noe
);

bool julgar_diluvio(const Arca *obra);

#endif
