
#include <ansi.h>
#include <music.h>
#include <task.h>
#include <equip.h>
#include <time.h>
#define BANDITI "/npc/task/8200"
#define WARRIOR "/npc/task/8900"
void clear_task_desc(object who);
void send_task_list(object who);
void random_bonus(object who);

void clear_gold_task_desc(object who);
void send_gold_task_list(object who);

// 函数:生成二进制码
void SAVE_BINARY() {}

// 函数:对话处理
void do_look(object who, object me)
{
	object npc;
	string banditi, tmp = "";
	int id = getoid(me);
	string cmd1 = sprintf("talk %x# task\n", id);
	string cmd2 = sprintf("talk %x# cancel\n", id);
	string cmd3 = sprintf("talk %x# fortune\n", id);

	string cmd4 = sprintf("talk %x# gold_start\n", id);

	if (who->get_legend(TASK_NEWBIE_01, 19) && !who->get_legend(TASK_NEWBIE_01, 20))
		tmp = ESC + HIY + "牛二报恩.\n" + sprintf("talk %x# welcome.1\n", id);
	/*	if ( who->get_level()>9 && (!who->get_legend(TASK_NEWBIE_01, 23) || !who->get_legend(TASK_NEWBIE_01, 24)) )
	{
		if ( !sizeof(tmp) )
			tmp = ESC "锻炼的机会.\n" + sprintf("talk %x# welcome.3\n", id );
		else
			tmp += ESC "锻炼的机会.\n" + sprintf("talk %x# welcome.3\n", id );
	}*/
	//	if ( !who->get_legend(TASK_41, 1) || (who->get_legend(TASK_41, 2) && !who->get_legend(TASK_41, 3)) )
	if (who->get_legend(TASK_48, 19) && !who->get_legend(TASK_48, 20))
		tmp += ESC HIY "Yêu Ngôn Mị Dân.\n" + sprintf("talk %x# welcome.5\n", id);
	if (who->get_legend(TASK_48, 20) && !who->get_legend(TASK_48, 21))
		tmp += sprintf(ESC HIY "疑难杂症(1)\ntalk %x# welcome.11\n", getoid(me));
	if (who->get_legend(TASK_48, 26) && !who->get_legend(TASK_48, 27))
		tmp += sprintf(ESC HIY "Chứng Bệnh Nan Y(3)\ntalk %x# welcome.11\n", getoid(me));
	//	if ( !who->get_legend(TASK_41, 13) || (who->get_legend(TASK_41, 14) && !who->get_legend(TASK_41, 15)) )
	if (who->get_legend(TASK_48, 27) && !who->get_legend(TASK_48, 28))
		tmp += ESC HIY "装饰房屋.\n" + sprintf("talk %x# welcome.8\n", id);

	if ("sys/party/gold_warrior"->get_warrior() || who->get_task("warrior_bonus"))
		tmp += ESC HIY "Hoàng Kim Thánh Y\n" + cmd4;
	tmp += CHAIN_D->get_chain_menu(who, me);
	if (stringp(banditi = who->get_task("banditi")) && (npc = find_char(banditi)) && npc->is_banditi())
		send_user(who, "%c%s", ':', sprintf(" %s :\n Ta…..ta là…….con của …...bổn thôn thôn trưởng, cũng…..cũng là Vệ Đội Trưởng…..của bổn thôn, có…...có gì cần…..ta…...giúp à?\n" + tmp + ESC HIG "Hỗ trợ việc trị an của thôn trang.\n" + cmd2 +
												//			ESC HIY "Hoàng Kim Thánh Y\n" + cmd4 +
												ESC "Sứ mệnh vật phẩm.\n" + cmd3 + ESC "Rời khỏi.\nCLOSE\n",
											me->get_name()));
	else
		send_user(who, "%c%s", ':', sprintf(" %s :\n Ta…..ta là…….con của …...bổn thôn thôn trưởng, cũng…..cũng là Vệ Đội Trưởng…..của bổn thôn, có…...có gì cần…..ta…...giúp à?\n" + tmp + ESC HIG "Hỗ trợ việc trị an của thôn trang.\n" + cmd1 +
												//			ESC HIY "Hoàng Kim Thánh Y\n" + cmd4 +
												ESC "Sứ mệnh vật phẩm.\n" + cmd3 + ESC "Rời khỏi.\nCLOSE\n",
											me->get_name()));
}
//经验修正
int correct_exp_bonus(int level, int level2, int exp) // level: 怪, level2 : 怪 - 玩家等级
{
	level2 = abs(level2);
	level2 = 100 - level2 * 5;
	if (level2 < 20)
		level2 = 20;
	exp = exp * level2 / 100;
	return exp;
}
//治安任务的奖励
void task_bonus(object who, object me)
{
	object *team, *team2;
	string id, id2;
	int level, level2, exp, exp2, pot, pot2, knbkhoa, cashkhoa;
	int i, size;

	if (who->is_npc())
		return;

	// team = who->get_team();
	// if ((size = sizeof(team)) < 1)
	// {
	// 	team = ({who});
	// 	size = 1;
	// }

	id = sprintf("%x#", getoid(me));

	// for (i = 0, team2 = ({}); i < size; i++)
	// {
	// 	if (team[i] && team[i]->get_task("banditi_bonus"))
	// 		team2 += ({team[i]});
	// }

	// if ((size = sizeof(team = team2)) < 1)
	// 	return;

	level = who->get_task("banditi_bonus");
	if (level <= 40)
		exp = (100 + 40 * level + random(10 * level) * 7) * ((100 - size * 5) > 0 ? (100 - size * 5) : 1) / 100;
	else
		exp = (100 + 40 * level + random(10 * level)) * ((100 - size * 5) > 0 ? (100 - size * 5) : 1) / 100;
	pot = level * 3 + random(level);
	"/sys/sys/count"->add_task("Vệ Đội Trưởng tiêu diệt", 1);

	if (who->get_task("banditi_bonus") == 0)
	{
		return;
	}
	level2 = level - who->get_level();
	exp2 = correct_exp_bonus(level, level2, exp) * 2 * who->get_online_rate() / 100;
	pot2 = pot * who->get_online_rate() / 100;
	knbkhoa = 15;
	cashkhoa = 10000;
	if (who->get_save_2("banditi.solan") == 10)
	{
		knbkhoa = 65;
		cashkhoa = 30000;
	}
	who->add_exp(exp2 * 3);
	who->add_potential(pot2);
	who->add_knbkhoa(knbkhoa);
	who->add_cashkhoa(cashkhoa);
	who->add_log("&banditi", exp2);
	who->add_log("*banditi", pot2);
	who->add_log("#banditi", 1);

	send_user(who, "%c%w", 0x0d, MUSIC_TASK);
	write_user(who, ECHO "Bạn hoàn thành nhiệm vụ trị an,được %d Ngân Lượng Khóa, Kim nguyên bảo khóa %d,  Kinh nghiệm %+d， Tiềm năng %+d, lượt %d", cashkhoa, knbkhoa / 10, exp2, pot2, who->get_save_2("banditi.solan"));
	who->delete_task("banditi_bonus");
	who->delete_task("banditi_name");
	who->delete_task("banditi_map");
	who->delete_task("banditi_x");
	who->delete_task("banditi_y");
	clear_task_desc(who);
	if (random100() < (2 * who->get_online_rate() / 100))
		random_bonus(who);
}
// 函数:开始任务
void do_task_start(object who, object me)
{
	object *team, npc, map, item;
	string *member, banditi, cName;
	int level, min, max, i, size;
	int z, x, y, p, iTime, iDay;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);
	iDay = mxTime[TIME_YDAY];
	if (who->get_task("banditi_bonus"))
	{
		send_user(who, "%c%s", ':', me->get_name() + ":\n    Làm không...tồi ! Ngươi thật....thật...sự làm bản thôn...quang vinh !\n" + ESC "Hoàn thành nhiệm vụ\n" + sprintf("talk %x# bonus\n", getoid(me)) + ESC "Rời khỏi\nCLOSE\n");
		return;
	}
	if (stringp(banditi = who->get_task("banditi")) && (npc = find_char(banditi)) && npc->is_banditi())
	{
		send_user(who, "%c%s", '!', "Hãy hoàn thành nhiệm vụ trước mắt đi đã");
		return;
	}
	if (who->get_save_2("banditi.ngay") == iDay)
	{
		send_user(who, "%c%s", ':', "Hôm nay bạn đã làm đủ 10 lần rồi");
		return;
	}
	if (gone_time(who->get_task("banditi_time")) < 180)
	{
		send_user(who, "%c%s", ':', "3 phút nữa hãy quay lại!");
		return;
	}

	// if (who->get_save_2("banditi.solan") > 9)
	// {
	// 	who->set_save_2("banditi.ngay", iDay);
	// 	who->set_save_2("banditi.solan", 0);
	// 	send_user(who, "%c%s", ':', "Hôm nay bạn đã làm 10 lần rồi!");
	// 	return;
	// }
	// if (arrayp(team = who->get_team()) && !who->is_leader())
	// {
	// 	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
	// 			  sprintf("%s:\n    Ngưoi...không..không phải đội trưởng....ta...ta không thể...giao trọng ...trọng trách cho ngươi !", me->get_name()));
	// 	return;
	// }
	// if (sizeof(team) == 0)
	// 	team = ({who});
	// for (i = 0, size = sizeof(team); i < size; i++)
	// 	if (team[i])
	// 	{
	// 		if (time() - team[i]->get_task("banditi_time") > 10)
	// 			continue;
	// 		send_user(who, "%c%s", ':', "Hiện tại Thôn thái....thái bình...không cần...cần hiệp trợ trị an !");
	// 		return;
	// 	}

	//        if( stringp( banditi = who->get_task("banditi") )
	//        && ( npc = find_char(banditi) ) && npc->is_banditi() )
	//        {
	//                send_user( who, "%c%s", '!', "Hãy hoàn thành nhiệm vụ trước mắt đi đã" );
	//                return;
	//        }

	// 	level = 0;
	// 	min = 10000;
	// 	max = 0;
	// 	for (i = 0, size = sizeof(team); i < size; i++)
	// 		if (team[i])
	// 		{
	// 			if (stringp(banditi = team[i]->get_task("banditi")) && (npc = find_char(banditi)) && npc->is_banditi())
	// 			{
	// 				send_user(who, "%c%s", '!', "Hãy hoàn thành nhiệm vụ trước mắt đi !");
	// 				return;
	// 			}
	// 			p = team[i]->get_level();
	// 			if (p < min)
	// 				min = p;
	// 			if (p > max)
	// 				max = p;
	// 			level += p;
	// 		}
	// 	// 取消40级的限制
	// 	/*
	//         if( max >= 40 )
	//         {
	// 		send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
	//                 sprintf("%s:\n    这――这点小事，我――我们自己就能解决，不――不用劳――劳烦――这位%s."
	//                         , me->get_name(),NPC_RANK_D->get_respect_2(who) ) );
	//                 return;
	//         }
	// */
	// 	if (max > min + 10)
	// 	{

	// 		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
	// 				  sprintf("%s:\n    Đội ngũ các ngươi tốt xấu lẫn lộn, ta không thể giao trọng trách !", me->get_name()));
	// 		return;
	// 	}
	// p = who->get_level();
	// if (p < min)
	// 	min = p;
	// if (p > max)
	// 	max = p;
	// if (max < 40)
	// {
	if (!(p = XY_D->get_newbie_point(IS_CHAR_BLOCK)))
		return;
	z = p / 1000000;
	x = (p % 1000000) / 1000;
	y = p % 1000;
	z += get_z(me) - 1; //新手村1,2,3
	//}
	// else
	// {
	// 	z = ({1, 2, 3, 162, 10, 20, 30, 40, 50, 60, 70, 80})[random(12)];
	// 	if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
	// 		return;
	// 	x = (p % 1000000) / 1000;
	// 	y = p % 1000;
	// }

	if (!objectp(map = get_map_object(z)) || !map->is_scene())
		return;

	cName = "Thổ Phỉ" + NPC_NAME_D->get_banditi_name();
	who->set("banditi_name", cName);
	who->set("banditi_x", x);
	who->set("banditi_y", y);
	who->set("banditi_z", z);

	item = who->get_equip(HAND_TYPE);
	if (item && item->get_item_number() == 10001078)
	{
		send_user(who, "%c%s", ':', me->get_name() + sprintf(":\nCó chí khí, cái kia giận %s, hãy cho hắn biết chúng ta lợi hại !\n", cName) + ESC "Nhận\n" + sprintf("talk %x# accept\n", getoid(me)) + ESC "Rời khỏi\n" + sprintf("talk %x# welcome.cancel\n", getoid(me)));
	}
	else
	{
		send_user(who, "%c%s", ':', me->get_name() + sprintf(":\nCó chí khí, cái kia giận %s, hãy cho hắn biết chúng ta lợi hại !\n", cName) + ESC "Nhận\n" + sprintf("talk %x# accept\n", getoid(me)) + ESC "Rời khỏi\nCLOSE\n");
	}
}
void accept_task(object who, object me)
{
	object *team, npc, map;
	string *member, banditi, cName;
	int level, min, max, i, size;
	int z, x, y, p, x1, y1, iTime, iDay;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);
	iDay = mxTime[TIME_YDAY];
	// if (arrayp(team = who->get_team()) && !who->is_leader())
	// {
	// 	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
	// 			  sprintf("%s:\n    Ngươi không phải đội trưởng, ta không thể giao trọng trách cho ngươi !", me->get_name()));
	// 	return;
	// }
	// if (sizeof(team) == 0)
	// 	team = ({who});

	if (stringp(banditi = who->get_task("banditi")) && (npc = find_char(banditi)) && npc->is_banditi())
	{
		send_user(who, "%c%s", '!', "Hãy hoàn thành nhiệm vụ trước mắt đi đã");
		return;
	}
	if (gone_time(who->get_task("banditi_time")) < 180)
	{
		send_user(who, "%c%s", ':', "3 phút nữa hãy quay lại!");
		return;
	}
	if (who->get_save_2("banditi.ngay") == iDay)
	{
		send_user(who, "%c%s", ':', "Hôm nay bạn đã làm đủ 10 lần rồi");
		return;
	}

	if (who->get_save_2("banditi.solan") > 9)
	{
		who->set_save_2("banditi.ngay", iDay);
		who->set_save_2("banditi.solan", 0);
		send_user(who, "%c%s", ':', "Hôm nay bạn đã làm 10 lần rồi!");
		return;
	}
	// if (gone_time(who->get_task("banditi_time")) < 180)
	// {
	// 	send_user(who, "%c%s", ':', "3 phút nữa hãy quay lại!");
	// 	return;
	// }
	// if (who->get_save_2("banditi.ngay") == iDay)
	// {
	// 	send_user(who, "%c%s", ':', "Hôm nay bạn đã làm đủ 10 lần rồi");
	// 	return;
	// }
	// if (who->get_save_2("banditi.solan") > 9)
	// {
	// 	who->set_save_2("banditi.ngay", iDay);
	// 	who->set_save_2("banditi.solan", 0);
	// 	send_user(who, "%c%s", ':', "Hôm nay bạn đã làm 10 lần rồi!");
	// 	return;
	// }
	// level = 0;
	// min = 10000;
	// max = 0;
	// for (i = 0, size = sizeof(team); i < size; i++)
	// 	if (team[i])
	// 	{
	// 		p = team[i]->get_level();
	// 		if (p < min)
	// 			min = p;
	// 		if (p > max)
	// 			max = p;
	// 		level += p;
	// 	}
	// if (max > min + 10)
	// {

	// 	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
	// 			  sprintf("%s:\n    Đội ngũ của ngươi tốt xấu lẫn lộn, ta không thể giao trọng trách được !", me->get_name()));
	// 	return;
	// }
	level = who->get_level();

	x = who->get("banditi_x");
	y = who->get("banditi_y");
	z = who->get("banditi_z");
	cName = who->get("banditi_name");

	if (!objectp(map = get_map_object(z)) || !map->is_scene())
		return;
	/*
        for( i = 0; i < 100; i ++ )
        {
                if( p = get_valid_xy(z, abs( x + random(10) - 5 ), abs( y + random(10) - 5 ), IS_CHAR_BLOCK) )
                {
                        x1 = p / 1000;  y1 = p % 1000;  break;
                }
        }
*/
	//who->set_save_2("banditi.day", localtime(time())[7]);
	who->set_task("banditi_time", time());
	who->add_save_2("banditi.solan", 1);
	x1 = x;
	y1 = y; // 取消随机，免得进入安全区
	if (!x1 || !y1)
		return;
	npc = new (BANDITI);
	NPC_ENERGY_D->init_level(npc, level);

	npc->set_ap(npc->get_ap() * 6 / 5);
	npc->set_dp(npc->get_dp() * 2);
	npc->set_cp(npc->get_cp() * 2);
	npc->set_pp(npc->get_pp() * 2);
	npc->set_sp(npc->get_sp() * 2);
	npc->set_con(level * 3);
	npc->set_max_hp(npc->get_max_hp() * 2 + 200);
	npc->set_max_mp(npc->get_max_mp() * 2);
	npc->set_name(cName);
	npc->add_to_scene(z, x1, y1, 3);
	npc->set("level", level);

	// member = ({});
	// size = sizeof(team);

	map->add_reset(npc); // 加入复位列表

	send_user(who, "%c%c%d%s", 0x43, 7, 0,
			  sprintf(HIW "%s nói: \"ở %s(%d,%d) phụ cận có %s đang tính toán cướp thôn, hy vọng các vị đại hiệp ra tay tương trợ !\"",
					  me->get_name(), map->get_name(), x, y, npc->get_name()));
	//        send_user( team, "%c%s", '!', sprintf( "去" HIY " %s(%d,%d) " NOR "附近击杀" HIY " %s " NOR ".", map->get_name(), x, y, npc->get_name() ) );

	who->set_task("banditi", sprintf("%x#", getoid(npc)));
	npc->set("xy.z", z);
	npc->set("xy.x", x);
	npc->set("xy.y", y);
	// for (i = 0; i < size; i++)
	// 	if (team[i])
	// 	{
	// 		member += ({sprintf("%d", team[i]->get_number())});
	// 		send_task_list(team[i]);
	// 	}

	send_task_list(who);
	npc->set("user", who->get_number());
}
//任务提示
void do_task_cancel(object who, object me)
{
	object npc, map;
	string banditi;
	int time, z;

	if (!stringp(banditi = who->get_task("banditi")) || !objectp(npc = find_char(banditi)) || !npc->is_banditi())
	{
		return;
	}
	z = npc->get("xy.z");
	if (!objectp(map = get_map_object(z)) || !map->is_scene())
		return;

	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
			  sprintf("Sao, thế nào rồi có tìm được %s không? Hắn ở ngay tại %s vùng lân cận",
					  npc->get_name(), map->get_name()));
}

