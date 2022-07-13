 
// 函数：命令处理
int main( object me, string arg )
{
        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        tell_user( me, "用户：%d，在线：%d / %d (ＧＭ：%d，玩家：%d)。",
                ID_D->get_max_id(), USER_D->sizeof_user(), sizeof_users(), USER_D->sizeof_gm(), USER_D->sizeof_player() );

	return 1;
}
