
// 自动生成：/make/npc/make8002

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>

#define GENERAL_D "/inh/city/general"

inherit OFFICER;

void do_patrol(string arg);
void do_soldier(string arg);
void do_armor(string arg);
void do_welcome(string arg);
//void do_defence(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5201; }

// 函数：构造处理
void create()
{
	set_name("Tần Quốc Đại Tướng Quân");
	set_real_name("Vương Tiễn");
	set_city_name("Tần Quốc");

	set_2("talk", (["patrol":(
								 : do_patrol:),
					  "soldier":(
									: do_soldier:),
						"armor":(
									: do_armor:),
					  "welcome":(
									: do_welcome:),
					  //   "defence":(
					  // 				: do_defence:),
	]));
	//        set("level",61);
	//        set("legend",({32*18+16}));
	set("mpLegend", ([49:({32 * 50 + 1}), 60:({32 * 18 + 16}), 65:({32 * 21 + 26}), 110:({32 * 45 + 4})]));
	set("mpLegend2", ([0:({
							 32 * 47 + 20,
							 32 * 47 + 28,
						 }),
						  49:({32 * 50 + 3}), 60:({
													 32 * 18 + 18,
													 32 * 18 + 21,
													 32 * 18 + 24,
													 32 * 18 + 27,
												 }),
						 110:({
								 32 * 45 + 6,
							 }),
	]));
	setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

//void do_defence(string arg) { "/sys/party/defence"->do_defence(this_player(), this_object(), arg); }

void do_look(object who)
{
	string tmp = "";
	object me = this_object();

	if ((who->get_level() >= 60 && !who->get_legend(TASK_18, 16)) || (who->get_legend(TASK_18, 16) && !who->get_legend(TASK_18, 18)))
	{
		tmp += sprintf(ESC HIY "兵器的缺乏\ntalk %x# welcome.1\n", getoid(me));
	}
	if ((who->get_legend(TASK_18, 18) && !who->get_legend(TASK_18, 19)) || (who->get_legend(TASK_18, 19) && !who->get_legend(TASK_18, 20)) || (who->get_legend(TASK_18, 20) && !who->get_legend(TASK_18, 21)))
	{
		tmp += sprintf(ESC HIY "请教用兵之法\ntalk %x# welcome.1\n", getoid(me));
	}
	if ((who->get_legend(TASK_18, 21) && !who->get_legend(TASK_18, 22)) || (who->get_legend(TASK_18, 22) && !who->get_legend(TASK_18, 24)))
	{
		tmp += sprintf(ESC HIY "挖战壕的锄头\ntalk %x# welcome.1\n", getoid(me));
	}
	if ((who->get_legend(TASK_18, 24) && !who->get_legend(TASK_18, 25)) || (who->get_legend(TASK_18, 25) && !who->get_legend(TASK_18, 27)))
	{
		tmp += sprintf(ESC HIY "探路\ntalk %x# welcome.1\n", getoid(me));
	}
	if (who->get_level() >= 65 && !who->get_legend(TASK_21, 26))
	{
		tmp += sprintf(ESC HIY "秦将辟谣\ntalk %x# welcome.10\n", getoid(me));
	}
	if ((who->get_level() >= 110 && !who->get_legend(TASK_45, 4)) || (who->get_legend(TASK_45, 4) && !who->get_legend(TASK_45, 6)))
	{
		tmp += sprintf(ESC HIY "天寒地冻\ntalk %x# welcome.12\n", getoid(me));
	}
	if (who->get_legend(TASK_47, 19) && !who->get_legend(TASK_47, 20))
		tmp += sprintf(ESC HIY "拜访秦将\ntalk %x# welcome.15\n", getoid(me));
	if (who->get_legend(TASK_47, 20) && !who->get_legend(TASK_47, 21))
		tmp += sprintf(ESC HIY "神剑之闻\ntalk %x# welcome.15\n", getoid(me));
	if (who->get_legend(TASK_47, 27) && !who->get_legend(TASK_47, 28))
		tmp += sprintf(ESC HIY "寻剑之路\ntalk %x# welcome.15\n", getoid(me));
	if (who->get_legend(TASK_47, 28) && !who->get_legend(TASK_47, 29))
		tmp += sprintf(ESC HIY "报效大王\ntalk %x# welcome.15\n", getoid(me));
	if ((who->get_level() >= 49 && !who->get_legend(TASK_2_00, 1)) || (who->get_legend(TASK_2_00, 1) && !who->get_legend(TASK_2_00, 2)) || (who->get_legend(TASK_2_00, 2) && !who->get_legend(TASK_2_00, 3)))
		tmp += sprintf(ESC HIY "剿灭叛军\ntalk %x# welcome.20\n", getoid(me));
	// if ("/sys/sys/count"->get_war_flag1()||"/sys/party/defence"->get_count())
	// 	tmp += sprintf(ESC HIY "Chiến Trường Thủ Thành\ntalk %x# defence.1\n",getoid(me));

	if (sizeof(tmp))
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf("%s：\n    " + "/quest/word"->get_country_word(me) + "\n" ESC "对话\ntalk %x# welcome.99\n", get_name(), getoid(me)) + tmp + ESC "离开");
	else
		GENERAL_D->do_look(who, me);
}
void do_patrol(string arg) { GENERAL_D->do_patrol(this_player(), this_object(), arg); }
void do_soldier(string arg) { GENERAL_D->do_soldier(this_player(), this_object(), arg); }
void do_armor(string arg) { GENERAL_D->do_armor(this_player(), this_object(), arg); }

