#include <ansi.h>
#include <effect.h>
#include <skill.h>
#include <city.h>
#include <chia_kenh.h>

inherit COMBINED;
inherit ITEM;

int get_item_value() { return 999; }
int get_item_value_2() { return 888; }
int get_item_number() { return 10001021; }
int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
	set_name("Định Bang Thần Châm");
	set_picid_1(3562);
	set_picid_2(3562);
	set_value(180);
	set_save("knb", 50);
	set_amount(1);
	set_record(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Một loại châm thêu hoa thần kỳ, hội tụ linh khí của trời đất, \nSau khi sử dụng có thể làm cho Bang Phái an định tăng 100 điểm. \nTái sử dụng 2 giây.";
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
	send_user(who, "%c%c%w%s", ':', 3, 0, sprintf("Sử dụng sẽ tăng độ Ổn Định Bang Phái thêm 100 điểm，muốn sử dụng không？\n" ESC "Xác nhận\nuse ! %x#\n" ESC "Huỷ bỏ", getoid(item)));
	return 0;
}

string get_loop_desc(object me)
{
	return "Sau khi sử dụng độ An Định của Bang tăng lên 100 điểm.";
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
	if (gone_time(who->get("use0026")) < 2)
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
	if (org->get_stable() == 10000)
	{
		send_user(who, "%c%s", '!', "Độ Ổn Định đã đến giới hạn rồi !");
		return 0;
	}
	who->set("use0026", time());

	org->add_stable(100);
	org->save();
	return 1;
}