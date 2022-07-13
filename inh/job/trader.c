
#include <ansi.h>
#include <action.h>

// 函数：对话处理
void do_look( object who, object me )
{
        string cmd1, cmd2, info;
        int time;
        int id = getoid(me);

        cmd1 = sprintf( "list %x#\n", id );
        cmd2 = sprintf( "talk %x# good.?\n", id );
	time = (600 + who->get("reset_time") - time())/60;
	if (time>5) info = "再过不久，我将重新上架一批货物.";
	else
	if (time>=2) info = "再过一会，我将重新上架一批货物.";
	else info = "我马上就会重新上架一批货物.";
        if( who->is_businessman() || who->get_save_2("mastertask.type")==11 || who->get_save_2("orgtask3.type") )
                me->more_look_menu( who, sprintf( "%s：\n    "+"/quest/word"->get_normal_word(me)+"\n    这位%s，刚上市的特产，您来点什么吧？(买入物价: %d  卖出: %d) "+info+"\n",
                        me->get_name(), NPC_RANK_D->get_respect(who), me->get_buy_rate() / 10,  me->get_sell_rate() / 10 ) +
                        ESC "买卖货物.\n" + cmd1 +
//                        ESC "砍价.\n" + cmd2 +
                        ESC "离开.\nCLOSE\n" );
        else    me->more_look_menu( who, me->get_name() + "：\n现在做商人吃香极了，既可以为门派或者帮派做出贡献，又可以自己发笔小财.\n" );
}

// 函数：领取、交还钱票
void do_cheque( object who, object me, string arg )
{
        object city, obj;
        string name1, name2;
        string cmd;
        int id, gold, gold2, p;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&      who->is_businessman() )
        {
                id = getoid(me);

                if( arg == "?" )
                {
                        if( present("钱票", who, 1, MAX_CARRY) )
                        {
                                send_user(who, "%c%s", '!', "您已经领了钱票了.");
                                return;
                        }
                        if( present("银票", who, 1, MAX_CARRY) )
                        {
                                send_user(who, "%c%s", '!', "您已经领了银票了.");
                                return;
                        }                        
                        if( sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY )
                        {
                                send_user(who, "%c%s", '!', "您携带的东西太多了.");
                                return;
                        }

                        cmd = sprintf( ESC "talk %x# cheque.%%s\n", id );
                        send_user( who, "%c%c%d%s", '?', 1, who->get_cash(), "您想领取多大本金的钱票？请输入具体金额：\n" + cmd );
                }
                else if( arg == "@" )
                {
                        if( !( obj = present("钱票", who, 1, MAX_CARRY) ) )
                        {
                                send_user(who, "%c%s", '!', "您没有领商人用的钱票.");
                                return;
                        }

                        gold = obj->get_money();    // 钱票的钱
                        gold2 = gold - obj->get_orgin_money();    // 赚到的钱

                        if( gold2 > 0 )
                        {
                                if( city = CITY_D->get_city_object(who) )
                                {
                                        city->add_tax(gold2 / 2);
                                }

                                gold = obj->get_orgin_money() + gold2 / 2;
                                who->add_cash(gold);  who->add_gold_log("trade", gold);
                                who->log_money("商人", gold);
                                "/sys/sys/count"->add_income("trader", gold);
                                who->add_contribute(gold2 / 1000);    // 1000 金 = 贡献
                                obj->remove_from_user();
                                destruct(obj);

                                write_user( who, ECHO "您把钱票交给%s，%s税收 %+d，您的国家贡献 %+d, 金钱 %+d.",
                                        me->get_name(), who->get_city_name(), gold2 / 2, gold2 / 1000, gold );
                        }
                        else    // 亏本
                        {
                                gold = obj->get_orgin_money() + gold2 / 2;
                                "/sys/sys/count"->add_income("trader", gold);
                                who->log_money("商人", gold);
                                who->add_cash(gold);  who->add_gold_log("trade", gold);
                                obj->remove_from_user();
                                destruct(obj);

                                write_user( who, ECHO "您把钱票交给%s，您的金钱 %+d.", me->get_name(), gold );
                        }
                }
                else if( gold = to_int(arg) )
                {
                        if( present("钱票", who, 1, MAX_CARRY) )
                        {
                                send_user(who, "%c%s", '!', "您已经领了钱票了.");
                                return;
                        }
                        if( sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY )
                        {
                                send_user(who, "%c%s", '!', "您携带的东西太多了.");
                                return;
                        }
                        if( gold < 1 )
                        {
                                send_user(who, "%c%s", '!', "您输入的金额必须是正整数.");
                                return;
                        }
                        if( gold > who->get_cash() )
                        {
                                send_user(who, "%c%s", '!', sprintf("您手上只有 %d 金.", who->get_cash() ) );
                                return;
                        }
                        
                        who->add_cash( -gold );  who->add_gold_log("trade", -gold);
                        who->log_money("商人", -gold);
                        "/sys/sys/count"->add_income("trader", -gold);

                        obj = new("/item/std/0002");
                        obj->set_orgin_money(gold);
                        obj->set_money(gold);

                        send_user( who, "%c%s", ':', sprintf( "%s：\n这是 %s，你现在是为国效命的红顶商人了，好好努力吧.", 
                                me->get_name(), obj->get_name() ) );

                        if( p = obj->move(who, -1) ) obj->add_to_user(p);
                        else destruct(obj);
                }
        }
}

