
#define HTM_FILE        __DIR__ "blank.htm"
#define BEGIN_MARK      "<!-- #### BEGIN #### -->"
#define END_MARK        "<!-- #### END #### -->"

// 函数：命令处理
int main( object me, string arg )
{
        mixed *dfile;
        string path, file, file2, html, html2, html3, result;
        int p, p2, i, size;

        html = read_file( HTM_FILE );

        if( !( p = strstr(html, BEGIN_MARK, 1) ) ) 
        {
                notify( "无法找到起始标记。" );
		return 1;
	}
        html2 = html[0..p-1] + BEGIN_MARK + "\n";

        if( !( p = strstr(html, END_MARK, 1) ) ) 
        {
                notify( "无法找到结束标记。" );
		return 1;
	}
        html3 = html[p..<1];

        html = "";

	if( !arg ) arg = "/log/make";

        path = absolute_path(me, arg);    // 获取绝对路径
        if( directory_exist(path) && path[<1] != '/' ) path += "/";

        dfile = get_dir(path) - ({ ".", ".." });    // 获取文件列表

        if( !( size = sizeof(dfile) ) ) 
        {
                notify( "无法找到这个文件。" );
		return 1;
	}

        path = path[ 0 .. strchr( path, '/', -1 ) + 1 ];    // 运算绝对路径

        tell_user( me, "扫描目录: %s\n", path );

        for( i = 0; i < size; i ++ )    // 遍历所有文件
        {
                file = path + dfile[i];    // 取绝对路径名

                if( directory_exist( file ) ) 
                {
                        main( me, file + "/" );    // 遍历子目录
                }
                else if( file[<4..<1] == ".htm" ) 
                {
                        html = read_file(file);

                        if( !( p = strstr(html, BEGIN_MARK, 1) ) ) 
                        {
                                tell_user(me, "%s 无起始标记", file);
                                continue;
                        }
                        if( !( p2 = strstr(html, END_MARK, 1) ) ) 
                        {
                                tell_user(me, "%s 无结束标记", file);
                                continue;
                        }

                        result = html2 + html[p + strlen(BEGIN_MARK) + 1..p2-1] + html3;

                        rm(file);    // 清除旧文件(WINDOWS)
                        write_file(file, result);
                }
        }

        return 1;
}
