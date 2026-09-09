# 08 — Memória Distribuída


Uma arquitetura formada por células independentes precisa definir como os dados são armazenados e disponibilizados durante a execução dos programas.

Na ACS, não existe uma única memória central responsável por todo o sistema.

A proposta é distribuir a capacidade de armazenamento entre as próprias células.

---

## Memória Local

Cada célula possui uma área de memória própria, utilizada para armazenar informações necessárias às suas operações.

Uma célula pode armazenar, por exemplo:

- dados;
- instruções;
- resultados intermediários;
- informações temporárias;
- estado de execução.

A organização interna e a tecnologia dessa memória ainda serão definidas em etapas posteriores.

### Representação conceitual

```text
┌─────────────────────┐
│      CÉLULA ACS     │
│                     │
│  ┌───────────────┐  │
│  │ Processamento │  │
│  └───────────────┘  │
│                     │
│  ┌───────────────┐  │
│  │ Memória Local │  │
│  └───────────────┘  │
│                     │
│  ┌───────────────┐  │
│  │ Comunicação   │  │
│  └───────────────┘  │
└─────────────────────┘
```
Memória Distribuída

A capacidade total de memória da ACS é formada pela combinação das memórias existentes nas células.
```text
        ┌──────────┐
        │ CÉLULA A │
        │ Memória  │
        └────┬─────┘
             │
        ┌────▼─────┐
        │ CÉLULA B │
        │ Memória  │
        └────┬─────┘
             │
        ┌────▼─────┐
        │ CÉLULA C │
        │ Memória  │
        └──────────┘
```
Dessa forma, o crescimento do número de células também pode aumentar a capacidade total de armazenamento da arquitetura.

⸻

Solicitação de Dados

Uma célula não acessa diretamente a memória interna de outra célula.

Quando necessita de um dado armazenado em outra célula, realiza uma solicitação através da rede.
```text
┌──────────┐
│ CÉLULA A │
└────┬─────┘
     │
     │ Solicitação
     ▼
┌──────────┐
│ CÉLULA B │
│ Memória  │
└────┬─────┘
     │
     │ Dado
     ▼
┌──────────┐
│ CÉLULA A │
└──────────┘
```

O processo conceitual é:

1. A célula A necessita de um dado.
2. A célula A solicita esse dado através da comunicação.
3. A célula B localiza o dado em sua memória local.
4. O dado é enviado de volta para a célula A.
5. A célula A utiliza o dado em sua execução.

⸻

Localização dos Dados

A memória distribuída introduz uma questão fundamental:

Como uma célula sabe onde determinado dado está armazenado?

Essa questão ainda não possui uma solução definida na arquitetura atual.

O projeto deverá investigar mecanismos capazes de localizar dados dentro da malha sem criar uma nova dependência de um controlador central.

Essa será uma das questões fundamentais para o desenvolvimento da ACS.

⸻

Crescimento da Memória

A capacidade total de armazenamento pode acompanhar o crescimento da arquitetura.

Ao adicionar novas células à malha, novas áreas de memória também são adicionadas ao sistema.

Conceitualmente:

```text
     MALHA MENOR

   ┌─────────────┐
   │ ○──○──○      │
   │ │  │  │      │
   │ ○──○──○      │
   └─────────────┘
          │
          ▼
     NOVAS CÉLULAS
          │
          ▼
     MALHA MAIOR

   ┌─────────────────┐
   │ ○──○──○──○──○    │
   │ │  │  │  │  │    │
   │ ○──○──○──○──○    │
   │ │  │  │  │  │    │
   │ ○──○──○──○──○    │
   └─────────────────┘
```
Isso permite investigar uma arquitetura em que capacidade computacional e capacidade de armazenamento crescem juntamente com o número de células.

⸻

Uso da Memória Durante a Execução

Uma tarefa pode utilizar dados armazenados em diferentes células da malha.

Isso conecta diretamente esta seção à Seção 07 — Execução de Programas.

Uma célula pode executar uma tarefa utilizando:

* dados presentes em sua própria memória;
* dados recebidos de outras células;
* resultados intermediários produzidos por outras células.

A comunicação definida na Seção 06 — Comunicação entre Células é utilizada para transportar essas informações.

⸻

Falha de uma Célula

A distribuição da memória também cria um novo desafio.

Se determinado dado existir somente na memória de uma célula que falhou, esse dado poderá ficar indisponível.

A partir disso, a ACS deverá investigar mecanismos de proteção, como:

* replicação;
* cópias distribuídas;
* reconstrução de dados;
* redistribuição de informações.

Esses mecanismos ainda não fazem parte da definição atual da arquitetura.

⸻

Princípio da ACS

Na ACS, a memória é distribuída entre as células e acessada através da comunicação, sem depender de uma única memória central.

09 — Tolerância a Falhas
