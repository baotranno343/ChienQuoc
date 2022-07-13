#include <ansi.h>
#include <map.h>
#include <city.h>

#define LOG_DAT          "/log/pkgame.dat"

// 函数：命令处理
int main( object me, string arg )
{
        string *line, cpp;
        int i, size;        

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        cpp = read_file( LOG_DAT );
        if (cpp==0)
        {
        	send_user( me, "%c%s", '>', "没有任何记录");
        	return 1;
        }        
        line = explode( cpp , "\n" );
        size = sizeof(line);
        if (size==0)
        {
        	send_user( me, "%c%s", '>', "没有任何记录");
        	return 1;
        }
        send_user( me, "%c%s", '>', "记录为：");
        
        for( i = 0; i < size; i ++ )
        {
                send_user( me, "%c%s", '>', line[i]);
        }

        return 1;
}
