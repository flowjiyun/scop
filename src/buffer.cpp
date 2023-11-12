#include "buffer.h"

BufferUPtr Buffer::CreateWithData(uint32_t bufferType, uint32_t usage, const void* data, size_t stride, size_t count) {
    BufferUPtr buffer = std::unique_ptr<Buffer>(new Buffer());
    if (!buffer->Init(bufferType, usage, data, stride, count)) {
        return nullptr;
    }
    return std::move(buffer);
}

Buffer::~Buffer() {
    if (m_bufferId) {
        glDeleteBuffers(1, &m_bufferId);
    }
}

void Buffer::Bind() const {
    glBindBuffer(m_bufferType, m_bufferId);
}

bool Buffer::Init(uint32_t bufferType, uint32_t usage, const void* data, size_t stride, size_t count) {
    m_bufferType = bufferType;
    m_usage = usage;
    glGenBuffers(1, &m_bufferId);
    Bind();
    glBufferData(m_bufferType, stride * count, data, m_usage);
    return true;
}