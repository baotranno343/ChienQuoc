
#define CPP_FILE        __DIR__ "vjiguan.cc"
#define HTM_FILE        __DIR__ "std.htm"
#define TEXT_FILE       __DIR__ "vjiguan.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, type, fam, type2, desc;
        int id, num, pic, level, showlevel, value, max, add_hp, add_mp;
        int i, size, olddir, dir, oldid, famtype, final;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        size = sizeof(line);
        olddir = 0; oldid = 0;
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %d %s %d %d %s", 
                        id, pic, name, max, value, desc  ) )
                {
			dir = 16;
                	if (olddir!=dir)
                	{
                		mkdir(sprintf(LOG_DIR+"make/%d", dir));
                		olddir = dir;
                	}			
                        file = sprintf("make/%02d/%04d.c", dir, id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)
                        log_file( file, sprintf(cpp, max, id, name, pic, pic, value, desc ) );
                        file = LOG_DIR + file;  file->do_nothing();                        
                        log_file( LIST_LOG, sprintf("\"%s\": \"\\\"/item/final/%02d/%04d\\\"\", \n", name, dir, id) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
