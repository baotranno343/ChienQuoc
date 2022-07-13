
// 自动生成：/make/npc/make8012

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

void do_out();
void do_record();

// 函数：获取人物造型
int get_char_picid() { return 0050; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Sở Quốc Thủ Vệ");
        set_city_name("Sở Quốc");

        set_2( "talk", ([
                "out"           : (: do_out :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("in", 13);
        set("out", 11);
//        set("level",31);
//        set("legend",({32*8+7}));
	set("mpLegend",([30:({32*8+7,32*37+25}),95:({32*33+16})]));
	set("mpLegend2",([30:({32*8+9,}),95:({32*33+18})]));
        setup();
}

string get_master() { return CITY_CHU->get_master(); }
string get_master_2() { return CITY_CHU->get_master_2(); }
string get_master_3() { return CITY_CHU->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	int id;
	object me = this_object();
	id = getoid(me);
	if ( (who->get_level() >= 30 && !who->get_legend(TASK_08,7)) || (who->get_legend(TASK_08,7)&&!who->get_legend(TASK_08,9)) )
	{
		tmp = sprintf(ESC HIY "沼泽寻宝\ntalk %x# welcome.1\n",id);
	}
	if ( ( who->get_level() >= 95 && !who->get_legend(TASK_33,16) ) || ( who->get_legend(TASK_33,16) && !who->get_legend(TASK_33,18) ) )
		tmp += sprintf(ESC HIY "惩戒梁少\ntalk %x# welcome.4\n",id);
	if ( who->get_level() >= 30 && !who->get_legend(TASK_37,25) )
		tmp += sprintf(ESC HIY "带口信给齐国使节\ntalk %x# welcome.7\n",id);

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GUARDER_D->do_look_2( who, me ); 
	
}
void do_out() { GUARDER_D->do_out( this_player(), this_object() ); }

void do_record() { GUARDER_D->do_record( this_player(), this_object() ); }
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
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你去过沼泽吗？\n    那幽绿茂盛的水草，腐烂的木头，随时可能吞噬你的泥潭，令人心生寒气。也只有这种鲜为人去的地方，才有可能存在宝物。\n    我听人说，在沼泽深处有一箱宝物，里面的东西足够让你生活一辈子！但是沼泽实在太危险，我不太敢去，你去给我找来行么？如果有了这箱宝物，我想我以后再也不用在这里站岗了，风吹雨淋的日子真不好受啊！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_08,7) && !who->get_legend(TASK_08,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没找到？我朋友骗我的啊！我还是亲自去找吧。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_08,8) && !who->get_legend(TASK_08,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈……我再也不用在这里站岗了，我有钱了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_08,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,15,"沼泽寻宝" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"沼泽寻宝");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_08,8) && !who->get_legend(TASK_08,9) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"宝箱",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_08,9);
			who->add_exp(2200);
			who->add_potential(80);
			who->add_cash(1700);
			send_user(who,"%c%s",';',"沼泽寻宝 经验 2200 潜能 80 金钱 1700");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,15,"" );
        	}
        	break;   
	case 4:
		if ( who->get_level() >= 95 && !who->get_legend(TASK_33,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太气人了，恶少梁居然三番五次调戏我表妹，这个天杀的，虽然我打不过他，可是我有你这个仁勇双全的朋友啊！你一定要帮我教训那个梁少！让他再也没有胆子调戏我的表妹！我表妹最近都要去大别山湘妃林采草药，梁少一定又在附近，你抓住他打的他爹妈都不认识！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_33,16) && !who->get_legend(TASK_33,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    什么？你居然被他打败了！天哪，我那苦命的表妹，我那苦命的未来孩儿……\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_33,17) && !who->get_legend(TASK_33,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这个恶少，欺负我表妹，活该不得好死！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 5:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_33,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_33,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,38,"惩戒梁少" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"惩戒梁少");        		
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_33,17) && !who->get_legend(TASK_33,18) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/61017",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_33,18);
			who->add_exp(71000);
			who->add_potential(930);
			who->add_cash(60000);
			send_user(who,"%c%s",';',"惩戒梁少 经验 71000 潜能 930 金钱 60000 神秘果图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,38,"" );
        	}
        	break;
        case 7:
       		if ( who->get_level() >= 30 && !who->get_legend(TASK_37,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    齐国使节是我母亲的侄子，也是我的表哥，我们已经很多年没见了，母亲老了，越来越想念她家乡的那些亲朋好友们，所以她想在最近回趟娘家，和她做姑娘时的那些好姐妹们聚聚，我考虑了一下，如果要去齐国，也只能借住在齐国使节家了。所以请你先去给齐国使节打个招呼，将这个消息告诉他。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 8:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_37,25) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_37,25);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,44,"带口信给齐国使节" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"带口信给齐国使节");        		
        	}
        	break;
        case 99:
        	GUARDER_D->do_look_2( who, me ); 
        	break;     
        }
}