//
// Created by Von on 2021/7/24.
//

#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include "esUtil.h"
#include "ResourceManager.h"
#include "ShaderManager.h"
#include "Texture.h"

// 代表了游戏的当前状态
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game {
public:
    // 游戏状态
    GameState State;
    GLboolean Keys[1024];
    ESContext Context;
    GLuint Width, Height;

    // 构造函数/析构函数
    Game(ESContext esContext);

    ~Game();

    // 初始化游戏状态（加载所有的着色器/纹理/关卡）
    void Init();

    // 游戏循环
    void ProcessInput(GLfloat dt);

    void Update(GLfloat dt);

    void Render();

    void Destroy();
};


#endif //BREAKOUT_GAME_H
