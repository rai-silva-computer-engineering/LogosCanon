# Bloco 03 — Sistema da Arca

```c
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Medidas exigidas para a construção da arca, em côvados
#define COMPRIMENTO_EXATO 300.0
#define LARGURA_EXATA 50.0
#define ALTURA_EXATA 30.0

// Estado atual da construção
typedef struct {
    float comprimento_construido;
    float largura_construida;
    float altura_construida;
    bool betume_aplicado;
    bool feita_de_gofer;
} Arca;

// Transfere os materiais do Noé para a construção
void adicionar_materiais_na_obra(Arca *obra, int *madeira_do_noe,
                                 int *betume_do_noe) {
    if (*madeira_do_noe > 0) {
        obra->comprimento_construido += *madeira_do_noe * 1.5;
        obra->feita_de_gofer = true;
        *madeira_do_noe = 0;
    }

    if (*betume_do_noe > 0) {
        obra->betume_aplicado = true;
        *betume_do_noe = 0;
    }
}

// Confere se a arca está pronta quando o tempo acaba
bool julgar_diluvio(Arca obra) {
    printf("\n[ O TEMPO ACABOU. O DILÚVIO COMEÇOU ]\n");

    // Confere se as medidas estão corretas
    if (fabs(obra.comprimento_construido - COMPRIMENTO_EXATO) > 0.001 ||
        fabs(obra.largura_construida - LARGURA_EXATA) > 0.001 ||
        fabs(obra.altura_construida - ALTURA_EXATA) > 0.001) {
        printf("FAILED. As medidas não seguem o projeto divino.\n");
        printf("A estrutura não resistiu ao dilúvio.\n");
        return false;
    }

    // Confere se o casco foi impermeabilizado
    if (!obra.betume_aplicado) {
        printf("FAILED. A água invadiu o casco.\n");
        printf("A arca afundou.\n");
        return false;
    }

    // Confere se a madeira utilizada é a correta
    if (!obra.feita_de_gofer) {
        printf("FAILED. Madeira incorreta utilizada.\n");
        printf("A estrutura cedeu.\n");
        return false;
    }

    printf("SUCESSO! A estrutura resistiu. A arca flutua!\n");
    printf("Fase 1 concluída!\n");

    return true;
}
```

**Função do módulo:** recebe a madeira e o betume coletados por Noé e verifica se a arca atende aos requisitos quando o tempo termina.

