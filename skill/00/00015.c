
#include <ansi.h>
#include <skill.h>
#include <equip.h>

#define THIS_PERFORM 00015
#define PF_START "00015"
#define PF_NAME "Tự động xạ kích"

// 函数：获取描述
string get_desc(object me)
{
	if (me->get_fam_name() == "Đường Môn")
		return "[ Tự động xạ kích ]\n Dùng ám khí công kích 1 tên địch , mục tiêu từ xa.\n ";
	else
		return "[ " PF_NAME " ]\n Dùng kiếm pháp công kích 1 tên địch , mục tiêu từ xa.\n ";
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
	string family, name;
	object item;
	family = me->get_fam_name();
	/*	
	if (family=="Cấm Vệ Quân" || family=="Đào Hoa Nguyên" || family=="" || family==0 )
	{
		printf( ECHO "您所在的门派没有\"" PF_NAME "\"。" );
		return 1;
	}
*/
	if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
	{
		send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
		return 1;
	}
	if (me->get_attack_move() == 1 && me->get_enemy())
	{
		me->set_enemy(0);
		printf(ECHO "Bạn ngừng giữa chừng \" " PF_NAME " \".");
		return 1;
	}
	item = me->get_equip(WEAPON_TYPE);
	/*	
	if ( family=="Thục Sơn" && (!item||item->get_weapon_type()!=SWORD) )
	{
		printf( ECHO "您需要装备剑才能使用\"" PF_NAME "\"。" );
		return 1;		
	}			
*/
	if (!who->can_be_fighted(me) || !me->can_fight(who))
		return 1; // 执行成功
	me->set_enemy(0);
	me->start_fight(who);
	if (who->is_npc())
		who->start_fight(me); // 玩家需主动还击
	me->set_attack_move(1);
	//printf( ECHO "Sử dụng \" " PF_NAME " \" ." );
	return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_CHAR_7; }

// 函数：能否使用指令
void can_perform(object me)
{
	send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME);
}
