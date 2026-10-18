# Bloco 01 — Sistema do Jogador

```c
#include <stdio.h>
#include <stdbool.h>

// Peso dos materiais e limites do personagem
#define PESO_MADEIRA_GOFER 5.0
#define PESO_BALDE_BETUME 2.0
#define CAPACIDADE_MAXIMA 50.0
#define VELOCIDADE_BASE 10.0

// Dados do Noé e dos materiais que ele carrega
typedef struct {
    int qtd_madeira;
    int qtd_betume;
    float peso_total;
    float velocidade_atual;
    bool vivo;
} Jogador;

// Calcula o peso da carga e ajusta a velocidade do Noé
void calcular_peso_e_velocidade(Jogador *noe) {
    noe->peso_total =
        (noe->qtd_madeira * PESO_MADEIRA_GOFER) +
        (noe->qtd_betume * PESO_BALDE_BETUME);

    // Com carga acima do limite, Noé fica mais lento
    if (noe->peso_total > CAPACIDADE_MAXIMA) {
        noe->velocidade_atual = VELOCIDADE_BASE * 0.2;
    } else {
        // Quanto mais peso, menor a velocidade
        noe->velocidade_atual =
            VELOCIDADE_BASE - (noe->peso_total * 0.1);
    }
}
```

**Função do módulo:** controla o inventário de Noé, calcula o peso dos materiais coletados e ajusta sua velocidade de acordo com a carga transportada.
