
// 函数：命令处理
int main( object me, string arg )
{
        object item;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

	if( !arg ) 
	{
                notify( "您要将哪样东西变成金色？" );
                return 1;
	}

        if( !( item = find_any_object(arg) ) )
        {
                notify( "无法找到这样东西。" );
                return 1;
        }
        if( item == me )
        {
                notify( "您连自己都想清除？" );
		return 1;
        }
        if (item->get_equip_type()==0)
	{
                notify( "只能将装备变成金色" );
                return 1;
	}
	
        tell_user( me, "Trang bị %s đã thành đồ Tử Kim", item->get_name() );

        "/sys/item/equip"->init_equip_prop_12345(item);
        send_user( me, "%c%d%c", 0x31, getoid(item), 0 );

        return 1;
}
