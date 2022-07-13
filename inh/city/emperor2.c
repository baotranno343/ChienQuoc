// emperor 君主，皇帝 - 外交／战争

#include <ansi.h>

// 函数：外交处理
void do_relation( object who, object me, string arg )
{
        object city, city2;
        string name1, name2, name3, name4, result;
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6;
        int id, number, city0, city7;

        id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2 
        &&      who->get_id() == me->get_master()
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( !arg || arg == "?" )    // ##################################################
                {
                        if( !city->get_save_2("war.city") )    // 没有战争
                        {
                                cmd1 = sprintf( "talk %x# relation.1\n", id );
                                cmd2 = sprintf( "talk %x# relation.2\n", id );
                                cmd3 = sprintf( "talk %x# relation.3\n", id );
                                cmd4 = sprintf( "talk %x# relation.4\n", id );
                                cmd5 = sprintf( "talk %x# relation.5\n", id );
                                send_user( who, "%c%s", ':', "您想建议" + me->get_name() + "实行哪种外交策略？(消耗 50 体力)\n"
                                        ESC "亲善外交.\n" + cmd1 +
                                        ESC "敌对外交.\n" + cmd2 +
                                        ESC "同盟.\n" + cmd3 +
                                        ESC "废弃同盟.\n" + cmd4 +
                                        ESC "发动战争.(100 体力)\n" + cmd5 +
                                        ESC "我再想想……\nCLOSE\n" );
                        }
                        else if( city->get_save_2("war.attack") )    // 发动战争
                        {
                                city7 = city->get_save_2("war.city");
                                if( city7 < 1 || city7 > 7 ) return;

                                name4 = CITY_D->get_city_name(city7);

                                cmd1 = sprintf( "talk %x# relation.1\n", id );
                                cmd2 = sprintf( "talk %x# relation.2\n", id );
                                cmd3 = sprintf( "talk %x# relation.3\n", id );
                                cmd4 = sprintf( "talk %x# relation.4\n", id );
                                send_user( who, "%c%s", ':', "您想建议" + me->get_name() + "实行哪种外交策略？(消耗 50 体力)\n"
                                        + sprintf("%s已经向%s宣战！\n", me->get_name(), name4) +
                                        ESC "亲善外交.\n" + cmd1 +
                                        ESC "敌对外交.\n" + cmd2 +
                                        ESC "同盟.\n" + cmd3 +
                                        ESC "废弃同盟.\n" + cmd4 +
                                        ESC "我再想想……\nCLOSE\n" );
                        }
                        else    // 响应战争
                        {
                                city7 = city->get_save_2("war.city");
                                if( city7 < 1 || city7 > 7 ) return;

                                name4 = CITY_D->get_city_name(city7);

                                cmd1 = sprintf( "talk %x# relation.1\n", id );
                                cmd2 = sprintf( "talk %x# relation.2\n", id );
                                cmd3 = sprintf( "talk %x# relation.3\n", id );
                                cmd4 = sprintf( "talk %x# relation.4\n", id );
                                cmd5 = sprintf( "talk %x# relation.?.6.%d\n", id, city7 );
                                cmd6 = sprintf( "talk %x# relation.?.7.%d\n", id, city7 );
                                send_user( who, "%c%s", ':', "您想建议" + me->get_name() + "实行哪种外交策略？(消耗 50 体力)\n"
                                        + sprintf("%s已经向%s宣战！\n", name4, me->get_name() ) +
                                        ESC "亲善外交.\n" + cmd1 +
                                        ESC "敌对外交.\n" + cmd2 +
                                        ESC "同盟.\n" + cmd3 +
                                        ESC "废弃同盟.\n" + cmd4 +
                                        ESC "抵抗入侵.(0 体力)\n" + cmd5 +
                                        ESC "投降.(0 体力)\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                        }
                }
                else if( sscanf( arg, "?.%d.%d", number, city7 ) == 2 )    // ##################################################
                {
                        if( city7 < 1 || city7 > 7 ) return;

                        name4 = CITY_D->get_city_name(city7);

                        if( !city->get_save_2("war.city") )    // 没有战争
                        {
                                switch( number )
                                {
                              default : name3 = "亲善外交";  break;
                               case 2 : name3 = "敌对外交";  break;
                               case 3 : name3 = "同盟";  break;
                               case 4 : name3 = "废弃同盟";  break;
                               case 5 : name3 = "发动战争";  break;
                                }
                        }
                        else if( city->get_save_2("war.attack") )    // 发动战争
                        {
                                switch( number )
                                {
                              default : name3 = "亲善外交";  break;
                               case 2 : name3 = "敌对外交";  break;
                               case 3 : name3 = "同盟";  break;
                               case 4 : name3 = "废弃同盟";  break;
                                }
                        }
                        else    // 响应战争
                        {
                                switch( number )
                                {
                              default : name3 = "亲善外交";  break;
                               case 2 : name3 = "敌对外交";  break;
                               case 3 : name3 = "同盟";  break;
                               case 4 : name3 = "废弃同盟";  break;
                               case 6 : name3 = "抵抗入侵";  break;
                               case 7 : name3 = "投降";  break;
                                }
                        }

                        cmd1 = sprintf( "talk %x# relation.%d.%d\n", id, number, city7 );
                        send_user( who, "%c%s", ':', sprintf( "您确定建议%s对%s实行“%s”外交策略？\n", me->get_name(), name4, name3 ) + 
                                ESC "是的.\n" + cmd1 +
                                ESC "我再想想……\nCLOSE\n" );
                }
                else if( sscanf( arg, "%d.%d", number, city7 ) == 2 )    // ##################################################
                {
                        if( city7 < 1 || city7 > 7 ) return;
                        if( !( city2 = CITY_D->get_city_object_2(city7) ) ) return;

                        city0 = CITY_D->get_city_number(name2);
                        name4 = CITY_D->get_city_name(city7);

                        switch( number )
                        {
                      default : name3 = "亲善外交";  break;
                       case 2 : name3 = "敌对外交";  break;
                       case 3 : name3 = "同盟";  break;
                       case 4 : name3 = "废弃同盟";  break;
//                     case 5 : name3 = "发动战争";  break;
//                     case 6 : name3 = "抵抗入侵";  break;
//                     case 7 : name3 = "投降";  break;
                        }

                        switch( number )
                        {
                      default : // 亲善外交
                                if( who->get_strength() < 50 )
                                {
                                        send_user(who, "%c%s", '!', "制定外交策略要 50 点体力.");
                                        return;
                                }
                                if( city->get_save_2("relation.flag") )
                                {
                                        send_user(who, "%c%s", '!', "还有没完成的外交任务.");
                                        return;
                                }
                                city->set_save_2("relation.flag", 1);
                                city->set_save_2("relation.city", city7);

                                result = sprintf( HIY "%s对%s实行“%s”外交策略，欢迎到使节处领取任务.", me->get_name(), name4, name3 );
                                FAMILY_D->city_channel(name2, 0, result);

                                who->add_strength(-50);
                                break;

                       case 2 : // 敌对外交
                                if( who->get_strength() < 50 )
                                {
                                        send_user(who, "%c%s", '!', "制定外交策略要 50 点体力.");
                                        return;
                                }
                                if( city->get_save_2("relation.flag") )
                                {
                                        send_user(who, "%c%s", '!', "还有没完成的外交任务.");
                                        return;
                                }
                                city->set_save_2("relation.flag", 2);
                                city->set_save_2("relation.city", city7);

                                result = sprintf( HIY "%s对%s实行“%s”外交策略，欢迎到使节处领取任务.", me->get_name(), name4, name3 );
                                FAMILY_D->city_channel(name2, 0, result);

                                who->add_strength(-50);
                                break;

                       case 3 : // 同盟
                                if( who->get_strength() < 50 )
                                {
                                        send_user(who, "%c%s", '!', "同盟要 50 点体力.");
                                        return;
                                }
                                if( city->get_relation(city7) == 2 )
                                {
                                        send_user(who, "%c%s", '!', sprintf("%s与%s已经是同盟了.", name2, name4) );
                                        return;
                                }
                                if( city->get_relation(city7) == -2 )
                                {
                                        send_user(who, "%c%s", '!', sprintf("%s与%s正在交战！", name2, name4) );
                                        return;
                                }
                                if( city->get_friend(city7) < 300 )
                                {
                                        send_user(who, "%c%s", '!', "友好度高于 300 才能同盟！");
                                        return;
                                }

                                city->set_relation(city7, 2);    // 以后要对方确认
                                city2->set_relation(city0, 2);

                                result = sprintf( HIY "%s开始对%s实行“%s”外交策略.", me->get_name(), name4, name3 );
                                FAMILY_D->city_channel(name2, 0, result);

                                who->add_strength(-50);
                                break;

                       case 4 : // 废弃同盟
                                if( who->get_strength() < 50 )
                                {
                                        send_user(who, "%c%s", '!', "废弃同盟要 50 点体力.");
                                        return;
                                }
                                if( city->get_relation(city7) != 2 )
                                {
                                        send_user(who, "%c%s", '!', sprintf("%s与%s没有同盟.", name2, name4) );
                                        return;
                                }
                                if( city->get_friend(city7) > 300 )
                                {
                                        send_user(who, "%c%s", '!', "友好度低于 300 才能解盟！");
                                        return;
                                }

                                city->set_relation(city7, 0);
                                city2->set_relation(city0, 0);

                                result = sprintf( HIY "%s开始对%s实行“%s”外交策略.", me->get_name(), name4, name3 );
                                FAMILY_D->city_channel(name2, 0, result);

                                who->add_strength(-50);
                                break;

                       case 5 : // 发动战争
                                if( who->get_strength() < 100 )
                                {
                                        send_user(who, "%c%s", '!', "发动战争要 100 点体力.");
                                        return;
                                }
                                if( city->get_relation(city7) == 2 )
                                {
                                        send_user(who, "%c%s", '!', sprintf("%s与%s还在同盟！", name2, name4) );
                                        return;
                                }
                                if( city->get_friend(city7) > -300 )
                                {
                                        send_user(who, "%c%s", '!', "友好度低于 -300 才能开战！");
                                        return;
                                }
                                if( city->get_save_2("war.city") )
                                {
                                        send_user(who, "%c%s", '!', "贵国正同别国交战！");
                                        return;
                                }
                                if( city2->get_save_2("war.city") )
                                {
                                        send_user(who, "%c%s", '!', name4 + "正同别国交战！");
                                        return;
                                }

                                city->set_save_2( "war.city", city7 );
                                city->set_save_2( "war.start", time() );
                                city->set_save_2( "war.attack", 1 );
                                city2->set_save_2( "war.city", city0 );
                                city2->set_save_2( "war.start", time() );

                                city->set_relation(city7, -2);
                                city2->set_relation(city0, -2);

                                result = sprintf( HIY "%s诏曰：“%s多行不义，我等奉周王之命伐之.”", me->get_name(), name4 );
                                FAMILY_D->city_channel(name2, 0, result);
                                FAMILY_D->city_channel(name4, 0, result + "(限６小时回应)");

                                who->add_strength(-100);
                                break;

                       case 6 : // 抵抗入侵
                                if( city->get_save_2("war.city") != city7 )
                                {
                                        send_user(who, "%c%s", '!', name4 + "没有入侵贵国！");
                                        return;
                                }
                                if( city->get_save_2("war.attack") )
                                {
                                        send_user(who, "%c%s", '!', "没有国家入侵贵国！");
                                        return;
                                }

                                // city->delete_save_2("war");
                                // city2->delete_save_2("war");

                                // city->set_relation(city7, -1);
                                // city2->set_relation(city0, -1);

                                result = sprintf( HIY "%s诏曰：“%s为一己之私侵犯我国，我等上下一心，将严阵以待.”", me->get_name(), name4 );
                                FAMILY_D->city_channel(name2, 0, result);
                                FAMILY_D->city_channel(name4, 0, result);

                                break;

                       case 7 : // 投降
                                if( city->get_save_2("war.city") != city7 )
                                {
                                        send_user(who, "%c%s", '!', name4 + "没有入侵贵国！");
                                        return;
                                }
                                if( city->get_save_2("war.attack") )
                                {
                                        send_user(who, "%c%s", '!', "没有国家入侵贵国！");
                                        return;
                                }
                                if( city->get_save_2("war.surrender") )
                                {
                                        send_user(who, "%c%s", '!', "只多只能投降一次！");
                                        return;
                                }

                                if( random(100) > 10 + who->get_level() / 4 )
                                {
                                        send_user( who, "%c%s", ':', me->get_name() + "愤然拒绝了您的投降建议！" );

                                        city->set_save_2("war.surrender", 1);    // 投降标志
                                        return;
                                }

                                city->delete_save_2("war");
                                city2->delete_save_2("war");

                                city->set_relation(city7, -1);
                                city2->set_relation(city0, -1);

                                result = sprintf( HIY "%s诏曰：“%s为一己之私侵犯我国，我等欲卧薪尝胆，以图后报.”", me->get_name(), name4 );
                                FAMILY_D->city_channel(name2, 0, result);
                                FAMILY_D->city_channel(name4, 0, result);

                                break;
                        }
                }
                else if( number = to_int(arg) )    // ##################################################
                {
                        switch( number )
                        {
                      default : name3 = "亲善外交";  break;
                       case 2 : name3 = "敌对外交";  break;
                       case 3 : name3 = "同盟";  break;
                       case 4 : name3 = "废弃同盟";  break;
                       case 5 : name3 = "发动战争";  break;
                        }

                        switch( name2 )
                        {
                      default : cmd1 = sprintf( "talk %x# relation.?.%d.2\n", id, number );
                                cmd2 = sprintf( "talk %x# relation.?.%d.3\n", id, number );
                                cmd3 = sprintf( "talk %x# relation.?.%d.4\n", id, number );
                                cmd4 = sprintf( "talk %x# relation.?.%d.5\n", id, number );
                                cmd5 = sprintf( "talk %x# relation.?.%d.6\n", id, number );
                                cmd6 = sprintf( "talk %x# relation.?.%d.7\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国实行“%s”外交策略？\n", me->get_name(), name3 ) + 
                                        ESC "Hàn Quốc.\n" + cmd1 +
                                        ESC "Triệu Quốc.\n" + cmd2 +
                                        ESC "Ngụy Quốc.\n" + cmd3 +
                                        ESC "Tần Quốc.\n" + cmd4 +
                                        ESC "Sở Quốc.\n" + cmd5 +
                                        ESC "Yên Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                  case "Hàn Quốc" : cmd1 = sprintf( "talk %x# relation.?.%d.1\n", id, number );
                                cmd2 = sprintf( "talk %x# relation.?.%d.3\n", id, number );
                                cmd3 = sprintf( "talk %x# relation.?.%d.4\n", id, number );
                                cmd4 = sprintf( "talk %x# relation.?.%d.5\n", id, number );
                                cmd5 = sprintf( "talk %x# relation.?.%d.6\n", id, number );
                                cmd6 = sprintf( "talk %x# relation.?.%d.7\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国实行“%s”外交策略？\n", me->get_name(), name3 ) + 
                                        ESC "Tề Quốc.\n" + cmd1 +
                                        ESC "Triệu Quốc.\n" + cmd2 +
                                        ESC "Ngụy Quốc.\n" + cmd3 +
                                        ESC "Tần Quốc.\n" + cmd4 +
                                        ESC "Sở Quốc.\n" + cmd5 +
                                        ESC "Yên Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                  case "Triệu Quốc" : cmd1 = sprintf( "talk %x# relation.?.%d.1\n", id, number );
                                cmd2 = sprintf( "talk %x# relation.?.%d.2\n", id, number );
                                cmd3 = sprintf( "talk %x# relation.?.%d.4\n", id, number );
                                cmd4 = sprintf( "talk %x# relation.?.%d.5\n", id, number );
                                cmd5 = sprintf( "talk %x# relation.?.%d.6\n", id, number );
                                cmd6 = sprintf( "talk %x# relation.?.%d.7\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国实行“%s”外交策略？\n", me->get_name(), name3 ) + 
                                        ESC "Tề Quốc.\n" + cmd1 +
                                        ESC "Hàn Quốc.\n" + cmd2 +
                                        ESC "Ngụy Quốc.\n" + cmd3 +
                                        ESC "Tần Quốc.\n" + cmd4 +
                                        ESC "Sở Quốc.\n" + cmd5 +
                                        ESC "Yên Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                  case "Ngụy Quốc" : cmd1 = sprintf( "talk %x# relation.?.%d.1\n", id, number );
                                cmd2 = sprintf( "talk %x# relation.?.%d.2\n", id, number );
                                cmd3 = sprintf( "talk %x# relation.?.%d.3\n", id, number );
                                cmd4 = sprintf( "talk %x# relation.?.%d.5\n", id, number );
                                cmd5 = sprintf( "talk %x# relation.?.%d.6\n", id, number );
                                cmd6 = sprintf( "talk %x# relation.?.%d.7\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国实行“%s”外交策略？\n", me->get_name(), name3 ) + 
                                        ESC "Tề Quốc.\n" + cmd1 +
                                        ESC "Hàn Quốc.\n" + cmd2 +
                                        ESC "Triệu Quốc.\n" + cmd3 +
                                        ESC "Tần Quốc.\n" + cmd4 +
                                        ESC "Sở Quốc.\n" + cmd5 +
                                        ESC "Yên Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                  case "Tần Quốc" : cmd1 = sprintf( "talk %x# relation.?.%d.1\n", id, number );
                                cmd2 = sprintf( "talk %x# relation.?.%d.2\n", id, number );
                                cmd3 = sprintf( "talk %x# relation.?.%d.3\n", id, number );
                                cmd4 = sprintf( "talk %x# relation.?.%d.4\n", id, number );
                                cmd5 = sprintf( "talk %x# relation.?.%d.6\n", id, number );
                                cmd6 = sprintf( "talk %x# relation.?.%d.7\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国实行“%s”外交策略？\n", me->get_name(), name3 ) + 
                                        ESC "Tề Quốc.\n" + cmd1 +
                                        ESC "Hàn Quốc.\n" + cmd2 +
                                        ESC "Triệu Quốc.\n" + cmd3 +
                                        ESC "Ngụy Quốc.\n" + cmd4 +
                                        ESC "Sở Quốc.\n" + cmd5 +
                                        ESC "Yên Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                  case "Sở Quốc" : cmd1 = sprintf( "talk %x# relation.?.%d.1\n", id, number );
                                cmd2 = sprintf( "talk %x# relation.?.%d.2\n", id, number );
                                cmd3 = sprintf( "talk %x# relation.?.%d.3\n", id, number );
                                cmd4 = sprintf( "talk %x# relation.?.%d.4\n", id, number );
                                cmd5 = sprintf( "talk %x# relation.?.%d.5\n", id, number );
                                cmd6 = sprintf( "talk %x# relation.?.%d.7\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国实行“%s”外交策略？\n", me->get_name(), name3 ) + 
                                        ESC "Tề Quốc.\n" + cmd1 +
                                        ESC "Hàn Quốc.\n" + cmd2 +
                                        ESC "Triệu Quốc.\n" + cmd3 +
                                        ESC "Ngụy Quốc.\n" + cmd4 +
                                        ESC "Tần Quốc.\n" + cmd5 +
                                        ESC "Yên Quốc.\n" + cmd6 +
                                        ESC "我再想想……\nCLOSE\n" );
                                break;
                  case "Yên Quốc" : cmd1 = sprintf( "talk %x# relation.?.%d.1\n", id, number );
                                cmd2 = sprintf( "talk %x# relation.?.%d.2\n", id, number );
                                cmd3 = sprintf( "talk %x# relation.?.%d.3\n", id, number );
                                cmd4 = sprintf( "talk %x# relation.?.%d.4\n", id, number );
                                cmd5 = sprintf( "talk %x# relation.?.%d.5\n", id, number );
                                cmd6 = sprintf( "talk %x# relation.?.%d.6\n", id, number );
                                send_user( who, "%c%s", ':', sprintf( "您想建议%s对哪国实行“%s”外交策略？\n", me->get_name(), name3 ) + 
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
