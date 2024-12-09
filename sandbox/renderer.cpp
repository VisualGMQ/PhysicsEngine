#include "renderer.hpp"
#include "log.hpp"

Renderer::Renderer(Window& window) {
    renderer_ = SDL_CreateRenderer(window.window_, -1, 0);
    if (!renderer_) {
        LOGE("renderer create failed");
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer_);
}

Renderer::operator bool() const {
    return renderer_;
}

void Renderer::Clear(const Color& c) {
    SDL_SetRenderDrawColor(renderer_, c.r * 255.0f, c.g * 255, c.b * 255, c.a * 255);
    SDL_RenderClear(renderer_);
}

void Renderer::Present() const {
    SDL_RenderPresent(renderer_);
}

void Renderer::DrawLine(const Vec2 &p1, const Vec2 &p2, const Color &c) {
    SDL_SetRenderDrawColor(renderer_, c.r * 255.0f, c.g * 255, c.b * 255,
                         c.a * 255);
    SDL_RenderDrawLineF(renderer_, p1.x, p1.y, p2.x, p2.y);
}

void Renderer::DrawCircle(const Vec2 &center, float radius, const Color &c,
                          uint32_t sectionNum) {
    SDL_SetRenderDrawColor(renderer_, c.r * 255.0f, c.g * 255, c.b * 255,
                         c.a * 255);
    const float angle = 2.0f * PI / sectionNum;

    for (int i = 0; i < sectionNum; i++) {
      float curAngle = i * angle;
      float nextAngle = (i + 1) * angle;
      Vec2 offset1{std::cos(curAngle), std::sin(curAngle)};
      offset1 *= radius;
      Vec2 offset2{std::cos(nextAngle), std::sin(nextAngle)};
      offset2 *= radius;

      Vec2 p1 = center + offset1;
      Vec2 p2 = center + offset2;
      SDL_RenderDrawLine(renderer_, p1.x, p1.y, p2.x, p2.y);
    }
}