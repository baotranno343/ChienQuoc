
#include <ansi.h>
#include <task.h>

// 数组：标准提示信息 -- [随意]
mapping TipsTable = ([

        "1" :  "Cấp bậc sau khi tăng năng lực cũng sẽ tăng cường, đồng thời sẽ đạt được "HIY"điểm thuộc tính" NOR " mỗi cấp. Mở ra bảng nhân vật thì có thể dùng ( ALT+W), có thể đem phân phối cho "HIY "5 loại thuộc tính" NOR " khác nhau. \n",

	"2" :  "Chúc mừng bạn thăng lên tới cấp 10! Đề nghị bạn nên thăm hỏi" HIY "Môn phái chiêu sinh ở Tân Thủ Thôn" NOR " để tới các môn phái. Chỉ cần gia nhập một trong bảy phái, võ công sẽ cao thêm 1 bậc." HIY "Môn Phái Chiêu Sinh" NOR " ở tại Tân Thủ thôn, không cần chần chờ, nhanh đi tìm hắn đi! \n",

	"3" :  "Tiêu diệt quái vật ngoài nhận được vật phẩm và kinh nghiệm, còn nhận được " HIY " Điểm Tiềm năng" NOR " ." HIY " Điểm Tiềm năng " NOR " dùng để tu luyện kĩ năng sau này, khi cấp bậc kỹ năng càng cao, thì " HIY " Điểm Tiềm năng" NOR " tiêu hao sẽ càng nhiều. \n",

	"4" :  "Bạn nhặt được vật phẩm mang tên " HIY "Sứ mệnh vật phẩm" NOR ", bình thường ở Tân Thủ thôn, vùng hoang vu đều có thể tìm thấy chúng. Thu thập vật phẩm này, đem nó giao cho Tân Thủ thôn "HIY"Vệ đội trưởng" NOR ", có thể nhận được phần thưởng. \n",

	"5" :  "Dùng phím Alt+2 thì nhân vật có thể ngồi xuống. Sau khi ngồi xuống tốc độ khôi phục Khí Huyết và Pháp Lực sẽ nhanh hơn. \n",

	"6" :	"Dùng "HIY" 'Shift+ chuột phải' " NOR " trên tên nhân vật ở khung chat, có thể nói thầm hoặc mời vào nhóm. \n",

	"7" :	"Dùng Alt+ T kích vào chính mình để tạo 1 đội nhóm, lúc này tiếp tục kích vào người khác có thể mời người chơi khác nhập nhóm ngũ của bạn. Đồng dạng, kích vào chân dung của thành viên nhóm có thể mở ra nhiều thao tác khác. \n",

	"8" :	"Ở Tân Thủ thôn, vùng hoang vu cùng dã ngoại vùng, mỗi cách xa nhau 30 phút liền sẽ xuất hiện một đám" HIY " 'Sứ mệnh nhân vật'" NOR "Phân bố tại đây đó cảnh tượng trung. Mau lợi dụng trụ cột kỹ năng trong đích 'Xem xét sứ mệnh nhân vật' công năng xem xét này đó" HIY " 'Sứ mệnh nhân vật' " NOR " vị trí, cũng tìm tới cùng chung chí hướng bạn tốt, tạo thành một chi đội ngũ đi khiêu chiến này đó 'Sứ mệnh nhân vật' đi! \n",

	"9" :	"Ở trong trò chơi gặp được không hiểu vấn đề sao? Hãy tìm không đến là một loại nPC? Mau mau mở ra bạn tốt mặt biên, thỉnh "HIY "Vạn Sự Thông" NOR "Giải đáp của ngươi nghi nan vấn đề đi. \n",

	"10 ":	"Chúc mừng ngươi đã muốn lướt qua tay mới giai đoạn, có phải hay không đang ở làm tiền tài chuyện tình mà phiền não đây? Nghe nói Chu quốc Vương Bộ đầu chỗ có thể nhận được một phần kiếm tiền chuyện tốt, gì không nhìn tới xem ~\n",

	"11 ":	"Nghe nói Tân Thủ thôn vệ đội trưởng chỗ có không ít chuyện tốt, đã có thể kiếm tiền có năng lực rèn luyện chính mình, gì không nhìn tới xem ~\n",

	"12 ":	"Chúc mừng ngài đạt tới 30 cấp, mau mau tìm Chu quốc thần tiên ông nội đi, nghe nói lão gia gia đang ở cử hành một cái "HIR " 'VIP thử dùng bao' "NOR "Đại đưa tặng hoạt động. VIP trong bọc giấu thần kỳ công năng, có thể làm cho ngươi thể nghiệm càng nhiều Chiến quốc phấn khích! Chỉ muốn trở thành VIP người sử dụng, ngài đem phải nhận được rất nhiều không tưởng được ưu đãi phục vụ.",

	"13 ":	"Lấy thực lực ngươi bây giờ, hoàn toàn có thể đảm nhiệm thành vì người khác thầy cô giáo. Nhanh đi bái phỏng một chút Chu quốc Khổng phu tử, kia vị đại sư sẽ giáo ngài như thế nào trở thành một gã xứng chức thầy cô giáo. \n",


]);

