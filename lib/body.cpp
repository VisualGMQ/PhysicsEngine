#include "body.hpp"
#include "macro.hpp"

Vec2 Shape::GetCenterOfMass() const {
    return m_centerOfMass;
}

ShapeSphere::ShapeSphere(float radius) : m_radius{radius} {}

Vec2 Body::GetCenterOfMassWorldSpace() const {
    RETURN_DEFAULT_IF_FALSE(m_shape);
    return CreateRotation2D(m_rotation) * m_shape->GetCenterOfMass() +
           m_position;
}

Vec2 Body::GetCenterOfMassLocalSpace() const {
    RETURN_DEFAULT_IF_FALSE(m_shape);
    return m_shape->GetCenterOfMass();
}

Vec2 Body::BodySpace2WorldSpace(const Vec2& p) const {
    return CreateRotation2D(m_rotation) * p + m_position;
}

Vec2 Body::WorldSpace2BodySpace(const Vec2& p) const {
    return CreateRotation2D(-m_rotation) * (p - m_position);
}

void Body::ApplyLinearImpulse(const Vec2& impulse) {
    RETURN_IF_FALSE(m_invMass != 0);

    m_linearVel += impulse * m_invMass; 
}