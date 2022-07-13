#include <ansi.h>
#include <item.h>
#include <time.h>
#include <equip.h>
#include <task.h>
#include <effect.h>
#include <skill.h>

inherit DBASE_F;
inherit SAVE_F;
#define EBA "npc/task/8300"
int iMarry;
int iDivorce1, iDivorce2, i214, iStart214, iFinish214, close_val, open_val;
static int host_type;

object check_marry(object me, object who);
object check_divorce(object me, object who);
void marry(object npc, object who, object user);
void force_divorce(object me, object who);
void divorce(object me, object who, object user);
object check_task(object me, object who);
void accept_task(object me, object who, object user);
void task_bonus(object me, object who);
void init_npc(object npc);
void force_divorce_time(object me, object who);

// 函数:生成二进制码
void SAVE_BINARY() {}
string get_save_file() { return "data/marry" SAVE_EXTENSION; }

void create()
{
	restore();
	host_type = MAIN_D->get_host_type();
	iStart214 = mktime(2007, 2, 14, 0, 0, 0);
	iFinish214 = mktime(2007, 2, 14, 23, 59, 59);
}

void do_look(object me, object who)
{
	int id;
	string result = "";
	object item;
	i214 = time();
	id = getoid(me);
	if (!close_val && who->get_level() >= 10 && who->get_quest("valentine.flag") == 0 && ((i214 > iStart214 && i214 < iFinish214) || open_val) && who->get_gender() == 1 && !objectp(item = present("月老给的包裹", who, 1, MAX_CARRY)))
		result = sprintf(ESC HIY "情人节活动\ntalk %x# welcome.214\n", getoid(me));
	if (who->get_quest("valentine.flag") == 3 && objectp(item = present("神秘的种子", who, 1, MAX_CARRY)))
		result = sprintf(ESC HIY "求索\ntalk %x# welcome.217\n", getoid(me));
	if (who->get_quest("valentine.flag") == 4 && !objectp(item = present("神秘的种子", who, 1, MAX_CARRY)))
		result = sprintf(ESC HIY "爱情之花\ntalk %x# welcome.219\n", getoid(me));
	if (who->get_legend(TASK_2_00, 23) && !who->get_legend(TASK_2_00, 24) && who->get_save("baifang_ms_4") != 1)
		result = sprintf(ESC HIY "拜访\ntalk %x# welcome.15\n", getoid(me));
	if (who->get_save_2("qixi.flag") == 1 && i214 < "sys/party/qixi"->get_qixi_time())
		result = sprintf(ESC HIY "七夕天赐奇缘\ntalk %x# qixi.16\n", getoid(me));

	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
			  me->get_name() + " :\n Hữu duyên thiên lý năng tương ngộ, Vô duyên đối diện bất tương phùng!! ngươi đến tìm ông già này có việc gì không? Có phải ngươi đã gặp người mình yêu? Haha……Vậy ông già này sẽ nói chuyện với ngươi!\n" + result + sprintf(ESC "Ta muốn hiểu rõ chuyện kết hôn\ntalk %x# welcome.1\n", id) + sprintf(ESC "Ta muốn hiểu rõ chuyện ly hôn\ntalk %x# welcome.2\n", id) + sprintf(ESC "Con muốn kết hôn, xin Nguyệt Lão làm người chứng hôn cho tụi con\ntalk %x# welcome.3\n", id) + sprintf(ESC "Con muốn đến làm thủ tục ly hôn\ntalk %x# welcome.4\n", id)
				  //+ sprintf(ESC"强制Ly Hôn过去3天\ntalk %x# welcome.13\n",id)
				  //+ sprintf(ESC"强制Ly Hôn过去10天\ntalk %x# welcome.14\n",id)
				  + ESC "Rời khỏi");
}

