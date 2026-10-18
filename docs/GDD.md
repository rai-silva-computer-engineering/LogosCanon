
|[Avançar &rarr;](./arquitetura.md)|
|:-------|--------:|



# Game Design Document: Logos Canon

## 1. Visão Geral
**Logos Canon** é um simulador físico e estrutural fundamentado em eventos bíblicos. O jogador precisa aplicar variáveis exatas de engenharia, balística e acústica para avançar. O fracasso matemático na execução dos parâmetros resulta em falha punitiva.

## 2. Arquitetura do Sistema
Para garantir o rigor das simulações físicas, o núcleo do jogo é projetado com foco em linguagens de baixo nível (C, C++ ou Rust), permitindo controle estrito de memória e processamento em tempo real de cálculos complexos, como fluidodinâmica e colisões vetoriais.

---

## 3. Fases e Mecânicas Físicas

### Fase 1: O Desafio de Gôfer (A Construção da Arca)

#### 3.1. Visão Geral da Fase
Nesta fase inaugural, o jogador assume a responsabilidade da construção da Arca. O objetivo não envolve combate, mas sim planejamento, precisão, engenharia de sobrevivência e, acima de tudo, obediência estrita às métricas divinas. O desafio é construir uma embarcação funcional e impermeável antes que o cronômetro do dilúvio zere.

#### 3.2. Mecânicas Principais (Core Mechanics)
*   **O Sistema de Côvados:** A interface não fornece marcações modernas (como metros ou centímetros). O menu de missões é um pergaminho com as instruções de Gênesis 6. O jogador deve converter a proporção bíblica (300 côvados de comprimento, 50 de largura e 30 de altura) para a grade de construção tridimensional do jogo. O corte da madeira exige precisão milimétrica.
*   **Coleta de Materiais Específicos:** O mapa oferece diversos tipos de árvores, mas apenas a "Madeira de Gôfer" garante a flutuabilidade e resistência corretas. Se o jogador tentar acelerar o processo usando madeiras mais fáceis de cortar ou mais próximas do acampamento (ex: pinheiro), a estrutura cederá sob a pressão da simulação de fluidos.
*   **Sistema de Impermeabilização (Betume):** Não basta encaixar a madeira. O jogo possui uma mecânica de selamento. O jogador deve aplicar betume por dentro e por fora de **todas** as juntas estruturais. O motor do jogo rastreia cada emenda. Uma junta sem betume é classificada silenciosamente como um "ponto de falha" (leak point).

#### 3.3. A Tela de Teste (O Dilúvio)
Quando o tempo de construção acaba, os controles de engenharia são bloqueados e a cinemática do dilúvio começa. O jogador é trancado na arca e o motor de física assume o controle.
*   **Condição de Vitória:** A simulação de empuxo calcula o volume da arca e seu peso. Se as medidas estiverem corretas e seladas, a arca balança, estabiliza e flutua. Fase concluída.
*   **Condição de Derrota (Game Over):** Se as proporções gerarem um centro de massa instável, a arca tomba. Se houver frestas sem betume, a física da água detecta a brecha e invade o casco. A embarcação perde flutuabilidade e afunda com o peso da água e dos animais.
*   **Mensagem de Derrota:** A tela escurece lentamente ao som da estrutura cedendo. Surge o texto: *"FAILED. Você não seguiu as orientações do Salvador."*

#### 3.4. Requisitos Técnicos e Arquitetura de Física
Para que o peso da madeira, o centro de massa dinâmico (com animais se movendo dentro) e a simulação de fluidos funcionem sem travar o jogo, o núcleo (*core*) de física exigirá otimização extrema. A lógica de colisão e empuxo não pode depender de *scripts* genéricos. O desenvolvimento dos módulos de detecção de frestas e cálculo de volume deslocado precisará ser construído em linguagens de baixo nível (como C, C++ ou Rust) para garantir o gerenciamento rigoroso de memória e processamento em tempo real durante a subida das águas.

---

### Fase 2: Davi e Golias (Balística e Cinética)
*(Em desenvolvimento - Foco no cálculo vetorial, força centrífuga da funda e impacto cinético).*

### Fase 3: As Muralhas de Jericó (Acústica e Ressonância)
*(Em desenvolvimento - Foco em frequência de ressonância natural da pedra e fadiga de material por ondas sonoras).*


|[Avançar &rarr;](./arquitetura.md)|
|:-------|--------:|


