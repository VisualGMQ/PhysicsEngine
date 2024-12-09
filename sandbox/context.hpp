#pragma once

#include "renderer.hpp"
#include "scene.hpp"
#include "window.hpp"
#include "input/keyboard.hpp"
#include "input/mouse.hpp"
#include "timer.hpp"

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
    std::unique_ptr<SceneManager> sceneMgr;
    std::unique_ptr<Keyboard> keyboard;
    std::unique_ptr<Mouse> mouse;
    std::unique_ptr<Time> time;
    
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