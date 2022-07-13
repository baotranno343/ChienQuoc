
#ifndef _SKILL_H_
#define _SKILL_H_

#define FAMILY_1        "Đào Hoa Nguyên"
#define FAMILY_2        "Thục Sơn"
#define FAMILY_3        "Cấm Vệ Quân"
#define FAMILY_4        "Đường Môn"
#define FAMILY_5        "Mao Sơn"
#define FAMILY_6        "Côn Luân"
#define FAMILY_7        "Vân Mộng Cốc"

// -------------------------------------------------------------

// 由 get_perform_type 返回，不能为 0
// fight_d.c 中用于判断是否 perform
#define ON_ME           1               // 自己使用
#define ON_ITEM         2               // 对物使用
#define ON_CHAR         3               // 对人使用
#define ON_XY           4               // 坐标使用(如果已有目标，对目标使用)
#define ON_ITEM_2       5               // 对物使用(他人)
#define ON_XY2           6              // 强制对坐标使用

#define ON_ME_7         11              // 自己使用
#define ON_ITEM_7       12              // 对物使用
#define ON_CHAR_7       13              // 对人使用
#define ON_XY_7         14              // 坐标使用
#define ON_ITEM_8       15              // 对物使用(他人)

//宠物使用
#define ON_CHAR_P	1              // 对人使用
#define ON_ME_P		2              // 自己使用
#define ON_XY_P		3              // 对坐标使用

#define ON_TALISMAN     19              // 法宝使用

// -------------------------------------------------------------

#define PF_STOP         0               // 停止持续效果
#define PF_ONCE         1               // 非持续效果
#define PF_LOOP         2               // 持续效果

#define OVER_TILE       0               // 地表之上，建筑之下(通常用于 x, y 法术)
#define UNDER_FOOT      1               // 人物脚下(通常用于人物法术)
#define OVER_BODY       2               // 人物之上(通常用于人物法术)
#define OVER_ALL        3               // 所有人物之上(用于箭塔之抛物线攻击效果)

// -------------------------------------------------------------

#define EFFECT_GOOD     1               // 好的持续效果
#define EFFECT_BAD      0               // 坏的持续效果

// -------------------------------------------------------------

#define HIT_NONE        0               // 无受击效果

#define HIT_NORMAL      9072            // 受击效果(普通)

#define HIT_UNARMED     9073            // 受击效果(空手)
#define HIT_BLADE       9074            // 受击效果(刀)
#define HIT_SWORD       9074            // 受击效果(剑)
#define HIT_SPEAR       9076            // 受击效果(枪)
#define HIT_STICK       9077            // 受击效果(棍)
#define HIT_THROWING    9078            // 受击效果(暗器)

// -------------------------------------------------------------

#define SKILL_0111      0111            // 基本拳脚
#define SKILL_0121      0121            // 基本刀法
#define SKILL_0131      0131            // 基本剑法
#define SKILL_0141      0141            // 基本枪法
#define SKILL_0151      0151            // 基本棍法
#define SKILL_0161      0161            // 暗器投射
#define PF_FILE_01611   "/skill/01/01611"

#define SKILL_0211      0211            // 太古神拳
#define PF_FILE_02114   "/skill/02/02114"
#define PF_FILE_02115	"/skill/02/02115"
#define PF_FILE_02117   "/skill/02/02117"
#define PF_FILE_02118	"/skill/02/02118"
#define SKILL_0221      0221            // 泼风刀法
#define PF_FLAG_02214  "02214"
#define PF_FILE_02212   "/skill/02/02212"
#define PF_FILE_02214   "/skill/02/02214"
#define PF_FILE_02216   "/skill/02/02216"
#define SKILL_0231      0231            // 飞仙剑法
#define PF_FILE_02313   "/skill/02/02313"
#define PF_FILE_02314   "/skill/02/02314"
#define SKILL_0241      0241            // 霸王枪法
#define PF_FILE_02412   "/skill/02/02412"
#define PF_FILE_02416   "/skill/02/02416"
#define SKILL_0251      0251            // 疯魔棍法
#define PF_FLAG_02514  "02514"
#define PF_FLAG_02515  "02515"
#define PF_FILE_02512   "/skill/02/02512"
#define PF_FILE_02513   "/skill/02/02513"
#define PF_FILE_02514   "/skill/02/02514"
#define PF_FILE_02515   "/skill/02/02515"
#define SKILL_0261      0261            // 漫天花雨
#define PF_FILE_02615   "/skill/02/02615"
#define PF_FILE_02616   "/skill/02/02616"
#define SKILL_0271      0271            // 降魔剑法
#define SKILL_0281      0281            // 清风剑法

