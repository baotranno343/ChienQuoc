// minister of finance 财政官

#include <ansi.h>

// 函数：增添对话菜单
void more_look_menu( object who, object me, string text )
{
        string result = "";
        int p, id = getoid(me);

        if( who->is_businessman() )
        {
                if( !present("钱票", who, 1, MAX_CARRY) )
                        result = sprintf( ESC "领取经商凭证.\ntalk %x# cheque.?\n", id );
                else    result = sprintf( ESC "交还经商凭证.\ntalk %x# cheque.@\n", id );
        }
        if(     who->get_save_2("build.flag") == 2
        &&      gone_time( who->get_save_2("build.time") ) < 2400 )
        {
                result = sprintf( ESC "帮手算帐.\ntalk %x# comput\n", id );
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
        string cmd1, cmd2, cmd3, cmd4;
        int id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if( stringp(name1) && stringp(name2) && name1 == name2 )
        {
                if( who->get_id() == me->get_master() )
                {
                        cmd1 = sprintf( "talk %x# info.?\n", id );
                        cmd2 = sprintf( "talk %x# tax.?\n", id );
                        cmd3 = sprintf( "talk %x# salary.?\n", id );
                        cmd4 = sprintf( "talk %x# salary\n", id );
                        more_look_menu( who, me, me->get_name() + "：\n    "+"/quest/word"->get_country_word(me)+"\n    " + who->get_name() + "城主阁下，您有什么事情？\n" 
                                ESC "查询本城情况.\n" + cmd1 +
                                ESC "设定本城税率.\n" + cmd2 +
                                ESC "设定城主薪水.\n" + cmd3 +
                                ESC "领取薪水.\n" + cmd4 +
                                ESC "离开.\nCLOSE\n" );
                }
                else if( who->get_id() == me->get_master_2() || who->get_id() == me->get_master_3() )
                {
                        cmd1 = sprintf( "talk %x# info.?\n", id );
                        cmd2 = sprintf( "talk %x# tax.?\n", id );
                        cmd4 = sprintf( "talk %x# salary\n", id );
                        more_look_menu( who, me, me->get_name() + "：\n    " + "/quest/word"->get_country_word(me) +"\n    " + who->get_name() + "副城主阁下，您有什么事情？\n" 
                                ESC "查询本城情况.\n" + cmd1 +
                                ESC "设定本城税率.\n" + cmd2 +
                                ESC "领取薪水.\n" + cmd4 +
                                ESC "离开.\nCLOSE\n" );
                }
                else
                {
                        cmd1 = sprintf( "talk %x# info.?\n", id );
                        more_look_menu( who, me, me->get_name() + "：\n    " + "/quest/word"->get_country_word(me) + "\n    " + who->get_name() + "，您有什么事情？\n" 
                                ESC "查询本城情况.\n" + cmd1 +
                                ESC "离开.\nCLOSE\n" );
                }
        }
        else
        {
                send_user( who, "%c%s", ':', me->get_name() + "：\n    "+"/quest/word"->get_country_word(me) );
        }
}

// 函数：查询状态
void do_info( object who, object me, string arg )
{
        object city;
        string relation, result;
        string name1, name2;
        string cmd1, cmd2, cmd3;
        int id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( arg == "?" )
                {
                        cmd1 = sprintf( "talk %x# info.prop\n", id );
                        cmd2 = sprintf( "talk %x# info.relation\n", id );
                        cmd3 = sprintf( "talk %x# info.tax\n", id );
                        send_user( who, "%c%s", ':', me->get_name() + "：\n您想查询本城哪方面的情况？\n" 
                                ESC "查询本城属性.\n" + cmd1 +
                                ESC "查询外交状况.\n" + cmd2 +
                                ESC "查询税率状况.\n" + cmd3 +
                                ESC "离开.\nCLOSE\n" );
                }
                else if( arg == "prop" )
                {
                        result = sprintf( "Quốc Gia: %-8s  等级：%d 级\n", name1, city->get_level() );

                        result += sprintf( "城主：%s\n", city->get_master_name() );
                        result += sprintf( "副城主：%s、%s\n", city->get_master_name_2(), city->get_master_name_3() );

                        result += sprintf( "城防：%8d  士兵：%8d\n", city->get_defence(), city->get_soldier() );
                        result += sprintf( "装备：%8d  训练：%8d\n", city->get_armor(), city->get_training() );

                        result += sprintf( "资金：%10d\n", city->get_cash() );
                        result += sprintf( "积累资金：%10d\n", city->get_money() );
                        result += sprintf( "粮草：%10d\n", city->get_food() );
                        result += sprintf( "税收：%10d\n", city->get_tax() );

                        result += sprintf( "安定：%8d  疾病：%8d\n", city->get_stability(), city->get_disease() );

                        result += sprintf( "农业：%8d  渔业：%8d  矿业：%8d\n", city->get_agriculture(), city->get_fishculture(), city->get_mining() );
                        result += sprintf( "工业：%8d  商业：%8d\n", city->get_industry(), city->get_commercial() );
                        result += sprintf( "艺术：%8d  教育：%8d  宗教：%8d\n", city->get_arts(), city->get_education(), city->get_religion() );

                        send_user( who, "%c%c%s", 0x51, '0', result );
                }
                else if( arg == "relation" )
                {
                        result = sprintf( "Quốc Gia: %s\n\n", name1 );

                        if( name1 != "Tề Quốc" ) result += sprintf( "Tề Quốc：%s(友好度 %4d)\n", city->get_relation_name(1), city->get_friend(1) );
                        if( name1 != "Hàn Quốc" ) result += sprintf( "Hàn Quốc：%s(友好度 %4d)\n", city->get_relation_name(2), city->get_friend(2) );
                        if( name1 != "Triệu Quốc" ) result += sprintf( "Triệu Quốc：%s(友好度 %4d)\n", city->get_relation_name(3), city->get_friend(3) );
                        if( name1 != "Ngụy Quốc" ) result += sprintf( "Ngụy Quốc：%s(友好度 %4d)\n", city->get_relation_name(4), city->get_friend(4) );
                        if( name1 != "Tần Quốc" ) result += sprintf( "Tần Quốc：%s(友好度 %4d)\n", city->get_relation_name(5), city->get_friend(5) );
                        if( name1 != "Sở Quốc" ) result += sprintf( "Sở Quốc：%s(友好度 %4d)\n", city->get_relation_name(6), city->get_friend(6) );
                        if( name1 != "Yên Quốc" ) result += sprintf( "Yên Quốc：%s(友好度 %4d)\n", city->get_relation_name(7), city->get_friend(7) );

                        send_user( who, "%c%c%s", 0x51, '0', result );
                }
                else if( arg == "tax" )
                {
                        result = sprintf( "Quốc Gia: %s\n\n", name1 );

                        result += sprintf( "本国人买入税：%2d%%\n", city->get_buy_tax() );
                        result += sprintf( "本国人卖出税：%2d%%\n", city->get_sell_tax() );
                        result += sprintf( "外地人买入税：%2d%%\n", city->get_buy_tax_2() );
                        result += sprintf( "外地人卖出税：%2d%%\n\n", city->get_sell_tax_2() );
                        result += sprintf( "日税收分红率：%2d%%\n", city->get_tax_2_cash() );

                        send_user( who, "%c%c%s", 0x51, '0', result );
                }
        }
}