mapping mpScene = ([

	001 : 0,
	002 : 0,
	003 : 0,
	004 : 0,
	005 : 0,
	006 : 0,
	007 : 0,
	008 : 0,
	009 : 0,
	161 : 5,
	162 : 5,
	061 : 10,
	062 : 10,
	063 : 10,
	281 : 10,
	282 : 10,
	283 : 10,
	284 : 10,
	081 : 15,
	082 : 15,
	251 : 15,
	021 : 20,
	041 : 20,
	042 : 20,
	043 : 20,
	141 : 20,
	142 : 20,
	211 : 20,
	089 : 25,
	131 : 25,
	132 : 25,
	155 : 25,
	181 : 25,
	182 : 25,
	231 : 25,
	241 : 25,
	242 : 25,
	243 : 25,
	271 : 25,
	272 : 25,
	164 : 30,
	261 : 30,
	262 : 30,
	263 : 30,
	264 : 30,
	111 : 35,
	112 : 35,
	265 : 35,
	266 : 35,
	011 : 40,
	012 : 40,
	013 : 40,
	014 : 40,
	015 : 40,
	151 : 45,
	152 : 45,
	153 : 45,
	501 : 45,
	502 : 45,
	503 : 45,
	171 : 50,
	172 : 50,
	173 : 50,
	174 : 50,
	528 : 50,
	529 : 50,
	530 : 50,
	071 : 55,
	072 : 55,
	073 : 55,
	512 : 55,
	513 : 55,
	031 : 60,
	032 : 60,
	033 : 60,
	510 : 60,
	511 : 60,
	051 : 65,
	052 : 65,
	053 : 65,
	524 : 65,
	525 : 65,
	526 : 65,
	527 : 65,
	321 : 70,
	322 : 70,
	323 : 70,
	516 : 70,
	517 : 70,
	311 : 75,
	312 : 75,
	313 : 75,
	514 : 75,
	515 : 75,
	311 : 75,
	312 : 75,
	313 : 75,
	331 : 80,
	332 : 80,
	333 : 80,
	334 : 80,
	335 : 80,
	504 : 80,
	505 : 80,
	341 : 85,
	342 : 85,
	343 : 85,
	344 : 85,
	345 : 85,
	508 : 85,
	509 : 85,
	291 : 90,
	292 : 90,
	293 : 90,
	506 : 90,
	507 : 90,
	381 : 95,
	383 : 95,
	385 : 95,
	520 : 95,
	522 : 95,
	372 : 100,
	373 : 100,
	374 : 100,
	521 : 100,
	523 : 100,
	091 : 105,
	092 : 105,
	093 : 105,
	531 : 105,
	532 : 105,
	391 : 110,
	392 : 110,
	393 : 110,
	518 : 110,
	519 : 110,

	]);

//
mapping mpGradeScene = ([


		]);

// 数组：新手提示信息 -- [随意]
mapping NewbieTipsTable = ([

        "1" :   "          Hoan nghênh quang lâm 《 Chiến quốc Ⅱ Online》. \n chứng kiến phía trước vị kia" HIY "Xinh đẹp tiểu tiên nữ" NOR "Sao? Thử xem dùng" HIY "Chuột hữu khóa" NOR "Điểm hướng vị kia" HIY "Tiểu tiên nữ" NOR ", người của ngài vật sẽ gặp hướng tới tiểu tiên nữ phương hướng di động.",


       "2" :  "Làm chuột kim đồng hồ chuyển qua nPC trên người thì kim đồng hồ sẽ biến thành một cái" HIY "Đối thoại dấu hiệu" NOR ", lúc này chỉ cần điểm kích một chút" HIY "Chuột tả khóa" NOR ", có thể cùng nPC tiến hành nói chuyện với nhau. \n",

]);

// 数组：场景公用提示 -- [200～255]
mapping CommonTipsTable = ([

        "255" : "Ở đất vườn lý có thể thu thập đến đủ loại dược thảo, căn cứ vị trí địa vực là không cùng, có thể thu thập đến" HIY "Dược thảo" NOR "Cũng không hết giống nhau. Thông qua sử dụng cuộc sống kỹ năng" HIY "Thu thập" NOR ", liền có thể tiến hành" HIY "Dược thảo" NOR " thu thập công tác. \n",

]);

