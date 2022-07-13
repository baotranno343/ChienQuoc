
#include <ansi.h>
#include <item.h>
#include <skill.h>

inherit ITEM;
inherit USABLE;
inherit COMBINED;

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
        string name, book, result, perform;
        int skill, level, exp, pf;
        object file;

        skill = item->get_skill_id();
        name = item->get_skill_name();
        book = item->get_name();
 /*       if (" " + me->get_fam_name()!=item->get_family_name())
        {
                send_user(me, "%c%s", '!', "Ngươi không phải"+item->get_family_name()+" phái, không thể học"+item->get_name()+"的奥义。");
                return 0;
        } */ 
        if( !( level = me->get_skill(skill) ) )
        {
                send_user(me, "%c%s", '!', "Ngươi hoàn toàn xem không hiểu " + book + ".");
                return 0;
        }      
        if( level < item->get_skill_level() )
        {
                send_user(me, "%c%s", '!', "Cấp bậc "+item->get_skill_name()+" không đủ "+sprintf("%d", item->get_skill_level())+" để học.");
                return 0;
        }       
        if (me->get_save(item->get_perform_id()))
        {
                send_user(me, "%c%s", '!', "Ngươi đã đọc" + book + "đến mức thâm sâu rồi，không cần đọc nữa");
                return 0;
        }
	me->set_save(item->get_perform_id(), 1);
	pf = to_int(item->get_perform_id());
	if(   ( file = load_object( SKILL->get_perform_file(pf) ) ) )
	{
		file->can_perform(me);
		send_user(me, "%c%s", '!', "Ngươi học được Kĩ Năng " + book + ".");
	}
        return 1;
}
