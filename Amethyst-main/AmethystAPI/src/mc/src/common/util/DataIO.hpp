#pragma once
#include <string>
#include <mc/src-deps/core/headerIncludes/gsl_includes.hpp>
#include <mc/src-deps/core/utility/Result.hpp>
#include <amethyst/Log.hpp>
#include <mc/src/common/world/phys/Vec3.hpp>
#include <mc/src/common/world/phys/Vec2.hpp>
#include <mc/src/common/world/level/ChunkPos.hpp>

class IDataOutput {
public:
    virtual ~IDataOutput() = default;
    virtual void writeString(std::string_view) = 0;
    virtual void writeLongString(std::string_view) = 0;
    virtual void writeFloat(float) = 0;
    virtual void writeDouble(double) = 0;
    virtual void writeByte(char) = 0;
    virtual void writeShort(short) = 0;
    virtual void writeInt(int) = 0;
    virtual void writeLongLong(int64_t) = 0;
    virtual void writeBytes(const void*, size_t) = 0;

    void writeVec3(const Vec3& vec) {
        writeFloat(vec.x);
        writeFloat(vec.y);
        writeFloat(vec.z);
    }

    void writeVec2(const Vec2& vec) {
        writeFloat(vec.x);
        writeFloat(vec.y);
    }

    void writeBlockPos(const BlockPos& pos) {
        writeInt(pos.x);
        writeInt(pos.y);
        writeInt(pos.z);
    }

    void writeChunkPos(const ChunkPos& pos) {
        writeInt(pos.x);
        writeInt(pos.z);
    }
};

class IDataInput {
public:
    virtual ~IDataInput() = default;
    virtual Bedrock::Result<std::string, std::error_code> readString() = 0;
    virtual Bedrock::Result<std::string, std::error_code> readLongString() = 0;
    virtual Bedrock::Result<float, std::error_code> readFloat() = 0;
    virtual Bedrock::Result<double, std::error_code> readDouble() = 0;
    virtual Bedrock::Result<char, std::error_code> readByte() = 0;
    virtual Bedrock::Result<short, std::error_code> readShort() = 0;
    virtual Bedrock::Result<int, std::error_code> readInt() = 0;
    virtual Bedrock::Result<int64_t, std::error_code> readLongLong() = 0;
    virtual Bedrock::Result<bool, std::error_code> readBytes(void*, size_t) = 0;
    virtual size_t numBytesLeft() const = 0;

    Vec3 readVec3()
    {
        float x = readFloat().value();
        float y = readFloat().value();
        float z = readFloat().value();
        return Vec3(x, y, z);
    }

    Vec2 readVec2()
    {
        float x = readFloat().value();
        float y = readFloat().value();
        return Vec2(x, y);
    }

    BlockPos readBlockPos()
    {
        int x = readInt().value();
        int y = readInt().value();
        int z = readInt().value();
        return BlockPos(x, y, z);
    }

    ChunkPos readChunkPos()
    {
        int x = readInt().value();
        int z = readInt().value();
        return ChunkPos(x, z);
    }
};

class BytesDataOutput : public IDataOutput {
public:
    virtual ~BytesDataOutput() = default;

    void writeString(std::string_view v) override
    {
        int16_t length = static_cast<int16_t>(v.size() & 0x7FFF);
        writeShort(length);
        writeBytes(v.data(), length);
    }

    void writeLongString(std::string_view v) override
    {
        int32_t length = static_cast<int32_t>(v.size());
        writeInt(length);
        writeBytes(v.data(), length);
    }

    void writeFloat(float v) override { writeBytes(&v, sizeof(v)); }
    void writeDouble(double v) override { writeBytes(&v, sizeof(v)); }
    void writeByte(char v) override { writeBytes(&v, sizeof(v)); }
    void writeShort(short v) override { writeBytes(&v, sizeof(v)); }
    void writeInt(int v) override { writeBytes(&v, sizeof(v)); }
    void writeLongLong(int64_t v) override { writeBytes(&v, sizeof(v)); }

    virtual void writeBytes(const void* data, size_t size) override = 0;
};

