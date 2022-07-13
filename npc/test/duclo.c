#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <equip.h>
inherit OFFICER;
// 函数：获取人物造型
int get_char_picid() { return 9956; }
void do_welcome(string arg);
void check_duc_lo(string arg);
void duc_lo(string arg);
void check_go_duc_lo(string arg);
void go_duc_lo(string arg);

void create()
{
	set_name("Đục Lỗ Trang Bị");
	set_real_name("Bồ Nguyên");
	set_2("talk", (["welcome":(
								  : do_welcome:),
						 "check_duc_lo":(
											: check_duc_lo:),
							   "duc_lo":(
											: duc_lo:),
					  "check_go_duc_lo":(
											: check_go_duc_lo:),
							"go_duc_lo":(
											: go_duc_lo:),
	]));
	setup();
}

void do_welcome(string arg)
{
	__FILE__->do_welcome2(this_object(), arg);
}
void do_welcome2(object npc, string arg)
{
	int flag;
	object player = this_player();
	flag = to_int(arg);
	switch (flag)
	{
	case 1:
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf(npc->get_name() + ":\n" + "Đục lỗ là việc cần thiết để nâng cao thuộc tính trang bị, gia tăng sức mạnh nhân vật. Một trang bị có thể đục tối đa được 3 lỗ, số tiền đục sẽ càng tăng theo số lỗ trên trang bị. Thế nào, có muốn đục lỗ cho trang bị của người không ?\n" ESC "Alt + G để giao trang bị\ntalk %x# welcome.2\n" ESC "Thoát ra\nCLOSE\n", getoid(npc)));
		break;
	case 2:
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), npc->get_name() + ":\n" + "Sử dụng Alt + G để đưa trang bị cho ta !\n" ESC "Ta hiểu rồi\nCLOSE\n" ESC "Thoát ra\nCLOSE\n");
		break;
	case 3:
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf(npc->get_name() + ":\n" + "Hãy chọn số lỗ mà ngươi muốn tháo gỡ và hủy bảo thạch cũ đi !\n" ESC "Gỡ lỗ thứ 1\ntalk %x# check_go_duc_lo.duc_lo.1\n" ESC "Gỡ lỗ thứ 2\ntalk %x# check_go_duc_lo.duc_lo.2\n" ESC "Gỡ lỗ thứ 3\ntalk %x# check_go_duc_lo.duc_lo.3\n" ESC "Thoát ra\nCLOSE\n", getoid(npc), getoid(npc), getoid(npc)));
		break;
	}
}
void do_look(object player)
{
	object npc = this_object();

	send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s :\n" + "Ta chính là thợ đục lỗ cho trang bị trong Chiến Quốc. Tuy nhiên đục lỗ trang bị tốn rất nhiều chi phí, thế nào, nhà ngươi có trang bị nào tốt cần đục lỗ khảm nạm không? Hãy đưa ta xem !\n" ESC "Tìm hiểu đục lỗ trang bị\ntalk %x# welcome.1\n" ESC "Rời khỏi\nCLOSE\n", npc->get_name(), getoid(npc), getoid(npc)));
}

int accept_object(object who, object item) { return __FILE__->accept_object_callout(this_object(), who, item); }

