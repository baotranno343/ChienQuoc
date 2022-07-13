
// 函数：命令处理
int main( object me, string arg )
{
        int which;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg || arg == "" ) 
        {
                tell_user( me, "当前加密方法：%d", get_crypt_code() );
		return 1;        
        }

        which = to_int(arg);
        set_crypt_code(which);

        tell_user( me, "设置加密方法：%d", get_crypt_code() );

    	return 1;
}

int get_crypt_code()
{
	return get_crypt_code();
}

int set_crypt_code(int i)
{
	return set_crypt_code(i);
}