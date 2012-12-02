#ifndef LAHHA_OPENGL_H
#define LAHHA_OPENGL_H

//#include <Lahha/OpenGL/GLBuffer.h>
#include <Lahha/OpenGL/GLVertexBuffer.h>
#include <Lahha/OpenGL/GLMesh.h>
//#include <Lahha/OpenGL/GLShader.h>
#include <Lahha/OpenGL/GLProgram.h>
#include <Lahha/OpenGL/GLTexture.h>

//Link binaries for VC.
#ifdef _DEBUG
#pragma comment(lib, "OpenGL_d.lib")

#else
#pragma comment(lib, "OpenGL.lib")

#endif

#endif //LAHHA_OPENGL_H