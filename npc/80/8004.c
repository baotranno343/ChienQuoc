
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 5505; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Vương Khải");
        set_city_name("Tề Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
        setup();
}

void do_look( object who )
{
	object me = this_object();
	string tmp="";
	
	if ( who->get("escort.finish") == 1 )
	{
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}
        if(     who->get_quest("escort.flag")    // 运镖任务
        &&      who->get_quest("escort.leader") == 1    // 队长完成
        &&      who->get_quest("escort.name") == get_name() 
        && 	who->get_quest("escort.city")+" Quốc" == get_city_name() )    // 找对人了
        {
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}        
	
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( who->get_legend(TASK_10,3) && !who->get_legend(TASK_10,4) )
		tmp += sprintf(ESC HIY "索取菜种\ntalk %x# welcome.1\n",getoid(me));
	if ( ( who->get_legend(TASK_10,4) && !who->get_legend(TASK_10,6) ) || ( who->get_legend(TASK_10,6) && !who->get_legend(TASK_10,7) ) )
		tmp += sprintf(ESC HIY "带话给程风\ntalk %x# welcome.1\n",getoid(me));
			
	send_user(who,"%c%s",':',sprintf( "%s：\n    好汉，想去哪？路上见到尉迟老镖头所托付运镖的那人，可否替我催催他，就说他得加快速度，我已经等急了，站在这日夜翘首的，唉。\n", get_name(),  ) 
			+ tmp +
			ESC"离开"
			);

}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,p;
        object who,item,obj;  
        string cmd1;
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_10,3) && !who->get_legend(TASK_10,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    俗话说，巧妇难为无米之炊，没有好的种子怎么种得出好的庄稼，正好我这出了一批新种子，你拿去吧，也当是给我做做实验，送去回来后帮我催催那程风，叫他快点给我把东西运来。\n"ESC"得到菜种\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_10,4) && !who->get_legend(TASK_10,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    前几天朋友给我运了点东西，托尉迟老镖头给运过来，可听他说，当时因为人手不够，所以他找了个外面的人来帮他运这趟镖，虽说那人武艺高强，又是尉迟老镖头的好朋友，可我老放不下这颗心啊，这么多日子了，也没见他过来，据说他还逗留在Yên Quốc的禅武台，也不知道他在做什么，你给我去看看吧。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_10,6) && !who->get_legend(TASK_10,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道你这点小忙都不肯帮我吗？看在我帮过你的份上，你就去帮我找找他吧，我真的快急死了！\n"ESC"离开", me->get_name()));

        	break;
        case 2:
        	if ( who->get_legend(TASK_10,3) && !who->get_legend(TASK_10,4) )
        	{
        		item = new("item/98/0040");
        		if ( !item )
        			return ;
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			return ;
        		}
        		item->add_to_user(p);
        		send_user(who, "%c%s", '!', HIY"菜种 1/1");
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_10,4);
        		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,9,"索取菜种（1）(完成)" );
        		me->do_welcome(1);
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_10,4) && !who->get_legend(TASK_10,6) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_10,6);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,10,"带话给程风（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"带话给程风（2）");
        	}
        	break;
        }
}