
#include <cmd.h>

// 函数：命令处理
int main( object me, string arg )
{
        object obj;
        string *ids = ({ }), id, result;
        int i, size, len, flag;
log_file("test.dat", "fi\n");
        if( is_player(me) ) 
        {
                send_user(me, "%c%c", 0xfd, 0);
		return 1;
        }
	if (!arg)
        {
                send_user(me, "%c%c", 0xfd, 0);
		return 1;
        }	
/*        
        if (MAIN_D->get_host_type()==4||MAIN_D->get_host_type()==0)
        {
		obj = new ("/inh/user/list");   
		if (!obj)
		{     
	        	send_user(me, "%c%c", 0xfd, 0);
	        	return 1;
	        }
	        obj->set_owner(arg);
	        obj->restore();
	        for (i=0;i<6;i++)
	        {
	    		if (obj->get_save_2(sprintf("%d.number", i+1))==0) continue;
	    		send_user(me, "%c%c%c%c%c%d%s", 0xfd, 3, i+1, 0, obj->get_save_2(sprintf("%d.bantime", i+1))>time(), obj->get_save_2(sprintf("%d.number", i+1)), obj->get_save_2(sprintf("%d.name", i+1)) );
	        }
	}	       
	else
*/	
	{
		for (i=0;i<6;i++)
		{
			if (i==0) id = arg;
			else id = sprintf("%s#%d", arg, i+1);
			obj = new ("/inh/user/user");
			obj->set_id(id);
			if (obj->restore())
			{			
				send_user(me, "%c%c%c%c%c%d%s", 0xfd, 3, i+1, 0, obj->get_save("bantime")>time(), obj->get_number(), obj->get_name() );				
			}
			destruct(obj);
		}
	}
	send_user(me, "%c%c", 0xa1, 1);
        return 1;
}
