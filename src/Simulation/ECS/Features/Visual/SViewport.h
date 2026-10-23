#ifndef VIEWPORT_H
#define VIEWPORT_H
#include "Math/Rect.h"
#include "Simulation/ECS/System.h"


class SViewport: public ECS::System
{
    // Y-up-directed screen viewport
public:
    SViewport();

    bool Update(float dt) override;

    static Vector2f ToScreen(Vector2f inViewport);

    static Vector2f ToLocal(Vector2f screenPoint);

    static RectF& Get();

    static RectF GetLocal();
};


#endif //VIEWPORT_H
