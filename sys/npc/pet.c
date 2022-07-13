/*******宠物模块********/
#include <effect.h>
#include <cmd.h>
#include <action.h>
#include <skill.h>
#include <ansi.h>
#define PET_NPC "npc/std/pet"

static int PetTime; //宠物生日时间

void count_all_prop(object me);

// 函数:生成二进制码
void SAVE_BINARY() {}

// 函数:判断可以战斗
int can_fight(object me, object who)
{
	object owner, enemy, map;

	if (me->is_die())
		return 0;
	me->set_enemy(0);
	if (!me->get("show"))
		return 0;
	if (me->get_no_fight())
		return 0;
	if (me == who)
		return 0; // 禁止攻击自己
				  //	map = get_map_object(get_z(me));
				  //	if (map->get_no_fight()) return 0;

	if (!(owner = me->get_owner()))
		return 0;
	if (owner == who)
		return 0; // 禁止攻击主人
	if (owner == who->get_owner())
		return 0;
	if (!owner->can_fight(who)) // 主人能否攻击
		return 0;
	me->set_enemy(who);
	return 1;
}
// 函数:可以接受战斗
int can_be_fighted(object me, object who)
{
	object owner, enemy, map;

	if (me->is_die())
		return 0;
	who->set_enemy(0);
	if (!me->get("show"))
		return 0;
	if (who->get_no_fight())
		return 0;
	if (me == who)
		return 0; // 禁止攻击自己
				  //	map = get_map_object(get_z(me));
				  //	if (map->get_no_fight()) return 0;

	if (!(owner = me->get_owner()))
		return 0;
	if (owner == who)
		return 0; // 主人禁止攻击
	if (owner == who->get_owner())
		return 0;

	if (!owner->can_be_fighted(who)) // 主人能否攻击
		return 0;
	who->set_enemy(enemy);
	return 1;
}
// 函数:获取升级所需经验
int get_level_exp(int level)
{
	return level * level * level * level / 40 + 50 * (level + 1);
}
//设置宠物的属性
int set_pet_info(object pet)
{
	int i, size;
	string *nSkill;
	mapping mpInfo, mpSkill;
	mpInfo = "quest/pet"->get_beast_info(pet->get_firstname());
	if (!mpInfo)
		return 0;
	pet->set_attack_speed(mpInfo["att_spe"]);
	pet->set_walk_speed(mpInfo["walk_spe"]);
	if (!get_effect(pet, EFFECT_MAGIC_CARD)) //变身状态
		pet->set_char_picid(pet->get_portrait());
	count_all_prop(pet);
	//技能的影响
	mpSkill = pet->get_skill_dbase();
	if (mpSkill)
	{
		nSkill = keys(mpSkill);
		for (i = 0, size = sizeof(nSkill); i < size; i++)
		{
			pet->remove_skill_effect(to_int(nSkill[i]));
			pet->skill_effect(to_int(nSkill[i]));
		}
	}
	return 1;
}
//生成新宠物
int generate_pet(object pet, string cName, int level, int iBlood)
{
	int iBonus, i, j, k, *nTmp, size, iSki;
	mapping mpInfo;
	int *list = ({
		0,
		0,
		0,
		0,
		0,
	});
	int *pos = ({
		0,
		1,
		2,
		3,
		4,
	});

	pet->set_firstname(cName);
	pet->set_name(cName);
	pet->set_blood(iBlood);
	pet->set_faith(80);
	pet->set_giftpoint(0);
	pet->init_skill_dbase();
	pet->add_exp(-1 * pet->get_exp());

	if (iBlood == 1)
	{
		iBonus = 50;
		level = 0;
	}
	else
		iBonus = level * 4;
	pet->set_level(level);
	for (k = 0; k < 4; k++)
	{
		i = random(iBonus);
		j = random(sizeof(pos));
		list[pos[j]] = i;
		iBonus -= i;
		pos -= ({pos[j]});
	}
	list[pos[0]] = iBonus;
	pet->set_con(10 + level + list[0]); //体魄
	pet->set_spi(10 + level + list[1]); //精神
	pet->set_str(10 + level + list[2]); //力量
	pet->set_cps(10 + level + list[3]); //耐力
	pet->set_dex(10 + level + list[4]); //智力

	mpInfo = "quest/pet"->get_beast_info(cName);
	if (!mpInfo)
		return 0;
	pet->set_con_grow(mpInfo["con"] * (1001 + random(100)) / 1000);
	pet->set_str_grow(mpInfo["str"] * (1001 + random(100)) / 1000);
	pet->set_cps_grow(mpInfo["cps"] * (1001 + random(100)) / 1000);
	pet->set_mp_grow(mpInfo["mp"] * (1001 + random(100)) / 1000);
	pet->set_ma_grow(mpInfo["ma"] * (1001 + random(100)) / 1000);
	pet->set_md_grow(mpInfo["md"] * (1001 + random(100)) / 1000);
	pet->set_dex_grow(mpInfo["dex"] * (1001 + random(100)) / 1000);
	pet->set_life(mpInfo["life"] + random(10));
	nTmp = mpInfo["skill"];
	size = sizeof(nTmp);
	size = random100() * size / 100;
	for (i = 0; i < size; i++)
	{
		iSki = nTmp[random(sizeof(nTmp))];
		nTmp -= ({iSki});
		pet->set_skill(iSki, 1);
	}

	i = set_pet_info(pet);
	pet->set_hp(pet->get_max_hp());
	pet->set_mp(pet->get_max_mp());
	pet->set_head_color("quest/pet"->get_pet_color(cName));
	return 1;
}
//生成新神兽
int generate_shenshou(object pet, string cName)
{
	int iBonus, i, j, k, *nTmp, size, iSki, level;
	mapping mpInfo;
	int *list = ({
		0,
		0,
		0,
		0,
		0,
	});
	int *pos = ({
		0,
		1,
		2,
		3,
		4,
	});

	pet->set_firstname(cName);
	pet->set_name(cName);
	pet->set_blood(1);
	pet->set_faith(80);
	pet->set_giftpoint(0);
	pet->init_skill_dbase();
	pet->add_exp(-1 * pet->get_exp());

	iBonus = 50;
	level = 0;
	pet->set_level(level);
	for (k = 0; k < 4; k++)
	{
		i = random(iBonus);
		j = random(sizeof(pos));
		list[pos[j]] = i;
		iBonus -= i;
		pos -= ({pos[j]});
	}
	list[pos[0]] = iBonus;
	pet->set_con(10 + level + list[0]); //体魄
	pet->set_spi(10 + level + list[1]); //精神
	pet->set_str(10 + level + list[2]); //力量
	pet->set_cps(10 + level + list[3]); //耐力
	pet->set_dex(10 + level + list[4]); //智力

	mpInfo = "quest/pet"->get_beast_info(cName);
	if (!mpInfo)
		return 0;
	pet->set_con_grow(mpInfo["con"]);
	pet->set_str_grow(mpInfo["str"]);
	pet->set_cps_grow(mpInfo["cps"]);
	pet->set_mp_grow(mpInfo["mp"]);
	pet->set_ma_grow(mpInfo["ma"]);
	pet->set_md_grow(mpInfo["md"]);
	pet->set_dex_grow(mpInfo["dex"]);
	pet->set_life(mpInfo["life"]);
	nTmp = mpInfo["skill"];
	size = sizeof(nTmp);
	for (i = 0; i < size; i++)
	{
		iSki = nTmp[i];
		pet->set_skill(iSki, 1);
	}

	i = set_pet_info(pet);
	pet->set_hp(pet->get_max_hp());
	pet->set_mp(pet->get_max_mp());
	pet->set_head_color("quest/pet"->get_pet_color(cName));
	pet->set_save("shenshou", 1);
	return 1;
}
//恢复宠物属性
int restore_pet(object pet)
{
}
//获取宠物阶级
int get_class()
{
}

