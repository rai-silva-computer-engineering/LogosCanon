## `main.c` — Módulo de Integração entre blocos e Controle da Simulação


#include <stdio.h>
#include <stdbool.h>

#include "jogador.h"
#include "gigante.h"
#include "arca.h"
#include "orientacao.h"

#define TEMPO_INICIAL 420.0f
#define TORAS_POR_VIAGEM 10
#define BETUME_POR_COLETA 1
#define TEMPO_COLETA 5.0f
#define INTERVALO_SIMULACAO 1.0f

#define POSICAO_MATERIAIS_X 0.0f
#define POSICAO_MATERIAIS_Y 0.0f
#define POSICAO_ARCA_X 10.0f
#define POSICAO_ARCA_Y 0.0f

static bool coletar_materiais(
    Jogador *noe,
    Nefilim *gigante,
    float noe_x,
    float noe_y,
    float *tempo_restante,
    bool *betume_coletado
) {
    if (noe == NULL || gigante == NULL ||
        tempo_restante == NULL || betume_coletado == NULL ||
        !noe->vivo || *tempo_restante < TEMPO_COLETA) {
        return false;
    }

    float tempo_coletando = 0.0f;

    while (tempo_coletando < TEMPO_COLETA) {
        atualizar_gigante(
            gigante,
            noe_x,
            noe_y,
            INTERVALO_SIMULACAO,
            &noe->vivo
        );

        *tempo_restante -= INTERVALO_SIMULACAO;
        tempo_coletando += INTERVALO_SIMULACAO;

        if (!noe->vivo) {
            printf("\nNoe foi alcancado enquanto coletava materiais!\n");
            return false;
        }

        if (*tempo_restante <= 0.0f) {
            return false;
        }
    }

    noe->qtd_madeira += TORAS_POR_VIAGEM;

    if (!*betume_coletado) {
        noe->qtd_betume += BETUME_POR_COLETA;
        *betume_coletado = true;
    }

    calcular_peso_e_velocidade(noe);

    printf("Materiais coletados: %d toras e %d balde(s) de betume.\n",
           TORAS_POR_VIAGEM,
           *betume_coletado ? BETUME_POR_COLETA : 0);

    return true;
}

static bool mover_noe(
    Jogador *noe,
    Nefilim *gigante,
    float *noe_x,
    float *noe_y,
    Rota *rota,
    float *tempo_restante
) {
    if (noe == NULL || gigante == NULL ||
        noe_x == NULL || noe_y == NULL ||
        rota == NULL || tempo_restante == NULL ||
        !noe->vivo || rota->quantidade <= 0) {
        return false;
    }

    while (*tempo_restante > 0.0f && !rota->concluida) {
        Ponto alvo = rota->pontos[rota->trecho_atual];

        float dx = alvo.x - *noe_x;
        float dy = alvo.y - *noe_y;
        float distancia = calcular_distancia(
            *noe_x, *noe_y, alvo.x, alvo.y
        );

        if (distancia <= rota->tolerancia) {
            validar_posicao_rota(
                rota, *noe_x, *noe_y, &noe->vivo
            );
            continue;
        }

        if (noe->velocidade_atual <= 0.0f) {
            return false;
        }

        float passo = noe->velocidade_atual * INTERVALO_SIMULACAO;

        if (passo > distancia) {
            passo = distancia;
        }

        *noe_x += (dx / distancia) * passo;
        *noe_y += (dy / distancia) * passo;

        atualizar_gigante(
            gigante,
            *noe_x,
            *noe_y,
            INTERVALO_SIMULACAO,
            &noe->vivo
        );

        *tempo_restante -= INTERVALO_SIMULACAO;

        if (!noe->vivo) {
            printf("\nNoe foi alcancado por um nefilim!\n");
            return false;
        }

        validar_posicao_rota(
            rota, *noe_x, *noe_y, &noe->vivo
        );
    }

    return rota->concluida && noe->vivo;
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
            break;
        }

        viagem++;

        printf("--- Viagem %d ---\n", viagem);

        if (!coletar_materiais(
                &noe,
                &gigante,
                noe_x,
                noe_y,
                &tempo_restante,
                &betume_coletado)) {
            jogo_rodando = false;
            break;
        }

        printf("Peso carregado: %.1f kg | Velocidade: %.1f\n",
               noe.peso_total,
               noe.velocidade_atual);

        Ponto rota_ida[] = {
            {5.0f, 0.0f},
            {POSICAO_ARCA_X, POSICAO_ARCA_Y}
        };

        Rota ida;

        if (!inicializar_rota(
                &ida,
                rota_ida,
                2,
                0.1f
            ) ||
            !mover_noe(
                &noe,
                &gigante,
                &noe_x,
                &noe_y,
                &ida,
                &tempo_restante
            )) {
            jogo_rodando = false;
            break;
        }

        adicionar_materiais_na_obra(
            &obra,
            &noe.qtd_madeira,
            &noe.qtd_betume
        );

        calcular_peso_e_velocidade(&noe);

        printf("Materiais entregues na arca.\n");
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

        arca_completa =
            obra.comprimento_construido >= COMPRIMENTO_EXATO &&
            obra.largura_construida >= LARGURA_EXATA &&
            obra.altura_construida >= ALTURA_EXATA;

        if (arca_completa || tempo_restante <= 0.0f) {
            break;
        }

        Ponto rota_volta[] = {
            {5.0f, 0.0f},
            {POSICAO_MATERIAIS_X, POSICAO_MATERIAIS_Y}
        };

        Rota volta;

        if (!inicializar_rota(
                &volta,
                rota_volta,
                2,
                0.1f
            ) ||
            !mover_noe(
                &noe,
                &gigante,
                &noe_x,
                &noe_y,
                &volta,
                &tempo_restante
            )) {
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
