#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <effect.h>

inherit OFFICER;
mapping mpBox = ([
			261092132: ([ 32*8 +28 : ([ "legend2" : 32*8 +29,"obj" : "item/98/0036" ,"taskid":TID_CHUGUO, "taskno":22,"taskname":"九道谷里的宝物(完成)"])]),
		]);
// 函数：获取人物造型
int get_char_picid() { return 2301; }

// 有自己的do_look函数
int is_self_look() { return 1; }

// 函数：构造处理
void create()
{
        set_name("神笔石");

        setup();
}

// 函数：对话处理
void do_look( object who )
{
	int z,y,x,p,*nLegend,i,size;
	mapping mpTmp;
	z = get_z(who);x=get_x(this_object());y=get_y(this_object());
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
			send_user(who, "%c%c%w%s", 0x5a, 0, 10, "挖掘中……");
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
