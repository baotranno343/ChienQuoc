
#include <ansi.h>
#include <map.h>
#include <skill.h>
#include <action.h>
#include <equip.h>
#include <cmd.h>

inherit "/inh/std/virtual";

private static object Owner;            // 用户标识(备注：记录主人，主人不在时清除此场景)

// -------------------------------------------------------------

// 函数：获取地型类别
int get_map_type() { return CAVE_MAP; }

// 函数：构造处理
void create() 
{ 
        object me = this_object();

        set_client_id(801);
        set_name("Tân Thủ Trường Cảnh");

        if( !clonep(me) ) return;

        set_heart_timer( me, set_heart_timer_2(me, getoid(me) % 10) );    // 心跳随机
        set_heart_loop(me, 600);    // 循环心跳：１分钟
        me->heart_beat();
        set_heart_beat(1);
}

// -------------------------------------------------------------

// 函数：获取用户标识
object get_owner() { return Owner; }

// 函数：设置用户标识
object set_owner( object who ) { return Owner = who; }

// -------------------------------------------------------------

// 函数：心跳处理
void heart_beat() { }
/*
private static int HeartSec = 0;        // 心跳计时

// 函数：获取心跳计时
int get_heart_sec() { return HeartSec; }

// 函数：设置心跳计时
int set_heart_sec( int point ) { return HeartSec = point; }

// 函数：增添心跳计时
int add_heart_sec( int point ) { return set_heart_sec(HeartSec + point); }
*/
// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) { __FILE__ ->heart_beat_loop_callout( this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8 ); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout( object map, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每１分处理
{
        object who = map->get_owner();

        if( !objectp(who) || get_z(who) != map->get_id() )    // 主人不存在，或不在本场景
        {
                NEWBIE->destruct_virtual_map( map, map->get_id() );
        }
}

// -------------------------------------------------------------

// 函数：清除所有物体
void cleanup_char_and_item( object map )
{
        object *item, who, npc;
        int z, x, y, p, max_x, max_y;
        int i, size;

        reset_eval_cost();

        z = map->get_id();  max_x = get_map_max_x(z);  max_y = get_map_max_y(z);

        for( x = 0; x < max_x; x += AREA_SIZE ) for( y = 0; y < max_y; y += AREA_SIZE )
        {
                if( have_scene_object(z, x, y, ITEM_TYPE, 1) )
                {
                        item = get_scene_object(z, x, y, ITEM_TYPE, 1);

                        for( i = 0, size = sizeof(item); i < size; i ++ ) if( who = item[i] )
                        {
                                who->remove_from_scene();
                                destruct(who);
                        }
                }
                if( have_scene_object(z, x, y, CHAR_TYPE, 1) )
                {
                        item = get_scene_object(z, x, y, CHAR_TYPE, 1);

                        for( i = 0, size = sizeof(item); i < size; i ++ ) if( who = item[i] )
                        {
                                who->remove_from_scene();
                                destruct(who);
                        }
                }
                if( have_scene_object(z, x, y, USER_TYPE, 1) )
                {
                        item = get_scene_object(z, x, y, USER_TYPE, 1);

                        for( i = 0, size = sizeof(item); i < size; i ++ ) 
                                if( who = item[i] ) MAP_D->add_to_void(who);    // 移入 VOID 场景
                }
        }
}

// 函数：删除虚拟场景
void destruct_virtual_map( object map, int id )
{
        if( !map->is_virtual_scene() ) return;

	cleanup_char_and_item(map);
	free_virtual_map(id);
	destruct(map);	
}

// 在切磋的死亡callout处理
void begin_fight_die()
{
        call_out("message1", 2);
}

void message1()
{
        remove_call_out("message1");   
        if (!Owner) return;
        send_user( Owner, "%c%s", '!', "Không cần dễ dàng buông tha, ta sẽ không làm khó ngươi!");               
        send_user( get_scene_object_2(Owner, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(Owner), 
                51141, 1, OVER_BODY, 51142, 1, OVER_BODY, 51143, 1, UNDER_FOOT, 51144, 1, UNDER_FOOT, PF_ONCE );                  
        call_out("message2", 2);
}

void message2()
{
        remove_call_out("message1");
        remove_call_out("message2");     
        if (!Owner) return;
        send_user( Owner, "%c%s", '!', "Ngươi lại một lần nữa đứng lên!");      
        Owner->set_die(0);
	Owner->set_hp(Owner->get_max_hp());
        Owner->set_mp(Owner->get_max_mp());                 
}