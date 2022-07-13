
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;
string *TalkTable = ({
	"Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
	"Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
	"Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
	"Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});
void do_task_start();
void do_task_cancel();
void do_welcome(string arg);

//void do_task_finish();
int get_char_picid() { return 7102; }

// 函数：构造处理
void create()
{
	set_name("Tào Thanh");
	set_city_name("Yên Quốc");

	set_2("talk", (["welcome":(
								  : do_welcome:),
	]));
	//	set("level",47);
	//	set("legend",({32*12+10}));
	set("mpLegend", ([45:({32 * 12 + 10}), 50:({32 * 15 + 15})]));
	set("mpLegend2", ([45:({32 * 12 + 12}), 50:({32 * 15 + 17})]));
	setup();
}

// 函数：对话处理
void do_look(object who)
{
	object me = this_object();
	string tmp = "";

	if (who->get("escort.finish") == 1)
	{
		TASK_ESCORT_D->do_look_2(who, me);
		return;
	}
	if (who->get_quest("escort.flag")																				  // 运镖任务
		&& who->get_quest("escort.leader") == 1																		  // 队长完成
		&& who->get_quest("escort.name") == get_name() && who->get_quest("escort.city") + " Quốc" == get_city_name()) // 找对人了
	{
		TASK_ESCORT_D->do_look_2(who, me);
		return;
	}

	tmp += CHAIN_D->get_chain_menu(who, me);
	if ((who->get_level() >= 45 && !who->get_legend(TASK_12, 10)) || (who->get_legend(TASK_12, 10) && !who->get_legend(TASK_12, 12)))
		tmp += sprintf(ESC HIY "河道惊魂\ntalk %x# welcome.1\n", getoid(me));
	if ((who->get_level() >= 50 && !who->get_legend(TASK_15, 15)) || (who->get_legend(TASK_15, 15) && !who->get_legend(TASK_15, 17)))
		tmp += sprintf(ESC HIY "饰品店\ntalk %x# welcome.4\n", getoid(me));

	send_user(who, "%c%s", ':', sprintf("%s：\n    %s\n", get_name(), TalkTable[random(sizeof(TalkTable))]) + tmp + ESC "离开");
}
void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object me, string arg)
{
	int flag, i, size, p, amount;
	object who, item, *inv;
	who = this_player();
	flag = to_int(arg);
	who->set_time("talk", 0);
	switch (flag)
	{
	case 1:
		if (who->get_level() >= 45 && !who->get_legend(TASK_12, 10))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近，郑Quốc渠被蒙上了一层恐怖的阴影，原因就在于——在这段时间，经过郑Quốc渠的人都会离奇失踪！\n    据我的推测，应该是鬼之魅在那里作祟，你前去将鬼之魅杀掉吧！\n" ESC "接受任务\ntalk %x# welcome.2\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_12, 10) && !who->get_legend(TASK_12, 11))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我得告诉我的亲戚朋友，叫他们不要从那里走。\n" ESC "离开", me->get_name()));
		else if (who->get_legend(TASK_12, 11) && !who->get_legend(TASK_12, 12))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    %s真是英勇啊！\n" ESC "完成任务\ntalk %x# welcome.3\n" ESC "离开", me->get_name(), NPC_RANK_D->get_respect_2(who), getoid(me)));
		break;
	case 2:
		if (who->get_level() >= 45 && !who->get_legend(TASK_12, 10))
		{
			if (TASK_LEGEND_D->can_task_add(who) != 1)
				return;
			who->set_legend(TASK_12, 10);
			send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_YANGUO, "Yên Quốc");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_YANGUO, 4, "河道惊魂");
			send_user(who, "%c%s", '!', "得到任务 " HIY "河道惊魂");
		}
		break;
	case 3:
		if (who->get_legend(TASK_12, 11) && !who->get_legend(TASK_12, 12))
		{
			if (TASK_LEGEND_D->can_carry_amount(who, 1) != 1)
				return;
			TASK_LEGEND_D->give_item(who, "item/product/64063", 1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_12, 12);
			who->add_exp(4900);
			who->add_potential(160);
			who->add_cash(4100);
			send_user(who, "%c%s", ';', "河道惊魂 经验 4900 潜能 160 金钱 4100 宣明冠图纸 1");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_YANGUO, 4, "");
		}
		break;
	case 4:
		if (who->get_level() >= 50 && !who->get_legend(TASK_15, 15))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    老太婆我虽然老了，但是自认为审美观还是挺好的，所以我开一家经营发夹的店，你能去燕长城给我收集10个发夹来吗？\n" ESC "接受任务\ntalk %x# welcome.5\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_15, 15) && !who->get_legend(TASK_15, 16))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没有发夹，我要怎么做饰物的生意呢？\n" ESC "离开", me->get_name()));
		else if (who->get_legend(TASK_15, 16) && !who->get_legend(TASK_15, 17))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    除了发夹，可能还需要一些玉佩之类的，我就不麻烦你了。\n" ESC "完成任务\ntalk %x# welcome.6\n" ESC "离开", me->get_name(), getoid(me)));
		break;
	case 5:
		if (who->get_level() >= 50 && !who->get_legend(TASK_15, 15))
		{
			if (TASK_LEGEND_D->can_task_add(who) != 1)
				return;
			who->set_legend(TASK_15, 15);
			who->delete_save_2("cqfajia");
			send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_YANGUO, "Yên Quốc");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_YANGUO, 33, "饰品店");
			send_user(who, "%c%s", '!', "得到任务 " HIY "饰品店");
		}
		break;
	case 6:
		if (who->get_legend(TASK_15, 16) && !who->get_legend(TASK_15, 17))
		{
			if (TASK_LEGEND_D->check_task_item(who, "发夹", 10) != 1)
				return;
			TASK_LEGEND_D->give_item(who, "item/final/15/1513", 1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_15, 17);
			who->delete_save_2("cqfajia");
			who->add_exp(6500);
			who->add_potential(225);
			who->add_cash(5500);
			send_user(who, "%c%s", ';', "饰品店 经验 6500 潜能 225 金钱 5500 高级法力 1");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_YANGUO, 33, "");
		}
		break;
	}
}