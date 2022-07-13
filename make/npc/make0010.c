
#define CPP_FILE        __DIR__ "0010.cc"
#define TEXT_FILE       __DIR__ "0010.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file, name, xy, city2, result2, result3, result4;
        string *city = ({ "", "", "", "", "", "", "", "", "", "" });
        int *no = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        int id, pic, z, x, y, d, i, j, size, size2;

        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        log_file( LIST_LOG, "# 驿站老板\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %s", 
                        id, name, pic, city2) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        log_file( file, sprintf( cpp, pic, name, city2 ) );
                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件及 /log/list.txt 的坐标点。" );

        return 1;       
}
