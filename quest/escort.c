
// 变量:任务列表
mapping PointTable = ([
	   // "Lí Đồ":"10-254,110",
	   // 				 "Lí Lăng":"10-284,212",
	   // 			 "Tôn Lão Đầu":"10-147,231",
	   // 			  "Vương Khải":"10-275,198",
	   // 		  "Khổng Tiểu Phi":"10-297,202",
	   // 			   "Thôi Ngọc":"10-225,166",
	   // 			"Tề Tổng Quản":"10-91,169",
	   // 			 "Tề Quản Gia":"10-83,115",
	   "Lão Vương Thẩm":"20-162,48",
		   "Mã Đại Hán":"20-304,154",
			"Triệu Mộc":"20-219,176",
			   "Lâm Vị":"20-236,179",
				"Du Tử":"20-139,174",
		 "Tiễn Lão Bát":"20-228,129",
		"Hàn Tổng Quản":"20-206,32",
		 "Hàn Quản Gia":"20-168,54",
	"Vương Thiết Tượng":"30-214,90",
			 "Cước Phu":"30-222,100",
			 "Lí Phòng":"30-214,239",
			"Bạch Dịch":"30-188,250",
	  "Triệu Tổng Quản":"30-200,39",
	   "Triệu Quản Gia":"30-155,72",
	   "Trình Lâm Khai":"40-106,146",
			 "Chu Đồng":"40-128,152",
		  "Lí Tam Thẩm":"40-330,184",
		   "Lí Đại Mao":"40-226,230",
			  "Hứa Thị":"40-310,181",
	  "Sa Tiêm Tiểu Tỷ":"40-88,150",
			  "Lưu Đức":"40-123,220",
			 "Mạnh Cầu":"40-112,199",
		"Tôn Thiếu Gia":"40-148,146",
			"Chu Cuồng":"40-324,180",
	   "Ngụy Tổng Quản":"40-324,122",
		"Ngụy Quản Gia":"40-308,195",
		"Bành Tiêm Hào":"50-73,180",
			  "Mã Hiển":"50-231,148",
		  "Hạ Đầu Đảng":"50-252,171",
		"Tần Tổng Quản":"50-36,159",
		 "Tần Quản Gia":"50-73,184",
	// 	  "Lưu Đầu":"60-129,222",
	//  "Tiễn Lão Cửu":"60-148,236",
	// 	  "Tôn Lục":"60-167,74",
	// 	"Vương Mãn":"60-181,87",
	// "Đinh Tiểu Nha":"60-156,226",
	//  "Sở Tổng Quản":"60-205,267",
	//   "Sở Quản Gia":"60-245,229",
	// 	"Tào Thanh":"70-170,248",
	// "Đinh Hạc Niên":"70-172,231",
	//   "Trình Phong":"70-190,210",
	// "Yên Tổng Quản":"70-214,264",
	//  "Yên Quản Gia":"70-138,233",
]);

