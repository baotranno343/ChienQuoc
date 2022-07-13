
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
int get_char_picid() { return 5701; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Lâm Vị");
        set_city_name("Hàn Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ])); 
	set("mpLegend2",([0:({32*26+21,}),]));
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
	if ( who->get_legend(TASK_26,20) && !who->get_legend(TASK_26,21) )
		tmp += sprintf(ESC HIY "寻人避难\ntalk %x# welcome.1\n",getoid(me));
			
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
        int flag,i,size,p,amount;
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_26,20) && !who->get_legend(TASK_26,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    什么！你已经把杀我妻子那个可恶的土匪杀掉了？真是天网恢恢呀！为了我的事叔叔是这样的担心，看来为了我叔叔，我不可以再这样颓废下去了，我必须振作。也谢谢你为我做了这么多的事，我真不知道该怎么谢谢你好，这是我以前行商的时候找到的一张玄铁炸弹图纸，我就把这个送给你吧。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_legend(TASK_26,20) && !who->get_legend(TASK_26,21) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/66043",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_26,21);
			who->add_exp(41000);
			who->add_potential(600);
			who->add_cash(40000);
			send_user(who,"%c%s",';',"寻人避难 经验 41000 潜能 600 金钱 40000 玄铁炸弹图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,35,"" );
        	}
        	break;
	}
}