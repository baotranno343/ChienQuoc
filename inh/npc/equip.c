
#include <equip.h>

private  int ArmorCode;           // 衣着代码
private  int ArmorColor1;         // 衣着颜色(色码２，色码１)
private  int ArmorColor2;         // 衣着颜色(色码４，色码３)

private  int HeadCode;            // 帽子代码
private  int HeadColor;           // 帽子颜色

private  int WeaponCode = UNARMED;// 武器代码
private  int WeaponColor = 0;     // 武器类别

// -------------------------------------------------------------

// 函数：获取装备数组
object *get_all_equip() { return ({ 0, 0, 0, 0, 0, 0, 0, 0 }); }    // 装备数组：头、颈、手、身、腰、脚、法宝

// 函数：获取装备对象
object get_equip( int index ) { return 0; }    // NPC 不装备道具

// 函数：设置装备对象
int use_equip( object equip ) { return NPC_EQUIP_D->use_equip( this_object(), equip ); }    // 只有装备，没有卸除

// -------------------------------------------------------------

// 函数：获取衣着代码
int get_armor_code() { return ArmorCode; }

// 函数：设置衣着代码
int set_armor_code( int code ) { return ArmorCode = code; }

// 函数：获取衣着颜色
int get_armor_color_1() { return ArmorColor1; }

// 函数：设置衣着颜色
int set_armor_color_1( int color ) { return ArmorColor1 = color; }

// 函数：获取衣着颜色
int get_armor_color_2() { return ArmorColor2; }

// 函数：设置衣着颜色
int set_armor_color_2( int color ) { return ArmorColor2 = color; }

// 函数：获取帽子代码
int get_head_code() { return HeadCode; }

// 函数：设置帽子代码
int set_head_code( int code ) { return HeadCode = code; }

// 函数：获取帽子颜色
int get_head_color() { return HeadColor; }

// 函数：设置帽子颜色
int set_head_color( int color ) { return HeadColor = color; }

// 函数：获取武器代码
int get_weapon_code() { return WeaponCode; }

// 函数：设置武器代码
int set_weapon_code( int code ) { return WeaponCode = code; }

// 函数：获取武器类别
int get_weapon_color() { return WeaponColor; }

// 函数：设置武器类别
int set_weapon_color( int code ) { return WeaponColor = code; }

// 函数：获取武器代码／类型
int get_weapon_code_2() { return WeaponCode | ( WeaponColor << 8 ); }
