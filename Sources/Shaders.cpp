#include "Global.h"
#include "Shaders.h"


#include "ResourceManager.h"


void Shaders::LoadFromFile(const std::string & filename)
{
	std::string pathString;
	pathString = "data/" + filename + ".vert";
	std::string vertexString = ResourceManager::Get().LoadTextFile(pathString);
	pathString = "data/" + filename + ".frag";
	std::string fragmentString = ResourceManager::Get().LoadTextFile(pathString).c_str();
	GLchar* vertexSource = (GLchar *)vertexString.c_str();
	GLchar* fragmentSource = (GLchar *)fragmentString.c_str();
	GLint programState = 0;
	GLint vertexSize = 0;
	GLint fragmentSize = 0;

	// Création des IDs
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	if (!vertexSource || !fragmentSource)
		{
		// Ici, il faudrait faire en sorte que le programme s'arrête
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
		return;
		}

	// Chargement des sources dans OpenGL
	vertexSize = strlen(vertexSource);
	fragmentSize = strlen(fragmentSource);
	glShaderSource(vertexID, 1, (const GLchar**)(&vertexSource), &vertexSize);
	glShaderSource(fragmentID, 1, (const GLchar**)(&fragmentSource), &fragmentSize);

	// Compilation du vertex shader
	glCompileShader(vertexID);
	glCompileShader(fragmentID);

	// Vérification des erreurs
	if (!CheckShaderCompilation(vertexID) || !CheckShaderCompilation(fragmentID))
		{
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
		return;
		}

	// Creation de l'ID pour le programme
	programID = glCreateProgram();

	// On attache les shaders ensemble
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);

	// On peut enfin passer aux liage.
	glLinkProgram(programID);

	// Et encore une fois on vérifie si tout se passe bien
	glGetProgramiv(programID, GL_LINK_STATUS, &programState);
	if (programState != GL_TRUE)
		{
		// On récupère la taille du log
		GLint logSize = 0;
		GLchar* log = NULL;

		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logSize);

		// On peut allouer la mémoire, une fois que l'on a la taille du log
		log = (GLchar*)malloc(logSize);
		if (log == NULL)
			{
			fprintf(stderr, "Erreur d'allocation de mémoire pour le log de la compilation du programme\n");
			glDeleteShader(vertexID);
			glDeleteShader(fragmentID);
			return;
			}

		// Et on récupère le log
		glGetProgramInfoLog(programID, logSize, &logSize, log);

		// On affiche
		fprintf(stderr, "Erreur lors du liage du shader:\n%s", log);

		free(log);
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
		return;
		}

	// Voilà, nous sommes prêt
	glUseProgram(programID);
}

// Pour plus de simplicité, j'ajoute une fonction qui vérifie la compilation des shaders
char Shaders::CheckShaderCompilation(GLuint shaderID)
	{
	GLint compilationStatus = 0;

	// Vérification de la compilation pour le vertex shader
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &compilationStatus);
	if (compilationStatus != GL_TRUE)
		{
		// Nous savons que la compilation a échoué, donc nous devons savoir pourquoi
		// Nous devons récupéré la taille du log
		GLint logLength = 0;
		GLchar* log = NULL;

		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

		// Maintenant que nous avons la taille, nous pouvons alloué la mémoire suffisante pour ce log
		log = (GLchar*)malloc(logLength);
		if (log == NULL)
			{
			fprintf(stderr, "Erreur d'allocation de mémoire pour le log de la compilation du shader\n");
			return 0;
			}

		glGetShaderInfoLog(shaderID, logLength, &logLength, log);

		// On peut afficher le message
		fprintf(stderr, "Erreur de compilation:\n%s", log);

		// Et on n'oublie pas de libéré la mémoire
		free(log);

		return 0;
		}

	return 1; // Pas d'erreur
	}