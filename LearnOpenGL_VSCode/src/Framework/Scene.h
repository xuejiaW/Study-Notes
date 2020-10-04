#pragma once

#include <string>
#ifndef __gl_h_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "Input.h"

using namespace std;

class GameObject;
class Camera;

class Scene
{
public:
    Scene(unsigned int screenWidth, unsigned int screenHeight, const char *windowName);
    ~Scene();
    void Init();
    void MainLoop();
    void AddGameObject(GameObject *GO);
    GameObject *GetGameObject(string name);

    Camera *GetMainCamera();

    virtual void
    DrawFunc();
    float GetScreenRatio();
    float GetFrameTime();
    static Scene *GetInstance();

private:
    static Scene *instance;
    Camera *mainCamera = nullptr;
    string windowName;
    unsigned int screenWidth;
    unsigned int screenHeight;
    GLFWwindow *window = nullptr;
    float frameDelta = 0.0f;

    vector<GameObject *> gameObjectsList;
};
