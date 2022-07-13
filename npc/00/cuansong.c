#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <effect.h>
inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5302; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("到九曲桥１的传送人");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));   
        setup();
}

// 函数：对话处理
void do_look( object who )
{
        int status;
        object me = this_object();
        status = who->get("xiannv.status");
        send_user( who, "%c%c%w%s", ':', 3, 5302,
        	sprintf("%s：\n    我可以把你从当前位置瞬间移到其他位置，你是否想试试？\n"
                ESC "确定\ntalk %x# welcome.1\n"
                ESC "取消\nCLOSE\n", me->get_name(), getoid(me) ) );

}

// 函数：对话处理
void do_welcome( string arg )
{
	int p;
	int x0,y0,z,x,y;
	object who = this_player();
	
	z = 1;
	if ( random(2) )
	{
		x0 = 304;
		y0 = 126;
	}
	else
	{
		x0 = 205;
		y0 = 183;
	}	
        if( p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK) )
        {
                x = p / 1000;  y = p % 1000;

//                me->set_login_flag(2);    // 跳转保护
//                set_invisible(who, 1);
//                set_effect(who, EFFECT_USER_LOGIN, 4);
//
                who->add_to_scene( z, x, y, get_front_xy(x, y, x0, y0) );

                tell_user( who, "您去到: %d (%d, %d)。", z, x, y );
		return ;
        }

}