#include <ansi.h>
#include <cmd.h>
#include <task.h>
static string *nTudi = ({"baishi.tudi", "baishi.tudi1", "baishi.tudi2", "baishi.tudi3"});

void baishi(object me, object who, object user);
object check_baishi(object me, object who);
object check_chushi(object me, object who);
void chushi(object me, object who, object user);
void dissolve1(object me, object who);
void dissolve2(object me, object who);
void query_shifu(object me, object who);
void dissolve1_list(object me, object who);
void dissolve2_list(object me, object who);
void dissolve1_tudi(object me, object who, int id);
void dissolve2_tudi(object me, object who, int id);
void dissolve1_shifu(object me, object who);
void dissolve2_shifu(object me, object who);
void query_tudi(object me, object who, int id);
void query_tudi_list(object me, object who);

// 函数:生成二进制码
void SAVE_BINARY() {}
//判断是否师傅
int is_shifu(object who)
{
	int i, size;
	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		if (mapp(who->get_save_2(nTudi[i])))
			return 1;
	}
	return 0;
}
//判断是否徒弟
int is_tudi(object who)
{
	return mapp(who->get_save_2("baishi.shifu"));
}
void do_look(object who, object me)
{
	int id;
	string tmp = "";
	id = getoid(me);
	if (is_shifu(who))
	{
		if (who->get_legend(TASK_2_00, 23) && !who->get_legend(TASK_2_00, 24) && who->get_save("baifang_ms_1") != 1)
			tmp = sprintf(ESC HIY "Thăm viếng\ntalk %x# welcome.21\n", id);
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  me->get_name() + ":\n    Vi sư phải biết dạy đồ đệ trở thành một người có tài, nếu một ngày bạn trở thành Sư phụ thì phải biết dạy dỗ hắn thành người có bản lĩnh !\n" + tmp + sprintf(ESC "Hiểu rõ Thăm viếng\ntalk %x# welcome.1\n", id) + sprintf(ESC "Ta đem đệ tử đến làm lễ bái sư\ntalk %x# welcome.2\n", id) + sprintf(ESC "Ta đem đệ tử đến làm lễ xuất xư\ntalk %x# welcome.3\n", id) + sprintf(ESC "Ta muốn tìm ghi chép việc dạy học của ta\ntalk %x# welcome.4\n", id) + sprintf(ESC "Ta đến giải trừ quan hệ thầy trò\ntalk %x# welcome.5\n", id) + sprintf(ESC "Ta muốn tìm ghi chép việc dạy học của ta\ntalk %x# welcome.6\n", id) + sprintf(ESC "Nhận phần thưởng sư đồ\ntalk %x# welcome.19\n", id) + ESC "Rời khỏi");
	}
	else if (is_tudi(who))
	{
		if (who->get_legend(TASK_2_00, 23) && !who->get_legend(TASK_2_00, 24) && who->get_save("baifang_ms_1") != 1)
			tmp = sprintf(ESC HIY "Thăm viếng\ntalk %x# welcome.21\n", id);
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  me->get_name() + ":\n    Vi sư phải biết dạy đồ đệ trở thành một người có tài, nếu một ngày bạn trở thành Sư phụ thì phải biết dạy dỗ hắn thành người có bản lĩnh !\n" + tmp + sprintf(ESC "Hiểu rõ Thăm viếng\ntalk %x# welcome.1\n", id) + sprintf(ESC "Ta đến giải trừ quan hệ thầy trò\ntalk %x# welcome.5\n", id) + sprintf(ESC "Ta muốn tìm ghi chép Sư phụ ta\ntalk %x# welcome.6\n", id) + sprintf(ESC "Nhận phần thưởng sư đồ\ntalk %x# welcome.19\n", id) + ESC "Rời khỏi");
	}
	else
	{
		if (who->get_legend(TASK_2_00, 23) && !who->get_legend(TASK_2_00, 24) && who->get_save("baifang_ms_1") != 1)
			tmp = sprintf(ESC HIY "Thăm viếng\ntalk %x# welcome.21\n", id);
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  me->get_name() + ":\n    Vi sư phải biết dạy đồ đệ trở thành một người có tài, nếu một ngày bạn trở thành Sư phụ thì phải biết dạy dỗ hắn thành người có bản lĩnh !\n" + tmp + sprintf(ESC "Hiểu rõ Thăm viếng\ntalk %x# welcome.1\n", id) + sprintf(ESC "Ta đem đệ tử đến làm lễ bái sư\ntalk %x# welcome.2\n", id) + sprintf(ESC "Ta đem đệ tử đến làm lễ xuất sư\ntalk %x# welcome.3\n", id) + sprintf(ESC "Ta muốn tìm ghi chép việc dạy học của ta\ntalk %x# welcome.4\n", id) + sprintf(ESC "Ta phải tìm kiếm sư phụ\ntalk %x# welcome.14\n", id) + sprintf(ESC "Nhận phần thưởng sư đồ\ntalk %x# welcome.19\n", id) + ESC "Rời khỏi");
	}
}