// 函数:搜索敌人(心跳之中调用)
void find_enemy(object me)
{
	object who, *see, *char, npc;
	object soldier, *zombie;
	int z, x, y, z1, x1, y1, p;
	int i, size;

	if (!objectp(who = me->get_owner()))
		return;

	if (distance_between(me, who) >= 25 && me->get_action() != 0) // 回到主人身边
	{
		z = get_z(who);
		x = get_x(who);
		y = get_y(who);
		if (p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK))
		{
			x1 = p / 1000;
			y1 = p % 1000;
			me->add_to_scene(z, x1, y1, get_front_xy(x1, y1, x, y), 9413, 0, 9413, 0);
		}
	}
	if (me->get_action() == 0)
		return; // 不攻击
	if (me->get_action_mode() != 1)
		return; // 在回主人身边的时候不攻击
	if (objectp(me->get_enemy()))
		return;																					  // 有对手就不寻找
	if (objectp(npc = who->get_enemy()) && inside_screen_2(who, npc) && inside_screen_2(me, npc)) // 主人攻击目标
	{
		if (me->get_enemy() != npc)
			me->set_fight_time(time());
		me->set_enemy(npc);
		return;
	}
	/*
        z = get_z(me);  x = get_x(me);  y = get_y(me);
        see = get_range_object(z, x, y, 10, USER_TYPE) + get_range_object(z, x, y, 10, CHAR_TYPE);    // 可见范围

        char = filter_array( see, (: objectp($1) && $1->get_enemy() == $2 :), who );    // 对主人有敌意

        if( objectp(npc = get_near_char(char, z, x, y) ) )
        {
                if( me->get_enemy() != npc ) me->set_fight_time( time() );
                me->set_enemy(npc);
                return;
        }

        char = filter_array( see, (: objectp($1) && $1->get_enemy() == $2 :), me );    // 对自己有敌意

        if( objectp(npc = get_near_char(char, z, x, y) ) )
        {
                if( me->get_enemy() != npc ) me->set_fight_time( time() );
                me->set_enemy(npc);
                return;
        }

        char = ({ });

        if( objectp( soldier = who->get("soldier") ) )    // 其它天兵攻击目标
        {
                if( objectp( npc = soldier->get_enemy() ) ) char += ({ npc });
        }
        if( arrayp( zombie = who->get("zombie") ) )
        {
                for( i = 0, size = sizeof(zombie); i < size; i ++ ) 
                        if( zombie[i] && objectp( npc = zombie[i]->get_enemy() ) ) char += ({ npc });
        }
        char = see - ( see - char );  

        if( objectp(npc = get_near_char(char, z, x, y) ) )
        {
                if( me->get_enemy() != npc ) me->set_fight_time( time() );
                me->set_enemy(npc);
                return;
        }

        char = ({ });

        if( objectp( soldier = who->get("soldier") ) )    // 对其它天兵有敌意
        {
                char += filter_array( see, (: objectp($1) && $1->get_enemy() == $2 :), soldier );
        }
        if( arrayp( zombie = who->get("zombie") ) )
        {
                for( i = 0, size = sizeof(zombie); i < size; i ++ ) if( zombie[i] )
                        char += filter_array( see, (: objectp($1) && $1->get_enemy() == $2 :), zombie[i] );
        }

        if( objectp(npc = get_near_char(char, z, x, y) ) )
        {
                if( me->get_enemy() != npc ) me->set_fight_time( time() );
                me->set_enemy(npc);
                return;
        }

        if(     objectp( npc = who->get_enemy() )    // who->get_main_enemy()
        &&      inside_screen_2(who, npc) && inside_screen_2(me, npc) )    // 对主人造成伤害
        {
                if( me->get_enemy() != npc ) me->set_fight_time( time() );
                me->set_enemy(npc);
                return;
        }
        
        if (me->get_action_mode()!=1) return;	// 不主动攻击别人        

        if( inside_screen_2(me, who) )    // 搜索(主人)最近怪物
        {
                if( MAP_D->is_inside_battle(z) )    // 战场之上
                {
                        char = filter_array( see, (: objectp($1) && $1->get_org_name() != $2->get_org_name() && $1->is_seller()==0 :), who );    // 所在不同帮派

                        if( objectp(npc = get_near_char(char, z, x, y) ) )
                        {
                                if( me->get_enemy() != npc ) me->set_fight_time( time() );
                                me->set_enemy(npc);
                                return;
                        }
                }
                else    // 平时场景
                {
                        x = get_x(who);  y = get_y(who);
                        if( npc = get_near_object(z, x, y, 10, CHAR_TYPE) )
                                if( npc->is_badman() ) me->start_fight(npc);
                }
        }
*/
}
void follow_owner(object me)
{
	object owner, who;
	string cmd;
	int x, y, z, x1, y1, p, walk;
	x = get_x(me);
	y = get_y(me);
	if (objectp(owner = me->get_owner()))
	{
		x1 = get_x(owner);
		y1 = get_y(owner);
		z = get_z(owner);
		if (z != get_z(owner) || distance_between(me, owner) >= 25 && me->get_action() != 0) // 回到主人身边
		{
			if (p = get_valid_xy(z, x1 + random(3) - 1, y1 + random(3) - 1, IS_CHAR_BLOCK))
			{
				x1 = p / 1000;
				y1 = p % 1000;
				me->add_to_scene(z, x1, y1, get_front_xy(x1, y1, x, y), 9413, 0, 9413, 0);
			}
			return;
		}

		if (abs(x - x1) < 2 && abs(y - y1) < 2)
		{
			me->set_action(me->get_next_action());
			return;
		}

		if (x1 > x)
			x1--;
		else if (x1 < x)
			x1++;
		if (y1 > y)
			y1--;
		else if (y1 < y)
			y1++;

		if (x != x1 || y != y1)
		{
			if (p = get_valid_path(get_z(me), x, y, x1, y1))
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
	}

	x = abs(x - get_x(me));
	y = abs(y - get_y(me));
	walk = (x > y) ? x : y;

	if (walk > 0)
	{
		set_heart_state(me, WALK_STAT);
		set_heart_count_2(me, me->get_walk_speed() * walk); // walk * 10 / 4
															//                if (owner) tell_user(owner, "时间 %d 步数 %d 间隔 %d 步速 %d", get_heart_timer(me), walk, get_heart_count_2(me), me->get_walk_speed() );
	}
}

// 函数:人物心跳处理
void heart_beat_walk(object me) // 每 0.1 秒处理
{
	object owner, who, oSki;
	string cmd;
	int x, y, x1, y1, p, walk, tick, iSki;

	if (!me->get("show"))
	{
		if (me->get_save("sungvatthach") > 0)
		{
			if (gone_time(me->get("sungvatthachtime")) >= 1)
			{
				me->delete ("sungvatthachtime");
				me->add_save("sungvatthach", -2);
				me->add_hp(100);
				me->add_mp(100);
				send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE);
			}
			me->set("sungvatthachtime", time());
		}
		return;
	}
	tick = me->add("tick", 1);
	if (tick >= 10) //减寿命, 忠诚
	{
		if (me->get("show_time") <= 0)
			me->set("show_time", time());
		if ((p = gone_time(me->get("show_time"))) >= 30) //超过30秒累计一次
		{
			me->set("show_time", time());
			p = me->add_save("show_time", p);
			if (p >= 600) //10分钟计算一次
			{
				me->add_life(-1);
				me->add_faith(-1);
				me->add_save("show_time", -600);
			}
		}

		me->delete ("tick");
	}
	if (me->get_save("sungvatthach") > 0)
	{
		if (gone_time(me->get("sungvatthachtime")) >= 1)
		{
			me->delete ("sungvatthachtime");
			me->add_save("sungvatthach", -2);
			me->add_hp(100);
			me->add_mp(100);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE);
		}
		me->set("sungvatthachtime", time());
	}

	if (get_effect(me, EFFECT_CHAR_BUSY) || get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_CHAR_FREEZE))
		return;

	//对己使用法术
	iSki = me->get_default_skill1();
	if (iSki && (oSki = load_object(SKILL->get_perform_file(iSki))))
	{
		if (oSki->perform_action_npc(me)) //使用成功
			return;
	}
	who = me->get_main_enemy();
	if (me->get_action() == 2 && me->get_action_mode() != 1 && !who)
	{
		follow_owner(me);
		return;
	}
	if (time() - me->get("2122") < 6)
		;
	else if (who) // 搜索何人攻击(最重要的敌人)
	{
		if (me->get_enemy() != who)
			me->set_fight_time(time());
		me->set_enemy(who);
	}
	else
		find_enemy(me); // 搜索攻击对象

	if (gone_time(me->get_fight_time()) > 110) // 110 秒打不死
	{
		me->init_enemy_damage(0, 0); // 清除伤害状态
		me->set_enemy(0);
		find_enemy(me); // 搜索攻击对象
	}
	x = get_x(me);
	y = get_y(me);

	if (objectp(who = me->get_enemy()) && !who->is_die())
		me->follow_user();
	else if (objectp(owner = me->get_owner()))
	{
		if (me->get_action() == 0)
			return;
		follow_owner(me);
		return;
	}
	x = abs(x - get_x(me));
	y = abs(y - get_y(me));
	walk = (x > y) ? x : y;

	if (walk > 0)
	{
		set_heart_state(me, WALK_STAT);
		set_heart_count_2(me, me->get_walk_speed() * walk); // walk * 10 / 4
															//                if (owner) tell_user(owner, "时间 %d 步数 %d 间隔 %d 步速 %d", get_heart_timer(me), walk, get_heart_count_2(me), me->get_walk_speed() );
	}
}
//宠物复活
void revive(object pet)
{
	int z;
	pet->set_die(0);
	pet->set_no_fight(0);
	if (!pet->get("show"))
		return;
	z = get_z(pet);
	if (!z)
		return;
	pet->add_to_scence(z, get_x(pet), get_y(pet));
}
//宠物死亡处理
void pet_die(object me, object pet, int iFlag)
{
	int revive;
	object owner;

	pet->set_cast_file(0); // 清除法术特技
	pet->set_cast_arg("");
	pet->set_perform_file(0); // 清除非法特技

	CHAR_CHAR_D->stop_loop_perform(pet);	// 中断持续效果
	CHAR_CHAR_D->stop_loop_perform_4(pet);	// 中断持续效果(不良)
											//        CHAR_CHAR_D->stop_loop_perform_5(pet);    // 中断持续效果(神打)
											//        CHAR_CHAR_D->stop_loop_perform_9(pet);    // 中断持续效果(其它)
	CHAR_CHAR_D->stop_poison_effect(pet);	// 中断毒药效果
	if (get_effect(pet, EFFECT_MAGIC_CARD)) //中断变身效果
		set_effect_2(pet, EFFECT_MAGIC_CARD, 1, 1);

	pet->add_life(-50);
	pet->add_faith(-25);
	send_user(get_scene_object_2(pet, USER_TYPE), "%c%d%d%c", 0x40, getoid(pet), time2(), FALL_ACT);
	if (iFlag == 1 && (revive = pet->get("revive")) && (time() - pet->get_save("revive_time") > 1800)) //复活
	{
		if (revive == 1)
		{
			pet->set_hp(pet->get_max_hp() / 5);
			pet->set_mp(pet->get_max_mp() / 5);
		}
		else if (revive == 2)
		{
			pet->set_hp(pet->get_max_hp() / 2);
			pet->set_mp(pet->get_max_mp() / 2);
		}
		pet->set_save("revive_time", time());
		pet->set_die(3);
		pet->set_no_fight(1);
		set_effect(pet, EFFECT_NPC_DIE, 10);
		return;
	}
	pet->set_hp(pet->get_max_hp() / 2);
	pet->set_mp(pet->get_max_mp() / 2);
	owner = pet->get_owner();
	USER_BEAST_D->hide_beast(owner, pet);
	//	pet->set_dead_time(time());
	//	pet->set_weakness(1);
	//	send_user(owner,"%c%c%d%d", 0xA1,4,getoid(pet),600);
}

