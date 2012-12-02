#include "GLVertexBuffer.h"

#include <iostream>

GLVertexBuffer::GLVertexBuffer()
{
	useIndexing = false;
	vertexCount = 0;
	indicesCount = 0;
}

GLVertexBuffer::GLVertexBuffer(bool _useIndexing = false)
{
	useIndexing = _useIndexing;
	vertexCount = 0;
	indicesCount = 0;
}

GLVertexBuffer::~GLVertexBuffer()
{
}

//TODO :: maybe make this into it's own class.
void GLVertexBuffer::enableVertexAttribArray(GLuint i, GLuint size, const GLBuffer& buffer) const
{
	glEnableVertexAttribArray(i);
	//gl::BindBuffer(gl::GL_ARRAY_BUFFER, buffer.get());
	buffer.bind(GL_ARRAY_BUFFER);
	glVertexAttribPointer(
		i,                  // attribute
		size,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
}

void GLVertexBuffer::draw() const
{	
	// 1st attribute buffer : vertices
	enableVertexAttribArray(0, 3, vertexbuffer);

	// 2nd attribute buffer : UVs
	enableVertexAttribArray(1, 2, uvbuffer);

	// 3rd attribute buffer : normals
	enableVertexAttribArray(2, 3, normalbuffer);

	int error = glGetError();

	if(error)
		return;
	//{
	//	std::stringstream ss;
	//	ss << "OpenGL error logged at " << __FILE__ << ":" << __LINE__ << " :: OpenGL error code " << error << ".";
	//	Log::get().entry(ss.str());
	//}

	if(useIndexing)
	{
		indexbuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT,  (void*)0 ); //TODO : IS THIS CORRECT ???
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);

		//wireframe
		//for(int i = 0; i < vertexCount; i += 3)
		//	gl::DrawArrays(gl::GL_LINE_LOOP, i, 3);
	}

	error = glGetError();

	if(error)
		return;
	//{
	//	std::stringstream ss;
	//	ss << "OpenGL error logged at " << __FILE__ << ":" << __LINE__ << " :: OpenGL error code " << error << ".";
	//	Log::get().entry(ss.str());
	//}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void GLVertexBuffer::enableIndexing(bool v)
{
	useIndexing = v;
}

void GLVertexBuffer::clear()
{
	//buffer empty vectors to clear existing buffers;
	bufferAll(std::vector<glm::vec3>(), std::vector<glm::vec2>(), std::vector<glm::vec3>(), std::vector<unsigned>());
}

void GLVertexBuffer::bufferVertices(const std::vector<glm::vec3>& v)
{
	vertexbuffer.data(GL_ARRAY_BUFFER, v, GL_STATIC_DRAW);
	vertexCount = v.size();
}

void GLVertexBuffer::bufferUVs(const std::vector<glm::vec2>& v)
{
	uvbuffer.data(GL_ARRAY_BUFFER, v, GL_STATIC_DRAW);
}

void GLVertexBuffer::bufferNormals(const std::vector<glm::vec3>& v)
{
	normalbuffer.data(GL_ARRAY_BUFFER, v, GL_STATIC_DRAW);
}

void GLVertexBuffer::bufferIndeces(const std::vector<unsigned>& v)
{
	indexbuffer.data(GL_ELEMENT_ARRAY_BUFFER, v, GL_STATIC_DRAW);
	indicesCount = v.size();
}

void GLVertexBuffer::bufferAll(const std::vector<glm::vec3>& v, const std::vector<glm::vec2>& u, const std::vector<glm::vec3>& n)
{
	bufferVertices(v);
	bufferUVs(u);
	bufferNormals(n);
}

void GLVertexBuffer::bufferAll(const std::vector<glm::vec3>& v, const std::vector<glm::vec2>& u, const std::vector<glm::vec3>& n, const std::vector<unsigned>& i)
{
	bufferAll(v, u, n);
	bufferIndeces(i);
}

void GLVertexBuffer::print_debug() const
{
	std::cout << "VBO DEBUG PRINT" << std::endl;

	std::cout << "useIndexing = " << useIndexing << std::endl;
	std::cout << "vertexCount = " << vertexCount << std::endl;
	std::cout << "indicesCount = " << indicesCount << std::endl;
}