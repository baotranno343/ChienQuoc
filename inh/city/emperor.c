// emperor 君主，皇帝

#include <ansi.h>
#include <music.h>

void do_advice( object who, object me, string arg );

// 函数：对话处理
void do_look( object who, object me )
{
        object city, city2;
        string name1, name2, name3, result;
        string cmd1, cmd2, cmd3;
        int id, flag, city0, city7;

        id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();
        if ( "/sys/task/master"->do_look2(who, me)==1 )
        	return ;  
        if(   ( city7 = who->get_save_2("relation.city2") )
        &&      CITY_D->get_city_name(city7) == name2
        &&      gone_time( who->get_save_2("relation.time") ) < 2400    // 40 分钟
        &&    ( flag = who->get_save_2("relation.flag") )
        &&    ( city = CITY_D->get_city_object(me) )
        &&    ( city0 = who->get_save_2("relation.city") )
        &&    ( city2 = CITY_D->get_city_object_2(city0) ) )
        {
                name3 = CITY_D->get_city_name( who->get_save_2("relation.city") );

                if( random(100) < 30 + who->get_level() / 2 )
                {
                        switch( flag )
                        {
                      default : send_user( who, "%c%s", ':', sprintf( "您：\n我是%s使节，携带礼物，以增进两国友谊.\n\n\n"
                                        "%s：\n那我就收下了，愿两国继续友好合作.\n", name3, me->get_name() ) );

                                city->add_friend(city0, 20);
                                city2->add_friend(city7, 20);
                                city->add_money(100000);
                                city2->add_money(-100000);

                                result = sprintf( "%s向%s进贡 100000 金，以增进两国友谊.", name3, name2 );
                                FAMILY_D->city_channel(name2, 0, result);
                                FAMILY_D->city_channel(name3, 0, result);

                                break;

                       case 2 : send_user( who, "%c%s", ':', sprintf( "您：\n我乃%s使节，尔等近日不利于我国，多番骚扰，还请自重.\n\n\n"
                                        "%s：\n阁下太过无礼！送客！\n", name3, me->get_name() ) );

                                city->add_friend(city0, -20);
                                city2->add_friend(city7, -20);

                                result = sprintf( "%s派使节向%s问罪，双方友好度下降.", name3, name2 );
                                FAMILY_D->city_channel(name2, 0, result);
                                FAMILY_D->city_channel(name3, 0, result);

                                break;
                        }

                        flag = who->get_level() * 70 + 1000;
                        who->add_exp(flag);
                        who->add_potential(5);

                        send_user( who, "%c%w", 0x0d, MUSIC_TASK );
                        write_user( who, ECHO "您的经验 %+d, 潜能 +5.", flag );
                }
                else
                {
                        switch( flag )
                        {
                      default : send_user( who, "%c%s", ':', sprintf( "您：\n我是%s使节，携带礼物，以增进两国友谊.\n\n\n"
                                        "%s：\n我们两国关系还没有如此密切，阁下请回吧.\n", name3, me->get_name() ) );
                                break;
                       case 2 : send_user( who, "%c%s", ':', sprintf( "您：\n我乃%s使节，尔等近日不利于我国，多番骚扰，还请自重.\n\n\n"
                                        "%s：\n阁下误会了，我们两国世代友好，并无它意.\n", name3, me->get_name() ) );
                                break;
                        }

                        who->add_exp(1);
                        who->add_potential(1);

                        write_user( who, ECHO "您的经验 +1, 潜能 +1." );
                }

                who->delete_save_2("relation");

                return;
        }
        if( who->is_scholar() )
        {
                if( who->get_save_2("advice.city") || who->get_save_2("advice.city2") )
                {
                        do_advice(who, me, "");    // 完成纵横任务
                        return;
                }
        }

        if( stringp(name1) && stringp(name2) && name1 == name2 && who->get_id() == me->get_master() )
        {
                cmd1 = sprintf( "talk %x# policy.?\n", id );
                cmd2 = sprintf( "talk %x# relation.?\n", id );
                cmd3 = sprintf( "talk %x# master.?\n", id );
                send_user( who, "%c%s", ':', me->get_name() + "：\n    "+"/quest/word"->get_country_word(me)+"\n    " + who->get_name() + "爱卿，你找我有什么事情吗？\n" 
                        ESC "发布政令.\n" + cmd1 +
                        ESC "制定外交策略.\n" + cmd2 +
                        ESC "副城主的事情.\n" + cmd3 +
                        ESC "退下.\nCLOSE\n" );
        }
        else if( who->is_scholar() )
        {

                cmd1 = sprintf( "talk %x# advice.1\n", id );
                cmd2 = sprintf( "talk %x# advice.2\n", id );

                send_user( who, "%c%s", ':', me->get_name() + "：\n    "+"/quest/word"->get_country_word(me) + "\n    "+ who->get_name() + "，你有什么事情？\n" 
                        ESC "同别国修好.\n" + cmd1 +
                        ESC "向别国问罪.\n" + cmd2 +
                        ESC "退下.\nCLOSE\n" );
        }
        else
        {
                send_user( who, "%c%s", ':', sprintf( " %s :\n "+"/quest/word"->get_country_word(me),me->get_name() ) );
        }
}

