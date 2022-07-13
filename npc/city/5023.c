
// 自动生成：/make/npc/make8020

#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0450; }
void do_welcome(string arg);

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
        set_name("Tần Quốc Công Tượng");
        set_real_name("Rèn Đúc 61~80");
        set_city_name("Tần Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",67);
//	set("legend",({32*21+3}));
	set("mpLegend",([65:({32*21+3}),105:({32*39+3,}),110:({32*43+23})]));
	set("mpLegend2",([65:({32*21+7,32*21+12,}),110:({32*43+25})]));
	set_skill(0620, 39);
        set_2( "good", ([
                "01" : "/item/product/62050",
                "02" : "/item/product/62051",
                "03" : "/item/product/62052",
                "04" : "/item/product/62053",
                "05" : "/item/product/62054",
                "06" : "/item/product/62055",
                "07" : "/item/product/62056",
                "08" : "/item/product/62057",
                "09" : "/item/product/62058",
                "10" : "/item/product/62059",
                "11" : "/item/product/62060",
                "12" : "/item/product/62061",
                "13" : "/item/product/62062",
                "14" : "/item/product/62063",
                "15" : "/item/product/62064",
                "16" : "/item/product/62065",
                "17" : "/item/product/62066",
                "18" : "/item/product/62067",
                "19" : "/item/product/62068",
                "20" : "/item/product/62069",
                "21" : "/item/product/62070",
                "22" : "/item/product/62071",
        ]) );	
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( who->get_level() >= 65 && !who->get_legend(TASK_21,3) )
	{
		tmp = sprintf(ESC HIY "打听消息\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_21,4) && !who->get_legend(TASK_21,5)) || (who->get_legend(TASK_21,5) && !who->get_legend(TASK_21,7)) )
	{
		tmp += sprintf(ESC HIY "修造之难\ntalk %x# welcome.1\n",getoid(me));
	}
	if (who->get_legend(TASK_21,7) && !who->get_legend(TASK_21,8))
	{
		tmp += sprintf(ESC HIY "降旨修墓\ntalk %x# welcome.1\n",getoid(me));
	}	
	if ( (who->get_legend(TASK_21,9) && !who->get_legend(TASK_21,10)) || (who->get_legend(TASK_21,10) && !who->get_legend(TASK_21,12)) )
	{
		tmp += sprintf(ESC HIY "铲除恶霸\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_21,12) && !who->get_legend(TASK_21,13) )
	{
		tmp += sprintf(ESC HIY "寻求支持\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_level() >= 105 && !who->get_legend(TASK_39,3) )
		tmp += sprintf(ESC HIY "嘱托之事\ntalk %x# welcome.9\n",getoid(me));
	if ( ( who->get_level() >=110 && !who->get_legend(TASK_43,23) ) || ( who->get_legend(TASK_43,23) && !who->get_legend(TASK_43,25) ) )
		tmp += sprintf(ESC HIY "黎明前的黑暗\ntalk %x# welcome.11\n",getoid(me));

	tmp += sprintf(ESC"Học kĩ năng\nlearn ? %s\n", me->get_char_id());
	tmp += sprintf(ESC"Mua công thức Rèn đúc cấp 61 - 80\nlist %s\n", me->get_char_id());
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) ,get_name()));
	
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 8 ); }

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,i,size,p,amount;
        object who,item, *inv;     
       	string *nTmp,tmp;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 65 && !who->get_legend(TASK_21,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听闻最近大王对于机关术非常感兴趣，打算尽起国内巧匠将建一座集聚天下机关术大成的地宫，但是同时也严格晓谕不得劳民伤财动摇国之根本。听到此我技痒难忍，但不知道具体行程如何，你可向秦国内政官甘罗打听一下吗？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if (who->get_legend(TASK_21,4) && !who->get_legend(TASK_21,5))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    据说那郦山所处乱石之地，想要在那开山建造工事，没有开山锄是很麻烦的。据说这次大王分发了许多开山锄，都放在秦长城的烽火台让我们自己去领取，你是否愿意帮我领来开山锄呢？\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_21,5) && !who->get_legend(TASK_21,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没有开山锄，在那乱石之地开山建造工事非常麻烦。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_21,6) && !who->get_legend(TASK_21,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下解决了修造郦山工事的大麻烦。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if (who->get_legend(TASK_21,7) && !who->get_legend(TASK_21,8))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我所领工匠已经准备完毕，你可将这封建造信函转交秦王赢政，降旨修建地宫。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if (who->get_legend(TASK_21,9) && !who->get_legend(TASK_21,10))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王既已下令开始修造，小民即日开始动工。只是修造所用石料被恶霸张九垄断，一味抬高物价，这本是大王之事，他违抗王命，理应伏法，你能前去秦长城烽火台将他除去吗？\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_21,10) && !who->get_legend(TASK_21,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    恶霸不除，石料如何取得？难道真要纵容他任意哄抬物价吗？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_21,11) && !who->get_legend(TASK_21,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可好了，为修造之路又除掉一大障碍。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_21,12) && !who->get_legend(TASK_21,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    郦山地宫之事万事具备，只欠内政批文了，你将消息禀告秦国内政官，希望他能够尽快批文下来。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
	case 2:
        	if ( who->get_level() >= 65 && !who->get_legend(TASK_21,3) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_21,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,28,"打听消息" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"打听消息");
        	}
        	break;
	case 3:
        	if (who->get_legend(TASK_21,4) && !who->get_legend(TASK_21,5))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_21,5);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,29,"修造之难" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"修造之难");
        	}
        	break;
        case 4:
        	if ( who->get_legend(TASK_21,6) && !who->get_legend(TASK_21,7) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"开山锄",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,7);
			who->add_exp(14000);
			who->add_potential(360);
			who->add_cash(13000);
			send_user(who,"%c%s",';',"修造之难 经验 14000 潜能 360 金钱 13000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,29,"" );
			me->do_welcome(1);
        	}
        	break; 
	case 5:
        	if ( who->get_legend(TASK_21,7) && !who->get_legend(TASK_21,8) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0097");
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			send_user(who,"%c%s",'!',"你携带的物品太多");	
        			return ;
        		}
        		item->add_to_user(p);
        		who->set_legend(TASK_21,8);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,30,"降旨修墓" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"降旨修墓");
        	}
        	break; 
	case 6:
        	if (who->get_legend(TASK_21,9) && !who->get_legend(TASK_21,10))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_21,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,31,"铲除恶霸" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"铲除恶霸");
        	}
        	break;
        case 7:
        	if ( who->get_legend(TASK_21,11) && !who->get_legend(TASK_21,12) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/62050",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,12);
			who->add_exp(15500);
			who->add_potential(370);
			who->add_cash(15000);
			send_user(who,"%c%s",';',"铲除恶霸 经验 15500 潜能 370 金钱 15000 日月剑图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,31,"" );
			me->do_welcome(1);
        	}
        	break; 
	case 8:
        	if (who->get_legend(TASK_21,12) && !who->get_legend(TASK_21,13))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_21,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,32,"寻求支持" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"寻求支持");
        	}
        	break;
        case 9:
		if ( who->get_level() >= 105 && !who->get_legend(TASK_39,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    之前赵国大将军嘱咐过我一件事情，当然，这是秘密，不能告诉你。\n    现在，这件事情我已替他办妥，因为是机密，所以我不能自己将这个消息告诉他，你只需替我找到赵国大将军，然后告诉他，工匠之事已办好就行了，我想他会重重赏赐你的。\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 10:
        	if ( who->get_level() >= 105 && !who->get_legend(TASK_39,3) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_39,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,94,"嘱托之事" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"嘱托之事");
        	}
        	break; 
	case 11:
        	if ( who->get_level() >=110 && !who->get_legend(TASK_43,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在我军忙于备战，无暇他顾，以前潜伏的妖孽恶道纷纷猖獗起来，频频滋扰我关中辎重，使得我们辛辛苦苦作出来的武器装备要么不翼而飞，要么被破坏得支离破碎，看的我们心在滴血啊！大王整日都为一堆奏折搞得不堪其繁，甚至动用了禁卫军，但狡猾的妖孽恶道一闻军队调动，那帮子就龟缩起来，听闻大侠武功盖世，急公好义，不知能否为我等打击一下他们的嚣张气焰，杀掉虚陵洞的土精5只，九曲桥的龟仙人6只，天门阵的天罡门众守8个？在此代表我国匠人先谢过了。等到天下平定之后，这帮子妖孽恶道的日子就到头了。\n"ESC"接受任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_43,23) && !who->get_legend(TASK_43,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，为何那些妖孽恶道还是如此猖獗呢，难道大侠你也畏惧他们吗？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_43,24) && !who->get_legend(TASK_43,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，这下子他们受了这么重的打击，一下子龟缩起来，我们太平好多，真亏了大侠你神功无敌保了我们的心血啊，小小意思不成敬意。\n"ESC"完成任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 12:
        	if ( who->get_level() >=110 && !who->get_legend(TASK_43,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_43,23);
        		who->delete_save("qggjtuj");
        		who->delete_save("qggjguixr");
        		who->delete_save("qggjtiangmzs");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,60,"黎明前的黑暗" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"黎明前的黑暗");
        	}
        	break;
        case 13:
        	if ( who->get_legend(TASK_43,24) && !who->get_legend(TASK_43,25) )
        	{
			if ( !sizeof(who->get_fam_name()) )
			{
				send_user(who,"%c%s",'!',"无门无派可交不了任务哦～");
				return;	
			}
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),0,110,WEAPON_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_43,25);
        		who->delete_save("qggjtuj");
        		who->delete_save("qggjguixr");
        		who->delete_save("qggjtiangmzs");
			who->add_exp(98000);
			who->add_potential(1120);
			who->add_cash(95000);
			send_user(who,"%c%s",';',sprintf("黎明前的黑暗 经验 98000 潜能 1120 金钱 95000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,60,"" );
        		
        	}
        	break;
        }
}