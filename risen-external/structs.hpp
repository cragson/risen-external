#pragma once
#include <cstdint>
#include "math.hpp"

enum EEntityType : int32_t
{
	PC_HERO = 18,
	NPC = 17,
	CREATURE = 16,
	ITEM_COLLECTABLE_1 = 8,
	ITEM_OBJECT_INTERACT = 7,
	ITEM_COLLECTABLE_2 = 6,
	TRIGGERSCRIPT = 3
};


class CApplication
{
public:
	char pad_0000[ 32 ]; //0x0000
	void* m_pCameraBase1; //0x0020
	void* m_pCameraBase2; //0x0024
	void* m_pCConsole; //0x0028
	void* m_pCGuiFrame; //0x002C
	void* m_pCConsoleEdit; //0x0030
	void* m_pCConsoleListCtrl; //0x0034
	void* m_pCPropertyEditFrame; //0x0038
	char pad_003C[ 44 ]; //0x003C
	void* m_pCModuleAdmin; //0x0068
	void* m_pCameraBase3; //0x006C
	int32_t m_iGameWindowWidth; //0x0070
	int32_t m_iGameWindowHeight; //0x0074
	int32_t m_iGameWindowRefreshRate; //0x0078
	char pad_007C[ 964 ]; //0x007C
}; //Size: 0x0440


class Skills_PS
{
public:
	char pad_0000[ 16 ]; //0x0000
	int32_t m_iHealth; //0x0010
	int32_t m_iMana; //0x0014
	char pad_0018[ 4 ]; //0x0018
	int32_t m_iExperience; //0x001C
	char pad_0020[ 4 ]; //0x0020
	int32_t m_iHealthMaximum; //0x0024
	int32_t m_iManaMaximum; //0x0028
	int32_t m_iStrength; //0x002C
	int32_t m_iDexterity; //0x0030
	int32_t m_iWisdom; //0x0034
	int32_t m_iBladeProtection; //0x0038
	int32_t m_iBluntProtection; //0x003C
	int32_t m_iPiercingProtection; //0x0040
	int32_t m_iFireProtection; //0x0044
	int32_t m_iIceProtection; //0x0048
	int32_t m_iMagicProtection; //0x004C
	int32_t m_iSwordFighting; //0x0050
	int32_t m_iAxeFighting; //0x0054
	int32_t m_iStaffCombat; //0x0058
	int32_t m_iArchery; //0x005C
	int32_t m_iCrossbow; //0x0060
	int32_t m_iRuneSeal; //0x0064
	int32_t m_iFireball; //0x0068
	int32_t m_iFrost; //0x006C
	int32_t m_iMagicBullet; //0x0070
	int32_t m_iSmithing; //0x0074
	int32_t m_iProspecting; //0x0078
	int32_t m_iLockpicking; //0x007C
	int32_t m_iPickpocket; //0x0080
	int32_t m_iSneak; //0x0084
	int32_t m_iAcrobatics; //0x0088
	int32_t m_iAlchemy; //0x008C
	int32_t m_iCreateScrolls; //0x0090
	int32_t m_iGutAnimals; //0x0094
	char pad_0098[ 236 ]; //0x0098
}; //Size: 0x0184


class NPC_t
{
public:
	char pad_0000[8]; //0x0000
	NPC_t* m_pLastCreature; //0x0008
	NPC_t* m_pNextCreature; //0x000C
	char pad_0010[12]; //0x0010
	class EntityClasses_NPC* m_pEntityClasses; //0x001C
	char pad_0020[68]; //0x0020
	vec3 m_vecWorldPos1; //0x0064
	char pad_0070[4]; //0x0070
	vec3 m_vecWorldPos2; //0x0074
	vec3 m_vecWorldUpPos; //0x0080
	char pad_008C[4]; //0x008C
	vec3 m_vecWorldPos3; //0x0090
	char pad_009C[32]; //0x009C
	class Illuminated_PS* m_pIlluminated; //0x00BC
	char pad_00C0[32]; //0x00C0
	matrix4x4 m_LocalMatrix; //0x00E0
	char pad_0120[64]; //0x0120
	class EntityNamePtr* m_ppName; //0x0160
	char pad_0164[20]; //0x0164
}; //Size: 0x0178

