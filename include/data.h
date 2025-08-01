#ifndef GUARD_DATA_H
#define GUARD_DATA_H

#include "constants/moves.h"
#include "constants/trainers.h"
#include "constants/battle.h"
#include "difficulty.h"

#define MAX_TRAINER_ITEMS 4

#define TRAINER_PIC_WIDTH 64
#define TRAINER_PIC_HEIGHT 64
#define TRAINER_PIC_SIZE (TRAINER_PIC_WIDTH * TRAINER_PIC_HEIGHT / 2)

// Red and Leaf's back pics have 5 frames, but this is presumably irrelevant in the places this is used.
#define MAX_TRAINER_PIC_FRAMES 4

enum {
    BATTLER_AFFINE_NORMAL,
    BATTLER_AFFINE_EMERGE,
    BATTLER_AFFINE_RETURN,
};

struct MonCoords
{
    // This would use a bitfield, but some function
    // uses it as a u8 and casting won't match.
    u8 size; // u8 width:4, height:4;
    u8 y_offset;
};

struct TrainerSprite
{
    u8 y_offset;
    struct CompressedSpriteSheet frontPic;
    struct SpritePalette palette;
    const union AnimCmd *const *const animation;
    const struct Coords16 mugshotCoords;
    s16 mugshotRotation;
};

struct TrainerBacksprite
{
    struct MonCoords coordinates;
    struct CompressedSpriteSheet backPic;
    struct SpritePalette palette;
    const union AnimCmd *const *const animation;
};

#define MON_COORDS_SIZE(width, height) (DIV_ROUND_UP(width, 8) << 4 | DIV_ROUND_UP(height, 8))
#define GET_MON_COORDS_WIDTH(size) ((size >> 4) * 8)
#define GET_MON_COORDS_HEIGHT(size) ((size & 0xF) * 8)
#define TRAINER_PARTY_IVS(hp, atk, def, speed, spatk, spdef) (hp | (atk << 5) | (def << 10) | (speed << 15) | (spatk << 20) | (spdef << 25))
#define TRAINER_PARTY_EVS(hp, atk, def, speed, spatk, spdef) ((const u8[6]){hp,atk,def,spatk,spdef,speed})

// Shared by both trainer and frontier mons
// See CreateNPCTrainerPartyFromTrainer and CreateFacilityMon
struct TrainerMon
{
    const u8 *nickname;
    const u8 *ev;
    u32 iv;
    u16 moves[4];
    u16 species;
    u16 heldItem;
    u16 ability;
    u8 lvl;
    u8 ball;
    u8 friendship;
    u8 nature:5;
    bool8 gender:2;
    bool8 isShiny:1;
    u8 teraType:5;
    bool8 gigantamaxFactor:1;
    u8 shouldUseDynamax:1;
    u8 padding1:1;
    u8 dynamaxLevel:4;
    u8 padding2:4;
    u32 tags;
};

#define TRAINER_PARTY(partyArray) partyArray, .partySize = ARRAY_COUNT(partyArray)

enum TrainerBattleType 
{
    TRAINER_BATTLE_TYPE_SINGLES,
    TRAINER_BATTLE_TYPE_DOUBLES,
};

struct Trainer
{
    /*0x00*/ u64 aiFlags;
    /*0x04*/ const struct TrainerMon *party;
    /*0x08*/ u16 items[MAX_TRAINER_ITEMS];
    /*0x10*/ u8 trainerClass;
    /*0x11*/ u8 encounterMusic_gender; // last bit is gender
    /*0x12*/ u8 trainerPic;
    /*0x13*/ u8 trainerName[TRAINER_NAME_LENGTH + 1];
    /*0x1E*/ u8 battleType:2;
             u8 startingStatus:6;    // this trainer starts a battle with a given status. see include/constants/battle.h for values
    /*0x1F*/ u8 mugshotColor;
    /*0x20*/ u8 partySize;
    /*0x21*/ u8 poolSize;
    /*0x22*/ u8 poolRuleIndex;
    /*0x23*/ u8 poolPickIndex;
    /*0x24*/ u8 poolPruneIndex;
};

struct TrainerClass
{
    u8 name[13];
    u8 money;
    u16 ball;
};

