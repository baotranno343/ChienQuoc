
#include <npc.h>
#include <ansi.h>

inherit OFFICER;
string cWord;
int iPic;
// 函数:获取人物造型
int get_char_picid() 
{ 
	int z;
	if ( !iPic )
	{
		z = get_z(this_object());
		if ( z == 283 || z == 20 || z == 371 || z == 10 )
			iPic = 2006;
		else
			iPic = 2005;		
	}
	return iPic; } 

// 函数:构造处理
void create()
{
        set_name("");
        setup();
	set("mpLegend",([0:({31}),]));
}

void do_look( object who )
{ 
	int z;
	object me=this_object();
	if ( !cWord )
	{
		z = get_z(who);
		switch(z)
		{
		case 162:
			cWord = "Chú ý, con đường này sẽ dẫn đến "HIR "Ranh Giới Đầm Lầy"NOR ", bên trong là quái vật cấp "HIR "30"NOR ", hãy suy nghĩ kỹ! !";
			break;
		case 165:
			cWord = "Chú ý, con đường nãy sẽ dẫn đến "HIR "Địa Giới Đầm Lầy"NOR ", bên trong là quái vật cấp "HIR "30"NOR ", hãy suy nghĩ kỹ! !";
			break;
		case 283:
			cWord = "Đây là cấm địa, bên trong là quái vật cấp "HIR "95"NOR ", hãy suy nghĩ kỹ! !";
			break;
		case 20:
			cWord = HIR "Loan Đạo"NOR " rất nguy hiểm, bên trong là quái vật cấp "HIR "70"NOR ", hãy suy nghĩ kỹ! !";
			break;
		case 324:
			cWord = HIR "Loan Đạo"NOR " rất nguy hiểm, bên trong là quái vật cấp "HIR "70"NOR ", hãy suy nghĩ kỹ! !";
			break;
		case 42:
			cWord = "Đây là "HIR "Tướng Quân Cổ Mộ"NOR ", bên trong là quái vật cấp "HIR "85"NOR ", hãy suy nghĩ kỹ! !";
			break;
		case 211:
			cWord = "Quan Phủ Bố Cáo:\n　　"HIR "Linh Cốc Động"NOR " bên trong là quái vật cấp "HIR "75"NOR ", hãy suy nghĩ kỹ trước khi vào! !";
			break;
		case 371:
			cWord = "Cẩn thận với Vương Bát.";
			break;
		case 10:
			cWord = "Quý Phủ Bố Cáo:\n　　"HIR "Tru Tiên Trận"NOR " có rất nhiều yêu quái với sức mạnh lạ thường, hãy suy nghĩ kỹ trước khi vào.";
			break;		
		case 132:
			cWord = "Quan Phủ Bố Cáo:\n　　"HIR "Thái Hành Sơn Động"NOR " đã bị phong toả, không được tự ý tiến vào, bằng không hậu quả gánh lấy sẽ rất lớn.";
			break;	
		case 231:
			cWord = "Các người hãy chú ý : Dưới chân các ngươi là một nhân thể nhân tạo.";
			break;	
		case 171:
			cWord = "Tặng ngươi một lời:\n　　Vì ngươi là tài tử, nên phải vong mạng.";
			break;	
		case 111:
			cWord = "Quan Phủ Bố Cáo:\n　　"HIR "Thái Sơn Động"NOR " đã bị phong toả, không được tự ý tiến vào, bằng không hậu quả gánh lấy sẽ rất lớn.";
			break;	
		default:
			cWord = HIR "Gấu"NOR " thường xuất hiện, chú ý, chú ý ! !";
			break;
		}
	}
	send_user(who,"%c%c%w%s",':',3,0,cWord);
}