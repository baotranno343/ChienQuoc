
// 自动生成:/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>
#include <equip.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数:获取人物造型
int get_char_picid() { return 5302; }

// 函数:构造处理
void create()
{
        set_name("Bảo Thạch Thương");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",51);
//        set("legend",({32*14+4}));
	set("mpLegend",([50:({32*14+4}),]));
	set("mpLegend2",([50:({32*14+6}),]));
        setup();
}

// 函数:对话处理
void do_look( object who )
{
	string tmp="";
        if ( (who->get_level() >= 50 && !who->get_legend(TASK_14,4)) || (who->get_legend(TASK_14,4)&&!who->get_legend(TASK_14,6)) ) 
		tmp += sprintf(ESC HIY "Bảo thạch quý hiếm\ntalk %x# welcome.1\n",getoid(this_object())); 
 
        send_user( who, "%c%s", ':', sprintf( "%s:\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(1101))
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
	       	if ( who->get_level() >= 50 && !who->get_legend(TASK_14,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Nghe nói đánh quái vật ở Trường Bạch Sơn có thể có được Hồng bảo thạch.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.2\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_14,4) && !who->get_legend(TASK_14,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Hồng bảo thạch đâu ?.\n"ESC"Rời khỏi", me->get_name()));
		else if ( who->get_legend(TASK_14,5) && !who->get_legend(TASK_14,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Cám ơn ngươi nhiều lắm.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.3\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
        		
        	break;
	case 2:
        	if( who->get_level() >=50 && !who->get_legend(TASK_14,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_14,4);
        		who->delete_save_2("zghongbaoshi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,24,"Bảo thạch quý hiếm" );
			send_user( who, "%c%s", '!', "Nhận nhiệm vụ "HIY"Bảo thạch quý hiếm");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_14,5) && !who->get_legend(TASK_14,6) )
        	{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),0,50,NECK_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
        		if (TASK_LEGEND_D->check_task_item(who,"Hồng bảo thạch",10) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_14,6);
        		who->delete_save_2("zghongbaoshi");
			who->add_exp(6000);
			who->add_potential(240);
			who->add_cash(4800);
			send_user(who,"%c%s",';',sprintf("Bảo thạch quý hiếm Kinh nghiệm 6000 Tiềm năng 240 Ngân lượng 4800 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,24,"" );
        	}
        	break;   
		
        }
}