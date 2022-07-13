#include <city.h>
#include <cmd.h>
#include <equip.h>
#include <ansi.h>
#include <task.h>
#include <time.h>
#include <effect.h>

/*
is_seller()
1	普通小贩
2	有数量限制的小贩
3	武器店老板
4	防具店老板
5	杂货店老板
6	药店老板
*/

// 函数:命令处理
int main( object me, string arg )
{
	object who, npc, item;
	string name, result, file;
	object orgnpc;
	int number, order, level, exp, pot, cash;
        if( !arg || !objectp( who = find_char(arg) ) ) return 1;

        if( me == who ) 
        {
                me->do_look(me);
                return 1;
        }
	"/quest/help"->send_help_tips(me, 48);
        if( !inside_screen_2(me, who) )
        {
                notify( "Bạn cách %s quá xa rồi.", who->get_name() );
                return 1;
        }
        else    
        if( !who->is_self_look() && (who->is_seller()> 0 && who->is_seller() != 2 || who->is_seller_2() || who->is_trader() || who->is_bonus_seller() ) )
        {
        	switch(who->is_seller())
        	{
		case 3:
			"/quest/help"->send_help_tips(me, 39);		
			break;
		case 4:
			"/quest/help"->send_help_tips(me, 40);		
			break;
		case 5:
			"/quest/help"->send_help_tips(me, 41);		
			break;
		case 6:
			"/quest/help"->send_help_tips(me, 42);		
			break;									
        	}      	
                send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), 
                        sprintf(" %s :\n "+"/quest/word"->get_normal_word(who)+"\n"
                                ESC "Tôi muốn xem hàng\nlist %x#\n"
                                ESC "Tôi chỉ xem qua thôi\nCLOSE\n", who->get_name(), getoid(who) ) );        	
	}       
        else if( who->is_item_seller() == 1 )    // 用点卡买道具！！直接弹出界面
        {
                LIST_CMD->main( me, sprintf( "%x#", getoid(who) ) );
        }	 
        else if( who->is_char() )
        {
	        if( me->get("huntian") && get_effect_3(me, EFFECT_PROGRESS2) )
	        {        	
	                file = me->get_progress_file();
	                arg = me->get_progress_arg();
	                if (file)
	                	file->effect_break(me, arg);        	
	                return 1;
	        }          	
                if( who->is_officer() ) 
                {        	
                	if (me->get_save_2("orgtask2.type")==2 && me->get_save_2("orgtask2.name")==who->get_name())
                	{
                		npc = me->get_2("orgtask2.npc");
                		if (objectp(npc))
                		{
                			if( !inside_screen_2(me, npc) )
                			{
                                        	send_user( me, "%c%s", '!', "您护送的人呢？！" );
                                        	return 1;                				
                			}
                			if (me->get_save_2("orgtask2.status")==1)
                			{
                				me->set_save_2("orgtask2.status", 2);
                				result = sprintf("%s:\n    谢谢你帮我找回了孩子，你们帮真乃侠义之帮.\n", who->get_name() );
                				result += sprintf(ESC"完成任务\nlook %x#\n", getoid(who));
						result += sprintf(ESC"离开\nCLOSE\n");		
						send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
                				return 1;
                			}
                			else
                			{
						name = me->get_org_name();
						if (name=="") return 1;
						orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );
						if (!objectp(orgnpc)) return 1;						
						number = me->get_number();
						level = me->get_level();
						order = me->get_save_2("orgtask2.order");
						order ++;
						orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number)+1+order*2/9);
						orgnpc->add_stable(2);
						orgnpc->add_favour(2);		
						exp = (level*8+order*order*level*4)*3/5;
						exp = exp * me->get_online_rate()/100;
						pot = order*10+level;
						pot = pot * me->get_online_rate()/100;
						cash = (500+level*6*(order-1))*3/6;	
						cash = cash * me->get_online_rate()/100;			
						me->add_potential(pot);
						me->add_cash(cash);
						me->add_exp(exp);
						result = sprintf("你获得经验%d，潜能%d，金钱%d，帮派贡献度%d点，帮派的人气提升2点、安定提升2点.\n", exp, pot, cash, 1+order*2/9 );
						send_user( me, "%c%s", ';', result );	
						me->delete_save_2("orgtask2");
						if (order>=10) 
						{
							order = 0;
							if (random100()<5*me->get_online_rate()/100) "/quest/box"->give_box(me);
						}
						me->set_save_2("orgtask2.order", order);
		                                npc->remove_from_scene();
		                                destruct(npc);	
						send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 2, "" );  
						send_user( me, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "" );			                                					
						return 1;						
                			}
                		}
                	}
                	if (me->get_save_2("orgtask2.type")==4 && me->get_save_2("orgtask2.name")==who->get_name())
                	{
                		
                		if (me->get_save_2("orgtask2.status")==1)
                		{
                			me->set_save_2("orgtask2.status", 2);
                			result = sprintf("%s:\n    谢谢你帮我带回家书，你们帮真乃情义之帮.\n", who->get_name() );
                			result += sprintf(ESC"完成任务\nlook %x#\n", getoid(who));
					result += sprintf(ESC"离开\nCLOSE\n");		
					send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
                			return 1;
                		}
                		else
                		{
					name = me->get_org_name();
					if (name=="") return 1;
					orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );
					if (!objectp(orgnpc)) return 1;						
					number = me->get_number();
					order = me->get_save_2("orgtask2.order");
					order ++;
					level = me->get_level();
					exp = (level*8+order*order*level*4)*3/5;
					exp = exp * me->get_online_rate()/100;
					pot = order*10+level;
					pot = pot * me->get_online_rate()/100;
					cash = (500+level*6*(order-1))*3/6;	
					cash = cash * me->get_online_rate()/100;			
					me->add_potential(pot);
					me->add_cash(cash);
					me->add_exp(exp);					
					orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number)+1+order*2/9);
					orgnpc->add_stable(1);
					orgnpc->add_favour(1);					
					me->add_exp(1000);
					result = sprintf("你获得经验%d，潜能%d，金钱%d，帮派贡献度%d点，帮派的人气提升1点、安定提升1点.", exp, pot, cash, 1+order*2/9);
					send_user( me, "%c%s", ';', result );	
					me->delete_save_2("orgtask2");	
					me->delete_2("orgtask2");
					if (order>=10) 
					{
						order = 0;
						if (random100()<5*me->get_online_rate()/100) "/quest/box"->give_box(me);
					}
					me->set_save_2("orgtask2.order", order);						
					item = present("家书", me, 1, MAX_CARRY*4);	
					if (item)
					{
						send_user( me, "%c%d", 0x2d, getoid(item) );
                        			destruct(item);
					}		
					send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 4, "" );  
					send_user( me, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "" );							
					return 1;						
                		}                		
                	}
                        me->to_front_eachother(who);
                        who->do_look(me);
                }
                else if( who->is_user() ) 
                {
                        if( me->get_enemy() == who || me->get_attack_mode()!=1 )    // !me->get_attack_mode()  无限制攻击
                                KILL_CMD->main( me, sprintf("%d", who->get_number() ) );
                        else if( who->can_be_fighted(me) && me->can_fight(who) ) 
                                send_user( me, "%c%d", 0x6b, who->get_number() );    // 发出走近，并 kill 指令
                        else    
                        {
                        	who->do_look(me);
                        	send_user(me,"%c%c%d%c",0xA2,6,who->get_number(),who->get_save_2("online_rank.level"));	//修为等级
                        }
                }
                else    KILL_CMD->main( me, sprintf("%x#", getoid(who) ) );
        }
	else
        	who->do_look(me);

        return 1;
}


