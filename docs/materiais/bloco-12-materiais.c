
#include <math.h>
#include "materiais.h"
#include "gigante.h"

bool inicializar_material(
    Material *material,
    float x,
    float y,
    TipoMaterial tipo,
    int quantidade
) {
    if (material == NULL || quantidade <= 0 ||
        (tipo != MATERIAL_GOFER &&
         tipo != MATERIAL_BETUME)) {
        return false;
    }

    material->x = x;
    material->y = y;
    material->tipo = tipo;
    material->quantidade = quantidade;
    material->disponivel = true;

    return true;
}

bool coletar_material(
    Material *material,
    float noe_x,
    float noe_y,
    float alcance,
    int *inventario
) {
    if (material == NULL || inventario == NULL ||
        !material->disponivel ||
        material->quantidade <= 0 ||
        alcance < 0.0f) {
        return false;
    }

    float distancia = calcular_distancia(
        noe_x,
        noe_y,
        material->x,
        material->y
    );

    if (distancia > alcance) {
        return false;
    }

    *inventario += material->quantidade;

    material->quantidade = 0;
    material->disponivel = false;

    return true;
}
