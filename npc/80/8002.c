
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;
string *TalkTable = ({ 
        "Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
        "Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});
void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 5505; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Lí Lăng");
        set_city_name("Tề Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ])); 
	set("mpLegend2",([0:({32*44+29,32*45+3,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who ) 
{
	object me = this_object();
	string tmp="";
	
	if ( who->get("escort.finish") == 1 )
	{
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}
        if(     who->get_quest("escort.flag")    // 运镖任务
        &&      who->get_quest("escort.leader") == 1    // 队长完成
        &&      who->get_quest("escort.name") == get_name() 
        && 	who->get_quest("escort.city")+" Quốc" == get_city_name() )    // 找对人了
        {
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}        
	
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( who->get_legend(TASK_44,27) && !who->get_legend(TASK_44,29) )
		tmp += sprintf(ESC HIY "油菜籽\ntalk %x# welcome.1\n",getoid(me));
	if ( (who->get_legend(TASK_44,29) && !who->get_legend(TASK_45,1)) || (who->get_legend(TASK_45,1) && !who->get_legend(TASK_45,3)) )
		tmp += sprintf(ESC HIY "替李屠报仇\ntalk %x# welcome.1\n",getoid(me));

	send_user(who,"%c%s",':',sprintf( "%s：\n    %s\n", get_name(), TalkTable[ random(sizeof(TalkTable))] ) 
			+ tmp +
			ESC"离开"
			);

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
        string tmp;
        
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_44,27) && !who->get_legend(TASK_44,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听李屠最近找你办事，是不是他有什么困难，需要我帮忙么？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_44,28) && !who->get_legend(TASK_44,29) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这李屠真是个受人滴水之恩，当涌泉相报之人啊。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_44,29) && !who->get_legend(TASK_45,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    既然李屠处境这么艰难还要帮助我，我也得再为他做点事情，不过现在我扩建作坊无暇分身，大侠能否代我走一趟？我听说天门阵的太极门众守曾经在李屠下狱之后抢劫了他家，结果他的儿女不知所踪，而他母亲听说为了保住什么东西自杀了，可恨我等无高强武艺傍身，不能为他亲手报仇，唯有劳烦大侠了，请你消灭天门阵的太极门众守18个，你放心，报酬是绝对不会少的。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_45,1) && !who->get_legend(TASK_45,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那些贼子狡猾多端，可是让大侠吃了苦头?\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_45,2) && !who->get_legend(TASK_45,3) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大侠急公好义，老天必会保佑你逢怪掉宝，遇人得友。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 2:
 		if ( who->get_legend(TASK_44,28) && !who->get_legend(TASK_44,29) )
        	{
			if (TASK_LEGEND_D->check_task_item(who,"油菜籽",10) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->delete_save("lituyoucaizi");
			who->set_legend(TASK_44,29);
			who->add_exp(51000);
			who->add_potential(778);
			who->add_cash(50300);
			send_user(who,"%c%s",';',"人情冷暖（2） 经验 51000 潜能 778 金钱 50300");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,67,"" );
	      		me->do_welcome(1);
	      	}
        	break;              	
        case 3:
        	if ( who->get_legend(TASK_44,29) && !who->get_legend(TASK_45,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_45,1);
        		who->delete_save("lilangtaijmzs");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,68,"人情冷暖（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"人情冷暖（3）");
        	}
        	break;        	
        case 4:
 		if ( who->get_legend(TASK_45,2) && !who->get_legend(TASK_45,3) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/62093",1);
        		who->delete_save("lilangtaijmzs");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_45,3);
			who->add_exp(190000);
			who->add_potential(1450);
			who->add_cash(193000);
			send_user(who,"%c%s",';',"人情冷暖（3） 经验 190000 潜能 1450 金钱 193000 飓风拳套图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,68,"" );
	      	}
        	break;         	
        	
        }
}