
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_zzy();
void accept_zzy();
void give_bonus();

// 函数：获取人物造型
int get_char_picid() { return 0951; }

// 函数：构造处理
void create()
{
        set_name( "巧克力精灵" );

        set_2( "talk", ([
                "zzy" : (: do_zzy :),
                "accept_zzy"	: (: accept_zzy :),
                "bonus_zy"	: (: give_bonus :),

        ]));

        setup();

}

// 函数：对话处理
void do_look( object who )
{
	object npc,item,me=this_object();
	int id = getoid( me ),i;
        string cmd = sprintf( "talk %x# zzy\n", id );
	string tmp ="";
	if ( who->get_quest("valentine.flag") == 8 && objectp( item = present("巧克力豆", who, 1, MAX_CARRY) ))
	tmp = ESC "情人节巧克力。\n" + cmd;
	send_user( who, "%c%s", ':', get_name() + "：\n    不同的巧克力都拥有着不同的涵义，但是都表达了浓浓的爱。\n" +
                        tmp +
                        ESC "离开。\nCLOSE\n" );	
}

void do_zzy()
{
	object who=this_player(); 
	object me = this_object();
        __FILE__ ->do_task_start(who, me);
}

void accept_zzy()
{
	object who=this_player(); 
	object me = this_object();
        __FILE__ ->accept_task(who, me);
}

void give_bonus(){ object who=this_player();__FILE__ ->give_bonus_2(who); }

// 函数：开始
void do_task_start( object who, object me )
{
	if ( who->get_quest("valentine.flag") == 8 )
	{
	string cWord="";
	cWord = sprintf(me->get_name() + "：\n    小姑娘，你也想送一块巧克力给自己的爱人吗？可是制作巧克力的机械需要你付出大量的法力才能驱动，你愿意吗？");
	send_user( who, "%c%s", ':', cWord +"\n"+
	ESC +sprintf("愿意。\ntalk %x# accept_zzy\n",getoid(me)) +
	ESC "不愿意。\nCLOSE\n" ); 
	}     
}
// 函数：得到巧克力
void accept_task( object who, object me )
{
        object item;
        string file,cWord="";
        int p,i;
	if ( who->get_quest("valentine.flag") == 8 && MAIN_D->get_host_type()!=4 )
	{
		if(USER_INVENTORY_D->count_empty_carry(who) < 3 )
		{
		        send_user(who,"%c%s",';',"您身上没有足够空位！建议您空出三格来放置情人节礼物。");
	    		return;
		}
	        if( objectp( item = present("巧克力豆", who, 1, MAX_CARRY) ) )
	        {
	        	item->remove_from_user();
	            	destruct(item); 
	        }
	        switch( random(4) )
	        {
	        	case 0 : file = "/item/04/0430";  break;
	                case 1 : file = "/item/04/0431";  break;
	                case 2 : file = "/item/04/0432";  break;
	                case 3 : file = "/item/04/0433";  break;
	               default : break;
	        }
	        for (i=0;i<3;i++)
	        {
	        	item = new (file);    
	                if ( item )
			{
				p = item->move(who,-1);
				item->add_to_user(p);			
			}	
		}
	     	who->set_mp(0);
		who->set_quest( "valentine.flag", 9 );
		who->add_exp(500);
		who->add_potential(10);
	       	send_user( who, "%c%s", '!', "得到"HIR"巧克力"NOR"三块");
	       	write_user(who,ECHO"因为你的真诚与勇气，得到了情人节礼物"+item->get_name()+"三块，赶紧送给心爱的他吧！");
	      	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"" ); 
	       	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,8,"" ); 		                        
	}

	if ( who->get_quest("valentine.flag") == 8 && MAIN_D->get_host_type()==4 )
	{
		if(USER_INVENTORY_D->count_empty_carry(who) < 3 )
		{
		        send_user(who,"%c%s",';',"您身上没有足够空位！建议您空出三格来放置情人节礼物。");
	    		return;
		}
	        if( objectp( item = present("巧克力豆", who, 1, MAX_CARRY) ) )
	        {
	        	item->remove_from_user();
	            	destruct(item); 
	        }
	        switch( random(4) )
	        {
	        	case 0 : file = "/item/04/0430m";  break;
	                case 1 : file = "/item/04/0431m";  break;
	                case 2 : file = "/item/04/0432m";  break;
	                case 3 : file = "/item/04/0433m";  break;
	               default : break;
	        }
	        for (i=0;i<3;i++)
	        {
	        	item = new (file);    
	                if ( item )
			{
				p = item->move(who,-1);
				item->add_to_user(p);			
			}	
		}
	     	who->set_mp(0);
		who->set_quest( "valentine.flag", 9 );
		who->add_exp(500);
		who->add_potential(10);
	       	send_user( who, "%c%s", '!', "得到"HIR"巧克力"NOR"三块");
	       	write_user(who,ECHO"因为你的真诚与勇气，得到了情人节礼物"+item->get_name()+"三块，赶紧送给心爱的他吧！");
	      	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"" ); 
	       	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,8,"" ); 		                        
	}
}

