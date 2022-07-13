
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 5405; }

// 有自己的do_look函数
int is_self_look() { return 1; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Trang Phục");
	set_real_name("Trí Tẩu");
        set_city_name("Hàn Quốc");

        set_2( "good", ([
                "01" : "/item/60/4020",
                "02" : "/item/60/4030",
                "03" : "/item/60/4040",
                "04" : "/item/60/4050",
                "05" : "/item/60/4060",
                "06" : "/item/61/4020",
                "07" : "/item/61/4030",
                "08" : "/item/61/4040",
                "09" : "/item/65/4020",
                "10" : "/item/65/4030",
                "11" : "/item/65/4040",
                "12" : "/item/66/4020",
                "13" : "/item/66/4030",
                "14" : "/item/66/4040",

        ]) );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",18);
//	set("legend",({32*4+15}));
 	set("mpLegend",([15:({32*4+15}),]));
 	set("mpLegend2",([15:({32*4+16}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	result = sprintf("%s：\n    "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	result += sprintf(ESC "哪里有适合我的装备？\ntalk %x# welcome.99\n", getoid(me) ) ;        	
	if ( ( who->get_level() >= 15 && !who->get_legend(TASK_04,15) ) || ( who->get_legend(TASK_04,15) && !who->get_legend(TASK_04,16) ) )
	{
		result += sprintf(ESC HIY "神奇的彩衣\ntalk %x# welcome.1\n",getoid(me));
	}
	result += sprintf( ESC "交易\nlist %x#\n" ESC "我只是随便看看\nCLOSE\n", getoid(me) ) ;        	
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(), result );
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
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,15)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我听说在无定河的将军冢曾经出现过一件神奇的彩衣。要是我的店能有这样一件衣服那该多好啊！你能帮我寻回来吗？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_04,15) && !who->get_legend(TASK_04,16) )
			me->do_welcome(3);
        	break;
        case 2:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,15)  )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			TASK_LEGEND_D->remove_task_item(who, "彩衣");                   	
        		who->set_legend(TASK_04,15);
			who->delete_save("sqcaiyi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,7,"神奇的彩衣" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"神奇的彩衣");
        	}
        	break;
        case 3:
        	if ( !who->get_legend(TASK_04,15) || who->get_legend(TASK_04,16) )
        		return ;
        	if ( objectp(item=present("彩衣",who,1,MAX_CARRY)) && item->is_legend_item() == 1 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太感谢你了！有了这件衣服，我店的招牌一定很多人知道。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没找到吗？可能只是个传说吧！麻烦你了，%s\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who)));
        	break;
        case 4:
        	if ( who->get_legend(TASK_04,15) && !who->get_legend(TASK_04,16) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"彩衣",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_04,16);
			who->delete_save("sqcaiyi");
			who->delete_save_2("shenqicaiyi");
			who->add_exp(1500);
			who->add_potential(80);
			who->add_cash(1300);
			send_user(who,"%c%s",';',"神奇的彩衣 经验 1500 潜能 80 金钱 1300");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,7,"" );
        	}
        	break;
        case 99:	
		"/npc/base/0005"->do_welcome2(me, "99");
        	break;
        }
}