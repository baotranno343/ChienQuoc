
#include <ansi.h>
#include <skill.h>
#include <effect.h>

// 变量：水果物品表
string *FruitTable = ({ 
        "/item/33/3350",
        "/item/33/3351",
        "/item/33/3352",
        "/item/33/3353",
        "/item/33/3354",
        "/item/33/3355",
        "/item/33/3356",
        "/item/33/3357",
        "/item/33/3358",
        "/item/33/3359",
        "/item/33/3360",
        "/item/33/3361",
});

int sizeof_fruit = sizeof(FruitTable);

// 变量：小吃物品表
string *FoodTable = ({ 
        "/item/34/3401",
        "/item/34/3402",
        "/item/34/3403",
        "/item/34/3404",
        "/item/34/3405",
        "/item/34/3406",
        "/item/34/3407",
        "/item/34/3408",
        "/item/34/3410",
        "/item/34/3411",
        "/item/34/3412",
        "/item/34/3413",
        "/item/34/3414",
        "/item/34/3415",
        "/item/34/3420",
        "/item/34/3421",
        "/item/34/3422",
        "/item/34/3423",
        "/item/34/3424",
        "/item/34/3425",
});

int sizeof_food = sizeof(FoodTable);

// 函数：跳舞处理
void do_dance( object me, object who, string arg )
{
        if( !me->is_actor() )
        {
                send_user(me, "%c%s", '!', "Bạn không phải nghệ sĩ.");
                return;
        }
        if( gone_time( me->get_time("work") ) < 10 )
        {
                send_user(me, "%c%s", '!', "Xin chờ 1 chút.");
                return;
        }
        if( me == who )
        {
                send_user(me, "%c%s", '!', "Không thể khiêu vũ với chính mình.");
                return;
        }
        if( who->is_die() )
        {
                send_user(me, "%c%s", '!', "Không thể khiêu vũ với người chết.");
                return;
        }
        if( me->get_strength() < 1 )
        {
                send_user(me, "%c%s", '!', "Điểm thể lực không đủ 1.");
                return;
        }

        who->to_front_eachother(me);
        write_user( me, ECHO "伴随着优美的旋律，您在%s身旁翩翩起舞...", who->get_name() );
        write_user( who, ECHO "伴随着优美的旋律，%s在您身旁翩翩起舞...", me->get_name() );

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 01011, 10, OVER_BODY, PF_ONCE );

        me->set_time( "work", time() );
        call_out( "do_dance_finish", 10, me, who, arg );
}

// 函数：跳舞结束
void do_dance_finish( object me, object who, string arg )
{
        object obj;
        string file;
        int level, gold, p;

        if( !me || !who ) return;

        if( distance_between(who, me) > 1 )
        {
                write_user( me, ECHO "跳舞没效果，%s已经走开了.", who->get_name() );
                return;
        }
        if( !me->is_actor() )    // 再次确认，防换职业 level 的 BUG
        {
                send_user(me, "%c%s", '!', "Bạn không phải nghệ sĩ.");
                return;
        }

        level = me->get_occupation_level();
        if( level < 1 ) level = 1;    // 防止后面除数为０

        who->set("actor.dance", level + 1);
        set_effect_2(who, EFFECT_CHAR_DANCE, 18, 10);
        CHAR_CHAR_D->init_loop_perform(who);
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 01011, 10, OVER_BODY, PF_ONCE );

        me->add_strength(-1);    // 体力 -1, 艺人经验 +10, 忠实 +1, 勇敢 +10, 智谋 + 10, 声望 +10, 国家贡献 +1
        me->add_occupation_exp(10);
        me->add_gift_zs(1);
        me->add_gift_yg(10);
        me->add_gift_zm(10);
        me->add_repute(10);
        me->add_contribute(1);
        me->add_exp(level + 10);
        me->add_potential(1);

        write_user( who, ECHO "您看了%s的舞蹈，只觉得心旷神怡.", me->get_name() );
        write_user( me, ECHO "%s看了您的舞蹈，只觉得心旷神怡.", who->get_name() );

        if( who->is_user() && random(100) < level * 5 / ( level + who->get_level() ) + 1 )
        {
                gold = 50 + level * 5;
                if( who->get_cash() < gold ) gold = who->get_cash();

                who->add_cash(-gold);  who->add_gold_log("give", gold);
                who->log_money("看舞蹈", -gold);
                me->add_cash(gold);  me->add_gold_log("give2", gold);
                who->log_money("舞蹈", gold);

                write_user( who, ECHO "您陶醉在%s的舞姿中，扔下 %d 金.", me->get_name(), gold );
                write_user( me, ECHO "%s陶醉在您的舞姿中，扔下 %d 金.", who->get_name(), gold );
        }
        else if( who->is_npc() && random(100) < 20 )
        {
                if( random(100) < 50 )    // 得到金钱
                {
                        gold = 50 + level * 5;
                        me->add_cash(gold);  me->add_gold_log("give2", gold);
                        me->log_money("舞蹈", gold);
                        "/sys/sys/count"->add_income("actor", gold);
                        write_user( me, ECHO "%s陶醉在您的舞姿中，扔下 %d 金.", who->get_name(), gold );
                }
                else    // 得到物品
                {
                        if( random(100) < 50 )
                        {
                                if( level / 10 < sizeof_fruit )
                                        file = FruitTable[ random(level / 10 + 1) ];
                                else    file = FruitTable[ random(sizeof_fruit) ];
                        }
                        else    file = FoodTable[ random(sizeof_food) ];

                        if( load_object(file) )
                        {
                                obj = new(file);

                                write_user( me, ECHO "%s笑道：“好技艺！这 %s，就当是我送给你的礼物吧.”", 
                                        who->get_name(), obj->get_name() );

                                if( p = obj->move(me, -1) ) obj->add_to_user(p);
                                else destruct(obj);
                        }
                }
        }

        write_user( me, ECHO "您的艺人经验 +10, 忠实 +1, 勇敢 +10, 智谋 +10, 声望 +10, 国家贡献 +1, 经验 %+d, 潜能 +1.", level + 10 );
}

