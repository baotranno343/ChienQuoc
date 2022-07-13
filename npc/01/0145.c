
#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5909; }

// 函数：构造处理
void create()
{
        set_name( "Lí Tiểu Mao" );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//        set("level", 0);
//        set("legend", ({ 32*2+24 }));
	set("mpLegend2",([5:({32*2+25,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
        string tmp="";
   
        if( who->get_legend(TASK_NEWBIE_02, 24) && !who->get_legend(TASK_NEWBIE_02, 25) )
        {
		tmp = sprintf(ESC +HIY+ "美味的蜜糖\ntalk %x# welcome.1\n",getoid(this_object()));
        }   
        send_user( who, "%c%s", ':', get_name() + "：\n嘻嘻。我最喜欢吃甜的东西，比如说红豆糕啦，绿豆糕啦，还有冰糖葫芦。\n" 
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
	int flag,i,j,k,size,p,amount;
	object who,item,*inv;
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:
		if ( who->get_legend(TASK_NEWBIE_02, 24) && who->get_save_2("xiaomao_fengmi") < 3 )
			send_user(who,"%c%s",':',sprintf("%s:\n    %s，是不是我太烦人了？你不喜欢我，所以不给我找蜜糖呢？\n"ESC"离开",me->get_name(),who->get_gender()==1?"哥哥":"姐姐"));
		else if ( who->get_legend(TASK_NEWBIE_02, 24) && who->get_save_2("xiaomao_fengmi") >= 3 )
			send_user(who,"%c%s",':',sprintf("%s:\n    嘻嘻，%s真是个大好人。这些东西是我奶奶给我的，我一直没舍得用，你拿着，就当我和你交换蜜糖哦！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),who->get_gender()==1?"哥哥":"姐姐",getoid(me)));
				
		break;

	case 3:
		if ( who->get_legend(TASK_NEWBIE_02, 24) && who->get_save_2("xiaomao_fengmi") >= 3 )
		{
			if (TASK_LEGEND_D->check_task_item(who,"蜜糖",3) != 1 )
        			return;
			item = new("item/32/3282");
			item->set_amount(8);
			p = item->move(who,-1);
			if ( !p )
			{
				send_user(who,"%c%s",'!',"你身上的东西太多");
				destruct(item);
				return;
			}
			TASK_LEGEND_D->task_finish(who);
			who->delete_save_2("xiaomao_fengmi");
			item->add_to_user(p);
			who->add_exp(380);
			who->add_potential(20);
			who->set_legend(TASK_NEWBIE_02, 25);
			send_user(who,"%c%s",';',"美味的蜜糖 经验 380 潜能 20 桔子 8");			
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YEWAI,1,"" );
		}
		break;
	}
}