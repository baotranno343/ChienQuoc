
// 函数：命令处理
int main( object me, string arg )
{
        object *inv, who = me;
        string str, result, result2, result3;
        int m, n, x, y, z;
        int block, len, flag, i, j, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( arg ) 
        {
                if( arg == "-l" ) 
                {
                        flag = 1;  arg = sprintf( "%d", me->get_number() );
                }
                else if( sscanf( arg, "-l %s", arg ) )
                {
                        flag = 1;
                }

                if( !( who = find_any_char(arg) ) ) 
                {
                        notify( "您无法找到这个人。" );
		        return 1;
                }
        }

        z = get_z(who);  x = get_x(who);  y = get_y(who);
        tell_user( me, "%s(%d)坐标: %d (%d, %d) %O", who->get_name(), who->get_number(), z, x, y, get_map_object(z) );

	for( i = 5; i >= -5; i -- ) 
	{
        	result = "";  result2 = "  ";  result3 = "  ";

        	for( j = -5; j <= 5; j ++ )
	        {
	                m = x + j;  n = y + i;  block = get_block(z, m, n);

	                result += sprintf( ( block & MAP_BLOCK ) ? "X" : 
	                                   ( block & FLY_BLOCK ) ? "O" : m%5 || n%5 ? "." : m%10 || n%10 ? ":" : "+" );

	                result2 += sprintf( ( block & ITEM_BLOCK ) ? "X" : 
	                                    ( block & SEAL_BLOCK ) ? "O" : m%5 || n%5 ? "." : m%10 || n%10 ? ":" : "+" );

	                result3 += sprintf( ( block & CHAR_BLOCK ) ? ( !j && !i ? "@" : "O" ) : 
	                                    m%5 || n%5 ? "." : m%10 || n%10 ? ":" : "+" );
	        }
	        tell_user(me, result + result2 + result3);
	}

        if( flag )
        {
                inv = get_scene_object(z, x, y, USER_TYPE);  size = sizeof(inv);  result = "";
                for( i = 0, len = 10; i < size; i ++ ) 
                {
                        if( inv[i]->is_user() )
                                str = sprintf( "%d %s(%d,%d)", inv[i]->get_number(), inv[i]->get_name(), get_x( inv[i] ), get_y( inv[i] ) );
                        else    str = sprintf( "%x#%s(%d,%d)", getoid( inv[i] ), inv[i]->get_name(), get_x( inv[i] ), get_y( inv[i] ) );
                        len += strlen(str) + 2;
                        if( len >= OUTPUT_WIDTH )
                        {
                                len = strlen(str);
                                result = sprintf( "%s\n%s, ", result, str );
                        }
                        else    result = sprintf( "%s%s, ", result, str );
                }
                tell_user( me, "玩家[%2d]：%s", size, result );

                inv = get_scene_object(z, x, y, CHAR_TYPE);  size = sizeof(inv);  result = "";
                for( i = 0, len = 10; i < size; i ++ ) 
                {
                        str = sprintf( "%x#%s(%d,%d)", getoid( inv[i] ), inv[i]->get_name(), get_x( inv[i] ), get_y( inv[i] ) );
                        len += strlen(str) + 2;
                        if( len >= OUTPUT_WIDTH )
                        {
                                len = strlen(str);
                                result = sprintf( "%s\n%s, ", result, str );
                        }
                        else    result = sprintf( "%s%s, ", result, str );
                }
                tell_user( me, "NPC [%2d]：%s", size, result );

                inv = get_scene_object(z, x, y, ITEM_TYPE);  size = sizeof(inv);  result = "";
                for( i = 0, len = 10; i < size; i ++ ) 
                {
                        str = sprintf( "%x#%s(%d,%d)", getoid( inv[i] ), inv[i]->get_name(), get_x( inv[i] ), get_y( inv[i] ) );
                        len += strlen(str) + 2;
                        if( len >= OUTPUT_WIDTH )
                        {
                                len = strlen(str);
                                result = sprintf( "%s\n%s, ", result, str );
                        }
                        else    result = sprintf( "%s%s, ", result, str );
                }
                tell_user( me, "物品[%2d]：%s", size, result );

                inv = get_scene_object(z, x, y, SEAL_TYPE);  size = sizeof(inv);  result = "";
                for( i = 0, len = 10; i < size; i ++ ) 
                {
                        str = sprintf( "[%d]%x#(%d,%d)", get_d( inv[i] ), getoid( inv[i] ), get_x( inv[i] ), get_y( inv[i] ) );
                        len += strlen(str) + 2;
                        if( len >= OUTPUT_WIDTH )
                        {
                                len = strlen(str);
                                result = sprintf( "%s\n%s, ", result, str );
                        }
                        else    result = sprintf( "%s%s, ", result, str );
                }
                tell_user( me, "阵法[%2d]：%s", size, result );
        }

        return 1;
}
