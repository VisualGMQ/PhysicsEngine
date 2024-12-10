#include "level.hpp"

Level LevelManager::null_;

Level* LevelManager::Find(const std::string& name) {
    auto it = sceneMap_.find(name);
    if (it == sceneMap_.end()) {
        return nullptr;
    }
    return it->second.get();
}

Level& LevelManager::GetCurScene() {
    return curScene_ ? *curScene_ : null_;
}

void LevelManager::Update() {
    if (curScene_) {
        curScene_->Update();
    }
}

bool LevelManager::ChangeScene(const std::string& name) {
    auto it = sceneMap_.find(name);
    if (it != sceneMap_.end()) {
        changeDstScene_ = it->second.get();
        return true;
    }
    return false;
}

void LevelManager::PostUpdate() {
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