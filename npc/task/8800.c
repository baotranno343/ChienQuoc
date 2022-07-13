
#include <npc.h>
#include <ansi.h>
#include <city.h>
#include <music.h>

inherit OFFICER;

void do_food( string arg );
void do_armor( string arg );

// 函数：获取人物造型
int get_char_picid() { return 9388; }

// 函数：构造处理
void create()
{
        set_name( "军备商人" );
        set_char_picid(5401);

        set_2( "talk", ([
                "armor"         : (: do_armor :),
                "food"          : (: do_food :),
        ]) );

        setup();

        if( !clonep( this_object() ) ) return;

        CALLOUT_D->add_hour_item( this_object() );
}

// 函数：复位处理(１小时)
void reset() 
{
        int p;

        if( p = XY_D->get_city_point( -1, IS_CHAR_BLOCK ) )
        {
                this_object()->add_to_scene(p / 1000000, ( p % 1000000 ) / 1000, p % 1000, 3);
        }
}

// 函数：对话处理
void do_look( object who )
{
        string cmd;
        int id = getoid( this_object() );

        if( who->is_soldier() )
        {
                cmd = sprintf( "talk %x# armor\n", id );
                more_look_menu( who, get_name() + "：\n我这里大量出售军粮、装备，您有兴趣看看吗？\n" 
                        ESC "购买装备。\n" + cmd +
                        ESC "离开。\nCLOSE\n" );
        }
        else if( who->is_businessman() )
        {
                cmd = sprintf( "talk %x# food\n", id );
                more_look_menu( who, get_name() + "：\n我这里大量出售军粮、装备，您有兴趣看看吗？\n" 
                        ESC "购买军粮。\n" + cmd +
                        ESC "离开。\nCLOSE\n" );
        }
        else
        {
                send_user( who, "%c%s", ':', get_name() + "：\n我这里大量出售军粮、装备……您还是有事再来找我吧。\n" );
        }
}

// 函数：军粮任务
void do_food( string arg )
{
        object city, me, who;
        string result;
        int level, food, gold, p;

        me = this_object();  who = this_player();

        if( who->is_businessman() && ( city = CITY_D->get_city_object(who) ) )
        {
                if( !who->get("trader.food") )
                {
                        send_user(who, "%c%s", '!', "您得先去接军粮任务。");
                        return;
                }
                if( city->get_food() >= city->get_soldier() * 10 )
                {
                        send_user(who, "%c%s", '!', "城里的军粮已经足够了。");
                        return;
                }
                if( who->get_strength() < 1 )
                {
                        send_user(who, "%c%s", '!', "您现在的体力不够。");
                        return;
                }

                level = who->get_occupation_level();

                city->add_money(-100000);
                p = random(40) + 10;  food = 100 * ( level + p );  city->add_food(food);

                result = sprintf( HIY "%s(%d)执行军粮任务，花费税收十万，买回 %d 军粮。", who->get_name(), who->get_number(), food );
                FAMILY_D->city_channel( city->get_name(), 0, result );

                p = ( p < 35 ) ? 50 : 50 + (p - 35) * 2;  if( p > 80 ) p = 80;
                gold = 5000;

                who->add_strength(-1);    // 体力 -1, 声望 +X
                who->add_repute(p);
                who->add_cash(gold);  who->add_gold_log("task", gold);
                who->log_money("军粮任务", gold);                
                "/sys/sys/count"->add_income("task", gold);

                write_user( who, ECHO "您的声望 %+d, 金钱 %+d。", p, gold );

                who->delete("trader.food");
                reset();
        }
}

// 函数：装备任务
void do_armor( string arg )
{
        object city, me, who;
        string result;
        int level, level2, armor, gold, exp;

        me = this_object();  who = this_player();

        if( who->is_soldier() && ( city = CITY_D->get_city_object(who) ) )
        {
                if( !who->get_2("train.armor") )
                {
                        send_user(who, "%c%s", '!', "您得先去接战备任务。");
                        return;
                }
                if( city->get_armor() >= city->get_soldier() )
                {
                        send_user(who, "%c%s", '!', "城里的装备已经足够了。");
                        return;
                }
                if( who->get_strength() < 1 )
                {
                        send_user(who, "%c%s", '!', "您现在的体力不够。");
                        return;
                }

                level = who->get_occupation_level();
                level2 = who->get_occupation_level( JOB_TRADER );

                city->add_money(-100000);
                armor = (level + level2) * 20 + 100 + random(200);  city->add_armor(armor);

                result = sprintf( HIY "%s(%d)执行战备任务，花费税收十万，买回装备 %d 件。", who->get_name(), who->get_number(), armor );
                FAMILY_D->city_channel( city->get_name(), 0, result );

                who->add_strength(-1);    // 体力 -1, 军官经验 +60, 正义 +60, 忠实 +1, 勇敢 +60, 声望 +6
                who->add_occupation_exp(60);
                who->add_gift_zy(60);
                who->add_gift_zs(1);
                who->add_gift_yg(60);
                who->add_repute(6);
                gold = level * 6 + 60;  who->add_cash(gold);  who->add_gold_log("task", gold);
                who->log_money("战备任务", gold);                
                "/sys/sys/count"->add_income("task", gold);
                exp = level * 6 + 60;  who->add_exp(exp);
                who->add_potential(6);

                send_user( who, "%c%w", 0x0d, MUSIC_TASK );
                write_user( who, ECHO "您的军官经验 +60, 正义 +60, 忠实 +1, 勇敢 +60, 声望 +6, 金钱 %+d, 经验 %+d, 潜能 +6。", gold, exp );

                who->delete_2("train.armor");
                reset();
        }
}
