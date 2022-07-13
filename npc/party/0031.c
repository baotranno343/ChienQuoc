#include <npc.h>
#include <city.h>
#include <ansi.h>
inherit SAVE_F;
inherit OFFICER;

void do_bonus(string arg);

// 函数：获取人物造型
int get_char_picid() { return 6009; }

// 函数：构造处理
void create()
{
	int i, size, *nTmp;
	set_name("Sứ Giả Phát Thưởng Chiến Quốc");

	set_2("talk", (["bonus":(
								: do_bonus:),
	]));

	setup();
}
//
void do_look(object who)
{
	__FILE__->do_look_2(who, this_object());
}

void do_look_2(object who, object me)
{
	int id;
	id = getoid(me);
	//	if ("/sys/sys/count"->get_hefu_time())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
				  me->get_name() + ":\n    Chào mừng, bạn của Chiến Quốc Loạn Thế Anh Hùng . Hãy tin tôi, trong thế giới này, bạn nhất địm tìm thấy niềm vui như mong đợi!\n" + sprintf(ESC "客户端抽奖奖品领取\ntalk %x# bonus.1004\n" ESC "探宝卡之探险大礼包领取\ntalk %x# bonus.1005\n" ESC "充卡有奖之紫参丹领取\ntalk %x# bonus.1006\n" ESC "直充有奖之兑奖牌领取\ntalk %x# bonus.1007\n"
																																															//			ESC"物品激活码之无敌宝宝包领取\ntalk %x# bonus.1008\n"
																																															//			ESC"Lãnh trứng Bảo Thú\ntalk %x# bonus.1012\n"
																																															ESC "兑奖牌换取奖励\ntalk %x# bonus.10\n" ESC "领取合服大奖\ntalk %x# bonus.20\n" ESC "领取黄金兑奖卡升级版奖品\ntalk %x# bonus.1014\n"
																																															//			ESC"猪年充值送神猪\ntalk %x# bonus.1015\n"
																																															//			ESC"Lãnh Thần Thú\ntalk %x# bonus.1017\n"
																																															ESC "Lãnh Thần Thú\ntalk %x# bonus.33\n" ESC "领取推广员奖励\ntalk %x# bonus.37\n" ESC "充值领骑宠的活动\ntalk %x# bonus.1016\n" ESC "领取龙卷风大礼包\ntalk %x# bonus.32\n" ESC "领取龙卷风抽奖奖品\ntalk %x# bonus.1020\n" ESC +
																																															HIY "修复锻造异常的装备\ntalk %x# bonus.30\n" ESC + HIY "补发七夕戒指\ntalk %x# bonus.31\n" ESC "Rời khỏi",
																																														id, id, id, id, id, id, id, id, id, id, id, id, id, id, ));
	}
	/*	else
	{
		send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
			me->get_name()+":\n    欢迎你，大话战国的朋友。相信我，在这个世界里，你一定能够找到你想要的快乐！\n"
			+ sprintf(ESC"客户端抽奖奖品领取\ntalk %x# bonus.1004\n"
			ESC"探宝卡之探险大礼包领取\ntalk %x# bonus.1005\n"
			ESC"充卡有奖之紫参丹领取\ntalk %x# bonus.1006\n"
			ESC"直充有奖之兑奖牌领取\ntalk %x# bonus.1007\n"
//			ESC"物品激活码之无敌宝宝包领取\ntalk %x# bonus.1008\n"
//			ESC"宠物蛋领取\ntalk %x# bonus.1012\n"
			ESC"兑奖牌换取奖励\ntalk %x# bonus.10\n"
			ESC"领取黄金兑奖卡升级版奖品\ntalk %x# bonus.1014\n"
//			ESC"猪年充值送神猪\ntalk %x# bonus.1015\n"
//			ESC"领取神兽\ntalk %x# bonus.1017\n"
			ESC"领取神兽\ntalk %x# bonus.33\n"
			ESC"充值领骑宠的活动\ntalk %x# bonus.1016\n"
			ESC"领取龙卷风大礼包\ntalk %x# bonus.32\n"
			ESC"领取龙卷风抽奖奖品\ntalk %x# bonus.1020\n"
			ESC+HIY"补发七夕戒指\ntalk %x# bonus.31\n"
			ESC+HIY"修复锻造异常的装备\ntalk %x# bonus.30\n"
			ESC"离开", id, id, id, id, id, id, id, id, id, id, id, id, ) );
	}*/
}

void do_bonus(string arg)
{
	__FILE__->do_bonus_2(this_player(), this_object(), arg);
}

