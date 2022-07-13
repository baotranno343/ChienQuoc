
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 5405; }

// 有自己的do_look函数
int is_self_look() { return 1; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Trang Phục");
	set_real_name("Thành Khoái Chỳ");
        set_city_name("Tần Quốc");

        set_2( "good", ([
                "01" : "/item/60/6020",
                "02" : "/item/60/6030",
                "03" : "/item/60/6040",
                "04" : "/item/60/6050",
                "05" : "/item/60/6060",
                "06" : "/item/61/6020",
                "07" : "/item/61/6030",
                "08" : "/item/61/6040",
                "09" : "/item/65/6020",
                "10" : "/item/65/6030",
                "11" : "/item/65/6040",
                "12" : "/item/66/6020",
                "13" : "/item/66/6030",
                "14" : "/item/66/6040",

        ]) );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	result = sprintf("%s：\n    "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	if ( (who->get_level() >= 65 && !who->get_legend(TASK_2_01,1)) || (who->get_legend(TASK_2_01,2) && !who->get_legend(TASK_2_01,3)) )
		result += sprintf(ESC HIY "魂兮归来\ntalk %x# welcome.1\n",getoid(me));
	result += sprintf(ESC "哪里有适合我的装备？\ntalk %x# welcome.99\n", getoid(me) ) ;        	
	result += sprintf( ESC "交易\nlist %x#\n" ESC "我只是随便看看\nCLOSE\n", getoid(me) ) ;        	
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(), result );
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
        	if ( who->get_level() >= 65 && !who->get_legend(TASK_2_01,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你是说若蝉姑娘吗？哎，真是可怜啊……她家搬来王城也有些年头了，与她指腹为婚青梅竹马的唐家小伙子名追的，因家中遭逢大变失散多年后来寻她完婚，为若蝉姑娘双亲不允，将之赶出。若蝉姑娘郁郁不乐，又不肯嫁与他人。过了一年那唐追又来，仍为不允。他走后若蝉姑娘就此痴痴呆呆，不言不语。我听说是那唐追学了些邪术，拘了姑娘三魂七魄之中三魂六魄去了，因而才弄到这样。你可以帮忙去替若蝉姑娘回魂么……听说那唐追如今在骊山陵墓之中为恶，此去十分危险，但别无他法，唉！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_2_01,2) && !who->get_legend(TASK_2_01,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你对若蝉姑娘念咒“魂兮归来”。\n"ESC"离开", me->get_name(),));

        	break;
        case 2:
        	if ( who->get_level() >= 65 && !who->get_legend(TASK_2_01,1) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_2_01,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,103,"魂兮归来" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"魂兮归来");
		}
        	break;
	default:
	case 99:
        	"/npc/base/0005"->do_welcome2(me, "99");
		break;
	}
	
}