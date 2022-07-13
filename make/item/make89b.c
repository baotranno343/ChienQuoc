
#define CPP_FILE        __DIR__ "89b.cc"
#define HTM_FILE        __DIR__ "30.htm"
#define TEXT_FILE       __DIR__ "89b.txt"
#define LIST_LOG        "list.txt"
#define LIST_LOG_2      "list2.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, unit, prop, desc;
        int id, pic1, pic2, combined, value, rate, total;
        int i, size;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG, "<!-- 完美宝石 -->\n\n" );

        log_file( LIST_LOG_2, "---------- /quest/stone (宝石)(残破藏宝图)已齐全 ----------\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %d %d %s %d %d %s %s", 
                        id, name, pic1, pic2, combined, unit, value, rate, prop, desc ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        total += rate;
                        log_file( LIST_LOG_2, sprintf( @LONG
        else if( p < %d ) return "/item/%02d/%04d";
LONG
, total, id / 100, id ) );

                        log_file( file, sprintf( cpp, prop, name, pic1, pic2, unit, value, desc ) );
                        file = LOG_DIR + file;  file->do_nothing();

                        log_file( LIST_LOG, sprintf( htm, name, value, file->get_desc() ) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
