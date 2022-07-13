#include <ansi.h>
#include <npc.h>
#include <effect.h>

// 函数:生成二进制码
void SAVE_BINARY() {}

mapping PlaceIndex =
	(["Tân Thủ Thôn":({0, 1}), // 前面是序号, 后面是场景编号
			   "Tề Quốc":({1, 10}),
			  "Hàn Quốc":({2, 20}),
			"Triệu Quốc":({3, 30}),
			 "Ngụy Quốc":({4, 40}),
			  "Tần Quốc":({5, 50}),
			   "Sở Quốc":({6, 60}),
			  "Yên Quốc":({7, 70}),
			  "Chu Quốc":({8, 80}),
		"Đào Hoa Nguyên":({9, 289}),
			  "Thục Sơn":({10, 273}),
			 "Đường Môn":({11, 324}),
			  "Côn Luân":({12, 54}),
			   "Mao Sơn":({13, 269}),
		  "Vân Mộng Cốc":({14, 165}),
		   "Cấm Vệ Quân":({15, 80}),
]);

mapping CountryIndex =
	(["Tân Thủ Thôn":({0, 1}), // 前面是序号, 后面是场景编号
		   "Tề Quốc":({1, 10}),
		  "Hàn Quốc":({2, 20}),
		"Triệu Quốc":({3, 30}),
		 "Ngụy Quốc":({4, 40}),
		  "Tần Quốc":({5, 50}),
		   "Sở Quốc":({6, 60}),
		  "Yên Quốc":({7, 70}),
		  "Chu Quốc":({8, 80}),
]);

int *TravelMoney = ({
	0,
	1200,
	700,
	1600,
	1100,
	1300,
	300,
	1600,
	1,
	800,
	1400,
	1100,
	1700,
	700,
	400,
	1,
	1200,
	0,
	500,
	900,
	400,
	1500,
	900,
	900,
	800,
	1200,
	900,
	900,
	1900,
	700,
	1400,
	800,
	700,
	500,
	0,
	900,
	400,
	1300,
	400,
	900,
	600,
	700,
	700,
	400,
	1700,
	800,
	900,
	600,
	1600,
	900,
	900,
	0,
	500,
	600,
	1300,
	800,
	500,
	800,
	700,
	1300,
	1000,
	1600,
	1700,
	500,
	1100,
	400,
	400,
	500,
	0,
	1100,
	700,
	500,
	400,
	1000,
	400,
	700,
	1500,
	1100,
	1200,
	400,
	1300,
	1500,
	1300,
	600,
	1100,
	0,
	1400,
	1600,
	700,
	1000,
	1300,
	1700,
	400,
	1800,
	1900,
	700,
	300,
	900,
	400,
	1300,
	700,
	1400,
	0,
	1200,
	600,
	500,
	1100,
	800,
	1400,
	400,
	500,
	600,
	1600,
	900,
	900,
	800,
	500,
	1600,
	1200,
	0,
	900,
	1500,
	300,
	1200,
	1700,
	1600,
	1700,
	900,
	1,
	800,
	600,
	500,
	400,
	700,
	600,
	900,
	0,
	300,
	800,
	1000,
	800,
	1400,
	1100,
	1,
	800,
	1200,
	700,
	800,
	1000,
	1000,
	500,
	1500,
	300,
	0,
	0,
	0,
	0,
	0,
	0,
	300,
	1400,
	900,
	700,
	700,
	400,
	1300,
	1100,
	300,
	800,
	0,
	0,
	0,
	0,
	0,
	0,
	800,
	1100,
	900,
	400,
	1300,
	700,
	1700,
	800,
	1200,
	1000,
	0,
	0,
	0,
	0,
	0,
	0,
	1000,
	1700,
	1900,
	1700,
	1000,
	1500,
	400,
	1400,
	1700,
	800,
	0,
	0,
	0,
	0,
	0,
	0,
	800,
	700,
	700,
	800,
	1600,
	1100,
	1800,
	400,
	1600,
	1400,
	0,
	0,
	0,
	0,
	0,
	0,
	1400,
	400,
	1400,
	900,
	1700,
	1200,
	1900,
	500,
	1700,
	1100,
	0,
	0,
	0,
	0,
	0,
	0,
	1100,
	1,
	800,
	600,
	500,
	400,
	700,
	600,
	900,
	1,
	300,
	800,
	1000,
	800,
	1400,
	1100,
	1,
});

