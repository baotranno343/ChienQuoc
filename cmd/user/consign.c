
#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <chia_kenh.h>
inherit SAVE_F;

#define SAVE_FILE "data/city/consign" SAVE_EXTENSION

mapping cardlist = ([50:([]),
					100:([]),
					200:([]),
]);

// int reset_time = 1;

// static int *cur_reset = ({0, 0, 0});

void create()
{
	restore_object(SAVE_FILE);
}
int set_reset_time(int i);
// 函数：命令处理
int main(object me, string arg)
{
	mapping list;
	int value, time, price, i, j, size, rands, id, flag, *list_value, khoangcach, cancel_knb, check = 0;

	string *key, file, desc, name, legend, result;
	object item;
	int *prices;
	//	iVip = me->get_vip();
	//	if (time()<iVip) iVip =	1;
	//	else iVip = 0;
	if (!arg)
	{
		return 1;
	}
	if (MAIN_D->get_kenh() != KENH_KYGUIKNB && KENH_KYGUIKNB != 0)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Ký Gửi hãy về Kênh Mua Bán ");
		return;
	}
	if (me->get_pay_money_buy_item() > 0)
	{
		send_user(me, "%c%s", '!', "Đang xử lý, xin chờ 1 chút !");
		return 1;
	}
	key = explode(arg, " ");
	switch (key[0])
	{
	case "sale":  // 提交寄售点卡
	case "sale2": // 确认提交寄售点卡
		if (sizeof(key) != 4)
			return;
		if (sscanf(arg, "%s %d %d %d", result, value, time, price) != 4)
			return 1;
		if (value != 50 && value != 100 && value != 200)
		{
			send_user(me, "%c%s", '!', "Kí gửi giá trị không đúng !");
			return 1;
		}
		time /= 3600;
		if (time != 8 && time != 12 && time != 24)
		{
			send_user(me, "%c%s", '!', "Thời gian kí gửi không đúng");
			return 1;
		}
		if (price < 10000)
		{
			send_user(me, "%c%s", '!', "Giá gửi bán ít nhất là 10000");
			return 1;
		}
		if (price % 1000)
		{
			send_user(me, "%c%s", '!', "Đơn vị gửi bán phải chia hết cho 1000");
			return 1;
		}
		if ("sys/sys/test_db"->get_yuanbao(me) < (value * 10 + (value * 5 / 100 * 10)))
		{
			send_user(me, "%c%s", '!', "Bạn không có đủ Kim Nguyên Bảo để ký gửi hãy bao gồm cả 5%% phí ký gửi");
			return 1;
		}
		//restore_object(SAVE_FILE);
		if (key[0] == "sale")
		{
			result = sprintf("Bạn xác định phải lấy " HIR "%d" NOR " giá bán ra" HIR " %d" NOR " Kim Nguyên Bảo phải không?\n", price, value);
			result += sprintf(ESC "Xác định\nconsign sale2 %d %d %d\n", value, time * 3600, price);
			result += ESC "Huỷ bỏ\n";
			send_user(me, "%c%c%w%s", ':', 3, 0, result);
			return;
		}
		//log_file("buycard.dat", sprintf("%s %s(%d) 寄售%d点卡 价格%d 时间%d\n", short_time(), me->get_id(), me->get_number(), value, price, time));
		rands = random(100000);
		if (!mapp(cardlist[value][rands]))
		{
			cardlist[value][rands] = ({price, time() + time * 3600, 0, me->get_number()});
		}
		else
		{
			rands += random(10);
			cardlist[value][rands] = ({price, time() + time * 3600, 0, me->get_number()});
		}

		"sys/sys/test_db"->add_yuanbao(me, -(value * 10 + (value * 5 / 100 * 10)));
		//	me->set_save_2(sprintf("banknb.%d", rands), 1);
		//	me->set_save_2(sprintf("banknb.%d", rands), sprintf("%d:%d:%d:%d", value, price, time, 0));
		send_user(me, "%c%s", ';', sprintf("Bạn thành công gửi bán " HIR "%d" NOR " Kim Nguyên Bảo, Hệ thống trừ đi" HIR " 5%% Kim Nguyên Bảo " NOR "phí kí gửi !", value));
		send_user(me, "%c%c%d", 0x45, 2, "sys/sys/test_db"->get_yuanbao(me));
		save_object(SAVE_FILE);
		log_file("consign.txt", sprintf("%s : %s (%d) đã bán %d Kim Nguyên Bảo\n", short_time(time()), me->get_name(), me->get_number(), value));
		break;
	case "list": // 查询可购买的点卡
		if (sizeof(key) != 2)
			return;
		value = to_int(key[1]);
		if (value != 50 && value != 100 && value != 200)
		{
			send_user(me, "%c%s", '!', "Điểm kí gửi không đúng !");
			return 1;
		}
		if (gone_time(me->get("khoangcach")) < 5)
		{
			send_user(me, "%c%s", '!', "Không được sử dụng liên tục vui lòng đợi 5 giây !");
			return 1;
		}
		me->set("khoangcach", time());
		//restore_object(SAVE_FILE);
		// 检查是否需要重新查询
		if (value == 50)
			j = 0;
		else if (value == 100)
			j = 1;
		else
			j = 2;

		// if (reset_time > 0)
		// {
		// if (time() < cur_reset[j] + reset_time)
		// {

		send_user(me, "%c%c%c", 0x92, 1, 2);
		list = cardlist[value];
		key = keys(list);
		size = sizeof(key);
		if (size == 0)
		{
			return 1;
		}
		for (i = 0; i < size; i++)
		{
			if (list[key[i]][1] > time())
			{

				if (list[key[i]][2] == 0)
				{
					send_user(me, "%c%c%d%d%d%d", 0x92, 2, to_int(key[i]), value, list[key[i]][0], list[key[i]][1]);
				}
			}
			else
			{
				if (list[key[i]][2] == 0)
				{
					list[key[i]][2] = 1;
					check = 1;
				}
			}
		}
		if (check == 1)
			save_object(SAVE_FILE);
		return 1;
		//}
		//}

		break;
	case "buy": // 购买点卡
		if (sizeof(key) != 2)
			return;
		//restore_object(SAVE_FILE);
		value = to_int(key[1]);
		prices = cardlist[50][value];
		//printf(prices);
		//CHAT_D->vip_channel(1, sprintf(CHAT " %s : %d ", "Tran", value));
		i = 50;
		if (prices == 0)
		{
			prices = cardlist[100][value];
			i = 100;
		}
		if (prices == 0)
		{
			prices = cardlist[200][value];
			i = 200;
		}
		if (prices == 0)
		{
			send_user(me, "%c%s", '!', "Kí gửi đã hết hạn !");
			return 1;
		}
		if (me->get_cash() < prices[0])
		{
			send_user(me, "%c%s", ';', "Trên người bạn không đủ ngân lượng để mua !");
			return 1;
		}
		if (prices[1] < time())
		{
			send_user(me, "%c%s", '!', "Ký gửi đã hết hạn");
			return 1;
		}
		if (prices[2] != 0)
		{
			send_user(me, "%c%s", '!', "Ký gửi đã bán hoặc ngưng bán");
			return 1;
		}
		me->add_cash(-prices[0]);
		"sys/sys/test_db"->add_yuanbao(me, i * 10);
		send_user(me, "%c%s", ';', sprintf("Bạn đã mua thành công %d Kim Nguyên Bảo！", i));
		send_user(me, "%c%c%d", 0x45, 2, "sys/sys/test_db"->get_yuanbao(me));
		send_user(me, "%c%c%d%d%d%d", 0x92, 2, value, 0, 0, 0);
		//	map_delete(cardlist[i], value);
		cardlist[i][value][2] = 2;
		save_object(SAVE_FILE);
		log_file("consign.txt", sprintf("%s : %s (%d) đã mua %d Kim Nguyên Bảo\n", short_time(time()), me->get_name(), me->get_number(), i));

		break;
	case "status": // 查询自已的寄售情况
				   // if (sizeof(key) != 2)
				   // 	return;

		if (gone_time(me->get("khoangcach")) < 5)
		{
			send_user(me, "%c%s", '!', "Không được sử dụng liên tục vui lòng đợi 5 giây !");
			return 1;
		}
		me->set("khoangcach", time());
		//restore_object(SAVE_FILE);
		send_user(me, "%c%c%c", 0x92, 1, 3);
		send_user(me, "%c%c%d", 0x45, 2, "sys/sys/test_db"->get_yuanbao(me));
		list_value = ({50, 100, 200});
		for (j = 0; j < sizeof(list_value); j++)
		{
			//	printf(list_value[j]);
			key = keys(cardlist[list_value[j]]);
			size = sizeof(key);
			if (size == 0)
			{
				continue;
			}
			//	CHAT_D->vip_channel(1, sprintf(CHAT " %s : %s ", "Tran", "Test0"));
			for (i = 0; i < size; i++)
			{
				//CHAT_D->vip_channel(1, sprintf(CHAT " %s : %s ", "Tran", "Test1"));
				if (cardlist[list_value[j]][key[i]][3] == me->get_number())
				{
					//	CHAT_D->vip_channel(1, sprintf(CHAT " %s : %s ", "Tran", "Test2"));
					if (cardlist[list_value[j]][key[i]][1] < time() && cardlist[list_value[j]][key[i]][2] == 0)
					{
						cardlist[list_value[j]][key[i]][2] = 1;
						check = 1;
					}
					send_user(me, "%c%c%d%d%d%d%d", 0x92, 3, to_int(key[i]), list_value[j], cardlist[list_value[j]][key[i]][0], cardlist[list_value[j]][key[i]][1], cardlist[list_value[j]][key[i]][2]);
				}
			}
		}
		if (check == 1)
			save_object(SAVE_FILE);
		break;
	case "cancel": // 取消寄售
		if (sizeof(key) != 2)
			return;
		//restore_object(SAVE_FILE);
		value = to_int(key[1]);
		prices = cardlist[50][value];
		//printf(prices);
		//CHAT_D->vip_channel(1, sprintf(CHAT " %s : %d ", "Tran", value));
		i = 50;
		if (prices == 0)
		{
			prices = cardlist[100][value];
			i = 100;
		}
		if (prices == 0)
		{
			prices = cardlist[200][value];
			i = 200;
		}
		if (prices == 0)
		{
			send_user(me, "%c%s", '!', "Kí gửi đã hết hạn !");
			return 1;
		}
		if (prices[3] != me->get_number())
		{
			send_user(me, "%c%s", '!', "Bạn không phải là người kí gửi !");
			return 1;
		}
		if (prices[2] != 1)
		{
			send_user(me, "%c%s", '!', "Chưa hết hạn bạn không thể rút tiền !");
			return 1;
		}
		// if (prices[1] > time())
		// {
		// 	send_user(me, "%c%s", '!', "Vẫn còn thời gian bán !");
		// 	return 1;
		// }
		cancel_knb = (i * 10 + (i * 5 / 100 * 10));
		"sys/sys/test_db"->add_yuanbao(me, cancel_knb);
		send_user(me, "%c%s", '!', "Xóa thành công, nhận lại: " + cancel_knb / 10 + " Kim Nguyên Bảo!");
		send_user(me, "%c%c%d", 0x45, 2, "sys/sys/test_db"->get_yuanbao(me));
		map_delete(cardlist[i], value);
		send_user(me, "%c%c%d%d%d%d%d", 0x92, 3, value, 0, 0, 0, 0);
		save_object(SAVE_FILE);
		log_file("consign.txt", sprintf("%s : %s (%d) đã hủy bỏ và nhận lại %d Kim nguyên bảo ký gửi \n", short_time(time()), me->get_name(), me->get_number(), cancel_knb / 10));
		break;
	case "get": // 拿回卖点卡的钱
		if (sizeof(key) != 2)
			return;
		//restore_object(SAVE_FILE);
		value = to_int(key[1]);
		prices = cardlist[50][value];
		//printf(prices);
		//CHAT_D->vip_channel(1, sprintf(CHAT " %s : %d ", "Tran", value));
		i = 50;
		if (prices == 0)
		{
			prices = cardlist[100][value];
			i = 100;
		}
		if (prices == 0)
		{
			prices = cardlist[200][value];
			i = 200;
		}
		if (prices == 0)
		{
			send_user(me, "%c%s", '!', "Kí gửi đã hết hạn !");
			return 1;
		}
		if (prices[3] != me->get_number())
		{
			send_user(me, "%c%s", '!', "Bạn không phải là người kí gửi !");
			return 1;
		}
		if (prices[2] != 2)
		{
			send_user(me, "%c%s", '!', "Chưa được bán bạn không thể rút tiền !");
			return 1;
		}
		me->add_cash(prices[0]);
		send_user(me, "%c%s", '!', "Lấy thành công !");
		send_user(me, "%c%c%d", 0x45, 2, "sys/sys/test_db"->get_yuanbao(me));
		map_delete(cardlist[i], value);
		send_user(me, "%c%c%d%d%d%d%d", 0x92, 3, value, 0, 0, 0, 0);
		save_object(SAVE_FILE);
		log_file("consign.txt", sprintf("%s : %s (%d) đã rút %d Ngân Lượng\n", short_time(time()), me->get_name(), me->get_number(), prices[0]));
		//log_file("buycard.dat", sprintf("%s %s(%d) 赎回点卡成功\n", short_time(), me->get_id(), me->get_number()));
		break;
	}
	return 1;
}
