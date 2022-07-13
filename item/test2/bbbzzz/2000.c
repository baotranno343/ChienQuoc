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
	set_name("Bang Ngân Thần Châm");
	set_picid_1(3562);
	set_picid_2(3562);
	set_value(180);
	set_amount(1);
	set_record(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Sử dụng sẽ trừ đi toàn bộ Bang ngân của Phái";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object item)
{
	if (!sizeof(who->get_org_name()))
	{
		send_user(who, "%c%s", '!', "你没有加入任何的帮派，无法使用定帮神针。");
		return 0;
	}
	if (who->get_org_position() < 1)
	{
		send_user(who, "%c%s", '!', "你没有加入任何的帮派，无法使用定帮神针。");
		return 0;
	}
	send_user(who, "%c%c%w%s", ':', 3, 0, sprintf("Sử dụng sẽ trừ đi toàn bộ Bang Ngân Bang Phái, muốn sử dụng không？\n" ESC "Xác nhận\nuse ! %x#\n" ESC "Huỷ bỏ", getoid(item)));
	return 0;
}

string get_loop_desc(object me)
{
	return "使用后能使帮派的安定度增加1000。";
}
// 函数：使用效果
int confirm_use(object me) { return __FILE__->confirm_use_callout(me, this_object()); }

// 函数：使用效果(在线更新)
int confirm_use_callout(object who, object item)
{
	object org;

	if (who->get_org_position() < 1)
	{
		send_user(who, "%c%s", '!', "你没有加入任何的帮派，无法使用定帮神针。");
		return 0;
	}
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(who, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	org = CITY_ZHOU->get_2(sprintf("org.%s", who->get_org_name()));
	if (!org)
	{
		send_user(who, "%c%s", '!', "您的帮派数据有误！");
		return 0;
	}

	org->add_gold(-org->get_gold());
	org->save();
	return 1;
}