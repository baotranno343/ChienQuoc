// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return %d; }
// 函数：获取技能类型
string get_name() { return "%s"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return %d; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return %d; }
// 函数：获取描述
string get_desc( object me )
{
	return "%s";
}
// 函数：获取指令类型
int get_perform_type() { return 0; }

// 函数：能否使用指令
void can_perform( object me ,object pet)
{
        %s
}
