
// 自动生成：/make/npc/make8020

#include <npc.h>
#include <ansi.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0452; }
void do_welcome( string arg );

// 函数：师父识别
int is_master() { return 1; }

// 函数：师父识别(武教头)
int is_basic_master() { return 2; }

int is_self_look() { return 1; }

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Ngụy Quốc Công Tượng");
        set_real_name("Luyện Đơn 1~20");
        set_city_name("Ngụy Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",21);
//	set("legend",({32*5+7}));
 	set("mpLegend",([20:({32*5+7}),95:({32*34+9})]));
 	set("mpLegend2",([20:({32*5+9,}),]));
	set_skill(0630, 39);
        set_2( "good", ([
                "01" : "/item/product/63001",
                "02" : "/item/product/63002",
                "03" : "/item/product/63003",
                "04" : "/item/product/63004",
                "05" : "/item/product/63005",
                "06" : "/item/product/63006",
        ]) );	
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	int id;
	string tmp="";
	object me = this_object();
	id = getoid(me);
	if ( ( who->get_level() >= 20 && !who->get_legend(TASK_05,7) ) || ( who->get_legend(TASK_05,7) && !who->get_legend(TASK_05,9) ) )
	{
		tmp = sprintf(ESC HIY "招摇撞骗\ntalk %x# welcome.1\n",id);
	}
	if ( who->get_level() >= 95 && !who->get_legend(TASK_34,9) )
	{
		tmp += sprintf(ESC HIY "了解情况\ntalk %x# welcome.4\n",id);
	}
	tmp += sprintf(ESC"学习生活技能\nlearn ? %s\n", me->get_char_id());
	tmp += sprintf(ESC"购买Luyện Đơn 技能等级1-20级的配方\nlist %s\n", me->get_char_id());
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) ,get_name()));
	
}
int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 1 ); }
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
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,7)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    别看我其貌不扬，可因为我的手艺好，很多人还是愿意请我做工的，可就我这点手艺还让人惦记上了。\n    那呆在巨鹿平丘的无赖马大龙，居然经常冒充我的名号到处骗人，最起初还只是冒充我去给人做工，现在居然发展到拿了定金就走人，影响了我的名誉与生意，你能给我除掉他吗？\n    他知道我很生气，所以现在躲在了巨鹿的平丘，如果你从赵国去，到了巨鹿向右走就可以看到他了，他就躲在那颗巨大的仙人掌旁边。从太行山方向的话，过了桥一直往前走就能找到。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_05,7) && !who->get_legend(TASK_05,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我得去报官才能把这无耻之徒绳之于法。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_05,8) && !who->get_legend(TASK_05,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这无耻之徒终于被除去了，算是为我母亲报了仇，也替自己出了一口气。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,7)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_05,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,13,"招摇撞骗" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"招摇撞骗");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_05,8) && !who->get_legend(TASK_05,9) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64004",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_05,9);
			who->add_exp(1000);
			who->add_potential(70);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"招摇撞骗 经验 1000 潜能 70 金钱 1200 沙场甲图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,13,"" );
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_34,9)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这段时间看到魏老汉徘徊城西河边，经常乱蹦乱跳，还在自己身上乱抹一些千奇百怪的东西，口中还常常念念有词，喊什么千秋万载，道仙保佑之类的话。我作为他的老友甚为担忧，但是他却每次抓住我就是翻来覆去那几句话，只得请你前去帮助他了。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 5:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_34,9)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_34,9);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,42,"了解情况" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"了解情况");
        	}
        	break;
        }
}