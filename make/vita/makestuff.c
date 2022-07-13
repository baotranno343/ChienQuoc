
#define CPP_FILE        __DIR__ "stuff.cc"
#define HTM_FILE        __DIR__ "std.htm"
#define TEXT_FILE       __DIR__ "stuff.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, desc, color;
        int id, pic1, pic2, combined, value, iColor;
        int i, size;

        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG, "<!-- 药材 -->\n\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %s %d %d %d %s", 
                        id, name, color, pic1, combined, value, desc ) )
                {
                	if (name=="砒霜") continue;
                	if (name=="打火石") continue;
                	if (name=="玉心") continue;
                	if (name=="补天石") continue;
                	if (name=="完美玉心") continue;
                	if (name=="完美补天石") continue;
			switch(color)
			{
			case "白色":
				iColor = 0;
				break;
			case "蓝色":
				iColor = 1;
				break;				
				
			}                	
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        log_file( file, sprintf( cpp, combined, id, iColor,name, pic1, pic1, value, desc ) );
                        file = LOG_DIR + file;  file->do_nothing();

                        log_file( LIST_LOG, sprintf( "\"%s\": \"\\\"%d\\\"\", \n", name, id ) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
