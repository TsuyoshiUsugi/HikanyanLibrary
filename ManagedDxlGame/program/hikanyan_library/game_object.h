#pragma once
#include "object.h"
#include "../dxlib_ext/dxlib_ext.h"
#include <unordered_map>
#include <typeindex>
#include <memory>

class Component;

class game_object : public object
{
public:
    std::string tag() const
    {
        return tagValue;
    }

    void setTag(const std::string& value)
    {
        tagValue = value;
    }

    // コンポーネントを取得する
    template <typename T>
    T* GetComponent() const
    {
        auto it = components.find(std::type_index(typeid(T)));
        return it != components.end() ? dynamic_cast<T*>(it->second.get()) : nullptr;
    }

    // コンポーネントを追加する
    template <typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        std::unique_ptr<Component> newComponent(new T(std::forward<Args>(args)...));
        T* componentPtr = dynamic_cast<T*>(newComponent.get());
        components[std::type_index(typeid(T))] = std::move(newComponent);
        return componentPtr;
    }

    // コンポーネントを削除する
    template <typename T>
    void RemoveComponent()
    {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end())
        {
            components.erase(it);
        }
    }

protected:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components; //コンポーネントの辞書
    std::string tagValue;
};
