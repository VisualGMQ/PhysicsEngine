#pragma once
#include "math/math.hpp"
#include <memory>

class Shape {
public:
    enum class ShapeType {
        Sphere
    };

    virtual ShapeType getShapeType() = 0;
    Vec2 GetCenterOfMass() const;

private:
    Vec2 m_centerOfMass;
};

class ShapeSphere : public Shape {
public:
    ShapeSphere(float radius);

    float m_radius;
};

using ShapePtr = std::shared_ptr<Shape>;

class Body {
public:
    Vec2 m_position;
    Vec2 m_linearVel;
    Vec2 m_angularVel;
    float m_invMass = 1.0;
    float m_rotation = 0;
    float m_elasticity = 0.1f;
    ShapePtr m_shape;

    Vec2 GetCenterOfMassWorldSpace() const;
    Vec2 GetCenterOfMassLocalSpace() const;
    Vec2 BodySpace2WorldSpace(const Vec2& p) const;
    Vec2 WorldSpace2BodySpace(const Vec2& p) const;
    void ApplyLinearImpulse(const Vec2& impulse);
};

using BodyPtr = std::shared_ptr<Body>;
