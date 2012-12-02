#define _CRT_SECURE_NO_WARNINGS

#include "GLMesh.h"

#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <GL\glfw.h>

GLMesh::GLMesh()
{
}

GLMesh::GLMesh(const GLMesh & v):
	vertices(v.vertices.begin(), v.vertices.end()),
	normals(v.normals.begin(), v.normals.end()),
	uvs(v.uvs.begin(), v.uvs.end())
{
}

GLMesh::~GLMesh(void)
{
	clearVBO();
	clear();
}

void GLMesh::updateVBO()
{//TODO :: error checks
	if(vertices.size() == 0)
	{
		clearVBO(); //clear previous buffers.
		return;
	}

	vbo.bufferAll(vertices, uvs, normals);
}

void GLMesh::clearVBO()
{
	vbo.clear();
}

GLVertexBuffer & GLMesh::getVBO()
{
	return vbo;
}

void GLMesh::clear()
{
	vertices.clear();
	uvs.clear();
	normals.clear();

	clearVBO();
}

bool GLMesh::loadOBJ(const std::string & path)
{
	std::cout << "Loading OBJ file " << path << std::endl;

	clear();

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE * file = fopen(path.c_str(), "r");
	if( file == NULL )
		throw std::runtime_error("Failed to open file : " + path);

	while( 1 ){
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				throw std::runtime_error("Failed to parse OBJ file : " + path);
				//printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				//return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		
		// Put the attributes in buffers
		vertices.push_back(vertex);
		uvs.push_back(uv);
		normals.push_back(normal);
	
	}

	updateVBO();

	return true;
}

void GLMesh::insertFace(const glm::vec3* vert, const glm::vec2* uv, const glm::vec3* norm)
{
	vertices.push_back(vert[0]);
	vertices.push_back(vert[1]);
	vertices.push_back(vert[2]);

	uvs.push_back(uv[0]);
	uvs.push_back(uv[1]);
	uvs.push_back(uv[2]);

	normals.push_back(norm[0]);
	normals.push_back(norm[1]);
	normals.push_back(norm[2]);
}

void GLMesh::insertMesh(const GLMesh & v)
{
	std::for_each(v.vertices.begin(), v.vertices.end(), [&](const glm::vec3& v){ vertices.push_back(v); });
	std::for_each(v.uvs.begin(), v.uvs.end(), [&](const glm::vec2& v){ uvs.push_back(v); });
	std::for_each(v.normals.begin(), v.normals.end(), [&](const glm::vec3& v){ normals.push_back(v); });
}
