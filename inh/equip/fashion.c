
#include <equip.h>

inherit ITEM;
inherit "/inh/equip/equip";

private static int Gender;              // 性别标志
private static int Code;                // 衣着代码
private static int Color1;              // 衣着颜色(色码２，色码１)
private static int Color2;              // 衣着颜色(色码４，色码３)

// 函数：获取性别标志
int get_gender() { return Gender; }

// 函数：设置性别标志
int set_gender( int flag ) { return Gender = flag; }

// 函数：获取衣着代码
int get_fashion_code() { return Code; }

//函数：设置衣着代码
int set_fashion_code( int code ) { return Code = code; }

// 函数：获取衣着颜色
int get_fashion_color_1() { return Color1; }

// 函数：设置衣着颜色
int set_fashion_color_1( int color ) {return Color1 = color;}

// 函数：获取衣着颜色
int get_fashion_color_2() { return Color2; }

// 函数：设置衣着颜色
int set_fashion_color_2( int color ) { return Color2 = color; }

int get_equip_type() { return FASHION_TYPE; }
