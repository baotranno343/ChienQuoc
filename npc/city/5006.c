
// 自动生成：/make/npc/make8006

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>

#define INQUISITOR_D    "/inh/city/inquisitor"

inherit OFFICER;

void do_elect( string arg );
void do_vote( string arg );
void do_score( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tần Quốc Ngự Sử");
	set_real_name("Lí Tư");
        set_city_name("Tần Quốc");

        set_2( "talk", ([
                "elect"         : (: do_elect :),
                "vote"          : (: do_vote :),
                "score"         : (: do_score :),
                "welcome"	: (: do_welcome :),
        ]) );
 	set("mpLegend",([115:({32*46+13,32*47+8,32*47+19}),]));
 	set("mpLegend2",([0:({32*22+2,32*22+20,}),115:({32*46+25,32*47+18,}),]));
        setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_legend(TASK_22,1) && !who->get_legend(TASK_22,2) )
	{
		tmp += sprintf(ESC HIY "陈述冤情\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_22,2) && !who->get_legend(TASK_22,3) )
	{
		tmp += sprintf(ESC HIY "明辨是非\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_22,19) && !who->get_legend(TASK_22,20) )
		tmp += sprintf(ESC HIY "上书之难\ntalk %x# welcome.4\n",getoid(this_object()));
	if ( who->get_level() >=115 && !who->get_legend(TASK_46,13) )
		tmp += sprintf(ESC HIY "探听消息\ntalk %x# welcome.6\n",getoid(me));
         if ( who->get_legend(TASK_46,24)&&!who->get_legend(TASK_46,25) ) 
		tmp += sprintf(ESC HIY "转交信函\ntalk %x# welcome.6\n",getoid(me)); 
	if ( who->get_level() >=115 && !who->get_legend(TASK_47,8) )
		tmp += sprintf(ESC HIY "探明谣传\ntalk %x# welcome.9\n",getoid(me));
         if ( who->get_legend(TASK_47,17)&&!who->get_legend(TASK_47,18) ) 
		tmp += sprintf(ESC HIY "破除谣言\ntalk %x# welcome.9\n",getoid(me)); 
	if ( who->get_level() >=115 && !who->get_legend(TASK_47,19) )
		tmp += sprintf(ESC HIY "拜访秦将\ntalk %x# welcome.12\n",getoid(me));
 
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		INQUISITOR_D->do_look( who, this_object() ); 
	
}
void do_elect( string arg ) { INQUISITOR_D->do_elect( this_player(), this_object(), arg ); }
void do_vote( string arg ) { INQUISITOR_D->do_vote( this_player(), this_object(), arg ); }
void do_score( string arg ) { INQUISITOR_D->do_score( this_player(), this_object(), arg ); }

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
		if ( who->get_legend(TASK_22,1) && !who->get_legend(TASK_22,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    原来大将军是被奸贼诽谤中伤，我一定要向大王奏明此事，\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_22,2) && !who->get_legend(TASK_22,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我这有一封奏书，里面将大将军蒙冤受屈的事情陈述的清清楚楚，你将这封奏书交给大王，大王看完后定会还大将军一个公道。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_legend(TASK_22,1) && !who->get_legend(TASK_22,2) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"信函",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_22,2);
			who->add_exp(21000);
			who->add_potential(410);
			who->add_cash(22000);
			send_user(who,"%c%s",';',"陈述冤情 经验 21000 潜能 410 金钱 22000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,40,"" );
			me->do_welcome(1);
        	}
        	break; 
	case 3:
        	if ( who->get_legend(TASK_22,2) && !who->get_legend(TASK_22,3) )
        	{
 			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
 			item = new("/item/98/0102");
 			p = item->move(who,-1);
 			if ( !p )
 			{
 				destruct(item);
 				send_user(who,"%c%s", '!', "你携带的物品太多了");	
 				return ;
 			}
 			item->add_to_user(p);
        		who->set_legend(TASK_22,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,41,"明辨是非" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"明辨是非");
        	}
        	break;
	case 4:
		if ( who->get_legend(TASK_22,19) && !who->get_legend(TASK_22,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这件事的性质很恶劣，竟然有人敢恐吓朝廷命官。本官一定会禀告大王，对这类猖狂之徒严加惩治。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 5:
        	if ( who->get_legend(TASK_22,19) && !who->get_legend(TASK_22,20) )
        	{
         		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),70,ARMOR_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_22,20);
			who->add_exp(25500);
			who->add_potential(430);
			who->add_cash(24000);
			send_user(who,"%c%s",';',sprintf("上书之难 经验 25500 潜能 430 金钱 24000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,47,"" );
        	}
        	break;
        case 6:
        	if ( who->get_level() >=115 && !who->get_legend(TASK_46,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如今真是个多事之秋啊，一天到晚案上的竹简已经弄得我焦头烂额，你能帮帮我分忧么？这里好多个平阳里正上报的凶杀或者伤人案件，都语焉不详，相关知情人都咸口不语，自从上次平阳刀魂捣乱之后已经太平了一阵了，不料最近居然又动荡起来，你去调查一下，听说秦医师比较清楚内情，你去问问他。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,24)&&!who->get_legend(TASK_46,25) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唔，此恶匪展五真该遭天谴，幸亏义士将其铲除，维护了一方安宁。（低声自语）金龙珠……莫非有什么秘密？\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 7:
        	if ( who->get_level() >=115 && !who->get_legend(TASK_46,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_46,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,69,"平阳之乱1" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"平阳之乱1");
       		}
        	break;
        case 8:
        	if( who->get_legend(TASK_46,24)&&!who->get_legend(TASK_46,25) )
        	{
			if (TASK_LEGEND_D->check_task_item(who,"平阳信函",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64183",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_46,25);
			who->add_exp(94000);
			who->add_potential(950);
			who->add_cash(92000);
			send_user(who,"%c%s",';',"平阳之乱5 经验 94000 潜能 950 金钱 92000 凤羽靴图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,73,"" );
        	}
        	break;
        case 9:
        	if ( who->get_level() >=115 && !who->get_legend(TASK_47,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太无法无天了，最近城外居然有人谣传王妃乃是雀妖所变，专门来迷惑大王的，王妃乃授命于天，母仪天下的，居然有人敢藐视王权，肆意造谣，置我王家尊严于何地！本官命你速速去彻查此事，平阳镇的马显一向克尽职守，效忠朝廷，你可先向他询问一下来龙去脉。\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_47,17)&&!who->get_legend(TASK_47,18) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哼，大胆刁民，藐视王家尊严，居然好意思来认罪，要不是刚刚大王下令不要追究了，我真想砍了这老儿的头，九族连坐！好了，没事了，你走吧！\n"ESC"完成任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 10:
        	if ( who->get_level() >=115 && !who->get_legend(TASK_47,8) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_47,8);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,79,"破除谣言1" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"破除谣言1");
       		}
        	break;
        case 11:
        	if( who->get_legend(TASK_47,17)&&!who->get_legend(TASK_47,18) )
        	{
			if (TASK_LEGEND_D->check_task_item(who,"认罪书",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/final/91/1814",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_47,18);
			who->add_exp(96000);
			who->add_potential(1300);
			who->add_cash(95000);
			send_user(who,"%c%s",';',"破除谣言5 经验 96000 潜能 1300 金钱 95000 天香续命丹 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,83,"" );
        	}
        	break;
        case 12:
        	if ( who->get_level() >=115 && !who->get_legend(TASK_47,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    据说最近大将军整日心事重重，仿佛有很忧心的事情却无法办到，但是我等并非执掌军务，不便相问，你代我拜访一下，问他可有什么需要帮忙的。\n"ESC"接受任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 13:
        	if ( who->get_level() >=115 && !who->get_legend(TASK_47,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_47,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,84,"索取神剑1" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"索取神剑1");
       		}
        	break;
        case 99:	
		INQUISITOR_D->do_look( who, me); 
        	break;  
        }
}    