#include <ansi.h>
#include <skill.h>
inherit COMBINED;
inherit ITEM;

int get_item_value() { return 450; }
int get_item_value_2() { return 380; }
int get_item_number() { return 10001006; }
int get_item_color() { return 2; }

// 函数:构造处理
void create()
{
	set_name("Chiến Quốc Lệnh");
	set_picid_1(0096);
	set_picid_2(0096);
	set_value(100);
	set_amount(1);
	set_record(1);
	set_no_give(1);
	set_no_sell(1);
}
int is_usable() { return 1; }
// 函数:获取描述
string get_desc()
{
	return "Lệnh bài thần kỳ, sau khi sử dụng bạn sẽ nhận được điểm Kinh nghiệm x 2 khi tiêu diệt quái vật trong suốt 1 tiếng.\n (Mỗi tuần chỉ có thể sử dụng tối đa 25 Chiến Quốc Lệnh.)";
}
// 函数:获取描述(持续)加血
string get_loop_desc(object me)
{
	return "Nhân đôi kinh nghiệm trong 1 giờ.";
}
int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object item)
{
	int i, iWeek;
	if (gone_time(who->get_login_time()) + who->get_game_time() < who->get_double_time())
	{
		send_user(who, "%c%c%w%s", ':', 3, 0, sprintf("Ngươi vẫn còn thời gian nhân đôi kinh nghiệm, Muốn dùng đè lên không?\n" ESC "Chấp nhận\nuse ! %x#\n" ESC "Huỷ bỏ", getoid(item)));
		return 0;
	}
	iWeek = (time() - 4 * 24 * 3600 + 8 * 3600) / (7 * 24 * 3600);
	if (who->get_save_2("double_time.week") != iWeek)
	{
		who->set_save_2("double_time.week", iWeek);
		who->set_save_2("double_time.time", 0);	  //双
		who->set_save_2("double_time.time1", 0);  //战国令
		who->set_save_2("double_time.time2", 0);  //战国号角
		who->set_save_2("double_time.time3", 0);  //战国号角
		who->set_save_2("double_time.freeze", 0); //冻结的双倍时间
	}
	// if ( who->get_save_2("double_time.time1") >= 25 )
	// {
	// 	send_user(who,"%c%s",'!',"Ngươi đã dùng tới giới hạn cao nhất.");
	// 	return 0;
	// }
	if (who->get_online_rate() == 210)
	{
		send_user(who, "%c%s", '!', "Ngươi đã mệt rồi,Không được sử dụng Chiến Quốc Lệnh nữa.");
		return 0;
	}
	else if (who->get_online_rate() == 0)
	{
		send_user(who, "%c%s", '!', "Ngươi không khoẻ,Không được sử dụng Chiến Quốc Lệnh nữa.");
		return 0;
	}
	if (who->get_save_2("double_time.freeze") > 3600 * 18)
	{
		send_user(who, "%c%s", '!', "Đông cứng nhân đôi kinh nghiệm vượt qua 18 giờ");
		return 0;
	}
	i = gone_time(who->get_login_time());
	who->add_save_2("double_time.time1", 1);

	if (who->get_save_2("double_time.freeze") > 0)
	{
		who->add_save_2("double_time.freeze", 3600);
		send_user(who, "%c%c%d%s", 0x43, 10, 0, HIY "Thời gian nhân đôi của ngươi đã gửi lại Thần Tiên Gia Gia.");
		"/inh/user/mail"->sys_mail(who->get_id(), who->get_number(), "Bởi vì ngươi đã gửi thời gian nhân đôi tại Thần Tiên Gia Gia,nên sử dụng Chiến Quốc Lệnh thời gian cũng sẽ gửi lại Thần Tiên Gia Gia tại " HIR "Chu Quốc（291，175） hoặc Tân Thủ Thôn（91，164） " NOR "Ngươi phải nhớ " HIR "giải trừ thời gian đông cứng trước 23:59 kể từ khi đông cứng," NOR "，Nếu không thời gian đông cứng sẽ biến mất.");
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, 0001, "Viện Trợ trò chơi");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi");
		"/sys/task/task"->send_task_intro(who, 1, 1, 1);
		return 1;
	}
	if (i + who->get_game_time() < who->get_double_time())
		who->set_double_time(who->get_double_time() + 3600);
	else
		who->set_double_time(i + who->get_game_time() + 3600);
	send_user(who, "%c%w%w%c", 0x81, 9998, 3600, EFFECT_GOOD);
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, 0001, "Viện Trợ trò chơi");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi");
	"/sys/task/task"->send_task_intro(who, 1, 1, 1);
	return 1;
}

// 函数:使用效果
int confirm_use(object me) { return __FILE__->confirm_use_callout(me, this_object()); }

// 函数:使用效果(在线更新)
int confirm_use_callout(object who, object item)
{
	int i, iWeek;

	iWeek = (time() - 4 * 24 * 3600 + 8 * 3600) / (7 * 24 * 3600);
	if (who->get_save_2("double_time.week") != iWeek)
	{
		who->set_save_2("double_time.week", iWeek);
		who->set_save_2("double_time.time", 0);	  //双
		who->set_save_2("double_time.time1", 0);  //战国令
		who->set_save_2("double_time.time2", 0);  //战国号角
		who->set_save_2("double_time.time3", 0);  //战国号角
		who->set_save_2("double_time.freeze", 0); //冻结的双倍时间
	}
	if (who->get_save_2("double_time.time1") >= 25)
	{
		send_user(who, "%c%s", '!', "Ngươi đã dùng tới giới hạn cao nhất.");
		return 0;
	}
	if (who->get_online_rate() == 210)
	{
		send_user(who, "%c%s", '!', "Ngươi đã mệt rồi,Không được sử dụng Chiến Quốc Lệnh nữa.");
		return 0;
	}
	else if (who->get_online_rate() == 0)
	{
		send_user(who, "%c%s", '!', "Ngươi không khoẻ,Không được sử dụng Chiến Quốc Lệnh nữa.");
		return 0;
	}
	who->add_save_2("double_time.time1", 1);
	if (who->get_save_2("double_time.freeze") > 0)
	{
		who->add_save_2("double_time.freeze", 3600);
		send_user(who, "%c%s", '!', "Thời gian nhân đôi của ngươi đã gửi lại Thần Tiên Gia Gia.");
		"/inh/user/mail"->sys_mail(who->get_id(), who->get_number(), "Bởi vì ngươi đã gửi thời gian nhân đôi tại Thần Tiên Gia Gia,nên sử dụng Chiến Quốc Lệnh thời gian cũng sẽ gửi lại Thần Tiên Gia Gia tại " HIR "Chu Quốc(291，175) hoặc Tân Thủ Thôn(91，164) " NOR "Ngươi phải nhớ " HIR "giải trừ thời gian đông cứng trước 23:59 kể từ khi đông cứng," NOR "，Nếu không thời gian đông cứng sẽ biến mất.");
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, 0001, "Viện Trợ trò chơi");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi");
		"/sys/task/task"->send_task_intro(who, 1, 1, 1);
		return 1;
	}
	i = gone_time(who->get_login_time());
	if (gone_time(who->get_login_time()) + who->get_game_time() < who->get_double_time())
		who->set_double_time(who->get_double_time() + 3600);
	else
		who->set_double_time(i + who->get_game_time() + 3600);
	send_user(who, "%c%w%w%c", 0x81, 9998, who->get_double_time() - i - who->get_game_time(), EFFECT_GOOD);
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, 0001, "Viện Trợ trò chơi");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi");
	"/sys/task/task"->send_task_intro(who, 1, 1, 1);
	return 1;
}