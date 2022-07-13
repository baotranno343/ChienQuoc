
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_zzy(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5802; }

// 函数：构造处理
void create()
{
        set_name( "洞庭湖舟子" );

        set_2( "talk", ([
                "zzy" : (: do_zzy :),
        ]));

        setup();

}

// 函数：对话处理
void do_look( object who )
{
	object npc,item,me=this_object();
	int id = getoid( me ),i;
        string cmd = sprintf( "talk %x# zzy.1\n", id );
	string tmp ="";
	tmp = ESC "做粽子\n" + cmd;
	send_user( who, "%c%s", ':', get_name() + "：\n    唉！我国大诗人大思想家屈原大人就是在这里投了江的。我很担心他的遗体被鱼儿咬坏，想要制作粽子来抛进江中，只是没有材料。需要糯米、猪肉和蓼叶各一份，你有吗？\n" +
                        tmp +
                        ESC "离开。\nCLOSE\n" );	
}

void do_zzy(string arg)
{
	object me = this_object();
        __FILE__ ->do_task_start(me, arg);
}

// 函数：开始
void do_task_start( object me, string arg )
{
	int flag;
	object who,item_dw1,item_dw2,item_dw3;
	string cWord="";
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
		cWord = sprintf(me->get_name() + "：\n    你要给我糯米、猪肉和蓼叶各一份吗？");
		send_user( who, "%c%s", ':', cWord +"\n"+
			ESC +sprintf("交出粽子材料。\ntalk %x# zzy.2\n",getoid(me)) +
			ESC "离开。\nCLOSE\n" ); 
                break;
        case 2:
        	if( !objectp( item_dw1 = present("泡过的糯米", who, 1, MAX_CARRY) ) )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的粽子材料好像不够呢。我需要糯米、猪肉、蓼叶各一份，你去楚国城外找找看吧。\n"ESC"离开",me->get_name()));
        		return;
        	}
        	if( !objectp( item_dw2 = present("切好的猪肉", who, 1, MAX_CARRY) ) )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的粽子材料好像不够呢。我需要糯米、猪肉、蓼叶各一份，你去楚国城外找找看吧。\n"ESC"离开",me->get_name()));
        		return;
        	}
        	if( !objectp( item_dw3 = present("蓼叶", who, 1, MAX_CARRY) ) )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的粽子材料好像不够呢。我需要糯米、猪肉、蓼叶各一份，你去楚国城外找找看吧。\n"ESC"离开",me->get_name()));
        		return;
        	}
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    太好了，这样我就可以做粽子抛进江中，以防屈大人遗体被鱼儿咬坏了。\n"
			ESC"获取奖励\ntalk %x# zzy.3\n"
			ESC"离开",me->get_name(),getoid(me)));
                break;
        case 3:
        	if( !objectp( item_dw1 = present("泡过的糯米", who, 1, MAX_CARRY) ) )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的粽子材料好像不够呢。我需要糯米、猪肉、蓼叶各一份，你去楚国城外找找看吧。\n"ESC"离开",me->get_name()));
        		return;
        	}
        	if( !objectp( item_dw2 = present("切好的猪肉", who, 1, MAX_CARRY) ) )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的粽子材料好像不够呢。我需要糯米、猪肉、蓼叶各一份，你去楚国城外找找看吧。\n"ESC"离开",me->get_name()));
        		return;
        	}
        	if( !objectp( item_dw3 = present("蓼叶", who, 1, MAX_CARRY) ) )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的粽子材料好像不够呢。我需要糯米、猪肉、蓼叶各一份，你去楚国城外找找看吧。\n"ESC"离开",me->get_name()));
        		return;
        	}
		item_dw1->add_amount(-1);
		item_dw2->add_amount(-1);
		item_dw3->add_amount(-1);
		who->add_exp(5000);
                break;
	}
}


