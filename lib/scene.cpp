#include "scene.hpp"

#include "contact.hpp"
#include "macro.hpp"

BodyPtr PhysicsScene::CreateBody(ShapePtr shape) {
    auto body = std::make_shared<Body>();
    body->m_shape = shape;
    return m_bodies.emplace_back(std::move(body));
}

void PhysicsScene::Update(float delta_time) {
    for (auto& body : m_bodies) {
        CONTINUE_IF(body->m_invMass == 0);
        Vec2 gravityImpulse = m_gravity * 1.0 / body->m_invMass * delta_time;
        body->ApplyLinearImpulse(gravityImpulse);
    }

    for (int i = 0; i < m_bodies.size(); ++i) {
        for (int j = i; j < m_bodies.size(); ++j) {
            auto& bodyA = m_bodies[i];
            auto& bodyB = m_bodies[j];
            CONTINUE_IF(bodyA->m_invMass == 0 && bodyB->m_invMass == 0);
            
            Contact contact;
            if (Intersect(bodyA, bodyB, contact)) {
                ResolveContact(contact);
            }
        }
    }

    for (auto& body : m_bodies) {
        body->m_position += body->m_linearVel * delta_time;
    }
}