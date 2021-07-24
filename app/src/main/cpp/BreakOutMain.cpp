#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <malloc.h>

#include "esUtil.h"
#include "Game.h"

typedef struct {
    Game mGame;
} UserData;

///
// Initialize the shader and program object
//
int Init(ESContext *esContext) {
    auto *userData = (UserData *) esContext->userData;
    userData->mGame.Init();
    return TRUE;
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw(ESContext *esContext) {
    auto *userData = (UserData *) esContext->userData;
    userData->mGame.Render();
}

void Shutdown(ESContext *esContext) {
    auto *userData = (UserData *) esContext->userData;
    userData->mGame.Destroy();
}

int esMain(ESContext *esContext) {
    esContext->userData = malloc(sizeof(UserData));

    esCreateWindow(esContext, "BreakOut", 320, 240, ES_WINDOW_RGB);

    auto *userData = (UserData *) esContext->userData;
    userData->mGame = Game(*esContext);

    if (!Init(esContext)) {
        return GL_FALSE;
    }

    esRegisterShutdownFunc(esContext, Shutdown);
    esRegisterDrawFunc(esContext, Draw);

    return GL_TRUE;
}
