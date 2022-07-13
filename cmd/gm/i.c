
#include <equip.h>

// 函数：命令处理
int main( object me, string arg )
{
        object *inv, item, who = me;
        int i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( arg && !( who = find_player(arg) ) ) 
        {
                notify( "无法找到这位玩家。" );
		return 1;
        }

        send_user( me, "%c%c%d%s", 0x76, 0, who->get_number(), sprintf( "%s(%d)\n%s\n%s\n%s\n%s\n", 
                who->get_name(), who->get_number(), 
                who->get_city_name() == "" ? "－－" : who->get_city_name(), 
                who->get_fam_name() == "" ? "－－" : who->get_fam_name(),
                who->get_org_name() == "" ? "－－" : who->get_org_name(),
                who->get_title() ) );
        send_user( me, "%c%c%c%d%d%c%d%w%s", 0x76, 0xff, 
                who->get_armor_code(), who->get_armor_color_1(), who->get_armor_color_2(), 
                who->get_head_code(), who->get_head_color(), who->get_weapon_code_2(),
                USER_RANK_D->get_rank(who) );

        inv = who->get_all_equip();
        for( i = 0, size = sizeof(inv); i < size; i ++ ) if( objectp( item = inv[i] ) )
                send_user( me, "%c%c%w%w%c%s", 0x76, get_d(item), 
                        item->get_picid_2(), item->get_amount(), item->get_item_type_2(),
                        sprintf( "%-12s%s", item->get_name(), ITEM_ITEM_D->get_look_string(me, item) ) );

        inv = all_inventory(who, 1, MAX_CARRY);
        for( i = 0, size = sizeof(inv); i < size; i ++ ) if( objectp( item = inv[i] ) )
                send_user( me, "%c%c%w%w%c%s", 0x76, get_d(item), 
                        item->get_picid_2(), item->get_amount(), item->get_item_type_2(),
                        sprintf( "%-12s%s", item->get_name(), ITEM_ITEM_D->get_look_string(me, item) ) );

        return 1;
}
