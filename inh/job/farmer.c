
#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <action.h>
#include <music.h>

string *PlantName = ({ "Cây non", "Nhất thành", "Nhị thành", "Tam thành", "Tứ thành", "Ngũ thành", "Lục thành", "Thất thành", "Bát thành", "Cửu thành", "Thành thục" });

// 函数：对话处理
void do_look_1( object me, object who )
{
        string cmd1, cmd2, cmd3, cmd4, cmd5;
        string result;
        int id = getoid(who);

        if(     !me->is_farmer()
        ||      me->get_task("plant") != sprintf( "%x#", id ) )
        {
                send_user( me, "%c%s", ':', "Đây là một cây nông nghiệp loại lớn." );
                return;
        }

        cmd1 = sprintf( "talk %x# plant.1\n", id );
        cmd2 = sprintf( "talk %x# plant.2\n", id );
        cmd3 = sprintf( "talk %x# plant.3\n", id );
        cmd4 = sprintf( "talk %x# plant.4\n", id );
        cmd5 = sprintf( "talk %x# plant.5\n", id );

        if( who->get("time") >= 10 ) 
                result = "Cây nặng trĩu quả.";
        else switch( who->get("plant") )
        {
      default : result = "";  break;
       case 1 : result = "Cỏ dại mọc bốn phía.";  break;
       case 2 : result = "Lá chuyển vàng, bị úa.";  break;
       case 3 : result = "Bốn phía đều khô cạn.";  break;
       case 4 : result = "Trên lá có sâu.";  break;
        }

        result = sprintf( "Cây nông nghiệp độ lớn dần %d.%s\n", who->get("time"), result );
        send_user( me, "%c%s", ':', result +
                ESC "Ta phải nhổ cỏ.\n" + cmd1 +
                ESC "Ta phải bón phân.\n" + cmd2 +
                ESC "Ta phải tưới nước.\n" + cmd3 +
                ESC "Ta phải khử trùng.\n" + cmd4 +
                ESC "Ta phải thu hoạch.\n" + cmd5 +
                ESC "Ta không muốn làm.\nCLOSE\n" );
}

