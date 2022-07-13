/*-----------------------------------------------------------------------------------------*\
	《真假虎王》活动配置NPC ---- 活动天使
	由cjxx创建
	使用此文件时需要配合活动主控文件。
\*-----------------------------------------------------------------------------------------*/
#include <npc.h>
#include <ansi.h>
#include <time.h>
inherit SAVE_F;
inherit OFFICER;

#define GUESS_TRUE_TIGER "/sys/party/guess_true_tiger"
#define _DEBUG(str) ; //if(objectp(find_char("1"))) {tell_user(find_char("1"),str);}

void do_tiger_active(string arg); //	真假虎王相关对话操作

int get_char_picid() { return 0951; }

void create()
{
	set_name("Thiên Sứ Hoạt Động");

	set_2("talk", (["tiger":(
								: do_tiger_active:),
	]));
	setup();
}

//	玩家点击NPC
void do_look(object who)
{
	__FILE__->do_look_reflash(who, this_object());
}
//	do_look 的在线更新函数
void do_look_reflash(object who, object me)
{
	int id = getoid(me);
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n Ta là Thiên Sứ Hoạt Động đáng yêu nhất, tên hàng xóm mang tên Thiên Sứ Trao đổi xấu xí hơn ta nhiều ~ Các hoạt động của Chiến Quốc đều do ta phụ trách, nếu như ngươi có chỗ nào không hiểu, có thể đến hỏi ta ~\n" ESC "Thật Giả Hổ Vương \ntalk %x# tiger.1\n" ESC "Rời đi", me->get_name(), id));
}
//	调用下一关的函数
void play_next_stage(object who, int level)
{
	GUESS_TRUE_TIGER->delete_tigers_on_player(who, 0);
	GUESS_TRUE_TIGER->active_main_logic(who, level);
	who->set("now_call_out_next_stage", 0);
}
//	玩家放弃活动
void give_up_the_activity(object who)
{
	string *active_bonus, say_word;
	int level = who->get_save("guess_true_tiger");
	if (level > 0)
	{
		active_bonus = active_bonus = GUESS_TRUE_TIGER->get_active_bonus(level);
		if (level > 1)
		{
			say_word = sprintf("Bạn vượt ải thành công, thu được %s Ngân Lượng Khóa và" HIR "%s" NOR "Tự hào ban thưởng, hãy tới nơi có hoạt động Thiên Sứ Trao Đổi để nhận thưởng.", active_bonus[2], active_bonus[1]);
		}
		else
		{
			say_word = sprintf("Bạn vượt ải thành công, thu được" HIR "%s" NOR "Tự hào ban thưởng, hãy tới nơi có hoạt động Thiên Sứ Trao Đổi để nhận thưởng.", active_bonus[1]);
		}
		GUESS_TRUE_TIGER->delete_tigers_on_player(who, 0);
		send_user(who, "%c%s", ';', say_word);
		MAILBOX->sys_mail(who->get_id(), who->get_number(), say_word);
		who->delete ("guess_true_tiger_map");
	}
	else
	{
		_DEBUG("DEBUG -- Sai rồi! Người chơi chưa đạt được đẳng cấp ban thưởng khi vượt ải!");
	}
}
//	隔段时间回调下一关
void call_out_next_stage(object who)
{
	string *active_bonus, say_word;
	int level = who->get_save("guess_true_tiger");
	if (level >= 6)
	{
		active_bonus = active_bonus = GUESS_TRUE_TIGER->get_active_bonus(level);
		say_word = sprintf("Bạn vượt ải thành công, thu được %s Ngân Lượng Khóa cùng " HIR "%s" NOR "Tự hào ban thưởng, hãy tới nơi có hoạt động Thiên Sứ Trao Đổi để nhận thưởng.", active_bonus[2], active_bonus[1]);
		send_user(who, "%c%s", ';', say_word);
		MAILBOX->sys_mail(who->get_id(), who->get_number(), say_word);
	}
	else
	{
		if (get_z(who) == who->get("guess_true_tiger_map"))
		{
			if (who->get("guess_true_tiger_nojump"))
			{
				return;
			}
			GUESS_TRUE_TIGER->delete_tigers_on_player(who, 0);
			if (!who->get("now_call_out_next_stage"))
			{
				send_user(who, "%c%s", '!', sprintf("5 giây sau sẽ tiến vào tầng thứ %d .", level + 1));
				call_out("play_next_stage", 5, who, level + 1);
				call_out("thongbao", 1, who, 5, get_z(who));
				who->set("now_call_out_next_stage", 1);
			}
			else
			{
				who->add("define_tiger_attacking", 1);
				if (who->get("define_tiger_attacking") > 5)
				{
					play_next_stage(who, 7);
					who->set("define_tiger_attacking", 0);
				}
			}
		}
		else
		{
			_DEBUG("DEBUG -- Người chơi đã không còn ở nơi hoạt động");
			GUESS_TRUE_TIGER->delete_tigers_on_player(who, 0);
			play_next_stage(who, 7);
		}
	}
}
//	《真假虎王》过一关后的对白操作
void do_next_stage(object who)
{
	__FILE__->do_next_stage_reflash(who, this_object());
}
//	do_next_stage 的在线更新函数
void do_next_stage_reflash(object who, object me)
{
	int id = getoid(me);
	int level = who->get_save("guess_true_tiger");
	if (level > 0)
	{
		if (level < 6)
		{
			send_user(who, "%c%s", ':', sprintf("Bạn vượt ải thành công, muốn tiếp tục ải thứ %d chứ? Nếu như thất bại, bạn sẽ mất đi tất cả phần thưởng, nhưng nếu vượt được ải thành công thì phần thưởng phong phú hơn nhiều.\n" ESC "Tiếp tục \ndesc tiger_next\n" ESC "Từ bỏ \ndesc tiger_drop\n", level + 1));
		}
		else
		{
			give_up_the_activity(who);
		}
	}
}
//	《真假虎王》相关对话操作
void do_tiger_active(string arg)
{
	__FILE__->do_tiger_active_reflash(this_object(), arg);
}
//	《真假虎王》活动在线更新函数
void do_tiger_active_reflash(object me, string arg)
{
	object who, *tmp_team;
	string say_word;
	int flag, id, level, iTime, iDay;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);
	iDay = mxTime[TIME_YDAY];
	who = this_player();
	flag = to_int(arg);
	id = getoid(me);

	switch (flag)
	{
	case 1: //	主对白
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n Thật giả Hổ Vương là một hoạt động cần vượt qua nhiều ải, ngươi có thể tìm hiểu nó tại chỗ ta.\n" ESC "Nói rõ về hoạt động Phần 1 \ntalk %x# tiger.2\n" ESC "Nói rõ về hoạt động Phần 2 \ntalk %x# tiger.22\n" ESC "Tham gia hoạt động \ntalk %x# tiger.3\n" ESC "Rời đi", me->get_name(), id, id, id));
		break;
	case 2: //	活动说明
		//	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n Hoạt động Thật giả Hổ Vương cần tham gia một mình, không thể tổ đội, lệ phí vào là 10000 Ngân Lượng.\n    Khi tiến vào phía sau bản đồ, trước mặt ngươi sẽ xuất hiện bảy Boss Hổ có sức mạnh khác biệt Hổ Vương, ngươi có thể chọn lựa một Boss tiến hành chiến đấu, đánh bại Hổ Vương thì qua một cửa.\n    7 Hổ Vương trong ải thứ nhất chỉ có 1 boss siêu cường, 6 Boss còn lại rất dễ đánh bại, 7 Hổ Vương bên trong ải thứ hai chỉ 2 Boss siêu cường, 5 Boss còn lại rất dễ đánh bại, cứ thế mà suy ra, ải thứ 6 sẽ có 6 boss siêu cường và 1 boss bình thường.\n    Nếu như ngươi có thể liên tục qua 6 ải, ngươi liền có thể đạt được ban thưởng chí cao, đương nhiên, ngươi cũng có thể từ bỏ giữa chừng, qua ải nào nhận thưởng của ải đó, nhưng nếu như ngươi vượt ải thất bại, ngươi sẽ không thu được bất kì phần thưởng nào.\n" ESC "Rời đi", me->get_name()));
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n Hoạt động Thật giả Hổ Vương cần tham gia một mình, không thể tổ đội, lệ phí vào là 10000 Ngân Lượng.\nKhi tiến vào phía sau bản đồ, trước mặt ngươi sẽ xuất hiện bảy Boss Hổ có sức mạnh khác biệt Hổ Vương, ngươi có thể chọn lựa một Boss tiến hành chiến đấu, đánh bại Hổ Vương thì qua một cửa.\n" ESC "Rời đi", me->get_name()));

		break;
	case 22: //	活动说明
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n 7 Hổ Vương trong ải thứ nhất chỉ có 1 boss siêu cường, 6 Boss còn lại rất dễ đánh bại, 7 Hổ Vương bên trong ải thứ hai chỉ 2 Boss siêu cường, 5 Boss còn lại rất dễ đánh bại, cứ thế mà suy ra, ải thứ 6 sẽ có 6 boss siêu cường và 1 boss bình thường.\n    Nếu như ngươi có thể liên tục qua 6 ải, ngươi liền có thể đạt được ban thưởng chí cao, đương nhiên, ngươi cũng có thể từ bỏ giữa chừng, qua ải nào nhận thưởng của ải đó, nhưng nếu như ngươi vượt ải thất bại, ngươi sẽ không thu được bất kì phần thưởng nào.\n" ESC "Rời đi", me->get_name()));
		///	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n Hoạt động Thật giả Hổ Vương cần tham gia một mình, không thể tổ đội, lệ phí vào là 10000 Ngân Lượng.\n" ESC "Rời đi", me->get_name()));

		break;
	case 3: //	参加活动
		if (mxTime[TIME_WDAY] != 0 && mxTime[TIME_WDAY] != 6)
		{
			send_user(who, "%c%s", '!', "Chỉ có thể tham gia Mini Game vào Thứ 7, Chủ Nhật.");
			return;
		}
		if (GUESS_TRUE_TIGER->is_in_active_area())
		{
			level = who->get_save("guess_true_tiger");
			if (level > 1)
			{
				say_word = "Ngươi lần trước vượt quan ban thưởng còn không có nhận lấy, nhất định phải lần nữa đi vào khiêu chiến sao? Dạng này sẽ để cho ngươi mất đi lần trước ban thưởng!";
			}
			else
			{
				say_word = "Khiêu chiến Hổ Vương cần lệ phí 10000 Ngân Lượng, sau khi tiến vào trường cảnh của hoạt động cũng có thể nhờ sự giúp đỡ của bằng hữu!";
			}
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n%s\n" ESC "Khiêu chiến \ntalk %x# tiger.4\n" ESC "Rời đi", me->get_name(), say_word, id));
		}
		// else
		// {
		// 	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n Hiện tại không thể tham gia Thật Giả Hổ Vương, %s mới là thời gian hoạt động.\n" ESC "Rời đi", me->get_name(), GUESS_TRUE_TIGER->get_active_time()));
		// }
		break;
	case 4: //	选择挑战
		if (mxTime[TIME_WDAY] != 0 && mxTime[TIME_WDAY] != 6)
		{
			send_user(who, "%c%s", '!', "Chỉ có thể tham gia Mini Game vào Thứ 7, Chủ Nhật.");
			return;
		}
		if (GUESS_TRUE_TIGER->is_in_active_area())
		{
			tmp_team = who->get_team();

			if (who->get_save("gtt.day") == iDay)
			{

				send_user(who, "%c%s", '!', "Hôm nay bạn đã tham gia rồi.");
				return;
			}
			if (tmp_team != 0 && sizeof(tmp_team) > 1)
			{
				send_user(who, "%c%s", '!', "Ngài đang trong đội ngũ, không thể tham gia hoạt động");
				return;
			}
			else
			{
				if (who->get_cash() >= 10000)
				{
					GUESS_TRUE_TIGER->active_main_logic(who, 1);
				}
				else
				{
					send_user(who, "%c%s", '!', "Ngân Lượng của ngài không đủ 10000");
				}
			}
		}
		// else
		// {
		// 	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n Hiện tại còn không thể tham gia thật giả Hổ Vương, %s Mới là thời gian hoạt động.\n" ESC "Rời đi", me->get_name(), GUESS_TRUE_TIGER->get_active_time()));
		// }
		break;
	}
	return;
}
void thongbao(object who, int sec, int z)
{
	object npc, item;
	int i, x, y, p, exp, cashkhoa;
	sec -= 1;

	//send_user(get_range_object_2(who, 10, USER_TYPE), "%c%c%d%s", 0x43, 10, who->get_number(), CHAT + HIR "Phó bản Loạn Sơn Kê" HIG " có thời gian là 1 phút 30 giây, trong thời gian	quy định càng bắt được nhiều " HIR "Sơn Kê" HIG " càng tích được nhiều điểm.");
	//CHAT_D->sys_channel(0, HIR "Phó bản Loạn Sơn Kê" HIG " có thời gian là 1 phút 30 giây, trong thời gian	quy định càng bắt được nhiều " HIR "Sơn Kê" HIG " càng tích được nhiều điểm.");
	if (who)
	{
		if (get_z(who) != z)
		{
			remove_call_out("thongbao");
			return;
		}

		if (sec > 0)
		{
			tell_user(who, "Phó bản sẽ bắt đầu sau %d giây", sec);
			call_out("thongbao", 1, who, sec, z);
			return;
		}
		else
		{
			remove_call_out("thongbao");
			return;
		}
	}
	else
	{
		remove_call_out("thongbao");
		return;
	}
	return;
}
