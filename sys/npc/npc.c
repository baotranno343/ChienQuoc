
#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <cmd.h>
#include <skill.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <time.h>
#include <public.h>
inherit SAVE_F;
int iStarttw1, iFinishtw1;
int iStart, iFinish, iTest, iFinish1;
void team_friend_degree(object *team);

// 函数:生成二进制码
void SAVE_BINARY() {}
string get_save_file() { return "data/drop_qiguoling" SAVE_EXTENSION; }
void create()
{
	restore();
	if (MAIN_D->get_host_type() == 2) //台湾
	{
		iStarttw1 = mktime(2000, 1, 1, 0, 0, 0);
		iFinishtw1 = mktime(2007, 12, 1, 0, 0, 0);
	}
}
// 函数:修正奖励队伍
object *correct_bonus_team(object me, object *team)
{
	object *team2;
	int i, size;

	team2 = ({});
	if (!team)
		return team2;
	size = sizeof(team);
	if (!size)
		return team2;

	for (i = 0; i < size; i++)
		if (team[i] && !team[i]->is_die() && distance_between(me, team[i]) <= 30) // inside_screen_2( me, team[i] )
			team2 += ({team[i]});

	return team2;
}

// 函数:修正奖励队伍(按距离)
object *correct_bonus_team1(object me, object *team, int iDistance)
{
	object *team2;
	int i, size;

	team2 = ({});
	if (!team)
		return team2;
	size = sizeof(team);
	if (!size)
		return team2;

	for (i = 0; i < size; i++)
		if (team[i] && !team[i]->is_die() && distance_between(me, team[i]) <= iDistance)
			team2 += ({team[i]});

	return team2;
}

// 函数:修正经验奖励
int correct_exp_bonus(int level, int level2, int exp) // level: 怪, level2 : 怪 - 玩家等级
{
	int ret;
	level2 = abs(level2);
	if (level2 <= 15)
		return exp;
	ret = range_value(100 - (level2 - 15) * 10, 0, 100) * exp / 100;
	if (ret < 1)
		ret = 1;
	return ret;
}

// 函数:组队修正经验奖励
int correct_exp_bonus2(int level, int level2, int exp) // level: 怪, level2 : 怪 - 玩家等级
{
	int ret;
	level2 = abs(level2);
	if (level2 <= 30)
		return exp;
	ret = range_value(100 - (level2 - 30) * 5, 0, 100) * exp / 100;
	if (ret < 1)
		ret = 1;
	return ret;
}

// 函数:修正掉宝率
int correct_drop_rate(int level) // level : 怪 - 玩家等级
{
	if (level > 0) // 怪 > 玩家
	{
		return 100;
		//                if( level <= 5 ) return 100;
		//                return range_value( 100 - (level - 5) * 10, 10, 100 );
	}
	else // 怪 < 玩家
	{
		level = abs(level);
		if (level <= 140)
			return 100;
		return range_value(100 - (level - 140) * 10, 10, 100);
	}
}

// 函数:boss掉宝率
int correct_drop_rate_2(int level) // level : 怪 - 玩家等级
{
	if (level > 0) // 怪 > 玩家
	{
		return 100;
	}
	else // 怪 < 玩家
	{
		level = abs(level);
		if (level <= 140)
			return 100;
		return range_value(100 - (level - 140) * 10, 10, 100);
	}
}

