#include <algorithm>
#include "Scene.h"
#include "./GameObjects/GameObject.h"
#include "./Components/Camera.h"

void HandleMouseButton(GLFWwindow *window, int button, int action, int modes);
void HandleKey(GLFWwindow *window, int key, int scanCode, int action, int mods);
void HandleCursorPos(GLFWwindow *window, double xPos, double yPos);

Scene *Scene::instance = nullptr;
float lastFrameTime = 0.0f;
float currentFrameTime = 0.0f;

Scene *Scene::GetInstance()
{
    if (!instance)
        instance = new Scene(800, 600, "instance");
    return instance;
}

Scene::Scene(unsigned int width, unsigned int height, const char *name)
    : screenWidth(width), screenHeight(height), windowName(name)
{
    instance = this;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screenWidth, screenHeight, windowName.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetMouseButtonCallback(window, HandleMouseButton);
    glfwSetKeyCallback(window, HandleKey);
    glfwSetCursorPosCallback(window, HandleCursorPos);

    Init();
}

void Scene::Init()
{
    glEnable(GL_DEPTH_TEST);
}

void Scene::MainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); // Receive input message
        if (Input::GetInstance()->GetKeyDown(GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, true);

        currentFrameTime = glfwGetTime();
        frameDelta = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        DrawFunc();

        glfwSwapBuffers(window);
        Input::GetInstance()->ClearInputState();

        frameIndex++;
    }
}

void Scene::AddGameObject(GameObject *GO)
{
    gameObjectsList.push_back(GO);
}

GameObject *Scene::GetGameObject(string name)
{
    vector<GameObject *>::iterator result = find_if(gameObjectsList.begin(), gameObjectsList.end(),
                                                    [name](GameObject *GO) { return GO->name == name; });
    return result == gameObjectsList.end() ? nullptr : *result;
}

Camera *Scene::GetMainCamera()
{
    if (!mainCamera)
    {
        GameObject *cameraGO = GetGameObject("GO_Camera");
        if (cameraGO)
        {
            mainCamera = dynamic_cast<Camera *>(cameraGO->GetComponent("Camera"));
        }
        else
            cout << "There is no cameraGO" << endl;
    }

    return mainCamera ? mainCamera : nullptr;
}

void Scene::DrawFunc()
{
    for (GameObject *go : gameObjectsList)
        go->Update();
    if (updateHandle)
        updateHandle();
}

float Scene::GetScreenRatio()
{
    return screenWidth * 1.0f / screenHeight;
}

float Scene::GetFrameTime()
{
    return frameDelta;
}

int Scene::GetFrameIndex()
{
    return frameIndex;
}

Scene::~Scene()
{
    delete window;
}

void HandleKey(GLFWwindow *window, int key, int scanCode, int action, int mods)
{
    Input::GetInstance()->HandleKey(key, scanCode, action, mods);
}

void HandleMouseButton(GLFWwindow *window, int button, int action, int modes)
{
    Input::GetInstance()->HandleMouseButton(button, action, modes);
}

void HandleCursorPos(GLFWwindow *window, double xPos, double yPos)
{
    Input::GetInstance()->HandleCursorPos(xPos, yPos);
}