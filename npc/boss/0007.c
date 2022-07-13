#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <effect.h>
#include <cmd.h>
#include <skill.h>
#include <action.h>

#define _DEBUG(x) tell_user(find_char("971"), x);

inherit NPC;

int flag;
int saytime, hptime, lowhp, silent, summon, RelaxTime, moveTime, pTime, pTime1;
int leiTime;
string *nFamily = ({"Đào Hoa Nguyên", "Thục Sơn", "Cấm Vệ Quân", "Đường Môn", "Mao Sơn", "Côn Luân", "Vân Mộng Cốc"});
// 函数：是否不能进城
int cannot_enter_city() { return 1; }
int get_id_color() { return 0x800080; }
int is_caster() { return 1; }
void drop_items(object me, object who);
int is_tiger_king() { return 1; }
int is_officer() { return get_char_type() == OFFICER_TYPE ? 1 : 0; }
void do_fight();
object summon_4131(object who);
object summon_4134(object who);

void init_fight_status()
{
	set_ap(100);
	set_dp(690);
	set_cp(750);
	set_pp(550);
	set_sp(660);
}

// 函数：构造处理
void create()
{
	object me = this_object();
	set_name("Khu Thi Đạo Trưởng");
	set_char_picid(9968);
	set_level(55);
	set_max_hp(1200000);
	set_max_mp(2500);
	init_fight_status();
	set_walk_speed(2);
	set_attack_speed(20);
	set_walk_step(2);
	set_max_seek(6);
	//        set("no_sk04237",1);	//玄龙决对其没有效果
	set("no_sk04211", 1);	//变身术对其没有效果
	set("anti_sleep", 1);	//不会昏迷
	set("anti_no_move", 1); //不会冻结

	set_skill(0271, 55);

	setup();
	set_char_type(OFFICER_TYPE);
	set("birthday", time());
	if (!clonep(me))
		return;
	CHAT_D->rumor_channel(0, CHAT + "Có người bắt gặp Khu Thi Đạo Trưởng xuất hiện ở Di Tề Mộ của Thủ Dương Sơn, không biết thật giả ra sao?");
	set_2("talk", (["fight":(
								: do_fight:),
	]));
	log_file("boss.txt", short_time() + " Khu Thi Đạo Trưởng xuất hiện\n");
}

int can_fight(object who)
{
	object owner;
	string leader, id;
	if (get_char_type() == OFFICER_TYPE)
		return 0;
	if (who->is_die())
	{
		set_enemy(0);
		return 0;
	}
	if (who->is_npc() && objectp(owner = who->get_owner()))
		who = owner;
	if (who->is_npc())
	{
		set_enemy(0);
		return 0;
	}

	return ::can_fight(who);
}
int can_be_fighted(object who)
{
	object owner;
	string leader, id;
	if (get_char_type() == OFFICER_TYPE)
		return 0;
	if (who->is_npc() && objectp(owner = who->get_owner()))
		who = owner;
	if (who->is_npc())
	{
		set_enemy(0);
		return 0;
	}
	if (who->is_user() && who->get_level() <= 40)
	{
		set_enemy(0);
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Ngươi còn bé lắm, hãy về luyện thêm võ công rồi đánh nhau với ta!");
		return 0;
	}
	return ::can_be_fighted(who);
}

