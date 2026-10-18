## `main.c` — Módulo de Integração e Controle da Simulação

Este arquivo implementa o ponto de entrada do programa e coordena a integração entre os módulos de gerenciamento do jogador, comportamento do gigante e construção da arca.

A lógica principal controla o fluxo de execução da simulação, coordenando as viagens de Noé para coletar dez toras por percurso, transportar os materiais e entregá-los na área de construção.

Durante a execução, o programa atualiza o tempo da simulação e integra o módulo responsável pelo comportamento do gigante, incluindo detecção, perseguição e ataque ao jogador.

O arquivo também coordena as operações de construção da arca, permitindo contabilizar os materiais utilizados e verificar se as condições necessárias para concluir a obra foram atendidas.

Dessa forma, `main.c` atua como a camada central de integração do sistema, conectando as funcionalidades implementadas em `jogador.c`, `gigante.c` e `arca.c`, mantendo a organização modular e facilitando a manutenção e a evolução do projeto.

#include <stdio.h>
#include <stdbool.h>

#include "jogador.h"
#include "gigante.h"
#include "arca.h"

#define TEMPO_INICIAL 420.0f
#define TORAS_POR_VIAGEM 10
#define POSICAO_MATERIAIS_X 0.0f
#define POSICAO_MATERIAIS_Y 0.0f
#define POSICAO_ARCA_X 10.0f
#define POSICAO_ARCA_Y 0.0f

static bool mover_noe(
    Jogador *noe,
    Nefilim *gigante,
    float *noe_x,
    float *noe_y,
    float destino_x,
    float destino_y,
    float *tempo_restante
) {
    while (*tempo_restante > 0.0f) {
        float dx = destino_x - *noe_x;
        float dy = destino_y - *noe_y;
        float distancia = calcular_distancia(
            *noe_x, *noe_y, destino_x, destino_y
        );

        if (distancia <= 0.01f) {
            *noe_x = destino_x;
            *noe_y = destino_y;
            return true;
        }

        if (noe->velocidade_atual <= 0.0f) {
            return false;
        }

        float passo = noe->velocidade_atual;

        if (passo > distancia) {
            passo = distancia;
        }

        *noe_x += (dx / distancia) * passo;
        *noe_y += (dy / distancia) * passo;

        atualizar_gigante(
            gigante,
            *noe_x,
            *noe_y,
            1.0f,
            &noe->vivo
        );

        *tempo_restante -= 1.0f;

        if (!noe->vivo) {
            printf("\nNoe foi alcancado por um nefilim!\n");
            return false;
        }
    }

    return false;
}

int main(void) {
    Jogador noe = {
        0, 0, 0.0f, VELOCIDADE_BASE, true
    };

    Nefilim gigante = {
        25.0f, 25.0f, false
    };

    Arca obra;
    inicializar_arca(&obra);

    float tempo_restante = TEMPO_INICIAL;
    float noe_x = POSICAO_MATERIAIS_X;
    float noe_y = POSICAO_MATERIAIS_Y;
    int viagem = 0;
    bool jogo_rodando = true;
    bool betume_coletado = false;

    printf("=== FASE 1: A ARCA ===\n");
    printf("Tempo disponivel: %.0f segundos\n\n",
           tempo_restante);

    while (jogo_rodando && tempo_restante > 0.0f) {
        bool arca_completa =
            obra.comprimento_construido >= COMPRIMENTO_EXATO &&
            obra.largura_construida >= LARGURA_EXATA &&
            obra.altura_construida >= ALTURA_EXATA;

        if (arca_completa) {
            jogo_rodando = false;
            break;
        }

        viagem++;

        noe.qtd_madeira = TORAS_POR_VIAGEM;
        noe.qtd_betume = betume_coletado ? 0 : 1;

        calcular_peso_e_velocidade(&noe);

        printf("Viagem %d: Noe coletou %d toras.\n",
               viagem, noe.qtd_madeira);

        printf("Peso: %.1f kg | Velocidade: %.1f\n",
               noe.peso_total, noe.velocidade_atual);

        if (!mover_noe(
                &noe, &gigante, &noe_x, &noe_y,
                POSICAO_ARCA_X, POSICAO_ARCA_Y,
                &tempo_restante)) {
            jogo_rodando = false;
            break;
        }

        adicionar_materiais_na_obra(
            &obra,
            &noe.qtd_madeira,
            &noe.qtd_betume
        );

        betume_coletado = obra.betume_aplicado;

        printf("Progresso da arca:\n");
        printf("  Comprimento: %.1f / %.1f\n",
               obra.comprimento_construido,
               COMPRIMENTO_EXATO);
        printf("  Largura: %.1f / %.1f\n",
               obra.largura_construida,
               LARGURA_EXATA);
        printf("  Altura: %.1f / %.1f\n",
               obra.altura_construida,
               ALTURA_EXATA);
        printf("  Tempo restante: %.0f segundos\n\n",
               tempo_restante);

        if (obra.comprimento_construido >= COMPRIMENTO_EXATO &&
            obra.largura_construida >= LARGURA_EXATA &&
            obra.altura_construida >= ALTURA_EXATA) {
            break;
        }

        if (!mover_noe(
                &noe, &gigante, &noe_x, &noe_y,
                POSICAO_MATERIAIS_X, POSICAO_MATERIAIS_Y,
                &tempo_restante)) {
            jogo_rodando = false;
            break;
        }
    }

    printf("\n=== JULGAMENTO DA FASE ===\n");

    if (!noe.vivo) {
        printf("FALHA: Noe nao sobreviveu.\n");
        return 1;
    }

    if (tempo_restante <= 0.0f) {
        printf("O tempo acabou!\n");
    }

    if (julgar_diluvio(obra)) {
        return 0;
    }

    printf("Fase nao concluida.\n");
    return 1;
}