int get_from_to_money(string place1, string place2)
{
	int index1, index2;
	int *message;
	if (place1 == place2)
		return 0;
	index1 = index2 = 0;
	message = PlaceIndex[place1];
	if (sizeof(message) > 1)
		index1 = message[0];
	message = PlaceIndex[place2];
	if (sizeof(message) > 1)
		index2 = message[0];
	if (sizeof(TravelMoney) > index1 * 16 + index2)
		return TravelMoney[index1 * 16 + index2];
	else
		return 0;
}

string *get_place_name()
{
	return ({"Tề Quốc", "Hàn Quốc", "Triệu Quốc", "Ngụy Quốc", "Tần Quốc", "Sở Quốc", "Yên Quốc", "Chu Quốc", "Tân Thủ Thôn", "Đào Hoa Nguyên", "Thục Sơn", "Đường Môn", "Côn Luân", "Mao Sơn", "Vân Mộng Cốc", "Cấm Vệ Quân"});
}

// 从国家到其他国家以及门派
void do_look(object npc, object who)
{
	string *name, tmp = "";
	int id = getoid(npc);
	name = get_place_name();
	name -= ({npc->get_city_name()});
	/*	
        if( present("钱票", who, 1, MAX_CARRY) )
        {
                send_user(who, "%c%s", '!', "带着钱票不能旅行.");
//              write_user(me, ECHO "……可是没有任何效果.");
                return ;
        }
*/
	if (present("Vật Phẩm Quý Bấu", who, 1, MAX_CARRY * 4))
	{
		send_user(who, "%c%s", '!', "Mang theo Vật Phẩm Quý Bấu không thể truyền tống.");
		//              write_user(me, ECHO "……可是没有任何效果.");
		return;
	}
	name -= ({0});
	if (!objectp(present("Chiến Quốc Bảo Điển", who, 1, MAX_CARRY)))
	{
		tmp = ESC "Nhận lãnh Chiến Quốc Bảo Điển\n" + sprintf("talk %x# goto.dict\n", id);
	}
	//	if (sizeof(name)==15) {
	send_user(who, "%c%s", ':', sprintf(" %s :\n " + "/quest/word"->get_normal_word(npc) + "\n Vị này " + NPC_RANK_D->get_respect(who) + " muốn đi đâu?\n"

											ESC "" +
											name[0] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[0]) + ESC "" + name[1] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[1]) + ESC "" + name[2] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[2]) + ESC "" + name[3] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[3]) + ESC "" + name[4] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[4]) + ESC "" + name[5] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[5]) + ESC "" + name[6] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[6]) + ESC "" + name[7] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[7]) + ESC "" + name[8] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[8]) + ESC "" + name[9] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[9]) + ESC "" + name[10] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[10]) + ESC "" + name[11] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[11]) + ESC "" + name[12] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[12]) + ESC "" + name[13] + "\n" + sprintf("talk %x# goto.? %s\n", id, name[13]) +

											//                ESC "打开传送地图\n"+sprintf("talk %x# goto.map\n",id)+
											ESC "Lấy " + npc->get_city_name() + " làm nơi trở lại thành.\n" + sprintf("talk %x# goto.here\n", id) + tmp + ESC "Rời khỏi.\nCLOSE\n",
										npc->get_name()));
	//	}
}

