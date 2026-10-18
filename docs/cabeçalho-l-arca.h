#ifndef ARCA_H
#define ARCA_H

#include <stdbool.h>

typedef struct {
    float comprimento_construido;
    float largura_construida;
    float altura_construida;
    bool betume_aplicado;
    bool feita_de_gofer;
} Arca;

// Funções de construção e julgamento da arca
void adicionar_materiais_na_obra(
    Arca *obra,
    int *madeira_do_noe,
    int *betume_do_noe
);

bool julgar_diluvio(Arca obra);

#endif // ARCA_H
