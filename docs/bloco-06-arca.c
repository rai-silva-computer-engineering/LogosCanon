#include <stdio.h>
#include <math.h>
#include "arca.h"

#define COMPRIMENTO_POR_TORA 1.5f
#define LARGURA_POR_TORA 0.25f
#define ALTURA_POR_TORA 0.15f
#define TOLERANCIA 0.001f

void inicializar_arca(Arca *obra) {
    obra->comprimento_construido = 0.0f;
    obra->largura_construida = 0.0f;
    obra->altura_construida = 0.0f;
    obra->betume_aplicado = false;
    obra->feita_de_gofer = false;
}

void adicionar_materiais_na_obra(
    Arca *obra,
    int *madeira_do_noe,
    int *betume_do_noe
) {
    int toras;
    int usadas = 0;

    if (*madeira_do_noe > 0) {
        toras = *madeira_do_noe;

        while (usadas < toras &&
               obra->comprimento_construido < COMPRIMENTO_EXATO &&
               obra->largura_construida < LARGURA_EXATA &&
               obra->altura_construida < ALTURA_EXATA) {

            obra->comprimento_construido += COMPRIMENTO_POR_TORA;
            obra->largura_construida += LARGURA_POR_TORA;
            obra->altura_construida += ALTURA_POR_TORA;

            if (obra->comprimento_construido > COMPRIMENTO_EXATO)
                obra->comprimento_construido = COMPRIMENTO_EXATO;

            if (obra->largura_construida > LARGURA_EXATA)
                obra->largura_construida = LARGURA_EXATA;

            if (obra->altura_construida > ALTURA_EXATA)
                obra->altura_construida = ALTURA_EXATA;

            usadas++;
        }

        *madeira_do_noe -= usadas;

        if (usadas > 0) {
            obra->feita_de_gofer = true;
        }
    }

    if (*betume_do_noe > 0) {
        obra->betume_aplicado = true;
        *betume_do_noe = 0;
    }
}

bool julgar_diluvio(Arca obra) {
    printf("\n[ O TEMPO ACABOU. O DILUVIO COMEÇOU ]\n");

    if (fabsf(obra.comprimento_construido - COMPRIMENTO_EXATO)
            > TOLERANCIA ||
        fabsf(obra.largura_construida - LARGURA_EXATA)
            > TOLERANCIA ||
        fabsf(obra.altura_construida - ALTURA_EXATA)
            > TOLERANCIA) {

        printf("FALHA: as medidas da arca estao incompletas.\n");
        printf("Comprimento: %.1f / %.1f\n",
               obra.comprimento_construido, COMPRIMENTO_EXATO);
        printf("Largura: %.1f / %.1f\n",
               obra.largura_construida, LARGURA_EXATA);
        printf("Altura: %.1f / %.1f\n",
               obra.altura_construida, ALTURA_EXATA);

        return false;
    }

    if (!obra.feita_de_gofer) {
        printf("FALHA: a arca nao foi construida com madeira de gofer.\n");
        return false;
    }

    if (!obra.betume_aplicado) {
        printf("FALHA: o casco nao foi impermeabilizado.\n");
        return false;
    }

    printf("SUCESSO: a arca esta pronta e impermeabilizada!\n");
    printf("Fase 1 concluida!\n");

    return true;
}
