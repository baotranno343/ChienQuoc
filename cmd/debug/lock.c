
#include <cmd.h>

// 函数：命令处理
int main( object me, string arg2 )
{
        object *user, char, who = me;
        string *ids = ({ }), id, result;
        int i, size, len, flag, order;
        string arg, name;
        int time, number;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        if (sscanf(arg2, "%s %d", arg, time)!=2)
        {
        	return 1;
        }        
        order = "/cmd/debug/basic"->get_order(arg);
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
                	if (time>0)
                		send_user(me, "%c%c%c%c%s", 0xfd, 4, 1, order, " ");
                	else
                		send_user(me, "%c%c%c%c%s", 0xfd, 5, 1, order, " ");
                        notify( "这个用户并不存在！" );
		        return 1;
                }

                who = new( USER );
                who->set_id(id);
                if( !who->restore() ) 
                {
                	if (time>0)
                		send_user(me, "%c%c%c%c%s", 0xfd, 4, 1, order, " ");
                	else
                		send_user(me, "%c%c%c%c%s", 0xfd, 5, 1, order, " ");                	
                        notify( "这个用户并不存在！" );
                        destruct(who);  return 1;
                }

                if( char = find_player( sprintf( "%d", who->get_number() ) ) )
                {
                        destruct(who);
                        who = char;
                }
                else    flag = 1;
        }
        name = who->get_name();
        number = who->get_number();        
        if (time>0)       
        { 
        	send_user(me, "%c%c%c%c%s", 0xfd, 4, 0, order, who->get_name());
        	who->set_save("bantime", time()+time*60);
        	result = sprintf("设置%s(%d)禁止进入游戏%d分钟。", name, number, time );
        }
        else
        {
        	send_user(me, "%c%c%c%c%s", 0xfd, 5, 0, order, who->get_name());
        	who->delete_save("bantime");
        	result = sprintf("允许%s(%d)进入游戏。", name, number );
        }
	send_user( me, "%c%s", '!', result );
        if (!flag)
        {
        	QUIT_CMD->main( who, "" );
        }
        else
        {
        	who->save();
        	destruct(who);
        }
        return 1;
}