// 函数:死亡奖励
// rớt item khi chết
void win_bonus(object me, object who)
{
	object owner, *team, oLeader, item, map, chuQuanDoan;
	int level, level2, exp, exp2, pot, alllevel, iExtraExpFlag, iExtraExp, level3, legend_level;
	int i, size, status, time, flag, rate;
	string leader;
	int iTime, iTimeFlag;
	mixed mxTime;
	int hulu_exp, iVip, iVipExp, ishuipingExp;
	object leader2;
	string file, owner2, id;
	int p;
	int z, x, y, poti;
	string cTmp;

	if (me->get_char_type() != FIGHTER_TYPE && me->get_char_type() != FIGHTER_TYPE_2)
		return;

	if (!me->can_be_fighted(who))
		return;

	if (owner = who->get_owner())
		who = owner;

	if (who->is_npc() && !who->is_quanDoan())
		return;

	if (!me->is_have_been_slave())
	{
		if (me->get_char_type() == FIGHTER_TYPE)
		{
			rate = correct_drop_rate_2(me->get_level() - who->get_level()) * who->get_online_rate() / 100;
			if (random(100000) < 10 * rate / 100)
				"/quest/box"->drop_box(who);
			iTime = time();
			mxTime = localtime(iTime);
			if (iTime < iFinish1 || iFinish1 == 0)
			{
				if ((mxTime[TIME_WDAY] == 5 && mxTime[TIME_HOUR] >= 18) || mxTime[TIME_WDAY] == 6 || mxTime[TIME_WDAY] == 0 || iTest == 1)
				{
					if (random(1000000) < 5000 * rate / 100)
						"/quest/ball"->drop_black_ball(who);
					if (random(1000000) < 5000 * rate / 100)
						"/quest/ball"->drop_blue_ball(who);
					if (random(1000000) < 50 * rate / 100)
						"/quest/ball"->drop_red_ball(who);
					if (random(1000000) < 5 * rate / 100)
						"/quest/ball"->drop_flower_ball(who);
				}
			}
		}
		if (me->get_char_type() == FIGHTER_TYPE_2)
		{
			rate = correct_drop_rate_2(me->get_level() - who->get_level()) * who->get_online_rate() / 100;
			iTime = time();
			mxTime = localtime(iTime);
			if (iTime < iFinish1 || iFinish1 == 0)
			{
				if ((mxTime[TIME_WDAY] == 5 && mxTime[TIME_HOUR] >= 18) || mxTime[TIME_WDAY] == 6 || mxTime[TIME_WDAY] == 0 || iTest == 1)
				{
					if (me->is_legend_npc())
					{
						if (random(1000000) < 5000 * rate / 100)
							"/quest/ball"->drop_black_ball(who);
						if (random(1000000) < 5000 * rate / 100)
							"/quest/ball"->drop_blue_ball(who);
						if (random(1000000) < 50 * rate / 100)
							"/quest/ball"->drop_red_ball(who);
						if (random(1000000) < 5 * rate / 100)
							"/quest/ball"->drop_flower_ball(who);
					}
					else
					{
						if (random(1000000) < 50000 * rate / 100)
							"/quest/ball"->drop_red_ball(who);
						if (random(1000000) < 3000 * rate / 100)
							"/quest/ball"->drop_flower_ball(who);
					}
				}
			}
		}
		me->drop_items(who); // 前提:末曾被魅惑
		"/quest/help"->send_help_tips(who, 14);
		"/quest/help"->send_help_tips(who, 35);
	}
	// 掉七国令

	if (iStart == 1 || (time() < iFinish && time() > iStart && iStart != 0 && iStart != 2))
	{
		z = get_z(me);
		x = get_x(me);
		y = get_y(me);
		id = who->get_leader();
		if (!id)
			owner2 = who->get_id();
		else
		{
			if (leader2 = find_player(id))
			{
				owner2 = leader2->get_id();
			}
			else
				owner2 = who->get_id();
		}
		rate = me->correct_drop_rate(me->get_level() - who->get_level()) * who->get_online_rate() / 100;
		p = random(300000);
		if (me->get_level() >= 20 && p < 1000 * rate / 100)
		{
			file = "/item/04/7777";
			if (load_object(file) && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
			{
				item = new (file);
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner2);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}

	// ---------- 最后一击，爆落装备 ///// 持续攻击，分配经验 ----------

	if (!objectp(who = me->get_enemy_4()))
		return;

	if (!me->can_be_fighted(who))
		return;

	if (owner = who->get_owner())
		who = owner;

	if (who->is_npc() && !who->is_quanDoan())
		return;

	level = me->get_level();
	level3 = level; // Nhiệm vụ thu yêu判断

	if (who->is_quanDoan())
	{
		//	CHAT_D->sys_channel(0, sprintf(" %s ", who->get_idChuQuanDoan()));
		if (chuQuanDoan = find_player(sprintf("%d", who->get_idChuQuanDoan())))
		{
			chuQuanDoan->add_cash(10);
		}
		else
		{

			"/map/city/08"->add_2(sprintf("quanDoan.%d.tien", who->get_idChuQuanDoan()), 10);
		}
	}
	if (chuQuanDoan)
		who = chuQuanDoan;
	// 战斗类 NPC 分配经验

	if ((leader = who->get_leader()) && arrayp(team = who->get_team()) && sizeof(team) > 1)
	{
		team = me->correct_bonus_team(team);
		size = sizeof(team);
		oLeader = find_char(leader);
		if (oLeader)
		{
			if (time() < oLeader->get_extra_exp_time()) //战国号角
				iExtraExpFlag = 1;
		}
		for (i = 0; i < size; i++)
		{
			if (team[i]->get_vip())
			{
				iVip = 1;
				break;
			}
		}
	}
	else
	{
		size = 1;
		if (who->get_vip())
			iVip = 1;
	}
	exp = NPC_ENERGY_D->get_exp_bonus(level); // 查表取值
	map = get_map_object(get_z(me));
	if (map && map->is_pvp()) // PVP
		exp = exp * 3 / 2;

	if (me->get("shiyong"))
	{
		exp = exp * 3;
	}
	// if (mxTime[TIME_HOUR] % 2 == 0)
	// {
	// 	exp = exp * 2;
	// }
	if ((mxTime[TIME_WDAY] == 6 && mxTime[TIME_HOUR] >= 0) || (mxTime[TIME_WDAY] == 0 && mxTime[TIME_HOUR] <= 23))
	{
		exp = exp * 2; // edit by Ben
	}
	// exp = exp * 2;
	/*	if ( mxTime[TIME_WDAY] == 0 && mxTime[TIME_HOUR] <= 23 )
	{
		exp = exp * 2; // edit by Ben
	}*/
	//--------------------------------------------------------------------edit by landy
	if (me->get("copy_map_add_exp"))
		exp = exp * 3 / 2; //副本怪增加1.5倍经验.
						   //---------------------------------------------------------------------------------
	if (me->is_copy_npc())
		exp = exp * 3 / 2;

	if (who->get_save_2("chuyensinh.score") && who->get_level() < 120)
	{
		exp = exp / 2;
	}
	status = who->get_save("tips_status");
	if ((status & 8) == 0)
	{
		QUEST_TIPS->send_tips(who, "3");
		status |= 8;
		who->set_save("tips_status", status);
	}
	//台湾的活动
	iTime = time();
	if (iTime > iStarttw1 && iTime < iFinishtw1)
	{
		mxTime = localtime(iTime);
		if (mxTime[TIME_HOUR] >= 17 && mxTime[TIME_HOUR] <= 21)
		{
			iTimeFlag = 1;
			iExtraExpFlag = 0;
		}
	}
	if (size > 1) // 多人
	{
		poti = random(size);
		//获取友好度
		team_friend_degree(team);
		for (i = 0; i < size; i++)
			if (team[i])
			{
				if (team[i]->get_group_id())
				{
					send_user(team[i], "%c%s", ';', "Bởi vì ngươi kết đồng đội với nhóm khác nên không thể đạt được kinh nghiệm cùng tiềm năng!");
					continue;
				}
				level2 = level - team[i]->get_level();
				exp2 = exp * (10 + size - 1) / 10;
				if (me->get("no_correct_exp"))
					exp2 = exp2 * team[i]->get_online_rate() / 100;
				else
					exp2 = me->correct_exp_bonus(level, level2, exp2) * team[i]->get_online_rate() / 100;
				if (exp2 < 1)
					exp2 = 1;
				if (iVip)
					iVipExp = exp2 / 10 * iVip;
				ishuipingExp = 0;
				if (item = team[i]->get("shuiping"))
				{
					if (time() < item->get("shuiping.time"))
					{
						ishuipingExp = exp2 * 20 / 100;
					}
				}
				if ((cTmp = team[i]->get_title_code()) == "Z888" || cTmp == "Z889") //无双城
					ishuipingExp += exp2 * 20 / 100;
				time = time();

				if (iExtraExpFlag)
					iExtraExp = exp2 / 5;
				// 加上双倍时间的影响
				time = gone_time(team[i]->get_login_time());
				if (iTimeFlag)
				{
					exp2 *= 2;
					flag = 1;
					iExtraExpFlag = 0;
					iExtraExp = 0;
				}
				else if (time + team[i]->get_game_time() < team[i]->get_double_time())
				{
					exp2 *= 2;
					flag = 1;
				}
				else if (time + team[i]->get_game_time() < team[i]->get_extra_double_time())
				{
					exp2 *= 2;
					flag = 1;
				}
				else
					flag = 0;
				//                        if (team[i]->get("soldier") || team[i]->get("zombie")) exp2 = exp2 * 88/100;
				if (mapp(team[i]->get_2("jishihulu")) && "npc/std/0003"->add_hulu_exp(team[i], exp2 + iExtraExp)) //济世葫芦增加经验
				{
					if (team[i]->get("wg_bl_15"))
						team[i]->add_exp((exp2 + ishuipingExp + iExtraExp + exp / 10 + iVipExp) * 3 / 2);
					else
						team[i]->add_exp(exp2 + ishuipingExp + iExtraExp + exp / 10 + iVipExp);
				}
				else
				{
					if (team[i]->get("wg_bl_15"))
						team[i]->add_exp((exp2 + iExtraExp + ishuipingExp + iVipExp) * 3 / 2);
					else
						team[i]->add_exp(exp2 + iExtraExp + ishuipingExp + iVipExp);
				}
				NPC_SLAVE_D->add_slave_exp(team[i], (exp2 + iExtraExp) * team[i]->get_online_rate() / 100);
				NPC_PET_D->fight_bonus(team[i], me, size, flag, iExtraExpFlag);
				if (i == poti)
				{
					if (level2 > -10)
						pot = (exp2 + iExtraExp) / 500 + 1;
					if (me->get("shiyong"))
						pot = pot * 3;
					team[i]->add_potential(pot); // 低于自身 10 级的怪，无潜能

					team[i]->add_log("&npc", exp2 + iExtraExp);
					team[i]->add_log("*npc", pot);
					team[i]->add_log("#npc", 1);
					/*
								if( exp2 )
								{
										if( pot ) write_user( team[i], ECHO "您击毙%s，%s经验 %+d, 潜能 %+d.", me->get_name(), flag ? "双倍":"", exp2, pot );
										else write_user( team[i], ECHO "您击毙%s，%s经验 %+d.", me->get_name(), flag ? "双倍":"", exp2 );
								}
								else    if( pot ) write_user( team[i], ECHO "您击毙%s，潜能 %+d.", me->get_name(), pot );
*/
				}
				else
				{
					//                        	if( level2 > -10 ) pot = 1;  team[i]->add_potential(pot);    // 低于自身 10 级的怪，无潜能
					team[i]->add_log("&npc", exp2);
					//                                team[i]->add_log("*npc", pot);
					team[i]->add_log("#npc", 1);

					//                                if( exp2 ) write_user( team[i], ECHO "您参与击毙%s，%s经验 %+d.", me->get_name(), flag ? "双倍":"", exp2 );
				}

				me->check_legend_task(team[i]); // 任务判断处理
				// 检查封妖任务
				if (team[i]->get_save_2("refine.status") == 1 && random100() < team[i]->get_online_rate())
				{
					level2 = team[i]->get_save_2("refine.level");
					if (level3 >= team[i]->get_save_2("refine.level1") && level3 <= team[i]->get_save_2("refine.level2"))
					{
						if (team[i]->get_save_2("refine.count") < 450)
						{
							team[i]->add_save_2("refine.count", 1);
							if (team[i]->get_save_2("refine.count") >= 450)
								send_user(team[i], "%c%c%c%w%w%s", 0x51, 1, 2, TID_REFINE, 1, "Nhiệm vụ Hồ Lô Thu Yêu(Hoàn thành)");
							send_user(team[i], "%c%c%c%w%w%s", 0x51, 1, 3, TID_REFINE, 1, "");
							item = present("收妖壶", team[i], 1, MAX_CARRY * 4);
							if (item)
								send_user(team[i], "%c%d%s", 0x31, getoid(item), "");
							if (team[i]->get_save_2("refine.count") < 450)
								send_user(team[i], "%c%s", '!', sprintf("Nhiệm vụ thu yêu:%d/450", team[i]->get_save_2("refine.count")));
							else
								send_user(team[i], "%c%s", '!', "Nhiệm vụ hồ lô thu yêu hoàn thành");
						}
					}
				}
				// Can Tương
				if (team[i]->get_save_2("cantuong.status") == 1 /*&& random100()<team[i]->get_online_rate()*/)
				{
					level2 = team[i]->get_save_2("cantuong.level");
					if (level3 >= team[i]->get_save_2("cantuong.level1") && level3 <= team[i]->get_save_2("cantuong.level2"))
					{
						if (team[i]->get_save_2("cantuong.count") < 10000)
						{
							team[i]->add_save_2("cantuong.count", 1);
							if (team[i]->get_save_2("cantuong.count") >= 10000 &&
								team[i]->get_save_2("cantuong.hv") >= 1 &&
								team[i]->get_save_2("cantuong.agbd") >= 1 &&
								team[i]->get_save_2("cantuong.uvdtq") >= 1 &&
								team[i]->get_save_2("cantuong.ktl") >= 1)
								send_user(team[i], "%c%c%c%w%w%s", 0x51, 1, 2, TID_CANTUONG, 1, "Tìm kiếm Thần Binh Phổ(Hoàn thành)");
						}
					}
				}
				//大胖任务
				if (team[i]->get_save_2("dapang.name") == me->get_name() && gone_time(team[i]->get_save_2("dapang.time")) < 1800 && team[i]->get_save_2("dapang.count") < team[i]->get_save_2("dapang.total") && random100() < team[i]->get_online_rate())
				{
					if (team[i]->add_save_2("dapang.count", 1) >= team[i]->get_save_2("dapang.total"))
						send_user(team[i], "%c%s", ';', "大胖任务完成");
					send_user(team[i], "%c%s", '!', sprintf(HIY "%s %d/%d", team[i]->get_save_2("dapang.name"), team[i]->get_save_2("dapang.count"), team[i]->get_save_2("dapang.total")));
					send_user(team[i], "%c%c%c%w%w%s", 0x51, 1, 2, TID_DAPANG, 1, "");
					send_user(team[i], "%c%c%c%w%s", 0x51, 1, 1, TID_DAPANG, "大胖任务");
					send_user(team[i], "%c%c%c%w%w%s", 0x51, 1, 2, TID_DAPANG, 1, "杀20只" + team[i]->get_save_2("dapang.name"));
				}
				//                        //天道酬勤
				//                        if ( team[i]->get_save_2("51tiandao.accept")
				//                        	&& team[i]->get_save_2("51tiandao.amount") < 100
				//                        	&& me->get_level() <= (team[i]->get_level() + 5)
				//                        	&& me->get_level() >= team[i]->get_level() )
				//                        {
				//                        	if ( team[i]->add_save_2("51tiandao.amount",1) >= 100 )
				//					send_user( team[i], "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,2,"天道酬勤(完成)" );
				//                        }
				CHAIN_D->legend_item(team[i], me); //打传说
			}
	}
	else // 单人
	{
		if (who->get_group_id())
		{
			send_user(who, "%c%s", ';', "Bởi vì ngươi kết đồng đội với nhóm khác nên không thể đạt được kinh nghiệm cùng tiềm năng!");
			return;
		}
		level2 = level - who->get_level();
		if (me->get("no_correct_exp"))
			exp2 = exp * who->get_online_rate() / 100;
		else
			exp2 = me->correct_exp_bonus(level, level2, exp) * who->get_online_rate() / 100;
		exp2 = exp2 * 12 / 10; // 增加单人的打怪奖励
		if (exp2 < 1)
			exp2 = 1;
		if (iVip)
			iVipExp = exp2 / 10;
		ishuipingExp = 0;
		if (item = who->get("shuiping"))
		{
			if (time() < item->get("shuiping.time"))
			{
				ishuipingExp = exp2 * 20 / 100;
			}
		}
		if ((cTmp = who->get_title_code()) == "Z888" || cTmp == "Z889") //无双城
			ishuipingExp += exp2 * 20 / 100;
		// 加上双倍时间的影响
		time = gone_time(who->get_login_time());
		if (iTimeFlag)
		{
			exp2 *= 2;
			flag = 1;
		}
		else if (time + who->get_game_time() < who->get_double_time())
		{
			exp2 *= 2;
			flag = 1;
		}
		else if (time + who->get_game_time() < who->get_extra_double_time())
		{
			exp2 *= 2;
			flag = 1;
		}
		else
			flag = 0;
		//		if (who->get("soldier") || who->get("zombie")) exp2 = exp2 * 88/100;
		if (mapp(who->get_2("jishihulu")) && "npc/std/0003"->add_hulu_exp(who, exp2)) //济世葫芦增加经验
		{
			if (who->get("wg_bl_15"))
				who->add_exp((exp2 + ishuipingExp + exp / 10 + iVipExp) * 3 / 2);
			else
				who->add_exp(exp2 + ishuipingExp + exp / 10 + iVipExp);
		}
		else
		{
			if (who->get("wg_bl_15"))
				who->add_exp((exp2 + ishuipingExp + iVipExp) * 3 / 2);
			else
				who->add_exp(exp2 + ishuipingExp + iVipExp);
		}
		NPC_SLAVE_D->add_slave_exp(who, exp2 * who->get_online_rate() / 100);
		NPC_PET_D->fight_bonus(who, me, 1, flag, 0);
		if (level2 > -10)
			pot = exp2 / 500 + 1;
		who->add_potential(pot); // 低于自身 10 级的怪，无潜能
		if (me->get("shiyong"))
		{
			pot = pot * 3;
			who->add_potential(pot);
		}
		who->add_log("&npc", exp2);
		who->add_log("*npc", pot);
		who->add_log("#npc", 1);
		/*
				if( exp2 )
				{
						if( pot ) write_user( who, ECHO "您击毙%s，%s经验 %+d, 潜能 %+d.", me->get_name(), flag ? "双倍":"", exp2, pot );
						else write_user( who, ECHO "您击毙%s，%s经验 %+d.", me->get_name(), flag ? "双倍":"", exp2 );
				}
				else    if( pot ) write_user( who, ECHO "您击毙%s，潜能 %+d.", me->get_name(), pot );
*/
		me->check_legend_task(who); // 任务判断处理
		if (who->get_save_2("refine.status") == 1 && random100() < who->get_online_rate())
		{
			level2 = who->get_save_2("refine.level");
			if (level3 >= who->get_save_2("refine.level1") && level3 <= who->get_save_2("refine.level2"))
			{
				if (who->get_save_2("refine.count") < 450)
				{
					who->add_save_2("refine.count", 1);
					if (who->get_save_2("refine.count") >= 450)
						send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_REFINE, 1, "Nhiệm vụ Hồ Lô Thu Yêu(Hoàn thành)");
					send_user(who, "%c%c%c%w%w%s", 0x51, 1, 3, TID_REFINE, 1, "");
					item = present("收妖壶", who, 1, MAX_CARRY * 4);
					if (item)
						send_user(who, "%c%d%s", 0x31, getoid(item), "");
					if (who->get_save_2("refine.count") < 450)
						send_user(who, "%c%s", '!', sprintf("Nhiệm vụ thu yêu:%d/450", who->get_save_2("refine.count")));
					else
						send_user(who, "%c%s", '!', "Nhiệm vụ hồ lô thu yêu hoàn thành");
				}
			}
		}
		// Can Tương
		if (who->get_save_2("cantuong.status") == 1 /*&& random100()<who->get_online_rate()*/)
		{
			level2 = who->get_save_2("cantuong.level");
			if (level3 >= who->get_save_2("cantuong.level1") && level3 <= who->get_save_2("cantuong.level2"))
			{
				if (who->get_save_2("cantuong.count") < 10000)
				{
					who->add_save_2("cantuong.count", 1);
					if (who->get_save_2("cantuong.count") >= 10000 &&
						who->get_save_2("cantuong.hv") >= 1 &&
						who->get_save_2("cantuong.agbd") >= 1 &&
						who->get_save_2("cantuong.uvdtq") >= 1 &&
						who->get_save_2("cantuong.ktl") >= 1)
						send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CANTUONG, 1, "Tìm kiếm Thần Binh Phổ(Hoàn thành)");
					//大胖任务
				}
			}
		}
		if (who->get_save_2("dapang.name") == me->get_name() && gone_time(who->get_save_2("dapang.time")) < 1800 && who->get_save_2("dapang.count") < who->get_save_2("dapang.total") && random100() < who->get_online_rate())
		{
			if (who->add_save_2("dapang.count", 1) >= who->get_save_2("dapang.total"))
				send_user(who, "%c%s", ';', "大胖任务完成");
			send_user(who, "%c%s", '!', sprintf(HIY "%s %d/%d", who->get_save_2("dapang.name"), who->get_save_2("dapang.count"), who->get_save_2("dapang.total")));
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DAPANG, 1, "");
			send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_DAPANG, "大胖任务");
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DAPANG, 1, "杀20只" + who->get_save_2("dapang.name") + "(完成)");
		}
		//                //天道酬勤
		//                if ( who->get_save_2("51tiandao.accept")
		//                	&& who->get_save_2("51tiandao.amount") < 100
		//                	&& me->get_level() <= (who->get_level() + 5)
		//                	&& me->get_level() >= who->get_level() )
		//                {
		//                	if ( who->add_save_2("51tiandao.amount",1) >= 100 )
		//				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,2,"天道酬勤(完成)" );
		//                }
		CHAIN_D->legend_item(who, me); //打传说
	}
}
//增加济世葫芦经验
int add_hulu_exp(object who, int exp)
{
	int exp1;
	object item;

	exp1 = "npc/std/0003"->add_hulu_exp(who, exp);
	if (objectp(item = who->get_2("jishihulu.item")))
	{
	}
	return exp1;
}

