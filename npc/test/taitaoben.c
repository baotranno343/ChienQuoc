/*------------------------------------
	NPC Tái Tạo by Ben
------------------------------------*/
#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <equip.h>
inherit OFFICER;
#define LPT "/npc/test/taitaoben2"
// 函数：获取人物造型
int get_char_picid() { return 9968; }
void do_welcome(string arg);
void do_accept(string arg);
void taitao(object item, int abc);

void create()
{
	set_name("Lương Phan Tiên");
	set_2("talk", (["welcome":(
								  : do_welcome:),
					  "giaotrangbi":(
										: do_accept:),
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
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf(npc->get_name() + ":\n" + "Lương Phan Tiên có thể giúp bạn tái tạo chỉ số của trang bị, chỉ cần bạn đưa ông ta trang bị hoặc Vũ khí Lam Kim, Hoàng Kim thêm một ít ngân lượng là được. Có thể tái tạo nhiều lần, tuy nhiên chưa chắc là chỉ số của trang bị luôn trở nên tốt hơn, điều này còn tùy thuộc vào sự may mắn của bạn, trang bị hoặc vũ khí đã tinh luyện hay chế tạo thành cũng có thể tái tạo chỉ số.\n" ESC "ALT+G để giao trang bị\ntalk %x# welcome.2\n" ESC "Thoát ra\nCLOSE\n", getoid(npc)));
		break;
	case 2:
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), npc->get_name() + ":\n" + "Sử dụng ALT + G để đưa trang bị cho tôi !\n" ESC "Ta hiểu rồi\nCLOSE\n" ESC "Thoát ra\nCLOSE\n");
		break;
	}
}
void do_look(object player)
{
	object npc = this_object();

	send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s :\n" + "Thiên linh linh, địa linh linh, yêu ma quỷ quái hãy hiện hình, vị khách quan đây, ấn đường đen, nhất định có chuyện không hay xảy ra, hay là để bần đạo xem giúp một quẻ! Muốn hỏi về tình duyên hay sự nghiệp?\n" ESC "Tái Tạo trang bị Hoàng Kim\ntalk %x# welcome.1\n" ESC "Tái Tạo trang bị Lam Kim\ntalk %x# welcome.1\n" ESC "Rời khỏi\nCLOSE\n", npc->get_name(), getoid(npc), getoid(npc)));
}
void taitao(object item, int abc)
{
	return LPT->taitao(item, abc);
}
// 函数:接受物品
int accept_object(object who, object item) { return __FILE__->accept_object_callout(this_object(), who, item); }

