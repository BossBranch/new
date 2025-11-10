///@symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <optional>
#include <bitset>
#include <memory>
#include "mc/src/common/world/actor/Actor.hpp"
#include "mc/src/common/world/level/BlockPos.hpp"
#include "mc/src/common/ActorUniqueID.hpp"

class CompassSpriteCalculator {
public:
    int mFrame;
    float mRot;
    float mRotA;
    const std::function<BlockPos(const BlockSource*, Actor*)> mTargetToPointTo;
    const std::function<bool(const BlockSource*, Actor*)> mIsPointingAtTarget;
};

class MobAnimationComponent;
class MobHurtTimeComponent;
class BodyControl;

class BuiltInMobComponents {
public:
    gsl::not_null<MobAnimationComponent*> mMobAnimationComponent;
    gsl::not_null<MobHurtTimeComponent*> mMobHurtTimeComponent;
};

class ClockSpriteCalculator {
public:
    int mFrame;
    float mRot;
    float mRotA;
};

enum MobSpawnMethod : int32_t {
    bleh
};

#pragma pack(push, 8)
/// @vptr {0x4DE88C8}
class Mob : public Actor {
public:
    int mHurtDuration;
    float mHurtDir;
    float mOTilt;
    float mTilt;
    CompassSpriteCalculator mCompassSpriteCalc;
    CompassSpriteCalculator mRecoveryCompassSpriteCalc;
    ClockSpriteCalculator mClockSpriteCalc;
    float mAttackAnim;
    bool mSwinging;
    int mSwingTime;
    int mDeathTime;
    float mMovementComponentCurrentSpeed;
    bool mSurfaceMob;
    bool mNaturallySpawned;
    bool mWantsToBeJockey;
    bool mSpawnedXP;
    BuiltInMobComponents mBuiltInMobComponents;
    ActorUniqueID mCaravanHead;
    ActorUniqueID mCaravanTail;
    float mOAttackAnim;
    bool mHasBoundOrigin;
    BlockPos mBoundOrigin;
    std::optional<bool> mActuallyDoKnockbackOrNotReallyBadHackDoNotUse;
    MobSpawnMethod mSpawnMethod;
    bool mCreateAiOnReload;
    ActorUniqueID mTargetCaptainId;

    MC static uintptr_t $vtable_for_this; 

public:
    // MC virtuals
    /*void setSprinting(bool isSprinting);

    void swing(); 

    float getAttackAnim(float a) const {
        float delta = mAttackAnim - mOAttackAnim;
        if (delta < 0.0f) delta += 1.0f;
        return (delta * a) + mOAttackAnim;
    }

    void aiStep();*/
    
    /**@vidx {2}*/
    MC virtual bool hasComponent(const HashedString& unk0) const override;

    /**@vidx {3}*/
    MC virtual void outOfWorld() override;

    /**@vidx {4}*/
    MC virtual void reloadHardcoded(ActorInitializationMethod unk0, const VariantParameterList& unk1) override;

    /**@vidx {5}*/
    MC virtual void reloadHardcodedClient(ActorInitializationMethod unk0, const VariantParameterList& unk1) override;

    /**@vidx {6}*/
    MC virtual void initializeComponents(ActorInitializationMethod unk0, const VariantParameterList& unk1) override;

    /**@vidx {9}*/
    MC virtual void _doInitialMove() override;

    /**@vidx {15}*/
    MC virtual float getInterpolatedBodyRot(float unk0) const override;

    /**@vidx {16}*/
    MC virtual float getInterpolatedHeadRot(float unk0) const override;

    /**@vidx {17}*/
    MC virtual float getInterpolatedBodyYaw(float unk0) const override;

    /**@vidx {18}*/
    MC virtual float getYawSpeedInDegreesPerSecond() const override;

    /**@vidx {21}*/
    MC virtual void blockedByShield(const ActorDamageSource& unk0, Actor& unk1) override;

