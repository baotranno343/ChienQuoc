
// 自动生成：/make/npc/make8020

#include <npc.h>
#include <ansi.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5503; }
void do_welcome( string arg );

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
        set_name("Cơ Quan Sư Chu Quốc");
        set_real_name("Cơ quan 1~20");
        set_city_name("Chu Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
	set_skill(0660, 39);
        set_2( "good", ([
                "01" : "/item/product/66001",
                "02" : "/item/product/66002",
                "03" : "/item/product/66003",
                "04" : "/item/product/66004",
                "05" : "/item/product/66005",
                "06" : "/item/product/66006",
                "07" : "/item/product/66056",
        ]) );	
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( who->get_legend(TASK_2_00,20) && !who->get_legend(TASK_2_00,21) && who->get_save("baifang_js_1") != 1)
		tmp = sprintf(ESC HIY "Bái sư\ntalk %x# welcome.1\n",getoid(me));
	tmp += sprintf(ESC"Học tập kỹ năng\nlearn ? %s\n", me->get_char_id());
	tmp += sprintf(ESC"Mua phương pháp pha chế kỹ năng cơ quan từ cấp1-20\nlist %s\n", me->get_char_id());
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( " %s :\n Ở chỗ của ta Ngươi có thể học hết những kỹ năng cơ quan mà Ngươi học ở Nước Tề, nhưng phương pháp pha chế cao cấp thì Ngươi phải mua chỗ những Công tượng của Nước Tề.\n",get_name(),getoid(me)) +
		tmp +
		ESC"Rời khỏi");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( " %s :\n Ở chỗ của ta Ngươi có thể học hết những kỹ năng cơ quan mà Ngươi học ở Nước Tề, nhưng phương pháp pha chế cao cấp thì Ngươi phải mua chỗ những Công tượng của Nước Tề.\n",get_name()));
	
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 1 ); }
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
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
		if ( who->get_legend(TASK_2_00,20) && !who->get_legend(TASK_2_00,21) && who->get_save("baifang_js_1") != 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你是新来的吧。既然大王派你来拜访我们，你可以到处看看，想学习什么技能。能够学习的生活技能除了酒食是不限制的以外，其他只能学习两种哦。如果不小心点错想忘记生活技能的话，可以去找申公豹。\n", me->get_name()));
			who->set_save("baifang_js_1",1);
			USER_TASK_D->send_task_intro(who,2,TID_ZHOUGUO,20);
		}
		if ( who->get_save("baifang_js_0") == 1 && who->get_save("baifang_js_1") == 1 && who->get_save("baifang_js_2") == 1 && who->get_save("baifang_js_2") == 1 && who->get_save("baifang_js_3") == 1 && who->get_save("baifang_js_4") == 1 && who->get_save("baifang_js_5") == 1 && who->get_save("baifang_js_6") == 1 && who->get_save("baifang_js_7") == 1 )
		{
			who->set_legend(TASK_2_00,21);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,20,"访问生活技能师傅(完成)" );
		}
        	break;
        }
}