// 函数：耕作处理
void do_plant( object me, object who, string arg )
{
        object city, obj, obj2;
        int work, gold, exp, exp2, level, p;

        if( !me->is_farmer() )
        {
                send_user(me, "%c%s", '!', "Bạn không phải nông phu, không thể trồng trọt.");
                return;
        }
        if( me->get_task("plant") != sprintf( "%x#", getoid(who) ) )
        {
                send_user(me, "%c%s", '!', "这不是您的农作物.");
                return;
        }
        if( me->get_strength() < 1 )
        {
                send_user(me, "%c%s", '!', "Điểm thể lực không đủ 1.");
                return;
        }

        if( !arg || arg == "" ) return;
        if( !( work = to_int(arg) ) ) return;

        obj = me->get_equip(HAND_TYPE);
        level = me->get_occupation_level();

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 02011, 10, OVER_BODY, PF_ONCE );

        if( work == 5 && who->get("time") >= 10 )    // 收割
        {
                me->add_strength(-1);    // 农夫经验 +60, 忠实 +3, 诚信 +60, 勇敢 +60, 声望 +3, 国家贡献 +10
                exp2 = 60;  me->add_occupation_exp(exp2);
                me->add_gift_zs(3);
                me->add_gift_cx(60);
                me->add_gift_yg(60);
                me->add_repute(3);
                me->add_contribute(10);
                gold = level * 2 + 20;  me->add_cash(gold);  me->add_gold_log("task", gold);
                me->log_money("农夫", gold);
                "/sys/sys/count"->add_income("task", gold);
                exp = level * 10 + 100;  me->add_exp(exp);
                me->add_potential(10);

                write_user( me, ECHO "Bạn thành công thu hoạch cây nông nghiệp." );

                who->remove_from_scene();
                destruct(who);

                send_user( me, "%c%w", 0x0d, MUSIC_TASK );
                write_user( me, ECHO "您的农夫经验 +60, 忠实 +3, 诚信 +60, 勇敢 +60, 声望 +3, 国家贡献 +10, 金钱 %+d, 经验 %+d, 潜能 +10.", gold, exp );

                if( !( city = CITY_D->get_city_object(me) ) ) return;

                work = level * 10 + 250;
                if( obj && obj->get_name() == "镰刀" ) work = work * 120 / 100;
                city->add_food(work);

                p = random(100);

                if( p < 50 )    // 好的事件
                {
                        p = random(100);

                        if( p < 30 )    // 城市丰收
                        {
                                city->add_food(1000);
                                write_user( me, ECHO "%s城市的粮草获得丰收！粮草增加 1000 点.", city->get_name() );
                        }
                        else if( p < 60 )
                        {
                                me->add_cash(1000);  me->add_gold_log("task", 1000);
                                me->log_money("农夫", 1000);
                                "/sys/sys/count"->add_income("task", 1000);
                                write_user( me, ECHO "您挖出了一些值钱的东西！您得到 1000 金." );
                        }
                        else if( p < 80 )    // 挖出药材
                        {
                                switch( random(35) )
                                {
                               case 0 : obj2 = new( "/item/90/9001" );  break;
                               case 1 : obj2 = new( "/item/90/9002" );  break;
                               case 2 : obj2 = new( "/item/90/9003" );  break;
                               case 3 : obj2 = new( "/item/90/9004" );  break;
                               case 4 : obj2 = new( "/item/90/9010" );  break;
                               case 5 : obj2 = new( "/item/90/9011" );  break;
                               case 6 : obj2 = new( "/item/90/9012" );  break;
                               case 7 : obj2 = new( "/item/90/9020" );  break;
                               case 8 : obj2 = new( "/item/90/9021" );  break;
                               case 9 : obj2 = new( "/item/90/9022" );  break;
                              case 10 : obj2 = new( "/item/90/9023" );  break;
                              case 11 : obj2 = new( "/item/90/9030" );  break;
                              case 12 : obj2 = new( "/item/90/9031" );  break;
                              case 13 : obj2 = new( "/item/90/9032" );  break;
                              case 14 : obj2 = new( "/item/90/9040" );  break;
                              case 15 : obj2 = new( "/item/90/9041" );  break;
                              case 16 : obj2 = new( "/item/90/9042" );  break;
                              case 17 : obj2 = new( "/item/90/9050" );  break;
                              case 18 : obj2 = new( "/item/90/9051" );  break;
                              case 19 : obj2 = new( "/item/90/9052" );  break;
                              case 20 : obj2 = new( "/item/90/9060" );  break;
                              case 21 : obj2 = new( "/item/90/9061" );  break;
                              case 22 : obj2 = new( "/item/90/9062" );  break;
                              case 23 : obj2 = new( "/item/90/9070" );  break;
                              case 24 : obj2 = new( "/item/90/9071" );  break;
                              case 25 : obj2 = new( "/item/90/9072" );  break;
                              case 26 : obj2 = new( "/item/90/9073" );  break;
                              case 27 : obj2 = new( "/item/90/9074" );  break;
                              case 28 : obj2 = new( "/item/90/9080" );  break;
                              case 29 : obj2 = new( "/item/90/9081" );  break;
                              case 30 : obj2 = new( "/item/90/9082" );  break;
                              case 31 : obj2 = new( "/item/90/9083" );  break;
                              case 32 : obj2 = new( "/item/90/9084" );  break;
                              case 33 : obj2 = new( "/item/90/9085" );  break;
                              case 34 : obj2 = new( "/item/90/9086" );  break;
                                }
                                write_user( me, ECHO "您掘地挖出了%s！", obj2->get_name() );
                                if( p = obj2->move(me, -1) ) obj2->add_to_user(p);
                                else destruct(obj2);
                        }
                        else if( p < 90 )    // 挖出藏宝图
                        {
                                obj2 = new( "/item/std/8000" );
                                if( p = obj2->move(me, -1) ) obj2->add_to_user(p);
                                else destruct(obj2);
                                write_user( me, ECHO "您掘地挖出了一张藏宝图！" );
                        }
                        else if( p < 92 )    // 挖出矿石
                        {
                        }
                        else 
                        {
                                me->add_strength(20);
                                write_user( me, ECHO "人们对您的工作赞不绝口！您的体力增加 20 点." );
                        }
                }
                else if( p < 60 )    // 坏的事件(职业经验加倍)
                {
                        p = random(100);

                        if( p < 50 )
                        {
                                city->add_food( -1000 );
                                me->add_occupation_exp(exp2);
                                write_user( me, ECHO "%s城市的粮草发生歉收！粮草减少 1000 点.", city->get_name() );
                        }
                        else
                        {
                                me->add_strength( -20 );
                                me->add_occupation_exp(exp2);
                                write_user( me, ECHO "您突然间觉得十分劳累！您的体力减少 20 点." );
                        }
                }

                return;
        }

        if( who->get("plant") == work )
        {
                switch( work )
                {
               case 1 : if( obj && obj->get_name() == "除草锄" ) 
                                who->add("time", 2);
                        else    who->add("time", 1);
                        write_user( me, ECHO "您给农作物锄草，结果它长得更好了." );
                        who->set_head_code_2(0);
                        break;
               case 2 : who->add("time", 1);  
                        write_user( me, ECHO "您给农作物施肥，结果它长得更好了." );
                        who->set_head_code_2(0);
                        break;
               case 3 : if( obj && obj->get_name() == "小木桶" ) 
                                who->add("time", 2);
                        else    who->add("time", 1);
                        write_user( me, ECHO "您给农作物浇水，结果它长得更好了." );
                        who->set_head_code_2(0);
                        break;
               case 4 : who->add("time", 1);  
                        write_user( me, ECHO "您给农作物除虫，结果它长得更好了." );
                        who->set_head_code_2(0);
                        break;
                }
                if( who->get("time") > 10 ) who->set("time", 10);
                level = who->get("time");  if( level < 0 ) level = 0;
                who->set_name( sprintf( "%s(%s)", PlantName[level], me->get_name() ) );    // 更改名称
                who->delete("plant");
        }
        else if( work == 5 )
        {
                write_user( me, ECHO "您过早收割了农作物，结果一无所获." );
                who->remove_from_scene();
                destruct(who);
        }
        else
        {
                if( who->add("time", -1) < 0 )
                {
                        write_user( me, ECHO "您没有照料好农作物，结果它死掉了." );
                        who->remove_from_scene();
                        destruct(who);
                }
        }
}

