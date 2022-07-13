/*---------------------------------------------------------------------------------*\
	新手物品：Chiến Quốc Bảo Điển。详情见文档《战国宝典设定》
	由 cjxx 于 2007-09-04 创建
\*---------------------------------------------------------------------------------*/
inherit ITEM;
#define ZG_DICTIONARY		"/quest/zg_dict"
#define _DEBUG(str) 		;//if(objectp(find_char("1"))) {tell_user(find_char("1"),str);}

//	道具是否可用
int is_usable() {
	return 1;
}
//	构造函数
void create() {
	set_name("Chiến Quốc Bảo Điển");
	set_picid_1(1017);
	set_picid_2(1017);	
	set_value(0);		//	价值为0
	//set_no_get(1);	//	不可存当铺
	set_no_give(1);		//	不可给予
	set_no_sell(1);		//	不可出售
}
//	道具描述
string get_desc() {
	return "Tương truyền trong bảo điển ghi lại những nơi có thể rèn luyện theo từng cấp độ.\n Mỗi lần tăng 1 cấp người chơi còn được nhận 1 lần quay xổ số may mắn, nhưng nếu bỏ qua cơ hội này thì sẽ không thể nhận lại nữa.";
}
//	执行使用效果函数
int get_use_effect(object me) {
	return __FILE__->get_use_effect_callout(me,this_object());
}
//	实际使用效果函数
int get_use_effect_callout(object me,object item) {
	ZG_DICTIONARY->search_in_user(me);
}