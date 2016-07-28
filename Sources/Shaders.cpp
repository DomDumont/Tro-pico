#include "Shaders.h"


#include "ResourceManager.h"


void Shaders::LoadFromFile(const std::string & filename)
{
	GLchar* vertexSource = (GLchar*)ResourceManager::Get().LoadBinaryFile("data/simple.vert");
	GLchar* fragmentSource = (GLchar*)ResourceManager::Get().LoadBinaryFile("data/simple.frag");
	GLint programState = 0;
	GLint vertexSize = 0;
	GLint fragmentSize = 0;

	// Création des IDs
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
}
