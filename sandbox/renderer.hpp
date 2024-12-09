#pragma once
#include "window.hpp"
#include "SDL.h"

class Renderer {
public:
    explicit Renderer(Window& window);
    ~Renderer();

    void Clear(const Color&);
    void Present() const;
    void DrawLine(const Vec2& p1, const Vec2& p2, const Color&);
    void DrawCircle(const Vec2& center, float radius, const Color&, uint32_t sectionNum = 16);

    operator bool() const;

private:
    SDL_Renderer* renderer_;
};