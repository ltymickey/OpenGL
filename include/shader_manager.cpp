#include "shader_manager.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
// constexpr GLfloat vertices[] = {
//     0.5f, 0.5f, 0.0f, //右上角
//     0.5f, -0.5f, 0.0f, //右下角
//     -0.5f, -0.5f, 0.0f, //左下角
//     -0.5f, 0.5f, 0.0f //左上角
// };
// constexpr GLuint indices[6] = {
//     //note tha we start from 0
//     0, 1, 3, //first triangle
//     1, 2, 3 //second triangle
// };

void shader_manager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void shader_manager::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    } 
}
float shader_manager::processInput(GLFWwindow* window,float mixValue,float max,float min)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.1f;
        if (mixValue >= max) mixValue = max;
    }
    if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.1f;
        if (mixValue <= min) mixValue = min;
    }
    return mixValue;
}

float shader_manager::processInput(GLFWwindow* window, float mixValue, float max, float min, float unit)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += unit;
        if (mixValue >= max) mixValue = max;
    }
    if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= unit;
        if (mixValue <= min) mixValue = min;
    }
    return mixValue;
}

void shader_manager::initialization_glfw(int major, int minor)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int shader_manager::shader_create_bind(GLchar* vertexShaderSource, GLint success, int bufferSize, char* infoLog, GLenum shadertype, char error)
{
    unsigned int vertexShader = glCreateShader(shadertype);
    glShaderSource(vertexShader,1,&vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    //check for linking errors
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader,bufferSize,nullptr,infoLog);
        std::cout << error << infoLog << std::endl;
    }
    return vertexShader;
}

int shader_manager::shader_link(GLint vertexShader, GLint fragmentShader, GLint success, char* infoLog, char error)
{
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    //check for linking errors
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram,constants::bufferSize512,nullptr,infoLog);
        std::cout << error << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

GLuint* shader_manager::buffer_array_bind(GLfloat vertices[],GLuint indices[],size_t vertices_size,size_t indices_size)        
{    
    GLuint vao,vbo,ebo;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo); 
    glGenBuffers(1,&ebo);
    //bind the vertex array object first, then bind and set vertex buffer(s), and then configure vertex attributes
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,vertices_size,vertices,GL_DYNAMIC_DRAW);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices_size,indices,GL_DYNAMIC_DRAW); 
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    auto* buffers = new GLuint[3]{vao, vbo, ebo};
    return buffers;
}
GLuint* shader_manager::buffer_array_bind(GLfloat vertices[], size_t vertices_size)
{
    GLuint vao,vbo;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    //bind the vertex array object first, then bind and set vertex buffer(s), and then configure vertex attributes
    glBindVertexArray(vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,vertices_size,vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    auto* buffers = new GLuint[2]{vao, vbo};
    return buffers;
}
GLuint* shader_manager::buffer_array_bind(GLfloat firstvertices[],size_t firstvertices_size,GLfloat secondvertices[],size_t secondvertices_size)
{
    GLuint VAOs[2],VBOs[2];
    glGenVertexArrays(2,VAOs);
    glGenBuffers(2,VBOs);
    setbuffer_data(VAOs[0],VBOs[0],firstvertices,firstvertices_size);
    setbuffer_data(VAOs[1],VBOs[1],secondvertices,secondvertices_size);
    auto* buffers = new GLuint[4]{VAOs[0],VAOs[1],VBOs[0],VBOs[1]};
    return buffers;
}
void shader_manager::render_loop(GLFWwindow* window,GLuint shaderPrograms[],GLuint VAOs[])
{
    while (!glfwWindowShouldClose(window))
    {
        //Input
        //-----
        processInput(window);
        //Render Code
        //-----
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //draw our first triangle
        bind_shader(shaderPrograms[0], VAOs[0]);
        bind_shader(shaderPrograms[1], VAOs[1]);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
void shader_manager::render_loop(GLFWwindow* window,GLuint shaderProgram,GLuint VAOs[])
{
    while (!glfwWindowShouldClose(window))
    {
        //Input
        //-----
        processInput(window);
        //Render Code
        //-----
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //draw our first triangle
        bind_shader(shaderProgram, VAOs[0]);
        bind_shader(shaderProgram, VAOs[1]);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void shader_manager::set_vertex_attribute(int index, int size, int stride, int offset)
{
    glVertexAttribPointer(index,size,GL_FLOAT,GL_FALSE, stride * sizeof(float),(void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(index);
}

void shader_manager::bind_shader(GLuint shaderProgram, GLuint vao)
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);//seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES,0,3);
}

int shader_manager::bind_texture(int index,GLuint textureID,const char* path,int width,int height,int nrChannels,bool ispng,int param)
{
    glGenTextures(index,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);
    //set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,param);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,param);
    //set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //load image,create texture and generate mipmaps
    unsigned char *data = stbi_load(path,&width,&height,&nrChannels,0);
    if (data)
    {
        if (ispng)
        {
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << constants::failedToLoadTexture << std::endl;
    }
    stbi_image_free(data);
    return textureID;
}



