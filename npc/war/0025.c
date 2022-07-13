#include <ansi.h>
#include <city.h>
#include <npc.h>
#include <equip.h>
#include <skill.h>

inherit COMRADE;

int is_caster() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 0053; }

// 函数：构造处理
void create()
{
        set_name("流氓");

        set_max_hp(400);  set_max_mp(0);
        set_ap(300);  set_dp(160);  
        set_cp(  0);  set_pp(160);  
        set_sp(0);

        set_walk_speed(3);  set_attack_speed(10);
        set_max_seek(6);

        setup();

        set_char_type(FIGHTER_TYPE);    // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return THROWING; }

// 函数：特技攻击对手
int perform_action( object who ) { return PF_FILE_01611->perform_action_npc( this_object(), who ); }

// 函数：掉宝奖励
void win_bonus( object who ) { __FILE__ ->win_bonus2( this_object(), who ); }

// 函数：掉宝奖励(在线更新)
void win_bonus2( object me, object who )
{
	string name, result, leader;
	object orgnpc, *team;
	int size, i, level2, exp2, level, exp;
	int drop = 1;
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
        if( (leader=who->get_leader()) && arrayp( team = who->get_team() ) && sizeof(team) > 1 )
        {
                team = me->correct_bonus_team(team);
                size = sizeof(team);
        }
        else    size = 1;
        level = 30 + me->get_level()*10;
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

void upgrade(int level)
{
	int hp;
	object me = this_object();
	hp = me->get_max_hp();
        me->set_max_hp(me->get_max_hp()*14/10);
        me->add_ap(20);
        me->add_hp(me->get_max_hp()-hp);
        me->set_level(level);
}