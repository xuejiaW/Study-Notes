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
    Cubemap(int id);
    unsigned int GetID();
    unsigned int GetID() const;
    int GetWidth();
    int GetHeight();
    void SetWrap(int, int, int);
    void BindTexture();
    ~Cubemap();

private:
    vector<string> faceSources;
};