void set_prepare()
{
	iStart = 0;
	save();
}

void set_open()
{
	iStart = 1;
	save();
}

int set_open_time(object who, string arg)
{
	int date1, date2, year1, year2, mon1, mon2, day1, day2;
	if (sscanf(arg, "%d-%d", date1, date2) != 2)
	{
		send_user(who, "%c%s", '!', "错误的格式!");
		return 0;
	}
	year1 = date1 / 10000;
	mon1 = date1 % 10000 / 100;
	day1 = date1 % 10000 % 100;
	year2 = date2 / 10000;
	mon2 = date2 % 10000 / 100;
	day2 = date2 % 10000 % 100;
	if (!year1 || !mon1 || !day1 || !year2 || !mon2 || !day2)
	{
		send_user(who, "%c%s", '!', "错误的时间!");
		return 0;
	}
	iStart = mktime(year1, mon1, day1, 0, 0, 0);
	iFinish = mktime(year2, mon2, day2, 0, 0, 0);
	if (iStart > iFinish)
	{
		send_user(who, "%c%s", '!', "错误的时间!!");
		return 0;
	}
	save();
	return 1;
}

void set_close()
{
	iStart = 2;
	iFinish = time();
	save();
}

void test_start()
{
	iTest = 1;
}

void test_finish()
{
	iTest = 0;
}

