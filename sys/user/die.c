
#include <ansi.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：死亡复活处理
void revive(object me) // 躺１０分
{
	mapping skls;
	string *name;
	int level, gold, exp;
	int pk, z, x, y, p, i, size, upexp, die_flag;

	die_flag = me->is_die();
	me->set_die(0);
	me->set_enemy(0);

	pk = me->get_pk();
	level = me->get_level();

	// 临时取消PK标志的影响
	pk = 0;

	if (pk < 100)
	{
		gold = -me->get_cash() / 80;
		exp = -level * level * 30 / 4;
	}
	else
	{
		gold = -me->get_cash() / 100 * (pk + 5); // 小心溢出 ( pk + 5 ) / 100
		exp = -level * level * (30 + pk * 10);
	}
	upexp = me->get_upgrade_exp();
	if (-exp > upexp)
		exp = -upexp;

	if (me->get_level() < 15) // 死亡新手保护
	{
		gold = 0;
		exp = 0;
		me->set_hp(me->get_max_hp());
	}
	else
		me->set_hp(me->get_max_hp() / 10);
	if (me->get("me_die"))
	{
		gold = 0;
		exp = 0;
	}
	if (me->get_save("userkill") == 0 && die_flag != 6)
	{

		me->add_cash(gold);
		me->add_gold_log("pay", -gold);
		me->log_money("死亡", gold);
		"/sys/sys/count"->add_use("die", -gold);
		me->add_exp(exp);
		//        USER_EXP_D->recount_user_level(me);
		if (me->get_save_2("insurance.timeover") > time()) //保险赔偿
		{
			me->add_save_2("insurance.money", -gold / 2);
			me->add_save_2("insurance.exp", -exp / 2);
		}
	}
	else
	{
		gold = 0;
		exp = 0;
		me->set_save("userkill", 0);
	}
	skls = me->get_skill_dbase();

	CHAR_CHAR_D->init_loop_perform(me);

	//      me->set_char_action(DEFAULT_ACT);    // 取消死亡状态，恢复正常站立
	if (me->get("me_die")) //古墓探险死亡后跳入点
	{
		z = 80;
		x = 276;
		y = 163;
		if (x > 0 && y > 0)
		{
			p = get_valid_xy(z, x, y, IS_CHAR_BLOCK);
			if (p > 0)
			{
				x = p / 1000;
				y = p % 1000;
				me->add_to_scene(z, x, y);
				me->delete ("me_die");
			}
		}
		set_heart_beat(1);
		return;
	}

	MAP_D->add_to_void(me); // 移入 VOID 场景  // 复活点！
							//        send_user(me, "%c%s", '!', "您刚才死了，但是现在又复活了。");
	if (gold || exp)
		write_user(me, ECHO "Tổn thất của bạn sau khi tử vong : %+d Ngân lượng , %+d Kinh nghiệm !", gold, exp);

	//        me->add_pk(-1);
	set_heart_beat(1);
}

// 函数：死亡复活处理
void revive_5(object me) // 躺３秒
{
	object map, npc;
	string name;
	int z, x, y, p;

	me->set_enemy(0);

	z = get_z(me);
	map = get_map_object(z);
	CHAR_CHAR_D->init_loop_perform(me);
	me->set_die(0);
	if (map && (map->get_client_id() == 885 || map->get_client_id() == 891 || map->is_wushuang() || map->is_wushuang_palace()))
	{
		MAP_D->add_to_void(me);		// 移入 VOID 场景  // 复活点！
		if ((p = get_jumpin(80, 5)) // 跳入点 31: 摆摊区
			&& (z = 80) && (p = get_valid_xy(z, p / 1000, p % 1000, IS_CHAR_BLOCK)))
		{
			me->add_to_scene(z, p / 1000, p % 1000, 3);
		}
	}
	else if (MAP_D->is_inside_battle(z))
	{
		/*        	
                if(   ( name = me->get_org_name() ) != "" 
                &&      objectp( npc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) ) )
                &&    ( z = get_z(npc) )
                &&    ( p = get_valid_xy( z, get_x(npc) + random(11) - 5, get_y(npc) + random(11) - 5, IS_CHAR_BLOCK ) ) ) 
*/
		if (1)
		{
			if (me->get_2("jiguan.z") && me->get_2("jiguan.x") && me->get_2("jiguan.y"))
			{
				z = me->get_2("jiguan.z");
				x = me->get_2("jiguan.x");
				y = me->get_2("jiguan.y");
				p = get_valid_xy(z, x, y, IS_CHAR_BLOCK);
				if (p == 0)
					p = x * 1000 + y;

				if (objectp(map = get_map_object(get_z(me))))
				{
					map->sub_user(me);
					map->sub_user_2(me);
				}
				send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 9005, 1, OVER_BODY, PF_STOP);
				send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 9006, 1, OVER_BODY, PF_STOP);
				me->add_to_scene(z, p / 1000, p % 1000, 3);
				if (me->get_max_hp() >= 1000)
					me->set_hp(me->get_max_hp() / 10); // 气血剩下１０％
				else
					me->set_hp(100);

				switch (me->get_level()) // 设置玩家种类
				{
				case 0..9:
					USER_D->add_level_a_user(me);
					break;
				case 10..29:
					USER_D->add_level_b_user(me);
					break;
				default:
					USER_D->add_level_c_user(me);
					break;
				}
				USER_D->sub_battle_user(me);
				me->set_save("org_die", time());
				FAMILY_D->org_channel(name, 0, sprintf(HIR "%s vì đại nghĩa anh hùng nên đã hy sinh.", me->get_name()));
			}
			else
				MAP_D->add_to_void(me);
		}
		else
			MAP_D->add_to_void(me);
	}
	set_heart_beat(1);
}

// 函数：死亡复活处理
void revive_9(object me) // 躺１５秒
{
	int p;
	object map;
	string cTmp;
	me->set_die(0);
	me->set_enemy(0);
	CHAR_CHAR_D->init_loop_perform(me);
	send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 3294, 1, OVER_BODY, PF_ONCE);
	map = get_map_object(get_z(me));
	if (map && map->is_changping())
	{
		cTmp = me->get_2("changping.country");
		if (cTmp == "Tần Quốc")
			p = get_valid_xy(get_z(me), 52, 48, IS_CHAR_BLOCK);
		else if (cTmp == "Triệu Quốc")
			p = get_valid_xy(get_z(me), 196, 152, IS_CHAR_BLOCK);
		me->set_hp(me->get_max_hp());
		me->set_mp(me->get_max_mp());
	}
	else if (me->get("autoRun") || map->get_hoiSinh())
	{

		me->set_hp(me->get_max_hp());
		me->set_mp(me->get_max_mp());
		if ((p = efun::get_xy_point(get_z(me), IS_CHAR_BLOCK)))
		{
			me->add_to_scene(get_z(me), p / 1000, p % 1000, 3);
		}
	}

	else
	{
		me->set_hp(me->get_max_hp() / 10);
	}
	if (p)
		me->add_to_scene(get_z(me), p / 1000, p % 1000, 3);
}
