#include "Crossant/feature/graphics/3d/texture.hpp"
#include <Windows.h>
#include <gl/GL.h>

using namespace Crossant::Graphics::Graphics3D;

static unsigned GenTextureID() {
	unsigned id;
	glGenTextures(1, &id);
	return id;
}

Texture::Texture(Image const &image) :
	image(image), id(GenTextureID()) {
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.size[0], image.size[1], 0, GL_RGBA, GL_FLOAT, image.pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::Apply() const {
}