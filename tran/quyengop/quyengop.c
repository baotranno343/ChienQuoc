#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <equip.h>
inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 1271; }
int is_seller() { return 1; }
int is_self_look() { return 1; }
void do_welcome(string arg);
void do_accept(string arg);
void create()
{
	set_name("Tiên Nhân");
	set_real_name("Tiêu Hủy Vật Phẩm");
	set_2("talk", (["welcome":(
								  : do_welcome:),
					  "accept":(
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
	int flag, p, i, size, diem, check;
	object *inv, item, player = this_player();
	flag = to_int(arg);
	switch (flag)
	{
	case 1:
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf(npc->get_name() + ":\n" + "Điểm Tiêu Hủy của ngươi hiện tại là: %d điểm. \nNếu ngươi đã có đủ điểm thì có thể đổi quà rồi!!\n" ESC "Túi Đoạn Thạch - 100 Điểm\ntalk %x# welcome.3\n" ESC "Túi Linh Thạch - 70 Điểm\ntalk %x# welcome.4\n" ESC "Thoát ra\nCLOSE\n", player->get_save("diem_tieuhuy"), getoid(npc), getoid(npc), getoid(npc), getoid(npc), getoid(npc)));
		break;
	case 2:
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), npc->get_name() + ":\n" + "Hãy nhấn phím Alt G để giao vật phẩm cho ta, sau đó ta sẽ kiểm tra nó có thể tiêu hủy hay không! \n" ESC "ALT+G để giao vật phẩm\nCLOSE\n" ESC "Thoát ra\nCLOSE\n");
		break;
	case 3:
	case 4:
		if (USER_INVENTORY_D->count_empty_carry(player) < 1)
		{
			send_user(player, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return;
		}
		if (flag == 3)
		{
			item = new ("item/test/tuiDT");
			diem = 100;
		}
		else if (flag == 4)
		{
			item = new ("item/test2/TuiLinhThach");
			diem = 70;
		}
		else
			return;
		if (player->get_save("diem_tieuhuy") < diem)
		{
			send_user(player, "%c%s", '!', sprintf("Điểm tiêu hủy của bạn không đủ %d điểm!", diem));
			destruct(item);
			return;
		}
		if (item)
		{
			p = item->move2(player, -1);
			item->add_to_user(p);
			player->add_save("diem_tieuhuy", -diem);
			send_user(player, "%c%s", '!', sprintf("Bạn dùng %d điểm tiêu hủy để đổi lấy %s", diem, item->get_name()));
			break;
		}
	case 5:
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf(npc->get_name() + ":\n" + "Bạn có chắc chắn muốn tiêu hủy tất các vật phẩm từ Túi Pháp Bảo và Túi Thần Thú có thể tiêu hủy ở túi 1 không, lưu ý sẽ không thể tiêu hủy Thần Thú Ma Yết và Đoạn Thạch \n" ESC "Đồng Ý Tiêu Hủy\ntalk %x# welcome.6\n" ESC "Thoát ra\nCLOSE\n", getoid(npc), getoid(npc), getoid(npc), getoid(npc), getoid(npc)));
		break;
	case 6:
		inv = all_inventory(player, 1, MAX_CARRY);

		for (i = 0, size = sizeof(inv); i < size; i++)
			if (objectp(item = inv[i]))
			{
				if (item->is_tieuhuy())
				{
					player->add_save("diem_tieuhuy", item->is_tieuhuy());
					write_user(player, sprintf(ECHO "Bạn tiêu hủy vật phẩm %s và nhận được %d điểm tiêu hủy", item->get_name(), item->is_tieuhuy()));
					item->remove_from_user();
					destruct(item);
					check = 1;
				}
			}
		if (!check)
		{
			send_user(player, "%c%s", '!', "Trong túi không có vật phẩm có thể tiêu hủy!");
		}
		break;
	default:
		break;
	}
	return;
}
void do_look(object player)
{
	object npc = this_object();
	send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s :\n" + "Điểm Tiêu Hủy của bạn hiện tại là: %d điểm\nNếu bạn muốn tiêu hủy vật phẩm hãy dùng những vật phẩm không cần thiết khi mở Túi Pháp Bảo hoặc Túi Thần Thú để tiêu hủy. \n" //
																			 ESC "Tiêu Hủy Vật Phẩm\ntalk %x# welcome.2\n"																																	   //
																			 ESC "Đổi Điểm Tiêu Hủy\ntalk %x# welcome.1\n"																																	   //																															   //
																			 ESC "Tiêu Hủy Nhiều Vật Phẩm Một Lúc\ntalk %x# welcome.5\n"																													   //
																			 ESC "Rời khỏi\nCLOSE\n",
																		 npc->get_name(), player->get_save("diem_tieuhuy"), getoid(npc), getoid(npc), getoid(npc))); //
																																									 //"sys/party/bxh_quyengop"->bxh_quyengop(player, npc);
																																									 //send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s :\n" + "%s ?\n" ESC "Làm cách nào để tiêu huỷ vật phẩm\ntalk %x# welcome.1\n" ESC "Mua vật phẩm\nlist %x#\n" ESC "Rời khỏi\nCLOSE\n", npc->get_name(), "sys/party/bxh_quyengop"->bxh_quyengop(player, npc), getoid(npc), getoid(npc)));
}