// 数组：地图场景提示 -- [地图号][001～199]
mapping MapTipsTable = ([

        "1001" : "Hoan nghênh đến với Tân Thủ Thôn, đây là nơi tụ tập của các Tân Thủ, cũng là quê hương trưởng thành của vô số dũng sĩ. Đến gặp thôn dân ở đây, tỉ mỉ lắng nghe lời họ nói, ngươi sẽ hiểu được nhiều hơn về tình hình của thế giới này.\n",

        "1002" : "Đi thẳng theo con đường đá xanh nhỏ, có thể đến Tân Thủ Thôn. Thần Tiên Gia Gia và Tiểu Tiên Nữ nói đang đợi ngươi ở ngõ vào của thôn.\n",

//        "1003" : "请将" HIY "百合仙子的信件" NOR "交给" HIY "神仙爷爷" NOR "。这样你便可以完成百合仙子的委托了。\n",

        "1004" : "Có nhìn thấy biểu tượng đối thoại đang phấp phới trên phần đầu của NPC không? Điều này có nghĩa là NPC có một nhiệm vụ giao cho ngươi hoàn thành, sau khi ngươi nhận nhiệm vụ này biểu tượng này sẽ chuyển thành màu xám, cho đến khi ngươi hoàn thành nhiệm vụ được giao thì biểu tượng này mới biến mất.\n",

        "1005" : "Phía nam của Tân Thủ Thôn là dã ngoại, phía đông hướng ra Động Đinh Hồ, còn phía bắc là vùng ngoại ô. Những nơi này đều là khu vực hoạt động của tân thủ, tương đối thích hợp cho các tân thủ đánh quái luyện cấp.\n",

        	"1006" : "Điểm kích tổ đội cái nút ( T), chuột kim đồng hồ sẽ chuyển biến làm một mặt cờ nhỏ, dùng cờ nhỏ điểm kích chính mình có thể tạo thành một chi" HIY "Đội ngũ" NOR ", nếu điểm kích người chơi khác còn lại là xin gia nhập người khác đội ngũ. \n",

	"1007" : "Chỉ có tổ đội mới có thể tiêu tan diệt thôn ngoại" HIY "Sứ mệnh nhân vật" NOR ", tiêu diệt này đó" HIY "Sứ mệnh nhân vật" NOR "Sau có thể đạt được so với bình thường quái vật càng nhiều là thưởng cho kinh nghiệm. \n",

	"1008" : "Rượu điếm lão bản nơi đó chẳng những bán ra thực vật cùng rượu, nhưng lại có thể tìm tới rượu và đồ nhắm kỹ năng cần có các loại nấu nướng tài liệu. \n",

        "1009" : "Ngoài Tân Thủ Thôn trong trò chơi còn có 8 thành phố lớn là Tề, Hàn, Triệu, Ngụy, Tần, Sở, Yên, Chu, thông qua chủ Dịch Trạm có thể giúp ngươi đi qua lại giữa các thành phố này.\n",

        "1010" : "Ngươi có thể mua được các loại vũ khí khác nhau như đao, thương, kiếm, côn, quyền chưởng , ám khí…ở Chủ Tiệm Vũ Khí. Đồng thời ngươi cũng có thể bán lại những vật phẩm vô dụng trên người ngươi cho ông Chủ Tiệm Vũ Khí.\n",

        "1011" : "Sửa chữa điếm lão bản có thể trợ giúp ngài đem hư hao vũ khí trang bị chữa trị, chẳng qua lên giá phí không ít tiền tài. \n",

	"1012" : "Phòng cụ điếm có thể mua được đủ loại phòng cụ đồ dùng. Đồng thời ngài cũng có thể đem trên người mình không có vật phẩm bán cho phòng cụ điếm lão bản. \n",

	"1013" : "Hiệu cầm đồ lão bản có thể giúp ngài đem vật phẩm, hoặc là tiền tài tạm thời bảo quản. Làm ngài lúc cần phải, tùy thời có thể thông qua hiệu cầm đồ lão bản đem lấy ra. Mặt khác, ở môn phái học tập kỹ năng thì nếu ngài trên người mang theo tiền mặt không đủ, không đủ bộ phận sẽ theo ngài ở trong tiệm cầm đồ gởi ngân hàng trung trực tiếp khấu trừ, cho đến gởi ngân hàng không đủ để học tập kỹ năng mới thôi. \n",

	"1014" : "Ngài có thể ở tiệm tạp hóa mua được các loại nhất định đồ dùng, tỷ như trở về thành phù, phi hành phù từ từ. Ngài cũng có thể đem trên người mình vô dụng vật phẩm bán cho tiệm tạp hóa lão bản để đổi lấy một ít tiền tài. \n",

	"1015" : "Ngươi có thể ở tiệm thuốc mua được các loại khôi phục loại thuốc. Ngươi cũng có thể đem trên người mình vô dụng vật phẩm bán cho tiệm thuốc lão bản để đổi lấy một ít tiền tài. \n",

        "80001" : "Đây là khu vực bày hàng của Chu Quốc, nếu ngươi muốn bán những vật dụng trên người cho những người chơi có hứng thú, hãy đứng trong khu vực này, thông qua chỉ lệnh “bày hàng” trong kỹ năng cơ sở để bày gian hàng nhỏ độc đáo!\n",

]);