// 函数：政令处理
void do_policy( object who, object me, string arg )
{
        object city;
        string name1, name2, name3, result;
        string cmd1, cmd2;
        int number, id;

        id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2 
        &&      who->get_id() == me->get_master()
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( who->get_strength() < 50 )
                {
                        send_user(who, "%c%s", '!', "发布政令要 50 点体力.");
                        return;
                }

                if( !arg || arg == "?" )
                {
                        cmd1 = sprintf( "talk %x# policy.?.1\n", id );
                        cmd2 = sprintf( "talk %x# policy.?.2\n", id );
                        send_user( who, "%c%s", ':', "您想建议" + me->get_name() + "发布什么政令？(消耗 50 体力)\n"
                                ESC "招贤令.\n" + cmd1 +
                                ESC "逐客令.\n" + cmd2 +
                                ESC "我再想想……\nCLOSE\n" );
                }
                else if( sscanf( arg, "?.%d", number ) )
                {
                        switch( number )
                        {
                      default : name3 = "招贤令";  break;
                       case 2 : name3 = "逐客令";  break;
                        }

                        cmd1 = sprintf( "talk %x# policy.%d\n", id, number );
                        send_user( who, "%c%s", ':', sprintf( "您确定建议%s发布%s？\n", me->get_name(), name3 ) + 
                                ESC "是的.\n" + cmd1 +
                                ESC "我再想想……\nCLOSE\n" );
                }
                else if( number = to_int(arg) )
                {
                        switch( number )
                        {
                      default : city->set_save_2("policy.flag", 1);
                                city->set_save_2("policy.time", time() );
                                who->add_strength(-50);

                                result = sprintf( HIY "%s发布了招贤令，诚邀天下能人异士晋见.", me->get_name() );
                                FAMILY_D->city_channel(name2, 0, result);

                                break;

                       case 2 : city->set_save_2("policy.flag", -1);
                                city->set_save_2("policy.time", time() );
                                who->add_strength(-50);

                                result = sprintf( HIY "%s发布了逐客令，谢绝巧言令色之徒晋见.", me->get_name() );
                                FAMILY_D->city_channel(name2, 0, result);

                                break;
                        }
                }
        }
}

