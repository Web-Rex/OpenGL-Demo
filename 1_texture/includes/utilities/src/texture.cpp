#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../include/texture.h"
#include <iostream>


Texture::Texture(const char* tx_path, GLenum tx_wrap_type, GLenum tx_color_type)
{
    stbi_set_flip_vertically_on_load(1);
    unsigned char *data = stbi_load(tx_path, &_width, &_height, &_nrChannels, 0);
    if (!data)
    {
        std::cout << "Failed to load texture" << std::endl;
        return;
    }

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    // [...] set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tx_wrap_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tx_wrap_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, tx_color_type, _width, _height, 0, tx_color_type, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    if (data)
        stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_id);
}


void Texture::Bind(unsigned int slot) const
{
    _slot = slot;

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}