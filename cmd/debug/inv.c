
#include <equip.h>

// 函数：命令处理
int main( object me, string arg )
{
        object *inv, obj, who = me;
        string str, result = "";
        int len, i, size;

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

        tell_user( me, who->get_name() + "已经装备：" );
        if( objectp( obj = who->get_equip(HEAD_TYPE) ) ) tell_user( me, 
                sprintf( "帽子：(%d)%s %x#", get_d(obj), obj->get_name(), getoid(obj) ) );
        if( objectp( obj = who->get_equip(NECK_TYPE) ) ) tell_user( me, 
                sprintf( "饰物：(%d)%s %x#", get_d(obj), obj->get_name(), getoid(obj) ) );
        if( objectp( obj = who->get_equip(WEAPON_TYPE) ) ) tell_user( me, 
                sprintf( "武器：(%d)%s %x#", get_d(obj), obj->get_name(), getoid(obj) ) );
        if( objectp( obj = who->get_equip(ARMOR_TYPE) ) ) tell_user( me, 
                sprintf( "衣服：(%d)%s %x#", get_d(obj), obj->get_name(), getoid(obj) ) );
        if( objectp( obj = who->get_equip(WAIST_TYPE) ) ) tell_user( me, 
                sprintf( "腰带：(%d)%s %x#", get_d(obj), obj->get_name(), getoid(obj) ) );
        if( objectp( obj = who->get_equip(BOOTS_TYPE) ) ) tell_user( me, 
                sprintf( "鞋子：(%d)%s %x#", get_d(obj), obj->get_name(), getoid(obj) ) );
        if( objectp( obj = who->get_equip(HAND_TYPE) ) ) tell_user( me, 
                sprintf( "手握：(%d)%s %x#", get_d(obj), obj->get_name(), getoid(obj) ) );

        if( !sizeof_inventory(who, 1, MAX_CARRY) ) 
        {
                tell_user( me,  "%s身上没有东西。", who->get_name() );
		return 1;
        }

        inv = all_inventory(who, 1, MAX_CARRY);
        size = sizeof(inv);
        for( i = 0, len = 0; i < size; i ++ )
        {
                if( !inv[i]->is_combined() )
                        str = sprintf( "(%d)%s %x#", get_d( inv[i] ), inv[i]->get_name(), getoid( inv[i] ) );
                else    str = sprintf( "(%d)%s:%d %x#", get_d( inv[i] ), inv[i]->get_name(), inv[i]->get_amount(), getoid( inv[i] ) );
                len += strlen(str) + 2;
                if( len >= OUTPUT_WIDTH )
                {
                        len = strlen(str);
                        result = sprintf( "%s\n%s ", result, str );
                }
                else    result = sprintf( "%s%s ", result, str );
        }
        tell_user( me, "%s身上拥有：\n%s", who->get_name(), result );

        return 1;
}
