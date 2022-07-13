
// 自动生成：/make/npc/make8020

#include <npc.h>
#include <ansi.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0451; }
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
        set_real_name("Rèn Đúc 1~20");
        set_city_name("Tần Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//	set("level",66);
//	set("legend",({32*20+19}));
	set("mpLegend",([65:({32*20+19}),]));
	set("mpLegend2",([60:({32*38+6}),65:({32*20+23,32*20+26,32*20+29,}),]));
	set_skill(0620, 39);
        set_2( "good", ([
                "01" : "/item/product/62001",
                "02" : "/item/product/62002",
                "03" : "/item/product/62003",
                "04" : "/item/product/62004",
                "05" : "/item/product/62005",
                "06" : "/item/product/62006",
        ]) );
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( ( who->get_level() >= 65 && !who->get_legend(TASK_20,19) ) || ( who->get_legend(TASK_20,19) && !who->get_legend(TASK_20,20) ) )
	{
		tmp = sprintf(ESC HIY "探听虚实\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_20,22) && !who->get_legend(TASK_20,23) )
	{
		tmp += sprintf(ESC HIY "宫殿图纸\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_20,23) && !who->get_legend(TASK_20,24)) || (who->get_legend(TASK_20,24) && !who->get_legend(TASK_20,26)))
	{
		tmp += sprintf(ESC HIY "千年红木\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_20,26) && !who->get_legend(TASK_20,27)) || (who->get_legend(TASK_20,27) && !who->get_legend(TASK_20,29)))
	{
		tmp += sprintf(ESC HIY "扫清障碍\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_20,29) && !who->get_legend(TASK_21,1) )
	{
		tmp += sprintf(ESC HIY "破土动工\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_level() >= 60 && who->get_legend(TASK_38,5) && !who->get_legend(TASK_38,6) )
	{
		tmp += sprintf(ESC HIY "打造武器\ntalk %x# welcome.9\n",getoid(me));
	}
	tmp += sprintf(ESC"学习生活技能\nlearn ? %s\n", me->get_char_id());
	tmp += sprintf(ESC"购买Rèn Đúc 技能等级1-20级的配方\nlist %s\n", me->get_char_id());
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
        int flag,i,size,p,amount;
        object who,item, *inv;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 65 && !who->get_legend(TASK_20,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听说秦王最近打算修缮冀阙宫，这可是个好差使，你帮我到秦管家处探听一下虚实。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,19) && !who->get_legend(TASK_20,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    去秦管家处探听到消息了吗？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_20,22) && !who->get_legend(TASK_20,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了冀阙宫的原始图纸，修缮起来容易多了！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,23) && !who->get_legend(TASK_20,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我仔细看了那宫殿图纸，后来勘测了一下冀阙宫情况，发现太庙里原先有一处用千年红木的地方竟然被刀兵所坏，必须得更换了，据说在秦长城的烽火台处有一根，你前去将它运回来。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,24) && !who->get_legend(TASK_20,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那根千年红木是非换不可，况且太庙庄严之地，不能随便用什么杂木凑合。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_20,25) && !who->get_legend(TASK_20,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这根红木找到了，这处最伤大雅的地方终于可以修缮了。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,26) && !who->get_legend(TASK_20,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    除了宫殿建造原图和木料，还需要上好的秦长城附近采石场的青石料，可是那附近的恶霸秦老四把持了石料开采，居然还敢不卖给大王，真是不要脑袋了！你给我去将这个胆大妄为的家伙干掉！\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,27) && !who->get_legend(TASK_20,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    恶霸不除，没有那种好石料，怎么才能完成大王交给的修缮任务啊。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_20,28) && !who->get_legend(TASK_20,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好了，一切就绪，三月之内，冀阙宫修缮必定完工。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,29) && !who->get_legend(TASK_20,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在所有一切都已经准备齐全，冀阙宫的修缮即刻可以动工。不过在动工之前须先禀告一下秦国内政官备案，你愿意前去禀告吗？\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 2:
        	if ( who->get_level() >= 65 && !who->get_legend(TASK_20,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_20,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,23,"探听虚实" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"探听虚实");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_20,22) && !who->get_legend(TASK_20,23) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"宫殿图纸",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_20,23);
			who->add_exp(12000);
			who->add_potential(330);
			who->add_cash(9500);
			send_user(who,"%c%s",';',"宫殿图纸 经验 12000 潜能 330 金钱 9500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,24,"" );
			me->do_welcome(1);
        	}
        	break;
	case 4:
        	if ( who->get_legend(TASK_20,23) && !who->get_legend(TASK_20,24) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_20,24);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,25,"千年红木" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"千年红木");
        	}
        	break;
        case 5:
        	if ( who->get_legend(TASK_20,25) && !who->get_legend(TASK_20,26) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"千年红木",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_20,26);
			who->add_exp(12500);
			who->add_potential(340);
			who->add_cash(10500);
			send_user(who,"%c%s",';',"千年红木 经验 12500 潜能 340 金钱 10500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,25,"" );
			me->do_welcome(1);
        	}
        	break;
	case 6:
        	if ( who->get_legend(TASK_20,26) && !who->get_legend(TASK_20,27) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_20,27);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,26,"扫清障碍" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"扫清障碍");
        	}
        	break;
        case 7:
        	if ( who->get_legend(TASK_20,28) && !who->get_legend(TASK_20,29) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64103",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_20,29);
			who->add_exp(13000);
			who->add_potential(340);
			who->add_cash(10000);
			send_user(who,"%c%s",';',"扫清障碍 经验 13000 潜能 340 金钱 10000 垂云披袍图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,26,"" );
			me->do_welcome(1);
        	}
        	break;
	case 8:
        	if ( who->get_legend(TASK_20,29) && !who->get_legend(TASK_21,1) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_21,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,27,"破土动工" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"破土动工");
        	}
        	break;
        case 9:
        	if ( who->get_level() >= 60 && who->get_legend(TASK_38,5) && !who->get_legend(TASK_38,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    既然是这样，那我就收下他这个徒弟，等他亲自来我这后，我再传授给他打造武器的知识吧！\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 10:
        	if ( who->get_level() >= 60 && who->get_legend(TASK_38,5) && !who->get_legend(TASK_38,6) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_38,6);
			who->add_exp(6500);
			who->add_potential(230);
			who->add_cash(6500);
			send_user(who,"%c%s",';',"打造武器 经验 6500 潜能 230 金钱 6500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,64,"" );
        	}
        	break;
        }
}