#ifndef __SHADERS_H__
#define __SHADERS_H__

#include <string>
#include <GL/glew.h>
#include <SDL_opengl.h>

class Shaders
{
public:
	void LoadFromFile(const std::string & filename);


public:
	// Création des IDs
	GLuint vertexID;
	GLuint fragmentID;
	GLuint programID;

private:
	char CheckShaderCompilation(GLuint shaderID);
	};
#endif

