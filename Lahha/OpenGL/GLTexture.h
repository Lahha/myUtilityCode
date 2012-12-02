#ifndef LAHHA_OPENGL_GLTEXTURE_H
#define LAHHA_OPENGL_GLTEXTURE_H

#include <string>
#include <memory>

#include <glload\gl_3_3.h>
//#include <SDL\SDL.h>

class GLTexture
{
public:
	typedef std::shared_ptr<GLTexture> SharedPtrType; 

private:
	GLuint textureID;

	bool generateTexture();
public:
	GLTexture(void);
	GLTexture(const std::string& file);
	//GLTexture(SDL_Surface * surface);
	virtual ~GLTexture(void);

	bool good() const;

	bool load(const std::string& file);
	bool loadTGA(const std::string& file);
	bool loadBMP(const std::string& file);
	bool loadDDS(const std::string& file);
	//bool loadSDL(SDL_Surface * surface);

	void unload();

	GLuint getTextureID() const;

	void useTrilinearFiltering() const;
	void useSimpleFiltering() const;
};

#endif //LAHHA_OPENGL_GLTEXTURE_H