//函数:Vệ Đội Trưởng Hoàng Kim Thánh Y的奖励
void gold_task_bonus(object who, object me)
{
	object item;
	string id, id2;
	int level, level2, exp, exp2, title;
	int i, size;

	if (who->is_npc())
		return;
	if (!who->get_task("warrior_bonus"))
		return;
	//	level = who->get_task("warrior_bonus");
	//	exp = 35*(100+40*level+random(10*level));

	if (!objectp(item = present("Hoàng Kim Thánh Y", who, 1, MAX_CARRY)))
	{
		send_user(who, "%c%s", '!', "Hoàng Kim Thánh Y của ngươi đâu ?");
		return;
	}
	item->remove_from_user();
	destruct(item);

	"/sys/sys/count"->add_task("Vệ Đội Trưởng Hoàng Kim Thánh Y", 1);
	who->add_exp(who->get("warrior_exp"));
	"sys/sys/test_db"->add_yuanbao(who, 50);
	who->add_log("&warrior", exp);
	who->add_log("#warrior", 1);

	send_user(who, "%c%w", 0x0d, MUSIC_TASK);
	write_user(who, ECHO "Bạn hoàn thành nhiệm vụ Vệ Đội Trưởng Hoàng Kim Thánh Y, kinh nghiệm %+d, Kim Nguyên Bảo +5", who->get("warrior_exp"));
	who->delete_task("warrior_bonus");
	who->delete_task("warrior_name");
	who->delete_task("warrior_map");
	who->delete_task("warrior_x");
	who->delete_task("warrior_y");
	clear_gold_task_desc(who);

	who->add_save("warrior_title", 1);
	title = who->get_save("warrior_title");
	if ((title == 5 && !who->have_title("A009")) || (title == 10 && !who->have_title("A010")) || (title == 50 && !who->have_title("A011")) || (title == 100 && !who->have_title("A012")))
		MAILBOX->sys_mail(who->get_id(), who->get_number(), "Nhiệm vụ Hoàng Kim Thánh Y của bạn đã đạt con số nhất định, có thể đến Thiên Sứ Trao Đổi để đổi danh hiệu");
}
//函数:开始Vệ Đội Trưởng Hoàng Kim Thánh Y任务
void do_gold_task_start(object who, object me)
{
	object *team, npc, map, item;
	string *member, warrior, cName;
	int level, exp, i, size;
	int z, x, y, p;

	if (who->get_task("warrior_bonus"))
	{
		level = who->get_task("warrior_bonus");
		exp = 50 * (100 + 50 * level + random(90 * level));
		who->set("warrior_exp", exp);
		//		"sys/sys/test_db"->add_yuanbao(who,20);
		send_user(who, "%c%s", ':', me->get_name() + sprintf(":\n    Ngươi có được Hoàng Kim Thánh Y, đem đến cho ta để đổi %d kinh nghiệm và 2 Kim Nguyên Bảo\n", exp) + ESC "Hoàn thành nhiệm vụ\n" + sprintf("talk %x# gold_bonus\n", getoid(me)) + ESC "Rời khỏi\nCLOSE\n");
		return;
	}

	if (!"sys/party/gold_warrior"->get_warrior())
		return;

	if (sizeof(who->get_team()) > 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  sprintf("%s:\n    Ta chỉ muốn mình ngươi nhớ việc này, hãy đi một mình tới tìm ta !", me->get_name()));
		return;
	}

	if (stringp(warrior = who->get_task("warrior")) && (npc = find_char(warrior)) && npc->is_warrior())
	{
		send_user(who, "%c%s", '!', "Hãy hoàn thành nhiệm vụ Hoàng Kim Thánh Y đi đã");
		return;
	}
	if (who->get_level() < 40)
	{
		if (!(p = XY_D->get_newbie_point(IS_CHAR_BLOCK)))
			return;
		z = p / 1000000;
		x = (p % 1000000) / 1000;
		y = p % 1000;
		z += get_z(me) - 1; //新手村1,2,3
	}
	else
	{
		z = ({1, 2, 3, 162, 10, 20, 30, 40, 50, 60, 70, 80})[random(12)];
		if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
			return;
		x = (p % 1000000) / 1000;
		y = p % 1000;
	}

	if (!objectp(map = get_map_object(z)) || !map->is_scene())
		return;

	cName = "Đạo Tặc" + NPC_NAME_D->get_banditi_name();
	who->set("warrior_name", cName);
	who->set("warrior_x", x);
	who->set("warrior_y", y);
	who->set("warrior_z", z);
	who->set_task("warrior_time", time());
	send_user(who, "%c%s", ':', me->get_name() + sprintf(":\n    Trong " HIR "2 phút" NOR " đủ để chứng minh ngươi có thể đảm đương trọng trách này\n    Ta muốn làm vô địch Hoàng Kim Thánh Đấu Sĩ ! nghe nói giết Đạo Tặc có thể có được Hoàng Kim Thánh Y !\n") + ESC "Nhận nhiệm vụ\n" + sprintf("talk %x# gold_accept\n", getoid(me)) + ESC "Rời khỏi\nCLOSE\n");
}
//函数:接受Vệ Đội Trưởng Hoàng Kim Thánh Y任务
void accept_gold_task(object who, object me)
{
	object *team, npc, map;
	string member, warrior, cName;
	int level, min, max, i, size;
	int z, x, y, p, x1, y1;

	if (!"sys/party/gold_warrior"->get_warrior())
		return;

	if (sizeof(who->get_team()) > 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  sprintf("%s:\n    Ta chỉ muốn mình ngươi nhớ việc này, hãy đi một mình tới tìm ta !", me->get_name()));
		return;
	}

	if (stringp(warrior = who->get_task("warrior")) && (npc = find_char(warrior)) && npc->is_warrior())
	{
		send_user(who, "%c%s", '!', "Hãy hoàn thành nhiệm vụ Hoàng Kim Thánh Y đi đã");
		return;
	}

	level = who->get_level();

	x = who->get("warrior_x");
	y = who->get("warrior_y");
	z = who->get("warrior_z");
	cName = who->get("warrior_name");

	if (!objectp(map = get_map_object(z)) || !map->is_scene())
		return;
	x1 = x;
	y1 = y; // 取消随机，免得进入安全区
	if (!x1 || !y1)
		return;
	npc = new (WARRIOR);
	NPC_ENERGY_D->init_level(npc, level);

	npc->set_ap(npc->get_ap() * 6 / 5);
	npc->set_dp(npc->get_dp() * 2);
	npc->set_cp(npc->get_cp() * 2);
	npc->set_pp(npc->get_pp() * 2);
	npc->set_sp(npc->get_sp() * 2);

	npc->set_max_hp(npc->get_max_hp() * 2 + 200);
	npc->set_max_mp(npc->get_max_mp() * 2);
	npc->set_name(cName);
	npc->add_to_scene(z, x1, y1, 3);
	npc->set("level", level);

	map->add_reset(npc); // 加入复位列表

	who->set_task("warrior", sprintf("%x#", getoid(npc)));
	npc->set("xy.z", z);
	npc->set("xy.x", x);
	npc->set("xy.y", y);

	member = sprintf("%d", who->get_number());
	who->delete_task("warrior_bonus");
	send_gold_task_list(who);
	npc->set("user", member);

	send_user(who, "%c%s", ':', me->get_name() + sprintf(":\n    %s có Hoàng Kim Thánh Y ngay tại ‘%s’(%d,%d) vùng phụ cận. Ngươi hãy đi tìm Hoàng Kim Thánh Y về cho ta！\n", cName, map->get_name(), x, y) + ESC "Rời khỏi\nCLOSE\n");
}

