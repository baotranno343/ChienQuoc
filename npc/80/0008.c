#include <npc.h>
#include <ansi.h>
#include <time.h>

inherit OFFICER;
// 函数:获取人物造型
int get_char_picid() { return 5502; }
void do_welcome(string arg);
// 函数:构造处理
void create()
{
	set_name("Quan Viên Vô Song Thành");
	set_2("talk", (["welcome":(
								  : do_welcome:),
	]));
	setup();
}

void do_look(object who) { __FILE__->do_look_call(this_object(), who); }

void do_look_call(object me, object who)
{
	int id = getoid(me), iTime;
	string tenbang;
	mixed *mixTime;
	iTime = time();
	mixTime = localtime(iTime);
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Xin hỏi ngươi tìm bản quan có chuyện gì ? \n" ESC "Xin chiếm lĩnh Vô Song Thành\ntalk %x# welcome.64\n" ESC "Rời khỏi", me->get_name(), id, id, id));
}

void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object me, string arg)
{
	int flag, p, i, size, id, iTime, amount, duty;
	object who, item, *nTeam;
	string tmp, tenbang;
	who = this_player();
	if (arg && sscanf(arg, "%d.%s", flag, tmp) != 2)
		flag = to_int(arg);
	id = getoid(me);
	//        flag = to_int(arg);
	who->set_time("talk", 0);
	tenbang = "/sys/party/vstfix"->get_occupy_org();
	switch (flag)
	{
	case 64:
		"/sys/party/vstfix"->occupy_city(me, who);
		break;
	// case 888:
	// 	return;
	// 	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Trước mắt thuế là %d lượng.\n", me->get_name(), WUSHUANG->get_save("wg_duty")));
	// 	break;
	// case 889:
	// 	return;
	// 	if (who->get_org_name() == tenbang && who->get_org_position() > 7)
	// 		send_user(who, "%c%c%d%s", '?', 16, 8, sprintf("Xin hãy nhập số thuế muốn nhận : ( trước mắt có thể nhận %d lượng )\n", WUSHUANG->get_save("wg_duty")) + sprintf(ESC "talk %x# welcome.890", id) + ".%s\n");
	// 	else
	// 		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Bang Chủ hoặc Phó Bang Chủ của bang phái đã chiếm Vô Song Thành mới có tư cách nhận thuế !\n" ESC "Rời khỏi", me->get_name()));
	// 	break;
	// case 890:
	// 	return;
	// 	duty = to_int(tmp);
	// 	if (duty > WUSHUANG->get_save("wg_duty"))
	// 	{
	// 		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Bản quan không có thu được số lượng thuế lớn như vậy !\n" ESC "Rời khỏi", me->get_name()));
	// 		return;
	// 	}
	// 	if (who->get_org_name() == tenbang && who->get_org_position() > 7)
	// 	{
	// 		if (duty > WUSHUANG->get_save("wg_duty"))
	// 			duty = WUSHUANG->get_save("wg_duty");
	// 		who->add_cash(duty);
	// 		log_file("wu_duty.dat", sprintf("%s %s(%d) lĩnh thuế %d\n", short_time(), who->get_id(), who->get_number(), duty));
	// 		WUSHUANG->add_save("wg_duty", -duty);
	// 		WUSHUANG->save();
	// 		send_user(who, "%c%s", ';', sprintf("Bạn đã nhận được" HIR " %d " NOR "lượng tiền thuế !", duty));
	// 	}
	// 	break;
	default:
		break;
	}
	return;
}