
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Medidas da arca em côvados
#define COMPRIMENTO_EXATO 300.0
#define LARGURA_EXATA 50.0
#define ALTURA_EXATA 30.0

// Quanto cada tora contribui para a construção
#define MEDIDA_POR_TORA 1.5
#define TOLERANCIA 0.001

// Estado atual da construção
typedef struct {
    float comprimento_construido;
    float largura_construida;
    float altura_construida;
    bool betume_aplicado;
    bool feita_de_gofer;
} Arca;

// Adiciona os materiais coletados à construção
void adicionar_materiais_na_obra(Arca *obra, int *madeira_do_noe,
                                 int *betume_do_noe) {
    if (*madeira_do_noe > 0) {
        float madeira_disponivel = *madeira_do_noe * MEDIDA_POR_TORA;

        if (obra->comprimento_construido < COMPRIMENTO_EXATO) {
            float restante = COMPRIMENTO_EXATO -
                             obra->comprimento_construido;
            float usada = fmin(madeira_disponivel, restante);

            obra->comprimento_construido += usada;
            madeira_disponivel -= usada;
        }

        if (madeira_disponivel > 0 &&
            obra->largura_construida < LARGURA_EXATA) {
            float restante = LARGURA_EXATA -
                             obra->largura_construida;
            float usada = fmin(madeira_disponivel, restante);

            obra->largura_construida += usada;
            madeira_disponivel -= usada;
        }

        if (madeira_disponivel > 0 &&
            obra->altura_construida < ALTURA_EXATA) {
            float restante = ALTURA_EXATA -
                             obra->altura_construida;
            float usada = fmin(madeira_disponivel, restante);

            obra->altura_construida += usada;
        }

        obra->feita_de_gofer = true;
        *madeira_do_noe = 0;
    }

    if (*betume_do_noe > 0) {
        obra->betume_aplicado = true;
        *betume_do_noe = 0;
    }
}

// Verifica se a arca está pronta quando o tempo acaba
bool julgar_diluvio(Arca obra) {
    printf("\n[ O TEMPO ACABOU. O DILÚVIO COMEÇOU ]\n");

    // Confere as medidas da arca
    if (fabs(obra.comprimento_construido - COMPRIMENTO_EXATO) > TOLERANCIA ||
        fabs(obra.largura_construida - LARGURA_EXATA) > TOLERANCIA ||
        fabs(obra.altura_construida - ALTURA_EXATA) > TOLERANCIA) {

        printf("FAILED. As medidas não seguem o projeto divino.\n");
        printf("A estrutura não resistiu ao dilúvio.\n");
        return false;
    }

    // Confere a impermeabilização
    if (!obra.betume_aplicado) {
        printf("FAILED. A água invadiu o casco.\n");
        printf("A arca afundou.\n");
        return false;
    }

    // Confere o material utilizado
    if (!obra.feita_de_gofer) {
        printf("FAILED. A madeira utilizada está incorreta.\n");
        printf("A estrutura cedeu.\n");
        return false;
    }

    printf("SUCESSO! A estrutura resistiu. A arca flutua!\n");
    printf("Fase 1 concluída!\n");

    return true;
}
