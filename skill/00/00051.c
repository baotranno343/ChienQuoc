
#include <ansi.h>
#include <action.h>
#include <skill.h>

#define THIS_PERFORM 00051
#define PF_NAME "Bắt Bảo Thú"

// 函数：获取描述
string get_desc(object me)
{
	return "[ " PF_NAME "  ]\n Khi bắt được quái vật huấn luyện thành vật nuôi, lúc dùng đến phải nhớ mang thêm dây thừng loại tốt(mua ở tiệm tạp hóa).\n ";
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
	int rate, mp;
	object item;
	mapping mpInfo;

	if (gone_time(me->get("capture_pet")) < 1)
	{
		send_user(me, "%c%s", '!', "Thao tác quá nhanh. Vui lòng chậm lại!");
		return 1;
	}
	if (me->get_level() + 5 < who->get_level())
	{
		send_user(me, "%c%s", '!', sprintf("Cấp độ của bạn không đủ để khống chế %s .", who->get_name()));
		return 1;
	}
	if (!who->is_badman() || who->can_not_catch())
	{
		send_user(me, "%c%s", '!', "Không bắt được đối phương.");
		return 1;
	}
	mpInfo = "quest/pet"->get_beast_info(who->get_name());
	if (!mpInfo)
	{
		send_user(me, "%c%s", '!', "Không bắt được đối phương.");
		return 1;
	}
	/*    if (me->get_level()<mpInfo["level"])
        {
                send_user(me, "%c%s", '!', sprintf("Cấp độ của bạn không đủ để khống chế %s .", who->get_name()));
                return 1;        	
        }*/
	if (distance_between(me, who) > 7)
	{
		printf(ECHO "Mục tiêu của bạn quá xa.");
		return 1;
	}
	if (who->is_loansonke()) //月兔类，采用特殊捕捉方式
	{
		if (!objectp(item = present("Dây Bắt Gà", me, 1, MAX_CARRY * 4)))
		{
			printf(ECHO "Phải có Dây Bắt Gà mới được sử dụng “" PF_NAME "”.");
			return 1;
		}

		item->add_amount(-1);
		me->set("capture_pet", time());
		"quest/pet"->bat_loansonke(me, who);
		return 1;
	}
	if (!objectp(item = present("Dây Càn Khôn", me, 1, MAX_CARRY * 4)))
	{
		printf(ECHO "Phải có Dây Càn Khôn mới được sử dụng “" PF_NAME "”.");
		return 1;
	}
	item->add_amount(-1);
	mp = 5 + who->get_level();
	rate = 85 + (100 - who->get_hp() * 100 / who->get_max_hp()) / 2;
	if (!who->get_max_damage())
		who->init_enemy_damage(me, 0);
	if (who->is_yutu()) //月兔类，采用特殊捕捉方式
	{
		"quest/pet"->get_yutu(me, who);
		return 1;
	}
	if (who->is_acquyvuong()) //月兔类，采用特殊捕捉方式
	{
		"quest/pet"->get_acquyvuong(me, who);
		return 1;
	}
	if (random(100) > rate)
	{
		send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 411, 1, OVER_BODY, PF_ONCE);
		send_user(me, "%c%s", '!', "Bắt bảo thú thất bại");
		return 1;
	}
	if (me->get_beast_amount() >= me->get_beast_max_amount())
	{
		send_user(me, "%c%s", '!', "Bạn không mang thêm được nhiều Bảo Thú hơn nữa");
		return 1;
	}
	if (USER_BEAST_D->capture_beast(me, who) != 1)
	{
		send_user(me, "%c%s", '!', "Không bắt được Bảo Thú");
		return 1;
	}
	else
		send_user(me, "%c%s", '!', "Bạn bắt được " + who->get_name());
	me->set("capture_pet", time());
	send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 412, 1, OVER_BODY, PF_ONCE);
	who->remove_from_scene(FALL_ACT);
	who->before_destruct();
	destruct(who);
	return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_CHAR_7; }

// 函数：能否使用指令
void can_perform(object me)
{
	//	if ( USER_BEAST_D->can_perform(me) )
	send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME); //显示捕捉指令
																						  //        else
																						  //        	send_user( me, "%c%w%w", 0x50, 0xffff,THIS_PERFORM);	//取消显示捕捉指令
}
