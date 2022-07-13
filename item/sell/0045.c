
#include <equip.h>
#include <effect.h>

inherit TALISMAN;

int get_item_value() {return 5 ;}
int get_item_value_2() {return 5 ;}
int get_item_number() {return 10001078 ;}
int get_item_color() {return 1 ;}

int get_no_repair() {return 1;}

void do_master();
void do_master2();
void do_escort();
void do_escort2();
void do_marry();
void do_banditi();
void do_banditi2();
void do_criminal();
void do_criminal2();
void do_robber();
void do_robber2();

// 函数：法宝识别
int get_talisman_type() { return 13; }
//不是完成任务时不掉耐久度
int add_lasting( int time )
{
	if ( time < 0 && time > -100 )
		return 0;
	return ::add_lasting(time);	
}

// 函数：构造处理
void create()
{
        object me = this_object();

        set_name( "Mãn Thiên Quá Hải Phù" );
        set_picid_1(3453);
        set_picid_2(3453);
        set_value(50);
	//	set_save("knb2",5);
        set_max_lasting(2000);
        set_2( "use", ([
                "master"        : (: do_master :),
                "master2"       : (: do_master2 :),
                "escort"	: (: do_escort :),
                "escort2"	: (: do_escort2 :),
                "marry"        	: (: do_marry :),
                "banditi"	: (: do_banditi :),
                "banditi2"	: (: do_banditi2 :),                
                "criminal"	: (: do_criminal :),
                "criminal2"	: (: do_criminal2 :),                  
                "robber"	: (: do_robber :),
                "robber2"	: (: do_robber2 :),                  
        ]));	
        setup();

}

// 函数：获取描述
string get_desc() 
{ 
        return "Tương truyền đây là loại pháp bảo mà Thần Hành Lão Quân sử dụng. \nSau khi trang bị vật phẩm này, có thể xoá bỏ ngăn cách thời gian của nhiệm vụ, \ntừ đó có thể nâng cao hiệu suất nhiệm vụ của người chơi.";
}

void do_master()
{
	object me, item;
	me = this_player();
	item = this_object();
	__FILE__->do_master_callout(me , item);	
}

void do_master_callout(object me, object item)
{
	me->set_save_2("mastertask.begintime", 0);
	item->add_lasting(-100);
	if (item->get_lasting()<100) 
	{
		item->remove_from_user();
		destruct(item);
		USER_INVENTORY_D->send_lasting_tips(me);
	}	
	"/sys/task/master"->task_giveup(me);
	if (!item) send_user(me, "%c%s", '!', "\"Mãn Thiên Quá Hải Phù\" đã sử dụng, hãy bổ sung sau !");
}

void do_master2()
{
	object me, item;
	me = this_player();
	item = this_object();
	__FILE__->do_master2_callout(me , item);	
}

void do_master2_callout(object me, object item)
{
	me->delete_save_2("master.questtime");
	"/sys/task/master"->clear_task(me, 0);
	item->add_lasting(-100);
	if (item->get_lasting()<100) 
	{
		item->remove_from_user();
		destruct(item);
		USER_INVENTORY_D->send_lasting_tips(me);
	}
	if (!item) send_user(me, "%c%s", '!', "\"Mãn Thiên Quá Hải Phù\" đã sử dụng, hãy bổ sung sau !");
}

void do_escort()
{
	object me, item;
	me = this_player();
	item = this_object();
	__FILE__->do_escort_callout(me , item);	
}

void do_escort_callout(object me, object item)
{
	me->delete_quest("escort.time");
	me->delete_quest("escort.quest");
	item->add_lasting(-100);
	if (item->get_lasting()<100) 
	{
		item->remove_from_user();
		destruct(item);
		USER_INVENTORY_D->send_lasting_tips(me);
	}	
	"/sys/task/escort"->task_giveup(me);
	if (!item) send_user(me, "%c%s", '!', "\"Mãn Thiên Quá Hải Phù\" đã sử dụng, hãy bổ sung sau !");
}

void do_escort2()
{
	object me, item;
	me = this_player();
	item = this_object();
	__FILE__->do_escort2_callout(me , item);	
}

void do_escort2_callout(object me, object item)
{
	me->delete_quest("escort.quest");
	item->add_lasting(-100);
	if (item->get_lasting()<100) 
	{
		item->remove_from_user();
		destruct(item);
		USER_INVENTORY_D->send_lasting_tips(me);
	}	
	"/sys/task/escort"->task_giveup(me);
	if (!item) send_user(me, "%c%s", '!', "\"Mãn Thiên Quá Hải Phù\" đã sử dụng, hãy bổ sung sau !");
}

