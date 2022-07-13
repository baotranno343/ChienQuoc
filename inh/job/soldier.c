
#include <ansi.h>
#include <music.h>

#define RASCAL        "/npc/task/8810"

// 函数：城内巡逻
void do_patrol( object who, object me, string arg )
{
        object city, map, npc;
        string rascal;
        string name1, name2;
        int level;
        int z, x, y, p;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2
        &&      who->is_soldier()
        &&      who->get_2("train.patrol")
//      &&      me->is_seller()
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( who->get_strength() < 1 )
                {
                        send_user(who, "%c%s", '!', "Điểm thể lực không đủ 1.");
                        return;
                }

                if(     stringp( rascal = who->get_task("rascal") )
                &&      ( npc = find_char(rascal) ) && npc->is_rascal() )
                {
                        npc->remove_from_scene();    // 清除旧的任务
                        destruct(npc);
                }

                if( !( p = city->get_xy_point(IS_CHAR_BLOCK) ) ) return;

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
                who->set_task("rascal", sprintf( "%x#", getoid(npc) ) );

                npc->set( "task", who->get_number() );
                npc->set("xy.z", z);
                npc->set("xy.x", x);
                npc->set("xy.y", y);

//              tell_user( who, "%s说道：“不瞒您说，最近有%s在%s（%d,%d）惹事生非，闹得左邻右舍不得安宁.”", 
//                      me->get_name(), npc->get_name(), map->get_name(), x, y );
                send_user( who, "%c%s", '!', sprintf( "去" HIY " %s(%d,%d) " NOR "教训" HIY " %s " NOR ".", map->get_name(), x, y, npc->get_name() ) );

                if( who->get_task("rascal#") )
                {
                        who->delete_2("train.patrol");
                }
                else    who->add_strength(-1);    // 已扣体力！！！
        }
}

