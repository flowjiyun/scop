#include "context.h"
#include "image.h"

ContextUPtr Context::Create() {
    ContextUPtr context = std::unique_ptr<Context>(new Context());
    if (!context->Init()) {
        return nullptr;
    }
    return std::move(context);
}

void Context::Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    // static float time = 0.0f;
    // float t = sinf(time) * 0.5f + 0.5f;
    // auto loc = glGetUniformLocation(m_program->Get(), "color");
    // m_program->Use();
    // glUniform4f(loc, t*t, 2.0f*t*(1.0f-t), (1.0f-t)*(1.0f-t), 1.0f);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // time += 0.016f;
    m_program->Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool Context::Init() {
    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    };

    uint32_t indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };
    //init shaders
    ShaderPtr vertexShader = Shader::CreateFromFile("./shader/texture.vs", GL_VERTEX_SHADER);
    ShaderPtr fragmentShader = Shader::CreateFromFile("./shader/texture.fs", GL_FRAGMENT_SHADER);
    if (!vertexShader || !fragmentShader) {
        std::cout << "fail to init context" << std::endl;
        return false;
    }
    std::cout << "vertex shader id : " << vertexShader->Get() << std::endl;
    std::cout << "fragment shader id : " << fragmentShader->Get() << std::endl;

    //init program with shaders
    m_program = Program::Create({vertexShader, fragmentShader});
    if (!m_program) {
        std::cout << "fail to init context" << std::endl;
        return false;
    }
    std::cout << "program id : " << m_program->Get() << std::endl;

    //generate vertext Array & buffers in gpu memory
    m_vertexLayout = VertexLayout::Create();
    m_vertextBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(vertices));
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
    m_vertexLayout->SetAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 3);
    m_vertexLayout->SetAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 6);
    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(indices));

    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    
    //image loading
    ImageUPtr image = Image::Load("./image/container.jpeg");
    if (!image) {
        return false;
    }
    std::cout << "image : " << image->GetWidth() << " * " << image->GetHeight() << " " << image->GetChannelCount() << "chanel" << std::endl;

    ImageUPtr image2 = Image::Load("./image/awesomeface.png");
    if (!image2) {
        return false;
    }
    std::cout << "image2 : " << image->GetWidth() << " * " << image->GetHeight() << " " << image->GetChannelCount() << "chanel" << std::endl;

    // generate texture in gpu memory
    m_texture = Texture::CreateFromImage(image.get());
    m_texture2 = Texture::CreateFromImage(image2.get());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->Get());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_texture2->Get());

    m_program->Use();
    glUniform1i(glGetUniformLocation(m_program->Get(), "tex"), 0);
    glUniform1i(glGetUniformLocation(m_program->Get(), "tex2"), 1);

    return true;
}
