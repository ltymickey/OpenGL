#pragma once
#include "glad.h"
#include "glfw3.h"
#include "constants.h"
#include <iostream>
class shader_manager
{
public:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow *window);
    static float processInput(GLFWwindow* window, float mixValue, float max, float min);
    static float processInput(GLFWwindow* window, float mixValue, float max, float min,float unit);
    void initialization_glfw(int major,int minor);
    int shader_create_bind(GLchar* vertexShaderSource, GLint success,int bufferSize,char* infoLog, GLenum shadertype,char error);
    int shader_link(GLint vertexShader, GLint fragmentShader, GLint success,char* infoLog,char error);

    static GLuint* buffer_array_bind(GLfloat vertices[],GLuint indices[],size_t vertices_size,size_t indices_size);
    static GLuint* buffer_array_bind(GLfloat vertices[],size_t vertices_size);
    static GLuint* buffer_array_bind(GLfloat vertices[],size_t vertices_size,GLfloat vertices1[],size_t vertices1_size);

    static void setbuffer_data(GLuint vao,GLuint vbo,GLfloat vertices[],size_t vertices_size)
    {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBufferData(GL_ARRAY_BUFFER,vertices_size,vertices,GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);
    }
    static void bind_shader(GLuint shaderProgram, GLuint vao);
    static int bind_texture(int index,GLuint textureID,const char* path,int width,int height,int nrChannels,bool ispng,int param);
    static void render_loop(GLFWwindow* window,GLuint shaderPrograms[],GLuint VAOs[]);
    static void render_loop(GLFWwindow* window,GLuint shaderProgram,GLuint VAOs[]);
    static void set_vertex_attribute(int index,int size,int stride,int offset);
};
