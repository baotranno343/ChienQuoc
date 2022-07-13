
#include <ansi.h>
#include <skill.h>

#define SKILL_LOG       "user/skill.txt"        // 删除技能日志

// 函数:命令处理
int main( object me, string arg )
{
        mapping skls;
        string *name, file;
        int skill, level, i, size;

        if( arg && sscanf( arg, "- %d", skill ) ) 
        {
                if( me->get_skill(skill) || me->get_skill_degree(skill) )
                {
                        file = SKILL->get_skill_file(skill);
                        file = load_object(file) ? file->get_name() : "未知技能";

                        switch( skill )
                        {
              case SKILL_0411 :
              case SKILL_0421 : if( me->get_skill(SKILL_0425) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“乾坤挪移”." );
                                        return 1;
                                }
                                if( me->get_skill(SKILL_0417) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“神打”." );
                                        return 1;
                                }
                                if( me->get_skill(SKILL_0408) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“奇门遁甲”." );
                                        return 1;
                                }
                                if( me->get_skill(SKILL_0418) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“穿越时空”." );
                                        return 1;
                                }
                                if( me->get_skill(SKILL_0409) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“神游”." );
                                        return 1;
                                }
                                if( me->get_skill(SKILL_0429) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“龙游四海”." );
                                        return 1;
                                }
                                break;

              case SKILL_0501 : if( me->get_skill(SKILL_0511) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“医术”." );
                                        return 1;
                                }
                                if( me->get_skill(SKILL_0521) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“毒经”." );
                                        return 1;
                                }
                                break;
                        }

                        send_user( me, "%c%s", ':', sprintf( "您的技能“%s”已经有 %d/%d 级了，您想放弃它吗？\n" 
                                ESC "删除它吧，我早就看它不顺眼了.\nskl x %d\n"
                                ESC "让我想想……要不先留着吧.\nCLOSE\n", 
                                file, me->get_skill(skill), me->get_skill_degree(skill), skill ) );
                }
                return 1;
        }
        else if( arg && sscanf( arg, "x %d", skill ) ) 
        {
                if( ( level = me->get_skill(skill) ) || me->get_skill_degree(skill) )
                {
                        file = SKILL->get_skill_file(skill);
                        file = load_object(file) ? file->get_name() : "未知技能";

                        switch( skill )
                        {
              case SKILL_0411 :
              case SKILL_0421 : if( me->get_skill(SKILL_0425) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“乾坤挪移”." );
                                        return 1;
                                }
                                if( me->get_skill(SKILL_0417) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“神打”." );
                                        return 1;
                                }
                                if( me->get_skill(SKILL_0408) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“奇门遁甲”." );
                                        return 1;
                                }
                                if( me->get_skill(SKILL_0418) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“穿越时空”." );
                                        return 1;
                                }
                                if( me->get_skill(SKILL_0409) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“神游”." );
                                        return 1;
                                }
                                if( me->get_skill(SKILL_0429) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“龙游四海”." );
                                        return 1;
                                }
                                break;

              case SKILL_0501 : if( me->get_skill(SKILL_0511) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“医术”." );
                                        return 1;
                                }
                                if( me->get_skill(SKILL_0521) )
                                {
                                        notify( "在放弃“" + file + "”之前得先放弃“毒经”." );
                                        return 1;
                                }
                                break;
                        }

                        if( level > 50 ) log_file( SKILL_LOG, sprintf("%s %s(%d)删除技能 %s(%04d) %d 级.\n",
                                short_time(), me->get_name(), me->get_number(), file, skill, level ) );

                        me->delete_skill(skill);
                        // send_user( me, "%c%w%w", 0x53, 0xffff, skill );    // 放入 delete_skill 函数
                }
                return 1;
        }

        return 1;
}
