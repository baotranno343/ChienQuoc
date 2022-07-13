
#include <ansi.h>
#include <skill.h>

#define THIS_PERFORM 00014
#define PF_START "00014"
#define PF_NAME "Tự động công kích"

// 函数：获取描述
string get_desc(object me)
{
	return "[ " PF_NAME " ]\n Tấn công gần người 1 tên địch mục tiêu.\n ";
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
	if (me->get_attack_move() == 0 && me->get_enemy())
	{
		me->set_enemy(0);
		printf(ECHO "Bạn ngừng giữa chừng \" " PF_NAME " \".");
		return 1;
	}
	if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
	{
		send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
		return 1;
	}
	if (!who->can_be_fighted(me) || !me->can_fight(who))
		return 1; // 执行成功
	me->set_enemy(0);
	me->start_fight(who);
	if (who->is_npc())
		who->start_fight(me); // 玩家需主动还击
	me->set_attack_move(0);
	printf(ECHO "Sử dụng \" " PF_NAME " \".");
	return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_CHAR_7; }

// 函数：能否使用指令
void can_perform(object me)
{
	send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME);
}
