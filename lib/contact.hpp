#pragma once
#include "body.hpp"
#include "math/math.hpp"

struct Contact {
    Vec2 m_ptOnAWorldSpace; 
    Vec2 m_ptOnBWorldSpace; 
    Vec2 m_ptOnALocalSpace; 
    Vec2 m_ptOnBLocalSpace;

    Vec2 m_normal;
    float m_sperateDist;
    float m_toi;

    BodyPtr m_bodyA;
    BodyPtr m_bodyB;
};

bool Intersect(BodyPtr&, BodyPtr&, Contact&);
void ResolveContact(Contact&);