class EntityClasses_NPC
{
public:
	class Navigation_PS* m_pNavigation; //0x0000
	class DynamicCollisionCircle_PS* m_pDynamicCollisionCircle; //0x0004
	class RigidBody_PS* m_pRigidBody; //0x0008
	class CollisionShape_PS* m_pCollisionShape; //0x000C
	class CharacterMovement_PS* m_pCharacterMovement; //0x0010
	class NPC_PS* m_pNPC; //0x0014
	class N00000656* m_pInventory; //0x0018
	class ScriptRoutine_PS* m_pScriptRoutine; //0x001C
	class Interaction_PS* m_pInteraction; //0x0020
	class N0000089C* m_pDamage; //0x0024
	void* m_pDialog; //0x0028
	class N00000906* m_pIlluminated; //0x002C
	class Party_PS* m_pParty; //0x0030
	class Effect_PS* m_pEffect; //0x0034
	class Animation_PS* m_pAnimation; //0x0038
	class N00000ABA* m_pSkills; //0x003C
	class CombatSystem_PS* m_pCombatSystem; //0x0040
}; //Size: 0x0040

class Creature_t
{
public:
	char pad_0000[8]; //0x0000
	Creature_t* m_pLastCreature; //0x0008
	Creature_t* m_pNextCreature; //0x000C
	char pad_0010[12]; //0x0010
	class EntityClasses_Creature* m_pEntityClasses; //0x001C
	char pad_0020[68]; //0x0020
	vec3 m_vecWorldPos1; //0x0064
	char pad_0070[4]; //0x0070
	vec3 m_vecWorldPos2; //0x0074
	vec3 m_vecWorldUpPos; //0x0080
	char pad_008C[4]; //0x008C
	vec3 m_vecWorldPos3; //0x0090
	char pad_009C[32]; //0x009C
	class Illuminated_PS* m_pIlluminated; //0x00BC
	char pad_00C0[32]; //0x00C0
	matrix4x4 m_LocalMatrix; //0x00E0
	char pad_0120[64]; //0x0120
	class EntityNamePtr* m_ppName; //0x0160
	char pad_0164[20]; //0x0164
}; //Size: 0x0178


class Illuminated_PS
{
public:
	char pad_0000[8]; //0x0000
	class N000001EC* m_pEntity; //0x0008
	char pad_000C[52]; //0x000C
	float m_flGlow; //0x0040
}; //Size: 0x0044


class EntityNamePtr
{
public:
	class EntityName* m_pName; //0x0000
	char pad_0004[64]; //0x0004
}; //Size: 0x0044

class EntityName
{
public:
	char* m_pszName; //0x0000
}; //Size: 0x0004


class EntityClasses_Creature
{
public:
	class Navigation_PS* m_pNavigation; //0x0000
	class DynamicCollisionCircle_PS* m_pDynamicCollisionCircle; //0x0004
	class RigidBody_PS* m_pRigidBody; //0x0008
	class CollisionShape_PS* m_pCollisionShape; //0x000C
	class CharacterMovement_PS* m_pCharacterMovement; //0x0010
	class NPC_PS* m_pNPC; //0x0014
	class N00000656* m_pInventory; //0x0018
	class ScriptRoutine_PS* m_pScriptRoutine; //0x001C
	class Interaction_PS* m_pInteraction; //0x0020
	class N0000089C* m_pDamage; //0x0024
	class N00000906* m_pIlluminated; //0x0028
	class Party_PS* m_pParty; //0x002C
	class Effect_PS* m_pEffect; //0x0030
	class Animation_PS* m_pAnimation; //0x0034
	class N00000ABA* m_pSkills; //0x0038
	class CombatSystem_PS* m_pCombatSystem; //0x003C
}; //Size: 0x0040

class Navigation_PS
{
public:
	char pad_0000[8]; //0x0000
	void* m_pEntity; //0x0008
	char pad_000C[28]; //0x000C
	vec3 m_vecWorldPos; //0x0028
	char pad_0034[444]; //0x0034
}; //Size: 0x01F0


class DynamicCollisionCircle_PS
{
public:
	char pad_0000[8]; //0x0000
	void* m_pEntity; //0x0008
	char pad_000C[4]; //0x000C
	float N000002D7; //0x0010
	vec3 N000002D8; //0x0014
	char pad_0020[4]; //0x0020
	float N000002DA; //0x0024
	char pad_0028[4]; //0x0028
	float N000002DC; //0x002C
	char pad_0030[12]; //0x0030
	vec3 m_vecWorldPos; //0x003C
	char pad_0048[4]; //0x0048
	float N000002E2; //0x004C
	char pad_0050[4]; //0x0050
	vec4 N000002E4; //0x0054
	char pad_0064[100]; //0x0064
}; //Size: 0x00C8