void do_bonus_2(object me, object who, string arg)
{
	int i, flag, type, p, total, count, amount, status, id, bonus, level, ii;
	string arg2, *key, name, result, var;
	object item, item2;
	flag = to_int(arg);
	status = me->get_pay_money_buy_item();
	id = getoid(who);
	bonus = me->get_save("phpbonus");
	if (bonus > 0)
	{
		me->delete_save("phpbonus");
		__FILE__->give_bonus(me, bonus);
		return;
	}
	if (status == 0)
	{
		switch (flag)
		{
		case 10:
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					  who->get_name() + ":\n    你有兑奖牌吗？如果你有兑奖牌，就给予（Alt+G键）我吧！你将会有意想不到的收获哦～！\n" + sprintf(ESC "给予\ntalk %x# bonus.11\n" ESC "离开", id));
			break;
		case 11:
			send_user(me, "%c%c%c%d%s", 0x90, 1, 0, id, who->get_name());
			break;
		case 20:
			ii = "/sys/sys/count"->get_hefu_ii();
			if (ii)
				var = sprintf("hefu_bonus%d", ii);
			else
				var = "hefu_bonus";
			if (me->get_save(var) > 0)
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
						  who->get_name() + ":\n    您已领取合服奖励了。\n" ESC "离开");
				return;
			}
			i = "/sys/sys/count"->get_hefu_time();
			if (i == 0)
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
						  who->get_name() + ":\n    现在没有合服的奖励。\n" ESC "离开");
				return;
			}
			if (me->get_birthday() > i)
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
						  who->get_name() + ":\n    你是合并服务器之后建立的角色呀？不能领取合服大奖了！\n" ESC "离开");
				return;
			}
			level = me->get_level();
			if (level < 30)
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
						  who->get_name() + ":\n    你的等级不足30级，还不可以领取合服的奖励。\n" ESC "离开");
				return;
			}
			i = 1;
			if (level >= 40)
				i = 2;
			if (sizeof_inventory(me, 1, MAX_CARRY) > MAX_CARRY - 2)
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
						  who->get_name() + ":\n    你的包袱已满，请清理一下你的包包再来找我吧～！\n" ESC "离开");
				return;
			}
			if (level < 40)
				item = new ("/item/sell/0041");
			else if (level < 50)
			{
				item = new ("/item/08/0003");
				item2 = new ("/item/08/0004");
			}
			else if (level < 70)
			{
				item = new ("/item/sell/0002");
				item2 = new ("/item/sell/0004");
			}
			else if (level < 90)
			{
				item = new ("/item/sell/0060");
				item2 = new ("/item/91/9178");
			}
			else
			{
				item = new ("/item/sell/0025");
				item2 = new ("/item/sell/0202");
			}
			me->set_save(var, 1);
			if (item)
			{
				result = item->get_name();
				if (item->get_max_combined() > 1)
				{
					total = 1;
					amount = USER_INVENTORY_D->carry_combined_item(me, item, total);
					if (amount > 0 && item->set_amount(amount))
					{
						if (p = item->move(me, -1))
						{
							item->add_to_user(p);
						}
					}
					else
					{
						item->add_amount(-total);
					}
				}
				else
				{
					if (p = item->move(me, -1))
					{
						item->add_to_user(p);
					}
				}
			}
			if (item2)
			{
				result = result + "、" + item2->get_name();
				if (item2->get_max_combined() > 1)
				{
					total = 1;
					amount = USER_INVENTORY_D->carry_combined_item(me, item2, total);
					if (amount > 0 && item2->set_amount(amount))
					{
						if (p = item2->move(me, -1))
						{
							item2->add_to_user(p);
						}
					}
					else
					{
						item2->add_amount(-total);
					}
				}
				else
				{
					if (p = item2->move(me, -1))
					{
						item2->add_to_user(p);
					}
				}
			}
			send_user(me, "%c%s", ':', "领取合服大奖成功，您获得" + result + "。");
			break;
		case 30:
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					  sprintf("%s:\n    你可以利用" HIR "给予（Alt＋G）" NOR "的指令，将之前使用旧锻造石锻造的装备交给我。根据锻造的等级，我可以帮助你重新恢复一件新的装备出来，除了锻造的属性会根据新规则生成外，你这件装备原来的属性都是不会改变的。\n" ESC "离开", who->get_name()));
			break;
		case 31:
			if (USER_INVENTORY_D->count_empty_carry(me) < 1)
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
						  who->get_name() + ":\n    你的包袱已满，请清理一下你的包包再来找我吧～！\n" ESC "离开");
				return;
			}
			if (me->get_save_2("qixi.finish2") == 1)
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
						  who->get_name() + ":\n    已经补发给你了！\n" ESC "离开");
				return;
			}
			if (me->get_number() == 215810 || me->get_number() == 451659 || me->get_number() == 383602 || me->get_number() == 47471 || me->get_number() == 208984 || me->get_number() == 430823 || me->get_number() == 408119 || me->get_number() == 105052 || me->get_number() == 383908 || me->get_number() == 132919 || me->get_number() == 548684 || me->get_number() == 137917 || me->get_number() == 18379 || me->get_number() == 556972 || me->get_number() == 444359 || me->get_number() == 443060 || me->get_number() == 420978 || me->get_number() == 59860 || me->get_number() == 78570)
			{
				if (me->get_gender() == 1)
					item = new ("item/04/ring1");
				else
					item = new ("item/04/ring2");
				p = item->move(me, -1);
				item->add_to_user(p);
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), sprintf("%s：\n    对您造成的不便，深表歉意。\n" ESC "离开", who->get_name()));
				send_user(me, "%c%s", ';', sprintf(HIR "补发情比金坚戒成功"));
				me->delete_save_2("qixi.flag");
				me->set_save_2("qixi.finish2", 1);
			}
			else
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), sprintf("%s：\n    你并不是应补发的玩家。\n" ESC "离开", who->get_name()));
			break;
		case 32:
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					  sprintf("%s:\n    你身上已经有水瓶宠物了，如果你的充值额足够再次领取水瓶宠物将会增加14天的使用时间；如果你身上没有的话，将会得到一只。\n" ESC "领取龙卷风礼包\ntalk %x# bonus.1018\n" ESC "领取水瓶宠物\ntalk %x# bonus.1019\n" ESC "离开", who->get_name(), id, id));
			break;
		case 33:
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					  sprintf("%s:\n    领取宠物——双子\n" ESC "领取忠厚的双子（一只）\ntalk %x# bonus.34\n" ESC "领取勇敢的双子（一只）\ntalk %x# bonus.35\n" ESC "领取英明的双子（一只）\ntalk %x# bonus.36\n" ESC "离开", who->get_name(), id, id, id));
			break;
		case 34:
			if (objectp(present("忠厚的双子", me, 1, MAX_CARRY * 4)))
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
						  sprintf("%s:\n    您已经领取了一个忠厚的双子，如果您继续领取系统将会为您的双子增加14天的使用时间，您确定要这样做么吗？\n" ESC "确定\ntalk %x# bonus.1021\n" ESC "离开", who->get_name(), id));
				return;
			}
			do_bonus_2(me, who, "1021");
			break;
		case 35:
			if (objectp(present("勇敢的双子", me, 1, MAX_CARRY * 4)))
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
						  sprintf("%s:\n    您已经领取了一个勇敢的双子，如果您继续领取系统将会为您的双子增加14天的使用时间，您确定要这样做么吗？\n" ESC "确定\ntalk %x# bonus.1022\n" ESC "离开", who->get_name(), id));
				return;
			}
			do_bonus_2(me, who, "1022");
			break;
		case 36:
			if (objectp(present("英明的双子", me, 1, MAX_CARRY * 4)))
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
						  sprintf("%s:\n    您已经领取了一个英明的双子，如果您继续领取系统将会为您的双子增加14天的使用时间，您确定要这样做么吗？\n" ESC "确定\ntalk %x# bonus.1023\n" ESC "离开", who->get_name(), id));
				return;
			}
			do_bonus_2(me, who, "1023");
			break;
		case 37:
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					  sprintf("%s:\n    请选择推广员奖励等级。\n" ESC "领取10级奖励\ntalk %x# bonus.38\n" ESC "领取40级奖励\ntalk %x# bonus.39\n" ESC "领取70级奖励\ntalk %x# bonus.40\n" ESC "离开", who->get_name(), id, id, id));
			break;
		case 38:
			if (me->get_level() < 10)
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), sprintf("%s:\n    您不符合领取条件！！！" ESC "离开", who->get_name()));
				return;
			}
			do_bonus_2(me, who, "1024");
			break;
		case 39:
			if (me->get_level() < 40)
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), sprintf("%s:\n    您不符合领取条件！！！" ESC "离开", who->get_name()));
				return;
			}
			do_bonus_2(me, who, "1025");
			break;
		case 40:
			if (me->get_level() < 70)
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), sprintf("%s:\n    您不符合领取条件！！！" ESC "离开", who->get_name()));
				return;
			}
			do_bonus_2(me, who, "1026");
			break;

		case 1004:
			count = 6;
		case 1005:
			if (count == 0)
				count = 5;
		case 1006:
			if (count == 0)
				count = 1;
		case 1007:
			if (count == 0)
				count = 2;
		case 1012:
			if (count == 0)
				count = 3;
		case 1008:
		case 1011:
		case 1014:
		case 1015:
		case 1016:
		case 1017:
		case 1018:
		case 1019:
		case 1020:
		case 1021:
		case 1022:
		case 1023:
		case 1024:
		case 1025:
		case 1026:
			if (count == 0)
				count = 1;
			if (sizeof_inventory(me, 1, MAX_CARRY) > MAX_CARRY - count)
			{
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
						  who->get_name() + ":\n    你的包袱已满，请清理一下你的包包再来找我吧～！\n" ESC "离开");
				return;
			}
			me->set("phpnum", flag);
			me->set_pay_money_buy_item(1);
			me->set_pay_type(4);
			me->set_buy_item_cmd_string(sprintf("%x# bonus.", getoid(who)));
			db_user_pay(me, sprintf("%s:80\n"
									"GET http:/"
									"/%s/getgoods.php?t=%s&u=%d&o=%d&n=%s&ip=%s&r=%d&h=%d\r\n",
									MAIN_D->get_php_ip(),
									MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), me->get_number(), arg, get_ip_name(me), MAIN_D->get_region(), MAIN_D->get_host()));
			log_file("php.dat", sprintf("%s:80\n"
										"GET http:/"
										"/%s/getgoods.php?t=%s&u=%d&o=%d&n=%s&ip=%s&r=%d&h=%d\r\n",
										MAIN_D->get_php_ip(),
										MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), me->get_number(), arg, get_ip_name(me), MAIN_D->get_region(), MAIN_D->get_host()));
			log_file("getitem.txt", sprintf("%s %s %d %s\n", short_time(), me->get_id(), me->get_number(), arg));
			break;
		}
		return;
	}
	if (status != 8)
	{
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
				  who->get_name() + ":\n    您的申请正在处理中，请稍候。\n" ESC "离开");
		return;
	}
	//if (MAIN_D->get_host_type()==0 ) flag = 101416;
	switch (flag)
	{
	case 10041:
		count = 5;
		break;
	case 10051:
		count = 5;
		break;
	case 10061:
	case 101401..101420:
	case 101501:
	case 101601:
	case 101701:
	case 101801:
	case 101901:
	case 102001:
	case 102101:
	case 102201:
	case 102301:
	case 102401:
	case 102501:
	case 102601:
		count = 1;
		break;
	case 10071:
	case 10072:
	case 10073:
	case 10074:
		count = 2;
		break;
	case 10081:
	case 101101:
	case 101102:
		count = 1;
		break;
	case 101201:
	case 101202:
	case 101203:
		count = 3;
		break;
	}
	if (sizeof_inventory(me, 1, MAX_CARRY) > MAX_CARRY - count)
	{
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
				  who->get_name() + ":\n    你的包袱已满，请清理一下你的包包再来找我吧～！\n" ESC "离开");
		me->set_save("phpbonus", flag);
		return;
	}
	me->set_pay_money_buy_item(0);
	__FILE__->give_bonus(me, flag);
}

