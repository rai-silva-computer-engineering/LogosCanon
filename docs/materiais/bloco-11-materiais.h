
#ifndef MATERIAIS_H
#define MATERIAIS_H

#include <stdbool.h>

#define MAX_MATERIAIS 100

typedef enum {
    MATERIAL_GOFER,
    MATERIAL_BETUME
} TipoMaterial;

typedef struct {
    float x;
    float y;
    TipoMaterial tipo;
    int quantidade;
    bool disponivel;
} Material;

bool inicializar_material(
    Material *material,
    float x,
    float y,
    TipoMaterial tipo,
    int quantidade
);

bool coletar_material(
    Material *material,
    float noe_x,
    float noe_y,
    float alcance,
    int *inventario
);

#endif
