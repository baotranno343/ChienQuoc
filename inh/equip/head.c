
#include <equip.h>

inherit ITEM;
inherit "/inh/equip/equip";

private int Gender;                     // 性别标志
private int Code;                       // 帽子代码
private int Color;                      // 帽子颜色(色码２，色码１)

// 函数：获取性别标志
int get_gender() { return Gender; }

// 函数：设置性别标志
int set_gender( int flag ) { return Gender = flag; }

// 函数：获取帽子代码
int get_head_code() { return Code; }

// 函数：设置帽子代码
int set_head_code( int code ) { return Code = code; }

// 函数：获取帽子颜色
int get_head_color() { return Color; }

// 函数：设置帽子颜色
int set_head_color( int color ) { return Color = color; }

int get_equip_type() { return HEAD_TYPE; }
