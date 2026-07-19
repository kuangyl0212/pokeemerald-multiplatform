#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "data.h"
#include "event_data.h"
#include "frontier_util.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "link.h"
#include "menu.h"
#include "palette.h"
#include "recorded_battle.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "trainer_hill.h"
#include "window.h"
#include "constants/battle_dome.h"
#include "constants/battle_string_ids.h"
#include "constants/frontier_util.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/trainers.h"
#include "constants/trainer_hill.h"
#include "constants/weather.h"

struct BattleWindowText
{
    u8 fillValue;
    u8 fontId;
    u8 x;
    u8 y;
    u8 letterSpacing;
    u8 lineSpacing;
    u8 speed;
    u8 fgColor;
    u8 bgColor;
    u8 shadowColor;
};

static void ChooseMoveUsedParticle(u8 *textPtr);
static void ChooseTypeOfMoveUsedString(u8 *dst);
static void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst);

static EWRAM_DATA u8 sBattlerAbilities[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA struct BattleMsgData *gBattleMsgDataPtr = NULL;

// todo: make some of those names less vague: attacker/target vs pkmn, etc.

static const u8 sText_Trainer1LoseText[] = _("{B_TRAINER1_LOSE_TEXT}");
static const u8 sText_PkmnGainedEXP[] = _("{CHN}{B_BUFF1}获得了{B_BUFF2}\n{B_BUFF3}点经验值！\p");
static const u8 sText_EmptyString4[] = _("");
static const u8 sText_ABoosted[] = _("{CHN}额外的");
static const u8 sText_PkmnGrewToLv[] = _("{CHN}{B_BUFF1}升级到了\nLv. {B_BUFF2}！{WAIT_SE}\p");
static const u8 sText_PkmnLearnedMove[] = _("{CHN}{B_BUFF1}学会了\n{B_BUFF2}！{WAIT_SE}\p");
static const u8 sText_TryToLearnMove1[] = _("{CHN}{B_BUFF1}想要\n学会{B_BUFF2}。\p");
static const u8 sText_TryToLearnMove2[] = _("{CHN}但是，{B_BUFF1}无法学会\n超过四个招式。\p");
static const u8 sText_TryToLearnMove3[] = _("{CHN}删除一个招式来\n给{B_BUFF2}腾出空间？");
static const u8 sText_PkmnForgotMove[] = _("{CHN}{B_BUFF1}忘记了\n{B_BUFF2}。\p");
static const u8 sText_StopLearningMove[] = _("{PAUSE 32}{CHN}停止学习\n{B_BUFF2}？");
static const u8 sText_DidNotLearnMove[] = _("{CHN}{B_BUFF1}没有学会\n{B_BUFF2}。\p");
static const u8 sText_UseNextPkmn[] = _("{CHN}使用下一只宝可梦？");
static const u8 sText_AttackMissed[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的\n招式没有命中！");
static const u8 sText_PkmnProtectedItself[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}\n保护了自己！");
static const u8 sText_AvoidedDamage[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}用{B_DEF_ABILITY}\n避免了伤害！");
static const u8 sText_PkmnMakesGroundMiss[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}用{B_DEF_ABILITY}使地面\n招式没有命中！");
static const u8 sText_PkmnAvoidedAttack[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}\n躲避了攻击！");
static const u8 sText_ItDoesntAffect[] = _("{CHN}对{B_DEF_NAME_WITH_PREFIX}\n没有效果……");
static const u8 sText_AttackerFainted[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}\n倒下了！\p");
static const u8 sText_TargetFainted[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}\n倒下了！\p");
static const u8 sText_PlayerGotMoney[] = _("{CHN}{B_PLAYER_NAME}赢得了\n¥{B_BUFF1}！\p");
static const u8 sText_PlayerWhiteout[] = _("{CHN}{B_PLAYER_NAME}没有\n可用的宝可梦了！\p");
static const u8 sText_PlayerWhiteout2[] = _("{CHN}{B_PLAYER_NAME}眼前发黑了！{PAUSE_UNTIL_PRESS}");
static const u8 sText_PreventsEscape[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}用{B_SCR_ACTIVE_ABILITY}\n阻止了逃跑！\p");
static const u8 sText_CantEscape2[] = _("{CHN}无法逃跑！\p");
static const u8 sText_AttackerCantEscape[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}无法逃跑！");
static const u8 sText_HitXTimes[] = _("{CHN}命中了{B_BUFF1}次！");
static const u8 sText_PkmnFellAsleep[] = _("{CHN}{B_EFF_NAME_WITH_PREFIX}\n睡着了！");
static const u8 sText_PkmnMadeSleep[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n使{B_EFF_NAME_WITH_PREFIX}睡着了！");
static const u8 sText_PkmnAlreadyAsleep[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}\n已经睡着了！");
static const u8 sText_PkmnAlreadyAsleep2[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}\n已经睡着了！");
static const u8 sText_PkmnWasntAffected[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}\n没有受到影响！");
static const u8 sText_PkmnWasPoisoned[] = _("{CHN}{B_EFF_NAME_WITH_PREFIX}\n中毒了！");
static const u8 sText_PkmnPoisonedBy[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n使{B_EFF_NAME_WITH_PREFIX}中毒了！");
static const u8 sText_PkmnHurtByPoison[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}被\n毒伤折磨！");
static const u8 sText_PkmnAlreadyPoisoned[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}已经\n中毒了。");
static const u8 sText_PkmnBadlyPoisoned[] = _("{CHN}{B_EFF_NAME_WITH_PREFIX}严重\n中毒了！");
static const u8 sText_PkmnEnergyDrained[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的\n能量被吸收了！");
static const u8 sText_PkmnWasBurned[] = _("{CHN}{B_EFF_NAME_WITH_PREFIX}烧伤了！");
static const u8 sText_PkmnBurnedBy[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n使{B_EFF_NAME_WITH_PREFIX}烧伤了！");
static const u8 sText_PkmnHurtByBurn[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}被\n烧伤折磨！");
static const u8 sText_PkmnAlreadyHasBurn[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}已经\n烧伤了。");
static const u8 sText_PkmnWasFrozen[] = _("{CHN}{B_EFF_NAME_WITH_PREFIX}被\n冻住了！");
static const u8 sText_PkmnFrozenBy[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n将{B_EFF_NAME_WITH_PREFIX}冻住了！");
static const u8 sText_PkmnIsFrozen[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}被\n冻住了！");
static const u8 sText_PkmnWasDefrosted[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的\n冰解除了！");
static const u8 sText_PkmnWasDefrosted2[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的\n冰解除了！");
static const u8 sText_PkmnWasDefrostedBy[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}被{B_CURRENT_MOVE}\n解冻了！");
static const u8 sText_PkmnWasParalyzed[] = _("{CHN}{B_EFF_NAME_WITH_PREFIX}麻痹了！\n可能无法行动！");
static const u8 sText_PkmnWasParalyzedBy[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n使{B_EFF_NAME_WITH_PREFIX}麻痹了！\l可能无法行动！");
static const u8 sText_PkmnIsParalyzed[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}麻痹了！\n无法行动！");
static const u8 sText_PkmnIsAlreadyParalyzed[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}已经\n麻痹了！");
static const u8 sText_PkmnHealedParalysis[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的\n麻痹治愈了！");
static const u8 sText_PkmnDreamEaten[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的\n梦被吃掉了！");
static const u8 sText_StatsWontIncrease[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的{B_BUFF1}\n无法再提高了！");
static const u8 sText_StatsWontDecrease[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_BUFF1}\n无法再降低了！");
static const u8 sText_TeamStoppedWorking[] = _("{CHN}我方的{B_BUFF1}\n停止了工作！");
static const u8 sText_FoeStoppedWorking[] = _("{CHN}敌方的{B_BUFF1}\n停止了工作！");
static const u8 sText_PkmnIsConfused[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}\n混乱了！");
static const u8 sText_PkmnHealedConfusion[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的\n混乱解除了！");
static const u8 sText_PkmnWasConfused[] = _("{CHN}{B_EFF_NAME_WITH_PREFIX}\n混乱了！");
static const u8 sText_PkmnAlreadyConfused[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}已经\n混乱了！");
static const u8 sText_PkmnFellInLove[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}\n陷入了爱情！");
static const u8 sText_PkmnInLove[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}爱上了\n{B_SCR_ACTIVE_NAME_WITH_PREFIX}！");
static const u8 sText_PkmnImmobilizedByLove[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}被\n爱情定身了！");
static const u8 sText_PkmnBlownAway[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}被\n吹走了！");
static const u8 sText_PkmnChangedType[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}变成了\n{B_BUFF1}属性！");
static const u8 sText_PkmnFlinched[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}畏缩了！");
static const u8 sText_PkmnRegainedHealth[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}\n回复了体力！");
static const u8 sText_PkmnHPFull[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的\nHP满了！");
static const u8 sText_PkmnRaisedSpDef[] = _("{CHN}{B_ATK_PREFIX2}的{B_CURRENT_MOVE}\n提高了特防！");
static const u8 sText_PkmnRaisedSpDefALittle[] = _("{CHN}{B_ATK_PREFIX2}的{B_CURRENT_MOVE}\n稍微提高了特防！");
static const u8 sText_PkmnRaisedDef[] = _("{CHN}{B_ATK_PREFIX2}的{B_CURRENT_MOVE}\n提高了防御！");
static const u8 sText_PkmnRaisedDefALittle[] = _("{CHN}{B_ATK_PREFIX2}的{B_CURRENT_MOVE}\n稍微提高了防御！");
static const u8 sText_PkmnCoveredByVeil[] = _("{CHN}{B_ATK_PREFIX2}的队伍被\n神秘护身笼罩！");
static const u8 sText_PkmnUsedSafeguard[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的队伍被\n神秘护身保护！");
static const u8 sText_PkmnSafeguardExpired[] = _("{CHN}{B_ATK_PREFIX3}的队伍不再被\n神秘护身保护！");
static const u8 sText_PkmnWentToSleep[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}\n睡着了！");
static const u8 sText_PkmnSleptHealthy[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}睡了一觉\n恢复了健康！");
static const u8 sText_PkmnWhippedWhirlwind[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}卷起了\n旋风！");
static const u8 sText_PkmnTookSunlight[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}吸收了\n阳光！");
static const u8 sText_PkmnLoweredHead[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}低下了\n头！");
static const u8 sText_PkmnIsGlowing[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}发出光芒！");
static const u8 sText_PkmnFlewHigh[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}飞到了\n高空！");
static const u8 sText_PkmnDugHole[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}挖了一个洞！");
static const u8 sText_PkmnHidUnderwater[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}潜入\n水下！");
static const u8 sText_PkmnSprangUp[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}跳了出来！");
static const u8 sText_PkmnSqueezedByBind[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}被{B_ATK_NAME_WITH_PREFIX}的\n紧束挤压！");
static const u8 sText_PkmnTrappedInVortex[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}被困在\n旋涡中！");
static const u8 sText_PkmnTrappedBySandTomb[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}被\n流沙地狱困住了！");
static const u8 sText_PkmnWrappedBy[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}被{B_ATK_NAME_WITH_PREFIX}\n卷紧了！");
static const u8 sText_PkmnClamped[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}夹住了\n{B_DEF_NAME_WITH_PREFIX}！");
static const u8 sText_PkmnHurtBy[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}被\n{B_BUFF1}伤害！");
static const u8 sText_PkmnFreedFrom[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}从\n{B_BUFF1}中解脱了！");
static const u8 sText_PkmnCrashed[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}继续冲撞\n结果撞倒了！");
const u8 gText_PkmnShroudedInMist[] = _("{CHN}{B_ATK_PREFIX2}被\n白雾笼罩！");
static const u8 sText_PkmnProtectedByMist[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}被\n白雾保护！");
const u8 gText_PkmnGettingPumped[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}正在\n蓄力！");
static const u8 sText_PkmnHitWithRecoil[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}受到\n反作用力伤害！");
static const u8 sText_PkmnProtectedItself2[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}保护了\n自己！");
static const u8 sText_PkmnBuffetedBySandstorm[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}被\n沙暴打击！");
static const u8 sText_PkmnPeltedByHail[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}被\n冰雹打击！");
static const u8 sText_PkmnsXWoreOff[] = _("{CHN}{B_ATK_PREFIX1}的{B_BUFF1}\n效果消失了！");
static const u8 sText_PkmnSeeded[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}被寄生了！");
static const u8 sText_PkmnEvadedAttack[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}躲避了\n攻击！");
static const u8 sText_PkmnSappedByLeechSeed[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的体力被\n寄生种子吸收！");
static const u8 sText_PkmnFastAsleep[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}正在\n沉睡。");
static const u8 sText_PkmnWokeUp[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}醒了过来！");
static const u8 sText_PkmnUproarKeptAwake[] = _("{CHN}但是{B_SCR_ACTIVE_NAME_WITH_PREFIX}的吵闹\n让它保持清醒！");
static const u8 sText_PkmnWokeUpInUproar[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}在\n吵闹中醒来！");
static const u8 sText_PkmnCausedUproar[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}引起了\n吵闹！");
static const u8 sText_PkmnMakingUproar[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}正在\n吵闹！");
static const u8 sText_PkmnCalmedDown[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}平静了下来。");
static const u8 sText_PkmnCantSleepInUproar[] = _("{CHN}但是{B_DEF_NAME_WITH_PREFIX}无法在\n吵闹中入睡！");
static const u8 sText_PkmnStockpiled[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}蓄积了\n{B_BUFF1}！");
static const u8 sText_PkmnCantStockpile[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}无法再\n蓄积了！");
static const u8 sText_PkmnCantSleepInUproar2[] = _("{CHN}但是{B_DEF_NAME_WITH_PREFIX}无法在\n吵闹中入睡！");
static const u8 sText_UproarKeptPkmnAwake[] = _("{CHN}但是吵闹让\n{B_DEF_NAME_WITH_PREFIX}保持清醒！");
static const u8 sText_PkmnStayedAwakeUsing[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}用{B_DEF_ABILITY}\n保持清醒！");
static const u8 sText_PkmnStoringEnergy[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}正在\n储存能量！");
static const u8 sText_PkmnUnleashedEnergy[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}释放了\n能量！");
static const u8 sText_PkmnFatigueConfusion[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}因为疲劳\n混乱了！");
static const u8 sText_PlayerPickedUpMoney[] = _("{CHN}{B_PLAYER_NAME}捡起了\n¥{B_BUFF1}！\p");
static const u8 sText_PkmnUnaffected[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}\n不受影响！");
static const u8 sText_PkmnTransformedInto[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}变成了\n{B_BUFF1}！");
static const u8 sText_PkmnMadeSubstitute[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}做出了\n替身！");
static const u8 sText_PkmnHasSubstitute[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}已经\n有替身了！");
static const u8 sText_SubstituteDamaged[] = _("{CHN}替身代替{B_DEF_NAME_WITH_PREFIX}\n承受了伤害！\p");
static const u8 sText_PkmnSubstituteFaded[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的\n替身消失了！\p");
static const u8 sText_PkmnMustRecharge[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}必须\n重新蓄力！");
static const u8 sText_PkmnRageBuilding[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的愤怒\n正在积聚！");
static const u8 sText_PkmnMoveWasDisabled[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_BUFF1}\n被禁止使用了！");
static const u8 sText_PkmnMoveDisabledNoMore[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的招式\n不再被禁止了！");
static const u8 sText_PkmnGotEncore[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}被\n安可了！");
static const u8 sText_PkmnEncoreEnded[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的安可\n结束了！");
static const u8 sText_PkmnTookAim[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}瞄准了\n{B_DEF_NAME_WITH_PREFIX}！");
static const u8 sText_PkmnSketchedMove[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}写生了\n{B_BUFF1}！");
static const u8 sText_PkmnTryingToTakeFoe[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}试图\n拉敌方同归于尽！");
static const u8 sText_PkmnTookFoe[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}拉\n{B_ATK_NAME_WITH_PREFIX}同归于尽！");
static const u8 sText_PkmnReducedPP[] = _("{CHN}减少了{B_DEF_NAME_WITH_PREFIX}的\n{B_BUFF1}{B_BUFF2}点！");
static const u8 sText_PkmnStoleItem[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}偷走了\n{B_DEF_NAME_WITH_PREFIX}的{B_LAST_ITEM}！");
static const u8 sText_TargetCantEscapeNow[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}现在\n无法逃跑了！");
static const u8 sText_PkmnFellIntoNightmare[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}陷入了\n恶梦！");
static const u8 sText_PkmnLockedInNightmare[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}被困在\n恶梦中！");
static const u8 sText_PkmnLaidCurse[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}削减自己的HP\n对{B_DEF_NAME_WITH_PREFIX}施加了诅咒！");
static const u8 sText_PkmnAfflictedByCurse[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}被\n诅咒折磨！");
static const u8 sText_SpikesScattered[] = _("{CHN}撒菱被散布在\n对手的周围！");
static const u8 sText_PkmnHurtBySpikes[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}被\n撒菱伤害！");
static const u8 sText_PkmnIdentified[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}识别了\n{B_DEF_NAME_WITH_PREFIX}！");
static const u8 sText_PkmnPerishCountFell[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的灭亡歌\n倒数到了{B_BUFF1}！");
static const u8 sText_PkmnBracedItself[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}打起了\n精神！");
static const u8 sText_PkmnEnduredHit[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}撑住了\n攻击！");
static const u8 sText_MagnitudeStrength[] = _("{CHN}震级{B_BUFF1}！");
static const u8 sText_PkmnCutHPMaxedAttack[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}削减自己的HP\n将攻击提升到最大！");
static const u8 sText_PkmnCopiedStatChanges[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}复制了\n{B_DEF_NAME_WITH_PREFIX}的能力变化！");
static const u8 sText_PkmnGotFree[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}从{B_DEF_NAME_WITH_PREFIX}的\n{B_BUFF1}中解脱了！");
static const u8 sText_PkmnShedLeechSeed[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}摆脱了\n寄生种子！");
static const u8 sText_PkmnBlewAwaySpikes[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}吹走了\n撒菱！");
static const u8 sText_PkmnFledFromBattle[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}从战斗中\n逃跑了！");
static const u8 sText_PkmnForesawAttack[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}预感到了\n攻击！");
static const u8 sText_PkmnTookAttack[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}承受了\n{B_BUFF1}的攻击！");
static const u8 sText_PkmnChoseXAsDestiny[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}选择了\n{B_CURRENT_MOVE}作为命运！");
static const u8 sText_PkmnAttack[] = _("{CHN}{B_BUFF1}的攻击！");
static const u8 sText_PkmnCenterAttention[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}成为了\n全场焦点！");
static const u8 sText_PkmnChargingPower[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}开始\n蓄力！");
static const u8 sText_NaturePowerTurnedInto[] = _("{CHN}自然之力变成了\n{B_CURRENT_MOVE}！");
static const u8 sText_PkmnStatusNormal[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的状态\n恢复正常了！");
static const u8 sText_PkmnSubjectedToTorment[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}被\n寻衅了！");
static const u8 sText_PkmnTighteningFocus[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}正在\n集中注意力！");
static const u8 sText_PkmnFellForTaunt[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}中了\n挑衅！");
static const u8 sText_PkmnReadyToHelp[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}准备\n帮助{B_DEF_NAME_WITH_PREFIX}！");
static const u8 sText_PkmnSwitchedItems[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}与对手\n交换了道具！");
static const u8 sText_PkmnObtainedX[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}获得了\n{B_BUFF1}。");
static const u8 sText_PkmnObtainedX2[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}获得了\n{B_BUFF2}。");
static const u8 sText_PkmnObtainedXYObtainedZ[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}获得了\n{B_BUFF1}。\p{B_DEF_NAME_WITH_PREFIX}获得了\n{B_BUFF2}。");
static const u8 sText_PkmnCopiedFoe[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}复制了\n{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}！");
static const u8 sText_PkmnMadeWish[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}许了愿！");
static const u8 sText_PkmnWishCameTrue[] = _("{CHN}{B_BUFF1}的祈愿\n实现了！");
static const u8 sText_PkmnPlantedRoots[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}扎根了！");
static const u8 sText_PkmnAbsorbedNutrients[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}用根\n吸收了养分！");
static const u8 sText_PkmnAnchoredItself[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}用根\n固定了自己！");
static const u8 sText_PkmnWasMadeDrowsy[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}让\n{B_DEF_NAME_WITH_PREFIX}犯困了！");
static const u8 sText_PkmnKnockedOff[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}打落了\n{B_DEF_NAME_WITH_PREFIX}的{B_LAST_ITEM}！");
static const u8 sText_PkmnSwappedAbilities[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}与对手\n交换了特性！");
static const u8 sText_PkmnSealedOpponentMove[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}封印了\n对手的招式！");
static const u8 sText_PkmnWantsGrudge[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}想让对手\n怀恨在心！");
static const u8 sText_PkmnLostPPGrudge[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的{B_BUFF1}因怨念\n失去了所有PP！");
static const u8 sText_PkmnShroudedItself[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}用\n{B_CURRENT_MOVE}掩护了自己！");
static const u8 sText_PkmnMoveBounced[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的{B_CURRENT_MOVE}\n被魔法反射弹回！");
static const u8 sText_PkmnWaitsForTarget[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}等待对手\n出招！");
static const u8 sText_PkmnSnatchedMove[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}抢夺了\n{B_SCR_ACTIVE_NAME_WITH_PREFIX}的招式！");
static const u8 sText_ElectricityWeakened[] = _("{CHN}电的威力\n减弱了！");
static const u8 sText_FireWeakened[] = _("{CHN}火的威力\n减弱了！");
static const u8 sText_XFoundOneY[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}找到了\n一个{B_LAST_ITEM}！");
static const u8 sText_SoothingAroma[] = _("{CHN}一阵舒适的香气\n飘荡在周围！");
static const u8 sText_ItemsCantBeUsedNow[] = _("{CHN}现在不能使用道具。{PAUSE 64}");
static const u8 sText_ForXCommaYZ[] = _("{CHN}对于{B_SCR_ACTIVE_NAME_WITH_PREFIX}，\n{B_LAST_ITEM}{B_BUFF1}");
static const u8 sText_PkmnUsedXToGetPumped[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}用了\n{B_LAST_ITEM}来蓄力！");
static const u8 sText_PkmnLostFocus[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}失去了\n注意力无法行动！");
static const u8 sText_PkmnWasDraggedOut[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}被\n强制拖出来了！\p");
static const u8 sText_TheWallShattered[] = _("{CHN}墙壁破碎了！");
static const u8 sText_ButNoEffect[] = _("{CHN}但是没有效果！");
static const u8 sText_PkmnHasNoMovesLeft[] = _("{CHN}{B_ACTIVE_NAME_WITH_PREFIX}没有\n招式可用了！\p");
static const u8 sText_PkmnMoveIsDisabled[] = _("{CHN}{B_ACTIVE_NAME_WITH_PREFIX}的{B_CURRENT_MOVE}\n被禁止了！\p");
static const u8 sText_PkmnCantUseMoveTorment[] = _("{CHN}{B_ACTIVE_NAME_WITH_PREFIX}因寻衅无法\n连续使用同一招式！\p");
static const u8 sText_PkmnCantUseMoveTaunt[] = _("{CHN}{B_ACTIVE_NAME_WITH_PREFIX}因挑衅\n无法使用{B_CURRENT_MOVE}！\p");
static const u8 sText_PkmnCantUseMoveSealed[] = _("{CHN}{B_ACTIVE_NAME_WITH_PREFIX}无法使用\n被封印的{B_CURRENT_MOVE}！\p");
static const u8 sText_PkmnMadeItRain[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n使天下雨了！");
static const u8 sText_PkmnRaisedSpeed[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n提高了速度！");
static const u8 sText_PkmnProtectedBy[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}被\n{B_DEF_ABILITY}保护！");
static const u8 sText_PkmnPreventsUsage[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n阻止了{B_ATK_NAME_WITH_PREFIX}\l使用{B_CURRENT_MOVE}！");
static const u8 sText_PkmnRestoredHPUsing[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}用{B_DEF_ABILITY}\n回复了HP！");
static const u8 sText_PkmnsXMadeYUseless[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n使{B_CURRENT_MOVE}无效了！");
static const u8 sText_PkmnChangedTypeWith[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n使其变成了{B_BUFF1}属性！");
static const u8 sText_PkmnPreventsParalysisWith[] = _("{CHN}{B_EFF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n防止了麻痹！");
static const u8 sText_PkmnPreventsRomanceWith[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n防止了迷惑！");
static const u8 sText_PkmnPreventsPoisoningWith[] = _("{CHN}{B_EFF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n防止了中毒！");
static const u8 sText_PkmnPreventsConfusionWith[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n防止了混乱！");
static const u8 sText_PkmnRaisedFirePowerWith[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n提高了火的威力！");
static const u8 sText_PkmnAnchorsItselfWith[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}用\n{B_DEF_ABILITY}固定了自己！");
static const u8 sText_PkmnCutsAttackWith[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n降低了{B_DEF_NAME_WITH_PREFIX}的攻击！");
static const u8 sText_PkmnPreventsStatLossWith[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n防止了能力下降！");
static const u8 sText_PkmnHurtsWith[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n伤害了{B_ATK_NAME_WITH_PREFIX}！");
static const u8 sText_PkmnTraced[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}追踪了\n{B_BUFF1}的{B_BUFF2}！");
static const u8 sText_PkmnsXPreventsBurns[] = _("{CHN}{B_EFF_NAME_WITH_PREFIX}的{B_EFF_ABILITY}\n防止了烧伤！");
static const u8 sText_PkmnsXBlocksY[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n阻挡了{B_CURRENT_MOVE}！");
static const u8 sText_PkmnsXBlocksY2[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n阻挡了{B_CURRENT_MOVE}！");
static const u8 sText_PkmnsXRestoredHPALittle2[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的{B_ATK_ABILITY}\n稍微回复了HP！");
static const u8 sText_PkmnsXWhippedUpSandstorm[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n卷起了沙暴！");
static const u8 sText_PkmnsXIntensifiedSun[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n增强了阳光！");
static const u8 sText_PkmnsXPreventsYLoss[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n防止了{B_BUFF1}下降！");
static const u8 sText_PkmnsXInfatuatedY[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n使{B_ATK_NAME_WITH_PREFIX}着迷了！");
static const u8 sText_PkmnsXMadeYIneffective[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n使{B_CURRENT_MOVE}无效了！");
static const u8 sText_PkmnsXCuredYProblem[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n治愈了它的{B_BUFF1}！");
static const u8 sText_ItSuckedLiquidOoze[] = _("{CHN}吸入了\n黏液！");
static const u8 sText_PkmnTransformed[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}变形了！");
static const u8 sText_PkmnsXTookAttack[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n承受了攻击！");
const u8 gText_PkmnsXPreventsSwitching[] = _("{CHN}{B_BUFF1}的{B_LAST_ABILITY}\n阻止了替换！\p");
static const u8 sText_PreventedFromWorking[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n阻止了{B_SCR_ACTIVE_NAME_WITH_PREFIX}的\l{B_BUFF1}生效！");
static const u8 sText_PkmnsXMadeItIneffective[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n使其无效了！");
static const u8 sText_PkmnsXPreventsFlinching[] = _("{CHN}{B_EFF_NAME_WITH_PREFIX}的{B_EFF_ABILITY}\n防止了畏缩！");
static const u8 sText_PkmnsXPreventsYsZ[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的{B_ATK_ABILITY}\n阻止了{B_DEF_NAME_WITH_PREFIX}的\l{B_DEF_ABILITY}生效！");
static const u8 sText_PkmnsXCuredItsYProblem[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n治愈了它的{B_BUFF1}！");
static const u8 sText_PkmnsXHadNoEffectOnY[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_SCR_ACTIVE_ABILITY}\n对{B_EFF_NAME_WITH_PREFIX}没有效果！");
static const u8 sText_StatSharply[] = _("{CHN}大幅");
const u8 gText_StatRose[] = _("{CHN}提高了！");
static const u8 sText_StatHarshly[] = _("{CHN}急剧");
static const u8 sText_StatFell[] = _("{CHN}降低了！");
static const u8 sText_AttackersStatRose[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的{B_BUFF1}\n{B_BUFF2}");
const u8 gText_DefendersStatRose[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_BUFF1}\n{B_BUFF2}");
static const u8 sText_UsingItemTheStatOfPkmnRose[] = _("{CHN}用{B_LAST_ITEM}，{B_SCR_ACTIVE_NAME_WITH_PREFIX}的\n{B_BUFF1}{B_BUFF2}");
static const u8 sText_AttackersStatFell[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的{B_BUFF1}\n{B_BUFF2}");
static const u8 sText_DefendersStatFell[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的{B_BUFF1}\n{B_BUFF2}");
static const u8 sText_StatsWontIncrease2[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}的能力\n无法再提高了！");
static const u8 sText_StatsWontDecrease2[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}的能力\n无法再降低了！");
static const u8 sText_CriticalHit[] = _("{CHN}击中要害了！");
static const u8 sText_OneHitKO[] = _("{CHN}是一击必杀！");
static const u8 sText_123Poof[] = _("{PAUSE 32}1{PAUSE 15}、2{PAUSE 15}…… {PAUSE 15}…… {PAUSE 15}…… {PAUSE 15}{PLAY_SE SE_BALL_BOUNCE_1}砰！\p");
static const u8 sText_AndEllipsis[] = _("{CHN}然后……\p");
static const u8 sText_HMMovesCantBeForgotten[] = _("{CHN}秘传招式现在无法\n忘记。\p");
static const u8 sText_NotVeryEffective[] = _("{CHN}效果不佳……");
static const u8 sText_SuperEffective[] = _("{CHN}效果绝佳！");
static const u8 sText_GotAwaySafely[] = _("{PLAY_SE SE_FLEE}{CHN}安全逃跑了！\p");
static const u8 sText_PkmnFledUsingIts[] = _("{PLAY_SE SE_FLEE}{CHN}{B_ATK_NAME_WITH_PREFIX}用\n{B_LAST_ITEM}逃跑了！\p");
static const u8 sText_PkmnFledUsing[] = _("{PLAY_SE SE_FLEE}{CHN}{B_ATK_NAME_WITH_PREFIX}用\n{B_ATK_ABILITY}逃跑了！\p");
static const u8 sText_WildPkmnFled[] = _("{PLAY_SE SE_FLEE}{CHN}野生{B_BUFF1}逃跑了！");
static const u8 sText_PlayerDefeatedLinkTrainer[] = _("{CHN}玩家击败了\n{B_LINK_OPPONENT1_NAME}！");
static const u8 sText_TwoLinkTrainersDefeated[] = _("{CHN}玩家击败了{B_LINK_OPPONENT1_NAME}\n和{B_LINK_OPPONENT2_NAME}！");
static const u8 sText_PlayerLostAgainstLinkTrainer[] = _("{CHN}玩家输给了\n{B_LINK_OPPONENT1_NAME}！");
static const u8 sText_PlayerLostToTwo[] = _("{CHN}玩家输给了{B_LINK_OPPONENT1_NAME}\n和{B_LINK_OPPONENT2_NAME}！");
static const u8 sText_PlayerBattledToDrawLinkTrainer[] = _("{CHN}玩家与\n{B_LINK_OPPONENT1_NAME}打成平手！");
static const u8 sText_PlayerBattledToDrawVsTwo[] = _("{CHN}玩家与{B_LINK_OPPONENT1_NAME}\n和{B_LINK_OPPONENT2_NAME}打成平手！");
static const u8 sText_WildFled[] = _("{PLAY_SE SE_FLEE}{CHN}{B_LINK_OPPONENT1_NAME}逃跑了！");
static const u8 sText_TwoWildFled[] = _("{PLAY_SE SE_FLEE}{CHN}{B_LINK_OPPONENT1_NAME}和\n{B_LINK_OPPONENT2_NAME}逃跑了！");
static const u8 sText_NoRunningFromTrainers[] = _("{CHN}不行！训练家对战中\n不能逃跑！\p");
static const u8 sText_CantEscape[] = _("{CHN}无法逃跑！\p");
static const u8 sText_DontLeaveBirch[] = _("{CHN}小田卷博士：别丢下我！\p");
static const u8 sText_ButNothingHappened[] = _("{CHN}但是什么也没发生！");
static const u8 sText_ButItFailed[] = _("{CHN}但是失败了！");
static const u8 sText_ItHurtConfusion[] = _("{CHN}它因混乱\n伤到了自己！");
static const u8 sText_MirrorMoveFailed[] = _("{CHN}鹦鹉学舌失败了！");
static const u8 sText_StartedToRain[] = _("{CHN}开始下雨了！");
static const u8 sText_DownpourStarted[] = _("{CHN}下起了暴雨！"); // corresponds to DownpourText in pokegold and pokecrystal and is used by Rain Dance in GSC
static const u8 sText_RainContinues[] = _("{CHN}雨继续下着。");
static const u8 sText_DownpourContinues[] = _("{CHN}暴雨持续着。"); // unused
static const u8 sText_RainStopped[] = _("{CHN}雨停了。");
static const u8 sText_SandstormBrewed[] = _("{CHN}沙暴卷起了！");
static const u8 sText_SandstormRages[] = _("{CHN}沙暴肆虐着。");
static const u8 sText_SandstormSubsided[] = _("{CHN}沙暴平息了。");
static const u8 sText_SunlightGotBright[] = _("{CHN}阳光变得强烈了！");
static const u8 sText_SunlightStrong[] = _("{CHN}阳光很强烈。");
static const u8 sText_SunlightFaded[] = _("{CHN}阳光消退了。");
static const u8 sText_StartedHail[] = _("{CHN}开始下冰雹了！");
static const u8 sText_HailContinues[] = _("{CHN}冰雹继续下着。");
static const u8 sText_HailStopped[] = _("{CHN}冰雹停了。");
static const u8 sText_FailedToSpitUp[] = _("{CHN}但是没能喷出\n任何东西！");
static const u8 sText_FailedToSwallow[] = _("{CHN}但是没能吞下\n任何东西！");
static const u8 sText_WindBecameHeatWave[] = _("{CHN}风变成了\n热风！");
static const u8 sText_StatChangesGone[] = _("{CHN}所有能力变化\n都被消除了！");
static const u8 sText_CoinsScattered[] = _("{CHN}金币散落一地！");
static const u8 sText_TooWeakForSubstitute[] = _("{CHN}太弱了无法\n做出替身！");
static const u8 sText_SharedPain[] = _("{CHN}双方分担了\n痛苦！");
static const u8 sText_BellChimed[] = _("{CHN}铃声响起了！");
static const u8 sText_FaintInThree[] = _("{CHN}所有受影响的宝可梦\n将在三回合内倒下！");
static const u8 sText_NoPPLeft[] = _("{CHN}这个招式\n没有PP了！\p");
static const u8 sText_ButNoPPLeft[] = _("{CHN}但是招式\n已经没有PP了！");
static const u8 sText_PkmnIgnoresAsleep[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}在\n睡眠中无视了指令！");
static const u8 sText_PkmnIgnoredOrders[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}无视了\n指令！");
static const u8 sText_PkmnBeganToNap[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}开始打盹了！");
static const u8 sText_PkmnLoafing[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}在\n游手好闲！");
static const u8 sText_PkmnWontObey[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}不\n听话！");
static const u8 sText_PkmnTurnedAway[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}转过身去！");
static const u8 sText_PkmnPretendNotNotice[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}假装\n没注意到！");
static const u8 sText_EnemyAboutToSwitchPkmn[] = _("{CHN}{B_TRAINER1_CLASS} {B_TRAINER1_NAME}\n即将派出{B_BUFF2}。\p{B_PLAYER_NAME}要更换\n宝可梦吗？");
static const u8 sText_PkmnLearnedMove2[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}学会了\n{B_BUFF1}！");
static const u8 sText_PlayerDefeatedLinkTrainerTrainer1[] = _("{CHN}玩家击败了\n{B_TRAINER1_CLASS} {B_TRAINER1_NAME}！\p");
static const u8 sText_CreptCloser[] = _("{CHN}{B_PLAYER_NAME}悄悄靠近了\n{B_OPPONENT_MON1_NAME}！");
static const u8 sText_CantGetCloser[] = _("{CHN}{B_PLAYER_NAME}无法再靠近了！");
static const u8 sText_PkmnWatchingCarefully[] = _("{CHN}{B_OPPONENT_MON1_NAME}正在\n警惕地观察！");
static const u8 sText_PkmnCuriousAboutX[] = _("{CHN}{B_OPPONENT_MON1_NAME}对\n{B_BUFF1}感兴趣！");
static const u8 sText_PkmnEnthralledByX[] = _("{CHN}{B_OPPONENT_MON1_NAME}被\n{B_BUFF1}吸引住了！");
static const u8 sText_PkmnIgnoredX[] = _("{CHN}{B_OPPONENT_MON1_NAME}完全无视了\n{B_BUFF1}！");
static const u8 sText_ThrewPokeblockAtPkmn[] = _("{CHN}{B_PLAYER_NAME}向{B_OPPONENT_MON1_NAME}\n投掷了{POKEBLOCK}！");
static const u8 sText_OutOfSafariBalls[] = _("{PLAY_SE SE_DING_DONG}{CHN}播音员：精灵球\n用完了！游戏结束！\p");
static const u8 sText_OpponentMon1Appeared[] = _("{CHN}{B_OPPONENT_MON1_NAME}出现了！\p");
static const u8 sText_WildPkmnAppeared[] = _("{CHN}野生{B_OPPONENT_MON1_NAME}出现了！\p");
static const u8 sText_LegendaryPkmnAppeared[] = _("{CHN}野生{B_OPPONENT_MON1_NAME}出现了！\p");
static const u8 sText_WildPkmnAppearedPause[] = _("{CHN}野生{B_OPPONENT_MON1_NAME}出现了！{PAUSE 127}");
static const u8 sText_TwoWildPkmnAppeared[] = _("{CHN}野生{B_OPPONENT_MON1_NAME}和\n{B_OPPONENT_MON2_NAME}出现了！\p");
static const u8 sText_Trainer1WantsToBattle[] = _("{CHN}{B_TRAINER1_CLASS} {B_TRAINER1_NAME}\n想要对战！\p");
static const u8 sText_LinkTrainerWantsToBattle[] = _("{CHN}{B_LINK_OPPONENT1_NAME}\n想要对战！");
static const u8 sText_TwoLinkTrainersWantToBattle[] = _("{CHN}{B_LINK_OPPONENT1_NAME}和{B_LINK_OPPONENT2_NAME}\n想要对战！");
static const u8 sText_Trainer1SentOutPkmn[] = _("{CHN}{B_TRAINER1_CLASS} {B_TRAINER1_NAME}派出了\n{B_OPPONENT_MON1_NAME}！");
static const u8 sText_Trainer1SentOutTwoPkmn[] = _("{CHN}{B_TRAINER1_CLASS} {B_TRAINER1_NAME}派出了\n{B_OPPONENT_MON1_NAME}和{B_OPPONENT_MON2_NAME}！");
static const u8 sText_Trainer1SentOutPkmn2[] = _("{CHN}{B_TRAINER1_CLASS} {B_TRAINER1_NAME}派出了\n{B_BUFF1}！");
static const u8 sText_LinkTrainerSentOutPkmn[] = _("{CHN}{B_LINK_OPPONENT1_NAME}派出了\n{B_OPPONENT_MON1_NAME}！");
static const u8 sText_LinkTrainerSentOutTwoPkmn[] = _("{CHN}{B_LINK_OPPONENT1_NAME}派出了\n{B_OPPONENT_MON1_NAME}和{B_OPPONENT_MON2_NAME}！");
static const u8 sText_TwoLinkTrainersSentOutPkmn[] = _("{CHN}{B_LINK_OPPONENT1_NAME}派出了{B_LINK_OPPONENT_MON1_NAME}！\n{B_LINK_OPPONENT2_NAME}派出了{B_LINK_OPPONENT_MON2_NAME}！");
static const u8 sText_LinkTrainerSentOutPkmn2[] = _("{CHN}{B_LINK_OPPONENT1_NAME}派出了\n{B_BUFF1}！");
static const u8 sText_LinkTrainerMultiSentOutPkmn[] = _("{CHN}{B_LINK_SCR_TRAINER_NAME}派出了\n{B_BUFF1}！");
static const u8 sText_GoPkmn[] = _("{CHN}去吧！{B_PLAYER_MON1_NAME}！");
static const u8 sText_GoTwoPkmn[] = _("{CHN}去吧！{B_PLAYER_MON1_NAME}和\n{B_PLAYER_MON2_NAME}！");
static const u8 sText_GoPkmn2[] = _("{CHN}去吧！{B_BUFF1}！");
static const u8 sText_DoItPkmn[] = _("{CHN}上吧！{B_BUFF1}！");
static const u8 sText_GoForItPkmn[] = _("{CHN}加油，{B_BUFF1}！");
static const u8 sText_YourFoesWeakGetEmPkmn[] = _("{CHN}敌方很弱！\n上吧，{B_BUFF1}！");
static const u8 sText_LinkPartnerSentOutPkmnGoPkmn[] = _("{CHN}{B_LINK_PARTNER_NAME}派出了{B_LINK_PLAYER_MON2_NAME}！\n去吧！{B_LINK_PLAYER_MON1_NAME}！");
static const u8 sText_PkmnThatsEnough[] = _("{CHN}{B_BUFF1}，够了！\n回来吧！");
static const u8 sText_PkmnComeBack[] = _("{CHN}{B_BUFF1}，回来吧！");
static const u8 sText_PkmnOkComeBack[] = _("{CHN}{B_BUFF1}，好！\n回来吧！");
static const u8 sText_PkmnGoodComeBack[] = _("{CHN}{B_BUFF1}，干得好！\n回来吧！");
static const u8 sText_Trainer1WithdrewPkmn[] = _("{CHN}{B_TRAINER1_CLASS} {B_TRAINER1_NAME}\n收回了{B_BUFF1}！");
static const u8 sText_LinkTrainer1WithdrewPkmn[] = _("{CHN}{B_LINK_OPPONENT1_NAME}收回了\n{B_BUFF1}！");
static const u8 sText_LinkTrainer2WithdrewPkmn[] = _("{CHN}{B_LINK_SCR_TRAINER_NAME}收回了\n{B_BUFF1}！");
static const u8 sText_WildPkmnPrefix[] = _("{CHN}野生");
static const u8 sText_FoePkmnPrefix[] = _("{CHN}敌方");
static const u8 sText_EmptyString8[] = _("");
static const u8 sText_FoePkmnPrefix2[] = _("{CHN}敌方");
static const u8 sText_AllyPkmnPrefix[] = _("{CHN}友方");
static const u8 sText_FoePkmnPrefix3[] = _("{CHN}敌方");
static const u8 sText_AllyPkmnPrefix2[] = _("{CHN}友方");
static const u8 sText_FoePkmnPrefix4[] = _("{CHN}敌方");
static const u8 sText_AllyPkmnPrefix3[] = _("{CHN}友方");
static const u8 sText_AttackerUsedX[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}使用了\n{B_BUFF2}");
static const u8 sText_ExclamationMark[] = _("{CHN}！");
static const u8 sText_ExclamationMark2[] = _("{CHN}！");
static const u8 sText_ExclamationMark3[] = _("{CHN}！");
static const u8 sText_ExclamationMark4[] = _("{CHN}！");
static const u8 sText_ExclamationMark5[] = _("{CHN}！");
static const u8 sText_HP2[] = _("{CHN}HP");
static const u8 sText_Attack2[] = _("{CHN}攻击");
static const u8 sText_Defense2[] = _("{CHN}防御");
static const u8 sText_Speed[] = _("{CHN}速度");
static const u8 sText_SpAtk2[] = _("{CHN}特攻");
static const u8 sText_SpDef2[] = _("{CHN}特防");
static const u8 sText_Accuracy[] = _("{CHN}命中");
static const u8 sText_Evasiveness[] = _("{CHN}闪避");

const u8 *const gStatNamesTable[NUM_BATTLE_STATS] =
{
    [STAT_HP]      = sText_HP2,
    [STAT_ATK]     = sText_Attack2,
    [STAT_DEF]     = sText_Defense2,
    [STAT_SPEED]   = sText_Speed,
    [STAT_SPATK]   = sText_SpAtk2,
    [STAT_SPDEF]   = sText_SpDef2,
    [STAT_ACC]     = sText_Accuracy,
    [STAT_EVASION] = sText_Evasiveness,
};

static const u8 sText_PokeblockWasTooSpicy[] = _("{CHN}太辣了！");
static const u8 sText_PokeblockWasTooDry[] = _("{CHN}太涩了！");
static const u8 sText_PokeblockWasTooSweet[] = _("{CHN}太甜了！");
static const u8 sText_PokeblockWasTooBitter[] = _("{CHN}太苦了！");
static const u8 sText_PokeblockWasTooSour[] = _("{CHN}太酸了！");

const u8 *const gPokeblockWasTooXStringTable[FLAVOR_COUNT] =
{
    [FLAVOR_SPICY]  = sText_PokeblockWasTooSpicy,
    [FLAVOR_DRY]    = sText_PokeblockWasTooDry,
    [FLAVOR_SWEET]  = sText_PokeblockWasTooSweet,
    [FLAVOR_BITTER] = sText_PokeblockWasTooBitter,
    [FLAVOR_SOUR]   = sText_PokeblockWasTooSour
};

static const u8 sText_PlayerUsedItem[] = _("{CHN}{B_PLAYER_NAME}使用了\n{B_LAST_ITEM}！");
static const u8 sText_WallyUsedItem[] = _("{CHN}小充使用了\n{B_LAST_ITEM}！");
static const u8 sText_Trainer1UsedItem[] = _("{CHN}{B_TRAINER1_CLASS} {B_TRAINER1_NAME}\n使用了{B_LAST_ITEM}！");
static const u8 sText_TrainerBlockedBall[] = _("{CHN}训练家挡住了精灵球！");
static const u8 sText_DontBeAThief[] = _("{CHN}别做小偷！");
static const u8 sText_ItDodgedBall[] = _("{CHN}它躲开了投掷的精灵球！\n这只宝可梦无法捕捉！");
static const u8 sText_YouMissedPkmn[] = _("{CHN}你错过了宝可梦！");
static const u8 sText_PkmnBrokeFree[] = _("{CHN}啊，不！\n宝可梦挣脱了！");
static const u8 sText_ItAppearedCaught[] = _("{CHN}哎呀！\n好像捉到了！");
static const u8 sText_AarghAlmostHadIt[] = _("{CHN}啊！\n就差一点！");
static const u8 sText_ShootSoClose[] = _("{CHN}可恶！\n差一点就成功了！");
static const u8 sText_GotchaPkmnCaughtPlayer[] = _("{CHN}抓住了！\n{B_OPPONENT_MON1_NAME}被捕捉到了！{WAIT_SE}{PLAY_BGM MUS_CAUGHT}\p");
static const u8 sText_GotchaPkmnCaughtWally[] = _("{CHN}抓住了！\n{B_OPPONENT_MON1_NAME}被捕捉到了！{WAIT_SE}{PLAY_BGM MUS_CAUGHT}{PAUSE 127}");
static const u8 sText_GiveNicknameCaptured[] = _("{CHN}要给捕捉到的\n{B_OPPONENT_MON1_NAME}起个昵称吗？");
static const u8 sText_PkmnSentToPC[] = _("{CHN}{B_OPPONENT_MON1_NAME}被送到了\n{B_PC_CREATOR_NAME}的电脑。");
static const u8 sText_Someones[] = _("{CHN}某人的");
static const u8 sText_Lanettes[] = _("{CHN}兰铃的");
static const u8 sText_PkmnDataAddedToDex[] = _("{CHN}{B_OPPONENT_MON1_NAME}的数据\n被添加到了宝可梦图鉴。\p");
static const u8 sText_ItIsRaining[] = _("{CHN}正在下雨。");
static const u8 sText_SandstormIsRaging[] = _("{CHN}沙暴正在肆虐。");
static const u8 sText_BoxIsFull[] = _("{CHN}箱子满了！\n无法再捕捉了！\p");
static const u8 sText_EnigmaBerry[] = _("{CHN}谜之果");
static const u8 sText_BerrySuffix[] = _("{CHN}果");
static const u8 sText_PkmnsItemCuredParalysis[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_LAST_ITEM}\n治愈了麻痹！");
static const u8 sText_PkmnsItemCuredPoison[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_LAST_ITEM}\n治愈了中毒！");
static const u8 sText_PkmnsItemHealedBurn[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_LAST_ITEM}\n治好了烧伤！");
static const u8 sText_PkmnsItemDefrostedIt[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_LAST_ITEM}\n解冻了！");
static const u8 sText_PkmnsItemWokeIt[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_LAST_ITEM}\n把它从睡眠中唤醒！");
static const u8 sText_PkmnsItemSnappedOut[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_LAST_ITEM}\n解除了混乱！");
static const u8 sText_PkmnsItemCuredProblem[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_LAST_ITEM}\n治愈了它的{B_BUFF1}！");
static const u8 sText_PkmnsItemNormalizedStatus[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_LAST_ITEM}\n使状态恢复正常！");
static const u8 sText_PkmnsItemRestoredHealth[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_LAST_ITEM}\n回复了体力！");
static const u8 sText_PkmnsItemRestoredPP[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_LAST_ITEM}\n回复了{B_BUFF1}的PP！");
static const u8 sText_PkmnsItemRestoredStatus[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_LAST_ITEM}\n回复了状态！");
static const u8 sText_PkmnsItemRestoredHPALittle[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的{B_LAST_ITEM}\n稍微回复了HP！");
static const u8 sText_ItemAllowsOnlyYMove[] = _("{CHN}{B_LAST_ITEM}只能\n使用{B_CURRENT_MOVE}！\p");
static const u8 sText_PkmnHungOnWithX[] = _("{CHN}{B_DEF_NAME_WITH_PREFIX}用\n{B_LAST_ITEM}坚持住了！");
const u8 gText_EmptyString3[] = _("");
static const u8 sText_YouThrowABallNowRight[] = _("{CHN}现在该扔精灵球了吧？\n我……我会尽力的！");

// early declaration of strings
static const u8 sText_PkmnIncapableOfPower[];
static const u8 sText_GlintAppearsInEye[];
static const u8 sText_PkmnGettingIntoPosition[];
static const u8 sText_PkmnBeganGrowlingDeeply[];
static const u8 sText_PkmnEagerForMore[];
static const u8 sText_DefeatedOpponentByReferee[];
static const u8 sText_LostToOpponentByReferee[];
static const u8 sText_TiedOpponentByReferee[];
static const u8 sText_QuestionForfeitMatch[];
static const u8 sText_ForfeitedMatch[];
static const u8 sText_Trainer1WinText[];
static const u8 sText_Trainer2WinText[];
static const u8 sText_TwoInGameTrainersDefeated[];
static const u8 sText_Trainer2LoseText[];

const u8 *const gBattleStringsTable[BATTLESTRINGS_COUNT - BATTLESTRINGS_TABLE_START] =
{
    [STRINGID_TRAINER1LOSETEXT - BATTLESTRINGS_TABLE_START] = sText_Trainer1LoseText,
    [STRINGID_PKMNGAINEDEXP - BATTLESTRINGS_TABLE_START] = sText_PkmnGainedEXP,
    [STRINGID_PKMNGREWTOLV - BATTLESTRINGS_TABLE_START] = sText_PkmnGrewToLv,
    [STRINGID_PKMNLEARNEDMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnLearnedMove,
    [STRINGID_TRYTOLEARNMOVE1 - BATTLESTRINGS_TABLE_START] = sText_TryToLearnMove1,
    [STRINGID_TRYTOLEARNMOVE2 - BATTLESTRINGS_TABLE_START] = sText_TryToLearnMove2,
    [STRINGID_TRYTOLEARNMOVE3 - BATTLESTRINGS_TABLE_START] = sText_TryToLearnMove3,
    [STRINGID_PKMNFORGOTMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnForgotMove,
    [STRINGID_STOPLEARNINGMOVE - BATTLESTRINGS_TABLE_START] = sText_StopLearningMove,
    [STRINGID_DIDNOTLEARNMOVE - BATTLESTRINGS_TABLE_START] = sText_DidNotLearnMove,
    [STRINGID_PKMNLEARNEDMOVE2 - BATTLESTRINGS_TABLE_START] = sText_PkmnLearnedMove2,
    [STRINGID_ATTACKMISSED - BATTLESTRINGS_TABLE_START] = sText_AttackMissed,
    [STRINGID_PKMNPROTECTEDITSELF - BATTLESTRINGS_TABLE_START] = sText_PkmnProtectedItself,
    [STRINGID_STATSWONTINCREASE2 - BATTLESTRINGS_TABLE_START] = sText_StatsWontIncrease2,
    [STRINGID_AVOIDEDDAMAGE - BATTLESTRINGS_TABLE_START] = sText_AvoidedDamage,
    [STRINGID_ITDOESNTAFFECT - BATTLESTRINGS_TABLE_START] = sText_ItDoesntAffect,
    [STRINGID_ATTACKERFAINTED - BATTLESTRINGS_TABLE_START] = sText_AttackerFainted,
    [STRINGID_TARGETFAINTED - BATTLESTRINGS_TABLE_START] = sText_TargetFainted,
    [STRINGID_PLAYERGOTMONEY - BATTLESTRINGS_TABLE_START] = sText_PlayerGotMoney,
    [STRINGID_PLAYERWHITEOUT - BATTLESTRINGS_TABLE_START] = sText_PlayerWhiteout,
    [STRINGID_PLAYERWHITEOUT2 - BATTLESTRINGS_TABLE_START] = sText_PlayerWhiteout2,
    [STRINGID_PREVENTSESCAPE - BATTLESTRINGS_TABLE_START] = sText_PreventsEscape,
    [STRINGID_HITXTIMES - BATTLESTRINGS_TABLE_START] = sText_HitXTimes,
    [STRINGID_PKMNFELLASLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnFellAsleep,
    [STRINGID_PKMNMADESLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnMadeSleep,
    [STRINGID_PKMNALREADYASLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyAsleep,
    [STRINGID_PKMNALREADYASLEEP2 - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyAsleep2,
    [STRINGID_PKMNWASNTAFFECTED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasntAffected,
    [STRINGID_PKMNWASPOISONED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasPoisoned,
    [STRINGID_PKMNPOISONEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnPoisonedBy,
    [STRINGID_PKMNHURTBYPOISON - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtByPoison,
    [STRINGID_PKMNALREADYPOISONED - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyPoisoned,
    [STRINGID_PKMNBADLYPOISONED - BATTLESTRINGS_TABLE_START] = sText_PkmnBadlyPoisoned,
    [STRINGID_PKMNENERGYDRAINED - BATTLESTRINGS_TABLE_START] = sText_PkmnEnergyDrained,
    [STRINGID_PKMNWASBURNED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasBurned,
    [STRINGID_PKMNBURNEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnBurnedBy,
    [STRINGID_PKMNHURTBYBURN - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtByBurn,
    [STRINGID_PKMNWASFROZEN - BATTLESTRINGS_TABLE_START] = sText_PkmnWasFrozen,
    [STRINGID_PKMNFROZENBY - BATTLESTRINGS_TABLE_START] = sText_PkmnFrozenBy,
    [STRINGID_PKMNISFROZEN - BATTLESTRINGS_TABLE_START] = sText_PkmnIsFrozen,
    [STRINGID_PKMNWASDEFROSTED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasDefrosted,
    [STRINGID_PKMNWASDEFROSTED2 - BATTLESTRINGS_TABLE_START] = sText_PkmnWasDefrosted2,
    [STRINGID_PKMNWASDEFROSTEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnWasDefrostedBy,
    [STRINGID_PKMNWASPARALYZED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasParalyzed,
    [STRINGID_PKMNWASPARALYZEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnWasParalyzedBy,
    [STRINGID_PKMNISPARALYZED - BATTLESTRINGS_TABLE_START] = sText_PkmnIsParalyzed,
    [STRINGID_PKMNISALREADYPARALYZED - BATTLESTRINGS_TABLE_START] = sText_PkmnIsAlreadyParalyzed,
    [STRINGID_PKMNHEALEDPARALYSIS - BATTLESTRINGS_TABLE_START] = sText_PkmnHealedParalysis,
    [STRINGID_PKMNDREAMEATEN - BATTLESTRINGS_TABLE_START] = sText_PkmnDreamEaten,
    [STRINGID_STATSWONTINCREASE - BATTLESTRINGS_TABLE_START] = sText_StatsWontIncrease,
    [STRINGID_STATSWONTDECREASE - BATTLESTRINGS_TABLE_START] = sText_StatsWontDecrease,
    [STRINGID_TEAMSTOPPEDWORKING - BATTLESTRINGS_TABLE_START] = sText_TeamStoppedWorking,
    [STRINGID_FOESTOPPEDWORKING - BATTLESTRINGS_TABLE_START] = sText_FoeStoppedWorking,
    [STRINGID_PKMNISCONFUSED - BATTLESTRINGS_TABLE_START] = sText_PkmnIsConfused,
    [STRINGID_PKMNHEALEDCONFUSION - BATTLESTRINGS_TABLE_START] = sText_PkmnHealedConfusion,
    [STRINGID_PKMNWASCONFUSED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasConfused,
    [STRINGID_PKMNALREADYCONFUSED - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyConfused,
    [STRINGID_PKMNFELLINLOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnFellInLove,
    [STRINGID_PKMNINLOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnInLove,
    [STRINGID_PKMNIMMOBILIZEDBYLOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnImmobilizedByLove,
    [STRINGID_PKMNBLOWNAWAY - BATTLESTRINGS_TABLE_START] = sText_PkmnBlownAway,
    [STRINGID_PKMNCHANGEDTYPE - BATTLESTRINGS_TABLE_START] = sText_PkmnChangedType,
    [STRINGID_PKMNFLINCHED - BATTLESTRINGS_TABLE_START] = sText_PkmnFlinched,
    [STRINGID_PKMNREGAINEDHEALTH - BATTLESTRINGS_TABLE_START] = sText_PkmnRegainedHealth,
    [STRINGID_PKMNHPFULL - BATTLESTRINGS_TABLE_START] = sText_PkmnHPFull,
    [STRINGID_PKMNRAISEDSPDEF - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedSpDef,
    [STRINGID_PKMNRAISEDDEF - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedDef,
    [STRINGID_PKMNCOVEREDBYVEIL - BATTLESTRINGS_TABLE_START] = sText_PkmnCoveredByVeil,
    [STRINGID_PKMNUSEDSAFEGUARD - BATTLESTRINGS_TABLE_START] = sText_PkmnUsedSafeguard,
    [STRINGID_PKMNSAFEGUARDEXPIRED - BATTLESTRINGS_TABLE_START] = sText_PkmnSafeguardExpired,
    [STRINGID_PKMNWENTTOSLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnWentToSleep,
    [STRINGID_PKMNSLEPTHEALTHY - BATTLESTRINGS_TABLE_START] = sText_PkmnSleptHealthy,
    [STRINGID_PKMNWHIPPEDWHIRLWIND - BATTLESTRINGS_TABLE_START] = sText_PkmnWhippedWhirlwind,
    [STRINGID_PKMNTOOKSUNLIGHT - BATTLESTRINGS_TABLE_START] = sText_PkmnTookSunlight,
    [STRINGID_PKMNLOWEREDHEAD - BATTLESTRINGS_TABLE_START] = sText_PkmnLoweredHead,
    [STRINGID_PKMNISGLOWING - BATTLESTRINGS_TABLE_START] = sText_PkmnIsGlowing,
    [STRINGID_PKMNFLEWHIGH - BATTLESTRINGS_TABLE_START] = sText_PkmnFlewHigh,
    [STRINGID_PKMNDUGHOLE - BATTLESTRINGS_TABLE_START] = sText_PkmnDugHole,
    [STRINGID_PKMNSQUEEZEDBYBIND - BATTLESTRINGS_TABLE_START] = sText_PkmnSqueezedByBind,
    [STRINGID_PKMNTRAPPEDINVORTEX - BATTLESTRINGS_TABLE_START] = sText_PkmnTrappedInVortex,
    [STRINGID_PKMNWRAPPEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnWrappedBy,
    [STRINGID_PKMNCLAMPED - BATTLESTRINGS_TABLE_START] = sText_PkmnClamped,
    [STRINGID_PKMNHURTBY - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtBy,
    [STRINGID_PKMNFREEDFROM - BATTLESTRINGS_TABLE_START] = sText_PkmnFreedFrom,
    [STRINGID_PKMNCRASHED - BATTLESTRINGS_TABLE_START] = sText_PkmnCrashed,
    [STRINGID_PKMNSHROUDEDINMIST - BATTLESTRINGS_TABLE_START] = gText_PkmnShroudedInMist,
    [STRINGID_PKMNPROTECTEDBYMIST - BATTLESTRINGS_TABLE_START] = sText_PkmnProtectedByMist,
    [STRINGID_PKMNGETTINGPUMPED - BATTLESTRINGS_TABLE_START] = gText_PkmnGettingPumped,
    [STRINGID_PKMNHITWITHRECOIL - BATTLESTRINGS_TABLE_START] = sText_PkmnHitWithRecoil,
    [STRINGID_PKMNPROTECTEDITSELF2 - BATTLESTRINGS_TABLE_START] = sText_PkmnProtectedItself2,
    [STRINGID_PKMNBUFFETEDBYSANDSTORM - BATTLESTRINGS_TABLE_START] = sText_PkmnBuffetedBySandstorm,
    [STRINGID_PKMNPELTEDBYHAIL - BATTLESTRINGS_TABLE_START] = sText_PkmnPeltedByHail,
    [STRINGID_PKMNSEEDED - BATTLESTRINGS_TABLE_START] = sText_PkmnSeeded,
    [STRINGID_PKMNEVADEDATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnEvadedAttack,
    [STRINGID_PKMNSAPPEDBYLEECHSEED - BATTLESTRINGS_TABLE_START] = sText_PkmnSappedByLeechSeed,
    [STRINGID_PKMNFASTASLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnFastAsleep,
    [STRINGID_PKMNWOKEUP - BATTLESTRINGS_TABLE_START] = sText_PkmnWokeUp,
    [STRINGID_PKMNUPROARKEPTAWAKE - BATTLESTRINGS_TABLE_START] = sText_PkmnUproarKeptAwake,
    [STRINGID_PKMNWOKEUPINUPROAR - BATTLESTRINGS_TABLE_START] = sText_PkmnWokeUpInUproar,
    [STRINGID_PKMNCAUSEDUPROAR - BATTLESTRINGS_TABLE_START] = sText_PkmnCausedUproar,
    [STRINGID_PKMNMAKINGUPROAR - BATTLESTRINGS_TABLE_START] = sText_PkmnMakingUproar,
    [STRINGID_PKMNCALMEDDOWN - BATTLESTRINGS_TABLE_START] = sText_PkmnCalmedDown,
    [STRINGID_PKMNCANTSLEEPINUPROAR - BATTLESTRINGS_TABLE_START] = sText_PkmnCantSleepInUproar,
    [STRINGID_PKMNSTOCKPILED - BATTLESTRINGS_TABLE_START] = sText_PkmnStockpiled,
    [STRINGID_PKMNCANTSTOCKPILE - BATTLESTRINGS_TABLE_START] = sText_PkmnCantStockpile,
    [STRINGID_PKMNCANTSLEEPINUPROAR2 - BATTLESTRINGS_TABLE_START] = sText_PkmnCantSleepInUproar2,
    [STRINGID_UPROARKEPTPKMNAWAKE - BATTLESTRINGS_TABLE_START] = sText_UproarKeptPkmnAwake,
    [STRINGID_PKMNSTAYEDAWAKEUSING - BATTLESTRINGS_TABLE_START] = sText_PkmnStayedAwakeUsing,
    [STRINGID_PKMNSTORINGENERGY - BATTLESTRINGS_TABLE_START] = sText_PkmnStoringEnergy,
    [STRINGID_PKMNUNLEASHEDENERGY - BATTLESTRINGS_TABLE_START] = sText_PkmnUnleashedEnergy,
    [STRINGID_PKMNFATIGUECONFUSION - BATTLESTRINGS_TABLE_START] = sText_PkmnFatigueConfusion,
    [STRINGID_PLAYERPICKEDUPMONEY - BATTLESTRINGS_TABLE_START] = sText_PlayerPickedUpMoney,
    [STRINGID_PKMNUNAFFECTED - BATTLESTRINGS_TABLE_START] = sText_PkmnUnaffected,
    [STRINGID_PKMNTRANSFORMEDINTO - BATTLESTRINGS_TABLE_START] = sText_PkmnTransformedInto,
    [STRINGID_PKMNMADESUBSTITUTE - BATTLESTRINGS_TABLE_START] = sText_PkmnMadeSubstitute,
    [STRINGID_PKMNHASSUBSTITUTE - BATTLESTRINGS_TABLE_START] = sText_PkmnHasSubstitute,
    [STRINGID_SUBSTITUTEDAMAGED - BATTLESTRINGS_TABLE_START] = sText_SubstituteDamaged,
    [STRINGID_PKMNSUBSTITUTEFADED - BATTLESTRINGS_TABLE_START] = sText_PkmnSubstituteFaded,
    [STRINGID_PKMNMUSTRECHARGE - BATTLESTRINGS_TABLE_START] = sText_PkmnMustRecharge,
    [STRINGID_PKMNRAGEBUILDING - BATTLESTRINGS_TABLE_START] = sText_PkmnRageBuilding,
    [STRINGID_PKMNMOVEWASDISABLED - BATTLESTRINGS_TABLE_START] = sText_PkmnMoveWasDisabled,
    [STRINGID_PKMNMOVEISDISABLED - BATTLESTRINGS_TABLE_START] = sText_PkmnMoveIsDisabled,
    [STRINGID_PKMNMOVEDISABLEDNOMORE - BATTLESTRINGS_TABLE_START] = sText_PkmnMoveDisabledNoMore,
    [STRINGID_PKMNGOTENCORE - BATTLESTRINGS_TABLE_START] = sText_PkmnGotEncore,
    [STRINGID_PKMNENCOREENDED - BATTLESTRINGS_TABLE_START] = sText_PkmnEncoreEnded,
    [STRINGID_PKMNTOOKAIM - BATTLESTRINGS_TABLE_START] = sText_PkmnTookAim,
    [STRINGID_PKMNSKETCHEDMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnSketchedMove,
    [STRINGID_PKMNTRYINGTOTAKEFOE - BATTLESTRINGS_TABLE_START] = sText_PkmnTryingToTakeFoe,
    [STRINGID_PKMNTOOKFOE - BATTLESTRINGS_TABLE_START] = sText_PkmnTookFoe,
    [STRINGID_PKMNREDUCEDPP - BATTLESTRINGS_TABLE_START] = sText_PkmnReducedPP,
    [STRINGID_PKMNSTOLEITEM - BATTLESTRINGS_TABLE_START] = sText_PkmnStoleItem,
    [STRINGID_TARGETCANTESCAPENOW - BATTLESTRINGS_TABLE_START] = sText_TargetCantEscapeNow,
    [STRINGID_PKMNFELLINTONIGHTMARE - BATTLESTRINGS_TABLE_START] = sText_PkmnFellIntoNightmare,
    [STRINGID_PKMNLOCKEDINNIGHTMARE - BATTLESTRINGS_TABLE_START] = sText_PkmnLockedInNightmare,
    [STRINGID_PKMNLAIDCURSE - BATTLESTRINGS_TABLE_START] = sText_PkmnLaidCurse,
    [STRINGID_PKMNAFFLICTEDBYCURSE - BATTLESTRINGS_TABLE_START] = sText_PkmnAfflictedByCurse,
    [STRINGID_SPIKESSCATTERED - BATTLESTRINGS_TABLE_START] = sText_SpikesScattered,
    [STRINGID_PKMNHURTBYSPIKES - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtBySpikes,
    [STRINGID_PKMNIDENTIFIED - BATTLESTRINGS_TABLE_START] = sText_PkmnIdentified,
    [STRINGID_PKMNPERISHCOUNTFELL - BATTLESTRINGS_TABLE_START] = sText_PkmnPerishCountFell,
    [STRINGID_PKMNBRACEDITSELF - BATTLESTRINGS_TABLE_START] = sText_PkmnBracedItself,
    [STRINGID_PKMNENDUREDHIT - BATTLESTRINGS_TABLE_START] = sText_PkmnEnduredHit,
    [STRINGID_MAGNITUDESTRENGTH - BATTLESTRINGS_TABLE_START] = sText_MagnitudeStrength,
    [STRINGID_PKMNCUTHPMAXEDATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnCutHPMaxedAttack,
    [STRINGID_PKMNCOPIEDSTATCHANGES - BATTLESTRINGS_TABLE_START] = sText_PkmnCopiedStatChanges,
    [STRINGID_PKMNGOTFREE - BATTLESTRINGS_TABLE_START] = sText_PkmnGotFree,
    [STRINGID_PKMNSHEDLEECHSEED - BATTLESTRINGS_TABLE_START] = sText_PkmnShedLeechSeed,
    [STRINGID_PKMNBLEWAWAYSPIKES - BATTLESTRINGS_TABLE_START] = sText_PkmnBlewAwaySpikes,
    [STRINGID_PKMNFLEDFROMBATTLE - BATTLESTRINGS_TABLE_START] = sText_PkmnFledFromBattle,
    [STRINGID_PKMNFORESAWATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnForesawAttack,
    [STRINGID_PKMNTOOKATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnTookAttack,
    [STRINGID_PKMNATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnAttack,
    [STRINGID_PKMNCENTERATTENTION - BATTLESTRINGS_TABLE_START] = sText_PkmnCenterAttention,
    [STRINGID_PKMNCHARGINGPOWER - BATTLESTRINGS_TABLE_START] = sText_PkmnChargingPower,
    [STRINGID_NATUREPOWERTURNEDINTO - BATTLESTRINGS_TABLE_START] = sText_NaturePowerTurnedInto,
    [STRINGID_PKMNSTATUSNORMAL - BATTLESTRINGS_TABLE_START] = sText_PkmnStatusNormal,
    [STRINGID_PKMNHASNOMOVESLEFT - BATTLESTRINGS_TABLE_START] = sText_PkmnHasNoMovesLeft,
    [STRINGID_PKMNSUBJECTEDTOTORMENT - BATTLESTRINGS_TABLE_START] = sText_PkmnSubjectedToTorment,
    [STRINGID_PKMNCANTUSEMOVETORMENT - BATTLESTRINGS_TABLE_START] = sText_PkmnCantUseMoveTorment,
    [STRINGID_PKMNTIGHTENINGFOCUS - BATTLESTRINGS_TABLE_START] = sText_PkmnTighteningFocus,
    [STRINGID_PKMNFELLFORTAUNT - BATTLESTRINGS_TABLE_START] = sText_PkmnFellForTaunt,
    [STRINGID_PKMNCANTUSEMOVETAUNT - BATTLESTRINGS_TABLE_START] = sText_PkmnCantUseMoveTaunt,
    [STRINGID_PKMNREADYTOHELP - BATTLESTRINGS_TABLE_START] = sText_PkmnReadyToHelp,
    [STRINGID_PKMNSWITCHEDITEMS - BATTLESTRINGS_TABLE_START] = sText_PkmnSwitchedItems,
    [STRINGID_PKMNCOPIEDFOE - BATTLESTRINGS_TABLE_START] = sText_PkmnCopiedFoe,
    [STRINGID_PKMNMADEWISH - BATTLESTRINGS_TABLE_START] = sText_PkmnMadeWish,
    [STRINGID_PKMNWISHCAMETRUE - BATTLESTRINGS_TABLE_START] = sText_PkmnWishCameTrue,
    [STRINGID_PKMNPLANTEDROOTS - BATTLESTRINGS_TABLE_START] = sText_PkmnPlantedRoots,
    [STRINGID_PKMNABSORBEDNUTRIENTS - BATTLESTRINGS_TABLE_START] = sText_PkmnAbsorbedNutrients,
    [STRINGID_PKMNANCHOREDITSELF - BATTLESTRINGS_TABLE_START] = sText_PkmnAnchoredItself,
    [STRINGID_PKMNWASMADEDROWSY - BATTLESTRINGS_TABLE_START] = sText_PkmnWasMadeDrowsy,
    [STRINGID_PKMNKNOCKEDOFF - BATTLESTRINGS_TABLE_START] = sText_PkmnKnockedOff,
    [STRINGID_PKMNSWAPPEDABILITIES - BATTLESTRINGS_TABLE_START] = sText_PkmnSwappedAbilities,
    [STRINGID_PKMNSEALEDOPPONENTMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnSealedOpponentMove,
    [STRINGID_PKMNCANTUSEMOVESEALED - BATTLESTRINGS_TABLE_START] = sText_PkmnCantUseMoveSealed,
    [STRINGID_PKMNWANTSGRUDGE - BATTLESTRINGS_TABLE_START] = sText_PkmnWantsGrudge,
    [STRINGID_PKMNLOSTPPGRUDGE - BATTLESTRINGS_TABLE_START] = sText_PkmnLostPPGrudge,
    [STRINGID_PKMNSHROUDEDITSELF - BATTLESTRINGS_TABLE_START] = sText_PkmnShroudedItself,
    [STRINGID_PKMNMOVEBOUNCED - BATTLESTRINGS_TABLE_START] = sText_PkmnMoveBounced,
    [STRINGID_PKMNWAITSFORTARGET - BATTLESTRINGS_TABLE_START] = sText_PkmnWaitsForTarget,
    [STRINGID_PKMNSNATCHEDMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnSnatchedMove,
    [STRINGID_PKMNMADEITRAIN - BATTLESTRINGS_TABLE_START] = sText_PkmnMadeItRain,
    [STRINGID_PKMNRAISEDSPEED - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedSpeed,
    [STRINGID_PKMNPROTECTEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnProtectedBy,
    [STRINGID_PKMNPREVENTSUSAGE - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsUsage,
    [STRINGID_PKMNRESTOREDHPUSING - BATTLESTRINGS_TABLE_START] = sText_PkmnRestoredHPUsing,
    [STRINGID_PKMNCHANGEDTYPEWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnChangedTypeWith,
    [STRINGID_PKMNPREVENTSPARALYSISWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsParalysisWith,
    [STRINGID_PKMNPREVENTSROMANCEWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsRomanceWith,
    [STRINGID_PKMNPREVENTSPOISONINGWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsPoisoningWith,
    [STRINGID_PKMNPREVENTSCONFUSIONWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsConfusionWith,
    [STRINGID_PKMNRAISEDFIREPOWERWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedFirePowerWith,
    [STRINGID_PKMNANCHORSITSELFWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnAnchorsItselfWith,
    [STRINGID_PKMNCUTSATTACKWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnCutsAttackWith,
    [STRINGID_PKMNPREVENTSSTATLOSSWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsStatLossWith,
    [STRINGID_PKMNHURTSWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtsWith,
    [STRINGID_PKMNTRACED - BATTLESTRINGS_TABLE_START] = sText_PkmnTraced,
    [STRINGID_STATSHARPLY - BATTLESTRINGS_TABLE_START] = sText_StatSharply,
    [STRINGID_STATROSE - BATTLESTRINGS_TABLE_START] = gText_StatRose,
    [STRINGID_STATHARSHLY - BATTLESTRINGS_TABLE_START] = sText_StatHarshly,
    [STRINGID_STATFELL - BATTLESTRINGS_TABLE_START] = sText_StatFell,
    [STRINGID_ATTACKERSSTATROSE - BATTLESTRINGS_TABLE_START] = sText_AttackersStatRose,
    [STRINGID_DEFENDERSSTATROSE - BATTLESTRINGS_TABLE_START] = gText_DefendersStatRose,
    [STRINGID_ATTACKERSSTATFELL - BATTLESTRINGS_TABLE_START] = sText_AttackersStatFell,
    [STRINGID_DEFENDERSSTATFELL - BATTLESTRINGS_TABLE_START] = sText_DefendersStatFell,
    [STRINGID_CRITICALHIT - BATTLESTRINGS_TABLE_START] = sText_CriticalHit,
    [STRINGID_ONEHITKO - BATTLESTRINGS_TABLE_START] = sText_OneHitKO,
    [STRINGID_123POOF - BATTLESTRINGS_TABLE_START] = sText_123Poof,
    [STRINGID_ANDELLIPSIS - BATTLESTRINGS_TABLE_START] = sText_AndEllipsis,
    [STRINGID_NOTVERYEFFECTIVE - BATTLESTRINGS_TABLE_START] = sText_NotVeryEffective,
    [STRINGID_SUPEREFFECTIVE - BATTLESTRINGS_TABLE_START] = sText_SuperEffective,
    [STRINGID_GOTAWAYSAFELY - BATTLESTRINGS_TABLE_START] = sText_GotAwaySafely,
    [STRINGID_WILDPKMNFLED - BATTLESTRINGS_TABLE_START] = sText_WildPkmnFled,
    [STRINGID_NORUNNINGFROMTRAINERS - BATTLESTRINGS_TABLE_START] = sText_NoRunningFromTrainers,
    [STRINGID_CANTESCAPE - BATTLESTRINGS_TABLE_START] = sText_CantEscape,
    [STRINGID_DONTLEAVEBIRCH - BATTLESTRINGS_TABLE_START] = sText_DontLeaveBirch,
    [STRINGID_BUTNOTHINGHAPPENED - BATTLESTRINGS_TABLE_START] = sText_ButNothingHappened,
    [STRINGID_BUTITFAILED - BATTLESTRINGS_TABLE_START] = sText_ButItFailed,
    [STRINGID_ITHURTCONFUSION - BATTLESTRINGS_TABLE_START] = sText_ItHurtConfusion,
    [STRINGID_MIRRORMOVEFAILED - BATTLESTRINGS_TABLE_START] = sText_MirrorMoveFailed,
    [STRINGID_STARTEDTORAIN - BATTLESTRINGS_TABLE_START] = sText_StartedToRain,
    [STRINGID_DOWNPOURSTARTED - BATTLESTRINGS_TABLE_START] = sText_DownpourStarted,
    [STRINGID_RAINCONTINUES - BATTLESTRINGS_TABLE_START] = sText_RainContinues,
    [STRINGID_DOWNPOURCONTINUES - BATTLESTRINGS_TABLE_START] = sText_DownpourContinues,
    [STRINGID_RAINSTOPPED - BATTLESTRINGS_TABLE_START] = sText_RainStopped,
    [STRINGID_SANDSTORMBREWED - BATTLESTRINGS_TABLE_START] = sText_SandstormBrewed,
    [STRINGID_SANDSTORMRAGES - BATTLESTRINGS_TABLE_START] = sText_SandstormRages,
    [STRINGID_SANDSTORMSUBSIDED - BATTLESTRINGS_TABLE_START] = sText_SandstormSubsided,
    [STRINGID_SUNLIGHTGOTBRIGHT - BATTLESTRINGS_TABLE_START] = sText_SunlightGotBright,
    [STRINGID_SUNLIGHTSTRONG - BATTLESTRINGS_TABLE_START] = sText_SunlightStrong,
    [STRINGID_SUNLIGHTFADED - BATTLESTRINGS_TABLE_START] = sText_SunlightFaded,
    [STRINGID_STARTEDHAIL - BATTLESTRINGS_TABLE_START] = sText_StartedHail,
    [STRINGID_HAILCONTINUES - BATTLESTRINGS_TABLE_START] = sText_HailContinues,
    [STRINGID_HAILSTOPPED - BATTLESTRINGS_TABLE_START] = sText_HailStopped,
    [STRINGID_FAILEDTOSPITUP - BATTLESTRINGS_TABLE_START] = sText_FailedToSpitUp,
    [STRINGID_FAILEDTOSWALLOW - BATTLESTRINGS_TABLE_START] = sText_FailedToSwallow,
    [STRINGID_WINDBECAMEHEATWAVE - BATTLESTRINGS_TABLE_START] = sText_WindBecameHeatWave,
    [STRINGID_STATCHANGESGONE - BATTLESTRINGS_TABLE_START] = sText_StatChangesGone,
    [STRINGID_COINSSCATTERED - BATTLESTRINGS_TABLE_START] = sText_CoinsScattered,
    [STRINGID_TOOWEAKFORSUBSTITUTE - BATTLESTRINGS_TABLE_START] = sText_TooWeakForSubstitute,
    [STRINGID_SHAREDPAIN - BATTLESTRINGS_TABLE_START] = sText_SharedPain,
    [STRINGID_BELLCHIMED - BATTLESTRINGS_TABLE_START] = sText_BellChimed,
    [STRINGID_FAINTINTHREE - BATTLESTRINGS_TABLE_START] = sText_FaintInThree,
    [STRINGID_NOPPLEFT - BATTLESTRINGS_TABLE_START] = sText_NoPPLeft,
    [STRINGID_BUTNOPPLEFT - BATTLESTRINGS_TABLE_START] = sText_ButNoPPLeft,
    [STRINGID_PLAYERUSEDITEM - BATTLESTRINGS_TABLE_START] = sText_PlayerUsedItem,
    [STRINGID_WALLYUSEDITEM - BATTLESTRINGS_TABLE_START] = sText_WallyUsedItem,
    [STRINGID_TRAINERBLOCKEDBALL - BATTLESTRINGS_TABLE_START] = sText_TrainerBlockedBall,
    [STRINGID_DONTBEATHIEF - BATTLESTRINGS_TABLE_START] = sText_DontBeAThief,
    [STRINGID_ITDODGEDBALL - BATTLESTRINGS_TABLE_START] = sText_ItDodgedBall,
    [STRINGID_YOUMISSEDPKMN - BATTLESTRINGS_TABLE_START] = sText_YouMissedPkmn,
    [STRINGID_PKMNBROKEFREE - BATTLESTRINGS_TABLE_START] = sText_PkmnBrokeFree,
    [STRINGID_ITAPPEAREDCAUGHT - BATTLESTRINGS_TABLE_START] = sText_ItAppearedCaught,
    [STRINGID_AARGHALMOSTHADIT - BATTLESTRINGS_TABLE_START] = sText_AarghAlmostHadIt,
    [STRINGID_SHOOTSOCLOSE - BATTLESTRINGS_TABLE_START] = sText_ShootSoClose,
    [STRINGID_GOTCHAPKMNCAUGHTPLAYER - BATTLESTRINGS_TABLE_START] = sText_GotchaPkmnCaughtPlayer,
    [STRINGID_GOTCHAPKMNCAUGHTWALLY - BATTLESTRINGS_TABLE_START] = sText_GotchaPkmnCaughtWally,
    [STRINGID_GIVENICKNAMECAPTURED - BATTLESTRINGS_TABLE_START] = sText_GiveNicknameCaptured,
    [STRINGID_PKMNSENTTOPC - BATTLESTRINGS_TABLE_START] = sText_PkmnSentToPC,
    [STRINGID_PKMNDATAADDEDTODEX - BATTLESTRINGS_TABLE_START] = sText_PkmnDataAddedToDex,
    [STRINGID_ITISRAINING - BATTLESTRINGS_TABLE_START] = sText_ItIsRaining,
    [STRINGID_SANDSTORMISRAGING - BATTLESTRINGS_TABLE_START] = sText_SandstormIsRaging,
    [STRINGID_CANTESCAPE2 - BATTLESTRINGS_TABLE_START] = sText_CantEscape2,
    [STRINGID_PKMNIGNORESASLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnIgnoresAsleep,
    [STRINGID_PKMNIGNOREDORDERS - BATTLESTRINGS_TABLE_START] = sText_PkmnIgnoredOrders,
    [STRINGID_PKMNBEGANTONAP - BATTLESTRINGS_TABLE_START] = sText_PkmnBeganToNap,
    [STRINGID_PKMNLOAFING - BATTLESTRINGS_TABLE_START] = sText_PkmnLoafing,
    [STRINGID_PKMNWONTOBEY - BATTLESTRINGS_TABLE_START] = sText_PkmnWontObey,
    [STRINGID_PKMNTURNEDAWAY - BATTLESTRINGS_TABLE_START] = sText_PkmnTurnedAway,
    [STRINGID_PKMNPRETENDNOTNOTICE - BATTLESTRINGS_TABLE_START] = sText_PkmnPretendNotNotice,
    [STRINGID_ENEMYABOUTTOSWITCHPKMN - BATTLESTRINGS_TABLE_START] = sText_EnemyAboutToSwitchPkmn,
    [STRINGID_CREPTCLOSER - BATTLESTRINGS_TABLE_START] = sText_CreptCloser,
    [STRINGID_CANTGETCLOSER - BATTLESTRINGS_TABLE_START] = sText_CantGetCloser,
    [STRINGID_PKMNWATCHINGCAREFULLY - BATTLESTRINGS_TABLE_START] = sText_PkmnWatchingCarefully,
    [STRINGID_PKMNCURIOUSABOUTX - BATTLESTRINGS_TABLE_START] = sText_PkmnCuriousAboutX,
    [STRINGID_PKMNENTHRALLEDBYX - BATTLESTRINGS_TABLE_START] = sText_PkmnEnthralledByX,
    [STRINGID_PKMNIGNOREDX - BATTLESTRINGS_TABLE_START] = sText_PkmnIgnoredX,
    [STRINGID_THREWPOKEBLOCKATPKMN - BATTLESTRINGS_TABLE_START] = sText_ThrewPokeblockAtPkmn,
    [STRINGID_OUTOFSAFARIBALLS - BATTLESTRINGS_TABLE_START] = sText_OutOfSafariBalls,
    [STRINGID_PKMNSITEMCUREDPARALYSIS - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemCuredParalysis,
    [STRINGID_PKMNSITEMCUREDPOISON - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemCuredPoison,
    [STRINGID_PKMNSITEMHEALEDBURN - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemHealedBurn,
    [STRINGID_PKMNSITEMDEFROSTEDIT - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemDefrostedIt,
    [STRINGID_PKMNSITEMWOKEIT - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemWokeIt,
    [STRINGID_PKMNSITEMSNAPPEDOUT - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemSnappedOut,
    [STRINGID_PKMNSITEMCUREDPROBLEM - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemCuredProblem,
    [STRINGID_PKMNSITEMRESTOREDHEALTH - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemRestoredHealth,
    [STRINGID_PKMNSITEMRESTOREDPP - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemRestoredPP,
    [STRINGID_PKMNSITEMRESTOREDSTATUS - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemRestoredStatus,
    [STRINGID_PKMNSITEMRESTOREDHPALITTLE - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemRestoredHPALittle,
    [STRINGID_ITEMALLOWSONLYYMOVE - BATTLESTRINGS_TABLE_START] = sText_ItemAllowsOnlyYMove,
    [STRINGID_PKMNHUNGONWITHX - BATTLESTRINGS_TABLE_START] = sText_PkmnHungOnWithX,
    [STRINGID_EMPTYSTRING3 - BATTLESTRINGS_TABLE_START] = gText_EmptyString3,
    [STRINGID_PKMNSXPREVENTSBURNS - BATTLESTRINGS_TABLE_START] = sText_PkmnsXPreventsBurns,
    [STRINGID_PKMNSXBLOCKSY - BATTLESTRINGS_TABLE_START] = sText_PkmnsXBlocksY,
    [STRINGID_PKMNSXRESTOREDHPALITTLE2 - BATTLESTRINGS_TABLE_START] = sText_PkmnsXRestoredHPALittle2,
    [STRINGID_PKMNSXWHIPPEDUPSANDSTORM - BATTLESTRINGS_TABLE_START] = sText_PkmnsXWhippedUpSandstorm,
    [STRINGID_PKMNSXPREVENTSYLOSS - BATTLESTRINGS_TABLE_START] = sText_PkmnsXPreventsYLoss,
    [STRINGID_PKMNSXINFATUATEDY - BATTLESTRINGS_TABLE_START] = sText_PkmnsXInfatuatedY,
    [STRINGID_PKMNSXMADEYINEFFECTIVE - BATTLESTRINGS_TABLE_START] = sText_PkmnsXMadeYIneffective,
    [STRINGID_PKMNSXCUREDYPROBLEM - BATTLESTRINGS_TABLE_START] = sText_PkmnsXCuredYProblem,
    [STRINGID_ITSUCKEDLIQUIDOOZE - BATTLESTRINGS_TABLE_START] = sText_ItSuckedLiquidOoze,
    [STRINGID_PKMNTRANSFORMED - BATTLESTRINGS_TABLE_START] = sText_PkmnTransformed,
    [STRINGID_ELECTRICITYWEAKENED - BATTLESTRINGS_TABLE_START] = sText_ElectricityWeakened,
    [STRINGID_FIREWEAKENED - BATTLESTRINGS_TABLE_START] = sText_FireWeakened,
    [STRINGID_PKMNHIDUNDERWATER - BATTLESTRINGS_TABLE_START] = sText_PkmnHidUnderwater,
    [STRINGID_PKMNSPRANGUP - BATTLESTRINGS_TABLE_START] = sText_PkmnSprangUp,
    [STRINGID_HMMOVESCANTBEFORGOTTEN - BATTLESTRINGS_TABLE_START] = sText_HMMovesCantBeForgotten,
    [STRINGID_XFOUNDONEY - BATTLESTRINGS_TABLE_START] = sText_XFoundOneY,
    [STRINGID_PLAYERDEFEATEDTRAINER1 - BATTLESTRINGS_TABLE_START] = sText_PlayerDefeatedLinkTrainerTrainer1,
    [STRINGID_SOOTHINGAROMA - BATTLESTRINGS_TABLE_START] = sText_SoothingAroma,
    [STRINGID_ITEMSCANTBEUSEDNOW - BATTLESTRINGS_TABLE_START] = sText_ItemsCantBeUsedNow,
    [STRINGID_FORXCOMMAYZ - BATTLESTRINGS_TABLE_START] = sText_ForXCommaYZ,
    [STRINGID_USINGITEMSTATOFPKMNROSE - BATTLESTRINGS_TABLE_START] = sText_UsingItemTheStatOfPkmnRose,
    [STRINGID_PKMNUSEDXTOGETPUMPED - BATTLESTRINGS_TABLE_START] = sText_PkmnUsedXToGetPumped,
    [STRINGID_PKMNSXMADEYUSELESS - BATTLESTRINGS_TABLE_START] = sText_PkmnsXMadeYUseless,
    [STRINGID_PKMNTRAPPEDBYSANDTOMB - BATTLESTRINGS_TABLE_START] = sText_PkmnTrappedBySandTomb,
    [STRINGID_EMPTYSTRING4 - BATTLESTRINGS_TABLE_START] = sText_EmptyString4,
    [STRINGID_ABOOSTED - BATTLESTRINGS_TABLE_START] = sText_ABoosted,
    [STRINGID_PKMNSXINTENSIFIEDSUN - BATTLESTRINGS_TABLE_START] = sText_PkmnsXIntensifiedSun,
    [STRINGID_PKMNMAKESGROUNDMISS - BATTLESTRINGS_TABLE_START] = sText_PkmnMakesGroundMiss,
    [STRINGID_YOUTHROWABALLNOWRIGHT - BATTLESTRINGS_TABLE_START] = sText_YouThrowABallNowRight,
    [STRINGID_PKMNSXTOOKATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnsXTookAttack,
    [STRINGID_PKMNCHOSEXASDESTINY - BATTLESTRINGS_TABLE_START] = sText_PkmnChoseXAsDestiny,
    [STRINGID_PKMNLOSTFOCUS - BATTLESTRINGS_TABLE_START] = sText_PkmnLostFocus,
    [STRINGID_USENEXTPKMN - BATTLESTRINGS_TABLE_START] = sText_UseNextPkmn,
    [STRINGID_PKMNFLEDUSINGITS - BATTLESTRINGS_TABLE_START] = sText_PkmnFledUsingIts,
    [STRINGID_PKMNFLEDUSING - BATTLESTRINGS_TABLE_START] = sText_PkmnFledUsing,
    [STRINGID_PKMNWASDRAGGEDOUT - BATTLESTRINGS_TABLE_START] = sText_PkmnWasDraggedOut,
    [STRINGID_PREVENTEDFROMWORKING - BATTLESTRINGS_TABLE_START] = sText_PreventedFromWorking,
    [STRINGID_PKMNSITEMNORMALIZEDSTATUS - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemNormalizedStatus,
    [STRINGID_TRAINER1USEDITEM - BATTLESTRINGS_TABLE_START] = sText_Trainer1UsedItem,
    [STRINGID_BOXISFULL - BATTLESTRINGS_TABLE_START] = sText_BoxIsFull,
    [STRINGID_PKMNAVOIDEDATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnAvoidedAttack,
    [STRINGID_PKMNSXMADEITINEFFECTIVE - BATTLESTRINGS_TABLE_START] = sText_PkmnsXMadeItIneffective,
    [STRINGID_PKMNSXPREVENTSFLINCHING - BATTLESTRINGS_TABLE_START] = sText_PkmnsXPreventsFlinching,
    [STRINGID_PKMNALREADYHASBURN - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyHasBurn,
    [STRINGID_STATSWONTDECREASE2 - BATTLESTRINGS_TABLE_START] = sText_StatsWontDecrease2,
    [STRINGID_PKMNSXBLOCKSY2 - BATTLESTRINGS_TABLE_START] = sText_PkmnsXBlocksY2,
    [STRINGID_PKMNSXWOREOFF - BATTLESTRINGS_TABLE_START] = sText_PkmnsXWoreOff,
    [STRINGID_PKMNRAISEDDEFALITTLE - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedDefALittle,
    [STRINGID_PKMNRAISEDSPDEFALITTLE - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedSpDefALittle,
    [STRINGID_THEWALLSHATTERED - BATTLESTRINGS_TABLE_START] = sText_TheWallShattered,
    [STRINGID_PKMNSXPREVENTSYSZ - BATTLESTRINGS_TABLE_START] = sText_PkmnsXPreventsYsZ,
    [STRINGID_PKMNSXCUREDITSYPROBLEM - BATTLESTRINGS_TABLE_START] = sText_PkmnsXCuredItsYProblem,
    [STRINGID_ATTACKERCANTESCAPE - BATTLESTRINGS_TABLE_START] = sText_AttackerCantEscape,
    [STRINGID_PKMNOBTAINEDX - BATTLESTRINGS_TABLE_START] = sText_PkmnObtainedX,
    [STRINGID_PKMNOBTAINEDX2 - BATTLESTRINGS_TABLE_START] = sText_PkmnObtainedX2,
    [STRINGID_PKMNOBTAINEDXYOBTAINEDZ - BATTLESTRINGS_TABLE_START] = sText_PkmnObtainedXYObtainedZ,
    [STRINGID_BUTNOEFFECT - BATTLESTRINGS_TABLE_START] = sText_ButNoEffect,
    [STRINGID_PKMNSXHADNOEFFECTONY - BATTLESTRINGS_TABLE_START] = sText_PkmnsXHadNoEffectOnY,
    [STRINGID_TWOENEMIESDEFEATED - BATTLESTRINGS_TABLE_START] = sText_TwoInGameTrainersDefeated,
    [STRINGID_TRAINER2LOSETEXT - BATTLESTRINGS_TABLE_START] = sText_Trainer2LoseText,
    [STRINGID_PKMNINCAPABLEOFPOWER - BATTLESTRINGS_TABLE_START] = sText_PkmnIncapableOfPower,
    [STRINGID_GLINTAPPEARSINEYE - BATTLESTRINGS_TABLE_START] = sText_GlintAppearsInEye,
    [STRINGID_PKMNGETTINGINTOPOSITION - BATTLESTRINGS_TABLE_START] = sText_PkmnGettingIntoPosition,
    [STRINGID_PKMNBEGANGROWLINGDEEPLY - BATTLESTRINGS_TABLE_START] = sText_PkmnBeganGrowlingDeeply,
    [STRINGID_PKMNEAGERFORMORE - BATTLESTRINGS_TABLE_START] = sText_PkmnEagerForMore,
    [STRINGID_DEFEATEDOPPONENTBYREFEREE - BATTLESTRINGS_TABLE_START] = sText_DefeatedOpponentByReferee,
    [STRINGID_LOSTTOOPPONENTBYREFEREE - BATTLESTRINGS_TABLE_START] = sText_LostToOpponentByReferee,
    [STRINGID_TIEDOPPONENTBYREFEREE - BATTLESTRINGS_TABLE_START] = sText_TiedOpponentByReferee,
    [STRINGID_QUESTIONFORFEITMATCH - BATTLESTRINGS_TABLE_START] = sText_QuestionForfeitMatch,
    [STRINGID_FORFEITEDMATCH - BATTLESTRINGS_TABLE_START] = sText_ForfeitedMatch,
    [STRINGID_PKMNTRANSFERREDSOMEONESPC - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredSomeonesPC,
    [STRINGID_PKMNTRANSFERREDLANETTESPC - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredLanettesPC,
    [STRINGID_PKMNBOXSOMEONESPCFULL - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredSomeonesPCBoxFull,
    [STRINGID_PKMNBOXLANETTESPCFULL - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredLanettesPCBoxFull,
    [STRINGID_TRAINER1WINTEXT - BATTLESTRINGS_TABLE_START] = sText_Trainer1WinText,
    [STRINGID_TRAINER2WINTEXT - BATTLESTRINGS_TABLE_START] = sText_Trainer2WinText,
};

const u16 gMissStringIds[] =
{
    [B_MSG_MISSED]      = STRINGID_ATTACKMISSED,
    [B_MSG_PROTECTED]   = STRINGID_PKMNPROTECTEDITSELF,
    [B_MSG_AVOIDED_ATK] = STRINGID_PKMNAVOIDEDATTACK,
    [B_MSG_AVOIDED_DMG] = STRINGID_AVOIDEDDAMAGE,
    [B_MSG_GROUND_MISS] = STRINGID_PKMNMAKESGROUNDMISS
};

const u16 gNoEscapeStringIds[] =
{
    [B_MSG_CANT_ESCAPE]          = STRINGID_CANTESCAPE,
    [B_MSG_DONT_LEAVE_BIRCH]     = STRINGID_DONTLEAVEBIRCH,
    [B_MSG_PREVENTS_ESCAPE]      = STRINGID_PREVENTSESCAPE,
    [B_MSG_CANT_ESCAPE_2]        = STRINGID_CANTESCAPE2,
    [B_MSG_ATTACKER_CANT_ESCAPE] = STRINGID_ATTACKERCANTESCAPE
};

const u16 gMoveWeatherChangeStringIds[] =
{
    [B_MSG_STARTED_RAIN]      = STRINGID_STARTEDTORAIN,
    [B_MSG_STARTED_DOWNPOUR]  = STRINGID_DOWNPOURSTARTED, // Unused
    [B_MSG_WEATHER_FAILED]    = STRINGID_BUTITFAILED,
    [B_MSG_STARTED_SANDSTORM] = STRINGID_SANDSTORMBREWED,
    [B_MSG_STARTED_SUNLIGHT]  = STRINGID_SUNLIGHTGOTBRIGHT,
    [B_MSG_STARTED_HAIL]      = STRINGID_STARTEDHAIL,
};

const u16 gSandStormHailContinuesStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_SANDSTORMRAGES,
    [B_MSG_HAIL]      = STRINGID_HAILCONTINUES
};

const u16 gSandStormHailDmgStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_PKMNBUFFETEDBYSANDSTORM,
    [B_MSG_HAIL]      = STRINGID_PKMNPELTEDBYHAIL
};

const u16 gSandStormHailEndStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_SANDSTORMSUBSIDED,
    [B_MSG_HAIL]      = STRINGID_HAILSTOPPED
};

const u16 gRainContinuesStringIds[] =
{
    [B_MSG_RAIN_CONTINUES]     = STRINGID_RAINCONTINUES,
    [B_MSG_DOWNPOUR_CONTINUES] = STRINGID_DOWNPOURCONTINUES,
    [B_MSG_RAIN_STOPPED]       = STRINGID_RAINSTOPPED
};

const u16 gProtectLikeUsedStringIds[] =
{
    [B_MSG_PROTECTED_ITSELF] = STRINGID_PKMNPROTECTEDITSELF2,
    [B_MSG_BRACED_ITSELF]    = STRINGID_PKMNBRACEDITSELF,
    [B_MSG_PROTECT_FAILED]   = STRINGID_BUTITFAILED,
};

const u16 gReflectLightScreenSafeguardStringIds[] =
{
    [B_MSG_SIDE_STATUS_FAILED]     = STRINGID_BUTITFAILED,
    [B_MSG_SET_REFLECT_SINGLE]     = STRINGID_PKMNRAISEDDEF,
    [B_MSG_SET_REFLECT_DOUBLE]     = STRINGID_PKMNRAISEDDEFALITTLE,
    [B_MSG_SET_LIGHTSCREEN_SINGLE] = STRINGID_PKMNRAISEDSPDEF,
    [B_MSG_SET_LIGHTSCREEN_DOUBLE] = STRINGID_PKMNRAISEDSPDEFALITTLE,
    [B_MSG_SET_SAFEGUARD]          = STRINGID_PKMNCOVEREDBYVEIL,
};

const u16 gLeechSeedStringIds[] =
{
    [B_MSG_LEECH_SEED_SET]   = STRINGID_PKMNSEEDED,
    [B_MSG_LEECH_SEED_MISS]  = STRINGID_PKMNEVADEDATTACK,
    [B_MSG_LEECH_SEED_FAIL]  = STRINGID_ITDOESNTAFFECT,
    [B_MSG_LEECH_SEED_DRAIN] = STRINGID_PKMNSAPPEDBYLEECHSEED,
    [B_MSG_LEECH_SEED_OOZE]  = STRINGID_ITSUCKEDLIQUIDOOZE,
};

const u16 gRestUsedStringIds[] =
{
    [B_MSG_REST]          = STRINGID_PKMNWENTTOSLEEP,
    [B_MSG_REST_STATUSED] = STRINGID_PKMNSLEPTHEALTHY
};

const u16 gUproarOverTurnStringIds[] =
{
    [B_MSG_UPROAR_CONTINUES] = STRINGID_PKMNMAKINGUPROAR,
    [B_MSG_UPROAR_ENDS]      = STRINGID_PKMNCALMEDDOWN
};

const u16 gStockpileUsedStringIds[] =
{
    [B_MSG_STOCKPILED]     = STRINGID_PKMNSTOCKPILED,
    [B_MSG_CANT_STOCKPILE] = STRINGID_PKMNCANTSTOCKPILE,
};

const u16 gWokeUpStringIds[] =
{
    [B_MSG_WOKE_UP]        = STRINGID_PKMNWOKEUP,
    [B_MSG_WOKE_UP_UPROAR] = STRINGID_PKMNWOKEUPINUPROAR
};

const u16 gSwallowFailStringIds[] =
{
    [B_MSG_SWALLOW_FAILED]  = STRINGID_FAILEDTOSWALLOW,
    [B_MSG_SWALLOW_FULL_HP] = STRINGID_PKMNHPFULL
};

const u16 gUproarAwakeStringIds[] =
{
    [B_MSG_CANT_SLEEP_UPROAR]  = STRINGID_PKMNCANTSLEEPINUPROAR2,
    [B_MSG_UPROAR_KEPT_AWAKE]  = STRINGID_UPROARKEPTPKMNAWAKE,
    [B_MSG_STAYED_AWAKE_USING] = STRINGID_PKMNSTAYEDAWAKEUSING,
};

const u16 gStatUpStringIds[] =
{
    [B_MSG_ATTACKER_STAT_ROSE] = STRINGID_ATTACKERSSTATROSE,
    [B_MSG_DEFENDER_STAT_ROSE] = STRINGID_DEFENDERSSTATROSE,
    [B_MSG_STAT_WONT_INCREASE] = STRINGID_STATSWONTINCREASE,
    [B_MSG_STAT_ROSE_EMPTY]    = STRINGID_EMPTYSTRING3,
    [B_MSG_STAT_ROSE_ITEM]     = STRINGID_USINGITEMSTATOFPKMNROSE,
    [B_MSG_USED_DIRE_HIT]      = STRINGID_PKMNUSEDXTOGETPUMPED,
};

const u16 gStatDownStringIds[] =
{
    [B_MSG_ATTACKER_STAT_FELL] = STRINGID_ATTACKERSSTATFELL,
    [B_MSG_DEFENDER_STAT_FELL] = STRINGID_DEFENDERSSTATFELL,
    [B_MSG_STAT_WONT_DECREASE] = STRINGID_STATSWONTDECREASE,
    [B_MSG_STAT_FELL_EMPTY]    = STRINGID_EMPTYSTRING3,
};

// Index read from sTWOTURN_STRINGID
const u16 gFirstTurnOfTwoStringIds[] =
{
    [B_MSG_TURN1_RAZOR_WIND] = STRINGID_PKMNWHIPPEDWHIRLWIND,
    [B_MSG_TURN1_SOLAR_BEAM] = STRINGID_PKMNTOOKSUNLIGHT,
    [B_MSG_TURN1_SKULL_BASH] = STRINGID_PKMNLOWEREDHEAD,
    [B_MSG_TURN1_SKY_ATTACK] = STRINGID_PKMNISGLOWING,
    [B_MSG_TURN1_FLY]        = STRINGID_PKMNFLEWHIGH,
    [B_MSG_TURN1_DIG]        = STRINGID_PKMNDUGHOLE,
    [B_MSG_TURN1_DIVE]       = STRINGID_PKMNHIDUNDERWATER,
    [B_MSG_TURN1_BOUNCE]     = STRINGID_PKMNSPRANGUP,
};

// Index copied from move's index in gTrappingMoves
const u16 gWrappedStringIds[NUM_TRAPPING_MOVES] =
{
    STRINGID_PKMNSQUEEZEDBYBIND,   // MOVE_BIND
    STRINGID_PKMNWRAPPEDBY,        // MOVE_WRAP
    STRINGID_PKMNTRAPPEDINVORTEX,  // MOVE_FIRE_SPIN
    STRINGID_PKMNCLAMPED,          // MOVE_CLAMP
    STRINGID_PKMNTRAPPEDINVORTEX,  // MOVE_WHIRLPOOL
    STRINGID_PKMNTRAPPEDBYSANDTOMB // MOVE_SAND_TOMB
};

const u16 gMistUsedStringIds[] =
{
    [B_MSG_SET_MIST]    = STRINGID_PKMNSHROUDEDINMIST,
    [B_MSG_MIST_FAILED] = STRINGID_BUTITFAILED
};

const u16 gFocusEnergyUsedStringIds[] =
{
    [B_MSG_GETTING_PUMPED]      = STRINGID_PKMNGETTINGPUMPED,
    [B_MSG_FOCUS_ENERGY_FAILED] = STRINGID_BUTITFAILED
};

const u16 gTransformUsedStringIds[] =
{
    [B_MSG_TRANSFORMED]      = STRINGID_PKMNTRANSFORMEDINTO,
    [B_MSG_TRANSFORM_FAILED] = STRINGID_BUTITFAILED
};

const u16 gSubstituteUsedStringIds[] =
{
    [B_MSG_SET_SUBSTITUTE]    = STRINGID_PKMNMADESUBSTITUTE,
    [B_MSG_SUBSTITUTE_FAILED] = STRINGID_TOOWEAKFORSUBSTITUTE
};

const u16 gGotPoisonedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPOISONED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNPOISONEDBY
};

const u16 gGotParalyzedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPARALYZED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNWASPARALYZEDBY
};

const u16 gFellAsleepStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLASLEEP,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNMADESLEEP,
};

const u16 gGotBurnedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASBURNED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNBURNEDBY
};

const u16 gGotFrozenStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASFROZEN,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNFROZENBY
};

const u16 gGotDefrostedStringIds[] =
{
    [B_MSG_DEFROSTED]         = STRINGID_PKMNWASDEFROSTED2,
    [B_MSG_DEFROSTED_BY_MOVE] = STRINGID_PKMNWASDEFROSTEDBY
};

const u16 gKOFailedStringIds[] =
{
    [B_MSG_KO_MISS]       = STRINGID_ATTACKMISSED,
    [B_MSG_KO_UNAFFECTED] = STRINGID_PKMNUNAFFECTED
};

const u16 gAttractUsedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLINLOVE,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNSXINFATUATEDY
};

const u16 gAbsorbDrainStringIds[] =
{
    [B_MSG_ABSORB]      = STRINGID_PKMNENERGYDRAINED,
    [B_MSG_ABSORB_OOZE] = STRINGID_ITSUCKEDLIQUIDOOZE
};

const u16 gSportsUsedStringIds[] =
{
    [B_MSG_WEAKEN_ELECTRIC] = STRINGID_ELECTRICITYWEAKENED,
    [B_MSG_WEAKEN_FIRE]     = STRINGID_FIREWEAKENED
};

const u16 gPartyStatusHealStringIds[] =
{
    [B_MSG_BELL]                     = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_ATTACKER] = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_PARTNER]  = STRINGID_BELLCHIMED,
    [B_MSG_BELL_BOTH_SOUNDPROOF]     = STRINGID_BELLCHIMED,
    [B_MSG_SOOTHING_AROMA]           = STRINGID_SOOTHINGAROMA
};

const u16 gFutureMoveUsedStringIds[] =
{
    [B_MSG_FUTURE_SIGHT] = STRINGID_PKMNFORESAWATTACK,
    [B_MSG_DOOM_DESIRE]  = STRINGID_PKMNCHOSEXASDESTINY
};

const u16 gBallEscapeStringIds[] =
{
    [BALL_NO_SHAKES]     = STRINGID_PKMNBROKEFREE,
    [BALL_1_SHAKE]       = STRINGID_ITAPPEAREDCAUGHT,
    [BALL_2_SHAKES]      = STRINGID_AARGHALMOSTHADIT,
    [BALL_3_SHAKES_FAIL] = STRINGID_SHOOTSOCLOSE
};

// Overworld weathers that don't have an associated battle weather default to "It is raining."
const u16 gWeatherStartsStringIds[] =
{
    [WEATHER_NONE]               = STRINGID_ITISRAINING,
    [WEATHER_SUNNY_CLOUDS]       = STRINGID_ITISRAINING,
    [WEATHER_SUNNY]              = STRINGID_ITISRAINING,
    [WEATHER_RAIN]               = STRINGID_ITISRAINING,
    [WEATHER_SNOW]               = STRINGID_ITISRAINING,
    [WEATHER_RAIN_THUNDERSTORM]  = STRINGID_ITISRAINING,
    [WEATHER_FOG_HORIZONTAL]     = STRINGID_ITISRAINING,
    [WEATHER_VOLCANIC_ASH]       = STRINGID_ITISRAINING,
    [WEATHER_SANDSTORM]          = STRINGID_SANDSTORMISRAGING,
    [WEATHER_FOG_DIAGONAL]       = STRINGID_ITISRAINING,
    [WEATHER_UNDERWATER]         = STRINGID_ITISRAINING,
    [WEATHER_SHADE]              = STRINGID_ITISRAINING,
    [WEATHER_DROUGHT]            = STRINGID_SUNLIGHTSTRONG,
    [WEATHER_DOWNPOUR]           = STRINGID_ITISRAINING,
    [WEATHER_UNDERWATER_BUBBLES] = STRINGID_ITISRAINING,
    [WEATHER_ABNORMAL]           = STRINGID_ITISRAINING
};

const u16 gInobedientStringIds[] =
{
    [B_MSG_LOAFING]            = STRINGID_PKMNLOAFING,
    [B_MSG_WONT_OBEY]          = STRINGID_PKMNWONTOBEY,
    [B_MSG_TURNED_AWAY]        = STRINGID_PKMNTURNEDAWAY,
    [B_MSG_PRETEND_NOT_NOTICE] = STRINGID_PKMNPRETENDNOTNOTICE,
    [B_MSG_INCAPABLE_OF_POWER] = STRINGID_PKMNINCAPABLEOFPOWER
};

const u16 gSafariGetNearStringIds[] =
{
    [B_MSG_CREPT_CLOSER]    = STRINGID_CREPTCLOSER,
    [B_MSG_CANT_GET_CLOSER] = STRINGID_CANTGETCLOSER
};

const u16 gSafariPokeblockResultStringIds[] =
{
    [B_MSG_MON_CURIOUS]    = STRINGID_PKMNCURIOUSABOUTX,
    [B_MSG_MON_ENTHRALLED] = STRINGID_PKMNENTHRALLEDBYX,
    [B_MSG_MON_IGNORED]    = STRINGID_PKMNIGNOREDX
};

const u16 gTrainerItemCuredStatusStringIds[] =
{
    [AI_HEAL_CONFUSION] = STRINGID_PKMNSITEMSNAPPEDOUT,
    [AI_HEAL_PARALYSIS] = STRINGID_PKMNSITEMCUREDPARALYSIS,
    [AI_HEAL_FREEZE]    = STRINGID_PKMNSITEMDEFROSTEDIT,
    [AI_HEAL_BURN]      = STRINGID_PKMNSITEMHEALEDBURN,
    [AI_HEAL_POISON]    = STRINGID_PKMNSITEMCUREDPOISON,
    [AI_HEAL_SLEEP]     = STRINGID_PKMNSITEMWOKEIT
};

const u16 gBerryEffectStringIds[] =
{
    [B_MSG_CURED_PROBLEM]     = STRINGID_PKMNSITEMCUREDPROBLEM,
    [B_MSG_NORMALIZED_STATUS] = STRINGID_PKMNSITEMNORMALIZEDSTATUS
};

const u16 gBRNPreventionStringIds[] =
{
    [B_MSG_ABILITY_PREVENTS_MOVE_STATUS]    = STRINGID_PKMNSXPREVENTSBURNS,
    [B_MSG_ABILITY_PREVENTS_ABILITY_STATUS] = STRINGID_PKMNSXPREVENTSYSZ,
    [B_MSG_STATUS_HAD_NO_EFFECT]            = STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gPRLZPreventionStringIds[] =
{
    [B_MSG_ABILITY_PREVENTS_MOVE_STATUS]    = STRINGID_PKMNPREVENTSPARALYSISWITH,
    [B_MSG_ABILITY_PREVENTS_ABILITY_STATUS] = STRINGID_PKMNSXPREVENTSYSZ,
    [B_MSG_STATUS_HAD_NO_EFFECT]            = STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gPSNPreventionStringIds[] =
{
    [B_MSG_ABILITY_PREVENTS_MOVE_STATUS]    = STRINGID_PKMNPREVENTSPOISONINGWITH,
    [B_MSG_ABILITY_PREVENTS_ABILITY_STATUS] = STRINGID_PKMNSXPREVENTSYSZ,
    [B_MSG_STATUS_HAD_NO_EFFECT]            = STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gItemSwapStringIds[] =
{
    [B_MSG_ITEM_SWAP_TAKEN] = STRINGID_PKMNOBTAINEDX,
    [B_MSG_ITEM_SWAP_GIVEN] = STRINGID_PKMNOBTAINEDX2,
    [B_MSG_ITEM_SWAP_BOTH]  = STRINGID_PKMNOBTAINEDXYOBTAINEDZ
};

const u16 gFlashFireStringIds[] =
{
    [B_MSG_FLASH_FIRE_BOOST]    = STRINGID_PKMNRAISEDFIREPOWERWITH,
    [B_MSG_FLASH_FIRE_NO_BOOST] = STRINGID_PKMNSXMADEYINEFFECTIVE
};

const u16 gCaughtMonStringIds[] =
{
    [B_MSG_SENT_SOMEONES_PC]  = STRINGID_PKMNTRANSFERREDSOMEONESPC,
    [B_MSG_SENT_LANETTES_PC]  = STRINGID_PKMNTRANSFERREDLANETTESPC,
    [B_MSG_SOMEONES_BOX_FULL] = STRINGID_PKMNBOXSOMEONESPCFULL,
    [B_MSG_LANETTES_BOX_FULL] = STRINGID_PKMNBOXLANETTESPCFULL,
};

const u16 gTrappingMoves[NUM_TRAPPING_MOVES + 1] =
{
    MOVE_BIND,
    MOVE_WRAP,
    MOVE_FIRE_SPIN,
    MOVE_CLAMP,
    MOVE_WHIRLPOOL,
    MOVE_SAND_TOMB,
    0xFFFF // Never read
};

const u8 gText_PkmnIsEvolving[] = _("{CHN}什么？\n{STR_VAR_1}开始进化了！");
const u8 gText_CongratsPkmnEvolved[] = _("{CHN}恭喜！你的{STR_VAR_1}\n进化成了{STR_VAR_2}！{WAIT_SE}\p");
const u8 gText_PkmnStoppedEvolving[] = _("{CHN}嗯？{STR_VAR_1}\n停止进化了！\p");
const u8 gText_EllipsisQuestionMark[] = _("{CHN}……？\p");
const u8 gText_WhatWillPkmnDo[] = _("{CHN}{B_ACTIVE_NAME_WITH_PREFIX}\n要做什么？");
const u8 gText_WhatWillPkmnDo2[] = _("{CHN}{B_PLAYER_NAME}\n要做什么？");
const u8 gText_WhatWillWallyDo[] = _("{CHN}小充\n要做什么？");
const u8 gText_LinkStandby[] = _("{PAUSE 16}{CHN}通讯待机……");
const u8 gText_BattleMenu[] = _("{CHN}战斗{CLEAR_TO 56}背包\n宝可梦{CLEAR_TO 56}逃跑");
const u8 gText_SafariZoneMenu[] = _("{CHN}精灵球{CLEAR_TO 56}{POKEBLOCK}\n靠近{CLEAR_TO 56}逃跑");
const u8 gText_MoveInterfacePP[] = _("{CHN}PP ");
const u8 gText_MoveInterfaceType[] = _("{CHN}属性/");
const u8 gText_MoveInterfacePpType[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}{CHN}PP\n属性/");
const u8 gText_MoveInterfaceDynamicColors[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}");
const u8 gText_WhichMoveToForget4[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}{CHN}要忘记\n哪个招式？");
const u8 gText_BattleYesNoChoice[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}{CHN}是\n否");
const u8 gText_BattleSwitchWhich[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}{CHN}切换\n哪只？");
const u8 gText_BattleSwitchWhich2[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}");
const u8 gText_BattleSwitchWhich3[] = _("{UP_ARROW}");
const u8 gText_BattleSwitchWhich4[] = _("{ESCAPE 4}");
const u8 gText_BattleSwitchWhich5[] = _("-");

static const u8 sText_HP[] = _("{CHN}HP");
static const u8 sText_Attack[] = _("{CHN}攻击");
static const u8 sText_Defense[] = _("{CHN}防御");
static const u8 sText_SpAtk[] = _("{CHN}特攻");
static const u8 sText_SpDef[] = _("{CHN}特防");

// Unused
static const u8 *const sStatNamesTable2[] =
{
    sText_HP, sText_SpAtk, sText_Attack,
    sText_SpDef, sText_Defense, sText_Speed
};

const u8 gText_SafariBalls[] = _("{HIGHLIGHT DARK_GRAY}{CHN} Safari球");
const u8 gText_SafariBallLeft[] = _("{HIGHLIGHT DARK_GRAY}{CHN}剩余：${HIGHLIGHT DARK_GRAY}");
const u8 gText_Sleep[] = _("{CHN}睡眠");
const u8 gText_Poison[] = _("{CHN}中毒");
const u8 gText_Burn[] = _("{CHN}烧伤");
const u8 gText_Paralysis[] = _("{CHN}麻痹");
const u8 gText_Ice[] = _("{CHN}冰冻");
const u8 gText_Confusion[] = _("{CHN}混乱");
const u8 gText_Love[] = _("{CHN}着迷");
const u8 gText_SpaceAndSpace[] = _("{CHN}和");
const u8 gText_CommaSpace[] = _("{CHN}、");
const u8 gText_Space2[] = _(" ");
const u8 gText_LineBreak[] = _("{CHN}\l");
const u8 gText_NewLine[] = _("\n");
const u8 gText_Are[] = _("{CHN}是");
const u8 gText_Are2[] = _("{CHN}是");
const u8 gText_BadEgg[] = _("{CHN}坏蛋");
const u8 gText_BattleWallyName[] = _("{CHN}小充");
const u8 gText_Win[] = _("{HIGHLIGHT TRANSPARENT}{CHN}胜");
const u8 gText_Loss[] = _("{HIGHLIGHT TRANSPARENT}{CHN}负");
const u8 gText_Draw[] = _("{HIGHLIGHT TRANSPARENT}{CHN}平");
static const u8 sText_SpaceIs[] = _("{CHN}是");
static const u8 sText_ApostropheS[] = _("{CHN}的");

// For displaying names of invalid moves.
// This is large enough that the text for TYPE_ELECTRIC will exceed TEXT_BUFF_ARRAY_COUNT.
static const u8 sATypeMove_Table[NUMBER_OF_MON_TYPES][20] =
{
    [TYPE_NORMAL]   = _("{CHN}一般招式"),
    [TYPE_FIGHTING] = _("{CHN}格斗招式"),
    [TYPE_FLYING]   = _("{CHN}飞行招式"),
    [TYPE_POISON]   = _("{CHN}毒招式"),
    [TYPE_GROUND]   = _("{CHN}地面招式"),
    [TYPE_ROCK]     = _("{CHN}岩石招式"),
    [TYPE_BUG]      = _("{CHN}虫招式"),
    [TYPE_GHOST]    = _("{CHN}幽灵招式"),
    [TYPE_STEEL]    = _("{CHN}钢招式"),
    [TYPE_MYSTERY]  = _("{CHN}???招式"),
    [TYPE_FIRE]     = _("{CHN}火招式"),
    [TYPE_WATER]    = _("{CHN}水招式"),
    [TYPE_GRASS]    = _("{CHN}草招式"),
    [TYPE_ELECTRIC] = _("{CHN}电招式"),
    [TYPE_PSYCHIC]  = _("{CHN}超能力招式"),
    [TYPE_ICE]      = _("{CHN}冰招式"),
    [TYPE_DRAGON]   = _("{CHN}龙招式"),
    [TYPE_DARK]     = _("{CHN}恶招式")
};

const u8 gText_BattleTourney[] = _("{CHN}对战锦标赛");
static const u8 sText_Round1[] = _("{CHN}第1轮");
static const u8 sText_Round2[] = _("{CHN}第2轮");
static const u8 sText_Semifinal[] = _("{CHN}半决赛");
static const u8 sText_Final[] = _("{CHN}决赛");

const u8 *const gRoundsStringTable[DOME_ROUNDS_COUNT] =
{
    [DOME_ROUND1]    = sText_Round1,
    [DOME_ROUND2]    = sText_Round2,
    [DOME_SEMIFINAL] = sText_Semifinal,
    [DOME_FINAL]     = sText_Final
};

const u8 gText_TheGreatNewHope[] = _("{CHN}伟大的新希望！\p");
const u8 gText_WillChampionshipDreamComeTrue[] = _("{CHN}冠军梦能实现吗？！\p");
const u8 gText_AFormerChampion[] = _("{CHN}前冠军！\p");
const u8 gText_ThePreviousChampion[] = _("{CHN}上届冠军！\p");
const u8 gText_TheUnbeatenChampion[] = _("{CHN}不败的冠军！\p");
const u8 gText_PlayerMon1Name[] = _("{B_PLAYER_MON1_NAME}");
const u8 gText_Vs[] = _("{CHN}VS");
const u8 gText_OpponentMon1Name[] = _("{B_OPPONENT_MON1_NAME}");
const u8 gText_Mind[] = _("{CHN}心智");
const u8 gText_Skill[] = _("{CHN}技巧");
const u8 gText_Body[] = _("{CHN}体魄");
const u8 gText_Judgment[] = _("{B_BUFF1}{CLEAR 13}{CHN}判定{CLEAR 13}{B_BUFF2}");
static const u8 sText_TwoTrainersSentPkmn[] = _("{CHN}{B_TRAINER1_CLASS} {B_TRAINER1_NAME}派出了\n{B_OPPONENT_MON1_NAME}！\p{B_TRAINER2_CLASS} {B_TRAINER2_NAME}派出了\n{B_OPPONENT_MON2_NAME}！");
static const u8 sText_Trainer2SentOutPkmn[] = _("{CHN}{B_TRAINER2_CLASS} {B_TRAINER2_NAME}派出了\n{B_BUFF1}！");
static const u8 sText_TwoTrainersWantToBattle[] = _("{CHN}{B_TRAINER1_CLASS} {B_TRAINER1_NAME}和\n{B_TRAINER2_CLASS} {B_TRAINER2_NAME}\l想要对战！\p");
static const u8 sText_InGamePartnerSentOutZGoN[] = _("{CHN}{B_PARTNER_CLASS} {B_PARTNER_NAME}派出了\n{B_PLAYER_MON2_NAME}！\l去吧，{B_PLAYER_MON1_NAME}！");
static const u8 sText_TwoInGameTrainersDefeated[] = _("{CHN}{B_TRAINER1_CLASS} {B_TRAINER1_NAME}和\n{B_TRAINER2_CLASS} {B_TRAINER2_NAME}\l被击败了！\p");
static const u8 sText_Trainer2LoseText[] = _("{B_TRAINER2_LOSE_TEXT}");
static const u8 sText_PkmnIncapableOfPower[] = _("{CHN}{B_ATK_NAME_WITH_PREFIX}似乎无法\n使用它的力量！");
static const u8 sText_GlintAppearsInEye[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}的眼中\n闪过光芒！");
static const u8 sText_PkmnGettingIntoPosition[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}正在\n准备就位！");
static const u8 sText_PkmnBeganGrowlingDeeply[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}开始低声咆哮！");
static const u8 sText_PkmnEagerForMore[] = _("{CHN}{B_SCR_ACTIVE_NAME_WITH_PREFIX}还想继续！");

const u16 gBattlePalaceFlavorTextTable[] =
{
    [B_MSG_GLINT_IN_EYE]   = STRINGID_GLINTAPPEARSINEYE,
    [B_MSG_GETTING_IN_POS] = STRINGID_PKMNGETTINGINTOPOSITION,
    [B_MSG_GROWL_DEEPLY]   = STRINGID_PKMNBEGANGROWLINGDEEPLY,
    [B_MSG_EAGER_FOR_MORE] = STRINGID_PKMNEAGERFORMORE,
};

static const u8 sText_RefIfNothingIsDecided[] = _("{CHN}裁判：如果在3回合内\n没有分出胜负，将进入判定！");
static const u8 sText_RefThatsIt[] = _("{CHN}裁判：好了！现在进入\n判定来决定胜者！");
static const u8 sText_RefJudgeMind[] = _("{CHN}裁判：判定项目1，心智！\n最有勇气的宝可梦！\p");
static const u8 sText_RefJudgeSkill[] = _("{CHN}裁判：判定项目2，技巧！\n招式使用最好的宝可梦！\p");
static const u8 sText_RefJudgeBody[] = _("{CHN}裁判：判定项目3，体魄！\n最有活力的宝可梦！\p");
static const u8 sText_RefPlayerWon[] = _("{CHN}裁判：判定：{B_BUFF1}比{B_BUFF2}！\n胜者是{B_PLAYER_NAME}的{B_PLAYER_MON1_NAME}！\p");
static const u8 sText_RefOpponentWon[] = _("{CHN}裁判：判定：{B_BUFF1}比{B_BUFF2}！\n胜者是{B_TRAINER1_NAME}的{B_OPPONENT_MON1_NAME}！\p");
static const u8 sText_RefDraw[] = _("{CHN}裁判：判定：3比3！\n双方平手！\p");
static const u8 sText_DefeatedOpponentByReferee[] = _("{CHN}{B_PLAYER_MON1_NAME}在裁判的判定中\n击败了对手{B_OPPONENT_MON1_NAME}！");
static const u8 sText_LostToOpponentByReferee[] = _("{CHN}{B_PLAYER_MON1_NAME}在裁判的判定中\n输给了对手{B_OPPONENT_MON1_NAME}！");
static const u8 sText_TiedOpponentByReferee[] = _("{CHN}{B_PLAYER_MON1_NAME}在裁判的判定中\n与对手{B_OPPONENT_MON1_NAME}平手！");
static const u8 sText_RefCommenceBattle[] = _("{CHN}裁判：{B_PLAYER_MON1_NAME} VS {B_OPPONENT_MON1_NAME}！\n对战开始！");

const u8 *const gRefereeStringsTable[] =
{
    [B_MSG_REF_NOTHING_IS_DECIDED] = sText_RefIfNothingIsDecided,
    [B_MSG_REF_THATS_IT]           = sText_RefThatsIt,
    [B_MSG_REF_JUDGE_MIND]         = sText_RefJudgeMind,
    [B_MSG_REF_JUDGE_SKILL]        = sText_RefJudgeSkill,
    [B_MSG_REF_JUDGE_BODY]         = sText_RefJudgeBody,
    [B_MSG_REF_PLAYER_WON]         = sText_RefPlayerWon,
    [B_MSG_REF_OPPONENT_WON]       = sText_RefOpponentWon,
    [B_MSG_REF_DRAW]               = sText_RefDraw,
    [B_MSG_REF_COMMENCE_BATTLE]    = sText_RefCommenceBattle,
};

static const u8 sText_QuestionForfeitMatch[] = _("{CHN}要放弃这场比赛\n退出吗？");
static const u8 sText_ForfeitedMatch[] = _("{CHN}{B_PLAYER_NAME}放弃了比赛！");
static const u8 sText_Trainer1WinText[] = _("{B_TRAINER1_WIN_TEXT}");
static const u8 sText_Trainer2WinText[] = _("{B_TRAINER2_WIN_TEXT}");
static const u8 sText_Trainer1Fled[] = _( "{PLAY_SE SE_FLEE}{CHN}{B_TRAINER1_CLASS} {B_TRAINER1_NAME}逃跑了！");
static const u8 sText_PlayerLostAgainstTrainer1[] = _("{CHN}玩家输给了\n{B_TRAINER1_CLASS} {B_TRAINER1_NAME}！");
static const u8 sText_PlayerBattledToDrawTrainer1[] = _("{CHN}玩家与\n{B_TRAINER1_CLASS} {B_TRAINER1_NAME}打成平手！");
const u8 gText_RecordBattleToPass[] = _("{CHN}要将你的对战记录\n记录在对战通行证上吗？");
const u8 gText_BattleRecordedOnPass[] = _("{CHN}{B_PLAYER_NAME}的对战结果\n已记录在对战通行证上。");
static const u8 sText_LinkTrainerWantsToBattlePause[] = _("{CHN}{B_LINK_OPPONENT1_NAME}\n想要对战！{PAUSE 49}");
static const u8 sText_TwoLinkTrainersWantToBattlePause[] = _("{CHN}{B_LINK_OPPONENT1_NAME}和{B_LINK_OPPONENT2_NAME}\n想要对战！{PAUSE 49}");

// This is four lists of moves which use a different attack string in Japanese
// to the default. See the documentation for ChooseTypeOfMoveUsedString for more detail.
static const u16 sGrammarMoveUsedTable[] =
{
    MOVE_SWORDS_DANCE, MOVE_STRENGTH, MOVE_GROWTH,
    MOVE_HARDEN, MOVE_MINIMIZE, MOVE_SMOKESCREEN,
    MOVE_WITHDRAW, MOVE_DEFENSE_CURL, MOVE_EGG_BOMB,
    MOVE_SMOG, MOVE_BONE_CLUB, MOVE_FLASH, MOVE_SPLASH,
    MOVE_ACID_ARMOR, MOVE_BONEMERANG, MOVE_REST, MOVE_SHARPEN,
    MOVE_SUBSTITUTE, MOVE_MIND_READER, MOVE_SNORE,
    MOVE_PROTECT, MOVE_SPIKES, MOVE_ENDURE, MOVE_ROLLOUT,
    MOVE_SWAGGER, MOVE_SLEEP_TALK, MOVE_HIDDEN_POWER,
    MOVE_PSYCH_UP, MOVE_EXTREME_SPEED, MOVE_FOLLOW_ME,
    MOVE_TRICK, MOVE_ASSIST, MOVE_INGRAIN, MOVE_KNOCK_OFF,
    MOVE_CAMOUFLAGE, MOVE_ASTONISH, MOVE_ODOR_SLEUTH,
    MOVE_GRASS_WHISTLE, MOVE_SHEER_COLD, MOVE_MUDDY_WATER,
    MOVE_IRON_DEFENSE, MOVE_BOUNCE, 0,

    MOVE_TELEPORT, MOVE_RECOVER, MOVE_BIDE, MOVE_AMNESIA,
    MOVE_FLAIL, MOVE_TAUNT, MOVE_BULK_UP, 0,

    MOVE_MEDITATE, MOVE_AGILITY, MOVE_MIMIC, MOVE_DOUBLE_TEAM,
    MOVE_BARRAGE, MOVE_TRANSFORM, MOVE_STRUGGLE, MOVE_SCARY_FACE,
    MOVE_CHARGE, MOVE_WISH, MOVE_BRICK_BREAK, MOVE_YAWN,
    MOVE_FEATHER_DANCE, MOVE_TEETER_DANCE, MOVE_MUD_SPORT,
    MOVE_FAKE_TEARS, MOVE_WATER_SPORT, MOVE_CALM_MIND, 0,

    MOVE_POUND, MOVE_SCRATCH, MOVE_VICE_GRIP,
    MOVE_WING_ATTACK, MOVE_FLY, MOVE_BIND, MOVE_SLAM,
    MOVE_HORN_ATTACK, MOVE_WRAP, MOVE_THRASH, MOVE_TAIL_WHIP,
    MOVE_LEER, MOVE_BITE, MOVE_GROWL, MOVE_ROAR,
    MOVE_SING, MOVE_PECK, MOVE_ABSORB, MOVE_STRING_SHOT,
    MOVE_EARTHQUAKE, MOVE_FISSURE, MOVE_DIG, MOVE_TOXIC,
    MOVE_SCREECH, MOVE_METRONOME, MOVE_LICK, MOVE_CLAMP,
    MOVE_CONSTRICT, MOVE_POISON_GAS, MOVE_BUBBLE,
    MOVE_SLASH, MOVE_SPIDER_WEB, MOVE_NIGHTMARE, MOVE_CURSE,
    MOVE_FORESIGHT, MOVE_CHARM, MOVE_ATTRACT, MOVE_ROCK_SMASH,
    MOVE_UPROAR, MOVE_SPIT_UP, MOVE_SWALLOW, MOVE_TORMENT,
    MOVE_FLATTER, MOVE_ROLE_PLAY, MOVE_ENDEAVOR, MOVE_TICKLE,
    MOVE_COVET, 0
};

static const u8 sText_EmptyStatus[] = _("{CHN}$$$$$$$");

static const struct BattleWindowText sTextOnWindowsInfo_Normal[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 2,
    },
    [B_WIN_VS_PLAYER] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_OPPONENT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_OUTCOME_DRAW] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 6,
    },
    [B_WIN_VS_OUTCOME_LEFT] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 6,
    },
    [B_WIN_VS_OUTCOME_RIGHT] = {
        .fillValue = PIXEL_FILL(0x0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 6,
    },
};

static const struct BattleWindowText sTextOnWindowsInfo_Arena[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 2,
    },
    [ARENA_WIN_PLAYER_NAME] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_VS] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_OPPONENT_NAME] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_MIND] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_SKILL] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_BODY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_JUDGMENT_TITLE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_JUDGMENT_TEXT] = {
        .fillValue = PIXEL_FILL(0x1),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .fgColor = 2,
        .bgColor = 1,
        .shadowColor = 3,
    },
};

static const struct BattleWindowText *const sBattleTextOnWindowsInfo[] =
{
    [B_WIN_TYPE_NORMAL] = sTextOnWindowsInfo_Normal,
    [B_WIN_TYPE_ARENA]  = sTextOnWindowsInfo_Arena
};

static const u8 sRecordedBattleTextSpeeds[] = {8, 4, 1, 0};

void BufferStringBattle(u16 stringID)
{
    s32 i;
    const u8 *stringPtr = NULL;

    gBattleMsgDataPtr = (struct BattleMsgData *)(&gBattleBufferA[gActiveBattler][4]);
    gLastUsedItem = gBattleMsgDataPtr->lastItem;
    gLastUsedAbility = gBattleMsgDataPtr->lastAbility;
    gBattleScripting.battler = gBattleMsgDataPtr->scrActive;
    *(&gBattleStruct->scriptPartyIdx) = gBattleMsgDataPtr->bakScriptPartyIdx;
    *(&gBattleStruct->hpScale) = gBattleMsgDataPtr->hpScale;
    gPotentialItemEffectBattler = gBattleMsgDataPtr->itemEffectBattler;
    *(&gBattleStruct->stringMoveType) = gBattleMsgDataPtr->moveType;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        sBattlerAbilities[i] = gBattleMsgDataPtr->abilities[i];
    }
    for (i = 0; i < TEXT_BUFF_ARRAY_COUNT; i++)
    {
        gBattleTextBuff1[i] = gBattleMsgDataPtr->textBuffs[0][i];
        gBattleTextBuff2[i] = gBattleMsgDataPtr->textBuffs[1][i];
        gBattleTextBuff3[i] = gBattleMsgDataPtr->textBuffs[2][i];
    }

    switch (stringID)
    {
    case STRINGID_INTROMSG: // first battle msg
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                {
                    stringPtr = sText_TwoTrainersWantToBattle;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = sText_TwoLinkTrainersWantToBattlePause;
                    else
                        stringPtr = sText_TwoLinkTrainersWantToBattle;
                }
                else
                {
                    if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                        stringPtr = sText_Trainer1WantsToBattle;
                    else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = sText_LinkTrainerWantsToBattlePause;
                    else
                        stringPtr = sText_LinkTrainerWantsToBattle;
                }
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                    stringPtr = sText_TwoTrainersWantToBattle;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_TwoTrainersWantToBattle;
                else
                    stringPtr = sText_Trainer1WantsToBattle;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
                stringPtr = sText_LegendaryPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) // interesting, looks like they had something planned for wild double battles
                stringPtr = sText_TwoWildPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_WALLY_TUTORIAL)
                stringPtr = sText_WildPkmnAppearedPause;
            else
                stringPtr = sText_WildPkmnAppeared;
        }
        break;
    case STRINGID_INTROSENDOUT: // poke first send-out
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                    stringPtr = sText_InGamePartnerSentOutZGoN;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_GoTwoPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkPartnerSentOutPkmnGoPkmn;
                else
                    stringPtr = sText_GoTwoPkmn;
            }
            else
            {
                stringPtr = sText_GoPkmn;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_TwoTrainersSentPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                    stringPtr = sText_TwoTrainersSentPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_TwoLinkTrainersSentOutPkmn;
                else if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
                    stringPtr = sText_LinkTrainerSentOutTwoPkmn;
                else
                    stringPtr = sText_Trainer1SentOutTwoPkmn;
            }
            else
            {
                if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK)))
                    stringPtr = sText_Trainer1SentOutPkmn;
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                    stringPtr = sText_Trainer1SentOutPkmn;
                else
                    stringPtr = sText_LinkTrainerSentOutPkmn;
            }
        }
        break;
    case STRINGID_RETURNMON: // sending poke to ball msg
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0)
                stringPtr = sText_PkmnThatsEnough;
            else if (*(&gBattleStruct->hpScale) == 1 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sText_PkmnComeBack;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sText_PkmnOkComeBack;
            else
                stringPtr = sText_PkmnGoodComeBack;
        }
        else
        {
            if (gTrainerBattleOpponent_A == TRAINER_LINK_OPPONENT || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkTrainer2WithdrewPkmn;
                else
                    stringPtr = sText_LinkTrainer1WithdrewPkmn;
            }
            else
            {
                stringPtr = sText_Trainer1WithdrewPkmn;
            }
        }
        break;
    case STRINGID_SWITCHINMON: // switch-in msg
        if (GetBattlerSide(gBattleScripting.battler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sText_GoPkmn2;
            else if (*(&gBattleStruct->hpScale) == 1)
                stringPtr = sText_DoItPkmn;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sText_GoForItPkmn;
            else
                stringPtr = sText_YourFoesWeakGetEmPkmn;
        }
        else
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                {
                    if (gBattleScripting.battler == 1)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_Trainer2SentOutPkmn;
                }
                else
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                        stringPtr = sText_LinkTrainerMultiSentOutPkmn;
                    else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_LinkTrainerSentOutPkmn2;
                }
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                {
                    if (gBattleScripting.battler == 1)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_Trainer2SentOutPkmn;
                }
                else
                {
                    stringPtr = sText_Trainer1SentOutPkmn2;
                }
            }
        }
        break;
    case STRINGID_USEDMOVE: // Pokémon used a move msg
        ChooseMoveUsedParticle(gBattleTextBuff1); // buff1 doesn't appear in the string, leftover from japanese move names

        if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT)
            StringCopy(gBattleTextBuff2, sATypeMove_Table[*(&gBattleStruct->stringMoveType)]);
        else
            StringCopy(gBattleTextBuff2, gMoveNames[gBattleMsgDataPtr->currentMove]);

        ChooseTypeOfMoveUsedString(gBattleTextBuff2);
        stringPtr = sText_AttackerUsedX;
        break;
    case STRINGID_BATTLEEND: // battle end
        if (gBattleTextBuff1[0] & B_OUTCOME_LINK_BATTLE_RAN)
        {
            gBattleTextBuff1[0] &= ~(B_OUTCOME_LINK_BATTLE_RAN);
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTextBuff1[0] == B_OUTCOME_LOST || gBattleTextBuff1[0] == B_OUTCOME_DREW)
                stringPtr = sText_GotAwaySafely;
            else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                stringPtr = sText_TwoWildFled;
            else
                stringPtr = sText_WildFled;
        }
        else
        {
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                        stringPtr = sText_TwoInGameTrainersDefeated;
                    else
                        stringPtr = sText_TwoLinkTrainersDefeated;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostToTwo;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawVsTwo;
                    break;
                }
            }
            else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainerTrainer1;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstTrainer1;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawTrainer1;
                    break;
                }
            }
            else
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainer;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstLinkTrainer;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawLinkTrainer;
                    break;
                }
            }
        }
        break;
    default: // load a string from the table
        if (stringID >= BATTLESTRINGS_COUNT)
        {
            gDisplayedStringBattle[0] = EOS;
            return;
        }
        else
        {
            stringPtr = gBattleStringsTable[stringID - BATTLESTRINGS_TABLE_START];
        }
        break;
    }

    BattleStringExpandPlaceholdersToDisplayedString(stringPtr);
}

u32 BattleStringExpandPlaceholdersToDisplayedString(const u8 *src)
{
    BattleStringExpandPlaceholders(src, gDisplayedStringBattle);
}

static const u8 *TryGetStatusString(u8 *src)
{
    u32 i;
    u8 status[8];
    u32 chars1, chars2;
    u8 *statusPtr;

    memcpy(status, sText_EmptyStatus, min(ARRAY_COUNT(status), ARRAY_COUNT(sText_EmptyStatus)));

    statusPtr = status;
    for (i = 0; i < ARRAY_COUNT(status); i++)
    {
        if (*src == EOS) break; // one line required to match -g
        *statusPtr = *src;
        src++;
        statusPtr++;
    }

    chars1 = *(u32 *)(&status[0]);
    chars2 = *(u32 *)(&status[4]);

    for (i = 0; i < ARRAY_COUNT(gStatusConditionStringsTable); i++)
    {
        if (chars1 == *(u32 *)(&gStatusConditionStringsTable[i][0][0])
            && chars2 == *(u32 *)(&gStatusConditionStringsTable[i][0][4]))
            return gStatusConditionStringsTable[i][1];
    }
    return NULL;
}

#define HANDLE_NICKNAME_STRING_CASE(battler, monIndex)                \
    if (GetBattlerSide(battler) != B_SIDE_PLAYER)                     \
    {                                                                   \
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)                     \
            toCpy = sText_FoePkmnPrefix;                                \
        else                                                            \
            toCpy = sText_WildPkmnPrefix;                               \
        while (*toCpy != EOS)                                           \
        {                                                               \
            dst[dstID] = *toCpy;                                        \
            dstID++;                                                    \
            toCpy++;                                                    \
        }                                                               \
        GetMonData(&gEnemyParty[monIndex], MON_DATA_NICKNAME, text);    \
    }                                                                   \
    else                                                                \
    {                                                                   \
        GetMonData(&gPlayerParty[monIndex], MON_DATA_NICKNAME, text);   \
    }                                                                   \
    StringGet_Nickname(text);                                           \
    toCpy = text;

// Ensure the defined length for an item name can contain the full defined length of a berry name.
// This ensures that custom Enigma Berry names will fit in the text buffer at the top of BattleStringExpandPlaceholders.
STATIC_ASSERT(BERRY_NAME_LENGTH + ARRAY_COUNT(sText_BerrySuffix) <= ITEM_NAME_LENGTH, BerryNameTooLong);

u32 BattleStringExpandPlaceholders(const u8 *src, u8 *dst)
{
    u32 dstID = 0; // if they used dstID, why not use srcID as well?
    const u8 *toCpy = NULL;
    // This buffer may hold either the name of a trainer, Pokémon, or item.
    u8 text[max(max(max(32, TRAINER_NAME_LENGTH + 1), POKEMON_NAME_LENGTH + 1), ITEM_NAME_LENGTH)];
    u8 multiplayerId;
    s32 i;

    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
        multiplayerId = gRecordedBattleMultiplayerId;
    else
        multiplayerId = GetMultiplayerId();

    while (*src != EOS)
    {
        if (*src == 0x80) // Chinese escape: next 2 bytes are GB2312 encoding
        {
            // Copy 3 bytes as a unit. Without this, the GB2312 second byte
            // (e.g. 0xFD in "升" = 0x80 0xC9 0xFD) would be mistaken for
            // PLACEHOLDER_BEGIN, causing byte misalignment and garbled text.
            if (src[1] == EOS || src[2] == EOS)
                break; // truncated escape, stop safely
            dst[dstID++] = src[0];
            dst[dstID++] = src[1];
            dst[dstID++] = src[2];
            src += 3;
            continue; // skip the trailing src++ below (already advanced 3 bytes)
        }
        else if (*src == PLACEHOLDER_BEGIN)
        {
            src++;
            switch (*src)
            {
            case B_TXT_BUFF1:
                if (gBattleTextBuff1[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff1, gStringVar1);
                    toCpy = gStringVar1;
                }
                else
                {
                    toCpy = TryGetStatusString(gBattleTextBuff1);
                    if (toCpy == NULL)
                        toCpy = gBattleTextBuff1;
                }
                break;
            case B_TXT_BUFF2:
                if (gBattleTextBuff2[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff2, gStringVar2);
                    toCpy = gStringVar2;
                }
                else
                {
                    toCpy = gBattleTextBuff2;
                }
                break;
            case B_TXT_BUFF3:
                if (gBattleTextBuff3[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff3, gStringVar3);
                    toCpy = gStringVar3;
                }
                else
                {
                    toCpy = gBattleTextBuff3;
                }
                break;
            case B_TXT_COPY_VAR_1:
                toCpy = gStringVar1;
                break;
            case B_TXT_COPY_VAR_2:
                toCpy = gStringVar2;
                break;
            case B_TXT_COPY_VAR_3:
                toCpy = gStringVar3;
                break;
            case B_TXT_PLAYER_MON1_NAME: // first player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON1_NAME: // first enemy poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_PLAYER_MON2_NAME: // second player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON2_NAME: // second enemy poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON1_NAME: // link first player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON1_NAME: // link first opponent poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 1]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON2_NAME: // link second player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 2]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON2_NAME: // link second opponent poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 3]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX_MON1: // attacker name with prefix, only battler 0/1
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker,
                                            gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker))])
                break;
            case B_TXT_ATK_PARTNER_NAME: // attacker partner name
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker)) + 2]], MON_DATA_NICKNAME, text);
                else
                    GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker)) + 2]], MON_DATA_NICKNAME, text);

                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX: // attacker name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker, gBattlerPartyIndexes[gBattlerAttacker])
                break;
            case B_TXT_DEF_NAME_WITH_PREFIX: // target name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerTarget, gBattlerPartyIndexes[gBattlerTarget])
                break;
            case B_TXT_EFF_NAME_WITH_PREFIX: // effect battler name with prefix
                HANDLE_NICKNAME_STRING_CASE(gEffectBattler, gBattlerPartyIndexes[gEffectBattler])
                break;
            case B_TXT_ACTIVE_NAME_WITH_PREFIX: // active battler name with prefix
                HANDLE_NICKNAME_STRING_CASE(gActiveBattler, gBattlerPartyIndexes[gActiveBattler])
                break;
            case B_TXT_SCR_ACTIVE_NAME_WITH_PREFIX: // scripting active battler name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler, gBattlerPartyIndexes[gBattleScripting.battler])
                break;
            case B_TXT_CURRENT_MOVE: // current move name
                if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT)
                    toCpy = sATypeMove_Table[gBattleStruct->stringMoveType];
                else
                    toCpy = gMoveNames[gBattleMsgDataPtr->currentMove];
                break;
            case B_TXT_LAST_MOVE: // originally used move name
                if (gBattleMsgDataPtr->originallyUsedMove >= MOVES_COUNT)
                    toCpy = sATypeMove_Table[gBattleStruct->stringMoveType];
                else
                    toCpy = gMoveNames[gBattleMsgDataPtr->originallyUsedMove];
                break;
            case B_TXT_LAST_ITEM: // last used item
                if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
                {
                    if (gLastUsedItem == ITEM_ENIGMA_BERRY)
                    {
                        if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
                        {
                            if ((gBattleScripting.multiplayerId != 0 && (gPotentialItemEffectBattler & BIT_SIDE))
                                || (gBattleScripting.multiplayerId == 0 && !(gPotentialItemEffectBattler & BIT_SIDE)))
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                            {
                                toCpy = sText_EnigmaBerry;
                            }
                        }
                        else
                        {
                            if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                            {
                                toCpy = sText_EnigmaBerry;
                            }
                        }
                    }
                    else
                    {
                        CopyItemName(gLastUsedItem, text);
                        toCpy = text;
                    }
                }
                else
                {
                    CopyItemName(gLastUsedItem, text);
                    toCpy = text;
                }
                break;
            case B_TXT_LAST_ABILITY: // last used ability
                toCpy = gAbilityNames[gLastUsedAbility];
                break;
            case B_TXT_ATK_ABILITY: // attacker ability
                toCpy = gAbilityNames[sBattlerAbilities[gBattlerAttacker]];
                break;
            case B_TXT_DEF_ABILITY: // target ability
                toCpy = gAbilityNames[sBattlerAbilities[gBattlerTarget]];
                break;
            case B_TXT_SCR_ACTIVE_ABILITY: // scripting active ability
                toCpy = gAbilityNames[sBattlerAbilities[gBattleScripting.battler]];
                break;
            case B_TXT_EFF_ABILITY: // effect battler ability
                toCpy = gAbilityNames[sBattlerAbilities[gEffectBattler]];
                break;
            case B_TXT_TRAINER1_CLASS: // trainer class name
                if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
                    toCpy = gTrainerClassNames[GetSecretBaseTrainerClass()];
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                    toCpy = gTrainerClassNames[GetUnionRoomTrainerClass()];
                else if (gTrainerBattleOpponent_A == TRAINER_FRONTIER_BRAIN)
                    toCpy = gTrainerClassNames[GetFrontierBrainTrainerClass()];
                else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                    toCpy = gTrainerClassNames[GetFrontierOpponentClass(gTrainerBattleOpponent_A)];
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                    toCpy = gTrainerClassNames[GetTrainerHillOpponentClass(gTrainerBattleOpponent_A)];
                else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
                    toCpy = gTrainerClassNames[GetEreaderTrainerClassId()];
                else
                    toCpy = gTrainerClassNames[gTrainers[gTrainerBattleOpponent_A].trainerClass];
                break;
            case B_TXT_TRAINER1_NAME: // trainer1 name
                if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
                {
                    for (i = 0; i < (s32) ARRAY_COUNT(gBattleResources->secretBase->trainerName); i++)
                        text[i] = gBattleResources->secretBase->trainerName[i];
                    text[i] = EOS;
                    ConvertInternationalString(text, gBattleResources->secretBase->language);
                    toCpy = text;
                }
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                {
                    toCpy = gLinkPlayers[multiplayerId ^ BIT_SIDE].name;
                }
                else if (gTrainerBattleOpponent_A == TRAINER_FRONTIER_BRAIN)
                {
                    CopyFrontierBrainTrainerName(text);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    GetFrontierTrainerName(text, gTrainerBattleOpponent_A);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    GetTrainerHillTrainerName(text, gTrainerBattleOpponent_A);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
                {
                    GetEreaderTrainerName(text);
                    toCpy = text;
                }
                else
                {
                    toCpy = gTrainers[gTrainerBattleOpponent_A].trainerName;
                }
                break;
            case B_TXT_LINK_PLAYER_NAME: // link player name
                toCpy = gLinkPlayers[multiplayerId].name;
                break;
            case B_TXT_LINK_PARTNER_NAME: // link partner name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_PARTNER(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT1_NAME: // link opponent 1 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_OPPOSITE(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT2_NAME: // link opponent 2 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_PARTNER(BATTLE_OPPOSITE(gLinkPlayers[multiplayerId].id)))].name;
                break;
            case B_TXT_LINK_SCR_TRAINER_NAME: // link scripting active name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(gBattleScripting.battler)].name;
                break;
            case B_TXT_PLAYER_NAME: // player name
                if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                    toCpy = gLinkPlayers[0].name;
                else
                    toCpy = gSaveBlock2Ptr->playerName;
                break;
            case B_TXT_TRAINER1_LOSE_TEXT: // trainerA lose text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerALoseText();
                }
                break;
            case B_TXT_TRAINER1_WIN_TEXT: // trainerA win text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                break;
            case B_TXT_26: // ?
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler, *(&gBattleStruct->scriptPartyIdx))
                break;
            case B_TXT_PC_CREATOR_NAME: // lanette pc
                if (FlagGet(FLAG_SYS_PC_LANETTE))
                    toCpy = sText_Lanettes;
                else
                    toCpy = sText_Someones;
                break;
            case B_TXT_ATK_PREFIX2:
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_DEF_PREFIX2:
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_ATK_PREFIX1:
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_DEF_PREFIX1:
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_ATK_PREFIX3:
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_DEF_PREFIX3:
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_TRAINER2_CLASS:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                    toCpy = gTrainerClassNames[GetFrontierOpponentClass(gTrainerBattleOpponent_B)];
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                    toCpy = gTrainerClassNames[GetTrainerHillOpponentClass(gTrainerBattleOpponent_B)];
                else
                    toCpy = gTrainerClassNames[gTrainers[gTrainerBattleOpponent_B].trainerClass];
                break;
            case B_TXT_TRAINER2_NAME:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    GetFrontierTrainerName(text, gTrainerBattleOpponent_B);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    GetTrainerHillTrainerName(text, gTrainerBattleOpponent_B);
                    toCpy = text;
                }
                else
                {
                    toCpy = gTrainers[gTrainerBattleOpponent_B].trainerName;
                }
                break;
            case B_TXT_TRAINER2_LOSE_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerBLoseText();
                }
                break;
            case B_TXT_TRAINER2_WIN_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                break;
            case B_TXT_PARTNER_CLASS:
                toCpy = gTrainerClassNames[GetFrontierOpponentClass(gPartnerTrainerId)];
                break;
            case B_TXT_PARTNER_NAME:
                GetFrontierTrainerName(text, gPartnerTrainerId);
                toCpy = text;
                break;
            }

            // missing if (toCpy != NULL) check
            while (*toCpy != EOS)
            {
                dst[dstID] = *toCpy;
                dstID++;
                toCpy++;
            }
            if (*src == B_TXT_TRAINER1_LOSE_TEXT || *src == B_TXT_TRAINER2_LOSE_TEXT
                || *src == B_TXT_TRAINER1_WIN_TEXT || *src == B_TXT_TRAINER2_WIN_TEXT)
            {
                dst[dstID] = EXT_CTRL_CODE_BEGIN;
                dstID++;
                dst[dstID] = EXT_CTRL_CODE_PAUSE_UNTIL_PRESS;
                dstID++;
            }
        }
        else
        {
            dst[dstID] = *src;
            dstID++;
        }
        src++;
    }

    dst[dstID] = *src;
    dstID++;

    return dstID;
}

static void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst)
{
    u32 srcID = 1;
    u32 value = 0;
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u16 hword;

    *dst = EOS;
    while (src[srcID] != B_BUFF_EOS)
    {
        switch (src[srcID])
        {
        case B_BUFF_STRING: // battle string
            hword = T1_READ_16(&src[srcID + 1]);
            StringAppend(dst, gBattleStringsTable[hword - BATTLESTRINGS_TABLE_START]);
            srcID += 3;
            break;
        case B_BUFF_NUMBER: // int to string
            switch (src[srcID + 1])
            {
            case 1:
                value = src[srcID + 3];
                break;
            case 2:
                value = T1_READ_16(&src[srcID + 3]);
                break;
            case 4:
                value = T1_READ_32(&src[srcID + 3]);
                break;
            }
            ConvertIntToDecimalStringN(dst, value, STR_CONV_MODE_LEFT_ALIGN, src[srcID + 2]);
            srcID += src[srcID + 1] + 3;
            break;
        case B_BUFF_MOVE: // move name
            StringAppend(dst, gMoveNames[T1_READ_16(&src[srcID + 1])]);
            srcID += 3;
            break;
        case B_BUFF_TYPE: // type name
            StringAppend(dst, gTypeNames[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_MON_NICK_WITH_PREFIX: // poke nick with prefix
            if (GetBattlerSide(src[srcID + 1]) == B_SIDE_PLAYER)
            {
                GetMonData(&gPlayerParty[src[srcID + 2]], MON_DATA_NICKNAME, nickname);
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                    StringAppend(dst, sText_FoePkmnPrefix);
                else
                    StringAppend(dst, sText_WildPkmnPrefix);

                GetMonData(&gEnemyParty[src[srcID + 2]], MON_DATA_NICKNAME, nickname);
            }
            StringGet_Nickname(nickname);
            StringAppend(dst, nickname);
            srcID += 3;
            break;
        case B_BUFF_STAT: // stats
            StringAppend(dst, gStatNamesTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_SPECIES: // species name
            GetSpeciesName(dst, T1_READ_16(&src[srcID + 1]));
            srcID += 3;
            break;
        case B_BUFF_MON_NICK: // poke nick without prefix
            if (GetBattlerSide(src[srcID + 1]) == B_SIDE_PLAYER)
                GetMonData(&gPlayerParty[src[srcID + 2]], MON_DATA_NICKNAME, dst);
            else
                GetMonData(&gEnemyParty[src[srcID + 2]], MON_DATA_NICKNAME, dst);
            StringGet_Nickname(dst);
            srcID += 3;
            break;
        case B_BUFF_NEGATIVE_FLAVOR: // flavor table
            StringAppend(dst, gPokeblockWasTooXStringTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_ABILITY: // ability names
            StringAppend(dst, gAbilityNames[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_ITEM: // item name
            hword = T1_READ_16(&src[srcID + 1]);
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (hword == ITEM_ENIGMA_BERRY)
                {
                    if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                    {
                        StringCopy(dst, gEnigmaBerries[gPotentialItemEffectBattler].name);
                        StringAppend(dst, sText_BerrySuffix);
                    }
                    else
                    {
                        StringAppend(dst, sText_EnigmaBerry);
                    }
                }
                else
                {
                    CopyItemName(hword, dst);
                }
            }
            else
            {
                CopyItemName(hword, dst);
            }
            srcID += 3;
            break;
        }
    }
}

// Loads one of two text strings into the provided buffer. This is functionally
// unused, since the value loaded into the buffer is not read; it loaded one of
// two particles (either "は" or "の") which works in tandem with ChooseTypeOfMoveUsedString
// below to effect changes in the meaning of the line.
static void ChooseMoveUsedParticle(u8 *textBuff)
{
    s32 counter = 0;
    u32 i = 0;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == 0)
            counter++;
        if (sGrammarMoveUsedTable[i++] == gBattleMsgDataPtr->currentMove)
            break;
    }

    if (counter >= 0)
    {
        if (counter <= 2)
            StringCopy(textBuff, sText_SpaceIs); // is
        else if (counter <= MAX_MON_MOVES)
            StringCopy(textBuff, sText_ApostropheS); // 's
    }
}

// Appends "!" to the text buffer `dst`. In the original Japanese this looked
// into the table of moves at sGrammarMoveUsedTable and varied the line accordingly.
//
// sText_ExclamationMark was a plain "!", used for any attack not on the list.
// It resulted in the translation "<NAME>'s <ATTACK>!".
//
// sText_ExclamationMark2 was "を つかった！". This resulted in the translation
// "<NAME> used <ATTACK>!", which was used for all attacks in English.
//
// sText_ExclamationMark3 was "した！". This was used for those moves whose
// names were verbs, such as Recover, and resulted in translations like "<NAME>
// recovered itself!".
//
// sText_ExclamationMark4 was "を した！" This resulted in a translation of
// "<NAME> did an <ATTACK>!".
//
// sText_ExclamationMark5 was " こうげき！" This resulted in a translation of
// "<NAME>'s <ATTACK> attack!".
static void ChooseTypeOfMoveUsedString(u8 *dst)
{
    s32 counter = 0;
    s32 i = 0;

    while (*dst != EOS)
        dst++;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == MOVE_NONE)
            counter++;
        if (sGrammarMoveUsedTable[i++] == gBattleMsgDataPtr->currentMove)
            break;
    }

    switch (counter)
    {
    case 0:
        StringCopy(dst, sText_ExclamationMark);
        break;
    case 1:
        StringCopy(dst, sText_ExclamationMark2);
        break;
    case 2:
        StringCopy(dst, sText_ExclamationMark3);
        break;
    case 3:
        StringCopy(dst, sText_ExclamationMark4);
        break;
    case 4:
        StringCopy(dst, sText_ExclamationMark5);
        break;
    }
}

void BattlePutTextOnWindow(const u8 *text, u8 windowId)
{
    const struct BattleWindowText *textInfo = sBattleTextOnWindowsInfo[gBattleScripting.windowsType];
    bool32 copyToVram;
    struct TextPrinterTemplate printerTemplate;
    u8 speed;

    if (windowId & B_WIN_COPYTOVRAM)
    {
        windowId &= ~B_WIN_COPYTOVRAM;
        copyToVram = FALSE;
    }
    else
    {
        FillWindowPixelBuffer(windowId, textInfo[windowId].fillValue);
        copyToVram = TRUE;
    }

    printerTemplate.currentChar = text;
    printerTemplate.windowId = windowId;
    printerTemplate.fontId = textInfo[windowId].fontId;
    printerTemplate.x = textInfo[windowId].x;
    printerTemplate.y = textInfo[windowId].y;
    printerTemplate.currentX = printerTemplate.x;
    printerTemplate.currentY = printerTemplate.y;
    printerTemplate.letterSpacing = textInfo[windowId].letterSpacing;
    printerTemplate.lineSpacing = textInfo[windowId].lineSpacing;
    printerTemplate.unk = 0;
    printerTemplate.fgColor = textInfo[windowId].fgColor;
    printerTemplate.bgColor = textInfo[windowId].bgColor;
    printerTemplate.shadowColor = textInfo[windowId].shadowColor;

    if (printerTemplate.x == 0xFF)
    {
        u32 width = GetBattleWindowTemplatePixelWidth(gBattleScripting.windowsType, windowId);
        s32 alignX = GetStringCenterAlignXOffsetWithLetterSpacing(printerTemplate.fontId, printerTemplate.currentChar, width, printerTemplate.letterSpacing);
        printerTemplate.x = printerTemplate.currentX = alignX;
    }

    if (windowId == ARENA_WIN_JUDGMENT_TEXT)
        gTextFlags.useAlternateDownArrow = FALSE;
    else
        gTextFlags.useAlternateDownArrow = TRUE;

    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED))
        gTextFlags.autoScroll = TRUE;
    else
        gTextFlags.autoScroll = FALSE;

    if (windowId == B_WIN_MSG || windowId == ARENA_WIN_JUDGMENT_TEXT)
    {
        if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            speed = 1;
        else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            speed = sRecordedBattleTextSpeeds[GetTextSpeedInRecordedBattle()];
        else
            speed = GetPlayerTextSpeedDelay();

        gTextFlags.canABSpeedUpPrint = 1;
    }
    else
    {
        speed = textInfo[windowId].speed;
        gTextFlags.canABSpeedUpPrint = 0;
    }

    AddTextPrinter(&printerTemplate, speed, NULL);

    if (copyToVram)
    {
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_FULL);
    }
}

void SetPpNumbersPaletteInMoveSelection(void)
{
    struct ChooseMoveStruct *chooseMoveStruct = (struct ChooseMoveStruct *)(&gBattleBufferA[gActiveBattler][4]);
    const u16 *palPtr = gPPTextPalette;
    u8 var = GetCurrentPpToMaxPpState(chooseMoveStruct->currentPp[gMoveSelectionCursor[gActiveBattler]],
                         chooseMoveStruct->maxPp[gMoveSelectionCursor[gActiveBattler]]);

    gPlttBufferUnfaded[BG_PLTT_ID(5) + 12] = palPtr[(var * 2) + 0];
    gPlttBufferUnfaded[BG_PLTT_ID(5) + 11] = palPtr[(var * 2) + 1];

    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(5) + 12], &gPlttBufferFaded[BG_PLTT_ID(5) + 12], PLTT_SIZEOF(1));
    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(5) + 11], &gPlttBufferFaded[BG_PLTT_ID(5) + 11], PLTT_SIZEOF(1));
}

u8 GetCurrentPpToMaxPpState(u8 currentPp, u8 maxPp)
{
    if (maxPp == currentPp)
    {
        return 3;
    }
    else if (maxPp <= 2)
    {
        if (currentPp > 1)
            return 3;
        else
            return 2 - currentPp;
    }
    else if (maxPp <= 7)
    {
        if (currentPp > 2)
            return 3;
        else
            return 2 - currentPp;
    }
    else
    {
        if (currentPp == 0)
            return 2;
        if (currentPp <= maxPp / 4)
            return 1;
        if (currentPp > maxPp / 2)
            return 3;
    }

    return 0;
}