void heart_beat_walk()
{
	int i, x, y, z, x0, y0, z0, p, x1, y1;
	object enemy, me = this_object();

	if (gone_time(hptime) >= 10)
	{
		add_hp(100);
		hptime = time();
		if (lowhp && get_hp() * 100 / get_max_hp() > 40)
		{
			lowhp = 0;
			init_fight_status();
		}
	}
	if (get_char_type() == OFFICER_TYPE) //普通状态
		return;
	enemy = get_enemy();
	if (objectp(enemy))
	{
		if (gone_time(saytime) >= 60)
		{
			saytime = time();
			if (random(2))
			{
				switch (random(3))
				{
				case 0:
					SAY_CMD->say(me, "Bần đạo thuật pháp thiên hạ vô song! Tựu toán thị thái thượng lão quân dã nại hà ngã bất đắc!");
					break;
				case 1:
					SAY_CMD->say(me, "Giá ta thi ma đích trớ chú khả tương nhĩ môn trực tiếp đả hạ thập bát tằng địa ngục!");
					break;
				default:
					SAY_CMD->say(me, sprintf("Cáp cáp ～～! %s nhĩ dã cảm dữ bần đạo đấu pháp!? Hồi khứ đa tu luyện kỉ kiếp tái lai!", enemy->get_name()));
					break;
				}
			}
		}
		if (enemy->is_die())
			set_enemy(0);
	}
	else if (RelaxTime == 0)
	{
		RelaxTime = time();
	}
	if (RelaxTime && gone_time(RelaxTime) >= 60)
	{
		RelaxTime = 0;
		set_char_type(OFFICER_TYPE);
	}
	if (!get_effect(me, EFFECT_CHAR_NO_PF_0)) //不沉默
	{
		set_effect(me, EFFECT_CHAR_NO_PF_0, 3600);
	}
	if (!get_effect(me, EFFECT_CHAR_WOUND_0)) //不负伤
	{
		set_effect(me, EFFECT_CHAR_WOUND_0, 3600);
	}
	if (!get_effect(me, EFFECT_CHAR_FAINT_0)) //不眩晕
	{
		set_effect(me, EFFECT_CHAR_FAINT_0, 3600);
	}
	if (!get_effect(me, EFFECT_CHAR_SHUT_0)) //不囚禁
	{
		set_effect(me, EFFECT_CHAR_SHUT_0, 3600);
	}
	if (!get_effect(me, EFFECT_CHAR_DREAM_0)) //不囚禁
	{
		set_effect(me, EFFECT_CHAR_DREAM_0, 3600);
	}
	if (!get_effect(me, EFFECT_CHAR_LAZY_0)) //不延缓
	{
		set_effect(me, EFFECT_CHAR_LAZY_0, 3600);
	}
	if (gone_time(moveTime) >= 15)
	{
		moveTime = time();
		//瞬间移动
		z = get_z(me);
		x = get_x(me);
		y = get_y(me);
		for (i = 0; i < 100; i++)
		{
			if (p = get_valid_xy(z, abs(x + 10 - random(20)), abs(y + 10 - random(20)), IS_CHAR_BLOCK))
			{
				x1 = p / 1000;
				y1 = p % 1000;
				me->add_to_scene(z, x1, y1, 4, 3421);
				break;
			}
		}
	}
	::heart_beat_walk();
}
void heart_beat_attack()
{
	if (get_char_type() == OFFICER_TYPE) //普通状态
		return;
	::heart_beat_attack();
}

