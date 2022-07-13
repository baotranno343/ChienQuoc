
#ifndef _EFFECT_H_
#define _EFFECT_H_
//31 63 95 127 159 191 223 255不能定义使用！
//简单效果
//每秒递减,到0调用

#define EFFECT_USER_LOGIN       0       // 连线保护

#define EFFECT_CHAR_BUSY        1       // 忙乱(眩晕)

#define EFFECT_CHAR_FAINT       2       // 眩晕(无法动作)  9002
#define EFFECT_CHAR_FAINT_0     3       // 眩晕保护
#define EFFECT_CHAR_FAINT_2     4       // 眩晕(无法动作)(麻沸散)  9002
#define EFFECT_CHAR_FAINT_3     5       // 眩晕保护
#define EFFECT_CHAR_FREEZE      6       // 僵直(无法动作)
#define EFFECT_CHAR_FREEZE_0    7       // 僵直保护
#define EFFECT_CHAR_SHUT        8       // 囚禁(不能行走)
#define EFFECT_CHAR_SHUT_0      9       // 囚禁保护
#define EFFECT_CHAR_NO_PF       10      // 封魔(禁止出招)
#define EFFECT_CHAR_NO_PF_0     11      // 封魔保护
#define EFFECT_CHAR_LAZY        12      // 延缓(攻击移动变慢)冰冻
#define EFFECT_CHAR_LAZY_0      13      // 延缓保护
#define EFFECT_CHAR_SLOW        14      // 延缓(移动变慢)
#define EFFECT_CHAR_SLOW_0      15      // 延缓保护
#define EFFECT_CHAR_DREAM_1     16      // 梦游(随机走路)失魂(保护状态)
#define EFFECT_CHAR_DREAM_0     17      // 梦游保护
#define EFFECT_CHAR_CHAOS       18      // 混乱(鼠标反转)
#define EFFECT_CHAR_CHAOS_0     19      // 混乱保护
#define EFFECT_CHAR_WOUND       20      // 负伤(－攻击－防御)  9020
#define EFFECT_CHAR_WOUND_0     21      // 负伤保护
#define EFFECT_USE_JIGUAN       22      // 使用机关的时间限制
#define EFFECT_CHAR_BLOOD_0     23      // 流血保护
#define EFFECT_CHAR_BLIND       24      // 失明(命中减半)
#define EFFECT_CHAR_BLIND_0     25      // 失明保护
#define EFFECT_MINE		26	//采矿
#define EFFECT_USER_BURN_0      27      // 燃烧保护
#define EFFECT_NO_WEAPON        28      // 武器失效
#define EFFECT_NO_WEAPON_0      29      // 武器失效保护
#define EFFECT_TRAVEL		30	// 通过驿站老板传送
//#define EFFECT_NO_USE		31	// 禁止使用这位

// -------------------------------------------------------------

#define EFFECT_USER_HP          32      // 临时＋ＨＰ
#define EFFECT_USER_MP          33      // 临时＋ＭＰ
#define EFFECT_USER_AP          34      // 临时＋ＡＰ
#define EFFECT_USER_DP          35      // 临时＋ＤＰ
#define EFFECT_USER_CP          36      // 临时＋ＣＰ
#define EFFECT_USER_PP          37      // 临时＋ＰＰ
#define EFFECT_USER_SP          38      // 临时＋ＳＰ    // 目前没用到

#define EFFECT_NPC_0531_1       32      // 被魅惑
#define EFFECT_NPC_0531_2       33      // 被魅惑２

#define EFFECT_NPC_ZOMBIE       34      // 僵尸
#define EFFECT_NPC_ZOMBIE_2     35      // 僵尸２

#define EFFECT_CONJURE		39	// 召唤

#define EFFECT_CHAR_5215        40      // ＡＰ－５０

#define EFFECT_USE_ITEM_1	41	// 一次性恢复气血药物的使用间隔
#define EFFECT_USE_ITEM_2	42	// 一次性恢复法力药物的使用间隔

#define EFFECT_2123_ARMORFALL	43	// 减防10%
#define EFFECT_2124		44	// 躲闪后的效果
#define EFFECT_EXCITE		45	// 鼓舞
#define EFFECT_REBOUND		46	// 反弹

#define EFFECT_MAGIC_4243	47	// 被施法变成小动物

#define EFFECT_CHAR_ATTACK      48      // 顺势推舟
#define EFFECT_CHAR_MOVE        49      // 踏雪无痕
#define EFFECT_CHAR_NO_MOVE   	50      // 不能移动
#define EFFECT_CHAR_CHANGE      51      // 乾坤挪移
#define EFFECT_SLEEP		52	// 昏迷，受攻击后恢复
#define EFFECT_03484		53	// 破釜沉舟的效果

#define EFFECT_DODGE		54	// 增加回避率
#define EFFECT_CHAR_HALFGOD2    55      // 神打(增加防御力)

#define EFFECT_CHAR_ARMORFALL   56      // 蚀甲(－防御－法防)
#define EFFECT_CHAR_ADD_DP      57      // 金钟罩(＋防御)
#define EFFECT_CHAR_ADD_PP      58      // 护体金光(＋法防)
#define EFFECT_CHAR_POWERFALL   59      // 蚀心(－攻击－法攻)
#define EFFECT_CHAR_POWERUP     60      // 银针渡厄(＋物攻)
#define EFFECT_CHAR_MISS        61      // 灵气甲
#define EFFECT_CHAR_HALFGOD     62      // 原神打(不受异常效果)
//#define EFFECT_NO_USE		63	// 禁止使用这位
#define EFFECT_CHAR_POWERUP2    64      // 金针渡厄(＋法攻)
#define EFFECT_CHAR_POWERUP3    65      // 强体术，增加气血上限
#define EFFECT_CHAR_MISS2       66      // 移花接木(减免伤害)

