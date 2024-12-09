#include "context.hpp"
#include "scene/sandbox.hpp"
#include "log.hpp"
#include "math/math.hpp"
#include "renderer.hpp"

Context* Context::inst = nullptr;

void Context::Init() {
    inst = new Context;
    inst->postInit();
}

void Context::Destroy() {
    delete inst;
}

void Context::postInit() {
    initSDL();

    window = std::make_unique<Window>("Treasure Looter", 1024, 720);
    renderer = std::make_unique<Renderer>(*window);
    if (!window || !renderer) {
        quitSDL();
        exit(1);
    }
    
    time = std::make_unique<Time>();
    keyboard = std::make_unique<Keyboard>();
    mouse = std::make_unique<Mouse>();
    sceneMgr = std::make_unique<SceneManager>();

    sceneMgr->Create<SandboxScene>("sandbox scene");
    sceneMgr->ChangeScene("sandbox scene");
}

void Context::initSDL() {
    SDL_Init(SDL_INIT_EVERYTHING);
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif
}

void Context::quitSDL() {
    SDL_Quit();
}

Context::~Context() {
    time.reset();
    mouse.reset();
    keyboard.reset();
    sceneMgr.reset();
    renderer.reset();
    window.reset();

    quitSDL();
}

void Context::Update() {
    time->BeginRecordElapse();

    handleEvent();

    renderer->Clear(Color{0.3, 0.3, 0.3, 1});

    keyboard->Update();
    mouse->Update();
    sceneMgr->Update();

    renderer->Present();
    sceneMgr->PostUpdate();

    time->WaitForFps();
    time->EndRecordElapse();
}

void Context::handleEvent() {
    while (SDL_PollEvent(&event_)) {
        if (event_.type == SDL_QUIT) {
            shouldExit_ = true;
        }
        keyboard->HandleEvent(event_);
        mouse->HandleEvent(event_);
    }
}