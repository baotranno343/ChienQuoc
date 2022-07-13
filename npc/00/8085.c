
#include <npc.h>
#include <ansi.h>

inherit OFFICER;

void do_goto();
void do_recover();
void do_khieuchien();
// void do_timnguoi();

// 函数:获取人物造型
int get_char_picid() { return 5109; }

// 函数:构造处理
void create()
{
	set_name("Võ Sư");
	set_real_name("Phàm Bá");

	set_2("talk", (["go":(
							 : do_goto:),
						 "recover":(
									   : do_recover:),
					  "khieuchien":(
									   : do_khieuchien:),
					  // "timnguoi":(
					  // 			   : do_timnguoi:),
	]));

	setup();
}

// 函数:对话处理
void do_look(object who)
{
	more_look_menu(who, sprintf(" %s :\nVị " + NPC_RANK_D->get_respect(who) + " này có muốn ra võ trường tìm người tỉ thí không?\n" ESC "Đi tỉ thí .\n" + sprintf("talk %x# go\n", getoid(this_object())) +
									ESC "Giúp ta hồi phục khí huyết và pháp lực đi.\n" + sprintf("talk %x# recover\n", getoid(this_object())) +
									//    ESC HIY"Gửi thư khiêu chiến.\n" + sprintf( "talk %x# khieuchien\n", getoid( this_object() ) ) +
									ESC HIY "Gửi thư khiêu chiến.\n" + sprintf("timnguoi ?.?\n") +
									ESC "Rời khỏi\nCLOSE\n",
								get_name()));
}

// 函数:移动处理
void do_goto()
{
	object who;
	int p, z, x, y;

	who = this_player();

	if (p = get_jumpin(885, 1))
	{
		x = 80;
		y = 60;
		z = 885;
		if (p = get_valid_xy(z, x + random(40) - 20, y + random(40) - 20, IS_CHAR_BLOCK))
		{
			write_user(who, sprintf(" %s nói: Tỉ võ sẽ không chết, yên tâm thử đi!", get_name()));

			who->add_to_scene(z, p / 1000, p % 1000, get_d(who));
		}
	}
}

// 函数:补血处理
void do_recover()
{
	object who;
	int hp, mp, yuan, cash;
	string result;
	who = this_player();
	hp = who->get_max_hp() - who->get_hp();
	mp = who->get_max_mp() - who->get_mp();
	yuan = who->get_max_yuan() - who->get_yuan();
	cash = hp * 2 + mp * 2 + yuan * 2000;
	if (cash == 0)
	{
		result = "Ngươi không cần phải trị liệu!";
		send_user(who, "%c%s", '!', result);
		return;
	}
	if (who->get_cash() < cash)
	{
		result = get_name() + ":\n    Ngươi không đủ ngân lượng để phục hồi Sinh khí !\n" ESC "Rời khỏi\nCLOSE\n";
		send_user(who, "%c%c%w%s", ':', 3, 5109, result);
		return;
	}
	who->add_cash(-cash);
	who->set_hp(who->get_max_hp());
	who->set_mp(who->get_max_mp());
	who->set_yuan(who->get_max_yuan());
	result = sprintf("Bạn đã dùng %d lượng hồi phục Sinh lực", cash);
	send_user(who, "%c%s", '!', result);
}
void do_khieuchien()
{
	object who;
	int hp, mp, yuan, cash;
	string result;
	who = this_player();

	if (who->get_cash() < 100000)
	{
		result = get_name() + ":\n    Ngươi không đủ 100.000 ngân lượng để gửi một lá thư Khiêu Chiến !\n" ESC "Rời khỏi\nCLOSE\n";
		send_user(who, "%c%c%w%s", ':', 3, 5109, result);
		return;
	}
	who->add_cash(-100000);
	USER_D->user_channel(sprintf(HIG "Bằng hữu " HIC "%s (%d)" HIG " đứng trong Võ Đài với ánh mắt đầy sát khí, hét lớn với mọi người trên khắp Thế Giới : \"Nếu như ai đánh bại được ta, ta sẽ làm nô lệ cho người đó\" . ", who->get_name(), who->get_number()));
}
