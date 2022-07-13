
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_task();

// 函数：获取人物造型
int get_char_picid() { return 0053; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Ẩn Quân Tử");
	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));
	set("mpLegend2",([0:({32*47+11,32*47+14,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
 	object me=this_object();
 	
        tmp += CHAIN_D->get_chain_menu(who,me);
         if ( who->get_legend(TASK_47,10)&&!who->get_legend(TASK_47,11) ) 
		tmp += sprintf(ESC HIY "追问详情\ntalk %x# welcome.1\n",getoid(me)); 
         if ( who->get_legend(TASK_47,11)&&!who->get_legend(TASK_47,14) ) 
		tmp += sprintf(ESC HIY "除掉恶人\ntalk %x# welcome.1\n",getoid(me)); 
         if ( who->get_legend(TASK_47,14)&&!who->get_legend(TASK_47,15) ) 
		tmp += sprintf(ESC HIY "深入调查\ntalk %x# welcome.1\n",getoid(me)); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    我最值得骄傲的事情就是，这辈子没有求过人！\n", get_name())
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
       	string *nTmp,tmp;     
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:
		if ( who->get_legend(TASK_47,10)&&!who->get_legend(TASK_47,11) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿嘿嘿，雀妖本来是天上的太阳精灵三足鸟，由于数目太多引起地气阳气过剩，干旱连年遭后羿射杀，其中有只被射伤的恰好掉落到诛仙阵阵眼之上，得到了源源不断的魂气支持得以重生为妖，唉，我们大王啊，哪里抵的过雀妖的媚惑啊。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_47,11)&&!who->get_legend(TASK_47,12) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你问我怎么知道得这么清楚，我老大许小四告诉我们小的啊，要不然我大字不识几个，怎么会知道这么隐秘的情况，有本事你去找我们老大问啊，不过放心我们老大可是很友善的，他会很友善的留下你的脑袋装酒，哈哈哈……我们老大在诛仙阵三层北部，他会盛情款待你的，哈哈……\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_47,12)&&!who->get_legend(TASK_47,13) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿嘿，挑不过我们老大还敢来同我硬？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_47,13)&&!who->get_legend(TASK_47,14) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊……（眼睛贼溜溜一阵转，掠过一丝不易察觉的精光）哼哼，你有本事！就不怕我们帮派的报复么？\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_47,14)&&!who->get_legend(TASK_47,15) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，其实不过是我那天去紫烟楼下讨酒喝的时候恰巧碰到大王出巡，秦老汉也在人群中，大家见了王妃觉得惊为天人，当下喝了点酒，神智糊涂，就瞎编乱造了一通，后来大家无聊，就越编越玄，小人真的没有半点造反的意思啊，求大侠高抬贵手，为我美言几句。不信你再去问问秦老汉，他可以为我作证。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));

		break;
        case 2:
        	if( who->get_legend(TASK_47,10)&&!who->get_legend(TASK_47,11) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_47,11);
			who->add_exp(91000);
			who->add_potential(1200);
			who->add_cash(88000);
			send_user(who,"%c%s",';',"破除谣言2 经验 91000 潜能 1200 金钱 88000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,80,"" );
			me->do_welcome(1);
        	}
        	break;        	
        case 3:
        	if ( who->get_legend(TASK_47,11)&&!who->get_legend(TASK_47,12) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_47,12);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,81,"破除谣言3" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"破除谣言3");
       		}
        	break;
        case 4:
        	if( who->get_legend(TASK_47,13)&&!who->get_legend(TASK_47,14) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_47,14);
			who->add_exp(93000);
			who->add_potential(1350);
			who->add_cash(86000);
			send_user(who,"%c%s",';',"破除谣言3 经验 93000 潜能 1350 金钱 86000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,81,"" );
			me->do_welcome(1);
        	}
        	break;
        case 5:
        	if ( who->get_legend(TASK_47,14)&&!who->get_legend(TASK_47,15) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_47,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,82,"破除谣言4" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"破除谣言4");
       		}
        	break;
        }
}