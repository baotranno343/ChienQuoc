// warder 典狱官

#include <ansi.h>

void do_look( object who, object me )
{
        string name1, name2;
        string cmd1, cmd2, cmd3,cmd4;

        name1 = who->get_city_name();
        name2 = me->get_city_name();
        
        cmd4 = TASK_MASTER_D->do_look_quest6(who, me);
               	
        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&    ( who->get_id() == me->get_master() || who->get_id() == me->get_master_2() || who->get_id() == me->get_master_3() ) )
        {
                cmd1 = sprintf( "talk %x# faling\n", getoid(me) );
                cmd2 = sprintf( "talk %x# list\n", getoid(me) );
                cmd3 = sprintf( "talk %x# free\n", getoid(me) );
                send_user( who, "%c%s", ':', me->get_name() + "：\n    "+"/quest/word"->get_country_word(me)+"\n    " + who->get_name() + "，您有什么事情？\n" 
                	+ cmd4 +
                        ESC "颂布法令.\n" + cmd1 +
//                        ESC "查看狱中玩家.\n" + cmd2 +
//                        ESC "释放狱中玩家.\n" + cmd3 +
                        ESC "离开.\nCLOSE\n" );
        }
        else
        {
                cmd1 = sprintf( "talk %x# list\n", getoid(me) );
                cmd2 = sprintf( "talk %x# free\n", getoid(me) );
                send_user( who, "%c%s", ':', me->get_name() + "：\n    "+"/quest/word"->get_country_word(me)+"\n" 
                	+ cmd4 +
//                        ESC "查看狱中玩家.\n" + cmd1 +
//                        ESC "保释狱中玩家.\n" + cmd2 +
                        ESC "离开.\nCLOSE\n" );
        }
}

void do_faling( object who, object me )
{
        string name1, name2;
        string cmd1, cmd2;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&    ( who->get_id() == me->get_master() || who->get_id() == me->get_master_2() || who->get_id() == me->get_master_3() ) )
        {
                cmd1 = sprintf( "talk %x# jieyan\n", getoid(me) );
                cmd2 = sprintf( "talk %x# dashe\n", getoid(me) );
                send_user( who, "%c%s", ':', "您想让" + me->get_name() + "颂布什么法令？(消耗 50 体力)\n" 
                        ESC "戒严令，全城搜捕有 PK 标志的人.\n" + cmd1 +
                        ESC "大赦令，取消搜捕有 PK 标志的人.\n" + cmd2 +
                        ESC "我再想想……\nCLOSE\n" );
        }
}

void accept_task(object who,object npc)
{
	TASK_MASTER_D->accept_task11(who,npc);
}