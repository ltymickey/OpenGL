#pragma once
#include "glad.h"
#include "glfw3.h"
#include "constants.h"
#include "..\..\include\shader_manager.h"
#include <iostream>
#include "shader.h"

class hellotriangles
{
    public:hellotriangles(){std::cout << "In to HelloTriangles" << std::endl;}
    public:~hellotriangles(){std::cout << "Out HelloTriangles" << std::endl;}
    public: static int draw()
    {
        shader_manager _shader_mgr = shader_manager();
         //glfw: initialize and configure
        //------------------------------
        _shader_mgr.initialization_glfw(3,3);

        //glfw window creation
        //------------------------------
        GLFWwindow* window = glfwCreateWindow(constants::SCR_WIDTH, constants::SCR_HEIGHT, constants::title, nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << constants::failedToCreateWindow << std::endl;
            glfwTerminate();//结束glfw
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, shader_manager::framebuffer_size_callback);
        //glad : load all OpenGL function pointers
        //------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << constants::failedToInitGLAD << std::endl;
            return -1;
        }
        //build and compile our shader program
        //------------------------------
        int success = 0;
        char infoLog[512];
        //vertex shader
        const unsigned int vertexShader = _shader_mgr.shader_create_bind(const_cast<GLchar*>(constants::vertexShaderSource),success,constants::bufferSize512,infoLog,GL_VERTEX_SHADER,*constants::vertexError);
        //fragment shader
        const unsigned int fragmentShader = _shader_mgr.shader_create_bind(const_cast<GLchar*>(constants::fragmentShaderSource),success,constants::bufferSize512,infoLog,GL_FRAGMENT_SHADER,*constants::fragmentError);
        //link shader
        const unsigned int shaderProgram = _shader_mgr.shader_link(static_cast<GLint>(vertexShader),static_cast<GLint>(fragmentShader),success,infoLog,*constants::programError);
        //set up vertex data(and buffers) and configure vertex attributes
        //------------------------------
        GLfloat vertices[] = {
            0.5f, 0.5f, 0.0f, //右上角
            0.5f, -0.5f, 0.0f, //右下角
            -0.5f, -0.5f, 0.0f, //左下角
            -0.5f, 0.5f, 0.0f //左上角
        };
        GLuint indices[6] = {
            //note tha we start from 0
            0, 1, 3, //first triangle
            1, 2, 3 //second triangle
        };
        const GLuint* buffers = shader_manager::buffer_array_bind(vertices,indices,sizeof(vertices),sizeof(indices));
        const GLuint VBO =  buffers[0];
        const GLuint VAO =  buffers[1];
        const GLuint EBO =  buffers[2];    
        //render loop
        //------------------------------    
        while (!glfwWindowShouldClose(window))
        {
            //Input
            //-----
            _shader_mgr.processInput(window);
            //Render Code
            //-----
            glClearColor(0.2f,0.3f,0.3f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            //draw our first triangle
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);//seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            // glDrawArrays(GL_TRIANGLES,0,6);
            glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
            glBindVertexArray(0);//no need to unbind it every time
                    
            //glfw: swap buffers and poll IO events (keyboard, mouse, etc.)
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        //optional: de-alloc all resources once they've outlived their purpose
        glDeleteVertexArrays(1,&VAO);
        glDeleteBuffers(1,&VBO);
        glDeleteBuffers(1,&EBO);
        glDeleteProgram(shaderProgram);    
        glfwTerminate();
        return 0;
    }
    public: static int toTriangles()
    {
        shader_manager _shader_mgr = shader_manager();
         //glfw: initialize and configure
        //------------------------------
        _shader_mgr.initialization_glfw(3,3);
        //glfw window creation
        //------------------------------
        GLFWwindow* window = glfwCreateWindow(constants::SCR_WIDTH, constants::SCR_HEIGHT, constants::title, nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << constants::failedToCreateWindow << std::endl;
            glfwTerminate();//结束glfw
            return -1;
        }    
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, shader_manager::framebuffer_size_callback);    
        //glad : load all OpenGL function pointers
        //------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << constants::failedToInitGLAD << std::endl;
            return -1;
        }    
        //build and compile our shader program
        //------------------------------
        int success = 0;
        char infoLog[constants::bufferSize512];
        //vertex shader
        const unsigned int vertexShader = _shader_mgr.shader_create_bind(const_cast<GLchar*>(constants::vertexShaderSource),success,constants::bufferSize512,infoLog,GL_VERTEX_SHADER,*constants::vertexError);     
        //fragment shader
        const unsigned int fragmentShader = _shader_mgr.shader_create_bind(const_cast<GLchar*>(constants::fragmentShaderSource),success,constants::bufferSize512,infoLog,GL_FRAGMENT_SHADER,*constants::fragmentError); 
        //link shader
        // unsigned int shaderProgram = glCreateProgram();
        const unsigned int shaderProgram = _shader_mgr.shader_link(static_cast<GLint>(vertexShader),static_cast<GLint>(fragmentShader),success,infoLog,*constants::programError);
        //set up vertex data(and buffers) and configure vertex attributes
        //------------------------------

        float vertices[] = {
            -0.9f,-0.5f,0.0f,
            0.0f,-0.5f,0.0f,
            -0.45f,0.5f,0.0f,
            //
            0.0f,-0.5f,0.0f,
            0.9f,-0.5f,0.0f,
            0.45f,0.5f,0.0f        
        };
        GLuint* buffers = shader_manager::buffer_array_bind(vertices,sizeof(vertices));
        GLuint VAO = buffers[0];
        GLuint VBO = buffers[1];        
        //render loop
        //------------------------------    
        while (!glfwWindowShouldClose(window))
        {
            //Input
            //-----
            _shader_mgr.processInput(window);
            //Render Code
            //-----
            glClearColor(0.2f,0.3f,0.3f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            //draw our first triangle
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);//seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(GL_TRIANGLES,0,6);
            // glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
            glBindVertexArray(0);//no need to unbind it every time
                    
            //glfw: swap buffers and poll IO events (keyboard, mouse, etc.)
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        //optional: de-alloc all resources once they've outlived their purpose
        glDeleteVertexArrays(1,&VAO);
        glDeleteBuffers(1,&VBO);
        // glDeleteBuffers(1,&EBO);
        glDeleteProgram(shaderProgram);    
        glfwTerminate();
        return 0;
    }
    public: static int toBuffers()
    {
        shader_manager _shader_mgr = shader_manager();
         //glfw: initialize and configure
        //------------------------------
        _shader_mgr.initialization_glfw(3,3);
        //glfw window creation
        //------------------------------
        GLFWwindow* window = glfwCreateWindow(constants::SCR_WIDTH, constants::SCR_HEIGHT, constants::title, nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << constants::failedToCreateWindow << std::endl;
            glfwTerminate();//结束glfw
            return -1;
        }    
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, shader_manager::framebuffer_size_callback);
    
        //glad : load all OpenGL function pointers
        //------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << constants::failedToInitGLAD << std::endl;
            return -1;
        }
    
        //build and compile our shader program
        //------------------------------
        int success = 0;
        char infoLog[constants::bufferSize512];
        //vertex shader
        const unsigned int vertexShader = _shader_mgr.shader_create_bind(const_cast<GLchar*>(constants::vertexShaderSource),success,constants::bufferSize512,infoLog,GL_VERTEX_SHADER,*constants::vertexError);     
        //fragment shader
        const unsigned int fragmentShader = _shader_mgr.shader_create_bind(const_cast<GLchar*>(constants::fragmentShaderSource),success,constants::bufferSize512,infoLog,GL_FRAGMENT_SHADER,*constants::fragmentError); 
        //link shader
        const unsigned int shaderProgram = _shader_mgr.shader_link(static_cast<GLuint>(vertexShader),static_cast<GLuint>(fragmentShader),success,infoLog,*constants::programError);
        //set up vertex data(and buffers) and configure vertex attributes
        //------------------------------
        float firstTriangle[] = {
            -0.9f,-0.5f,0.0f,
             0.0f,-0.5f,0.0f,
            -0.45f,0.5f,0.0f,
            //
        };
         float secondTriangle[]
         {
             0.0f,-0.5f,0.0f,
             0.9f,-0.5f,0.0f,
             0.45f,0.5f,0.0f        
         };
        
        auto* buffers = shader_manager::buffer_array_bind(firstTriangle,sizeof(firstTriangle),secondTriangle,sizeof(secondTriangle));
        // GLuint VBOs[2],VAOs[2];
        GLuint VAOs[2] = {buffers[0],buffers[1]};
        GLuint VBOs[2] = {buffers[2],buffers[3]};
        //render loop
        //------------------------------
        shader_manager::render_loop(window,shaderProgram,VAOs);
        //optional: de-alloc all resources once they've outlived their purpose
        glDeleteVertexArrays(2,VAOs);
        glDeleteBuffers(2,VBOs);
        // glDeleteBuffers(1,&EBO);
        glDeleteProgram(shaderProgram);    
        glfwTerminate();
        return 0;
    }
    public: static int singleShader()
    {
        shader_manager _shader_mgr = shader_manager();
         //glfw: initialize and configure
        //------------------------------
        _shader_mgr.initialization_glfw(3,3);
        //glfw window creation
        //------------------------------
        GLFWwindow* window = glfwCreateWindow(constants::SCR_WIDTH, constants::SCR_HEIGHT, constants::title, nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << constants::failedToCreateWindow << std::endl;
            glfwTerminate();//结束glfw
            return -1;
        }    
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, shader_manager::framebuffer_size_callback);
        //glad : load all OpenGL function pointers
        //------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << constants::failedToInitGLAD << std::endl;
            return -1;
        }    
        //build and compile our shader program
        //------------------------------
        int success = 0;
        char infoLog[constants::bufferSize512];
        //vertex shader
        const unsigned int vertexShader = _shader_mgr.shader_create_bind(const_cast<GLchar*>(constants::vertexShaderSource),success,constants::bufferSize512,infoLog,GL_VERTEX_SHADER,*constants::vertexError);        
        //fragment shader
        const unsigned int fragmentShader = _shader_mgr.shader_create_bind(const_cast<GLchar*>(constants::fragmentShaderSource),success,constants::bufferSize512,infoLog,GL_FRAGMENT_SHADER,*constants::fragmentError); 
        const unsigned int fragmentShader1 = _shader_mgr.shader_create_bind(const_cast<GLchar*>(constants::fragmentShader1Source),success,constants::bufferSize512,infoLog,GL_FRAGMENT_SHADER,*constants::fragmentError); 
        //link shader
        // unsigned int shaderProgram = glCreateProgram();
        unsigned int shaderProgram = _shader_mgr.shader_link(static_cast<GLuint>(vertexShader),static_cast<GLuint>(fragmentShader),success,infoLog,*constants::programError);
        // unsigned int shaderProgram1 = glCreateProgram();
        unsigned int shaderProgram1 = _shader_mgr.shader_link(static_cast<GLuint>(vertexShader),static_cast<GLuint>(fragmentShader1),success,infoLog,*constants::programError);
        //set up vertex data(and buffers) and configure vertex attributes
        //------------------------------
        float firstTriangle[] = {
            -0.9f,-0.5f,0.0f,
             0.0f,-0.5f,0.0f,
            -0.45f,0.5f,0.0f,
        };
         float secondTriangle[]
         {
             0.0f,-0.5f,0.0f,
             0.9f,-0.5f,0.0f,
             0.45f,0.5f,0.0f        
         };
        // unsigned int indices[] = { //note tha we start from 0
        //     0,1,3,//first triangle
        //     1,2,3//second triangle
        // };
        auto* buffers = shader_manager::buffer_array_bind(firstTriangle,sizeof(firstTriangle),secondTriangle,sizeof(secondTriangle));
        // GLuint VBOs[2],VAOs[2];
        GLuint VAOs[2] = {buffers[0],buffers[1]};
        GLuint VBOs[2] = {buffers[2],buffers[3]};
        //render loop
        //------------------------------
        shader_manager::render_loop(window,new GLuint[2]{shaderProgram,shaderProgram1},VAOs);
        //optional: de-alloc all resources once they've outlived their purpose
        glDeleteVertexArrays(2,VAOs);
        glDeleteBuffers(2,VBOs);
        // glDeleteBuffers(1,&EBO);
        glDeleteProgram(shaderProgram);    
        glDeleteProgram(shaderProgram1);    
        glfwTerminate();
        return 0;
    }    
};


