#pragma once
#include <memory>
#include <string>
#include <unordered_map>

class Scene {
public:
    friend class SceneManager;
    
    Scene() = default;  // trivial constructor to construct a NULL-like object

    bool IsInited() const { return isInited_; }
    virtual void Init() {}
    virtual void Enter() {}
    virtual void Quit() {}
    virtual void Update() {}

private:
    bool isInited_ = false;
};

class SceneManager {
public:
    SceneManager() = default;

    template <typename SceneType>
    SceneType* Create(const std::string& name);
    Scene* Find(const std::string& name);
    Scene& GetCurScene();

    void Update();
    void PostUpdate();
    bool ChangeScene(const std::string& name);
    auto& GetAllScenes() const { return sceneMap_; }

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> sceneMap_;
    static Scene null_;
    Scene* curScene_ = nullptr;
    Scene* changeDstScene_ = nullptr;
};

template <typename SceneType>
SceneType* SceneManager::Create(const std::string& name) {
    return static_cast<SceneType*>(
        sceneMap_.emplace(name, std::make_unique<SceneType>())
            .first->second.get());
}