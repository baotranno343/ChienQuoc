
// 函数：返回字节缩减表达
string byte_expression( int byte )
{
	if( byte < 1024 ) 
	        return byte + "";
	else if( byte < 1024 * 1024 ) 
	        return sprintf( "%d.%02d K", byte / 1024, byte % 1024 * 100 / 1024 );
	else    return sprintf( "%d.%03d M", byte / 1048576, byte % 1048576 * 1000 / 1048576 );
}

// 函数：命令处理
int main( object me, string arg )
{
	object obj;
	int size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg )
        {
		size = memory_info();
		tell_user( me, "目前使用 %s / %d 字节内存。", byte_expression(size), size );
        }
        else 
        {
                if( !( obj = find_any_object(arg) ) ) 
                {
                        notify( "您找不到这样东西。" );
                        return 0;
                }

		size = memory_info(obj);
	        tell_user( me, "%O 使用 %s / %d 字节内存。", obj, byte_expression(size), size );
        }

	return 1;
}
