#include "ShaderProgram.h"
#include <fstream>
#include <iostream>
#include <sstream>

ShaderProgram::ShaderProgram() : handle(0) {

}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(handle);
}

bool ShaderProgram::loadShaders(const char* vsFilename, const char* fsFilename) {
    std::string vsString = fileToString(vsFilename);
    std::string fsString = fileToString(fsFilename);
    const GLchar* vsSource = vsString.c_str();
    const GLchar* fsSource = fsString.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);


    glShaderSource(vs, 1, &vsSource, NULL);
    glShaderSource(fs, 1, &fsSource, NULL);
    
    glCompileShader(vs);
    checkCompileErrors(vs, VERTEX);
    glCompileShader(fs);
    checkCompileErrors(fs, FRAGMENT);



    handle = glCreateProgram();
    glAttachShader(handle, vs);
    glAttachShader(handle, fs);
    glLinkProgram(handle);

    checkCompileErrors(handle, PROGRAM);

    glDeleteShader(vs);
    glDeleteShader(fs);

	return true;
}

void ShaderProgram::use() {
	if (handle > 0)
		glUseProgram(handle);
}

std::string ShaderProgram::fileToString(const std::string& filename) {
	std::stringstream ss;
	std::ifstream file;

	try {
		file.open(filename, std::ios::in);
		if (!file.fail()) {
			ss << file.rdbuf();
		}

		file.close();
	}
	catch (std::exception ex){
		std::cerr << "Error reading shader file." << std::endl;
	}

	return ss.str();
}

void ShaderProgram::checkCompileErrors(GLuint shader, ShaderType type) {
    int status = 0;
    if (type == PROGRAM) {
        glGetProgramiv(handle, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            GLint length = 0;
            glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
            
            std::string errorLog(length, ' ');
            glGetProgramInfoLog(handle, length, &length, &errorLog[0]);

            std::cerr << "Error - Program failed to link: " << errorLog << std::endl;
        }
    }
    else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            GLint length = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            std::string errorLog(length, ' ');
            glGetShaderInfoLog(shader, length, &length, &errorLog[0]);

            std::cerr << "Error - Shader failed to compile: " << errorLog << std::endl;
        }
    }
}