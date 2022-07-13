#include <ansi.h>
#include <city.h>
#include <npc.h>
#include <equip.h>
#include <skill.h>

inherit COMRADE;

// 函数：构造处理
void create()
{
        set_name("佣兵");
	set_char_picid(8012);
        set_max_hp(10000);  set_max_mp(0);
        set_ap(700);  set_dp(600);  
        set_cp(  0);  set_pp(600);  
        set_sp(0);

        set_walk_speed(3);  set_attack_speed(10);
        set_max_seek(4);

        setup();

        set_char_type(FIGHTER_TYPE);    // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：掉宝奖励
void win_bonus( object who ) { __FILE__ ->win_bonus2( this_object(), who ); }

// 函数：掉宝奖励(在线更新)
void win_bonus2( object me, object who )
{
	int random, number;
	object item;
	string id, owner;
	string name, result, leader;
	object orgnpc, *team;
	int size, i, level2, exp2, level, exp;
	int p, x, y, z;
	int drop = 3;
	if (who->is_npc())
	{
		who = who->get_owner();
	}
	if (!who) return;
	if (who->is_npc()) return;	

        name = who->get_org_name();
        if (name=="") return;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );	
	if (!objectp(orgnpc)) return;        
	orgnpc->add_wood(drop);
	result = sprintf("你消灭了%s，为帮派获得了%d个木材。", me->get_name(), drop);
	tell_user( who, ECHO + result );	
	
	number = who->get_number();
	orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number)+2);
	result = sprintf("你消灭了%s，得到了%d点帮派贡献。", me->get_name(), 2);
	tell_user( who, ECHO + result );	
	
        if( (leader=who->get_leader()) && arrayp( team = who->get_team() ) && sizeof(team) > 1 )
        {
                team = me->correct_bonus_team(team);
                size = sizeof(team);
        }
        else    size = 1;
        level = who->get_level();
        exp = NPC_ENERGY_D->get_exp_bonus(level);    // 查表取值
         
        if( size > 1 )    // 多人
        {
                for( i = 0; i < size; i ++ ) if( team[i] )
                {
                        level2 = level - team[i]->get_level();
                        exp2 = exp*(10+size-1)/10;
                        exp2 = me->correct_exp_bonus(level, level2, exp2) * team[i]->get_online_rate() / 100;  
                        if (exp2<1) exp2 = 1;
                        team[i]->add_exp(exp2);
			NPC_SLAVE_D->add_slave_exp(team[i], exp2);
			NPC_PET_D->fight_bonus(team[i],me,size,0,0);
                        team[i]->add_log("&battle", exp2);
			team[i]->add_log("#battle", 1);                        	
                }
        }
        else    // 单人
        {
                level2 = level - who->get_level();
                exp2 = me->correct_exp_bonus(level, level2, exp) * who->get_online_rate() / 100;  
                who->add_exp(exp2);
                NPC_SLAVE_D->add_slave_exp(who, exp2);
		NPC_PET_D->fight_bonus(who,me,1,0,0);

                who->add_log("&battle", exp2);                
                who->add_log("#battle", 1);
        }
	
	
}
