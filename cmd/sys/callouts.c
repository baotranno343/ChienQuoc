
// 函数：命令处理
int main( object me, string arg )
{
        mixed *info;
        int i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

	info = call_out_info();
	if( arg ) info = filter_array( info, (: $1[1] == $2 :), arg );

        tell_user( me, "%-30s %-20s %4s", "物体", "函数", "延迟" ); 
        for( i = 0, size = sizeof(info); i < size; i ++ ) {
                tell_user( me, "%-30O %-20s %4d", info[i][0], info[i][1], info[i][2] );
		//log_file("call_out_now.txt",sprintf("%04d\t%-30O %-20s %4d\n",i, info[i][0], info[i][1], info[i][2]));
	}
        return 1;
}
