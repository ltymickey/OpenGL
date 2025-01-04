#ifndef SHADER_H
#define SHADER_H
#pragma once
#include "glad.h"
#include "glfw3.h"
#include "constants.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include "..\..\include\shader_manager.h"

class shader
{
public:
    //program ID
    unsigned int ID;
    //构造器读取并构建着色器
    shader(const char* vertexPath,const char* fragmentPath);
    //使用、激活程序
    void use();
    //uniform工具函数    
    void setBool(const std::string& name, bool value) const;

    void setInt(const std::string &name,int value) const;

    void setFloat(const std::string &name,float value) const;
    void set_mat4(const ::std::string& name, glm::mat4 &value) const;
    void set_mat3(const ::std::string& name, glm::mat3 &value) const;
    void set_mat2(const ::std::string& name, glm::mat2 &value) const;
    void set_vec4(const ::std::string& name, glm::vec4 &value) const;
    void set_vec4(const ::std::string& name, float x,float y,float z,float w) const;
    void set_vec3(const ::std::string& name, glm::vec3 &value) const;
    void set_vec3(const ::std::string& name, float x,float y,float z) const;
    void set_vec2(const ::std::string& name, glm::vec2 &value) const;
    void set_vec2(const ::std::string& name, float x,float y) const;
    static int draw();
private:
    static void checkCompileErrors(unsigned int shader,std::string type);
};
#endif
