//称谓处理模块
#include <ansi.h>

//称谓编码表
mapping mpTitle = ([

	"A001":"Anh Hùng Đả Hổ",
	"A002":"Uy Võ Thiên Hạ",
	"A003":"劳动最光荣",
	"A004":"勤劳的小蜜蜂",
	"A005":"爆强的战国劳模",
	"A006":"Vận Tiêu Đại Siêu Nhân",
	"A007":"Địa Ngục Thiếu Niên",
	"A008":"Địa Ngục Thiếu Nữ",
	"A009":"Thanh Đồng Thánh Đấu Sĩ",
	"A010":"Bạch Ngân Thánh Đấu Sĩ",
	"A011":"Hoàng Kim Thánh Đấu Sĩ",
	"A012":"Hắc Ám Thánh Đấu Sĩ",
	"A013":"Nhất Mã Bình Xuyên", //真假虎王的称谓
	"A014":"Nhị Long Hí Châu",
	"A015":"Nhập Mộc Tam Phân",
	"A016":"Ngao Du Tứ Hải",
	"A017":"Võ Tòng Đả Hổ",
	"A018":"Diệt Lục Hổ Tướng",

	"A020":"Thiên Hạ Đệ Nhất",
	"A021":"Nhất Đại Phú Hộ",
	"A022":"Công Đức Vô Lượng",
	"A023":"Giáo Lý Thiên Hạ",

	"B001":"Sư Phụ", //Danh hiệu sư đồ
	"B002":"Đệ Tử",
	"B003":"Vị Nhân Sư Biểu",
	"B004":"Giáo Lý Thiên Hạ",

	"C001":"Bang Chủ", // Bang phái
	"C002":"Phó Bang Chủ",
	"C003":"Trưởng Lão",
	"C004":"Đường Chủ",
	"C005":"Hương Chủ",
	"C006":"Tinh Anh",
	"C007":"Thương nhân",
	"C008":"Bang Chúng",

	"F001":"Đào Hoa Nguyên Đại Đệ Tử",
	"F002":"Thục Sơn Đại Đệ Tử",
	"F003":"Cấm Vệ Quân Đại Đệ Tử",
	"F004":"Đường Môn Đại Đệ Tử",
	"F005":"Mao Sơn Đại Đệ Tử",
	"F006":"Côn Luân Đại Đệ Tử",
	"F007":"Vân Mộng Cốc Đại Đệ Tử",

	"G001":"全家英雄",
	"G002":"Loạn Thế Anh Hùng",
	"G003":"游戏在线GM",
	"G004":"游戏开发人员",
	"G005":"线上活动主持人",
	"G006":"游戏巡察人员",
	"G007":"封测第一帮",

	"M001":"Tướng công",
	"M002":"Nương tử",

	"P001":"Tân binh Chiến Quốc",
	"P002":"Ngũ Trường",
	"P003":"Bách Phu Trường",
	"P004":"Thiên Phu Trường",
	"P005":"Thiên Tướng Quân",
	"P006":"Bình Quốc Tướng Quân",
	"P007":"An Quốc Tướng Quân",
	"P008":"Trấn Quốc Tướng Quân",
	"P009":"Chính Dị Tướng Quân",
	"P010":"Phiêu Kị Đại Tướng Quân",
	"P011":"Thiên Hạ Đại Tướng Quân",

	"S111":"Dẫn Lộ Tiểu Đồng", //桃花源门派称谓
	"S112":"Kình Hoa Sĩ Nữ",
	"S121":"Đào Viên Lực Sĩ",
	"S122":"Sở Sở Y Nhân",
	"S131":"Tiêu Dao Tán Tiên",
	"S132":"Huệ Chất Lan Tâm",
	"S141":"Thế Ngoại Chân Nhân",
	"S142":"Khuynh Quốc Khuynh Thành",

	"S211":"Sơn Giản Linh Đồng", //蜀山门派称谓
	"S212":"Sơn Khê Linh Ngư",
	"S221":"Giang Hồ Du Hiệp",
	"S222":"Bích Thiên Nữ Hiệp",
	"S231":"Thông Thần Đạo Giả",
	"S232":"Hoán Thần Sứ Giả",
	"S241":"Thiên Ngoại Phi Tiên",
	"S242":"Cửu Thiên Tiên Nữ",

	"S311":"Tuần Thành Tiểu Binh", //禁卫军门派称谓
	"S312":"Truyền Lệnh Tín Sứ",
	"S321":"Cấm Quân Giáo Đầu",
	"S322":"Cấm Quân Thị Vệ",
	"S331":"Chấp Pháp Quân Môn",
	"S332":"Nguyệt Quang Anh Hiệp",
	"S341":"Thần Uy Tướng Quân",
	"S342":"Nữ Kiệt Anh Hào",

	"S411":"Môn Tiền Thị Giả", //唐门门派称谓
	"S412":"Tiểu Gia Bích Ngọc",
	"S421":"Đoạt Mệnh Thần Thủ",
	"S422":"Tú Các Thiên Kim",
	"S431":"Vô Ảnh Thần Tông",
	"S432":"A Na Hoa Dung",
	"S441":"Bát Thủ La Hán",
	"S442":"Chí Tôn Hồng Nhan",

	"S511":"Mao Sơn Tiểu Đạo", //茅山门派称谓
	"S512":"Thái Hoa Tiểu Tiên",
	"S521":"Hộ Pháp Hành Giả",
	"S522":"U Lan Mỹ Nhân",
	"S531":"Giáng Ma Tôn Giả",
	"S532":"Khu Ma Nữ Sứ",
	"S541":"Ngự Pháp Thiên Sư",
	"S542":"Kinh Thế Ngọc Cơ",

	"S611":"Tam Thanh Đạo Đồng", //昆仑山门派称谓
	"S612":"Ngọc Thanh Tú Nữ",
	"S621":"Ngự Long Sứ Giả",
	"S622":"Ngự Long Tiên Tử",
	"S631":"Hỏa Long Pháp Thần",
	"S632":"Gia Lạc Sứ Giả",
	"S641":"Thần Long Pháp Tôn",
	"S642":"Phi Thiên Thánh Nữ",

	"S711":"Dược Cốc Ngoan Hài", //云梦泽门派称谓
	"S712":"Quỷ Linh Tinh Quái",
	"S721":"Hồi Mệnh Thánh Thủ",
	"S722":"Băng Tuyết Ái Nhân",
	"S731":"Quỷ Cốc Thần Y",
	"S732":"Tố Thủ Kỳ Tài",
	"S741":"Tế Thế Y Tôn",
	"S742":"Độ Thế Quan Âm",

	"V001":"VIP",

	   "X":"Bình Giới Đầu Hàm",

	"Z001":"Chiến Quốc Nguyên Lão",
	"Z002":"Chiến Quốc Tân Thủ Vương",
	"Z003":"Chiến Quốc May Mặc Đại Sư",
	"Z004":"Chiến Quốc Rèn Đúc Đại Sư",
	"Z005":"Chiến Quốc Luyện Đơn Đại Sư",
	"Z006":"Chiến Quốc Cơ Quan Đại Sư",
	"Z007":"Chiến Quốc Đầu Bếp Đại Sư",
	"Z008":"Chiến Quốc Đệ Nhất Bang Chủ",
	"Z009":"Tiệt Đồ Tôn Giả",
	"Z010":"Sáng Ý Sứ Giả",
	"Z011":"Chiến Quốc Tài Tử",
	"Z012":"Chiến Quốc Tài Nữ",
	"Z013":"Chiến Quốc Điêu Khắc Đại Sư",
	"Z014":"Chiến Quốc Vương Giả",
	"Z888":"Vô Song Thành Chủ",
	"Z889":"Hiệu Úy Vô Song Thành",

	"Y001":"Hiệp Khách Giang Hồ",
	"Y005":"Anh Hùng Võ Lâm",
	"Y010":"Võ Học Cái Thế",
	"Y015":"Võ Lâm Kinh Hồng Ảnh",
	"Y020":"Võ Lâm Minh Chủ",
	"Y025":"Thiên Hạ Vô Song",
	"Y101":"Quản Trị Game",
	"Y200":"Địa Ngục Bá Nhân",
	"Y300":"Hiệu Úy Vô Song Thành",
	"Y301":"Quân Sư Vô Song Thành",
	"Y302":"Phó Soái Vô Song Thành",
	"Y303":"Đại Soái Vô Song Thành",
	"Y304":"Vô Song Thành Chủ",

]);
mapping mpShouxi = (["Đào Hoa Nguyên":"F001",
						   "Thục Sơn":"F002",
						"Cấm Vệ Quân":"F003",
						  "Đường Môn":"F004",
							"Mao Sơn":"F005",
						   "Côn Luân":"F006",
					   "Vân Mộng Cốc":"F007",

]);

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：构造处理
void create()
{
}
//检查代码是否有效
int check_title_code(string titlecode)
{
	return stringp(mpTitle[titlecode]) ? 1 : 0;
}
//增加玩家称谓
void send_title(object who, string titlecode)
{
	string titlename, name;
	int position;
	if (titlecode[0..0] == "B")
	{
		if (titlecode == "B002")
			titlename = CRA + "Đệ Tử của " + who->get_save_2("baishi.shifu.name");
		else if (titlecode == "B001")
			titlename = CRA + "Sư Phụ của " + who->get_save_2("baishi.tudi.name");
		else
			titlename = CRA + mpTitle[titlecode];
	}
	else if (titlecode[0..0] == "C")
	{
		name = who->get_org_name();
		if (name != "")
		{
			titlename = CRE + name + " " + mpTitle[titlecode];
		}
	}
	else if (titlecode[0..0] == "M")
	{
		name = who->get_save_2("marry.name");
		if (stringp(name) && name != "")
		{
			if (titlecode == "M001")
				titlename = CRD + "Tướng công của " + name + "";
			else if (titlecode == "M002")
				titlename = CRD + "Nương tử của " + name + "";
		}
	}
	else if (titlecode[0..0] == "X")
		titlename = USER_RANK_D->get_rank(who);
	else
		titlename = mpTitle[titlecode];
	if (sizeof(titlename) == 0)
		return;
	if (titlecode[0..0] == "A" || titlecode[0..0] == "Z")
		titlename = CRF + titlename;
	send_user(who, "%c%c%s", 0xA2, 1, sprintf("%-4s%s", titlecode, titlename));
}
//删除玩家称谓
void delete_title(object who, string titlecode)
{
	string titlename;

	titlename = mpTitle[titlecode];
	if (sizeof(titlename) == 0)
		return;
	send_user(who, "%c%c%s", 0xA2, 2, titlecode);
}
//显示称谓(不同类别的称谓代码可以拼成不同的称谓名称)
void show_title(object who, string titlecode)
{
	string titlename, name, tmp_title_code;
	int position, rank;
	string *mingren_titlecode = ({
		"A020",
		"A021",
		"A022",
		"A023",
		"F001",
		"F002",
		"F003",
		"F004",
		"F005",
		"F006",
		"F007",
	});

	who->delete ("add_mingren_power");
	USER_ENERGY_D->count_ap(who);
	USER_ENERGY_D->count_cp(who);
	if (titlecode[0..0] == "P")
	{
		sscanf(titlecode, "P%d", rank);
		if (rank < 4)
			titlename = HIW + mpTitle[titlecode];
		else if (rank < 7)
			titlename = HIG + mpTitle[titlecode];
		else if (rank < 9)
			titlename = HIB + mpTitle[titlecode];
		else if (rank < 11)
			titlename = HIY + mpTitle[titlecode];
		else if (rank < 12)
			titlename = PPM + mpTitle[titlecode];
		else
			titlename = HIR + mpTitle[titlecode];
	}
	else if (titlecode[0..0] == "Y")
	{
		sscanf(titlecode, "Y%d", rank);
		if (rank < 2)
			titlename = HIC + mpTitle[titlecode];
		else if (rank < 6)
			titlename = HIC + mpTitle[titlecode];
		else if (rank < 11)
			titlename = PPM + mpTitle[titlecode];
		else if (rank < 16)
			titlename = PPM + mpTitle[titlecode];
		else if (rank < 100)
			titlename = YEL + mpTitle[titlecode];
		else if (rank < 200)
			titlename = HIR + mpTitle[titlecode];
		else
			titlename = CRF + mpTitle[titlecode]; //GRN
	}
	else if (titlecode[0..0] == "B")
	{
		if (titlecode == "B002")
			titlename = CRA + "Đệ Tử của " + who->get_save_2("baishi.shifu.name");
		else if (titlecode == "B001")
			titlename = CRA + "Sư Phụ của " + who->get_save_2("baishi.tudi.name");
		else
			titlename = CRA + mpTitle[titlecode];
		/*else
			titlename = CRA + "Sư Phụ của "+who->get_save_2("baishi.tudi.name");*/
	}
	else if (titlecode[0..0] == "C")
	{
		name = who->get_org_name();
		if (name != "")
		{
			titlename = CRE + name + " " + mpTitle[titlecode];
		}
	}
	else if (titlecode[0..0] == "M")
	{
		name = who->get_save_2("marry.name");
		if (stringp(name) && name != "")
		{
			if (titlecode == "M001")
				titlename = CRD + "Tướng công của " + name + "";
			else if (titlecode == "M002")
				titlename = CRD + "Nương tử của " + name + "";
		}
	}
	else if (titlecode[0..0] == "X")
		titlename = USER_RANK_D->get_rank(who);
	else
		titlename = mpTitle[titlecode];
	if (sizeof(titlename) == 0)
		return;
	if (titlecode[0..0] == "A" || titlecode[0..0] == "Z")
		titlename = CRF + titlename;
	else if (titlecode == "V001")
		titlename = HIY + titlename;
	tmp_title_code = who->get_title_code();
	who->set_title(titlecode, titlename);
	if (tmp_title_code == "A018" || titlecode == "A018")
	{ //	此称号所具有的附加属性
		USER_ENERGY_D->count_dp(who);
		USER_ENERGY_D->count_pp(who);
	}
	if (tmp_title_code == "Y001" || titlecode == "Y001")
	{
		CHAR_CHAR_D->init_loop_perform(who);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	if (tmp_title_code == "Y010" || titlecode == "Y010")
	{
		CHAR_CHAR_D->init_loop_perform(who);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	if (tmp_title_code == "Y015" || titlecode == "Y015")
	{
		CHAR_CHAR_D->init_loop_perform(who);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	if (tmp_title_code == "Y025" || titlecode == "Y025")
	{
		CHAR_CHAR_D->init_loop_perform(who);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	if (tmp_title_code == "M001" || titlecode == "M001")
	{
		CHAR_CHAR_D->init_loop_perform(who);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	if (tmp_title_code == "M002" || titlecode == "M002")
	{
		CHAR_CHAR_D->init_loop_perform(who);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	if (member_array(titlecode, mingren_titlecode) != -1)
	{ //称号为名人堂称谓ap,cp加成
		who->set("add_mingren_power", 1);
		USER_ENERGY_D->count_ap(who);
		USER_ENERGY_D->count_cp(who);
	}
	if (titlecode[0..0] == "P")
	{
		USER_ENERGY_D->count_ap(who);
		USER_ENERGY_D->count_cp(who);
	}
	/*	if ( titlecode[0..0] == "Y" )
	{
		USER_ENERGY_D->count_ap(who);
		USER_ENERGY_D->count_cp(who);
	}*/
	who->add_to_scene(get_z(who), get_x(who), get_y(who));
}
//隐藏称谓
void hide_title(object who, string titlecode)
{
	if (who->get_title_code() == "A018")
	{ //	此称号所具有的附加属性
		who->set_title("", "");
		USER_ENERGY_D->count_dp(who);
		USER_ENERGY_D->count_pp(who);
	}
	else if (who->get_title_code() == "Y001")
	{ //	此称号所具有的附加属性
		who->set_title("", "");
		CHAR_CHAR_D->init_loop_perform(who);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	else if (who->get_title_code() == "Y010")
	{ //	此称号所具有的附加属性
		who->set_title("", "");
		CHAR_CHAR_D->init_loop_perform(who);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	else if (who->get_title_code() == "Y015")
	{ //	此称号所具有的附加属性
		who->set_title("", "");
		CHAR_CHAR_D->init_loop_perform(who);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	else if (who->get_title_code() == "Y025")
	{ //	此称号所具有的附加属性
		who->set_title("", "");
		CHAR_CHAR_D->init_loop_perform(who);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	else if (who->get_title_code() == "M001")
	{ //	此称号所具有的附加属性
		who->set_title("", "");
		CHAR_CHAR_D->init_loop_perform(who);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	else if (who->get_title_code() == "M002")
	{ //	此称号所具有的附加属性
		who->set_title("", "");
		CHAR_CHAR_D->init_loop_perform(who);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	else
	{
		who->delete ("add_mingren_power");
		who->set_title("", "");
		USER_ENERGY_D->count_ap(who);
		USER_ENERGY_D->count_cp(who);
	}
	who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
}
//获得称谓名称
string get_titlename(string titlecode)
{
	string titlename;

	titlename = mpTitle[titlecode];
	if (sizeof(titlename) == 0)
		return "";
	return titlename;
}

void add_shouxi_title(object who, string fam_name)
{
	who->add_title(mpShouxi[fam_name]);
}

string get_shouxi_titlecode(string fam_name)
{
	return mpShouxi[fam_name];
}
