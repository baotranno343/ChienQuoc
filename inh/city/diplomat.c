// diplomat 使节, 外交官

#include <ansi.h>
#include <action.h>

void do_look( object who, object me )
{
        object city;
        string name1, name2, result;
        string cmd;
        int id, flag, city7;

        id = getoid(me);

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2 
        &&    ( city = CITY_D->get_city_object(who) ) 
        &&    ( flag = city->get_save_2("relation.flag") ) )
        {
                switch( flag )
                {
              default : result = "友好";  break;
               case 2 : result = "交恶";  break;
                }
                city7 = city->get_save_2("relation.city");
                cmd = sprintf( "talk %x# relation.%d\n", id, flag );
                send_user( who, "%c%s", ':', sprintf( "%s：\n    "+"/quest/word"->get_country_word(me)+"\n    %s，我国要同%s%s，有兴趣跑一趟吗？\n", 
                                me->get_name(), who->get_name(), CITY_D->get_city_name(city7), result ) +
                        ESC "接外交任务.\n" + cmd +
                        ESC "离开.\nCLOSE\n" );
        }
        else
        {
                send_user( who, "%c%s", ':', me->get_name() + "：\n    "+"/quest/word"->get_country_word(me)+"\n" );
        }
}

// 函数：外交任务
void do_relation( object who, object me, string arg )
{
        object city;
        string name1, name2, result;
        int flag, city0, city7;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if(     stringp(name1) && stringp(name2) && name1 == name2 
        &&    ( city = CITY_D->get_city_object(who) ) 
        &&    ( flag = city->get_save_2("relation.flag") )
        &&      flag == to_int(arg) )
        {
                if( gone_time( who->get_save_2("relation.time") ) < 2400 )    // 40 分钟
                {
                        send_user(who, "%c%s", '!', "您还有未完成的外交任务.");
                        return;
                }
                if( who->get_strength() < 1 )
                {
                        send_user(who, "%c%s", '!', "外交任务要 1 点体力.");
                        return;
                }
                if( who->get_repute() < 100 )
                {
                        send_user(who, "%c%s", '!', "声望高于 100 才能接外交任务.");
                        return;
                }

                city0 = CITY_D->get_city_number(name2);
                city7 = city->get_save_2("relation.city");

                who->set_save_2("relation.flag", flag);
                who->set_save_2("relation.city", city0);
                who->set_save_2("relation.city2", city7);
                who->set_save_2("relation.time", time() );
                who->add_strength(-1);

                city->delete_save_2("relation");

                switch( flag )
                {
              default : send_user( who, "%c%s", ':', sprintf( "%s：\n我国欲与%s友好，就请你担任使节，在４０分钟内完成修好任务！", 
                                me->get_name(), CITY_D->get_city_name(city7) ) );
                        break;
               case 2 : send_user( who, "%c%s", ':', sprintf( "%s：\n%s近日欺我太甚，就请你担任使节，在４０分钟内彰显我大国风范！", 
                                me->get_name(), CITY_D->get_city_name(city7) ) );
                        break;
                }
        }
}
