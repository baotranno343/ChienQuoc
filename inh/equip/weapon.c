
#include <equip.h>

inherit ITEM;
inherit "/inh/equip/equip";

private int WeaponType;                 // 武器类别
private static int Poison;              // 毒性点数

// 函数：获取武器类别
int get_weapon_type() { return WeaponType; }

// 函数：设置武器类别
int set_weapon_type( int type ) { return WeaponType = type; }

int get_equip_type() { return WEAPON_TYPE; }

// 函数：获取毒性点数
int get_poison() { return Poison; }

// 函数：设置毒性点数
int set_poison( int point ) { return Poison = range_value(point, 0, MAX_NUMBER); }

// 函数：增添毒性点数
int add_poison( int point ) { return set_poison( get_poison() + point ); }