// 从门派到国家（不能到其他门派）
void do_look2(object npc, object who)
{
	string place1, place2;
	string index1, index2;
	string tmp = "";
	int money;
	int id = getoid(npc);
	place1 = npc->get_fam_name();
	if (place1 == "Cấm Vệ Quân")
		place1 = "Chu Quốc";
	/*	
        if( present("钱票", who, 1, MAX_CARRY) )
        {
                send_user(who, "%c%s", '!', "带着钱票不能旅行.");
//              write_user(me, ECHO "……可是没有任何效果.");
                return ;
        }
*/
	if (present("Vật Phẩm Quý Bấu", who, 1, MAX_CARRY * 4))
	{
		send_user(who, "%c%s", '!', "Mang.");
		//              write_user(me, ECHO "……可是没有任何效果.");
		return;
	}
	switch (who->get_latest_city() / 100)
	{
	case 10:
		place2 = "Tề Quốc";
		break;
	case 20:
		place2 = "Hàn Quốc";
		break;
	case 30:
		place2 = "Triệu Quốc";
		break;
	case 40:
		place2 = "Ngụy Quốc";
		break;
	case 50:
		place2 = "Tần Quốc";
		break;
	case 60:
		place2 = "Sở Quốc";
		break;
	case 70:
		place2 = "Yên Quốc";
		break;
	case 80:
		place2 = "Chu Quốc";
		break;
	default:
		place2 = "Tân Thủ Thôn";
		break;
	}
	if (!objectp(present("Chiến Quốc Bảo Điển", who, 1, MAX_CARRY)))
	{
		tmp = ESC "Nhận lãnh Chiến Quốc Bảo Điển\n" + sprintf("talk %x# go.dict\n", id);
	}
	money = get_from_to_money(place1, place2);
	if (npc->get_fam_name() == who->get_fam_name() || who->get_fam_name() == "" || who->get_fam_name() == 0)
		send_user(who, "%c%s", ':', " " + npc->get_name() + " :\n " + NPC_RANK_D->get_respect(who) + " muốn về " + place2 + " phải không ? Ta có thể giúp người chuyện này.\n" ESC "Chấp nhận\n" + sprintf("talk %x# go\n", id) + tmp + ESC "Rời khỏi\nCLOSE\n");
	else
		send_user(who, "%c%s", ':', sprintf(" " + npc->get_name() + " :\n " + NPC_RANK_D->get_respect(who) + " muốn về " + place2 + " phải không ? Ta chỉ lấy %d lượng thôi.\n" ESC "Chấp nhận\n" + sprintf("talk %x# go\n", id) + tmp + ESC "Rời khỏi\nCLOSE\n", money));
}