class RigidBody_PS
{
public:
	char pad_0000[4]; //0x0000
	uint32_t N00000403; //0x0004
	void* m_pEntity; //0x0008
	int32_t N00000405; //0x000C
	int32_t N00000406; //0x0010
	float N00000407; //0x0014
	char pad_0018[56]; //0x0018
	float N00000416; //0x0050
	char pad_0054[36]; //0x0054
	int32_t m_iRigidBodyFlag; //0x0078
	char pad_007C[28]; //0x007C
	vec3 m_vecWorldPos1; //0x0098
	char pad_00A4[12]; //0x00A4
	float N0000042C; //0x00B0
	vec3 m_vecWorldPos2; //0x00B4
	char pad_00C0[12]; //0x00C0
	float N00000431; //0x00CC
	char pad_00D0[28]; //0x00D0
	float N00000439; //0x00EC
	char pad_00F0[8]; //0x00F0
	float N0000043C; //0x00F8
	char pad_00FC[4]; //0x00FC
	float N0000043E; //0x0100
	float N0000043F; //0x0104
}; //Size: 0x0108


class CollisionShape_PS
{
public:
	char pad_0000[8]; //0x0000
	void* m_pEntity; //0x0008
	char pad_000C[8]; //0x000C
	int32_t m_iCollisionGroup; //0x0014
	char pad_0018[4]; //0x0018
	int32_t m_iPhysicsRangeType; //0x001C
	char pad_0020[48]; //0x0020
}; //Size: 0x0050


class CharacterMovement_PS
{
public:
	char pad_0000[8]; //0x0000
	class Creature_t* m_pEntity; //0x0008
	char pad_000C[16]; //0x000C
	float N00000553; //0x001C
	float N00000554; //0x0020
	float N00000555; //0x0024
	float N00000556; //0x0028
	float N00000557; //0x002C
	float N00000558; //0x0030
	float N00000559; //0x0034
	float N0000055A; //0x0038
	float N0000055B; //0x003C
	float N0000055C; //0x0040
	char pad_0044[4]; //0x0044
	float N0000055E; //0x0048
	float N0000055F; //0x004C
	float N00000560; //0x0050
	float N00000561; //0x0054
	float N00000562; //0x0058
	float N00000563; //0x005C
	float N00000564; //0x0060
	float N00000565; //0x0064
	char pad_0068[4]; //0x0068
	float N00000567; //0x006C
	float N00000568; //0x0070
	char pad_0074[4]; //0x0074
	float N0000056A; //0x0078
	char pad_007C[4]; //0x007C
	float N0000056C; //0x0080
	float N0000056D; //0x0084
	float N0000056E; //0x0088
	float N0000056F; //0x008C
	float N00000570; //0x0090
	float N00000571; //0x0094
	char pad_0098[12]; //0x0098
	float N00000575; //0x00A4
	float N00000576; //0x00A8
	float N00000577; //0x00AC
	float N00000578; //0x00B0
	float N00000579; //0x00B4
	float N0000057A; //0x00B8
	float N0000057B; //0x00BC
	float N0000057C; //0x00C0
	float N0000057D; //0x00C4
	float N0000057E; //0x00C8
	float N0000057F; //0x00CC
	float N00000580; //0x00D0
	float N00000581; //0x00D4
	float N00000582; //0x00D8
	float N00000583; //0x00DC
	float N00000584; //0x00E0
	float N00000585; //0x00E4
	float N00000586; //0x00E8
	float N00000587; //0x00EC
	char pad_00F0[4]; //0x00F0
}; //Size: 0x00F4


class NPC_PS
{
public:
	char pad_0000[8]; //0x0000
	class Creature_t* m_pEntity; //0x0008
	char pad_000C[16]; //0x000C
	int32_t m_iGender; //0x001C
	char pad_0020[4]; //0x0020
	int32_t m_iBraveryOverride; //0x0024
	char pad_0028[4]; //0x0028
	int32_t m_iSpecies; //0x002C
	char pad_0030[4]; //0x0030
	int32_t m_iAttitude; //0x0034
	char pad_0038[4]; //0x0038
	int32_t m_iCrime; //0x003C
	char pad_0040[4]; //0x0040
	int32_t m_iComment; //0x0044
	char pad_0048[8]; //0x0048
	int32_t m_iReason1; //0x0050
	char pad_0054[4]; //0x0054
	int32_t m_iReason2; //0x0058
	char pad_005C[4]; //0x005C
	int32_t m_iReason3; //0x0060
	char pad_0064[4]; //0x0064
	int32_t m_iFight; //0x0068
	char pad_006C[52]; //0x006C
	int32_t m_iGuardStatus; //0x00A0
	char pad_00A4[36]; //0x00A4
	char* m_pszName; //0x00C8
	char pad_00CC[36]; //0x00CC
	char* m_pszAnimation; //0x00F0
	char pad_00F4[4]; //0x00F4
}; //Size: 0x00F8

