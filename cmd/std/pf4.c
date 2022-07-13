#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：命令处理
int main(object me, string arg)
{
	object file, what, diamond1, diamond2, diamond3, tool;
	string id1, id2, id3, sex;
	int busy, pf, x, y, which, skill, type;
	int rate, rate2;

	if (me->is_store_open())
	{
		notify("您在摆摊，不能使用生活技能。");
		return 1;
	}
	if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
	{
		send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
		return 1;
	}
	if (busy = get_effect(me, EFFECT_CHAR_BUSY))
	{
		notify("Bạn còn phải bận %d giây", busy);
		return 1;
	}
	if (get_effect_3(me, EFFECT_PROGRESS) || get_effect_3(me, EFFECT_PROGRESS2))
		return 1;

	if (get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_MAGIC_4243) || get_effect(me, EFFECT_CHAR_FREEZE) || get_effect(me, EFFECT_CHAR_DREAM_1) || get_effect(me, EFFECT_CHAR_DREAM))
		return 1;

	if (!arg)
		return 1;
	if (sscanf(arg, "%d %d %s %s %s %s", pf, x, sex, id1, id2, id3) == 6)
	{
		diamond1 = 0;
		diamond2 = 0;
		diamond3 = 0;
		if (id1 != "0#")
			diamond1 = find_any_object(id1);
		if (id2 != "0#")
			diamond2 = find_any_object(id2);
		if (id3 != "0#")
			diamond3 = find_any_object(id3);
		if (diamond1 == diamond2)
			diamond2 = 0;
		if (diamond1 == diamond3)
			diamond3 = 0;
		if (diamond2 == diamond3)
			diamond3 = 0;
		y = 0;
		if (diamond1 && diamond1->is_luban())
			y++;
		if (diamond2 && diamond2->is_luban())
			y++;
		if (diamond3 && diamond3->is_luban())
			y++;
		if (y > 1)
		{
			notify("一次只能使用一个鲁班宝石！");
			return 1;
		}
		if ((file = load_object(SKILL->get_perform_file(pf))))
		{
			tool = me->get_equip(107);
			type = pf / 1000;
			if (type != 610 & type != 670 && tool)
			{
				if (tool->get_lasting() < 100 && tool->get_stuff_type() >= 500)
				{
					notify("您的工具耐久度不足，无法使用。");
					return 1;
				}
			}
			file->main(me, x, sex, diamond1, diamond2, diamond3);
		}
	}
	else if (sscanf(arg, "? %d %s %s %s", pf, id1, id2, id3) == 4)
	{
		if (id1 != "0#")
			diamond1 = find_any_object(id1);
		if (id2 != "0#")
			diamond2 = find_any_object(id2);
		if (id3 != "0#")
			diamond3 = find_any_object(id3);
		if (diamond1 == diamond2)
			diamond2 = 0;
		if (diamond1 == diamond3)
			diamond3 = 0;
		if (diamond2 == diamond3)
			diamond3 = 0;
		if (diamond1)
		{
			rate += diamond1->get_rate();
			rate2 += diamond1->get_rate2();
		}
		if (diamond2)
		{
			rate += diamond2->get_rate();
			rate2 += diamond2->get_rate2();
		}
		if (diamond3)
		{
			rate += diamond3->get_rate();
			rate2 += diamond3->get_rate2();
		}
		if ((file = load_object(SKILL->get_perform_file(pf))))
		{
			rate += file->get_base_rate();
			if (me->get_vip() && !me->get_save_2("vip_package.trial"))
				rate += 5;
			if (rate > 100)
				rate = 100;
			if (rate2 > 100)
				rate2 = 100;
			send_user(me, "%c%c%d%c%c", 0x60, 9, pf, rate, rate2);
		}
	}
	else if (sscanf(arg, "%s %d %s", id1, pf, id2) == 3)
	{
		what = find_any_object(id1);
		tool = find_any_object(id2);
		if ((file = load_object(SKILL->get_perform_file(pf))))
			file->main(me, what, tool);
	}
	else if (sscanf(arg, "%d %d", pf, x) == 2)
	{
		if (x == 0)
			x = 1;
		if ((file = load_object(SKILL->get_perform_file(pf))))
		{
			tool = me->get_equip(107);
			type = pf / 1000;
			if (type != 610 & type != 670 && tool)
			{
				if (tool->get_lasting() < 100 && tool->get_stuff_type() >= 500)
				{
					notify("您的工具耐久度不足，无法使用。");
					return 1;
				}
			}
			file->main(me, x, "", 0, 0, 0);
		}
	}
	return 1;
}
