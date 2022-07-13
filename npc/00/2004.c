#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <effect.h>

inherit OFFICER;
mapping mpBox = ([
			382043062: ([ 32*33+4 : ([ "legend2" : 32*33+5,"obj" : "item/98/0154" ,"taskid":TID_CHUGUO,"taskno":34,"taskname":"祖父的遗产（4）(完成)"])]),
		]);
// 函数：获取人物造型
int get_char_picid() { return 2200; }

// 有自己的do_look函数
int is_self_look() { return 1; }

// 函数：构造处理
void create()
{
        set_name("破罐子");

        setup();
}

// 函数：对话处理
void do_look( object who )
{
	int z,y,x,p,*nLegend,i,size;
	mapping mpTmp;
	z = get_z(who);x=get_x(this_object());y=get_y(this_object());
//	if( z == 2 && who->get_legend(TASK_NEWBIE_02, 12) && !who->get_legend(TASK_NEWBIE_02, 13)&& !who->get_save_2("dssouzuo1") )
	if( (z==2||z==5||z==8) && who->get_legend(TASK_49, 9) && !who->get_legend(TASK_49, 10)&& !who->get_save_2("dssouzuo1") )
	{
		if (get_effect(who, EFFECT_OPEN_BOX)) return;
		send_user(who, "%c%c%w%s", 0x5a, 0, 10, "寻找中……");
		set_effect_2(who, EFFECT_OPEN_BOX, 1,10);
		who->set("openbox",this_object());
	}	
	else
	{
		p = z*1000000 + x * 1000+y;
		if ( !mapp(mpBox[p]) )
			return ;
		nLegend = keys(mpBox[p]);
		for(i=0,size=sizeof(nLegend);i<size;i++)
		{
			mpTmp = mpBox[p][nLegend[i]];
			if ( !mapp(mpTmp) )
				continue;
			if ( !who->get_legend(nLegend[i]/32, nLegend[i]%32) || who->get_legend(mpTmp["legend2"]/32, mpTmp["legend2"]%32) )
				continue;
			if (get_effect(who, EFFECT_OPEN_BOX)) return;
			who->set("openbox",this_object());
			send_user(who, "%c%c%w%s", 0x5a, 0, 10, "寻找中……");
			set_effect_2(who, EFFECT_OPEN_BOX, 1,10);				
			return;
		}
	}
}

void into_effect( object who,object npc )
{
	object item;
	int p,z,x,y;
	int i,size,*nLegend;
	mapping mpTmp;
	string tmp;
	
	z=get_z(who);
//	if ( z == 2 && who->get_legend(TASK_NEWBIE_02, 12) && !who->get_save_2("dssouzuo1") )
	if ( (z==2||z==5||z==8) && who->get_legend(TASK_49, 9) && !who->get_save_2("dssouzuo1") )
	{
		item = new("item/98/9888");
		if ( !item ) return;
		 p =item->move(who, -1);
		if( p )
		{
                        item->add_to_user(p);	
                        send_user( who, "%c%s", '!', "您获得了"HIY"丢失的手镯");
			who->set_save_2("dssouzuo1",1);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,117,"丢失的手镯(已经完成)" );					
			USER_TASK_D->send_task_intro(who,2,TID_NEWBIE_01,117);
		}
		else
		{
                       	destruct(item); 
                       	send_user( who, "%c%s", '!', "您身上没有空位！");				
		}
	}		
	else 
	{
		x = get_x(npc);
		y = get_y(npc);
		p = z*1000000 + x * 1000+y;
		if ( !mapp(mpBox[p]) )
			return ;
		nLegend = keys(mpBox[p]);
		for(i=0,size=sizeof(nLegend);i<size;i++)
		{
			mpTmp = mpBox[p][nLegend[i]];
			if ( !mapp(mpTmp) )
				continue;
			if ( !who->get_legend(nLegend[i]/32, nLegend[i]%32) || who->get_legend(mpTmp["legend2"]/32, mpTmp["legend2"]%32) )
				continue;
			item = new(mpTmp["obj"]);
			if ( !item ) return;
			p =item->move(who, -1);
			if( p )
			{
	                        item->add_to_user(p);	
	                        who->set_legend(mpTmp["legend2"]/32, mpTmp["legend2"]%32);
	                        send_user( who, "%c%s", '!', "您获得了"HIY+item->get_name());
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,mpTmp["taskid"],mpTmp["taskno"],mpTmp["taskname"] );
				USER_TASK_D->send_task_intro(who,2,mpTmp["taskid"],mpTmp["taskno"]);
			}
			else
			{
	                       	destruct(item); 
	                       	send_user( who, "%c%s", '!', "您身上没有空位！");				
			}			
			return;
		}		
	}
}
