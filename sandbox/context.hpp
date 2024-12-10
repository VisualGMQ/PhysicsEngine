#pragma once

#include "input/keyboard.hpp"
#include "input/mouse.hpp"
#include "level.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "timer.hpp"
#include "window.hpp"

class Context {
public:
    static Context& GetInst() {
        assert(inst);
        return *inst;
    }

    static void Init();
    static void Destroy();

    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<LevelManager> sceneMgr;
    std::unique_ptr<Keyboard> keyboard;
    std::unique_ptr<Mouse> mouse;
    std::unique_ptr<Time> time;
    PhysicsScene physics_scene;
    
    void Update();

    void Exit() { shouldExit_ = true; }
    bool ShouldExit() const { return shouldExit_; }

private:
    SDL_Event event_;
    bool shouldExit_ = false;

    ~Context();

    void initSDL();
    void quitSDL();
    void postInit();
    void handleEvent();

    static Context* inst;
};