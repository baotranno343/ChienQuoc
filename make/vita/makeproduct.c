
#define CPP_FILE        __DIR__ "product.cc"
#define HTM_FILE        __DIR__ "std.htm"
#define TEXT_FILE       __DIR__ "product.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, htm, *line, file, name, desc, skillname, sort, buff, color, fam;
        int id, pic1, pic2, value, skill, level, exp;
        int i, size ;
	object obj;
        cpp = read_file( CPP_FILE );
        htm = read_file( HTM_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG, "<!-- 药材 -->\n\n" );

        size = sizeof(line);
        value = 200;
        pic1 = 9807;
        sort = "0";
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%s %d %s", 
                        name, id, skillname ) )
                {			
			switch(skillname)
			{
			case "酒食":
				skill = 610;
				break;				
			case "铁匠":
				skill = 620;
				break;	
			case "炼丹":
				skill = 630;
				break;		
			case "裁缝":
				skill = 640;
				break;			
			case "石刻":
				skill = 650;
				break;		
			case "机关":
				skill = 660;
				break;																			
			}
			desc = "学习制作"+name+"。";
			name += "图纸";
                        file = sprintf("make/%04d.c", skill*100+id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)	                        
                        obj = new (sprintf("/skill/%d/%d", skill/10, skill*100+id));
                        if (!obj)
                        {
                        	tell_user(me, sprintf(line[i]+"缺失/skill/%d/%d", skill/10, skill*100+id));
                        	return 1;
                        }                        
                        log_file( file, sprintf( cpp, id, skill, obj->get_skill_type(), obj->get_skill_level(), obj->get_skill_color(), name, pic1, pic1, value, desc, obj->get_final() ) );
                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
