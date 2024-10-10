#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

/*ALL CAPS COMMENTS ARE FOR PERSONAL USE OF REMEMBERING WHAT DOES WHAT*/

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



    /*DRAW CODE WITHOUT SHADER STUFF*/
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /*DRAW CODE FOR SHADER STUFF*/
  // glDrawElements(GL_TRIANGLES, 3)

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
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