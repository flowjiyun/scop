#pragma once

#include "common.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"

CLASS_PTR(Context)
class Context {
    public:
        static ContextUPtr Create();
        void Render();

    private:
        Context() = default;
        bool Init();
        ProgramUPtr m_program;
        VertexLayoutUPtr m_vertexLayout;
        BufferUPtr m_vertextBuffer;
        BufferUPtr m_indexBuffer;
        uint32_t m_texture;
};