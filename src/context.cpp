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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    // static float time = 0.0f;
    // float t = sinf(time) * 0.5f + 0.5f;
    // auto loc = glGetUniformLocation(m_program->Get(), "color");
    // m_program->Use();
    // glUniform4f(loc, t*t, 2.0f*t*(1.0f-t), (1.0f-t)*(1.0f-t), 1.0f);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // time += 0.016f;
    m_program->Use();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

bool Context::Init() {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

        0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
        };

    uint32_t indices[] = {
        0,  2,  1,  2,  0,  3,
        4,  5,  6,  6,  7,  4,
        8,  9, 10, 10, 11,  8,
        12, 14, 13, 14, 12, 15,
        16, 17, 18, 18, 19, 16,
        20, 22, 21, 22, 20, 23,
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
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    m_vertexLayout->SetAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, sizeof(float) * 3);
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

    // x축으로 -55도 회전
    // local coordinate -> world coordinate
    auto model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // 카메라는 원점으로부터 z축 방향으로 -3만큼 떨어짐
    auto view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    // 종횡비 4:3, 세로화각 45도의 원근 투영
    auto projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 10.0f);
    auto transform = projection * view * model;
    auto transformLoc = glGetUniformLocation(m_program->Get(), "transform");
    glUniformMatrix4fv(transformLoc, 1, false, glm::value_ptr(transform));
    return true;
}
