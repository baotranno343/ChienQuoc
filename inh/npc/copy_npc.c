#include <cmd.h>
#include <skill.h>

inherit BADMAN;

int StartX, StartY;	  //初始点
int TargetX, TargetY; //终点
int WalkStatus;		  //1 持续走路 2 只走一次
int FightStatus;
int transTime; //传送时间
int iAttack_time;

void heart_beat_walk()
{
	int x, y, z, p, x1, y1, seek, z0, x0, y0;
	int *dir, i, size;
	object me, *see, enemy;
	string cmd, place;

	me = this_object();
	enemy = me->get_enemy();
	if (enemy && (gone_time(transTime) >= 10))
	{
		transTime = time();
		z = get_z(enemy);
		z0 = get_z(me);
		if (z == z0 && (p = distance_between(me, enemy)) < 20 && p > 1)
		{
			x = get_x(enemy);
			y = get_y(enemy);
			x0 = get_x(me);
			y0 = get_y(me);
			for (i = 0; i < 10; i++)
			{
				if (p = get_valid_xy(z, abs(x + random(3) - 1), abs(y + random(3) - 1), IS_CHAR_BLOCK))
				{
					x1 = p / 1000;
					y1 = p % 1000;
					break;
				}
			}
			if (x1 && y1 && z)
			{
				me->add_to_scene(z, x1, y1, 0, 9413);
				me->to_front_xy(x, y);
			}
		}
		return;
	}

	if (!enemy && iAttack_time && gone_time(iAttack_time) > 10) //10秒内没战斗回出生点
	{
		iAttack_time = 0;
		place = me->get_start_place();
		if (place)
		{
			sscanf(place, "%d", p);
			if (p > 0 && (abs((p / 1000) - get_x(me)) > 4 || abs((p % 1000) - get_y(me)) > 4))
			{
				me->add_to_scene(get_z(me), p / 1000, p % 1000, 3);
			}
		}
		return;
	}
	if (!enemy && WalkStatus)
	{
		if (!TargetX || !StartX)
		{
			::heart_beat_walk();
			return;
		}
		x = get_x(me);
		y = get_y(me);
		z = get_z(me);
		if (WalkStatus == 1)
		{
			seek = get_max_seek();
			see = get_range_object(z, x, y, seek, USER_TYPE) + get_range_object(z, x, y, seek, CHAR_TYPE) - ({me}); // 可见范围
			for (i = 0, size = sizeof(see); i < size; i++)
			{
				if (!me->can_fight(see[i]) || !see[i]->can_be_fighted(me))
					continue;
				x1 = get_x(see[i]);
				y1 = get_y(see[i]);
				me->start_fight(see[i]);
				return;
			}
		}
		x1 = abs(TargetX - x);
		y1 = abs(TargetY - y);
		if (x1 * x1 + y1 * y1 < 9) //交换始点，终点
		{
			if (WalkStatus == 1) //持续走路
			{
				x1 = StartX;
				y1 = StartY;
				StartX = TargetX;
				StartY = TargetY;
				TargetX = x1;
				TargetY = y1;
			}
			else //只走一次，到达终点不走
			{
				WalkStatus = 0;
				return;
			}
		}
		p = get_valid_path(z, x, y, TargetX, TargetY);
		if (!p)
		{
			dir = ({});
			if (p = get_valid_path(z, x, y, (TargetX - 3), TargetY + 3))
				dir += ({p});
			if (p = get_valid_path(z, x, y, (TargetX - 3), TargetY - 3))
				dir += ({p});
			if (p = get_valid_path(z, x, y, (TargetX - 3), TargetY))
				dir += ({p});
			if (p = get_valid_path(z, x, y, (TargetX + 3), TargetY + 3))
				dir += ({p});
			if (p = get_valid_path(z, x, y, (TargetX + 3), TargetY - 3))
				dir += ({p});
			if (p = get_valid_path(z, x, y, (TargetX + 3), TargetY))
				dir += ({p});
			if (p = get_valid_path(z, x, y, TargetX, TargetY + 3))
				dir += ({p});
			if (p = get_valid_path(z, x, y, TargetX, TargetY - 3))
				dir += ({p});
			size = sizeof(dir);
			if (size > 0)
				p = dir[random(size)];
			else
				p = 0;
		}
		if (p) // 找到可走路径
		{
			cmd = sprintf("%d", p);

			switch (me->get_walk_step())
			{
			case 0:
			case 1:
				if (strlen(cmd) > 1)
					cmd = cmd[0..0];
				break;
			case 2:
				if (strlen(cmd) > 2)
					cmd = cmd[0..1];
				break;
			default:
				break;
			}
			GO_CMD->main_npc(me, cmd);
		}
	}
	else
		::heart_beat_walk();
}

void set_start_point(int x, int y)
{
	StartX = x;
	StartY = y;
}

void set_target_point(int x, int y)
{
	TargetX = x;
	TargetY = y;
}

int set_walk_status(int i) { return WalkStatus = i; }

int get_walk_status() { return WalkStatus; }

int set_fight_status(int i) { return FightStatus = i; }

//是否可以呼唤
int can_help() { return 1; }

// 函数：获取人物名称
string get_short()
{
	return this_object()->get_name();
}

// 函数：修正经验奖励
int correct_exp_bonus(int level, int level2, int exp) { return exp; }

// 函数：修正掉宝率
int correct_drop_rate(int level) { return 100; }

//开始战斗
void start_fight(object who)
{
	object me, *see, help;
	int i, size, seek;

	::start_fight(who);
	me = this_object();
	if (objectp(who = me->get_enemy()) && !who->is_die() && get_z(who) == get_z(me) && distance_between(me, who) <= 20)
	{
		seek = get_max_seek();
		see = get_range_object(get_z(me), get_x(me), get_y(me), seek, CHAR_TYPE) - ({me}); // 可见范围
		for (i = 0, size = sizeof(see); i < size; i++)
		{
			if (!objectp(help = see[i]) || !help->can_help())
				continue;
			if (objectp(help->get_enemy()) || help->get_walk_status())
				continue;
			if (distance_between(help, who) > 20)
				continue;
			help->call_to_fight(who);
			//	CHAT_D->sys_channel(0, sprintf(" %s ", "test"));
		}
	}
}
//呼救
void call_to_fight(object who)
{
	object me, *see, help;
	int i, size, seek, x1, y1, x, y;

	me = this_object();
	if (get_z(who) != get_z(me) || distance_between(me, who) > 20)
		return;

	//设定路线
	x = get_x(me);
	y = get_y(me);
	x1 = get_x(who);
	y1 = get_y(who);
	set_start_point(x, y);
	set_target_point(x1, y1);
	set_walk_status(2);
	//继续呼救
	seek = get_max_seek();
	see = get_range_object(get_z(me), get_x(me), get_y(me), seek, CHAR_TYPE) - ({me}); // 可见范围
	for (i = 0, size = sizeof(see); i < size; i++)
	{
		if (!objectp(help = see[i]) || !help->can_help())
			continue;
		if (objectp(help->get_enemy()) || help->get_walk_status())
			continue;
		help->call_to_fight(who);
	}
}

int can_fight(object who)
{
	if (who->can_help())
		return 0;
	iAttack_time = time();
	return ::can_fight(who);
}
//不能捕抓
int can_not_catch()
{
	return 1;
}