// 函数：对话处理
void do_look_2( object me, object who )
{
        object city;
        string cmd, result;

        if(     me->is_farmer()
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                cmd = sprintf( "talk %x# fish\n", getoid(who) );
                result = ( city->get_2("fish.total") > city->get_2("fish.kill") * 2 ) ? "" : "已经捕捞得所剩无几了，";
                result = sprintf( "这里鱼的数量为 %d，%s您想：\n", who->get("fish"), result );
                send_user( me, "%c%s", ':', result +
                        ESC "我要捕鱼.\n" + cmd +
                        ESC "Ta không muốn làm.\nCLOSE\n" );
        }
}

// 函数：捕鱼处理
void do_fish( object me, object who, string arg )
{
        if( !me->is_farmer() )
        {
                send_user(me, "%c%s", '!', "您不是农夫，不懂得捕鱼.");
                return;
        }
        if( gone_time( me->get_time("work") ) < 10 )
        {
                send_user(me, "%c%s", '!', "Xin chờ 1 chút.");
                return;
        }
        if( me->get_strength() < 1 )
        {
                send_user(me, "%c%s", '!', "Điểm thể lực không đủ 1.");
                return;
        }

        write_user( me, ECHO "您张开网开始捕鱼..." );

        me->set_time( "work", time() );
        call_out( "do_fish_finish", 10, me, who, arg );
}

// 函数：捕鱼结束
void do_fish_finish( object me, object who, string arg )
{
        object city, city2, obj;
        int p;
        int level, cx, yg, gold, exp, exp2, flag;

        if( !me || !who ) return;

        if( distance_between(who, me) > 3 )
        {
                send_user(me, "%c%s", '!', "您距离鱼有些远了.");
                return;
        }

        if( !( city = CITY_D->get_city_object(who) ) ) return;
        if( !( city2 = CITY_D->get_city_object(me) ) ) return;

        level = me->get_occupation_level();

        if( random(100) < 60 + level / 5 )    // 捕鱼成功
        {
                write_user( me, ECHO "您成功地捕到了一些鱼！" );
                who->add("fish", -1);
                city->add_2("fish.kill", 1);
                flag = 1;
        }
        else
        {
                write_user( me, ECHO "您一不小心让鱼溜走了." );
                flag = 0;
        }

        me->add_strength(-1);    // 体力 -1, 农夫经验 +10, 忠实 +1, 诚信 +10, 勇敢 +10, 声望 +1, 国家贡献 +1
        exp2 = 10;  me->add_occupation_exp(exp2);
        me->add_gift_zs(1);

        if( city->get_2("fish.total") > city->get_2("fish.kill") * 2 )
        {
                cx = 10;  me->add_gift_cx(cx);
                yg = 10;  me->add_gift_yg(yg);
                if( flag ) 
                {
                        gold = level * 2 + 20;  me->add_cash(gold);  me->add_gold_log("task", gold);
                        me->log_money("农夫", gold);
                        city2->add_food(level * 2 + 20);
                }
        }
        else    // 捕鱼过量
        {
                cx = 5;  me->add_gift_cx(cx);    // 所得属性、金钱减半
                yg = 5;  me->add_gift_yg(yg);
                if( flag ) 
                {
                        gold = level + 10;  me->add_cash(gold);  me->add_gold_log("task", gold);
                        me->log_money("农夫", gold);
                        "/sys/sys/count"->add_income("task", gold);
                        "/sys/sys/count"->add_income("task", gold);
                        city2->add_food(level + 10);
                }
        }

        me->add_repute(1);
        me->add_contribute(1);
        exp = level * 4 + 40;  me->add_exp(exp);
        me->add_potential(1);

        send_user( me, "%c%w", 0x0d, MUSIC_TASK );
        write_user( me, ECHO "您的农夫经验 %+d, 忠实 +1, 诚信 %+d, 勇敢 %+d, 声望 +1, 国家贡献 +1, 金钱 %+d, 经验 %+d, 潜能 +1.", 
                exp2, cx, yg, gold, exp );

        if( who->get("fish") < 1 )    // 鱼全部捕完
        {
                write_user( me, ECHO "这里的鱼已经全部被您捕光了." );
                who->remove_from_scene();
                destruct(who);
        }
}
