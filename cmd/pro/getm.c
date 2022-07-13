
#include <cmd.h>

int get_order(string id);

// 函数：命令处理
int main( object me, string arg2 )
{
        object *user, char, who = me;
        string *ids = ({ }), id, result, result2;
        int i, size, len, order, flag, z, x, y;
        string arg, name;
        int time, number;

        if( is_player(me) )
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        if (!arg2) return 1;
        ids = explode(arg2, " ");
        arg = ids[0];
        if (sizeof(ids)!=3) return 1;
        if(!( who = find_player(arg) ) )
        {
                id = strlwr(arg);
/*
                if( !CHECK_D->is_legal_id(me, id) )
                {
	        	return 1;
                }
*/
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
                else    flag = 1;
        }
        else
        {
        	send_user(me, "%c%s", '!', "该用户处于在线状态！");
        	return 1;
        }        
        x = to_int(ids[1]);
        y = to_int(ids[2]);
        switch(x)
        {
        case 3:
        	result2 = sprintf("现金 %d", who->get_cash());        	
        	who->set_cash(y);
        	send_user( me, "%c%c%d%d", 0xac, 3, who->get_number(), who->get_cash() );
        	break;
        case 4:
        	result2 = sprintf("存款 %d", who->get_savings());
        	who->set_savings(y);
        	send_user( me, "%c%c%d%d", 0xac, 4, who->get_number(), who->get_savings() );
        	break;      
        default:  
        	send_user(me, "%c%s", '!', "无法修改金钱！");
        	destruct(who);
        	return 1;
        	
        }
        
log_file("gm/op.dat", sprintf("%s %s(%d) 修改 %s(%d) %s %s\n", short_time(), me->get_id(), me->get_number(), who->get_id(), who->get_number(), result2, ids[2] ));

        who->save();
        destruct(who);
        return 1;
}

int get_order(string id)
{
	int i, size;
	size = strlen(id);
	if (size==0) return 1;
	for (i=0;i<size;i++)
	{
		if (id[i]=='#'&& i<size-1)
			return to_int(id[<1..<1]);
	}
	return 1;
}