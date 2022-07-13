
#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
#include <equip.h>

inherit OFFICER;

void do_bonus(string arg);
int check_item_amount(object who,string name);
void reduce_item_amount(object who,string name,int i);

// 函数：获取人物造型
int get_char_picid() { return 9312; } 

// 函数：构造处理
void create()
{
        set_name( "重阳老人" );
        set_2( "talk", ([
                 "bonus"         : (: do_bonus :),
        ]));    
        setup();     
}

void do_look( object who )
{
	__FILE__->do_look_2(who, this_object());
}

void do_look_2( object who, object me )
{
	string cmd1="",cmd2="";
	int id;
	id = getoid(me);
	cmd1 = sprintf(ESC"活动规则介绍\ntalk %x# bonus.6\n"ESC"活动时间查询\ntalk %x# bonus.7\n"ESC"给予重阳四宝\ntalk %x# bonus.2\n",id,id,id);
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		me->get_name()+":\n    我就是重阳老人，看这位小友举止不凡，一定不是普通人，不知道是否愿意帮助老朽收集重阳四宝呢？\n"
		+cmd1
		+ESC"离开" );
}


void do_bonus(string arg)
{
	__FILE__->do_bonus_2(this_object(),arg);
}

void do_bonus_2(object me , string arg)
{
	int flag, p,iTime,i,j,size,id,x,y,z,level,rate,amount,amount01,amount02,amount03;
       	object who, item,*nTeam,member,npc,map,item_q,*inv,*inv2,item_q1,item_q2,item_q3,item_q4;
       	string name,*nTmp,tmp,result="",result2="",cTmp;
	mixed *mxTime;  
	string *treasure=({"黄菊","茱萸","重阳糕","菊花酒",});
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 2:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    小友帮我寻到了重阳四宝吗？真是太感谢你了！\n"
			ESC"给予重阳四宝任意1件\ntalk %x# bonus.3\n"
			ESC"给予重阳四宝每样1件\ntalk %x# bonus.4\n"
			ESC"给予重阳四宝每样3件\ntalk %x# bonus.5\n"
			ESC"离开",me->get_name(),id,id,id));
        	break;
        case 3:
		for (i=0;i<4;i++)
		{
			if( objectp( item_q = present(treasure[i], who, 1, MAX_CARRY*4) ) ) j++;
		}
		if (!j)
        	{
        		send_user( who, "%c%s", ';', "我要的重阳四宝呢？");
        		return;
        	}  
		for (i=0;i<4;i++)
		{
			if( objectp( item_q = present(treasure[i], who, 1, MAX_CARRY*4) ) ) 
			{
				item_q->add_amount(-1);
				break;
			}
		}
		who->add_cash(500);
		result = result + HIR"500金、";
		who->add_exp(50+who->get_level()*25);
		result = result + sprintf(HIR"%d经验。",50+who->get_level()*25);
		send_user(who,"%c%s",';',"恭喜你获得 "+result);
        	break;
        case 4:
		if( !objectp( item_q1 = present("黄菊", who, 1, MAX_CARRY*4) ) )
		{
			send_user(who,"%c%s",';',"你的重阳四宝数量不足！");
			return;	
		}
		if( !objectp( item_q2 = present("茱萸", who, 1, MAX_CARRY*4) ) )
		{
			send_user(who,"%c%s",';',"你的重阳四宝数量不足！");
			return;	
		}
		if( !objectp( item_q3 = present("重阳糕", who, 1, MAX_CARRY*4) ) )
		{
			send_user(who,"%c%s",';',"你的重阳四宝数量不足！");
			return;	
		}
		if( !objectp( item_q4 = present("菊花酒", who, 1, MAX_CARRY*4) ) )
		{
			send_user(who,"%c%s",';',"你的重阳四宝数量不足！");
			return;	
		}
		if(USER_INVENTORY_D->count_empty_carry(who) < 1 )
		{
		        send_user(who,"%c%s",';',"请保留至少一格道具栏空间。");
	    		return;
		}
		item_q1->add_amount(-1);item_q2->add_amount(-1);item_q3->add_amount(-1);item_q4->add_amount(-1);
		who->add_exp(50+who->get_level()*25+who->get_level()*who->get_level());
		result = result + sprintf(HIR"%d经验、",50+who->get_level()*25+who->get_level()*who->get_level());
		item = new ("item/04/0463");//重阳礼包
		result = result + sprintf(HIR"%s。",item->get_name());
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		send_user(who,"%c%s",';',"恭喜你获得 "+result);
        	break;
        case 5:
		if ( check_item_amount(who,"黄菊") < 3 )
		{
			send_user(who,"%c%s",';',"你的重阳四宝数量不足！");
			return;	
		}
		if ( check_item_amount(who,"茱萸") < 3 )
		{
			send_user(who,"%c%s",';',"你的重阳四宝数量不足！");
			return;	
		}
		if ( check_item_amount(who,"重阳糕") < 3 )
		{
			send_user(who,"%c%s",';',"你的重阳四宝数量不足！");
			return;	
		}
		if ( check_item_amount(who,"菊花酒") < 3 )
		{
			send_user(who,"%c%s",';',"你的重阳四宝数量不足！");
			return;	
		}
		if(USER_INVENTORY_D->count_empty_carry(who) < 1 )
		{
		        send_user(who,"%c%s",';',"请保留至少一格道具栏空间。");
	    		return;
		}
		reduce_item_amount(who,"黄菊",3);reduce_item_amount(who,"茱萸",3);reduce_item_amount(who,"重阳糕",3);reduce_item_amount(who,"菊花酒",3);
		who->add_exp(50+who->get_level()*100+who->get_level()*who->get_level());
		result = result + sprintf(HIR"%d经验、",50+who->get_level()*100+who->get_level()*who->get_level());
		item = new ("item/04/0464");//重阳大礼包
		result = result + sprintf(HIR"%s。",item->get_name());
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		send_user(who,"%c%s",';',"恭喜你获得 "+result);
        	break;
        case 6:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    在活动期间，系统将会在新手村以及秦国、楚国、燕国、赵国、韩国、齐国和魏国郊外随机刷新重阳四宝，你只需要捡起重阳四宝交给我，我就会给予你一定的奖励哦！\n"
			ESC"离开",me->get_name()));
        	break;
        case 7:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    重阳节活动时间为10月19日10：00至10月20日22：00。\n    但是我会在大话战国里面一直待到10月23日22：00。没有领取奖励的朋友可以趁此机会领取奖励哦！\n"
			ESC"离开",me->get_name()));
        	break;
	}
}

int check_item_amount(object who,string name)
{
	object *inv;
	int i,amount,size;
	inv = all_inventory(who, 1, MAX_CARRY*4);
	
	for(i=0,size=sizeof(inv);i<size;i++)
	{
		if ( !objectp(inv[i]) )
			continue;
		if ( inv[i]->get_name() != name )
			continue;
		amount += inv[i]->get_amount();		
	}
	return amount;
}

void reduce_item_amount(object who,string name,int p)
{
	object *inv2;
	int i,j,size;
	j=p;
	inv2 = all_inventory(who, 1, MAX_CARRY*4);

	for(i=0,size=sizeof(inv2);i<size;i++)
	{
		if ( !objectp(inv2[i]) )
			continue;
		if ( inv2[i]->get_name() != name )
			continue;
        	if ( inv2[i]->get_amount() <= j )
        	{
        		j -= inv2[i]->get_amount();
        		inv2[i]->remove_from_user();
        		destruct(inv2[i]);
        	}
        	else
        	{
        		inv2[i]->set_amount(inv2[i]->get_amount()-j);
        		j = 0;
        	}     
        	if ( j == 0 )
        		break;

	}
	
}
