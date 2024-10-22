#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "string_view"

#define ASSERT(x) if (!(x)) __debugbreak()
#define GlCall(x) GLCleatError();\
    x;\
    


void GLDebugCallback(
    unsigned int source,
    unsigned int type,
    unsigned int id,
    unsigned int severity,
    int length,
    const char* message,
    const void* userParam)
{
    const char* severityString = " ";
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        severityString = "[NOTIFICATION]";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        severityString = "[LOW]";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        severityString = "[MEDIUM]";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        severityString = "[HIGH]";
        break;
    default:
        severityString = "[DEBUG]";
    }
    std::cout << "[OpenGL] " << message << "\n";
    if (severity > GL_DEBUG_SEVERITY_MEDIUM)
    __debugbreak();
}

static void GlClearError()
{
    while (glGetError() != GL_NO_ERROR);
}




void GLFWErrorCallback(int error, const char* description)
{
    std::cerr << description << "/n";
};



struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

/*ALL CAPS COMMENTS ARE FOR PERSONAL USE OF REMEMBERING WHAT DOES WHAT*/

static ShaderProgramSource ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {   
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line; 
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                //set mode to vertex
                type = ShaderType::VERTEX;

            }
            else if (line.find("fragment") != std::string::npos)
            {
                //set mode to fragment
                type = ShaderType::FRAGMENT;

            }
        }
        else
        {
            ss[(int)type] << line << "\n";
        }

    }
    return { ss[0].str(), ss[1].str() };
}


static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

     //error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);      /*the iv basically stand for integer and vector that the function wants*/
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile  "<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << "\n"; /*line to print out error for not compiling a vertex or fragment shader. not perfect though */
        std::cout << message << "\n";
        glDeleteShader(id);
        return 0;
    }

    return id;
}


static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
   unsigned int program =  glCreateProgram();
   unsigned int vertshade = CompileShader(GL_VERTEX_SHADER, vertexShader);
   unsigned int fragshade = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

   glAttachShader(program, vertshade);
   glAttachShader(program, fragshade);
   glLinkProgram(program);
   glValidateProgram(program);

   glDeleteShader(vertshade);
   glDeleteShader(fragshade);

   return program;
}




int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*Makes frame rate = to the fps of the monitor running the program*/
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error! GLEW not OK" << std::endl;
    };
     
    
    
    std::cout << glGetString(GL_VERSION) << std::endl;
    

    //GLFW error callback
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glEnable(GL_DEBUG_OUTPUT);
    glfwSetErrorCallback(GLFWErrorCallback);
    glDebugMessageCallback(GLDebugCallback, nullptr);

    float positions[] = {
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    ///vertex array object
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /*CREATING AND BINDING THE VERTEX BUFFER*/
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
    
    /*CREATING AND BINDING THE INDEX BUFFER*/
    unsigned int ibo;  /*Index Buffer Object*/
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    /*creates a Vertex Attribute pointer and enables it*/
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);  /*apparently the size of a float doubled is 8 bytes*/

    ShaderProgramSource source = ParseShader("resources/shaders/Shader.shader");
    std::cout << "VERTEX" << "\n";
    std::cout << source.VertexSource << "\n";
    std::cout << "FRAGMENT" << "\n";
    std::cout << source.FragmentSource << "\n";
    

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    int location = glGetUniformLocation(shader, "u_Color");
    ASSERT(location != -1);
    glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);
    
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    
    /*DRAW CODE FOR SHADER STUFF*/
   // glDrawElements(GL_TRIANGLES, 3);

    float r = 0.0f;
    float increment = 0.5f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glUniform4f(location, r, 0.3f, 0.8f, 1.0f);

        glBindVertexArray(vao);
      //  glBindBuffer(GL_ARRAY_BUFFER, buffer);
       //glEnableVertexAttribArray(0);
      //  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        
        /*DRAW CODE WITHOUT SHADER STUFF*/
       // glDrawArrays(GL_TRIANGLES, 0, 6);

        /*DRAW WITH SHADER STUFF*/
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); /*pulls the 6 indices from ibo and since it is bound above we can just put nullptr for the indices ptr*/
        
        if (r > 1.0f)
            increment = -0.5f;
        else if (r < 0.0f)
            increment = 0.5f;

        r += increment;




        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();


      //  glDeleteProgram(shader);
    }

    glfwTerminate();
    return 0;
}