class BytesDataInput : public IDataInput {
public:
    virtual ~BytesDataInput() = default;

    Bedrock::Result<std::string, std::error_code> readString() override
    {
        auto lenResult = readShort();
        Assert(lenResult.has_value(), "Failed to read string length");
        short len = lenResult.value();
        Assert(len >= 0 && static_cast<size_t>(len) <= numBytesLeft(), "Invalid string length");

        std::string buffer(len, '\0');
        auto okResult = readBytes(buffer.data(), len);
        Assert(okResult.has_value() && okResult.value(), "Failed to read string bytes");

        return Bedrock::Result<std::string, std::error_code>(buffer);
    }

    Bedrock::Result<std::string, std::error_code> readLongString() override
    {
        auto lenResult = readInt();
        Assert(lenResult.has_value(), "Failed to read long string length");
        int32_t len = lenResult.value();
        Assert(len >= 0 && static_cast<size_t>(len) <= numBytesLeft(), "Invalid long string length");

        std::string buffer(len, '\0');
        auto okResult = readBytes(buffer.data(), len);
        Assert(okResult.has_value() && okResult.value(), "Failed to read long string bytes");

        return Bedrock::Result<std::string, std::error_code>(buffer);
    }

    Bedrock::Result<float, std::error_code> readFloat() override
    {
        float o{};
        auto okResult = readBytes(&o, sizeof(o));
        Assert(okResult.has_value() && okResult.value(), "Failed to read float");
        return Bedrock::Result<float, std::error_code>(o);
    }

    Bedrock::Result<double, std::error_code> readDouble() override
    {
        double o{};
        auto okResult = readBytes(&o, sizeof(o));
        Assert(okResult.has_value() && okResult.value(), "Failed to read double");
        return Bedrock::Result<double, std::error_code>(o);
    }

    Bedrock::Result<char, std::error_code> readByte() override
    {
        char o{};
        auto okResult = readBytes(&o, sizeof(o));
        Assert(okResult.has_value() && okResult.value(), "Failed to read byte");
        return Bedrock::Result<char, std::error_code>(o);
    }

    Bedrock::Result<short, std::error_code> readShort() override
    {
        short o{};
        auto okResult = readBytes(&o, sizeof(o));
        Assert(okResult.has_value() && okResult.value(), "Failed to read short");
        return Bedrock::Result<short, std::error_code>(o);
    }

    Bedrock::Result<int, std::error_code> readInt() override
    {
        int o{};
        auto okResult = readBytes(&o, sizeof(o));
        Assert(okResult.has_value() && okResult.value(), "Failed to read int");
        return Bedrock::Result<int, std::error_code>(o);
    }

    Bedrock::Result<int64_t, std::error_code> readLongLong() override
    {
        int64_t o{};
        auto okResult = readBytes(&o, sizeof(o));
        Assert(okResult.has_value() && okResult.value(), "Failed to read long long");
        return Bedrock::Result<int64_t, std::error_code>(o);
    }

    virtual Bedrock::Result<bool, std::error_code> readBytes(void*, size_t) override = 0;
    virtual size_t numBytesLeft() const override = 0;
};

struct StringByteOutput : BytesDataOutput {
public:
    StringByteOutput() = default;

    void writeBytes(const void* data, size_t size) override
    {
        const char* cdata = reinterpret_cast<const char*>(data);
        mBuffer.append(cdata, size);
    }

    std::string str() const
    {
        return mBuffer;
    }

private:
    std::string mBuffer;
};


class StringByteInput : public BytesDataInput {
public:
    uint64_t mIdx = 0;
    std::string mBuffer;

    explicit StringByteInput(std::string buffer)
        : mBuffer(std::move(buffer)) {}

    Bedrock::Result<bool, std::error_code> readBytes(void* buffer, size_t size) override
    {
        assert(mIdx + size <= mBuffer.size() && "Attempted to read past end of buffer");
        memcpy(buffer, mBuffer.data() + mIdx, size);
        mIdx += size;
        return Bedrock::Result<bool, std::error_code>(true);
    }

    size_t numBytesLeft() const override
    {
        return mBuffer.size() - mIdx;
    }
};