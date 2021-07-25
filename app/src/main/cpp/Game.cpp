//
// Created by Von on 2021/7/24.
//

#include "Game.hpp"
#include "Config.h"
#include "SpriteRenderer.h"

SpriteRenderer *Renderer;

Game::Game(ESContext esContext)
        : State(GAME_ACTIVE), Keys(), Context(esContext), Width(esContext.width),
          Height(esContext.height) {
//    Levels = std::vector<std::string>{};
}

Game::~Game() {

}

void Game::Init() {
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ESContext *esContext = &this->Context;

    // 加载着色器
    ResourceManager::LoadShader(esContext,
                                "glsl/sprite.vert",
                                "glsl/sprite.frag",
                                PROGRAM_NAME_SPRITE);

    Shader spriteShader = ResourceManager::GetShader(PROGRAM_NAME_SPRITE);
    // 配置着色器
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
                                      static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    spriteShader.Use().SetInteger(SPRITE_UNIFORM_NAME_IMAGE, 0);
    spriteShader.SetMatrix4(SPRITE_UNIFORM_NAME_PROJECTION, projection);
    // 设置专用于渲染的控制
    Renderer = new SpriteRenderer(spriteShader);

    // 加载纹理
    ResourceManager::LoadTexture(esContext, "textures/background.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture(esContext, "textures/awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture(esContext, "textures/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture(esContext, "textures/block_solid.png", GL_FALSE, "block_solid");
    // 加载关卡
    GameLevel one;
    one.Load(esContext, "levels/one.lvl", this->Width, this->Height * 0.5);
    GameLevel two;
    two.Load(esContext, "levels/two.lvl", this->Width, this->Height * 0.5);
    GameLevel three;
    three.Load(esContext, "levels/three.lvl", this->Width, this->Height * 0.5);
    GameLevel four;
    four.Load(esContext, "levels/four.lvl", this->Width, this->Height * 0.5);
//    this->Levels.push_back(one);
//    this->Levels.push_back(two);
//    this->Levels.push_back(three);
//    this->Levels.push_back(four);
    this->Level = 1;

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void Game::Update(GLfloat dt) {

}


void Game::ProcessInput(GLfloat dt) {

}

void Game::Render() {
    Renderer->DrawSprite(ResourceManager::GetTexture("background"),
                         glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f,
                         glm::vec3(0.0f, 1.0f, 0.0f));
}