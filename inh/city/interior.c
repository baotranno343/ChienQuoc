// ministry of interior 内政官

#include <ansi.h>
#include <music.h>

#define RASCAL          "/npc/task/8820"
#define BUILD_FILE      "/quest/build"

void do_build_finish( object who, object me );

// 函数：增添对话菜单
void more_look_menu( object who, object me, string text )
{
        object city;
        string name, result = "\n";
        int number, p, id;

        id = getoid(me);

        if( ( city = CITY_D->get_city_object(who) ) && ( number = city->get_save_2("build.flag") ) )
        {
                p = city->get_save_2("build.work");

                switch( number )
                {
              default : name = "城防";  p /= 10;  break;
               case 2 : name = "农业";  p /= 5;  break;
               case 3 : name = "渔业";  p /= 5;  break;
               case 4 : name = "矿业";  p /= 5;  break;
               case 5 : name = "工业";  p /= 5;  break;
               case 6 : name = "商业";  p /= 5;  break;
               case 7 : name = "艺术";  p /= 5;  break;
               case 8 : name = "教育";  p /= 5;  break;
               case 9 : name = "宗教";  p /= 5;  break;
                }

                result += sprintf( ESC "领取建设任务.(%s %d%%)\ntalk %x# build\n", name, p, id );
        }
        if( who->is_farmer() && !present("种子", who, 1, MAX_CARRY) )
        {
                result += sprintf( ESC "领取种子播种.\ntalk %x# plant\n", id );
        }
        else if( who->is_businessman() )
        {
                result += sprintf( ESC "领取军粮任务.\ntalk %x# food\n", id );
        }

        if( result == "" )
        {
                send_user( who, "%c%s", ':', text );
                return;
        }

        if( strlen(text) > 10 && text[<6..<1] == "CLOSE\n" )    // 有关闭选择
        {
                if( p = strchr(text, 27, -1) )    // ESC
                        send_user( who, "%c%s", ':', sprintf( "%s%s%s", text[0..p-1], result, text[p..<1] ) );
                else    send_user( who, "%c%s", ':', text + result );
        }
        else    send_user( who, "%c%s", ':', sprintf( "%s%s%s", text, result, ESC "离开.\nCLOSE\n" ) );
}

// 函数：对话处理
void do_look( object who, object me )
{
        string name1, name2;
        string cmd1;
        int id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if( stringp(name1) && stringp(name2) && name1 == name2 )
        {
                if( who->get_id() == me->get_master() || who->get_id() == me->get_master_2() || who->get_id() == me->get_master_3() )
                {
                        cmd1 = sprintf( "talk %x# build.?\n", id );
                        more_look_menu( who, me, me->get_name() + "：\n    "+"/quest/word"->get_country_word(me)+"\n    " + who->get_name() + "阁下，您有什么事情？\n" 
                                ESC "发布建设任务.\n" + cmd1 +
                                ESC "离开.\nCLOSE\n" );
                }
                else    more_look_menu( who, me, me->get_name() + "：\n    "+"/quest/word"->get_country_word(me) );
        }
        else
        {
                send_user( who, "%c%s", ':', me->get_name() + "：\n    "+"/quest/word"->get_country_word(me) );
        }
}

// 函数：发放种子
void do_plant( object who, object me, string arg )
{
        object obj;
        string name1, name2;
        int p;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if( stringp(name1) && stringp(name2) && name1 == name2 )
        {
                if( !who->is_farmer() )
                {
                        send_user(who, "%c%s", '!', "您不是农夫要种子干嘛？");
                        return;
                }
                if( sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY )
                {
                        send_user(who, "%c%s", '!', "您携带的东西太多了.");
                        return;
                }
                if( present("种子", who, 1, MAX_CARRY) )
                {
                        send_user(who, "%c%s", '!', "您已经领了种子了.");
                        return;
                }

                obj = new("/item/92/9210");

                send_user( who, "%c%s", ':', sprintf( "%s：\n这里是一%s%s，我们在城外找了块好地，您赶快过去耕种吧.", 
                        me->get_name(), obj->get_unit(), obj->get_name() ) );

                if( p = obj->move(who, -1) ) obj->add_to_user(p);
                else destruct(obj);
        }
}

// 函数：军粮任务
void do_food( object who, object me, string arg )
{
        object city;
        string name1, name2;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&      who->is_businessman()
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( city->get_food() >= city->get_soldier() * 10 )
                {
                        send_user( who, "%c%s", ':', me->get_name() + "：\n城里军粮已经足够了，不需要再购买了.\n" );
                        return;
                }
                if( who->get("trader.food") )
                {
                        send_user( who, "%c%s", ':', me->get_name() + "：\n你去各国调查一下，看哪里能买到军粮？\n" );
                        return;
                }
                if( who->get_strength() < 1 )
                {
                        send_user(who, "%c%s", '!', "您现在的体力不够.");
                        return;
                }

                who->set("trader.food", 1);
                send_user( who, "%c%s", ':', me->get_name() + "：\n你去各国调查一下，看哪里能买到军粮？\n" );
        }
}

