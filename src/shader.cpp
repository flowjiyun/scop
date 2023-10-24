#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType) {
    ShaderUPtr shader = std::unique_ptr<Shader>(new Shader());
    if (!shader->LoadFile(filename, shaderType)) {
        return nullptr;
    }
    return std::move(shader);
}

Shader::~Shader() {
    if (m_shaderId) {
        glDeleteShader(m_shaderId);
    }
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType) {
    // get code string from shader file
    std::optional<std::string> result = LoadTextFile(filename);
    if (!result.has_value()) {
        return false;
    }

    std::string& code = result.value();
    const char* codePtr = code.c_str();
    int32_t codeLength = static_cast<int32_t>(code.length());

    //create and compile shader
    m_shaderId = glCreateShader(shaderType);
    glShaderSource(m_shaderId, 1, (const GLchar* const*)&codePtr, &codeLength);
    glCompileShader(m_shaderId);

    //check compile error
    int isSuccess = 0;
    glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &isSuccess);
    if (!isSuccess) {
        char infoLog[1024];
        glGetShaderInfoLog(m_shaderId, 1024, nullptr, infoLog);
        std::cout << "fail to compile shader : " << filename << '\n' << "reason : " << infoLog << std::endl;
        return false;
    }
    return true;
}