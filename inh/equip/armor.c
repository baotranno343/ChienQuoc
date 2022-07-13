
#include <equip.h>

inherit ITEM;
inherit "/inh/equip/equip";

private static int Gender;              // 性别标志
private static int Code;                // 衣着代码
private static int Color1;              // 衣着颜色(色码２，色码１)
private static int Color2;              // 衣着颜色(色码４，色码３)

private static int * armor_code = ({  20000, 20100, 30000, 30100, 40000, 40100, 50000, 50100, 80000, 80100, 60000, 60100, 70000, 70100, 10000, 10100, 10200, 10300 });

// 函数：获取性别标志
int get_gender() { return Gender; }

// 函数：设置性别标志
int set_gender( int flag ) { return Gender = flag; }

// 函数：获取衣着代码
int get_armor_code() 
{ 
	object me = this_object();
	int family, gender, level, i, size;
//	if (MAIN_D->get_host_type()!=1000) return Code; 
	family = me->get_family();
	if (family==0) family=8;
	if (family>8) family=8;
	gender = me->get_gender();
	family -= 1;
	gender-=1;
	if (gender<0||gender>1) gender=0;		
	return armor_code[2*family+gender];
}

// 函数：设置衣着代码
int set_armor_code( int code ) { return Code = code; }

// 函数：获取衣着颜色
int get_armor_color_1() { return Color1; }

// 函数：设置衣着颜色
int set_armor_color_1( int color ) { return Color1 = color; }

// 函数：获取衣着颜色
int get_armor_color_2() { return Color2; }

// 函数：设置衣着颜色
int set_armor_color_2( int color ) { return Color2 = color; }

int get_equip_type() { return ARMOR_TYPE; }
