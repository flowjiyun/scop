#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType) {
     ShaderUPtr shader = std::unique_ptr<Shader>(new Shader());
}