
#define CPP_FILE        __DIR__ "foodnpc.cc"
#define TEXT_FILE       __DIR__ "foodnpc.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file, name;
        int id, skill_level, skill_exp, stuff_number, pic;
        int i, size;
       
        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );
        
        
        
        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
        	
                if( sscanf( line[i], "%d %d %s %d %d %d", 
                       id, pic, name, stuff_number, skill_exp, skill_level) )
                {
                	
			mkdir(LOG_DIR+"make/npc/00");	
                        file = sprintf("make/npc/00/food%d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)
                        tell_user( me, file );
                        log_file( file, sprintf(cpp, pic, name, stuff_number, skill_exp, skill_level) );
                        file = LOG_DIR + file;
                        file->do_nothing();                        
                        log_file( LIST_LOG, sprintf("\"%s\": \"\\\"/npc/00/food%d\\\"\", \n", name, id) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;
}