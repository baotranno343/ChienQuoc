
#include <equip.h>

// 函数：命令处理
int main( object me, string arg )
{
        object *inv, item, who = me, char, pawn;
        int i, size, type, total, index;
        string *ids = ({ }), *key, name, file, id;
	mapping list;
        if( is_player(me) )
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
	if (!arg) return 1;
	ids = explode(arg, " ");
	if (sizeof(ids)<3) return 1;
	type = to_int(ids[1]);
	index = to_int(ids[2]);
	if (type<0) return 1;
	if (index<0) return 1;
	arg = ids[0];
        if(!( who = find_player(arg) ) )
        {
                id = strlwr(arg);
                if( !user_exist(id) )
                {
                        notify( "这个用户并不存在！" );
		        return 1;
                }

                who = new( USER );
                who->set_id(id);
                if( !who->restore() )
                {
                	send_user(me, "%c%s", '!', "这个用户并不存在！");
                        destruct(who);
                        return 1;
                }

                if( char = find_player( sprintf( "%d", who->get_number() ) ) )
                {
                	destruct(who);
	        	send_user(me, "%c%s", '!', "该用户处于在线状态！");
	        	return 1;
                }
        }
        else
        {
        	send_user(me, "%c%s", '!', "该用户处于在线状态！");
        	return 1;
        }
        if (type==0)	// 删除道具
        {
        	who->restore_inventory();
        	if (index>= HEAD_TYPE)
        	{
        		if (who->get_equip(index))
        		{
        			item = who->get_equip(index);
        			send_user( me, "%c%c%d%c%w", 0xac, 1, who->get_number(), get_d(item), item->get_amount() );
log_file("gm/op.dat", sprintf("%s %s(%d) 删除 %s(%d) 装备 %s\n", short_time(), me->get_id(), me->get_number(), who->get_id(), who->get_number(), "/sys/item/equip"->get_save_prop_string(item) ));
        			destruct(item);
        		}
        	}
        	else
        	{
        		item = number_present(who, index, 0, 0);
        		if (item)
        		{
        			send_user( me, "%c%c%d%c%w", 0xac, 1, who->get_number(), get_d(item), item->get_amount() );
log_file("gm/op.dat", sprintf("%s %s(%d) 删除 %s(%d) 装备 %s\n", short_time(), me->get_id(), me->get_number(), who->get_id(), who->get_number(), "/sys/item/equip"->get_save_prop_string(item) ));        			
				destruct(item);
        		}
        	}
	        who->save_inventory();
	        who->save();
		who->before_destruct();
		destruct(who);
		return 1;
        }
        type --;
        pawn = new(PAWN);
        pawn->set_id(type);
        pawn->set_owner( who->get_id() );
        list = pawn->get_pawn();        
        if( !mapp(list) || !( size = sizeof( key = keys(list) ) ) )
        {
        	destruct(pawn);
        	destruct(who);
        	return 1;
        }
	if (list[sprintf("%02d", index)])
	{
log_file("gm/op.dat", sprintf("%s %s(%d) 删除 %s(%d) 当铺 %s\n", short_time(), me->get_id(), me->get_number(), who->get_id(), who->get_number(), list[sprintf("%02d", index)] ));		
		pawn->delete_pawn( sprintf( "%02d", index ) );
		pawn->save();
		send_user( me, "%c%c%d%c%c%w", 0xac, 7, who->get_number(), type+1, index, 200 );
	}
        destruct(pawn);
        destruct(who);
        return 1;
}

