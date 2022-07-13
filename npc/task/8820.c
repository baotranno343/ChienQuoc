
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <music.h>

#define INTERIOR_D      "/inh/city/interior"

inherit NPC;

// 函数：城中恶少
int is_rascal_2() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "恶少" + NPC_NAME_D->get_rascal_name_2() );
        set_char_picid(0053);    // 流氓
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
        object who;
        string *member, id;
        int i, size;

        if( gone_time( get("birthday") ) >= 2400 )    // 40 分钟
        {
                if( who = find_player( sprintf("%d", get("task") ) ) ) who->delete_task("rascal2");
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
                        if( who = find_player( sprintf("%d", get("task") ) ) ) who->delete_task("rascal2");
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

        if(     who->get_save_2("build.flag") == 1 
        &&      get("task") == who->get_number() ) 
                return 1;

        send_user( who, "%c%s", '!', get_name() + "不想同你打架。" );

        return 0;
}

// 函数：死亡奖励
void win_bonus( object who )
{
        object owner;
        int level, exp;

        if( !can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;

        write_user( who, ECHO + get_name() + "叫道：“大侠放过我吧，我再也不敢胡做非为了！”\n"
                ECHO "您大义凛然地教训道：“回去好好做人！”，说罢抬手将他放走。" );

        level = who->get_level();

        who->add_contribute(1);    // 国家贡献 +1
        exp = level * random(50) + 1000;  who->add_exp(exp);
        who->add_potential(5);

        send_user( who, "%c%w", 0x0d, MUSIC_TASK );
        write_user( who, ECHO "您的国家贡献 +1, 经验 %+d, 潜能 +5。", exp );

        who->delete_task("rascal2");
        who->delete_save_2("build");    // 删除任务标志

        INTERIOR_D->do_build_finish( who, this_object() );    // 用 this_object 以防 BUG！要 set_city_name
}
