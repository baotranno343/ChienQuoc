
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 9957; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("合服补偿使者");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));

        setup();
}

void do_look( object who )
{
	object me = this_object();
	string tmp = sprintf(ESC"领取奖励\ntalk %x# welcome.1\n",getoid(me));
	send_user(who,"%c%s",':',sprintf( "%s：\n    因为合服的关系，我们特地为玩家作出了补偿。只要等级满足了"HIR "60级"NOR"的玩家都可以来我这里领取一份礼物。从"HIR"3月23日至28日"NOR"我都会在这里。大家可千万不要错过这次机会。\n", get_name()) + tmp + ESC"离开");
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,i,size,p;
        object who,item;     
	string name1;
	string *giftname = ({ "0104", "0109", "0111", "0121", "0131", "0141", "0151", "0161", "0202", "0401", "0402", "0403", "0211", "0212", "0316", "0317", "0319", "0221", "0231", "0222", "0325", "0329", "0241", "0251", "0242", "0348", "0349", "0261", "0363", "0364", "0365", "0368", "0271", "0413", "0414", "0417", "0418", "0421", "0422", "0423", "0424", "0425", "0281", "0501", "0511", "0531", "0591", });
	string *file = ({"0006","0007","0009","0012",});
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 60 && who->get_save_2("receive.prize") != 1 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这是我一点小小的心意，收下吧。希望能给予您些帮助。\n"ESC"接受奖品\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_save_2("receive.prize") == 1 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你之前不是已经领取过奖品了吗？怎么又问我拿了？贪心可不是一件好事情。\n"ESC"离开", me->get_name()));
		else if ( who->get_level() < 60 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你的等级还不够"HIR "60级"NOR"吧？十分抱歉我不能赠送任务奖励给你。好好努力吧，从"HIR"3月23日至28日"NOR"我都待在这里的。\n"ESC"离开", me->get_name()));
        	break;
	case 2:
        	if ( who->get_level() >= 60 && who->get_save_2("receive.prize") != 1 )
        	{
			if(USER_INVENTORY_D->count_empty_carry(who) < 7 )
			{
			        send_user(who,"%c%s",';',"你身上的道具空间不太足够，腾出7个空位置后再来吧。");
        			return;
			}

			size = sizeof(giftname);
			name1 = giftname[random(size)];
			item = new (sprintf("/item/95/%s.c", name1));
			p =item->move(who, -1);
			item->add_to_user(p);

        		item = new("/item/sell/0002");
        		p = item->move(who,-1);
        		item->add_to_user(p);

        		item = new("/item/sell/0004");
        		p = item->move(who,-1);
        		item->add_to_user(p);

                        for (i=0;i<4;i++)
                        {
				item = new (sprintf("/item/sell/%s.c", file[i]));    
				item->set_amount(5);
                        	if ( item )
				{	
					p = item->move(who,-1);
					item->add_to_user(p);			
				}	
			}
        		who->set_save_2("receive.prize",1);
        	}
        	break;  
        }
}