//世界BOSS掉落四色球
void drop_ball(object me, object who)
{
	int iHour, rate1;
	iHour = time();
	rate1 = correct_drop_rate_2(me->get_level() - who->get_level()) * who->get_online_rate() / 100;
	if (iHour < iFinish1 || iFinish1 == 0)
	{
		if (random(1000000) < 300000 * rate1 / 100)
			"/quest/ball"->drop_red_ball(who);
		if (random(1000000) < 40000 * rate1 / 100)
			"/quest/ball"->drop_flower_ball(who);
	}
}

//设置四色球活动关闭时间
int set_ball_close_time(object who, string arg)
{
	int year, mon, day, hour, min;
	string cTmp2;
	if (sscanf(arg, "%s", cTmp2) != 1)
	{
		send_user(who, "%c%s", '!', "错误的格式!");
		return 0;
	}
	year = to_int(cTmp2[0..3]);
	mon = to_int(cTmp2[4..5]);
	day = to_int(cTmp2[6..7]);
	hour = to_int(cTmp2[8..9]);
	min = to_int(cTmp2[10..11]);
	iFinish1 = mktime(year, mon, day, hour, min, 0); //结束时间

	if (!iFinish1)
	{
		send_user(who, "%c%s", '!', "错误的时间!");
		return 0;
	}
	if (iFinish1 < time())
	{
		send_user(who, "%c%s", '!', "错误的时间!!");
		return 0;
	}
	tell_user(who, "四色球活动关闭时间:%s!", arg);
	send_user(who, "%c%s", '!', "成功设置四色球活动关闭时间!");
	save();
	return 1;
}

