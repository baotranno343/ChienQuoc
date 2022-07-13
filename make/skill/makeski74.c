
#define CPP_FILE        __DIR__ "74.cc"
#define TEXT_FILE       __DIR__ "74.txt"
#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        int i, size,id,iLev,type;
        string cpp,*line,tmp1,name,level,desc,file,tmp3;

        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

	log_file( LIST_LOG, "# 宠物法术\n" );

	tmp3 = "send_user( me, \"\%c\%c\%d\%d\%c\%c\%w\%w\%s\", 0xA1,19,getoid(pet),get_id(),1, get_perform_type(), 1, 0, get_name() );";
        size = sizeof(line);
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
                        file = sprintf("make/%05d.c", id);
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        log_file( file, sprintf( cpp, id,name,type,iLev,desc,tmp3) );

                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