//函数:放弃Vệ Đội Trưởng Hoàng Kim Thánh Y任务
void gold_task_giveup(object who, int iKind)
{
	object npc, item;
	string id, member;
	//	if ( who->get_task("warrior_bonus") )
	//	{
	//	 	send_user( who, "%c%s", '!', "Nhiệm vụ đã hoàn thành, quay về báo với Vệ Đội Trưởng" );
	//	 	return ;
	//	}
	if (objectp(item = present("Hoàng Kim Thánh Y", who, 1, MAX_CARRY)) && item->is_sacred_clothes())
	{
		item->remove_from_user();
		destruct(item);
	}
	clear_gold_task_desc(who);
	id = who->get_task("warrior");
	who->delete_task("warrior");
	who->delete_task("warrior_bonus");
	if (!stringp(id) || !objectp(npc = find_char(id)) || !npc->is_warrior())
	{
		return;
	}
	npc->remove_from_scene();
	destruct(npc);
}

void send_gold_task_list(object who)
{
	string id;
	object npc;

	if (who->get_task("warrior_bonus"))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_BANDITI, "Nhiệm vụ Vệ Đội Trưởng");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_BANDITI, 2, "Hoàng Kim Thánh Y(Đã hoàn thành)");
	}
	else if (stringp(id = who->get_task("warrior")) && (npc = find_char(id)) && npc->is_warrior())
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_BANDITI, "Nhiệm vụ Vệ Đội Trưởng");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_BANDITI, 2, "Hoàng Kim Thánh Y");
	}
}

