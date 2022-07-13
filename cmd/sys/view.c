
// 函数：命令处理
int main( object me, string arg )
{
        object *char, *npc, *npc2, *user;
        int size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        size = memory_info();
        tell_user( me, "内存: %d.%03d M    物体: %d", 
                size / 1048576, size % 1048576 * 1000 / 1048576, sizeof( objects() ) );
        tell_user( me, "处理: %s  %d", get_load_average(), MAIN_D->get_absolute_random_number() );

        // char = objects( (: $1->is_char() && !clonep($1) :) );
        char = filter_array( livings(), (: $1->is_char() && !clonep($1) :) );
        npc = filter_array( livings(), (: $1->is_npc() && clonep($1) :) );
        user = filter_array( livings(), (: $1->is_user() && clonep($1) :) );
        tell_user( me, "人物: %d － %d种 ＝ 人物(%d) ＋ 用户(%d)", 
                sizeof( livings() ), sizeof(char), sizeof(npc), sizeof(user) );

        char = heart_beats();    // objects( (: get_heart_beat($1) :) );    // 注意：get_heart_beat 效率太低
        npc = filter_array( char, (: $1->is_npc() && clonep($1) :) );
        npc2 = filter_array( npc, (: get_heart_idle($1) :) );
        user = filter_array( char, (: $1->is_user() && clonep($1) :) );
        tell_user( me, "心跳: %d ＝ 人物(%d)空闲(%d) ＋ 玩家(%d)", sizeof(char), sizeof(npc), sizeof(npc2), sizeof(user) );

/*      char = objects( (: $1->get_enemy() :) );
        npc = filter_array( char, (: $1->is_npc() && clonep($1) :) );
        user = filter_array( char, (: $1->is_user() && clonep($1) :) );
        tell_user( me, "战斗: %d ＝ 人物(%d) ＋ 玩家(%d)", sizeof(char), sizeof(npc), sizeof(user) );
*/
        tell_user( me, "用户: %d  在线：%d / %d ＝ ＧＭ(%d) ＋ 玩家(%d)", 
                ID_D->get_max_id(), USER_D->sizeof_user(), sizeof_users(), USER_D->sizeof_gm(), USER_D->sizeof_player() );

	return 1;
}
