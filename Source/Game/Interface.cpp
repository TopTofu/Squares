#include <Game/Interface.h>
#include <Engine\Controls.h>


void pickCell(glm::vec3 worldCoords) {
		Cell* c = cellAtWorldCoords(world, worldCoords);
		quad.translation = c->worldPosition;
}