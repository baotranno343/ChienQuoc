
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
object *Party_npc = ({});;
// 函数：小贩识别
int is_seller() { return 2; }


// 函数：获取人物造型
int get_char_picid() { return 5420; }

void accept_task(string arg);
void do_qixi(string arg);
// 重设商品2
void reset_good2();

// 函数：构造处理
void create()
{
        set_name("云游商人");

        set_2( "talk", ([
                "accept_task"          : (: accept_task :),
                "qixi"                 : (: do_qixi :),	
        ]));

	set_save("diamond_count", 100);
        setup();
        restore();
        reset_good2();
        if (get_save("diamond_count")==0)
        {
        	set_save("diamond_count", 100);
        	save();
        }

}

// 函数：对话处理
void do_look( object who )
{
	COLLECT_FILE->do_look(who,this_object());
}


// 函数：复位处理
void reset() 
{
        int p,z,x,y;
        string buf;
        object map;
//        if( p = XY_D->get_seller_point( IS_CHAR_BLOCK ) )
	p = XY_D->get_seller_point_2();
	z = p / 1000000;
	x = p % 1000000 / 1000;
	y = p % 1000;
	map = get_map_object(z);
	buf = sprintf("听说云游商人将在大约五分钟后带着神秘的宝物出现在"HIR"%s(%d,%d)"NOR"一带，嘿嘿～～一般人我还不告诉他哦！",map->get_name(),x-7,y-7);
	CHAT_D->sys_channel( 0, CHAT+buf );
	CHAT_D->sys_channel( 0, CHAT+buf );
	CHAT_D->sys_channel( 0, CHAT+buf );
	call_out( "reset_2", 240+random(120), p, x, y, z );

/*        if( p = XY_D->get_seller_point_2() )
        {        	
                this_object()->add_to_scene(z=p / 1000000, ( p % 1000000 ) / 1000, p % 1000, 3);
                if( !objectp( map = get_map_object(z) ) || !map->is_scene() ) return;
                TASK_MASTER_D->set_seller_locate(p);
               
                switch(random(3))
                {
                	case 0:
                		buf = "听说百年难得一见，专售宝物的云游商人在%s出现了。";
                		break;
                	case 1:
                		buf = "云游商人果然是来无影去无踪，他现在又云游到%s了。";
                		break;
			default:
				buf = "云游商人好象出现在%s了，嘘，一般人我还不告诉他。";
                		break;
                }                		
                buf = sprintf(buf,map->get_name());
	buf = sprintf("听说云游商人将在5分钟后带着神秘的宝物出现在%s（地图）XXX（%d,%d）一带，嘿嘿～～一般人我还不告诉他哦！",


		CHAT_D->sys_channel( 0, CHAT+buf );   
        }*/

//        if ( gone_time(get("reset_good")) < 60*29 )
//        	return ;
//log_file("reset_good.txt",sprintf("%s 变身卡\n",short_time()));

//        reset_good2();
/*        if ( MAIN_D->get_host_type() != 4 )
        	buf = "传闻周国的神秘商人又有了一批新的变身卡片和晶石出售，大家快去看看啊～！";
	else
        	buf = "传闻周国的神秘商人又有了一批晶石出售，大家快去看看啊～！";
        CHAT_D->rumor_channel( 0, CHAT+buf );*/

}


