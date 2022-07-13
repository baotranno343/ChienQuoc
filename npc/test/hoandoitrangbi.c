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

void create()
{
	set_name("Hoán Đổi Trang Bị");
	set_real_name("Thượng Nhân");
	set_2("talk", (["welcome":(
								  : do_welcome:),
					  "check_duc_lo":(
										 : check_duc_lo:),
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

	send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s :\n" + "Ta sẽ hoán đổi trang bị của ngươi lên 7 sao!\n" ESC "Rời khỏi\nCLOSE\n", npc->get_name(), getoid(npc), getoid(npc)));
}

int accept_object(object who, object item) { return __FILE__->accept_object_callout(this_object(), who, item); }

// 函数:接受物品(在线更新)
int accept_object_callout(object me, object who, object item)
{
	me->to_front_eachother(who);
	me->set("id_item", sprintf("%x#", getoid(item)));
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Bồ Nguyên:\n Ngươi muốn hoán đổi trang bị có tư chất kém cỏi để lấy trang bị tư chất tốt hơn\n" ESC "Đúng Vậy\ntalk %x# check_duc_lo.%x#\n" ESC "Huỷ bỏ", getoid(me), getoid(item), getoid(me), getoid(item)));
	return -99;
}
// 函数:接受物品
void check_duc_lo(string arg) { return __FILE__->check_duc_lo_callout(this_object(), this_player(), arg); }
// 函数:接受物品(在线更新)
void check_duc_lo_callout(object me, object who, string arg)
{
	object item;
	string forge = "";
	int i;
	if (!objectp(item = present(me->get("id_item"), who, 1, MAX_CARRY * 4)))
		return 0;

	for (i = 0; i < 7; i++)
	{
		"/sys/item/equip"->init_equip_prop_5(item);
		forge += "1";
		item->set("forge", forge);
	}
	item->add_to_user(get_d(item));
	send_user(who, "%c%d%c", 0x31, getoid(item), 0);
	send_user(who, "%c%s", ';', sprintf("Trang bị %s đã được hoán đổi lên 7 sao thành công!", item->get_name()));
	return 0;
}

