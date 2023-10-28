#pragma once

#include "common.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"

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
        TextureUPtr m_texture;
        TextureUPtr m_texture2;
};