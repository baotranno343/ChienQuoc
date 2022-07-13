// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <public.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 9715; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Lý Ẩn Sĩ");
        set_city_name("Chu Quốc");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
	set("mpLegend2",([0:({32*40+6,32*40+9,32*40+12,}),]));
        setup();
}
// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        if ( who->get_legend(TASK_40,5) && !who->get_legend(TASK_40,6) ) 
		tmp += sprintf(ESC HIY "Tù Và Lập Bang\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_legend(TASK_40,6) && !who->get_legend(TASK_40,9) ) 
		tmp += sprintf(ESC HIY "Thẻ Tre Bị Mất\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_legend(TASK_40,9) && !who->get_legend(TASK_40,12) ) 
		tmp += sprintf(ESC HIY "Sừng Trâu Vàng\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_legend(TASK_40,12) && !who->get_legend(TASK_40,13) ) 
		tmp += sprintf(ESC HIY "Thỉnh Cầu Vua Giúp Đỡ\ntalk %x# welcome.1\n",getoid(this_object())); 

        send_user( who, "%c%s", ':', sprintf( " %s :\n Giang hồ phân tranh, mãi mãi không có điểm dừng.Vinh hoa phú quý cũng chỉ là mây khói, sống không tìm ra, chết không thể mang theo, không có giá trị gì cả.\n", get_name())
        + tmp +
        ESC"Rời khỏi"
         );
}

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
        	if ( who->get_legend(TASK_40,5) && !who->get_legend(TASK_40,6) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    战事依旧连连，苦了那些贫民百姓，既然你有志做一番大事，利用民间的力量来拯救他们，那我也不能阻拦你，只是这么多年没有在意这门手艺，连记录制作方法的竹简也丢失了，如果你能找回，我定当为你做好号角。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_40,6) && !who->get_legend(TASK_40,7) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    其实，江湖上传说的王之号角并不只是传说，只是王之号角的制作过程非常复杂，而我，也只能做出普通的号角，如何将普通的号角加工为能建立帮派的王之号角，我想只有王府的工匠才能做得到。\n    既然你打算做一番大事，想集合民间的力量来拯救黎民百姓，那我也不能阻拦你，只是我已经多年没有做过号角了，就连记录制作方法的竹简也被肖柱偷走了，现在你已经找到我，料想你不会半途而废，所以你去肖柱的手中夺回竹简交给我吧。他就在东海岛的东海渔村，就在那几个草垛旁边。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,7) && !who->get_legend(TASK_40,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果没有记录制作方法的竹简，我想我是无论如何都想不起那些复杂的制作方法了。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_40,8) && !who->get_legend(TASK_40,9) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    别把制作号角看得太简单了，实际上它是一项很复杂的工艺，所以我还需要一样原材料才能开始制作。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_40,9) && !who->get_legend(TASK_40,10) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    虽然你已经将记录制作号角方法的竹简交给我了，但是由于用来制作王之号角的号角是一件很特殊的物品，所以我还需要一样特殊的原材料——金色牛角，如果不是用金色牛角制成的号角是不可能加工为王之号角的，你想要王府的工匠给你加工成王之号角，作为建帮的信物，你就必须找到金色牛角，\n    金色牛角本是金牛之角，但是由于一场突如其来的变故，这些浑身金灿灿的牛一夜之间全部暴毙，而原本就与金牛生活在一起的苦役们为了悼念这群金牛，便将它们的角收藏了起来，你去郑Quốc渠想办法找苦役要到这些金色牛角吧。听说他们把牛角保护得很好，用装满了药物的箱子装着。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,10) && !who->get_legend(TASK_40,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没有金色牛角，我不能给你做出能加工成王之号角的号角，你自己看着办吧。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_40,11) && !who->get_legend(TASK_40,12) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了记录制作方法的竹简和你刚刚带来的金牛之角，我想我很快就能做成号角了，你稍后再过来找我取号角吧。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_40,12) && !who->get_legend(TASK_40,13) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在，我把号角交给你，可是你要记得，我交给你的号角并不是建帮用的王之号角，而要得到建帮用的王之号角，必须要经过宫廷工匠的加工，我想你应该去找找你们Quốc家的王，看他能不能帮助你，我听说他是一个很民主的人，支持民间善意的力量，我相信你既然能用你的诚意打动我，你一定会打动他的。\n    去吧，去找你们Quốc家的王，并请求他帮助你吧！拿着这只箱子，里面装的就是号角。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));

        	break;

        case 2:
        	if ( who->get_legend(TASK_40,5) && !who->get_legend(TASK_40,6) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_40,6);
			who->add_exp(3000);
			who->add_potential(100);
			who->add_cash(2500);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,10,"" );
			send_user(who,"%c%s",';',"Tù Và Lập Bang Kinh nghiệm 3000 Tiềm năng 100 Ngân lượng 2500");
			me->do_welcome(1);
        	}
        	break;   
 	case 3:
        	if ( who->get_legend(TASK_40,6) && !who->get_legend(TASK_40,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_40,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"Chu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,11,"Thẻ Tre Bị Mất" );
			send_user( who, "%c%s", '!', "Nhận nhiệm vụ "HIY"Thẻ Tre Bị Mất");
        	}
        	break;  
        case 4:
        	if ( who->get_legend(TASK_40,8) && !who->get_legend(TASK_40,9) ) 
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"Thẻ Tre",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_40,9);
			who->add_exp(3500);
			who->add_potential(120);
			who->add_cash(3000);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,11,"" );
			send_user(who,"%c%s",';',"Thẻ Tre Bị Mất Kinh nghiệm 3500 Tiềm năng 120 Ngân lượng 3000");
			me->do_welcome(1);
        	}
        	break;
 	case 5:
        	if ( who->get_legend(TASK_40,9) && !who->get_legend(TASK_40,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_40,10);
			who->delete_save("lysjinsnj");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"Chu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,12,"Sừng Trâu Vàng" );
			send_user( who, "%c%s", '!', "Nhận nhiệm vụ "HIY"Sừng Trâu Vàng");
        	}
        	break;  
        case 6:
        	if ( who->get_legend(TASK_40,11) && !who->get_legend(TASK_40,12) ) 
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"Rương Chứa Sừng Trâu Vàng",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_40,12);
			who->delete_save("lysjinsnj");
			who->add_exp(3100);
			who->add_potential(105);
			who->add_cash(2700);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,12,"" );
			send_user(who,"%c%s",';',"Sừng Trâu Vàng Kinh nghiệm 3100 Tiềm năng 105 Ngân lượng 2700");
			me->do_welcome(1);
        	}
        	break;
 	case 7:
        	if ( who->get_legend(TASK_40,12) && !who->get_legend(TASK_40,13) )
        	{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;        		
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			TASK_LEGEND_D->give_item(who,"item/98/0196",1); 
        		who->set_legend(TASK_40,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"Chu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,13,"Thỉnh Cầu Vua Giúp Đỡ" );
			send_user( who, "%c%s", '!', "Nhận nhiệm vụ "HIY"Thỉnh Cầu Vua Giúp Đỡ");
        	}
        	break;
        }
}