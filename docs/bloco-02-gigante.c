# Bloco 02 — Sistema dos Gigantes

```c
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Configurações do gigante
#define RAIO_DE_VISAO 15.0
#define VELOCIDADE_GIGANTE 6.0
#define DISTANCIA_DE_ATAQUE 1.5

// Posição e estado do gigante
typedef struct {
    float pos_x;
    float pos_y;
    bool perseguindo_jogador;
} Nefilim;

// Calcula a distância entre o gigante e Noé
float calcular_distancia(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Verifica se Noé foi visto ou alcançado
void atualizar_gigante(Nefilim *gigante, float noe_x, float noe_y,
                       float velocidade_noe, bool *noe_vivo) {

    float distancia = calcular_distancia(
        gigante->pos_x, gigante->pos_y, noe_x, noe_y
    );

    // Noé entrou no campo de visão
    if (distancia <= RAIO_DE_VISAO) {
        gigante->perseguindo_jogador = true;

        // O gigante consegue alcançar Noé?
        if (VELOCIDADE_GIGANTE > velocidade_noe) {
            if (distancia <= DISTANCIA_DE_ATAQUE) {
                *noe_vivo = false;
            }
        }
    } else {
        // Noé saiu do alcance e o gigante para de perseguir
        gigante->perseguindo_jogador = false;
    }
}
```

**Função do módulo:** controla o campo de visão dos gigantes, calcula a distância até Noé e verifica se ele foi alcançado.