class ScriptRoutine_PS
{
public:
	char pad_0000[8]; //0x0000
	class Creature_t* m_pEntity; //0x0008
	char pad_000C[12]; //0x000C
	char* m_pszTask; //0x0018
	char pad_001C[32]; //0x001C
	char* m_pszState; //0x003C
	char pad_0040[8]; //0x0040
	int32_t m_iAniState1; //0x0048
	char pad_004C[4]; //0x004C
	int32_t m_iAniState2; //0x0050
	char pad_0054[16]; //0x0054
	int32_t m_iAmbientAction; //0x0064
	char pad_0068[4]; //0x0068
	int32_t m_iAIMode1; //0x006C
	char pad_0070[4]; //0x0070
	int32_t m_iAIMode2; //0x0074
	char pad_0078[8]; //0x0078
	int32_t m_iHitDirection; //0x0080
	char pad_0084[332]; //0x0084
}; //Size: 0x01D0

class Interaction_PS
{
public:
	char pad_0000[8]; //0x0000
	class Creature_t* m_pEntity; //0x0008
	char pad_000C[8]; //0x000C
	int32_t m_iInteractionUseType; //0x0014
	char pad_0018[108]; //0x0018
	int32_t m_iFocusPriority; //0x0084
	char pad_0088[4]; //0x0088
	int32_t m_iFocusNameType; //0x008C
	char pad_0090[136]; //0x0090
}; //Size: 0x0118


class Damage_PS
{
public:
	char pad_0000[8]; //0x0000
	class Creature_t* m_pEntity; //0x0008
	char pad_000C[8]; //0x000C
	int32_t m_iDamageType; //0x0014
	char pad_0018[100]; //0x0018
	int32_t m_iInteractionType; //0x007C
	char pad_0080[96]; //0x0080
}; //Size: 0x00E0


class Party_PS
{
public:
	char pad_0000[120]; //0x0000
}; //Size: 0x0078

class Effect_PS
{
public:
	char pad_0000[8]; //0x0000
	class Creature_t* m_pEntity; //0x0008
	char pad_000C[36]; //0x000C
	int32_t m_iEffectTargetMode; //0x0030
	char pad_0034[12]; //0x0034
	int32_t m_iEffectLoopMode; //0x0040
	char pad_0044[4]; //0x0044
	int32_t m_iEffectDecayMode; //0x0048
	char pad_004C[4]; //0x004C
	int32_t m_iEffectStopMode; //0x0050
	float N00000985; //0x0054
	float N00000986; //0x0058
	float N00000987; //0x005C
	float N00000988; //0x0060
	char pad_0064[8]; //0x0064
	float N0000098B; //0x006C
	char pad_0070[36]; //0x0070
	float N00000995; //0x0094
	char pad_0098[8]; //0x0098
}; //Size: 0x00A0


class Animation_PS
{
public:
	char pad_0000[8]; //0x0000
	class Creature_t* m_pEntity; //0x0008
	char pad_000C[12]; //0x000C
	float N000009E8; //0x0018
	char pad_001C[16]; //0x001C
	float N000009ED; //0x002C
	float N000009EE; //0x0030
	float N000009EF; //0x0034
	float N000009F0; //0x0038
	float N000009F1; //0x003C
	float N000009F2; //0x0040
	char pad_0044[4]; //0x0044
	float N000009F4; //0x0048
	char pad_004C[56]; //0x004C
	float N00000A03; //0x0084
	float N00000A04; //0x0088
	char pad_008C[36]; //0x008C
	float N00000A0E; //0x00B0
	float N00000A0F; //0x00B4
	float N00000A10; //0x00B8
	float N00000A11; //0x00BC
	float N00000A12; //0x00C0
	float N00000A13; //0x00C4
	char pad_00C8[96]; //0x00C8
	float N00000A2C; //0x0128
	char pad_012C[404]; //0x012C
}; //Size: 0x02C0


class CombatSystem_PS
{
public:
	char pad_0000[8]; //0x0000
	class Creature_t* m_pEntity; //0x0008
	char pad_000C[4]; //0x000C
	char* m_szEntityName; //0x0010
	char pad_0014[12]; //0x0014
	int32_t m_iCombatFightAIMode; //0x0020
	char pad_0024[56]; //0x0024
	float N00000AFB; //0x005C
	char pad_0060[8]; //0x0060
	float N00000AFE; //0x0068
	float N00000AFF; //0x006C
}; //Size: 0x0070
