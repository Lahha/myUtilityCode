#ifndef LAHHA_OPENGL_GLVERTEXBUFFER_H
#define LAHHA_OPENGL_GLVERTEXBUFFER_H

#include <glload\gl_3_3.h>
//#include <glload\gll.h>

#include <glm\glm.hpp>

#include "GLBuffer.h"

class GLVertexBuffer
{
protected:
	GLBuffer vertexbuffer;
	GLBuffer uvbuffer;
	GLBuffer normalbuffer;
	GLBuffer indexbuffer;

	int vertexCount;
	int indicesCount;

	bool useIndexing;

	void enableVertexAttribArray(GLuint i, GLuint size, const GLBuffer& buffer) const;

public:
	GLVertexBuffer();
	GLVertexBuffer(bool useIndexing);
	virtual ~GLVertexBuffer(void);

	void draw() const; // TODO !! THIS DOES NOT BELONG HERE !!

	void enableIndexing(bool v);

	void clear();

	void bufferVertices(const std::vector<glm::vec3>& v);
	void bufferUVs(const std::vector<glm::vec2>& v);
	void bufferNormals(const std::vector<glm::vec3>& v);
	void bufferIndeces(const std::vector<unsigned>& v);
	void bufferAll(const std::vector<glm::vec3>& v, const std::vector<glm::vec2>& u, const std::vector<glm::vec3>& n);
	void bufferAll(const std::vector<glm::vec3>& v, const std::vector<glm::vec2>& u, const std::vector<glm::vec3>& n, const std::vector<unsigned>& i);

	void print_debug() const;
};

#endif //LAHHA_OPENGL_GLVERTEXBUFFER_H