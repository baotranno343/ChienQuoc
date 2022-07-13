
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <map.h>
#include <skill.h>
#include <task.h>

inherit BADMAN;

// 函数：是否允许移动
// int is_moveable() { return 0; }    // 禁止使用 go 命令

// 函数：跟随对手(心跳之中调用)
// void follow_user() { }    // 禁止跟随敌人

// 函数：获取人物造型
// int get_char_picid() { return 1000; }

// 函数：构造处理
void create()
{
        set_name("石俑");
        set_char_picid(1000);

        set_char_type(FIGHTER_TYPE);    // init_level 要用到

        NPC_ENERGY_D->init_level( this_object(), 5 );    // + random(0)
        set_max_seek(4);

        setup();

        set_char_type(FIGHTER_TYPE);    // 重设类型

        set( "birthday", time() );
}

// 函数：复位处理
void reset() 
{
        if( gone_time( get("birthday") ) >= 3600 )    // 30 分钟
        {
                remove_from_scene();
                destruct( this_object() );
        }
}

// 函数：可以接受战斗
int can_be_fighted( object who ) { return 1; }

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
        object owner, obj, map, city, oldcity, npc, wuobj;
        int p, x, y, z, status, date, oldz;

        if( !me->can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;
                
        if (!who) return;
                
        who->add_save("fighter.status", 1);
        status = who->get_save("fighter.status");
        who->add_exp(20);
        send_user( who, "%c%s", ']', "您得到" HIY "经验" NOR " 20 点！");
        who->add_potential(2);
        send_user( who, "%c%s", ']', "您得到" HIY "潜能" NOR " 2 点！");        
        if( status >= 6 && !who->get_legend(TASK_NEWBIE_00, 7) )
        {
                oldz = get_z(who);
                oldcity = get_map_object(oldz);        

                if( ( z = find_map_flag(NEWBIE_MAP_BEGIN, NEWBIE_MAP_END, 0) ) <= 0 )
                {
                        MAP_D->add_to_void(who);    // 移入 VOID 场景
                        who->delete_save_2("Newbie");    // "Newbie.Login"

                        return;
                }

                p = 802;
                init_virtual_map(z, p);    // 生成虚拟地图

                map = new( NEWBIE );
                map->set_client_id(p);
                set_map_object( map, map->set_id(z) );

                map->set_name("仙灵岛２");
                map->set_owner(who);
                who->set_die(0);
                who->set_hp(who->get_max_hp());
                who->set_mp(who->get_max_mp());
                if( p = get_jumpin(z, 2) )
                {
                        who->add_to_scene(z, p / 1000, p % 1000, 3);

                        if(     objectp( npc = new( "/npc/01/0010" ) )    // 文曲星
                        &&    ( p = get_valid_xy(z, 82, 75, IS_CHAR_BLOCK) ) )
                                npc->add_to_scene(z, p / 1000, p % 1000, 4);

                        if(     objectp( npc = new( "/npc/01/0011" ) )    // 武曲星
                        &&    ( p = get_valid_xy(z, 91, 44, IS_CHAR_BLOCK) ) )
                        {
                                npc->add_to_scene(z, p / 1000, p % 1000, 3);
                                wuobj = npc;
                        }

                        if(     objectp( npc = new( "/npc/01/0012" ) )    // 大伯公
                        &&    ( p = get_valid_xy(z, 66, 71, IS_CHAR_BLOCK) ) )
                                npc->add_to_scene(z, p / 1000, p % 1000, 2);

                        if(     objectp( npc = new( "/npc/01/0013" ) )    // 瑶姬仙子
                        &&    ( p = get_valid_xy(z, 98, 68, IS_CHAR_BLOCK) ) )
                                npc->add_to_scene(z, p / 1000, p % 1000, 3);

                        if(     objectp( npc = new( "/npc/01/0014" ) )    // 仙岛精灵
                        &&    ( p = get_valid_xy(z, 126, 58, IS_CHAR_BLOCK) ) )
                                npc->add_to_scene(z, p / 1000, p % 1000, 4);
                }
                
                if (objectp(wuobj))        
                        send_user( who, "%c%c%w%s", ':', 4, 4153, 
                                sprintf("%s：\n    不错！相当漂亮！这是作为你成绩优秀的奖励，拿去吧！\n"
                                        ESC "继续\ntalk %x# welcome.18", wuobj->get_name(), getoid(wuobj) ) );
                NEWBIE->destruct_virtual_map(oldcity, oldz);
                return;                                                        
        }
        else
                send_user(who, "%c%s", '!', sprintf("还剩下%d个目标没有完成。", 6 - status ));                
                        
}