// 函数:接受物品
int accept_object(object who, object item) { return __FILE__->accept_object_callout(this_object(), who, item); }

// 函数:接受物品(在线更新)
int accept_object_callout(object me, object who, object item)
{
	int level, p, i;
	object item2;

	me->to_front_eachother(who);
	if (!item->is_tieuhuy())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\nTa chỉ nhận các vật phẩm từ Túi Pháp Bảo và Túi Thần Thú!!!!.\n" ESC "Rời khỏi", me->get_name()));
		return -99;
	}
	if (USER_INVENTORY_D->get_free_count(who) < 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\nHành trang của ngươi không đủ 1 ô trống.\n" ESC "Rời khỏi", me->get_name()));
		return -99;
	}

	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + sprintf("\nTiêu hủy vật phẩm này bạn có thể nhận được %d điểm tiêu hủy, bạn muốn Tiêu Hủy Vật Phẩm không ?\n" ESC "Xác nhận\ntalk %x# accept.%x#\n" ESC "Huỷ bỏ", item->is_tieuhuy(), getoid(me), getoid(item)));

	return -99;
}
// Bla bla
void do_accept(string arg) { return __FILE__->do_accept_callout(this_object(), this_player(), arg); }

// Bla bla
void do_accept_callout(object me, object who, string arg)
{
	int level, p, i;
	object item, item2;

	if (!objectp(item = present(arg, who, 1, MAX_CARRY * 4)))
		return 0;
	if (!item->is_tieuhuy())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\nTa chỉ nhận các vật phẩm từ Túi Pháp Bảo và Túi Thần Thú!!!!.\n" ESC "Rời khỏi", me->get_name()));
	}

	if (USER_INVENTORY_D->get_free_count(who) < 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\nHành trang của ngươi không đủ 1 ô trống.\n" ESC "Rời khỏi", me->get_name()));
		return 0;
	}
	who->add_save("diem_tieuhuy", item->is_tieuhuy());
	write_user(who, sprintf(ECHO "Bạn tiêu hủy vật phẩm %s và nhận được %d điểm tiêu hủy", item->get_name(), item->is_tieuhuy()));
	item->remove_from_user();
	destruct(item);

	// if (who->get_save("diem_quyengop") % 50 == 0)
	// {
	// 	item2 = new ("/item/91/9167"); // TSD
	// 	p = item2->move2(who, -1);
	// 	item2->add_to_user(p);
	// }

	return 0;
}