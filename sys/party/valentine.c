/*****************************
	**情人节**
*****************************/

#include <ansi.h>
#include <music.h>
#include <task.h>

#include <time.h>
#include <cmd.h>

int iStart214,iFinish214,close_val,open_val=0;
object ChocoLate;

void get_chocolate();
// 函数：生成二进制码
void SAVE_BINARY() { }

void create()
{
	iStart214 = mktime(2007,2,14,0,0,0);	
	iFinish214 = mktime(2007,2,14,23,59,59);
	call_out("check_time",10);
}

void check_time()
{
	int i;
	remove_call_out("check_time");
	i = time();
	switch( open_val )
	{
		case 1 : 
			get_chocolate();
			break;
		case 0 : 
			if ( i > iFinish214 )
				return ;
			if ( i < iStart214 )	//没到时间
			{
				call_out("check_time",iStart214 - i);
				return ;
			}
			get_chocolate();
			break;
	}
}

// 函数：放入巧克力精灵
void get_chocolate()
{
	if ( !objectp(ChocoLate) )
	{
		ChocoLate = new("/npc/party/chocolate");
		ChocoLate->add_to_scene(1,170,190,8);
	}
}

// 函数：情人节飞贼任务（男）
void do_valentine4_call( object who, object me )
{
        object map, npc, item;
        string *member,name;
        int level, i, size;
        int z, x, y, p,iType,x1,y1;
	if( who->get_quest("valentine.flag") == 2 && who->get_quest("valentine.type") != 1)
	{
	      	x = who->get("valentine.x");
	       	y = who->get("valentine.y");
	       	z = who->get("valentine.z");
	       	name = who->get_quest("valentine.name");
	       	if ( !stringp(name) )	return ;		
	        if( !objectp( map = get_map_object(z) ) || !map->is_scene() ) return;
	        for( i = 0; i < 100; i ++ )
	        {
	        	if( p = get_valid_xy(z, abs( x + random(10) - 5 ), abs( y + random(10) - 5 ), IS_CHAR_BLOCK) )
	                {
	                	x1 = p / 1000;  y1 = p % 1000;  break;
	                }
	        }
	        npc = new( "/npc/party/rosethief" );
		npc->set_name(sprintf("诡异的飞贼(%d)", who->get_number()));
		npc->set_char_picid(0202);
		npc->set_max_hp(1);
		npc->set_ap(1);
		npc->set_dp(1);
		npc->set_cp(1);
		npc->set_pp(1);
		npc->set_sp(1);
		npc->set_walk_speed(4);  
		npc->set_attack_speed(3);
	        npc->add_to_scene(z, x, y, 3);
	        member = ({ sprintf( "%d", who->get_number() ) });
	        npc->set("user", member);
	        map->add_reset(npc);   
	        who->set_quest( "valentine.time", time() );
	        who->set_quest( "valentine.thief", sprintf( "%x#", getoid(npc) ) );
	        who->set_quest( "valentine.z", z );
	        who->set_quest( "valentine.x", x );
	        who->set_quest( "valentine.y", y );
	        who->set_quest("valentine.type",1);
	        npc->set( "task", who->get_number() );
	
		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,2,"诡异的飞贼" ); 
		send_user( who, "%c%s", '!', "你领取了情人节任务————诡异的飞贼！");
	}
}

// 函数：情人节流氓任务（女）
void do_valentine5_call( object who, object me )
{
	if( who->get_quest("valentine.flag") == 6 && who->get_quest("valentine.type")!= 1)
	{
	        object map, npc, item;
	        string *member,name;
	        int level, i, size;
	        int z, x, y, p,iType,x1,y1;
		if(USER_INVENTORY_D->count_empty_carry(who) < 3 )
		{
		        send_user(who,"%c%s",';',"您身上没有足够空位！建议您空出三格来放置忘情婆婆需要的东西。");
       			return;
		}
	      	x = who->get("valentine.x");
	       	y = who->get("valentine.y");
	       	z = who->get("valentine.z");
	       	name = who->get_quest("valentine.name");
	       	if ( !stringp(name) )	return ;		
	        if( !objectp( map = get_map_object(z) ) || !map->is_scene() ) return;
	        for( i = 0; i < 100; i ++ )
	        {
	        	if( p = get_valid_xy(z, abs( x + random(10) - 5 ), abs( y + random(10) - 5 ), IS_CHAR_BLOCK) )
	                {
	                	x1 = p / 1000;  y1 = p % 1000;  break;
	                }
	        }
                npc = new( "/npc/party/gangster" );
		npc->set_name(sprintf("情人节流氓(%d)", who->get_number()));
		npc->set_char_picid(0053);
		npc->set_max_hp(1);
		npc->set_ap(1);
		npc->set_dp(1);
		npc->set_cp(1);
		npc->set_pp(1);
		npc->set_sp(1);
		npc->set_walk_speed(4);  
		npc->set_attack_speed(3);
                npc->add_to_scene(z, x, y, 3);
                member = ({ sprintf( "%d", who->get_number() ) });
                npc->set("user", member);
                map->add_reset(npc);   
                who->set_quest( "valentine.time", time() );
                who->set_quest( "valentine.thief", sprintf( "%x#", getoid(npc) ) );
                who->set_quest( "valentine.z", z );
                who->set_quest( "valentine.x", x );
                who->set_quest( "valentine.y", y );
                who->set_quest("valentine.type",1);
                npc->set( "task", who->get_number() );

		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,6,"天使爱美丽" ); 
		send_user( who, "%c%s", '!', "你领取了情人节任务————天使爱美丽！");
	}
}

