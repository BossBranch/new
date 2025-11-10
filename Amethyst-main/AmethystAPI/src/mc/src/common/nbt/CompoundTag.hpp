#pragma once
#include <map>
#include <string_view>
#include "mc/src/common/nbt/Tag.hpp"

class CompoundTagVariant;
class IntTag;
class StringTag;
class ListTag;
class ByteTag;
class Int64Tag;
class FloatTag;

typedef std::map<std::string, CompoundTagVariant, std::less<>> TagMap;

class CompoundTag : public Tag {
public:
    TagMap mTags;

public:
    CompoundTag();
    CompoundTag(CompoundTag&&) noexcept;
    CompoundTag& operator=(CompoundTag&&) noexcept;

    const Tag* get(std::string_view name) const;
    Tag* get(std::string_view);

    bool contains(std::string_view name) const;
    bool contains(std::string_view name, Tag::Type type) const;

    void clear();
    void deepCopy(const CompoundTag& other);
    std::unique_ptr<CompoundTag> clone() const;

    const CompoundTag* getCompound(std::string_view name) const;
    CompoundTag* getCompound(std::string_view name);

    const ListTag* getList(std::string_view name) const;
    ListTag* getList(std::string_view name);

    const ByteTag* getByteTag(std::string_view name) const;
    ByteTag* getByteTag(std::string_view name);
    uint8_t getByte(std::string_view) const;
    void putByte(std::string name, unsigned char value);

    const StringTag* getStringTag(std::string_view name) const;
    StringTag* getStringTag(std::string_view name);
    const std::string* getString(std::string_view name) const;
    void putString(std::string name, std::string value);

    const IntTag* getIntTag(std::string_view name) const;
    IntTag* getIntTag(std::string_view name);
    int getInt(std::string_view name) const;
	void putInt(std::string name, int value);

	const Int64Tag* getInt64Tag(std::string_view name) const;
	Int64Tag* getInt64Tag(std::string_view name);
	int64_t getInt64(std::string_view name) const;
	void putInt64(std::string name, int64_t value);

	const FloatTag* getFloatTag(std::string_view name) const;
	FloatTag* getFloatTag(std::string_view name);
	float getFloat(std::string_view name) const;
	void putFloat(std::string name, float value);

    Tag& put(std::string, Tag&&);
    Tag* put(std::string, std::unique_ptr<Tag>);

    virtual void write(IDataOutput& output) const override;
    virtual void load(IDataInput& input) override;
    virtual std::string toString() const override;
    virtual Tag::Type getId() const override;
    virtual std::unique_ptr<Tag> copy() const override;
    virtual void print(const std::string&, PrintStream&) const override;
    virtual size_t hash() const override;
    virtual bool equals(const Tag&) const override;

private:
    template <typename T>
    const T* get(std::string_view) const;

    template <typename T>
    T* get(std::string_view);
};