void do_welcome(object me, object who, string arg)
{
	int flag, i, size, id, exp, pot, max, exp1, pot1;
	string *name, tmp, *nTmp, username;
	object user;
	if (!arg)
		return;
	nTmp = explode(arg, ".");
	flag = to_int(nTmp[0]);
	who->set_time("talk", 0);
	id = getoid(me);
	switch (flag)
	{
	case 1:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\n Bái sư cần 2 người đang ở trong cùng 1 nhóm, sư phụ làm nhóm trưởng, 2 người nhất định ở trong phạm vi nhìn thấy của lão phu. Đẳng cấp sư phụ yêu cầu từ cấp 60; đẳng cấp đệ tử yêu cầu cấp 30. Sau khi bái sư, đồ đệ phải đạt đủ 50 cấp có thể xuất sư thành tài; lúc xuất sư cần phải sư phụ dẫn đồ đệ đến gặp lão phu cử hành nghi lễ xuất sư. Ngày đồ đệ xuất sư, lão phu sẽ tặng phần thưởng rất hậu cho công lao dạy dỗ khó nhọc của sư phụ và việc học hành chăm chỉ của đồ đệ!!\n" ESC "Rời khỏi", me->get_name()));
		break;
	case 2:
		if (!objectp(user = check_baishi(me, who)))
			return;
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  sprintf("%s\n    Hiện tại bạn có thể nhận %s làm đồ đệ, mong bạn hết lòng dạy dỗ đồ đệ thành tài !\n", me->get_name(), user->get_name()) + sprintf(ESC "Xác nhận\ntalk %x# welcome.7\n" ESC "Rời khỏi", getoid(me)));
		who->set("baishi.tudi", user);
		break;
	case 3:
		if (!objectp(user = check_chushi(me, who)))
			return;
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  sprintf("%s\n    Bởi vì bạn hết lòng dạy dỗ, đồ đệ của bạn bây giờ đã có thể xuất sư, xin chúc mừng !\n", me->get_name()) + sprintf(ESC "Xác nhận\ntalk %x# welcome.8\n" ESC "Rời khỏi", getoid(me)));

		break;
	case 4:
		name = who->get_apprentice();
		if ((size = sizeof(name)) == 0)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn không có đồ đệ !");
			return;
		}
		tmp = name[0];
		for (i = 1; i < size; i++)
		{
			tmp += ", " + name[i];
		}
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn có đồ đệ " + tmp + ".");
		break;
	case 5:
		if (is_tudi(who))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  me->get_name() + ":\n    Tình thầy trò ? bạn thật sự muốn cắt bỏ quan hệ thầy trò hả, nếu trong 7 ngày Sư phụ bạn vẫn không đến trấn an bạn thì ta đồng ý cắt bỏ quan hệ thầy trò của bạn, nhưng phải nạp cho ta 200.000 lượng\n" + sprintf(ESC "Hoà bình giải trừ quan hệ thầy trò\ntalk %x# welcome.9\n", getoid(me)) + sprintf(ESC "Mạnh mẽ giải trừ quan hệ thầy trò\ntalk %x# welcome.10\n", getoid(me)) + ESC "Rời khỏi");
		else if (is_shifu(who))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  me->get_name() + ":\n    Tình thầy trò ? bạn thật sự muốn cắt bỏ quan hệ thầy trò hả, nếu trong 7 ngày Đồ đệ bạn vẫn không đến trấn an bạn thì ta đồng ý cắt bỏ quan hệ thầy trò của bạn, nhưng phải nạp cho ta 500.000 lượng\n" + sprintf(ESC "Hoà bình giải trừ quan hệ thầy trò\ntalk %x# welcome.9\n", getoid(me)) + sprintf(ESC "Mạnh mẽ giải trừ quan hệ thầy trò\ntalk %x# welcome.10\n", getoid(me)) + ESC "Rời khỏi");

		break;
	case 6:
		if (is_tudi(who))
			query_shifu(me, who);
		else
			query_tudi_list(me, who);
		break;
	case 7:
		if (!objectp(user = check_baishi(me, who)))
			return;
		send_user(user, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  sprintf("%s:\n    Bạn bằng lòng làm đồ đệ của %s không ?\n", me->get_name(), who->get_name()) + sprintf(ESC "Xác nhận\ntalk %x# welcome.13\n" ESC "Rời khỏi", getoid(me)));
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Xin đợi đối phương xác nhận");
		user->set("baishi.shifu", who);
		break;
	case 8:
		if (!objectp(user = check_chushi(me, who)))
			return;
		chushi(me, who, user);
		break;
	case 9: //和平解除
		if (who->get_save_2("baishi.shifu"))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  me->get_name() + ":\n    Bạn bằng lòng cùng Sư phụ của bạn Hoà bình giải trừ quan hệ thầy trò～！\n" + sprintf(ESC "Xác nhận\ntalk %x# welcome.11\n", getoid(me)) + ESC "Rời khỏi");
		else
			dissolve1_list(me, who);
		break;
	case 10: //强行解除
		if (is_tudi(who))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  me->get_name() + ":\n    Bạn bằng lòng cùng Sư Phụ của bạn Mạnh mẽ giải trừ quan hệ thầy trò～！\n" + sprintf(ESC "Xác nhận\ntalk %x# welcome.12\n", getoid(me)) + ESC "Rời khỏi");
		else
			dissolve2_list(me, who);
		break;
	case 11:
		dissolve1_shifu(me, who);
		break;
	case 12:
		dissolve2_shifu(me, who);
		break;
	case 13:
		user = who;
		who = user->get("baishi.shifu");
		if (!objectp(who))
			return;
		if (user != who->get("baishi.tudi"))
			return;
		who->delete ("baishi.tudi");
		user->delete ("baishi.shifu");
		if (!objectp(user = check_baishi(me, who)))
			return;
		baishi(me, who, user);
		break;
	case 14:
		if (is_tudi(who))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn đã bái sư, không cần sư phụ đến dạy !\n");
		else if (who->get_level() > 30)
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\n Ngươi đã đủ sức suy nghĩ và chấm dứt khó khăn một mình, không cần tìm thầy về dạy!\n", me->get_name()));
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Lão phu gặp người không rành thế sự, có thể giúp bạn kiếm Sư phụ nhưng có kiếm được hay không là nhờ tạo hoá của bạn\n" + sprintf(ESC "Phát ra tin tức tìm Sư Phụ\ntalk %x# welcome.15\n" ESC "Rời khỏi", id));

		break;
	case 15: //发寻师信息
		if (gone_time(who->get("baishi.shout")) < 120)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Hãy đợi trong chốc lát rồi lại đến tìm ta ～！\n");
			return;
		}
		who->set("baishi.shout", time());
		username = sprintf("%c+%d,%s=%d%c-", '\t', 0xffffff, who->get_name(), who->get_number(), '\t');
		CHAT_D->sys_channel(0, sprintf(HIR " %s ( %d )tư chất thông minh, mới vào Chiến Quốc , muốn tìm một sư phụ dạy dỗ. Ai muốn nhận đồ đệ vui lòng liên hệ với bổn nhân!", username, who->get_number()));
		break;
	case 16:
		dissolve1_tudi(me, who, to_int(nTmp[1]));
		break;
	case 17:
		dissolve2_tudi(me, who, to_int(nTmp[1]));
		break;
	case 18:
		query_tudi(me, who, to_int(nTmp[1]));
		break;
	case 19:
		exp = who->get_save_2("shitu.exp");
		pot = who->get_save_2("shitu.pot");
		if (!exp && !pot)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\n ngươi không phù hợp điều kiện lĩnh thưởng!\n", me->get_name()));
			return;
		}
		if (who->get_online_rate() != 100)
		{
			send_user(who, "%c%s", '!', "Bạn hiện tại thời gian không khoẻ mạnh, không thể lĩnh");
			return;
		}
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  me->get_name() + sprintf(":\n    Bạn hiện tại được thưởng %d kinh nghiệm và %d tiềm năng, muốn nhận thưởng không ?\n", exp, pot) + sprintf(ESC "Lĩnh thưởng\ntalk %x# welcome.20\n", getoid(me)) + ESC "Rời khỏi");
		break;
	case 20:
		exp = who->get_save_2("shitu.exp");
		pot = who->get_save_2("shitu.pot");
		if (!exp && !pot)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\n ngươi không phù hợp điều kiện lĩnh thưởng!\n", me->get_name()));
			return;
		}
		if (who->get_online_rate() != 100)
		{
			send_user(who, "%c%s", '!', "Bạn hiện tại thời gian không khoẻ mạnh, không thể lĩnh");
			return;
		}
		max = USER_EXP_D->get_upgrade_exp_limit(who); //经验上限
		if (exp && (exp1 = max - who->get_upgrade_exp()) > 0)
		{
			if (exp1 <= exp)
			{
				send_user(who, "%c%s", '!', "Kinh nghiệm của ngươi đã tới hạn mức cao nhất, hãy xử lý rồi lại đến nhận thưởng");
				exp = exp1;
			}
			else
				exp1 = 0;
			who->add_save_2("shitu.exp", -exp);
			who->add_exp(exp);
			who->add_log("&baishi", exp);
		}
		else if (exp && exp1 <= 0)
		{
			send_user(who, "%c%s", '!', "Kinh nghiệm của ngươi đã tới hạn mức cao nhất, hãy xử lý rồi lại đến nhận thưởng");
			exp = 0;
		}
		max = who->get_max_potential(); //最大潜能
		if (pot && (pot1 = max - who->get_potential()) > 0)
		{
			if (pot1 <= pot)
			{
				send_user(who, "%c%s", '!', "Tiềm năng của ngươi đã tới hạn mức cao nhất, hãy xử lý rồi lại đến nhận thưởng");
				pot = pot1;
			}
			else
				pot1 = 0;
			who->add_save_2("shitu.pot", -pot);
			who->add_potential(pot);
			who->add_log("&potential", pot);
		}
		else if (pot && pot1 <= 0)
		{
			send_user(who, "%c%s", '!', "Tiềm năng của ngươi đã tới hạn mức cao nhất, hãy xử lý rồi lại đến nhận thưởng");
			pot = 0;
		}
		if (exp && pot)
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  me->get_name() + sprintf(":\n    Bạn nhận được %d kinh nghiệm và %d tiềm năng\n", exp, pot) + ESC "Rời khỏi");
		else if (exp)
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  me->get_name() + sprintf(":\n    Bạn nhận được %d kinh nghiệm\n", exp) + ESC "Rời khỏi");
		else if (pot)
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  me->get_name() + sprintf(":\n    Bạn nhận được %d tiềm năng\n", pot) + ESC "Rời khỏi");

		break;
	case 21:
		if (who->get_legend(TASK_2_00, 23) && !who->get_legend(TASK_2_00, 24) && who->get_save("baifang_ms_1") != 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Đại vương gọi ngươi đến Thăm viếng ta sao? Ngươi có thể nhìn xem hiện tại cùng tương lai ở ta này sẽ có cái gì cần đích, ha hả. Người trẻ tuổi, có tinh thần phấn chấn, thật tốt a.\n", me->get_name()));
			who->set_save("baifang_ms_1", 1);
			USER_TASK_D->send_task_intro(who, 2, TID_ZHOUGUO, 21);
		}
		if (who->get_save("baifang_ms_1") == 1 && who->get_save("baifang_ms_2") == 1 && who->get_save("baifang_ms_2") == 1 && who->get_save("baifang_ms_3") == 1 && who->get_save("baifang_ms_4") == 1 && who->get_save("baifang_ms_5") == 1)
		{
			who->set_legend(TASK_2_00, 24);
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_ZHOUGUO, 21, "访问周国名士(完成)");
		}
		break;
	}
}
// Bái sư检查
object check_baishi(object me, object who)
{
	int i, size;
	object *team, user;
	string leader;

