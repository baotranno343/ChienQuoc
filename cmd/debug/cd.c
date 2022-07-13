
#include <ansi.h>

#define DIR_COLOR       HIB

// 函数：命令处理
int main( object me, string arg )
{
	object obj;
	string *file, path;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

	if( !arg )
	{
                if( !me->get_cwd() ) me->set_cwd( "/" );

                tell_user( me, "目录：" DIR_COLOR + me->get_cwd() );

	        return 1;	
	}

        path = absolute_path(me, arg);
        if( !directory_exist(path) ) 
        {
		obj = find_any_object(arg);
		if( !obj ) 
		{
                        notify( "无法找到这个目录。" );
		        return 1;
		}
		file = explode( get_file_name(obj), "/" );
                path = implode( file[0..<2], "/" );
                if( !directory_exist(path) )
		{
                        notify( "无法找到这个目录。" );
		        return 1;
		}
        }
        if( path[<1] != '/' ) path += "/";

	me->set_cwd(path);    // 设置当前目录

        tell_user( me, "目录：" DIR_COLOR + me->get_cwd() );    // 列示当前目录

	return 1;	
}
