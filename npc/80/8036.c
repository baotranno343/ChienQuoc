
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;
string *TalkTable = ({ 
        "Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
        "Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});
void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 0053; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Mã Hiển");
        set_city_name("Tần Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",40);
//	set("legend",({32*10+17}));
	set("mpLegend",([40:({32*10+17})]));
	set("mpLegend2",([0:({32*46+7,32*46+10,32*47+9,}),40:({32*10+19,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string tmp="";
	string *npc_info;
	
	if ( who->get("escort.finish") == 1 )
	{
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}
	npc_info = who->get_quest("escort.npcinfo");
	if ( who->get_quest("escort.biaowang") && arrayp(npc_info) && 
		npc_info[1] == me->get_name())
		tmp += sprintf(ESC HIG "镖王争霸战\ntalk %x# welcome.21\n",getoid(me));
        else if(     who->get_quest("escort.flag")    // 运镖任务
        &&      who->get_quest("escort.leader") == 1    // 队长完成
        &&      who->get_quest("escort.name") == get_name() 
        && 	who->get_quest("escort.city")+" Quốc" == get_city_name() )    // 找对人了
        {
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}        
	
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( ( who->get_level() >= 40 && !who->get_legend(TASK_10,17) ) || ( who->get_legend(TASK_10,17) && !who->get_legend(TASK_10,19) ) )
		tmp += sprintf(ESC HIY "寻找菜谱\ntalk %x# welcome.1\n",getoid(me));
        if ( who->get_legend(TASK_46,6)&&!who->get_legend(TASK_46,7) ) 
		tmp += sprintf(ESC HIY "询问消息\ntalk %x# welcome.4\n",getoid(this_object())); 
        if ( who->get_legend(TASK_46,7)&&!who->get_legend(TASK_46,10) ) 
		tmp += sprintf(ESC HIY "勇闯诛仙阵\ntalk %x# welcome.4\n",getoid(this_object())); 
        if ( who->get_legend(TASK_46,10)&&!who->get_legend(TASK_46,11) ) 
		tmp += sprintf(ESC HIY "危险解除\ntalk %x# welcome.4\n",getoid(this_object())); 
        if ( who->get_legend(TASK_47,8)&&!who->get_legend(TASK_47,9) ) 
		tmp += sprintf(ESC HIY "探明谣传\ntalk %x# welcome.9\n",getoid(this_object())); 
        if ( who->get_legend(TASK_47,9)&&!who->get_legend(TASK_47,10) ) 
		tmp += sprintf(ESC HIY "追问详情\ntalk %x# welcome.9\n",getoid(this_object())); 
			
	send_user(who,"%c%s",':',sprintf( "%s：\n    %s\n", get_name(), TalkTable[ random(sizeof(TalkTable))] ) 
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
        	if ( who->get_level() >= 40 && !who->get_legend(TASK_10,17)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    开酒店靠的就是这菜谱吸引客人，菜谱做得好，让客人看见就有想吃的冲动，这样才赚得到钱，除了我的厨艺，这菜谱也算是我们酒店的命根子，所以平日里我都随身携带。\n    可是前日出去游玩，居然不小心将菜谱弄丢了，我估计是掉在郑Quốc渠了，你去看看能不能替我找回来，如果找不回来麻烦可大了，唉。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_10,17) && !who->get_legend(TASK_10,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果菜谱找不到，我这小酒店也要关门喽！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_10,18) && !who->get_legend(TASK_10,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    多亏你找到了，如果没了这菜谱，我要怎么做生意！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >= 40 && !who->get_legend(TASK_10,17)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_10,17);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,17,"寻找菜谱" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"寻找菜谱");
        	}
        	break;
       case 3:
        	if ( who->get_legend(TASK_10,18) && !who->get_legend(TASK_10,19) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"菜谱",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_10,19);
			who->add_exp(4200);
			who->add_potential(115);
			who->add_cash(3000);
			send_user(who,"%c%s",';',"寻找菜谱 经验 4200 潜能 115 金钱 3000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,17,"" );
        	}
        	break; 
	case 4:
		if ( who->get_legend(TASK_46,6)&&!who->get_legend(TASK_46,7) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    让我来占上一卦，（转向东南，执毫画苻）神里灵灵，通幽达冥；松君效职，兰友凝声；仙真降格，速写云骤！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,7)&&!who->get_legend(TASK_46,8) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我占过卦之后，得到上天提示，甑九共抢劫了30个刀魂和30个枪魂的镇魂石，为了天地秩序回归正常，重新恢复诛仙阵的阵法，必须杀掉30个刀魂和30个枪魂使之镇魂的力量与魂魄数量相符，你记住，一个不可多，一个不可少，否则也可能出现不可控的灾难，完成任务之后回来告诉我，我再问问天是否有其他没有考虑到的遗漏。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,8)&&!who->get_legend(TASK_46,9) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你还未回归诛仙阵的秩序，我平阳镇的灾难不知道何时才能解除啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_46,9)&&!who->get_legend(TASK_46,10) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    让我再来占上一卦。天灵灵，水灵灵，火灵灵。天地水火他最灵，奉请仙翁请圣众。降我明堂贯我净，我净室水协我箕。急急如律令！\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,10)&&!who->get_legend(TASK_46,11) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    天之大幸，诛仙阵法已经恢复正常了，刀魂暂时不能随便乱跑了，你可向秦管家报告，困扰我平阳镇的危险已经解除了，那些乡亲们也可以回乡了。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));

		break;
        case 5:
        	if( who->get_legend(TASK_46,6)&&!who->get_legend(TASK_46,7) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/64186",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_46,7);
			who->add_exp(85000);
			who->add_potential(810);
			who->add_cash(98000);
			send_user(who,"%c%s",';',"刀魂传说3 经验 85000 潜能 810 金钱 98000 霸王战甲图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,66,"" );
			me->do_welcome(4);
        	}
        	break;        	
        case 6:
        	if ( who->get_legend(TASK_46,7)&&!who->get_legend(TASK_46,8) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_46,8);
        		who->delete_save("mxdaohun");
        		who->delete_save("mxqianhun");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,67,"刀魂传说4" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"刀魂传说4");
       		}
        	break;
        case 7:
        	if( who->get_legend(TASK_46,9)&&!who->get_legend(TASK_46,10) )
        	{
        		who->delete_save("mxdaohun");
        		who->delete_save("mxqianhun");
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_46,10);
			who->add_exp(89000);
			who->add_potential(1000);
			who->add_cash(96000);
			send_user(who,"%c%s",';',"刀魂传说4 经验 89000 潜能 1000 金钱 96000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,67,"" );
			me->do_welcome(4);
        	}
        	break;
        case 8:
        	if ( who->get_legend(TASK_46,10)&&!who->get_legend(TASK_46,11) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_46,11);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,68,"刀魂传说5" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"刀魂传说5");
       		}
        	break;
	case 9:
		if ( who->get_legend(TASK_47,8)&&!who->get_legend(TASK_47,9) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    既然是御史大人授命你前来，我必将我所知的都告于你。\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_47,9)&&!who->get_legend(TASK_47,10) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    经过我多日的观察，这些谣言都是平阳镇北的那个瘾君子在胡言乱语，你最好再细细质问他究竟是谁指使他的，小心这家伙一点都不老实，你一定要问出真话来，别被他蒙骗了到处咬人，不过宁可错杀一千，不可放过一个，如果他实在是一味乱咬，也没有办法，你自己掂量着吧。\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));

		break;
        case 10:
        	if( who->get_legend(TASK_47,8)&&!who->get_legend(TASK_47,9) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_47,9);
			who->add_exp(87000);
			who->add_potential(1100);
			who->add_cash(90000);
			send_user(who,"%c%s",';',"破除谣言1 经验 87000 潜能 1100 金钱 90000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,79,"" );
			me->do_welcome(9);
        	}
        	break;
        case 11:
        	if ( who->get_legend(TASK_47,9)&&!who->get_legend(TASK_47,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_47,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,80,"破除谣言2" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"破除谣言2");
       		}
        	break;
        case 21:
        case 22:
        	TASK_ESCORT_D->biaowang(me,who,flag);
        }
}