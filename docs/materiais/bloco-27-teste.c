#include <assert.h>
#include <stdio.h>

#include "bloco-20-integracao.h"

int main(void) {

    EstadoFaseArca estado = {0};

    printf("INICIANDO TESTES DA FASE DA ARCA\n\n");

    // TESTE 1: Inicialização dos sistemas.

    inicializar_fase_arca(
        &estado,
        10.0f,
        5.0f,
        3.0f,
        10000.0f,
        0.1f,
        10.0f,
        200
    );

    assert(estado.inicializado);

    printf("[OK] Inicializacao dos sistemas\n");

    // TESTE 2: Construção da Arca.
    // Simula uma construção já concluída.

    estado.construcao.construcao_finalizada = true;

    assert(estado.construcao.construcao_finalizada);

    printf("[OK] Estado da construcao\n");

    // TESTE 3: Impermeabilização.

    int betume_aplicado =
        integracao_aplicar_betume(&estado, 200);

    assert(betume_aplicado == 200);

    assert(
        estado.impermeabilizacao
        .impermeabilizacao_finalizada
    );

    assert(estado.betume.quantidade == 0);

    printf("[OK] Impermeabilizacao da Arca\n");

    // TESTE 4: Flutuabilidade.

    atualizar_flutuabilidade(
        &estado.flutuabilidade,
        1.0f
    );

    assert(estado.flutuabilidade.flutuando);

    printf("[OK] Calculo de flutuabilidade\n");

    // TESTE 5: Estabilidade.

    atualizar_estabilidade(
        &estado.estabilidade,
        2.0f
    );

    assert(estado.estabilidade.estavel);

    printf("[OK] Verificacao de estabilidade\n");

    // TESTE 6: Inicio do Diluvio.

    integracao_iniciar_diluvio(&estado);

    assert(estado.diluvio.diluvio_ativo);

    printf("[OK] Inicio do Diluvio\n");

    // TESTE 7: Simulacao e avaliacao final.

    ResultadoFase resultado = integracao_atualizar(
        &estado,
        10.0f,
        2.0f
    );

    assert(estado.diluvio.nivel_maximo_atingido);

    assert(estado.diluvio.arca_sobrevivendo);

    assert(resultado == FASE_VITORIA);

    printf("[OK] Simulacao do Diluvio\n");
    printf("[OK] Avaliacao final da fase\n");

    printf("\nTODOS OS TESTES FORAM CONCLUIDOS.\n");
    printf("RESULTADO: VITORIA!\n");

    return 0;
}
