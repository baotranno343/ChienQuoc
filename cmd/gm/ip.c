
#include <ansi.h>

// 函数：ＩＰ比较
int ip_cmp( string ip1, string ip2 )    // ip1 = "127.0.0.1";  ip2 = "127.0.0";  返回１
{
        int len;

        if( ip1 == ip2 ) return 1;
        len = strlen( ip2 ) + 1;
        if( strlen(ip1) > len && ip2 + "." == ip1[0..len - 1] ) return 1;

        return 0;
}

// 函数：命令处理
int main( object me, string arg )
{
        object *user;
        string *id = ({ }), result = "";
        int i, size, len;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg )
        {
                send_user( me, "%c%c%d%s", '?', 16, 16, sprintf( "查找相同ＩＰ玩家。\n\n请输入对方的ＩＰ：\n"
                        ESC "ip %%s\n" ) );
                return 1;
        }

        user = filter_array( USER_D->get_user(), (: ip_cmp( get_ip_name($1), $2 ) :), arg );    // get_ip_name($1) == $2
        for( i = 0, size = sizeof(user); i < size; i ++ )
                id += ({ sprintf( "%s(%s)", user[i]->get_name(), user[i]->get_id() ) });

        if( size = sizeof(id) ) 
        {
                tell_user( me, "ＩＰ是 %s 的玩家有：", arg );
                for( i = 0, len = 0; i < size; i ++ )
                {
                        len += strlen( id[i] ) + 2;
                        if( len >= OUTPUT_WIDTH )
                        {
                                len = strlen( id[i] );
                                result = sprintf( "%s\n%s, ", result, id[i] );
                        }
                        else    result = sprintf( "%s%s, ", result, id[i] );
                }
                tell_user( me, result );
        }
        else    tell_user( me, "没有ＩＰ为 %s 的玩家。", arg );

        return 1;
}
