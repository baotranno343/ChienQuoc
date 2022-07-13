#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <public.h>
#include <time.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0450; }
void do_bonus();
int *ta = ({"Hoa Hồng", "Hoa Đào", "Hoa Sen", "Hoa Huệ", "Hoa Cúc"});
// 函数：构造处理
void create()
{
	set_name("Mẹ");
	set_2("talk", (["bonus":(
								: do_bonus:),
	]));

	setup();
}
void do_look(object who)
{
	send_user(who, "%c%c%w%s", ':', 3, 0450, "Mẹ:\n Hôm nay ra chợ, tự nhiên mẹ thấy thích hoa ghê á! #54#26\n" + sprintf(ESC "Con sẽ mua cho mẹ\ntalk %x# bonus\n", getoid(this_object())) + ESC "Kệ mẹ chứ!");
}
void do_bonus()
{
	int a;
	object npc;
	object who = this_player(), me = this_object();
	if (who->get_level() < 20)
	{
		send_user(who, "%c%c%w%s", ':', 3, 0450, "Mẹ:\n Con còn bé, hãy cứ học giỏi, điểm của con là quà của mẹ. Khi nào lên 20 tuổi rồi hẵng mua cho mẹ nhé! #64 \n");
		return 0;
	}
	a = random(5);
	npc = new ("npc/event/83/mother2");
	npc->set("mother", who);
	npc->set("mother2", who->get_number());
	npc->set("thucan", ta[a]);
	npc->set("birthday", time());
	npc->set_owner(who);
	npc->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
	me->remove_from_scene();
	destruct(me);
}
