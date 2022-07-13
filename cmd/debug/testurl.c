
#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

inherit DBASE_F;

object * userlist = ({ });
string * ret = ({ });

// 函数：命令处理
int main( object me, string arg )
{
        int i, size;
        object user;
        size = sizeof(userlist);
        if (size==0)
        {
        	for (i=0;i<30;i++)
        	{
        		user = new(USER);
        		user->set_id(sprintf("test%d", i+1));
        		userlist += ({ user });
        		ret += ({ " " });
        	}
        }
        size = sizeof(userlist);
	if (!arg)
	{
		for (i=0;i<size;i++)
		{
			tell_user(me, sprintf("%d: %s\n", i+1, ret[i]));
		}
		return;
	}
	switch(arg)
	{
	case "delete":
		for (i=0;i<size;i++)
			destruct(userlist[i]);
		userlist = ({ });
		ret = ({ });
		tell_user(me, "删除完毕。");
		break;
	case "add":
        	for (i=0;i<30;i++)
        	{
        		user = new(USER);
        		user->set_id(sprintf("test%d", i+1));
        		userlist += ({ user });
        		ret += ({ " " });
        	}
        	break;
        case "start":
        	for (i=0;i<size;i++)
        	{
        		db_user_authentic( userlist[i], "ten", sprintf( MAIN_D->get_php_ip()+":80\n"
				"GET /xq2/authentic.php?id=%s&passwd=1234567890&region=1&host=1\r\n", "ten") );    // 之后 destruct 要用 db_user_clear        			
			call_out( "check_auth_result", 1, userlist[i], i);
        	}
        	break;
	}
	   		
        return 1;
}

void check_auth_result(object me, int order)
{
	int size;
	string result = get_exchange_urs_string(me);
        if( result == "" )
        {
                call_out( "check_auth_result", 1, me, order );    // 继续等待结果
                return;
        }	
        size = sizeof(ret);
        if (order>=size) return;
        ret[order] = result;
}