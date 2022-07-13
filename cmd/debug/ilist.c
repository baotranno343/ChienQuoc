
int show_tree( object obj, int indent );

// 函数：命令处理
int main( object me, string arg )
{
        object obj;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg ) 
        {
                notify( "您要列示什么东西？" );
		return 1;
        }

        if( !( obj = find_any_object(arg) ) )
        {
                notify( "无法找到这样东西。" );
                return 1;
        }

        tell_user( me, "对象：%O 继承：", obj );
        show_tree(obj, 0);

        return 1;
}

int show_tree( object obj, int indent ) 
{
        object me = this_player();
        string *list = inherit_list(obj);
        int i, size;

        if( !( size = sizeof(list) ) ) return 1;

        for( i = 0; i < size; i ++ ) 
        {
                tell_user( me, 
                        sprintf( "%s%2d: %s", repeat_string( " ", indent * 4 ), i + 1, list[i] ) );
                if( catch( call_other( list[i], "???" ) ) ) 
                {
                        tell_user( me, "载入 %s 失败！", list[i] );
                        return 1;
                }
                obj = find_object( list[i] );
                show_tree( obj, indent + 1 );
        }

        return 1;
}