// 函数：设置税率
void do_tax( object who, object me, string arg )
{
        object city;
        string result;
        string name1, name2;
        string cmd1, cmd2, cmd3, cmd4, cmd5;
        int tax, id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2 
        &&    ( who->get_id() == me->get_master() || who->get_id() == me->get_master_2() || who->get_id() == me->get_master_3() )
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( arg == "?" )
                {
                        cmd1 = sprintf( ESC "本国人买入税.(%d%%)\ntalk %x# tax.1.?\n", city->get_buy_tax(), id );
                        cmd2 = sprintf( ESC "本国人卖出税.(%d%%)\ntalk %x# tax.2.?\n", city->get_sell_tax(), id );
                        cmd3 = sprintf( ESC "外地人买入税.(%d%%)\ntalk %x# tax.3.?\n", city->get_buy_tax_2(), id );
                        cmd4 = sprintf( ESC "外地人卖出税.(%d%%)\ntalk %x# tax.4.?\n", city->get_sell_tax_2(), id );
                        cmd5 = sprintf( ESC "日税收分红率.(%d%%)\ntalk %x# tax.5.?\n", city->get_tax_2_cash(), id );
                        send_user( who, "%c%s", ':', me->get_name() + "：\n您想设定本城哪方面的税率？(消耗 10 体力)\n" +
                                cmd1 + cmd2 + cmd3 + cmd4 + cmd5 + 
                                ESC "我再想想……\nCLOSE\n" );
                }
                else if( arg == "1.?" )
                {
                        send_user( who, "%c%c%d%s", '?', 1, 20, sprintf( "%s：\n目前本国人买入税是 %d%%，请问您想改为多少？(范围：1～20%%)\n" 
                                ESC "talk %x# tax.1.%%s\n", me->get_name(), city->get_buy_tax(), id ) );
                }
                else if( arg == "2.?" )
                {
                        send_user( who, "%c%c%d%s", '?', 1, 20, sprintf( "%s：\n目前本国人卖出税是 %d%%，请问您想改为多少？(范围：1～20%%)\n" 
                                ESC "talk %x# tax.2.%%s\n", me->get_name(), city->get_sell_tax(), id ) );
                }
                else if( arg == "3.?" )
                {
                        send_user( who, "%c%c%d%s", '?', 1, 20, sprintf( "%s：\n目前外地人买入税是 %d%%，请问您想改为多少？(范围：1～20%%)\n" 
                                ESC "talk %x# tax.3.%%s\n", me->get_name(), city->get_buy_tax_2(), id ) );
                }
                else if( arg == "4.?" )
                {
                        send_user( who, "%c%c%d%s", '?', 1, 20, sprintf( "%s：\n目前外地人卖出税是 %d%%，请问您想改为多少？(范围：1～20%%)\n" 
                                ESC "talk %x# tax.4.%%s\n", me->get_name(), city->get_sell_tax_2(), id ) );
                }
                else if( arg == "5.?" )
                {
                        send_user( who, "%c%c%d%s", '?', 1, 80, sprintf( "%s：\n目前日税收分红率是 %d%%，请问您想改为多少？(范围：40～80%%)\n" 
                                ESC "talk %x# tax.5.%%s\n", me->get_name(), city->get_tax_2_cash(), id ) );
                }
                else if( sscanf(arg, "1.%d", tax) )
                {
                        if( who->get_strength() < 10 )
                        {
                                send_user(who, "%c%s", '!', "设置买入税要 10 点体力.");
                                return;
                        }
                        if( tax < 1 || tax > 20 )
                        {
                                send_user(who, "%c%s", '!', "买入税得在 1～20%% 之间.");
                                return;
                        }
                        result = sprintf( HIY "城主%s把本国人买入税设为 %d%%.", who->get_name(), tax );
                        FAMILY_D->city_channel(name1, 0, result);
                        city->set_buy_tax(tax);
                        who->add_strength(-10);
                }
                else if( sscanf(arg, "2.%d", tax) )
                {
                        if( who->get_strength() < 10 )
                        {
                                send_user(who, "%c%s", '!', "设置卖出税要 10 点体力.");
                                return;
                        }
                        if( tax < 1 || tax > 20 )
                        {
                                send_user(who, "%c%s", '!', "卖出税得在 1～20%% 之间.");
                                return;
                        }
                        result = sprintf( HIY "城主%s把本国人卖出税设为 %d%%.", who->get_name(), tax );
                        FAMILY_D->city_channel(name1, 0, result);
                        city->set_sell_tax(tax);
                        who->add_strength(-10);
                }
                else if( sscanf(arg, "3.%d", tax) )
                {
                        if( who->get_strength() < 10 )
                        {
                                send_user(who, "%c%s", '!', "设置买入税要 10 点体力.");
                                return;
                        }
                        if( tax < 1 || tax > 20 )
                        {
                                send_user(who, "%c%s", '!', "买入税得在 1～20%% 之间.");
                                return;
                        }
                        result = sprintf( HIY "城主%s把外地人买入税设为 %d%%.", who->get_name(), tax );
                        FAMILY_D->city_channel(name1, 0, result);
                        city->set_buy_tax_2(tax);
                        who->add_strength(-10);
                }
                else if( sscanf(arg, "4.%d", tax) )
                {
                        if( who->get_strength() < 10 )
                        {
                                send_user(who, "%c%s", '!', "设置卖出税要 10 点体力.");
                                return;
                        }
                        if( tax < 1 || tax > 20 )
                        {
                                send_user(who, "%c%s", '!', "卖出税得在 1～20%% 之间.");
                                return;
                        }
                        result = sprintf( HIY "城主%s把外地人卖出税设为 %d%%.", who->get_name(), tax );
                        FAMILY_D->city_channel(name1, 0, result);
                        city->set_sell_tax_2(tax);
                        who->add_strength(-10);
                }
                else if( sscanf(arg, "5.%d", tax) )
                {
                        if( who->get_strength() < 10 )
                        {
                                send_user(who, "%c%s", '!', "设置分红率要 10 点体力.");
                                return;
                        }
                        if( tax < 40 || tax > 80 )
                        {
                                send_user(who, "%c%s", '!', "分红率得在 40～80%% 之间.");
                                return;
                        }
                        result = sprintf( HIY "城主%s把日税收分红率设为 %d%%.", who->get_name(), tax );
                        FAMILY_D->city_channel(name1, 0, result);
                        city->set_tax_2_cash(tax);
                        who->add_strength(-10);
                }
        }
}

