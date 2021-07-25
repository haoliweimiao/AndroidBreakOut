/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "GameLevel.hpp"

#include <fstream>
#include <sstream>

GameLevel::GameLevel() {}

GameLevel::~GameLevel() {}

std::vector<std::string> vStringSplit(const std::string &s, const std::string &delim = ",") {
    std::vector<std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0) return elems;
    while (pos < len) {
        int find_pos = s.find(delim, pos);
        if (find_pos < 0) {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}

//字符串分割函数
std::vector<std::string> split(std::string str, std::string pattern) {
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;//扩展字符串以方便操作
    int size = str.size();
    for (int i = 0; i < size; i++) {
        pos = str.find(pattern, i);
        if (pos < size) {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

void GameLevel::Load(const ESContext *esContext, const GLchar *file, GLuint levelWidth,
                     GLuint levelHeight) {
    // Clear old data
    this->Bricks.clear();
    // Load from file
    GLuint tileCode;
    GameLevel level;
    std::string line;

    // todo : this method not work to read assets file
    auto *assetManager = (AAssetManager *) esContext->assetManager;

    char fileContext[1024 * 16] = {0};
    readAssetsFile(assetManager, file, fileContext);

    std::vector<std::string> lines = split(fileContext, "\n");
    std::vector<std::vector<GLuint>> tileData;

    for (auto iter = lines.begin(); iter != lines.end(); iter++) {
        std::vector<std::string> count = split(iter->c_str(), " ");
        std::vector<GLuint> row;
        for (auto iterCount = count.begin(); iterCount != count.end(); iterCount++) {
            char readSingle = iterCount->c_str()[0];
            if (readSingle >= '0' && readSingle <= '9') {
                row.push_back(readSingle);
            }
        }
        tileData.push_back(row);
    }
    if (tileData.size() > 0)
        this->init(tileData, levelWidth, levelHeight);
}

void GameLevel::Draw(SpriteRenderer &renderer) {
    for (GameObject &tile : this->Bricks)
        if (!tile.Destroyed)
            tile.Draw(renderer);
}

GLboolean GameLevel::IsCompleted() {
    for (GameObject &tile : this->Bricks)
        if (!tile.IsSolid && !tile.Destroyed)
            return GL_FALSE;
    return GL_TRUE;
}

void
GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight) {
    // Calculate dimensions
    GLuint height = tileData.size();
    GLuint width = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
    GLfloat unit_width = levelWidth / static_cast<GLfloat>(width), unit_height =
            levelHeight / height;
    // Initialize level tiles based on tileData
    for (GLuint y = 0; y < height; ++y) {
        for (GLuint x = 0; x < width; ++x) {
            // Check block type from level data (2D level array)
            if (tileData[y][x] == 1) // Solid
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"),
                               glm::vec3(0.8f, 0.8f, 0.7f));
                obj.IsSolid = GL_TRUE;
                this->Bricks.push_back(obj);
            } else if (tileData[y][x] > 1) // Non-solid; now determine its color based on level data
            {
                glm::vec3 color = glm::vec3(1.0f); // original: white
                if (tileData[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                this->Bricks.push_back(
                        GameObject(pos, size, ResourceManager::GetTexture("block"), color));
            }
        }
    }
}