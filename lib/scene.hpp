#pragma once

#include "body.hpp"
#include <vector>

class PhysicsScene {
public:
    Vec2 m_gravity;
    
    BodyPtr CreateBody(ShapePtr shape);
    void Update(float delta_time);
    
private:
    std::vector<BodyPtr> m_bodies;
};
