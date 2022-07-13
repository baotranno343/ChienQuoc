
#include <ansi.h>

// 函数：命令处理
int main( object me, string arg )
{
        object who;
        string name, id;

        if( userp(me) && is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

	if( !arg ) 
	{
                notify( "您想对大家说什么？" );
                return 1;
	}

        name = sprintf( NAME_LEFT "%s" NAME_RIGHT, me->get_name() );

	if( arg[0] == '#' && ( arg[1] < '0' || arg[1] > '9' ) )
	{
	        arg = arg[1..<1];

                USER_D->gm_channel( sprintf( HIR "%s%s", name, arg ) );
	}
	else if( arg[0] == '*' )
	{
	        arg = arg[1..<1];

                if( sscanf( arg, "%s %s", arg, id ) == 2 )
                {
                        if( id == "i" || id == "me" )
                        {
                                who = me;
                        }
                        else if( !( who = find_char(id) ) )
                        {
                                notify( "您无法找到这个人。" );
	        	        return 1;
                        }
                        arg = EMOTE_D->do_emote(me, name, arg, who);
                }
                else    arg = EMOTE_D->do_emote(me, name, arg, 0);

                if( !arg ) return 1;

                USER_D->gm_channel( HIR + arg );
	}
	else    USER_D->gm_channel( sprintf( HIR " %s : %s ", name, arg ) );

        return 1;
}
