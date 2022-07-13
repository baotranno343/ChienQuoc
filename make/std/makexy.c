
/*

这个程序用成查出怪点的 xy.c 文件，不过这种做法已被取消。

*/

#define CPP_FILE        __DIR__ "xy.cc"

// 函数：命令处理
int main( object me, string arg )
{
        mixed *dir, file;
        string cpp, *line, result;
        int id, z, x, y;
        int i, j, size, size2;

        cpp = read_file( CPP_FILE );

        dir = get_dir(__DIR__ "*.txt", -1);

        if( !( size = sizeof(dir) ) )
        {
                tell_user( me, "无法找到任何文件！" );
                return 1;
        }
        for( i = 0; i < size; i ++ ) if( strlen( dir[i][0] ) == 7 )    // ???.txt
        {
                if( dir[i][0][0] < '0' || dir[i][0][0] > '9' ) continue;
                if( dir[i][0][1] < '0' || dir[i][0][1] > '9' ) continue;
                if( dir[i][0][2] < '0' || dir[i][0][2] > '9' ) continue;

                id = to_int( dir[i][0] );
                result = "";

                line = ({ });
                line = explode( read_file( __DIR__ + dir[i][0] ), "\n" );

                size2 = sizeof(line);
                for( j = 0; j < size2; j ++ ) 
                {
                        if( line[j][0] == '#' || line[j] == "" ) continue;

                        if( sscanf( line[j], "%d,%d", x, y ) )
                        {
                                result += sprintf( @LONG
        "%d,%d,%d",
LONG
, id, x, y );
                        }
                }

                file = sprintf("make/%03d.c", id );
                rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                if( result != "" ) 
                {
                        log_file(file, sprintf(cpp, result) );
                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
