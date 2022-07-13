
#define CPP_FILE        __DIR__ "09.cc"
#define HTM_FILE        __DIR__ "30.htm"
#define TEXT_FILE       __DIR__ "09.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, unit,family;
        int id, pic1, pic2, combined, value;
        int i, size;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

	log_file( LIST_LOG, "<!-- 门派信物 -->\n\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {        	
                if( line[i][0] == '#' || line[i] == "" ) continue;
                
                if( sscanf( line[i], "%d %s %d %d %d %s %s", 
                        id, name, pic1, pic2, combined,unit,family ) == 7 )
                {
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        log_file( file, sprintf( cpp, name, pic1, pic2,unit,family,"%d" ) );
                        file = LOG_DIR + file;  
//                        load_object(file);
                        file->do_nothing();

                        log_file( LIST_LOG, sprintf( htm, name, value, file->get_desc() ) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
