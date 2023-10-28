#include "context.h"

ContextUPtr Context::Create() {
    ContextUPtr context = std::unique_ptr<Context>(new Context());
    if (!context->Init()) {
        return nullptr;
    }
    return std::move(context);
}

void Context::Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    static float time = 0.0f;
    float t = sinf(time) * 0.5f + 0.5f;
    auto loc = glGetUniformLocation(m_program->Get(), "color");
    m_program->Use();
    glUniform4f(loc, t*t, 2.0f*t*(1.0f-t), (1.0f-t)*(1.0f-t), 1.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    time += 0.016f;
    // m_program->Use();
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool Context::Init() {
    float vertices[] = {
    0.5f, 0.5f, 0.0f, // top right
    0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, // top left
    };

    uint32_t indices[] = { // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3, // second triangle
    };
    //init shaders
    ShaderPtr vertexShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragmentShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    if (!vertexShader || !fragmentShader) {
        std::cout << "fail to init context" << std::endl;
        return false;
    }
    std::cout << "vertex shader id : " << vertexShader->Get() << std::endl;
    std::cout << "fragment shader id : " << fragmentShader->Get() << std::endl;

    //init program
    m_program = Program::Create({vertexShader, fragmentShader});
    if (!m_program) {
        std::cout << "fail to init context" << std::endl;
        return false;
    }
    std::cout << "program id : " << m_program->Get() << std::endl;

    m_vertexLayout = VertexLayout::Create();
    m_vertextBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(vertices));
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(indices));


    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

    return true;
}
