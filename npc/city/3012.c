
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
int get_char_picid() { return 0600; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Triệu Quốc Thủ Vệ");
        set_city_name("Triệu Quốc");

        set_2( "talk", ([
                "out"           : (: do_out :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("in", 13);
        set("out", 11);
//        set("level",83);
//        set("legend",({32*28+4}));
 	set("mpLegend",([80:({32*28+4}),110:({32*39+9})]));
 	set("mpLegend2",([80:({32*28+6}),]));
        setup();
}

string get_master() { return CITY_ZHAO->get_master(); }
string get_master_2() { return CITY_ZHAO->get_master_2(); }
string get_master_3() { return CITY_ZHAO->get_master_3(); }

void do_look( object who ) 
{ 
	string tmp="";
	object me = this_object();

	if ( (who->get_level() >= 80 && !who->get_legend(TASK_28,4)) || (who->get_legend(TASK_28,4) && !who->get_legend(TASK_28,6)))
	{
		tmp = sprintf(ESC HIY "深入牧场\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_level() >= 110 && !who->get_legend(TASK_39,9) )
		tmp += sprintf(ESC HIY "心愿\ntalk %x# welcome.4\n",getoid(me));

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
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_28,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    邯郸城的原阳牧场处处透着诡异，据说商旅路过都是结伴同行，饶是如此，稍有不慎就会失去踪迹，而后只能找到破碎的尸首和凌乱的货物，而此间居然有个叫做李刃的居住，之所以不称他为人，是因为大家都怀疑就是他亲手导演了这一幕幕惨剧，虽然平常经过他也热情待客，可是总觉得他的笑容阴森森的，说不出的诡异，所以尽管怕把他惹得当场发飙而留下来歇歇脚，可是大家都心惊胆战的，水不敢喝，东西也不敢碰，后来慢慢开始流传他原本是个正在修炼的僵尸，所以选择了这个荒无人烟但是又有行旅经过的地方既避开人群的生气侵扰，又可以适时补充鲜血提高法力。对于这种危害大众的人我们的职责就是坚决予以清除，我命你速速前去铲除这个李刃，还大家一个太平的道路。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_28,4) && !who->get_legend(TASK_28,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯？没有李刃？莫非他会隐身还是一切只是玄之又玄的传说？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_28,5) && !who->get_legend(TASK_28,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呃，杀死了，不见了？什么都没有留下？太古怪了，不是僵尸是什么，不过谢天谢地，壮士你已经为我们民众除了一个大害了！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 2:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_28,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_28,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,46,"深入牧场" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"深入牧场");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_28,5) && !who->get_legend(TASK_28,6) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/final/15/1521",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_28,6);
			who->add_exp(49000);
			who->add_potential(690);
			who->add_cash(47000);
			send_user(who,"%c%s",';',"深入牧场 经验 49000 潜能 690 金钱 47000 强效物防 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,46,"" );
        	}
        	break; 
        case 4:
		if ( who->get_level() >= 110 && !who->get_legend(TASK_39,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我的兄弟得了重病，已经奄奄一息了。\n    他这辈子最大的心愿就是见一下秦管家，秦管家是一个足智多谋的人，他听说过秦管家的一些事迹后，相当崇拜他，现在他已在弥留之际，只希望能见到秦管家一面。\n    你能去将这个心愿告诉秦管家吗？\n    \n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 5:
        	if ( who->get_level() >= 110 && !who->get_legend(TASK_39,9) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_39,9);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,67,"心愿" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"心愿");
        	}
        	break; 
        case 99:
        	GUARDER_D->do_look_2( who, me ); 
        	break;     
        }
}