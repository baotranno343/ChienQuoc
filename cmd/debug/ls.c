
#include <ansi.h>

#define DIR_COLOR       HIB

// 函数：列示数组内容
int list_array( object me, string *file )
{
        string line = "";
        int i, size, len, width = 0;

        if( !sizeof(file) ) return 0;

        // 取字串的最大长度
        for( i = 0, size = sizeof(file); i < size; i ++ ) 
                if( ( len = strlen( file[i] ) ) > width ) width = len;

        // 列示数组中的内容
        for( i = 0, len = 79 / (width + 2); i < size; i ++ ) 
                if( ( i + 1 ) % len ) 
                        line = sprintf( "%s%-*s", line, width + 2, file[i] );
                else    
                {
                        tell_user( me, "%s%-*s", line, width + 2, file[i] );
                        line = "";
                }
        
        if( i % len ) tell_user( me, line );

        return 1;
}

// 函数：命令处理
int main( object me, string arg )
{
        mixed *dfile, *stats;
        string path, file, time1, time2, *result = ({ });
        int i, size, flag = 0;        

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg ) arg = "";
        else if( arg == "-l" )
        {
                arg = "";  flag = 1;
        }
        else if( sscanf(arg, "-l %s", arg) == 1 ) flag = 1;

        path = absolute_path(me, arg);    // 获取绝对路径
        if( directory_exist(path) && path[<1] != '/' ) path += "/";

        dfile = get_dir(path, -1);    // 获取文件列表

        if( ! ( size = sizeof(dfile) ) )    // 路径合法判断
        {
                if( path[<1] != '/' ) 
		{
                        notify( "无法找到这个文件。" );
		        return 1;
		}
                if( directory_exist( path[ 1..<2 ] ) ) 
		{
                        notify( "这个目录没有东西。" );
		        return 1;
                }
                else
		{
                        notify( "无法找到这个目录。" );
		        return 1;
		}
        }

        path = path[ 0 .. strchr( path, '/', -1 ) + 1 ];    // 运算绝对路径

        for( i = 0; i < size; i ++ )    // 生成列示内容
        {
                file = path + dfile[i][0];    // 取绝对路径名

                if( directory_exist(file) || dfile[i][0] == "." || dfile[i][0] == ".." ) dfile[i][0] += "/";

                if( flag )    // 详细列示模式
                {
                        if( !strcmp( dfile[i][0], "./" ) || !strcmp( dfile[i][0], "../" ) ) 
                        {
                        }
                        else if( directory_exist(file) )    // 子目录的列示
                        {
                                // time1 = short_time( stats[1] );
                                result += ({ sprintf( "%-16s%-10s%8s  %s",
                                        "", "", "<子目录>", dfile[i][0] ) });    // time1[2..<4]
                        }
                        else    // 列示所有文件
                        {
                                stats = stat(file);
                                time1 = short_time( stats[1] );
                                time2 = short_time( stats[2] );
                                result += ({ sprintf( "%-16s%-10s%8d  %s %s",
                                        time1[2..<4], stats[2] ? time2[<8..<1] : "   －",
                                        stats[0], dfile[i][0], find_object(file) ? "*" : " " ) });
                        }
                }
                else    result += ({ sprintf( "%4d %s %s",    // 简单列示模式
                                dfile[i][1] / 1024 + 1, dfile[i][0], find_object( file ) ? "*" : " " ) });
        }

        tell_user( me, "目录：" DIR_COLOR + path );    // 列示目录内容

        if( flag ) 
        {
                tell_user( me, "\n%-16s%-10s%8s  %s\n%s", 
                        "   修改日期", "载入时间", "文件尺寸", "文件名称", repeat_string( "─", 30 ) );
        }

        if( !list_array(me, result) )
        {
                notify( "没有任何文件。" );
		return 1;
        }

        return 1;       
}
