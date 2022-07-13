// agent 职业经纪(相关命令：job)

#include <ansi.h>
#include <city.h>
#include <skill.h>

string *occupation = ({ JOB_TRADER, JOB_SCHOLAR, JOB_SOLDIER, JOB_FARMER, JOB_ACTOR });
string *occupation2 = ({ JOB_SCHOLAR, JOB_ACTOR });

int sizeof_occupation = sizeof(occupation);

// 函数：对话处理
void do_look( object who, object me )
{
        string name, result;
        int id, i, size;

        id = getoid(me);
        name = who->get_occupation();
        result = "";
        
        send_user( who, "%c%s", '!', "职业功能尚未开放." );
        return ;

        for( i = 0, size = sizeof(occupation); i < size; i ++ ) if( name != occupation[i] ) 
                result = sprintf( "%s" ESC "%s\ntalk %x# job.?.%d\n", result, occupation[i], id, i+1 );

        send_user( who, "%c%s", ':', me->get_name() + "：\n    "+"/quest/word"->get_country_word(me)+"\n    我是本城职业经纪，您想转为哪种职业？介绍费为 1000 金.转职后原来的职业经验和等级是不受影响的.\n" 
                + result + ESC "我再想想……\nCLOSE\n" );
}

// 函数：职业变更
void do_job( object who, object me, string arg )
{
        object file;
        string cmd;
        int index;
        
        send_user( who, "%c%s", '!', "职业功能尚未开放." );
        return ;

        if( who->get_cash() < 1000 )
        {
                send_user( who, "%c%s", '!', "您手上的现金不够." );
                return;
        }

        if( sscanf(arg, "?.%d", index) )
        {
                if( index <= 0 || index > sizeof_occupation ) return;

                if( who->get_city_name() == "" && member_array( occupation[index-1], occupation2 ) == -1 )
                {
                        send_user( who, "%c%s", '!', "转职" + occupation[index-1] + "得先加入国家." );
                        return;
                }

                cmd = sprintf( "talk %x# job.%d\n", getoid(me), index );
                send_user( who, "%c%s", ':', "您确定要转职为‘" + occupation[index-1] + "’吗？\n" 
                        ESC "是的.\n" + cmd +
                        ESC "我再想想……\nCLOSE\n" );
        }
        else if( index = to_int(arg) )
        {
                if( index <= 0 || index > sizeof_occupation ) return;

                if( who->get_city_name() == "" && member_array( occupation[index-1], occupation2 ) == -1 )
                {
                        send_user( who, "%c%s", '!', "转职" + occupation[index-1] + "得先加入国家." );
                        return;
                }

                switch( who->get_occupation() )    // 删除职业指令
                {
               case JOB_ACTOR : if( file = load_object( SKILL->get_skill_file(SKILL_ACTOR) ) ) file->remove_perform(who);  break;
              case JOB_FARMER : if( file = load_object( SKILL->get_skill_file(SKILL_FARMER) ) ) file->remove_perform(who);  break;
             case JOB_SOLDIER : if( file = load_object( SKILL->get_skill_file(SKILL_SOLDIER) ) ) file->remove_perform(who);  break;
             case JOB_SCHOLAR : if( file = load_object( SKILL->get_skill_file(SKILL_SCHOLAR) ) ) file->remove_perform(who);  break;
              case JOB_TRADER : if( file = load_object( SKILL->get_skill_file(SKILL_TRADER) ) ) file->remove_perform(who);  break;
                }

                who->add_cash( -1000 );  who->add_gold_log("pay", 1000);
                who->log_money("职业变更", -1000);
                "/sys/sys/count"->add_use("pay", 1000);
                who->set_occupation( occupation[index-1] );
                who->add_occupation_level(0);    // 刷新资料
                who->add_occupation_exp(0);

                switch( who->get_occupation() )    // 列示职业指令
                {
               case JOB_ACTOR : if( file = load_object( SKILL->get_skill_file(SKILL_ACTOR) ) ) file->can_perform(who);  break;
              case JOB_FARMER : if( file = load_object( SKILL->get_skill_file(SKILL_FARMER) ) ) file->can_perform(who);  break;
             case JOB_SOLDIER : if( file = load_object( SKILL->get_skill_file(SKILL_SOLDIER) ) ) file->can_perform(who);  break;
             case JOB_SCHOLAR : if( file = load_object( SKILL->get_skill_file(SKILL_SCHOLAR) ) ) file->can_perform(who);  break;
              case JOB_TRADER : if( file = load_object( SKILL->get_skill_file(SKILL_TRADER) ) ) file->can_perform(who);  break;
                }

                send_user( who, "%c%s", ':', me->get_name() + "：\n恭喜！您的职业变更为“" + occupation[index-1] + "”.\n" );
        }
}