void do_welcome(object me, object who, string arg)
{
	int flag, i, size, p;
	string *name, tmp, name214_1;
	object user, item, item214_1;
	i214 = time();
	flag = to_int(arg);
	who->set_time("talk", 0);
	switch (flag)
	{
	case 1:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Kết hôn yêu cầu hai người yêu nhau phải lập tổ đội và nam sẽ là đội trưởng, hai người phải mặc áo cưới và phải cùng 1 loại Truyền Thống hoặc Hiện Đại, cấp bậc cả hai phải trên 40.");
		break;
	case 2:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ly hôn phân chia thành Tình Nguyện Ly Hôn và Bắt Buộc Ly Hôn.Tình Nguyện Ly Hôn: hai vợ chồng phải cùng nhau đến và đồng ý ly hôn thì sẽ lập tức giải trừ quan hệ vợ chồng. Bắt Buộc Ly Hôn: yêu cầu chỉ một người dù là vợ hoặc chồng đến làm giấy phép ly hôn nhưng phải tiêu hao 1 triệu ngân lượng.");
		break;
	case 3:
		if (MAIN_D->get_host_type() == 6012)
		{
			send_user(who, "%c%%s", ':', "婚姻系统尚未开放!");
			return;
		}
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  me->get_name() + ":\n    Ngươi muốn thật sự Kết hôn phải không? thế thì hãy chừa chỗ trống trong hành trang ta có quà chúc phúc cho 2 ngươi đây !\n" + sprintf(ESC "Xác nhận\ntalk %x# welcome.5\n", getoid(me)) + ESC "Rời khỏi");
		who->delete ("marry.wait");
		break;
	case 4:
		if (!who->get_save_2("marry"))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Không kết hôn sẽ không phải ràng buộc!!");
			return;
		}
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  me->get_name() + ":\n    Ngươi đã cảm thấy quan hệ vợ chồng bắt đầu rạn nứt rồi chăng? Nếu thế thì yêu nhau chi bằng không quen biết nhau ! Ngươi xác định ly hôn không?\n" + sprintf(ESC "Tình Nguyện Ly Hôn\ntalk %x# welcome.7\n", getoid(me)) + sprintf(ESC "Bắt Buộc Ly Hôn\ntalk %x# welcome.8\n", getoid(me)) + ESC "Rời khỏi");

		break;
	case 5:
		if (MAIN_D->get_host_type() == 6012)
		{
			send_user(who, "%c%%s", ':', "婚姻系统尚未开放!");
			return;
		}
		if (!objectp(user = check_marry(me, who)))
			return;
		send_user(user, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  sprintf("%s\n    Ngươi nguyện ý %s %s không? (chừa ô trống trong hành trang,ta có quà cho ngươi !)\n", me->get_name(), user->get_gender() == 1 ? "lấy" : "gả cho", who->get_name()) + sprintf(ESC "Xác nhận\ntalk %x# welcome.6\n" ESC "Rời khỏi", getoid(me)));
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Xin đợi đối phương trả lời");
		who->set("marry.waitfor", user);
		user->set("marry.reply", who);
		break;
	case 6:
		if (MAIN_D->get_host_type() == 6012)
		{
			send_user(who, "%c%%s", ':', "婚姻系统尚未开放!");
			return;
		}
		user = who;
		if (!objectp(who = user->get("marry.reply")))
			return;
		if (user != who->get("marry.waitfor"))
			return;
		who->delete ("marry.waitfor");
		user->delete ("marry.reply");
		if (!objectp(user = check_marry(me, who)))
			return;
		marry(me, who, user);
		break;
	case 7:
		if (!objectp(user = check_divorce(me, who)))
			return;
		send_user(user, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  sprintf("%s\n    %s với ngươi tình nguyện ly hôn,ngươi đồng ý không ?\n", me->get_name(), who->get_name()) + sprintf(ESC "Xác nhận\ntalk %x# welcome.9\n" ESC "Rời khỏi", getoid(me)));
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Xin đợi đối phương trả lời");
		who->set("divorce.waitfor", user);
		user->set("divorce.reply", who);

		break;
	case 8:
		if (!who->get_save_2("marry"))
			return;
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  me->get_name() + ":\n    Ngươi xác định ly hôn bắt buộc không ?\n" + sprintf(ESC "Xác nhận\ntalk %x# welcome.11\n", getoid(me)) + ESC "Rời khỏi");
		break;
	case 9:
		user = who;
		if (!objectp(who = who->get("divorce.reply")))
			return;
		if (user != who->get("divorce.waitfor"))
			return;
		who->delete ("divorce.waitfor");
		user->delete ("divorce.reply");
		if (!objectp(user = check_divorce(me, who)))
			return;
		divorce(me, who, user);
		break;
	case 10:
		force_divorce_time(me, who);
		break;
	case 11:
		force_divorce(me, who);
		break;
		// case 13:
		//	who->set_save_2("marry.divorcetime",time()-3600*24*3);
		//	break;
		// case 14:
		//	who->set_save_2("marry.divorcetime",time()-3600*24*10);
		//	break;
	case 15:
		if (who->get_legend(TASK_2_00, 23) && !who->get_legend(TASK_2_00, 24) && who->get_save("baifang_ms_4") != 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王叫你来拜访我吗?你可以看看现在和将来在我这会有什么需要的, 呵呵.年轻人, 有朝气, 真好啊.\n", me->get_name()));
			who->set_save("baifang_ms_4", 1);
			USER_TASK_D->send_task_intro(who, 2, TID_ZHOUGUO, 21);
		}
		if (who->get_save("baifang_ms_1") == 1 && who->get_save("baifang_ms_2") == 1 && who->get_save("baifang_ms_2") == 1 && who->get_save("baifang_ms_3") == 1 && who->get_save("baifang_ms_4") == 1 && who->get_save("baifang_ms_5") == 1)
		{
			who->set_legend(TASK_2_00, 24);
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_ZHOUGUO, 21, "访问周国名士(完成)");
		}
		break;
	case 214:
		if (!close_val && who->get_level() >= 10 && who->get_quest("valentine.flag") == 0 && ((i214 > iStart214 && i214 < iFinish214) || open_val) && who->get_gender() == 1 && !objectp(item = present("月老给的包裹", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  sprintf("%s:\n    2月14是一个很神奇的日子, 据说在这期间内, 心怀爱意的小伙子凭借自己的诚心和实力, 就有可能得到不同寓意的玫瑰.\n" ESC "神秘的种子\ntalk %x# welcome.215\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
		}
		break;

	case 215:
		if (!close_val && who->get_level() >= 10 && who->get_quest("valentine.flag") == 0 && ((i214 > iStart214 && i214 < iFinish214) || open_val) && who->get_gender() == 1 && !objectp(item = present("月老给的包裹", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  sprintf("%s:\n    既然如此, 那你就去找唐老爷子求取传说中神秘的种子吧!顺便帮我把这个包裹带给唐老爷子, 记住这个包裹可是千万不能打开的喔!\n" ESC "接受任务\ntalk %x# welcome.216\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
		}
		break;

	case 216:
		if (!close_val && who->get_level() >= 10 && who->get_quest("valentine.flag") == 0 && ((i214 > iStart214 && i214 < iFinish214) || open_val) && who->get_gender() == 1 && !objectp(item = present("月老给的包裹", who, 1, MAX_CARRY)))
		{
			item214_1 = new ("/item/04/0420"); //情人节包裹
			name214_1 = "/item/04/0411";
			if (item214_1)
			{
				if (USER_INVENTORY_D->can_carry(who, item214_1) >= 1)
				{
					p = item214_1->move(who, -1);
					item214_1->add_to_user(p);
					send_user(who, "%c%s", '!', "得到" HIR "包裹" NOR "一个");
					who->set_quest("valentine.name", name214_1);
					who->set_quest("valentine.flag", 1);
					send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_VALENTINE, "情人节任务");
					send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_VALENTINE, 1, "神秘的种子");
					send_user(who, "%c%s", '!', "你领取了情人节任务————神秘的种子!");
				}
				else
				{
					destruct(item214_1);
					send_user(who, "%c%s", '!', "您身上没有空位!");
				}
			}
		}
		break;

	case 217:
		if (who->get_quest("valentine.flag") == 3 && objectp(item = present("神秘的种子", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  sprintf("%s:\n    Tiểu tử, ta hiểu rồi, ngươi làm rất tốt! Cụ thể là như thế nào ta cũng không rõ, nhưng ta chưa nghĩ ra ai có thể nói cho ngươi biết, nên ngươi đến đây sau vậy nhé!\n" ESC "Hoàn Thành Nhiệm Vụ\ntalk %x# welcome.218\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
		}
		break;

	case 218:
		if (who->get_quest("valentine.flag") == 3 && objectp(item = present("神秘的种子", who, 1, MAX_CARRY)))
		{
			if (!objectp(item214_1 = present("神秘的种子", who, 1, MAX_CARRY)))
			{
				send_user(who, "%c%s", '!', "您身上没有神秘的种子");
				return;
			}
			item214_1->remove_from_user();
			destruct(item214_1);
			who->add_exp(500);
			who->set_quest("valentine.flag", 4);

			send_user(who, "%c%c%c%w%w%w%s", 0x51, 1, 4, TID_VALENTINE, 3, 0, "");
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_VALENTINE, 3, "");
			send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_VALENTINE, "");
		}
		break;
	case 219:
		if (who->get_quest("valentine.flag") == 4 && !objectp(item = present("神秘的种子", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  sprintf("%s:\n    Ta nhớ ra rồi! Nghe nói Tân Thủ Thôn có Trí Tuệ Lão Nhân biết mọi chuyện trên thiên hạ, người hãy đi hỏi hắn một chút, có lẽ hắn biết làm cho hoa này nở. Người cầm loại hoa này đi tìm hắn, để rõ hơn.\n" ESC "Tiếp nhận nhiệm vụ\ntalk %x# welcome.220\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
		}
		break;
	case 220:
		if (who->get_quest("valentine.flag") == 4 && !objectp(item = present("神秘的种子", who, 1, MAX_CARRY)))
		{
			item214_1 = new ("/item/04/0421"); //神秘的种子
			name214_1 = "/item/04/0414";
			if (item214_1)
			{
				if (USER_INVENTORY_D->can_carry(who, item214_1) >= 1)
				{
					p = item214_1->move(who, -1);
					item214_1->add_to_user(p);
					send_user(who, "%c%s", '!', "得到" HIR "神秘的种子" NOR "一袋");
					who->set_quest("valentine.name", name214_1);
					send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_VALENTINE, "Nhiệm vụ lễ tình nhân");
					send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_VALENTINE, 4, "爱情之花");
					send_user(who, "%c%s", '!', "你领取了情人节任务————爱情之花!");
				}
				else
				{
					destruct(item214_1);
					send_user(who, "%c%s", '!', "Trên người không còn chỗ trống!");
				}
			}
		}
		break;
	}
}

object check_marry(object me, object who)
{
	object *team, user;
	string leader;

	if (who->get_save_2("marry"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngươi đã kết hôn rồi, vì vậy không thể làm thủ tục kết hôn");
		return 0;
	}
	if (who->get_level() < 40)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Tuổi còn nhỏ đã nghĩ đến chuyện hôn nhân ? 2 người cùng làm thủ tục kết hôn phải đạt trên cấp 40 nhá !");
		return 0;
	}
	if (!who->get_save_2("marry_fashion"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngươi không có áo cưới, hãy mặc áo cưới rồi lại đến làm lễ Cưới hỏi !");
		return 0;
	}

	if (!arrayp(team = who->get_team()) || sizeof(team) == 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngươi thật biết nói đùa, một mình ngươi thì đòi kết hôn với ai !");
		return 0;
	}
	if (sizeof(team) > 2)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Rốt cuộc người nào mới là vợ ngươi, suy nghĩ kĩ rồi lại đến !");
		return;
	}
	if (!stringp(leader = who->get_leader()) || to_int(leader) != who->get_number())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Muốn kết hôn không ? Hãy lập tổ đội với vợ ngưoi rồi đến đây");
		return;
	}
	team -= ({who});
	user = team[0];
	if (user->get_gender() == who->get_gender())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Hai người là Gay hay là Les đây, ôi thật là.....haizzzzzz.");
		return;
	}
	/*	if ( (user->get_gender()==1) && (who->get_gender()==1) )
	{
		send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name()+":\n    Hai người là Gay à, ôi thật là.....haizzzzzz.");
		return ;
	}*/
	if (!inside_screen_2(who, user))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Muốn kết hôn không ? Hãy lập tổ đội với vợ ngưoi rồi đến đây");
		return;
	}

	if (user->get_save_2("marry"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Đối phương đã kết hôn rồi, vì vậy không thể làm thủ tục kết hôn");
		return;
	}
	if (user->get_level() < 40)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Tuổi còn nhỏ đã nghĩ đến chuyện hôn nhân ? 2 người cùng làm thủ tục kết hôn phải đạt trên cấp 40 nhá !");
		return 0;
	}
	if (!user->get_save_2("marry_fashion"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Đối phương không có áo cưới, phải mặc áo cưới mới có thể làm lễ Cưới hỏi !");
		return 0;
	}
	if (user->get_save_2("marry_fashion.type") != who->get_save_2("marry_fashion.type"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Hai người mặc 2 loại áo cưới khác nhau, ta nghĩ mắt thẩm mĩ của hai ngươi về việc đám cưới quá tệ !!!.");
		return;
	}

	return user;
}
// cùng nhau ly hôn检查
object check_divorce(object me, object who)
{
	object user;
	if (!who->get_save_2("marry"))
	{
		return 0;
	}
	user = find_player(sprintf("%d", who->get_save_2("marry.id")));
	if (!user)
		return 0;
	if (user->get_leader() != sprintf("%d", who->get_number()))
		return 0;
	if (!user->get_save_2("marry"))
		return 0;
	if (user->get_save_2("marry.id") != who->get_number())
		return 0;
	if (!inside_screen_2(who, user))
		return 0;
	return user;
}

//结婚
void marry(object npc, object who, object user)
{
	int iTime, p;
	string cSpecial;
	object item, item1;
	mixed mxTime;

	if (who->get_cash() < 1000000)
	{
		send_user(who, "%c%s", ':', "Ngân lượng không đủ 1.000.000 lượng");
		return;
	}

	iTime = time();
	mxTime = localtime(iTime);
	cSpecial = sprintf("%s|%s|%d|%d|%d", who->get_name(), user->get_name(), mxTime[TIME_YEAR], mxTime[TIME_MON] + 1, mxTime[TIME_MDAY]);
	who->add_cash(-1000000);
	who->log_money("Kết Hôn", -1000000);
	"/sys/sys/count"->add_use("Kết Hôn", 1000000);

	who->set_save_2("marry.name", user->get_name());
	who->set_save_2("marry.account", user->get_id());
	who->set_save_2("marry.id", user->get_number());
	who->set_save_2("marry.time", iTime);
	if (who->get_gender() == 1)
	{
		who->add_title("M001");
		who->show_title("M001");
	}
	else
	{
		who->add_title("M002");
		who->show_title("M002");
	}
	send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 5914, 3, OVER_BODY, PF_ONCE);
	send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 5916, 3, OVER_BODY, PF_ONCE);
	send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 5917, 3, OVER_BODY, PF_ONCE);
	send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 5915, 4, OVER_BODY, PF_ONCE);
	user->set_save_2("marry.name", who->get_name());
	user->set_save_2("marry.account", who->get_id());
	user->set_save_2("marry.id", who->get_number());
	user->set_save_2("marry.time", iTime);
	if (user->get_gender() == 1)
	{
		user->add_title("M001");
		user->show_title("M001");
	}
	else
	{
		user->add_title("M002");
		user->show_title("M002");
	}
	send_user(get_scene_object_2(user, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(user), 5914, 3, OVER_BODY, PF_ONCE);
	send_user(get_scene_object_2(user, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(user), 5916, 3, OVER_BODY, PF_ONCE);
	send_user(get_scene_object_2(user, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(user), 5917, 3, OVER_BODY, PF_ONCE);
	send_user(get_scene_object_2(user, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(user), 5915, 4, OVER_BODY, PF_ONCE);
	item = new ("item/08/0005");
	item->set_amount(10);
	item->set("special", cSpecial);
	p = item->move(who, -1);
	if (!p)
	{
		send_user(who, "%c%s", '!', "Hành trang không đủ chỗ, không thể nhận Hỷ Đường !");
		destruct(item);
	}
	else
	{
		send_user(who, "%c%s", '!', "Bạn nhận được 10 cái Hỷ Đường !");
		item->add_to_user(p);
	}

	item = new ("item/08/0005");
	item->set_amount(10);
	item->set("special", cSpecial);
	p = item->move(user, -1);
	if (!p)
	{
		send_user(user, "%c%s", '!', "Hành trang không đủ chỗ, không thể nhận Hỷ Đường !");
		destruct(item);
	}
	else
	{
		send_user(user, "%c%s", '!', "Bạn nhận được 10 cái Hỷ Đường !");
		item->add_to_user(p);
	}
	iMarry++;
	save();
	send_user(who, "%c%c%w%s", ':', 3, npc->get_char_picid(), npc->get_name() + ":\n    Chúc 2 ngươi bạc đầu giai lão, vĩnh kết đồng tâm !");
	send_user(user, "%c%c%w%s", ':', 3, npc->get_char_picid(), npc->get_name() + ":\n    Chúc 2 ngươi bạc đầu giai lão, vĩnh kết đồng tâm !");
	CHAT_D->sys_channel(0, sprintf(HIY "%s" HIG " cùng " HIY "%s" HIG " đã kết thành vợ chồng, trở thành %d con người mới!Chúng ta chúc phúc cho họ bách niên giai lão,vĩnh kết đồng tâm!", who->get_name(), user->get_name(), iMarry));
	who->log_legend(sprintf("Bạn cùng %s(%d) kết hôn", user->get_name(), user->get_number()));
	user->log_legend(sprintf("Bạn cùng %s(%d) kết hôn", who->get_name(), who->get_number()));
	log_file("marry.txt", sprintf("%s %s(%s %d) %s(%s %d) Kết Hôn %d\n", short_time(), who->get_name(), who->get_id(), who->get_number(), user->get_name(), user->get_id(), user->get_number(), iMarry));
}
// cùng nhau ly hôn
void divorce(object me, object who, object user)
{
	object item;

	who->delete_save_2("marry");
	if (who->get_gender() == 1)
		who->delete_title("M001");
	else
		who->delete_title("M002");

	item = who->get_equip(HAND_TYPE); //去掉同心锁
	if (!item || item->get_name() != "Khóa Đồng Tâm")
	{
		item = present("Khóa Đồng Tâm", who, 0, MAX_CARRY * 4);
		if (item && item->get_item_type() == ITEM_TYPE_TALISMAN)
		{
			item->remove_from_user();
			destruct(item);
		}
	}
	else
	{
		item->remove_from_user();
		destruct(item);
	}

	user->delete_save_2("marry");
	if (user->get_gender() == 1)
		user->delete_title("M001");
	else
		user->delete_title("M002");

	item = user->get_equip(HAND_TYPE); //去掉同心锁
	if (!item || item->get_name() != "Khóa Đồng Tâm")
	{
		item = present("Khóa Đồng Tâm", user, 0, MAX_CARRY * 4);
		if (item && item->get_item_type() == ITEM_TYPE_TALISMAN)
		{
			item->remove_from_user();
			destruct(item);
		}
	}
	else
	{
		item->remove_from_user();
		destruct(item);
	}

	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ly hôn thành công !");
	send_user(user, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ly hôn thành công !");
	iDivorce1++;
	save();
	log_file("marry.txt", sprintf("%s %s(%s %d) %s(%s %d) cùng nhau ly hôn %d\n", short_time(), who->get_name(), who->get_id(), who->get_number(), user->get_name(), user->get_id(), user->get_number(), iDivorce1));
	who->log_legend(sprintf("Bạn cùng %s(%d) ly hôn", user->get_name(), user->get_number()));
	user->log_legend(sprintf("Bạn cùng %s(%d) ly hôn", who->get_name(), who->get_number()));
}
//设置强制Ly Hôn确认时间
void force_divorce_time(object me, object who)
{
	int iTime;
	if (!mapp(who->get_save_2("marry")))
		return;
	iTime = who->get_save_2("marry.divorcetime");
	if (!iTime || gone_time(iTime) > 3600 * 24 * 10)
	{
		who->set_save_2("marry.divorcetime", time());
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngươi phải biết quý trọng hôn nhân ! Ta cho ngươi 3 ngày suy nghĩ để xem ngươi còn ý định lý hôn hay không !");
		log_file("marry.txt", sprintf("%s %s(%s %d)  Bắt buộc ly hôn\n", short_time(), who->get_name(), who->get_id(), who->get_number()));
		return;
	}
	else if (is_god(who) || (iTime && gone_time(iTime) > 3600 * 24 * 3 && gone_time(iTime) < 3600 * 24 * 10))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  me->get_name() + ":\n    Trải qua mấy ngày ngươi cũng không hồi tâm chuyển ý, ngươi muốn ly hôn phải không ?\n" + sprintf(ESC "Xác nhận\ntalk %x# welcome.11\n", getoid(me)) + ESC "Rời khỏi");
		return;
	}
	else if (iTime && gone_time(iTime) < 3600 * 24 * 3)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ba ngày ta cho ngươi để suy nghĩ vẫn chưa hết !");
		return;
	}
}
//强制Ly Hôn
void force_divorce(object me, object who)
{
	int flag, id;
	string account, cName;
	object user, item;
	mapping mpTmp;

	mpTmp = who->get_save_2("marry");
	if (!mapp(mpTmp))
		return;

	account = mpTmp["account"];
	cName = mpTmp["name"];
	id = mpTmp["id"];
	user = find_player(sprintf("%d", id));
	if (!user)
	{
		if ("sys/sys/user2"->check_id_online(id) != 0)
		{
			send_user(who, "%c%s", '!', " Người chơi này đang ở khác kênh với bạn. Người chơi phải đăng xuất hoặc ở cùng kênh với bạn !");
			return;
		}
		if (!user_exist(mpTmp["account"]))
		{
			flag = -1;
		}
		else
		{
			user = new (USER);
			user->set_id(account);
			if (!user->restore())
				destruct(user);
			else
				flag = 1; // restore的
		}
	}
	if (user && user->get_number() == id) //结婚的对象存在
	{
		if (who->get_cash() < 1000000)
		{
			send_user(who, "%c%s", '!', "Ngân lượng không đủ 1.000.000 lượng !");
			if (flag == 1)
				destruct(user);
			return;
		}
		who->add_cash(-1000000);
		who->log_money("Ly Hôn", -1000000);
		"/sys/sys/count"->add_use("Ly Hôn", 1000000);
	}
	who->delete_save_2("marry");
	if (who->get_gender() == 1)
		who->delete_title("M001");
	else
		who->delete_title("M002");

	/*	item = who->get_equip(HAND_TYPE);//去掉同心锁
	if ( !item || item->get_name() != "Khóa Đồng Tâm" )
	{
		item = present("Khóa Đồng Tâm",who,0,MAX_CARRY*4);
		if ( item && item->get_item_type() == ITEM_TYPE_TALISMAN )
		{
			item->remove_from_user();
			destruct(item);
		}
	}
	else
	{
		item->remove_from_user();
		destruct(item);
	}
	*/
	if (user && user->get_number() == id) //结婚的对象存在
	{
		user->delete_save_2("marry");
		if (flag == 0) //去掉同心锁
		{
			if (user->get_gender() == 1)
				user->delete_title("M001");
			else
				user->delete_title("M002");

			/*	item = user->get_equip(HAND_TYPE);
			if ( !item || item->get_name() != "Khóa Đồng Tâm" )
			{
				item = present("Khóa Đồng Tâm",user,0,MAX_CARRY*4);
				if ( item && item->get_item_type() == ITEM_TYPE_TALISMAN )
				{
					item->remove_from_user();
					destruct(item);
				}
			}
			else
			{
				item->remove_from_user();
				destruct(item);
			}	*/
		}
		user->log_legend(sprintf("%s(%d) cùng ngươi bắt buộc ly hôn", who->get_name(), who->get_number()));
		if (flag == 1)
			user->save();
	}
	if (flag == 1)
		destruct(user);
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ly hôn thành công !");
	MAILBOX->sys_mail(account, id, sprintf("%s đã cùng ngươi ly hôn !", who->get_name()));
	iDivorce2++;
	save();
	log_file("marry.txt", sprintf("%s %s(%s %d) %s(%s %d) ly hôn %d\n", short_time(), who->get_name(), who->get_id(), who->get_number(), cName, account, id, iDivorce2));
	who->log_legend(sprintf("Bạn cùng %s(%d) bắt buộc ly hôn", cName, id));
}
//红娘的对话
void do_look1(object me, object who)
{
	int id;
	string cmd, result;
	object item;
	i214 = time();
	cmd = "";
	result = "";
	id = getoid(me);
	if (!close_val && ((i214 > iStart214 && i214 < iFinish214) || open_val) && who->get_level() >= 10 && who->get_gender() != 1 && who->get_quest("valentine.type") != 1 && who->get_quest("valentine.flag") == 0)
		result = sprintf(ESC HIY "Hoạt động Lễ Tình Nhân\ntalk %x# welcome.214\n", getoid(me));
	if (who->get_quest("valentine.flag") == 7 && objectp(item = present("巧克力豆", who, 1, MAX_CARRY)))
		result = sprintf(ESC HIY "巧克力豆\ntalk %x# welcome.217\n", getoid(me));
	if (who->get_quest("valentine.flag") == 8 && !objectp(item = present("巧克力豆", who, 1, MAX_CARRY)))
		result = sprintf(ESC HIY "情人节巧克力\ntalk %x# welcome.219\n", getoid(me));
	if (who->get_legend(TASK_2_00, 23) && !who->get_legend(TASK_2_00, 24) && who->get_save("baifang_ms_5") != 1)
		result = sprintf(ESC HIY "Bái kiến\ntalk %x# welcome.11\n", getoid(me));
	if (who->get_save_2("marrytask"))
		cmd = sprintf(ESC "Dạy dỗ %s\ntalk %x# welcome.9\n", who->get_save_2("marrytask.name"), id);
	else if (who->get_save_2("marry"))
		cmd = sprintf(ESC "Chúng ta tới nhận nhiệm vụ vợ chồng\ntalk %x# welcome.2\n", id);

	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
			  me->get_name() + " :\n Ngươi tìm bổn cô nương có gì không? Ta chỉ dẫn đường dẫn lối cho người có duyên thôi!\n" + sprintf(ESC "Ta muốn tìm hiểu nhiệm vụ của hôn nhân\ntalk %x# welcome.1\n", id) + sprintf(ESC "Cùng nhau thu phục Khóa Đồng Tâm\ntalk %x# welcome.?\n", id) + cmd + result + ESC "Rời khỏi");
}

