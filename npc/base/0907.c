
#include <npc.h>
#include <cmd.h>
#include <ansi.h>
#include <item.h>

inherit OFFICER;

// 函数：修理师傅
int is_repairer() { return 1; }

void do_welcome(string arg);
void do_identify(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5407; }

// 函数：构造处理
void create()
{
        set_name("巨兽岛修理人");
        set_city_name("Cự Thú Đảo");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
                "identify"          : (: do_identify :),
        ]));
        setup();
}



// 函数：对话处理
void do_look( object me )
{
	object who = this_object();
	"/quest/help"->send_help_tips(who, 52);
        if (me->get_skill(650))
	        send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
                        sprintf("%s：\n    据说这岛上的怪物长的比人还高！不知你可否见过？\n    请问您需要什么服务？\n"
                        ESC "我要鉴定装备\nrepair %x# identify\n"
                        ESC "我要分解装备\nrepair * %x#\n"
                        ESC "我需要普通修理\nrepair %x# 2\n"
                        ESC "我只是经过来逛逛而已\nCLOSE\n", who->get_name(), getoid(who), getoid(who), getoid(who) ) );
        else
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
                	sprintf("%s：\n    据说这岛上的怪物长的比人还高！不知你可否见过？\n    请问您需要什么服务？\n"
                	ESC "我要鉴定装备\nrepair %x# identify\n"
//                        ESC "我需要完美的特殊修理\nrepair %x# 1\n"
                        ESC "我需要普通修理\nrepair %x# 2\n"
                        ESC "我只是经过来逛逛而已\nCLOSE\n", who->get_name(), getoid(who), getoid(who) ) );
}