	if (who->get_level() < 60)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Lão phu thấy phẩm đức tu vi còn chưa đạt, hãy đợi tới cấp 60 rồi lại đến tìm ta");
		return 0;
	}
	if (who->get_save_2("baishi.shifu"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn chưa xuất xư, làm thế nào làm Sư phụ được đây !");
		return 0;
	}
	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		if (!mapp(who->get_save_2(nTudi[i])))
			break;
	}
	if (i >= size)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Đồ đệ của bạn chưa xuất xư, bạn không thể nhận đồ đệ khác");
		return 0;
	}
	if (!arrayp(team = who->get_team()) || sizeof(team) == 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngươi đến gặp lão phu là muốn thỉnh giáo ư ? tổ đội sao chỉ có một mình thế !");
		return 0;
	}
	if (sizeof(team) > 2)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Nhiều người như vậy đến tìm ta có chuyện gì ? Nếu không phải tới vì danh sư thì mời rời khỏi cho !");
		return;
	}
	if (!stringp(leader = who->get_leader()) || to_int(leader) != who->get_number())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bái sư cần hai người vào trong 1 nhóm, Sư phụ sẽ là đội trưởng, 2 người nhất định phải đứng trong tầm nhìn của lão phu !");
		return 0;
	}
	team -= ({who});
	user = team[0];

	if (user->get_level() > 30)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn muốn nhận hắn làm đồ đệ, hắn giờ đã có thể tự lập rồi ,không cần phải dạy nữa !");
		return 0;
	}
	if (user->get_save_2("baishi.shifu"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn suy nghĩ thu nhận đồ đệ tuy rằng là lựa chọn sáng suốt, nhưng hắn đã có Sư phụ rồi !");
		return 0;
	}
	if (!inside_screen_2(who, user))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn sắp sửa thu đồ đệ ? vậy hắn đâu ? mau bảo hắn tới đây cho ta nhìn mặt !");
		return 0;
	}
	return user;
}
// Bái sư
void baishi(object me, object who, object user)
{
	int i, size;
	string cTudi;

	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		if (!mapp(who->get_save_2(nTudi[i])))
			break;
	}
	if (i >= size)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Đồ đệ của bạn chưa xuất xư, bạn không thể nhận đồ đệ khác");
		return;
	}
	cTudi = nTudi[i];
	who->set_save_2(cTudi + ".name", user->get_name());
	who->set_save_2(cTudi + ".id", user->get_number());
	who->set_save_2(cTudi + ".account", user->get_id());
	who->set_save_2(cTudi + ".level", user->get_level());

	user->set_save_2("baishi.shifu.name", who->get_name());
	user->set_save_2("baishi.shifu.id", who->get_number());
	user->set_save_2("baishi.shifu.account", who->get_id());
	user->set_save_2("baishi.shifu.level", who->get_level());

	who->add_title("B001");
	user->add_title("B002");

	CHAT_D->chat_channel(0, sprintf(HIR "%s " HIY "thu nhận " HIR "%s" HIY " làm đồ đệ, hy vọng " HIR "%s" HIY " về sau có thể dốc lòng dậy dỗ !", who->get_name(), user->get_name(), who->get_name()));
	log_file("baishi.txt", sprintf("%s %s(%d) %s(%d) Bái sư\n", short_time(), who->get_name(), who->get_number(), user->get_name(), user->get_number()));
	who->log_legend(sprintf("Bạn thu nhận %s(%d) làm đồ đệ", user->get_name(), user->get_number()));
	user->log_legend(sprintf("Bạn nhận %s(%d) làm sư phụ", who->get_name(), who->get_number()));
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Chúc mừng ngươi thu nhận một vị cao đồ");
}
// Xuất sư检查
object check_chushi(object me, object who)
{
	int i, size;
	object *team, user;
	string leader, cTudi;