void do_welcome1(object me, object who, string arg)
{
	int flag, i, p, size;
	string *name, tmp;
	object user, item, item214_1;
	i214 = time();
	flag = to_int(arg);
	who->set_time("talk", 0);
	switch (flag)
	{
	case 1:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Nhiệm vụ vợ chồng là do người chơi kết hôn mới nhận được, chỉ nhận nhiệm vụ vợ chồng khi vợ chồng cùng đồng ý song kiếm hợp bích và cùng họp thành một đội. Khi hoàn thành nhiệm vụ hãy tới chỗ ta trả, ta sẽ đưa cho vợ chồng ngươi một pháp bảo đó là Khóa Đồng Tâm! Nhiệm vụ thất bại thì cũng có thể hủy bỏ và trở lại, sau hai giờ nhận lại!");
		break;
	case 2:
		if (!who->get_save_2("marry"))
			return;
		if (who->get_save_2("marry.task"))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngươi đã giúp ta nhiều rồi, xin cảm phiền làm phiền ngươi lần nữa!");
			return;
		}
		if (gone_time(who->get_save("marrytask.time")) < 7200)
		{
			item = who->get_equip(HAND_TYPE);
			if (item && item->get_item_number() == 10001078)
			{
				send_user(who, "%c%c%s", 0x59, 1, sprintf("Ngươi có sử dụng 'Mãn Thiên Quá Hải Phù' để làm mới thời gian??\n" ESC "%c\n" ESC "use %x# marry\n", 1, getoid(item)));
				return;
			}
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Đáng tiếc, vừa có người tới trước ngươi một bước, giúp ta dạy dỗ tên Ác Phách rồi, giờ thiên hạ thái bình, ngươi hãy trở lại sau một thời gian ngắn nữa nhé!");
			return;
		}
		if (who->get_save_2("marrytask"))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Lần trước ngươi chưa hoàn thành nhiệm vụ vợ chồng, cho nên lần này không thể nhận nhiệm vụ.");
			return;
		}
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  me->get_name() + ":\n    Gần đây có một Ác Phách, tự xưng là Thiên Hạ Đệ Nhất. Hắn hạn cho ta ba ngày nếu không rời khỏi Chu Quốc, hắn sẽ mang người đến đập ta. Ngươi có thể đi dạy dỗ hắn một trận hay không, tránh cái miệng ngông cuồng của hắn!\n" + sprintf(ESC "Tiếp Nhận\ntalk %x# welcome.3\n", getoid(me)) + ESC "Rời khỏi");
		break;
	case 3:
		if (!who->get_save_2("marry"))
			return;
		if (!objectp(user = check_task(me, who)))
			return;
		send_user(user, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  sprintf("%s\n    %s đã nhận nhiệm vụ vợ chồng, ngươi có cùng hiệp trợ không?\n", me->get_name(), who->get_name()) + sprintf(ESC "Tiếp Nhận\ntalk %x# welcome.4\n" ESC "Hủy Bỏ\ntalk %x# welcome.5\n", getoid(me), getoid(me)));
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Xin đợi đối phương trả lời.");
		who->set("marry.task", user);
		user->set("marry.task", who);
		break;
	case 4:
		user = who;
		if (!objectp(who = user->get("marry.task")))
			return;
		if (user != who->get("marry.task"))
			return;
		who->delete ("marry.task");
		user->delete ("marry.task");
		if (!objectp(user = check_task(me, who)))
			return;
		accept_task(me, who, user);
		break;
	case 5:
		user = who;
		if (!objectp(who = user->get("marry.task")))
			return;
		if (user != who->get("marry.task"))
			return;
		who->delete ("marry.task");
		user->delete ("marry.task");
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Người yêu ngươi cự tuyệt viện trợ, ngươi không thể nhận nhiệm vụ vợ chồng!");
		break;
	case 9:
		if (!who->get_save_2("marrytask"))
			return;
		if (!who->get_save_2("marry"))
		{
			who->delete_save_2("marrytask");
			who->delete_save("marrytask.time");
			return;
		}
		if (!who->get_save_2("marrytask.finish"))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Hy vọng các ngươi có thể nhanh hơn một chút!");
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  sprintf("%s\n    Vô cùng cảm tạ các ngươi đã viện trợ! Chúc các ngươi trăm năm hạnh phúc!\n", me->get_name()) + sprintf(ESC "Hoàn Thành Nhiệm Vụ\ntalk %x# welcome.10\n" ESC "Rời khỏi", getoid(me)));
		break;
	case 10:
		if (!who->get_save_2("marrytask"))
			return;
		if (!who->get_save_2("marrytask.finish"))
			return;
		task_bonus(me, who);
		break;
	case 11:
		if (who->get_legend(TASK_2_00, 23) && !who->get_legend(TASK_2_00, 24) && who->get_save("baifang_ms_5") != 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Đại Vương gọi ngươi tới bái kiến ta sao? Ta có thể thấy ngươi có tương lai sáng lạng! Trẻ tuổi và rất tài khí.\n", me->get_name()));
			who->set_save("baifang_ms_5", 1);
			USER_TASK_D->send_task_intro(who, 2, TID_ZHOUGUO, 21);
		}
		if (who->get_save("baifang_ms_1") == 1 && who->get_save("baifang_ms_2") == 1 && who->get_save("baifang_ms_2") == 1 && who->get_save("baifang_ms_3") == 1 && who->get_save("baifang_ms_4") == 1 && who->get_save("baifang_ms_5") == 1)
		{
			who->set_legend(TASK_2_00, 24);
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_ZHOUGUO, 21, "Bái Kiến Chu Quốc Danh Sĩ (Hoàn Thành)");
		}
		break;
	case 214:
		if (!close_val && ((i214 > iStart214 && i214 < iFinish214) || open_val) && who->get_level() >= 10 && who->get_gender() != 1 && who->get_quest("valentine.type") != 1 && who->get_quest("valentine.flag") == 0)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  sprintf("%s:\n    2月14是一个很神奇的日子, 据说在这期间内, 心怀爱意的小姑娘凭借自己的诚心和实力, 就有可能得到不同寓意的巧克力.\n" ESC "情人节的传说\ntalk %x# welcome.215\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
		}
		break;
	case 215:
		if (!close_val && ((i214 > iStart214 && i214 < iFinish214) || open_val) && who->get_level() >= 10 && who->get_gender() != 1 && who->get_quest("valentine.type") != 1 && who->get_quest("valentine.flag") == 0)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  sprintf("%s:\n    看来你也是一位怀抱着诚意来的姑娘, 那么, 你去桃花源找到忘情婆婆吧, 她会告诉你怎样才能得到巧克力的!\n" ESC "Tiếp nhận nhiệm vụ\ntalk %x# welcome.216\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
		}
		break;
	case 216:
		if (!close_val && ((i214 > iStart214 && i214 < iFinish214) || open_val) && who->get_level() >= 10 && who->get_gender() != 1 && who->get_quest("valentine.type") != 1 && who->get_quest("valentine.flag") == 0)
		{
			who->set_quest("valentine.flag", 5);
			who->set_quest("valentine.type", 1);
			send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_VALENTINE, "情人节任务");
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_VALENTINE, 5, "情人节的传说");
			send_user(who, "%c%s", '!', "你领取了情人节任务————情人节的传说!");
		}
		break;
	case 217:
		if (who->get_quest("valentine.flag") == 7 && objectp(item = present("巧克力豆", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  sprintf("%s:\n    这果然是上好的巧克力豆, 不过我也不太懂巧克力的做法, 等我想想谁会做再告诉你吧.\n" ESC "完成任务\ntalk %x# welcome.218\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
		}
		break;
	case 218:
		if (who->get_quest("valentine.flag") == 7 && objectp(item = present("巧克力豆", who, 1, MAX_CARRY)))
		{
			if (objectp(item214_1 = present("巧克力豆", who, 1, MAX_CARRY)))
			{
				item214_1->remove_from_user();
				destruct(item214_1);
			}
			who->set_quest("valentine.flag", 8);
			who->add_exp(500);
			send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_VALENTINE, "");
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_VALENTINE, 7, "");
		}
		break;
	case 219:
		if (who->get_quest("valentine.flag") == 8 && !objectp(item = present("巧克力豆", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  sprintf("%s:\n    我想起来了, 我记得在新手村外的西北方有一个万丈深渊, 这悬崖旁生活着一个巧克力精灵, 我想它一定会知道巧克力的做法的, 你赶紧起程去吧!\n" ESC "接受任务\ntalk %x# welcome.220\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
		}
		break;
	case 220:
		if (who->get_quest("valentine.flag") == 8 && !objectp(item = present("巧克力豆", who, 1, MAX_CARRY)))
		{
			item214_1 = new ("/item/04/0425"); //巧克力豆
			if (item214_1)
			{
				if (USER_INVENTORY_D->can_carry(who, item214_1) >= 1)
				{
					p = item214_1->move(who, -1);
					item214_1->add_to_user(p);
					send_user(who, "%c%s", '!', "得到" HIR "巧克力豆" NOR "一些");
					send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_VALENTINE, "情人节任务");
					send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_VALENTINE, 8, "情人节巧克力");
					send_user(who, "%c%s", '!', "你领取了情人节任务————情人节巧克力!");
				}
				else
				{
					destruct(item214_1);
					send_user(who, "%c%s", '!', "您身上没有空位!");
				}
			}
		}
		break;
	}
}
//检查夫妻任务
object check_task(object me, object who)
{
	object *team, user;
	string leader;