void give_bonus(object me, int type)
{
	int i, p, total, amount, count, level;
	string result, *nTmp2, tmp;
	object item;
	int *name = ({
		6000,
		6510,
		8810,
		7210,
		6100,
		6610,
		8810,
		7210,
	});
	int *armor = ({101, 102, 104, 105, 106});
	switch (type)
	{
	case 10041:
		count = 5;
		break;
	case 10051:
		count = 5;
		break;
	case 10061:
	case 10081:
	case 101101:
	case 101102:
	case 101401..101420:
	case 101501:
	case 101601:
	case 101701:
	case 101801:
	case 101901:
	case 102001:
	case 102101:
	case 102201:
	case 102301:
	case 102401:
	case 102501:
	case 102601:
		count = 1;
		break;
	case 10071:
	case 10072:
	case 10073:
	case 10074:
		count = 2;
		break;
	}
	if (sizeof_inventory(me, 1, MAX_CARRY) > MAX_CARRY - count)
	{
		send_user(me, "%c%c%w%s", ':', 3, get_char_picid(),
				  get_name() + ":\n    你的包袱已满，请清理一下你的包包再来找我吧～！\n" ESC "离开");
		me->set_save("phpbonus", type);
		return;
	}
	log_file("getitem.txt", sprintf("%s %s %d 领取%d成功\n", short_time(), me->get_id(), me->get_number(), type));
	result = "";
	switch (type)
	{
	case 10041:
		result = "";
		for (i = 0; i < 5; i++)
		{
			item = new ("/item/std/8000");
			if (item)
			{
				if (result == "")
					result = item->get_name();
				else
					result = result + "、" + item->get_name();
				if (item->get_max_combined() > 1)
				{
					total = 1;
					amount = USER_INVENTORY_D->carry_combined_item(me, item, total);
					if (amount > 0 && item->set_amount(amount))
					{
						if (p = item->move(me, -1))
						{
							item->add_to_user(p);
						}
					}
					else
					{
						item->add_amount(-total);
					}
				}
				else
				{
					if (p = item->move(me, -1))
					{
						item->add_to_user(p);
					}
				}
			}
		}
		send_user(me, "%c%s", ':', "您获得五张藏宝图。");
		break;
	case 10051:
		result = "";
		for (i = (me->get_gender() - 1) * 4; i < (me->get_gender() - 1) * 4 + 4; i++)
		{
			item = new (sprintf("/item/mop/%d", name[i]));
			if (item)
			{
				if (result == "")
					result = item->get_name();
				else
					result = result + "、" + item->get_name();
				if (item->get_max_combined() > 1)
				{
					total = 1;
					amount = USER_INVENTORY_D->carry_combined_item(me, item, total);
					if (amount > 0 && item->set_amount(amount))
					{
						if (p = item->move(me, -1))
						{
							item->add_to_user(p);
						}
					}
					else
					{
						item->add_amount(-total);
					}
				}
				else
				{
					if (p = item->move(me, -1))
					{
						item->add_to_user(p);
					}
				}
			}
		}
		item = new ("/item/mop/8000");
		if (item)
		{
			result = result + "、" + item->get_name();
			if (p = item->move(me, -1))
			{
				item->add_to_user(p);
			}
		}
		me->add_cash(10000);
		result = result + "、一万金";
		send_user(me, "%c%s", ':', "您获得" + result + "。");
		break;
	case 10061:
		item = new ("/item/91/9167");
		if (item)
		{
			result = item->get_name();
			if (p = item->move(me, -1))
			{
				item->add_to_user(p);
			}
		}
		send_user(me, "%c%s", ':', "您获得" + result + "。");
		break;
	case 10081:
	case 101101:
	case 101102:
		if (type == 10081)
			item = new ("/item/mop/0020");
		else if (type == 101101)
			item = new ("/item/mop/007");
		else
			item = new ("/item/mop/006");
		if (item)
		{
			result = item->get_name();
			if (p = item->move(me, -1))
			{
				item->add_to_user(p);
			}
			if (type == 10081)
				send_user(me, "%c%s", ':', "你已经成功领取无敌宝宝包。");
			else
				send_user(me, "%c%s", ':', "您已经领取了骑宠，赶紧骑上去秀一秀吧！");
		}
		break;
	case 10071:
	case 10072:
	case 10073:
	case 10074:
		item = new ("/item/mop/3601");
		if (item)
		{
			if (type == 10072)
				item->set_amount(4);
			else if (type == 10073)
				item->set_amount(7);
			else if (type == 10074)
				item->set_amount(12);
			total = item->get_amount();
			result = sprintf("%d个" + item->get_name(), total);

			amount = USER_INVENTORY_D->carry_combined_item(me, item, total);
			if (amount > 0 && item->set_amount(amount))
			{
				if (p = item->move(me, -1))
				{
					item->add_to_user(p);
				}
			}
			else
			{
				item->add_amount(-total);
			}
		}
		if (type == 10074)
		{
			item = new ("item/91/9178");
			if (item)
			{
				item->set_amount(2);
				total = item->get_amount();
				result += sprintf("、%d个" + item->get_name(), total);

				amount = USER_INVENTORY_D->carry_combined_item(me, item, total);
				if (amount > 0 && item->set_amount(amount))
				{
					if (p = item->move(me, -1))
					{
						item->add_to_user(p);
					}
				}
				else
				{
					item->add_amount(-total);
				}
			}
		}
		send_user(me, "%c%s", ':', "您获得" + result + "。");
		break;
	case 101203:
		item = new ("/item/mop/105");
		item->set_lock_time(time() + 31 * 24 * 3600);
		if (result == "")
			result = item->get_name();
		else
			result = item->get_name() + "、" + result;
		if (p = item->move(me, -1))
		{
			item->add_to_user(p);
		}
	case 101202:
		item = new ("/item/mop/106");
		item->set_lock_time(time() + 31 * 24 * 3600);
		if (result == "")
			result = item->get_name();
		else
			result = item->get_name() + "、" + result;
		if (p = item->move(me, -1))
		{
			item->add_to_user(p);
		}
	case 101201:
		item = new ("/item/mop/107");
		item->set_lock_time(time() + 31 * 24 * 3600);
		if (result == "")
			result = item->get_name();
		else
			result = item->get_name() + "、" + result;
		if (p = item->move(me, -1))
		{
			item->add_to_user(p);
		}
		send_user(me, "%c%s", ':', "您获得" + result + "。");
		break;
	case 101401:
		item = new ("/item/mop/107");
		item->set_lock_time(time() + 31 * 24 * 3600);
	case 101402:
		if (!item)
		{
			item = new ("/item/mop/106");
			item->set_lock_time(time() + 31 * 24 * 3600);
		}
	case 101403:
		if (!item)
		{
			item = new ("/item/mop/105");
			item->set_lock_time(time() + 31 * 24 * 3600);
		}
	case 101404:
		if (!item)
			item = new ("/item/std/9511");
	case 101405:
		if (!item)
			item = new ("/item/std/9521");
	case 101406:
		if (!item)
			item = new ("/item/std/9531");
	case 101407:
		if (!item)
			item = new ("/item/std/9541");
	case 101408:
		if (!item)
			item = new ("/item/std/9551");
	case 101409:
		if (!item)
			item = new ("/item/std/9561");
	case 101410:
		if (!item)
			item = new ("/item/std/9571");
	case 101411:
		if (!item)
			item = new ("/item/std/9581");
	case 101412:
		if (!item)
			item = new ("/item/sell/0025");
	case 101413:
		if (!item)
			item = new ("/item/sell/0032");
	case 101414:
		if (!item)
			item = new ("/item/sell/6002");
	case 101415:
		if (!item)
			item = new ("/item/08/0810");
	case 101416:
		if (!item)
		{
			item = new ("/quest/armor"->get_random_fam_level_equip(me->get_fam_name(), me->get_gender(), me->get_level()));
			"/sys/item/equip"->init_equip_prop_3(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			item->set("forge", "1");
			"/sys/item/equip"->init_equip_prop_5(item);
			item->set("forge", "11");
			"/sys/item/equip"->init_equip_prop_5(item);
			item->set("forge", "111");
			"/sys/item/equip"->init_equip_prop_5(item);
			item->set("forge", "1111");
			"/sys/item/equip"->init_equip_prop_5(item);
			item->set("forge", "11111");
			"/sys/item/equip"->init_equip_prop_5(item);
			item->set("forge", "111111");
			item->set_hide(0);
		}
	case 101417:
		if (!item)
			item = new ("/item/44/4489");
	case 101418:
		if (!item)
			item = new ("item/01/0008"); //凤凰玉佩
	case 101419:
		if (!item)
			item = new ("item/mop/9001"); //紫金钥匙、红木钥匙、青铜钥匙各1
	case 101420:
		if (!item)
			item = new ("item/mop/9002"); //金灵石5
		if (item && (p = item->move(me, -1)))
		{
			item->add_to_user(p);
			send_user(me, "%c%s", ':', "您获得" + item->get_name() + "。");
		}
		"/sys/sys/id"->add_cardcount(1);
		break;
	case 101501:
		item = new ("/item/08/0811");
		if (item && (p = item->move(me, -1)))
		{
			item->add_to_user(p);
			send_user(me, "%c%s", ':', "您获得" + item->get_name() + "。");
		}
		break;
	case 101601:
		item = new ("/item/mop/108");
		if (item && (p = item->move(me, -1)))
		{
			item->add_to_user(p);
			send_user(me, "%c%s", ':', "您获得" + item->get_name() + "。");
		}
		break;
	case 101701:
		item = new ("/item/08/0802");
		if (item && (p = item->move(me, -1)))
		{
			item->add_to_user(p);
			send_user(me, "%c%s", ':', "您获得" + item->get_name() + "。");
		}
		break;
	case 101801:
		item = new ("/item/mop/9004");
		if (item && (p = item->move(me, -1)))
		{
			item->add_to_user(p);
			send_user(me, "%c%s", ':', "您获得" + item->get_name() + "。");
		}
		break;
	case 101901:
		if (objectp(item = present("水瓶", me, 1, MAX_CARRY * 4)))
		{
			if (item->get_lock_time() == 0)
				item->set_lock_time(time() + 14 * 24 * 60 * 60);
			item->set_lock_time(item->get_lock_time() + 14 * 24 * 60 * 60);
			send_user(me, "%c%d", 0x31, getoid(item));
			send_user(me, "%c%s", ':', "您的水瓶宠使用时间增加了14天。");
		}
		else
		{
			item = new ("/item/08/shuiping");
			if (item && (p = item->move(me, -1)))
			{
				item->add_to_user(p);
				send_user(me, "%c%s", ':', "您获得" + item->get_name() + "。");
			}
		}
		break;

	case 102001:
		item = new ("/item/mop/9005");
		if (item && (p = item->move(me, -1)))
		{
			item->add_to_user(p);
			send_user(me, "%c%s", ':', "您获得" + item->get_name() + "。");
		}
		break;
	case 102101:
		if (objectp(item = present("忠厚的双子", me, 1, MAX_CARRY * 4)))
		{
			if (item->get_lock_time() == 0)
				item->set_lock_time(time() + 14 * 24 * 60 * 60);
			item->set_lock_time(item->get_lock_time() + 14 * 24 * 60 * 60);
			send_user(me, "%c%d", 0x31, getoid(item));
			send_user(me, "%c%s", ':', "您的宠物:忠厚的双子,使用时间增加了14天。");
			return;
		}
		item = new ("/item/08/0841");
		if (item && (p = item->move(me, -1)))
		{
			item->add_to_user(p);
			send_user(me, "%c%s", ':', "您获得了" + item->get_name() + "。");
		}
		break;
	case 102201:
		if (objectp(item = present("勇敢的双子", me, 1, MAX_CARRY * 4)))
		{
			if (item->get_lock_time() == 0)
				item->set_lock_time(time() + 14 * 24 * 60 * 60);
			item->set_lock_time(item->get_lock_time() + 14 * 24 * 60 * 60);
			send_user(me, "%c%d", 0x31, getoid(item));
			send_user(me, "%c%s", ':', "您的宠物:勇敢的双子,使用时间增加了14天。");
			return;
		}
		item = new ("/item/08/0842");
		if (item && (p = item->move(me, -1)))
		{
			item->add_to_user(p);
			send_user(me, "%c%s", ':', "您获得了" + item->get_name() + "。");
		}
		break;
	case 102301:
		if (objectp(item = present("英明的双子", me, 1, MAX_CARRY * 4)))
		{
			if (item->get_lock_time() == 0)
				item->set_lock_time(time() + 14 * 24 * 60 * 60);
			item->set_lock_time(item->get_lock_time() + 14 * 24 * 60 * 60);
			send_user(me, "%c%d", 0x31, getoid(item));
			send_user(me, "%c%s", ':', "您的宠物:英明的双子,使用时间增加了14天。");
			return;
		}
		item = new ("/item/08/0843");
		if (item && (p = item->move(me, -1)))
		{
			item->add_to_user(p);
			send_user(me, "%c%s", ':', "您获得了" + item->get_name() + "。");
		}
		break;

	case 102401:
		item = new ("item/08/0013"); //绑定的战国令
		if (item && (p = item->move(me, -1)))
		{
			item->add_to_user(p);
			send_user(me, "%c%s", ':', "您获得" + item->get_name() + "。");
		}
		break;
	case 102501:
		//		level=me->get_level();
		//		if (level>120) level=120;
		//		if (level>50 && me->get_fam_name()=="") level=50;
		nTmp2 = WEAPON_FILE->get_family_equip(me->get_fam_name(), me->get_gender(), 40, armor[random(5)]);
		tmp = nTmp2[random(sizeof(nTmp2))];
		item = new (tmp);
		"/sys/item/equip"->init_equip_prop_3(item);
		"/sys/item/equip"->init_equip_prop_5(item);
		item->set("forge", "1");
		"/sys/item/equip"->init_equip_prop_5(item);
		item->set("forge", "11");
		"/sys/item/equip"->init_equip_prop_5(item);
		item->set("forge", "111"); //三星金装
		item->set_hide(0);
		item->set_bind(4); //绑定
		if (item && (p = item->move(me, -1)))
		{
			item->add_to_user(p);
			send_user(me, "%c%s", ':', "您获得三星" + item->get_name() + "。");
		}
		break;
	case 102601:
		level = me->get_level();
		//		if (level>120) level=120;
		if (level > 50 && me->get_fam_name() == "")
			level = 50;
		else
			level = 70;
		nTmp2 = WEAPON_FILE->get_family_equip(me->get_fam_name(), me->get_gender(), level, 103);
		tmp = nTmp2[random(sizeof(nTmp2))];
		item = new (tmp);
		"/sys/item/equip"->init_equip_prop_3(item);
		"/sys/item/equip"->init_equip_prop_5(item);
		item->set("forge", "1");
		"/sys/item/equip"->init_equip_prop_5(item);
		item->set("forge", "11");
		"/sys/item/equip"->init_equip_prop_5(item);
		item->set("forge", "111");
		"/sys/item/equip"->init_equip_prop_5(item);
		item->set("forge", "1111");
		"/sys/item/equip"->init_equip_prop_5(item);
		item->set("forge", "11111"); //五星武器
		item->set_hide(0);
		item->set_bind(4); //绑定
		if (item && (p = item->move(me, -1)))
		{
			item->add_to_user(p);
			send_user(me, "%c%s", ':', "您获得五星" + item->get_name() + "。");
		}
		break;
	}
}

int accept_object(object me, object item)
{
	return __FILE__->accept_object2(me, this_object(), item);
}

int accept_object2(object me, object who, object item2)
{
	string result, forge;
	object item;
	object *user;
	int i, flag, p, total, amount, len;
	forge = item2->get("forge");
	len = strlen(forge);
	if (item2->is_equip() && len > 0)
	{
		"/sys/item/equip"->reset_equip_prop(item2);
		item2->delete ("forge");
		forge = "";
		for (i = 0; i < len; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item2);
			forge += "1";
			item2->set("forge", forge);
		}
		send_user(me, "%c%d%c", 0x31, getoid(item2), 0);
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
				  who->get_name() + ":\n    您的星级装备已经修复完毕。\n" ESC "离开");
		return -99;
	}
	if (item2->get_name() != "兑奖牌")
	{
		return 0;
	}
	if (sizeof_inventory(me, 1, MAX_CARRY) >= MAX_CARRY)
	{
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
				  who->get_name() + ":\n    你的包袱已满，请清理一下你的包包再来找我吧～！\n" ESC "离开");
		return -99;
	}
	result = sprintf("使用 %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item2->get_name(), "/sys/item/item"->get_pawn_save_string(item2), 1, item2->get_user_id(), get_z(me), get_x(me), get_y(me));
	//"/sys/user/cmd"->log_item(result);
	item2->add_amount(-1);
	i = random(10000);
	result = "";
	if (i < 1000)
	{
		me->add_exp(400);
		result = "400点经验";
	}
	else if (i < 2000)
	{
		me->add_potential(30);
		result = "30点潜能";
	}
	else if (i < 3000)
	{
		me->add_cash(1000);
		result = "1000金";
	}
	else if (i < 3500)
		item = new ("/quest/book"->get_book_file());
	else if (i < 4000)
		item = new ("/quest/book"->get_diamond_file());
	else if (i < 4500)
		item = new ("/item/std/8000");
	else if (i < 5000)
		item = new ("item/final/91/1808");
	else if (i < 5500)
		item = new ("item/final/91/1809");
	else if (i < 6000)
		item = new ("item/final/91/1810");
	else if (i < 6500)
		item = new ("item/final/91/1811");
	else if (i < 7000)
	{
		item = new ("item/std/5211");
		item->set_amount(3);
	}
	else if (i < 7500)
	{
		item = new ("item/91/9145");
		item->set_amount(2);
	}
	else if (i < 8000)
		item = new ("/item/91/9167");
	else if (i < 8500) //对应等级随机蓝装
	{
		if (random(2))
			item = new (ARMOR_FILE->get_armor_file_2(me->get_level()));
		else
			item = new (WEAPON_FILE->get_weapon_file_2(me->get_level()));
		ITEM_EQUIP_D->init_equip_prop_1(item);
	}
	else if (i < 8700)
		item = new ("/item/sell/0007");
	else if (i < 8900)
		item = new ("/item/sell/0009");
	else if (i < 9100)
		item = new ("/item/08/0002");
	else if (i < 9300)
		item = new ("/item/08/0004");
	else if (i < 9500)
		item = new ("/item/91/9178");
	else if (i < 9700)
		item = new ("/item/44/4404");
	else if (i < 9900)
		item = new ("/item/sell/0012");
	else if (i < 9925)
		item = new ("item/08/0001");
	else if (i < 9950)
		item = new ("/item/08/0003");
	else if (i < 9975)
		item = new ("/item/std/6001");
	else
	{
		if (random(2))
			item = new (ARMOR_FILE->get_armor_file_2(me->get_level()));
		else
			item = new (WEAPON_FILE->get_weapon_file_2(me->get_level()));
		ITEM_EQUIP_D->init_equip_prop_3(item);
	}
	if (item)
	{
		result = item->get_name();
		if (item->get_max_combined() > 1)
		{
			total = item->get_amount();
			amount = USER_INVENTORY_D->carry_combined_item(me, item, total);
			if (amount > 0 && item->set_amount(amount))
			{
				if (p = item->move(me, -1))
				{
					item->add_to_user(p);
				}
			}
			else
				item->add_amount(-total);
		}
		else
		{
			if (p = item->move(me, -1))
			{
				item->add_to_user(p);
			}
		}
	}
	user = USER_D->get_user();
	if (i >= 8500)
	{
		send_user(user, "%c%s", 0xA3, sprintf(HIY "恭喜%s玩家在兑换奖励时，获得了%s！", me->get_name(), result));
	}
	USER_D->user_channel(sprintf(HIY "恭喜%s玩家在兑换奖励时，获得了%s，大家向其表示祝贺！", me->get_name(), result));
	return -99;
}