// 函数：建设任务
void do_build( object who, object me, string arg )
{
        object city, map, npc, obj;
        string name1, name2, name3, result;
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7, cmd8, cmd9;
        int level;
        int z, x, y, p;
        int number, id;

        id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( !arg )    // 领取任务 ##################################################
                {
                        if( p = who->get_save_2("build.flag") ) switch( p )    // 40 分钟
                        {
                      default : if(     stringp( name3 = who->get_task("rascal2") ) 
                                &&    ( npc = find_char(name3) ) && npc->is_rascal_2() )
                                {
                                        send_user(who, "%c%s", '!', "您还有未完成的建设任务.");
                                        return;
                                }
                                break;

                       case 2 : case 3 : case 4 :
                                if( gone_time( who->get_save_2("build.time") ) < 2400 )
                                {
                                        send_user(who, "%c%s", '!', "您还有未完成的建设任务.");
                                        return;
                                }
                                break;
                        }
                        
                        if( who->get_strength() < 1 )
                        {
                                send_user(who, "%c%s", '!', "建设任务要 1 点体力.");
                                return;
                        }

                        switch( random(4) + 1 )
                        {
                      default : if( !( p = city->get_xy_point(IS_CHAR_BLOCK) ) ) return;

                                z = p / 1000000;  x = ( p % 1000000 ) / 1000;  y = p % 1000;

                                if( !objectp( map = get_map_object(z) ) || !map->is_scene() ) return;

                                npc = new( RASCAL );
                                level = who->get_level() - random(6);
                                if( level < 0 ) level = 0;
                                NPC_ENERGY_D->init_level(npc, level);
                                npc->add_max_hp(750);
                                npc->add_dp( level * 5 / 10 );
                                npc->add_pp( level * 15 / 10 );
                                npc->add_to_scene(z, x, y, 3);

                                npc->set( "user", ({ sprintf( "%d", who->get_number() ) }) );
                                map->add_reset(npc);    // 加入复位列表

                                npc->set_city_name(name1);
                                who->set_task("rascal2", sprintf( "%x#", getoid(npc) ) );

                                npc->set( "task", who->get_number() );
                                npc->set("xy.z", z);
                                npc->set("xy.x", x);
                                npc->set("xy.y", y);

                                send_user( who, "%c%s", ':', sprintf( "%s：\n城中正在施工，却有%s在%s（%d,%d）捣乱，影响进度，请阁下去维护秩序.\n", 
                                        me->get_name(), npc->get_name(), map->get_name(), x, y ) );

                                who->delete_save_2("build");
                                who->set_save_2("build.flag", 1);
                                who->set_save_2("build.time", time() );

                                break;

                       case 2 : send_user( who, "%c%s", ':', sprintf( "%s：\n城中建设繁忙，你去财政官那儿帮手算几天帐吧.\n", me->get_name() ) );

                                who->delete_save_2("build");
                                who->set_save_2("build.flag", 2);
                                who->set_save_2("build.time", time() );

                                break;

                       case 3 : send_user( who, "%c%s", ':', sprintf( "%s：\n你来得正好，我正要送四份食物到城中四处的工地上.\n", me->get_name() ) );

                                if( sizeof_inventory(who, 1, MAX_CARRY) + 3 >= MAX_CARRY )
                                {
                                        send_user(who, "%c%s", '!', "您携带的东西太多了.");
                                        return;
                                }

                                obj = new( "/item/std/0034" );
                                if( p = obj->move(who, -1) ) obj->add_to_user(p);
                                else destruct(obj);

                                obj = new( "/item/std/0034" );
                                if( p = obj->move(who, -1) ) obj->add_to_user(p);
                                else destruct(obj);

                                obj = new( "/item/std/0034" );
                                if( p = obj->move(who, -1) ) obj->add_to_user(p);
                                else destruct(obj);

                                obj = new( "/item/std/0034" );
                                if( p = obj->move(who, -1) ) obj->add_to_user(p);
                                else destruct(obj);

                                who->delete_save_2("build");
                                who->set_save_2("build.flag", 3);
                                who->set_save_2("build.time", time() );

                                break;

                       case 4 : result = BUILD_FILE->get_quest(who);

                                send_user( who, "%c%s", ':', sprintf( "%s：\n城中的建设急需%s，你帮我找来吧.\n", 
                                        me->get_name(), result ) );

                                who->delete_save_2("build");
                                who->set_save_2("build.flag", 4);
                                who->set_save_2("build.time", time() );
                                who->set_save_2("build.item", result);

                                break;
                        }

                        who->add_strength(-1);

                        return;
                }

                if( who->get_id() == me->get_master() || who->get_id() == me->get_master_2() || who->get_id() == me->get_master_3() )
                {

                if( !arg || arg == "?" )    // 发布任务 ##################################################
                {
                        cmd1 = sprintf( "talk %x# build.?.1\n", id );
                        cmd2 = sprintf( "talk %x# build.?.2\n", id );
                        cmd3 = sprintf( "talk %x# build.?.3\n", id );
                        cmd4 = sprintf( "talk %x# build.?.4\n", id );
                        cmd5 = sprintf( "talk %x# build.?.5\n", id );
                        cmd6 = sprintf( "talk %x# build.?.6\n", id );
                        cmd7 = sprintf( "talk %x# build.?.7\n", id );
                        cmd8 = sprintf( "talk %x# build.?.8\n", id );
                        cmd9 = sprintf( "talk %x# build.?.9\n", id );
                        send_user( who, "%c%s", ':', "请选择建设城市的项目：(消耗 50 体力)\n" +
                                sprintf( ESC "城防(%d).\n", city->get_defence() ) + cmd1 +
                                sprintf( ESC "农业(%d).\n", city->get_agriculture() ) + cmd2 +
                                sprintf( ESC "渔业(%d).\n", city->get_fishculture() ) + cmd3 +
                                sprintf( ESC "矿业(%d).\n", city->get_mining() ) + cmd4 +
                                sprintf( ESC "工业(%d).\n", city->get_industry() ) + cmd5 +
                                sprintf( ESC "商业(%d).\n", city->get_commercial() ) + cmd6 +
                                sprintf( ESC "艺术(%d).\n", city->get_arts() ) + cmd7 +
                                sprintf( ESC "教育(%d).\n", city->get_education() ) + cmd8 +
                                sprintf( ESC "宗教(%d).\n", city->get_religion() ) + cmd9 +
                                ESC "我再想想……\nCLOSE\n" );
                }
                else if( sscanf( arg, "?.%d", number ) )
                {
                        switch( number )
                        {
                      default : name3 = "城防";  break;
                       case 2 : name3 = "农业";  break;
                       case 3 : name3 = "渔业";  break;
                       case 4 : name3 = "矿业";  break;
                       case 5 : name3 = "工业";  break;
                       case 6 : name3 = "商业";  break;
                       case 7 : name3 = "艺术";  break;
                       case 8 : name3 = "教育";  break;
                       case 9 : name3 = "宗教";  break;
                        }

                        cmd1 = sprintf( "talk %x# build.%d\n", id, number );
                        send_user( who, "%c%s", ':', sprintf( "您确定发布建设“%s”任务？\n", name3 ) + 
                                ESC "是的.\n" + cmd1 +
                                ESC "我再想想……\nCLOSE\n" );
                }
                else if( number = to_int(arg) )
                {
                        if( who->get_strength() < 50 )
                        {
                                send_user(who, "%c%s", '!', "发布建设任务要 50 点体力.");
                                return;
                        }
                        if( city->get_save_2("build.flag") )
                        {
                                switch( city->get_save_2("build.flag") )
                                {
                              default : name3 = "城防";  break;
                               case 2 : name3 = "农业";  break;
                               case 3 : name3 = "渔业";  break;
                               case 4 : name3 = "矿业";  break;
                               case 5 : name3 = "工业";  break;
                               case 6 : name3 = "商业";  break;
                               case 7 : name3 = "艺术";  break;
                               case 8 : name3 = "教育";  break;
                               case 9 : name3 = "宗教";  break;
                                }

                                send_user(who, "%c%s", '!', "建设“" + name3 + "”任务还未完成.");
                                return;
                        }

                        switch( number )
                        {
                      default : name3 = "城防";  city->add_money(-1000000);  break;
                       case 2 : name3 = "农业";  city->add_money(-500000);  break;
                       case 3 : name3 = "渔业";  city->add_money(-500000);  break;
                       case 4 : name3 = "矿业";  city->add_money(-500000);  break;
                       case 5 : name3 = "工业";  city->add_money(-500000);  break;
                       case 6 : name3 = "商业";  city->add_money(-500000);  break;
                       case 7 : name3 = "艺术";  city->add_money(-500000);  break;
                       case 8 : name3 = "教育";  city->add_money(-500000);  break;
                       case 9 : name3 = "宗教";  city->add_money(-500000);  break;
                        }

                        city->set_save_2("build.flag", number);
                        city->set_save_2("build.work", 0);

                        result = sprintf( HIY "%s发布建设%s“%s”任务，欢迎到内政官处领取任务.", who->get_name(), name2, name3 );
                        FAMILY_D->city_channel(name2, 0, result);

                        who->add_strength(-50);
                }

                }
        }
}