	if (!who->get_save_2("marry"))
	{
		return 0;
	}
	if (who->get_save_2("marry.task"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngươi đã trợ giúp ta rồi, rất khổ thẹn khi nhờ ngươi lần nữa!!");
		return;
	}
	if (!arrayp(team = who->get_team()) || sizeof(team) == 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngươi dẫn người yêu ngươi theo cùng đi!");
		return 0;
	}
	if (sizeof(team) > 2)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ta chỉ cung cấp cho hai vợ chồng, không có người thứ ba!“");
		return;
	}
	if (!stringp(leader = who->get_leader()) || to_int(leader) != who->get_number())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bổn cô nương chỉ cung cấp nhiệm vụ cho vợ chồng thôi!");
		return;
	}
	team -= ({who});
	user = team[0];
	if (user->get_save_2("marry.id") != who->get_number())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Các ngươi là vợ chồng sao? Ta muốn chắc đúng là như vậy!");
		return;
	}
	if (!inside_screen_2(who, user))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Ngươi dẫn người yêu ngươi theo đi!");
		return;
	}
	if (user->get_save_2("marrytask"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Bởi vì " + user->get_name() + " chưa hoàn thành nhiệm vụ vợ chồng lần trước, nên không thể nhận tiếp.");
		return;
	}
	if (gone_time(user->get_save("marrytask.time")) < 7200)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Đáng tiếc, đã có người tới trước ngươi một bước, trợ giúp ta dạy dỗ Ác Phách, bây giờ thái bình, hãy chờ một thời gian hẵng quay lại!");
		return;
	}
	return user;
}
//红娘任务
void accept_task(object me, object who, object user)
{
	int z, x, y, p, iTime, level;
	string cName;
	object npc, map;

	if (!(p = XY_D->get_city_point(-1, IS_CHAR_BLOCK)))
		return;
	z = p / 1000000;
	x = (p % 1000000) / 1000;
	y = p % 1000;
	if (!objectp(map = get_map_object(z)) || !map->is_scene())
		return;
	level = who->get_level() > user->get_level() ? who->get_level() : user->get_level();
	iTime = time();
	npc = new (EBA);
	if (!npc)
		return;
	cName = "Ác Phách" + NPC_NAME_D->get_thief_name();
	npc->set_name(cName);
	npc->set("marry1", who->get_number());
	npc->set("marry2", user->get_number());
	NPC_ENERGY_D->init_level(npc, level);
	init_npc(npc);
	npc->set_max_seek(8);

	npc->add_to_scene(z, x, y);

	who->delete_save_2("marrytask");
	who->set_save_2("marrytask.target", sprintf("%x#", getoid(npc)));
	who->set_save_2("marrytask.name", cName);
	who->set_save_2("marrytask.country", map->get_name());
	who->set_save_2("marrytask.x", x);
	who->set_save_2("marrytask.y", y);
	who->set_save_2("marrytask.x1", x + random(20));
	who->set_save_2("marrytask.y1", y + random(20));
	who->set_save_2("marrytask.time", iTime);
	who->set_save("marrytask.time", iTime);

	user->delete_save_2("marrytask");
	user->set_save_2("marrytask.target", sprintf("%x#", getoid(npc)));
	user->set_save_2("marrytask.name", cName);
	user->set_save_2("marrytask.country", map->get_name());
	user->set_save_2("marrytask.x", x);
	user->set_save_2("marrytask.y", y);
	user->set_save_2("marrytask.x1", x + random(20));
	user->set_save_2("marrytask.y1", y + random(20));
	user->set_save_2("marrytask.time", iTime);
	user->set_save("marrytask.time", iTime);

	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Hy vọng các người có thể nhanh lên một chút!");
	send_user(user, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Hy vọng các người có thể nhanh lên một chút!");

	//发送任务提示
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_HONGNIANG, "Nhiệm Vụ Hồng Nương");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_HONGNIANG, 1, "Dạy Dỗ Ác Phách");
	send_user(user, "%c%c%c%w%s", 0x51, 1, 1, TID_HONGNIANG, "Nhiệm Vụ Hồng Nương");
	send_user(user, "%c%c%c%w%w%s", 0x51, 1, 2, TID_HONGNIANG, 1, "Dạy Dỗ Ác Phách");
}

