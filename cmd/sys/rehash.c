
#define UPDATE_CMD      "/cmd/debug/update"     // 更新命令

// 函数：命令处理
int main( object me, string arg )
{
        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        UPDATE_CMD->main(me, USER_CMD_D);

	return 1;
}
