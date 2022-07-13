
#include <npc.h>
#include <ansi.h>
#include <map.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 6009; } 

// 函数：构造处理
void create()
{
        set_name( "Bách Hợp Tiên Tử" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
//        set("level", 1);
//        set("legend", ({1}));
	set("mpLegend",([0:({1,}),]));
        setup();     
}

void do_look( object who )
{
        int status;
        object me = this_object();
        status = who->get("xiannv.status");
        send_user( who, "%c%c%w%s", ':', 4, 6009,
        	sprintf("%s：\n    太好了～没想到又来了一位新朋友～要喝杯茶吗？还是想品尝一下我亲手作的糕点呢~嘻嘻，开个玩笑。\n    还没自我介绍呢～我叫百合仙子，是仙界的指引仙子，我想你身上一定肩负了神圣的使命吧。在这个岛上，除了我之外，还有四位知识渊博的神仙，你有什么不懂的可以直接和他们聊聊。\n"
                ESC "继续\ntalk %x# welcome.1\n"
                ESC "关闭\nCLOSE\n", me->get_name(), getoid(me) ) );
}

void do_welcome( string arg )
{
        object map, map2, who, me, npc, item,*nEquip;
        int flag, status, z, z2, x, y, p;
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, result;
        me = this_object();
        who = this_player();
        flag = to_int(arg);
        status = who->get("xiannv.status");
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
                send_user( who, "%c%c%w%s", ':', 4, 6009,
                        sprintf("%s：\n    不要认为仙界就非常的神秘，其实也和凡间一样，每个人都有自己明确的分工。\n    大伯公是主管仙界的财政，他的身份其实就相当于凡间的当铺老板哦。\n    文曲星不用我说你也知道他是干嘛的吧，你可以去找他谈谈，关于"HIR"《战国Ⅱonline》"NOR"界面的知识他可全懂。\n    瑶姬仙子是个人见人爱的可人儿，她可是外交官哦，交谈技巧你得向她多学习学习。\n    武曲星最了不起了，他武艺高超，一直保护着我们仙灵岛的安全，有兴趣的话你可以向他讨教讨教！\n"
                	ESC "继续\ntalk %x# welcome.2\n"
                	ESC "关闭\nCLOSE\n", me->get_name(), getoid(me) ) );
                break;
        case 2:
                cmd1 = sprintf("talk %x# welcome.3", getoid(me));
                cmd2 = sprintf("talk %x# welcome.5", getoid(me));
                cmd3 = "CLOSE";
                result = sprintf("%s：\n    我呢，算是一座小小的桥梁，负责仙灵岛与凡间的沟通。我还有一个小小的秘密哦，在我没有成为仙子的时候，凡间有一位神仙爷爷非常照顾我，我来到仙灵岛后一直都很挂念他，如果你到了凡间，请一定把这封信交给他。\n", me->get_name() );
                if (!who->get_legend(TASK_NEWBIE_00, 0)) result += sprintf( ESC "送信使命\n%s\n", cmd1 );

                result += sprintf(ESC "回到凡间\n%s\n"
                        ESC "关闭\n%s\n",  cmd2, cmd3 );
                send_user( who, "%c%c%w%s", ':', 4, 6009, result );
                break;
        case 3:
        	if (who->get_legend(TASK_NEWBIE_00, 1))  return;
                send_user( who, "%c%c%w%s", ':', 4, 6009,
                        sprintf("%s：\n    你愿意给我送信了？真是太好了！爷爷已经很久都没有我的消息了，肯定非常着急，你能给我把信送到的话，爷爷会给你奖励的。我会在仙灵岛祝福你！爷爷就在新手村的村口。从天坛的东南方向一直往前走，你就可以看到神仙爷爷了。\n"
                	ESC "领取任务\ntalk %x# welcome.4\n"
                	ESC "离开\nCLOSE\n", me->get_name(), getoid(me) ) );
                break;              
        case 4:
                send_user( who, "%c%d", ':', 0);
                if (!who->get_legend(TASK_NEWBIE_00, 1))
                {                                           
                        item = new ("/item/01/0001");    // 介绍信
                        if (item)
                        {
                                if( USER_INVENTORY_D->can_carry(who, item)  >=1 )
                                {
                                        p =item->move(who, -1);
                                        item->add_to_user(p);
		                        send_user( who, "%c%s", '!', "你领取了送信使命的任务！");
		                        who->set_legend(TASK_NEWBIE_00, 1);                                         
					send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_00,"仙灵岛" );
					send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_00,1,"送信使命" );		                        
                                }   
                                else     
                                {
                                	send_user( who, "%c%s", '!', "您身上没有空位！");
                                	destruct(item);
				}                                	
                        }        
                }  
                break;
        case 5:
                cmd1 = sprintf("talk %x# welcome.6", getoid(me));
                cmd2 = "CLOSE";
                result = sprintf("%s：\n    这样啊……没想到这么快就要分别了，但是一旦你离开了这个仙界，你以后就再也不能回来了。你真的确定要如此吗？\n"
                        ESC "确定\n%s\n"
                        ESC "关闭\n%s\n", me->get_name(), cmd1, cmd2 );        
                send_user( who, "%c%c%w%s", ':', 3, 6009, result );   
                break;                
        case 6:     
        	nEquip = who->get_all_equip();                                                                                    
                if ( sizeof(nEquip) == 0 || !nEquip[FAMILY_POSITION] ) 
                {          

			item = new("/item/09/0908");
			if ( !item )
				return ;
			if ( !who->restore_equip(item) )
			{
				destruct(item);
				return ;
			}
			tell_user(who,"你得到了新手信物: "HIY+item->get_name());
		} 
                z2 = get_z(who);
                map2 = get_map_object(z2);                                

                MAP_D->add_to_void(who);    // 移入 VOID 场景  // 新手村！
                who->delete_save_2("Newbie.Login"); 
                NEWBIE->destruct_virtual_map(map2, z2);                
                break;
        }
}