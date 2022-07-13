
// 函数：命令处理
int main( object me, string arg )
{
        string *name, result;
        int i, size;

        result = sprintf( "目前的大神有：" );
        name = CLASS_D->get_godlist();
        for( i = 0, size = sizeof(name); i < size; i ++ ) 
                result = sprintf( "%s%s%s、", result, i % 8 ? "" : "\n", name[i] );
        tell_user(me, result);

        result = sprintf( "目前的ＧＭ有：" );
        name = CLASS_D->get_gmlist();
        for( i = 0, size = sizeof(name); i < size; i ++ ) 
                result = sprintf( "%s%s%s、", result, i % 8 ? "" : "\n", name[i] );
        tell_user(me, result);
        result = sprintf( "目前的ＧＭ主管号有：" );
        name = CLASS_D->get_gm2list();
        for( i = 0, size = sizeof(name); i < size; i ++ ) 
                result = sprintf( "%s%s%s、", result, i % 8 ? "" : "\n", name[i] );
        tell_user(me, result);
        result = sprintf( "目前的活动号有：" );
        name = CLASS_D->get_gm3list();
        for( i = 0, size = sizeof(name); i < size; i ++ ) 
                result = sprintf( "%s%s%s、", result, i % 8 ? "" : "\n", name[i] );
        tell_user(me, result);

        return 1;
}
