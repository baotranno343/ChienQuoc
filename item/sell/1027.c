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
	set_name("人气王");
	set_picid_1(4904);
	set_picid_2(4904);
	set_value(150000);
	set_amount(1);
	set_record(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "远古时代流传下来的一种名为人气王的人形木偶，在帮派\n人气低于1000时，使用后能使帮派人气增加1000。冷却2秒。";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object item)
{
	if (!sizeof(who->get_org_name()))
	{
		send_user(who, "%c%s", '!', "你没有帮派！");
		return 0;
	}
	if (who->get_org_position() < 1)
	{
		send_user(who, "%c%s", '!', "人气王只能是帮派成员使用。");
		return 0;
	}
	send_user(who, "%c%c%w%s", ':', 3, 0, sprintf("使用该道具后帮派的人气会增加1000点，你确定要使用吗？\n" ESC "确定\nuse ! %x#\n" ESC "取消", getoid(item)));
	return 0;
}

string get_loop_desc(object me)
{
	return "使用后能使帮派的人气增加1000。";
}
// 函数：使用效果
int confirm_use(object me) { return __FILE__->confirm_use_callout(me, this_object()); }

// 函数：使用效果(在线更新)
int confirm_use_callout(object who, object item)
{
	object org;

	if (who->get_org_position() < 1)
	{
		send_user(who, "%c%s", '!', "人气王只能是帮派成员使用。");
		return 0;
	}
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(who, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (gone_time(who->get("use0027")) <= 2)
	{
		send_user(who, "%c%s", '!', "请不要频繁使用！");
		return 0;
	}
	who->set("use0027", time());
	org = CITY_ZHOU->get_2(sprintf("org.%s", who->get_org_name()));
	if (!org)
		return 0;
	if (org->get_favour() >= 1000)
	{
		send_user(who, "%c%s", '!', "抱歉，贵帮的人气不需要使用该道具。");
		return 0;
	}
	org->add_favour(1000);
	org->save();
	return 1;
}