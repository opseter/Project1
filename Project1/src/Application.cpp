#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include"Renderer.h"
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"
int main(void) 
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_COMPAT_PROFILE);//compat ����ģʽ���Ǻ���ģʽ
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

    glfwSwapInterval(1);


    //glViewport(0, 0, 640/2, 480/2);//�������洴���windows��ʵ�ʴ����е�ռλ

    GLenum err = glewInit();
    if (GLEW_OK != err)
        std::cout << "err" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            // positions           // texture coords
             0.5f,  0.5f, 0.0f,    1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.0f,    1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,    0.0f, 1.0f  // top left 
        };
        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));



        VertexArray va;
        VertexBuffer vb(positions, 4 * 5* sizeof(float));
       
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
 
        IndexBuffer ib(indices, 6);


        Shader shader("res/shaders/Test.shader");
        shader.Bind();
        Texture texture("res/textures/pic.png");
        texture.Bind();
        shader.SetUniform1i("texture1", 0);

        //unbind everything 
       
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            //va.Bind();
            //vb.Bind();
            //ib.Bind();
            //shader.Bind();
            renderer.Draw(va, ib, shader);
           

            



            //glClearColor(0.0f, 0.5f, 0.0f, 1.0f);//set the color which will clear the scream
            //glClear(GL_COLOR_BUFFER_BIT);//apply the color prior setted

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
       
    }
    glfwTerminate();
    return 0;
}
