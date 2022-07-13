
#define CPP_FILE        __DIR__ "vita.cc"
#define TEXT_FILE       __DIR__ "660.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file, name, desc, color, type, temp, vita, final, tool, buff;
        int id, pic1, pic2, value, iColor, level, dir, counts;
        object obj;
        int i, j, k, size, rate, tili;
        string * stuff = ({ "", "", "", "", "", "", "//", "//", "//", "//", "//", "//", });
        int * count = ({ 0, 0, 0, 0, 0, 0});

        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%s %d %s %d %s %d %d %d %s %s %d %s %d %s %d %s %d %s %d %s %d", 
                        name, id, temp, level, final, counts, rate, tili, tool, stuff[0], count[0], stuff[1], count[1], stuff[2], count[2], stuff[3], count[3], stuff[4], count[4], stuff[5], count[5] ) )
                {     
			type= "1";
			buff = "/make/vita/vitalist"->get_item_file(tool);
			if (buff!="") sscanf(buff, "\"%s\"", tool);
			buff = "/make/vita/vitalist"->get_item_file(final);
			if (buff=="") 
			{
				tell_user(me, sprintf("%s找不到%s", name, final));
				return 1;
			}
			if (strlen(buff)<10)
			{
				sscanf(buff, "\"%d\"", j);				
				final = sprintf("\"/item/stuff/%04d\"", j);
			}
			else final = buff;
			id = 66000 + id;        	
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)
                        tell_user(me, sprintf("%d %s %s %s %s %s %s", id, stuff[0], stuff[1], stuff[2], stuff[3], stuff[4], stuff[5] ));
                        for (j=0;j<5;j++)
                        {
                        	for (k = j+1;k<6;k++)
                        	{
                        		if (stuff[j]!="无" && stuff[j]==stuff[k])
                        		{
                        			tell_user(me, "有重复的原料！");
                        			return 1;
                        		}
                        	}
                        }
                        for (j=0;j<6;j++)
                        {
                        	if (stuff[j]!="无")
                        	{
                        		buff = "/make/vita/vitalist"->get_item_file(stuff[j]);
                        		if (buff=="") 
                        		{
                        			tell_user(me, sprintf("stuff[%d]找不到%s", j+1, stuff[j]));
                        			return 1;
                        		}
                        		// 有可能成品也是一种原料
                        		if (strlen(buff)>10)
                        		{
                        			buff = buff[1..<2];     
						obj = load_object(buff);               			
                        			stuff[j] = sprintf("\"%d\"", obj->get_fin_type());
                        		}
                        		else
                        			stuff[j] = buff;
                        		stuff[j+6] = "";
                        	}
                        	else 
                        		stuff[j+6] = "//";
                        }
			if (temp=="是") temp = "0";
			else temp = "1";
			name += "制作";			
                        log_file( file, sprintf( cpp, 660, 1, id%1000, name, level, tool, tili, final, to_int(temp), "0", iColor, rate, stuff[6], stuff[0], count[0], stuff[7], stuff[1], count[1], stuff[8], stuff[2], count[2], stuff[9], stuff[3], count[3], stuff[10], stuff[4], count[4], stuff[11], stuff[5], count[5], counts  ) );
                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