    /**@vidx {23}*/
    MC virtual void teleportTo(const Vec3& unk0, bool shouldStopRiding, int unk, int unkn2, bool keepVelocity) override;

    /**@vidx {26}*/
    MC virtual void normalTick() override;

    /// @vidx {27}
    MC virtual void baseTick() override;

    /**@vidx {29}*/
    MC virtual bool startRiding(Actor& unk0) override;

    /**@vidx {30}*/
    MC virtual void addPassenger(Actor& unk0) override;

    /**@vidx {43}*/
    MC virtual bool isImmobile() const override;

    /**@vidx {45}*/
    MC virtual bool isSleeping() const override;

    /**@vidx {46}*/
    MC virtual void setSleeping(bool unk0) override;

    /**@vidx {48}*/
    MC virtual bool isBlocking() const override;

    /**@vidx {50}*/
    MC virtual bool isAlive() const override;

    /**@vidx {52}*/
    MC virtual bool isSurfaceMob() const override;

    /**@vidx {55}*/
    MC virtual void setTarget(Actor* unk0) override;

    /**@vidx {57}*/
    MC virtual bool attack(Actor& unk0, const ActorDamageCause& unk1) override;

    /**@vidx {64}*/
    MC virtual bool canPowerJump() const override;

    /**@vidx {70}*/
    MC virtual ActorDamageCause getBlockDamageCause(const Block& unk0) const override;

    /**@vidx {71}*/
    MC virtual bool doFireHurt(int unk0) override;

    /**@vidx {74}*/
    MC virtual void handleEntityEvent(ActorEvent unk0, int unk1) override;

    /**@vidx {78}*/
    MC virtual ArmorMaterialType getArmorMaterialTypeInSlot(ArmorSlot unk0) const override;

    /**@vidx {79}*/
    MC virtual int getArmorTextureIndexInSlot(ArmorSlot unk0) const override;

    /**@vidx {80}*/
    MC virtual float getArmorColorInSlot(ArmorSlot unk0, int unk1) const override;

    /**@vidx {81}*/
    MC virtual void setEquippedSlot(Puv::Legacy::EquipmentSlot unk0, const ItemStack& unk1) override;

    /**@vidx {91}*/
    MC virtual bool canFreeze() const override;

    /**@vidx {94}*/
    MC virtual bool canChangeDimensionsUsingPortal() const override;

    /**@vidx {98}*/
    MC virtual float causeFallDamageToActor(float unk0, float unk1, ActorDamageSource unk2) override;

    /**@vidx {102}*/
    MC virtual bool canBePulledIntoVehicle() const override;

    /**@vidx {103}*/
    MC virtual bool inCaravan() const override;

    /**@vidx {108}*/
    MC virtual void buildDebugInfo(std::string& unk0) const override;

    /**@vidx {110}*/
    MC virtual int getDeathTime() const override;

    /**@vidx {117}*/
    MC virtual void swing() override;

    /**@vidx {130}*/
    MC virtual void kill() override;

    /**@vidx {131}*/
    MC virtual void die(const ActorDamageSource& unk0) override;

    /**@vidx {132}*/
    MC virtual bool shouldDropDeathLoot() const override;

    /**@vidx {144}*/
    MC virtual void updateEntitySpecificMolangVariables(RenderParams& unk0) override;

    /**@vidx {146}*/
    MC virtual bool _hurt(const ActorDamageSource& unk0, float unk1, bool unk2, bool unk3) override;

    /**@vidx {147}*/
    MC virtual void readAdditionalSaveData(const CompoundTag& unk0, DataLoadHelper& unk1) override;

    /**@vidx {148}*/
    MC virtual void addAdditionalSaveData(CompoundTag& unk0) const override;

    /**@vidx {149}*/
    MC virtual void _playStepSound(const BlockPos& unk0, const Block& unk1) override;

    /**@vidx {151}*/
    MC virtual void knockback(Actor* unk0, int unk1, float unk2, float unk3, float unk4, float unk5, float unk6);