// 函数：显示提示信息(标准)
void send_tips( object me, string id ) 
{ 
        if( !id || !TipsTable[id] ) return;
        send_user( me, "%c%s", ';', TipsTable[id] );
}

// 函数：显示提示信息(新手)
void send_newbie_tips( object me, string id ) 
{ 
        if( !id || !NewbieTipsTable[id] ) return;
        send_user( me, "%c%s", ';', NewbieTipsTable[id] );
}

// 函数：显示提示信息(场景公用)
void send_common_tips( object me, string id ) 
{ 
        if( !id || !CommonTipsTable[id] ) return;
        send_user( me, "%c%s", ';', CommonTipsTable[id] );
}

// 函数：显示提示信息(地图)
void send_map_tips( object me, string id ) 
{ 
        int z, p;
	int status;
        z = get_z(me);  p = to_int(id);
	id = sprintf("%d%03d", z, p);
	status = me->get_save("tipsstatus");
        switch(id)
        {
        case "80001":
        	"/quest/help"->send_help_tips(me, 23);
        	break;
        case "80002":
        	"/quest/help"->send_help_tips(me, 32);
        	break;
        case "80003":
        	"/quest/help"->send_help_tips(me, 18);
        	break;       
        case "1001":
        	"/quest/help"->send_help_tips(me, 50);       
        	break; 	 	        	
        case "1002":
        	"/quest/help"->send_help_tips(me, 37);
        	"/quest/help"->send_help_tips(me, 48);
        	break;        
        case "1004":
        	"/quest/help"->send_help_tips(me, 38);
        	break;    
        case "1005":
        	"/quest/help"->send_help_tips(me, 39);
        	break;    
        case "1006":
        	"/quest/help"->send_help_tips(me, 40);
        	break;            	        	        	
        }	
        switch( z )
        {
       case 1 : 
       		if (status & (1<<p)) return;
       		status = status | (1<<p);
       		me->set_save("tipsstatus", status);
		break;
        }
        

        if( !id || !MapTipsTable[id] ) return;
        


        send_user( me, "%c%s", ';', MapTipsTable[id] );
}

void create()
{
	int i,size,*nTmp,p,g;
	
	nTmp = keys(mpScene);
	for(i=0,size=sizeof(nTmp);i<size;i++)
	{
		p = nTmp[i];
		g = mpScene[p];
		if ( !arrayp(mpGradeScene[g]) )
			mpGradeScene[g] = ({ p });
		else
			mpGradeScene[g] += ({ p });
	}	
}

void enter_scene_tip(object who,object map)
{
	int level,level1,z,*nTmp,i,size;
	string cName,cTmp;
	object map1;
	z = map->get_id();
	if ( undefinedp(level1=mpScene[z]) )
	{
		send_user(who,"%c%c%s",0xA5,1,map->get_name()); 
		return ;	
	}
	level = who->get_level();
	cName = map->get_name();
	level = level/5*5;
	
	if ( level1 >= level + 10 )
		cName = cName + "|" + sprintf(HIR"cấp %d khu vực, cẩn thận！",level1);
	else if ( level1 >= level + 5 )
		cName = cName + "|" + sprintf(HIY"cấp %d khu vực！",level1);
	else if ( level1 >= 1 )
		cName = cName + "|" + sprintf("cấp %d khu vực！",level1);
	send_user(who,"%c%c%s",0xA5,1,cName); 
	
	if ( level1 > level )
	{
		cTmp = "";
		nTmp = mpGradeScene[level];
		if (sizeof(nTmp)==0) return;
		nTmp = sort_array(nTmp,1);
		for(i=0,size=sizeof(nTmp);i<size;i++)
		{
			if ( !objectp(map1 = get_map_object(nTmp[i])) )
				continue;
			if ( sizeof(cTmp) )
				cTmp += "、";
			cTmp += map1->get_name();
		}
		if ( sizeof(cTmp) )
			send_user(who,"%c%s",';',"Vì suy nghĩ cho sự an toàn của bạn, đề nghị bạn đi thích hợp hiện tại đẳng cấp"+HIR+cTmp+NOR+"Vùng luyện cấp.");
	}
//	send_user( who, "%c%s", '!', map->get_name() );
}
