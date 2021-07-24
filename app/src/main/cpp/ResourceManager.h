//
// @description: resoure manager class
// @author: von.wu
// @date: 2021-07-03 21:57:14
//

#ifndef RESUOURCE_MANAGER_H
#define RESUOURCE_MANAGER_H
// include something
#include <map>
#include <string>

#include "esUtil.h"
#include "Texture.h"
#include "ShaderManager.h"

#ifdef __cplusplus
extern "C"
{
#endif
// your code

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no
// public constructor is defined.
class ResourceManager {
public:
    ESContext mESContext;
    // Resource storage
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures;

    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader
    LoadShader(const ESContext *esContext,
               const GLchar *vShaderFile, const GLchar *fShaderFile,
               const std::string& name);

    // Retrieves a stored sader
    static Shader &GetShader(const std::string& name);

    // Loads (and generates) a texture from file
    static Texture2D LoadTexture(const ESContext *esContext, const GLchar *file, GLboolean alpha, const std::string& name);

    // Retrieves a stored texture
    static Texture2D &GetTexture(const std::string& name);

    // Properly de-allocates all loaded resources
    static void Clear();

private:
    // Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() {}

    // Loads and generates a shader from file
    static Shader loadShaderFromFile(const ESContext *esContext, const GLchar *vShaderFile, const GLchar *fShaderFile);

    // Loads a single texture from file
    static Texture2D loadTextureFromFile(const ESContext *esContext, const GLchar *file, GLboolean alpha);
};
#ifdef __cplusplus
}
#endif
#endif // RESUOURCE_MANAGER_H