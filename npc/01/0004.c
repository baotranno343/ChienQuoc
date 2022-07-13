
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5503; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("生活技能帮助使者");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
        int id = getoid( this_object() );
        
	send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    你好！在这里可以了解生活技能的相关介绍。你想知道什么？\n"ESC"生活技能是什么？\ntalk %x# welcome.1\n"ESC"多少级可以学这些生活技能？\ntalk %x# welcome.2\n"ESC"如何删除学错的生活技能？\ntalk %x# welcome.3\n"ESC"生活技能的升级是如何的？\ntalk %x# welcome.4\n"ESC"如何采集资源？\ntalk %x# welcome.5\n"ESC"离开",id,id,id,id,id));

}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,p,id;
	object who,item;
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        	case 0:
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf(me->get_name() + "：\n    你好！在这里可以了解生活技能的相关介绍。你想知道什么？\n"ESC"生活技能是什么？\ntalk %x# welcome.1\n"ESC"多少级可以学这些生活技能？\ntalk %x# welcome.2\n"ESC"如何删除学错的生活技能？\ntalk %x# welcome.3\n"ESC"生活技能的升级是如何的？\ntalk %x# welcome.4\n"ESC"如何采集资源？\ntalk %x# welcome.5\n"ESC"离开",id,id,id,id,id));
        		break;
        	case 1:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    生活技能属于辅助角色的技能。可以让你学到如何制造武器，防具，饰品，药剂，有趣的神秘物品等等。每个角色都可以学习2种主要生活技能和酒食辅助技能。\n"ESC"有哪些生活技能？\ntalk %x# welcome.6\n"ESC"返回\ntalk %x# welcome.0\n"ESC"离开",id,id));
        		break;	
        	case 2:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    当人物等级达到10级就可以去各个国家学习生活技能。\n"ESC"有哪些生活技能？\ntalk %x# welcome.7\n"ESC"返回\ntalk %x# welcome.0\n"ESC"离开",id,id));
        		break;	        	
        	case 3:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    如果你觉得生活技能学错了，可以到周国找到申公豹把生活技能删除。不过你之前所学到的制造配方，升级所用过的经验、潜能、金钱都会消失并且不会返还。所以选择生活技能要慎重。\n"ESC"有哪些生活技能？\ntalk %x# welcome.8\n"ESC"返回\ntalk %x# welcome.0\n"ESC"离开",id,id));
        		break;
        	case 4:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    升级生活技能你必须回去你学习生活技能的NPC，跟他对话选择所需的生活技能就可以升级。你可以使用经验或者潜能来升级生活技能。生活技能有2个技能指标。一个是等级，一个是熟练度。生活技能满级是120级。\n"ESC"有哪些生活技能？\ntalk %x# welcome.9\n"ESC"什么是生活技能的等级？\ntalk %x# welcome.41\n"ESC"什么是生活技能的熟练度？\ntalk %x# welcome.42\n"ESC"返回\ntalk %x# welcome.0\n"ESC"离开",id,id,id,id));
        		break;
        	case 5:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    生活技能的资源有很多种，包括矿石、布料、草药、玉石、食材。矿石可以通过矿冶技能在野外采集。布料可以杀死怪物后得到。草药可以通过药师技能在野外采集。玉石需要石刻技能分解蓝色或者金色的装备获得。食材可以通过酒食技能在野外采集或者杀死怪物后获得。\n"ESC"返回\ntalk %x# welcome.0\n"ESC"离开",id));
        		break;
        	case 9:
        		p += 1;
        	case 8:
        		p += 1;
        	case 7:
        		p += 1;
        	case 6:
        		p += 1;
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf(me->get_name() + "：\n    生活技能有：铁匠、矿冶、裁缝、炼丹、药师、石刻、机关。辅助性的生活技能是酒食。一个人物角色可以学习2种主要生活技能和一种辅助性的生活技能。比如可以学铁匠和矿冶还有酒食。\n"ESC"什么是铁匠？\ntalk %x# welcome.61\n"ESC"什么是矿冶？\ntalk %x# welcome.62\n"ESC"什么是裁缝？\ntalk %x# welcome.63\n"ESC"什么是炼丹？\ntalk %x# welcome.64\n"ESC"什么是药师？\ntalk %x# welcome.65\n"ESC"什么是石刻？\ntalk %x# welcome.66\n"ESC"什么是机关？\ntalk %x# welcome.67\n"ESC"什么是酒食？\ntalk %x# welcome.68\n"ESC"返回\ntalk %x# welcome.%d\n"ESC"离开",id,id,id,id,id,id,id,id,id,p));
        		break;
        	case 41:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    生活技能的等级是衡量人物此生活技能达到的等级，是用来学习配方所需要的。如果等级不够，你是学习不到配方，也制造不了物品。\n"ESC"返回\ntalk %x# welcome.4\n"ESC"离开",id));
        		break;
        	case 42:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    生活技能的熟练度是让玩家可以真正制造或者采集到物品的数值。熟练度依靠制造物品，采集物品来提升。\n"ESC"返回\ntalk %x# welcome.4\n"ESC"离开",id));
        		break;
        	case 61:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    铁匠是可以制造所有门派的武器。铁匠可以在秦国找秦国工匠学习技能， 铁匠的工具是铁锤，可以在秦国杂货店老板处购买。铁匠需要的原料是矿石。需要矿冶技能去采集和熔炼成矿锭才能提供给铁匠使用。\n"ESC"返回\ntalk %x# welcome.6\n"ESC"离开",id));
        		break;        			
        	case 62:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    矿冶就是采矿和冶金。矿冶包括2个技能，一个是矿石的采集，一个矿石的冶炼。我们在野外采集回来的是矿石的原矿，要进一步进行冶炼才能真正提供给铁匠、机关使用。矿冶可以在燕国找燕国工匠处学习技能，矿冶所需要的工具是锄头可以在燕国的杂货店老板处购买。矿石可以在各地的修理店老板附近熔炼成矿锭。\n"ESC"返回\ntalk %x# welcome.6\n"ESC"离开",id));
        		break; 
        	case 63:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    裁缝是制造各种防具的，包括了衣服、帽子、鞋子。裁缝可以在韩国找韩国工匠学习技能， 裁缝的工具是绣花针，可以在韩国杂货店老板处购买。 裁缝需要的原料是布和一些线。布料可以从怪物身上获得，而线可以在任何的饰品店老板处购买。\n"ESC"返回\ntalk %x# welcome.6\n"ESC"离开",id));
        		break; 
        	case 64:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    炼丹就是制作一些补药，可以补充气血、法力。有些丹药还可以在一定时间内提高人物的属性。炼丹可以在魏国找魏国工匠学习技能，炼丹的工具丹炉可以在魏国的杂货店老板处购买。炼丹需要的原料是草药，一般由药师来采集提供。\n"ESC"返回\ntalk %x# welcome.6\n"ESC"离开",id));
        		break; 
        	case 65:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    药师就是草药的采集。采集到的草药可以提供给炼丹使用。药师可以在赵国找赵国工匠学习技能。药师采集草药的工具可以在赵国杂货店老板处购买。草药会在野外的一些地方随机刷新。\n"ESC"返回\ntalk %x# welcome.6\n"ESC"离开",id));
        		break;
        	case 66:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    石刻包括了3个子技能，项链制造、装备分解、道具镶嵌。玩家可以使用这3个技能。石刻可以在楚国找楚国工匠学习技能。石刻需要的工具雕刻刀可以在楚国杂货店老板处购买。石刻所需要的原料是靠装备分解来获得玉石、宝石和木料。凡是蓝色、金色的物品都可以找到修理店老板来分解装备获得玉石或宝石和木料。某些国家的流浪商人也出售一些原料。道具镶嵌就使用这些分解的道德玉石来制造一些对装备有增强作用的制品。\n"ESC"返回\ntalk %x# welcome.6\n"ESC"离开",id));
        		break;
        	case 67:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    机关是做一些诸如炸弹、机械小宠物、有特殊用途的道具。属于比较好玩，有娱乐性的的生活技能。机关可以在齐国找齐国工匠学习技能。机关需要的工具铁锤可以在齐国的杂货店老板处购买。\n"ESC"返回\ntalk %x# welcome.6\n"ESC"离开",id));
        		break;
        	case 68:
			send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    酒食可以让玩家制作各种各样的食物与酒。这些都是可以在战斗后使用的道具，可以恢复气血和法力。酒食属于辅助技能，任何学了2个主要生活技能的人物都可以再学酒食技能。酒食可以在周国找周国大厨学习技能。酒食需要工具镰刀来采集食材也可以杀怪物得到食材。\n"ESC"返回\ntalk %x# welcome.6\n"ESC"离开",id));
        		break;        		
        }	
}