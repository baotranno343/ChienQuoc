
#ifndef _NPC_H_
#define _NPC_H_

#define PLAYER_TYPE_1   1               // 0x01: 玩家类型(登录成功)
#define PLAYER_TYPE_2   2               // 0x02: 玩家类型(准备就绪)

#define PK_TYPE         16              // 0x10: 主动ＰＫ

#define PK_TYPE_1       17              // 0x11: ＰＫ类型１
#define PK_TYPE_2       18              // 0x12: ＰＫ类型２
#define PK_TYPE_3       19              // 0x13: ＰＫ类型３
#define PK_TYPE_4       20              // 0x14: ＰＫ类型４
#define PK_TYPE_5       21              // 0x15: ＰＫ类型５

#define OFFICER_TYPE    128             // 0x80: 功能 NPC
#define NPC_TYPE        129             // 0x81: 普通 NPC
#define FIGHTER_TYPE    130             // 0x82: 战斗 NPC(小怪)
#define FIGHTER_TYPE_2  131             // 0x83: 战斗 NPC(小怪头目)

#define SLAVE_TYPE_1    160             // 0xa0: 奴仆 NPC(初级)
#define SLAVE_TYPE_2    161             // 0xa1: 奴仆 NPC(二级)
#define SLAVE_TYPE_3    162             // 0xa2: 奴仆 NPC(三级)
#define SLAVE_TYPE_4    163             // 0xa3: 奴仆 NPC(四级)
#define SLAVE_TYPE_5    164             // 0xa4: 奴仆 NPC(五级)

// -------------------------------------------------------------

#define SOLDIER_TYPE_1  1               // 鬼卒    // 注：顺序不能改
#define SOLDIER_TYPE_2  2               // 天兵
#define SOLDIER_TYPE_3  3               // 神将

#define ZOMBIE_TYPE_1   4               // 僵尸
#define ZOMBIE_TYPE_2   5               // 豆兵
#define ZOMBIE_TYPE_3   6               // 怪物

// -------------------------------------------------------------

#define WALK_SPEED_1    4               // 0.4 秒    // 行走速度
#define WALK_SPEED_2    6               // 0.6 秒
#define WALK_SPEED_3    8               // 0.8 秒
#define WALK_SPEED_4    10              // 1.0 秒

#define ATTACK_SPEED_1  10              // 1.0 秒    // 战斗速度
#define ATTACK_SPEED_2  20              // 2.0 秒
#define ATTACK_SPEED_3  30              // 3.0 秒
#define ATTACK_SPEED_4  40              // 4.0 秒

// -------------------------------------------------------------

#define MALE            1               // 男性
#define FEMALE          2               // 女性

#define KING            10              // 王爷
#define MINISTER        11              // 大臣
#define CAPTOR          12              // 捕头
#define CAPTOR_2        13              // 衙役

#define MARSHAL         20              // 将帅
#define GENERAL         21              // 军官
#define SOLDIER         22              // 士兵

#define RICH_MAN        30              // 富人、富商
#define RICH_YOUNG      35              // 富家公子
#define RICH_BOY        40              // 富家男孩

#define SELLER          31              // 老板
#define SCHOLAR         36              // 书生
#define BOY             41              // 穷家男孩

#define PALADIN         50              // 游侠
#define GUARD           51              // 守卫
#define WARRIOR         52              // 打手

#define WOODMAN         53              // 樵夫、猎户
#define WAITER          54              // 小二、渔夫
#define ROGUE           55              // 流氓、无赖

#define FARMER          56              // 农民

#define RICH_WOMAN      60              // 贵妇
#define RICH_LADY       61              // 富家小姐
#define RICH_GIRL       62              // 富家女孩
#define SERVANT_GIRL    63              // 丫鬟

#define FARM_WOMAN      70              // 村妇
#define FARM_LADY       71              // 村姑
#define GIRL            72              // 穷家女孩

#define ZOMBIE          99              // 僵尸

#endif                                  /* _NPC_H_ */
