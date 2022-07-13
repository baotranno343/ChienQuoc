// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74207; }
// 函数：获取技能类型
string get_name() { return "Cao Cấp Độc Nha"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 0; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 1; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Kỹ năng của Bảo thú, tấn công Ngoại Công có 15 % khả năng làm mục tiêu trúng Độc trong 20 giây,\n Tiêu hao 30 điểm Khí Huyết mỗi 2 giây.\n";
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
	if ( pet->get_skill(74116) )
		pet->remove_skill_effect(74116);
	pet->set("@",300);
}
//删除技能的影响
void remove_skill_effect(object pet,object owner)
{
	pet->delete("@");
	if ( pet->get_skill(74116) )
		pet->skill_effect(74116);

}
