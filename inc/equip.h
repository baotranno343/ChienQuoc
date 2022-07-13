
#ifndef _EQUIP_H_
#define _EQUIP_H_

int get_armor_code();
int get_armor_color_1();
int get_armor_color_2();
int get_head_code();
int get_head_color();
int get_weapon_code();
int get_weapon_code_2();

#define MAX_EQUIP       10               // 装备总数

#define HEAD_TYPE       101              // 头部(勿改号码顺序)
#define NECK_TYPE       102              // 颈部
#define WEAPON_TYPE     103              // 手部：武器
#define ARMOR_TYPE      104              // 身部：防具
#define WAIST_TYPE      105              // 腰部
#define BOOTS_TYPE      106              // 脚部
#define HAND_TYPE       107              // 法宝/毒药/阵旗
#define FAMILY_TYPE     108              // 门派信物
#define BACK_TYPE     	109              // 背饰
#define FASHION_TYPE      110              // 身部：防具

#define HEAD_POSITION       0              // 头部(勿改号码顺序)
#define NECK_POSITION       1              // 颈部
#define WEAPON_POSITION     2              // 手部：武器
#define ARMOR_POSITION      3              // 身部：防具
#define WAIST_POSITION      4              // 腰部
#define BOOTS_POSITION      5              // 脚部
#define HAND_POSITION       6              // 法宝/毒药/阵旗
#define FAMILY_POSITION     7              // 门派信物
#define BACK_POSITION       8              // 背饰
#define FASHION_POSITION      9              // 身部：防具

#define BAG_TYPE_1      1               // 包裹
#define BAG_TYPE_2      2               // 百宝囊
#define BAG_TYPE_3      4               // 乾坤袋

#define UNARMED         60              // 空手
#define BLADE           61              // 刀
#define SWORD           62              // 剑
#define SPEAR           63              // 枪
#define STICK           64              // 棍
#define THROWING        69              // 暗器

#define M_DUANGUA       10000              // 短褂
#define M_BUYI          10000              // 布衣
#define M_JINZHUANG     30000              // 劲装
#define M_CHANGPAO      40000              // 长袍
#define M_GUANPAO       70000              // 官袍
#define M_PIJIA         50000              // 皮甲
#define M_RUANJIA       50000              // 软甲
#define M_KAIJIA        40000              // 铠甲
#define M_ZHANJIA       40000              // 战甲
#define F_DUANSHAN      10100              // 短衫
#define F_BUYI          10100              // 布衣
#define F_JINZHUANG     30100              // 劲装
#define F_BEIZI         40000              // 背子
#define F_RUQUN         70100              // 襦裙
#define F_PIJIA         50100              // 皮甲
#define F_RUANJIA       50100              // 软甲
#define F_KAIJIA        40100              // 铠甲
#define F_ZHANJIA       40100              // 战甲

#define X_JIANGSHI      99              // 僵尸
#define X_JOBS          100             // 职业类

#define M_BANGDAI       40              // 绑带
#define M_ZHANMAO       41              // 毡帽
#define M_WUSHENGMAO    42              // 武生帽
#define M_PINGMAO       43              // 平帽
#define M_DAOGUAN       44              // 道冠
#define M_PIMAO         45              // 皮帽
#define M_ZIJINGUAN     46              // 紫金冠
#define M_YINGKUI       47              // 缨盔
#define M_ZHANKUI       48              // 战盔
#define F_BANGDAI       50              // 绑带
#define F_PINGMAO       51              // 平帽
#define F_WUSHENGMAO    52              // 武生帽
#define F_DAOGUAN       53              // 道冠
#define F_SHAMAO        54              // 纱帽
#define F_PIMAO         55              // 皮帽
#define F_ZIJINGUAN     56              // 紫金冠
#define F_YINGKUI       57              // 缨盔
#define F_ZHANKUI       58              // 战盔

