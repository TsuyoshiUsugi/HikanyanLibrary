#include "entity_controller.h"
#include "bullet.h"
#include "player.h"
#include <random>

#include "enemy.h"

tnl::Vector3 getRandomPosition()
{
    std::random_device rd;
    std::mt19937 gen(rd()); // メルセンヌ・ツイスタ法を使用した乱数生成器を初期化
    std::uniform_real_distribution<float> posX(0.0f, DXE_WINDOW_WIDTH);
    std::uniform_real_distribution<float> posY(0.0f, DXE_WINDOW_HEIGHT * 0.6);

    float x = posX(gen); // 指定範囲内のランダムな x 座標
    float y = posY(gen); // 指定範囲内のランダムな y 座標

    return tnl::Vector3(x, y, 0);
}

void entity_controller::initialize()
{
    auto* player_ = new player();
    entityList.push_back(player_);
}

void entity_controller::bulletInstance(tnl::Vector3 position)
{
    auto* bullet_ = new bullet();
    bullet_->setPosition(position);
    entityList.push_back(bullet_);
}

void entity_controller::enemyInstance(tnl::Vector3 position)
{
    // エネミーを指定された数だけ生成し、ランダムな位置に配置
    for (int i = 0; i < num_enemies; ++i)
    {
        auto* enemy_ = new enemy();
        enemy_->setPosition(getRandomPosition()); // ランダムな位置に配置
        entityList.push_back(enemy_);
    }
}

void entity_controller::gameStart()
{
    initialize();
    for (int i = 0; i < entityList.size(); i++)
    {
        entityList[i]->gameStart();
    }
}

void entity_controller::draw()
{
    for (int i = 0; i < entityList.size(); i++)
    {
        entityList[i]->draw();
    }
}

void entity_controller::update(float delta_time)
{
    for (int i = 0; i < entityList.size();)
    {
        if (entityList[i]->getIsSurvival())
        {
            entityList[i]->update(delta_time);
            i++;
        }
        else
        {
            delete entityList[i];
            entityList.erase(i);
        }
    }

    for (int i = 0; i < entityList.size(); ++i)
    {
        for (int j = i + 1; j < entityList.size(); ++j) // jはiの次から始めることで、重複したペアを避ける
        {
            // entityList[i] と entityList[j] の衝突判定を行う
            if (entityList[i]->intersects(entityList[j]))
            {
                // 衝突が検出された場合、関連するエンティティのOnTriggerEnter2Dメソッドを呼び出す。
                entityList[i]->OnTriggerEnter2D(entityList[j]);

                entityList[j]->OnCollisionEnter2D(entityList[i]);
            }
        }
    }
}
