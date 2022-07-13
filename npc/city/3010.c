
// 自动生成：/make/npc/make8010

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0600; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Triệu Quốc Thủ Vệ");
        set_city_name("Triệu Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",54);
//        set("legend",({32*15+27}));
	set("mpLegend",([50:({32*15+27}),55:({32*38+5}),60:({32*18+10,}),80:({32*27+28})]));
	set("mpLegend2",([50:({32*15+29}),60:({32*18+12,}),80:({32*27+30})]));
        setup();
}

string get_master() { return CITY_ZHAO->get_master(); }
string get_master_2() { return CITY_ZHAO->get_master_2(); }
string get_master_3() { return CITY_ZHAO->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( (who->get_level() >= 50 && !who->get_legend(TASK_15,27)) || (who->get_legend(TASK_15,27)&&!who->get_legend(TASK_15,29)) )
	{
		tmp = sprintf(ESC HIY "除恶惩凶\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_level() >=60 && !who->get_legend(TASK_18,10)) || (who->get_legend(TASK_18,10) && !who->get_legend(TASK_18,12)) )
		tmp += sprintf(ESC HIY "守卫的遗憾\ntalk %x# welcome.4\n",getoid(me));
	if ( (who->get_level() >= 80 && !who->get_legend(TASK_27,28)) || (who->get_legend(TASK_27,28) && !who->get_legend(TASK_27,30)))
	{
		tmp += sprintf(ESC HIY "鹿角\ntalk %x# welcome.7\n",getoid(me));
	}
	if ( who->get_level() >= 55 && !who->get_legend(TASK_38,5) )
		tmp += sprintf(ESC HIY "打造武器\ntalk %x# welcome.10\n",getoid(me));

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GUARDER_D->do_look_3( who, me ); 
	
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
        	if ( who->get_level() >=50 && !who->get_legend(TASK_15,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    赵长城的弓兵可是帮恶人，他们目无王法，倚仗自己箭术很好，到处乱伤无辜，不知有多少人或伤或死在他们的箭下，将军曾派了不少人去歼灭他们，可都无功而退，我现在希望你能帮这个忙，去赵长城消灭赵国弓兵，记得千万要小心行事，他们的箭术不容小窥。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_15,27) && !who->get_legend(TASK_15,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果你一人不能消灭他们，可以找人帮忙。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_15,28) && !who->get_legend(TASK_15,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    集合大家的力量，我想这帮狂妄之徒以后都不会这么嚣张了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if( who->get_level() >=50 && !who->get_legend(TASK_15,27) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_15,27);
        		who->delete_save_2("zggongbing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,6,"除恶惩凶" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"除恶惩凶");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_15,28) && !who->get_legend(TASK_15,29) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/65053",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_15,29);
        		who->delete_save_2("zggongbing");
			who->add_exp(6350);
			who->add_potential(260);
			who->add_cash(5500);
			send_user(who,"%c%s",';',"除恶惩凶 经验 6350 潜能 260 金钱 5500 炎阳项链图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,6,"" );
        	}
        	break;  
        case 4:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_18,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    上次我率小队奔袭敌人后路，在燕长城匝道上全歼敌军，但是那时候竟然没有找到敌军首领的领军符，这样子就不能证明我的功勋来论功行赏了，你愿意帮我找到它吗？\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_18,10) && !who->get_legend(TASK_18,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，好不容易立了功却不能封赏，气死我也！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_18,11) && !who->get_legend(TASK_18,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下我可以升官发财啦！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 5:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_18,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_18,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,33,"守卫的遗憾" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"守卫的遗憾");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_18,11) && !who->get_legend(TASK_18,12) )
        	{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),0,60,NECK_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
        		if (TASK_LEGEND_D->check_task_item(who,"领兵符",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_18,12);
			who->add_exp(7000);
			who->add_potential(270);
			who->add_cash(6300);
			send_user(who,"%c%s",';',sprintf("守卫的遗憾 经验 7000 潜能 270 金钱 6300 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,33,"" );
        	}
        	break;  
        case 7:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_27,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我表哥说万人坑里那些人不少曾经是贩卖鹿角的商贾，他们至死都不肯放弃自己的货物，结果白白便宜了我们，去那里随便拣都能拣到不少上好的鹿角，可以卖不少钱呢，当然了，鹿角只中意有勇气的勇士，所以请你帮我找来吧，至于佣金是绝对会让你满意的，要知道，敢收这种地方鹿角的人可就我，因为只有我才知道怎么样除去鹿角上的秽气。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_27,28) && !who->get_legend(TASK_27,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    叫你找的鹿角呢？我可是准备了丰厚的报酬给你哦。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_27,29) && !who->get_legend(TASK_27,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，拿到这些鹿角，我这辈子都衣食无忧了！\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 8:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_27,28) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_27,28);
        		who->delete_save("zgswlujiao");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,44,"鹿角" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"鹿角");
        	}
        	break;
        case 9:
        	if ( who->get_legend(TASK_27,29) && !who->get_legend(TASK_27,30) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"鹿角",20) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/final/15/1520",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_27,30);
        		who->delete_save("zgswlujiao");
			who->add_exp(48000);
			who->add_potential(680);
			who->add_cash(46000);
			send_user(who,"%c%s",';',"鹿角 经验 48000 潜能 680 金钱 46000 强效法力 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,44,"" );
        	}
        	break;
        case 10:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_38,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听说秦国有一个会打造武器的工匠，他打造出来的武器一般的商铺都买不到，据说最近他收了不少弟子，而跟随他学习打造武器的徒弟们也对他的技艺赞不绝口，说实话，我还真有点动心，只是我不知道他具体住在哪，你去秦国给我找找他，看他能不能收下我这个徒弟。\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 11:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_38,5) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_38,5);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,64,"打造武器" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"打造武器");
        	}
		break;
        case 99:
        	GUARDER_D->do_look_3( who, me ); 
        	break;     
        }
}