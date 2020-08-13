#include<iostream>
#include"Renderer.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);

}
bool GLLogCall(const char*function,const char*file,int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error]:"<<"(" << error <<")"<<function<<" "<<file<<":"<<line<< std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{  
    shader.Bind();
    va.Bind(); 
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    //GLCall(glClearColor(1.0f,1.0f,1.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
