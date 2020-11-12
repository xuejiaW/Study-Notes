#pragma once

#include "Texture.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class Cubemap : public Texture
{
public:
    Cubemap(vector<string> facesSources);
    unsigned int GetID();
    unsigned int GetID() const;
    int GetWidth();
    int GetHeight();
    void SetWrap(int, int, int);
    ~Cubemap();

private:
    vector<string> faceSources;

    // unsigned int id = 0;
    // int width = 0;
    // int height = 0;
};