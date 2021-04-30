#pragma once

#include <string>
using std::string;

class Texture
{
public:
    Texture();
    Texture(const char *path, bool sRGB = false);
    Texture(string path, bool sRGB = false);
    Texture(unsigned int tid, int width, int height);
    virtual unsigned int GetID();
    virtual unsigned int GetID() const;
    void SetWrap(int, int);
    virtual void BindTexture();
    virtual int GetWidth();
    virtual int GetHeight();
    virtual ~Texture();

protected:
    unsigned int id = 0;
    int width = 0;
    int height = 0;

private:
};
