/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <cstddef>
#include "mc/src/common/world/phys/Vec3.hpp"
#include "amethyst/Memory.hpp"
#include <cstdint>
#include "glm/glm.hpp"
#include "mc/src-deps/minecraftrenderer/renderer/MeshData.hpp"
#include <mc/src/common/world/phys/Vec2.hpp>

struct TessellatorQuadInfo {
public:
    /* this + 0  */ unsigned char facing;
    /* this + 1  */ unsigned char twoFace;
    /* this + 4  */ Vec3 centroid;
};

static_assert(sizeof(TessellatorQuadInfo) == 0x10);

namespace mce {
    class Mesh; 
	class BufferResourceService;

    enum class PrimitiveMode : int {
        None = 0,
        QuadList = 1,
        TriangleList = 2,
        TriangleStrip = 3,
        LineList = 4,
        LineStrip = 5,
    };
}

//is_virtual = False
//hide_vtable = False
//struct_size = 562
//
//# (Type, Name, Size (in bytes), Offset (in bytes))
//struct = [
//("mce::MeshData", "mMeshData", 0xf0, 8),
//("bool", "mNoColor", 1, 484),
//("bool", "mTessellating", 1, 532),
//("bool", "mBuildFaceData", 1, 561),
//("std::vector<TessellatorQuadInfo>", "mQuadInfoList", 24, 376),
//("Vec3", "mPostTransformOffset", 12, 348),
//("unsigned int", "mCount", 4, 552),
//("bool", "mIsFormatFixed", 1, 0),
//("bool", "mApplyTransform", 1, 416),
//("Vec3", "mPostTransformScale", 12, 360),
//("bool", "mIsFormatFixed", 1, 0),
//("std::optional<unsigned int>", "mNextColor", 8, 328),
//("bool", "mVoidBeginEnd", 1, 485)
//]

class Tessellator {
public:
    /* this + 0   */ bool mIsFormatFixed;
    /* this + 1   */ std::byte padding1[7];
    /* this + 8   */ mce::MeshData mMeshData;
    /* this + 280 */ std::byte padding280[328 - 280];
    /* this + 328 */ std::optional<unsigned int> mNextColor;
    /* this + 336 */ std::byte padding336[12];
    /* this + 348 */ Vec3 mPostTransformOffset;
    /* this + 360 */ Vec3 mPostTransformScale;
    /* this + 372 */ std::byte padding372[4];
    /* this + 376 */ std::vector<TessellatorQuadInfo> mQuadInfoList;
    /* this + 400 */ std::byte padding400[16];
    /* this + 416 */ bool mApplyTransform;
    /* this + 417 */ std::byte padding417[67];
    /* this + 484 */ bool mNoColor;
    /* this + 485 */ bool mVoidBeginEnd;
    /* this + 486 */ std::byte padding486[46];
    /* this + 532 */ bool mTessellating;
    /* this + 533 */ std::byte padding533[19];
    /* this + 552 */ unsigned int mCount;
    /* this + 556 */ std::byte padding556[5];
    /* this + 561 */ bool mBuildFaceData;
	/* this + 562 */ std::byte padding562[592-562];

public:
	/// @sig {48 89 5C 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B F2 48 8B F9 48 89 4C 24 ? 48 89 54 24}
	MC Tessellator(std::weak_ptr<mce::BufferResourceService> bufferService);

    void begin(mce::PrimitiveMode mode, int maxVertices);
    void beginOverride();

    void vertex(float x, float y, float z);
    void vertex(const Vec3&);
    void vertex(float x, float y);
    void vertex(const Vec2&);
    void vertexUV(float x, float y, float z, float uvX, float uvY);
    void vertexUV(const Vec3&, float uvX, float uvY);

    void color(float r, float g, float b, float a);
    void color(uint32_t packed);

    void setPostTransformOffset(float xo, float yo, float zo);
    void setPosTransformOffset(Vec3 v);
    Vec3* getPostTransformOffset();
    void addPostTransformOffset(float x, float y, float z);
    void addPostTransformOffset(Vec3 v);

    void resetPostTransformScale();

    mce::Mesh end( uint64_t a3, std::string_view debugName, int a5);
    void clear();
    mce::Mesh endOverride(uint64_t a3, std::string_view debugName, int a5);
};

static_assert(offsetof(Tessellator, mBuildFaceData) == 561);
static_assert(sizeof(Tessellator) == 592);