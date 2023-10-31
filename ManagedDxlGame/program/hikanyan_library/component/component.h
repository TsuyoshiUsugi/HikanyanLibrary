#pragma once

class GameObject; // GameObjectの前方宣言。

class Component
{
protected:
    GameObject* owner; // このコンポーネントを所有するGameObjectへのポインタ。

public:
    Component() : owner(nullptr)
    {
    }

    virtual ~Component()
    {
    }

    // シーン開始時に呼ばれます。
    virtual void Awake()
    {
    }

    // シーン開始時に呼ばれます。
    virtual void Start()
    {
    }

    // 毎フレーム呼ばれます。
    virtual void Update()
    {
    }

    // コンポーネントが有効になった時に呼ばれます。
    virtual void OnEnable()
    {
    }

    // コンポーネントが無効になった時に呼ばれます。
    virtual void OnDisable()
    {
    }

    // コンポーネントが破棄される直前に呼ばれます。
    virtual void OnDestroy()
    {
    }

    // このコンポーネントを所有するGameObjectへの参照を設定します。
    void SetOwner(GameObject* gameObject)
    {
        owner = gameObject;
    }

    // このコンポーネントを所有するGameObjectへの参照を取得します。
    GameObject* GetOwner() const
    {
        return owner;
    }
};
