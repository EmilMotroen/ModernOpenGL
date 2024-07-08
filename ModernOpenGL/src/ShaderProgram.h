#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "GL/glew.h"
#include <string>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	enum ShaderType {
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

	/// <summary>
	/// Load the vertex and fragment shaders.
	/// </summary>
	/// <param name="vsFilename">The vertex shader file</param>
	/// <param name="fsFile">The fragment shader file</param>
	/// <returns>True if the shaders are loaded correctly, else false</returns>
	bool loadShaders(const char* vsFilename, const char* fsFile);
	
	/// <summary>
	/// Use the loaded shaders.
	/// </summary>
	void use();

private:
	std::string fileToString(const std::string& filename);
	void checkCompileErrors(GLuint shader, ShaderType type);

	GLuint handle;
};

#endif