void clear_gold_task_desc(object who)
{
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 3, TID_BANDITI, 2, "");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_BANDITI, 2, "");
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_BANDITI, "");
}

// 函数:取消任务
//void do_task_cancel( object who, object me )
//{
//        object *team, npc;
//        string banditi;
//        int time;
//
//        if(    !stringp( banditi = who->get_task("banditi") )
//        ||     !objectp( npc = find_char(banditi) )
//        ||     !npc->is_banditi() )
//        {
//                send_user( who, "%c%s", '!', "你们没有领取剿匪任务." );
//                return;
//        }
//
//        if( !arrayp( team = who->get_team() ) || !who->is_leader() )
//        {
//                send_user( who, "%c%s", '!', "只有队长才能取消剿匪任务." );
//                return;
//        }
//
//        if( ( time = gone_time( npc->get("birthday") ) ) < 180 )    // ３分钟
//        {
//                send_user( who, "%c%s", '!', sprintf( "还有 %d 秒才能取消剿匪任务.", 180 - time ) );
//                return;
//        }
//
////      who->add_hp( - who->get_hp() / 2 );    // 气血、法力减少一半
////      who->add_mp( - who->get_mp() / 2 );
//
//        team->delete_task("banditi");
//
//        send_user( who, "%c%s", ':', sprintf( "%s:\n我们已经将%s抓起来了，不用再劳烦你们了.\n",
//                me->get_name(), npc->get_name() ) );
//
//        npc->remove_from_scene();
//        destruct(npc);
//
//        return;
//}