// 函数：唱歌处理
void do_sing( object me, object who, string arg )
{
        if( !me->is_actor() )
        {
                send_user(me, "%c%s", '!', "您不是艺人，不懂得唱歌.");
                return;
        }
        if( gone_time( me->get_time("work") ) < 10 )
        {
                send_user(me, "%c%s", '!', "Xin chờ 1 chút.");
                return;
        }
        if( me == who )
        {
                send_user(me, "%c%s", '!', "您不能对自己唱歌.");
                return;
        }
        if( who->is_die() )
        {
                send_user(me, "%c%s", '!', "您不能对死人唱歌.");
                return;
        }
        if( me->get_strength() < 1 )
        {
                send_user(me, "%c%s", '!', "Điểm thể lực không đủ 1.");
                return;
        }

        who->to_front_eachother(me);
        write_user( me, ECHO "伴随着优美的旋律，您在%s身边放声歌唱...", who->get_name() );
        write_user( who, ECHO "伴随着优美的旋律，%s在您身边放声歌唱...", me->get_name() );

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 01011, 10, OVER_BODY, PF_ONCE );

        me->set_time( "work", time() );
        call_out( "do_sing_finish", 10, me, who, arg );
}

// 函数：唱歌结束
void do_sing_finish( object me, object who, string arg )
{
        object obj;
        string file;
        int level, gold, p;

        if( !me || !who ) return;

        if( distance_between(who, me) > 1 )
        {
                write_user( me, ECHO "唱歌没效果，%s已经走开了.", who->get_name() );
                return;
        }
        if( !me->is_actor() )    // 再次确认，防换职业 level 的 BUG
        {
                send_user(me, "%c%s", '!', "您不是艺人，不懂得唱歌.");
                return;
        }

        level = me->get_occupation_level();
        if( level < 1 ) level = 1;    // 防止后面除数为０

        who->set("actor.sing", level + 1);
        set_effect_2(who, EFFECT_CHAR_SING, 18, 10);
        CHAR_CHAR_D->init_loop_perform(who);
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 01011, 10, OVER_BODY, PF_ONCE );

        me->add_strength(-1);    // 体力 -1, 艺人经验 +10, 忠实 +1, 勇敢 +10, 智谋 + 10, 声望 +10, 国家贡献 +1
        me->add_occupation_exp(10);
        me->add_gift_zs(1);
        me->add_gift_yg(10);
        me->add_gift_zm(10);
        me->add_repute(10);
        me->add_contribute(1);
        me->add_exp(level + 10);
        me->add_potential(1);

        write_user( who, ECHO "您听了%s的歌声，只觉得心旷神怡.", me->get_name() );
        write_user( me, ECHO "%s听了您的歌声，只觉得心旷神怡.", who->get_name() );

        if( who->is_user() && random(100) < level * 5 / ( level + who->get_level() ) + 1 )
        {
                gold = 50 + level * 5;
                if( who->get_cash() < gold ) gold = who->get_cash();

                who->add_cash(-gold);  who->add_gold_log("give", gold);
                who->log_money("看舞蹈", -gold);
                me->add_cash(gold);  me->add_gold_log("give2", gold);
                me->log_money("舞蹈", gold);

                write_user( who, ECHO "您陶醉在%s的歌声中，扔下 %d 金.", me->get_name(), gold );
                write_user( me, ECHO "%s陶醉在您的歌声中，扔下 %d 金.", who->get_name(), gold );
        }
        else if( who->is_npc() && random(100) < 20 )
        {
                if( random(100) < 50 )    // 得到金钱
                {
                        gold = 50 + level * 5;
                        me->add_cash(gold);  me->add_gold_log("give2", gold);
                        me->log_money("舞蹈", gold);
                        "/sys/sys/count"->add_income("actor", gold);
                        write_user( me, ECHO "%s陶醉在您的歌声中，扔下 %d 金.", who->get_name(), gold );
                }
                else    // 得到物品
                {
                        if( random(100) < 50 )
                        {
                                if( level / 10 < sizeof_fruit )
                                        file = FruitTable[ random(level / 10 + 1) ];
                                else    file = FruitTable[ random(sizeof_fruit) ];
                        }
                        else    file = FoodTable[ random(sizeof_food) ];

                        if( load_object(file) )
                        {
                                obj = new(file);

                                write_user( me, ECHO "%s笑道：“好技艺！这 %s，就当是我送给你的礼物吧.”", 
                                        who->get_name(), obj->get_name() );

                                if( p = obj->move(me, -1) ) obj->add_to_user(p);
                                else destruct(obj);
                        }
                }
        }

        write_user( me, ECHO "您的艺人经验 +10, 忠实 +1, 勇敢 +10, 智谋 +10, 声望 +10, 国家贡献 +1, 经验 %+d, 潜能 +1.", level + 10 );
}