void task_bonus(object me, object who)
{
	int p;
	object item;

	if (!who->get_save_2("marrytask.finish"))
		return;
	if (!who->get_save_2("marry"))
	{
		who->delete_save_2("marrytask");
		who->delete_save("marrytask.time");
		return;
	}
	item = who->get_equip(HAND_TYPE); //去掉同心锁
	if (!item || item->get_name() != "Khóa Đồng Tâm")
	{
		item = present("Khóa Đồng Tâm", who, 0, MAX_CARRY * 4);
		if (item && item->get_item_type() == ITEM_TYPE_TALISMAN)
		{
			item->remove_from_user();
			destruct(item);
		}
	}
	else
	{
		item->remove_from_user();
		destruct(item);
	}
	item = new ("item/std/9611");
	if (!item)
		return;
	p = item->move(who, -1);
	if (!p)
	{
		destruct(item);
		send_user(who, "%c%s", '!', "Ngươi mang quá nhiều đồ!");
		return;
	}
	item->add_to_user(p);
	who->delete_save_2("marrytask");
	who->delete_save("marrytask.time");
	who->set_save_2("marry.task", time());
	send_user(who, "%c%s", ';', "Hoàn thành nhiệm vụ vợ chồng, nhận được Khóa Đồng Tâm!");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_HONGNIANG, 1, "");
}

