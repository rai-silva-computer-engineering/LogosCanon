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

