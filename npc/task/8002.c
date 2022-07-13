
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <music.h>

inherit NPC;

// 函数：是否僵尸
// int is_zombie() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 4144; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        object me = this_object();

        set_name( "Cương Thi" );
        set_gender(1);

        set_armor_code( M_GUANPAO );
        set_armor_color_1( M_PURPLE | M_PURPLE_H );
        set_armor_color_2( M_PURPLE | M_PURPLE_H );
        set_head_code( M_DAOGUAN );
        set_head_color( M_PURPLE | M_PURPLE_H );

        set_walk_speed(WALK_SPEED_4);
        set_attack_speed(ATTACK_SPEED_4);

        setup();

        set( "birthday", time() );

        if( !clonep(me) ) return;

        set_heart_timer( me, set_heart_timer_2(me, getoid(me) % 10) );    // 心跳随机
        set_heart_loop(me, 10);    // 循环心跳：１秒钟
        me->heart_beat();
        set_heart_beat(1);
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：复位处理
void reset() 
{
        if( gone_time( get("birthday") ) >= 1200 )    // 20 分钟
        {
                remove_from_scene();
                destruct( this_object() );
        }
}

// -------------------------------------------------------------

private static int HeartSec = 0;        // 心跳计时

// 函数：获取心跳计时
int get_heart_sec() { return HeartSec; }

// 函数：设置心跳计时
int set_heart_sec( int point ) { return HeartSec = point; }

// 函数：增添心跳计时
int add_heart_sec( int point ) { return set_heart_sec(HeartSec + point); }

// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) { __FILE__ ->heart_beat_loop_callout( this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8 ); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout( object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每１秒处理
{
        object who;

        NPC_EFFECT_D->into_effect(me, effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8);    // 征状处理
        if( !me ) return;    // 死亡退出

        NPC_HEART_D->heart_beat_other(me);
        if( !me ) return;    // 死亡退出

        if( me->add_heart_sec(1) % 10 == 0 )    // 每十秒处理以下
        {
                if(    !objectp( who = me->get("task") ) 
                ||      get_z(who) != get_z(me) )
                {
                        me->remove_from_scene();
                        destruct(me);
                }
                else    me->set_enemy(who);    // 保持攻击
        }
}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner;
        int id;

        if( who->get_enemy() == this_object() ) return 1;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return 0;

        if( get("task") == who ) return 1;

        send_user( who, "%c%s", '!', get_name() + "不想同你打架。" );
        return 0;
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
        object owner;
        int level, level2, exp, exp2, pot, pot2;

        if( !me->can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;

        __FILE__ ->drop_items(me, who);

        // ---------- 最后一击，爆落装备 ///// 持续攻击，分配经验 ----------

        if( !objectp( who = me->get_enemy_4() ) ) return;

        if( !me->can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;

        if( me->get("task") != who ) return;

        level = me->get_level();

        exp = level * 22 + 200;
        pot = level * 2 / 3 + random(level);

        level2 = level - who->get_level();
        exp2 = me->correct_exp_bonus(level, level2, exp);  who->add_exp(exp2);    // add_exp(exp2, 1);
        pot2 = me->correct_exp_bonus(level, level2, pot);  who->add_potential(pot2);

        who->add_log("&monster2", exp2);
        who->add_log("*monster2", pot2);
        who->add_log("#monster2", 1);

        send_user( who, "%c%w", 0x0d, MUSIC_TASK );
        write_user( who, ECHO "您击毙了%s，经验 %+d, 潜能 %+d。", me->get_name(), exp2, pot2 );
}

// 函数：掉宝奖励
void drop_items( object me, object who )
{
        object item;
        string file;
        int p, rate;
        int z, x, y;

        z = get_z(me);  x = get_x(me);  y = get_y(me);

        p = random(100);

        rate = me->correct_drop_rate( me->get_level() - who->get_level() );

        if( p < 95 * rate / 100 ) ;    // NONE

        else if( p < 100 * rate / 100 )    // 金钱
        {
                if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
                {
                        item = new( "/item/std/0001" );
                        TEAM_D->drop_item(item,who);
                        item->set_user_id(who->get_id());
                        item->set_value( get_level() * 5 + 500 );
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set( "time", time() );
                }
        }
}
