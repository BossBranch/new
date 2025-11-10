#pragma once
#include <amethyst/Imports.hpp>

class CreativeItemRegistry;
class ItemInstance;
class CreativeGroupInfo;

class CreativeItemEntry : public Bedrock::EnableNonOwnerReferences {
public:
	/// @vidx {0}
	MC virtual ~CreativeItemEntry();

//begin members:
	MC CreativeItemEntry(CreativeItemRegistry*, const ItemInstance&, unsigned int);

	MC CreativeItemEntry(CreativeItemEntry&&);

	// MC const TypedServerNetId<CreativeItemNetIdTag, unsigned int, 0>& getCreativeNetId() const;

	MC CreativeGroupInfo* getGroup() const;

	MC unsigned int getIndex() const;

	MC const ItemInstance& getItemInstance() const;

	MC UnknownReturn _setGroup(CreativeGroupInfo* unk0);

	// MC UnknownReturn operator(CreativeItemEntry&& unk0);
};