void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object me, string arg)
{
	int flag, i, size, p, amount;
	object who, item, *inv;
	string *nTmp, tmp;
	who = this_player();
	flag = to_int(arg);
	who->set_time("talk", 0);
	switch (flag)
	{
	case 1:
		if (who->get_level() >= 60 && !who->get_legend(TASK_18, 16))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近犬戎人蠢蠢欲动，最近必定有场大仗要打，最近新来了不少士兵，工部却总是推脱不发兵器，气死本将军了，你去秦长城给我找20把剑来！\n" ESC "接受任务\ntalk %x# welcome.2\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_18, 16) && !who->get_legend(TASK_18, 17))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    剑呢？可别耽误了本将军的行军大计！\n" ESC "离开", me->get_name()));
		else if (who->get_legend(TASK_18, 17) && !who->get_legend(TASK_18, 18))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    既然你找来了20把剑，你是否可以考虑再跑一趟呢？\n" ESC "完成任务\ntalk %x# welcome.3\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_18, 18) && !who->get_legend(TASK_18, 19))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    别看本城的夏侯党是一介土匪，可他精通作战之道，本将军原想将他纳为己用，可他说对官场不感兴趣，所以只得请你再跑一趟，问问他对于这次战役有什么好的建议。\n" ESC "接受任务\ntalk %x# welcome.4\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_18, 19) && !who->get_legend(TASK_18, 20))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    夏侯党没有给你意见吗？\n" ESC "离开", me->get_name()));
		else if (who->get_legend(TASK_18, 20) && !who->get_legend(TASK_18, 21))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    果然是条妙计！这夏侯党真是个不可多得之才呀！不过既然要挖壕沟，那还得用锄头。\n" ESC "完成任务\ntalk %x# welcome.5\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_18, 21) && !who->get_legend(TASK_18, 22))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    夏侯党果然是个人才，我准备开挖5条壕沟，你先去给我在秦长城收集20把锄头吧。\n" ESC "接受任务\ntalk %x# welcome.6\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_18, 22) && !who->get_legend(TASK_18, 23))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我委托的其他人的锄头都收集好了，你怎么办事如此不力？\n" ESC "离开", me->get_name()));
		else if (who->get_legend(TASK_18, 23) && !who->get_legend(TASK_18, 24))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    锄头收集齐了，我就可以选在敌军的必经之路上开始挖壕沟了，你是否还愿意帮我去探下路呢？\n" ESC "完成任务\ntalk %x# welcome.7\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_18, 24) && !who->get_legend(TASK_18, 25))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我已经开始挖壕沟了，可是我还希望知道自己士兵战斗力如何，你帮我去秦长城上试探一下枪兵的战斗力吧，记住，打晕了就可，可别给我打死了。\n" ESC "接受任务\ntalk %x# welcome.8\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_18, 25) && !who->get_legend(TASK_18, 26))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果你到现在还不能打败他们，是否我选择的你能力太弱了，根本不能负担测试重任？\n" ESC "离开", me->get_name()));
		else if (who->get_legend(TASK_18, 26) && !who->get_legend(TASK_18, 27))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，你都费了如此多力才能搞定他们，看来这仗我们赢定了。\n" ESC "完成任务\ntalk %x# welcome.9\n" ESC "离开", me->get_name(), getoid(me)));

		break;
	case 2:
		if (who->get_level() >= 60 && !who->get_legend(TASK_18, 16))
		{
			if (TASK_LEGEND_D->can_task_add(who) != 1)
				return;
			who->set_legend(TASK_18, 16);
			who->delete_save_2("qgdjjjian");
			send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_QINGUO, "Tần Quốc");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 11, "大展神威（1）");
			send_user(who, "%c%s", '!', "得到任务 " HIY "大展神威（1）");
		}
		break;
	case 3:
		if (who->get_legend(TASK_18, 17) && !who->get_legend(TASK_18, 18))
		{
			if (TASK_LEGEND_D->check_task_item(who, "剑", 20) != 1)
				return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_18, 18);
			who->delete_save_2("qgdjjjian");
			who->add_exp(7500);
			who->add_potential(280);
			who->add_cash(6500);
			send_user(who, "%c%s", ';', "大展神威（1） 经验 7500 潜能 280 金钱 6500");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 11, "");
			me->do_welcome(1);
		}
		break;
	case 4:
		if (who->get_legend(TASK_18, 18) && !who->get_legend(TASK_18, 19))
		{
			if (TASK_LEGEND_D->can_task_add(who) != 1)
				return;
			who->set_legend(TASK_18, 19);
			send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_QINGUO, "Tần Quốc");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 12, "大展神威（2）");
			send_user(who, "%c%s", '!', "得到任务 " HIY "大展神威（2）");
		}
		break;
	case 5:
		if (who->get_legend(TASK_18, 20) && !who->get_legend(TASK_18, 21))
		{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_18, 21);
			who->add_exp(6800);
			who->add_potential(263);
			who->add_cash(6500);
			send_user(who, "%c%s", ';', "大展神威（3） 经验 6800 潜能 263 金钱 6500");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 13, "");
			me->do_welcome(1);
		}
		break;
	case 6:
		if (who->get_legend(TASK_18, 21) && !who->get_legend(TASK_18, 22))
		{
			if (TASK_LEGEND_D->can_task_add(who) != 1)
				return;
			who->set_legend(TASK_18, 22);
			who->delete_save_2("qgdjjchutou");
			send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_QINGUO, "Tần Quốc");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 14, "大展神威（4）");
			send_user(who, "%c%s", '!', "得到任务 " HIY "大展神威（4）");
		}
		break;
	case 7:
		if (who->get_legend(TASK_18, 23) && !who->get_legend(TASK_18, 24))
		{
			if (TASK_LEGEND_D->check_task_item(who, "锄头", 20) != 1)
				return;
			TASK_LEGEND_D->give_item(who, "item/product/65061", 1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_18, 24);
			who->delete_save_2("qgdjjchutou");
			who->add_exp(7500);
			who->add_potential(290);
			who->add_cash(6800);
			send_user(who, "%c%s", ';', "大展神威（4） 经验 7500 潜能 290 金钱 6800 紫焰项链图纸 1");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 14, "");
			me->do_welcome(1);
		}
		break;
	case 8:
		if (who->get_legend(TASK_18, 24) && !who->get_legend(TASK_18, 25))
		{
			if (TASK_LEGEND_D->can_task_add(who) != 1)
				return;
			who->set_legend(TASK_18, 25);
			who->delete_save_2("qgdjjqiangbin");
			send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_QINGUO, "Tần Quốc");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 15, "大展神威（5）");
			send_user(who, "%c%s", '!', "得到任务 " HIY "大展神威（5）");
		}
		break;
	case 9:
		if (who->get_legend(TASK_18, 26) && !who->get_legend(TASK_18, 27))
		{
			if (TASK_LEGEND_D->can_carry_amount(who, 1) != 1)
				return;
			nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), 0, 60, BOOTS_TYPE);
			tmp = nTmp[random(sizeof(nTmp))];
			if (!stringp(tmp))
				return;
			TASK_LEGEND_D->give_item(who, tmp, 1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_18, 27);
			who->delete_save_2("qgdjjqiangbin");
			who->add_exp(9000);
			who->add_potential(330);
			who->add_cash(8000);
			send_user(who, "%c%s", ';', sprintf("大展神威（5） 经验 9000 潜能 330 金钱 8000 %s 1", tmp->get_name()));
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 15, "");
		}
		break;
	case 10:
		if (who->get_level() >= 65 && !who->get_legend(TASK_21, 26))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本大将军戍守边关多年，对大王忠心耿耿，方才卫得长城不失，犬戎不得践踏我关中沃土，最近有人在大王面前诽谤于我，说我拥兵自重，不服号令，居然还说我私通犬戎，令我冤屈愤怒，大王居然还为谣言所动，对我多有责罚不满之心，你代我将这封军函送给我国内政官，让他为我在大王面前分辩一下，别着了小人圈套。\n" ESC "接受任务\ntalk %x# welcome.11\n" ESC "离开", me->get_name(), getoid(me)));
		break;
	case 11:
		if (who->get_level() >= 65 && !who->get_legend(TASK_21, 26))
		{
			if (TASK_LEGEND_D->can_task_add(who) != 1)
				return;
			item = new ("/item/98/0100");
			p = item->move(who, -1);
			if (!p)
			{
				destruct(item);
				send_user(who, "%c%s", '!', "你携带的物品太多了");
				return;
			}
			item->add_to_user(p);
			who->set_legend(TASK_21, 26);
			send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_QINGUO, "Tần Quốc");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 38, "秦将辟谣");
			send_user(who, "%c%s", '!', "得到任务 " HIY "秦将辟谣");
		}
		break;
	case 12:
		if (who->get_level() >= 110 && !who->get_legend(TASK_45, 4))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    徐福道长夜观星象，近日天将大寒，然则近段时间商路多为盗贼所阻，军需管采购不到足够的御寒衣物，听闻诛仙阵中有匪类秘密储存的铠甲，进入诛仙阵相信对于壮士身手不是难事，如此报效国家的良机壮士可愿意效力？壮士先去探探路，帮我军找5套来好了。\n" ESC "接受任务\ntalk %x# welcome.13\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_45, 4) && !who->get_legend(TASK_45, 5))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    莫非壮士连找几件铠甲这点小事也无法完成么？\n" ESC "离开", me->get_name()));
		else if (who->get_legend(TASK_45, 5) && !who->get_legend(TASK_45, 6))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    壮士身手果然矫健，如来投效我军，本大将军必将重用！\n" ESC "完成任务\ntalk %x# welcome.14\n" ESC "离开", me->get_name(), getoid(me)));
		break;
	case 13:
		if (who->get_level() >= 110 && !who->get_legend(TASK_45, 4))
		{
			if (TASK_LEGEND_D->can_task_add(who) != 1)
				return;
			who->set_legend(TASK_45, 4);
			who->delete_save("qgdjjkuijia");
			send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_QINGUO, "Tần Quốc");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 63, "天寒地冻");
			send_user(who, "%c%s", '!', "得到任务 " HIY "天寒地冻");
		}
		break;
	case 14:
		if (who->get_legend(TASK_45, 5) && !who->get_legend(TASK_45, 6))
		{
			if (TASK_LEGEND_D->check_task_item(who, "秦国盔甲", 5) != 1)
				return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_45, 6);
			who->delete_save("qgdjjkuijia");
			who->add_exp(91000);
			who->add_potential(980);
			who->add_cash(94000);
			send_user(who, "%c%s", ';', "天寒地冻 经验 91000 潜能 980 金钱 94000");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 63, "");
		}
		break;
	case 15:
		if (who->get_legend(TASK_47, 19) && !who->get_legend(TASK_47, 20))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎……本将军的确有一件急欲得到之物，但是其中困难却非想象啊！\n" ESC "完成任务\ntalk %x# welcome.16\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_47, 20) && !who->get_legend(TASK_47, 21))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我听说最近有一把神剑出世，自古神剑配将军，我非常希望上阵杀敌的时候能够佩戴它，但是据说现在数路人马都在虎视眈眈，而我责任所系，不敢擅离职守，我只派了几名得力手下找剑然而都不见踪影，现在我心焦不已，恐怕又与它失之交臂，不知道壮士可为我找寻神剑？城外平阳镇的夏侯党对此事比较清楚，你向他打听一下吧。\n" ESC "接受任务\ntalk %x# welcome.17\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_47, 27) && !who->get_legend(TASK_47, 28))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    （仰天长笑中）哈哈哈……神剑终于归本将军所有了！也不枉我浪费了那么多手下，壮士你可有意在我军中效力？\n" ESC "完成任务\ntalk %x# welcome.18\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_47, 28) && !who->get_legend(TASK_47, 29))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本将军得到天赐神剑，这是天佑我大秦，本将军必将百战不殆，助大王平宇内，扫六合！请你代我将这番话转告大王！\n" ESC "接受任务\ntalk %x# welcome.19\n" ESC "离开", me->get_name(), getoid(me)));

		break;
	case 16:
		if (who->get_legend(TASK_47, 19) && !who->get_legend(TASK_47, 20))
		{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_47, 20);
			who->add_exp(97000);
			who->add_potential(1200);
			who->add_cash(94000);
			send_user(who, "%c%s", ';', "索取神剑1 经验 97000 潜能 1200 金钱 94000");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 84, "");
			me->do_welcome(15);
		}
		break;
	case 17:
		if (who->get_legend(TASK_47, 20) && !who->get_legend(TASK_47, 21))
		{
			if (TASK_LEGEND_D->can_task_add(who) != 1)
				return;
			who->set_legend(TASK_47, 21);
			send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_QINGUO, "Tần Quốc");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 85, "索取神剑2");
			send_user(who, "%c%s", '!', "得到任务 " HIY "索取神剑2");
		}
		break;
	case 18:
		if (who->get_legend(TASK_47, 27) && !who->get_legend(TASK_47, 28))
		{
			if (TASK_LEGEND_D->check_task_item(who, "神剑", 1) != 1)
				return;
			TASK_LEGEND_D->give_item(who, "item/final/16/1620", 1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_47, 28);
			who->add_exp(93000);
			who->add_potential(1300);
			who->add_cash(92000);
			send_user(who, "%c%s", ';', "索取神剑4 经验 93000 潜能 1300 金钱 92000 药店连接器 1");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 87, "");
			me->do_welcome(15);
		}
		break;
	case 19:
		if (who->get_legend(TASK_47, 28) && !who->get_legend(TASK_47, 29))
		{
			if (TASK_LEGEND_D->can_task_add(who) != 1)
				return;
			who->set_legend(TASK_47, 29);
			send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_QINGUO, "Tần Quốc");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 88, "索取神剑5");
			send_user(who, "%c%s", '!', "得到任务 " HIY "索取神剑5");
		}
		break;
	case 20:
		if (who->get_level() >= 49 && !who->get_legend(TASK_2_00, 1))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王登极众望所归，然王弟成峤受华阳夫人怂恿，有心谋叛，实乃国之不幸。你，去剿灭那些叛贼！然后回来报我知道！\n" ESC "接受任务\ntalk %x# welcome.21\n" ESC "离开", me->get_name(), getoid(me)));
		else if (who->get_legend(TASK_2_00, 1) && !who->get_legend(TASK_2_00, 2))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你还没有前去剿灭叛贼么？\n" ESC "离开", me->get_name()));
		else if (who->get_legend(TASK_2_00, 2) && !who->get_legend(TASK_2_00, 3))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    王族兄弟情浅，终至反目，可叹啊……\n" ESC "完成任务\ntalk %x# welcome.22\n" ESC "离开", me->get_name(), getoid(me)));
		break;
	case 21:
		if (who->get_level() >= 49 && !who->get_legend(TASK_2_00, 1))
		{
			if (TASK_LEGEND_D->can_task_add(who) != 1)
				return;
			who->delete_save("fb_001_001");
			who->delete_save("fb_001_002");
			who->delete_save("fb_001_003");
			who->delete_save("fb_001_004");
			who->delete_save("fb_001_005");
			who->set_legend(TASK_2_00, 1);
			send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_QINGUO, "Tần Quốc");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 101, "剿灭叛军");
			send_user(who, "%c%s", '!', "得到任务 " HIY "剿灭叛军");
		}
		break;
	case 22:
		if (who->get_legend(TASK_2_00, 2) && !who->get_legend(TASK_2_00, 3))
		{
			TASK_LEGEND_D->task_finish(who);
			who->delete_save("fb_001_001");
			who->delete_save("fb_001_002");
			who->delete_save("fb_001_003");
			who->delete_save("fb_001_004");
			who->delete_save("fb_001_005");
			who->set_legend(TASK_2_00, 3);
			who->add_exp(6800);
			who->add_potential(400);
			who->add_cash(9600);
			send_user(who, "%c%s", ';', "剿灭叛军 经验 6800 潜能 400 金钱 9600");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_QINGUO, 101, "");
		}
		break;

	case 99:
		GENERAL_D->do_look(who, me);
		break;
	}
}