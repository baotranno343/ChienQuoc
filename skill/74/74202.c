// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74202; }
// 函数：获取技能类型
string get_name() { return "Cao Cấp Hộ Tâm Thuẫn"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 0; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 1; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Kỹ năng của Bảo thú, tăng 13 % Nội Kháng.\n";
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
	int pp;
	if ( pet->get_skill(74102) )
		pet->remove_skill_effect(74102);
	pp = pet->get_pp()*13/100;
	pet->set("sk74202",pp);
	NPC_PET_D->count_pp(pet);
}
//删除技能的影响
void remove_skill_effect(object pet,object owner)
{
	int pp;
	pp = pet->get("sk74202");
	if ( pp )
	{
		pet->delete("sk74202");
		NPC_PET_D->count_pp(pet);
	}
	if ( pet->get_skill(74102) )
		pet->skill_effect(74102);	
}