
#include <npc.h>
#include <ansi.h>
#include <map.h>
#include <task.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 952; }

// 函数：构造处理
void create()
{
	object me = this_object();
        set_name( "Tiên Đảo Tinh Linh" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
        setup();     
}

void do_look( object who )
{
	object me = this_object();

	send_user( who, "%c%c%s", ':', 2, "仙岛精灵：\n    你是谁呀？我们见过面吗？\n"ESC" \nCLOSE\n" );	

}

void do_welcome( string arg )
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	object map, map2, who, npc;
	int z, z2, x, y, p;

	who = this_player();
	who->set_time("talk",  0);
	send_user( who, "%c%d", ':', 0);

        if( ( z = find_map_flag(NEWBIE_MAP_BEGIN, NEWBIE_MAP_END, 0) ) <= 0 ) return;

	z2 = get_z(who);
	map2 = get_map_object(z2);	

        init_virtual_map(z, 803);

        map = new( NEWBIE );
        map->set_client_id(803);
	set_map_object( map, map->set_id(z) );

	map->set_name("仙灵岛3");
	map->set_owner(who);

	who->set_save_2("Newbie.Login", 803);

        if( p = get_jumpin(z, 1) )
        {
                who->add_to_scene(z, p / 1000, p % 1000, 3);

                if(     objectp( npc = new( "/npc/01/0020" ) )    // 百合仙子
                &&    ( p = get_valid_xy(z, 34, 27, IS_CHAR_BLOCK) ) )
                        npc->add_to_scene(z, p / 1000, p % 1000, 4);
        }

	NEWBIE->destruct_virtual_map(map2, z2);
}
