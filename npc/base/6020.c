
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller_2() { return 1; }

int is_self_look() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 5402; }
void do_welcome( string arg );

void reset() ;

// 函数：构造处理
void create()
{
        set_name("Lưu Lãng Thương Nhân");
	set_real_name("Lỗ Trọng Liên");
        set_city_name("Sở Quốc");

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
                "welcome"          : (: do_welcome :),
        ]));
//	set("level",10);
//	set("legend",({32*37+15,}));
	set("mpLegend",([5:({32*37+15}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	result = sprintf("%s：\n    "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );

	if ( who->get_level() >= 5 && !who->get_legend(TASK_37,15) )
		result += sprintf(ESC HIY "收购珠宝\ntalk %x# welcome.1\n",getoid(me));

	result = result + sprintf( ESC "交易\nlist %x#\n" ESC "我只是随便看看\nCLOSE\n", getoid(me) ) ;        	
	send_user( who, "%c%s", ':', result );

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
        	if ( who->get_level() >= 5 && !who->get_legend(TASK_37,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我们经商的，听到哪有商机就往哪条路上走，这是必然的。\n    现在我做珠宝生意，自然是到处搜集珠宝，打听到谁家有收藏的珍贵宝石，那我可是一定会想方设法的弄到手，我听说城外的王满家有块家传宝玉，你去替我问问，他是否愿意出售，如果愿意的话，你将他开的价格报给我吧。\n    王满就在城外的百越村，他旁边还有户人家叫孙陆的，你也可以给我顺便问问孙陆有没有什么珠宝要出售。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 2:
        	if ( who->get_level() >= 5 && !who->get_legend(TASK_37,15) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_37,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,42,"收购珠宝" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"收购珠宝");
        	}
        	break;
	}
}