	if (!arrayp(team = who->get_team()) || sizeof(team) == 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngươi đến gặp lão phu là muốn thỉnh giáo ư ? tổ đội sao chỉ có một mình thế !");
		return 0;
	}
	team -= ({0});
	if (sizeof(team) > 2)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Nhiều người như vậy đến tìm ta có chuyện gì ? Nếu không phải tới vì danh sư thì mời rời khỏi cho !");
		return;
	}
	if (!stringp(leader = who->get_leader()) || to_int(leader) != who->get_number())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Xuất xư cần 2 người ở trong 1 nhóm, Sư phụ phải là đội trưởng và phải đứng trong tầm nhìn của ta");
		return 0;
	}
	team -= ({who});
	user = team[0];
	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		//		原来的代码
		//		if ( !mapp(who->get_save_2(nTudi[i])) || who->get_save_2(nTudi[i]+".id") != user->get_number() )
		//			continue;

		//修改上面的代码，以便修正以前的bug导致师父身上缺少徒弟数据不能Xuất sư的问题.
		if (!mapp(who->get_save_2(nTudi[i])) || who->get_save_2(nTudi[i] + ".id") != user->get_number())
		{
			if (user->get_save_2("baishi.shifu.account") == who->get_id() && user->get_save_2("baishi.shifu.name") == who->get_name() && user->get_save_2("baishi.shifu.id") == who->get_number())
			{
				break;
			}
			else
				continue;
		}
		//修改完毕.
		break;
	}
	if (i >= size)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn sắp sửa xuất xư ? đồ đệ bạn đâu ? nhanh đi tìm hắn lại đây");
		return 0;
	}
	if (user->get_level() < 50)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Đồ đệ của ngươi bây giờ vẫn chưa thể xuất sư, ngươi hãy cố gắng dạy dỗ hắn đ !i");
		return 0;
	}
	if (user->get_save_2("baishi.shifu.id") != who->get_number())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Đối phương không phải là đồ đệ của bạn !");
		return 0;
	}
	if (!inside_screen_2(who, user))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Đồ đệ của bạn đâu ? hắn ở đâu đâu ? hãy nhanh tìm hắn lại đây");
		return 0;
	}
	if (user->get_online_rate() != 100)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Đồ đệ của ngươi trước mắt thời gian không khoẻ mạnh, không thể xuất xư");
		return 0;
	}
	if (who->get_online_rate() != 100)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn trước mắt thời gian không khoẻ mạnh, không thể xuất xư");
		return 0;
	}
	return user;
}
// Xuất sư
void chushi(object me, object who, object user)
{
	int i, level, size, j, size1, size2, bonus_exp;
	string fam_name1, fam_name2, tmp1, tmp2, cTudi;
	int *nSkill = ({});
	object fileobj;

	if (user->get_save_2("baishi.shifu.account") != who->get_id() || user->get_save_2("baishi.shifu.name") != who->get_name() || user->get_save_2("baishi.shifu.id") != who->get_number())
		return;

	j = -1;
	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		if (!mapp(who->get_save_2(nTudi[i])))
			continue;
		if (who->get_save_2(nTudi[i] + ".id") != user->get_number())
			continue;
		j = i;
		break;
	}

	(j >= 0) ? cTudi = nTudi[j] : cTudi = "";

	if (user->get_save_2("baishi.shifu.level"))
		bonus_exp = 170000;
	else
		bonus_exp = 400000; //新Xuất sư奖励规则之前Bái sư的
	if (cTudi != "")
		who->delete_save_2(cTudi);

	user->set_save_2("chushi", user->get_save_2("baishi.shifu"));
	user->delete_save_2("baishi");

	who->delete_title("B001");
	user->delete_title("B002");
	who->add_title("B003");
	size1 = sizeof(who->get_apprentice());
	who->add_apprentice(user->get_name());
	size2 = sizeof(who->get_apprentice());
	if (size1 == 9 && size2 == 10)
	{
		who->add_title("B004");
		MAILBOX->sys_mail(who->get_id(), who->get_number(), "Bởi vì bạn dạy dỗ đồ đệ rất bản lĩnh, nên Chu vương bạn cho bạn danh hiệu “Giáo Lý Thiên Hạ”");
	}

	//奖励
	who->add_bonus(500);
	who->add_exp(bonus_exp);
	fam_name1 = who->get_fam_name();
	nSkill = SKILL->get_bonus_skill(who); //可以加的技能
	if (sizeof(nSkill) >= 2)
	{
		i = nSkill[random(sizeof(nSkill))];
		nSkill -= ({i});
		fileobj = load_object(SKILL->get_skill_file(i));
		if (!fileobj)
			return;
		tmp1 = fileobj->get_name();
		who->set_skill(i, who->get_skill(i) + 1);
		i = nSkill[random(sizeof(nSkill))];
		who->set_skill(i, who->get_skill(i) + 1);
		fileobj = load_object(SKILL->get_skill_file(i));
		if (!fileobj)
			return;
		tmp2 = fileobj->get_name();
		send_user(who, "%c%s", ';', sprintf("Bạn nhận được %d điểm công đức, %d kinh nghiệm, %s kỹ năng tăng lên một bậc, %s kỹ năng tăng lên một bậc", 50, bonus_exp, tmp1, tmp2));
	}
	if (sizeof(nSkill) == 1)
	{
		i = nSkill[random(sizeof(nSkill))];
		nSkill -= ({i});
		fileobj = load_object(SKILL->get_skill_file(i));
		if (!fileobj)
			return;
		tmp1 = fileobj->get_name();
		who->set_skill(i, who->get_skill(i) + 1);
		send_user(who, "%c%s", ';', sprintf("Bạn nhận được %d điểm công đức, %d kinh nghiệm, %s kỹ năng tăng lên một bậc", 50, bonus_exp, tmp1, ));
	}
	else
		send_user(who, "%c%s", ';', sprintf("Bạn nhận được %d điểm công đức, %d kinh nghiệm", 50, bonus_exp, ));
	user->add_exp(200000);
	fam_name1 = user->get_fam_name();
	nSkill = SKILL->get_bonus_skill(user);
	tmp1 = "";
	if (sizeof(nSkill) >= 1)
	{
		i = nSkill[random(sizeof(nSkill))];
		fileobj = load_object(SKILL->get_skill_file(i));
		if (!fileobj)
			return;
		tmp1 = fileobj->get_name();
		if (i)
			user->set_skill(i, user->get_skill(i) + 1);
		send_user(user, "%c%s", ';', sprintf("Bạn nhận được %d kinh nghiệm, %s kỹ năng tăng thêm 1 bậc.", 200000, tmp1));
	}
	else
		send_user(user, "%c%s", ';', sprintf("Bạn nhận được %d kinh nghiệm", 200000));
	log_file("baishi.txt", sprintf("%s %s(%d) %s(%d) Xuất sư\n", short_time(), who->get_name(), who->get_number(), user->get_name(), user->get_number()));
	who->log_legend(sprintf("Đồ đệ của bạn %s(%d) xuất xư", user->get_name(), user->get_number()));
	user->log_legend(sprintf("Bạn theo Sư phụ của bạn %s(%d) xuất xư", who->get_name(), who->get_number()));
}
//查询师傅
void query_shifu(object me, object who)
{
	int iFlag, id, iTime, i, size;
	string tmp;
	string account;
	object user, user1;
	mapping mpTmp;

	if (gone_time(who->get("baishi.query")) < 3)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Trong chốc lát nữa lại đến kiểm tra !\n");
		return;
	}
	who->set("baishi.query", time());
	if (!(mpTmp = who->get_save_2("baishi.shifu")))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngươi muốn cùng lão phu tham thảo vi sư chi nói vẫn là nho học chi nói?");
		return;
	}
	id = mpTmp["id"];
	account = mpTmp["account"];
	if (!objectp(user = find_player(sprintf("%d", id))) && user_exist(account))
	{
		user1 = new (USER);
		user1->set_id(account);
		user1->restore();
		user = user1;
	}
	else
		iFlag = 1;
	if (objectp(user))
	{
		for (i = 0, size = sizeof(nTudi); i < size; i++)
		{
			if (!mapp(user->get_save_2(nTudi[i])))
				continue;
			if (user->get_save_2(nTudi[i] + ".id") != who->get_number())
				continue;
			break;
		}
		if (i >= size)
			iFlag = -1;
	}
	else
		iFlag = -1; //不存在
	iTime = gone_time(user->get_quit_time());
	if (objectp(user1))
		destruct(user1);
	if (iFlag == -1)
		return;
	if (iFlag == 1)
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Sư phụ của ngươi hiện tại trong trò chơi !");
	else
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + sprintf(":\n    Sư phụ %d của ngươi không thấy ngươi !", iTime / (3600 * 24) + 1));
}
//徒弟Hoà bình giải trừ quan hệ thầy trò
void dissolve1_shifu(object me, object who)
{
	int iFlag, iTime, id, i, size, j, count;
	string account, tmp, name;
	mapping mpTmp;
	object user, user1;

	mpTmp = who->get_save_2("baishi.shifu");
	if (!mpTmp)
		return;
	id = mpTmp["id"];
	account = mpTmp["account"];
	name = mpTmp["name"];
	if ("sys/sys/user2"->check_id_online(id) != 0)
	{
		send_user(who, "%c%s", '!', " Người chơi này đang ở khác kênh với bạn. Người chơi phải đăng xuất hoặc ở cùng kênh với bạn !");
		return;
	}
	if (!objectp(user = find_player(sprintf("%d", id))) && user_exist(account))
	{
		user1 = new (USER);
		user1->set_id(account);
		user1->restore();
		user = user1;
	}
	if (objectp(user))
	{
		j = -1;
		for (i = 0, size = sizeof(nTudi); i < size; i++)
		{
			if (!mapp(user->get_save_2(nTudi[i])))
				continue;
			count++;
			if (user->get_save_2(nTudi[i] + ".id") != who->get_number())
				continue;
			j = i;
		}
		if (j == -1) //对方没有这样的徒弟
			iTime = -1;
		else if (user1) //对方不在线
			iTime = gone_time(user1->get_quit_time());
	}
	else
		iTime = -1;
	if (iTime != -1 && iTime < 3600 * 24 * 6)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + sprintf(":\n    Của ngươi sư phó liên tục không ở tuyến thời gian nhỏ 7 thiên, ngươi không thể cùng của ngươi sư phó Hoà bình giải trừ quan hệ thầy trò～！", tmp, tmp));
		if (objectp(user1))
			destruct(user1);
		return;
	}
	who->delete_title("B002");
	who->delete_save_2("baishi");
	who->log_legend(sprintf("Bạn cùng Sư phụ %s(%d) giải trừ quan hệ", name, id));
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn đã giải trừ quan hệ thầy trò !");
	if (j != -1) //清除师傅中的徒弟信息
	{
		if (count == 1)
		{
			user->delete_title("B001");
			user->delete_save_2("baishi");
		}
		else
			user->delete_save_2(nTudi[j]);
		MAILBOX->sys_mail(account, id, "Đồ đệ " + who->get_name() + " đã cùng bạn Hoà bình giải trừ quan hệ thầy trò～！");
		user->log_legend(sprintf("Đồ đệ của bạn %s(%d) cùng bạn giải trừ quan hệ thầy trò", who->get_name(), who->get_number()));
	}
	if (objectp(user1))
	{
		user1->save();
		destruct(user1);
	}
	log_file("baishi.txt", sprintf("%s Đồ đệ %s(%d) cùng Sư phụ %s(%d) Hoà bình giải trừ quan hệ thầy trò\n", short_time(), who->get_name(), who->get_number(), name, id));
}
//师傅和平解除指定ID的徒弟的师徒关系
void dissolve1_tudi(object me, object who, int id)
{
	int iFlag, iTime, i, j, count, size;
	string account, tmp, titlecode, name;
	mapping mpTmp;
	object user, user1;

	j = -1;
	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		if (!mapp(who->get_save_2(nTudi[i])))
			continue;
		count++;
		if (who->get_save_2(nTudi[i] + ".id") != id)
			continue;
		j = i;
	}
	if (j == -1)
		return;
	mpTmp = who->get_save_2(nTudi[j]);
	id = mpTmp["id"];
	account = mpTmp["account"];
	name = mpTmp["name"];
	if ("sys/sys/user2"->check_id_online(id) != 0)
	{
		send_user(who, "%c%s", '!', " Người chơi này đang ở khác kênh với bạn. Người chơi phải đăng xuất hoặc ở cùng kênh với bạn !");
		return;
	}
	if (!objectp(user = find_player(sprintf("%d", id))) && user_exist(account))
	{
		user1 = new (USER);
		user1->set_id(account);
		user1->restore();
		user = user1;
		iTime = gone_time(user1->get_quit_time());
	}
	if (objectp(user))
	{
		if (user->get_save_2("baishi.shifu.id") != who->get_number())
			iTime = -1;
		else if (user1) //对方不在线
			iTime = gone_time(user->get_quit_time());
	}
	else
		iTime = -1; //不存在
	if (iTime != -1 && iTime < 3600 * 24 * 6)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Của ngươi đồ đệ " + user->get_name() + " Liên tục không ở tuyến thời gian nhỏ 7 thiên, ngươi không thể cùng của ngươi đồ đệHoà bình giải trừ quan hệ thầy trò～！");
		if (objectp(user1))
			destruct(user1);
		return;
	}
	if (count == 1)
	{
		who->delete_title("B001");
		who->delete_save_2("baishi");
	}
	else
		who->delete_save_2(nTudi[j]);
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn đã giải trừ quan hệ thầy trò !");
	who->log_legend(sprintf("Bạn cùng %s(%d) giải trừ quan hệ thầy trò", name, id));
	if (user)
	{
		user->delete_title("B002");
		user->delete_save_2("baishi");
		MAILBOX->sys_mail(account, id, "Sư phụ " + who->get_name() + " của bạn muốn Hoà bình giải trừ quan hệ thầy trò～！");
		user->log_legend(sprintf("Đồ đệ của bạn %s(%d) cùng bạn giải trừ quan hệ thầy trò", who->get_name(), who->get_number()));
	}
	if (objectp(user1))
	{
		user1->save();
		destruct(user1);
	}
	log_file("baishi.txt", sprintf("%s Sư phụ %s(%d) cùng Đồ đệ %s(%d) Hoà bình giải trừ quan hệ thầy trò\n", short_time(), who->get_name(), who->get_number(), name, id));
}
//徒弟Mạnh mẽ giải trừ quan hệ thầy trò
void dissolve2_shifu(object me, object who)
{
	int iFlag, iTime, id, i, size, j, count, fee;
	string account, tmp, name;
	mapping mpTmp;
	object user, user1;

	mpTmp = who->get_save_2("baishi.shifu");
	if (!mpTmp)
		return;
	id = mpTmp["id"];
	account = mpTmp["account"];
	name = mpTmp["name"];
	if ("sys/sys/user2"->check_id_online(id) != 0)
	{
		send_user(who, "%c%s", '!', " Người chơi này đang ở khác kênh với bạn. Người chơi phải đăng xuất hoặc ở cùng kênh với bạn !");
		return;
	}
	if (!objectp(user = find_player(sprintf("%d", id))) && user_exist(account))
	{
		user1 = new (USER);
		user1->set_id(account);
		user1->restore();
		user = user1;
	}
	j = -1;
	if (user) //清除师傅中的徒弟信息
	{
		for (i = 0, size = sizeof(nTudi); i < size; i++)
		{
			if (!mapp(user->get_save_2(nTudi[i])))
				continue;
			count++;
			if (user->get_save_2(nTudi[i] + ".id") != who->get_number())
				continue;
			j = i;
		}
	}
	if (j != -1) //对方没有解除关系
	{
		fee = who->get_cash() - 200000;
		if (fee < 0)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngân lượng của bạn không đủ, không thể giải trừ quan hệ thầy trò");
			if (objectp(user1))
				destruct(user1);
			return;
		}
		who->add_cash(-20000);
	}
	who->delete_title("B002");
	who->delete_save_2("baishi");
	who->log_legend(sprintf("Bạn cùng Sư phụ %s(%d) giải trừ quan hệ", name, id));
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn đã giải trừ quan hệ thầy trò !");
	if (j != -1) //清除师傅中的徒弟信息
	{
		if (count == 1)
		{
			user->delete_title("B001");
			user->delete_save_2("baishi");
		}
		else
			user->delete_save_2(nTudi[j]);
		MAILBOX->sys_mail(account, id, "Đồ đệ " + who->get_name() + " đã cùng bạn Mạnh mẽ giải trừ quan hệ thầy trò～！");
		user->log_legend(sprintf("Đồ đệ của bạn %s(%d) cùng bạn giải trừ quan hệ thầy trò", who->get_name(), who->get_number()));
	}
	if (objectp(user1))
	{
		user1->save();
		destruct(user1);
	}
	log_file("baishi.txt", sprintf("%s Đồ đệ %s(%d) cùng Sư phụ %s(%d) Mạnh mẽ giải trừ quan hệ thầy trò\n", short_time(), who->get_name(), who->get_number(), name, id));
}
//师傅强行解除指定ID的徒弟的师徒关系
void dissolve2_tudi(object me, object who, int id)
{
	int iFlag, iTime, i, j, count, size, fee;
	string account, tmp, titlecode, name;
	mapping mpTmp;
	object user, user1;

	j = -1;
	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		if (!mapp(who->get_save_2(nTudi[i])))
			continue;
		count++;
		if (who->get_save_2(nTudi[i] + ".id") != id)
			continue;
		j = i;
	}
	if (j == -1)
		return;
	mpTmp = who->get_save_2(nTudi[j]);
	id = mpTmp["id"];
	account = mpTmp["account"];
	name = mpTmp["name"];
	if ("sys/sys/user2"->check_id_online(id) != 0)
	{
		send_user(who, "%c%s", '!', " Người chơi này đang ở khác kênh với bạn. Người chơi phải đăng xuất hoặc ở cùng kênh với bạn !");
		return;
	}
	if (!objectp(user = find_player(sprintf("%d", id))) && user_exist(account))
	{
		user1 = new (USER);
		user1->set_id(account);
		user1->restore();
		user = user1;
	}
	if (objectp(user) && user->get_save_2("baishi.shifu.id") == who->get_number()) //对方没有解除关系
	{
		fee = who->get_cash() - 500000;
		if (fee < 0)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngân lượng của bạn không đủ, không thể giải trừ quan hệ thầy trò");
			if (objectp(user1))
				destruct(user1);
			return;
		}
		who->add_cash(-50000);
	}
	if (count == 1)
	{
		who->delete_title("B001");
		who->delete_save_2("baishi");
	}
	else
		who->delete_save_2(nTudi[j]);
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bạn đã giải trừ quan hệ thầy trò !");
	who->log_legend(sprintf("Bạn cùng %s(%d) giải trừ quan hệ thầy trò", name, id));
	if (user)
	{
		user->delete_title("B002");
		user->delete_save_2("baishi");
		MAILBOX->sys_mail(account, id, "Sư phụ " + who->get_name() + " của bạn muốn Mạnh mẽ giải trừ quan hệ thầy trò～！");
		user->log_legend(sprintf("Sư phụ %s(%d) cùng bạn giải trừ quan hệ thầy trò", who->get_name(), who->get_number()));
	}
	if (objectp(user1))
	{
		user1->save();
		destruct(user1);
	}
	log_file("baishi.txt", sprintf("%s Sư phụ %s(%d) cùng Đồ đệ %s(%d) Mạnh mẽ giải trừ quan hệ thầy trò\n", short_time(), who->get_name(), who->get_number(), name, id));
}
//和平解除徒弟列表
void dissolve1_list(object me, object who)
{
	int i, size, id;
	string result;
	mapping mpTmp;

	id = getoid(me);
	result = sprintf("%s\n    Hãy lựa muốn cùng đồ đệ Hoà bình giải trừ quan hệ thầy trò:\n", me->get_name());
	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		if (!mapp(mpTmp = who->get_save_2(nTudi[i])))
			continue;
		result += sprintf(ESC "%s\ntalk %x# welcome.16.%d\n", mpTmp["name"], id, mpTmp["id"]);
	}
	result += ESC "Rời khỏi";
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
}

