
#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
#include <equip.h>

inherit OFFICER;

void do_bonus(string arg);

// 函数：获取人物造型
int get_char_picid() { return 0552; } 

// 函数：构造处理
void create()
{
        set_name( "战国征集兵" );
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
	cmd1 = sprintf( ESC"上交1件金色装备\ntalk %x# bonus.1\n"
			ESC"上交2件紫色装备\ntalk %x# bonus.2\n"
			ESC"上交5件蓝色装备\ntalk %x# bonus.3\n",id,id,id);
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		me->get_name()+":\n    最近为抵御外族侵略，战场物资已出现供给不足现象。尔等身为华夏子民，理应为国家尽一份力量。本人奉周王之命特来征集以下物品：紫色装备、金色装备、蓝色装备。凡是参与者，将会视参与程度不同给予对应奖励。\n"
		+cmd1
		+ESC"离开" );
}


void do_bonus(string arg)
{
	__FILE__->do_bonus_2(this_object(),arg);
}

void do_bonus_2(object me , string arg)
{
	int flag, p,iTime,i,j,size,id,x,y,z,level,rate,amount,amount01,amount02,amount03,jj=0;
       	object who, item,*nTeam,member,npc,map,item_q,*inv,*inv2=({}),item_q1,item_q2,item_q3,item_q4;
       	string name,*nTmp,tmp,result="",result2="",cTmp;
	mixed *mxTime;  
	int *gift_color=({2,3,1,4});
	int *gift_amount=({1,2,5,8});
	string *gift_name=({"金","紫","蓝","绿"});
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
	case 1:
	case 2:
	case 3:
	case 4:
		inv = all_inventory(who, 1, MAX_CARRY);
		for (i=0;i<sizeof(inv);i++)
		{
			if ( inv[i]->is_equip() && inv[i]->get_equip_type() && (inv[i]->get_equip_type()!=107) && (inv[i]->get_item_color()==gift_color[flag-1]) )
			{
				if (inv[i]->get("make")){send_user(who,"%c%s",';',"你的道具栏有精炼装备。");return;}
				if (inv[i]->get("forge")){send_user(who,"%c%s",';',"你的道具栏有锻造装备。");return;}
				inv2 += ({ inv[i] });
				jj++;
				if(jj>=gift_amount[flag-1]) break;
			}
		}
		if (jj<gift_amount[flag-1]) 
		{
			send_user(who,"%c%s",';',sprintf("你没有足够%s装",gift_name[flag-1]));
			return;
		}
		for (i=0;i<sizeof(inv2);i++)
		{
			inv2[i]->remove_from_user();
			destruct(inv2[i]);
		}
		item = new (sprintf("/item/mop/800%d",flag));//礼包
		if ( item )
		{
			p = item->move2(who);
			item->add_to_user(p);	
			send_user(who,"%c%s",';',"恭喜你获得 "+item->get_name());
		}
		break;
	}
}