#define EFFECT_02614		67	// 透骨钉造成防御下降
#define EFFECT_PROGRESS2	68	// 完全排它的进度条，受攻击，走路，使用技能会中断
#define EFFECT_03642		69	// 瞬影步，完全回避下一次攻击

// -------------------------------------------------------------

#define EFFECT_CHAR_9140        70      // 不会中毒
#define EFFECT_CHAR_9145        71      // 不受异常状态影响

#define EFFECT_03643		72	// 捕风捉影

#define EFFECT_CHAR_KING        73      // 天王散
#define EFFECT_CHAR_KING_2      74      // 天王散２

#define EFFECT_CHAR_CHAN        75      // 被缠住
#define EFFECT_CHAR_SUPPRESS    76      // 压制法宝

#define EFFECT_DOUBLE_USE	77	// 双倍消耗

#define EFFECT_USER_HERB        78      // 采集草药
#define EFFECT_USER_HERB_OK     79      // 采集草药(结束)

#define EFFECT_USER_PK          80      // ＰＫ状态
#define EFFECT_USER_PK_RED      81      // ＰＫ红名

#define EFFECT_USER_DIE         83      // 死亡等待(正常)
#define EFFECT_USER_DIE_5       84      // 死亡等待(比武场)
#define EFFECT_USER_DIE_9       85      // 死亡等待(战场)

#define EFFECT_NPC_DIE         	83      // 宠物死亡等待(正常)

#define EFFECT_1808		86	// 临时增加气血10%
#define EFFECT_1809		87	// 临时增加法力10%
#define EFFECT_1810		88	// 临时增加敏捷10%
#define EFFECT_1811		89	// 临时增加防御10%

#define EFFECT_USER_ESCAPE      90      // 逃离战场

#define EFFECT_RENSHEN		91	// 人参的效果 + 600 气血
#define EFFECT_ITEM_9165	92	// 归元丹的效果

#define EFFECT_RIDE		93	// 试骑宠

#define EFFECT_ITEM_ORG         94      // 帮派
//#define EFFECT_NO_USE		95	// 禁止使用这位
#define EFFECT_USER_EXCHANGE_HP	96	// 临时送出的HP
#define EFFECT_USER_EXCHANGE_MP	97	// 临时送出的MP
#define EFFECT_USER_EXCHANGE_AP	98	// 临时送出的AP
#define EFFECT_USER_EXCHANGE_CP	99	// 临时送出的CP
#define EFFECT_NO_CLOTH        	100      // 衣服失效
#define EFFECT_NO_CLOTH_0      	101      // 衣服失效保护
#define EFFECT_HOE_WORK         120     // 挖宝的效果

//#define EFFECT_NO_USE		127	// 禁止使用这位

// ========================复杂效果==================================
//每秒递减,分段调用

#define EFFECT_CHAR_POISON      192      // 中毒   32*6
#define EFFECT_CHAR_POISON_2    193      // 中毒２
#define EFFECT_CHAR_BLOOD       194      // 流血(不断减血)
#define EFFECT_USER_BURN        195      // 燃烧(持续减少气血)

#define EFFECT_USER_HURT        196     // 伤人无形
#define EFFECT_02616		197	// 摄取精华的持续效果
#define EFFECT_CHAR_FALL        198     // 蚀魂
#define EFFECT_MP_FALL        	199     // 蚀魄

#define EFFECT_CHAR_INVISIBLE   200     // 隐身
#define EFFECT_CHAR_DREAM       201     // 梦游(随机走路)失魂
#define EFFECT_CON_HP_MP	202	// 持续恢复气血法力

#define EFFECT_PROGRESS		203	// 进度条参数 (凡是独占的走路会取消的都可以用这个)
#define EFFECT_CON_RECOVER	204	// 持续恢复气血法力(法术的效果，不中断)

#define EFFECT_CON_MP		205	// 持续恢复法力

#define EFFECT_USER_RECOVER     206     // 休整(恢复气血)
#define EFFECT_USER_THUNDER     207     // 雷龙诀

#define EFFECT_USER_STUDY       208     // 读书
#define EFFECT_CHAR_DANCE       209     // 跳舞
#define EFFECT_CHAR_SING        210     // 唱歌
#define EFFECT_USER_WORK        211     // 打工
#define EFFECT_XUESHI_HP	212	//使用血石的效果
#define EFFECT_FALISHI_MP	213	//使用法力石的效果
#define EFFECT_MAGIC_CARD	214	//变身卡
#define EFFECT_CHAR_IGNORE	215	//战斗忽略
#define EFFECT_CHAR_GOOD_BAD	216	//福祸相依
#define EFFECT_CHAR_SOUL_LOCK	217	//灵魂枷锁
#define EFFECT_OPEN_BOX		218	// 打开宝箱
#define EFFECT_CHAR_IMMORTAL    219      // 不死之身(不死)
#define EFFECT_ITEM_CITY        220      // 城市
#define EFFECT_USER_SUIT        221      // 套装
#define EFFECT_RECOVER_YUAN	222	// 恢复元气
#define HOA_COT_MIEN_CHUONG	254	// 恢复元气
#define BAT_TU_DON	253	// 恢复元气
#define PHONG_VU_PHA_DICH	252	// 恢复元气
//#define EFFECT_NO_USE		223	// 禁止使用这位

//#define EFFECT_NO_USE		255	// 禁止使用这位

#endif                                  /* _EFFECT_H_ */
