/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"

class ItemStackRequestActionTransferBase;

enum class ItemStackNetResult : unsigned char {
    Success = 0x0000,
    Error = 0x0001,
    InvalidRequestActionType = 0x0002,
    ActionRequestNotAllowed = 0x0003,
    ScreenHandlerEndRequestFailed = 0x0004,
    ItemRequestActionHandlerCommitFailed = 0x0005,
    InvalidRequestCraftActionType = 0x0006,
    InvalidCraftRequest = 0x0007,
    InvalidCraftRequestScreen = 0x0008,
    InvalidCraftResult = 0x0009,
    InvalidCraftResultIndex = 0x000a,
    InvalidCraftResultItem = 0x000b,
    InvalidItemNetId = 0x000c,
    MissingCreatedOutputContainer = 0x000d,
    FailedToSetCreatedItemOutputSlot = 0x000e,
    RequestAlreadyInProgress = 0x000f,
    FailedToInitSparseContainer = 0x0010,
    ResultTransferFailed = 0x0011,
    ExpectedItemSlotNotFullyConsumed = 0x0012,
    ExpectedAnywhereItemNotFullyConsumed = 0x0013,
    ItemAlreadyConsumedFromSlot = 0x0014,
    ConsumedTooMuchFromSlot = 0x0015,
    MismatchSlotExpectedConsumedItem = 0x0016,
    MismatchSlotExpectedConsumedItemNetIdVariant = 0x0017,
    FailedToMatchExpectedSlotConsumedItem = 0x0018,
    FailedToMatchExpectedAllowedAnywhereConsumedItem = 0x0019,
    ConsumedItemOutOfAllowedSlotRange = 0x001a,
    ConsumedItemNotAllowed = 0x001b,
    PlayerNotInCreativeMode = 0x001c,
    InvalidExperimentalRecipeRequest = 0x001d,
    FailedToCraftCreative = 0x001e,
    FailedToGetLevelRecipe = 0x001f,
    FailedToFindRecipeByNetId = 0x0020,
    MismatchedCraftingSize = 0x0021,
    MissingInputSparseContainer = 0x0022,
    MismatchedRecipeForInputGridItems = 0x0023,
    EmptyCraftResults = 0x0024,
    FailedToEnchant = 0x0025,
    MissingInputItem = 0x0026,
    InsufficientPlayerLevelToEnchant = 0x0027,
    MissingMaterialItem = 0x0028,
    MissingActor = 0x0029,
    UnknownPrimaryEffect = 0x002a,
    PrimaryEffectOutOfRange = 0x002b,
    PrimaryEffectUnavailable = 0x002c,
    SecondaryEffectOutOfRange = 0x002d,
    SecondaryEffectUnavailable = 0x002e,
    DstContainerEqualToCreatedOutputContainer = 0x002f,
    DstContainerAndSlotEqualToSrcContainerAndSlot = 0x0030,
    FailedToValidateSrcSlot = 0x0031,
    FailedToValidateDstSlot = 0x0032,
    InvalidAdjustedAmount = 0x0033,
    InvalidItemSetType = 0x0034,
    InvalidTransferAmount = 0x0035,
    CannotSwapItem = 0x0036,
    CannotPlaceItem = 0x0037,
    UnhandledItemSetType = 0x0038,
    InvalidRemovedAmount = 0x0039,
    InvalidRegion = 0x003a,
    CannotDropItem = 0x003b,
    CannotDestroyItem = 0x003c,
    InvalidSourceContainer = 0x003d,
    ItemNotConsumed = 0x003e,
    InvalidNumCrafts = 0x003f,
    InvalidCraftResultStackSize = 0x0040,
    CannotRemoveItem = 0x0041,
    CannotConsumeItem = 0x0042,
    ScreenStackError = 0x0043,
};

class ItemStackRequestActionHandler {
public:
    class ScreenData;

    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B DA 48 8B F1 4C 8D 72}
    MC ItemStackNetResult _handleTransfer(const ItemStackRequestActionTransferBase& action, bool unk1, bool unk2, bool unk3);

    /// @signature {48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8D 91 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 80 7C 24 ? ? 74 ? 8B 44 24 ? 48 8D 54 24 ? 48 8B 4C 24 ? 89 44 24 ? E8 ? ? ? ? 48 8B 4C 24}
    MC ScreenData* _tryGetCurrentScreenData();
};