// 函数：建设任务(接收物品)
int accept_object( object who, object me, object obj ) 
{ 
        string name1, name2;
        string result;
        int level, exp;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        me->to_front_eachother(who);

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&      who->get_save_2("build.flag") == 4
        &&      gone_time( who->get_save_2("build.time") ) < 2400
        &&      who->get_save_2("build.item") == obj->get_name() )
        {
                level = who->get_level();

                who->add_contribute(1);    // 国家贡献 +1
                exp = level * random(50) + 1000;  who->add_exp(exp);
                who->add_potential(5);

                send_user( who, "%c%w", 0x0d, MUSIC_TASK );
                write_user( who, ECHO "您的国家贡献 +1, 经验 %+d, 潜能 +5.", exp );

                who->delete_save_2("build");    // 删除任务标志

                do_build_finish(who, me);    // 用 me 以防 BUG！要 set_city_name

                return 1;
        }

        return 0;
}

// 函数：建设任务(工匠接收食物)
int accept_object_2( object who, object me, object obj, int flag ) 
{ 
        string name1, name2;
        string result;
        int level, exp;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        me->to_front_eachother(who);

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&      who->get_save_2("build.flag") == 3
        &&      gone_time( who->get_save_2("build.time") ) < 2400
        &&      obj->get_name() == "食物" )
        {
                if( ( level = who->get_save_2("build.food") ) & flag )
                {
                        send_user(who, "%c%s", '!', "您已经给过他食物了.");
                        return 0;
                }

                level = who->set_save_2("build.food", level | flag);

                if( level != 15 )
                {
                        send_user( who, "%c%s", ':', sprintf( "%s：\n正好肚子也饿了，谢谢你给我及时送来食物！\n", me->get_name() ) );
                        return 1;
                }

                level = who->get_level();

                who->add_contribute(1);    // 国家贡献 +1
                exp = level * random(50) + 1000;  who->add_exp(exp);
                who->add_potential(5);

                send_user( who, "%c%w", 0x0d, MUSIC_TASK );
                write_user( who, ECHO "您的国家贡献 +1, 经验 %+d, 潜能 +5.", exp );

                who->delete_save_2("build");    // 删除任务标志

                do_build_finish(who, me);    // 用 me 以防 BUG！要 set_city_name

                return 1;
        }

        return 0;
}

