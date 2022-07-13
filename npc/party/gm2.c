
#include <npc.h>
#include <ansi.h>
#include <map.h>
#include <task.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5201; } 

// 函数：构造处理
void create()
{
        set_name( "GM" );  
        setup();     
}

void do_look( object who )
{
        int status;
        int time, p, type;
        string result, name;
        object item;
        object me = this_object();
        time = "/cmd/gm/findgm"->get_save("gm_time");
        if (who->get_save("findgm")==time)
        {
	        send_user( who, "%c%c%w%s", ':', 3, 5201,
	        	sprintf("%s：\n    我今天很感谢你，不过这次机会还是让给别人吧。\n"
	                , me->get_name() ) );        	
		return;	               
        }
        type = "/cmd/gm/findgm"->get_save("bonus");
        switch(time)
        {
        case 1:
        	name = "/item/08/0001";
        	break;    
        case 2:     	
        	name = "/item/08/0002";
        	break;         
        case 3:     	
        	name = "/item/08/0003";
        	break;            
        case 4:     	
        	name = "/item/08/0004";
        	break;         
        case 5:     	
        	name = "/item/04/0407";
        	break;       
        case 6:     	
        	name = "/item/91/9160";
        	break;    
        case 7:     	
        	name = "/item/91/9162";
        	break;         	     
        default:     	
        	name = "/item/91/9164";
        	break;         		  	    	 	 	 		
        }        
        item = new (name);
        if (!item) return;
        if( USER_INVENTORY_D->can_carry(who, item)  >=1 )
        {
                p =item->move(who, -1);
                item->add_to_user(p);
	        send_user( who, "%c%c%w%s", ':', 3, 5201,
	        	sprintf("%s：\n    终于来救我了，好勇敢呀！我要谢谢你的救命之恩，好好的重谢你！\n"
	                , me->get_name() ) );        	
		who->set_save("findgm", time);
		who->add_cash(20000);
		result = sprintf( HIY "%s援救ＧＭ成功，获得了%s和两万元。", who->get_name(), item->get_name() );
		USER_D->user_channel(result);
		me->remove_from_scene();
		destruct(me);                
		return;
        }      
        destruct(item);       
           
}
