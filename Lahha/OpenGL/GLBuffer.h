#ifndef LAHHA_OPENGL_GLBUFFER_H
#define LAHHA_OPENGL_GLBUFFER_H

#include <vector>

#include <glload\gl_3_3.h>
//#include <glload\gll.hpp>

#include <boost\utility.hpp>

class GLBuffer : boost::noncopyable
{
	GLuint buffer;

public:
	GLBuffer();
	virtual ~GLBuffer();

	void generateBuffer();
	void deleteBuffer();

	GLuint get() const;
	bool good() const;

	bool bind(GLenum target) const;

	template<typename T>
	bool data(GLenum target, const std::vector<T>& data, GLenum usage)
	{
		unsigned size = data.size() * sizeof(T);

		bind(target);

		if(good())
		{
			if(size == 0)
				glBufferData(target, size, (void*)0, usage);
			else
				glBufferData(target, size, &data[0], usage);
		}
		else
			 return false;

		return true;
	}
};

#endif //LAHHA_OPENGL_GLBUFFER_H