//强行解除徒弟列表
void dissolve2_list(object me, object who)
{
	int i, size, id;
	string result;
	mapping mpTmp;

	id = getoid(me);
	result = sprintf("%s\n    Hãy lựa muốn cùng đồ đệ Mạnh mẽ giải trừ quan hệ thầy trò:\n", me->get_name());
	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		if (!mapp(mpTmp = who->get_save_2(nTudi[i])))
			continue;
		result += sprintf(ESC "%s\ntalk %x# welcome.17.%d\n", mpTmp["name"], id, mpTmp["id"]);
	}
	result += ESC "Rời khỏi";
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
}
//查询徒弟列表
void query_tudi_list(object me, object who)
{
	int i, size, id;
	string result;
	mapping mpTmp;

	id = getoid(me);
	result = sprintf("%s\n    Hãy lựa chọn kiếm tra đồ đệ:\n", me->get_name());
	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		if (!mapp(mpTmp = who->get_save_2(nTudi[i])))
			continue;
		result += sprintf(ESC "%s\ntalk %x# welcome.18.%d\n", mpTmp["name"], id, mpTmp["id"]);
	}
	result += ESC "Rời khỏi";
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
}
//查询徒弟
void query_tudi(object me, object who, int id)
{
	int iFlag, iTime, i, size, j;
	string tmp;
	string account, name;
	object user, user1;
	mapping mpTmp;

	if (gone_time(who->get("baishi.query")) < 3)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Trong chốc lát nữa lại đến kiểm tra !\n");
		return;
	}
	who->set("baishi.query", time());
	j = -1;
	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		if (!mapp(who->get_save_2(nTudi[i])))
			continue;
		if (who->get_save_2(nTudi[i] + ".id") != id)
			continue;
		j = i;
	}
	if (j == -1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngươi muốn cùng lão phu tham thảo vi sư chi nói vẫn là nho học chi nói?");
		return;
	}
	mpTmp = who->get_save_2(nTudi[j]);
	id = mpTmp["id"];
	account = mpTmp["account"];
	name = mpTmp["name"];
	if (!objectp(user = find_player(sprintf("%d", id))) && user_exist(account))
	{
		user1 = new (USER);
		user1->set_id(account);
		user1->restore();
		user = user1;
	}
	else
		iFlag = 1;
	if (!objectp(user))
		return; //不存在
	iTime = gone_time(user->get_quit_time());
	if (objectp(user1))
		destruct(user1);
	if (iFlag == -1)
		return;
	if (iFlag == 1)
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + sprintf(":\n    Đồ đệ %s của bạn hiện trong trò chơi !", name));
	else
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + sprintf(":\n    Đồ đệ %s của bạn đã %d ngày không thấy ngươi !", name, iTime / (3600 * 24) + 1));
}
//徒弟升级，师傅用友好度换的经验
void add_friend_bonus(object user, object who, int level)
{
	int i, j, size, exp, *nTmp;
	string cTudi, cTmp;

	if (level == 10)
		exp = 200000;
	else if (level == 20)
		exp = 500000;
	else if (level == 30)
		exp = 1000000;
	else if (level == 40)
		exp = 2000000;
	else
		return;
	j = -1;
	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		if (!mapp(who->get_save_2(nTudi[i])))
			continue;
		if (who->get_save_2(nTudi[i] + ".id") != user->get_number())
			continue;
		j = i;
		break;
	}
	if (j == -1)
		return;
	cTudi = nTudi[j];
	nTmp = who->get_save_2(cTudi + ".friend_bonus");
	if (sizeof(nTmp) == 0)
		nTmp = ({});
	if (member_array(level, nTmp) == -1)
		nTmp += ({level});
	who->set_save_2(cTudi + ".friend_bonus", nTmp);
	nTmp = user->get_save_2("baishi.shifu.friend_bonus");
	if (sizeof(nTmp) == 0)
		nTmp = ({});
	if (member_array(level, nTmp) == -1)
		nTmp += ({level});
	user->set_save_2("baishi.shifu.friend_bonus", nTmp);
	MAILBOX->sys_mail(who->get_id(), who->get_number(), sprintf(BLK "Bởi vì đồ đệ của bạn " HIR "%s" BLK " chăm chỉ hiếu học, thực lực tiến bộ,Lão Thôn Trưởng (150, 98) đặc biệt ngợi khen " HIR "%d kinh nghiệm" BLK " cho bạn !", user->get_name(), exp));
	cTmp = who->get_name();
	CHAT_D->sys_channel(0, sprintf(HIG "Bởi vì %s(%d) có tài dậy dỗ, thực lực của đồ đệ tiến bộ, Lão Thôn Trưởng (150,98) đặc biệt khen thưởng %s %d kinh nghiệm !", cTmp, who->get_number(), cTmp, exp));
}

