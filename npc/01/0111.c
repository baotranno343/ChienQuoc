
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5901; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name( "Trần Lão Đầu" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//        set("level", 6);
//        set("legend", ({ 32*2+17 }));
//	set("mpLegend",([5:({32*2+17,}),]));
        setup();
}

// 变量：随机对话
string *TalkTable = ({ 
        "啊，天好蓝啊！",
        "天上的云好白啊！",
        "不知道天有多高？！",
});

int sizeof_talk = sizeof(TalkTable);

// 函数：对话处理
void do_look( object who )
{
        string tmp="";

/*        if( who->get_level() >= 5 )
        {
                if( !who->get_legend(TASK_NEWBIE_02, 21) )
                {
			tmp = sprintf(ESC"百步仙\ntalk %x# welcome.1\n",getoid(this_object()));
                }
        }*/
        
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        send_user( who, "%c%s", ':', sprintf( " %s :\n Nơi này phong cảnh thật đẹp, trời xanh, mây trắng, thác đổ, chim hót, cây xanh, hoa tươi, suốt cả đời ở đây mình cũng chịu.\n", get_name() )
        + tmp +
        ESC"Rời khỏi" );
}


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i,j,k,size,*tmp=({}),*res=({}),p;
	object who,item,item1;
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:
		if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 17) )
			send_user(who,"%c%s",':',sprintf("%s:\n    村中的人都知道李老汉是一位藏酒的名家，据说有一壶天下名酒‘百步仙’就收藏于他家中。我曾多次登门向他讨酒，可惜他说什么都不愿将酒给我。如果有幸让我尝上一口百步仙，就算死一回也值了。\n    李老汉就在我的西北方，在去往巴丘的那条路上，你很容易就找到他了，前天我还在他那喝了次酒，路不远，我知道的。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
		else if( who->get_legend(TASK_NEWBIE_02, 17) && !who->get_legend(TASK_NEWBIE_02, 20) )
			send_user(who,"%c%s",':',sprintf("%s:\n    那李老汉不肯是吧？还是有别的条件？我能帮上你的我一定帮你！\n"ESC"离开",me->get_name()));
		else if( who->get_legend(TASK_NEWBIE_02, 17) && who->get_legend(TASK_NEWBIE_02, 20) && !who->get_legend(TASK_NEWBIE_02, 21))	
			send_user(who,"%c%s",':',sprintf("%s:\n    哈哈哈哈！好酒！果然是好酒！！！能尝上此等美酒，我此生无憾了！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),getoid(me)));
		break;
	case 2:
		if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 17) )
		{
			who->set_legend(TASK_NEWBIE_02, 17);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,21,"百步仙" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"百步仙");	
		}
		break;
	case 3:
		if( who->get_legend(TASK_NEWBIE_02, 17) && who->get_legend(TASK_NEWBIE_02, 20) && !who->get_legend(TASK_NEWBIE_02, 21))	
		{
			if( !objectp( item = present("百步仙", who, 1, MAX_CARRY) ) || !item->is_baibuxian() == 1 )
			{
				send_user(who,"%c%s",'!',"你的百步仙呢?");
				return;		
			}
			item->remove_from_user();
			destruct(item);	
			item = new("item/std/0407");
			if ( !item )
				return;
			item->set_amount(5);
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
				send_user(who,"%c%s",'!',"你身上的东西太多了");	
				return ;
			}		
			item->add_to_user(p);
			who->add_exp(200);
			who->add_cash(3000);
			who->set_legend(TASK_NEWBIE_02, 21);
			send_user(who,"%c%s",';',"百步仙 经验 200 金钱 3000 回城符 5");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,21,"" );			
		}
		break;
	}
}