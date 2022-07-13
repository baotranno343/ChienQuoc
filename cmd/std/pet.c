#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <public.h>

// 函数：命令处理
int main(object me, string arg)
{
	object *zombie, soldier, who, *pets, enemy, pet, item;
	int i, size, skill, action;
	string id, target, type, *args, name;
	target = "";
	if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
	{
		send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
		return 1;
	}
	if (sscanf(arg, "%s %s %s", id, type, target) == 3)
		;
	else if (sscanf(arg, "%s %s", id, type) == 2)
		;
	else
	{
		return 1;
	}
	pets = ({});
	if (id == "all")
	{
		if (objectp(soldier = me->get("soldier")))
			pets += ({soldier});
		if (arrayp(zombie = me->get("zombie")) && arrayp(zombie = filter_array(zombie - ({0}), (
																								   : $1->get_owner() == $2:),
																			   me)) // 清除叛变的怪
			&& (size = sizeof(zombie)))												// zombie -= ({ 0 })
		{
			pets += zombie;
		}
		if (objectp(pet = me->get("showbeast")))
			pets += ({pet});
	}
	else if (!objectp(who = find_char(id)))
	{
		notify("您无法找到这个人.");
		return 1;
	}
	else
	{
		if (who->get_owner() != me)
			return 1;
		pets = ({who});
	}
	if (who)
	{
		//宠物指令
		if (type == "show") //宠物参战
		{
			name = who->get_name();
			args = explode(name, " ");
			if (args[0] != name)
				USER_BEAST_D->change_name(me, who, args[0]);
			USER_BEAST_D->show_beast_perform(me, who);
			return 1;
		}
		else if (type == "hide") //宠物收回
		{
			USER_BEAST_D->hide_beast(me, who);
			return 1;
		}
		else if (type == "free") //宠物释放
		{
			if (who->get_save("locktime") > time())
			{
				send_user(me, "%c%s", '!', sprintf("%s đã khoá, không thể phóng sinh.", who->get_name()));
				return 1;
			}
			USER_BEAST_D->free_beast(me, who);
			return 1;
		}
		else if (type == "rename")
		{
			if (sizeof(target))
			{
				args = explode(target, " ");
				USER_BEAST_D->change_name(me, who, args[0]);
			}
			return 1;
		}
		else if (type == "gift") //宠物属性点分配
		{
			NPC_PET_D->add_giftpoint(who, target);
			return 1;
		}
		else if (type == "ski") //宠物默认技能设置
		{
			NPC_PET_D->set_default_skill(who, target);
			return 1;
		}
		else if (type == "fuse") //宠物合成
		{
			NPC_PET_D->fuse(who, target, 0);
			return 1;
		}
		else if (type == "fuse_y") //宠物合成(确认)
		{
			NPC_PET_D->fuse(who, target, 1);
			return 1;
		}
		else if (type == "fuse_yy") //宠物合成(确认)
		{
			NPC_PET_D->fuse(who, target, 2);
			return 1;
		}
		else if (type == "lock")
		{
			item = present("Khoá Càn Khôn", me, 1, MAX_CARRY * 4);
			if (!item)
			{
				notify("Bạn không có Khoá Càn Khôn");
				return 1;
			}
			if (sizeof(target))
				item->pet_item2(me, item, who);
			else
				item->pet_item(me, item, who);
		}
	}
	if (type == "mode")
	{
		if (target == "" || target == 0)
			return 1;
		skill = to_int(target);
		if (skill >= 0 && skill < 3)
		{
			//        		if (skill==1) skill = 2;
			size = sizeof(pets);
			for (i = 0; i < size; i++)
			{
				pets[i]->set_action_mode(skill);
				if (skill == 2 || skill == 0)
				{
					pets[i]->set_enemy(0);
					pets[i]->set_main_enemy(0);
				}
				else if (skill == 1)
					NPC_SLAVE_D->find_enemy(pets[i]);
			}
		}
	}
	enemy = 0;
	if (target != 0 && target != "")
	{
		enemy = find_char(target);
	}
	if (sizeof(pets) == 0)
		return 1;
	action = pets[0]->get_action();
	skill = to_int(type);
	if (skill > 0 && skill < 4)
	{
		size = sizeof(pets);
		if (skill == 3)
			skill = 0;
		if (skill == 1)
		{
			if (objectp(enemy) && enemy->can_be_fighted(me) && me->can_fight(enemy))
			{
				for (i = 0; i < size; i++)
				{
					pets[i]->set_next_action(action);
					pets[i]->set_action(1);
					pets[i]->init_heart_beat_idle();
					pets[i]->auto_fight(enemy);
					pets[i]->set_enemy(enemy);
					pets[i]->set_main_enemy(enemy);
					pets[i]->set_fight_time(time());
				}
			}
			return 1;
		}
		for (i = 0; i < size; i++)
		{
			pets[i]->set_action(skill);
			if (enemy == 0)
				action = skill;
			else
			{
				if (action != 0)
					action = 1;
			}
			//			if (action!=2)
			pets[i]->set_next_action(action);
			if (skill == 2)
			{
				pets[i]->set_enemy(0);
				pets[i]->set_main_enemy(0);
				NPC_SLAVE_D->follow_owner(pets[i]);
			}
		}
	}

	return 1;
}
