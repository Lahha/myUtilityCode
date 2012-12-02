#define _CRT_SECURE_NO_WARNINGS

#include "GLTexture.h"

#include <algorithm>
#include <iostream>

#include <GL\glfw.h>

GLTexture::GLTexture(void)
{
	textureID = 0;
}

GLTexture::GLTexture(const std::string& file)
{
	textureID = 0;
	load(file);
}

//GLTexture::GLTexture(SDL_Surface * surface)
//{
//	textureID = 0;
//	loadSDL(surface);
//}

GLTexture::~GLTexture(void)
{
	unload();
}

bool GLTexture::generateTexture()
{
	unload();
	glGenTextures(1, &textureID);

	if(textureID == 0)
	{
		GLenum error = glGetError();
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, textureID);

	return true;
}

bool GLTexture::good() const
{
	return (textureID != 0);
}

bool GLTexture::load(const std::string& file)
{
	int pos = file.find_last_of('.');

	std::string extension = file.substr(pos + 1, std::string::npos);
	std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

	if(extension == "dds")
		return loadDDS(file);
	else if(extension == "tga")
		return loadTGA(file);
	else if(extension == "bmp")
		return loadBMP(file);

	std::cout << "Can't load \"" << file << "\". Format not supported." << std::endl;

	return false;
}

bool GLTexture::loadTGA(const std::string& file)
{
	//Log::get().entry("Loading TGA texture : " + file);

	if(!generateTexture())
		return false;

	if(glfwLoadTexture2D(file.c_str(), 0) == GL_FALSE)
	{
		unload();
		//Log::get().entry("glfwLoadTexture2D() failed.");
		return false;
	}

	useTrilinearFiltering(); 

	return true;
}

bool GLTexture::loadBMP(const std::string& file)
{
	//Log::get().entry("Loading BMP texture : " + file);

	if(!generateTexture())
		return false;

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * imagefile = fopen(file.c_str(),"rb");
	if (imagefile == NULL)
	{
		unload();
		//Log::get().entry("Could not open image.");
		return false;
	}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 byes are read, problem
	if ( fread(header, 1, 54, imagefile)!=54 ) { unload(); fclose(imagefile); return false; }
	// A BMP files always begins with "BM"
	if ( header[0]!='B' || header[1]!='M' ) { unload(); fclose(imagefile); return false; }
	// Make sure this is a 24bpp file
	if ( *(int*)&(header[0x1E])!=0  ) { unload(); fclose(imagefile); return false;}
	if ( *(int*)&(header[0x1C])!=24 ) { unload(); fclose(imagefile); return false;}

	// Read the information about the image
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize, imagefile);

	// Everything is in memory now, the file wan be closed
	fclose (imagefile);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	useTrilinearFiltering(); 

	return true;
}

bool GLTexture::loadDDS(const std::string& file)
{
	std::cout << "DDS loader not implemented yet.";
	return false;

	//useTrilinearFiltering(); 
	//return true;
}

//bool GLTexture::loadSDL(SDL_Surface * surface)
//{
//	GLenum errorCode;
//
//	if ( !surface ) 
//		return false;
//
//	if ( surface->format->BytesPerPixel < 2 )
//		return false;
//
//	if(!generateTexture())
//		return false;
//
//	int w = surface->w;
//	int h = surface->h;
//	int bpp = surface->format->BytesPerPixel;
//
//	 void *raw = (void *) new __int32[w * h];
//	 Uint8 *dstPixel = (Uint8 *)raw;
//
//	 SDL_LockSurface(surface);
//
//	 for (int i = h ; i > 0 ; i-- ) 
//	 {
//		for (int j = 0 ; j < w ; j++ ) 
//		{
//			Uint8 * srcPixel = (Uint8 *)surface->pixels + i * surface->pitch + j * bpp;
//
//			Uint32 truePixel;
//
//			switch (bpp) 
//			{
//			case 1:
//				truePixel = *srcPixel;
//				break;
//
//			case 2:
//				truePixel = *(Uint16 *)srcPixel;
//				break;
//
//			case 3:
//				if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
//					truePixel = srcPixel[0] << 16 | srcPixel[1] << 8 | srcPixel[2];
//				else
//					truePixel = srcPixel[0] | srcPixel[1] << 8 | srcPixel[2] << 16;
//				break;
//
//			case 4:
//				truePixel = *(Uint32 *)srcPixel;
//				break;
//
//			default:
//				printf("Image bpp of %d unusable\n", bpp);
//				return 0;
//				break;
//			}
//
//			 SDL_GetRGBA( truePixel, surface->format, &(dstPixel[0]), &(dstPixel[1]), &(dstPixel[2]), &(dstPixel[3]));
//			 dstPixel++;
//			 dstPixel++;
//			 dstPixel++;
//			 dstPixel++;
//		 }
//	 }
//
//	SDL_UnlockSurface(surface);
//
//	while ( gl::GetError() ) { ; }
//
//	gl::TexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR_MIPMAP_LINEAR );
//	gl::TexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR );
//
//	errorCode = gl::GetError();
//	if ( errorCode != 0 ) 
//	{
//		delete [] raw;
//
//		if ( errorCode == gl::GL_OUT_OF_MEMORY )
//			throw std::exception("LoadSDL out of memory,");
//	
//		throw std::exception("LoadSDL error.");
//	}
//
//	//gluBuild2DMipmaps(gl::GL_TEXTURE_2D, 4, w, h, gl::GL_RGBA, gl::GL_UNSIGNED_BYTE, (Uint8 *)raw);
//	gl::TexImage2D(gl::GL_TEXTURE_2D, 0, gl::GL_RGB, w, h, 0, gl::GL_RGBA, gl::GL_UNSIGNED_BYTE, (Uint8 *)raw);
//
//	delete [] raw;
//
//	errorCode = gl::GetError();
//	if ( errorCode != 0 ) 
//	{
//		if ( errorCode == gl::GL_OUT_OF_MEMORY )
//			throw std::exception("LoadSDL out of memory,");
//	
//		throw std::exception("LoadSDL error.");
//	}
//
//	 return true;
//} 

void GLTexture::unload()
{
	if(textureID != 0)
		glDeleteTextures(1, &textureID);
	textureID = 0;
}


GLuint GLTexture::getTextureID() const
{
	return textureID;
}

void GLTexture::useTrilinearFiltering() const
{
	if(!good())
		return;

	// Nice trilinear filtering.
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GLTexture::useSimpleFiltering() const
{
	if(!good())
		return;

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
}