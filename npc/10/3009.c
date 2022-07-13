
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_task();

// 函数：获取人物造型
int get_char_picid() { return 5801; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tần Lão Hán");
	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));
	set("mpLegend2",([0:({32*46+2,32*46+5,32*47+16,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me=this_object();
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( who->get_legend(TASK_46,1)&&!who->get_legend(TASK_46,2) ) 
		tmp += sprintf(ESC HIY "确认传说\ntalk %x# welcome.1\n",getoid(me)); 
        if ( who->get_legend(TASK_46,2)&&!who->get_legend(TASK_46,5) ) 
		tmp += sprintf(ESC HIY "除掉无赖\ntalk %x# welcome.1\n",getoid(me)); 
        if ( who->get_legend(TASK_46,5)&&!who->get_legend(TASK_46,6) ) 
		tmp += sprintf(ESC HIY "询问消息\ntalk %x# welcome.1\n",getoid(me)); 
        if ( who->get_legend(TASK_47,15)&&!who->get_legend(TASK_47,16) ) 
		tmp += sprintf(ESC HIY "深入调查\ntalk %x# welcome.6\n",getoid(me)); 
        if ( who->get_legend(TASK_47,16)&&!who->get_legend(TASK_47,17) ) 
		tmp += sprintf(ESC HIY "破除谣言\ntalk %x# welcome.6\n",getoid(me)); 

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
		if ( who->get_legend(TASK_46,1)&&!who->get_legend(TASK_46,2) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，说起来此事也是甚为蹊跷，人们纷纷传说有恶神诅咒降临，如今本来热闹的村落人丁愈加零落，许多人都在计划搬走，只剩下我们几个老骨头和一些无处可去的孤儿寡母，煞是凄凉，我们无非是在等那不知何时降临的厄运罢了。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,2)&&!who->get_legend(TASK_46,3) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    刚刚有人告诉我刀魂之所以在这个小镇上杀戮，是因为本镇无赖甑九误入了诛仙阵抢走了刀魂的镇魂石，如今他躲在诛仙阵一层南部，还继续做他的发财大梦，浑然不知道他这种行为为本镇带来了多么大的祸害，你去将他杀掉，带回他的人头来当祭品，或许可以平息刀魂的怒气。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,3)&&!who->get_legend(TASK_46,4) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，看来老朽这把骨头也要交代了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_46,4)&&!who->get_legend(TASK_46,5) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    多谢义士拯救我们平阳镇，我得赶快派人告诉马先生，甑九被义士除了，这个人头现在我们就去摆放在刀魂的祭案上，但愿能够免除灾祸吧。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,5)&&!who->get_legend(TASK_46,6) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本镇的马显曾经嘱咐过如若除掉甑九，需得知会他，好为我镇前途再占一卦，我已经派人报告过他了，现在你去请他占一卦吧。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));

 	      	break;
     
        case 2:
        	if( who->get_legend(TASK_46,1)&&!who->get_legend(TASK_46,2) )
        	{
        		who->set_legend(TASK_46,2);
			who->add_exp(82000);
			who->add_potential(980);
			who->add_cash(68000);
			send_user(who,"%c%s",';',"刀魂传说1 经验 82000 潜能 980 金钱 68000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,64,"" );
			me->do_welcome(1);
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_46,2)&&!who->get_legend(TASK_46,3) )
        	{
        		who->set_legend(TASK_46,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,65,"刀魂传说2" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"刀魂传说2");
       		}
        	break;
        case 4:
        	if( who->get_legend(TASK_46,4)&&!who->get_legend(TASK_46,5) )
        	{
        		who->set_legend(TASK_46,5);
			who->add_exp(83000);
			who->add_potential(920);
			who->add_cash(96000);
			send_user(who,"%c%s",';',"刀魂传说2 经验 83000 潜能 920 金钱 96000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,65,"" );
			me->do_welcome(1);
        	}
        	break;
        case 5:
        	if ( who->get_legend(TASK_46,5)&&!who->get_legend(TASK_46,6) )
        	{
        		who->set_legend(TASK_46,6);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,66,"刀魂传说3" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"刀魂传说3");
       		}
        	break;
        case 6:
		if ( who->get_legend(TASK_47,15)&&!who->get_legend(TASK_47,16) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("“啊……”秦老汉神色变了，手中的水杯掉落到地上摔了个粉碎\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", getoid(me)));
		else if ( who->get_legend(TASK_47,16)&&!who->get_legend(TASK_47,17) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("（秦老汉用颤抖的手收拾了地面上的碎片，慢慢将他们扫拢，倒掉，仿佛你不存在一样，做完这些事情后，秦老汉方才抬起头来，眼中隐含着泪光）这些话真是我上次见过王妃之后和那瘾君子瞎编乱造的。我知道错了，但是老朽的确从来没有想过反对大王，我写了封认罪书，请你代我将它交给御史大人。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", getoid(me)));

		break;
        case 7:
        	if( who->get_legend(TASK_47,15)&&!who->get_legend(TASK_47,16) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/64189",1); 	
        		who->set_legend(TASK_47,16);
			who->add_exp(95000);
			who->add_potential(1200);
			who->add_cash(97000);
			send_user(who,"%c%s",';',"破除谣言4 经验 95000 潜能 1200 金钱 97000 摄魂行装图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,82,"" );
			me->do_welcome(6);
        	}
        	break;
        case 8:
        	if ( who->get_legend(TASK_47,16)&&!who->get_legend(TASK_47,17) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;
        		TASK_LEGEND_D->give_item(who,"item/98/0234",1); 
        		who->set_legend(TASK_47,17);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,83,"破除谣言5" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"破除谣言5");
       		}
        	break;
        }
}