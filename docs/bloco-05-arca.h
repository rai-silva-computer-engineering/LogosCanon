#ifndef ARCA_H
#define ARCA_H

#include <stdbool.h>

#define COMPRIMENTO_EXATO 300.0f
#define LARGURA_EXATA 50.0f
#define ALTURA_EXATA 30.0f

typedef struct {
    float comprimento_construido;
    float largura_construida;
    float altura_construida;
    bool betume_aplicado;
    bool feita_de_gofer;
} Arca;

void inicializar_arca(Arca *obra);

void adicionar_materiais_na_obra(
    Arca *obra,
    int *madeira_do_noe,
    int *betume_do_noe
);

bool julgar_diluvio(Arca obra);

#endif
