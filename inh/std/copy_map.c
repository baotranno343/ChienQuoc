//Phó Bản Trường Cảnh
#include <ansi.h>
#include <map.h>
#include <skill.h>
#include <action.h>
#include <equip.h>
#include <cmd.h>

inherit "/inh/std/virtual";

private static object Owner;            // 用户标识(备注：记录主人，主人不在时清除此场景)
private object *nNpc = ({});		//副本的怪
// -------------------------------------------------------------
// 函数：副本场景识别
int is_copy_scene() { return 1; }

// 函数：获取地型类别
int get_map_type() { return CAVE_MAP; }

// 函数：构造处理
void create() 
{ 
        object me = this_object();

        set_client_id(801);
        set_name("Phó Bản Trường Cảnh");

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

// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) { __FILE__ ->heart_beat_loop_callout( this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8 ); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout( object map, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每１分处理
{
	int tId;
	object *nMember;

	tId = map->get("copy_id");
	if ( !tId )
		return ;
	nMember = TEAM_D->get_team_by_id(tId);
	if ( nMember )
		nMember -= ({0});
	if ( sizeof(nMember) )
		return ;
	//队伍无人在线，则删除此副本
	COPY_MAP->destruct_virtual_map( map, map->get_id() );
}

// -------------------------------------------------------------

// 函数：清除所有物体
void cleanup_char_and_item( object map )
{
        object *item, who, npc,*nObj;
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
        //删除副本的其余怪
        nObj = map->get_copy_npc();
        for(i=0,size=sizeof(nObj);i<size;i++)
        {
        	if ( !objectp(who=nObj[i]) )
        		continue;
        	who->remove_from_scene();
        	destruct(who);	
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

//加入副本的怪
void add_copy_npc(object npc)
{
	nNpc += ({npc});	
}
//取副本的所有怪
object *get_copy_npc() { return copy(nNpc); }
//初始化副本的怪集合
void init_copy_npc() { nNpc = ({}); }
//设置
void set_copy_npc(object *npc ) { nNpc = npc; }

string get_name()
{
	return "Phó Bản "+::get_name();	//告诉客户端是副本地图
}