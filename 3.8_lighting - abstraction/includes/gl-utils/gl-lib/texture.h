#pragma once


class Texture
{
private:
    unsigned int _id;
    mutable unsigned int _slot;
    int _width, _height, _nrChannels;

public:
    Texture(const char* tx_path, GLenum tx_wrap_type = GL_REPEAT);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
};