|[&larr; Voltar](./GDD.md)  | [avançar &rarr;](./bloco-01-jogador.h)|
|:---------|------------:|

# Arquitetura do gamer 


#include <stdio.h>
#include <stdbool.h>

int main() {
    bool jogo_rodando = true;
    float tempo_restante = 420.0; // 7 minutos de jogo

    printf("--- INICIANDO FASE 1: A ARCA ---\n\n");

    // Loop principal do jogo
    while (jogo_rodando) {

        // Atualiza o jogador e o peso da madeira coletada
        // atualizar_jogador(&noe);

        // Verifica se os gigantes encontram Noé
        // atualizar_gigantes(&gigante, noe.posicao);

        // Cuida da construção da arca
        // construir_arca(&arca, &noe);

        // Fim do tempo: hora de decidir o destino da fase
        if (tempo_restante <= 0) {
            // julgar_diluvio(arca);
            jogo_rodando = false;
        }

        break; // Remover quando o loop estiver funcionando de verdade
    }

    return 0;
    }



|[&larr; Voltar](./GDD.md)  | [avançar &rarr;](./bloco-01-jogador.h)|
|:---------|------------:|