// 函数:使命物品
void do_fortune(object who, object me)
{
	int i;
	string cmdl = "", cName;
	object *nObj = ({}), *inv, obj;

	inv = all_inventory(who, 1, MAX_CARRY);
	if (sizeof(inv))
	{
		foreach (obj in inv)
		{
			if (obj->is_task_item())
				nObj += ({obj});
			if (sizeof(nObj) == 3)
				break;
		}
	}
	cName = TASK_FILE->get_random_item_file();
	if (find_object(cName) || load_object(cName))
		cName = cName->get_name();
	else
		cName = "Sơn Hải Kinh";
	if (sizeof(nObj))
	{
		foreach (obj in nObj)
		{
			cmdl += ESC + sprintf("Cho %s\ngive %x# %x#%d %x#%d %x#%d %x#%d %x#%d %x#%d $%d\n",
								  obj->get_name(), getoid(me), getoid(obj), 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		}
	}
	cmdl += ESC "Rời khỏi\nCLOSE\n";
	send_user(who, "%c%s", ':', me->get_name() + ":\nNgươi có sao không ? Nghe nói \"" + cName + "\" linh tinh đông đông, ngươi có thể giúp ta tìm trở về hay không ?\n" + cmdl);
}
//放弃任务
void task_giveup(object who, int iKind)
{
	object npc, item;
	string id, *member;

	if (who->get_task("banditi_bonus"))
	{
		send_user(who, "%c%s", '!', "Nhiệm vụ đã hoàn thành, quay về báo với Vệ Đội Trưởng");
		return;
	}
	if (time() - who->get_task("banditi_time") < 10)
	{
		item = who->get_equip(HAND_TYPE);
		if (item && item->get_item_number() == 10001078)
		{
			send_user(who, "%c%c%s", 0x59, 1, sprintf("你是否使用'瞒天过海符'来消除你的任务间隔时间?\n" ESC "%c\n" ESC "use %x# banditi2\n", 1, getoid(item)));
			return;
		}
		send_user(who, "%c%s", '!', "Hãy huỷ bỏ nhiệm vụ sau !");
		return;
	}
	clear_task_desc(who);
	id = who->get_task("banditi");
	who->delete_task("banditi");

	if (!stringp(id) || !objectp(npc = find_char(id)) || !npc->is_banditi())
	{
		return;
	}
	// member = npc->get("user");
	// id = sprintf("%d", who->get_number());

	// if (sizeof(member) == 0)
	// {
	npc->remove_from_scene();
	destruct(npc);
	// }
	// else
	// 	npc->set("user", member);
}

void send_task_list(object who)
{
	string id;
	object npc;

	if (who->get_task("banditi_bonus"))
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_BANDITI, "Nhiệm vụ Vệ Đội Trưởng");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_BANDITI, 1, "Hiệp trợ trị an (Đã hoàn thành)");
	}
	else if (stringp(id = who->get_task("banditi")) && (npc = find_char(id)) && npc->is_banditi())
	{
		send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_BANDITI, "Nhiệm vụ Vệ Đội Trưởng");
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_BANDITI, 1, "Hiệp trợ trị an");
	}
}

