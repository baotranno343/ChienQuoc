
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <cmd.h>

inherit OFFICER;


// 有自己的do_look函数
int is_self_look() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 5503; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("生活技能更新使者");

        set_2( "talk", ([
                "welcome"           : (: do_welcome :),
        ]));
        setup();
}

void do_look( object who )
{
	__FILE__ ->do_look2(this_object(), who);
}

// 函数：对话处理
void do_look2( object me, object who )
{
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7;
        int id;

        id = getoid( me );
        cmd1 = sprintf( "talk %x# welcome.610\n", id );
        cmd2 = sprintf( "talk %x# welcome.620\n", id );
        cmd3 = sprintf( "talk %x# welcome.630\n", id );
        cmd4 = sprintf( "talk %x# welcome.640\n", id );
        cmd5 = sprintf( "talk %x# welcome.650\n", id );
        cmd6 = sprintf( "talk %x# welcome.660\n", id );        
        cmd7 = sprintf( "talk %x# welcome.680\n", id ); 
        send_user( who, "%c%s", ':', sprintf( get_name() + "：\n    由于酒食生活技能的最高等级下调到80级，所以请大家更新酒食技能。给大家带来的不便，深表歉意。\n"+
//                ESC "调整酒食技能\n" + cmd1 +
//                ESC "调整铁匠技能\n" + cmd2 +
//		ESC "调整炼丹技能\n" + cmd3 +
//                ESC "调整裁缝技能\n" + cmd4 +
//                ESC "调整石刻技能\n" + cmd5 +
//                ESC "调整机关技能\n" + cmd6 +
                ESC "调整采药技能\n" + cmd7 +
                ESC "离开。\nCLOSE\n" ) );                            
}


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag, size , pf, i, level, count;
        object file, perform, who;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        if (flag!=680) return;
        level = who->get_skill(flag);
        if (level<=0)
        {
        	send_user( who, "%c%c%w%s", ':', 3, 5901, "您还没有学会这样技能。" );  
        	return ;
        }
        count = 0;
        for (i=0;i<500;i++)
        {
        	pf = flag * 100 + i;
		if ("/sys/item/product"->check_vita_skill(who, pf)) continue;
		perform = load_object( SKILL->get_perform_file(pf) );
		if (perform)
		{
			if (perform->get_skill_color()) break;
			if (perform->get_skill_level()<=level) 
			{		
				count ++;				
				"/sys/item/product"->add_vita_skill(who, pf);
				perform->can_perform(who);
			}
			else break;
		}
		if (i>40 && !perform) break;        	
        }
        if (count==0)
        	send_user( who, "%c%c%w%s", ':', 3, 5901, "您的技能不需要调整。" );  
        else
        	send_user( who, "%c%c%w%s", ':', 3, 5901, sprintf("调整了%d项特殊技。", count) );  
}