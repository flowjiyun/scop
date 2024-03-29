#include "program.h"

ProgramUPtr Program::Create(const std::vector<ShaderPtr> &shaders) {
  ProgramUPtr program = std::unique_ptr<Program>(new Program());
  if (!program->Link(shaders)) {
    return nullptr;
  }
  return std::move(program);
}

ProgramUPtr Program::Create(const std::string &vertexShaderFileName,
                            const std::string &fragmentShaderFileName) {
  ShaderPtr vs = Shader::CreateFromFile(vertexShaderFileName, GL_VERTEX_SHADER);
  ShaderPtr fs =
      Shader::CreateFromFile(fragmentShaderFileName, GL_FRAGMENT_SHADER);
  if (!vs || !fs) {

    return nullptr;
  }
  return std::move(Create({vs, fs}));
}

Program::~Program() {
  if (m_programId) {
    glDeleteProgram(m_programId);
  }
}

void Program::Use() const { glUseProgram(m_programId); }

void Program::SetUniform(const std::string &name, int value) {
  glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Program::SetUniform(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Program::SetUniform(const std::string &name, float value) {
  glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Program::SetUniform(const std::string &name, const glm::vec2 &value) {
  auto transformLoc = glGetUniformLocation(m_programId, name.c_str());
  glUniform2fv(transformLoc, 1, glm::value_ptr(value));
}

void Program::SetUniform(const std::string &name, const glm::vec3 &value) {
  auto transformLoc = glGetUniformLocation(m_programId, name.c_str());
  glUniform3fv(transformLoc, 1, glm::value_ptr(value));
}

void Program::SetUniform(const std::string &name, const glm::vec4 &value) {
  auto transformLoc = glGetUniformLocation(m_programId, name.c_str());
  glUniform4fv(transformLoc, 1, glm::value_ptr(value));
}

void Program::SetUniform(const std::string &name, const glm::mat4 &value) {
  auto transformLoc = glGetUniformLocation(m_programId, name.c_str());
  glUniformMatrix4fv(transformLoc, 1, false, glm::value_ptr(value));
}

bool Program::Link(const std::vector<ShaderPtr> &shaders) {
  m_programId = glCreateProgram();
  for (auto &shader : shaders) {
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
