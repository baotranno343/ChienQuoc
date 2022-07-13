/*------------------------------------
	NPC Can Tương by Ben
	item/sell/6032 : Tái tạo thạch
------------------------------------*/
#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>
inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 9959; }
void do_welcome(string arg);
void do_nhannv(string arg);
//void do_accept(string arg);
int is_cantuong_nangcaptb() { return 1; }
void create()
{
	set_name("Can Tương");
	set_real_name("Thiên Địa Đại Sư");
	set_2("talk", (["welcome":(
								  : do_welcome:),
					  //   "giaotrangbi":(
					  // 					: do_accept:),
					  "nhannv":(
								   : do_nhannv:),
	]));
	setup();
}
void do_nhannv(string arg)
{
	"/sys/user/cantuong"->do_gift(this_player(), this_object(), arg);
}
void do_welcome(string arg)
{
	__FILE__->do_welcome2(this_object(), arg);
}
void do_welcome2(object npc, string arg)
{
	int flag, p, i, size, sao, ben, ben123, s;
	object player = this_player(), item, item2, item3;
	string name, name2, name3, name4, thanbinh, ss, forge = "", nhat123, nhat1234;
	flag = to_int(arg);
	switch (flag)
	{
	case 1:
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf(npc->get_name() + ":\n" + "Nếu muốn trang bị tốt hơn hiện tại, có thể đến gặp ta. Ta sẽ giúp ngươi rèn lại trang bị, nếu may mắn, ngươi có thể đạt được trang bị tinh luyện vượt mức đến 8 sao. Tuy nhiên điều này còn tuỳ thuộc vào vận may nữa, ta không dám nói trước.\n" ESC "ALT+G để giao trang bị\ntalk %x# welcome.200\n" ESC "Thoát ra\nCLOSE\n", getoid(npc)));
		break;
	case 200:
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), npc->get_name() + ":\n" + "Sử dụng ALT + G để đưa trang bị cho tôi !\n" ESC "Ta hiểu rồi\nCLOSE\n" ESC "Thoát ra\nCLOSE\n");
		break;
	case 300:
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf(npc->get_name() + ":\n" + "Thần binh tuyệt thế tưởng chừng chỉ là vũ khí có trong truyền thuyết, nhưng ngươi biết không? Nó có thật đấy! Nếu ngươi có trong tay Thần Binh Phổ, hãy mang đến đây, ta sẽ đúc nó cho ngươi.\n" ESC "Đúc thần binh Trụ Thiên Quyền Thủ\ntalk %x# welcome.1001\n" ESC "Đúc thần binh Đoạt Mệnh Ma Khí\ntalk %x# welcome.1002\n" ESC "Đúc thần binh Càn Khôn Vân Đao\ntalk %x# welcome.1003\n" ESC "Đúc thần binh Huyết Lệ\ntalk %x# welcome.1004\n" ESC "Đúc thần binh Phá Thiên Thương\ntalk %x# welcome.1005\n" ESC "Đúc thần binh Hoả Thiên Côn\ntalk %x# welcome.1006\n" ESC "%s\ntalk %x# nhannv.100\n" ESC "Thoát ra\nCLOSE\n", getoid(npc), getoid(npc), getoid(npc), getoid(npc), getoid(npc), getoid(npc), player->get_save_2("cantuong.status") < 1 ? HIG "Nhận nhiệm vụ tìm kiếm Thần Binh Phổ" : HIC "Nhiệm vụ tìm kiếm Thần Binh Phổ", getoid(npc), getoid(npc)));
		break;
	case 400:
		send_user(player, "%c%c%d", 0x60, 10, getoid(npc));
		break;

	case 1001:
	case 1002:
	case 1003:
	case 1004:
	case 1005:
	case 1006:
		if (flag == 1001)
		{
			ben = 2001;
			name = "Ngọc La Quyền Thủ";
			name2 = "Trụ Thiên Quyền Thủ";
			name3 = sprintf("Thần Binh Phổ - %s", name2);
		}
		else if (flag == 1002)
		{
			ben = 2002;
			name = "Thần Tiên Hạc Kim";
			name2 = "Đoạt Mệnh Ma Khí";
			name3 = sprintf("Thần Binh Phổ - %s", name2);
		}
		else if (flag == 1003)
		{
			ben = 2003;
			name = "Đao Tử Vân";
			name2 = "Càn Khôn Vân Đao";
			name3 = sprintf("Thần Binh Phổ - %s", name2);
		}
		else if (flag == 1004)
		{
			ben = 2004;
			name = "Lục Tiên Kiếm";
			name2 = "Huyết Lệ";
			name3 = sprintf("Thần Binh Phổ - %s", name2);
		}
		else if (flag == 1005)
		{
			ben = 2005;
			name = "Lục Thần Thương";
			name2 = "Phá Thiên Thương";
			name3 = sprintf("Thần Binh Phổ - %s", name2);
		}
		else if (flag == 1006)
		{
			ben = 2006;
			name = "Phàn Thiên Côn";
			name2 = "Hoả Thiên Côn";
			name3 = sprintf("Thần Binh Phổ - %s", name2);
		}
		if (!objectp(item = present(name, player, 1, MAX_CARRY * 4)))
		{
			send_user(player, "%c%c%w%s", ':', 3, 9959, sprintf("Can Tương: \nNgươi không có trong tay thần binh %s, không thể đúc Tuyệt thế thần binh %s ! \n" ESC "Xác nhận", name, name2));
			return;
		}
		if (TASK_LEGEND_D->check_task_item_amount(player, name) > 1)
		{
			send_user(player, "%c%c%w%s", ':', 3, 9959, sprintf("Can Tương: \nHành trang của ngươi quá có nhiều %s, ta không thể phân biệt được vũ khí nào mới là vũ khí mà ngươi ưng ý nhất ! \n" ESC "Xác nhận", name));
			return;
		}
		ss = item->get("forge");
		sao = strlen(ss);
		if (TASK_LEGEND_D->check_task_item_amount(player, name3) < 1 ||
			TASK_LEGEND_D->check_task_item_amount(player, "Tái Tạo Thạch") < (sao + 1) * 12 ||
			TASK_LEGEND_D->check_task_item_amount(player, "Lỗ Ban Bảo Thạch") < 300)
		{
			send_user(player, "%c%c%w%s", ':', 3, 9959, sprintf("Can Tương: \n Nguyên liệu của ngươi không đủ! Đúc %s cần các loại nguyên liệu sau:\n " + name + ", %s" NOR ", %s" NOR ", %s" NOR ".\n" ESC "Rời khỏi", name2, TASK_LEGEND_D->check_task_item_amount(player, "Lỗ Ban Bảo Thạch") < 300 ? HIR "300 viên Lỗ Ban" : "300 viên Lỗ Ban", TASK_LEGEND_D->check_task_item_amount(player, "Tái Tạo Thạch") < (sao + 1) * 12 ? sprintf(HIR "%d Tái Tạo Thạch", (sao + 1) * 12) : sprintf("%d Tái Tạo Thạch", (sao + 1) * 12), TASK_LEGEND_D->check_task_item_amount(player, name3) < 1 ? HIR + name3 : name3));
			return;
		}
		if (USER_INVENTORY_D->get_free_count(player) < 1)
		{
			send_user(player, "%c%c%w%s", ':', 3, 9959, "Can Tương: \nHành trang của ngươi không đủ 1 ô trống, hãy thu xếp hành trang rồi đến gặp ta ! \n" ESC "Xác nhận");
			return;
		}
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf(npc->get_name() + ":\n" + "Ngươi xác nhận phải đúc ra một Thần binh tuyệt thế %s không ?\n" ESC "Xác nhận\ntalk %x# welcome.%d\n" ESC "Huỷ bỏ\nCLOSE\n", name2, getoid(npc), ben));
		break;
	case 2001:
	case 2002:
	case 2003:
	case 2004:
	case 2005:
	case 2006:
		if (flag == 2001)
		{
			name = "Ngọc La Quyền Thủ";
			name2 = "Trụ Thiên Quyền Thủ";
			name3 = sprintf("Thần Binh Phổ - %s", name2);
			thanbinh = "/item/70/9130";
		}
		else if (flag == 2002)
		{
			name = "Thần Tiên Hạc Kim";
			name2 = "Đoạt Mệnh Ma Khí";
			name3 = sprintf("Thần Binh Phổ - %s", name2);
			thanbinh = "/item/71/9130";
		}
		else if (flag == 2003)
		{
			name = "Đao Tử Vân";
			name2 = "Càn Khôn Vân Đao";
			name3 = sprintf("Thần Binh Phổ - %s", name2);
			thanbinh = "/item/72/9130";
		}
		else if (flag == 2004)
		{
			name = "Lục Tiên Kiếm";
			name2 = "Huyết Lệ";
			name3 = sprintf("Thần Binh Phổ - %s", name2);
			thanbinh = "/item/73/9130";
		}
		else if (flag == 2005)
		{
			name = "Lục Thần Thương";
			name2 = "Phá Thiên Thương";
			name3 = sprintf("Thần Binh Phổ - %s", name2);
			thanbinh = "/item/74/9130";
		}
		else if (flag == 2006)
		{
			name = "Phàn Thiên Côn";
			name2 = "Hoả Thiên Côn";
			name3 = sprintf("Thần Binh Phổ - %s", name2);
			thanbinh = "/item/75/9130";
		}
		if (!objectp(item = present(name, player, 1, MAX_CARRY * 4)))
		{
			send_user(player, "%c%c%w%s", ':', 3, 9959, sprintf("Can Tương: \nNgươi không có trong tay thần binh %s, không thể đúc Tuyệt thế thần binh %s ! \n" ESC "Xác nhận", name, name2));
			return;
		}
		if (TASK_LEGEND_D->check_task_item_amount(player, name) > 1)
		{
			send_user(player, "%c%c%w%s", ':', 3, 9959, sprintf("Can Tương: \nHành trang của ngươi quá có nhiều %s, ta không thể phân biệt được vũ khí nào mới là vũ khí mà ngươi ưng ý nhất ! \n" ESC "Xác nhận", name));
			return;
		}
		ss = item->get("forge");
		sao = strlen(ss);
		if (TASK_LEGEND_D->check_task_item_amount(player, name3) < 1 ||
			TASK_LEGEND_D->check_task_item_amount(player, "Tái Tạo Thạch") < (sao + 1) * 12 ||
			TASK_LEGEND_D->check_task_item_amount(player, "Lỗ Ban Bảo Thạch") < 300)
		{
			send_user(player, "%c%c%w%s", ':', 3, 9959, sprintf("Can Tương: \n Nguyên liệu của ngươi không đủ! Đúc %s cần các loại nguyên liệu sau:\n " + name + ", %s" NOR ", %s" NOR ", %s" NOR ".\n" ESC "Rời khỏi", name2, TASK_LEGEND_D->check_task_item_amount(player, "Lỗ Ban Bảo Thạch") < 300 ? HIR "300 viên Lỗ Ban" : "300 viên Lỗ Ban", TASK_LEGEND_D->check_task_item_amount(player, "Tái Tạo Thạch") < (sao + 1) * 12 ? sprintf(HIR "%d Tái Tạo Thạch", (sao + 1) * 12) : sprintf("%d Tái Tạo Thạch", (sao + 1) * 12), TASK_LEGEND_D->check_task_item_amount(player, name3) < 1 ? HIR + name3 : name3));
			return;
		}
		if (USER_INVENTORY_D->get_free_count(player) < 1)
		{
			send_user(player, "%c%c%w%s", ':', 3, 9959, "Can Tương: \nHành trang của ngươi không đủ 1 ô trống, hãy thu xếp hành trang rồi đến gặp ta ! \n" ESC "Xác nhận");
			return;
		}
		TASK_LEGEND_D->check_task_item1(player, name3, 1);
		TASK_LEGEND_D->check_task_item1(player, "Tái Tạo Thạch", (sao + 1) * 12);
		TASK_LEGEND_D->check_task_item1(player, "Lỗ Ban Bảo Thạch", 300);
		CHAT_D->sys_channel(0, sprintf("Can Tương vừa từ lò rèn lấy ra một Tuyệt thế thần binh " HIR "%s" NOR ", đưa cho %s. Đất trời bỗng rung chuyển dữ dội, phải chăng sắp có đại loạn?", name2, player->get_name()));
		send_user(player, "%c%s", ';', sprintf("Bạn nhận được Tuyệt thế thần binh " HIY "%s" NOR " !", name2));
		send_user(player, "%c%c%w%s", ':', 3, 9959, sprintf("Can Tương: \nXin chúc mừng! Ngươi đã đúc được Tuyệt thế thần binh %s ! \n" ESC "Xác nhận\nCLOSE\n" ESC "Rời khỏi", name2));
		item2 = new (thanbinh);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item2);
			forge += "1";
			item2->set("forge", forge);
		}
		item2->set_hide(0);
		p = item2->move2(player, -1);
		item2->add_to_user(p);
		item->remove_from_user();
		destruct(item);
		break;
	}
}
void do_look(object player)
{
	object npc = this_object();

	send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s :\n" + "Xưa đại sư Âu Dã Tử rèn kiếm, quặng sắt không chảy phải để một người phụ nữ nhảy vào lò thì việc rèn sau mới thành công. Ngươi hiểu ý nghĩa của việc này chứ? Haha! \n"
																			 //ESC "Rèn lại trang bị\ntalk %x# welcome.1\n"
																			 ESC "Đúc Tuyệt thế thần binh\ntalk %x# welcome.300\n"
																			 //	ESC "Tách Đoạn Thạch\ntalk %x# welcome.6\n"
																			 ESC HIC "Phân giải Đoạn Thạch\ntalk %x# welcome.400\n"
																			 //  ESC HIG"Đổi Đoạn Thạch\ntalk %x# welcome.5\n"
																			 ESC "Rời khỏi\nCLOSE\n",
																		 npc->get_name(), getoid(npc), getoid(npc), getoid(npc), getoid(npc)));
}
// 函数：用锻造石生成蓝色装备

void do_accept(string arg) { return __FILE__->do_accept_callout(this_object(), this_player(), arg); }

void do_accept_callout(object me, object who, string arg)
{
	return 0;
}