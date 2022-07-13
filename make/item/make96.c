
#define CPP_FILE        __DIR__ "96.cc"
#define HTM_FILE        __DIR__ "30.htm"
#define TEXT_FILE       __DIR__ "96.txt"
#define LIST_LOG        "list.txt"
#define LIST_LOG_2      "list2.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, unit, family, name2;
        int id, pic1, pic2, combined, value;
        int i, size;
        object item;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG, "<!-- 秘籍 -->\n\n" );
                        log_file( LIST_LOG_2, "// 秘籍，放到 /quest/book\n\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %d %d %s %d %s", 
                        id, name, pic1, pic2, combined, unit, value, family ) )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)
                        item = load_object( SKILL->get_skill_file(id) );
                        if (!item) continue;
                        name2 = item->get_name()+"秘籍";		
                        log_file( file, sprintf( cpp, name2, pic1, pic2, unit, value, 
                                family == "－" ? "" : family,
                                id, name2[0..<5] ) );
                        file = LOG_DIR + file;  file->do_nothing();

                        log_file( LIST_LOG, sprintf( htm, name, value, file->get_desc() ) );

                        log_file( LIST_LOG_2, sprintf( @LONG
        "/item/96/%04d",
LONG, id ) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