// 函数：建设任务(完成奖励)
void do_build_finish( object who, object me )
{
        object city;
        string result, name;
        int point;

        if( city = CITY_D->get_city_object(me) )    // 用 me 以防 BUG！要 set_city_name
        {
                switch( city->get_save_2("build.flag") )
                {
              default : if( city->add_save_2("build.work", 1) < 1000 ) return;
                        result = "城防";
                        point = city->add_defence(100);
                        break;
               case 2 : if( city->add_save_2("build.work", 1) < 500 ) return;
                        result = "农业";
                        point = city->add_agriculture(100);
                        break;
               case 3 : if( city->add_save_2("build.work", 1) < 500 ) return;
                        result = "渔业";
                        point = city->add_fishculture(100);
                        break;
               case 4 : if( city->add_save_2("build.work", 1) < 500 ) return;
                        result = "矿业";
                        point = city->add_mining(100);
                        break;
               case 5 : if( city->add_save_2("build.work", 1) < 500 ) return;
                        result = "工业";
                        point = city->add_industry(100);
                        break;
               case 6 : if( city->add_save_2("build.work", 1) < 500 ) return;
                        result = "商业";
                        point = city->add_commercial(100);
                        break;
               case 7 : if( city->add_save_2("build.work", 1) < 500 ) return;
                        result = "艺术";
                        point = city->add_arts(100);
                        break;
               case 8 : if( city->add_save_2("build.work", 1) < 500 ) return;
                        result = "教育";
                        point = city->add_education(100);
                        break;
               case 9 : if( city->add_save_2("build.work", 1) < 500 ) return;
                        result = "宗教";
                        point = city->add_religion(100);
                        break;
                }
                
                city->delete_save_2("build");    // 删除任务标志

                name = me->get_city_name();
                result = sprintf( HIY "%s完成%s建设“%s”最后一个任务.(%s +100 至 %d)", who->get_name(), name, result, result, point );
                FAMILY_D->city_channel(name, 0, result);
        }
}