// 函数：游说物价
void do_good( object who, object me, string arg )
{
        string cmd;

        if( !who->is_businessman() )
        {
                send_user(who, "%c%s", '!', "您不懂得如何游说.");
                return;
        }
        if( gone_time( who->get_time("work") ) < 10 )
        {
                send_user(who, "%c%s", '!', "Xin chờ 1 chút.");
                return;
        }
        if( who->get_occupation_level() < 20 )
        {
                send_user(who, "%c%s", '!', "游说得要 20 级商人等级.");
                return;
        }
        if( who->get_hp() < who->get_max_hp() )
        {
                send_user(who, "%c%s", '!', "您没有足够的气血.");
                return;
        }
        if( who->get_mp() < who->get_max_mp() )
        {
                send_user(who, "%c%s", '!', "您没有足够的法力.");
                return;
        }

        if( arg == "?" )
        {
                cmd = sprintf( "talk %x# good.@\n", getoid(me) );
                send_user( who, "%c%s", ':', "您确定要游说商人以影响物价指数吗？(消耗 100 商人经验)\n" 
                        ESC "是的.\n" + cmd +
                        ESC "我再想想...\nCLOSE\n" );
                return;
        }

        write_user( who, ECHO "您面露异光，对%s滔滔不绝地讲述自己经商的种种艰辛...", me->get_name() );

        who->set_time( "work", time() );
        call_out( "do_good_finish", 10, who, me, arg );
}

// 函数：游说结束
void do_good_finish( object who, object me, string arg )
{
        string result;
        int level;

        if( !who || !me ) return;

        if( distance_between(me, who) > 1 )
        {
                write_user( who, ECHO "游说没效果，%s已经走开了.", me->get_name() );
                return;
        }

        level = who->get_occupation_level();

        if( random(100) < 30 + level )
        {
                if( who->add_occupation_exp(-100) < who->get_job_exp(level - 1) )
                {
                        level = who->add_occupation_level(-1);
                        result = sprintf( HIC "您的‘商人’等级降至 %d 级！", level );
                        send_user( who, "%c%s", '!', result );
                }

                me->set_buy_rate( random(1001) );
                me->set_sell_rate( random(1001) );

                write_user( who, ECHO "%s只听得滴下几滴泪水，悄悄把物价改动了.", me->get_name() );
        }
        else
        {
                write_user( who, ECHO "%s听了不动声色，一点同情心都没有.", me->get_name() );
        }

        who->set_hp( who->get_max_hp() / 4 );
        who->set_mp( who->get_max_mp() / 4 );
}

