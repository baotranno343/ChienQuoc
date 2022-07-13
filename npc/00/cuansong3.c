#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <effect.h>
inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5302; }

// 函数：构造处理
void create()
{
        set_name("到雁门关的传送人");

        setup();
}

// 函数：对话处理
void do_look( object me )
{
	object who;
	string id;
	int p;
	int x0,y0,z,x,y, d;
	
	z = 155;	
        x = 228;  y = 193;    // get_jumpout 内含 z
        d = 3;

        if(   ( who = me->get_quest("escort.npc") )    // 运镖人物
        &&      who->get_owner() == me
        &&      inside_screen_2(me, who) )
                who->add_to_scene(z, x, y, d);
        if(   ( who = me->get_2("orgtask2.npc") )    // 帮派任务
        &&      who->get_owner() == me
        &&      inside_screen_2(me, who) )
                who->add_to_scene(z, x, y, d);                        

        if(   ( stringp(id = me->get_save_2("xiamama") )    // 活动NPC
        &&     objectp(who=find_char(id))
        && 	who->is_daughter()
        &&      inside_screen_2(me, who) ) )
                who->add_to_scene(z, x, y, d);

        if( p = get_valid_xy( z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK ) )
        {
                x = p / 1000;  y = p % 1000;

                me->set_login_flag(2);    // 跳转保护
                set_invisible(me, 1);
                set_effect(me, EFFECT_USER_LOGIN, 4);

                me->add_to_scene(z, x, y, d);

//              if( z != z0 ) if( map = get_map_object(z) ) notify( map->get_name() );    // 显示地图名
        }

}
