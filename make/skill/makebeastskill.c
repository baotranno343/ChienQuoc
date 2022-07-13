
#define TEXT_FILE       __DIR__ "74.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        int i, size,id,iLev,type,j;
        string cpp,*line,tmp1,name,level,desc,file,tmp;

        line = explode( read_file( TEXT_FILE ), "\n" );

	log_file( LIST_LOG, "# 宠物法术DATA\n" );

        size = sizeof(line);
        file = "make/beastskill.txt";
	rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)
        log_file(file,"mapping mpBeastSkill = ([ \n");
        tmp = "		";
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%s %d %s %s %s", tmp1,id,name,level,desc) == 5 )
                {
                	if ( tmp1 == "主动" )
                		type = 1;
                	else 
                		type = 0;
                	if ( level == "高级" )
                		iLev = 1;
                	else
                		iLev = 0;
                	id = 74*1000+id ;

                       tmp += sprintf("\"%s\" : %d, ",name,id);
                       if ( j++ >= 10 )
                       	{
                       		tmp += "\n		";	
                       		j = 0;
                       	}

                }
        }
        log_file(file,tmp+"\n		]); \n");

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
