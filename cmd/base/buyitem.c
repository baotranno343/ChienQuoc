
#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

mapping allgood = (["good1":(["01":"/item/sell/0061",
								"02":"/item/sell/0200",
								"03":"/item/sell/0201",
								"04":"/item/sell/0202",
								//	"02":"/item/test/vktk2",
								//"02":"/item/test/damai1",
								//"03":"/item/test/damai2",
								//"04":"/ken/pb/lenhbai",
								//	"05":"/item/test/TuiDT",

]),
					"good2":(["01":"/item/test/tuihoangkimtanthucap20",
								"02":"/item/test/tuihoangkimtanthucap30",
								"03":"/item/test/tuihoangkimtanthucap40",
								"04":"/item/test/congthanhtacdan",
								"05":"/item/08/0001",
								"06":"/item/08/0002",
								"07":"/item/08/0004",
								"08":"/item/08/0003",
								"09":"/item/sell/0007",
								"10":"/item/sell/0009",
								"11":"/item/91/9166",
								//	"12":"/item/91/9178",
								"12":"/item/sell/0006",
								"13":"/item/mop/9988",
								"14":"/item/sell/0060",
								"15":"/item/100/10056",
								"16":"/item/100/11056",
								"17":"/item/30/3027",

]),
					"good3":([
								// "01":"/item/08/0800",
								// 		"02":"/item/08/0801",
								// 		"03":"/item/08/0804",
								// 		"04":"/item/08/0805",
								// 		"05":"/item/08/0806",
								// 		"06":"/item/08/0810",
								"01":"/item/08/shuiping",
								"02":"/item/08/0850",
								"03":"/item/08/0841",
								"04":"/item/08/0842",
								"05":"/item/08/0843",
								"06":"/item/sell/0025",
								"07":"/item/test2/SVT",
								"08":"/item/test2/SungVatDuoc",
								"09":"/item/test2/SungVatDuoc2",
								"09":"/item/test2/Tui12ConGiap",
								"10":"/item/test2/TuiThanThuHoangDao",

]),
					"good4":(["01":"/item/test2/AXP",
								"02":"/item/sell/0015",
								"03":"/item/sell/0016",
								"04":"/item/sell/0017",
								"05":"/item/sell/0018",
								"06":"/item/sell/0019",
								"07":"/ken/keocattoc",
								"08":"/item/54/4134",
								"09":"/item/54/4141",
								"10":"/item/54/4142",
								"11":"/item/54/4143",
								"12":"/item/54/4145",
								"13":"/item/54/8013",

]),
					"good5":(["01":"/item/sell/0012",
								"02":"/item/sell/0026",
								"03":"/item/sell/0027",
								"04":"/item/test2/TLTA",
								"05":"/item/sell/0030",
								"06":"/item/sell/0043",
								"07":"/item/sell/0042",
								"08":"/item/sell/0028",
								"09":"/item/sell/0029",
								"10":"/item/sell/0033",
								"11":"/item/test2/TuiPhapBao",
								"12":"/item/std/0095",
								"13":"/item/sell/6003",
								"14":"/item/sell/0031_2",
								"15":"/item/sell/0031",
								"16":"/item/test2/LTDB",
								"17":"/item/std/8000",
								//"18":"/item/std/8005",
								"18":"/item/test2/TuiThanThu",
								"19":"/item/01/0006",
								"20":"/item/test2/TuiQuaVoSong",
								"21":"/item/test2/TheGiamGia",
]),
					"good6":(["01":"/item/100/10059",
								"02":"/item/100/11059",
								// "03":"/item/100/10055",
								// "04":"/item/100/11055",
								// "05":"/item/100/10052",
								// "06":"/item/100/11052",
								"03":"/item/std/0004",
								"04":"/item/std/0005",
								"05":"/item/std/0006",
								"06":"/item/std/0007",
								// "11":"/item/100/10060",
								// "12":"/item/100/11060",
								// "13":"/item/100/10061",
								// "14":"/item/100/11061",
								// "15":"/item/100/10062",
								// "16":"/item/100/11062",
								// "17":"/item/100/10063",
								// "18":"/item/100/11063",
								// "19":"/item/100/10064",
								// "20":"/item/100/11064",
								// "21":"/item/100/10065",
								// "22":"/item/100/11065",

]),
				   //----------------?????????????????????????????????????????????????????????????????????------------------------------------
				   "good99":([
								//	"01" : "/item/mop/9003",
								"01":"/item/test2/tuitukim55",
								"02":"/item/mop/9006",
]),
	//--------------------------------------------------------------------------------------------
]);
mapping gonggao = (["????????????":"2007???4???11??????5???11????????????????????????????????????????????????????????????????????????????????????100???????????????????????? ???????????????1??????????????????????????????????????????100?????????100?????????????????????????????????.??????????????????????????????+2000?????????",
					"????????????":"2007???4???11??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????.???????????????????????????zg.mop.com??????????????????.",
]);

