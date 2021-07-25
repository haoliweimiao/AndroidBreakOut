#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <malloc.h>
#include <string>
#include <vector>

#include "esUtil.h"
#include "Game.hpp"

typedef struct {
    Game mGame;
} UserData;

///
// Initialize the shader and program object
//
int Init(ESContext *esContext) {
    auto *userData = (UserData *) esContext->userData;
    userData->mGame.Init();

    // Start Game within Menu State
    userData->mGame.State = GAME_ACTIVE;
    return TRUE;
}

void Update(ESContext *esContext, float deltaTime) {
    auto *userData = (UserData *) esContext->userData;
    userData->mGame.ProcessInput(deltaTime);
    userData->mGame.Update(deltaTime);
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw(ESContext *esContext) {
    auto *userData = (UserData *) esContext->userData;
    std::string test = "fuck google";
    esLogMessage("draw %s", test.c_str());
    std::vector<char> fuckGoogle;
    userData->mGame.Render();
}

void Key(ESContext *esContext, unsigned char key, int action, int flags) {
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == AKEYCODE_ESCAPE && action == AKEY_EVENT_ACTION_DOWN) {
        system(0);
    }
    if (key >= 0 && key < 1024) {
        auto *userData = (UserData *) esContext->userData;
        if (action == AKEY_EVENT_ACTION_DOWN)
            userData->mGame.Keys[key] = GL_TRUE;
        else if (action == AKEY_EVENT_ACTION_UP)
            userData->mGame.Keys[key] = GL_FALSE;
    }
}

void Shutdown(ESContext *esContext) {
    auto *userData = (UserData *) esContext->userData;
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
    esRegisterUpdateFunc(esContext, Update);
    esRegisterKeyFunc(esContext, Key);

    return GL_TRUE;
}