void clear_task_desc(object who)
{
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 3, TID_BANDITI, 1, "");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_BANDITI, 1, "");
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_BANDITI, "");
}

void random_bonus(object who)
{
	int rand, i, p, total, amount;
	string result, file;
	object item;
	if (sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY)
	{
		return;
	}
	rand = random(10000);
	if (is_god(who))
	{
		if (who->get("lb") > 0)
			rand = who->get("lb");
	}
	if (rand < 1000)
		item = new ("/item/std/8000");
	else if (rand < 1060)
		item = new (sprintf("/item/91/%d", 9160 + random(6)));
	else if (rand < 1070)
		item = new ("/item/91/9167");
	else if (rand < 1170)
		item = new ("/item/01/0202");
	else if (rand < 1370)
		item = new ("/item/01/0201");
	else if (rand < 1670)
		item = new ("/item/01/0200");
	else if (rand < 1724)
	{
		if (random(2))
			file = ARMOR_FILE->get_armor_file(who->get_level());
		else
			file = WEAPON_FILE->get_weapon_file(who->get_level());
		if (load_object(file))
		{
			item = new (file);
		}
	}
	else if (rand < 3094)
	{
		who->add_cash(5000);
		result = "5000 lượng";
	}
	else if (rand < 3194)
	{
		who->add_cash(10000);
		result = "10000 lượng";
	}
	else if (rand < 3294)
	{
		item = new ("/item/std/5216");
		item->set_amount(30);
	}
	else if (rand < 3394)
	{
		item = new ("/item/std/5211");
		item->set_amount(30);
	}
	else if (rand < 3395)
		item = new (sprintf("/item/93/%d", 9301 + random(10)));
	else if (rand < 3400)
		item = new ("/item/44/4488");
	else if (rand < 4300)
	{
		item = new ("/item/91/9101");
		item->set_amount(8);
	}
	else if (rand < 5200)
	{
		item = new ("/item/91/9111");
		item->set_amount(8);
	}
	else if (rand < 7600)
	{
		item = new (sprintf("/item/32/%d", 3280 + random(4)));
		item->set_amount(30);
	}
	else
	{
		item = new (sprintf("/item/31/%d", 3150 + random(4)));
		item->set_amount(30);
	}
	if (item)
	{
		result = item->get_name();
		if (item->get_max_combined() > 1)
		{
			total = item->get_amount();
			amount = USER_INVENTORY_D->carry_combined_item(who, item, total);
			if (amount > 0 && item->set_amount(amount))
			{
				if (p = item->move(who, -1))
				{
					item->add_to_user(p);
				}
			}
			else
				item->add_amount(-total);
		}
		else
		{
			if (p = item->move(who, -1))
			{
				item->add_to_user(p);
			}
		}
	}
	if (result == "")
	{
		who->add_cash(5000);
		result = "5000 lượng";
	}

	send_user(who, "%c%s", ';', "Bạn hoàn thành nhiệm vụ, nhận được " + result + " phần thưởng ngoài ý muốn");
}