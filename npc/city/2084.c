
// 自动生成：/make/npc/make8084

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5505; }
void do_welcome( string arg );

int is_self_look() { return 1; }

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Hàn Quốc Bá Tánh");
	set_real_name("Tử Doanh (May Mặc 69~79)");
        set_city_name("Hàn Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",18);
//	set("legend",({32*4+17}));
 	set("mpLegend",([15:({32*4+17,32*4+23}),70:({32*22+27,}),75:({32*25+4,}),80:({32*26+22,}),60:({32*51+7})]));
	set("mpLegend2",([0:({32*26+4,}),15:({32*4+18,32*4+25}),70:({32*22+29,}),60:({32*51+9})]));
        set_2( "good", ([
                "01" : "/item/product/64116",
                "02" : "/item/product/64117",
                "03" : "/item/product/64118",
                "04" : "/item/product/64119",
                "05" : "/item/product/64120",
                "06" : "/item/product/64121",
                "07" : "/item/product/64122",
                "08" : "/item/product/64123",
                "09" : "/item/product/64124",
                "10" : "/item/product/64125",
                "11" : "/item/product/64126",        
                "12" : "/item/product/64127",
                "13" : "/item/product/64128",
                "14" : "/item/product/64129",
                "15" : "/item/product/64130",      
                "16" : "/item/product/64131",
                "17" : "/item/product/64132",
                "18" : "/item/product/64133",
                "19" : "/item/product/64134",
                "20" : "/item/product/64135",
                "21" : "/item/product/64136",        
                "22" : "/item/product/64137",
                "23" : "/item/product/64138",                                       
                "24" : "/item/product/64139",
        ]) ); 	
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 15 && !who->get_legend(TASK_04,17) ) || ( who->get_legend(TASK_04,17) && !who->get_legend(TASK_04,18) ) )
	{
		tmp = sprintf(ESC HIY "百姓的嘱托\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_level() >= 15 && !who->get_legend(TASK_04,23) ) || ( who->get_legend(TASK_04,23) && !who->get_legend(TASK_04,25) ) )
	{
		tmp += sprintf(ESC HIY "惩恶扬善\ntalk %x# welcome.5\n",getoid(me));
	}
	if ( ( who->get_level() >= 70 && !who->get_legend(TASK_22,27) ) || ( who->get_legend(TASK_22,27) && !who->get_legend(TASK_22,29) ) )
	{
		tmp += sprintf(ESC HIY "害人的水鬼\ntalk %x# welcome.8\n",getoid(me));
	}
	if ( who->get_level() >= 75 && !who->get_legend(TASK_25,4) )
	{
		tmp += sprintf(ESC HIY "索取宝图\ntalk %x# welcome.11\n",getoid(me));
	}
	if ( who->get_legend(TASK_26,3) && !who->get_legend(TASK_26,4) )
		tmp += sprintf(ESC HIY "御史的建议\ntalk %x# welcome.13\n",getoid(me));
	if ( who->get_legend(TASK_26,4) && !who->get_legend(TASK_26,5) )
		tmp += sprintf(ESC HIY "指明方向\ntalk %x# welcome.13\n",getoid(me));
	if ( who->get_level() >= 80 && !who->get_legend(TASK_26,22) )
		tmp += sprintf(ESC HIY "百姓的好心\ntalk %x# welcome.16\n",getoid(me));
	if ( (who->get_level() >= 60 && !who->get_legend(TASK_2_01,7)) || (who->get_legend(TASK_2_01,7) && !who->get_legend(TASK_2_01,9)))
		tmp += sprintf(ESC HIY "千里寻亲\ntalk %x# welcome.18\n",getoid(me));

	tmp += sprintf(ESC"购买道具\nlist %x#\n", getoid(me));
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) ,get_name()));
	
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
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,17)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我上次在去邻国探亲的路上不小心把翡翠珠串弄丢了，好象是在无定河的白虎坛一带丢失的。那串翡翠珠可是我的命根子，花了好多钱才买的，你要是能帮我找回来，我一定会重重的谢你。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_04,17) && !who->get_legend(TASK_04,18) )
			me->do_welcome(3);
        	break;
        case 2:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,17)  )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			TASK_LEGEND_D->remove_task_item(who, "翡翠珠串");                   	
        		who->set_legend(TASK_04,17);
			who->delete_save("feicuizucuan");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,8,"百姓的嘱托" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"百姓的嘱托");
        	}
        	break;
        case 3:
        	if ( !who->get_legend(TASK_04,17) || who->get_legend(TASK_04,18) )
        		return ;
        	if ( objectp(item=present("翡翠珠串",who,1,MAX_CARRY)) && item->is_legend_item() == 1 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太谢谢你了，你真是个好人，真不知该如何感谢你才好。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    算了，看来想找到那翡翠珠串的希望是没有了。\n"ESC"离开", me->get_name()));
        	break;
        case 4:
        	if ( who->get_legend(TASK_04,17) && !who->get_legend(TASK_04,18) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"翡翠珠串",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_04,18);
			who->delete_save("feicuizucuan");
			who->delete_save_2("feicuizucuan");
			who->add_exp(1600);
			who->add_potential(80);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"百姓的嘱托 经验 1600 潜能 80 金钱 1200");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,8,"" );
        	}
        	break;
        case 5:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大侠你终于出现了，世道不太平，百姓遭殃。最近有一个叫冯大龙的马贼，常常来勒索我的钱财。还扬言：要是我不给，就性命不保！我看你一身正气，定是侠义之士，%s你可否替我们百姓除掉这一大害？\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		else if ( who->get_legend(TASK_04,24) && !who->get_legend(TASK_04,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢%s你呀！这下我可有安静的日子过了。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        	else if ( who->get_legend(TASK_04,23) && !who->get_legend(TASK_04,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    算了，我还是定期给他一些钱财来求得安宁吧！\n"ESC"离开", me->get_name()));
        	break; 
        case 6:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_04,23);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,11,"惩恶扬善" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"惩恶扬善");
        	}
        	break;
        case 7:
        	if ( who->get_legend(TASK_04,24) && !who->get_legend(TASK_04,25) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/final/33/1702",3);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_04,25);
			who->add_exp(1800);
			who->add_potential(80);
			who->add_cash(1600);
			send_user(who,"%c%s",';',"惩恶扬善 经验 1800 潜能 80 金钱 1600 地瓜粥 3");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,11,"" );
        	}
        	break;
        case 8:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_22,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近传闻在弯道一带出现了水鬼，路过的人经常被拉到水下溺死，但其实那里的水鬼只是一帮装成鬼把人拉下水下溺死然后抢劫财物的败类贼寇，在弯道已经有不少路过的人被这样杀害了，你去想办法杀掉那里的10个这样的败类，为民除此一害吧！\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_22,27) && !who->get_legend(TASK_22,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果不尽快除掉这些败类，会有越来越多的人受害呀！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_22,28) && !who->get_legend(TASK_22,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    终于消灭了这群害人的败类了，那些被害的路人在天之灵也得到了安慰。\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 9:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_22,27) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_22,27);
        		who->delete_save_2("hgbxsuigui");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,43,"害人的水鬼" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"害人的水鬼");
        	}
        	break;  
        case 10:
        	if ( who->get_legend(TASK_22,28) && !who->get_legend(TASK_22,29) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_22,29);
        		who->delete_save_2("hgbxsuigui");
			who->add_exp(25000);
			who->add_potential(430);
			who->add_cash(23000);
			send_user(who,"%c%s",';',"害人的水鬼 经验 25000 潜能 430 金钱 23000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,43,"" );
        	}
        	break;
        case 11:
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_25,4)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    传闻灵谷洞有一个古老的秘密，在灵谷洞深处有一处神秘的宝藏，那宝藏至今未被人发现。但想要找到那宝藏必须先有一张灵谷洞宝图做引导，听说那宝图在韩国财政官手上，你去向他索要。\n"ESC"接受任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 12:
       		if ( who->get_level() >= 75 && !who->get_legend(TASK_25,4)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_25,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,16,"索取宝图" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"索取宝图");
        	}        	
        	break;   	    
	case 13:
        	if ( who->get_legend(TASK_26,3) && !who->get_legend(TASK_26,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你说的王真人我见过啊，那时候大家都说他是一个活神仙。但是这位活神仙早已经在十年前仙逝了。\n"ESC"完成任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_26,4) && !who->get_legend(TASK_26,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你先别急，虽然王真人已经仙逝了，但是他在仙逝之前收过一个徒弟。那个徒弟就是李方士，现在李方士就住在我们韩国西郊，你去找找他吧，虽然他的法力比王真人差很远，但是他也懂得许多风水法术，应该可以帮上你的一点忙。\n"ESC"接受任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));
  
		break;
	case 14:
        	if ( who->get_legend(TASK_26,3) && !who->get_legend(TASK_26,4) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_26,4);
			who->add_exp(37000);
			who->add_potential(540);
			who->add_cash(37000);
			send_user(who,"%c%s",';',"御史的建议 经验 37000 潜能 540 金钱 37000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,28,"" );
			me->do_welcome(13);
        	}
        	break;
	case 15:
        	if( who->get_legend(TASK_26,4) && !who->get_legend(TASK_26,5) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_26,5);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,29,"指明方向" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"指明方向");
        	}
        	break; 
	case 16:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_26,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听说住在郑城北郊的乐师他父亲最近好象被捉进监狱了，乐师现在好象很苦恼的样子，我跟乐师素有交情，你可以替我去慰问乐师一下吗？\n"ESC"接受任务\ntalk %x# welcome.17\n"ESC"离开", me->get_name(),getoid(me)));
  
		break;
	case 17:
        	if( who->get_level() >= 80 && !who->get_legend(TASK_26,22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_26,22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,36,"百姓的好心" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"百姓的好心");
        	}
        	break; 
        case 18:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_2_01,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这位英雄，我军中的兄长托人带信说，他被秦国俘虏充为苦役，在替秦王修陵，希望我能够帮助赎他回来，可那地方凶多吉少啊……呜呜呜，你能不能帮我去找找我兄长现在的下落啊。他身上有个玉佩为信物，如果他真的死了，也请带个信回来吧。\n"ESC"接受任务\ntalk %x# welcome.19\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_2_01,7) && !who->get_legend(TASK_2_01,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    英雄见到我兄长了吗？\n"ESC"离开", me->get_name(),));
		else if ( who->get_legend(TASK_2_01,8) && !who->get_legend(TASK_2_01,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呜呜呜，我可怜的兄长，你让我怎么给母亲说啊……这位英雄，还是谢谢你了。\n"ESC"完成任务\ntalk %x# welcome.20\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 19:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_2_01,7) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_2_01,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,101,"千里寻亲" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"千里寻亲");
		}
        	break;
        case 20:
        	if ( who->get_legend(TASK_2_01,8) && !who->get_legend(TASK_2_01,9) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"兄长的玉佩",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_2_01,9);
			who->add_exp(16800);
			who->add_potential(500);
			who->add_cash(9600);
			send_user(who,"%c%s",';',"千里寻亲 经验 16800 潜能 500 金钱 9600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,101,"" );
        	}
        	break;
        }
}