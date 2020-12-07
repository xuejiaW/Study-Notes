#pragma once

#include <string>
using std::string;

class Texture
{
public:
    Texture();
    Texture(string, bool = false);
    Texture(unsigned int, int, int);
    virtual unsigned int GetID();
    virtual unsigned int GetID() const;
    void SetWrap(int, int);
    virtual int GetWidth();
    virtual int GetHeight();
    virtual ~Texture();

protected:
    unsigned int id = 0;
    int width = 0;
    int height = 0;

private:
};