// 函数:对话处理
void do_goto(object npc, object who, string arg)
{
	object map, npc2, item;
	string *cmd;
	string place;
	int id = getoid(npc);
	int *message, money, *p, p2, x, y, z;
	arg = replace_string(arg, "?", "? ");
	arg = replace_string(arg, "!", "! ");
	cmd = explode(arg, "  ");
	if (cmd[0] == "here")
	{
		z = get_z(who);
		if (p2 = get_jumpin(z, 10))
		{
			who->set_latest_city(z * 100 + 10);
			write_user(who, ECHO "Bạn thiết lập nơi này là địa điểm trở về thành.\n");
		}
		return;
	}
	if (cmd[0] == "map")
	{
		send_user(who, "%c%c%s", 0xa5, 4, sprintf("talk %x# goto.? ", id));
		return;
	}
	if (cmd[0] == "dict")
	{
		if (objectp(item = "/quest/zg_dict"->want_an_zgdict(npc, who)))
		{
			p2 = item->move(who, -1);
			item->add_to_user(p2);
			send_user(who, "%c%s", '!', "Ngươi đạt được Chiến Quốc Bảo Điển");
		}
		return;
	}
	if (sizeof(cmd) != 2)
		return;
	if (get_effect(who, EFFECT_TRAVEL))
	{
		send_user(who, "%c%s", '!', "Bạn đang truyền tống");
		return;
	}
	/*	
        if( present("钱票", who, 1, MAX_CARRY) )
        {
                send_user(who, "%c%s", '!', "带着钱票不能旅行.");
//              write_user(me, ECHO "……可是没有任何效果.");
                return ;
        }
*/
	if (present("Vật Phẩm Quý Bấu", who, 1, MAX_CARRY * 4))
	{
		send_user(who, "%c%s", '!', "Mang theo Vật Phẩm Quý Bấu không thể truyền tống.");
		//              write_user(me, ECHO "……可是没有任何效果.");
		return;
	}
	place = npc->get_city_name();
	money = get_from_to_money(place, cmd[1]);
	if (money == 0)
		return;
	if (cmd[0] == "?")
	{
		send_user(who, "%c%s", ':', sprintf(" %s :\n Vị " + NPC_RANK_D->get_respect(who) + " này , đi " + cmd[1] + " cần %d lượng, ngươi có ý kiến gì không?\n" ESC "Tốt , không có vấn đề gì\n" + sprintf("talk %x# goto.! %s\n", id, cmd[1]) + ESC "Rời khỏi.\nCLOSE\n", npc->get_name(), money));
	}
	if (cmd[0] != "!")
		return;
	if (who->get_cash() < money)
	{
		send_user(who, "%c%s", ':', npc->get_name() + ":\n Vị " + NPC_RANK_D->get_respect(who) + " này, không đủ ngân lượng làm sao đi?\n");
		return;
	}
	if (who->get_level() < 10)
	{
		send_user(who, "%c%s", '!', "Đẳng cấp của bạn quá thấp, không thích hợp với những con đường gồ ghề.");
		return;
	}
	if (objectp(npc2 = who->get_quest("escort.robber#")) && npc2->is_escort_robber()) // 寻找蒙面人
	{
		send_user(who, "%c%s", '!', npc2->get_name() + " xuất hiện, hành động bị ảnh hưởng.");
		return;
	}
	message = PlaceIndex[cmd[1]];
	if (sizeof(message) == 2)
	{
		z = message[1];
		if (message[0] < 8)
			p = ({get_jumpin(z, 10), get_jumpin(z, 11)});
		else if (message[0] == 8)
			p = ({get_jumpin(z, 10)});
		else
			p = ({get_jumpin(z, 20)});
		p -= ({0});
		if (sizeof(p) && (p2 = p[random(sizeof(p))]))
		{
			send_user(who, "%c%c%w%s", 0x5a, 0, 3, "Đang di chuyển……");
			who->set_2("travel.z", z);
			who->set_2("travel.p", p2);
			who->set_2("travel.money", money);
			set_effect(who, EFFECT_TRAVEL, 3);
		}
	}
}

void into_effect(object who)
{
	int z, p2, money;
	object map, npc2, map1;
	z = who->get_2("travel.z");
	p2 = who->get_2("travel.p");
	money = who->get_2("travel.money");
	if (z == 0)
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}
	who->delete_2("travel");

	if (who->get_level() < 10 && who->get("familyuse") == 0)
	{
		send_user(who, "%c%s", '!', "Đẳng cấp của bạn quá thấp, không thích hợp với những con đường gồ ghề.");
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}
	if (objectp(npc2 = who->get_quest("escort.robber#")) && npc2->is_escort_robber()) // 寻找蒙面人
	{
		send_user(who, "%c%s", '!', npc2->get_name() + " xuất hiện, hành động bị ảnh hưởng.");
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}
	send_user(who, "%c%c%c", 0x5a, 1, 1);
	/*        
        if( present("钱票", who, 1, MAX_CARRY) )
        {
                send_user(who, "%c%s", '!', "带着钱票不能旅行.");
//              write_user(me, ECHO "……可是没有任何效果.");
                return ;
        }
*/
	if (present("Vật Phẩm Quý Bấu", who, 1, MAX_CARRY * 4))
	{
		send_user(who, "%c%s", '!', "Mang theo Vật Phẩm Quý Bấu không thể truyền tống.");
		//              write_user(me, ECHO "……可是没有任何效果.");
		return;
	}
	map1 = get_map_object(get_z(who));
	who->add_to_scene(z, p2 / 1000, p2 % 1000, get_d(who), 40971, 0, 40971, 0);
	if ((map = get_map_object(z)) && (money > 0))
	{
		if (map1 && map1->is_changping())
		{
			CHAR_CHAR_D->init_loop_perform(who);
			CHAR_CHAR_D->send_loop_perform(who, get_scene_object_2(who, USER_TYPE)); // 显示持续效果
		}
		write_user(who, ECHO "Ngươi tốn %d lượng phí đi lại %s .\n", money, map->get_name());
		who->add_cash(-money);
		who->add_gold_log("pay", money);
		who->log_money("Dịch Trạm", -money);
		"/sys/sys/count"->add_use("travel", money);
	}
	if (who->get("familyuse")) //使用门派信物
		who->set("familyuse", 0);
	// 去掉帮派处的影响
	who->set_2("jiguan.z", 0);
	who->set_2("jiguan.x", 0);
	who->set_2("jiguan.y", 0);
}

