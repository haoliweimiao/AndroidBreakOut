/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <stb_image.h>
#include "LinkUtil.h"

// Instantiate static variables
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const ESContext *esContext, const GLchar *vShaderFile,
                                   const GLchar *fShaderFile, const std::string &name) {
    Shaders[name] = loadShaderFromFile(esContext, vShaderFile, fShaderFile);
    return Shaders[name];
}

Shader &ResourceManager::GetShader(const std::string &name) {
    return Shaders[name];
}

Texture2D
ResourceManager::LoadTexture(const ESContext *esContext, const GLchar *file, GLboolean alpha,
                             const std::string &name) {
    Textures[name] = loadTextureFromFile(esContext, file, alpha);
    return Textures[name];
}

Texture2D &ResourceManager::GetTexture(const std::string &name) {
    return Textures[name];
}

void ResourceManager::Clear() {
    // (Properly) delete all shaders
    for (const auto &iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (Properly) delete all textures
    for (const auto &iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const ESContext *esContext, const GLchar *vShaderFile,
                                           const GLchar *fShaderFile) {
    // 1. Retrieve the vertex/fragment source code from filePath

    char vShaderStr[1024 * 16] = {0};
    char fShaderStr[1024 * 16] = {0};
    readAssetsFile((AAssetManager *) esContext->assetManager, vShaderFile, vShaderStr);
    readAssetsFile((AAssetManager *) esContext->assetManager, fShaderFile, fShaderStr);
    esLogMessage("load vertex shader\n%s", vShaderStr);
    esLogMessage("load fragment shader\n%s", fShaderStr);

    // 2. Now create shader object from source code
    Shader shader;
    shader.Compile(vShaderStr, fShaderStr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const ESContext *esContext, const GLchar *file,
                                               GLboolean alpha) {
    // Create Texture object
    Texture2D texture;
    if (alpha) {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // tell stb_image.h not to flip loaded texture's on the y-axis.
    stbi_set_flip_vertically_on_load(
            false);

    // 打开 Asset 文件夹下的文件
    AAsset *pathAsset = AAssetManager_open((AAssetManager *) esContext->assetManager, file,
                                           AASSET_MODE_UNKNOWN);
    // 得到文件的长度
    off_t assetLength = AAsset_getLength(pathAsset);
    // 得到文件对应的 Buffer
    auto *fileData = (unsigned char *) AAsset_getBuffer(pathAsset);
    // stb_image 的方法，从内存中加载图片
    unsigned char *buffer = stbi_load_from_memory(fileData, assetLength, &width, &height,
                                                  &nrChannels, 0);

    if (buffer) {
        // Now generate texture
        texture.Generate(width, height, buffer);
    } else {
        esLogMessage("ERROR: Failed to load texture");
    }
    stbi_image_free(buffer);

    return texture;
}