// 函数:接受物品(在线更新)
int accept_object_callout(object me, object who, object item)
{
	me->to_front_eachother(who);
	me->set("id_item", sprintf("%x#", getoid(item)));
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Bồ Nguyên:\n Ngươi muốn đục lỗ hay tháo gỡ và hủy bảo thạch ? Nên nhớ, một khi đã tháo gỡ bảo thạch, bảo thạch đó sẽ mất đi. Ta khuyên ngươi nên cân nhắc kỹ càng trước khi gỡ và hủy bảo thạch !!\n" ESC "Đục lỗ trang bị\ntalk %x# check_duc_lo.%x#\n" ESC "Tháo gỡ bảo thạch\ntalk %x# welcome.3\n" ESC "Huỷ bỏ", getoid(me), getoid(item), getoid(me), getoid(item)));
	return -99;
}
// 函数:接受物品
void check_duc_lo(string arg) { return __FILE__->check_duc_lo_callout(this_object(), this_player(), arg); }
// 函数:接受物品(在线更新)
void check_duc_lo_callout(object me, object who, string arg)
{
	object item;

	if (!objectp(item = present(me->get("id_item"), who, 1, MAX_CARRY * 4)))
		return 0;

	if (item->get("duc_lo.1"))
	{
		if (item->get("duc_lo.2"))
		{
			if (item->get("duc_lo.3"))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Trang bị đã khảm tối đa !\n" ESC "Xác nhận"));
			}
			else
			{

				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Đục lỗ thứ 3 cho trang bị này cần %d ngân lượng, tiến hành đục không ?\n" ESC "Xác nhận\ntalk %x# duc_lo.%x#\n" ESC "Huỷ bỏ", 15000000, getoid(me), getoid(item), getoid(me), getoid(item)));
			}
		}
		else
		{

			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Đục lỗ thứ 2 cho trang bị này cần %d ngân lượng, tiến hành đục không ?\n" ESC "Xác nhận\ntalk %x# duc_lo.%x#\n" ESC "Huỷ bỏ", 10000000, getoid(me), getoid(item), getoid(me), getoid(item)));
		}
	}
	else
	{

		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Đục lỗ thứ 1 cho trang bị này cần %d ngân lượng, tiến hành đục không ?\n" ESC "Xác nhận\ntalk %x# duc_lo.%x#\n" ESC "Huỷ bỏ", 5000000, getoid(me), getoid(item), getoid(me), getoid(item)));
	}

	return 0;
}
// Bla bla
void duc_lo(string arg) { return __FILE__->duc_lo_callout(this_object(), this_player(), arg); }
// Bla bla
void duc_lo_callout(object me, object who, string arg)
{
	int level, i, knb, nl, dct;
	object item;
	if (!objectp(item = present(me->get("id_item"), who, 1, MAX_CARRY * 4)))
		return 0;
	if (!item->is_equip())
		return 0;
	if (item->is_equip())
	{
		level = item->get_level();
		i = item->get_equip_type();
		if (i != WEAPON_TYPE && i != ARMOR_TYPE && i != HEAD_TYPE && i != BOOTS_TYPE && i != WAIST_TYPE && i != NECK_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Bồ Nguyên:\n Thứ ngươi giao cho ta không phải là trang bị hoặc vũ khí !\n" ESC "Xác nhận");
			return 0;
		}
	}

	if (item->get("duc_lo.1"))
	{
		if (item->get("duc_lo.2"))
		{
			if (item->get("duc_lo.3"))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Trang bị đã khảm tối đa !\n" ESC "Xác nhận"));
			}
			else
			{
				if (who->get_cash() < 15000000)
				{
					send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Không đủ %d ngân lượng để đục lỗ thứ 3 !\n" ESC "Xác nhận", 15000000));
					return 0;
				}
				else
				{

					who->add_cash(-15000000);
					item->set("duc_lo.3", 1);
					item->add_to_user(get_d(item));
					send_user(who, "%c%d%c", 0x31, getoid(item), 0);
					send_user(who, "%c%s", ';', sprintf("Trang bị %s đã đục lỗ thứ 3 thành công!", item->get_name()));
					return 0;
				}
			}
		}
		else
		{
			if (who->get_cash() < 10000000)
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Không đủ %d ngân lượng để đục lỗ thứ 2 !\n" ESC "Xác nhận", 10000000));
				return 0;
			}
			else
			{

				who->add_cash(-10000000);
				item->set("duc_lo.2", 1);
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);
				send_user(who, "%c%s", ';', sprintf("Trang bị %s đã đục lỗ thứ 2 thành công!", item->get_name()));
				return 0;
			}
		}
	}
	else
	{
		if (who->get_cash() < 5000000)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Không đủ %d ngân lượng để đục lỗ thứ 1 !\n" ESC "Xác nhận", 5000000));
			return 0;
		}
		else
		{
			who->add_cash(-5000000);
			item->set("duc_lo.1", 1);
			item->add_to_user(get_d(item));
			send_user(who, "%c%d%c", 0x31, getoid(item), 0);
			send_user(who, "%c%s", ';', sprintf("Trang bị %s đã đục lỗ thứ 1 thành công!", item->get_name()));
			return 0;
		}
	}
}
// 函数:接受物品
void check_go_duc_lo(string arg) { return __FILE__->check_go_duc_lo_callout(this_object(), this_player(), arg); }
// 函数:接受物品(在线更新)
void check_go_duc_lo_callout(object me, object who, string arg)
{
	object item;

	if (!objectp(item = present(me->get("id_item"), who, 1, MAX_CARRY * 4)))
		return 0;

	if (arg == "duc_lo.1")
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Bạn có muốn gỡ và hủy bảo thạch ở lỗ 1 không ?\n" ESC "Xác nhận\ntalk %x# go_duc_lo.duc_lo.1\n" ESC "Huỷ bỏ", getoid(me), getoid(item)));
	}
	if (arg == "duc_lo.2")
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Bạn có muốn gỡ và hủy bảo thạch ở lỗ 2 không ?\n" ESC "Xác nhận\ntalk %x# go_duc_lo.duc_lo.2\n" ESC "Huỷ bỏ", getoid(me), getoid(item)));
	}
	if (arg == "duc_lo.3")
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Bạn có muốn gỡ và hủy bảo thạch ở lỗ 3 không ?\n" ESC "Xác nhận\ntalk %x# go_duc_lo.duc_lo.3\n" ESC "Huỷ bỏ", getoid(me), getoid(item)));
	}
	return 0;
}

