
#include <npc.h>
#include <cmd.h>
#include <ansi.h>

inherit SAVE_F;

inherit OFFICER;
static string *nCard = ({"0010","0011","0050","0051","0052","0053","0101","0102","0150",
			"0151","0152","0200","0201","0202","0250","0251","0252","8011",
			"8010","0300","0301","0302","0303","0304","0350","0351","0352",
			"0400","0401","0402","0450","0500","0502","0550","0551","0552",
		});	//"0100"

#define SAVE_FILE       "data/city/diamond" SAVE_EXTENSION

// 函数：小贩识别
int is_seller() { return 2; }

// 函数：获取人物造型
int get_char_picid() { return 5420; }

// 重设商品
void reset_good();

// 函数：构造处理
void create()
{
        set_name("Thương Nhân Thần Bí");
	set_save("diamond_count", 100);
        setup();
        restore();
        reset_good();
        if (get_save("diamond_count")==0)
        {
        	set_save("diamond_count", 100);
        	save();
        }
}


// 函数：复位处理
void reset()
{
        string buf;

        if ( gone_time(get("reset_good")) < 60*29 )
        	return ;
//log_file("reset_good.txt",sprintf("%s 变身卡\n",short_time()));

        reset_good();
        if ( MAIN_D->get_host_type() != 4 )
        	buf = "传闻周国的神秘商人又有了一批新的变身卡片和晶石出售，大家快去看看啊～！";
	else
        	buf = "传闻周国的神秘商人又有了一批晶石出售，大家快去看看啊～！";
        CHAT_D->rumor_channel( 0, CHAT+buf );
}

void reset_good()
{
	int i,size;
	string *nTmp=({}),cTmp;
        object me = this_object();
        string * diamond = ({ "9301", "9302", "9303", "9304", "9305", "9306", "9307", "9308", "9309", "9310",  });
        string * diamondgood = ({ });
        size = sizeof(diamond);
        for (i=0;i<size;i++)
        {
        	if (me->get_save_2("diamond."+diamond[i])>=105)
        		me->add_save_2("diamond."+diamond[i], -5);
        	else
        		me->set_save_2("diamond."+diamond[i], 100);
        }
        set("reset_good",time());
        size = sizeof(nCard);
	while(sizeof(nTmp)<3)
	{
		cTmp = nCard[random(size)];
		if ( member_array(cTmp,nTmp) != -1 )
			continue;
		nTmp += ({ cTmp });
	}
	while(sizeof(diamondgood)<3)
	{
		cTmp = diamond[random(sizeof(diamond))];
		diamondgood += ({ cTmp });
		diamond -= ({ cTmp });
	}
	if (MAIN_D->get_host_type()==4 || MAIN_D->get_host_type()==2)
	{
		me->set_2( "good", ([
		        "01" : "item/54/"+nTmp[0],
		        "02" : "item/54/"+nTmp[1],
		        "03" : "item/54/"+nTmp[2],
		        "04" : "item/93/"+diamondgood[0],
		        "05" : "item/93/"+diamondgood[1],
		        "06" : "item/93/"+diamondgood[2],
		]) );
	        me->set_2( "list", ([
	                "01" : 5,
	                "02" : 5,
			"03" : 5,
	                "04" : 5,
	                "05" : 5,
			"06" : 5,
	        ]) );
	}
	else
	{
		me->set_2( "good", ([
		        "01" : "item/54/"+nTmp[0],
		        "02" : "item/54/"+nTmp[1],
		        "03" : "item/54/"+nTmp[2],
		        "04" : "item/93/"+diamondgood[0],
		        "05" : "item/93/"+diamondgood[1],
		        "06" : "item/93/"+diamondgood[2],
		        "07" : "/item/sell/1026",
		        "08" : "/item/sell/1027",
		        "09" : "/item/mop/0200",
		        "10" : "/item/mop/0201",
		        "11" : "/item/mop/0202",	        		        
		]) );
	        me->set_2( "list", ([
	                "01" : 5,
	                "02" : 5,
			"03" : 5,
	                "04" : 5,
	                "05" : 5,
			"06" : 5,
	                "07" : 999,
			"08" : 999,
	                "09" : 9999,
			"10" : 9999,			
			"11" : 9999,	
	        ]) );
	}
        me->save();
}

void do_look( object who )
{
	object npc=this_object();
	if ( sizeof(npc->get_2("good")) != 0 )
	{
	        send_user( who, "%c%c%w%s", ':', 3, npc->get_char_picid(),
	                sprintf("%s：\n    嘿嘿，只有有缘人才能找到我，既然你能够这么快的来到我这里，看来你就是我的有缘人，我身上的东西，你尽管挑吧！对待有缘人，我从不吝啬。"+"/quest/word"->get_normal_word(npc)+"\n"
	                        ESC "交易\nlist %x#\n"
	                        ESC "离开\nCLOSE\n", npc->get_name(), getoid(npc) ) );
	}
	else
	{
	        send_user( who, "%c%c%w%s", ':', 3, npc->get_char_picid(),
	                sprintf("%s：\n    唉，你晚来了一步，刚刚我的最后一件收藏品已经被别人买走了，看来我们的缘分还未到，别心急，慢慢等待吧，总有一天缘分会到来的。"+"/quest/word"->get_normal_word(npc)+"\n"
	                        ESC "离开\nCLOSE\n", npc->get_name(), getoid(npc) ) );
	}

}