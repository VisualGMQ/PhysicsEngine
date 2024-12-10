#pragma once
#include <memory>
#include <string>
#include <unordered_map>

class Level {
public:
    friend class LevelManager;
    
    Level() = default;  // trivial constructor to construct a NULL-like object

    bool IsInited() const { return isInited_; }
    virtual void Init() {}
    virtual void Enter() {}
    virtual void Quit() {}
    virtual void Update() {}

private:
    bool isInited_ = false;
};

class LevelManager {
public:
    LevelManager() = default;

    template <typename SceneType>
    SceneType* Create(const std::string& name);
    Level* Find(const std::string& name);
    Level& GetCurScene();

    void Update();
    void PostUpdate();
    bool ChangeScene(const std::string& name);
    auto& GetAllScenes() const { return sceneMap_; }

private:
    std::unordered_map<std::string, std::unique_ptr<Level>> sceneMap_;
    static Level null_;
    Level* curScene_ = nullptr;
    Level* changeDstScene_ = nullptr;
};

template <typename SceneType>
SceneType* LevelManager::Create(const std::string& name) {
    return static_cast<SceneType*>(
        sceneMap_.emplace(name, std::make_unique<SceneType>())
            .first->second.get());
}