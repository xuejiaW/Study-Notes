#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"
#include "../SHADER.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
static int windowWidth = 960;
static int windowHeight = 540;

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST); //to enable depth test
    GLfloat vertices[] = {
        // front face
        -0.5f, -0.5f, -0.5f, 0, 0,
        +0.5f, -0.5f, -0.5f, 1, 0,
        +0.5f, +0.5f, -0.5f, 1, 1,
        -0.5f, +0.5f, -0.5f, 0, 1,

        // back face
        +0.5f, -0.5f, +0.5f, 0, 0,
        -0.5f, -0.5f, +0.5f, 1, 0,
        -0.5f, +0.5f, +0.5f, 1, 1,
        +0.5f, +0.5f, +0.5f, 0, 1,

        // right face
        +0.5f, -0.5f, -0.5f, 0, 0,
        +0.5f, -0.5f, +0.5f, 1, 0,
        +0.5f, +0.5f, +0.5f, 1, 1,
        +0.5f, +0.5f, -0.5f, 0, 1,

        // left face
        -0.5f, -0.5f, +0.5f, 0, 0,
        -0.5f, -0.5f, -0.5f, 1, 0,
        -0.5f, +0.5f, -0.5f, 1, 1,
        -0.5f, +0.5f, +0.5f, 0, 1,

        // top face
        -0.5f, +0.5f, -0.5f, 0, 0,
        +0.5f, +0.5f, -0.5f, 1, 0,
        +0.5f, +0.5f, +0.5f, 1, 1,
        -0.5f, +0.5f, +0.5f, 0, 1,

        // bottom face
        -0.5f, -0.5f, +0.5f, 0, 0,
        +0.5f, -0.5f, +0.5f, 1, 0,
        +0.5f, -0.5f, -0.5f, 1, 1,
        -0.5f, -0.5f, -0.5f, 0, 1};

    GLuint index[] =
        {
            0, 1, 2,
            0, 2, 3,
            4, 5, 6,
            4, 6, 7,
            8, 9, 10,
            8, 10, 11,
            12, 13, 14,
            12, 14, 15,
            16, 17, 18,
            16, 18, 19,
            20, 21, 22,
            20, 22, 23};
    GLuint VAO, VBO, EBO;

    // Generate buffer
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind buffer and load data
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    // Unbind buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid *)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    Shader shader("Vertex.vert", "Fragment.frag");
    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *image = stbi_load("../container.jpg", &width, &height, &nrChannels, 0);
    GLuint format = nrChannels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);

    shader.Use();

    // Camera pos
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);

    // Camera rotation
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0, 1.0f);

    GLfloat pitch =0.0f; // toward up
    GLfloat yaw = 90.0f;  // to the -z axis
    cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront.y = sin(glm::radians(pitch));
    cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(cameraFront);

    glm::vec3 cameraUp = glm::vec3(0, 1, 0);
    GLfloat roll =  90.0f; // to +y axis
    cameraUp.x = cos(glm::radians(roll));
    cameraUp.y = sin(glm::radians(roll));
    cameraUp = glm::normalize(cameraUp);

    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 projection;
    glfwGetFramebufferSize(window, &width, &height);
    projection = glm::perspective(glm::radians(45.0f), (GLfloat)width / height,0.1f,100.0f);

    glm::mat4 trans, xRot, yRot, zRot;

    trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
    xRot = glm::rotate(xRot, glm::radians(30.0f), glm::vec3(1, 0, 0));
    yRot = glm::rotate(yRot, glm::radians(30.0f), glm::vec3(0, 1, 0));
    zRot = glm::rotate(zRot, glm::radians(30.0f), glm::vec3(0, 0, 1));
    trans *= yRot;
    trans *= xRot;
    trans *= zRot;
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glActiveTexture(GL_TEXTURE0);                                       // active 0(id) texture sampler
    glUniform1i(glGetUniformLocation(shader.Program, "ourTexture"), 0); // bind outTexture to 0(id) texture sampler

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.0f, 0.f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();

    return 0;
}

