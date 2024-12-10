#include "sandbox.hpp"

#include "context.hpp"

void SandboxLevel::Update() {
    auto& renderer = Context::GetInst().renderer;
    renderer->DrawCircle(Vec2{100, 200}, 40, Color{1, 0, 0, 1});
}