#include "contact.hpp"

#include "../sandbox/macro.hpp"

bool Intersect(BodyPtr& b1, BodyPtr& b2, Contact& contact) {
    if (b1->m_shape->getShapeType() == Shape::ShapeType::Sphere &&
        b2->m_shape->getShapeType() == Shape::ShapeType::Sphere) {
        auto sphere1 = std::dynamic_pointer_cast<ShapeSphere>(b1->m_shape);
        auto sphere2 = std::dynamic_pointer_cast<ShapeSphere>(b2->m_shape);
        float radiusSum = sphere1->m_radius + sphere2->m_radius;
        float distSquard = LengthSqrd(b1->m_position - b2->m_position);
        bool intersected = distSquard <= radiusSum * radiusSum;

        RETURN_FALSE_IF_FALSE(intersected);

        float dist = std::sqrt(distSquard);
        float elasticity = b1->m_elasticity * b2->m_elasticity;

        Vec2 vab =
            dist == 0 ? Vec2{0, 0} : (b2->m_position - b1->m_position) / dist;
        contact.m_normal = Normalize(vab);
        contact.m_bodyA = b1;
        contact.m_bodyB = b2;
        contact.m_sperateDist =
            std::abs(dist - (sphere1->m_radius + sphere2->m_radius));
        contact.m_ptOnAWorldSpace =
            b1->m_position + sphere1->m_radius * contact.m_normal;
        contact.m_ptOnBWorldSpace =
            b2->m_position - sphere1->m_radius * contact.m_normal;

        return intersected;
    }
    return false;
}

void ResolveContact(Contact& contact) {
    BodyPtr& bA = contact.m_bodyA;
    BodyPtr& bB = contact.m_bodyB;
    
    contact.m_bodyA->m_linearVel = Vec2{0, 0};
    contact.m_bodyB->m_linearVel = Vec2{0, 0};
    float elasticity = bA->m_elasticity * bB->m_elasticity;

    Vec2 vba =  bA->m_linearVel - bB->m_linearVel;
    float impulseJ = -(1.0f + elasticity) * Dot(vba, contact.m_normal) /
                     (bA->m_invMass + bB->m_invMass);
    Vec2 vectorImpulseJ = contact.m_normal * impulseJ;

    bA->ApplyLinearImpulse(vectorImpulseJ);
    bA->ApplyLinearImpulse(-vectorImpulseJ);

    float tA = bA->m_invMass / (bA->m_invMass + bB->m_invMass);
    float tB = bB->m_invMass / (bA->m_invMass + bB->m_invMass);

    Vec2 ds = contact.m_ptOnBWorldSpace - contact.m_ptOnAWorldSpace;

    bA->m_position += ds * tA;
    bA->m_position -= ds * tB;
}
