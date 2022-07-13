
#include <equip.h>

string *buy_item = ({"Đoản Mộc Đao","Trường Mâu","Mộc Kiếm","Trường Mộc Côn","Thô Ma Thủ","Toái Thạch Tử","Ma Y","Ma Bố Mão","Đằng Mạn Hài"});

string get_buy_name(object who)
{
	return buy_item[random(sizeof(buy_item))];	
}