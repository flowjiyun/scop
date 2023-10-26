#pragma once

#include "common.h"

CLASS_PTR(Buffer)
class Buffer {
    public:
        static BufferUPtr CreateWithData(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize);
        ~Buffer();
        uint32_t Get() const {return m_bufferId;}
        void Bind() const;

    private:
        Buffer() = default;
        bool Init(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize);
        uint32_t m_bufferId {0};
        uint32_t m_bufferType {0};
        uint32_t m_usage {0};
};