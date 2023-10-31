#pragma once

#include "common.h"
#include "shader.h"

CLASS_PTR(Program)
class Program {
    public:
        static ProgramUPtr Create(const std::vector<ShaderPtr>& shaders);
        ~Program();
        uint32_t Get() const {return m_programId;}
        void Use() const;
        void SetUniform(const std::string& name, int value);
        void SetUniform(const std::string& name, float value);
        void SetUniform(const std::string& name, const glm::vec3& value);
        void SetUniform(const std::string& name, const glm::mat4& value);
    
    private:
        Program() = default;
        bool Link(const std::vector<ShaderPtr>& shaders);
        uint32_t m_programId {0};
};