#define SKILL_0202      0202            // 招架之术

#define SKILL_0212      0212            // 拳脚招架
#define SKILL_0222      0222            // 刀法格挡
#define SKILL_0232      0232            // 剑法格挡
#define PF_NO_02321     02321
#define PF_FILE_02321   "/skill/02/02321"
#define SKILL_0242      0242            // 枪法格挡
#define SKILL_0252      0252            // 棍法格挡

#define SKILL_0104      0104            // 腾挪躲闪
#define SKILL_0109      0109            // 经络学说

#define SKILL_0324      0324            // 踏雪无痕
#define SKILL_0364      0364            // 踏雪无痕(pf)
#define PF_FILE_03641   "/skill/03/03641"
#define PF_NO_03641     03641
#define SKILL_0325      0325            // 混元真气
#define PF_FILE_03251   "/skill/03/03251"
#define PF_FILE_03252   "/skill/03/03252"
#define PF_FILE_03254   "/skill/03/03254"
#define PF_NO_03251     03251
#define PF_NO_03252     03252
#define PF_NO_03254     03254
#define SKILL_0316      0316            // 金刚不坏
#define SKILL_0317      0317            // 护体金罡
#define PF_FILE_03171   "/skill/03/03171"
#define PF_FILE_03172   "/skill/03/03172"
#define PF_FILE_03173   "/skill/03/03173"
#define PF_FLAG_03171  "03171"
#define PF_FLAG_03172  "03172"
#define PF_FLAG_03173  "03173"
#define SKILL_0319      0319            // 周天运转
#define SKILL_0329      0329            // 周天运转
#define SKILL_0349      0349            // 周天运转
#define SKILL_0348      0348            // 兵法
#define PF_FILE_03481   "/skill/03/03481"
#define PF_FILE_03482   "/skill/03/03482"
#define PF_FILE_03483   "/skill/03/03483"
#define PF_FILE_03484   "/skill/03/03484"
#define PF_FILE_03485   "/skill/03/03485"
#define PF_FILE_03486   "/skill/03/03486"
#define PF_FLAG_03484  "03484"
#define PF_FLAG_03485  "03485"
#define PF_FLAG_03486  "03486"

#define SKILL_0363      0363            // 唐门心法
#define PF_FILE_03631   "/skill/03/03631"
#define PF_FILE_03632   "/skill/03/03632"
#define PF_NO_03631     03631
#define SKILL_0368      0368            // 巧手空空
#define PF_FLAG_03681  "03681"

#define SKILL_0401      0401            // 道家学说
#define SKILL_0411      0411            // 大乘道法
#define SKILL_0421      0421            // 大乘道法
#define SKILL_0402      0402            // 诵经
#define SKILL_0403      0403            // 禅定
#define SKILL_0422      0422            // 阴阳五行

#define SKILL_0371      0371            // 强化太古神拳
#define SKILL_0372      0372            // 强化拳脚招架
#define SKILL_0373      0373            // 强化金刚不坏
#define SKILL_0374      0374            // 强化护体金罡
#define SKILL_0375      0375            // 强化周天运转（桃花）

#define SKILL_0331      0331            // 强化天罗刀法
#define SKILL_0332      0332            // 强化飞仙剑法
#define SKILL_0333      0333            // 强化混元真气
#define SKILL_0334      0334            // 强化周天运转（蜀山）
#define SKILL_0335      0335            // 强化刀剑格挡

#define SKILL_0351      0351            // 强化霸王枪法
#define SKILL_0352      0352            // 强化疯魔棍法
#define SKILL_0353      0353            // 强化步法
#define SKILL_0354      0354            // 强化磨炼
#define SKILL_0355      0355            // 强化兵法

