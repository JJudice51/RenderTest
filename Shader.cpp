#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"





Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    std::cout << "VERTEX" << "\n";
    std::cout << source.VertexSource << "\n";
    std::cout << "FRAGMENT" << "\n";
    std::cout << source.FragmentSource << "\n";
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}


 unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
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
        std::cout << "Failed to compile  " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << "\n"; /*line to print out error for not compiling a vertex or fragment shader. not perfect though */
        std::cout << message << "\n";
        glDeleteShader(id);
        return 0;
    }

    return id;
}
 
 unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
 {
     unsigned int program = glCreateProgram();
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

 ShaderProgramSource Shader::ParseShader(const std::string& filePath)
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


void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(m_RendererID);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform" << name << "doesn't exist!" << std::endl;
    else
        m_UniformLocationCache[name] = location;
    return location;
}


//