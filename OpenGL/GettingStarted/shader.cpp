#include "shader.h"

#include <glm/gtc/type_ptr.inl>

#include "HelloTriangles.h"
#include "HelloTriangles.h"
#include "HelloTriangles.h"
#include "HelloTriangles.h"
#include "..\..\include\shader_manager.h"
shader::shader(const char* vertexPath,const char* fragmentPath)
{
    //1.从文件路径中获取顶点/片段着色器
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    //保证ifstream对象可以抛出异常:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        //打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream,fShaderStream;
        //读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        //关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        //转换数据流到string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << constants::shaderUnSuccessError << std::endl;
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Vertex Path: " << vertexPath << std::endl;
        std::cerr << "Fragment Path: " << fragmentPath << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    //2.compile shaders
    unsigned int vertex,fragment;
    //vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vShaderCode,nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex,constants::vertexType);
    //print compile errors if any
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fShaderCode,nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment,constants::fragmentType);
    //shader program
    ID = glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID,constants::programType);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void shader::use()
{
    glUseProgram(ID);
}

void shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),static_cast<int>(value));
}

void shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}

void shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
}

void shader::set_mat4(const std::string& name, glm::mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,&value[0][0]);
}

void shader::set_mat3(const std::string& name, glm::mat3& value) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,&value[0][0]);
}

void shader::set_mat2(const std::string& name, glm::mat2& value) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,&value[0][0]);
}

void shader::set_vec4(const std::string& name, glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void shader::set_vec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()),x,y,z,w); 
}

void shader::set_vec3(const std::string& name, glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void shader::set_vec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()),x,y,z); 
}

void shader::set_vec2(const std::string& name, glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void shader::set_vec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()),x,y); 
}


int shader::draw()
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

        shader outShader("G:/Projects/VisualStudio2022/OpenGL/OpenGL/GettingStarted/vertex.glsl","G:/Projects/VisualStudio2022/OpenGL/OpenGL/GettingStarted/fragment.glsl");
        GLfloat vertices[] = {
            0.5f, -0.5f, 0.0f,  1.0f,0.0f,0.0f, //右上角
            -0.5f, -0.5f, 0.0f, 0.0f,1.0f,0.0f,//右下角
            0.0f, 0.5f, 0.0f,    0.0f,0.0f,1.0f//左上角
        };
        
        unsigned int VBO,VAO;
        glGenVertexArrays(1,&VAO);
        glGenBuffers(1,&VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //------------------------------
        //render loop
        //------------------------------    
        while (!glfwWindowShouldClose(window))
        {
            //Input
            //-----
            shader_manager::processInput(window);
            //Render Code
            //-----
            glClearColor(0.2f,0.3f,0.3f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            outShader.use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES,0,3);
            //draw
            float timeValue = glfwGetTime() * 5.0f;
            float sinColor = sin(timeValue) / 2.0f + 0.5f;
            // int vertexColorLocation = glGetUniformLocation(outShader.ID,"ourColor");
            int vertexOffsetLocation = glGetUniformLocation(outShader.ID,"offset");
            // glUniform4f(vertexColorLocation,1.0f,sinColor,0.0f,1.0f);
            glUniform3f(vertexOffsetLocation,0.5f,0.0f,0.0f);
            //glfw: swap buffers and poll IO events (keyboard, mouse, etc.)
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        //optional: de-alloc all resources once they've outlived their purpose
        glDeleteVertexArrays(1,&VAO);
        glDeleteBuffers(1,&VBO);
        glfwTerminate();
        return 0;
}

void shader::checkCompileErrors(unsigned shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != constants::programType)
    {
        glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
        if (!success)
        {
            glGetShaderInfoLog(shader,1024,nullptr,infoLog);
            std::cout << constants::shaderCompileOfTypeError << type << "\n" << infoLog << "\n -- --------------------------------------------- --" << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader,GL_LINK_STATUS,&success);
        if (!success)
        {
            glGetProgramInfoLog(shader,constants::bufferSize1024,nullptr,infoLog);
            std::cout << constants::shaderLinkOfTypeError << type << "\n" << infoLog <<  "\n -- --------------------------------------------- --" << std::endl;
        }
    }
}