mapping PlaceTable = (["Trình Lâm Khai":"Ngoài trấn gần ven sông thành tây",
							 "Chu Đồng":"Ngoài trấn gần ven sông thành tây",
						  "Lí Tam Thẩm":"Bên trong thành Ngụycông phủ",
							  "Hứa Thị":"Bên trong thành Ngụycông phủ",
							  "Lưu Đức":"Ngoài thành phía tây bắc",
							 "Mạnh Cầu":"Ngoài trấn gần ven sông thành tây",
							"Chu Cuồng":"Bên trong thành Ngụycông phủ",
						"Ngụy Quản Gia":"Bên trong thành Ngụycông phủ",
								"Lí Đồ":"Lâm truy ngoài thành đích lâm két nam giao",
							  "Lí Lăng":"Lâm truy ngoài thành phía đông bắc đích kiệt thạch trấn nội",
						   "Vương Khải":"Lâm truy ngoài thành phía đông bắc đích kiệt thạch trấn nội",
					   "Khổng Tiểu Phi":"Lâm truy ngoài thành phía đông bắc đích kiệt thạch trấn nội",
							"Thôi Ngọc":"Lâm truy ngoài thành lâm két nam giao đích tiểu kiều giữ",
						  "Tề Quản Gia":"Lâm truy bên trong thành đích điền công phủ",
					   "Lão Vương Thẩm":"Trịnh bên trong thành đích Hàncông phủ",
						   "Mã Đại Hán":"Trịnh ngoài thành đích lê hoa thôn",
							"Triệu Mộc":"Trịnh ngoài thành đích trịnh thành đông giao",
							   "Lâm Vị":"Trịnh ngoài thành đích lê hoa thôn ngoại",
								"Du Tử":"Trịnh ngoài thành đích trịnh thành tây giao",
						 "Tiễn Lão Bát":"Trịnh ngoài thành phía đông bắc đích sông đào bảo vệ thành giữ",
						 "Hàn Quản Gia":"Trịnh bên trong thành đích Hàncông phủ",
							  "Lưu Đầu":"Dĩnh bên trong thành đích phương Tây",
						 "Tiễn Lão Cửu":"Dĩnh bên trong thành đích phương Tây",
							  "Tôn Lục":"Dĩnh ngoài thành phía nam đích Bách Việt thôn",
							"Vương Mãn":"Dĩnh ngoài thành phía nam đích Bách Việt thôn",
						  "Sở Quản Gia":"Dĩnh bên trong thành đích mị bên trong thành",
					"Vương Thiết Tượng":"Hàm Đan bên trong thành đích Hàm Đan thành",
							 "Cước Phu":"Hàm Đan bên trong thành đích Hàm Đan thành",
							 "Lí Phòng":"Hàm Đan ngoài thành phương bắc đích biên thuỳ trấn nhỏ",
							"Bạch Dịch":"Hàm Đan ngoài thành phương bắc đích biên thuỳ trấn nhỏ",
					   "Triệu Quản Gia":"Hàm Đan bên trong thành đích Triệuphủ",
						"Bành Tiêm Hào":"Hàm dương bên trong thành đích lữ phủ",
							  "Mã Hiển":"Hàm dương ngoài thành đích Bình Dương trấn ngoại",
						  "Hạ Đầu Đảng":"Hàm dương ngoài thành đích Bình Dương trấn",
						 "Tần Quản Gia":"Hàm dương bên trong thành đích lữ phủ",
							"Tào Thanh":"Kế bên trong thành đích tào phủ",
						"Đinh Hạc Niên":"Kế bên trong thành đích vương phủ",
						  "Trình Phong":"Kế bên trong thành đích thiện võ thai",
						 "Yên Quản Gia":"Kế bên trong thành đích vương phủ",

]);

mapping CountryTable = (["Trình Lâm Khai":"Ngụy",
							   "Chu Đồng":"Ngụy",
							"Lí Tam Thẩm":"Ngụy",
								"Hứa Thị":"Ngụy",
								"Lưu Đức":"Ngụy",
							   "Mạnh Cầu":"Ngụy",
							  "Chu Cuồng":"Ngụy",
						  "Ngụy Quản Gia":"Ngụy",
								  "Lí Đồ":"Tề",
								"Lí Lăng":"Tề",
							 "Vương Khải":"Tề",
						 "Khổng Tiểu Phi":"Tề",
							  "Thôi Ngọc":"Tề",
							"Tề Quản Gia":"Tề",
						 "Lão Vương Thẩm":"Hàn",
							 "Mã Đại Hán":"Hàn",
							  "Triệu Mộc":"Hàn",
								 "Lâm Vị":"Hàn",
								  "Du Tử":"Hàn",
						   "Tiễn Lão Bát":"Hàn",
						   "Hàn Quản Gia":"Hàn",
								"Lưu Đầu":"Sở",
						   "Tiễn Lão Cửu":"Sở",
								"Tôn Lục":"Sở",
							  "Vương Mãn":"Sở",
							"Sở Quản Gia":"Sở",
					  "Vương Thiết Tượng":"Triệu",
							   "Cước Phu":"Triệu",
							   "Lí Phòng":"Triệu",
							  "Bạch Dịch":"Triệu",
						 "Triệu Quản Gia":"Triệu",
						  "Bành Tiêm Hào":"Tần",
								"Mã Hiển":"Tần",
							"Hạ Đầu Đảng":"Tần",
						   "Tần Quản Gia":"Tần",
							  "Tào Thanh":"Yên",
						  "Đinh Hạc Niên":"Yên",
							"Trình Phong":"Yên",
						   "Yên Quản Gia":"Yên",
]);

string *NameTable = ({});

int sizeof_point = sizeof(PointTable);

// 函数:构造处理
void create() { NameTable = keys(PointTable); } // 生成名字数组

// 函数:获取任务姓名
string get_quest() { return NameTable[random(sizeof_point)]; }

// 函数:获取人物坐标
int get_xy_point(string name)
{
	int z, x, y;

	if (undefinedp(PointTable[name]))
		return 0;

	if (!sscanf(PointTable[name], "%d-%d,%d", z, x, y))
		return 0;

	return z * 1000000 + x * 1000 + y;
}

string get_place_name(string name)
{
	if (undefinedp(PlaceTable[name]))
		return "Không biết chỗ"; //不知所在
	return PlaceTable[name];
}

string get_country_name(string name)
{
	if (undefinedp(CountryTable[name]))
		return "Không biết tên"; //不知名处
	return CountryTable[name] + " Quốc";
}