// 函数:接受物品(在线更新)
int accept_object_callout(object me, object who, object item)
{
	int level, p, i, t1, t2, t3, t4, mau, cap, cap1, cap2, cap3;
	object item2;
	string sao, ngoc;
	me->to_front_eachother(who);
	if (!item->is_equip())
		return 0;
	if (item->is_equip())
	{
		i = item->get_equip_type();
		if (i != WEAPON_TYPE && i != ARMOR_TYPE && i != HEAD_TYPE && i != BOOTS_TYPE && i != WAIST_TYPE && i != NECK_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Lương Phan Tiên:\nBạn đưa tôi không phải là trang bị hoặc vũ khí !!!\n" ESC "Xác nhận");
			return -99;
		}
		if (i == WEAPON_TYPE && item->get_item_color() == 5)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Lương Phan Tiên:\nKhông thể tái tạo vũ khí Thần Binh!!!\n" ESC "Xác nhận");
			return -99;
		}
	}
	sao = item->get("forge");
	cap = strlen(sao);
	ngoc = item->get("make");
	cap1 = strlen(ngoc);
	cap2 = item->get_level();
	cap3 = item->get_level() / 2;
	mau = item->get_item_color();
	if (item->get_hide() > 0)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nHãy giám định %s trước khi Tái tạo !!!\n" ESC "Xác nhận", item->get_name()));
		return -99;
	}
	if (mau == 1)
	{
		if (who->get_save("giamtientaitao") < 1)
		{
			if (who->get_cash() < (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nKhông đủ %d lượng để Tái tạo chỉ số của %s !!!\n" ESC "Xác nhận", (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000), item->get_name()));
				return -99;
			}
			else
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nTái tạo chỉ số của %s cần tiêu hao %d lượng, bạn muốn tái tạo không ?\n" ESC "Xác nhận\ntalk %x# giaotrangbi.%x#\n" ESC "Huỷ bỏ", item->get_name(), (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000), getoid(me), getoid(item)));
			}
		}
		else
		{
			if (who->get_cash() < (cap * 22500) + (cap1 * 30000) + (cap2 * 500) + (cap3 * 500))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nKhông đủ %d lượng để Tái tạo chỉ số của %s !!!\n" ESC "Xác nhận", (cap * 22500) + (cap1 * 30000) + (cap2 * 500) + (cap3 * 500), item->get_name()));
				return -99;
			}
			else
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nTái tạo chỉ số của %s cần tiêu hao %d lượng, bạn muốn tái tạo không ? ( %s )\n" ESC "Xác nhận\ntalk %x# giaotrangbi.%x#\n" ESC "Huỷ bỏ", item->get_name(), (cap * 22500) + (cap1 * 30000) + (cap2 * 500) + (cap3 * 500), get_file_name(item), getoid(me), getoid(item)));
			}
		}
	}
	else if (mau == 2)
	{
		if (who->get_save("giamtientaitao") < 1)
		{
			if (who->get_cash() < (cap * 90000) + (cap1 * 120000) + (cap2 * 2000) + (cap3 * 2000))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nKhông đủ %d lượng để Tái tạo chỉ số của %s !!!\n" ESC "Xác nhận", (cap * 90000) + (cap1 * 120000) + (cap2 * 2000) + (cap3 * 2000), item->get_name()));
				return -99;
			}
			else
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nTái tạo chỉ số của %s cần tiêu hao %d lượng, bạn muốn tái tạo không ?\n" ESC "Xác nhận\ntalk %x# giaotrangbi.%x#\n" ESC "Huỷ bỏ", item->get_name(), (cap * 90000) + (cap1 * 120000) + (cap2 * 2000) + (cap3 * 2000), getoid(me), getoid(item)));
			}
		}
		else
		{
			if (who->get_cash() < (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nKhông đủ %d lượng để Tái tạo chỉ số của %s !!!\n" ESC "Xác nhận", (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000), item->get_name()));
				return -99;
			}
			else
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nTái tạo chỉ số của %s cần tiêu hao %d lượng, bạn muốn tái tạo không ?\n" ESC "Xác nhận\ntalk %x# giaotrangbi.%x#\n" ESC "Huỷ bỏ", item->get_name(), (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000), getoid(me), getoid(item)));
			}
		}
	}
	else if (mau == 5)
	{
		if (who->get_save("giamtientaitao") < 1)
		{
			if (who->get_cash() < (cap * 180000) + (cap1 * 140000) + (cap2 * 4000) + (cap3 * 4000))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nKhông đủ %d lượng để Tái tạo chỉ số của %s !!!\n" ESC "Xác nhận", (cap * 180000) + (cap1 * 140000) + (cap2 * 4000) + (cap3 * 4000), item->get_name()));
				return -99;
			}
			else
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nTái tạo chỉ số của %s cần tiêu hao %d lượng, bạn muốn tái tạo không ?\n" ESC "Xác nhận\ntalk %x# giaotrangbi.%x#\n" ESC "Huỷ bỏ", item->get_name(), (cap * 180000) + (cap1 * 140000) + (cap2 * 4000) + (cap3 * 4000), getoid(me), getoid(item)));
			}
		}
		else
		{
			if (who->get_cash() < (cap * 60000) + (cap1 * 120000) + (cap2 * 1500) + (cap3 * 1500))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nKhông đủ %d lượng để Tái tạo chỉ số của %s !!!\n" ESC "Xác nhận", (cap * 60000) + (cap1 * 120000) + (cap2 * 1500) + (cap3 * 1500), item->get_name()));
				return -99;
			}
			else
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nTái tạo chỉ số của %s cần tiêu hao %d lượng, bạn muốn tái tạo không ?\n" ESC "Xác nhận\ntalk %x# giaotrangbi.%x#\n" ESC "Huỷ bỏ", item->get_name(), (cap * 60000) + (cap1 * 120000) + (cap2 * 1500) + (cap3 * 1500), getoid(me), getoid(item)));
			}
		}
	}
	else if (mau == 3)
	{
		if (item->get_equip_type() == WEAPON_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Vũ khí " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == ARMOR_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Y phục " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == HEAD_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Nón " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == BOOTS_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Giày " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == WAIST_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Yêu đới " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == NECK_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Hạng liên " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
	}
	else if (mau == 4)
	{
		if (item->get_equip_type() == WEAPON_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Vũ khí " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == ARMOR_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Y phục " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == HEAD_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Nón " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == BOOTS_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Giày " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == WAIST_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Yêu đới " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == NECK_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Hạng liên " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
	}
	else if (mau == 0)
	{
		if (item->get_equip_type() == WEAPON_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Vũ khí " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == ARMOR_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Y phục " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == HEAD_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Nón " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == BOOTS_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Giày " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == WAIST_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Yêu đới " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == NECK_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Hạng liên " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
	}

	return -99;
}
// Bla bla
void do_accept(string arg) { return __FILE__->do_accept_callout(this_object(), this_player(), arg); }

// Bla bla
void do_accept_callout(object me, object who, string arg)
{
	int level, p, i, t1, t2, t3, t4, mau, cap, cap1, cap2, cap3, itemid;
	object item, item1;
	string sao, ngoc, forge = "";

	if (!objectp(item = present(arg, who, 1, MAX_CARRY * 4)))
		return 0;
	if (!item->is_equip())
		return 0;
	if (item->is_equip())
	{
		i = item->get_equip_type();
		if (i != WEAPON_TYPE && i != ARMOR_TYPE && i != HEAD_TYPE && i != BOOTS_TYPE && i != WAIST_TYPE && i != NECK_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Lương Phan Tiên:\nBạn đưa tôi không phải là trang bị hoặc vũ khí !!!\n" ESC "Xác nhận");
			return 0;
		}
		if (i == WEAPON_TYPE && item->get_item_color() == 5)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Lương Phan Tiên:\nKhông thể tái tạo vũ khí Thần Binh!!!\n" ESC "Xác nhận");
			return 0;
		}
	}
	sao = item->get("forge");
	cap = strlen(sao);
	ngoc = item->get("make");
	cap1 = strlen(ngoc);
	cap2 = item->get_level();
	cap3 = item->get_level() / 2;
	mau = item->get_item_color();
	if (item->get_hide() > 0)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nHãy giám định %s trước khi Tái tạo !!!\n" ESC "Xác nhận", item->get_name()));
		return 0;
	}
	if (mau == 1)
	{
		if (who->get_save("giamtientaitao") < 1)
		{
			if (who->get_cash() < (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nKhông đủ %d lượng để Tái tạo chỉ số của %s !!!\n" ESC "Xác nhận", (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000), item->get_name()));
				return 0;
			}
			if (random(100) < cap + cap1 + 1)
			{
				item->set("make", 0);
				item->delete ("app");
				item->delete ("ap");
				item->delete ("cp");
				item->delete ("dp");
				item->delete ("pp");
				item->delete ("hp");
				item->delete ("mp");
				item->delete ("sp");
				item->delete ("double");
				item->delete ("double2");
				item->delete ("!%");
				item->delete ("c!%");
				item->delete ("t!%");
				item->delete ("cpp");
				item->delete ("dpp");
				item->delete ("ppp");
				item->delete ("hpp");
				item->delete ("mpp");
				item->delete ("?%");
				item->delete ("c?%");
				item->delete ("hp*");
				item->delete ("mp*");
				item->delete ("hp+@");
				item->delete ("mp+@");
				item->delete ("cp+@");
				item->delete ("heal+@");
				taitao(item, 1);
				item->set_item_color(2);
				item->delete ("forge");
				"/sys/item/equip"->reset_equip_prop(item);
				for (i = 0; i < cap; i++)
				{
					"/sys/item/equip"->init_equip_prop_5(item);
					forge += "1";
					item->set("forge", forge);
				}
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);

				send_user(who, "%c%s", ';', sprintf("Xin chúc mừng ! %s của bạn đã trở thành trang bị Hoàng Kim !", item->get_name()));

				who->add_cash(-((cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000)));
			}
			else
			{
				item->set("make", 0);
				item->delete ("app");
				item->delete ("ap");
				item->delete ("cp");
				item->delete ("dp");
				item->delete ("pp");
				item->delete ("hp");
				item->delete ("mp");
				item->delete ("sp");
				item->delete ("double");
				item->delete ("double2");
				item->delete ("!%");
				item->delete ("c!%");
				item->delete ("t!%");
				item->delete ("cpp");
				item->delete ("dpp");
				item->delete ("ppp");
				item->delete ("hpp");
				item->delete ("mpp");
				item->delete ("?%");
				item->delete ("c?%");
				item->delete ("hp*");
				item->delete ("mp*");
				item->delete ("hp+@");
				item->delete ("mp+@");
				item->delete ("cp+@");
				item->delete ("heal+@");
				taitao(item, 1);
				item->delete ("forge");
				"/sys/item/equip"->reset_equip_prop(item);
				for (i = 0; i < cap; i++)
				{
					"/sys/item/equip"->init_equip_prop_5(item);
					forge += "1";
					item->set("forge", forge);
				}
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);

				send_user(who, "%c%s", ';', sprintf("Bạn đã dùng %d lượng để tái tạo chỉ số của %s !", (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000), item->get_name()));

				who->add_cash(-((cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000)));
			}
		}
		else
		{
			if (who->get_cash() < (cap * 22500) + (cap1 * 30000) + (cap2 * 500) + (cap3 * 500))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nKhông đủ %d lượng để Tái tạo chỉ số của %s !!!\n" ESC "Xác nhận", (cap * 22500) + (cap1 * 30000) + (cap2 * 500) + (cap3 * 500), item->get_name()));
				return 0;
			}
			if (random(100) < cap + cap1 + 1)
			{
				item->set("make", 0);
				item->delete ("app");
				item->delete ("ap");
				item->delete ("cp");
				item->delete ("dp");
				item->delete ("pp");
				item->delete ("hp");
				item->delete ("mp");
				item->delete ("sp");
				item->delete ("double");
				item->delete ("double2");
				item->delete ("!%");
				item->delete ("c!%");
				item->delete ("t!%");
				item->delete ("cpp");
				item->delete ("dpp");
				item->delete ("ppp");
				item->delete ("hpp");
				item->delete ("mpp");
				item->delete ("?%");
				item->delete ("c?%");
				item->delete ("hp*");
				item->delete ("mp*");
				item->delete ("hp+@");
				item->delete ("mp+@");
				item->delete ("cp+@");
				item->delete ("heal+@");
				taitao(item, 1);
				item->set_item_color(2);
				item->delete ("forge");
				"/sys/item/equip"->reset_equip_prop(item);
				for (i = 0; i < cap; i++)
				{
					"/sys/item/equip"->init_equip_prop_5(item);
					forge += "1";
					item->set("forge", forge);
				}
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);

				send_user(who, "%c%s", ';', sprintf("Xin chúc mừng ! %s của bạn đã trở thành trang bị Hoàng Kim !", item->get_name()));

				who->add_cash(-((cap * 22500) + (cap1 * 30000) + (cap2 * 500) + (cap3 * 500)));
				who->add_save("giamtientaitao", -1);
			}
			else
			{
				item->set("make", 0);
				item->delete ("app");
				item->delete ("ap");
				item->delete ("cp");
				item->delete ("dp");
				item->delete ("pp");
				item->delete ("hp");
				item->delete ("mp");
				item->delete ("sp");
				item->delete ("double");
				item->delete ("double2");
				item->delete ("!%");
				item->delete ("c!%");
				item->delete ("t!%");
				item->delete ("cpp");
				item->delete ("dpp");
				item->delete ("ppp");
				item->delete ("hpp");
				item->delete ("mpp");
				item->delete ("?%");
				item->delete ("c?%");
				item->delete ("hp*");
				item->delete ("mp*");
				item->delete ("hp+@");
				item->delete ("mp+@");
				item->delete ("cp+@");
				item->delete ("heal+@");
				taitao(item, 1);
				item->delete ("forge");
				"/sys/item/equip"->reset_equip_prop(item);
				for (i = 0; i < cap; i++)
				{
					"/sys/item/equip"->init_equip_prop_5(item);
					forge += "1";
					item->set("forge", forge);
				}
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);

				send_user(who, "%c%s", ';', sprintf("Bạn đã dùng %d lượng để tái tạo chỉ số của %s !", (cap * 22500) + (cap1 * 30000) + (cap2 * 500) + (cap3 * 500), item->get_name()));

				who->add_cash(-((cap * 22500) + (cap1 * 30000) + (cap2 * 500) + (cap3 * 500)));
				who->add_save("giamtientaitao", -1);
			}
		}
	}
	else if (mau == 2)
	{
		if (who->get_save("giamtientaitao") < 1)
		{
			if (who->get_cash() < (cap * 90000) + (cap1 * 120000) + (cap2 * 2000) + (cap3 * 2000))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nKhông đủ %d lượng để Tái tạo chỉ số của %s !!!\n" ESC "Xác nhận", (cap * 90000) + (cap1 * 120000) + (cap2 * 2000) + (cap3 * 2000), item->get_name()));
				return 0;
			}
			if (random(100) < 51)
			{
				item->set("make", 0);
				item->delete ("app");
				item->delete ("ap");
				item->delete ("cp");
				item->delete ("dp");
				item->delete ("pp");
				item->delete ("hp");
				item->delete ("mp");
				item->delete ("sp");
				item->delete ("double");
				item->delete ("double2");
				item->delete ("!%");
				item->delete ("c!%");
				item->delete ("t!%");
				item->delete ("cpp");
				item->delete ("dpp");
				item->delete ("ppp");
				item->delete ("hpp");
				item->delete ("mpp");
				item->delete ("?%");
				item->delete ("c?%");
				item->delete ("hp*");
				item->delete ("mp*");
				item->delete ("hp+@");
				item->delete ("mp+@");
				item->delete ("cp+@");
				item->delete ("heal+@");
				taitao(item, 1);
				//LPT->giamngoc(item);
				item->delete ("forge");
				"/sys/item/equip"->reset_equip_prop(item);
				for (i = 0; i < cap; i++)
				{
					"/sys/item/equip"->init_equip_prop_5(item);
					forge += "1";
					item->set("forge", forge);
				}
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);

				send_user(who, "%c%s", ';', sprintf("Bạn đã dùng %d lượng để tái tạo chỉ số của %s !", (cap * 90000) + (cap1 * 120000) + (cap2 * 2000) + (cap3 * 2000), item->get_name()));

				who->add_cash(-((cap * 90000) + (cap1 * 120000) + (cap2 * 2000) + (cap3 * 2000)));
			}
			else
			{
				item->set("make", 0);
				item->delete ("app");
				item->delete ("ap");
				item->delete ("cp");
				item->delete ("dp");
				item->delete ("pp");
				item->delete ("hp");
				item->delete ("mp");
				item->delete ("sp");
				item->delete ("double");
				item->delete ("double2");
				item->delete ("!%");
				item->delete ("c!%");
				item->delete ("t!%");
				item->delete ("cpp");
				item->delete ("dpp");
				item->delete ("ppp");
				item->delete ("hpp");
				item->delete ("mpp");
				item->delete ("?%");
				item->delete ("c?%");
				item->delete ("hp*");
				item->delete ("mp*");
				item->delete ("hp+@");
				item->delete ("mp+@");
				item->delete ("cp+@");
				item->delete ("heal+@");
				taitao(item, 2);
				//LPT->giamngoc(item);
				item->delete ("forge");
				"/sys/item/equip"->reset_equip_prop(item);
				for (i = 0; i < cap; i++)
				{
					"/sys/item/equip"->init_equip_prop_5(item);
					forge += "1";
					item->set("forge", forge);
				}
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);

				send_user(who, "%c%s", ';', sprintf("Bạn đã dùng %d lượng để tái tạo chỉ số của %s !", (cap * 90000) + (cap1 * 120000) + (cap2 * 2000) + (cap3 * 2000), item->get_name()));

				who->add_cash(-((cap * 90000) + (cap1 * 120000) + (cap2 * 2000) + (cap3 * 2000)));
			}
		}
		else
		{
			if (who->get_cash() < (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nKhông đủ %d lượng để Tái tạo chỉ số của %s !!!\n" ESC "Xác nhận", (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000), item->get_name()));
				return 0;
			}
			if (random(100) < 51)
			{
				item->set("make", 0);
				item->delete ("app");
				item->delete ("ap");
				item->delete ("cp");
				item->delete ("dp");
				item->delete ("pp");
				item->delete ("hp");
				item->delete ("mp");
				item->delete ("sp");
				item->delete ("double");
				item->delete ("double2");
				item->delete ("!%");
				item->delete ("c!%");
				item->delete ("t!%");
				item->delete ("cpp");
				item->delete ("dpp");
				item->delete ("ppp");
				item->delete ("hpp");
				item->delete ("mpp");
				item->delete ("?%");
				item->delete ("c?%");
				item->delete ("hp*");
				item->delete ("mp*");
				item->delete ("hp+@");
				item->delete ("mp+@");
				item->delete ("cp+@");
				item->delete ("heal+@");
				taitao(item, 1);
				//LPT->giamngoc(item);
				item->delete ("forge");
				"/sys/item/equip"->reset_equip_prop(item);
				for (i = 0; i < cap; i++)
				{
					"/sys/item/equip"->init_equip_prop_5(item);
					forge += "1";
					item->set("forge", forge);
				}
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);

				send_user(who, "%c%s", ';', sprintf("Bạn đã dùng %d lượng để tái tạo chỉ số của %s !", (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000), item->get_name()));

				who->add_cash(-((cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000)));
				who->add_save("giamtientaitao", -1);
			}
			else
			{
				item->set("make", 0);
				item->delete ("app");
				item->delete ("ap");
				item->delete ("cp");
				item->delete ("dp");
				item->delete ("pp");
				item->delete ("hp");
				item->delete ("mp");
				item->delete ("sp");
				item->delete ("double");
				item->delete ("double2");
				item->delete ("!%");
				item->delete ("c!%");
				item->delete ("t!%");
				item->delete ("cpp");
				item->delete ("dpp");
				item->delete ("ppp");
				item->delete ("hpp");
				item->delete ("mpp");
				item->delete ("?%");
				item->delete ("c?%");
				item->delete ("hp*");
				item->delete ("mp*");
				item->delete ("hp+@");
				item->delete ("mp+@");
				item->delete ("cp+@");
				item->delete ("heal+@");
				taitao(item, 2);
				//LPT->giamngoc(item);
				item->delete ("forge");
				"/sys/item/equip"->reset_equip_prop(item);
				for (i = 0; i < cap; i++)
				{
					"/sys/item/equip"->init_equip_prop_5(item);
					forge += "1";
					item->set("forge", forge);
				}
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);

				send_user(who, "%c%s", ';', sprintf("Bạn đã dùng %d lượng để tái tạo chỉ số của %s !", (cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000), item->get_name()));

				who->add_cash(-((cap * 45000) + (cap1 * 60000) + (cap2 * 1000) + (cap3 * 1000)));
				who->add_save("giamtientaitao", -1);
			}
		}
	}

	// Huyết sắc
	else if (mau == 5)
	{
		if (who->get_save("giamtientaitao") < 1)
		{
			if (who->get_cash() < (cap * 180000) + (cap1 * 140000) + (cap2 * 4000) + (cap3 * 4000))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nKhông đủ %d lượng để Tái tạo chỉ số của %s !!!\n" ESC "Xác nhận", (cap * 180000) + (cap1 * 140000) + (cap2 * 4000) + (cap3 * 4000), item->get_name()));
				return 0;
			}
			if (random(100) < 51)
			{
				item->set("make", 0);
				item->delete ("app");
				item->delete ("ap");
				item->delete ("cp");
				item->delete ("dp");
				item->delete ("pp");
				item->delete ("hp");
				item->delete ("mp");
				item->delete ("sp");
				item->delete ("double");
				item->delete ("double2");
				item->delete ("!%");
				item->delete ("c!%");
				item->delete ("t!%");
				item->delete ("cpp");
				item->delete ("dpp");
				item->delete ("ppp");
				item->delete ("hpp");
				item->delete ("mpp");
				item->delete ("?%");
				item->delete ("c?%");
				item->delete ("hp*");
				item->delete ("mp*");
				item->delete ("hp+@");
				item->delete ("mp+@");
				item->delete ("cp+@");
				item->delete ("heal+@");
				taitao(item, 1);
				//LPT->giamngoc(item);
				item->delete ("forge");
				"/sys/item/equip"->reset_equip_prop(item);
				for (i = 0; i < cap; i++)
				{
					"/sys/item/equip"->init_equip_prop_5(item);
					forge += "1";
					item->set("forge", forge);
				}
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);

				send_user(who, "%c%s", ';', sprintf("Bạn đã dùng %d lượng để tái tạo chỉ số của %s !", (cap * 180000) + (cap1 * 140000) + (cap2 * 4000) + (cap3 * 4000), item->get_name()));

				who->add_cash(-((cap * 180000) + (cap1 * 140000) + (cap2 * 4000) + (cap3 * 4000)));
			}
			else
			{
				item->set("make", 0);
				item->delete ("app");
				item->delete ("ap");
				item->delete ("cp");
				item->delete ("dp");
				item->delete ("pp");
				item->delete ("hp");
				item->delete ("mp");
				item->delete ("sp");
				item->delete ("double");
				item->delete ("double2");
				item->delete ("!%");
				item->delete ("c!%");
				item->delete ("t!%");
				item->delete ("cpp");
				item->delete ("dpp");
				item->delete ("ppp");
				item->delete ("hpp");
				item->delete ("mpp");
				item->delete ("?%");
				item->delete ("c?%");
				item->delete ("hp*");
				item->delete ("mp*");
				item->delete ("hp+@");
				item->delete ("mp+@");
				item->delete ("cp+@");
				item->delete ("heal+@");
				taitao(item, 2);
				//LPT->giamngoc(item);
				item->delete ("forge");
				"/sys/item/equip"->reset_equip_prop(item);
				for (i = 0; i < cap; i++)
				{
					"/sys/item/equip"->init_equip_prop_5(item);
					forge += "1";
					item->set("forge", forge);
				}
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);

				send_user(who, "%c%s", ';', sprintf("Bạn đã dùng %d lượng để tái tạo chỉ số của %s !", (cap * 180000) + (cap1 * 140000) + (cap2 * 4000) + (cap3 * 4000), item->get_name()));

				who->add_cash(-((cap * 180000) + (cap1 * 140000) + (cap2 * 4000) + (cap3 * 4000)));
			}
		}
		else
		{
			if (who->get_cash() < (cap * 60000) + (cap1 * 120000) + (cap2 * 1500) + (cap3 * 1500))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\nKhông đủ %d lượng để Tái tạo chỉ số của %s !!!\n" ESC "Xác nhận", (cap * 60000) + (cap1 * 120000) + (cap2 * 1500) + (cap3 * 1500), item->get_name()));
				return 0;
			}
			if (random(100) < 51)
			{
				item->set("make", 0);
				item->delete ("app");
				item->delete ("ap");
				item->delete ("cp");
				item->delete ("dp");
				item->delete ("pp");
				item->delete ("hp");
				item->delete ("mp");
				item->delete ("sp");
				item->delete ("double");
				item->delete ("double2");
				item->delete ("!%");
				item->delete ("c!%");
				item->delete ("t!%");
				item->delete ("cpp");
				item->delete ("dpp");
				item->delete ("ppp");
				item->delete ("hpp");
				item->delete ("mpp");
				item->delete ("?%");
				item->delete ("c?%");
				item->delete ("hp*");
				item->delete ("mp*");
				item->delete ("hp+@");
				item->delete ("mp+@");
				item->delete ("cp+@");
				item->delete ("heal+@");
				taitao(item, 1);
				//LPT->giamngoc(item);
				item->delete ("forge");
				"/sys/item/equip"->reset_equip_prop(item);
				for (i = 0; i < cap; i++)
				{
					"/sys/item/equip"->init_equip_prop_5(item);
					forge += "1";
					item->set("forge", forge);
				}
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);

				send_user(who, "%c%s", ';', sprintf("Bạn đã dùng %d lượng để tái tạo chỉ số của %s !", (cap * 60000) + (cap1 * 120000) + (cap2 * 1500) + (cap3 * 1500), item->get_name()));

				who->add_cash(-((cap * 60000) + (cap1 * 120000) + (cap2 * 1500) + (cap3 * 1500)));
				who->add_save("giamtientaitao", -1);
			}
			else
			{
				item->set("make", 0);
				item->delete ("app");
				item->delete ("ap");
				item->delete ("cp");
				item->delete ("dp");
				item->delete ("pp");
				item->delete ("hp");
				item->delete ("mp");
				item->delete ("sp");
				item->delete ("double");
				item->delete ("double2");
				item->delete ("!%");
				item->delete ("c!%");
				item->delete ("t!%");
				item->delete ("cpp");
				item->delete ("dpp");
				item->delete ("ppp");
				item->delete ("hpp");
				item->delete ("mpp");
				item->delete ("?%");
				item->delete ("c?%");
				item->delete ("hp*");
				item->delete ("mp*");
				item->delete ("hp+@");
				item->delete ("mp+@");
				item->delete ("cp+@");
				item->delete ("heal+@");
				taitao(item, 2);
				//LPT->giamngoc(item);
				item->delete ("forge");
				"/sys/item/equip"->reset_equip_prop(item);
				for (i = 0; i < cap; i++)
				{
					"/sys/item/equip"->init_equip_prop_5(item);
					forge += "1";
					item->set("forge", forge);
				}
				item->add_to_user(get_d(item));
				send_user(who, "%c%d%c", 0x31, getoid(item), 0);

				send_user(who, "%c%s", ';', sprintf("Bạn đã dùng %d lượng để tái tạo chỉ số của %s !", (cap * 60000) + (cap1 * 120000) + (cap2 * 1500) + (cap3 * 1500), item->get_name()));

				who->add_cash(-((cap * 60000) + (cap1 * 120000) + (cap2 * 1500) + (cap3 * 1500)));
				who->add_save("giamtientaitao", -1);
			}
		}
	}
	else if (mau == 3)
	{
		if (item->get_equip_type() == WEAPON_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Vũ khí " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == ARMOR_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Y phục " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == HEAD_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Nón " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == BOOTS_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Giày " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == WAIST_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Yêu đới " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == NECK_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Hạng liên " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
	}
	else if (mau == 4)
	{
		if (item->get_equip_type() == WEAPON_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Vũ khí " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == ARMOR_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Y phục " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == HEAD_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Nón " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == BOOTS_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Giày " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == WAIST_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Yêu đới " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == NECK_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Hạng liên " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
	}
	else if (mau == 0)
	{
		if (item->get_equip_type() == WEAPON_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Vũ khí " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == ARMOR_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Y phục " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == HEAD_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Nón " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == BOOTS_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Giày " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == WAIST_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Yêu đới " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
		else if (item->get_equip_type() == NECK_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Lương Phan Tiên:\n%s không phải là " HIR "Hạng liên " NOR "Lam Kim, Hoàng Kim !!!\n" ESC "Xác nhận", item->get_name()));
		}
	}
	return 0;
}