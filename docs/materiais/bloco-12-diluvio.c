#include "bloco-18-diluvio.h"

void inicializar_diluvio(
    Diluvio *diluvio,
    float velocidade_elevacao,
    float duracao_diluvio
) {
    if (
        diluvio == NULL ||
        velocidade_elevacao <= 0.0f ||
        duracao_diluvio <= 0.0f
    ) {
        return;
    }

    diluvio->nivel_agua = 0.0f;
    diluvio->nivel_anterior = 0.0f;

    diluvio->velocidade_elevacao = velocidade_elevacao;
    diluvio->profundidade_agua = 0.0f;

    diluvio->tempo_decorrido = 0.0f;
    diluvio->duracao_diluvio = duracao_diluvio;

    diluvio->diluvio_ativo = false;
    diluvio->nivel_maximo_atingido = false;
    diluvio->arca_sobrevivendo = true;
}

void iniciar_diluvio(Diluvio *diluvio) {
    if (diluvio == NULL) {
        return;
    }

    diluvio->diluvio_ativo = true;
}

void atualizar_diluvio(
    Diluvio *diluvio,
    float tempo,
    Flutuabilidade *flutuabilidade
) {
    if (
        diluvio == NULL ||
        flutuabilidade == NULL ||
        !diluvio->diluvio_ativo ||
        tempo <= 0.0f
    ) {
        return;
    }

    if (diluvio->nivel_maximo_atingido) {
        return;
    }

    diluvio->nivel_anterior = diluvio->nivel_agua;

    diluvio->tempo_decorrido += tempo;

    diluvio->nivel_agua +=
        diluvio->velocidade_elevacao * tempo;

    // Atualiza a profundidade da água.
    diluvio->profundidade_agua = diluvio->nivel_agua;

    // Atualiza a submersão da Arca.
    atualizar_flutuabilidade(
        flutuabilidade,
        diluvio->profundidade_agua
    );

    // Verifica se a Arca continua flutuando.
    verificar_sobrevivencia(
        diluvio,
        flutuabilidade
    );

    // Verifica se o tempo total do evento foi atingido.
    if (diluvio->tempo_decorrido >= diluvio->duracao_diluvio) {
        diluvio->nivel_maximo_atingido = true;
        diluvio->diluvio_ativo = false;
    }
}

bool verificar_nivel_maximo(Diluvio *diluvio) {
    if (diluvio == NULL) {
        return false;
    }

    return diluvio->nivel_maximo_atingido;
}

bool verificar_sobrevivencia(
    Diluvio *diluvio,
    const Flutuabilidade *flutuabilidade
) {
    if (
        diluvio == NULL ||
        flutuabilidade == NULL
    ) {
        return false;
    }

    diluvio->arca_sobrevivendo =
        flutuabilidade->flutuando;

    return diluvio->arca_sobrevivendo;
}
