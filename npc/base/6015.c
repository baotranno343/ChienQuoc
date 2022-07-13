
// 自动生成：/make/npc/make0015

#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 1; }

// 有自己的do_look函数
int is_self_look() { return 1; }

void do_talk_exchange();

void do_info();
void do_exchange(string sArg);
void do_inputx(string sArg);
void do_welcome(string sArg);

// 函数：获取人物造型
int get_char_picid() { return 5415; }

// 函数：构造处理
void create()
{
        set_name("Chủ Tửu Lâu");
	set_real_name("Vu Lăng");

      	set_2( "talk", ([
                "info"  : (: do_info :),
                "do_exchange" : (: do_exchange :),
                "inputx"	: (: do_inputx :),   
                "exchange" : (: do_talk_exchange :),             	
                "welcome" : (: do_welcome :),             	
        ]));    
        set_2( "good", ([
                "01" : "/item/31/3150",
                "02" : "/item/31/3151",
                "03" : "/item/31/3152",
                "04" : "/item/32/3280",
                "05" : "/item/32/3281",
                "06" : "/item/32/3282",
                "07" : "/item/32/3283",
                "08" : "/item/32/3284",
                "09" : "/item/32/3285",
                "10" : "/item/stuff/0165",
		"11" : "/item/stuff/0166",
		"12" : "/item/stuff/0167",
		"13" : "/item/stuff/0168",                
		"14" : "/item/stuff/0213",
		"15" : "/item/stuff/0214",
		"16" : "/item/stuff/0219",
		"17" : "/item/stuff/0220",
		"18" : "/item/stuff/0221",
		"19" : "/item/stuff/0222",                
		"20" : "/item/stuff/0223",
		"21" : "/item/stuff/0224",	
		"22" : "/item/stuff/0159",	
		"23" : "/item/32/3204",
        ]) );
//	set("level",30);
//	set("legend",({32*7+25}));
 	set("mpLegend",([30:({32*7+25,32*9+1}),]));
 	set("mpLegend2",([30:({32*7+27,32*9+3}),]));
        setup();
}

void do_talk_exchange()
{
	TASK_COLLECT_D->do_talk_exchange( this_player(), this_object(), 6015 );
}

