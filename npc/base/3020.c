
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller_2() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 5402; }

void reset() ;

int is_self_look() { return 1; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Lưu Lãng Thương Nhân");
	set_real_name("Huyền Cao");
        set_city_name("Triệu Quốc");

	set_2( "good", ([
	                "01" : "/sys/item/product"->get_random_diamond(),
	                "02" : "/sys/item/product"->get_random_diamond(),
	                "03" : "/sys/item/product"->get_random_diamond(),
	                "04" : "/sys/item/product"->get_random_diamond(),
	        ]) );
	set_2( "list", ([
	                "01" : 1+random(2),
	                "02" : 1+random(2),
			"03" : 1+random(2),
			"04" : 1+random(2),
	        ]) );	
	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));
//	set("level",60);
//	set("legend",({32*18+7}) );
 	set("mpLegend",([60:({32*18+7}),]));
 	set("mpLegend2",([60:({32*18+9}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	result = sprintf("%s：\n    "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );

	if ( (who->get_level() >=60 && !who->get_legend(TASK_18,7)) || (who->get_legend(TASK_18,7) && !who->get_legend(TASK_18,9)) )
		result += sprintf(ESC HIY "流浪奇遇\ntalk %x# welcome.1\n",getoid(me));

	result = result + sprintf( ESC "交易\nlist %x#\n" ESC "我只是随便看看\nCLOSE\n", getoid(me) ) ;        	
	send_user( who, "%c%s", ':', result );

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
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_18,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    走南访北，遇见不少的奇人奇事，最让我惊讶的是关于一颗玉兰石的传说，不知道这石头有什么功效，居然让人花费那么大的代价去抢夺它，想发财？赶快去燕长城找找那颗玉兰石吧，传说只有有缘人才能找到它！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_18,7) && !who->get_legend(TASK_18,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道是我眼睛看花了吗？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_18,8) && !who->get_legend(TASK_18,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈……有了这个东西我再也不用去流浪了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_18,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_18,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,32,"流浪奇遇" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"流浪奇遇");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_18,8) && !who->get_legend(TASK_18,9) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"玉兰石",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		TASK_LEGEND_D->give_item(who,"item/product/66028",1);
			who->set_legend(TASK_18,9);
			who->add_exp(7000);
			who->add_potential(260);
			who->add_cash(6500);
			send_user(who,"%c%s",';',"流浪奇遇 经验 7000 潜能 260 金钱 6500 高爆炸弹图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,32,"" );
        	}
        	break;  
        }
}

// 函数：复位处理
void reset() 
{
	object me = this_object();
	int count;
	count = me->add("count", 1);
	if (count % 3==0)
	{
	        me->set_2( "good", ([
	                "01" : "/sys/item/product"->get_random_diamond(),
	                "02" : "/sys/item/product"->get_random_diamond(),
	                "03" : "/sys/item/product"->get_random_diamond(),
	                "04" : "/sys/item/product"->get_random_diamond(),
	        ]) );
	
	        me->set_2( "list", ([
	                "01" : 1+random(2),
	                "02" : 1+random(2),
			"03" : 1+random(2),
			"04" : 1+random(2),
	        ]) );		
	}	
}