void summon_guard()
{
	int i, x, y, z, count, p;
	object npc, me = this_object();

	x = get_x(me);
	y = get_y(me);
	z = get_z(me);
	for (i = 0; i < 3; i++) //3个僵尸守卫
	{
		if (objectp(me->get(sprintf("jiansi%d", i))))
			continue;
		p = get_valid_xy(z, x + random(10) - 5, y + random(10) - 5, IS_CHAR_BLOCK);
		if (!p)
			continue;
		npc = summon_4134(me);
		if (!npc)
			continue;
		npc->add_to_scene(z, p / 1000, p % 1000);
		npc->set_owner(me);
		NPC_SLAVE_D->find_enemy(npc); // 寻找敌人
		send_user(get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc),
				  41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE);
		me->set(sprintf("jiansi%d", i), npc);
	}
	for (i = 0; i < 2; i++) //2个鬼卒守卫
	{
		if (objectp(me->get(sprintf("guizhu%d", i))))
			continue;
		p = get_valid_xy(z, x + random(10) - 5, y + random(10) - 5, IS_CHAR_BLOCK);
		if (!p)
			continue;
		npc = summon_4131(me);
		if (!npc)
			continue;
		npc->add_to_scene(z, p / 1000, p % 1000);
		npc->set_owner(me);
		NPC_SLAVE_D->find_enemy(npc); // 寻找敌人
		send_user(get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc),
				  41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE);
		me->set(sprintf("guizhu%d", i), npc);
	}
	if (!lowhp)
		return;
	for (i = 3; i < 5; i++) //2个僵尸守卫
	{
		if (objectp(me->get(sprintf("jiansi%d", i))))
			continue;
		p = get_valid_xy(z, x + random(10) - 5, y + random(10) - 5, IS_CHAR_BLOCK);
		if (!p)
			continue;
		npc = summon_4134(me);
		if (!npc)
			continue;
		npc->add_to_scene(z, p / 1000, p % 1000);
		npc->set_owner(me);
		NPC_SLAVE_D->find_enemy(npc); // 寻找敌人
		send_user(get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc),
				  41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE);
		me->set(sprintf("jiansi%d", i), npc);
	}
	for (i = 2; i < 3; i++) //1个鬼卒守卫
	{
		if (objectp(me->get(sprintf("guizhu%d", i))))
			continue;
		p = get_valid_xy(z, x + random(10) - 5, y + random(10) - 5, IS_CHAR_BLOCK);
		if (!p)
			continue;
		npc = summon_4131(me);
		if (!npc)
			continue;
		npc->add_to_scene(z, p / 1000, p % 1000);
		npc->set_owner(me);
		NPC_SLAVE_D->find_enemy(npc); // 寻找敌人
		send_user(get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc),
				  41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE);
		me->set(sprintf("guizhu%d", i), npc);
	}
}
// 函数：特技攻击对手
int perform_action(object who)
{
	int rate, x, y, z, p, i, j, x1, y1, x0, y0, z0;
	object me = this_object();

	if (distance_between(me, who) > me->get_max_seek())
		return 0;
	RelaxTime = 0;
	if (lowhp == 0 && get_hp() * 100 / get_max_hp() < 40) //生命值为40％以下
	{
		lowhp = 1;
		summon_guard();
		SAY_CMD->say(me, "Khả ác…… Bổn đạo trường khả bất hội tựu giá dạng bị đả bại đích!");
		return 0;
	}
	if (gone_time(summon) > 10) //召唤
	{
		summon = time();
		summon_guard();
	}
	if (gone_time(pTime) > 40) //幽冥法阵
	{
		pTime = time();
		if (random(100) < 60)
		{
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
			set_heart_state(me, MAGIC_STAT);
			set_heart_count_2(me, 5);
			me->set_cast_file(__FILE__);
			me->set_cast_arg(sprintf("%s %d", who->get_char_id(), 2));
			return 1;
		}
		return 0;
	}
	if (gone_time(pTime1) > 30) //尸偶术
	{
		pTime1 = time();
		if (random(100) < 50)
		{
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
			set_heart_state(me, MAGIC_STAT);
			set_heart_count_2(me, 5);
			me->set_cast_file(__FILE__);
			me->set_cast_arg(sprintf("%s %d", who->get_char_id(), 3));
			return 1;
		}
		return 0;
	}

	if (!who)
		return 0;
	rate = random(100);
	if (rate < 5) //死印
	{
		if (!who->can_be_fighted(me) || !me->can_fight(who))
			return 1;
		SAY_CMD->say(me, who->get_name() + "，受死吧！！");
		me->to_front_xy(get_x(who), get_y(who));
		send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
		send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END);
		set_heart_state(me, MAGIC_STAT);
		set_heart_count_2(me, 5);
		me->set_cast_file(__FILE__);
		me->set_cast_arg(sprintf("%s %d", who->get_char_id(), 1));
		return 1;
	}
	else //伏魔诀
		return "skill/02/02711"->perform_action_npc(me, who);

	return 0;
}

