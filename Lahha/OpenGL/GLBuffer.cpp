#include "GLBuffer.h"

GLBuffer::GLBuffer()
{
	buffer = 0;
	generateBuffer();
}

GLBuffer::~GLBuffer()
{
	deleteBuffer();
}

void GLBuffer::generateBuffer()
{
	deleteBuffer();
	glGenBuffers(1, &buffer);
}

void GLBuffer::deleteBuffer()
{
	if(buffer != 0)
		glDeleteBuffers(1, &buffer);
}

GLuint GLBuffer::get() const
{
	return buffer;
}

bool GLBuffer::good() const
{
	return buffer != 0;
}

bool GLBuffer::bind(GLenum target) const
{
	if(good())
		glBindBuffer(target, buffer);
	else
		return false;

	return true;
}