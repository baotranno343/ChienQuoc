#include <ansi.h>
#include <effect.h>
#include <skill.h>
#include <city.h>
#include <time.h>

inherit ITEM;

int get_item_value() { return 5; }
int get_item_value_2() { return 5; }
int get_item_number() { return 10001034; }
int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
	set_name("锦囊");
	set_picid_1(7113);
	set_picid_2(7113);
	set_value(50);
	set_record(1);
	// -- 与原装备相比增加绑定属性
	set_no_give(1);
	set_no_sell(1);
	//
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Dodolook的小口袋，能从口袋里掏出很多不一样的道具，让你惊喜连连。";
}

string get_short()
{
	return "打开后能让你获得意想不到的惊喜的小布袋。";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object item)
{
	mixed *mixTime;
	string result, file;
	int *card = ({
		0902,
		0950,
		0951,
		0952,
		0953,
		0954,
		1000,
		1001,
		1050,
		1051,
		1052,
		1100,
		1101,
		1102,
		4141,
		4142,
		4143,
		4145,
		8000,
		8012,
		8013,
	});
	int rand, p, total, amount, i, flag;
	object *allitem, *user, item2, item3, item4;
	mixTime = localtime(time());
	if (who->get_save_2("item41.day") == mixTime[TIME_YDAY] && who->get_save_2("item41.time") >= 50)
	{
		send_user(who, "%c%s", ';', "每个人每天只有50次使用锦囊的机会。");
		return 0;
	}
	if (who->get_online_rate() < 100)
	{
		send_user(who, "%c%s", ';', "非健康时间不能使用锦囊");
		return 0;
	}
	if (sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY - 5)
	{
		send_user(who, "%c%s", '!', "您需预备六个空间。");
		return 0;
	}
	result = sprintf("使用消失 %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), "", item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(who), get_x(who), get_y(who));
	//"/sys/user/cmd"->log_item(result);
	item->remove_from_user();
	destruct(item);
	if (who->get_save_2("item41.day") != mixTime[TIME_YDAY])
	{
		who->set_save_2("item41.day", mixTime[TIME_YDAY]);
		who->set_save_2("item41.time", 1);
	}
	else
		who->add_save_2("item41.time", 1);
	result = "";
	// 鼓励奖
	item = 0;
	flag = 0;
	rand = random(10000);
	if (is_god(who))
	{
		if (who->get("lb") > 0)
			rand = who->get("lb");
	}
	if (rand < 905)
	{
		who->add_cash(30000);
		result = "30000金";
	}
	else if (rand < 1705)
	{
		who->add_cash(35000);
		result = "35000金";
	}
	else if (rand < 2705)
	{
		if (random(2))
			file = ARMOR_FILE->get_armor_file_3(20, 60);
		else
			file = WEAPON_FILE->get_weapon_file_3(20, 60);
		if (load_object(file))
		{
			item = new (file);
		}
	}
	else if (rand < 3305)
	{
		item = new ("/item/91/9101");
		item->set_amount(30);
	}
	else if (rand < 4015)
	{
		item = new ("/item/stuff/0230");
		item->set_amount(30);
	}
	else if (rand < 4425)
	{
		item = new ("/item/stuff/0009");
		item->set_amount(30);
	}
	else if (rand < 4825)
	{
		item = new ("/item/stuff/0288");
		item->set_amount(20);
	}
	else if (rand < 5225)
	{
		item = new ("/item/stuff/0318");
		item->set_amount(15);
	}
	else if (rand < 6725)
		item = new (sprintf("/item/final/15/%d", 1500 + random(6)));
	else if (rand < 6925)
		item = new ("/item/sell/0012");
	else if (rand < 7085)
	{
		if (random(2))
			file = ARMOR_FILE->get_armor_file_3(20, 60);
		else
			file = WEAPON_FILE->get_weapon_file_3(20, 60);
		if (load_object(file))
		{
			item = new (file);
			ITEM_EQUIP_D->init_equip_prop_1(item);
		}
	}
	else if (rand < 7130)
		item = new (sprintf("/item/93/%d", 9301 + random(10)));
	else if (rand < 7170)
		item = new (sprintf("/item/54/%04d", card[random(sizeof(card))]));
	else if (rand < 7200)
		item = new ("/item/08/0001");
	else if (rand < 7240)
		item = new ("/item/08/0002");
	else if (rand < 7260)
		item = new ("/item/08/0003");
	else if (rand < 7280)
		item = new ("/item/08/0004");
	else if (rand < 7325)
		item = new (BOOK_FILE->get_book_file());
	else if (rand < 7375)
		item = new ("/item/sell/0033");
	else if (rand < 7405)
		item = new ("/item/sell/0006");
	else if (rand < 7705)
		item = new ("/item/01/0200");
	else if (rand < 7905)
		item = new ("/item/01/0201");
	else if (rand < 7955)
		item = new ("/item/01/0202");
	else if (rand < 8755)
	{
		item = new ("/item/01/0006");
		item2 = new ("/item/01/0006");
		item3 = new ("/item/01/0006");
		item4 = new ("/item/01/0006");
	}
	else if (rand < 8845)
		item = new ("/item/sell/0042");
	else if (rand < 8855)
		item = new ("/item/sell/0043");
	else if (rand < 9145)
		item = new ("/item/91/9125");
	else if (rand < 9245)
		item = new ("/item/91/9160");
	else if (rand < 9445)
		item = new (sprintf("/item/97/%d", 9706 + random(4)));
	else if (rand < 9480)
		item = new ("/item/sell/0030");
	else if (rand < 9560)
		item = new ("/item/sell/0200");
	else if (rand < 9620)
		item = new ("/item/sell/0201");
	else if (rand < 9650)
		item = new ("/item/sell/0202");
	else if (rand < 9780)
	{
		item = new ("/item/final/16/1601");
		item->set_amount(5);
	}
	else if (rand < 9880)
	{
		item = new ("/item/final/16/1615");
		item->set_amount(5);
	}
	else if (rand < 9950)
	{
		item = new ("/item/final/16/1621");
		item->set_amount(5);
	}
	else if (rand < 9990)
	{
		item = new ("/item/final/16/1630");
		item->set_amount(5);
	}
	else
		item = new ("/item/sell/0044");
	allitem = ({});
	if (item)
	{
		if (item->is_record())
			flag = 1;
		result = item->get_name();
		allitem += ({item});
		if (item2)
			allitem += ({item2});
		if (item3)
			allitem += ({item3});
		if (item4)
			allitem += ({item4});
		item = 0;
	}
	else if (result == "")
	{
		who->add_cash(3000);
		result = "3000金";
	}
	if (random(10000) < 1000)
	{
		rand = random(10000);
		if (rand < 1600)
		{
			who->add_cash(45000);
			result += "、45000金";
		}
		else if (rand < 2000)
		{
			item = new ("/item/sell/0007");
			item->set_amount(10);
		}
		else if (rand < 2400)
			item = new (sprintf("/item/sell/%04d", 15 + random(5)));
		else if (rand < 2700)
			item = new ("/item/91/9166");
		else if (rand < 3100)
			item = new (sprintf("/item/93/%d", 9301 + random(10)));
		else if (rand < 3500)
			item = new ("/item/08/0002");
		else if (rand < 3900)
			item = new ("/item/08/0001");
		else if (rand < 4100)
			item = new ("/item/44/4488");
		else if (rand < 4300)
			item = new (sprintf("/item/std/%d", 8001 + random(4)));
		else if (rand < 4700)
		{
			item = new ("/item/sell/0009");
			item->set_amount(10);
		}
		else if (rand < 5250)
		{
			item = new ("/item/stuff/0050");
			item->set_amount(10);
		}
		else if (rand < 5800)
		{
			item = new ("/item/stuff/0011");
			item->set_amount(10);
		}
		else if (rand < 6350)
		{
			item = new ("/item/stuff/0058");
			item->set_amount(10);
		}
		else if (rand < 6900)
			item = new ("/item/01/0201");
		else if (rand < 7000)
			item = new ("/item/01/0202");
		else if (rand < 7400)
			item = new ("/item/final/16/1629");
		else if (rand < 7650)
			item = new (sprintf("/item/38/%d", 3801 + random(5)));
		else if (rand < 7850)
			item = new ("/item/sell/0042");
		else if (rand < 7900)
			item = new ("/item/sell/0043");
		else if (rand < 8700)
			item = new ("/item/01/0006");
		else if (rand < 8850)
		{
			item = new ("/item/stuff/0062");
			item->set_amount(15);
		}
		else if (rand < 8950)
		{
			item = new ("/item/stuff/0085");
			item->set_amount(5);
		}
		else if (rand < 9350)
			item = new ("/item/08/0003");
		else if (rand < 9750)
			item = new ("/item/08/0004");
		else if (rand < 9900)
			item = new (BOOK_FILE->get_book_file());
		else
		{
			if (random(2))
				file = ARMOR_FILE->get_armor_file_3(20, 60);
			else
				file = WEAPON_FILE->get_weapon_file_3(20, 60);
			if (load_object(file))
			{
				item = new (file);
				ITEM_EQUIP_D->init_equip_prop_1(item);
			}
		}
	}
	if (item)
	{
		if (item->is_record())
			flag = 1;
		result = result + "、" + item->get_name();
		allitem += ({item});
		item = 0;
	}
	if (random(10000) < 50)
	{
		rand = random(10000);
		if (rand < 1050)
		{
			who->add_cash(70000);
			result += "、70000金";
		}
		else if (rand < 1450)
			item = new ("/item/sell/0002");
		else if (rand < 1850)
			item = new ("/item/sell/0004");
		else if (rand < 2250)
		{
			item = new ("/item/sell/0008");
			item->set_amount(10);
		}
		else if (rand < 2650)
		{
			item = new ("/item/sell/0010");
			item->set_amount(10);
		}
		else if (rand < 3050)
			item = new ("/item/sell/0031");
		else if (rand < 3650)
			item = new (sprintf("/item/sell/%d", 9301 + random(10)));
		else if (rand < 4350)
			item = new ("/item/sell/0030");
		else if (rand < 4750)
		{
			item = new ("/item/sell/0012");
			item->set_amount(2);
		}
		else if (rand < 4950)
			item = new ("/item/sell/0041");
		else if (rand < 5250)
			item = new ("/item/08/0001");
		else if (rand < 8550)
			item = new (sprintf("/item/final/15/%d", 1506 + random(6)));
		else if (rand < 8850)
			item = new ("/item/sell/0042");
		else if (rand < 9150)
			item = new ("/item/sell/0043");
		else if (rand < 9350)
			item = new ("/item/sell/0033");
		else if (rand < 9550)
			item = new ("/item/sell/0040");
		else if (rand < 9650)
			item = new ("/item/sell/0032");
		else if (rand < 9800)
			item = new ("/item/sell/0029");
		else
			item = new ("/item/sell/0028");
	}
	if (item)
	{
		flag = 1;
		result = result + "、" + item->get_name();
		allitem += ({item});
		item = 0;
	}
	if (random(10000) < 5)
	{
		rand = random(10000);
		if (rand < 700)
		{
			who->add_cash(100000);
			result += "、100000金";
		}
		else if (rand < 1300)
			item = new ("/item/std/6002");
		else if (rand < 1900)
			item = new ("/item/91/9178");
		else if (rand < 2600)
			item = new ("/item/sell/0026");
		else if (rand < 3300)
			item = new ("/item/sell/0027");
		else if (rand < 4000)
			item = new ("/item/sell/0025");
		else if (rand < 4600)
			item = new ("/item/sell/0032");
		else if (rand < 5200)
			item = new ("/item/sell/0043");
		else if (rand < 5800)
			item = new ("/item/sell/0029");
		else
			item = new (sprintf("/item/final/15/%d", 1512 + random(6)));
	}
	if (item)
	{
		flag = 1;
		result = result + "、" + item->get_name();
		allitem += ({item});
	}
	send_user(who, "%c%s", ';', "你打开锦囊，获得" + result + "。");
	if (sizeof(allitem) > 0)
	{
		if (flag == 1)
			USER_D->user_channel(sprintf(HIR "恭喜%s玩家打开锦囊获得了%s！", who->get_name(), result));
		for (i = 0; i < sizeof(allitem); i++)
			if (item = allitem[i])
			{
				if (item->get_max_combined() > 1)
				{
					total = item->get_amount();
					if (total == 0)
						total = 1;
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
	}
	return 0;
}
