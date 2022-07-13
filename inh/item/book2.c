
#include <ansi.h>
#include <item.h>
#include <skill.h>

inherit ITEM;
inherit USABLE;

// 函数：书籍识别
// int is_book_2() { return 1; }

// 函数：书籍识别
int get_item_type() { return ITEM_TYPE_BOOK_2; }

int get_record() {return 1;}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
        string name, book, result;
        int skill, level, exp, i, pf, level2, maxlevel;
        object file, perform;

        skill = item->get_skill_id();
        name = item->get_skill_name();
        book = item->get_name();
        file = load_object( SKILL->get_skill_file(skill) );
	if (!file) return 0;

        if( !( level = me->get_skill(skill) ) )
        {
                send_user(me, "%c%s", '!', "Ngươi hoàn toàn xem không hiểu " + book + ".");
                return 0;
        }
/*      if( level >= me->get_max_skill_level() )
        {
                send_user(me, "%c%s", '!', book + "不值得您一看。");
                return 0;
        }       */
        if (file->is_vita_skill()==1)
        {
	        level2 = me->get_level();
	        if (level2<10) maxlevel = 0;
	        else
	        if (level2<25) maxlevel = 39;
	        else
	        if (level2<35) maxlevel = 69;
	        else
	        if (level2<60) maxlevel = 99;
	        else maxlevel = 200;      
	        if (me->get_skill(skill)>=maxlevel)
	        {
	                notify( "Cấp độ của ngươi không đủ để học Kĩ Năng" );
	                return 0;
	        }	          
	}
	else	       
        if( level >= me->get_max_skill_level_3() )    // 限制：等级、最高
        {
                send_user(me, "%c%s", '!', "Kinh nghiệm của ngươi không đủ để đọc " + book + ".");
                return 0;
        }

        level ++;
        me->set_skill(skill, level);        
	if (skill==670||skill==680)
	{
		// 设置初始熟练度
		me->set_skill_degree(skill, 1);
		// 自动学习可以使用的技能
		for (i=0;i<500;i++)
		{
			pf = skill * 100 + i;
			if ("/sys/item/product"->check_vita_skill(me, pf)) continue;
			perform = load_object( SKILL->get_perform_file(pf) );					
			if (perform)
			{
				if (perform->get_skill_color()) break;
				if (perform->get_skill_level()<=level) 
				{							
					"/sys/item/product"->add_vita_skill(me, pf);
					perform->can_perform(me);
				}
				else break;
			}
			if (i>40 && !perform) break;
		}	
	}         
        if (file->is_vita_skill()==1) log_file("lifeskill.txt",sprintf("%s %s %d %d %d\n",short_time(),me->get_id(),me->get_number(),skill,level));
        result = sprintf( HIC "Kĩ năng \"%s\"của ngươi thăng tới %d cấp！", name, level );
        send_user( me, "%c%s", '!', result );
        send_user(me, result);

        return 1;
}
