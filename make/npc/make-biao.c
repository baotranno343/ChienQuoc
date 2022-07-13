
#define CPP_FILE        __DIR__ "biao.cc"
#define TEXT_FILE       __DIR__ "biao.txt"
#define LIST_LOG        "list.txt"
#define LIST_LOG_2      "list2.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file, name, city, xy;
        int id, pic, z, x, y, d, flag, i, size;

        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        log_file( LIST_LOG, "# 运镖任务\n" );
        log_file( LIST_LOG_2, "// 运镖任务\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %s %d %s", id, name, pic, city, z, xy ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        xy = replace_string(xy, "，", ",");
                        if( sscanf( xy, "%d,%d,%d", x, y, d ) )
                                log_file( LIST_LOG, sprintf("%d-%d,%d,%d:/npc/80/%04d\n", z, x, y, d, id ) );
                        else    tell_user(me, "ERR: %04d 坐标: %s", id, xy);

                        flag = ( city == "－－" ) ? 1 : 0;

                        if( !flag ) log_file( LIST_LOG_2, sprintf("        \"%s%s\" : \"%d-%d,%d\",\n", city, name, z, x, y) );

                        log_file( file, sprintf( cpp, pic, name, city,
                                flag ? "  " : "/*", flag ? "  " : "*/", 
                                flag ? "  " : "//", flag ? "//" : "  ",
                                flag ? "  " : "//", flag ? "  " : "//" ) );
                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 文件及 /log/list.txt 坐标点，list2.txt 列表(坐标点)。" );

        return 1;       
}