// 函数：煽动敌方
void do_stir_up( object who, object me, string arg )
{
        object city;
        string name1, name2;
        string cmd;
        int what;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 != name2 && name2 != ""
        &&      who->is_businessman()
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( gone_time( who->get_time("work") ) < 10 )
                {
                        send_user(who, "%c%s", '!', "Xin chờ 1 chút.");
                        return;
                }
                if( who->get_strength() < 20 )
                {
                        send_user(who, "%c%s", '!', "Điểm thể lực không đủ 1.");
                        return;
                }

                if( arg == "?" )
                {
                        cmd = sprintf( "talk %x# stir_up.@\n", getoid(me) );
                        send_user( who, "%c%s", ':', "您确定要造谣吗？(消耗 20 体力)\n" 
                                ESC "是的.\n" + cmd +
                                ESC "我再想想...\nCLOSE\n" );
                }
                else if( arg == "@" )
                {
                        switch( what = random(8) )
                        {
                      default : send_user( who, "%c%s", ':', "您：\n听说官府要加重农业税了." );
                                break;
                       case 1 : send_user( who, "%c%s", ':', "您：\n听说官府要加重渔业税了." );
                                break;
                       case 2 : send_user( who, "%c%s", ':', "您：\n听说官府要加重矿业税了." );
                                break;
                       case 3 : send_user( who, "%c%s", ':', "您：\n听说官府要加重工业税了." );
                                break;
                       case 4 : send_user( who, "%c%s", ':', "您：\n听说官府要加重商业税了." );
                                break;
                       case 5 : send_user( who, "%c%s", ':', "您：\n听说官府要加重艺术税了." );
                                break;
                       case 6 : send_user( who, "%c%s", ':', "您：\n听说官府就要废止教育了." );
                                break;
                       case 7 : send_user( who, "%c%s", ':', "您：\n听说官府就要废止宗教了." );
                                break;
                        }
                        who->set_time( "work", time() );
                        call_out( "do_stir_up_finish", 10, who, me, what );
                }
        }
}

// 函数：造谣结束
void do_stir_up_finish( object who, object me, int what )
{
        object city;
        int level;

        if( !who || !me ) return;

        if( distance_between(me, who) > 1 )
        {
                write_user( who, ECHO "造谣不成功，%s已经走开了.", me->get_name() );
                return;
        }

        level = who->get_occupation_level();

        if( random( level + 1 ) > 0 )
        {
                who->add_strength(-20);    // 体力 -20, 商人经验 +100, 声望 +10
                who->add_occupation_exp(100);
                who->add_repute(10);

                if( city = CITY_D->get_city_object(me) ) switch( what )
                {
              default : send_user( who, "%c%s", ':', sprintf( "%s：\n是吗？我得告诉乡亲们不能再务农了.(农业 %+d)", me->get_name(), -level ) );
                        city->add_agriculture(-level);  
                        break;
               case 1 : send_user( who, "%c%s", ':', sprintf( "%s：\n是吗？我得告诉乡亲们不能再务渔了.(渔业 %+d)", me->get_name(), -level ) );
                        city->add_fishculture(-level);  
                        break;
               case 2 : send_user( who, "%c%s", ':', sprintf( "%s：\n是吗？我得告诉乡亲们不能再务矿了.(矿业 %+d)", me->get_name(), -level ) );
                        city->add_mining(-level);  
                        break;
               case 3 : send_user( who, "%c%s", ':', sprintf( "%s：\n是吗？我得告诉乡亲们不能再开工场了.(工业 %+d)", me->get_name(), -level ) );
                        city->add_industry(-level);  
                        break;
               case 4 : send_user( who, "%c%s", ':', sprintf( "%s：\n是吗？我得告诉乡亲们不能再去经商了.(商业 %+d)", me->get_name(), -level ) );
                        city->add_commercial(-level);  
                        break;
               case 5 : send_user( who, "%c%s", ':', sprintf( "%s：\n是吗？我得告诉乡亲们不能再搞艺术了.(艺术 %+d)", me->get_name(), -level ) );
                        city->add_arts(-level);  
                        break;
               case 6 : send_user( who, "%c%s", ':', sprintf( "%s：\n是吗？我得告诉乡亲们不能再去学堂了.(教育 %+d)", me->get_name(), -level ) );
                        city->add_education(-level);  
                        break;
               case 7 : send_user( who, "%c%s", ':', sprintf( "%s：\n是吗？我得告诉乡亲们不能再去拜神了.(宗教 %+d)", me->get_name(), -level ) );
                        city->add_religion(-level);  
                        break;
                }

//                write_user( who, ECHO "您的商人经验 +100, 声望 +10." );
        }
        else
        {
                who->add_strength(-20);    // 体力 -20
                send_user( who, "%c%s", ':', sprintf( "%s：\n你别骗我了，我不信.", me->get_name() ) );
        }
}
