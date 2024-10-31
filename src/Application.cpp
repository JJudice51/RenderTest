#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "string_view"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"







/*ALL CAPS COMMENTS ARE FOR PERSONAL USE OF REMEMBERING WHAT DOES WHAT*/


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
    {

        //GLFW error callback
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        glEnable(GL_DEBUG_OUTPUT);
        glfwSetErrorCallback(Renderer::GLFWErrorCallback);
        glDebugMessageCallback(Renderer::GLDebugCallback, nullptr);

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



        /*CREATING AND BINDING THE VERTEX BUFFER*/
        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));


        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);



        /*CREATING AND BINDING THE INDEX BUFFER*/
        IndexBuffer ib(indices, 6);

        Shader shader("resources/shaders/Shader.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


     /////   Texture texture ("res/textures/somethingsomewherehere") /////NEED TO FINISH FILE PATH FOR TEXTURES
      /////  texture.Bind();
     /////   shader.SetUniform1i("u_Texture",0);                   

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();


        Renderer renderer;


        float r = 0.0f;
        float increment = 0.5f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            renderer.Clear();

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            va.Bind();
            ib.Bind();


            //Draw via window.
            renderer.Draw(va,ib, shader);                                                                           

            if (r > 1.0f)
                increment = -0.5f;
            else if (r < 0.0f)
                increment = 0.5f;

            r += increment;




            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();



        }


    }
        glfwTerminate();
        return 0;
    
}