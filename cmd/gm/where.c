
// 函数：命令处理
int main( object me, string arg )
{
        object who = me;
        int time;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( arg && !( who = find_any_char(arg) ) ) 
        {
                notify( "您无法找到这个人。" );
		return 1;
        }

        tell_user( me, "%s(%s)坐标: %d (%d, %d) %d", 
                who->get_name(), who->get_id(), get_z(who), get_x(who), get_y(who), get_d(who) );
	time = time() + 8 * 3600;
	tell_user( me, "time=%d /3600=%d mode 24=%d second=%d", time, time/3600, (time/3600) % 24, time % 3600);
        return 1;
}
