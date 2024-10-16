#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "string_view"


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
            else
            {
                ss[(int)type] << line << "\n";
            }
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

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error! GLEW not OK" << std::endl;
    
    std::cout << glGetString(GL_VERSION) << std::endl;
    
    float positions[6] = {
        -0.5f, -0.5f,
         0.5f,  0.5f,
         0.5f, -0.5f
    };

    /*CREATING AND BINDING THE BUFFER*/
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    
    /*creates a Vertex Attribute pointer and enables it*/
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);  /*apparently the size of a float doubled is 8 bytes*/

    ShaderProgramSource source = ParseShader("resources/shaders/Shader.shader");
    std::cout << source.VertexSource << "\n";

   // unsigned int shader = CreateShader(vertexShader, fragmentShader);
   // glUseProgram(shader);

    
    /*DRAW CODE FOR SHADER STUFF*/
   // glDrawElements(GL_TRIANGLES, 3);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        /*DRAW CODE WITHOUT SHADER STUFF*/
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /*LEGACY OPENGL DRAW CODE GLEW NOT NEEDED*/
        // glBegin(GL_TRIANGLES);
        // glVertex2f(-0.5f, -0.5f);
        // glVertex2f( 0.5f, 0.5f);
        // glVertex2f( 0.5f, -0.5f);
        // glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}