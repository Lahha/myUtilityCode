#ifndef LAHHA_OPENGL_GLMESH_H
#define LAHHA_OPENGL_GLMESH_H

#include <vector>
#include <string>

#include <glload\gl_3_3.h>
//#include <glload\gll.hpp>

#include <glm\glm.hpp>

#include "GLVertexBuffer.h"

class GLMesh
{
public:
	typedef std::shared_ptr<GLMesh> SharedPtrType;

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	/*GLBuffer vertexbuffer;
	GLBuffer uvbuffer;
	GLBuffer normalbuffer;*/

	GLVertexBuffer vbo;

public:
	GLMesh();
	GLMesh(const GLMesh & v);
	virtual ~GLMesh(void);

	void updateVBO();
	void clearVBO();
	GLVertexBuffer & getVBO();

	void clear();
	bool loadOBJ(const std::string & filename);

	void insertFace(const glm::vec3* vert, const glm::vec2* uv, const glm::vec3* norm);
	void insertMesh(const GLMesh & v);
};

#endif //LAHHA_OPENGL_GLMESH_H