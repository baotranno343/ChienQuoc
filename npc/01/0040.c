
#include <npc.h>
#include <ansi.h>
#include <map.h>
#include <task.h>
#include <equip.h>
#include <effect.h>
#include <skill.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 6009; } 

// 函数：构造处理
void create()
{
        set_name( "Trì Dũ Tiên Tử" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
        setup();     
}

void do_look( object who )
{
        int status;
        string name;
        object me = this_object();
        status = who->get("xiannv.status");
        if (who->get_gender()==1) name = "小哥哥";
        else name = "小姐姐";
        if (who->get_level()<10)
        	send_user( who, "%c%c%w%s", ':', 3, 6009,
	        	sprintf("%s：\n    这位%s，您的身体是不是觉得有些不舒服？需要我的帮助吗？可别小看我，我可是药神的小徒弟哦～\n"
	                ESC "请帮助我恢复吧～\ntalk %x# welcome.1\n"
	                ESC "离开\nCLOSE\n", me->get_name(), name, getoid(me) ) );
	else
        	send_user( who, "%c%c%w%s", ':', 3, 6009,
	        	sprintf("%s：\n    你的等级已经脱离新手阶段了，我也不能再帮助你恢复了。不过我还会祝福你往后的旅程一路顺风的。\n"
	                ESC "离开\nCLOSE\n", me->get_name(), getoid(me) ) );
		               
}

void do_welcome( string arg )
{
        object map, map2, who, me, npc, item,*nEquip, level;
        int flag, status, z, z2, x, y, p;
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, result;
        me = this_object();
        who = this_player();
        flag = to_int(arg);
        status = who->get("xiannv.status");
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if (who->get_level()>=10)
        	{
	        	send_user( who, "%c%c%w%s", ':', 4, 6009,
		        	sprintf("%s：\n    你的等级已经脱离新手阶段了，我也不能再帮助你恢复了。不过我还会祝福你往后的旅程一路顺风的。\n"
		                ESC "离开\nCLOSE\n", me->get_name(), getoid(me) ) );
        		return;
        	}       	
        	who->set_hp(who->get_max_hp());
        	who->set_mp(who->get_max_mp());
        	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 51121, 1, OVER_BODY, PF_ONCE );
                break;
        }
}