//取消四色球活动关闭时间
int set_ball_cancel(object who)
{
	iFinish1 = 0;
	send_user(who, "%c%s", '!', "四色球活动关闭时间取消!");
	save();
	return 1;
}
//队伍获得友好度
void team_friend_degree(object *team)
{
	int i, j, size, *nTmp, max;
	object who, me, oTmp;
	mapping mpTmp = ([]);
	mixed *mxTime;

	for (i = 0, size = sizeof(team); i < size; i++)
	{
		me = team[i];
		if (!me)
			continue;
		for (j = i + 1; j < size; j++)
		{
			who = team[j];
			if (!who)
				continue;
			if (!stringp(who->get_friend_name(me->get_number())) || !stringp(me->get_friend_name(who->get_number()))) //双方不是互为好友
				continue;
			mpTmp[i * 100 + j] = 1; //双方是好友
		}
	}
	nTmp = keys(mpTmp);
	for (i = 0, size = sizeof(nTmp); i < size; i++)
	{
		j = nTmp[i];
		who = team[j / 100];
		me = team[j % 100];
		max = me->get_friend_max_degree(who->get_number());
		me->inc_friend_sub_degree(who->get_number(), 1, 0);
		who->inc_friend_sub_degree(me->get_number(), 1, 0);
		if (max < me->get_friend_max_degree(who->get_number()))
		{
			if (me->get_number() > who->get_number())
			{
				oTmp = who;
				who = me;
				me = oTmp;
			}
			mxTime = localtime(time());
			// log_file(sprintf("friend_%d%02d%02d.txt", mxTime[TIME_YEAR], mxTime[TIME_MON] + 1, mxTime[TIME_MDAY]),
			//	 sprintf("%s %s %d %s and %s %d %s max %d\n", short_time(), me->get_id(), me->get_number(), me->get_name(), who->get_id(), who->get_number(), who->get_name(), me->get_friend_max_degree(who->get_number())));
		}
	}
}
