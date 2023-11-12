#pragma once

#include "common.h"

CLASS_PTR(Buffer)
class Buffer {
    public:
        static BufferUPtr CreateWithData(uint32_t bufferType, uint32_t usage, const void* data, size_t stride, size_t count);
        ~Buffer();
        uint32_t Get() const {return m_bufferId;}
        uint32_t GetStride() const {return m_stride;}
        uint32_t GetCount() const {return m_count;}
        void Bind() const;

    private:
        Buffer() = default;
        bool Init(uint32_t bufferType, uint32_t usage, const void* data, size_t stride, size_t count);
        uint32_t m_bufferId {0};
        uint32_t m_bufferType {0};
        uint32_t m_usage {0};
        uint32_t m_stride {0};
        uint32_t m_count {0};
};