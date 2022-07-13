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
        set_name("领取道具使者");

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
		get_name()+":\n    我这里可以领取道具和查询帐号余额。\n"
		+ sprintf(ESC"输入活动编号\ntalk %x# bonus.1\n"ESC"查询余额\ntalk %x# bonus.3\n"ESC"离开", id, id) );
}


void do_bonus(string arg)
{
	__FILE__->do_bonus_2(this_player(),this_object(),arg);
}

void do_bonus_2(object me , object who, string arg)
{
	int flag, type, p, total, count, amount;
	string arg2, *key, name;
	object item;
	key = explode(arg, " ");
	if (key[0]=="1" && sizeof(key)>1)
	{
		if (me->get_pay_money_buy_item()>0)
		{
			send_user(me,"%c%s",'!',"您的申请正在处理中，请稍候。");
			return ;
		}
		if (sscanf(arg, "%d %s", type, arg2)!=2) return;
		me->set_pay_money_buy_item(1);    // 验证序列号
                me->set_pay_type(4);
                me->set_buy_item_cmd_string( sprintf("%x# bonus.2 ", getoid(who) ) );
		db_user_pay( me, sprintf( "%s:80\n"
	               		"GET http:/""/%s/getgoods.php?t=%s&u=%d&o=%d&n=%s&ip=%s&r=%d&h=%d\r\n", MAIN_D->get_php_ip(),
	               		MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), me->get_number(), arg2, get_ip_name(me), MAIN_D->get_region(), MAIN_D->get_host() ) );
log_file("php.dat", sprintf( "%s:80\n"
	               		"GET http:/""/%s/getgoods.php?t=%s&u=%d&o=%d&n=%s&ip=%s&r=%d&h=%d\r\n", MAIN_D->get_php_ip(),
	               		MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), me->get_number(), arg2, get_ip_name(me), MAIN_D->get_region(), MAIN_D->get_host() ) );
		log_file("getitem.txt",sprintf("%s %s %d %s\n",short_time(),me->get_id(),me->get_number(),arg2 ));
		return;
	}
	flag = to_int(key[0]);
	switch(flag)
	{
	case 1:
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
                send_user( me, "%c%c%d%s", '?', 16, 40, sprintf( "请输入活动编号：\n"
                        ESC "talk %x# bonus.1 %%s\n", getoid(who), flag ) );
		break;
	case 2:
		if (me->get_pay_money_buy_item()==0)
		{
			send_user(me,"%c%s",'!',"您没有申请领取物品。");
			return ;
		}
		if (me->get_pay_money_buy_item()==1)
		{
			send_user(me,"%c%s",'!',"您的申请正在处理中，请稍候。");
			return ;
		}
		if (sizeof(key)==1)
		{
			send_user(me,"%c%s",'!',"申请的返回值不对");
			return ;
		}
		item = new (key[1]);
		if (!item)
		{
			send_user(me,"%c%s",'!',"没有"+key[1]+"这样东西。");
			return;
		}
		count = 1;
		name = item->get_name();
		if( item->get_max_combined()>1 )
		{
			total = count;
			amount = USER_INVENTORY_D->carry_combined_item(me, item, total);
		        if( amount > 0 && item->set_amount(amount) )
		        {
		                if( p = item->move(me, -1) )
		                {
		                        item->add_to_user(p);
		                }
		        }
		        else    
		        {
		        	p = 1;
		        	item->add_amount( -total );
		        }
		}
		else
		{
			if( p = item->move(me, -1) )
		        {
		                item->add_to_user(p);
		        }
		}
		if ( !p )
		{
			send_user(me,"%c%s",'!',"您携带的东西太多了。");
			destruct(item);
			log_file("getitem.txt",sprintf("%s %s %d 领取%s失败\n",short_time(),me->get_id(),me->get_number(),item->get_name() ));
			return ;
		}
		else
			log_file("getitem.txt",sprintf("%s %s %d 领取%s成功\n",short_time(),me->get_id(),me->get_number(),name ));
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
			who->get_name()+":\n    您领取了一个"+name+"。\n" );
		me->set_pay_money_buy_item(0);
		break;
	case 3:
		if (me->get_pay_money_buy_item()>0)
		{
			send_user(me,"%c%s",'!',"您的申请正在处理中，请稍候。");
			return ;
		}
		me->set_pay_money_buy_item(1);    // 查询余额
                me->set_pay_type(5);
                me->set_buy_item_cmd_string( sprintf("%x# bonus.", getoid(who) ) );
		db_user_pay( me, sprintf( "%s:80\n"
	               		"GET http:/""/%s/querybalance.php?t=%s&u=%d\r\n", MAIN_D->get_php_ip(),
	               		MAIN_D->get_php_ip(), short_time_2(), me->get_acountid() ) );
log_file("php.dat", sprintf( "%s:80\n"
	               		"GET http:/""/%s/querybalance.php?t=%s&u=%d\r\n", MAIN_D->get_php_ip(),
	               		MAIN_D->get_php_ip(), short_time_2(), me->get_acountid() ) );
		return;
	}
}

