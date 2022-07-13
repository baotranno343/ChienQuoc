
#define CPP_FILE        __DIR__ "orenpc.cc"
#define TEXT_FILE       __DIR__ "orenpc.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file_name, file, name;
        int skill_level, reset_time, tool_level, stuff_number, pic;
        int i, size;
       
        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );
        
        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
        	
                if( sscanf( line[i], "%s %s %d %d %d %d %d", 
                       file_name, name, stuff_number, tool_level, reset_time, skill_level,pic) );
                {
                	
			mkdir(LOG_DIR+"make/npc/00");	
                        file = sprintf("make/npc/00/%s.c", file_name );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)
                        tell_user( me, file );
                        log_file( file, sprintf(cpp, name, stuff_number, tool_level, reset_time
                        , skill_level,pic) );
                        file = LOG_DIR + file;
                        file->do_nothing();                        
                        log_file( LIST_LOG, sprintf("\"%s\": \"\\\"/npc/00/%s\\\"\", \n", name, file_name) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;
}