// 函数：取消情人节任务
void task_giveup(object who , int iKind)
{
        object map, *reset, npc, item;
        string thief,*member;
        int time, id, i, size;
        if( !who->get_quest("valentine.flag") )    
        {
                return;
        }
	if ( iKind != who->get_quest("valentine.flag") )
		return ;
        switch( iKind )
        {
	      default : break;
	       case 1 : 
	               	who->set_quest("valentine.flag",0);
	               	if( objectp( item = present("月老给的包裹", who, 1, MAX_CARRY) ) )
	               	{
	                	item->remove_from_user();
	                	destruct(item); 
	               	}          
	                break;
	       case 2 :
		        who->delete_quest("valentine.bonus");
		        if(     stringp( thief = who->get_quest("valentine.thief") ) 
	                &&    ( npc = find_char(thief) ))
	                {
			        member = npc->get("user");
			        thief = sprintf("%d",who->get_number());
			        member -= ({thief});
			        if ( sizeof(member) == 0 )
			        {
				        npc->remove_from_scene();
				        destruct(npc);        	
			        }          
		        }
	               	if( objectp( item = present("神秘的种子", who, 1, MAX_CARRY) ) )
	               	{
	               		item->remove_from_user();
	               		destruct(item); 
	               	}          
	
	                break;
	       case 3 : 
	       case 4 : 
	               	if( objectp( item = present("神秘的种子", who, 1, MAX_CARRY) ) )
	               	{
	               		item->remove_from_user();
	               		destruct(item);  
	               	}          
	                break;
	       case 5 : 	               	
	       case 6 :
	       		who->set_quest("valentine.flag",0);
		        who->delete_quest("valentine.bonus");
		        if(     stringp( thief = who->get_quest("valentine.thief") ) 
	                &&    ( npc = find_char(thief) ))
	                {
			        member = npc->get("user");
			        thief = sprintf("%d",who->get_number());
			        member -= ({thief});
			        if ( sizeof(member) == 0 )
			        {
				        npc->remove_from_scene();
				        destruct(npc);        	
			        }          
		        }
	               	if( objectp( item = present("忘情婆婆要的胭脂", who, 1, MAX_CARRY) ) )
	               	{
	               		item->remove_from_user();
	               		destruct(item); 
	               	}          
	               	if( objectp( item = present("忘情婆婆要的梳子", who, 1, MAX_CARRY) ) )
	               	{
	               		item->remove_from_user();
	               		destruct(item); 
	               	}          
	               	if( objectp( item = present("忘情婆婆要的头钗", who, 1, MAX_CARRY) ) )
	               	{
	               		item->remove_from_user();
	               		destruct(item); 
	               	}          
	                break;
	       case 7 : 
	       case 8 : 
	               	if( objectp( item = present("巧克力豆", who, 1, MAX_CARRY) ) )
	               	{
	               		item->remove_from_user();
	               		destruct(item);  
	               	}          
	                break;    
        }
        
        send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_VALENTINE,iKind,0,"" );
	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,iKind,"" ); 
	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"" ); 

        who->delete_quest("valentine.time");
        who->delete_quest("valentine.type");
        who->delete_quest("valentine.name");
        who->delete_quest("valentine.z");
        who->delete_quest("valentine.x");
        who->delete_quest("valentine.y");
        who->delete_quest("valentine.count");

}

// 函数：情人节任务信息
void send_task_list(object who)
{
	int iFlag;
	string name,id;
	object npc;
	if( iFlag = who->get_quest("valentine.flag") ) 
	{
		    
		switch( iFlag )
		{
		       	case 1 : // 1. 神秘的种子
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,1,"神秘的种子" ); 
		                break;
		
		       	case 2 : // 2. 诡异的飞贼
				if ( who->get_quest("valentine.bonus")==1 )
				{
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,2,"诡异的飞贼(已完成)" ); 
				}
		                else if(     stringp( id = who->get_quest("valentine.thief") ) 
		                &&    ( npc = find_char(id) ) )    // 30 分钟
		                {
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,2,"诡异的飞贼" ); 
		                }
		                else
		                {
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 				
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,2,"诡异的飞贼(任务失败)" ); 
		                }
		                break;

		       	case 3 : // 3. 求索
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,3,"求索" ); 
		                break;
		
		       	case 4 : // 4. 爱情之花
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,4,"爱情之花" ); 
		                break;
		       	case 5 : // 5. 情人节的传说
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,5,"情人节的传说" ); 
		                break;
		
		       	case 6 : // 6. 天使爱美丽
				if ( who->get_quest("valentine.bonus")==1 )
				{
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,6,"天使爱美丽(已完成)" ); 
				}
		                else if(     stringp( id = who->get_quest("valentine.thief") ) 
		                &&    ( npc = find_char(id) ) )    // 30 分钟
		                {
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,6,"天使爱美丽" ); 
		                }
		                else
		                {
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 				
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,6,"天使爱美丽(任务失败)" ); 
		                }
		                break;

		       	case 7 : // 3. 巧克力豆
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,7,"巧克力豆" ); 
		                break;
		
		       	case 8 : // 4. 情人节巧克力
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,8,"情人节巧克力" ); 
		                break;
	        }			
	}	
}

// 移除巧克力精灵
void destruct_chocolate()
{
	if ( objectp(ChocoLate) )
	{
		ChocoLate->remove_from_scene();
		destruct(ChocoLate);
	}
}

//设置情人节活动的开启和关闭
int set_valentine(int open,int close)
{
	open_val = open;
	close_val = close;
	check_time();
	return 1;	
}