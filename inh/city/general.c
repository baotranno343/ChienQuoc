// general 将军

#include <ansi.h>
#include <city.h>
#include <cmd.h>
#include <skill.h>

// 函数：对话处理
void do_look( object who, object me )
{
        string name1, name2;
        string cmd1, cmd2, cmd3, cmd4, cmd5;

        name1 = who->get_city_name();
        name2 = me->get_city_name();
 
        if( stringp(name1) && stringp(name2) && name1 == name2 )
        {
                if( who->is_soldier() )
                {
                        cmd1 = sprintf( "talk %x# patrol\n", getoid(me) );
                        cmd2 = sprintf( "talk %x# soldier\n", getoid(me) );
                        cmd3 = sprintf( "talk %x# armor\n", getoid(me) );
                        cmd4 = sprintf( "talk %x# taofa\n", getoid(me) );
                        cmd5 = sprintf( "talk %x# baowei\n", getoid(me) );
                        send_user( who, "%c%s", ':', me->get_name() + "：\n    " + "/quest/word"->get_country_word(me) + "\n    " + who->get_name() + "，尔等找我有何事情？\n" 
                                ESC "参加城内巡逻.\n" + cmd1 +
                                ESC "领取征兵任务.\n" + cmd2 +
                                ESC "领取战备任务.\n" + cmd3 +
                                ESC "讨伐敌国.\n" + cmd4 +
                                ESC "保卫家园.\n" + cmd5 +
                                ESC "离开.\nCLOSE\n" );
                }
                else
                {
                        send_user( who, "%c%s", ':', me->get_name() + "：\n    "+"/quest/word"->get_country_word(me) );
                }
        }
        else
        {
                send_user( who, "%c%s", ':', me->get_name() + "：\n    "+ "/quest/word"->get_country_word(me) );
        }
}

// 函数：城内巡逻
void do_patrol( object who, object me, string arg )
{
        object city;
        string name1, name2;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&      who->is_soldier()
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( who->get_2("train.patrol") )
                {
                        send_user( who, "%c%s", ':', me->get_name() + "：\n你四周巡逻一下，看有谁被宵小滋扰.\n" );
                        return;
                }
                if( who->get_strength() < 1 )
                {
                        send_user(who, "%c%s", '!', "您现在的体力不够.");
                        return;
                }

                who->set_2("train.patrol", 1);
                send_user( who, "%c%s", ':', me->get_name() + "：\n城里有些宵小正在捣乱，你四处巡逻打听一下吧.\n" );
        }
}

// 函数：征兵任务
void do_soldier( object who, object me, string arg )
{
        object city;
        string name1, name2;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&      who->is_soldier()
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( city->is_soldier_enough() )
                {
                        send_user( who, "%c%s", ':', me->get_name() + "：\n城里士兵已经足够了，不需要再征兵了.\n" );
                        return;
                }
                if( who->get_2("train.soldier") )
                {
                        send_user( who, "%c%s", ':', me->get_name() + "：\n你在城中各处动员一下，看有谁愿意参军吧.\n" );
                        return;
                }
                if( who->get_strength() < 1 )
                {
                        send_user(who, "%c%s", '!', "您现在的体力不够.");
                        return;
                }

                who->set_2("train.soldier", 1);
                send_user( who, "%c%s", ':', me->get_name() + "：\n你在城中各处动员一下，看有谁愿意参军吧.\n" );
        }
}

// 函数：战备任务
void do_armor( object who, object me, string arg )
{
        object city;
        string name1, name2;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&      who->is_soldier()
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( city->get_armor() >= city->get_soldier() )
                {
                        send_user( who, "%c%s", ':', me->get_name() + "：\n城里装备已经足够了，不需要再添置了.\n" );
                        return;
                }
                if( who->get_2("train.armor") )
                {
                        send_user( who, "%c%s", ':', me->get_name() + "：\n你去各国调查一下，看哪里能买到装备？\n" );
                        return;
                }
                if( who->get_strength() < 1 )
                {
                        send_user(who, "%c%s", '!', "您现在的体力不够.");
                        return;
                }

                who->set_2("train.armor", 1);
                send_user( who, "%c%s", ':', me->get_name() + "：\n你去各国调查一下，看哪里能买到装备？\n" );
        }
}
