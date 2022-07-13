
// 函数：命令处理
int main( object me, string arg )
{
        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

    	tell_user( me, "处理负担：%s  %d", get_load_average(), MAIN_D->get_absolute_random_number() );

    	return 1;
}
