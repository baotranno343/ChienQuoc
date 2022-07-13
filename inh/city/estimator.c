// estimator 职业评定师

#include <ansi.h>
#include <city.h>

// 函数：对话处理
void do_look( object who, object me )
{
        string name, cmd;

        name = who->get_occupation();

        if( !name || name == "" )
        {
                send_user( who, "%c%s", ':', me->get_name() + "：\n    "+"/quest/word"->get_country_word(me) );
        }
        else 
        {
                cmd = sprintf( "talk %x# upgrade\n", getoid(me) );
                send_user( who, "%c%s", ':', me->get_name() + "\n    "+"/quest/word"->get_country_word(me)+"\n    您确定要提升职业等级吗？\n" 
                        ESC "是的.\n" + cmd +
                        ESC "我再想想……\nCLOSE\n" );
        }
}

// 函数：提升等级
void do_upgrade( object who, object me )
{
        string name;
        string *desc = ({ "仁爱", "正义", "忠实", "诚信", "勇敢", "智谋" });
        int *gift = ({ 0, 0, 0, 0, 0, 0 });
        int level, point, i, size;

        name = who->get_occupation();

        if( !name || name == "" )
        {
                send_user( who, "%c%s", ':', me->get_name() + "：\n您现在没有职业，我很难进行评估." );
        }
        else 
        {
                level = who->get_occupation_level();

                if( level >= who->get_level() + 10 )
                {
                        send_user( who, "%c%s", ':', me->get_name() + "：\n您的人物等级不够，无法升级." );
                        return;
                }

                switch( name )
                {             // 仁 义 忠 信 勇 智
               case JOB_ACTOR : gift = ({ 0, 0, 0, 0, 1, 1 });  break;
              case JOB_FARMER : gift = ({ 0, 0, 0, 1, 1, 0 });  break;
             case JOB_SOLDIER : gift = ({ 0, 1, 0, 0, 1, 0 });  break;
             case JOB_SCHOLAR : gift = ({ 1, 0, 0, 0, 0, 1 });  break;
              case JOB_TRADER : gift = ({ 0, 0, 0, 1, 0, 1 });  break;
                }

                level ++;  level = level * level * 10;

                for( i = 0; i < 6; i ++ ) if( gift[i] )
                {
                        switch( i )
                        {
                       case 0 : point = who->get_gift_ra();  break;
                       case 1 : point = who->get_gift_zy();  break;
                       case 2 : point = who->get_gift_zs();  break;
                       case 3 : point = who->get_gift_cx();  break;
                       case 4 : point = who->get_gift_yg();  break;
                       case 5 : point = who->get_gift_zm();  break;
                        }

                        if( point >= level ) continue;

                        send_user( who, "%c%s", ':', me->get_name() + "：\n您的" + desc[i] + "不足，无法升级." );
                        return;
                }

                level = who->get_occupation_level();

                if( who->get_occupation_exp() < who->get_job_exp(level) )
                {
                        send_user( who, "%c%s", ':', me->get_name() + "：\n您的‘" + name + "’经验不足，无法升级." );
                        return;
                }

                level ++;

                if( who->get_repute() < level * 10 )
                {
                        send_user( who, "%c%s", ':', me->get_name() + "：\n您的声望不足，无法升级." );
                        return;
                }

                point = level * 2000;

                if( who->get_cash() < point )
                {
                        send_user( who, "%c%s", ':', sprintf( "%s：\n请您交纳 %d 金的升级费用.", me->get_name(), point ) );
                        return;
                }

                who->add_cash( -point );  who->add_gold_log("pay", point);
                who->log_money("职业升级", -point);
                "/sys/sys/count"->add_use("pay", point);
                who->add_occupation_level(1);
                send_user( who, "%c%s", '!', sprintf( HIC "您的“%s”等级升至 %d 级！", name, who->get_occupation_level() ) );
                write_user( who, ECHO "您交纳 %d 金升至 %d 级！(%s经验：%d；升级所需：%d)", 
                        point, who->get_occupation_level(), name, who->get_occupation_exp(), who->get_job_exp(level + 1) );
        }
}