void reset_2(int p,int x,int y,int z)
{
	int i,size;
	object npc;
	for(i=0,size=sizeof(Party_npc);i<size;i++)
	{
		if ( !objectp(Party_npc[i]) )
			continue;
		Party_npc[i]->remove_from_scene();
		destruct(Party_npc[i]);
	}
	Party_npc = ({});
	this_object()->add_to_scene(z,x+random(14),y+random(14));
	for (i=0;i<7;i++)
	{
		npc=new("npc/task/8808_f");
		npc->add_to_scene(z,x+random(14),y+random(14));
		Party_npc += ({ npc });
	}
	log_file("yunyou.txt",sprintf("云游在%s ，刷到%d(%d,%d)附近。 \n",short_time(),z,x,y));
	TASK_MASTER_D->set_seller_locate(p);
	reset_good2();
}
/*void reset_good()
{
        object me = this_object();
        int * stuff = ({ 24, 42, 54, 241, 272, 273, 274, 275, 276, });
        int size;
	size = sizeof(stuff);
	if (MAIN_D->get_host_type()==4)	
	        me->set_2( "good", ([
	                "03" : COLLECT_FILE->get_collect_file(),
	                "04" : COLLECT_FILE->get_collect_file(),
	                "05" : COLLECT_FILE->get_collect_file(),
	                "06" : COLLECT_FILE->get_collect_file(),
	                "07" : COLLECT_FILE->get_collect_file(),
	                "08" : COLLECT_FILE->get_collect_file(),                	
	                "09" : "/sys/item/product"->get_random_sell_product(),
	                "10" : sprintf("/item/stuff/%04d", stuff[random(size)]),
	//                "11" : "item/44/4404",
	        ]) );
	else
	        me->set_2( "good", ([
	                "03" : COLLECT_FILE->get_collect_file(),
	                "04" : COLLECT_FILE->get_collect_file(),
	                "05" : COLLECT_FILE->get_collect_file(),
	                "06" : COLLECT_FILE->get_collect_file(),
	                "07" : COLLECT_FILE->get_collect_file(),
	                "08" : COLLECT_FILE->get_collect_file(),                	
	                "09" : "/sys/item/product"->get_random_sell_product(),
	                "10" : sprintf("/item/stuff/%04d", stuff[random(size)]),
	                "11" : "item/44/4404",
	        ]) );		       

        me->set_2( "list", ([
                "03" : 1,
                "04" : 1,
		"05" : 1,
                "06" : 1,
		"07" : 1,
                "08" : 1,                
                "09" : 1,   
                "10" : 60,   
                "11" : 5,   
        ]) );
        me->set_2( "price", ([
                "11" : 250000,   
        ]) );
}*/

void reset_good2()
{
	int i,size;
	string *nTmp=({}),cTmp;
        object me = this_object();

        int * stuff = ({ 24, 42, 54, 241, 272, 273, 274, 275, 276, });
        int size2;



        string * diamond = ({
        	 "9301", "9302", "9303", "9304", "9305", "9306", "9307", "9308", "9309", "9310",  
        	 "9301", "9302", "9307", "9308", "9309", "9306", "9307", "9308", "9309", "9310",  
        	 });
        string * diamondgood = ({ });
        size = sizeof(diamond);
	size2 = sizeof(stuff);
        for (i=0;i<size;i++)
        {
        	if (me->get_save_2("diamond."+diamond[i])>=105)
        		me->add_save_2("diamond."+diamond[i], -5);
        	else
        		me->set_save_2("diamond."+diamond[i], 100);
        }
//        set("reset_good",time());
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

	                "12" : COLLECT_FILE->get_collect_file(),
	                "13" : COLLECT_FILE->get_collect_file(),
	                "14" : COLLECT_FILE->get_collect_file(),
	                "15" : COLLECT_FILE->get_collect_file(),
	                "16" : COLLECT_FILE->get_collect_file(),
	                "17" : COLLECT_FILE->get_collect_file(),                	
	                "18" : "/sys/item/product"->get_random_sell_product(),
	                "19" : sprintf("/item/stuff/%04d", stuff[random(size2)]),
		        "20" : "/item/mop/0200",
		        "21" : "/item/mop/0201",

	        ]) );

	        me->set_2( "list", ([
	                "01" : 5,
	                "02" : 5,
	                "03" : 5,
	                "04" : 5,
	                "05" : 5,
	                "06" : 5,

	                "12" : 1,
	                "13" : 1,
			"14" : 1,
	                "15" : 1,
			"16" : 1,
	                "17" : 1,                
	                "18" : 1,   
	                "19" : 60,   
	                "20" : 9999,   
	                "21" : 9999,   
	        ]) );
	        me->set_2( "price", ([
	                "20" : 150000,   
	                "21" : 250000,   
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

	                "12" : COLLECT_FILE->get_collect_file(),
	                "13" : COLLECT_FILE->get_collect_file(),
	                "14" : COLLECT_FILE->get_collect_file(),
	                "15" : COLLECT_FILE->get_collect_file(),
	                "16" : COLLECT_FILE->get_collect_file(),
	                "17" : COLLECT_FILE->get_collect_file(),                	
	                "18" : "/sys/item/product"->get_random_sell_product(),
	                "19" : sprintf("/item/stuff/%04d", stuff[random(size2)]),
	                "20" : "item/44/4404",

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

	                "12" : 1,
	                "13" : 1,
			"14" : 1,
	                "15" : 1,
			"16" : 1,
	                "17" : 1,                
	                "18" : 1,   
	                "19" : 60,   
	                "20" : 5,   
	        ]) );
	        me->set_2( "price", ([
	                "20" : 250000,   
	        ]) );
	}
        me->save();
}

void accept_task(string arg)
{
	TASK_MASTER_D->accept_task10(this_player(),this_object(),arg);
}

void do_qixi( string arg ) {"sys/party/qixi"->do_qixi3(this_object(),this_player(),arg);}