//徒弟升级的奖励
int add_shifu_exp(object who, int exp)
{
	int id, max, exp1, pot, level, level1, flag, iSave;
	string account, name;
	mapping mpTmp;
	object user, user1;

	if (mapp(mpTmp = who->get_save_2("baishi.shifu"))) // Xuất sư前升级
		flag = 1;
	else if (mapp(mpTmp = who->get_save_2("chushi"))) // Xuất sư后升级
		flag = 2;
	else
		return 0;
	id = mpTmp["id"];
	account = mpTmp["account"];
	name = mpTmp["name"];
	if (!objectp(user = find_player(sprintf("%d", id))) && user_exist(account))
	{
		user1 = new (USER);
		user1->set_id(account);
		user1->restore();
		user = user1;
	}
	if (!user)
		return 0;
	if (flag == 2) // Xuất sư后
	{
		exp /= 100;
		iSave = 1;
		user->add_save_2("shitu.exp", exp);
		MAILBOX->sys_mail(account, id, sprintf(BLK "Đồ đệ " HIR "%s" BLK " của bạn chăm học khổ luyện, thực lực lại tăng tiến một tầng. Bởi vậy bạn được thưởng %d điểm kinh nghiệm ! Mạnh Tử ở Tân Thủ Thôn (136, 144). Khổng Phu Tử ở Chu Quốc (136, 144) ", who->get_name(), exp));
	}
	else if (flag == 1) // Xuất sư前
	{
		level = who->get_level();
		level1 = mpTmp["level"];
		; //新的Bái sư规则下才有这个值
		if (level == 5)
			pot = 500;
		else if (level == 10)
		{
			exp1 = 50000;
			pot = 1000;
		}
		else if (level == 15)
			pot = 1500;
		else if (level == 20)
		{
			exp1 = 80000;
			pot = 2000;
		}
		else if (level == 25)
			pot = 2500;
		else if (level == 30)
		{
			exp1 = 100000;
			pot = 3000;
		}
		else if (level == 35)
			pot = 5000;
		else if (level == 40)
			pot = 7000;
		if (level1 && exp1) //奖励给师傅(新规则)
		{
			iSave = 1;
			user->add_save_2("shitu.exp", exp1);
			MAILBOX->sys_mail(account, id, sprintf(BLK "Đồ đệ " HIR "%s" BLK " của bạn chăm học khổ luyện, thực lực lại tăng tiến một tầng. Bởi vậy bạn được thưởng %d điểm kinh nghiệm ! Mạnh Tử ở Tân Thủ Thôn (136, 144). Khổng Phu Tử ở Chu Quốc (136, 144) ", who->get_name(), exp1));
		}
		if (pot) //奖励给徒弟
		{
			who->add_save_2("shitu.pot", pot);
			MAILBOX->sys_mail(who->get_id(), who->get_number(), sprintf(BLK "Bởi vì bạn khổ luyện chăm chỉ, được Chu vương ưu ái, do đó bạn được thưởng %d kinh nghiệm ! Mạnh Tử ở Tân Thủ Thôn (136, 144). Khổng Phu Tử ở Chu Quốc (136, 144)", pot));
		}
		if (level == 10 || level == 20 || level == 30 || level == 40) //师傅用友好度换经验
		{
			add_friend_bonus(who, user, level);
			iSave = 1;
		}
	}
	if (user1)
	{
		if (iSave)
			user1->save();
		destruct(user1);
	}
	return exp;
}
// Lĩnh thưởng的列表
void friend_bonus_list1(object me, object who)
{
	int i, size;
	string cTmp = "";

	for (i = 0, size = sizeof(nTudi); i < size; i++)
	{
		if (!mapp(who->get_save_2(nTudi[i])))
			continue;
		if (!who->get_save_2(nTudi[i] + ".friend_bonus"))
			continue;
		cTmp += sprintf(ESC "Đổi lấy %s phần thưởng\ntalk %x# welcome.%d\n", who->get_save_2(nTudi[i] + ".name"), getoid(me), 1000 + 31 + i);
	}
	if (sizeof(cTmp))
		cTmp = me->get_name() + ":\n    Ngươi xác nhận muốn dùng cùng ngươi đồ đệ đích hữu hảo độ đổi lấy đặc biệt thưởng cho sao không? Vậy được rồi!\n" + cTmp + ESC "Rời khỏi";
	else
		cTmp = me->get_name() + ":\n    Bạn không phù hợp điều kiện lĩnh phần thưởng đặc biệt !\n" + ESC "Rời khỏi";
	send_user(who, "%c%s", ':', cTmp);
}
//等级奖励列表
void friend_bonus_list2(object me, object who, int which)
{
	int i, size, *nTmp, level;
	string cTmp = "", cTudi;

	cTudi = nTudi[which - 1031];
	nTmp = who->get_save_2(cTudi + ".friend_bonus");
	if ((size = sizeof(nTmp)) == 0)
		return;
	which -= 1030;
	for (i = 0; i < size; i++)
	{
		level = nTmp[i];
		if (level == 10)
			cTmp += sprintf(ESC "Phần thưởng đặc biệt đồ đệ 10 cấp ( tiêu hao 100 điểm hảo hữu)\ntalk %x# welcome.%d\n", getoid(me), 1000 + which * 100 + level);
		else if (level == 20)
			cTmp += sprintf(ESC "Phần thưởng đặc biệt đồ đệ 20 cấp ( tiêu hao 800 điểm hảo hữu)\ntalk %x# welcome.%d\n", getoid(me), 1000 + which * 100 + level);
		else if (level == 30)
			cTmp += sprintf(ESC "Phần thưởng đặc biệt đồ đệ 30 cấp ( tiêu hao 1500 điểm hảo hữu)\ntalk %x# welcome.%d\n", getoid(me), 1000 + which * 100 + level);
		else if (level == 40)
			cTmp += sprintf(ESC "Phần thưởng đặc biệt đồ đệ 40 cấp ( tiêu hao 2000 điểm hảo hữu)\ntalk %x# welcome.%d\n", getoid(me), 1000 + which * 100 + level);
	}
	if (sizeof(cTmp))
		cTmp = me->get_name() + ":\n    Ngươi xác nhận muốn dùng cùng ngươi đồ đệ đích hữu hảo độ đổi lấy đặc biệt thưởng cho sao không? Vậy được rồi!\n" + cTmp + ESC "Rời khỏi";
	else
		cTmp = me->get_name() + ":\n    Bạn không phù hợp điều kiện lĩnh phần thưởng đặc biệt !\n" + ESC "Rời khỏi";
	send_user(who, "%c%s", ':', cTmp);
}
//获取友好度奖励
int get_friend_bonus(object me, object who, int flag)
{
	int which, *nTmp, level, exp, degree, id;
	string cTudi;

	which = flag % 1000 / 100 - 1;
	if (which < 0 || which >= sizeof(nTudi))
		return;
	level = flag % 100;
	cTudi = nTudi[which];
	nTmp = who->get_save_2(cTudi + ".friend_bonus");
	if (sizeof(nTmp) == 0 || member_array(level, nTmp) == -1)
		return;
	if (level == 10)
	{
		exp = 200000;
		degree = 100;
	}
	else if (level == 20)
	{
		exp = 500000;
		degree = 800;
	}
	else if (level == 30)
	{
		exp = 1000000;
		degree = 1500;
	}
	else if (level == 40)
	{
		exp = 2000000;
		degree = 2000;
	}
	else
		return;
	if (who->get_friend_degree(who->get_save_2(cTudi + ".id")) < degree)
	{
		send_user(who, "%c%s", ':', me->get_name() + sprintf(":\n    Bạn cùng đồ đệ độ hảo hữu không đủ %d , không thể lĩnh thưởng !\n", degree) + ESC "Rời khỏi");
		return;
	}
	who->add_friend_degree(who->get_save_2(cTudi + ".id"), -degree);
	who->add_exp(exp);
	nTmp -= ({level});
	if (sizeof(nTmp) == 0)
		who->delete_save_2(cTudi + ".friend_bonus");
	else
		who->set_save_2(cTudi + ".friend_bonus", nTmp);
	send_user(who, "%c%s", '!', "Bạn nhận phần thưởng đặc biệt");
}
