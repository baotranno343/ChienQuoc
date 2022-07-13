#include <ansi.h>
#include <effect.h>
#include <skill.h>
#include <city.h>
#include <chia_kenh.h>
inherit COMBINED;
inherit ITEM;

int get_item_value() { return 999; }
int get_item_value_2() { return 888; }
int get_item_number() { return 10001022; }
int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
	set_name("Nhân Khí Vương");
	set_picid_1(4904);
	set_picid_2(4904);
	set_value(160);
	set_save("knb", 50);
	set_amount(1);
	set_record(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Lưu truyền thời kỳ nguyên cổ có một loại sen giống hình người đó là Nhân Khí Vương, \nSau khi sử dụng có thể làm cho nhân khí Bang Phái tăng 100 điểm. \nTái sử dụng 2 giây.";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object item)
{
	if (!sizeof(who->get_org_name()))
	{
		send_user(who, "%c%s", '!', "Bạn chưa gia nhập Bang Phái, không thể sử dụng.");
		return 0;
	}
	if (who->get_org_position() < 1)
	{
		send_user(who, "%c%s", '!', "Bạn chưa gia nhập Bang Phái, không thể sử dụng.");
		return 0;
	}
	send_user(who, "%c%c%w%s", ':', 3, 0, sprintf("Sử dụng sẽ tăng Nhân Khí Bang Phái thêm 100 điểm，muốn sử dụng không？\n" ESC "Xác nhận\nuse ! %x#\n" ESC "Huỷ bỏ", getoid(item)));
	return 0;
}

string get_loop_desc(object me)
{
	return "Sau khi sử dụng Nhân Khí của Bang tăng lên 100 điểm.";
}
// 函数：使用效果
int confirm_use(object me) { return __FILE__->confirm_use_callout(me, this_object()); }

// 函数：使用效果(在线更新)
int confirm_use_callout(object who, object item)
{
	object org;

	if (who->get_org_position() < 1)
	{
		send_user(who, "%c%s", '!', "Bạn chưa gia nhập Bang Phái, không thể sử dụng.");
		return 0;
	}
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(who, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (gone_time(who->get("use0027")) < 2)
	{
		send_user(who, "%c%s", '!', "Không nên sử dụng thường xuyên !");
		return 0;
	}
	org = CITY_ZHOU->get_2(sprintf("org.%s", who->get_org_name()));
	if (!org)
	{
		send_user(who, "%c%s", '!', "Số liệu Bang Phái có sai lầm !");
		return 0;
	}
	who->set("use0027", time());
	if (org->get_favour() == org->get_grade() * 2000)
	{
		send_user(who, "%c%s", '!', "Nhân Khí đã đến giới hạn rồi !");
		return 0;
	}
	org->add_favour(100);
	org->save();
	return 1;
}