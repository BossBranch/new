#include <sstream>
#include "mc/src/common/nbt/DoubleTag.hpp"
#include "mc/src/common/util/DataIO.hpp"
#include "mc/src-deps/core/math/Math.hpp"

DoubleTag::DoubleTag() : Tag(), data(0) {}

DoubleTag::DoubleTag(double data) : Tag(), data(data) {}

void DoubleTag::write(IDataOutput& dos) const
{
    dos.writeDouble(data);
}

void DoubleTag::load(IDataInput& dis)
{
    data = dis.readDouble().value();
}

Tag::Type DoubleTag::getId() const
{
    return Type::Double;
}

std::string DoubleTag::toString() const
{
    std::stringstream ss;
    ss << data;
    return ss.str();
}

std::unique_ptr<Tag> DoubleTag::copy() const
{
    return std::make_unique<DoubleTag>(data);
}

bool DoubleTag::equals(const Tag& rhs) const
{
    if (Tag::equals(rhs)) {
        return data == static_cast<const DoubleTag&>(rhs).data;
    }
    else {
        return false;
    }
}

size_t DoubleTag::hash() const
{
    return std::hash<double>{}(data);
}