
// 函数：命令处理
int main( object me, string arg )
{
        object *user;
        string result;
        int i, size;

        if( is_player(me) ) 
        {
                notify( "Không đủ quyền hạn" );
		return 1;
        }

        if( arrayp( user = USER_D->get_user() ) ) 
        {
                size = sizeof(user);
                result = sprintf( "Hiện tại có %d người chơi :\n", size );               
                if (size<200)
                {
	                for( i = 0; i < size; i ++ ) 
	                        if( user[i] ) result = sprintf( "%s%s%s( %d )(Cấp: %d) -- ", 
	                                result, i % 8 ? "" : "\n", user[i]->get_name(), user[i]->get_number(), user[i]->get_level() );
		}	                                
                tell_user(me, result);
        }
        else    tell_user(me, "Hiện tại không có người chơi");

        return 1;
}