// 函数：副手处理
void do_master( object who, object me, string arg )
{
        object city, master;
        string name1, name2;
        string cmd1, cmd2, player;
        string result;
        int id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2 
        &&      who->get_id() == me->get_master()
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( arg == "?" )
                {
                        cmd1 = sprintf( "talk %x# master.+\n", id );
                        cmd2 = sprintf( "talk %x# master.-\n", id );
                        send_user( who, "%c%s", ':', "您同" + me->get_name() + "谈关于副城主的事情.\n"
                                ESC "举荐副城主.\n" + cmd1 +
                                ESC "弹劾副城主.\n" + cmd2 +
                                ESC "我再想想……\nCLOSE\n" );
                }
                else if( arg == "+" )
                {
                        if( city->get_master_2() != "" && city->get_master_3() != "" )
                        {
                                send_user(who, "%c%s", '!', "副城主职缺最多两位.");
                                return;
                        }
                        send_user( who, "%c%c%d%s", '?', 1, 0, sprintf( "您想向%s举荐谁做副城主？请输入对方的数字ＩＤ：\n"
                                ESC "talk %x# master.+.?.%%s\n", me->get_name(), id ) );
                }
                else if( arg == "-" )
                {
                        if( city->get_master_2() == "" && city->get_master_3() == "" )
                        {
                                send_user(who, "%c%s", '!', "现在还没有副城主.");
                                return;
                        }
                        result = sprintf( "您想向%s弹劾哪位副城主？\n", me->get_name() );
                        if( city->get_master_2() != "" )
                        {
                                result += sprintf( ESC "%s\ntalk %x# master.-.?.1\n",
                                        city->get_master_name_2(), id );
                        }
                        if( city->get_master_3() != "" )
                        {
                                result += sprintf( ESC "%s\ntalk %x# master.-.?.2\n",
                                        city->get_master_name_3(), id );
                        }
                        send_user( who, "%c%s", ':', result +
                                ESC "我再想想……\nCLOSE\n" );
                }
                else if( sscanf( arg, "+.?.%s", player ) )
                {
                        if( city->get_master_2() != "" && city->get_master_3() != "" )
                        {
                                send_user(who, "%c%s", '!', "副城主职缺最多两位.");
                                return;
                        }
                        if( !( master = find_player(player) ) )
                        {
                                send_user(who, "%c%s", '!', "无法找到这位玩家.");
                                return;
                        }
                        else if( master == who )
                        {
                                send_user(who, "%c%s", '!', "您不能举荐您自己.");
                                return;
                        }
                        else if( master->get_city_name() != name1 )
                        {
                                send_user(who, "%c%s", '!', "您举荐的人非本国人士.");
                                return;
                        }
                        else if( city->get_master_2() == master->get_id() || city->get_master_3() == master->get_id() )
                        {
                                send_user(who, "%c%s", '!', "您举荐的人已经是副城主了.");
                                return;
                        }

                        result = sprintf( "您确定向%s举荐%s(%d)做副城主？\n", 
                                me->get_name(), master->get_name(), master->get_number() );
                        cmd1 = sprintf( "talk %x# master.+.%s\n", id, player );
                        send_user( who, "%c%s", ':', result +
                                ESC "是的.\n" + cmd1 +
                                ESC "我再想想……\nCLOSE\n" );
                }
                else if( sscanf( arg, "+.%s", player ) )
                {
                        if( city->get_master_2() != "" && city->get_master_3() != "" )
                        {
                                send_user(who, "%c%s", '!', "副城主职缺最多两位.");
                                return;
                        }
                        if( !( master = find_player(player) ) )
                        {
                                send_user(who, "%c%s", '!', "无法找到这位玩家.");
                                return;
                        }
                        else if( master == who )
                        {
                                send_user(who, "%c%s", '!', "您不能举荐您自己.");
                                return;
                        }
                        else if( master->get_city_name() != name1 )
                        {
                                send_user(who, "%c%s", '!', "您举荐的人非本国人士.");
                                return;
                        }
                        else if( city->get_master_2() == master->get_id() || city->get_master_3() == master->get_id() )
                        {
                                send_user(who, "%c%s", '!', "您举荐的人已经是副城主了.");
                                return;
                        }

                        if( city->get_master_2() == "" )
                        {
                                city->set_master_2( master->get_id() );
                                city->set_master_name_2( sprintf( "%s(%s)", master->get_name(), player ) );
                        }
                        else if( city->get_master_3() == "" )
                        {
                                city->set_master_3( master->get_id() );
                                city->set_master_name_3( sprintf( "%s(%s)", master->get_name(), player ) );
                        }
                        city->save();

                        result = sprintf( HIY "%s接受城主%s举荐，委任%s(%d)出任副城主.", 
                                me->get_name(), who->get_name(), master->get_name(), master->get_number() );
                        FAMILY_D->city_channel(name1, 0, result);
                }
                else if( arg == "-.?.1" )
                {
                        if( city->get_master_2() == "" )
                        {
                                send_user(who, "%c%s", '!', "您无法弹劾这位副城主.");
                                return;
                        }
                        result = sprintf( "您确定向%s弹劾%s？\n", me->get_name(), city->get_master_name_2() );
                        cmd1 = sprintf( "talk %x# master.-.1\n", id );
                        send_user( who, "%c%s", ':', result +
                                ESC "是的.\n" + cmd1 +
                                ESC "我再想想……\nCLOSE\n" );
                }
                else if( arg == "-.?.2" )
                {
                        if( city->get_master_3() == "" )
                        {
                                send_user(who, "%c%s", '!', "您无法弹劾这位副城主.");
                                return;
                        }
                        result = sprintf( "您确定向%s弹劾%s？\n", me->get_name(), city->get_master_name_3() );
                        cmd1 = sprintf( "talk %x# master.-.2\n", id );
                        send_user( who, "%c%s", ':', result +
                                ESC "是的.\n" + cmd1 +
                                ESC "我再想想……\nCLOSE\n" );
                }
                else if( arg == "-.1" )
                {
                        if( city->get_master_2() == "" )
                        {
                                send_user(who, "%c%s", '!', "您无法弹劾这位副城主.");
                                return;
                        }

                        result = sprintf( HIY "%s接受城主%s弹劾，免去%s副城主职务.", 
                                me->get_name(), who->get_name(), city->get_master_name_2() );
                        FAMILY_D->city_channel(name1, 0, result);

                        city->set_master_2("");
                        city->set_master_name_2("－－");
                        city->save();
                }
                else if( arg == "-.2" )
                {
                        if( city->get_master_3() == "" )
                        {
                                send_user(who, "%c%s", '!', "您无法弹劾这位副城主.");
                                return;
                        }

                        result = sprintf( HIY "%s接受城主%s弹劾，免去%s副城主职务.", 
                                me->get_name(), who->get_name(), city->get_master_name_3() );
                        FAMILY_D->city_channel(name1, 0, result);

                        city->set_master_3("");
                        city->set_master_name_3("－－");
                        city->save();
                }
        }
}

