/// @symbolgeneration
#pragma once
#include <string>
#include <mc/src-deps/core/file/Path.hpp>
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"
#include <mc/src-deps/core/headerIncludes/gsl_includes.hpp>
#include <mc/src-deps/core/threading/EnableQueueForMainThread.hpp>
#include <mc/src-client/common/client/world/WorldID.hpp>
#include <mc/src/common/world/level/LevelSettings.hpp>
#include <amethyst/Imports.hpp>

class ILevelListCache;
class IContentManager; 
class FileArchiver;
class LevelDbEnv;
namespace Social {
    class IUserManager;
};
class HolographicPlatform;
class IContentKeyProvider;
class LevelSummary;
class LevelData; 
   
namespace World {

//class WorldID {
//public:
//    uint64_t mId;
//};

struct IdkWhatThisIsButItNeedsToBeAStruct {
    uint64_t data;
};

class WorldStorageHandler : public Bedrock::Threading::EnableQueueForMainThread {
public:
    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 49 8B E9 4D 8B E0 4C 8B F2}
    MC WorldStorageHandler(
        const Core::PathBuffer<std::string>& a2, 
        ILevelListCache& a3, 
        IContentManager& a4, 
        FileArchiver& a5, 
        Social::IUserManager& a6,  
        HolographicPlatform& a7, 
        const gsl::not_null<Bedrock::NonOwnerPointer<const IContentKeyProvider>>& a8,
        gsl::not_null<Bedrock::NonOwnerPointer<LevelDbEnv>> a9
    );

    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 49 8B E9 4D 8B E0 4C 8B F2}
    MC void _WorldStorageHandler(
        const Core::PathBuffer<std::string>& a2, 
        ILevelListCache& a3, 
        IContentManager& a4, 
        FileArchiver& a5, 
        Social::IUserManager& a6,  
        HolographicPlatform& a7, 
        const gsl::not_null<Bedrock::NonOwnerPointer<const IContentKeyProvider>>& a8,
        gsl::not_null<Bedrock::NonOwnerPointer<LevelDbEnv>> a9);

    virtual ~WorldStorageHandler();
    virtual void virtual1();
    virtual IdkWhatThisIsButItNeedsToBeAStruct updateOrCreateWorld(LevelData& levelData, LevelSummary& summary, std::shared_ptr<LevelSettings> settings);
};

};