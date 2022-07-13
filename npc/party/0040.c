#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <chia_kenh.h>
inherit SAVE_F;
inherit OFFICER;

void do_bonus(string arg);

// 函数:获取人物造型
int get_char_picid() { return 5302; }

// 函数:构造处理
void create()
{
	int i, size, *nTmp;
	set_name("Người Ký Gửi Kim Bảo");

	set_2("talk", (["bonus":(
								: do_bonus:),
	]));

	setup();
}

void do_look(object who)
{
	__FILE__->do_look_2(who, this_object());
}

void do_look_2(object who, object me)
{
	int id;
	id = getoid(me);
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
			  me->get_name() + ":\nĐược sự uỷ thác của Chu Vương, từ nay ta sẽ giúp thiên hạ trao đổi Kim Bảo. Mọi người có thể yên tâm gửi bán Kim Bảo cho bổn nhân, ta nhất định sẽ công bằng hành sự tuỳ theo yêu cầu của từng người!\n" + sprintf(ESC "Chú ý khi gửi bán\ntalk %x# bonus.1\n" ESC "Ta đến gửi bán Kim Bảo\ntalk %x# bonus.10\n" ESC "Ta đến thu mua Kim Bảo\ntalk %x# bonus.20\n" ESC "Kiểm tra Kim Bảo đã gửi bán\nconsign status\n" ESC "Rời khỏi", id, id, id));
}

void do_bonus(string arg)
{
	__FILE__->do_bonus_2(this_player(), this_object(), arg);
}

void do_bonus_2(object me, object who, string arg)
{
	int id, flag;
	string result;
	if (MAIN_D->get_kenh() != KENH_KYGUIKNB && KENH_KYGUIKNB != 0)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Ký Gửi hãy về Kênh Mua Bán");
		return;
	}
	flag = to_int(arg);
	id = getoid(who);
	switch (flag)
	{
	case 1:
		result = sprintf("%s:\nKhi gửi bán Kim Nguyên Bảo đều phải tốn 5%% Kim Nguyên Bảo chi phí, Khi kí gửi ta cho phép thời gian kí gửi tối đa là 8 giờ, 12 giờ, 24 giờ, nếu vượt qua thời gian kí gửi mà số Kim Bảo ngươi kí gửi vẫn chưa có người mua thì ta sẽ trả lại Kim Bảo cho ngươi, lần sau vẫn có thể đến gửi bán !\n", who->get_name());
		result += ESC "Rời khỏi";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 10:
		send_user(me, "%c%c%c", 0x92, 1, 1);
		send_user(me, "%c%c%d", 0x45, 2, "sys/sys/test_db"->get_yuanbao(me));
		break;
	case 20:
		result = sprintf("%s:\nNgươi muốn mua bao nhiêu Kim Nguyên Bảo :\n", who->get_name());
		result += ESC "Ta muốn mua 50 Kim Nguyên Bảo\nconsign list 50\n";
		result += ESC "Ta muốn mua 100 Kim Nguyên Bảo\nconsign list 100\n";
		result += ESC "Ta muốn mua 200 Kim Nguyên Bảo\nconsign list 200\n";
		result += ESC "Rời khỏi";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	}
}
