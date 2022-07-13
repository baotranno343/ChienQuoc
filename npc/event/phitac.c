#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <public.h>
#include <time.h>

inherit BADMAN;
//#define ACTIVE_FEIZEI	"/sys/party/feizei"
object robber;
int picid;
// 函数：获取人物造型
int get_char_picid() { return picid; }
void do_bonus();
// 函数：构造处理
void create()
{
	set_name("Trộm Bảo Phi Tặc");
	set_2("talk", (["bonus":(
								: do_bonus:),
	]));
	picid = ({0200, 0201, 0202, 0251, 0252})[random(5)];
	set_level(20);
	set("birthday", time());
	setup();
	set_char_type(FIGHTER_TYPE_2);
}
/*void reset() {
        if( gone_time( get("birthday") ) >= ACTIVE_FEIZEI->get_alive_time() &&  !objectp(get_enemy())) {
                remove_from_scene();
                destruct( this_object() );
        }
}*/
int can_fight(object who)
{
	if (!objectp(this_object()->get_enemy()))
		return 0;
	if (who->is_user() && this_object()->get_level() + 10 < who->get_level())
	{
		return 0;
	}
	if (who->is_user() && who->get_level() + 100 <= this_object()->get_level())
	{
		return 0;
	}
	return 1;
}
int can_be_fighted(object who)
{
	object owner;
	string leader, id;
	if (who->is_npc() && objectp(owner = who->get_owner()))
		who = owner;
	if (who->is_npc())
	{
		return 0;
	}
	if (who->is_user() && who->get_save_2("chuyensinh.score") && this_object()->get_level() < 110)
	{
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Nếu đã chuyển sinh rồi hãy tìm những phỉ từ 110 trở lên. !");
		return 0;
	}
	if (who->is_user() && this_object()->get_level() + 10 < who->get_level())
	{
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Đẳng cấp cao vậy rồi mà vẫn tới bắt nạt ta. Hãy tới nơi khác đi !");
		return 0;
	}
	if (who->is_user() && who->get_level() < 40 && this_object()->get_level() > 50)
	{
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Đẳng cấp của ngươi dưới 40 chỉ có thể đánh phỉ tặc lv 50 trở xuống.");
		return 0;
	}
	if (who->is_user() && who->get_level() + 100 <= this_object()->get_level())
	{
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Ngươi không nhìn thấy ta! Ngươi không nhìn thấy ta! \nHa ha ha ! Ha ha ha !");
		return 0;
	}
	return 1;
}

// 函数：死亡奖励
void win_bonus(object who) { "sys/party/phitac"->win_bonus_callout(this_object(), who); }
