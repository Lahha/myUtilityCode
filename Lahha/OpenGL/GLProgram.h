#ifndef LAHHA_OPENGL_GLPROGRAM_H
#define LAHHA_OPENGL_GLPROGRAM_H

#include "GLShader.h"

#include <boost\utility.hpp>

class GLProgram : boost::noncopyable
{
public:
	typedef std::shared_ptr<GLProgram> SharedPtrType;

private:
	GLuint programID;
	bool _good;
	std::string errorMsg;

	bool _create();
	void _delete();
	bool _attach(const GLShader& shader);
	bool _link();

public:
	GLProgram(const GLShader& vertexShader, const GLShader& fragmentShader);
	virtual ~GLProgram(void);

	bool good() const;

	GLuint getProgramID() const;
	void use() const;

	GLuint getUniformLocation(const std::string & name) const;
};

#endif //LAHHA_OPENGL_GLPROGRAM_H