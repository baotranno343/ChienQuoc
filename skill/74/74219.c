// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74219; }
// 函数：获取技能类型
string get_name() { return "Nội Kháng Phù Trợ"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 0; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 1; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Kỹ năng của Bảo thú, sau khi được triệu hồi sẽ tăng 5 % Nội Kháng cho chủ nhân,\n Khi Bảo thú chết hoặc bị thu hồi thì kỹ năng sẽ mất tác dụng.\n";
}
// 函数：获取指令类型
int get_perform_type() { return 0; }

// 函数：能否使用指令
void can_perform( object me ,object pet)
{
        send_user( me, "%c%c%d%d%c%c%w%w%s", 0xA1,19,getoid(pet),get_id(),1, get_perform_type(), 1, 0, get_name() );
}
//技能的影响(召唤)
void show_effect(object pet,object owner)
{
	int point;
	point = owner->get_pp()/20;
	pet->set("sk74219",point);
	USER_ENERGY_D->count_pp(owner);
}
//删除技能的影响(收回)
void remove_show_effect(object pet,object owner)
{
	int point;
	point = pet->get("sk74219");
	if ( point )
	{
		pet->delete("sk74219");
		USER_ENERGY_D->count_pp(owner);
	}
}
//技能的影响
void skill_effect(object pet,object owner)
{
	if ( pet->get("show") )
		show_effect(pet,owner);
}
//删除技能的影响
void remove_skill_effect(object pet,object owner)
{
	if ( pet->get("show") )
		remove_show_effect(pet,owner);
}