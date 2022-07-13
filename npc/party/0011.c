#include <npc.h>
#include <city.h>
#include <ansi.h>
inherit SAVE_F;
inherit OFFICER;

void do_bonus(string arg);


// 函数：获取人物造型
int get_char_picid() { return 5302; }

// 函数：构造处理
void create()
{
	int i,size,*nTmp;
        set_name("礼物领取使者");

        set_2( "talk", ([
                 "bonus"         : (: do_bonus :),
        ]) );

        setup();
}

void do_look( object who )
{
	int id;
	
	id = getoid(this_object());
	send_user( who, "%c%c%w%s", ':', 3, get_char_picid(),
		get_name()+":\n    在我这里可以领取乱世星人和乱世英雄的奖励\n"
		+ sprintf(ESC"领取乱世英雄的奖励\ntalk %x# bonus.1\n"ESC"领取全家英雄的奖励\ntalk %x# bonus.2\n"ESC"领取帮派虚宝包的奖励\ntalk %x# bonus.3\n"ESC"离开", id, id, id) );
}


void do_bonus(string arg)
{
	__FILE__->do_bonus_2(this_player(),this_object(),arg);	
}

void do_bonus_2(object me , object who, string arg)
{
	int flag, type, p;
	string arg2;
	object item;
	if (strlen(arg)>5)
	{			
		if (me->get_pay_money_buy_item()>0)
		{
			send_user(me,"%c%s",'!',"您的申请正在处理中，请稍候。");
			return ;
		}
		if (sscanf(arg, "%d %s", type, arg2)!=2) return;
		me->set_pay_money_buy_item(1);    // 验证序列号
                me->set_pay_type(2);		
                me->set("moneytype", type);
                me->set_buy_item_cmd_string( sprintf("%x# bonus.%d", getoid(who), 10+type) );
		db_user_pay( me, sprintf( "%s:80\n"
			"GET /xq2/bdid.php?id=%s&type=%d&code=%s\r\n", MAIN_D->get_php_ip(), 
        	        rawurlencode( me->get_id() ), type, arg2 ) );    // 检查序列号
		log_file("newbie.txt",sprintf("%s %s %d %s %d\n",short_time(),me->get_id(),me->get_number(),arg2, type ));                	
		return;		
	}
	flag = to_int(arg);
	switch(flag)
	{ 
	case 1:
	case 2:
	case 3:
		if (me->get_pay_money_buy_item()>0)
		{
			send_user(me,"%c%s",'!',"您的申请正在处理中，请稍候。");
			return ;
		}	
                if( sizeof_inventory(me, 1, MAX_CARRY) >= MAX_CARRY )
                {
                        notify( "您携带的东西太多了。" );
                        return ;
                }	
                if (flag==1)	
                	send_user( me, "%c%c%d%s", '?', 16, 40, sprintf( "请输入乱世英雄的序列号：\n"
                        	ESC "talk %x# bonus.%d %%s\n", getoid(who), flag ) );		
		else
		if (flag==2)                       
                	send_user( me, "%c%c%d%s", '?', 16, 40, sprintf( "请输入全家英雄的序列号：\n"
                        	ESC "talk %x# bonus.%d %%s\n", getoid(who), flag ) );		

		else
                	send_user( me, "%c%c%d%s", '?', 16, 40, sprintf( "请输入帮派争霸的序列号：\n"
                        	ESC "talk %x# bonus.%d %%s\n", getoid(who), flag ) );						
		break; 		
	case 11:               
	case 12:
	case 13: 
		if (me->get_pay_money_buy_item()==0)
		{
			send_user(me,"%c%s",'!',"您没有申请序列号验证。");
			return ;
		}
		if (me->get_pay_money_buy_item()==1)
		{
			send_user(me,"%c%s",'!',"您的申请正在处理中，请稍候。");
			return ;
		}
		if (me->get("moneytype")!=flag-10)
		{
			send_user(me,"%c%s",'!',"验证序列号有误");
			return ;
		}		
		if (flag==11)
			item = new ("/item/04/0410");
		else
		if (flag==12)
			item = new ("/item/04/0411");
		else
			item = new ("/item/04/0440");
		if (!item) return;
		p = item->move(me,-1);
		if ( !p )
		{
			send_user(me,"%c%s",'!',"您携带的东西太多了。");
			destruct(item);
			log_file("newbie.txt",sprintf("%s %s %d 领取%s失败\n",short_time(),me->get_id(),me->get_number(),item->get_name() ));                
			return ;
		}	
		else	
			log_file("newbie.txt",sprintf("%s %s %d 领取%s成功\n",short_time(),me->get_id(),me->get_number(),item->get_name() ));                
		item->add_to_user(p);			
		if (flag==13)
		{
			send_user( me, "%c%c%w%s", ':', 3, get_char_picid(),
				who->get_name()+":\n    您获得了一个"+item->get_name()+"。\n" );				
			me->set_pay_money_buy_item(0);	
			break;		
		}							
		me->add_cash(50000);	
		if (flag==11)
		{
			me->add_title("G001");
			"/sys/sys/title"->show_title(me, "G001");
		}
		else
		if (flag==12)
		{
			me->add_title("G002");
			"/sys/sys/title"->show_title(me, "G002");
		}
				
		send_user( me, "%c%c%w%s", ':', 3, get_char_picid(),
			who->get_name()+":\n    您获得了一个"+item->get_name()+"，五万金。\n" );				
		me->set_pay_money_buy_item(0);
		break;			    
	}
}