// 函数：建议处理
void do_advice( object who, object me, string arg )
{
        object city, city2;
        string name1, name2, name3, name4, result;
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6;
        int number, id, city7;
        int level, rate, cash, exp;

        id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if( who->is_scholar() && ( city = CITY_D->get_city_object(me) ) )
        {
                if( who->get_occupation_level() < 80 )
                {
                        send_user(who, "%c%s", '!', "您的书生等级不够.");
                        return;
                }
                if( ( level = gone_time( who->get_save_2("advice.time") ) ) < 300 )    // 五分钟后
                {
                        send_user(who, "%c%s", '!', sprintf("%d 秒后才能再提建议.", 300 - level) );
                        return;
                }

                if( !arg || arg == "" )    // ##################################################
                {
                        if( who->get_save_2("advice.city2") != CITY_D->get_city_number(name2) )
                        {
                                send_user(who, "%c%s", '!', "您的纵横任务还没完成呢！");
                                return;
                        }
                        
                        number = who->get_save_2("advice.type");
                        city7 = who->get_save_2("advice.city");
                        if( city7 < 1 || city7 > 7 ) return;
                        if( city7 == who->get_save_2("advice.city2") ) return;

                        name4 = CITY_D->get_city_name(city7);
                        level = who->get_occupation_level();

                        switch( number )
                        {
                      default : // 修好
                                switch( city->get_save_2("policy.flag") )
                                {
                              default : rate = level / 2 + 1;  break;
                               case 1 : rate = (level / 2 + 1) * 2;  break;
                              case -1 : rate = (level / 2 + 1) / 2;  break;
                                }

                                if( random(100) < rate )
                                {
                                        send_user( who, "%c%s", ':', sprintf( "您：\n我代表%s前来，欲与贵国携手，共图王霸大业.\n\n\n"
                                                "%s：\n寡人求之不得，尊驾来得真是太好了.\n", name4, me->get_name() ) );

                                        who->add_occupation_exp(40);    // 书生经验 +40, 智谋 + 40
                                        who->add_gift_zm(40);
                                        cash = 0;  exp = 0;

                                        if( city2 = CITY_D->get_city_object_2(city7) ) 
                                        {
                                                cash = level * 50 + 500;
                                                if( city2->get_tax() < cash ) cash = city2->get_tax();
                                                if( cash < 0 ) cash = 0;
                                                who->add_cash(cash);  who->add_gold_log("task", cash);
                                                who->log_money("外交", cash);
						"/sys/sys/count"->add_income("task", cash);
                                                exp = level * 50 + 500;
                                                who->add_exp(exp);
                                                
                                                city2->add_tax(-cash);
                                                number = level / 10 + 1;
                                                city->add_friend( city7, number );
                                                city2->add_friend( CITY_D->get_city_number(name2), number );
                                        }

                                        send_user( who, "%c%w", 0x0d, MUSIC_TASK );
                                        write_user( who, ECHO "您的书生经验 +40, 智谋 +40, 金钱 %+d, 经验 %+d.", cash, exp );
                                }
                                else 
                                {
                                        send_user( who, "%c%s", ':', sprintf( "您：\n我代表%s前来，欲与贵国携手，共图王霸大业.\n\n\n"
                                                "%s：\n寡人没有结盟的意思，你的好意我心领了.\n", name4, me->get_name() ) );

                                        who->add_occupation_exp(1);

                                        write_user( who, ECHO "您的书生经验 +1." );
                                }

                                who->delete_save_2("advice");

                                break;

                       case 2 : // 问罪
                                switch( city->get_save_2("policy.flag") )
                                {
                              default : rate = level / 2 + 1;  break;
                               case 1 : rate = (level / 2 + 1) * 2;  break;
                              case -1 : rate = (level / 2 + 1) / 2;  break;
                                }

                                if( random(100) < rate )
                                {
                                        send_user( who, "%c%s", ':', sprintf( "您：\n我乃%s使节，尔等对我国恶意骚扰破坏，是何道理！\n\n\n"
                                                "%s：\n%s不愿臣服于我，自当略施小惩，你回去转告%s国主，尽快投降，以免自误.\n", 
                                                name4, me->get_name(), name4, name4 ) );

                                        who->add_occupation_exp(40);    // 书生经验 +40, 智谋 + 40
                                        who->add_gift_zm(40);
                                        cash = 0;  exp = 0;

                                        if( city2 = CITY_D->get_city_object_2(city7) ) 
                                        {
                                                cash = level * 50 + 500;
                                                if( city2->get_tax() < cash ) cash = city2->get_tax();
                                                if( cash < 0 ) cash = 0;
                                                who->add_cash(cash);  who->add_gold_log("task", cash);
						"/sys/sys/count"->add_income("task", cash);
						who->log_money("外交", cash);
                                                exp = level * 50 + 500;
                                                who->add_exp(exp);

                                                city2->add_tax(-cash);
                                                number = level / 10 + 1;
                                                city->add_friend( city7, -number );
                                                city2->add_friend( CITY_D->get_city_number(name2), -number );
                                        }

                                        send_user( who, "%c%w", 0x0d, MUSIC_TASK );
                                        write_user( who, ECHO "您的书生经验 +40, 智谋 +40, 金钱 %+d, 经验 %+d.", cash, exp );
                                }
                                else 
                                {
                                        send_user( who, "%c%s", ':', sprintf( "您：\n我乃%s使节，尔等对我国恶意骚扰破坏，是何道理！\n\n\n"
                                                "%s：\n哪来的家伙在这里无理取闹？快将他赶出去.\n", name4, me->get_name() ) );

                                        who->add_occupation_exp(1);

                                        write_user( who, ECHO "您的书生经验 +1." );
                                }

                                who->delete_save_2("advice");

                                break;
                        }

                        return;
                }

                if( who->get_save_2("advice.city") || who->get_save_2("advice.city2") )
                {
                        send_user(who, "%c%s", '!', "您的纵横任务还没完成呢！");
                        return;
                }

                if( me->get( sprintf("advice_%d", time() / 86400) ) >= 200 )
                {
                        send_user(who, "%c%s", '!', me->get_city_name() + "合纵连横次数太多了.");
                        return;
                }
                if( who->get_strength() < 1 )
                {
                        send_user(who, "%c%s", '!', "您现在的体力不够.");
                        return;
                }

                if( sscanf( arg, "?.%d.%d", number, city7 ) == 2 )    // ##################################################
                {
                        if( city7 < 1 || city7 > 7 ) return;

                        name4 = CITY_D->get_city_name(city7);

                        switch( number )
                        {
                      default : name3 = "修好";  break;
                       case 2 : name3 = "问罪";  break;
                        }

                        cmd1 = sprintf( "talk %x# advice.%d.%d\n", id, number, city7 );
                        send_user( who, "%c%s", ':', sprintf( "您确定建议%s对%s进行“%s”？\n", me->get_name(), name4, name3 ) + 
                                ESC "是的.\n" + cmd1 +
                                ESC "我再想想……\nCLOSE\n" );
                }
                else if( sscanf( arg, "%d.%d", number, city7 ) == 2 )    // ##################################################
                {
                        if( city7 < 1 || city7 > 7 ) return;
                        if( city7 == CITY_D->get_city_number(name2) ) return;

                        name4 = CITY_D->get_city_name(city7);
                        level = who->get_occupation_level();

                        switch( number )
                        {
                      default : // 修好
                                switch( city->get_save_2("policy.flag") )
                                {
                              default : rate = level / 3 + 20;  break;
                               case 1 : rate = (level / 3 + 20) * 2;  break;
                              case -1 : rate = (level / 3 + 20) / 2;  break;
                                }

                                if( random(100) < rate )
                                {
                                        send_user( who, "%c%s", ':', sprintf( "您：\n%s前有狼后有虎，只有和%s结盟方为上策.\n\n\n"
                                                "%s：\n阁下言之有理，我任命你为本国使节，前去%s共商结盟大计.\n", 
                                                name2, name4, me->get_name(), name4 ) );

                                        who->add_strength(-1);    // 体力 -1, 书生经验 +20, 智谋 + 20
                                        who->add_occupation_exp(20);
                                        who->add_gift_zm(20);
                                        who->add_exp(level * 10 + 200);

                                        who->set_save_2( "advice.city", CITY_D->get_city_number(name2) );
                                        who->set_save_2( "advice.city2", city7 );
                                        who->set_save_2( "advice.type", number );

                                        send_user( who, "%c%w", 0x0d, MUSIC_TASK );
                                        write_user( who, ECHO "您的书生经验 +20, 智谋 +20, 经验 %+d.", level * 10 + 200 );
                                }
                                else 
                                {
                                        send_user( who, "%c%s", ':', sprintf( "您：\n%s前有狼后有虎，只有和%s结盟方为上策.\n\n\n"
                                                "%s：\n我国兵力强盛，国富民强，没必要畏惧其他国家，休得危言耸听！\n", 
                                                name2, name4, me->get_name() ) );

                                        who->add_strength(-1);    // 体力 -1, 书生经验 +1
                                        who->add_occupation_exp(1);

                                        who->set_save_2( "advice.time", time() );

                                        write_user( who, ECHO "您的书生经验 +1." );
                                }

                                me->add( sprintf("advice_%d", time() / 86400), 1);

                                break;

                       case 2 : // 问罪
                                switch( city->get_save_2("policy.flag") )
                                {
                              default : rate = level / 3 + 20;  break;
                               case 1 : rate = (level / 3 + 20) * 2;  break;
                              case -1 : rate = (level / 3 + 20) / 2;  break;
                                }

                                if( random(100) < rate )
                                {
                                        send_user( who, "%c%s", ':', sprintf( "您：\n%s在密谋对%s不利，已经多次派人来搞破坏了.\n\n\n"
                                                "%s：\n竟然有这等事？我派你去警告%s立即收敛这种行为.\n", 
                                                name4, name2, me->get_name(), name4 ) );

                                        who->add_strength(-1);    // 体力 -1, 书生经验 +20, 智谋 + 20
                                        who->add_occupation_exp(20);
                                        who->add_gift_zm(20);
                                        who->add_exp(level * 10 + 200);

                                        who->set_save_2( "advice.city", CITY_D->get_city_number(name2) );
                                        who->set_save_2( "advice.city2", city7 );
                                        who->set_save_2( "advice.type", number );

                                        send_user( who, "%c%w", 0x0d, MUSIC_TASK );
                                        write_user( who, ECHO "您的书生经验 +20, 智谋 +20, 经验 %+d.", level * 10 + 200 );
                                }
                                else 
                                {
                                        send_user( who, "%c%s", ':', sprintf( "您：\n%s在密谋对%s不利，已经多次派人来搞破坏了.\n\n\n"
                                                "%s：\n有这回事吗？我可没有收到这种消息.\n", 
                                                name4, name2, me->get_name() ) );

                                        who->add_strength(-1);    // 体力 -1, 书生经验 +1
                                        who->add_occupation_exp(1);

                                        who->set_save_2( "advice.time", time() );

                                        write_user( who, ECHO "您的书生经验 +1." );
                                }

                                me->add( sprintf("advice_%d", time() / 86400), 1);

                                break;
                        }
                }
                else if( number = to_int(arg) )    // ##################################################
                {
                        switch( number )
                        {
                      default : name3 = "修好";  break;
                       case 2 : name3 = "问罪";  break;
                        }

                        switch( name2 )
                        {
                      default : cmd1 = sprintf( "talk %x# advice.?.%d.2\n", id, number );
                                cmd2 = sprintf( "talk %x# advice.?.%d.3\n", id, number );
                                cmd3 = sprintf( "talk %x# advice.?.%d.4\n", id, number );
                                cmd4 = sprintf( "talk %x# advice.?.%d.5\n", id, number );
                                cmd5 = sprintf( "talk %x# advice.?.%d.6\n", id, number );
                                cmd6 = sprintf( "talk %x# advice.?.%d.7\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国进行“%s”？\n", me->get_name(), name3 ) + 
                                        ESC "Hàn Quốc.\n" + cmd1 +
                                        ESC "Triệu Quốc.\n" + cmd2 +
                                        ESC "Ngụy Quốc.\n" + cmd3 +
                                        ESC "Tần Quốc.\n" + cmd4 +
                                        ESC "Sở Quốc.\n" + cmd5 +
                                        ESC "Yên Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                  case "Hàn Quốc" : cmd1 = sprintf( "talk %x# advice.?.%d.1\n", id, number );
                                cmd2 = sprintf( "talk %x# advice.?.%d.3\n", id, number );
                                cmd3 = sprintf( "talk %x# advice.?.%d.4\n", id, number );
                                cmd4 = sprintf( "talk %x# advice.?.%d.5\n", id, number );
                                cmd5 = sprintf( "talk %x# advice.?.%d.6\n", id, number );
                                cmd6 = sprintf( "talk %x# advice.?.%d.7\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国进行“%s”？\n", me->get_name(), name3 ) + 
                                        ESC "Tề Quốc.\n" + cmd1 +
                                        ESC "Triệu Quốc.\n" + cmd2 +
                                        ESC "Ngụy Quốc.\n" + cmd3 +
                                        ESC "Tần Quốc.\n" + cmd4 +
                                        ESC "Sở Quốc.\n" + cmd5 +
                                        ESC "Yên Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                  case "Triệu Quốc" : cmd1 = sprintf( "talk %x# advice.?.%d.1\n", id, number );
                                cmd2 = sprintf( "talk %x# advice.?.%d.2\n", id, number );
                                cmd3 = sprintf( "talk %x# advice.?.%d.4\n", id, number );
                                cmd4 = sprintf( "talk %x# advice.?.%d.5\n", id, number );
                                cmd5 = sprintf( "talk %x# advice.?.%d.6\n", id, number );
                                cmd6 = sprintf( "talk %x# advice.?.%d.7\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国进行“%s”？\n", me->get_name(), name3 ) + 
                                        ESC "Tề Quốc.\n" + cmd1 +
                                        ESC "Hàn Quốc.\n" + cmd2 +
                                        ESC "Ngụy Quốc.\n" + cmd3 +
                                        ESC "Tần Quốc.\n" + cmd4 +
                                        ESC "Sở Quốc.\n" + cmd5 +
                                        ESC "Yên Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                  case "Ngụy Quốc" : cmd1 = sprintf( "talk %x# advice.?.%d.1\n", id, number );
                                cmd2 = sprintf( "talk %x# advice.?.%d.2\n", id, number );
                                cmd3 = sprintf( "talk %x# advice.?.%d.3\n", id, number );
                                cmd4 = sprintf( "talk %x# advice.?.%d.5\n", id, number );
                                cmd5 = sprintf( "talk %x# advice.?.%d.6\n", id, number );
                                cmd6 = sprintf( "talk %x# advice.?.%d.7\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国进行“%s”？\n", me->get_name(), name3 ) + 
                                        ESC "Tề Quốc.\n" + cmd1 +
                                        ESC "Hàn Quốc.\n" + cmd2 +
                                        ESC "Triệu Quốc.\n" + cmd3 +
                                        ESC "Tần Quốc.\n" + cmd4 +
                                        ESC "Sở Quốc.\n" + cmd5 +
                                        ESC "Yên Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                  case "Tần Quốc" : cmd1 = sprintf( "talk %x# advice.?.%d.1\n", id, number );
                                cmd2 = sprintf( "talk %x# advice.?.%d.2\n", id, number );
                                cmd3 = sprintf( "talk %x# advice.?.%d.3\n", id, number );
                                cmd4 = sprintf( "talk %x# advice.?.%d.4\n", id, number );
                                cmd5 = sprintf( "talk %x# advice.?.%d.6\n", id, number );
                                cmd6 = sprintf( "talk %x# advice.?.%d.7\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国进行“%s”？\n", me->get_name(), name3 ) + 
                                        ESC "Tề Quốc.\n" + cmd1 +
                                        ESC "Hàn Quốc.\n" + cmd2 +
                                        ESC "Triệu Quốc.\n" + cmd3 +
                                        ESC "Ngụy Quốc.\n" + cmd4 +
                                        ESC "Sở Quốc.\n" + cmd5 +
                                        ESC "Yên Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                  case "Sở Quốc" : cmd1 = sprintf( "talk %x# advice.?.%d.1\n", id, number );
                                cmd2 = sprintf( "talk %x# advice.?.%d.2\n", id, number );
                                cmd3 = sprintf( "talk %x# advice.?.%d.3\n", id, number );
                                cmd4 = sprintf( "talk %x# advice.?.%d.4\n", id, number );
                                cmd5 = sprintf( "talk %x# advice.?.%d.5\n", id, number );
                                cmd6 = sprintf( "talk %x# advice.?.%d.7\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国进行“%s”？\n", me->get_name(), name3 ) + 
                                        ESC "Tề Quốc.\n" + cmd1 +
                                        ESC "Hàn Quốc.\n" + cmd2 +
                                        ESC "Triệu Quốc.\n" + cmd3 +
                                        ESC "Ngụy Quốc.\n" + cmd4 +
                                        ESC "Tần Quốc.\n" + cmd5 +
                                        ESC "Yên Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                  case "Yên Quốc" : cmd1 = sprintf( "talk %x# advice.?.%d.1\n", id, number );
                                cmd2 = sprintf( "talk %x# advice.?.%d.2\n", id, number );
                                cmd3 = sprintf( "talk %x# advice.?.%d.3\n", id, number );
                                cmd4 = sprintf( "talk %x# advice.?.%d.4\n", id, number );
                                cmd5 = sprintf( "talk %x# advice.?.%d.5\n", id, number );
                                cmd6 = sprintf( "talk %x# advice.?.%d.6\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国进行“%s”？\n", me->get_name(), name3 ) + 
                                        ESC "Tề Quốc.\n" + cmd1 +
                                        ESC "Hàn Quốc.\n" + cmd2 +
                                        ESC "Triệu Quốc.\n" + cmd3 +
                                        ESC "Ngụy Quốc.\n" + cmd4 +
                                        ESC "Tần Quốc.\n" + cmd5 +
                                        ESC "Sở Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                        }
                }
        }
}