// 函数：煽动敌方
void do_stir_up( object who, object me, string arg )
{
        object city;
        string name1, name2;
        string id;
        int what;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 != name2 && name2 != ""
        &&      who->is_soldier()
        &&    ( city = CITY_D->get_city_object(who) ) )
        {
                if( gone_time( who->get_time("work") ) < 10 )
                {
                        send_user(who, "%c%s", '!', "Xin chờ 1 chút.");
                        return;
                }
                if( who->get_strength() < 10 )
                {
                        send_user(who, "%c%s", '!', "Điểm thể lực không đủ 1.");
                        return;
                }
                if( arg == "?" )
                {
                        id = sprintf("%x#", getoid(me) );
                        send_user( who, "%c%s", ':', "您打算对哪方面造谣？每次消耗体力 10 点.\n" 
                                ESC "城防.\ntalk " + id + " stir_up.1\n"
                                ESC "士兵.\ntalk " + id + " stir_up.2\n"
                                ESC "装备.\ntalk " + id + " stir_up.3\n"
                                ESC "训练.\ntalk " + id + " stir_up.4\n"
                                ESC "资金.\ntalk " + id + " stir_up.5\n"
                                ESC "粮草.\ntalk " + id + " stir_up.6\n"
                                ESC "税收.\ntalk " + id + " stir_up.7\n"
                                ESC "安定.\ntalk " + id + " stir_up.8\n"
                                ESC "农业.\ntalk " + id + " stir_up.9\n"
                                ESC "渔业.\ntalk " + id + " stir_up.10\n"
                                ESC "矿业.\ntalk " + id + " stir_up.11\n"
                                ESC "工业.\ntalk " + id + " stir_up.12\n"
                                ESC "商业.\ntalk " + id + " stir_up.13\n"
                                ESC "艺术.\ntalk " + id + " stir_up.14\n"
                                ESC "教育.\ntalk " + id + " stir_up.15\n"
                                ESC "宗教.\ntalk " + id + " stir_up.16\n" );
                }
                else if( what = to_int(arg) )
                {
                        switch( what )
                        {
                       case 1 : send_user( who, "%c%s", ':', "您：\n听说早年造城墙的时候下面埋了一些宝物做为镇城之宝." );
                                break;
                       case 2 : send_user( who, "%c%s", ':', "您：\n听说蛮族准备大肆进攻城市，当兵的全要当肉盾了，我们还是快逃吧." );
                                break;
                       case 3 : send_user( who, "%c%s", ':', "您：\n听说现在士兵用的盔甲又厚又重，这样士兵们太辛苦了." );
                                break;
                       case 4 : send_user( who, "%c%s", ':', "您：\n听说有些灵丹妙药，吃下去马上脸上发烫，用来装病是最好的了." );
                                break;
                      default : send_user( who, "%c%s", ':', "您：\n听说有人可以假钱换真钱，那些钱做得简直同真的一样." );
                                break;
                       case 6 : send_user( who, "%c%s", ':', "您：\n听说有一种办法用粮食能酿成美酒，真是太好喝了." );
                                break;
                       case 7 : send_user( who, "%c%s", ':', "您：\n听说有人通过研究法典，找到了些避税的法门." );
                                break;
                       case 8 : send_user( who, "%c%s", ':', "您：\n你知道吗？城主歧视咱们这些人，简直是另眼相看啊." );
                                break;
                       case 9 : send_user( who, "%c%s", ':', "您：\n听说洪水快要来了，赶紧抢收庄稼吧！" );
                                break;
                      case 10 : send_user( who, "%c%s", ':', "您：\n听说用更细小的网孔，可以捕捉到更多的鱼." );
                                break;
                      case 11 : send_user( who, "%c%s", ':', "您：\n矿石可是好东西，听说卖到外地可以赚很多钱啊." );
                                break;
                      case 12 : send_user( who, "%c%s", ':', "您：\n你知道吗？别的城市做工的人，工钱比我们这里高多了." );
                                break;
                      case 13 : send_user( who, "%c%s", ':', "您：\n你听说了吗？下个月开始，税收要大大提高了." );
                                break;
                      case 14 : send_user( who, "%c%s", ':', "您：\n民以食为天，你说那些唱歌弹琴的，四体不勤，五谷不分，有什么用？" );
                                break;
                      case 15 : send_user( who, "%c%s", ':', "您：\n绝圣弃智，民利百倍；绝仁弃义，民复孝慈；绝巧弃利，盗贼无有." );
                                break;
                      case 16 : send_user( who, "%c%s", ':', "您：\n世间没有什么神仙，万事万物都有它的缘由，没有鬼神虚幻之事." );
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
        int level, exp;
        int p;

        if( !who || !me ) return;

        if( distance_between(me, who) > 1 )
        {
                write_user( who, ECHO "造谣不成功，%s已经走开了.", me->get_name() );
                return;
        }

        level = who->get_occupation_level();

        if( random(100) < 25 )
        {
                who->add_strength(-10);    // 体力 -10, 军官经验 +20, 正义 +20, 忠实 +1, 勇敢 +20, 声望 +20
                who->add_occupation_exp(20);
                who->add_gift_zy(20);
                who->add_gift_zs(1);
                who->add_gift_yg(20);
                who->add_repute(20);
                exp = level * 20 + 200;  who->add_exp(exp);
                who->add_potential(20);

                p = - random(level / 10) - 1;

                if( city = CITY_D->get_city_object(me) ) switch( what )
                {
               case 1 : send_user( who, "%c%s", ':', sprintf( "%s：\n是吗？真有此事？待我晚上去看看...(城防 %+d)", me->get_name(), p ) );
                        city->add_defence(p);
                        break;
               case 2 : send_user( who, "%c%s", ':', sprintf( "%s：\n啊...我那小儿子今年刚入的伍，我要想办法让他赶快回来.(士兵 %+d)", me->get_name(), p ) );
                        city->add_soldier(p);
                        break;
               case 3 : send_user( who, "%c%s", ':', sprintf( "%s：\n就是呀，我家那小子正向我抱怨呢，我让他偷偷换套轻的吧.(装备 %+d)", me->get_name(), p *= 10 ) );
                        city->add_armor(p);
                        break;
               case 4 : send_user( who, "%c%s", ':', sprintf( "%s：\n这个真不错，我家那小子训练的时候正好可以用上.(训练 %+d)", me->get_name(), p *= 10 ) );
                        city->add_training(p);
                        break;
              default : send_user( who, "%c%s", ':', sprintf( "%s：\n我要换一批！这次发财了，嘿嘿嘿...(资金 %+d)", me->get_name(), p ) );
                        city->add_cash(p);
                        break;
               case 6 : send_user( who, "%c%s", ':', sprintf( "%s：\n啊，城中正好有大批的军粮...赚到了.(粮草 %+d)", me->get_name(), p ) );
                        city->add_food(p);
                        break;
               case 7 : send_user( who, "%c%s", ':', sprintf( "%s：\n我早就想学了，现在可以少交点税钱了.(税收 %+d)", me->get_name(), p ) );
                        city->add_tax(p);
                        break;
               case 8 : send_user( who, "%c%s", ':', sprintf( "%s：\n这太可恶了，真是官逼民反啊.(安定 %+d)", me->get_name(), p = -2 ) );
                        city->add_stability(p);
                        break;
               case 9 : send_user( who, "%c%s", ':', sprintf( "%s：\n我马上去收割家里种的庄稼，多谢您的提醒.(农业 %+d)", me->get_name(), p ) );
                        city->add_agriculture(p);
                        break;
              case 10 : send_user( who, "%c%s", ':', sprintf( "%s：\n嗯，说得极是，我马上去试试.(渔业 %+d)", me->get_name(), p ) );
                        city->add_fishculture(p);
                        break;
              case 11 : send_user( who, "%c%s", ':', sprintf( "%s：\n真的吗？我明天多动员些亲戚朋友去挖.(矿业 %+d)", me->get_name(), p ) );
                        city->add_mining(p);
                        break;
              case 12 : send_user( who, "%c%s", ':', sprintf( "%s：\n老板也太黑心了，我这么努力还有什么用呢？(工业 %+d)", me->get_name(), p ) );
                        city->add_industry(p);
                        break;
              case 13 : send_user( who, "%c%s", ':', sprintf( "%s：\n还让不让人话了？还是打消经商的念头吧.(商业 %+d)", me->get_name(), p ) );
                        city->add_commercial(p);
                        break;
              case 14 : send_user( who, "%c%s", ':', sprintf( "%s：\n是啊，又不能当饭吃，这种人简直是蛀虫.(艺术 %+d)", me->get_name(), p ) );
                        city->add_arts(p);
                        break;
              case 15 : send_user( who, "%c%s", ':', sprintf( "%s：\n真有道理，还是让我家那小子停止读书，专心种地吧.(教育 %+d)", me->get_name(), p ) );
                        city->add_education(p);
                        break;
              case 16 : send_user( who, "%c%s", ':', sprintf( "%s：\n阁下教训得是，我不再相信鬼神之事了.(宗教 %+d)", me->get_name(), p ) );
                        city->add_religion(p);
                        break;
                }

                send_user( who, "%c%w", 0x0d, MUSIC_TASK );
                write_user( who, ECHO "您的军官经验 +20, 正义 +20, 忠实 +1, 勇敢 +20, 声望 +20, 经验 %+d, 潜能 +20.", exp );
        }
        else
        {
                who->add_strength(-10);    // 体力 -10, 军官经验 +1, 正义 +1, 忠实 +1, 勇敢 +1, 声望 +1
                who->add_occupation_exp(1);
                who->add_gift_zy(1);
                who->add_gift_zs(1);
                who->add_gift_yg(1);
                who->add_repute(1);
                exp = 1;  who->add_exp(exp);
                who->add_potential(1);

                switch( what )
                {
               case 1 : send_user( who, "%c%s", ':', sprintf( "%s：\n可它是镇城的宝物，不能去挖呀.", me->get_name() ) );
                        break;
               case 2 : send_user( who, "%c%s", ':', sprintf( "%s：\n保家卫国，是士兵的责任，也是他的光荣.", me->get_name() ) );
                        break;
               case 3 : send_user( who, "%c%s", ':', sprintf( "%s：\n当兵就要流血流汗，辛苦些训练才有效果.", me->get_name() ) );
                        break;
               case 4 : send_user( who, "%c%s", ':', sprintf( "%s：\n这种宵小勾当，我不屑于做.", me->get_name() ) );
                        break;
              default : send_user( who, "%c%s", ':', sprintf( "%s：\n这种事情是要坐牢的呀.", me->get_name() ) );
                        break;
               case 6 : send_user( who, "%c%s", ':', sprintf( "%s：\n现在粮食宝贵，酿成酒真是浪费.", me->get_name() ) );
                        break;
               case 7 : send_user( who, "%c%s", ':', sprintf( "%s：\n我是老实本份人家，不学这些歪门邪道的东西.", me->get_name() ) );
                        break;
               case 8 : send_user( who, "%c%s", ':', sprintf( "%s：\n话也不能这样说，我看我们城主的为人还是不错的.", me->get_name() ) );
                        break;
               case 9 : send_user( who, "%c%s", ':', sprintf( "%s：\n我看天时蛮好，不象有洪水的样子，您过虑啦.", me->get_name() ) );
                        break;
              case 10 : send_user( who, "%c%s", ':', sprintf( "%s：\n这不是一个好主意，鱼要是绝迹我们就惨了.", me->get_name() ) );
                        break;
              case 11 : send_user( who, "%c%s", ':', sprintf( "%s：\n我不懂挖矿的技术，随便乱挖会适得其反的.", me->get_name() ) );
                        break;
              case 12 : send_user( who, "%c%s", ':', sprintf( "%s：\n各人有各人的命啊，我还是做好自己的本份吧.", me->get_name() ) );
                        break;
              case 13 : send_user( who, "%c%s", ':', sprintf( "%s：\n我没有听说啊，是不是谣言呀？", me->get_name() ) );
                        break;
              case 14 : send_user( who, "%c%s", ':', sprintf( "%s：\n你不觉得听到他们的音乐，一天的疲劳也会消除吗？", me->get_name() ) );
                        break;
              case 15 : send_user( who, "%c%s", ':', sprintf( "%s：\n如果你也同意这个观点，就不会去读书，也不会跑来和我说这些文绉绉的话了.", me->get_name() ) );
                        break;
              case 16 : send_user( who, "%c%s", ':', sprintf( "%s：\n小孩说话，莫怪莫怪，不要说这些折阴德的事，小心老天怪罪！", me->get_name() ) );
                        break;
                }

                write_user( who, ECHO "您的军官经验 +1, 正义 +1, 忠实 +1, 勇敢 +1, 声望 +1, 经验 %+d, 潜能 +1.", exp );
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
        &&      who->get_2("train.soldier")
        &&    ( city = CITY_D->get_city_object(who) )
        &&     !city->is_soldier_enough() )
        {
                if( gone_time( who->get_time("work") ) < 10 )
                {
                        send_user(who, "%c%s", '!', "Xin chờ 1 chút.");
                        return;
                }
                if( who->get_strength() < 1 )
                {
                        send_user(who, "%c%s", '!', "Điểm thể lực không đủ 1.");
                        return;
                }

                send_user( who, "%c%s", ':', "您：\n您有兴趣当兵去吃军粮吗？" );

                who->set_time( "work", time() );
                call_out( "do_soldier_finish", 10, who, me, arg );
        }
}

// 函数：征兵结束
void do_soldier_finish( object who, object me, string arg )
{
        object city;
        int level, soldier, gold, exp;

        if( !who || !me ) return;

        if( distance_between(me, who) > 1 )
        {
                write_user( who, ECHO "%s对征兵没兴趣，已经走开了.", me->get_name() );
                return;
        }

        if( city = CITY_D->get_city_object(who) ) city->add_money(-10000);

        level = who->get_occupation_level();

        if( random(100) < level + 20 )
        {
                soldier = level * 5 + who->get_gift_zm() / 100 + 200;
                if( city ) city->add_soldier(soldier);
                send_user( who, "%c%s", ':', sprintf( "%s：\n既然阁下这么看得起我，自当效劳.我会带领一批儿郎入伍.(士兵 %+d)", me->get_name(), soldier ) );

                who->add_strength(-1);    // 体力 -1, 军官经验 +40, 正义 +40, 忠实 +1, 勇敢 +40, 声望 +4, 国家贡献 +1
                who->add_occupation_exp(40);
                who->add_gift_zy(40);
                who->add_gift_zs(1);
                who->add_gift_yg(40);
                who->add_repute(4);
                who->add_contribute(1);
                gold = level * 4 + 40;  who->add_cash(gold);  who->add_gold_log("task", gold);
                who->log_money("军官", gold);
                "/sys/sys/count"->add_income("task", gold);
                exp = level * 4 + 40;  who->add_exp(exp);
                who->add_potential(4);

                send_user( who, "%c%w", 0x0d, MUSIC_TASK );
                write_user( who, ECHO "您的军官经验 +40, 正义 +40, 忠实 +1, 勇敢 +40, 声望 +4, 国家贡献 +1, 金钱 %+d, 经验 %+d, 潜能 +4.", gold, exp );
        }
        else
        {
                who->add_strength(-1);
                send_user( who, "%c%s", ':', sprintf( "%s：\n当兵又累又辛苦，还会随时送命，你还是省省吧！", me->get_name() ) );
        }

        who->delete_2("train.soldier");
}
