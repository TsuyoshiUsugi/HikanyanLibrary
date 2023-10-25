#pragma once
#include <iostream>


// シングルトンを実現するテンプレートクラス
template <typename T>
class singleton
{
public:
    // インスタンスを取得する
    static T* getInstance()
    {
        static T* instance = nullptr; // スレッドセーフなシングルトン
        if (!instance)instance = new T();
        return instance;
    }

    // インスタンスを破棄する
    static void destroyInstance()
    {
        delete getInstance();
    }

protected:
    singleton()
    {
    } // プライベートコンストラクタを使って外部からのインスタンス生成を防ぐ
    singleton(const singleton&) = delete; // コピーを禁止
    singleton& operator=(const singleton&) = delete; // 代入演算子を禁止
};
