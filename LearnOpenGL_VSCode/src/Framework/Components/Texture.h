#pragma once

#include "Component.h"

class Texture : public Component
{
public:
    Texture(string);
    unsigned int GetID();
    int GetWidth();
    int GetHeight();
    ~Texture();

private:
    unsigned int id = 0;
    int width = 0;
    int height = 0;
};
