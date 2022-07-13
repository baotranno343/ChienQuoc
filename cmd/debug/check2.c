
// 函数：命令处理
int main( object me, string arg )
{
        string * line, buff;
        int i, j, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
	line = explode( read_file( "/log/temp.txt" ), "\n" );	
	size = sizeof(line);
	tell_user(me, sprintf("size=%d", size));
        for( i = 0; i < size; i ++ ) 
        {
if (!arg)
{        	
        	buff = "/make/vita/vitalist"->get_item_file(line[i]);
		if (strlen(buff)<10)
		{
			sscanf(buff, "\"%d\"", j);
			if (j>0) buff = sprintf("\"/item/stuff/%04d\"", j);
		} 
		if (strlen(buff)<10)
		{
			tell_user(me, line[i]+"有误！");
			return 1;
		}
}				
		log_file("list.txt", buff+",\n");       	
        }
        return 1;
}
