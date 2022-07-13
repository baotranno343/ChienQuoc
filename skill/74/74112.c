// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74112; }
// 函数：获取技能类型
string get_name() { return "Phục Sinh"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 0; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 0; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Kỹ năng của Bảo thú, Khi bảo thủ chết sẽ \nkhông thu về mà sau 10 giây \ntự động hồi sinh,khí huyết và \npháp lực sẽ còn lại 20 % \nThời gian tái sử dụng là 30 phút \nSau khi sống lại tuổi thọ giảm 50, \ntrung thành giảm 20.";
}
// 函数：获取指令类型
int get_perform_type() { return 0; }

// 函数：能否使用指令
void can_perform( object me ,object pet)
{
        send_user( me, "%c%c%d%d%c%c%w%w%s", 0xA1,19,getoid(pet),get_id(),1, get_perform_type(), 1, 0, get_name() );
}
//技能的影响
void skill_effect(object pet,object owner)
{
	if ( pet->get_skill(74203) )
		return ;
	pet->set("revive",1);
}
//删除技能的影响
void remove_skill_effect(object pet,object owner)
{
	if ( pet->get_skill(74203) )
		return ;
	pet->delete("revive");
}