#include "texture_manager.h"
#include <glad.h>
#include <glfw3.h>
#include <constants.h>
#include <shader_manager.h>
#include <stb_image.h>
#include <iostream>
#include <conio.h>

#include "shader.h"
int texture_manager::draw()
{
        shader_manager _shaderMgr = shader_manager();
         //glfw: initialize and configure
        //------------------------------
        _shaderMgr.initialization_glfw(3,3);
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

        shader ourShader("G:/Projects/VisualStudio2022/OpenGL/OpenGL/GettingStarted/shader_texture/vertex.vert","G:/Projects/VisualStudio2022/OpenGL/OpenGL/GettingStarted/shader_texture/fragment.frag");
        unsigned int VBO,VAO,EBO;
        glGenVertexArrays(1,&VAO);
        glGenBuffers(1,&VBO);
        glGenBuffers(1,&EBO);
    
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(constants::texture_vertices),constants::texture_vertices,GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(constants::texture_indices),constants::texture_indices,GL_STATIC_DRAW);
        //position attribute
        shader_manager::set_vertex_attribute(0,3,8,0);
        //color attribute
        shader_manager::set_vertex_attribute(1,3,8,3);
        //texture coord attribute
        shader_manager::set_vertex_attribute(2,2,8,6);
        unsigned int texture1 = 0,texture2 = 0;
        int width = 0,height = 0,nrChannels = 0;
        texture1 = shader_manager::bind_texture(1,texture1,"G:/Projects/VisualStudio2022/OpenGL/resources/textures/container.jpg",width,height,nrChannels,false,GL_CLAMP_TO_EDGE);
        stbi_set_flip_vertically_on_load(true);
        texture2 = shader_manager::bind_texture(2,texture2,"G:/Projects/VisualStudio2022/OpenGL/resources/textures/awesomeface.png",width,height,nrChannels,true,GL_REPEAT);
        ourShader.use();
        glUniform1i(glGetUniformLocation(ourShader.ID,"texture1"),0);
        ourShader.setInt("texture2",1);     
        float mixValue = 0.2f; 
        //------------------------------
        //render loop
        //------------------------------    
        while (!glfwWindowShouldClose(window))
        {
            //Input
            //-----
            mixValue = shader_manager::processInput(window,mixValue,1.0f,0.0f);
            ourShader.setFloat("mixValue",mixValue);
            //Render Code
            //-----
            glClearColor(0.2f,0.3f,0.3f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,texture1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,texture2);
            ourShader.use();
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
            //glfw: swap buffers and poll IO events (keyboard, mouse, etc.)
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        //optional: de-alloc all resources once they've outlived their purpose
        glDeleteVertexArrays(1,&VAO);
        glDeleteBuffers(1,&VBO);
        glDeleteBuffers(1,&EBO); 
        glfwTerminate();
        return 0;
}