void do_marry()
{
	object me, item;
	me = this_player();
	item = this_object();
	__FILE__->do_marry_callout(me , item);	
}

void do_marry_callout(object me, object item)
{
	me->delete_save("marrytask.time");
	item->add_lasting(-100);
	if (item->get_lasting()<100) 
	{
		item->remove_from_user();
		destruct(item);
		USER_INVENTORY_D->send_lasting_tips(me);
	}	
	if (!item) send_user(me, "%c%s", '!', "\"Mãn Thiên Quá Hải Phù\" đã sử dụng, hãy bổ sung sau !");
}

void do_banditi()
{
	object me, item;
	me = this_player();
	item = this_object();
	__FILE__->do_banditi_callout(me , item);	
}

void do_banditi_callout(object me, object item)
{
	me->delete_task("banditi_time");
	item->add_lasting(-100);
	if (item->get_lasting()<100) 
	{
		item->remove_from_user();
		destruct(item);
		USER_INVENTORY_D->send_lasting_tips(me);
	}	
	if (!item) send_user(me, "%c%s", '!', "\"Mãn Thiên Quá Hải Phù\" đã sử dụng, hãy bổ sung sau !");
}

void do_banditi2()
{
	object me, item;
	me = this_player();
	item = this_object();
	__FILE__->do_banditi2_callout(me , item);	
}

void do_banditi2_callout(object me, object item)
{
	me->delete_task("banditi_time");
	"/sys/task/banditi"->task_giveup(me, 1);
	item->add_lasting(-100);
	if (item->get_lasting()<100) 
	{
		item->remove_from_user();
		destruct(item);
		USER_INVENTORY_D->send_lasting_tips(me);
	}	
	if (!item) send_user(me, "%c%s", '!', "\"Mãn Thiên Quá Hải Phù\" đã sử dụng, hãy bổ sung sau !");
}

void do_criminal()
{
	object me, item;
	me = this_player();
	item = this_object();
	__FILE__->do_criminal_callout(me , item);	
}

void do_criminal_callout(object me, object item)
{
	me->delete_task("criminal.time");
	item->add_lasting(-100);
	if (item->get_lasting()<100) 
	{
		item->remove_from_user();
		destruct(item);
		USER_INVENTORY_D->send_lasting_tips(me);
	}	
	if (!item) send_user(me, "%c%s", '!', "\"Mãn Thiên Quá Hải Phù\" đã sử dụng, hãy bổ sung sau !");
}

void do_criminal2()
{
	object me, item;
	me = this_player();
	item = this_object();
	__FILE__->do_criminal2_callout(me , item);	
}

void do_criminal2_callout(object me, object item)
{
	me->delete_task("criminal.time");
	"npc/00/8006"->task_giveup(me, 1);
	item->add_lasting(-100);
	if (item->get_lasting()<100) 
	{
		item->remove_from_user();
		destruct(item);
		USER_INVENTORY_D->send_lasting_tips(me);
	}	
	if (!item) send_user(me, "%c%s", '!', "\"Mãn Thiên Quá Hải Phù\" đã sử dụng, hãy bổ sung sau !");
}

void do_robber()
{
	object me, item;
	me = this_player();
	item = this_object();
	__FILE__->do_robber_callout(me , item);	
}

void do_robber_callout(object me, object item)
{
	me->delete_task("robber.time");
	item->add_lasting(-100);
	if (item->get_lasting()<100) 
	{
		item->remove_from_user();
		destruct(item);
		USER_INVENTORY_D->send_lasting_tips(me);
	}	
	if (!item) send_user(me, "%c%s", '!', "\"Mãn Thiên Quá Hải Phù\" đã sử dụng, hãy bổ sung sau !");
}

void do_robber2()
{
	object me, item;
	me = this_player();
	item = this_object();
	__FILE__->do_robber2_callout(me , item);	
}

void do_robber2_callout(object me, object item)
{
	me->delete_task("robber.time");
	"/sys/task/robber"->task_giveup(me, 1);
	item->add_lasting(-100);
	if (item->get_lasting()<100) 
	{
		item->remove_from_user();
		destruct(item);
		USER_INVENTORY_D->send_lasting_tips(me);
	}	
	if (!item) send_user(me, "%c%s", '!', "\"Mãn Thiên Quá Hải Phù\" đã sử dụng, hãy bổ sung sau !");
}