// 函数：复位处理
void reset()
{
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus(object who) { __FILE__->win_bonus_callout(this_object(), who); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout(object me, object who)
{
	object owner, *team;
	int level, level2, exp, exp2, pot, alllevel;
	int i, size, status, time, flag;

	CHAT_D->rumor_channel(0, CHAT + "Khu Thi Đạo trưởng đã bị tráng sĩ dũng cảm tiêu diệt");
	log_file("boss.txt", short_time() + " Khu Thi Đạo Trưởng bị tiêu diệt\n");

	if (!objectp(who = me->get_enemy_4()))
		return;

	if (owner = who->get_owner())
		who = owner;
	if (who->is_npc())
		return;

	drop_items(me, who);

	level = me->get_level();
	if (who->get_leader() && arrayp(team = who->get_team()) && sizeof(team) > 1)
	{
		team = me->correct_bonus_team(team);
		size = sizeof(team);
	}
	else
	{
		team = ({who});
		size = 1;
	}

	alllevel = 0;
	for (i = 0; i < size; i++)
		if (team[i])
		{
			alllevel += team[i]->get_level();
		}
	if (alllevel == 0)
		alllevel = 1;
	exp = 20000;
	for (i = 0; i < size; i++)
		if (team[i])
		{
			level2 = level - team[i]->get_level();
			exp2 = exp * team[i]->get_level() / alllevel;
			exp2 = me->correct_exp_bonus(level, level2, exp2) * who->get_online_rate() / 100;

			if (exp2 < 5)
				exp2 = 5;
			team[i]->add_exp(exp2);
			team[i]->add_potential(150);
			team[i]->add_log("#jiangsi", 1);
			team[i]->add_log("&jiangsi", exp2);
			team[i]->add_log("*jiangsi", 150);
		}
}

// 函数：掉宝奖励
void drop_items(object me, object who)
{
	int x, y, z, p, i, rate, rate1;
	string *nTmp, id, owner;
	object item, leader;

	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	id = who->get_leader();
	if (!id)
		owner = who->get_id();
	else
	{
		if (leader = find_player(id))
		{
			owner = leader->get_id();
		}
		else
			owner = who->get_id();
	}
	rate1 = me->correct_drop_rate(me->get_level() - who->get_level()) * who->get_online_rate() / 100;
	rate = random(100);
	if (rate < rate1)
	{
		//50级的随机门派蓝色装备2件
		for (i = 0; i < 2; i++)
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)], 0, 50, HEAD_TYPE + random(6));
				if (sizeof(nTmp))
				{
					item = new (nTmp[random(sizeof(nTmp))]);
					if (!item)
						return;
					ITEM_EQUIP_D->init_equip_prop_1(item);
					TEAM_D->drop_item(item, who);
					item->set_user_id(owner);
					item->add_to_scene(z, p / 1000, p % 1000);
					item->set("winner", who);
					item->set("time", time());
				}
			}
		//玉灵液
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/44/4404");
			if (!item)
				return;
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
		//随机宠物技能书
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/44/4488");
			if (!item)
				return;
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
		for (i = 0; i < 3; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/std/0001");
				item->set_value(100000);
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		for (i = 0; i < 5; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/TuiLinhThach/NgauNhien/2");
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}

	p = get_valid_xy(z, x, y, IS_ITEM_BLOCK);
	if (!p)
		return;
	rate = random(10000);
	if (rate < 500 * rate1 / 100) //50级的随机门派金色装备
	{
		nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)], 0, 50, HEAD_TYPE + random(6));
		if (sizeof(nTmp))
		{
			item = new (nTmp[random(sizeof(nTmp))]);
			if (!item)
				return;
			ITEM_EQUIP_D->init_equip_prop_3(item);
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	else if (rate < 4500 * rate1 / 100) //紫参丹
	{
		for (i = 0; i < 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/91/9167");
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	else if (rate < 9040 * rate1 / 100) //随机技能进阶2本
	{
		for (i = 0; i < 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new (BOOK_FILE->get_book_file());
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	else if (rate < 9090 * rate1 / 100) //1级晶石9个
	{
		for (i = 0; i < 9; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new (STONE_FILE->get_diamond_file());
				item->set_level(1);
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	else if (rate < 9100 * rate1 / 100) //1级晶石16个
	{
		for (i = 0; i < 16; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new (STONE_FILE->get_diamond_file());
				item->set_level(1);
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	else if (rate < 10000 * rate1 / 100) //八仙丹2个
	{
		for (i = 0; i < 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/91/9166");
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	"/sys/npc/npc"->drop_ball(me, who);
}

void do_look(object who)
{
	send_user(who, "%c%c%w%s", ':', 3, 9968, "Khu Thi Đạo Trưởng:\n  Sinh tử khứ lai, bằng đầu khôi lỗi. Nhất tuyến đoạn thời, lạc lạc lỗi lỗi. Hi hi, nhân đích sinh mệnh bất quá thị bần đạo thủ trung đích mộc ngẫu, tựu tượng giá ta cương thi nhất dạng, ngẫu tuyến nhất đoạn, thập ma đô hoàn kết liễu.\n" + sprintf(ESC "Khiêu chiến\ntalk %x# fight\n", getoid(this_object())) + ESC "Rời khỏi");
}

void do_fight()
{
	object who = this_player(), me = this_object();

	if (get_char_type() != OFFICER_TYPE) //普通状态
		return;
	set_char_type(FIGHTER_TYPE_2);
	add_to_scene(get_z(me), get_x(me), get_y(me));
}
//杀死一个敌人加10000气血
void stop_fight()
{
	object enemy;
	enemy = get_enemy();
	if (enemy && enemy->get_hp() == 0)
		add_hp(10000);
	::stop_fight();
}

//鬼卒召唤
object summon_4131(object who)
{
	int level = 55;
	object npc;

	npc = new ("npc/boss/00071");
	npc->set_char_picid(4131);
	npc->set_level(level);
	npc->set_name("Quỷ Tốt Thủ Vệ");
	npc->set_max_hp((150 + (level - 1) / 10 * 280) * 4);
	npc->set_max_mp(100 + (level - 1) / 10 * 20);
	npc->set_ap(20 + (level - 1) / 10 * 20);
	npc->set_dp(150 + (level - 1) / 10 * 60);
	npc->set_cp(65 + (level - 1) / 10 * 150);
	npc->set_pp(150 + (level - 1) / 10 * 60);
	npc->set_sp(80 + (level - 1) / 10 * 55);
	npc->set_hp(npc->get_max_hp());
	npc->set_mp(npc->get_max_mp());
	npc->set_owner(who);
	return npc;
}

//僵尸符法
object summon_4134(object who)
{
	int level = 55;
	object npc;

	npc = new ("npc/boss/00072");
	npc->set_char_picid(4134);
	npc->set_level(level);
	npc->set_name("Cương Thi Thủ Vệ");
	npc->set_max_hp((1600 + (level - 35) / 10 * 300) * 6);
	npc->set_ap(500 + (level - 35) / 10 * 120);
	npc->set_dp(300 + (level - 35) / 10 * 100);
	npc->set_pp(300 + (level - 35) / 10 * 100);
	npc->set_sp(150 + (level - 35) / 10 * 50);
	npc->set_hp(npc->get_max_hp());
	npc->set_mp(npc->get_max_mp());
	npc->set_owner(who);
	return npc;
}

// 函数：法术处理
int cast_done_npc(object me)
{
	object who, *user;
	string arg;
	int type, x, y, z, damage;

	if (!stringp(arg = me->get_cast_arg()))
		return 1;
	if (sscanf(arg, "%s %d", arg, type) != 2)
		return 1;
	if (type == 1)
	{
		if (!objectp(who = find_char(arg)))
			return 1;
		send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 41311, 1, OVER_BODY, PF_ONCE);
		if (!who->can_be_fighted(me) || !me->can_fight(who))
			return 2; // 执行成功
		who->set_hp(1);
	}
	else if (type == 2) //幽冥法阵
	{
		z = get_z(me);
		x = get_x(me);
		y = get_y(me);
		user = get_range_object(z, x, y, 10, USER_TYPE) + get_range_object(z, x, y, 10, CHAR_TYPE) - ({me});
		user -= ({0});
		if (!sizeof(user))
			return 1;
		damage = 250 + (55 - 22) / 10 * 200;
		foreach (who in user)
		{
			if (!who->can_be_fighted(me) || !me->can_fight(who))
				continue;
			send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who),
					  41451, 1, OVER_BODY, 41451, 1, OVER_BODY, PF_ONCE);
			if (-who->get("pf.fall") > damage / 15)
				continue;
			who->set("pf.fall", -damage / 15);
			if (who->is_user())
				who->set_save_2("pf.fall", -damage / 15);
			set_effect_2(who, EFFECT_CHAR_FALL, 20 / 2, 2);
			send_user(who, "%c%w%w%c", 0x81, 4145, get_effect_3(who, EFFECT_CHAR_FALL), EFFECT_BAD);
			send_user(get_scene_object_2(who, USER_TYPE) - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 4145, 1, EFFECT_BAD);
		}
	}
	else if (type == 3) //尸偶术
	{
		z = get_z(me);
		x = get_x(me);
		y = get_y(me);
		user = get_range_object(z, x, y, 10, USER_TYPE) + get_range_object(z, x, y, 10, CHAR_TYPE) - ({me});
		user -= ({0});
		if (!sizeof(user))
			return 1;
		foreach (who in user)
		{
			if (!who->can_be_fighted(me) || !me->can_fight(who))
				continue;
			if (who->is_anti_effect() || get_effect(who, EFFECT_CHAR_CHAOS) || get_effect(who, EFFECT_CHAR_CHAOS_0))
				continue;
			send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who),
					  41452, 1, OVER_BODY, 41452, 1, OVER_BODY, PF_ONCE);
			set_effect(who, EFFECT_CHAR_CHAOS, 10);
			send_user(who, "%c%w%w%c", 0x81, 9018, get_effect_3(who, EFFECT_CHAR_CHAOS), EFFECT_BAD);
			send_user(get_scene_object_2(who, USER_TYPE) - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9018, 1, EFFECT_BAD);
			send_user(who, "%c%c%c", 0x3d, 242, 1); // 鼠标失控
		}
	}
	return 2; // 执行成功
}