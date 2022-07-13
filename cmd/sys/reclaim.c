
// 函数：命令处理
int main( object me, string arg )
{
	object * temp;
	int i, size;
        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        temp = children("/inh/user/mail");
        size = sizeof(temp);
        for (i=0;i<size;i++) if (objectp(temp[i])) destruct(temp[i]);
    	tell_user( me, "共清除 %d 个无用变量。", reclaim_objects() );

	return 1;
}