void php_log()
{
	int count;
	mixed *mxTime;
	string result;
	mxTime = localtime(time());
	count = mxTime[TIME_HOUR]*2;
	if (mxTime[TIME_MIN]>=30) count++;
	result = "";
	if ("/sys/sys/id"->get_avguser())
	{
		result += sprintf("m=%d&a=%d&g=%d", "/sys/sys/id"->get_maxuser(), "/sys/sys/id"->get_avguser(), "/sys/sys/id"->get_cardcount());
		"/sys/sys/id"->init_count();
	}
	if ("/sys/sys/id"->get_buyer() && (count%2==0))
//	if ("/sys/sys/id"->get_buyer())
	{
		result += sprintf("&b=%d&i=%d&p=%d","/sys/sys/id"->get_buyer(), "/sys/sys/id"->get_buycount(), "/sys/sys/id"->get_buypoint() );
		"/sys/sys/id"->init_buy();
	}
	if (count==0 && "/sys/sys/id"->get_loginplayer())
//	if ("/sys/sys/id"->get_loginplayer())
	{
		result += sprintf("&u=%d&n=%d&l=%d","/sys/sys/id"->get_newuser(), "/sys/sys/id"->get_charnumber(), "/sys/sys/id"->get_loginplayer() );
		"/sys/sys/id"->init_login();
	}	
	"/sys/sys/id"->save();
	if (MAIN_D->get_host_type()==4)		
		db_sys_info( sprintf( "202.105.13.205:80\n"
			"GET /xq2/mop.php?region=%d&host=%d&%s&time=%d\r\n", MAIN_D->get_region(), MAIN_D->get_host(), result, time() ) ); 
/*			
	if (MAIN_D->get_host_type()!=4)	
		log_file("test.dat", sprintf( "http://202.105.13.205:80\n"
			"GET /xq2/mop.php?region=%d&host=%d&%s&time=%d\r\n", MAIN_D->get_region(), MAIN_D->get_host(), result, time() ) ); 
*/			
}