#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
  public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath) {
      std::string vertexCode;
      std::string fragmentCode;
      std::ifstream vertexShaderFile;
      std::ifstream fragmentShaderFile;


      try {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        std::stringstream vertexStream, fragmentStream;

        vertexStream << vertexShaderFile.rdbuf();
        fragmentStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
      } catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
      }

      const char* vShaderCode = vertexCode.c_str();
      const char* fShaderCode = fragmentCode.c_str();

      // compile shaders
      unsigned int vertex, fragment;
      int success;
      char infoLog[512];

      // vertex Shader
      vertex = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertex, 1, &vShaderCode, NULL);
      glCompileShader(vertex);

      glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      }
        
      // fragment Shader
      fragment = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragment, 1, &fShaderCode, NULL);
      glCompileShader(fragment);

      glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
      }

      // compile program
      ID = glCreateProgram();
      glAttachShader(ID, vertex);
      glAttachShader(ID, fragment);
      glLinkProgram(ID);

      glGetProgramiv(ID, GL_LINK_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      }

      glDeleteShader(vertex);
      glDeleteShader(fragment);
    };

    void use() {
      glUseProgram(ID);
    };

    void setBool(const std::string& name, bool value) const {
      glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    };

    void setInt(const std::string& name, int value) const {
      glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    };
    void setFloat(const std::string& name, float value) const {
      glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    };

    void setVec3(const std::string& name, float x, float y, float z) const {
      glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
    }
    void setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
};
