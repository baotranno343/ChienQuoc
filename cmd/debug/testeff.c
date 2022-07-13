
#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：命令处理
int main( object me, string arg )
{
        int i, size, a1, a2, a3, a4;
        int * number = ({ 0, 0, 0, 0, 0, 0 });
        int * shape = ({ 0, 0, 0, 0, 0, 0 });
        int * level = ({ 0, 0, 0, 0, 0, 0 });
        string * namelist = ({ " ", " ", " ", " ", " ", " " });
        string * fam = ({ " ", " ", " ", " ", " ", " " });	
	object * temp, org;
	if (!arg)
	{
		return 1;
	}
	temp = children(arg);
/*	
	temp = children("/inh/user/user");
	size = sizeof(temp);
	if (size>0)
	{
		for (i=0;i<size;i++)
		{
			if (temp[i]->get_id()==arg)
				tell_user(me, sprintf("%d: %x#", i+1, getoid(temp[i])));
		}
	}
	tell_user(me, "ok");	        
	return 1;	
*/		
	size = sizeof(temp);
	if (size>0)
	{
		for (i=0;i<size;i++)
		{			
			if (objectp(temp[i]) && get_x(temp[i])>0) 
			{
				if (get_block(get_z(temp[i]), get_x(temp[i]), get_y(temp[i]))&IS_MAP_BLOCK) 
				{
					tell_user(me, sprintf("%d: %x# %d %d %d位置不对", i+1, getoid(temp[i]), get_z(temp[i]), get_x(temp[i]), get_y(temp[i])));
					temp[i]->reset_stuff(temp[i]);					
				}
				else
					tell_user(me, sprintf("%d: %x#", i+1, getoid(temp[i])));
			}			
		}
	}	        		
	tell_user(me, "ok");	        		
        return 1;
}
