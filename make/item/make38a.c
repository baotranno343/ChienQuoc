
#define CPP_FILE        __DIR__ "38a.cc"
#define HTM_FILE        __DIR__ "30.htm"
#define TEXT_FILE       __DIR__ "38a.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, unit;
        int id, pic1, pic2, combined, value;
        int i, size;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG, "<!-- 书籍 -->\n\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %d %d %s %d", 
                        id, name, pic1, pic2, combined, unit, value ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        log_file( file, sprintf( cpp, 
                                combined > 1 ? "  " : "//",
                                combined > 1 ? "//" : "//", combined,
                                name, pic1, pic2, unit, range_value(value, 2, MAX_NUMBER), 
                                combined > 1 ? "  " : "//" ) );
                        file = LOG_DIR + file;  file->do_nothing();

                        log_file( LIST_LOG, sprintf( htm, name, value, file->get_desc() ) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