void effect_break(object who)
{
	set_effect(who, EFFECT_TRAVEL, 0);
	send_user(who, "%c%c%c", 0x5a, 1, 0);
	who->delete_2("travel");

	if (who->get("familyuse"))
	{
		who->set("familyuse", 0);
		who->set_save_2("familyuse", 0);
		send_user(who, "%c%c%c%w", 0x30, 0, 8, 0);
	}
}

// 从门派到国家（不能到其他门派）
void do_goto2(object npc, object who, string arg)
{
	string place1, place2;
	string index1, index2;
	object npc2, item;
	int money, p, z, x, y;
	int id = getoid(npc);
	if (arg == "dict")
	{
		if (objectp(item = "/quest/zg_dict"->want_an_zgdict(npc, who)))
		{
			p = item->move(who, -1);
			item->add_to_user(p);
			send_user(who, "%c%s", '!', "Ngươi đạt được Chiến Quốc Bảo Điển");
		}
		return;
	}
	place1 = npc->get_fam_name();
	if (place1 == "Cấm Vệ Quân")
		place1 = "Chu Quốc";
	switch (who->get_latest_city() / 100)
	{
	case 10:
		place2 = "Tề Quốc";
		break;
	case 20:
		place2 = "Hàn Quốc";
		break;
	case 30:
		place2 = "Triệu Quốc";
		break;
	case 40:
		place2 = "Ngụy Quốc";
		break;
	case 50:
		place2 = "Tần Quốc";
		break;
	case 60:
		place2 = "Sở Quốc";
		break;
	case 70:
		place2 = "Yên Quốc";
		break;
	case 80:
		place2 = "Chu Quốc";
		break;
	default:
		place2 = "Tân Thủ Thôn";
		break;
	}
	if (who->get_level() < 10)
	{
		send_user(who, "%c%s", '!', "Đẳng cấp của bạn quá thấp, không thích hợp với những con đường gồ ghề.");
		return;
	}
	if (objectp(npc2 = who->get_quest("escort.robber#")) && npc2->is_escort_robber()) // 寻找蒙面人
	{
		send_user(who, "%c%s", '!', "Người lạ xuất hiết, hành động bị ảnh hưởng.");
		return;
	}
	money = get_from_to_money(place1, place2);
	if (npc->get_fam_name() != who->get_fam_name() && who->get_fam_name() != 0 && who->get_fam_name() != "")
	{
		if (who->get_cash() < money)
		{
			send_user(who, "%c%s", ':', npc->get_name() + ":\n Vị " + NPC_RANK_D->get_respect(who) + " này, không đủ ngân lượng làm sao đi?\n");
			return;
		}
	}
	else
		money = 0;
	p = who->get_latest_city();
	if (p == 0)
		p = 110;
	z = p / 100;
	p = get_jumpin(z, p % 100);
	if (p)
	{
		send_user(who, "%c%c%w%s", 0x5a, 0, 3, "Đang di chuyển……");
		who->set_2("travel.z", z);
		who->set_2("travel.p", p);
		who->set_2("travel.money", money);
		set_effect(who, EFFECT_TRAVEL, 3);
		return;
	}
	else
	{
		write_user(who, ECHO "Không hiệu quả.....");
		return;
	}
}