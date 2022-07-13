
#include <npc.h>
#include <ansi.h>
#include <music.h>
#include <task.h>

inherit NPC;

// 函数：使命人物识别
int is_task_npc() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：使命人物设置
void setup()
{
        ::setup();

        NPC_ENERGY_D->init_level( this_object() , 9 );

        add_max_hp(1000);
}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner;

        if( who->get_enemy() == this_object() ) return 1;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return 0;
	"/quest/help"->send_help_tips(who, 16);
	return 1;
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
        object owner, *team,item;
        int level, level2, exp,  pot, pot2, p,exp2;
        int i, size;
        if( !me->can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;

        __FILE__ ->drop_items(me, who);

        // ---------- 最后一击，爆落装备 ///// 持续攻击，分配经验 ----------
        if( !objectp( who = me->get_enemy_4() ) ) return;
        if( !me->can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;

        team = me->correct_bonus_team1( who->get_team(),30);	//30格以内可以得到奖励
        if( ( size = sizeof(team) ) < 1 )
        {
        	size = 1;
        	team = ({ who });
        }

        level = me->get_level();
        exp = 500 * ( 100 - size * 5 ) / 100;
        pot = 50;

        for( i = 0; i < size; i ++ ) if ( team[i] )
        {
		pot2 = pot * team[i]->get_online_rate() / 100;
		exp2 = exp * team[i]->get_online_rate() / 100;
                team[i]->add_exp(exp2);
                team[i]->add_potential(pot2);
                team[i]->add_log("&task2", exp2);
                team[i]->add_log("*task2", pot2);
                team[i]->add_log("#task2", 1);

//                send_user( team[i], "%c%w", 0x0d, MUSIC_TASK );
                if (team[i]==who)
                	write_user( team[i], ECHO "Bạn tiêu diệt %s, nhận được %+d kinh nghiệm và %+d tiềm năng.", me->get_name(), exp2, pot2 );
                else
                	write_user( team[i], ECHO "Bạn tham gia đánh gục %s nhân vật sứ mệnh, nhận được %+d kinh nghiệm và %+d tiềm năng.", me->get_name(), exp2, pot2 );

        }
}

// 函数：掉宝奖励
void drop_items( object me, object who )
{
        object obj;
        string file;
        int p, rate;
        int z, x, y;

        z = get_z(me);  x = get_x(me);  y = get_y(me);

        p = random(100);

        rate = me->correct_drop_rate( me->get_level() - who->get_level() );

	rate = rate * who->get_online_rate() / 100;
        if( p < 80 * rate / 100 ) ;    // NONE

        else if( p < 96 * rate / 100 )    // 金钱
        {
                if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
                {
                        obj = new( "/item/std/0001" );
                        obj->set_value( 1000 + random(1001) );
                        obj->add_to_scene(z, p / 1000, p % 1000);
                        obj->set("winner", who);
                        obj->set( "time", time() );
                }
        }
        else if( p < 100 * rate / 100 )    // 特殊药物
        {
                switch( random(8) )
                {
               case 0 : file = "/item/91/9160";  break;
               case 1 : file = "/item/91/9161";  break;
               case 2 : file = "/item/91/9162";  break;
               case 3 : file = "/item/91/9163";  break;
               case 4 : file = "/item/91/9164";  break;
               case 5 : file = "/item/91/9165";  break;
               case 6 : file = "/item/91/9166";  break;
               case 7 : file = "/item/91/9167";  break;
                }
                if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                {
                        obj = new( file );
                        obj->add_to_scene(z, p / 1000, p % 1000);
                        obj->set("winner", who);
                        obj->set( "time", time() );
                }
        }
}
