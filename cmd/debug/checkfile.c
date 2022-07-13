
// 函数：命令处理
int main( object me, string arg )
{
        mixed *dfile;
        string path, file;
        int i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

	if( !arg ) arg = ".";

        path = absolute_path(me, arg);    // 获取绝对路径
        if( directory_exist(path) && path[<1] != '/' ) path += "/";

        dfile = get_dir(path) - ({ ".", ".." });    // 获取文件列表

        if( !( size = sizeof(dfile) ) ) 
        {
//                notify( "无法找到这个文件。" );
		return 1;
	}

        path = path[ 0 .. strchr( path, '/', -1 ) + 1 ];    // 运算绝对路径

        if( path[0..5] == "/data/" )
        {
                notify( "不能扫描 /data 目录！" );
		return 1;
	}
        if( path[0..4] == "/log/" )
        {
                notify( "不能扫描 /log 目录！" );
		return 1;
	}

        tell_user( me, "扫描目录: %s", path );

        for( i = 0; i < size; i ++ )    // 遍历所有文件
        {
                file = path + dfile[i];    // 取绝对路径名

                if( directory_exist( file ) ) 
                {
                        main( me, file + "/" );    // 遍历子目录
                }
                else 
                {
                        if( file[<2..<1] == ".c" ) 
                        {
                        	"/cmd/debug/update"->main(me, file);
                        }
                }
        }

        return 1;
}
