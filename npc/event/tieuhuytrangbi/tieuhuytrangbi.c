#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <equip.h>
inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5505; }
int is_seller() { return 1; }
int is_self_look() { return 1; }
void do_welcome(string arg);
void do_accept(string arg);
void create()
{
	set_name("Thư Sinh");
	set_real_name("Quyên Góp");
	set_2("good", ([
					  //    "01" : "/item/sell/0032",
					  //	"02" : "/item/sell/1032",
					  //	"03" : "/item/sell/2032",
					  //	"04" : "/item/sell/3032",
					  "01":"/item/test2/TichLuy/BiKipKNB",
					  "02":"/item/test2/TichLuy/BiKipKNB1",
					  "03":"/item/test2/TichLuy/BiKipKNB2",
					  //	"07" : "/item/test2/TichLuy/BiKipKNB3",
					  //	"08" : "/item/test2/TichLuy/BiKipKNB4",
					  //	"09" : "/item/test2/TichLuy/BiKipKNB5",
					  "04":"/item/std/0095",
					  //	"11" : "/item/test2/TichLuy/BKCT",
					  //	"12" : "/item/test2/TichLuy/BKCT1",
					  //	"13" : "/item/test2/TichLuy/BKCT2",
	]));
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
	int flag;
	object player = this_player();
	flag = to_int(arg);
	switch (flag)
	{
	case 1:
		"sys/party/bxh_quyengop"->bxh_quyengop(player, npc);
		break;
	case 2:

		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), npc->get_name() + ":\n" + "Nếu bạn muốn quyên góp hãy dùng trang bị xanh để quyên góp. Mỗi 10 trang bị bạn sẽ nhận được 1 viên Tử Sâm Đơn. \n" ESC "ALT+G để giao trang bị\nCLOSE\n" ESC "Thoát ra\nCLOSE\n");
		break;
	}
}
void do_look(object player)
{
	object npc = this_object();
	send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s :\n" + "Điểm Quyên Góp của bạn hiện tại là: %d \n" ESC "Bảng Xếp Hạng Quyên Góp\ntalk %x# welcome.1\n" ESC "Quyên Góp Trang Bị\ntalk %x# welcome.2\n" ESC "Rời khỏi\nCLOSE\n", npc->get_name(), player->get_save("diem_quyengop"), getoid(npc), getoid(npc)));
	//"sys/party/bxh_quyengop"->bxh_quyengop(player, npc);
	//send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s :\n" + "%s ?\n" ESC "Làm cách nào để tiêu huỷ trang bị\ntalk %x# welcome.1\n" ESC "Mua vật phẩm\nlist %x#\n" ESC "Rời khỏi\nCLOSE\n", npc->get_name(), "sys/party/bxh_quyengop"->bxh_quyengop(player, npc), getoid(npc), getoid(npc)));
}

// 函数:接受物品
int accept_object(object who, object item) { return __FILE__->accept_object_callout(this_object(), who, item); }

// 函数:接受物品(在线更新)
int accept_object_callout(object me, object who, object item)
{
	int level, p, i, t1, t2, t3, t4, mau, cap, cap1, cap2, price;
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
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\nBạn đưa Thư Sinh trang bị không đúng.\n" ESC "Rời khỏi", me->get_name()));
			//	send_user(who,"%c%s",':',me->get_name()+":\nBạn đưa tôi trang bị không đúng !!!\n"ESC"Rời khỏi.");
			return -99;
		}
	}
	if (USER_INVENTORY_D->get_free_count(who) < 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\nHành trang của ngươi không đủ 1 ô trống.\n" ESC "Rời khỏi", me->get_name()));
		return -99;
	}
	cap = item->get_level();
	mau = item->get_item_color();
	price = item->get_value();
	if (mau != 1)
	{

		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\nThư Sinh chỉ nhận trang bị xanh dương.\n" ESC "Rời khỏi", me->get_name()));
		return -99;
	}
	// if (cap < 1)
	// {
	// 	write_user(who, ECHO "Trang bị chưa đạt 1 sao, không thể tiêu huỷ");
	// 	//	send_user(who,"%c%s",':',me->get_name()+":\nTrang bị chưa đạt 1 sao, không thể tiêu huỷ !!!\n"ESC"Rời khỏi.");
	// 	return -99;
	// }

	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Thư Sinh:\nQuyên Góp trang bị này bạn có thể nhận được 1 điểm Quyên Góp, bạn muốn Quyên Góp không ?\n" ESC "Xác nhận\ntalk %x# accept.%x#\n" ESC "Huỷ bỏ", getoid(me), getoid(item)));

	return -99;
}
// Bla bla
void do_accept(string arg) { return __FILE__->do_accept_callout(this_object(), this_player(), arg); }