#define SKILL_0381      0381            // 强化漫天花雨
#define SKILL_0382      0382            // 强化唐门毒经
#define SKILL_0383      0383            // 强化潜隐心法
#define SKILL_0384      0384            // 强化踏雪无痕
#define SKILL_0385      0385            // 强化唐门心法

#define SKILL_0441      0441            // 强化金仙符咒
#define SKILL_0442      0442            // 强化金罡法咒
#define SKILL_0443      0443            // 强化乾坤挪移
#define SKILL_0444      0444            // 强化阴阳五行
#define SKILL_0445      0445            // 强化大乘道法

#define SKILL_0461      0461            // 强化降魔法咒
#define SKILL_0462      0462            // 强化道法神通
#define SKILL_0463      0463            // 强化逆天法咒
#define SKILL_0464      0464            // 强化顺天法咒
#define SKILL_0465      0465            // 强化玄学正道

#define SKILL_0541      0541            // 强化御风心法
#define SKILL_0542      0542            // 强化医术
#define SKILL_0543      0543            // 强化中医药理
#define SKILL_0544      0544            // 强化迷魂决
#define SKILL_0545      0545            // 强化奇门遁甲


#define SKILL_0413      0413            // 道法神通
#define PF_FILE_04131   "/skill/04/04131"
#define PF_FILE_04132   "/skill/04/04132"
#define PF_FILE_04133   "/skill/04/04133"

#define SKILL_0423      0423            // 天师符咒
#define PF_FILE_04231   "/skill/04/04231"
#define PF_FILE_04232   "/skill/04/04232"
#define PF_FILE_04233   "/skill/04/04233"
#define PF_FILE_04234   "/skill/04/04234"
#define PF_FILE_04236   "/skill/04/04236"
#define PF_FILE_04243   "/skill/04/04243"
#define SKILL_0424      0424            // 金罡法咒

#define SKILL_0425      0425            // 乾坤挪移
#define PF_FILE_04251   "/skill/04/04251"
#define PF_FILE_04252   "/skill/04/04252"
#define PF_NO_04251     04251
#define PF_NO_04252     04252

#define SKILL_0414      0414            // 逆天法咒
#define PF_FILE_04143   "/skill/04/04143"
#define PF_FILE_04144   "/skill/04/04144"
#define PF_FILE_04145   "/skill/04/04145"

#define SKILL_0417      0417            // 神打
#define PF_NO_04171     04171
#define PF_FILE_04171   "/skill/04/04171"

#define SKILL_0408      0408            // 奇门遁甲
#define SKILL_0418      0418            // 穿越时空

#define SKILL_0409      0409            // 神游
#define SKILL_0429      0429            // 龙游四海

#define SKILL_0501      0501            // 中医药理
#define PF_FILE_05011   "/skill/05/05011"
#define SKILL_0511      0511            // 医术
#define SKILL_0503      0503            // 炼丹术
#define SKILL_0513      0513            // 金丹法门

#define SKILL_0521      0521            // 毒经
#define PF_FILE_05211   "/skill/05/05211"
#define PF_FILE_05212   "/skill/05/05212"
#define SKILL_0531      0531            // 迷魂诀
#define PF_FILE_05311   "/skill/05/05311"
#define SKILL_0591      0591            // 布阵图

#define PF_FILE_LOOP    "/skill/00/loop"

#define SEAL_AREA       "seal.area"     // 布阵尺寸
#define SEAL_START      "seal.start"    // 开始时间
#define SEAL_INTERVAL   "seal.interval" // 阵法时间
#define SEAL_CP         "seal.cp"       // 阵法攻击

#define SKILL_USER      0001            // 指令
#define PF_NO_00031     "/skill/00/00031"

#define SKILL_ACTOR     0010            // 艺人
#define SKILL_FARMER    0020            // 农夫
#define SKILL_SOLDIER   0030            // 军官
#define SKILL_SCHOLAR   0040            // 书生
#define SKILL_TRADER    0050            // 商人

#define SKILL_TALISMAN  0090            // 法宝
#define PF_FILE_11001   "/skill/11/11001"
#define PF_FILE_11002   "/skill/11/11002"
#define PF_FILE_11003   "/skill/11/11003"

#endif                                  /* _SKILL_H_ */