#define H_WHITE         0x630c
#define M_WHITE         0x52aa
#define WHITE           0x4a49          // 白色
#define H_GRAY          0x39e7
#define M_GRAY          0x3186
#define GRAY            0x2124          // 灰色
#define H_BLACK         0x18c3
#define M_BLACK         0x0861
#define BLACK           0x0020          // 黑色
#define H_RED           0x6186
#define M_RED           0x60c3
#define D_RED           0x6000          // 红色
#define H_MAROON        0x30c3
#define M_MAROON        0x3061
#define MAROON          0x3000          // 绛紫(暗红)
#define H_LIME          0x3306
#define M_LIME          0x1b03
#define LIME            0x0300          // 草绿
#define H_GREEN         0x1983
#define M_GREEN         0x0981
#define GREEN           0x0180          // 绿色(深绿)
#define H_BLUE          0x318c
#define M_BLUE          0x18cc
#define BLUE            0x000c          // 蓝色
#define H_NAVY          0x18c6
#define M_NAVY          0x0866
#define NAVY            0x0006          // 藏蓝(深蓝)
#define H_YELLOW        0x6306
#define M_YELLOW        0x6303
#define YELLOW          0x6300          // 黄色
#define H_OLIVE         0x3183
#define M_OLIVE         0x3181
#define OLIVE           0x3180          // 橄榄(暗黄)
#define H_FUCHSIA       0x618c
#define M_FUCHSIA       0x60cc
#define FUCHSIA         0x600c          // 紫红
#define H_PURPLE        0x30c6
#define M_PURPLE        0x3066
#define PURPLE          0x3006          // 紫色(深紫)
#define H_CYAN          0x330c
#define M_CYAN          0x1b0c
#define CYAN            0x030c          // 海蓝
#define H_TEAL          0x1986
#define M_TEAL          0x0986
#define TEAL            0x0186          // 黑绿(深青)

#define H_ORANGE        0x6180
#define M_ORANGE        0x5140
#define ORANGE          0x4100          // 橙色
#define H_BROWN         0x30c0
#define M_BROWN         0x2080
#define BROWN           0x1040          // 褐色
#define H_PINK          0x6006
#define M_PINK          0x5005
#define PINK            0x4004          // 粉红
#define H_RADIANCE      0x3003
#define M_RADIANCE      0x2002
#define RADIANCE        0x1001          // 深粉红

#define H_WHITE_H       0x630c0000
#define M_WHITE_H       0x52aa0000
#define WHITE_H         0x4a490000      // 白色
#define H_GRAY_H        0x39e70000
#define M_GRAY_H        0x31860000
#define GRAY_H          0x21240000      // 灰色
#define H_BLACK_H       0x18c30000
#define M_BLACK_H       0x08610000
#define BLACK_H         0x00200000      // 黑色
#define H_RED_H         0x61860000
#define M_RED_H         0x60c30000
#define D_RED_H         0x60000000      // 红色
#define H_MAROON_H      0x30c30000
#define M_MAROON_H      0x30610000
#define MAROON_H        0x30000000      // 绛紫(暗红)
#define H_LIME_H        0x33060000
#define M_LIME_H        0x1b030000
#define LIME_H          0x03000000      // 草绿
#define H_GREEN_H       0x19830000
#define M_GREEN_H       0x09810000
#define GREEN_H         0x01800000      // 绿色(深绿)
#define H_BLUE_H        0x318c0000
#define M_BLUE_H        0x18cc0000
#define BLUE_H          0x000c0000      // 蓝色
#define H_NAVY_H        0x18c60000
#define M_NAVY_H        0x08660000
#define NAVY_H          0x00060000      // 藏蓝(深蓝)
#define H_YELLOW_H      0x63060000
#define M_YELLOW_H      0x63030000
#define YELLOW_H        0x63000000      // 黄色
#define H_OLIVE_H       0x31830000
#define M_OLIVE_H       0x31810000
#define OLIVE_H         0x31800000      // 橄榄(暗黄)
#define H_FUCHSIA_H     0x618c0000
#define M_FUCHSIA_H     0x60cc0000
#define FUCHSIA_H       0x600c0000      // 紫红
#define H_PURPLE_H      0x30c60000
#define M_PURPLE_H      0x30660000
#define PURPLE_H        0x30060000      // 紫色(深紫)
#define H_CYAN_H        0x330c0000
#define M_CYAN_H        0x1b0c0000
#define CYAN_H          0x030c0000      // 海蓝
#define H_TEAL_H        0x19860000
#define M_TEAL_H        0x09860000
#define TEAL_H          0x01860000      // 黑绿(深青)

#define H_ORANGE_H      0x61800000
#define M_ORANGE_H      0x51400000
#define ORANGE_H        0x41000000      // 橙色
#define H_BROWN_H       0x30c00000
#define M_BROWN_H       0x20800000
#define BROWN_H         0x10400000      // 褐色
#define H_PINK_H        0x60060000
#define M_PINK_H        0x50050000
#define PINK_H          0x40040000      // 粉红
#define H_RADIANCE_H    0x30030000
#define M_RADIANCE_H    0x20020000
#define RADIANCE_H      0x10010000      // 深粉红

#endif                                  /* _EQUIP_H_ */