struct TypeInfo
{
    u8 name[TYPE_NAME_LENGTH + 1];
    u8 generic[17];
    u8 palette;
    u16 zMove;
    u16 maxMove;
    u16 teraTypeRGBValue;    // Most values pulled from the Tera type icon palette.
    u16 damageCategory:2;    // Used for B_PHYSICAL_SPECIAL_SPLIT <= GEN_3
    u16 useSecondTypeIconPalette:1;
    u16 isSpecialCaseType:1;
    u16 isHiddenPowerType:1; // Changing this for any type will change the distribution of all Hidden Power types from vanilla.
    u16 padding:11;
    const u16 *const paletteTMHM;
    //u16 enhanceItem;
    //u16 berry;
    //u16 gem;
    //u16 plate;
    //u16 memory;
    //u16 zCrystal;
    //u16 teraShard;
    //u16 arceusForm;
};

struct FollowerMsgInfo
{
    const u8 *text;
    const u8 *script;
};

struct FollowerMessagePool
{
    const struct FollowerMsgInfo *messages;
    const u8 *script;
    u16 length;
};

extern const u16 gMinigameDigits_Pal[];
extern const u32 gMinigameDigits_Gfx[];

extern const struct SpriteFrameImage gBattlerPicTable_PlayerLeft[];
extern const struct SpriteFrameImage gBattlerPicTable_OpponentLeft[];
extern const struct SpriteFrameImage gBattlerPicTable_PlayerRight[];
extern const struct SpriteFrameImage gBattlerPicTable_OpponentRight[];
extern const struct SpriteFrameImage gTrainerBackPicTable_Brendan[];
extern const struct SpriteFrameImage gTrainerBackPicTable_May[];
extern const struct SpriteFrameImage gTrainerBackPicTable_Red[];
extern const struct SpriteFrameImage gTrainerBackPicTable_Leaf[];
extern const struct SpriteFrameImage gTrainerBackPicTable_RubySapphireBrendan[];
extern const struct SpriteFrameImage gTrainerBackPicTable_RubySapphireMay[];
extern const struct SpriteFrameImage gTrainerBackPicTable_Wally[];
extern const struct SpriteFrameImage gTrainerBackPicTable_Steven[];
extern const struct SpriteFrameImage gTrainerBackPicTable_Selene[];

extern const union AffineAnimCmd *const gAffineAnims_BattleSpritePlayerSide[];
extern const union AffineAnimCmd *const gAffineAnims_BattleSpriteOpponentSide[];
extern const union AffineAnimCmd *const gAffineAnims_BattleSpriteContest[];

extern const union AnimCmd sAnim_GeneralFrame0[];
extern const union AnimCmd sAnim_GeneralFrame3[];
extern const union AnimCmd *const gAnims_MonPic[];
extern const union AnimCmd *const gAnims_Trainer[];
extern const struct TrainerSprite gTrainerSprites[];
extern const struct TrainerBacksprite gTrainerBacksprites[];
extern const u16 gTrainerPicToTrainerBackPic[];

extern const struct Trainer gTrainers[DIFFICULTY_COUNT][TRAINERS_COUNT];
extern const struct Trainer gBattlePartners[DIFFICULTY_COUNT][PARTNER_COUNT];

extern const struct TrainerClass gTrainerClasses[TRAINER_CLASS_COUNT];

// Follower text messages
extern const struct FollowerMsgInfo gFollowerHappyMessages[];
extern const struct FollowerMsgInfo gFollowerNeutralMessages[];
extern const struct FollowerMsgInfo gFollowerSadMessages[];
extern const struct FollowerMsgInfo gFollowerUpsetMessages[];
extern const struct FollowerMsgInfo gFollowerAngryMessages[];
extern const struct FollowerMsgInfo gFollowerPensiveMessages[];
extern const struct FollowerMsgInfo gFollowerLoveMessages[];
extern const struct FollowerMsgInfo gFollowerSurpriseMessages[];
extern const struct FollowerMsgInfo gFollowerCuriousMessages[];
extern const struct FollowerMsgInfo gFollowerMusicMessages[];
extern const struct FollowerMsgInfo gFollowerPoisonedMessages[];

static inline u16 SanitizeTrainerId(u16 trainerId)
{
    if (trainerId >= TRAINERS_COUNT)
        return TRAINER_NONE;
    return trainerId;
}

static inline const struct Trainer *GetTrainerStructFromId(u16 trainerId)
{
    u32 sanitizedTrainerId = SanitizeTrainerId(trainerId);
    enum DifficultyLevel difficulty = GetTrainerDifficultyLevel(sanitizedTrainerId);

    return &gTrainers[difficulty][sanitizedTrainerId];
}

