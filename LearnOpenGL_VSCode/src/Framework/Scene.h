#pragma once

#include <string>
#ifndef __gl_h_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "Input.h"
#include "Debug.h"

using namespace std;

class GameObject;
class Camera;

class Scene
{
public:
    Scene(unsigned int screenWidth, unsigned int screenHeight, const char *windowName);
    ~Scene();
    virtual void Init();
    void MainLoop();
    void AddGameObject(GameObject *GO);
    GameObject *GetGameObject(string name);

    Camera *GetMainCamera();

    virtual void DrawFunc();
    float GetScreenRatio();
    unsigned int GetWidth();
    unsigned int GetHeight();
    float GetFrameTime();
    int GetFrameIndex();
    static Scene *GetInstance();
    void (*updateHandle)() = nullptr;
    void (*preRender)() = nullptr;
    void (*postRender)() = nullptr;

    bool renderingDepthMap = false;

private:
    int frameIndex = 0;
    static Scene *instance;
    Camera *mainCamera = nullptr;
    string windowName;
    unsigned int screenWidth;
    unsigned int screenHeight;
    GLFWwindow *window = nullptr;
    float frameDelta = 0.0f;

    vector<GameObject *> gameObjectsList;
};
