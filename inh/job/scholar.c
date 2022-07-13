
#include <ansi.h>
#include <skill.h>

// 函数：授课处理
void do_teach( object me, object who, string arg )
{
        if( !me->is_scholar() )
        {
                send_user(me, "%c%s", '!', "您不是书生，不懂得授课.");
                return;
        }
        if( gone_time( me->get_time("work") ) < 10 )
        {
                send_user(me, "%c%s", '!', "Xin chờ 1 chút.");
                return;
        }
        if( me == who )
        {
                send_user(me, "%c%s", '!', "您不能对自己授课.");
                return;
        }
        if( who->is_die() )
        {
                send_user(me, "%c%s", '!', "您不能对死人授课.");
                return;
        }
        if(     me->get_gift_ra() < who->get_gift_ra() 
        &&      me->get_gift_zy() < who->get_gift_zy() 
        &&      me->get_gift_zs() < who->get_gift_zs() 
        &&      me->get_gift_cx() < who->get_gift_cx() 
        &&      me->get_gift_yg() < who->get_gift_yg() 
        &&      me->get_gift_zm() < who->get_gift_zm() )
        {
                send_user(me, "%c%s", '!', "您能力不够，不能授课.");
                return;
        }
        if( me->get_strength() < 1 )
        {
                send_user(me, "%c%s", '!', "Điểm thể lực không đủ 1.");
                return;
        }

        who->to_front_eachother(me);
        write_user( me, ECHO "您打开书本，一本正经地给%s讲课...", who->get_name() );
        write_user( who, ECHO "%s打开书本，一本正经地给您讲课...", me->get_name() );

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 04011, 10, OVER_BODY, PF_ONCE );

        me->set_time( "work", time() );
        call_out( "do_teach_finish", 10, me, who, arg );
}

// 函数：授课结束
void do_teach_finish( object me, object who, string arg )
{
        mapping skls;
        string *name, gift;
        int i, size, *id = ({ });
        int level, z, x, y, p;

        if( !me || !who ) return;

        if( distance_between(who, me) > 1 )
        {
                write_user( me, ECHO "授课太枯燥，%s已经走开了.", who->get_name() );
                return;
        }
        if( !me->is_scholar() )    // 再次确认，防换职业 level 的 BUG
        {
                send_user(me, "%c%s", '!', "您不是书生，不懂得授课.");
                return;
        }

        if( me->get_gift_ra()*9/10 > who->get_gift_ra()+level+1 ) id += ({ 1 });
        if( me->get_gift_zy()*9/10 > who->get_gift_zy()+level+1 ) id += ({ 2 });
        if( me->get_gift_zs()*9/10 > who->get_gift_zs()+level+1 ) id += ({ 3 });
        if( me->get_gift_cx()*9/10 > who->get_gift_cx()+level+1 ) id += ({ 4 });
        if( me->get_gift_yg()*9/10 > who->get_gift_yg()+level+1 ) id += ({ 5 });
        if( me->get_gift_zm()*9/10 > who->get_gift_zm()+level+1 ) id += ({ 6 });

        if( !( size = sizeof(id) ) )
        {
                send_user(me, "%c%s", '!', "您能力不够，不能授课.");
                return;
        }

        level = me->get_occupation_level();

        me->add_strength(-1);    // 体力 -1, 书生经验 +10, 仁爱 +10, 智谋 +10, 声望 +1, 国家贡献 +1
        me->add_occupation_exp(10);
        me->add_gift_ra(10);
        me->add_gift_zm(10);
        me->add_repute(1);
        me->add_contribute(1);
        me->add_cash(level + 10);  me->add_gold_log("task", level + 10);
        me->log_money("书生", level+10);
        "/sys/sys/count"->add_income("task", level+10);
        me->add_exp(level + 10);
        me->add_potential(1);

        switch( id[ random(size) ] )
        {
      default : gift = "仁爱";
                x = level + 1;  p = me->add_gift_ra(1) * 9 / 10;
                if( ( z = who->add_gift_ra(x) ) > p ) { who->set_gift_ra(p);  x -= z - p; }
                break;
       case 2 : gift = "正义";
                x = level + 1;  p = me->add_gift_zy(1) * 9 / 10;
                if( ( z = who->add_gift_zy(x) ) > p ) { who->set_gift_zy(p);  x -= z - p; }
                break;
       case 3 : gift = "忠实";
                x = level + 1;  p = me->add_gift_zs(1) * 9 / 10;
                if( ( z = who->add_gift_zs(x) ) > p ) { who->set_gift_zs(p);  x -= z - p; }
                break;
       case 4 : gift = "诚信";
                x = level + 1;  p = me->add_gift_cx(1) * 9 / 10;
                if( ( z = who->add_gift_cx(x) ) > p ) { who->set_gift_cx(p);  x -= z - p; }
                break;
       case 5 : gift = "勇敢";
                x = level + 1;  p = me->add_gift_yg(1) * 9 / 10;
                if( ( z = who->add_gift_yg(x) ) > p ) { who->set_gift_yg(p);  x -= z - p; }
                break;
       case 6 : gift = "智谋";
                x = level + 1;  p = me->add_gift_zm(1) * 9 / 10;
                if( ( z = who->add_gift_zm(x) ) > p ) { who->set_gift_zm(p);  x -= z - p; }
                break;
        }

        write_user( me, ECHO "%s听了您的教诲，觉得收益不少.", who->get_name() );
        write_user( who, ECHO "您听了%s的教诲，觉得收益不少.(%s %+d)", me->get_name(), gift, x );

        write_user( me, ECHO "您的书生经验 +10, 仁爱 +10, 智谋 +10, %s +1, 声望 +1, 国家贡献 +1, 金钱 %+d, 经验 %+d, 潜能 +1.", gift, level + 10, level + 10 );

        if( random(100) > 10 + level / 10 ) return;

        skls = me->get_skill_dbase();
        if( !( size = sizeof(skls) ) ) return;

        z = 0;  p = 0;
        name = keys(skls);
        for( i = 0; i < size; i ++ )
        {
                x = to_int( name[i] );
                y = me->get_skill(x);
                if( y > p )
                {
                        z = x;  p = y;
                }
        }

        if(     z 
        &&    ( y = who->get_skill(z) ) > 0 
        &&      y < p )
        {
                who->improve_skill(z, level * 2 + 2);
        }
}