void go_duc_lo(string arg) { return __FILE__->go_duc_lo_callout(this_object(), this_player(), arg); }
void go_duc_lo_callout(object me, object who, string arg)
{
	int level, i, knb, nl, dct;
	object item;
	string *chi_so = ({"hp3", "ap3", "cp3", "dp3", "pp3"});

	if (!objectp(item = present(me->get("id_item"), who, 1, MAX_CARRY * 4)))
		return 0;
	if (!item->is_equip())
		return 0;
	if (item->is_equip())
	{
		level = item->get_level();
		i = item->get_equip_type();
		if (i != WEAPON_TYPE && i != ARMOR_TYPE && i != HEAD_TYPE && i != BOOTS_TYPE && i != WAIST_TYPE && i != NECK_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Bồ Nguyên:\n Thứ ngươi giao cho ta không phải là trang bị hoặc vũ khí !\n" ESC "Xác nhận");
			return 0;
		}
	}
	if (who->get_cash() < 100000)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Không đủ %d ngân lượng để tháo gỡ bảo thạch!\n" ESC "Xác nhận", 100000));
		return 0;
	}

	if (arg == "duc_lo.1" || arg == "duc_lo.2" || arg == "duc_lo.3")
	{
		if (!item->get(arg) || item->get(arg) == 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Có lỗ chưa được đục hoặc chưa khảm nạm bảo thạch!\n" ESC "Xác nhận"));
			return 0;
		}
		if (i == WEAPON_TYPE || i == HEAD_TYPE || i == NECK_TYPE)
		{
			if (TASK_LEGEND_D->check_task_item_amount(who, "Đá Mài Hổ Phách") < 1)
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Ngươi không có Đá Mài Hổ Phách !\n" ESC "Xác nhận"));
				return 0;
			}
			else
			{
				TASK_LEGEND_D->check_task_item1(who, "Đá Mài Hổ Phách", 1);
			}
		}
		if (i == ARMOR_TYPE || i == BOOTS_TYPE || i == WAIST_TYPE)
		{
			if (TASK_LEGEND_D->check_task_item_amount(who, "Đá Mài Lam Linh") < 1)
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Ngươi không có Đá Mài Lam Linh !\n" ESC "Xác nhận"));
				return 0;
			}
			else
			{
				TASK_LEGEND_D->check_task_item1(who, "Đá Mài Lam Linh", 1);
			}
		}

		for (i = 0; i < 5; i++)
		{
			if (item->get(chi_so[i]) > 1)
			{
				item->add(chi_so[i], -item->get(arg));
				item->set(arg, 1);
				break;
			}
		}
		who->add_cash(-100000);
		item->add_to_user(get_d(item));
		send_user(who, "%c%d%c", 0x31, getoid(item), 0);
		send_user(who, "%c%s", ';', sprintf("Trang bị %s đã tháo gỡ bảo thạch thành công!", item->get_name()));
		return 0;
	}
}
