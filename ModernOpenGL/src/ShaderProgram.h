#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "GL/glew.h"
#include <string>
#include <map>
#include "glm/glm.hpp"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	enum ShaderType { VERTEX, FRAGMENT, PROGRAM };

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

	void setUniform(const GLchar* name, const glm::vec2& v);
	void setUniform(const GLchar* name, const glm::vec3& v);
	void setUniform(const GLchar* name, const glm::vec4& v);

private:
	std::string fileToString(const std::string& filename);
	void checkCompileErrors(GLuint shader, ShaderType type);
	GLint getUniformLocation(const GLchar* name);

	GLuint handle;
	std::map<std::string, GLint> uniformLocations;
};

#endif

