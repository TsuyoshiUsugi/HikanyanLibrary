#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class BoxCollider
{
public:
    tnl::Vector3 size{1, 1, 1}; // コライダーのサイズ
    tnl::Vector3 offset{0, 0, 0}; // 中心からのオフセット

    bool Intersects(const BoxCollider& other, const tnl::Vector3& position, const tnl::Vector3& otherPosition) const
    {
        tnl::Vector3 halfSize = size / 2;
        tnl::Vector3 otherHalfSize = other.size / 2;

        if (position.x + halfSize.x + offset.x < otherPosition.x - otherHalfSize.x + other.offset.x) return false;
        if (position.x - halfSize.x + offset.x > otherPosition.x + otherHalfSize.x + other.offset.x) return false;
        if (position.y + halfSize.y + offset.y < otherPosition.y - otherHalfSize.y + other.offset.y) return false;
        if (position.y - halfSize.y + offset.y > otherPosition.y + otherHalfSize.y + other.offset.y) return false;
        return true;
    }
};

class entity
{
public:
    virtual ~entity() = default;
    virtual void draw() = 0;
    virtual void gameStart() = 0;
    virtual void update(float delta_time) = 0;

    virtual void OnTriggerEnter2D(entity* other)
    {
    };

    virtual void OnCollisionEnter2D(entity* other)
    {
    };

    bool intersects(const entity* other) const
    {
        return collider.Intersects(other->collider, transform.position, other->transform.position);
    }

    class transform
    {
    public:
        tnl::Vector3 position{0, 0, 0};
        tnl::Vector3 rotation{0, 0, 0};
        tnl::Vector3 scale{1, 1, 1};
    };

protected:
    transform transform;
    bool isSurvival = false;
    std::string tag = "None";

public:
    BoxCollider collider;

    const std::string& getTag() const
    {
        return tag;
    }

    void setIsSurvival(bool survival)
    {
        isSurvival = survival;
    }

    bool getIsSurvival() const
    {
        return isSurvival;
    }
};