// 函数：对话处理
void do_look( object who )
{
	object item;
	object me = this_object(), map;
        int id = getoid(me);
	string tmp;
	"/quest/help"->send_help_tips(who, 53);
	tmp = "";
        tmp += sprintf(ESC"购买食物\nlist %x#\n", id);
//        tmp += sprintf(ESC"换取食物\ntalk %x# exchange\n",id);
        tmp += sprintf(ESC"坊间传闻\ntalk %x# info\n", id);
        if ( ( who->get_level() >= 30 && !who->get_legend(TASK_07,25) ) || ( who->get_legend(TASK_07,25) && !who->get_legend(TASK_07,27) ) )
		tmp += sprintf(ESC HIY "三片羽毛\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( ( who->get_legend(TASK_07,27) && !who->get_legend(TASK_07,28) ) || ( who->get_legend(TASK_07,28) && !who->get_legend(TASK_07,29) ) )
		tmp += sprintf(ESC HIY "唤醒记忆\ntalk %x# welcome.4\n",getoid(this_object())); 
        if ( ( who->get_level() >= 30 && !who->get_legend(TASK_09,1) ) || ( who->get_legend(TASK_09,1) && !who->get_legend(TASK_09,3) ) )
		tmp += sprintf(ESC HIY "大孤山脚里的哭声\ntalk %x# welcome.6\n",getoid(this_object())); 

        tmp += ESC"离开\nCLOSE\n";
        send_user(who,"%c%s",':',get_name()+": \n    "+"/quest/word"->get_normal_word(this_object())+"\n    客官，需要换点什么吗？\n"+ tmp);
}

// 函数：住宿处理
void do_info()
{
        object me, who;
        string result, info;
        me = this_object();  who = this_player();
        TASK_MASTER_D->do_info(me, who);             
}

void do_exchange(string sArg)
{
	TASK_COLLECT_D->do_exchange(sArg,6015);
}

void do_inputx(string sArg)
{
	object me,who;
	me = this_object(); who = this_player();
	TASK_COLLECT_D->do_inputx(me,who,sArg,6015);
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
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_07,25)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如今你的机缘已到，不知你是否愿意做这个有缘人，唤醒崔大官人的记忆呢？\n    崔大官人在三年前的一次失事中失去了记忆，可怜他的老婆孩子不幸丧命，他老婆临死之前交给他三片羽毛，他失去记忆后却弄丢了那三片羽毛，我想这可能是唯一能使他恢复记忆的方法了，你去收集这三片羽毛来我这吧，我再告诉你下一步怎么做！\n    羽毛在鄱阳湖的猪妖身上出现过。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_07,25) && !who->get_legend(TASK_07,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果不能找到那三片羽毛，崔大官人的记忆看来是恢复不了啦！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_07,26) && !who->get_legend(TASK_07,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    找到了这三片羽毛，就有希望恢复崔大官人的记忆了！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_07,25)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_07,25);
        		who->delete_save_2("spyumao");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,11,"三片羽毛" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"三片羽毛");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_07,26) && !who->get_legend(TASK_07,27) )
        	{
        	
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_07,27);
        		who->delete_save_2("spyumao");
			who->add_exp(1800);
			who->add_potential(30);
			who->add_cash(1500);
			send_user(who,"%c%s",';',"三片羽毛 经验 1800 潜能 30 金钱 1500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,11,"" );
			me->do_welcome(4);
        	}
        	break;
        case 4:
        	if ( who->get_legend(TASK_07,27) && !who->get_legend(TASK_07,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你已经找来了这三片羽毛，而这三片羽毛是唯一可能会使崔大官人恢复记忆的物品，因为这是他老婆临终时留下的。\n    崔大官人失去记忆后就一直居住在魏国的大梁城内，你将这三片羽毛交给他，试试能不能使他恢复记忆。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_07,28) && !who->get_legend(TASK_07,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你不去怎么知道这三片羽毛能不能唤醒崔大官人的记忆呢？\n"ESC"离开", me->get_name()));
        	break;
        case 5:
        	if ( who->get_legend(TASK_07,27) && !who->get_legend(TASK_07,28) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_07,28);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,12,"唤醒记忆" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"唤醒记忆");
        	}
        	break;
        case 6:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_09,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近常听见鄱阳湖的大孤山脚传来一阵阵的哭喊声，颤巍巍的，悲愤，却又忍辱负重，在山谷里飘荡，久久不能散去。\n    我不明白那是怎样的一种哭喊，也不知道确切的方位，但是我能体会到那种痛楚，撕心裂肺、肝肠寸断，被凌辱却不敢吭声，被压迫却不敢反抗，只有用那一声声的哭喊，洗脱、宣泄内心积攒的种种情绪。\n    我猜想，应该又是张大升在仗势欺负生活在鄱阳湖大孤山脚的老百姓，你过去看看吧。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_09,1) && !who->get_legend(TASK_09,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在不好好教训那恶霸，以后非出大乱不可。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_09,2) && !who->get_legend(TASK_09,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    教训的好，教训的好啊！是该惩治一下他，不然以后不知有多少人要遭殃。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 7:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_09,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_09,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,23,"大孤山脚里的哭声" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"大孤山脚里的哭声");
        	}
        	break;
        case 8:
        	if ( who->get_legend(TASK_09,2) && !who->get_legend(TASK_09,3) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),0,30,WAIST_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_09,3);
			who->add_exp(2700);
			who->add_potential(100);
			who->add_cash(2000);
			send_user(who,"%c%s",';',sprintf("大孤山脚里的哭声 经验 2700 潜能 100 金钱 2000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,23,"" );
        	}
        	break;   
        }

}