// Bla bla
void do_accept_callout(object me, object who, string arg)
{
	int level, p, i, t1, t2, t3, t4, mau, cap, cap1, cap2, price;
	object item, item2;
	string sao, ngoc;

	if (!objectp(item = present(arg, who, 1, MAX_CARRY * 4)))
		return 0;
	if (!item->is_equip())
		return 0;
	if (item->is_equip())
	{
		i = item->get_equip_type();
		if (i != WEAPON_TYPE && i != ARMOR_TYPE && i != HEAD_TYPE && i != BOOTS_TYPE && i != WAIST_TYPE && i != NECK_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\nBạn đưa Thư Sinh trang bị không đúng.\n" ESC "Rời khỏi", me->get_name()));
			//	send_user(who,"%c%s",':',me->get_name()+":\nBạn đưa tôi trang bị không đúng !!!\n"ESC"Rời khỏi.");
			return 0;
		}
	}
	if (USER_INVENTORY_D->get_free_count(who) < 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\nHành trang của ngươi không đủ 1 ô trống.\n" ESC "Rời khỏi", me->get_name()));
		return 0;
	}
	// sao = item->get("forge");
	// cap = strlen(sao);
	// ngoc = item->get("make");
	// cap1 = strlen(ngoc);
	cap = item->get_level();
	mau = item->get_item_color();
	price = item->get_value();
	if (mau != 1)
	{

		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\nThư Sinh chỉ nhận trang bị xanh dương.\n" ESC "Rời khỏi", me->get_name()));
		return 0;
	}

	// if (cap < 1)
	// {
	// 	write_user(who, ECHO "Trang bị chưa đạt 1 sao, không thể tiêu huỷ");
	// 	//	send_user(who,"%c%s",':',me->get_name()+":\nTrang bị chưa đạt 1 sao, không thể tiêu huỷ !!!\n"ESC"Rời khỏi.");
	// 	return 0;
	// }

	who->add_save("diem_quyengop", 1);
	write_user(who, sprintf(ECHO "Bạn Quyên Góp %s và nhận được 1 điểm", item->get_name()));
	item->remove_from_user();
	destruct(item);

	if (who->get_save("diem_quyengop") % 10 == 0)
	{
		item2 = new ("/item/91/9167"); // TSD
		p = item2->move2(who, -1);
		item2->add_to_user(p);
	}

	// else if (mau == 2)
	// {

	// 	who->add_save("diem_quyengop", 2);
	// 	write_user(who, sprintf(ECHO "Bạn Quyên Góp %s và nhận được 2 điểm", item->get_name()));
	// 	item->remove_from_user();
	// 	destruct(item);
	// }
	// else if (mau == 3)
	// {
	// 	who->add_save("diem_quyengop", 3);
	// 	write_user(who, sprintf(ECHO "Bạn Quyên Góp %s và nhận được 3 điểm", item->get_name()));
	// 	item->remove_from_user();
	// 	destruct(item);
	// }
	// else if (mau == 4)
	// {
	// 	who->add_save("diem_quyengop", 4);
	// 	write_user(who, sprintf(ECHO "Bạn Quyên Góp %s và nhận được 4 điểm", item->get_name()));
	// 	item->remove_from_user();
	// 	destruct(item);
	// }
	// else if (mau == 5)
	// {
	// 	who->add_save("diem_quyengop", 5);
	// 	write_user(who, sprintf(ECHO "Bạn Quyên Góp %s và nhận được 5 điểm", item->get_name()));
	// 	item->remove_from_user();
	// 	destruct(item);
	// }
	// else if (mau == 0)
	// {
	// 	who->add_save("diem_quyengop", 1);
	// 	write_user(who, sprintf(ECHO "Bạn Quyên Góp %s và nhận được 1 điểm", item->get_name()));
	// 	item->remove_from_user();
	// 	destruct(item);
	// }
	//who->add_cash(price);
	"sys/party/bxh_quyengop"->update_bxh_quyengop(who);
	return 0;
}