void send_gonggao(object me);
int xacnhanmua(object me, string arg, int total, string file);
mapping goodprice = ([]);

void create()
{
	string cpp, *line;
	int i, size, a, b, c, d, ret;
	cpp = read_file("/quest/good.dat");
	if (!cpp)
	{
		return;
	}
	line = explode(cpp, "\n");
	size = sizeof(line);
	if (size == 0)
		return;
	for (i = 0; i < size; i++)
	{
		if (sscanf(line[i], "%d %d %d %d", a, b, c, d) != 4)
		{
			continue;
		}
		goodprice[a] = ({b, c, d});
	}
}
//Question before Buy
int xacnhanmua(object me, string arg, int total, string file)
{
	string result;
	if (me->get_save("muaxn2") >= 1)
		return 0;
	me->set_save("muaxn", arg);
	result = sprintf("B???n quy???t ?????nh mua %d c??i %s ch??a?\n" ESC "%c\n" ESC "\nvip 123\n", total, file->get_name(), 1);
	send_user(me, "%c%c%s", 0x59, 1, result);
	return 1;
}
// ?????????????????????
int main(object me, string arg)
{

	mapping list;
	int iVip, i, size, price, price1, price2, type, what, total, amount, count, p, x, y, z, itemid;
	string *key, file, desc, name, legend, result, cmd1, cmd2;
	object item;
	int *prices;
	//	iVip = me->get_vip();
	//	if (time()<iVip) iVip =	1;
	//	else iVip = 0;

	//me->set("knbkhoa", 1);
	if (!arg)
	{
		cmd1 = sprintf("buyitem knb\n");
		cmd2 = sprintf("buyitem knbkhoa\n");
		send_user(me, "%c%s", ':', sprintf("B???n Mu???n D??ng KNB N??o ????? Giao D???ch: \nKim Nguy??n B???o: %d \nKim Nguy??n B???o Kh??a: %d \n" ESC "Kim Nguy??n B???o\n" + cmd1 + ESC "Kim Nguy??n B???o Kh??a\n" + cmd2, "sys/sys/test_db"->get_yuanbao(me) / 10, me->get_knbkhoa() / 10));
		return 1;
		//tell_user(me, "???????????????");

		// else if (MAIN_D->get_host_type() == 6012)
		// {
		// 	//tell_user(me, "???????????????1");
		// 	me->set_pay_money_buy_item(1);
		// 	me->set_pay_type(5);
		// 	me->set_buy_item_cmd_string("  ");
		// 	db_user_pay(me, sprintf("210.48.144.183:2500\n"
		// 							"21,\"%s\",%d\r\n",
		// 							me->get_real_id(), me->get_acountno()));
		// 	//			log_file( "php.date", sprintf( "open 210.48.144.183:2500\n"
		// 	//				"21,\"%s\",%d\r\n", me->get_real_id(), me->get_acountno() ) );
		// }
		// else if (me->get_pay_money_buy_item() == 0 && !me->get("phpbalance"))
		// {
		// 	me->set_pay_money_buy_item(1);
		// 	me->set_pay_type(5);
		// 	me->set_buy_item_cmd_string("  ");
		// 	db_user_pay(me, sprintf("%s:80\n"
		// 							"GET http:/"
		// 							"/%s/querybalance.php?t=%s&u=%d\r\n",
		// 							MAIN_D->get_php_ip(),
		// 							MAIN_D->get_php_ip(), short_time_2(), me->get_acountid()));
		// 	//log_file( "php.date", 	sprintf( "%s:80\n"
		// 	//				"GET http:/""/%s/querybalance.php?t=%s&u=%d\r\n", MAIN_D->get_php_ip(),
		// 	//				MAIN_D->get_php_ip(), short_time_2(), me->get_acountid() ) );
		// }

		//	arg = "2";
	}
	if (arg == "knbkhoa")
	{
		me->set("knbkhoa", 1);
		send_user(me, "%c%c%c", 0x45, 1, 0);
		if (MAIN_D->get_host_type() == 1 || MAIN_D->get_host_type() == 1000)
		{
			if (me->get("knbkhoa"))
			{
				send_user(me, "%c%c%d", 0x45, 2, me->get_knbkhoa());
			}
			else
			{
				send_user(me, "%c%c%d", 0x45, 2, "sys/sys/test_db"->get_yuanbao(me));
			}
		}
		arg = "2";
	}
	if (arg == "knb")
	{
		me->set("knbkhoa", 0);
		send_user(me, "%c%c%c", 0x45, 1, 0);
		if (MAIN_D->get_host_type() == 1 || MAIN_D->get_host_type() == 1000)
		{
			if (me->get("knbkhoa"))
			{
				send_user(me, "%c%c%d", 0x45, 2, me->get_knbkhoa());
			}
			else
			{
				send_user(me, "%c%c%d", 0x45, 2, "sys/sys/test_db"->get_yuanbao(me));
			}
		}
		arg = "2";
	}
	if (arg == "notice")
	{
		send_gonggao(me);
		return 1;
	}
	key = explode(arg, " ");
	if (sizeof(key) == 1)
	{
		list = allgood["good" + arg];
		if (!mapp(list))
			return 1;
		key = keys(list);
		size = sizeof(key);
		if (size == 0)
			return 1;
		key = sort_array(key, 1);
		send_gonggao(me);
		for (i = 0; i < size; i++)
		{
			file = list[key[i]];
			desc = file->get_short();
			prices = goodprice[file->get_item_number()];
			if (sizeof(prices) == 3)
			{
				if (iVip == 0)
					price = prices[0];
				else
				{
					if (prices[2] > 0)
						price = prices[2];
					else
						price = prices[1];
				}
				if (prices[2] > 0 && prices[2] < price) //???????????????
					price = prices[2];

				if (desc == 0)
					desc = file->get_desc();
				price1 = prices[0];
				price2 = prices[1];
				if (me->get("knbkhoa"))
				{
					if (to_int(arg) == 1 || to_int(arg) == 5 || to_int(arg) == 6)
					{
						price1 = 0;
						price2 = 0;
						price = 0;
					}
				}
				name = sprintf("%-40s%s", file->get_name(), desc);
				send_user(me, "%c%c%c%c%d%d%d%w%w%c%c%s", 0x45, 3, to_int(arg), to_int(key[i]), price1, price2, price,
						  file->get_picid_2(), file->get_amount(), 0, file->get_item_color(), name);
			}
			else
			{
				price = file->get_item_value();
				if (iVip == 0)
					price = file->get_item_value();
				else
				{
					if (file->get_item_value_3() > 0)
						price = file->get_item_value_3();
					else
						price = file->get_item_value_2();
				}
				if (desc == 0)
					desc = file->get_desc();
				name = sprintf("%-40s%s", file->get_name(), desc);
				price1 = file->get_item_value();
				price2 = file->get_item_value_2();
				if (me->get("knbkhoa"))
				{
					if (to_int(arg) == 1 || to_int(arg) == 5 || to_int(arg) == 6)
					{
						price1 = 0;
						price2 = 0;
						price = 0;
					}
				}
				send_user(me, "%c%c%c%c%d%d%d%w%w%c%c%s", 0x45, 3, to_int(arg), to_int(key[i]), price1, price2, price,
						  file->get_picid_2(), file->get_amount(), 0, file->get_item_color(), name);
			}
		}
		return 1;
	}
	if (key[0] == "desc")
	{
		if (sizeof(key) != 3)
			return 1;
		type = to_int(key[1]);
		what = to_int(key[2]);
		if (!stringp(file = allgood[sprintf("good%d.%02d", type, what)]))
			return 1;
		send_user(me, "%c%c%c%c%s", 0x45, 4, type, what, file->get_desc());
		return 1;
	}
	if (sscanf(arg, "%d %d %d", type, what, total) != 3)
		return 1;
	if (total < 1)
	{
		notify("S??? l?????ng v???t ph???m c???n mua ph???i l???n h??n 0.");
		return 1;
	}
	if (me->get("knbkhoa"))
	{

		if (type == 1 || type == 5 || type == 6)
		{
			notify("Kh??ng Th??? D??ng KNB Kh??a ????? Mua d???ng c??? ??? trang n??y");
			return 1;
		}
	}
	// if (type == 1 && (what == 2 || what == 3) && me->get("knbkhoa"))
	// {

	// 	notify("Kh??ng Th??? D??ng KNB Kh??a ????? Mua ???? M??i");
	// 	return 1;
	// }
	if (MAIN_D->get_host_type() == 1 || MAIN_D->get_host_type() == 1000)
	{
		list = allgood[sprintf("good%d", type)];
		if (!mapp(list))
		{
			notify("?????o c??? n??y kh??ng c?? b??n ra");
			return 1;
		}
		file = list[sprintf("%02d", what + 1)];
		if (!stringp(file))
		{
			notify("Kh??ng c?? ?????o c??? b??n ra");
			return 1;
		}
		if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
		{
			notify("H??nh trang ??ang trong tr???ng th??i Kho??.");
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "H??nh trang c???a b???n ??ang trong tr???ng th??i Kho?? !");
			return 1;
		}
		if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
		{
			notify("H??y ch???a 1 ch??? tr???ng");
			return 1;
		}
		if ((price = file->get_item_value()) < 1)
		{
			notify("Kh??ng c?? ?????o c??? b??n ra");
			return 1;
		}
		if (file->get_sell_amount() && amount > file->get_sell_amount())
			amount = file->get_sell_amount();
		if (total > amount)
			total = amount;
		if (xacnhanmua(me, arg, total, file) == 1)
			return 1;
		if (file->question_before_buy(me, arg) == 1)
			return 1;
		prices = goodprice[file->get_item_number()];
		if (sizeof(prices) == 3)
		{
			price = prices[0];
			if (iVip > 0)
			{
				if (prices[2] > 0)
					price = prices[2];
				else if (prices[1] > 0)
					price = prices[1];
			}
			if (prices[2] > 0 && prices[2] < price)
				price = prices[2];
		}
		else
		{
			price = file->get_item_value();
			if (iVip > 0)
			{
				if (file->get_item_value_3() > 0)
					price = file->get_item_value_3();
				else if (file->get_item_value_2() > 0)
					price = file->get_item_value_2();
			}
		}
		price *= total;
		if (me->get("knbkhoa"))
		{
			if (me->get_knbkhoa() < price)
			{
				notify("Ng????i kh??ng c?? ????? Kim Nguy??n B???o Kh??a");
				if (stringp(me->get_save("muaxn")))
					me->delete_save("muaxn");
				if (me->get_save("muaxn2") >= 1)
					me->delete_save("muaxn2");
				if (stringp(me->get_save("muavip")))
					me->delete_save("muavip");
				if (me->get_save("muavip2") >= 1)
					me->delete_save("muavip2");
				return 1;
			}
			me->add_knbkhoa(-price);
			send_user(me, "%c%c%d", 0x45, 2, me->get_knbkhoa());

			"/sys/sys/id"->add_buy(total, price);
		}
		else
		{
			if ("sys/sys/test_db"->get_yuanbao(me) < price)
			{
				notify("Ng????i kh??ng c?? ????? Kim Nguy??n B???o");
				if (stringp(me->get_save("muaxn")))
					me->delete_save("muaxn");
				if (me->get_save("muaxn2") >= 1)
					me->delete_save("muaxn2");
				if (stringp(me->get_save("muavip")))
					me->delete_save("muavip");
				if (me->get_save("muavip2") >= 1)
					me->delete_save("muavip2");
				return 1;
			}
			"sys/sys/test_db"->add_yuanbao(me, -price);
			send_user(me, "%c%c%d", 0x45, 2, "sys/sys/test_db"->get_yuanbao(me));
			"/sys/sys/id"->add_buy(total, price);
		}

		if (file->give_item_to_user(me))
			return;
		else if (file->is_combined())
		{
			item = new (file);
			if (me->get("knbkhoa"))
			{
				item->set_no_give(1);
			}
			if (amount = USER_INVENTORY_D->carry_combined_item(me, item, total))
			{
				// item = new (file);
				item->set_hide(0);
				item->set_amount(amount);
				// if (me->get("knbkhoa"))
				// {
				// 	item->set_no_give(1);
				// }
				count = "/sys/sys/count"->add_buy_count(1);
				itemid = "/sys/sys/id"->add_max_itemid(1);

				item->set_user_id(sprintf("#%d#", itemid));

				//log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
				legend = sprintf("???? mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", "Ng??n Kh???", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
				//	"/sys/user/cmd"->log_item(legend);
				if (p = item->move2(me))
				{
					item->add_to_user(p);
				}
				else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
				{
					item->add_to_scene(z, p / 1000, p % 1000);
				}
			}
			else
			{
				destruct(item);
			}
		}
		else
			for (i = 0; i < total; i++)
			{
				item = new (file);
				item->set_hide(0);
				if (me->get("knbkhoa"))
				{
					item->set_no_give(1);
				}
				count = "/sys/sys/count"->add_buy_count(1);
				itemid = "/sys/sys/id"->add_max_itemid(1);
				item->set_user_id(sprintf("#%d#", itemid));
				//log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
				legend = sprintf("???? mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", "Ng??n Kh???", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
				//	"/sys/user/cmd"->log_item(legend);
				if (p = item->move2(me))
				{
					item->add_to_user(p);
				}
				else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
				{
					item->add_to_scene(z, p / 1000, p % 1000);
				}
			}
		log_file("buyitem.dat", sprintf("%s %s(%d) mua %s th??nh c??ng %d %d\n", short_time(), me->get_id(), me->get_number(), file->get_name(), total, price));
		send_user(me, "%c%s", '!', sprintf("B???n ???? mua %s .", file->get_name()));
		if (stringp(me->get_save("muaxn")))
			me->delete_save("muaxn");
		if (me->get_save("muaxn2") >= 1)
			me->delete_save("muaxn2");
		return 1;
	}
	if (!me->get_pay_money_buy_item())
	{
		if (me->get("paycount") < 0)
		{
			notify("Ng????i kh??ng ????? Kim Nguy??n B???o,n???u ng????i ???? b??? sung h??y reset tr?? ch??i r???i l???i mua ?????o c???");
			return 1;
		}
		list = allgood[sprintf("good%d", type)];
		if (!mapp(list))
		{
			notify("Kh??ng c?? ?????o c??? b??n ra");
			return 1;
		}
		file = list[sprintf("%02d", what + 1)];
		if (!stringp(file))
		{
			notify("Kh??ng c?? ?????o c??? b??n ra");
			return 1;
		}
		if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
		{
			notify("H??nh trang kh??ng ????? ?? tr???ng.");
			return 1;
		}
		if ((price = file->get_item_value()) < 1)
		{
			notify("Kh??ng c?? ?????o c??? b??n ra");
			return 1;
		}
		if (file->question_before_buy(me, arg) == 1)
			return 1;
		if (file->get_sell_amount() && amount > file->get_sell_amount())
			amount = file->get_sell_amount();
		if (total > amount)
			total = amount;
		prices = goodprice[file->get_item_number()];
		if (sizeof(prices) == 3)
		{
			price = prices[0];
			if (iVip > 0)
			{
				if (prices[2] > 0)
					price = prices[2];
				else if (prices[1] > 0)
					price = prices[1];
			}
			if (prices[2] > 0 && prices[2] < price)
				price = prices[2];
		}
		else
		{
			price = file->get_item_value();
			if (iVip > 0)
			{
				if (file->get_item_value_3() > 0)
					price = file->get_item_value_3();
				else if (file->get_item_value_2() > 0)
					price = file->get_item_value_2();
			}
		}
		price *= total;
		// me->set_pay_money_buy_item(1); // ?????????? mua?????????
		// me->set_pay_type(6);
		// me->set_buy_item_cmd_string(sprintf("%d %d %d", type, what, total));
		// log_file("buyitem.dat", sprintf(" %s %s ( %d ) ???? mua %s %d \n", short_time(), me->get_id(), me->get_number(), file->get_name(), total));
		// if (MAIN_D->get_host_type() == 4 || MAIN_D->get_host_type() == 0)
		// {
		// 	db_user_pay(me, sprintf("%s:80\n"
		// 							"GET http:/"
		// 							"/%s/purchase.php?t=%s&u=%d&o=%d&n=%d&m=%d&c=%d&ip=%s&r=%d&h=%d\r\n",
		// 							MAIN_D->get_php_ip(),
		// 							MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), me->get_number(), total, price, file->get_item_number(), get_ip_name(me), MAIN_D->get_region(), MAIN_D->get_host()));
		// 	//log_file("php.dat", sprintf( "%s:80\n"
		// 	//				"GET http:/""/%s/purchase.php?t=%s&u=%d&o=%d&n=%d&m=%d&c=%d&ip=%s&r=%d&h=%d\n",	MAIN_D->get_php_ip(),
		// 	//				MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), me->get_number(), total, price, file->get_item_number(), get_ip_name(me), MAIN_D->get_region(), MAIN_D->get_host() ) );
		// }
		// else if (MAIN_D->get_host_type() == 6012)
		// {
		// 	db_user_pay(me, sprintf("210.48.144.183:2500\n"
		// 							"22,\"%s\",%d,\"99\",99,%d,\"%d\",\"%d\",\"%s\",\"%s\"\r\n",
		// 							me->get_real_id(), me->get_acountno(), price, "/sys/sys/id"->get_transid(), file->get_item_number(), file->get_name(), get_ip_name(me)));
		// 	//			log_file( "php.date", sprintf( "210.48.144.183:2500\n"
		// 	//				"22,\"%s\",%d,\"99\",99,%d,\"%d\",\"%d\",\"%s\",\"%s\"\r\n", me->get_real_id(), me->get_acountno(),price, "/sys/sys/id"->get_transid(), file->get_item_number(), file->get_name(), get_ip_name(me)  ) );
		// 	"/sys/sys/id"->add_transid(1);
		// }
		// else
		// 	db_user_pay(me, sprintf("%s:80\n"
		// 							"GET /xq2/buy.php?id=%s&time=%d&region=%d&host=%d&item=%d&point=%d&ip=%s\r\n",
		// 							MAIN_D->get_php_ip(),
		// 							rawurlencode(me->get_id()), time(), MAIN_D->get_region(), MAIN_D->get_host(), file->get_item_number(), price, get_ip_name(me))); // ?????????
		//
		return 1;
	}
	// if (me->get_pay_money_buy_item() == 8 && me->get_pay_type() == 6) // ?????????? mua???????????????
	// {
	// 	me->set_pay_money_buy_item(0); // ???????????????? mua??????
	// 	me->set_pay_type(0);

	// 	list = allgood[sprintf("good%d", type)];
	// 	if (!mapp(list))
	// 	{
	// 		notify("Kh??ng c?? ?????o c??? b??n ra");
	// 		return 1;
	// 	}
	// 	file = list[sprintf("%02d", what + 1)];
	// 	if (!stringp(file))
	// 	{
	// 		log_file("buyitem.dat", sprintf("%s %s(%d) kh??ng c?? mua ?????i t?????ng\n", short_time(), me->get_id(), me->get_number()));
	// 		notify("Kh??ng c?? ?????o c??? b??n ra");
	// 		return 1;
	// 	}
	// 	if ((price = file->get_item_value()) < 1)
	// 	{
	// 		log_file("buyitem.dat", sprintf("%s %s(%d) mua th????ng ph???m kh??ng ????ng\n", short_time(), me->get_id(), me->get_number()));
	// 		notify("Kh??ng c?? ?????o c??? b??n ra");
	// 		return 1;
	// 	}

	// 	if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
	// 	{
	// 		log_file("buyitem.dat", sprintf("%s %s(%d) mua kh??ng ????? kh??ng v???\n", short_time(), me->get_id(), me->get_number()));
	// 		notify("H??nh trang kh??ng ????? ch??? tr???ng");
	// 		return 1;
	// 	}
	// 	prices = goodprice[file->get_item_number()];
	// 	if (sizeof(prices) == 3)
	// 	{
	// 		price = prices[0];
	// 		if (iVip > 0)
	// 		{
	// 			if (prices[2] > 0)
	// 				price = prices[2];
	// 			else if (prices[1] > 0)
	// 				price = prices[1];
	// 		}
	// 		if (prices[2] > 0 && prices[2] < price)
	// 			price = prices[2];
	// 	}
	// 	else
	// 	{
	// 		price = file->get_item_value();
	// 		if (iVip > 0)
	// 		{
	// 			if (file->get_item_value_3() > 0)
	// 				price = file->get_item_value_3();
	// 			else if (file->get_item_value_2() > 0)
	// 				price = file->get_item_value_2();
	// 		}
	// 	}
	// 	if (file->get_sell_amount() && amount > file->get_sell_amount())
	// 		amount = file->get_sell_amount();
	// 	if (total > amount)
	// 		total = amount;
	// 	price *= total;
	// 	"/sys/sys/id"->add_buy(total, price);
	// 	if (file->give_item_to_user(me))
	// 		return;
	// 	else if (file->is_combined())
	// 	{
	// 		if (amount = USER_INVENTORY_D->carry_combined_item(me, load_object(file), total))
	// 		{

	// 			item = new (file);
	// 			item->set_hide(0);
	// 			item->set_amount(amount);
	// 			count = "/sys/sys/count"->add_buy_count(1);
	// 			itemid = "/sys/sys/id"->add_max_itemid(1);
	// 			item->set_user_id(sprintf("#%d#", itemid));
	// 			//log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
	// 			legend = sprintf("???? mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", "Ng??n Kh???", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
	// 			//	"/sys/user/cmd"->log_item(legend);
	// 			if (p = item->move2(me))
	// 			{
	// 				item->add_to_user(p);
	// 			}
	// 			else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
	// 			{
	// 				item->add_to_scene(z, p / 1000, p % 1000);
	// 			}
	// 		}
	// 	}
	// 	else
	// 		for (i = 0; i < total; i++)
	// 		{
	// 			item = new (file);
	// 			item->set_hide(0);
	// 			count = "/sys/sys/count"->add_buy_count(1);
	// 			itemid = "/sys/sys/id"->add_max_itemid(1);
	// 			item->set_user_id(sprintf("#%d#", itemid));
	// 			//log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
	// 			legend = sprintf("???? mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", "Ng??n Kh???", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
	// 			//	"/sys/user/cmd"->log_item(legend);
	// 			if (p = item->move2(me))
	// 			{
	// 				item->add_to_user(p);
	// 			}
	// 			else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
	// 			{
	// 				item->add_to_scene(z, p / 1000, p % 1000);
	// 			}
	// 		}
	// 	log_file("buyitem.dat", sprintf(" %s %s ( %d ) ???? mua %s th??nh c??ng %d %d \n", short_time(), me->get_id(), me->get_number(), file->get_name(), total, price));
	// 	send_user(me, "%c%s", '!', sprintf("B???n ???? mua %s .", file->get_name()));
	// 	if (file->get_name() == "???????????????")
	// 		send_user(me, "%c%s", ';', "?????????????????????????????????????????????????????????????????????" HIR "200??????" NOR "?????????????????????????????????????????????????????????");
	// }
	// else
	// {
	// 	if (me->get_pay_money_buy_item() > 0)
	// 	{
	// 		send_user(me, "%c%s", '!', "??ang x??? l??, xin ch??? 1 ch??t");
	// 		return;
	// 	}
	// }
	return 1;
}

void send_gonggao(object me)
{
	int i, size;
	string *key;
	key = keys(gonggao);
	size = sizeof(key);
	for (i = 0; i < size; i++)
	{
		send_user(me, "%c%c%c%s", 0x45, 5, i + 1, key[i]);
		send_user(me, "%c%c%c%s", 0x45, 6, i + 1, gonggao[key[i]]);
	}
}