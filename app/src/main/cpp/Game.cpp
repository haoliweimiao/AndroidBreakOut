//
// Created by Von on 2021/7/24.
//

#include "Game.h"
#include "Config.h"

Game::Game(ESContext esContext)
        : State(GAME_ACTIVE), Keys(), Context(esContext), Width(esContext.width),
          Height(esContext.height) {
}

Game::~Game() {

}

void Game::Init() {
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ResourceManager::LoadShader(&this->Context, "demo_triangle_vertex.glsl",
                                "demo_triangle_fragment.glsl", PROGRAM_NAME_TEST);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void Game::Update(GLfloat dt) {

}


void Game::ProcessInput(GLfloat dt) {

}

void Game::Render() {
    GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                           0.5f, -0.5f, 0.0f
    };

    // Set the viewport
    glViewport(0, 0, Width, Height);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    GLint programObject = ResourceManager::GetShader(PROGRAM_NAME_TEST).ID;
    // Use the program object
    glUseProgram(programObject);

    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Game::Destroy() {
    ResourceManager::Clear();
}