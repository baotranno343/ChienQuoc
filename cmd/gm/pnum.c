
// 函数：命令处理
int main( object me, string arg )
{
        object *user;
        string result;
        int i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( arrayp( user = USER_D->get_user() ) ) 
        {
                size = sizeof(user);	                                
        }
        else size = 0;
        send_user(me, "%c%w", 0xd2, size);
        return 1;
}
