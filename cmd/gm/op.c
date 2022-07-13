
#include <city.h>

// 函数：命令处理
int main( object me, string arg )
{
        object who, npc;
        mapping org, skls;
        string *name, file, result;
        int id, number, skill, flag;
        int i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg )    // 列示所有帮派
        {
                if( mapp( org = CITY_ZHOU->get_2("org") ) && arrayp( name = keys(org) ) )
                {
                        result = sprintf( "目前的帮派有：" );
                        for( i = 0, size = sizeof(name); i < size; i ++ ) 
                        	if (org[name[i]])
                                	result = sprintf( "%s%s%d.%s、", result, i % 8 ? "" : "\n", i + 1, name[i] );
                        tell_user(me, result);
                }
                else    tell_user(me, "目前没有任何帮派。");
        }
        else
        {
                if( sscanf(arg, "info %s", arg) ) flag = 1;
                else if( sscanf(arg, "apply %s", arg) ) flag = 2;
                else if( sscanf(arg, "skill %s", arg) ) flag = 3;
                else if( sscanf(arg, "note %s", arg) ) flag = 4;
                else if( sscanf(arg, "note2 %s", arg) ) flag = 5;
                else if( sscanf(arg, "savings %s", arg) ) flag = 6;

                if( mapp( org = CITY_ZHOU->get_2("org") ) && arrayp( name = keys(org) ) )
                {

                if(     objectp( who = CITY_ZHOU->get_2("org." + arg) )
                ||  ( ( number = to_int(arg) ) 
                &&      number > 0 && number <= sizeof(name) 
                &&      objectp( who = CITY_ZHOU->get_2("org." + name[number - 1] ) ) ) )
                {
                        npc = who;  who = me;  me = npc;    // 注意！

                        id = getoid(me);

                        switch( flag )
                        {
                      default : send_user( who, "%c%c%d%c%s", 0x95, 10, id, who->get_org_position(), me->get_org_name() );

                                size = me->sizeof_member_dbase();
                                name = me->get_all_member();

                                for( i = 0; i < size; i ++ )
                                {
                                        number = to_int( name[i] );
	                                if (me->get_member_id(number)==0) 
	                                {
	                                	me->delete_member_info(number);
	                                	continue;
	                                }
                                        send_user( who, "%c%c%d%d%c%d%d%c%s", 0x95, 11, number,
                                                me->get_member_time(number), me->get_member_quit(number) ? 0 : 1,
                                                me->get_member_gold(number), me->get_member_all_contribute(number), me->get_member_level(number), 
                                                sprintf( "%-12s%s", me->get_member_name(number), me->get_member_rank(number) ) );
                                }

                                tell_user( who, "列示“%s”帮众信息。", me->get_org_name() );
                                break;

                       case 2 : send_user( who, "%c%c%d%c%s", 0x95, 20, id, who->get_org_position(), me->get_org_name() );

                                size = me->sizeof_join_dbase();
                                name = me->get_all_join();

                                for( i = 0; i < size; i ++ )
                                {
                                        number = to_int( name[i] );
                                        send_user( who, "%c%c%d%w%s", 0x95, 21, number,
                                                me->get_join_level(number), me->get_join_name(number) );
                                }

                                tell_user( who, "列示“%s”申请信息。", me->get_org_name() );
                                break;
                       
                       case 3 :
                                send_user( who, "%c%c%d%c%w%w%s", 0x95, 30, id, who->get_org_position(), 1, 20, me->get_org_name() );

                                if( sizeof( skls = me->get_skill_dbase() ) )
                                {
                                        name = sort_array( keys(skls), 1 );
                                        for( i = 0, size = sizeof(name); i < size; i ++ )
                                        {
                                                skill = to_int( name[i] );
                                                file = SKILL->get_skill_file(skill);
                                                file = load_object(file) ? file->get_name() : "未知技能";
                                                send_user( who, "%c%c%w%w%d%s", 0x95, 31, skill, me->get_skill(skill), me->get_skill_degree(skill), file );
                                        }
                                }

                                if( skill = me->get_research() )
                                {
                                        file = SKILL->get_skill_file(skill);
                                        file = load_object(file) ? file->get_name() : "未知技能";
                                        send_user( who, "%c%c%w%s", 0x95, 32, skill, file );
                                }

                                tell_user( who, "列示“%s”技能信息。", me->get_org_name() );
                                break;

                       case 4 : send_user( who, "%c%c%d%c%s", 0x95, 40, id, who->get_org_position(), me->get_bulletin() );
                                tell_user( who, "列示“%s”公告。", me->get_org_name() );
                                break;

                       case 5 : send_user( who, "%c%c%d%c%s", 0x95, 41, id, who->get_org_position(), me->get_note() );
                                tell_user( who, "列示“%s”大事记。", me->get_org_name() );
                                break;

                       case 6 : send_user( who, "%c%c%d%d%s", 0x95, 60, id, me->get_gold(), me->get_org_name() );
                                tell_user( who, "列示“%s”金库。", me->get_org_name() );
                                break;
                        }
                }
                else    tell_user(me, "无法找到这个帮派。");

                }
                else    tell_user(me, "目前没有任何帮派。");
        }

        return 1;
}
