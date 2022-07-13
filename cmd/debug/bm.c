
// 函数：命令处理
int main( object me, string arg )
{
        object item,*inv;
	int i;
        if( is_player(me) ) 
        {
                notify( "Bạn không đủ quyền hạn." );
		return 1;
        }

	if( !arg ) 
	{
                notify( "Bạn muốn gì ?" );
                return 1;
	}

	if( arg == "all") 
	{
		inv = all_inventory(me, 1, MAX_CARRY*4);
		for (i=0;i<sizeof(inv);i++)
		{
			inv[i]->remove_from_user();
			destruct(inv[i]);
		}
                return 1;
	}


        if( !( item = find_any_object(arg) ) )
        {
                notify( "Không tìm thấy." );
                return 1;
        }
        if( item == me )
        {
                notify( "Bạn muốn gì ?" );
		return 1;
        }

        tell_user( me, "Bạn sử dụng Ma lực, phá huỷ %s hoàn toàn.", item->get_name() );

        if( item->is_char() )
        {
                item->remove_from_scene();
        }
        else if( item->is_item() )
        {
                if( !item->remove_from_user() ) item->remove_from_scene();
        }

        item->before_destruct();
        destruct(item);



        if( item ) 
        {
                notify( "Bạn đã phá huỷ." );
                return 1;
        }

        return 1;
}
