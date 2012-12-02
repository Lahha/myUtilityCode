#include "GLShader.h"

#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>


GLShader::GLShader(GLenum type, const std::string & filename)
{
	shaderID = 0;
	shaderType = 0;
	_good = false;

	_load(type, filename);
}

GLShader::~GLShader(void) {
	_delete();
}

bool GLShader::_create(GLenum type)
{
	shaderID = glCreateShader(type);

	if(shaderID == 0 || shaderID == GL_INVALID_ENUM)
		return false;

	return true;
}

void GLShader::_delete()
{
	glDeleteShader(shaderID);

	shaderID = 0;
	shaderType = 0;
	_good = false;
}

bool GLShader::_loadSource(const std::string & filename)
{  
	shaderCodeFilename = filename;

	std::ifstream file(shaderCodeFilename, std::ios::in);

	if(!file.is_open())
		return false;

	std::string Line = "";
	while(getline(file, Line))
		shaderCode += "\n" + Line;
	
	file.close();

	return true;
}

bool GLShader::_compile()
{
	if(shaderCode.length() == 0)
		return false;

	// Compile Shader
	//Log::get().entry("Compiling shader : " + ShaderCodeFilename);
	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer , NULL);
	glCompileShader(shaderID);

	GLint result = GL_FALSE;
	
	// Check Shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

	if(result == GL_TRUE)
		return true;

	std::cout << "Error while compiling shader " << shaderCodeFilename << "." << std::endl;

	int InfoLogLength;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> shaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &shaderErrorMessage[0]);
	std::cout << &shaderErrorMessage[0] << std::endl;

	return false;
}

bool GLShader::_load(GLenum type, const std::string & filename)
{
	//Log::get().entry("Creating shader : " + filename);

	if(good())
		throw std::runtime_error(std::string("Shader already loaded into this object. \"") + filename + std::string("\"."));
	
	if(!_create(type))
		throw std::runtime_error(std::string("Failed to create shader \"") + filename + std::string("\"."));

	//std::stringstream ss;
	//ss << "Shader created. ID = " << ShaderID;
	//Log::get().entry(ss.str());
	
	if(!_loadSource(filename))
	{
		_delete();
		throw std::runtime_error(std::string("Failed to load shaderfile \"") + filename + std::string("\"."));
	}

	if(!_compile())
	{
		_delete();
		throw std::runtime_error(std::string("Failed to compile shaderfile \"") + filename + std::string("\"."));
	}
	
	shaderType = type;
	_good = true;

	return true;
}

GLuint GLShader::getShaderID() const
{
	return shaderID;
}

const std::string & GLShader::getShaderCodeFilename() const 
{
	return shaderCodeFilename;
}

bool GLShader::good() const
{
	return _good;
}