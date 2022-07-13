
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 6; }
// 有自己的do_look函数
int is_self_look() { return 1; }
// 函数：获取人物造型
int get_char_picid() { return 5403; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Y Dược");
	set_real_name("Tử Dương");
        set_city_name("Yên Quốc");

        set_2( "good", ([
                "01" : "/item/91/9100",
                "02" : "/item/91/9101",
                "03" : "/item/91/9110",
                "04" : "/item/91/9111",
                "05" : "/item/stuff/0106",
        ]) );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
	set("mpLegend2",([50:({32*15+8}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	result = sprintf("%s：\n    "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	if ( who->get_legend(TASK_15, 7) && !who->get_legend(TASK_15, 8) )
	{
		result = result + sprintf( ESC HIY "3 cái Cỏ Linh Chi\ntalk %x# welcome.1\n", getoid(me) );
	}
	if ( (who->get_legend(TASK_15, 8) && !who->get_legend(TASK_15, 9)) || (who->get_legend(TASK_15, 9) && !who->get_legend(TASK_15, 10)) )
	{
		result = result + sprintf( ESC HIY "Căn bệnh của Phu Nhân\ntalk %x# welcome.1\n", getoid(me) );
	}
	result = result + sprintf( ESC "交易\nlist %x#\n" ESC "我只是随便看看\nCLOSE\n", getoid(me) ) ;        	
	send_user( who, "%c%s", ':', result );

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
 		if ( who->get_legend(TASK_15,7) && !who->get_legend(TASK_15,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Ngươi có thể đi tới Yên Trường Thành tìm Cỏ Linh Chi.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.2\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_15, 8) && !who->get_legend(TASK_15, 9))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Ngươi có thể đi tới Yên Trường Thành tìm Cỏ Linh Chi.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.3\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_15, 9) && !who->get_legend(TASK_15, 10))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Cỏ Linh Chi không tìm dễ dàng, ngươi chịu khó đi!\n"ESC"Rời khỏi", me->get_name()));

        	break;
    
        case 2:
        	if ( who->get_legend(TASK_15,7) && !who->get_legend(TASK_15,8) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_15,8);
			who->add_exp(4800);
			who->add_potential(180);
			who->add_cash(2800);
			send_user(who,"%c%s",';',"Căn bệnh của Phu Nhân（1） Kinh nghiệm 4800 Tiềm năng 180 Ngân lượng 2800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,30,"" );
        		me->do_welcome(1);
        	}
        	break;   
	case 3:
        	if(who->get_legend(TASK_15, 8) && !who->get_legend(TASK_15, 9))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_15,9);
        		who->delete_save_2("frlingzhi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,31,"Căn bệnh của Phu Nhân（2）" );
			send_user( who, "%c%s", '!', "Nhận nhhiệm vụ "HIY"Căn bệnh của Phu Nhân（2）");
        	}
        	break; 
        }
}