// 函数：设置、领取薪水
void do_salary( object who, object me, string arg )
{
        object city;
        string result;
        string name1, name2;
        string cmd1, cmd2, cmd3;
        int salary, id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( !arg )    // 领取薪水
                {
                        result = short_time();  result = result[0..10];
                        if( who->get_id() == me->get_master() )
                        {
                                if( city->get_save_2("salary.date1") != result )
                                {
                                        salary = city->get_save_2("salary.1");
                                        who->add_cash(salary);  who->add_gold_log("task", salary);
                                        who->log_money("薪水", salary);
                                        "/sys/sys/count"->add_income("salary", salary);
                                        city->add_money(-salary);
                                        city->set_save_2("salary.date1", result);
                                        write_user( who, ECHO "%s把今天的薪水 %d 金发给您.", me->get_name(), salary );
                                }
                                else 
                                {
                                        send_user( who, "%c%s", ':', me->get_name() + "：\n您今天已经领过薪水了，明天再来找我吧.\n" );
                                }
                        }
                        else if( who->get_id() == me->get_master_2() )
                        {
                                if( city->get_save_2("salary.date2") != result )
                                {
                                        salary = city->get_save_2("salary.2");
                                        who->add_cash(salary);  who->add_gold_log("task", salary);
                                        who->log_money("薪水", salary);
                                        "/sys/sys/count"->add_income("salary", salary);
                                        city->add_money(-salary);
                                        city->set_save_2("salary.date2", result);
                                        write_user( who, ECHO "%s把今天的薪水 %d 金发给您.", me->get_name(), salary );
                                }
                                else 
                                {
                                        send_user( who, "%c%s", ':', me->get_name() + "：\n您今天已经领过薪水了，明天再来找我吧.\n" );
                                }
                        }
                        else if( who->get_id() == me->get_master_3() )
                        {
                                if( city->get_save_2("salary.date3") != result )
                                {
                                        salary = city->get_save_2("salary.3");
                                        who->add_cash(salary);  who->add_gold_log("task", salary);
                                        who->log_money("薪水", salary);
                                        "/sys/sys/count"->add_income("salary", salary);
                                        city->add_money(-salary);
                                        city->set_save_2("salary.date3", result);
                                        write_user( who, ECHO "%s把今天的薪水 %d 金发给您.", me->get_name(), salary );
                                }
                                else 
                                {
                                        send_user( who, "%c%s", ':', me->get_name() + "：\n您今天已经领过薪水了，明天再来找我吧.\n" );
                                }
                        }
                }
                else if( who->get_id() == me->get_master() )    // 更改薪水
                {
                        if( arg == "?" )
                        {
                                cmd1 = sprintf( "",  );
                                cmd2 = sprintf( "", id );
                                cmd3 = sprintf( "", id );
                                cmd1 = sprintf( ESC "城主我的薪水.(%d 金)\ntalk %x# salary.1.?\n", city->get_save_2("salary.1"), id );
                                cmd2 = sprintf( ESC "第一副城主的薪水.(%d 金)\ntalk %x# salary.2.?\n", city->get_save_2("salary.2"), id );
                                cmd3 = sprintf( ESC "第二副城主的薪水.(%d 金)\ntalk %x# salary.3.?\n", city->get_save_2("salary.3"), id );
                                send_user( who, "%c%s", ':', me->get_name() + "：\n您想设定谁的薪水？(消耗 50 体力)\n" +
                                        cmd1 + cmd2 + cmd3 +
                                        ESC "我再想想……\nCLOSE\n" );
                        }
                        else if( arg == "1.?" )
                        {
                                send_user( who, "%c%c%d%s", '?', 1, 100000, sprintf( "%s：\n您每天的薪水是 %d 金，请问您想改为多少？(范围：10000～100000)\n" 
                                        ESC "talk %x# salary.1.%%s\n", me->get_name(), city->get_save_2("salary.1"), id ) );
                        }
                        else if( arg == "2.?" )
                        {
                                send_user( who, "%c%c%d%s", '?', 1, 100000, sprintf( "%s：\n第一副城主每天的薪水是 %d 金，请问您想改为多少？(范围：10000～100000)\n" 
                                        ESC "talk %x# salary.2.%%s\n", me->get_name(), city->get_save_2("salary.2"), id ) );
                        }
                        else if( arg == "3.?" )
                        {
                                send_user( who, "%c%c%d%s", '?', 1, 100000, sprintf( "%s：\n第二副城主每天的薪水是 %d 金，请问您想改为多少？(范围：10000～100000)\n" 
                                        ESC "talk %x# salary.3.%%s\n", me->get_name(), city->get_save_2("salary.3"), id ) );
                        }
                        else if( sscanf(arg, "1.%d", salary) )
                        {
                                if( who->get_strength() < 50 )
                                {
                                        send_user(who, "%c%s", '!', "设置薪水要 50 点体力.");
                                        return;
                                }
                                if( salary < 10000 || salary > 100000 )
                                {
                                        send_user(who, "%c%s", '!', "薪水得在 10000～100000 之间.");
                                        return;
                                }
                                result = sprintf( HIY "城主%s把自己的薪水设为每天 %d 金.", who->get_name(), salary );
                                FAMILY_D->city_channel(name1, 0, result);
                                city->set_save_2("salary.1", salary);
                                who->add_strength(-50);
                        }
                        else if( sscanf(arg, "2.%d", salary) )
                        {
                                if( who->get_strength() < 50 )
                                {
                                        send_user(who, "%c%s", '!', "设置薪水要 50 点体力.");
                                        return;
                                }
                                if( salary < 10000 || salary > 100000 )
                                {
                                        send_user(who, "%c%s", '!', "薪水得在 10000～100000 之间.");
                                        return;
                                }
                                result = sprintf( HIY "城主%s把第一副城主的薪水设为每天 %d 金.", who->get_name(), salary );
                                FAMILY_D->city_channel(name1, 0, result);
                                city->set_save_2("salary.2", salary);
                                who->add_strength(-50);
                        }
                        else if( sscanf(arg, "3.%d", salary) )
                        {
                                if( who->get_strength() < 50 )
                                {
                                        send_user(who, "%c%s", '!', "设置薪水要 50 点体力.");
                                        return;
                                }
                                if( salary < 10000 || salary > 100000 )
                                {
                                        send_user(who, "%c%s", '!', "薪水得在 10000～100000 之间.");
                                        return;
                                }
                                result = sprintf( HIY "城主%s把第二副城主的薪水设为每天 %d 金.", who->get_name(), salary );
                                FAMILY_D->city_channel(name1, 0, result);
                                city->set_save_2("salary.3", salary);
                                who->add_strength(-50);
                        }
                }
        }
}