    /**@vidx {152}*/
    MC virtual void _unknown_152();

    /**@vidx {153}*/
    MC virtual void setSprinting(bool unk0);

    /**@vidx {154}*/
    MC virtual Puv::Legacy::LevelSoundEvent getDeathSound();

    /**@vidx {155}*/
    MC virtual float getSpeed() const;

    /**@vidx {156}*/
    MC virtual void setSpeed(float unk0);

    /**@vidx {157}*/
    MC virtual void hurtEffects(const ActorDamageSource& unk0, float unk1, bool unk2, bool unk3);

    /**@vidx {158}*/
    MC virtual void aiStep();

    /**@vidx {159}*/
    MC virtual void pushActors();

    /**@vidx {160}*/
    MC virtual bool checkSpawnRules(bool unk0);

    /**@vidx {161}*/
    MC virtual bool checkSpawnObstruction() const;

    /**@vidx {162}*/
    MC virtual int getItemUseDuration() const;

    /**@vidx {163}*/
    MC virtual float getItemUseStartupProgress() const;

    /**@vidx {164}*/
    MC virtual float getItemUseIntervalProgress() const;

    /**@vidx {165}*/
    MC virtual float getMaxHeadXRot();

    /**@vidx {166}*/
    MC virtual bool isAlliedTo(Mob* unk0);

    /**@vidx {167}*/
    MC virtual bool doHurtTarget(Actor* unk0, const ActorDamageCause& unk1);

    /**@vidx {168}*/
    MC virtual int getArmorValue() const;

    /**@vidx {169}*/
    MC virtual void hurtArmorSlots(const ActorDamageSource& unk0, int unk1, std::bitset<4> unk2);

    /**@vidx {170}*/
    MC virtual void setDamagedArmor(ArmorSlot unk0, const ItemStack& unk1);

    /**@vidx {171}*/
    MC virtual void _unknown_171();

    /**@vidx {172}*/
    MC virtual void sendArmor(std::bitset<4> unk0);

    /**@vidx {173}*/
    MC virtual std::vector<const ItemStack*> getAllHand() const;

    /**@vidx {174}*/
    MC virtual std::vector<const ItemStack*> getAllEquipment() const;

    /**@vidx {175}*/
    MC virtual void dropEquipmentOnDeath();

    /**@vidx {176}*/
    MC virtual void dropEquipmentOnDeath(const ActorDamageSource& unk0);

    /**@vidx {177}*/
    MC virtual void clearVanishEnchantedItemsOnDeath();

    /**@vidx {178}*/
    MC virtual void sendInventory(bool unk0);

    /**@vidx {179}*/
    MC virtual float getDamageAfterEnchantReduction(const ActorDamageSource& unk0, float unk1) const;

    /**@vidx {180}*/
    MC virtual bool createAIGoals();

    /**@vidx {181}*/
    MC virtual void _unknown_181();

    /**@vidx {182}*/
    MC virtual bool setItemSlot(Puv::Legacy::EquipmentSlot unk0, const ItemStack& unk1);

    /**@vidx {183}*/
    MC virtual void setTransitioningSitting(bool unk0);

    /**@vidx {184}*/
    MC virtual float _getWalkTargetValue(const BlockPos& unk0);

    /**@vidx {185}*/
    MC virtual bool canExistWhenDisallowMob() const;

    /**@vidx {186}*/
    MC virtual std::unique_ptr<BodyControl> initBodyControl();

    /**@vidx {187}*/
    MC virtual void newServerAiStep();

    /**@vidx {188}*/
    MC virtual void tickDeath();

    /**@vidx {189}*/
    MC virtual AABB _getAdjustedAABBForSpawnCheck(const AABB& unk0, const Vec3& unk1) const;

    // non-MC virtuals
    int getCurrentSwingDuration() const;
};
#pragma pack(pop)

// 1.21.0.3
//static_assert(sizeof(Mob) == 1512);