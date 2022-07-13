#include <ansi.h>
object npc;
int *nId1 = ({
	11977,
	21974,
	18061,
	12976,
	10251,
	10248,
	64781,
	30830,
	11400,
	32599,
	10025,
	10340,
	10852,
	971,
	});
int *nId2 = ({	
	19976,
	10247,
	10035,
	});
int *nId3 = ({		
	18162,
	10248,
	});
int *nId4 = ({	
	30908,
	15994,
	10334,
	});

// 函数：命令处理
int main( object me, string arg )
{
	int p,x,y,z,r;
	object who,item;
        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        x = to_int(arg);
        if ( member_array(x,nId1) != -1 )
        	r = 1;
        else if ( member_array(x,nId2) != -1 )
        	r = 2;
        else if ( member_array(x,nId3) != -1 )
        	r = 3;
        else if ( member_array(x,nId4) != -1 )
        	r = 4;
        if ( r == 0 )
        {
                notify( "对方不在领取的范围！" );
		return 1;
        }	
	who = find_char(arg);
	if ( !objectp(who) )
	{
                notify( "对方不存在！" );
		return 1;
        }
        if ( r == 1 )
        {
        	if ( who->get_save("zgyuanlao") )
        	{
	                notify( "对方已经领取！" );
			return 1;
        	}	
        	item = 	new("item/std/6002");
        	p = item->move(who,-1);
        	if ( !p )
        	{
	                notify( "对方的物品太多，请其腾出位置！" );
			return 1;
        	}
        	item->add_to_user(p);
		who->add_title("Z001");
		who->set_save("zgyuanlao",1);
	}
	else  if ( r == 2 )	
		who->add_title("Z009");
	else  if ( r == 3 )	
		who->add_title("Z010");	
	else  if ( r == 4 )	
	{
		if ( who->get_gender() == 1 )
			who->add_title("Z011");	
		else 
			who->add_title("Z012");	
	}
	notify( "操作成功！" );
	log_file("xinrenwang.txt",sprintf("%s %s 操作 %s %d %d\n",short_time(),me->get_id(),who->get_id(),who->get_number(),r));
	return 1; 
}