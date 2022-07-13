
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 5505; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Bạch Dịch");
        set_city_name("Triệu Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));
//	set("level",58);
//	set("legend",({32*17+10}));	
 	set("mpLegend",([55:({32*17+10}),]));
 	set("mpLegend2",([0:({32*23+26}),55:({32*17+12}),]));
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
	if ( (who->get_level() >=55 && !who->get_legend(TASK_17,10)) || (who->get_legend(TASK_17,10) && !who->get_legend(TASK_17,12)) )
		tmp += sprintf(ESC HIY "烽火台上的烟雾\ntalk %x# welcome.1\n",getoid(me));
        if (who->get_legend(TASK_23,25)&&!who->get_legend(TASK_23,26)) 
		tmp += sprintf(ESC HIY "家书\ntalk %x# welcome.4\n",getoid(this_object())); 
        if (who->get_legend(TASK_23,26)&&!who->get_legend(TASK_23,27)) 
		tmp += sprintf(ESC HIY "送信\ntalk %x# welcome.4\n",getoid(this_object())); 
			
	send_user(who,"%c%s",':',sprintf( "%s：\n    周Quốc的京都镖局尉迟老镖头武艺高强，生性豪爽，真是一条好汉！\n", get_name(),  ) 
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
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_17,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这世上就是有这些无聊的人，没事儿瞎折腾，搞得人心惶惶。\n    你说那燕长城的匝道上空突然升起一团烟雾，这事不是有人搞鬼，难道还是鬼搞鬼啊！你快点去看看，我估计是那个叫李四的家伙弄的，天干物燥，要小心火烛啊！\n    见到他后记得要教训他一顿，免得他不长记性，又搞出这样的事情来！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_17,10) && !who->get_legend(TASK_17,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这种人真是太可恶了！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_17,11) && !who->get_legend(TASK_17,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看他以后还敢不敢乱来！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_17,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_17,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,23,"烽火台上的烟雾" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"烽火台上的烟雾");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_17,11) && !who->get_legend(TASK_17,12) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/61010",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_17,12);
			who->add_exp(6500);
			who->add_potential(240);
			who->add_cash(6600);
			send_user(who,"%c%s",';',"烽火台上的烟雾 经验 6500 潜能 240 金钱 6600 牛肉炒鸡蛋图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,23,"" );
        	}
		break;
        case 4:
	       	if ( who->get_legend(TASK_23,25) && !who->get_legend(TASK_23,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    其实所谓的不识字的人能看的懂的信，只是我画的画而已。因为我画的画取材自委托者的内心，所以我可以把人内心想说的话用图画表现出来。所以，人们都把我画替别人画的画叫做不识字的人也能看懂的信。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
	       	else if ( who->get_legend(TASK_23,26) && !who->get_legend(TASK_23,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    前一阵子我经过Ngụy Quốc的临河镇的时候我也曾经见过这位寻儿姑娘，听说她丈夫被捉到韩Quốc去已经十年都没有音信了，她却一直没有改嫁，一直在等候着她丈夫回来。帮助这样的一对痴情夫妻我自然是义不容辞。但是，我听说她这些日子一直受到一个叫赵讯的地主逼婚，现在寻儿姑娘甚至快要到了走投无路的地步。我想你在把这封信交给寻儿姑娘之前最好还是到无定河畔的小农社旁边把赵讯教训一下，然后再把信交到寻儿姑娘手上比较好一点。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));

        	break;   
        case 5:
        	if ( who->get_legend(TASK_23,25) && !who->get_legend(TASK_23,26) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_23,26);
			who->add_exp(17000);
			who->add_potential(260);
			who->add_cash(17000);
			send_user(who,"%c%s",';',"武士的爱情（2） 经验 17000 潜能 260 金钱 17000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,47,"" );
			me->do_welcome(4);
        	}
		break;
	case 6:
        	if ( who->get_legend(TASK_23,26) && !who->get_legend(TASK_23,27) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0109");
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			send_user(who,"%c%s",'!',"你携带的物品太多了");
        			return ;	
        		}
        		item->add_to_user(p);
        		who->set_legend(TASK_23,27);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,40,"武士的爱情（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"武士的爱情（3）");
        	}
        	break;  
        }
}