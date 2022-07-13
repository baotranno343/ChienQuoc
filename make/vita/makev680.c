
#define CPP_FILE        __DIR__ "vita.cc"
#define TEXT_FILE       __DIR__ "680.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file, name, desc, color, type, temp, vita, final, tool, buff, master;
        int id, pic1, pic2, value, iColor, level, exp, dir, rate;
        object obj;
        int i, j, size;
        string * stuff = ({ "", "", "", "", "", "", "//", "//", "//", "//", "//", "//", });
        int * count = ({ 0, 0, 0, 0, 0, 0});

        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %s", 
                        id, name, level, final ) )
                {     
			type= "1";
			tool = "0";
			master = "药店老板";
			buff = "/make/vita/vitalist"->get_item_file(final);
			if (buff=="") 
			{
				tell_user(me, sprintf("找不到%s", final));
				return 1;
			}
			if (strlen(buff)<10)
			{
				sscanf(buff, "\"%d\"", j);				
				final = sprintf("\"/item/stuff/%04d\"", j);
			}
			else final = buff;
			buff = "/make/vita/vitalist"->get_item_file(name);
			if (buff=="") 
			{
				tell_user(me, sprintf("找不到%s", name));
				return 1;
			}
                        // 有可能成品也是一种原料
                        if (strlen(buff)>10)
                        {
                        	buff = buff[1..<2];     
				obj = load_object(buff);               			
                        	stuff[0] = sprintf("\"%d\"", obj->get_fin_type());
                        }
                        else
                        	stuff[0] = buff;		
			
			id = 68000 + id;        	
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)                        
			name += "加工";
			
                        log_file( file, sprintf( cpp, 680, 1, id%1000, name, level, tool, 1, final, 0, master, 0, 100, "", stuff[0], 1, "//", "", 0, "//", "", 0, "//", "", 0, "//", "", 0, "//", "", 0, 1 ) );
                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
