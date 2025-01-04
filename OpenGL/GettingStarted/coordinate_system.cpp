#include "coordinate_system.h"

#include <complex>
#include <stb_image.h>

#include "shader.h"
#include "shader_manager.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

coordinate_system::coordinate_system() = default;

coordinate_system::~coordinate_system() = default;

int coordinate_system::draw()
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

        shader ourShader("G:/Projects/VisualStudio2022/OpenGL/OpenGL/GettingStarted/shader_coordinate/vertex.vert","G:/Projects/VisualStudio2022/OpenGL/OpenGL/GettingStarted/shader_coordinate/fragment.frag");
      
        
        unsigned int VBO,VAO,EBO;
        glGenVertexArrays(1,&VAO);
        glGenBuffers(1,&VBO);
        glGenBuffers(1,&EBO);
    
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(constants::cube_vertices),constants::cube_vertices,GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(constants::texture_indices),constants::texture_indices,GL_STATIC_DRAW);
        //position attribute
        shader_manager::set_vertex_attribute(0,3,5,0);
        //color attribute
        shader_manager::set_vertex_attribute(1,2,5,3);
        unsigned int texture1 = 0,texture2 = 0;
        int width = 0,height = 0,nrChannels = 0;
        texture1 = shader_manager::bind_texture(1,texture1,"G:/Projects/VisualStudio2022/OpenGL/resources/textures/container.jpg",width,height,nrChannels,false,GL_CLAMP_TO_EDGE);
        stbi_set_flip_vertically_on_load(true);
        texture2 = shader_manager::bind_texture(2,texture2,"G:/Projects/VisualStudio2022/OpenGL/resources/textures/awesomeface.png",width,height,nrChannels,true,GL_REPEAT);
        ourShader.use();
        ourShader.setInt("texture1",0);
        ourShader.setInt("texture2",1);
        float ros = 0.0f;
        glm::vec3 cubePositions[] =
            {
            glm::vec3( 0.0f,  0.0f,  0.0f), 
            glm::vec3( 2.0f,  5.0f, -15.0f), 
            glm::vec3(-1.5f, -2.2f, -2.5f),  
            glm::vec3(-3.8f, -2.0f, -12.3f),  
            glm::vec3( 2.4f, -0.4f, -3.5f),  
            glm::vec3(-1.7f,  3.0f, -7.5f),  
            glm::vec3( 1.3f, -2.0f, -2.5f),  
            glm::vec3( 1.5f,  2.0f, -2.5f), 
            glm::vec3( 1.5f,  0.2f, -1.5f), 
            glm::vec3(-1.3f,  1.0f, -1.5f)  
        };
        //------------------------------
        //render loop
        //------------------------------    
        while (!glfwWindowShouldClose(window))
        {
            //Input
            //-----
            ros = shader_manager::processInput(window,ros, 1.0f,-1.0f,0.01f);
            //Render Code
            //-----
            glEnable(GL_DEPTH_TEST);
            glClearColor(0.2f,0.3f,0.3f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,texture1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,texture2);

            //transform
            glm::mat4 model = glm::mat4(1.0f),view = glm::mat4(1.0f),projection = glm::mat4(1.0f);
            model = glm::rotate(model,glm::radians(50.0f) * static_cast<float>(glfwGetTime()),glm::vec3(0.5f,1.0f,0.0f));
            view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
            projection = glm::perspective(glm::radians(45.0f),static_cast<float>(constants::SCR_WIDTH / constants::SCR_HEIGHT),0.1f,100.0f);
            std::cout << ros << std::endl;
            
            ourShader.use();
            ourShader.set_mat4("view", view);
            ourShader.set_mat4("projection", projection);
            
            glBindVertexArray(VAO);
            for (unsigned int i = 0; i < 10; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model,constants().cubePositions[i]);
                float angle = 20.0f;
                if (i % 3 == 0)
                {
                    if (i != 0)
                    {
                        angle *= i * glfwGetTime();
                    }
                    else
                    {
                        angle *= glfwGetTime();
                    }
                }                
                model = glm::rotate(model,glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));
                ourShader.set_mat4("model", model);
                glDrawArrays(GL_TRIANGLES,0,36);
            }   
            // glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
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

