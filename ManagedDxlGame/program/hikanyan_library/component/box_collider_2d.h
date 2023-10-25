#pragma once
#include <cstdint>
#include <typeinfo>

#include "component.h"

// このCastHelperは疑似コードです。具体的な定義が必要です。
template <typename T>
struct CastHelper {
    T t;
    uintptr_t onePointerFurtherThanT = reinterpret_cast<uintptr_t>(&t) + sizeof(T);
};

class box_collider_2d: public component
{
public:
    void GetComponentFastPath(const std::type_info& type, uintptr_t oneFurtherThanResultValue) {
        //TODO
    }

    template <typename T>
    T GetComponent() {
        CastHelper<T> castHelper;
        GetComponentFastPath(typeid(T), reinterpret_cast<uintptr_t>(&castHelper.onePointerFurtherThanT));
        return castHelper.t;
    }
};