static inline const u8 GetTrainerClassFromId(u16 trainerId)
{
    u32 sanitizedTrainerId = SanitizeTrainerId(trainerId);
    enum DifficultyLevel difficulty = GetTrainerDifficultyLevel(sanitizedTrainerId);

    return gTrainers[difficulty][sanitizedTrainerId].trainerClass;
}

static inline const u8 *GetTrainerClassNameFromId(u16 trainerId)
{
    enum DifficultyLevel difficulty = GetBattlePartnerDifficultyLevel(trainerId);

    if (trainerId > TRAINER_PARTNER(PARTNER_NONE))
        return gTrainerClasses[gBattlePartners[difficulty][trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerClass].name;
    return gTrainerClasses[GetTrainerClassFromId(trainerId)].name;
}

static inline const u8 *GetTrainerNameFromId(u16 trainerId)
{
    u32 sanitizedTrainerId = SanitizeTrainerId(trainerId);

    enum DifficultyLevel difficulty = GetTrainerDifficultyLevel(sanitizedTrainerId);

    enum DifficultyLevel partnerDifficulty = GetBattlePartnerDifficultyLevel(trainerId);

    if (trainerId > TRAINER_PARTNER(PARTNER_NONE))
        return gBattlePartners[partnerDifficulty][trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerName;
    return gTrainers[difficulty][sanitizedTrainerId].trainerName;
}

static inline const u8 GetTrainerPicFromId(u16 trainerId)
{
    u32 sanitizedTrainerId = SanitizeTrainerId(trainerId);
    enum DifficultyLevel difficulty = GetTrainerDifficultyLevel(sanitizedTrainerId);
    enum DifficultyLevel partnerDifficulty = GetBattlePartnerDifficultyLevel(trainerId);

    if (trainerId > TRAINER_PARTNER(PARTNER_NONE))
        return gBattlePartners[partnerDifficulty][trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerPic;

    return gTrainers[difficulty][sanitizedTrainerId].trainerPic;
}

static inline const u8 GetTrainerStartingStatusFromId(u16 trainerId)
{
    return gTrainers[GetCurrentDifficultyLevel()][SanitizeTrainerId(trainerId)].startingStatus;
}

static inline const enum TrainerBattleType GetTrainerBattleType(u16 trainerId)
{
    u32 sanitizedTrainerId = SanitizeTrainerId(trainerId);
    enum DifficultyLevel difficulty = GetTrainerDifficultyLevel(sanitizedTrainerId);

    return gTrainers[difficulty][sanitizedTrainerId].battleType;
}

static inline const u8 GetTrainerPartySizeFromId(u16 trainerId)
{
    u32 sanitizedTrainerId = SanitizeTrainerId(trainerId);
    enum DifficultyLevel difficulty = GetTrainerDifficultyLevel(sanitizedTrainerId);

    return gTrainers[difficulty][sanitizedTrainerId].partySize;
}

static inline const bool32 DoesTrainerHaveMugshot(u16 trainerId)
{
    return gTrainers[GetCurrentDifficultyLevel()][SanitizeTrainerId(trainerId)].mugshotColor;
}

static inline const u8 GetTrainerMugshotColorFromId(u16 trainerId)
{
    return gTrainers[GetCurrentDifficultyLevel()][SanitizeTrainerId(trainerId)].mugshotColor;
}

static inline const u16 *GetTrainerItemsFromId(u16 trainerId)
{
    u32 sanitizedTrainerId = SanitizeTrainerId(trainerId);
    enum DifficultyLevel difficulty = GetTrainerDifficultyLevel(sanitizedTrainerId);

    return gTrainers[difficulty][sanitizedTrainerId].items;
}

static inline const struct TrainerMon *GetTrainerPartyFromId(u16 trainerId)
{
    u32 sanitizedTrainerId = SanitizeTrainerId(trainerId);
    enum DifficultyLevel difficulty = GetTrainerDifficultyLevel(sanitizedTrainerId);

    return gTrainers[difficulty][sanitizedTrainerId].party;
}

static inline const u64 GetTrainerAIFlagsFromId(u16 trainerId)
{
    u32 sanitizedTrainerId = SanitizeTrainerId(trainerId);
    enum DifficultyLevel difficulty = GetTrainerDifficultyLevel(sanitizedTrainerId);

    return gTrainers[difficulty][sanitizedTrainerId].aiFlags;
}

#endif // GUARD_DATA_H