// 函数：占卜处理
void do_augur( object me, string arg )
{
        object who;

        if( !me->is_scholar() )
        {
                send_user(me, "%c%s", '!', "您不是书生，不懂得占卜.");
                return;
        }
        if( gone_time( me->get_time("work") ) < 10 )
        {
                send_user(me, "%c%s", '!', "Xin chờ 1 chút.");
                return;
        }
        if( me->is_die() )
        {
                send_user(who, "%c%s", '!', "您不能对死人占卜.");
                return;
        }
        if( me->get_strength() < 1 )
        {
                send_user(me, "%c%s", '!', "Điểm thể lực không đủ 1.");
                return;
        }
        if( arg == "?" )
        {
                send_user( me, "%c%c%d%s", '?', 1, 0, "您想给谁占卜？请输入对方的数字ＩＤ：\n"
                                ESC "pf2 00402.%s\n" );
                return;
        }
        if( !( who = find_player(arg) ) )
        {
                send_user(me, "%c%s", '!', "无法找到这位玩家.");
                return;
        }

        write_user( me, ECHO "您拿出龟甲，诚心诚意为%s占卜...", who->get_name() );

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 04021, 10, OVER_BODY, PF_ONCE );

        me->set_time( "work", time() );
        call_out( "do_augur_finish", 10, me, who, arg );
}

// 函数：占卜结束
void do_augur_finish( object me, object who, string arg )
{
        int level;

        if( !me || !who ) return;

        if( !me->is_scholar() )    // 再次确认，防换职业 level 的 BUG
        {
                send_user(me, "%c%s", '!', "您不是书生，不懂得占卜.");
                return;
        }

        level = me->get_occupation_level();

        if( random(100) < 75 )
        {
                switch( random(3) )
                {
              default : write_user( me, ECHO "你占得乾卦，见群龙无首，大吉.对方气血、法力增加." );
                        who->set_hp( range_value( who->get_hp() + level * 2 + 20, 1, who->get_max_hp() ) );
                        who->set_mp( range_value( who->get_mp() + level * 2 + 20, 1, who->get_max_mp() ) );
                        break;
               case 1 : write_user( me, ECHO "你占得坤卦，安贞，吉.对方气血增加." );
                        who->set_hp( range_value( who->get_hp() + level * 2 + 20, 1, who->get_max_hp() ) );
                        break;
               case 2 : write_user( me, ECHO "你占得泰卦，小往大来，吉亨.对方法力增加." );
                        who->set_mp( range_value( who->get_mp() + level * 2 + 20, 1, who->get_max_mp() ) );
                        break;
                }
                write_user( who, ECHO "你忽然觉得心里涌出一股暖流，整个人懒洋洋地，舒服无比." );
        }
        else 
        {
                switch( random(4) )
                {
               case 0 : write_user( me, ECHO "你占得归妹卦，凶." );
               case 1 : write_user( me, ECHO "你占得节卦，不出门庭，凶." );
               case 2 : write_user( me, ECHO "你占得讼卦，惕中吉，终凶." );
               case 3 : write_user( me, ECHO "你占得否卦，不利君子贞，大往小来." );
                }
                write_user( who, ECHO "你不由自主地打了几个寒颤." );
        }

        me->add_strength(-1);    // 体力 -1, 书生经验 +10, 仁爱 +10, 智谋 +10
        me->add_occupation_exp(10);
        me->add_gift_ra(10);
        me->add_gift_zm(10);
        me->add_exp(level + 10);

        write_user( me, ECHO "您的书生经验 +10, 仁爱 +10, 智谋 +10, 经验 %+d.", level + 10 );
}