//战斗奖励
void fight_bonus(object owner, object npc, int team_size, int doubletime, int extra)
{
	int exp, exp1, level, level1, time;
	object pet;

	pet = owner->get("showbeast");
	if (!pet || !pet->is_pet())
		return;
	if (distance_between(npc, pet) > 30)
		return;
	if ((level = pet->get_level()) >= owner->get_level() || level >= pet->get_max_pet_level())
	{
		//	send_user(owner,"%c%s",'>',"Đẳng cấp Bảo Thú "+pet->get_name()+" của bạn trước mắt đã đạt đến đỉnh điểm, tham chiến sẽ không nhận thêm Kinh nghiệm nữa!");
		return;
	}
	team_size = range_value(team_size, 1, 5);
	exp = NPC_ENERGY_D->get_exp_bonus(level1 = npc->get_level()); // 查表取值
	exp = npc->correct_exp_bonus(level1, level1 - level, exp) * owner->get_online_rate() / 100;
	exp *= team_size;
	if (doubletime) //双倍时间
		exp1 = exp * 2;
	else
		exp1 = exp;
	if (extra) //号角
		exp1 += exp / 5;

	pet->add_exp(exp1);
	//send_user(owner,"%c%s",'>',sprintf("您的宠物%s得到%d点经验",pet->get_name(),exp1));
}
//增加属性点
void add_giftpoint(object pet, string arg)
{
	int con, spi, str, cps, dex, sum;
	if (!pet->is_pet())
		return;
	if (sscanf(arg, "%d %d %d %d %d", con, spi, str, cps, dex) != 5)
		return;
	if (con < 0 || spi < 0 || str < 0 || cps < 0 || dex < 0)
		return;
	sum = con + spi + str + cps + dex;
	if (!sum)
		return;
	if (sum > pet->get_giftpoint())
	{
		send_user(pet->get_owner(), "%c%s", '!', "Không đủ điểm phân phối !");
		return;
	}
	else if (sum < 0)
	{
		send_user(pet->get_owner(), "%c%s", '!', "Bạn đã Hack Pet thành công !");
		return;
	}
	pet->add_giftpoint(-sum);
	if (con)
		pet->add_con(con);
	if (spi)
		pet->add_spi(spi);
	if (str)
		pet->add_str(str);
	if (cps)
		pet->add_cps(cps);
	if (dex)
		pet->add_dex(dex);

	set_pet_info(pet);
	pet->set_hp(pet->get_max_hp());
	pet->set_mp(pet->get_max_mp());
	send_user(pet->get_owner(), "%c%c%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", 0xA1, 6, getoid(pet), pet->get_level(), pet->get_hp(), pet->get_max_hp(), pet->get_mp(), pet->get_max_mp(), pet->get_ap_0(), pet->get_ap(), pet->get_dp_0(), pet->get_dp(), pet->get_cp_0(), pet->get_cp(), pet->get_pp_0(), pet->get_pp(), pet->get_sp(), pet->get_double_rate(), pet->get_con(), pet->get_spi(), pet->get_str(), pet->get_cps(), pet->get_dex(), pet->get_giftpoint(), pet->get_faith(), pet->get_exp(), pet->get_upgrade_exp(), );
}
// 函数:升级
int upgrade(object pet)
{
	int level;
	object owner;
	level = pet->get_level();
	if (level < pet->get_max_pet_level())
	{
		owner = pet->get_owner();
		level++;
		pet->set_level(level);
		pet->set_hp(pet->get_max_hp()); // 升级加满气血
		pet->set_mp(pet->get_max_mp());
		//计算属性点数
		pet->add_giftpoint(4);
		pet->add_con(1);
		pet->add_spi(1);
		pet->add_str(1);
		pet->add_cps(1);
		pet->add_dex(1);
		set_pet_info(pet);
		send_user(owner, "%c%s", '!', sprintf("Bảo Thú %s của bạn tăng đến cấp %d !", pet->get_name(), level));
		//[A1][6][宠物ID][等级][气血][最大气血] [法力][最大法力] [物攻][物防] [法攻][法防] [躲闪][暴击][体魄][精神][力量][耐力][敏捷][分配点数] [忠诚] [经验][升级经验]
		send_user(owner, "%c%c%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", 0xA1, 6, getoid(pet), pet->get_level(), pet->get_hp(), pet->get_max_hp(), pet->get_mp(), pet->get_max_mp(), pet->get_ap_0(), pet->get_ap(), pet->get_dp_0(), pet->get_dp(), pet->get_cp_0(), pet->get_cp(), pet->get_pp_0(), pet->get_pp(), pet->get_sp(), pet->get_double_rate(), pet->get_con(), pet->get_spi(), pet->get_str(), pet->get_cps(), pet->get_dex(), pet->get_giftpoint(), pet->get_faith(), pet->get_exp(), pet->get_upgrade_exp(), );
		send_user(get_scene_object_2(pet, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(pet),
				  9043, 1, OVER_BODY, 9044, 1, OVER_BODY, PF_ONCE);
	}
	return 1;
}
// 函数:统计最大ＨＰ
void count_max_hp(object me)
{
	int hp, *nProp;
	mapping mpInfo;
	mpInfo = "quest/pet"->get_beast_info(me->get_firstname());
	if (!mpInfo)
		return;
	nProp = "quest/pet"->get_beast_prop(mpInfo["cKind"]);
	if (!nProp)
		return;
	hp = me->get_con() * (me->get_level() * 4 + nProp[0] * 10) / 100 * me->get_con_grow() / 1000;
	hp += hp * me->get("hp%") / 100;
	hp += me->get("hp");
	if (me->get("sk74213")) //高级御命术
		hp += me->get("sk74213");
	else if (me->get("sk74122")) //御命术
		hp += me->get("sk74122");
	if (get_effect(me, EFFECT_MAGIC_CARD) && me->get_save("change_shape") == 8100) //变身虎王
		hp += hp;
	me->set_max_hp(hp);
	if (me->get_hp() > hp)
		me->set_hp(hp);
}
// 函数:统计最大ＭＰ
void count_max_mp(object me)
{
	int mp, *nProp;
	mapping mpInfo;
	mpInfo = "quest/pet"->get_beast_info(me->get_firstname());
	if (!mpInfo)
		return;
	nProp = "quest/pet"->get_beast_prop(mpInfo["cKind"]);
	if (!nProp)
		return;
	mp = me->get_spi() * (me->get_level() * 4 + nProp[1] * 10) / 100 * me->get_mp_grow() / 1000;
	mp += mp * me->get("mp%") / 100;
	mp += me->get("mp");
	if (get_effect(me, EFFECT_MAGIC_CARD) && me->get_save("change_shape") == 8100) //变身虎王
		mp += mp;
	me->set_max_mp(mp);
	if (me->get_mp() > mp)
		me->set_mp(mp);
}
// 函数:统计法术攻击
void count_cp(object me)
{
	int cp, *nProp;
	mapping mpInfo;
	mpInfo = "quest/pet"->get_beast_info(me->get_firstname());
	if (!mpInfo)
		return;
	nProp = "quest/pet"->get_beast_prop(mpInfo["cKind"]);
	if (!nProp)
		return;
	cp = me->get_spi() * (me->get_level() / 10 + nProp[4]) / 10 * me->get_ma_grow() / 1000;
	cp += cp * me->get("cp%") / 100;
	cp += me->get("cp");
	if (me->get("sk74206")) //高级御法
		cp += me->get("sk74206");
	else if (me->get("sk74115")) //御法
		cp += me->get("sk74115");
	if (get_effect(me, EFFECT_MAGIC_CARD) && me->get_save("change_shape") == 8100) //变身虎王
		cp += cp;
	me->set_cp(cp);
}
// 函数:统计法术防御
void count_pp(object me)
{
	int pp, *nProp;
	mapping mpInfo;
	mpInfo = "quest/pet"->get_beast_info(me->get_firstname());
	if (!mpInfo)
		return;
	nProp = "quest/pet"->get_beast_prop(mpInfo["cKind"]);
	if (!nProp)
		return;
	pp = me->get_spi() * (me->get_level() / 10 + nProp[5]) / 10 * me->get_md_grow() / 1000;
	pp += pp * me->get("pp%") / 100;
	pp += me->get("pp");
	if (me->get("sk74202")) //高级法盾
		pp += me->get("sk74202");
	else if (me->get("sk74102")) //法盾
		pp += me->get("sk74102");
	if (get_effect(me, EFFECT_USER_PP))
		pp += me->get("03292#");
	if (get_effect(me, EFFECT_MAGIC_CARD) && me->get_save("change_shape") == 8100) //变身虎王
		pp += pp;

	me->set_pp(pp);
}
// 函数:统计物理攻击
void count_ap(object me)
{
	int ap, *nProp;
	mapping mpInfo;
	mpInfo = "quest/pet"->get_beast_info(me->get_firstname());
	if (!mpInfo)
		return;
	nProp = "quest/pet"->get_beast_prop(mpInfo["cKind"]);
	if (!nProp)
		return;
	ap = me->get_str() * (me->get_level() / 10 + nProp[2]) / 10 * me->get_str_grow() / 1000;
	if (get_effect(me, EFFECT_CHAR_WOUND))
		ap -= ap * 30 / 100; // 负伤
	ap += ap * me->get("ap%") / 100;
	ap += me->get("ap");
	if (me->get("sk74205")) //高级强攻
		ap += me->get("sk74205");
	else if (me->get("sk74114")) //强攻
		ap += me->get("sk74114");
	if (get_effect(me, EFFECT_MAGIC_CARD) && me->get_save("change_shape") == 8100) //变身虎王
		ap += ap;
	me->set_ap(ap);
}
// 函数:统计物理防御
void count_dp(object me)
{
	int dp, *nProp;
	mapping mpInfo;
	mpInfo = "quest/pet"->get_beast_info(me->get_firstname());
	if (!mpInfo)
		return;
	nProp = "quest/pet"->get_beast_prop(mpInfo["cKind"]);
	if (!nProp)
		return;
	dp = me->get_cps() * (me->get_level() / 10 + nProp[3]) / 10 * me->get_cps_grow() / 1000;
	if (get_effect(me, EFFECT_CHAR_WOUND))
		dp -= dp * 30 / 100; // 负伤
	dp += dp * me->get("dp%") / 100;
	dp += me->get("dp");
	if (me->get("sk74201")) //高级防盾
		dp += me->get("sk74201");
	else if (me->get("sk74101")) //防盾
		dp += me->get("sk74101");
	if (get_effect(me, EFFECT_USER_DP))
		dp += me->get("03291#");
	if (get_effect(me, EFFECT_MAGIC_CARD) && me->get_save("change_shape") == 8100) //变身虎王
		dp += dp;
	me->set_dp(dp);
}
// 函数:统计腾挪躲闪
void count_sp(object me)
{
	int sp, *nProp;
	mapping mpInfo;
	mpInfo = "quest/pet"->get_beast_info(me->get_firstname());
	if (!mpInfo)
		return;
	nProp = "quest/pet"->get_beast_prop(mpInfo["cKind"]);
	if (!nProp)
		return;
	sp = me->get_dex() * (me->get_level() / 10 + nProp[6]) / 10 * me->get_dex_grow() / 1000;
	sp += sp * me->get("sp%") / 100;
	sp += me->get("sp");
	if (me->get("sk74214")) //高级飞行术
		sp += me->get("sk74214");
	else if (me->get("sk74123")) //飞行术
		sp += me->get("sk74123");
	if (get_effect(me, EFFECT_MAGIC_CARD) && me->get_save("change_shape") == 8100) //变身虎王
		sp += sp;
	me->set_sp(sp);
}
// 函数:统计抗毒率/御毒率
void count_poison(object me)
{
	me->set_poison_rate(me->get("@%"));
	me->set_anti_poison(me->get("X@%"));
	me->set_lost_poison(me->get("-@%"));
	me->set_immunity(me->get("/%"));
}
// 函数:统计吸取气血/法力
void count_absorb(object me)
{
	me->set_absorb_hp(me->get("hp*"));
	me->set_absorb_mp(me->get("mp*"));
}
// 函数:统计命中率
void count_hit_rate(object me)
{
	me->set_hit_rate(me->get("!%"));
	me->set_hit_rate_2(me->get("c!%"));
	me->set_hit_rate_3(me->get("t!%"));
}
// 函数:统计闪避率
void count_dodge_rate(object me)
{
	me->set_dodge_rate(me->get("?%"));
	me->set_dodge_rate_2(me->get("c?%"));
}
// 函数:统计免伤害
void count_anti_hurt(object me)
{
	me->set_anti_hurt(me->get("-*"));
	me->set_anti_hurt_rate(me->get("-*%"));
	me->set_anti_hurt_rate_2(me->get("-c*%"));
}
// 函数:统计反伤害
void count_hurt(object me)
{
	int cent = 0, rand = 0;
	me->set_hurt_rate(cent);
	me->set_hurt_rand(rand);
	cent = 0;
	rand = 0;
	me->set_hurt_rate_2(cent);
	me->set_hurt_rand_2(rand);
}
// 函数:统计其它
void count_other(object me)
{
	int cent;
	me->set_lucky(me->get("??%"));
	me->set_less_prop(me->get("#%"));
	cent = 0;
	me->set_healing_rate(cent);
	//暴击率
	cent = me->get_dex() * 100 / 80;
	if (me->get("sk74204")) //高级暴击
		cent += me->get("sk74204");
	else if (me->get("sk74113")) //暴击
		cent += me->get("sk74113");
	me->set_double_rate(cent);
	me->set_double_rate2(cent);
	//抗封魔率
	me->set_anti_NoPF(0);
}
// 函数:统计所有属性
void count_all_prop(object me)
{
	count_max_hp(me);
	count_max_mp(me);
	count_cp(me); // cp/pp 影响 ap/dp, 所以放前
	count_pp(me);
	count_ap(me);
	count_dp(me);
	count_sp(me);

	count_poison(me);
	count_absorb(me);
	count_hit_rate(me);
	count_dodge_rate(me);
	count_anti_hurt(me);
	count_hurt(me);
	count_other(me);
}
//设定默认使用技能
void set_default_skill(object pet, string arg)
{
	int iSkill, i;
	object owner;
	iSkill = to_int(arg);

	i = pet->get_default_skill();
	owner = pet->get_owner();
	if (owner && i)
		send_user(owner, "%c%c%d%d%c", 0xA1, 22, 0, i, 0);
	if (!iSkill || iSkill == 74001)
	{
		pet->set_default_skill(0);
		return;
	}
	if (pet->get_skill(iSkill))
		iSkill = pet->set_default_skill(iSkill);
	if (owner && iSkill)
		send_user(owner, "%c%c%d%d%c", 0xA1, 22, 0, iSkill, 1);
}
//宠物技能攻击:使用默认技能, 没有默认技能则物理攻击
int perform_action(object pet, object who)
{
	int iSkill, type;
	object oSki, oEnemy;

	iSkill = pet->get_default_skill();
	if (!iSkill || !(oSki = load_object(SKILL->get_perform_file(iSkill))))
		return 0;
	type = oSki->get_perform_type();
	if (type == ON_ME_P)
		return oSki->perform_action_npc(pet, 0);
	oEnemy = pet->get_enemy_3();
	if (!oEnemy)
	{
		find_enemy(pet);
		oEnemy = pet->get_enemy();
		if (!oEnemy)
			return 0;
		pet->set_enemy_3(oEnemy);
	}

	if (type == ON_CHAR_P)
		return oSki->perform_action_npc(pet, oEnemy);
	else if (type == ON_XY_P)
		return oSki->perform_action_npc(pet, oEnemy, get_x(oEnemy), get_y(oEnemy), "");
	return 0;
}
//合成宠物
void fuse_pet(object pet1, object pet2, int iFlag)
{
	int i, size, count, rate, char_id, color;
	string *nAllSki, *nAllSki1, *nSki, cName;
	mapping mpSki, mpSki1, mpInfo, mpInfo1;
	object owner, obj, oSki, pet;

	owner = pet1->get_owner();
	if (pet2->get_owner() != owner)
		return;
	if (get_effect(pet1, EFFECT_MAGIC_CARD) || get_effect(pet2, EFFECT_MAGIC_CARD))
	{
		send_user(owner, "%c%s", '!', "Bảo thú đang biến thân, không thể hợp thành !");
		return;
	}
	if (pet1->get("show") || pet2->get("show"))
	{
		send_user(owner, "%c%s", '!', "Hãy thu hồi bảo thú lại rồi hãy hợp thành !");
		return;
	}
	if (pet1->get_save("no_fuse") || pet2->get_save("no_fuse"))
	{
		send_user(owner, "%c%s", '!', "Bảo thú không thể cùng với hợp thành !");
		return;
	}
	if (pet1->get("store") || pet2->get("store"))
	{
		send_user(owner, "%c%s", '!', "Đang mở quán bán rong, không thể hợp thành !");
		return;
	}
	if (gone_time(owner->get("fuse_pet")) < 2)
	{
		send_user(owner, "%c%s", '!', "Không nên thường xuyên hợp thành !");
		return;
	}
	if (!iFlag)
	{
		send_user(owner, "%c%c%w%s", ':', 3, 0,
				  sprintf("Bạn muốn hợp thành báo thú không ?\n" ESC "Xác nhận\npet %x# fuse_y %x#\n" ESC "Rời khỏi", getoid(pet1), getoid(pet2)));
		return;
	}
	owner->set("fuse_pet", time());
	if (pet1->get_blood() != 1 || pet2->get_blood() != 1)
	{
		send_user(owner, "%c%s", '!', "Chỉ có bảo thú Bảo Bảo mới có thể hợp thành !");
		return;
	}
	if (pet1->get_level() < 50 || pet2->get_level() < 50)
	{
		send_user(owner, "%c%s", '!', "Bảo thú đạt tới cấp 50 mới có thể hợp thành !");
		return;
	}
	mpInfo = "quest/pet"->get_beast_info(pet1->get_firstname());
	if (!mpInfo)
		return;
	mpInfo1 = "quest/pet"->get_beast_info(pet2->get_firstname());
	if (!mpInfo1)
		return;
	if ((mpInfo["level"] < mpInfo1["level"]) || (mpInfo["level"] == mpInfo1["level"] && random(2))) //等级段高的为主
	{
		cName = pet2->get_firstname();
		char_id = pet2->get_char_picid();
		color = pet2->get_head_color();
	}
	else
	{
		cName = pet1->get_firstname();
		char_id = pet1->get_char_picid();
		color = pet1->get_head_color();
	}
	pet = new (PET_NPC);
	if (!pet)
		return;
	generate_pet(pet, cName, 0, 1);
	pet->set_owner(owner);
	pet->set_char_picid(char_id);
	pet->set_portrait(char_id);
	pet->set_head_color(color);
	//技能分配
	mpSki = pet1->get_skill_dbase();
	mpSki1 = pet2->get_skill_dbase();
	pet->init_skill_dbase();
	if (random100() < 50)
	{
		nAllSki = ({});
		nAllSki1 = ({}); //主动技能
		nSki = keys(mpSki);
		for (i = 0, size = sizeof(nSki); i < size; i++)
		{
			oSki = load_object(SKILL->get_perform_file(to_int(nSki[i])));
			if (!oSki)
				continue;
			if (oSki->get_type() == 1 && member_array(nSki[i], nAllSki1) == -1)
				nAllSki1 += ({nSki[i]}); //加入主动技能
			else if (oSki->get_type() == 0 && member_array(nSki[i], nAllSki) == -1)
				nAllSki += ({nSki[i]});
		}
		nSki = keys(mpSki1);
		for (i = 0, size = sizeof(nSki); i < size; i++)
		{
			oSki = load_object(SKILL->get_perform_file(to_int(nSki[i])));
			if (!oSki)
				continue;
			if (oSki->get_type() == 1 && member_array(nSki[i], nAllSki1) == -1)
				nAllSki1 += ({nSki[i]}); //加入主动技能
			else if (oSki->get_type() == 0 && member_array(nSki[i], nAllSki) == -1)
				nAllSki += ({nSki[i]});
		}
		while (sizeof(nAllSki1) > 3)
			nAllSki1 -= ({nAllSki1[random(sizeof(nAllSki1))]});
		nAllSki += nAllSki1;
		size = sizeof(nAllSki);
		if (size)
		{
			for (i = 0; i < size; i++)
			{
				count = random(size);
				cName = nAllSki[i];
				nAllSki[i] = nAllSki[count];
				nAllSki[count] = cName;
			}
			rate = random100();
			if (rate < 5) //决定技能数量
				count = size > 6 ? 6 : size;
			else if (rate < 35)
				count = (size > 6 ? 6 : size) - 1;
			else
			{
				if (random(2))
					count = sizeof(mpSki);
				else
					count = sizeof(mpSki1);
			}
			if (count > size)
				count = size;
			for (i = 0; i < count; i++)
				pet->set_skill(to_int(nAllSki[i]), 1); //设定宠物技能
		}
	}
	if (!owner->add_beast(pet))
	{
		destruct(pet);
		return;
	}
	pet->save();
	//log_file("pet.txt",sprintf("%s %s(%d}  %s(%s,%s) + %s(%s,%s) hợp thành %s(%s)\n",short_time(), owner->get_name(),owner->get_number(), pet1->get_name(),pet1->get_firstname(),pet1->get_pet_id(),pet2->get_name(),pet2->get_firstname(),pet2->get_pet_id(),pet->get_firstname(),pet->get_pet_id(),));
	USER_BEAST_D->destruct_pet(owner, pet1);
	USER_BEAST_D->destruct_pet(owner, pet2);
	pet->send_info();
	send_user(owner, "%c%s", '!', "Bạn hợp thành nhận được bảo thú mới !");
	"/sys/sys/count"->add_pet("Hợp thành bảo thú", 1);
}
//合成物品
void fuse_item(object pet, object obj, int iFlag)
{
	int i, size, skill, skill1, rate, count;
	string cName, *nSki, *nSki1, name1, name2;
	mapping mpInfo, mpSki;
	object owner, oSki, oSki1, item;

	owner = pet->get_owner();
	if (get_effect(pet, EFFECT_MAGIC_CARD))
	{
		send_user(owner, "%c%s", '!', "Bảo thú đang biến thân, không thể hợp thành !");
		return;
	}
	if (pet->get("show"))
	{
		send_user(owner, "%c%s", '!', "Hãy thu hồi bảo thú lại rồi hãy hợp thành !");
		return;
	}
	if (pet->get("store"))
	{
		send_user(owner, "%c%s", '!', "Đang mở hàng rong, không thể hợp thành !");
		return;
	}
	if (owner->get_store(sprintf("%02d", get_d(obj))))
	{
		send_user(owner, "%c%s", '!', "Đang mở hàng rong, không thể hợp thành !");
		return;
	}
	owner = pet->get_owner();
	cName = pet->get_name();
	if (obj->get_name() == "Ngọc Linh Dịch" || obj->get_name() == "玉灵露") //合成玉灵液
	{
		if (pet->get_save("no_fuse"))
		{
			send_user(owner, "%c%s", '!', obj->get_name() + "Không thể sử dụng ở bảo thú trên người !");
			return;
		}
		if (iFlag == 0)
		{
			send_user(owner, "%c%c%w%s", ':', 3, 0,
					  sprintf("Sắp cho %d cấp bảo thú %s sử dụng Ngọc Linh Dịch, %s được luân hồi tái sinh, xác nhận không ?\n" ESC "Xác nhận\npet %x# fuse_y %x#\n" ESC "Rời khỏi", pet->get_level(), pet->get_name(), pet->get_name(), getoid(pet), getoid(obj)));
			return;
		}
		//清除所有的技能
		nSki = keys(pet->get_skill_dbase());
		for (i = 0, size = sizeof(nSki); i < size; i++)
		{
			pet->delete_skill(to_int(nSki[i]));
		}
		generate_pet(pet, pet->get_firstname(), 0, 1);
		pet->set_name(cName);
		pet->set_exp(0);
		pet->send_info();
		pet->save();
		obj->add_amount(-1);
		//log_file("pet.txt", sprintf("%s %s(%d) Tẩy bảo bảo %s(%s) %s\n", short_time(), owner->get_name(), owner->get_number(), pet->get_name(), pet->get_firstname(), pet->get_pet_id()));
		send_user(owner, "%c%s", '!', sprintf("Bảo thú %s của bạn đã được tái sinh !", cName));
		"/sys/sys/count"->add_pet("Tẩy bảo bảo", 1);
		return;
	}
	else if (obj->get_name() == "Tinh Nguyên Đơn") //合成精元丹
	{
		/*		if ( pet->get_save("no_fuse") )
		{
			send_user(owner,"%c%s",'!',"特殊的宠物无法学习任何新技能。");
			return ;	
		}*/
		if (iFlag == 0)
		{
			send_user(owner, "%c%c%w%s", ':', 3, 0,
					  sprintf("Sắp cho Bảo Thú %s uống Tinh Nguyên Đơn, tiếp tục hay không?\n" ESC "Chấp nhận\npet %x# fuse_yy %x#\n" ESC "Rời khỏi", pet->get_name(), getoid(pet), getoid(obj)));
			return;
		}
		skill = to_int(obj->get("special"));
		if (pet->get_skill(skill))
		{
			send_user(owner, "%c%s", '!', "Bảo thú của ngươi đã có kĩ năng này !");
			return;
		}
		if (!skill || !(oSki = load_object(SKILL->get_perform_file(skill))))
			return;

		name1 = oSki->get_name();
		mpSki = pet->get_skill_dbase();
		mpInfo = "quest/pet"->get_beast_info(pet->get_firstname());
		if (!mpInfo)
			return;
		size = sizeof(mpSki);
		if (size >= 3 && oSki->get_type() == 1) //主动技能是否达到3个?
		{
			nSki = keys(mpSki);
			nSki1 = ({});
			for (i = 0; i < size; i++)
			{
				skill1 = to_int(nSki[i]);
				oSki1 = load_object(SKILL->get_perform_file(skill1));
				if (!oSki1)
					continue;
				if (oSki1->get_type() == 1)
					nSki1 += ({skill1});
			}
			if ((count = sizeof(nSki1)) >= 3)
			{
				if (iFlag != 1)
				{
					send_user(owner, "%c%c%w%s", ':', 3, 0,
							  sprintf("Bảo thú " HIR + pet->get_name() + NOR " đã có năng lực công kích, năng lực mới sẽ thay thế năng lực cũ, có muốn hợp thành không ?\n" ESC "Xác nhận\npet %x# fuse_y %x#\n" ESC "Rời khỏi", getoid(pet), getoid(obj)));
					return;
				}
				else //取代已有的之一主动技能
				{
					skill1 = to_int(nSki1[random(count)]);
					pet->delete_skill(skill1);
					pet->set_skill(skill, 1);
					oSki1 = load_object(SKILL->get_perform_file(skill1));
					name2 = oSki1->get_name();
					tell_user(owner, "Bảo thú " + cName + " học kĩ năng mới: " + name1 + ", nhưng mất đi kĩ năng: " + name2);
					obj->remove_from_user();
					destruct(obj);
					//log_file("pet.txt", sprintf("%s %s(%d) Tinh Nguyên Đơn %s(%s,%s) học %s mất đi %s\n", short_time(), owner->get_name(), owner->get_number(), pet->get_name(), pet->get_firstname(), pet->get_pet_id(), name1, name2));
					pet->save();
					"/sys/sys/count"->add_pet("Hợp thành kĩ năng" + name1, 1);
					return;
				}
			}
		}
		size = sizeof(mpSki);
		rate = random(10000);
		if (!size || (size < mpInfo["max_ski"] && rate < (2000 / size)))
		{
			pet->set_skill(skill, 1);
			tell_user(owner, "Bảo thú " + cName + " học kĩ năng mới: " + name1);
			//log_file("pet.txt", sprintf("%s %s(%d) Tinh Nguyên Đơn %s(%s,%s) học %s \n", short_time(), owner->get_name(), owner->get_number(), pet->get_name(), pet->get_firstname(), pet->get_pet_id(), name1, ));
			"/sys/sys/count"->add_pet("Hợp thành kĩ năng" + name1, 1);
		}
		else
		{
			nSki = keys(mpSki);
			skill1 = to_int(nSki[random(sizeof(nSki))]);
			pet->delete_skill(skill1);
			pet->set_skill(skill, 1);
			oSki1 = load_object(SKILL->get_perform_file(skill1));
			name2 = oSki1->get_name();
			tell_user(owner, "Bảo thú " + cName + " học kĩ năng mới: " + name1 + ", nhưng mất đi kĩ năng: " + name2);
			//log_file("pet.txt", sprintf("%s %s(%d) Tinh Nguyên Đơn %s(%s,%s) học %s mất đi %s\n", short_time(), owner->get_name(), owner->get_number(), pet->get_name(), pet->get_firstname(), pet->get_pet_id(), name1, name2));
			"/sys/sys/count"->add_pet("Hợp thành kĩ năng" + name1, 1);
		}
		obj->remove_from_user();
		destruct(obj);
		pet->save();
		return;
	}
	else if (obj->get_name() == "Hấp Hồn Châu") //合成Hấp Hồn Châu
	{
		if (pet->get_save("no_fuse"))
		{
			send_user(owner, "%c%s", '!', "Bảo thú đặc thù không thể lấy kỹ năng ra");
			return;
		}
		if (!iFlag)
		{
			send_user(owner, "%c%c%w%s", ':', 3, 0,
					  sprintf("Ngươi phải lấy ra " HIR + pet->get_name() + NOR " kĩ năng, sau khi lấy ra, bảo thú của ngươi sẽ biến mất!\n" ESC "Xác nhận\npet %x# fuse_y %x#\n" ESC "Rời khỏi", getoid(pet), getoid(obj)));
			return;
		}
		if (pet->get_blood() != 1)
		{
			send_user(owner, "%c%s", '!', "Chỉ có bảo thú Bảo Bảo mới có thể học kĩ năng tinh luyện !");
			return;
		}
		if (pet->get_level() < 50)
		{
			send_user(owner, "%c%s", '!', "Bảo thú Bảo Bảo đạt tới cấp 50 mới có thể tinh luyện kĩ năng !");
			return;
		}
		mpSki = pet->get_skill_dbase();
		size = sizeof(mpSki);
		if (size < 2)
		{
			send_user(owner, "%c%s", '!', "Kĩ năng không thể ít hơn 2");
			return;
		}
		nSki = keys(mpSki);
		obj->remove_from_user();
		destruct(obj);
		//log_file("pet.txt", sprintf("%s %s(%d) Hấp Hồn Châu %s(%s) %s\n", short_time(), owner->get_name(), owner->get_number(), pet->get_name(), pet->get_firstname(), pet->get_pet_id()));
		USER_BEAST_D->destruct_pet(owner, pet);
		if (random100() < 20)
		{
			nSki1 = ({});
			if (random100() < 90) //提炼普通技能
				iFlag = 0;
			else //提炼高级技能
				iFlag = 1;
			for (i = 0, size = sizeof(nSki); i < size; i++)
			{
				skill = to_int(nSki[i]);
				if (!skill || !(oSki = load_object(SKILL->get_perform_file(skill))))
					continue;
				if (oSki->get_level() != iFlag)
					continue;
				nSki1 += ({skill});
			}
			size = sizeof(nSki1); //target
			if (size)
			{
				skill = to_int(nSki1[random(size)]);
				item = new ("item/44/4488");
				if (!item)
					return;
				item->set("special", sprintf("%d", skill));
				iFlag = item->move(owner, -1);
				if (!iFlag)
				{
					destruct(item);
				}
				else
				{
					item->add_to_user(iFlag);
					name1 = item->get_name();
				}
			}
		}
		if (name1)
		{
			tell_user(owner, "Chúc mừng bạn nhận được " HIY + name1 + NOR "!");
			send_user(owner, "%c%s", '!', "Chúc mừng bạn nhận được " HIY + name1 + NOR "!");
			//log_file("pet.txt", sprintf("%s %s(%d) Hấp Hồn Châu 得到 \n", short_time(), owner->get_name(), owner->get_number(), name1));
			"/sys/sys/count"->add_pet("Lấy kỹ năng ra" + name1, 1);
		}
		else
			tell_user(owner, "Không có kết quả gì! ");
		return;
	}
}
//合成
void fuse(object pet, string arg, int iFlag)
{
	object obj;
	if ((obj = find_any_object(arg)) && obj->is_pet_item())
		fuse_item(pet, obj, iFlag);
	else if ((obj = find_char(arg)) && obj->is_pet())
		fuse_pet(pet, obj, iFlag);
}
//判断是否可以携带
int can_carry(object who, object pet)
{
	string cName;
	mapping mpInfo;
	cName = pet->get_firstname();
	if (!stringp(cName))
		cName = pet->get_name();
	if (!stringp(cName))
		return 0;
	mpInfo = "quest/pet"->get_beast_info(cName);
	if (!mpInfo)
		return 0;
	//ignore_level 忽视携带等级
	if (!pet->get_save("ignore_level") && who->get_level() < mpInfo["level"])
		return 0;

	return 1;
}

//取宠物ID
string get_pet_id(int ownerId)
{
	int i;
	i = time();
	if (PetTime == i)
		PetTime++;
	else
		PetTime = i;
	return sprintf("%d_%d", ownerId, PetTime);
}