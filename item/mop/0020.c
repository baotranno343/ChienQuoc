#include <item.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;
//inherit COMBINED;

mapping mpInfo = ([

"金精" : 	([ "prop" : ({1475,1079,1189,1004,0806,0906,1426}), "ski" : ({"高级防盾","高级强攻","高级复生","高级飞行术"})]),
"木精" : 	([ "prop" : ({1475,1079,1189,1004,0806,0906,1426}), "ski" : ({"高级防盾","高级狂攻","高级暴击","高级飞行术"})]),
"水精" : 	([ "prop" : ({1475,1079,1189,1004,0806,0906,1426}), "ski" : ({"高级法盾","福星高照","高级弱点攻击","高级飞行术"})]),
"火精" : 	([ "prop" : ({1330,0876,0991,1194,0970,1070,1240}), "ski" : ({"高级防盾","高级御法","火攻","灭天火法"})]),
"土精" : 	([ "prop" : ({1330,0876,0991,1194,0970,1070,1240}), "ski" : ({"高级御命术","高级御法","落石","飞沙走石"})]),
"龟仙人" : 	([ "prop" : ({1330,0876,0991,1194,0970,1070,1240}), "ski" : ({"高级复生","高级御法","水击","翻云覆雨"})]),

]);

mapping mpPet = (["石狮":0700,"石虎":0701,"刀俑":0850,"弓箭石俑":0853,"枪俑":0852,"剑俑":0851,]);

int get_item_color() {return 1 ;}
int give_pet(object who, string arg);


// 函数：构造处理
void create()
{
        set_name( "无敌宝宝包" );
        set_picid_1(4980);
        set_picid_2(4980);
        set_value(1);
        set_no_give(1);
        set_no_sell(1);
        set_no_drop(1);
        set_record(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "大话战国无敌宝宝包，一次性满足你四个不同的愿望。";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me,this_object()); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me,object item )
{
	mapping mpPet1 = (["小山鸡":10,"小野兔":11,"小蜜蜂":150,"小蚂蚁":151, "斑点蛙":304, "赤褐蚁":151,]);
	int * name = ({ 6000, 6510, 8810, 7210, 6100, 6610, 8810, 7210, });
	int id = getoid(item), i, p, total, amount;
	string cName,*nKey;
	object pet;
	if ( me->get_beast_amount() + 1 > me->get_beast_max_amount() )
	{
		send_user(me, "%c%s", '!', "你的宠物空间已经满了，请放弃掉不要的宠物后再来使用无敌宝宝包吧。");
		return 0;
	}	
	if( sizeof_inventory(me, 1, MAX_CARRY) >= MAX_CARRY-6 )
	{
		send_user(me, "%c%s", '!', "开启无敌宝宝包必须有7个以上道具栏空位");
	        return 0;
	}	
	item->remove_from_user();
	destruct(item);
	nKey = keys(mpPet1);
	cName = nKey[random(sizeof(nKey))];	
	pet = USER_BEAST_D->give_pet(me,cName,1,0,mpPet1[cName],1);	
	if ( pet )
		pet->set_save("no_give",1);	
	for (i=(me->get_gender()-1)*4;i<(me->get_gender()-1)*4+4;i++)
	{
		item = new (sprintf("/item/mop/%d", name[i]));
		if (item)
		{
			if( item->get_max_combined()>1 )
			{
				total = 1;
				amount = USER_INVENTORY_D->carry_combined_item(me, item, total);
			        if( amount > 0 && item->set_amount(amount) )
			        {
			                if( p = item->move(me, -1) )
			                {
			                        item->add_to_user(p);
			                }
			        }
			        else
			        {
			        	item->add_amount( -total );
			        }
			}
			else
			{
				if( p = item->move(me, -1) )
			        {
			                item->add_to_user(p);
			        }
			}
		}
	}
	for (i=0;i<4;i++)
	{
		switch(i)
		{
		case 0:
			item = new ("/item/91/9100");
			item->set_amount(20);
			break;
		case 1:
			item = new ("/item/91/9110");
			item->set_amount(20);
			break;
		case 2:
		case 3:
			item = new (sprintf("/item/98/%d", 9800+random(20) ));
			break;								
		}
		if( item->get_max_combined()>1 )
		{
			total = item->get_amount();
			amount = USER_INVENTORY_D->carry_combined_item(me, item, total);
		        if( amount > 0 && item->set_amount(amount) )
		        {
		                if( p = item->move(me, -1) )
		                {
		                        item->add_to_user(p);
		                }
		        }
		        else
		        {
		        	item->add_amount( -total );
		        }
		}
		else
		{
			if( p = item->move(me, -1) )
		        {
		                item->add_to_user(p);
		        }
		}	
	}
	send_user(me, "%c%s", '!', "您成功获得了无敌宝宝包的奖励");
	return 0;	                        
} 
