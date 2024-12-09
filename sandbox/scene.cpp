#include "scene.hpp"

Scene SceneManager::null_;

Scene* SceneManager::Find(const std::string& name) {
    auto it = sceneMap_.find(name);
    if (it == sceneMap_.end()) {
        return nullptr;
    }
    return it->second.get();
}

Scene& SceneManager::GetCurScene() {
    return curScene_ ? *curScene_ : null_;
}

void SceneManager::Update() {
    if (curScene_) {
        curScene_->Update();
    }
}

bool SceneManager::ChangeScene(const std::string& name) {
    auto it = sceneMap_.find(name);
    if (it != sceneMap_.end()) {
        changeDstScene_ = it->second.get();
        return true;
    }
    return false;
}

void SceneManager::PostUpdate() {
    if (changeDstScene_) {
        if (curScene_) {
            curScene_->Quit();
        }

        curScene_ = changeDstScene_;
        changeDstScene_ = nullptr;

        if (curScene_) {
            if (!curScene_->IsInited()) {
                curScene_->Init();
                curScene_->isInited_ = true;
            }
            curScene_->Enter();
        }
    }
}