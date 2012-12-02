#include "GLProgram.h"

#include <vector>

GLProgram::GLProgram(const GLShader& vertexShader, const GLShader& fragmentShader)
{
	programID = 0;
	_good = false;

	if(!_create())
		throw std::runtime_error("Failed to create shader program.");

	try {
		if(!_attach(vertexShader))
			throw std::runtime_error("Failed to attach vertex shader. "  + errorMsg);
	
		if(!_attach(fragmentShader))
			throw std::runtime_error("Failed to attach fragment shader. " + errorMsg);

		if(!_link())
			throw std::runtime_error("Failed to link shader program (" + vertexShader.getShaderCodeFilename() + ", " + fragmentShader.getShaderCodeFilename()  + ").\n" + errorMsg);

	} catch (std::exception &e) {
		_delete();
		throw e;
	}

	_good = true;
}

GLProgram::~GLProgram(void)
{
	_delete();
}

bool GLProgram::_create()
{
	programID = glCreateProgram();

	if(programID == 0)
		return false;

	return true;
}

void GLProgram::_delete()
{
	glDeleteProgram(programID);
	programID = 0;
	_good = false;
}

bool GLProgram::_attach(const GLShader& shader)
{
	if(programID == 0 || !shader.good())
	{
		errorMsg = "Pre-check failed.";
		return false;
	}

	glAttachShader(programID, shader.getShaderID());

	GLuint error = glGetError();

	if(error == GL_NO_ERROR)
		return true;
		
	switch(error)
	{
	case GL_INVALID_VALUE:
		errorMsg = "GL_INVALID_VALUE";
		break;

	case GL_INVALID_OPERATION:
		errorMsg = "GL_INVALID_OPERATION";
		break;

	default:
		errorMsg = "UNEXPECTED ERROR CODE";
	}

	return false;
}

bool GLProgram::_link()
{
	glLinkProgram(programID);

	GLint result = GL_FALSE;
	int InfoLogLength;

	glGetProgramiv(programID, GL_LINK_STATUS, &result);

	if(result == GL_TRUE)
		return true;

	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	std::vector<char> ProgramErrorMessage( std::max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);

	errorMsg = &ProgramErrorMessage[0];

	return false;
}

GLuint GLProgram::getProgramID() const
{
	return programID;
}

void GLProgram::use() const
{
	if(good())
		glUseProgram(programID);
}

bool GLProgram::good() const
{
	return programID != 0 && _good;
}

GLuint GLProgram::getUniformLocation(const std::string & name) const
{
	return glGetUniformLocation(programID, name.c_str());
}