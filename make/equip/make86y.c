
#define CPP_FILE        __DIR__ "86y.cc"
#define HTM_FILE        __DIR__ "86y.htm"
#define TEXT_FILE       __DIR__ "86y.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, unit;
        int id, pic1, pic2, level, value, lasting, ap, cp, rate1, pp, rate2, rate3;
        int i, size;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG, "# 敏捷项链\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %d %s %d %d %d %d %d %d %d %d%% %d%%", 
                        id, name, pic1, pic2, unit, level, value, lasting, ap, cp, rate1, pp, rate2, rate3 ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        lasting = lasting / 100 * 100 + 99;
                        log_file( file, sprintf( cpp, name, pic1, pic2, unit, level, value, lasting, ap, cp, rate1, pp, rate2, rate3, name ) );

                        log_file( LIST_LOG, sprintf( htm, name, level, "男、女", "唐　门<BR>云梦泽", ap, cp, lasting / 100, lasting / 100, value ) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
