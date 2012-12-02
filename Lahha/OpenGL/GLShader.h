#ifndef LAHHA_OPENGL_GLSHADER_H
#define LAHHA_OPENGL_GLSHADER_H

#include <glload\gl_3_3.h>
//#include <glload\gll.hpp>

#include <string>
#include <memory>

#include <boost\utility.hpp>

class GLShader : boost::noncopyable
{
public:
	typedef std::shared_ptr<GLShader> SharedPtrType;

protected:
	GLuint shaderID;
	GLenum shaderType;

	std::string shaderCodeFilename;
	std::string shaderCode;

	bool _good;

	bool _create(GLenum type);
	void _delete();
	bool _loadSource(const std::string & filename);
	bool _compile();

	bool _load(GLenum type, const std::string & filename);

public:
	GLShader(GLenum type, const std::string & filename);
	virtual ~GLShader(void);

	GLuint getShaderID() const;
	const std::string & getShaderCodeFilename() const;
	bool good() const;
};

#endif //LAHHA_OPENGL_GLSHADER_H