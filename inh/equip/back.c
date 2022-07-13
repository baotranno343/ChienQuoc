
#include <equip.h>

inherit ITEM;
inherit "/inh/equip/equip";

private static int Gender;              // 性别标志
private static int Type1;               // 背饰代码1
private static int Type2;               // 背饰代码2
private static int Color1;              // 背饰1颜色(色码２，色码１)
private static int Color2;              // 背饰2颜色(色码４，色码３)

// 函数：获取性别标志
int get_gender() { return Gender; }

// 函数：设置性别标志
int set_gender( int flag ) { return Gender = flag; }

int get_back_type() {return Type1;}

int set_back_type(int i) {return Type1 = i;}

int get_back2_type() {return Type2;}

int set_back2_type(int i) {return Type2 = i;}

int get_back_color() {return Color1;}

int set_back_color(int i) {return Color1 = i;}

int get_back2_color() {return Color2;}

int set_back2_color(int i) {return Color2 = i;}

int get_equip_type() { return BACK_TYPE; }
