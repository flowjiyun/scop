#include "program.h"

ProgramUPtr Program::Create(const std::vector<ShaderPtr>& shaders) {
    ProgramUPtr program = std::unique_ptr<Program>(new Program());
    if (!program->Link(shaders)) {
        return nullptr;
    }
    return std::move(program);
}

Program::~Program() {
    if (m_programId) {
        glDeleteProgram(m_programId);
    }
}

bool Program::Link(const std::vector<ShaderPtr>& shaders) {
    m_programId = glCreateProgram();
    for (auto& shader : shaders) {
        glAttachShader(m_programId, shader->Get());
    }
    glLinkProgram(m_programId);

    int isSuccess = 0;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &isSuccess);
    if (!isSuccess) {
        char infoLog[1024];
        glGetProgramInfoLog(m_programId, 1024, nullptr, infoLog);
        std::cout << "fail to Link program : " << infoLog << std::endl;
        return false;
    }
    return true;
}

