
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <city.h>
#include <music.h>

inherit NPC;

// 函数：城中混混
int is_rascal() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "混混" + NPC_NAME_D->get_rascal_name() );
        set_char_picid(0052);    // 混混
        set_walk_speed(WALK_SPEED_4);
        set_attack_speed(ATTACK_SPEED_4);

        setup();

        set( "birthday", time() );
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：复位处理
void reset() 
{
        object city, who;
        string *member, id;
        int i, size;

        if( gone_time( get("birthday") ) >= 2400 )    // 40 分钟
        {
                if( who = find_player( sprintf("%d", get("task") ) ) )
                {
                        who->add_gift_cx(-1);
                        who->add_repute(-1);
                        who->delete_task("rascal");
                        who->delete_task("rascal#");
                }

                if( city = CITY_D->get_city_object( this_object() ) ) city->add_stability(-1);

                remove_from_scene();
                destruct( this_object() );
        }
        else
        {
                member = get("user");
                for( i = 0, size = sizeof(member); i < size; i ++ )
                        if( !( who = find_player( member[i] ) ) ) member[i] = "";
                if( sizeof( member - ({ "" }) ) < 1 )
                {
                        if( who = find_player( sprintf("%d", get("task") ) ) )
                        {
                                who->add_gift_cx(-1);
                                who->add_repute(-1);
                                who->delete_task("rascal");
                                who->delete_task("rascal#");
                        }

                        if( city = CITY_D->get_city_object( this_object() ) ) city->add_stability(-1);

                        remove_from_scene();
                        destruct( this_object() );
                }
        }
}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner;

        if( who->get_enemy() == this_object() ) return 1;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return 0;

        if(     who->is_soldier() 
        &&      get("task") == who->get_number() ) 
                return 1;    // && who->get_strength()

        send_user( who, "%c%s", '!', get_name() + "不想同你打架。" );

        return 0;
}

// 函数：死亡奖励
void win_bonus( object who )
{
        object city, owner;
        int level, gold, exp;

        if( !can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;

        write_user( who, ECHO + get_name() + "说道：“大侠饶命，我还要养三岁孩儿，八十岁的老母呢！”\n"
                ECHO "您大义凛然地教训道：“回去好好做人！”，说罢抬手将他放走。" );

        if( who->add_task("rascal#", 1) >= 2 )
        {
                level = who->get_occupation_level(JOB_SOLDIER);

//              who->add_strength(-1);    // 体力 -1, 军官经验 +60, 正义 +60, 忠实 +1, 勇敢 +60, 声望 +6, 国家贡献 +1
                who->add_occupation_exp(60);
                who->add_gift_zy(60);
                who->add_gift_zs(1);
                who->add_gift_yg(60);
                who->add_repute(6);
                who->add_contribute(1);
                gold = level * 6 + 60;  who->add_cash(gold);  who->add_gold_log("task", gold);
                who->log_money("军官任务", gold);                
                "/sys/sys/count"->add_income("task", gold);
                exp = level * 6 + 60;  who->add_exp(exp);
                who->add_potential(6);

                send_user( who, "%c%w", 0x0d, MUSIC_TASK );
                write_user( who, ECHO "您的军官经验 +60, 正义 +60, 忠实 +1, 勇敢 +60, 声望 +6, 国家贡献 +1, 金钱 %+d, 经验 %+d, 潜能 +6。", gold, exp );

                who->delete_task("rascal");
                who->delete_task("rascal#");

                if( city = CITY_D->get_city_object(who) ) city->add_stability(1);
        }
}

// 函数：失败惩罚
void lose_bonus( object who )
{
        object city;
        int id;

        id = getoid( this_object() );

        if(     get("task") == who->get_number()
        &&      sprintf( "%x#", id ) == who->get_task("rascal") )
        {
                who->add_gift_cx(-1);
                who->add_repute(-1);
                write_user( who, ECHO "您的巡逻任务失败了！(诚信 -1, 声望 -1)" );

                who->delete_task("rascal");
                who->delete_task("rascal#");

                if( city = CITY_D->get_city_object( this_object() ) ) city->add_stability(-1);

                remove_from_scene();
                destruct( this_object() );
        }
}