void init_npc(object npc)
{
	int p, level;

	level = npc->get_level();
	p = random(100);
	if (p < 20) //低物防高敏型
	{
		npc->set_skill(348, level);
		npc->set_skill(251, level);
		npc->set_skill(241, level);
		npc->set_char_picid(8011);
		npc->set_walk_speed(4);
		npc->set_attack_speed(10);
		npc->add_dp(-1 * npc->get_dp() / 4);
		npc->add_max_hp(npc->get_max_hp() * 17 / 2);
		npc->add_sp(npc->get_sp() * 2);
		npc->add_ap(npc->get_ap() * 4 / 5);
		npc->add_mp(npc->get_mp() / 2);
		npc->set("marry.type", 1);
	}
	else if (p < 40) //高物防低法防型
	{
		npc->set_skill(221, level);
		npc->set_skill(231, level);
		npc->set_char_picid(0252);
		npc->set_walk_speed(4);
		npc->set_attack_speed(10);
		npc->add_dp(npc->get_dp() * 3);
		npc->add_max_hp(npc->get_max_hp() * 9 / 2);
		npc->add_pp(-1 * npc->get_pp() * 3 / 10);
		npc->add_ap(npc->get_ap() * 4 / 5);
		npc->add_mp(npc->get_mp() / 2);
		npc->set("marry.type", 2);
	}
	else if (p < 60) //高法防低物防型
	{
		npc->set_skill(424, level);
		npc->set_skill(423, level);
		npc->set_skill(425, level);
		npc->set_char_picid(8010);
		npc->set_walk_speed(4);
		npc->set_attack_speed(10);
		npc->add_dp(-1 * npc->get_dp() / 4);
		npc->add_max_hp(npc->get_max_hp() * 9 / 2);
		npc->add_sp(npc->get_sp());
		npc->add_pp(npc->get_pp() * 3 / 2);
		npc->add_cp(npc->get_cp());
		npc->add_mp(npc->get_mp() * 6);
		npc->set("marry.type", 3);
	}
	else if (p < 70) //长血型:拳脚类
	{
		npc->set_skill(317, level);
		npc->set_skill(211, level);
		npc->set_char_picid(8000);
		npc->set_walk_speed(4);
		npc->set_attack_speed(10);
		npc->add_dp(-1 * npc->get_dp() / 5);
		npc->add_max_hp(npc->get_max_hp() * 21);
		npc->add_pp(-1 * npc->get_pp() / 5);
		npc->add_cp(npc->get_cp() / 2);
		npc->add_ap(npc->get_ap() * 9 / 10);
		npc->set("marry.type", 4);
	}
	else if (p < 90) //长血高物防高法防型:远程暗器类
	{
		npc->set_skill(261, level);
		npc->set_char_picid(8012);
		npc->set_walk_speed(4);
		npc->set_attack_speed(10);
		npc->add_dp(npc->get_dp() * 9 / 20);
		npc->add_max_hp(npc->get_max_hp() * 11 / 2);
		npc->add_sp(npc->get_sp() * 3);
		npc->add_pp(npc->get_pp() * 9 / 5);
		npc->add_mp(npc->get_mp());
		npc->add_ap(npc->get_ap() / 2);
		npc->set("marry.type", 5);
	}
	else //强攻型加召唤
	{
		npc->set_skill(414, level);
		npc->set_char_picid(8013);
		npc->set_walk_speed(4);
		npc->set_attack_speed(8);
		npc->add_dp(npc->get_dp() * 9 / 20);
		npc->add_ap(npc->get_ap());
		npc->add_max_hp(npc->get_max_hp() * 11 / 2);
		npc->add_sp(npc->get_sp() * 3);
		npc->add_pp(npc->get_pp() * 9 / 20);
		npc->add_mp(npc->get_mp() * 3 / 2);
		npc->set("marry.type", 6);
	}
}
//设置情人节活动的开启和关闭
int set_valentine(int open, int close)
{
	open_val = open;
	close_val = close;
	return 1;
}