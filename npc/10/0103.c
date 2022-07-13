#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5404; }

// 函数：构造处理
void create()
{
        set_name("Mã Đồng");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
	set("mpLegend2",([0:({32*36+30,32*37+9,32*37+12,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        if ( who->get_legend(TASK_36,29) && !who->get_legend(TASK_36,30) ) 
		tmp += sprintf(ESC HIY "肖独贵\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_36,30) && !who->get_legend(TASK_37,7)) || ( who->get_legend(TASK_37,7) && !who->get_legend(TASK_37,9) ) )
		tmp += sprintf(ESC HIY "僵尸粉\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_37,9) && !who->get_legend(TASK_37,10)) || ( who->get_legend(TASK_37,10) && !who->get_legend(TASK_37,12) ) )
		tmp += sprintf(ESC HIY "治疗\ntalk %x# welcome.1\n",getoid(this_object())); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    呜呜呜，我对不起肖大哥、大姐啊！都是我没有照顾好他，如今如何是好啊！\n", get_name())
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
        int flag,i,size,p,amount;
        object who,item, *inv;     
        string *nTmp,tmp;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_36,29) && !who->get_legend(TASK_36,30) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    肖大哥中了僵尸毒了！我多日奔走倒是有个云游道长告诉了我个治疗偏房，可是配方太难找了，哎，如今我整日奔波，忧心忡忡，心中羞愧万分，也不敢捎信给大姐啊。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_36,30) && !who->get_legend(TASK_37,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    肖大哥是中了僵尸毒，明确点说，他被僵尸咬了一口，现在已经是僵尸了，这种僵尸毒不是普通的解药能解的，必须要僵尸王身上的僵尸粉，而这种僵尸粉只有杀掉僵尸王才能拿到。现在僵尸王就在孤竹小筑的凝月湖，你穿过九曲桥就能找到。事情的详细经过，稍后再向你慢慢叙述吧。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_37,7) && !who->get_legend(TASK_37,8) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你也拿不到吗？哎，我要是救不回肖大哥，我也不想活了！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_37,8) && !who->get_legend(TASK_37,9) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢天谢地，终于拿到僵尸粉了，这个最大的困难解决了，肖大哥也许可以恢复了！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_37,9) && !who->get_legend(TASK_37,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    肖大哥的病况，在还差几件辅助的物品才能解毒，去九曲桥给我找点现行粉、糯米、保和丹来。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_37,10) && !who->get_legend(TASK_37,11) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    肖大哥整日被两种毒折磨得死去活来，你怎么一点都不着急呢？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_37,11) && !who->get_legend(TASK_37,12) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好了，万事具备，只欠东风，其他事情都交给我吧，我终于可以不必背负这么大的心理负担了。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));

        	break;

        case 2:
        	if ( who->get_legend(TASK_36,29) && !who->get_legend(TASK_36,30) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_36,30);
			who->add_exp(36000);
			who->add_potential(600);
			who->add_cash(40000);
			send_user(who,"%c%s",';',"肖独贵（2） 经验 36000 潜能 600 金钱 40000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,61,"" );
			me->do_welcome(1);
        	}
        	break;   
	case 3:
        	if ( who->get_legend(TASK_36,30) && !who->get_legend(TASK_37,7) )
        	{
          		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
          		who->set_legend(TASK_37,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_DONGHAIDAO,"东海岛" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_DONGHAIDAO,1,"肖独贵（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"肖独贵（3）");
        	}
        	break;
        case 4:
        	if ( who->get_legend(TASK_37,8) && !who->get_legend(TASK_37,9) ) 
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"僵尸粉",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_37,9);
			who->add_exp(45000);
			who->add_potential(655);
			who->add_cash(44000);
			send_user(who,"%c%s",';',"肖独贵（3） 经验 45000 潜能 655 金钱 44000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_DONGHAIDAO,1,"" );
			me->do_welcome(1);
        	}
        	break;
	case 5:
        	if ( who->get_legend(TASK_37,9) && !who->get_legend(TASK_37,10) )
        	{
          		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
          		who->set_legend(TASK_37,10);
			who->delete_save("mtxianxf");
			who->delete_save("mtnuomi");
			who->delete_save("mtbaohd");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_DONGHAIDAO,"东海岛" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_DONGHAIDAO,2,"肖独贵（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"肖独贵（4）");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_37,11) && !who->get_legend(TASK_37,12) ) 
        	{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),100,BOOTS_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
        		if (TASK_LEGEND_D->check_task_item(who,"现行粉",1) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"糯米",8) != 1 )
        		{
        			TASK_LEGEND_D->give_item(who,"item/98/0174",1);
        			return;
        		}
        		if (TASK_LEGEND_D->check_task_item(who,"保和丹",1) != 1 )
        		{
        			TASK_LEGEND_D->give_item(who,"item/98/0174",1);
        			TASK_LEGEND_D->give_item(who,"item/98/0175",8);
        			return;
        		}		
			TASK_LEGEND_D->give_item(who,tmp,1);
			who->delete_save("mtxianxf");
			who->delete_save("mtnuomi");
			who->delete_save("mtbaohd");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_37,12);
			who->add_exp(210000);
			who->add_potential(2300);
			who->add_cash(210000);
			send_user(who,"%c%s",';',sprintf("肖独贵（4） 经验 210000 潜能 2300 金钱 210000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_DONGHAIDAO,2,"" );
			me->do_welcome(1);
        	}
        	break;
        }
}