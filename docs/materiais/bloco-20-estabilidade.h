### O que este bloco acrescenta?

- Calcula a massa total da Arca e das cargas.
- Registra a posição de cada carga.
- Calcula o centro de massa nos três eixos.
- Identifica deslocamentos laterais.
- Sinaliza risco de tombamento conforme um limite configurado.

**Fundamento físico:** o centro de massa depende da soma dos momentos de massa dividida pela massa total:

```math
x_{CM}=\frac{\sum m_i x_i}{\sum m_i}



#ifndef ESTABILIDADE_H
#define ESTABILIDADE_H

#include <stdbool.h>

#define GRAVIDADE_ESTABILIDADE 9.81f

typedef struct {
    float massa;
    float posicao_x;
    float posicao_y;
    float posicao_z;
} CargaEstabilidade;

typedef struct {
    float massa_arca;

    float centro_massa_x;
    float centro_massa_y;
    float centro_massa_z;

    float momento_x;
    float momento_y;
    float momento_z;

    float massa_total;

    float deslocamento_x;
    float deslocamento_y;

    float angulo_inclinacao;

    bool estavel;
    bool risco_tombamento;

} Estabilidade;

void inicializar_estabilidade(
    Estabilidade *estabilidade,
    float massa_arca
);

bool adicionar_carga_estabilidade(
    Estabilidade *estabilidade,
    const CargaEstabilidade *carga
);

void calcular_centro_massa(
    Estabilidade *estabilidade
);

void atualizar_estabilidade(
    Estabilidade *estabilidade,
    float limite_deslocamento
);

#endif
