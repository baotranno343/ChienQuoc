
// 函数：生成二进制码
void SAVE_BINARY() { }

mapping LevelTarget =
        ([
		"1"     : ({ 3281, 3283, 3285, 3310, 3250, 3288, 3221, 3223, 3244, 3230, 3232, 3233, 3234, 3513, 3404,  }),
		"2"     : ({ 3153, 3512, 3514, 3325, 3303, 3156, 3321, 3154, 3155, 3152, 3604, 3505,  }),
		"3"	: ({ 3205, 3235, 3460, 3117, 3243, 3406, 3405, 3421, 3212, 3301, 3311, 3310, 3450, 3452, 3410, 4903, 3242, 3220, 3210, 3211, 3280, 3284, 3282, 3286, 3106, 3304, 3502, }),
		"4"	: ({ 3222, 3511, 3252, 3513, 3501, 3254, 3411, 3412, 3420, 3320, 3302, 3510, 3502, 4910, 3402, 3403, 3401, 3310, 3150, 3155, 3505, 3410, 3413, 3414, 3323, 3324, 3506, 3507, 3322,  }),
		"5"	: ({ 3244, 3224, 3303, 3304, 3310, 3311, 3101, 3102, 3103, 3284, 3241, 3287, 3322, 3325, 3320, 3104,  }),
		"6"	: ({ 3240, 3150, 3153, 3311, 3323, 3324, 3301, 3321, 3154, 3310, 3220, 3156, 3151, 3152, 3211,  }),
		"7"	: ({ 3501, 3502, 3506, 3505, 3507, 3515, 3563, 3453, 3450, 3451, 3455, 3456, 3454, 3460, 3461,  }),
		"8"	: ({ 3451, 3412, 3515, 3456, 3512, 3513, 3404, }),
		"9"	: ({ 3452, 3454, 3451, 3460, 3455, 3456, 3461, }),
		"10"	: ({ 3301, 3302, 3310, 3311, 3244, 3250, 3101, 3103, 3450, 3453, }),
		"11"	: ({ 3709, 3719, 3729, 3731, 3732, 3733, 3734, 3735, 3736, 3737, }),
		"12"	: ({ 3780, 3781, 3760, 3750, 3756, 3766, }),
        ]);
mapping mpMasterObj = ([
			0 : ({"Đoản Mộc Đao","Trường Mâu","Mộc Kiếm","Trường Mộc Côn","Thô Ma Thủ"}),
			10: ({"Đơn Đao","Thiết Mâu","Truy Phong Kiếm","Hàn Thiết Côn","Thanh Đẳng Quyền Sáo","Toái Thạch Tử","Thuý Mộc Kiếm","Thuỷ Mộc Kiếm","Vân Mộng Kiếm",}),
			20: ({"Nguyệt Nha Đao","Hắc Thiết Mâu","Thanh Phong Kiếm","Thanh Trúc Côn","Ngư Lân Quyền Sáo","Liễu Điệp Tiêu","Đào Mộc Kiếm","Linh Mộc Kiếm","Huyền Mộc Kiếm",}),
			30: ({"Hàn Thiết Đao","Mặc Thanh Kích","Kim Xà Kiếm","Đàn Tử Côn","Thanh Đồng Quyền Sáo","Phi Hoàng Thạch","Huyền Hoàng Kiếm","Minh Hoàng Kiếm","Xích Hoàng Kiếm",}),
			40: ({"Trảm Mã Đao","Trọng Linh Thương","Nghênh Phong Trảm","Khu Ma Côn","Tinh Cương Quyền Sáo","Tinh Cương Tiêu","Xích Dương Kiếm","Triều Dương Kiếm","Xích Đảm Kiếm",}),
			50: ({"Kim Hoàn Đao","Huyền Mặc Mâu","Mặc Ngọc Kiếm","Lang Nha Côn","Hoàng Kim Lung Thủ","Như Ý Châu","Ám Thanh Kiếm","Nhiếp Hồn Kiếm","Hàn Thanh Kiếm"}),
			60: ({"Xích Luyện Đao","Cự Nha Thương","Long Xí Giản","Huyền Văn Côn","Kim Lũ Quyền Sáo","Tụ Tiễn","Chân Vũ Kiếm","Huyền Hồn Kiếm","Âm Dương Kiếm",}),
			]);
mapping LevelNpc =
        ([
                "1" : "Gà Núi",
                "2" : "Ong Mật",
                "3" : "Ếch Đốm",
                "5" : "Bù Nhìn Tinh",
                "6" : "Kiến Đen",
                "7" : "Ếch Tử Mẫu",
                "11" : "Sở Quân Đao Binh",
                "12" : "Gấu Ù",
                "13" : "Khỉ Đầu Chó",
                "14" : "Bọ Ngựa Càng Xanh",
                "16" : "Độc Nhãn Thú",
                "17" : "Côn Đồ",
                "18" : "Tay Sai",
                "21" : "Quỷ Hỏa",
                "22" : "Ác Lão Đầu",
                "23" : "Ác Đồ",
                "24" : "Cuồng Đồ",
                "25" : "Tuần Thành Tiểu Binh",
                "26" : "Thổ Phỉ",
                "27" : "Triệu Quốc Tuần Binh",
                "28" : "Quỷ Mị",
                "29" : "Khô Lâu Binh",
                "31" : "Hạt Vĩ Hạt",
                "32" : "Lang Yêu",
                "33" : "Trư Yêu",
                "34" : "Sài Cẩu",
                "36" : "Thuỷ Tặc",
                "37" : "Con Cóc",
                "38" : "Hắc Hùng",
                "39" : "Xích Viêm Xà",
                "40" : "Đường Lang Yêu",
                "41" : "Binh Tôm",
                "42" : "Tướng Cua",
                "46" : "Tráng Đinh",
                "47" : "Khổ Dịch",
                "48" : "Lao Dịch",
                "51" : "Lục Xác Tri Chu",
                "52" : "Đại Bổn Hùng",
                "53" : "Võng Lượng",
                "54" : "Hoa Báo Tinh",
                "55" : "Sài Lang",
                "56" : "Yên Quốc Đao Thuẫn Binh",
                "57" : "Yên Quốc Kiếm Thuẫn Binh",
                "58" : "Yên Quốc Thương Binh",
                "62" : "Triệu Quốc Đao Thuẫn Binh",
                "63" : "Triệu Quốc Kiếm Thuẫn Binh",
                "64" : "Triệu Quốc Cung Binh",
                "66" : "Tần Quốc Đao Thuẫn Binh",
                "67" : "Tần Quốc Thương Binh",
                "68" : "Tần Quốc Cung Binh",
                "72" : "Kiếp Phỉ",
                "73" : "Mật Thám",
                "74" : "Thủy Quỷ",
                "76" : "Quán Trung Yêu",
                "77" : "Oan Hồn",
                "78" : "Dịch Quỷ",
                "79" : "Ác Linh",
                "81" : "Đồng Giáp Thi",
                "82" : "Thiết Giáp Thi",
                "83" : "Đao Thuẫn Khô Lâu",
                "84" : "Cương Thi",
                "85" : "Thạch Sư",
                "86" : "Đao Dũng",
                "87" : "Cung Tiễn Thạch Dũng",
                "88" : "Thương Dũng",
                "89" : "Kiếm Dũng",
                "91" : "Khô Lâu Yêu",
                "92" : "Thi Ma",
                "93" : "Oán Linh",
                "96" : "Kim Tinh",
                "97" : "Mộc Tinh",
                "98" : "Thuỷ Tinh",
                "99" : "Hoả Tinh",
                "100" : "Thổ Tinh",
                "102" : "Quán Trung Tiên",
                "104" : "Quy Tiên Nhân",
                "106" : "Thiên Cương Môn Thủ",
                "107" : "Địa Sát Môn Thủ",
                "108" : "Thái Cực Môn Thủ",
                "112" : "Đao Hồn",
                "113" : "Kiếm Hồn",
                "114" : "Thương Hồn",

        ]);
mapping managername =
        ([
		"Đào Hoa Nguyên"        : "Thôn Dân",
                "Thục Sơn"          : "Tư Khố",
		"Cấm Vệ Quân"        : "Quan Hậu Cần",
                "Đường Môn"          : "Đường Tổng Quản",
		"Mao Sơn"          : "Quỷ Tốt",
                "Côn Luân"        : "Thạch Sư",
		"Vân Mộng Cốc"        : "Dược Đồng",
        ]);
mapping fightmap =
        ([
		"Đào Hoa Nguyên"        : 891,
                "Thục Sơn"          : 892,
		"Cấm Vệ Quân"        : 893,
                "Đường Môn"          : 894,
		"Mao Sơn"          : 895,
                "Côn Luân"        : 896,
		"Vân Mộng Cốc"        : 897,
        ]);
mapping levelNPC1 = ([
	0 : 	([
		"Gà Núi" : "Tân Thủ Thôn có thể bắt được Gà Núi",
		"Thỏ Hoang" : "Tân Thủ Thôn có thể bắt được Thỏ Hoang",
		"Ong Mật" : "Thanh Khê có thể bắt được Ong Mật",
		"Kiến Nhỏ" : "Thanh Khê có thể bắt được Kiến Nhỏ",
		"Ếch Đốm" : "U Cốc có thể bắt được Ếch Đốm",
		]),
	1:	([
		"Kiến Đen" : "Ba Khâu có thể bắt được Kiến Đen",
		"Ếch Tử Mẫu" : "Ba Khâu có thể bắt được Ếch Tử Mẫu",		
		]),
	2:	([
		"Sở Quân Đao Binh" : "Sở Phương Thành có thể bắt được Sở Quân Đao Binh",
		"Sở Quân Kiếm Binh" : "Sở Phương Thành có thể bắt được Sở Quân Kiếm Binh",
		"Kỳ Nhông" : "Hoa Sơn có thể bắt được Kỳ Nhông",
		"Độc Giác Tiên" : "Đào Hoa Nguyên có thể bắt được Độc Giác Tiên",
		"Thích Vĩ Phong" : "Đào Hoa Nguyên có thể bắt được Thích Vĩ Phong",
		"Gấu Ù" : "Hoa Sơn có thể bắt được Gấu Ù",
		"Khỉ Đầu Chó" : "Triều Dương Phong có thể bắt được Khỉ Đầu Chó",
		"Bọ Ngựa Càng Xanh" : "Đào Hoa Nguyên có thể bắt được Bọ Ngựa Càng Xanh",
		]),
	3:	([
		"Độc Nhãn Thú" : "Thủ Dương Sơn có thể bắt được Độc Nhãn Thú",		
		]),
	4: 	([
		"Quỷ Hỏa" : "Bờ Vô Định Hà có thể bắt được Quỷ Hỏa",
		"U Linh" : "Vô Định Hà có thể bắt được U Linh",
		"Phi Tặc" : "Mã Lăng có thể bắt được Phi Tặc",		
		"Tuần Thành Tiểu Binh" : "Cự Lộc có thể bắt được Tuần Thành Tiểu Binh",	
		]),
	5: 	([
		"Thảo Khấu" : "Quế Lăng có thể bắt được Thảo Khấu",
		"Triệu Quốc Tuần Binh" : "Cự Lộc có thể bắt được Triệu Quốc Tuần Binh",	
		"Khô Lâu Binh" : "Trường Bình có thể bắt được Khô Lâu Binh",		
		]),
	6:	([
		"Hạt Vĩ Hạt" : "Ranh Giới Đầm Lầy có thể bắt được Hạt Vĩ Hạt",
		"Chu Chu Quái" : "Ranh Giới Đầm Lầy có thể bắt được Chu Chu Quái",
		"Độc Thứ Phong" : "Ranh Giới Đầm Lầy có thể bắt được Độc Thứ Phong",
		"Ngưu Đầu Quái" : "Đại Biệt Sơn có thể bắt được Ngưu Đầu Quái",		
		]),
	7:	([
		"Thuỷ Tặc" : "Xích Bích có thể bắt được Thuỷ Tặc",
		"Con Cóc" : "Thái Hồ có thể bắt được Con Cóc",
		"Hắc Hùng" : "Chân Núi Thái Sơn có thể bắt được Hắc Hùng",
		"Xích Viêm Xà" : "Thái Sơn có thể bắt được Xích Viêm Xà",
		"Đường Lang Yêu" : "Thái Sơn có thể bắt được Đường Lang Yêu",		
		]),		
	8:	([
		"Binh Tôm" : "Đông Hải Ngư Thôn có thể bắt được Binh Tôm",
		]),
	9:	([
		"Tráng Đinh" : "Kênh Trịnh Quốc có thể bắt được Tráng Đinh",
		]),	
	10:	([
		"Lục Xác Tri Chu" : "Trường Bạch Sơn có thể bắt được Lục Xác Tri Chu",
		"Đại Bổn Hùng" : "Ngọc Trụ Phong có thể bắt được Đại Bổn Hùng",
		"Võng Lượng" : "Bạch Vân Phong có thể bắt được Võng Lượng",
		]),
	11:	([
		"Yên Quốc Đao Thuẫn Binh" :	"Yên Trường Thành có thể bắt được Yên Quốc Đao Thuẫn Binh",
		"Yên Quốc Kiếm Thuẫn Binh" : "Yên Trường Thành có thể bắt được Yên Quốc Kiếm Thuẫn Binh",
		"Yên Quốc Thương Binh": "Yên Trường Thành có thể bắt được Yên Quốc Thương Binh",
		]),					
	12:	([
		"Triệu Quốc Đao Thuẫn Binh" : "Triệu Trường Thành có thể bắt được Triệu Quốc Đao Thuẫn Binh",
		"Triệu Quốc Kiếm Thuẫn Binh" : "Triệu Trường Thành có thể bắt được Triệu Quốc Kiếm Thuẫn Binh",
		"Triệu Quốc Cung Binh" : "Triệu Trường Thành có thể bắt được Triệu Quốc Cung Binh",	
		]),
	13:	([
		"Tần Quốc Thương Binh" : "Tần Trường Thành có thể bắt được Tần Quốc Thương Binh",
		]),
	14:	([
		"Thủy Quỷ": "Loan Đạo có thể bắt được Thủy Quỷ",
		]),
	15:	([
		"Quán Trung Yêu" : "Linh Cốc Động tầng 1 có thể bắt được Quán Trung Yêu",
		"Ác Linh" : "Linh Cốc Động tầng 3 có thể bắt được Ác Linh",
		]),
	16:	([
		"Đồng Giáp Thi" : "Linh Cốc Động tầng 1 có thể bắt được Đồng Giáp Thi",
		"Thị Vệ Vong Linh" : "Linh Cốc Động tầng 2 có thể bắt được Thị Vệ Vong Linh",
		"Thiết Giáp Thi" : "Linh Cốc Động tầng 2 có thể bắt được Thiết Giáp Thi",
		"Đao Thuẫn Khô Lâu" : "Hầm Vạn Nhân có thể bắt được Đao Thuẫn Khô Lâu",
		"Kiếm Thuẫn Khô Lâu" : "Hầm Vạn Nhân có thể bắt được Kiếm Thuẫn Khô Lâu",
		"Song Đao Khô Lâu" : "Hầm Vạn Nhân có thể bắt được Song Đao Khô Lâu",
		"Cương Thi" : "Hầm Vạn Nhân tầng 4 có thể bắt được Cương Thi",
		]),
	17:	([
		"Thạch Sư" : "Tướng Quân Cổ Mộ tầng 1 có thể bắt được Thạch Sư",		
		"Đao Dũng" : "Tướng Quân Cổ Mộ tầng 2 có thể bắt được Đao Dũng",
		"Cung Tiễn Thạch Dũng" : "Tướng Quân Cổ Mộ tầng 3 có thể bắt được Cung Tiễn Thạch Dũng",
		]),
	18:	([
		"Tà Linh" : "Khốn Ma Trận tầng 2 có thể bắt được Tà Linh",
		"Thi Ma" : "Khốn Ma Trận tầng 2 có thể bắt được Thi Ma",
		]),
	19:	([
		"Kim Tinh" : "Hư Lăng Động có thể bắt được Kim Tinh",		
		]),
	20:	([
		"Quán Trung Tiên" : "Cầu Cửu Khúc có thể bắt được Quán Trung Tiên",
		"Quy Tiên Nhân" : "Cầu Cửu Khúc có thể bắt được Quy Tiên Nhân",		
		]),
	21:	([
		"Thủ Trận Thiên Binh" : "Thiên Môn Trận tầng 1 có thể bắt được Thủ Trận Thiên Binh",
		"Thủ Trận Thần Tướng" : "Thiên Môn Trận tầng 1 có thể bắt được Thủ Trận Thần Tướng",
		"Thái Cực Môn Thủ" : "Thiên Môn Trận tầng 2 có thể bắt được Thái Cực Môn Thủ",
		]),
	22:	([
		"Đao Hồn" : "Tru Tiên Trận tầng 3 có thể bắt được Đao Hồn",
		"Kiếm Hồn" : "Tru Tiên Trận tầng 4 có thể bắt được Kiếm Hồn",
		"Thương Hồn" : "Tru Tiên Trận tầng 5 có thể bắt được Thương Hồn",
		]),	
	]);    
	
mapping LevelTarget1 = ([
	2:	([
		"Phá Tổn Đầu Khôi" : "Sở Phương Thành đánh Sở Quân Đao Binh sẽ có Phá Tổn Đầu Khôi",
		"Phá Tổn Giáp" : "Sở Phương Thành đánh Sở Quân Kiếm Binh sẽ có Phá Tổn Giáp",
		"Xà Chi Quán" : "Hoa Sơn đánh Kỳ Nhông sẽ có Xà Chi Quán",
		"Cánh Bọ Cánh Cứng" : "Đào Hoa Nguyên đánh Độc Giác Tiên sẽ có Cánh Bọ Cánh Cứng",
		"Ngòi Ong" : "Đào Hoa Nguyên đánh Thích Vĩ Phong sẽ có Ngòi Ong",
		"Xương Cá" : "Hoa Sơn đánh Gấu Ù sẽ có Xương Cá",
		"Đuôi Khỉ" : "Triều Dương Phong đánh Khỉ Đầu Chó sẽ có Đuôi Khỉ",
		"Càng Bọ Ngựa" : "Đào Hoa Nguyên đánh Bọ Ngựa Càng Xanh sẽ có Càng Bọ Ngựa",
		"Cánh Bọ Ngựa" : "Đào Hoa Nguyên đánh Bọ Ngựa Càng Xanh sẽ có Cánh Bọ Ngựa",		
		]),
	3:	([
		"Đuôi Chó" : "Thủ Dương Sơn đánh Độc Nhãn Thú sẽ có Đuôi Chó",
		]),
	4:	([
		"Hoả Chủng" : "Vô Định Hà đánh Quỷ Hỏa sẽ có Hoả Chủng",
		"Châu Xuyến" : "Bờ Vô Định Hà đánh U Linh sẽ có Châu Xuyến",
		"Núm Vú" : "Mã Lăng đánh Phi Tặc sẽ có Núm Vú",
		"Phi Hành Phiến" : "Mã Lăng đánh Phi Tặc sẽ có Phi Hành Phiến",
		"Yêu Bài" : "Cự Lộc đánh Tuần Thành Tiểu Binh sẽ có Yêu Bài",		
		]),
	5:	([
		"Búi Tóc" : "Quế Lăng đánh Thảo Khấu sẽ có Búi Tóc",
		"Cẩu Bì Dược Cao" : "Quế Lăng đánh Thảo Khấu sẽ có Cẩu Bì Dược Cao",
		"Phá Cựu Đầu Khôi" : "Cự Lộc đánh Triệu Quốc Tuần Binh sẽ có Phá Cựu Đầu Khôi",
		"Phá Cựu Khôi Giáp" : "Cự Lộc đánh Triệu Quốc Tuần Binh sẽ có Phá Cựu Khôi Giáp",
		"Hài Cốt Toái Phiến" : "Trường Bình đánh Khô Lâu Binh sẽ có Hài Cốt Toái Phiến",		
		]),
	6:	([
		"Đuôi Bọ Cạp" : "Ranh Giới Đầm Lầy đánh Hạt Vĩ Hạt sẽ có Đuôi Bọ Cạp",
		"Tơ Nhện" : "Ranh Giới Đầm Lầy đánh Chu Chu Quái sẽ có Tơ Nhện",
		"Kịch Độc Châm" : "Ranh Giới Đầm Lầy đánh Độc Thứ Phong sẽ có Kịch Độc Châm",
		"Gân Bò" : "Chân Núi Đại Biệt đánh Ngưu Đầu Quái sẽ có Gân Bò",
		"Khoen Mũi" : "Chân Núi Đại Biệt đánh Ngưu Đầu Quái sẽ có Khoen Mũi",
		]),
	7:	([
		"Thuỷ Tặc Đầu Cân" : "Xích Bích đánh Thuỷ Tặc sẽ có Thuỷ Tặc Đầu Cân",
		"Chân Ếch" : "Thái Hồ đánh Con Cóc sẽ có Chân Ếch",
		"Thiểm Quang Thạch Đầu" : "Chân Núi Thái Sơn đánh Hắc Hùng sẽ có Thiểm Quang Thạch Đầu",
		"Đuôi Thằn Lằn" : "Thái Sơn đánh Xích Viêm Xà sẽ có Đuôi Thằn Lằn",
		"Lục Sắc Tiểu Thạch" : "Thái Sơn đánh Đường Lang Yêu sẽ có Lục Sắc Tiểu Thạch",		
		]),
	8:	([
		"Càng Lớn" : "Đông Hải Ngư Thôn đánh Binh Tôm sẽ có Càng Lớn",
		]),
	9:	([
		"Phá Bố Y" : "Kênh Trịnh Quốc đánh Tráng Đinh sẽ có Phá Bố Y",
		]),
	10:	([
		"Mạng Nhện" : "Trường Bạch Sơn đánh Lục Xác Tri Chu sẽ có Mạng Nhện",
		"Tơ Nhện" : "Trường Bạch Sơn đánh Lục Xác Tri Chu sẽ có Tơ Nhện",
		"Hồng Sắc Tiểu Thạch" : "Ngọc Trụ Phong đánh Đại Bổn Hùng sẽ có Hồng Sắc Tiểu Thạch",
		"Xương Cá" : "Ngọc Trụ Phong đánh Đại Bổn Hùng sẽ có Xương Cá",
		"Tứ Giả Di Vật" : "Bạch Vân Phong đánh Võng Lượng sẽ có Tứ Giả Di Vật",		
		]),
	11:	([
		"Tua Mũ" : "Yên Trường Thành đánh Yên Quốc Đao Thuẫn Binh sẽ có Tua Mũ",
		"Phá Cựu Đầu Khôi" : "Yên Trường Thành đánh Yên Quốc Kiếm Thuẫn Binh sẽ có Phá Cựu Đầu Khôi",
		"Phá Cựu Khôi Giáp" : "Yên Trường Thành đánh Yên Quốc Thương Binh sẽ có Phá Cựu Khôi Giáp",		
		]),
	12:	([
		"Chuôi Đao" : "Triệu Trường Thành đánh Triệu Quốc Đao Thuẫn Binh sẽ có Chuôi Đao",
		"Vỏ Kiếm" : "Triệu Trường Thành đánh Triệu Quốc Kiếm Thuẫn Binh sẽ có Vỏ Kiếm",
		"Bao Đựng Tên" : "Triệu Trường Thành đánh Triệu Quốc Cung Binh sẽ có Bao Đựng Tên",		
		]),
	13:	([
		"Đầu Thương" : "Tần Trường Thành đánh Tần Quốc Thương Binh sẽ có Đầu Thương",
		]),
	14:	([
		"Ngư Xoa" : "Loan Đạo đánh Thủy Quỷ sẽ có Ngư Xoa",
		]),
	15:	([
		"Đồng Quán" : "Linh Cốc Động tầng 1 đánh Quán Trung Yêu sẽ có Đồng Quán",
		"Hoàng Sắc Tiểu Thạch" : "Linh Cốc Động tầng 2 đánh Võng Lượng Quỷ sẽ có Hoàng Sắc Tiểu Thạch",
		"Hủ Cốt" : "Linh Cốc Động tầng 3 đánh Ác Linh sẽ có Hủ Cốt",		
		]),
	16:	([
		"Đồng Hài" : "Linh Cốc Động tầng 1 đánh Đồng Giáp Thi sẽ có Đồng Hài",
		"Thất Sắc Xuyến Châu" : "Linh Cốc Động tầng 2 đánh Thị Vệ Vong Linh sẽ có Thất Sắc Xuyến Châu",
		"Thiết Hài" : "Linh Cốc Động tầng 2 đánh Thiết Giáp Thi sẽ có Thiết Hài",
		"Cốt Thuẫn" : "Hầm Vạn Nhân tầng 1 đánh Đao Thuẫn Khô Lâu sẽ có Cốt Thuẫn",
		"Khô Đầu Lâu" : "Khốn Ma Trận tầng 1 đánh Kiếm Thuẫn Khô Lâu sẽ có Khô Đầu Lâu",
		"Đào Mộc Đinh" : "Hầm Vạn Nhân tầng 2 đánh Song Đao Khô Lâu sẽ có Đào Mộc Đinh",
		"Cương Thi Quán" : "Hầm Vạn Nhân tầng 4 đánh Cương Thi sẽ có Cương Thi Quán",
		"Toái Ngọc" : "Tướng Quân Cổ Mộ tầng 1 đánh Thạch Sư sẽ có Toái Ngọc",		
		]),
	17:	([
		"Đào Dũng Chi Thử" : "Tướng Quân Cổ Mộ tầng 2 đánh Đao Dũng sẽ có Đào Dũng Chi Thử",
		"Đào Dũng Tí" : "Tướng Quân Cổ Mộ tầng 3 đánh Cung Tiễn Thạch Dũng sẽ có Đào Dũng Tí",
		]),
	18:	([
		"Toả Ma Liên" : "Khốn Ma Trận tầng 2 đánh Tà Linh sẽ có Toả Ma Liên",
		"Giáp Trụ " : "Khốn Ma Trận tầng 2 đánh Thi Ma sẽ có Giáp Trụ ",		
		]),
	19:	([
		"Tiểu Thái Cực" : "Hư Lăng Động đánh Kim Tinh sẽ có Tiểu Thái Cực",		
		]),
	20:	([
		"Ngọc Cái" : "Cầu Cửu Khúc đánh Quán Trung Tiên sẽ có Ngọc Cái",
		"Mai Rùa" : "Cầu Cửu Khúc đánh Quy Tiên Nhân sẽ có Mai Rùa",
		"Trường Thọ Thạch" : "Cầu Cửu Khúc đánh Quy Tiên Nhân sẽ có Trường Thọ Thạch",		
		]),
	21:	([
		"Ngọc Thúc Kế" : "Thiên Môn Trận tầng 1 đánh Thủ Trận Thiên Binh sẽ có Ngọc Thúc Kế",
		"Hoả Phượng Dực" : "Thiên Môn Trận tầng 1 đánh Thủ Trận Thần Tướng sẽ có Hoả Phượng Dực",
		"Phất Trần" : "Thiên Môn Trận tầng 2 đánh Thái Cực Môn Thủ sẽ có Phất Trần",
		]),
	22:	([
		"Chuôi Đao Hàn Thiết" : "Tru Tiên Trận tầng 3 đánh Đao Hồn sẽ có Chuôi Đao Hàn Thiết",
		"Chuôi Kiếm Hàn Thiết" : "Tru Tiên Trận tầng 4 đánh Kiếm Hồn sẽ có Chuôi Kiếm Hàn Thiết",
		"Đầu Thương Hàn Thiết" : "Tru Tiên Trận tầng 5 đánh Thương Hồn sẽ có Đầu Thương Hàn Thiết",
		]),				
	]);
mapping mpSiku = ([
1:({
	({"Trái quýt","Chủ Tửu Lâu"}),({"Khoai Lang","Chủ Tửu Lâu"}),({"Nước Trong","Chủ Tửu Lâu"}),({"Chính Khí Tán","Chủ Tiệm Y Dược"}),({"Hành Quân Tán","Chủ Tiệm Y Dược"}),({"Thạch Tín","Chủ Tiệm Y Dược"}),({"Đoản Mộc Đao","Chủ Tiệm Vũ Khí Tân Thủ Thôn"}),({"Trường Mâu","Chủ Tiệm Vũ Khí Tân Thủ Thôn"}),
	({"Mộc Kiếm","Chủ Tiệm Vũ Khí Tân Thủ Thôn"}),({"Trường Mộc Côn","Chủ Tiệm Vũ Khí Tân Thủ Thôn"}),
	({"Thô Ma Thủ","Chủ Tiệm Vũ Khí Tân Thủ Thôn"}),({"Ma Y","Chủ Tiệm Giáp Trụ  Tân Thủ Thôn"}),({"Ma Y","Chủ Tiệm Giáp Trụ  Tân Thủ Thôn"}),({"Ma Bố Mão","Chủ Tiệm Giáp Trụ  Tân Thủ Thôn"}),
	({"Ma Bố Mão","Chủ Tiệm Giáp Trụ  Tân Thủ Thôn"}),({"Đằng Mạn Hài","Chủ Tiệm Giáp Trụ  Tân Thủ Thôn"}),({"Bùa Giấy","Chủ Tiệm Tạp Hoá"}),({"Đậu Nành","Chủ Tiệm Tạp Hoá"}),({"Dây Càn Khôn","Chủ Tiệm Tạp Hoá"}),
   }),
2:({
	({"Miên Bố Y","Chủ Tiệm Giáp Trụ  Sở Quốc"}),({"Miên Bố Y","Chủ Tiệm Giáp Trụ  Sở Quốc"}),({"Miên Bố Mão","Chủ Tiệm Giáp Trụ  Sở Quốc"}),({"Miên Bố Mão","Chủ Tiệm Giáp Trụ  Sở Quốc"}),({"Bố Hài","Chủ Tiệm Giáp Trụ  Sở Quốc"}),({"Đơn Đao","Chủ Tiệm Vũ Khí Sở Quốc"}),({"Thiết Mâu","Chủ Tiệm Vũ Khí Sở Quốc"}),({"Truy Phong Kiếm","Chủ Tiệm Vũ Khí Sở Quốc"}),
	({"Hàn Thiết Côn","Chủ Tiệm Vũ Khí Sở Quốc"}),({"Thanh Đẳng Quyền Sáo","Chủ Tiệm Vũ Khí Sở Quốc"}),({"Toái Thạch Tử","Chủ Tiệm Vũ Khí Hàn Quốc"}),({"Thuý Mộc Kiếm","Chủ Tiệm Vũ Khí Tề Quốc"}),({"Thuỷ Mộc Kiếm","Chủ Tiệm Vũ Khí Tần Quốc"}),({"Vân Mộng Kiếm","Chủ Tiệm Vũ Khí Ngụy Quốc"}),
   }),
3:({
	({"Nguyệt Nha Đao","Chủ Tiệm Vũ Khí Yên Quốc"}),({"Hắc Thiết Mâu","Chủ Tiệm Vũ Khí Chu Quốc"}),({"Thanh Phong Kiếm","Chủ Tiệm Vũ Khí Yên Quốc"}),
	({"Thanh Trúc Côn","Chủ Tiệm Vũ Khí Chu Quốc"}),({"Ngư Lân Quyền Sáo","Chủ Tiệm Vũ Khí Triệu Quốc"}),({"Liễu Điệp Tiêu","Chủ Tiệm Vũ Khí Hàn Quốc"}),
	({"Đào Mộc Kiếm","Chủ Tiệm Vũ Khí Tề Quốc"}),({"Linh Mộc Kiếm","Chủ Tiệm Vũ Khí Tần Quốc"}),({"Huyền Mộc Kiếm","Chủ Tiệm Vũ Khí Ngụy Quốc"}),
	({"Hàn Thiết Đao","Chủ Tiệm Vũ Khí Yên Quốc"}),({"Mặc Thanh Kích","Chủ Tiệm Vũ Khí Chu Quốc"}),({"Kim Xà Kiếm","Chủ Tiệm Vũ Khí Yên Quốc"}),
	({"Đàn Tử Côn","Chủ Tiệm Vũ Khí Chu Quốc"}),({"Thanh Đồng Quyền Sáo","Chủ Tiệm Vũ Khí Triệu Quốc"}),
	({"Phi Hoàng Thạch","Chủ Tiệm Vũ Khí Hàn Quốc"}),({"Huyền Hoàng Kiếm","Chủ Tiệm Vũ Khí Tề Quốc"}),
	({"Minh Hoàng Kiếm","Chủ Tiệm Vũ Khí Tần Quốc"}),({"Xích Hoàng Kiếm","Chủ Tiệm Vũ Khí Ngụy Quốc"}),
	({"Bì Y","Chủ Tiệm Giáp Trụ  Triệu Quốc"}),({"Bì Quần","Chủ Tiệm Giáp Trụ  Triệu Quốc"}),({"Ti Trù Y","Chủ Tiệm Giáp Trụ  Triệu Quốc"}),
	({"Ti Trù Quần","Chủ Tiệm Giáp Trụ  Triệu Quốc"}),({"Thanh Liễu Giáp","Chủ Tiệm Giáp Trụ  Yên Quốc"}),({"Thanh Liễu Quần","Chủ Tiệm Giáp Trụ  Yên Quốc"}),
	({"Sa Trường Giáp","Chủ Tiệm Giáp Trụ  Chu Quốc"}),({"Sa Trường Quần","Chủ Tiệm Giáp Trụ  Chu Quốc"}),({"Bích Long Y","Chủ Tiệm Giáp Trụ  Yên Quốc"}),({"Bích Long Quần","Chủ Tiệm Giáp Trụ  Yên Quốc"}),
	({"Cuồng Chiến Y","Chủ Tiệm Giáp Trụ  Chu Quốc"}),({"Cuồng Chiến Quần","Chủ Tiệm Giáp Trụ  Chu Quốc"}),
	({"Tuỳ Phong Y","Chủ Tiệm Giáp Trụ  Hàn Quốc"}),({"Thiên Thủy Y","Chủ Tiệm Giáp Trụ  Hàn Quốc"}),({"Tuỳ Phong Quần","Chủ Tiệm Giáp Trụ  Hàn Quốc"}),({"Thiên Thuỷ Quần","Chủ Tiệm Giáp Trụ  Hàn Quốc"}),
	({"Tế Ma Y","Chủ Tiệm Giáp Trụ  Tần Quốc"}),({"Thanh Long Y","Chủ Tiệm Giáp Trụ  Tần Quốc"}),({"Tế Ma Quần","Chủ Tiệm Giáp Trụ  Tần Quốc"}),({"Thanh Long Quần","Chủ Tiệm Giáp Trụ  Tần Quốc"}),({"Cổ Đằng Giáp","Chủ Tiệm Giáp Trụ  Tề Quốc"}),
	({"Ngọc Lộ Y","Chủ Tiệm Giáp Trụ  Tề Quốc"}),({"Cổ Đằng Quần","Chủ Tiệm Giáp Trụ  Tề Quốc"}),({"Ngọc Lộ Quần","Chủ Tiệm Giáp Trụ  Tề Quốc"}),({"Cổ Giáp","Chủ Tiệm Giáp Trụ  Ngụy Quốc"}),({"Truyện Phong Y","Chủ Tiệm Giáp Trụ  Ngụy Quốc"}),
	({"Cổ Giáp Quần","Chủ Tiệm Giáp Trụ  Ngụy Quốc"}),
	({"Tuyện Phong Quần","Chủ Tiệm Giáp Trụ  Ngụy Quốc"}),({"Bì Cách Mão","Chủ Tiệm Giáp Trụ  Triệu Quốc"}),({"Ti Trù Mão","Chủ Tiệm Giáp Trụ  Triệu Quốc"}),({"Bì Tử Đầu Cân","Chủ Tiệm Giáp Trụ  Triệu Quốc"}),({"Ti Trù Đầu Cân","Chủ Tiệm Giáp Trụ  Triệu Quốc"}),
	({"Thanh Liễu Mão","Chủ Tiệm Giáp Trụ  Yên Quốc"}),
	({"Bích Long Mão","Chủ Tiệm Giáp Trụ  Yên Quốc"}),({"Thanh Liễu Đầu Cân","Chủ Tiệm Giáp Trụ  Yên Quốc"}),({"Bích Long Đầu Cân","Chủ Tiệm Giáp Trụ  Yên Quốc"}),({"Sa Trường Mão","Chủ Tiệm Giáp Trụ  Chu Quốc"}),({"Cuồng Chiến Quán","Chủ Tiệm Giáp Trụ  Chu Quốc"}),
	({"Sa Trường Đầu Cân","Chủ Tiệm Giáp Trụ  Chu Quốc"}),
	({"Cuồng Chiến Đầu Cân","Chủ Tiệm Giáp Trụ  Chu Quốc"}),({"Tuỳ Phong Mão","Chủ Tiệm Giáp Trụ  Hàn Quốc"}),({"Thiên Thuỷ Mão","Chủ Tiệm Giáp Trụ  Hàn Quốc"}),
	({"Tuỳ Phong Đầu Cân","Chủ Tiệm Giáp Trụ  Hàn Quốc"}),({"Thiên Thuỷ Đầu Cân","Chủ Tiệm Giáp Trụ  Hàn Quốc"}),({"Tế Ma Mão","Chủ Tiệm Giáp Trụ  Tần Quốc"}),({"Thanh Long Mão","Chủ Tiệm Giáp Trụ  Tần Quốc"}),({"Tế Ma Đầu Cân","Chủ Tiệm Giáp Trụ  Tần Quốc"}),
	({"Thanh Long Đầu Cân","Chủ Tiệm Giáp Trụ  Tần Quốc"}),({"Cổ Đằng Mão","Chủ Tiệm Giáp Trụ  Tề Quốc"}),({"Ngọc Lộ Mão","Chủ Tiệm Giáp Trụ  Tề Quốc"}),({"Cổ Đằng Đầu Cân","Chủ Tiệm Giáp Trụ  Tề Quốc"}),({"Ngọc Lộ Đầu Cân","Chủ Tiệm Giáp Trụ  Tề Quốc"}),({"Cổ Giáp Mão","Chủ Tiệm Giáp Trụ  Ngụy Quốc"}),
	({"Truyện Phong Quán","Chủ Tiệm Giáp Trụ  Ngụy Quốc"}),({"Cổ Giáp Đầu Cân","Chủ Tiệm Giáp Trụ  Ngụy Quốc"}),({"Truyện Phong Đầu Cân","Chủ Tiệm Giáp Trụ  Ngụy Quốc"}),({"Bì Cách Hài","Chủ Tiệm Trang Sức Triệu Quốc"}),({"Ti Trù Hài","Chủ Tiệm Trang Sức Triệu Quốc"}),({"Thanh Liễu Hài","Chủ Tiệm Trang Sức Yên Quốc"}),
	({"Bích Long Hài","Chủ Tiệm Trang Sức Yên Quốc"}),({"Sa Trường Hài","Chủ Tiệm Trang Sức Chu Quốc"}),({"Cuồng Chiến Lý","Chủ Tiệm Trang Sức Chu Quốc"}),({"Tùy Phong Hài","Chủ Tiệm Trang Sức Hàn Quốc"}),({"Thiên Thủy Hài","Chủ Tiệm Trang Sức Hàn Quốc"}),({"Tế Ma Hài","Chủ Tiệm Trang Sức Tần Quốc"}),
	({"Thanh Long Hài","Chủ Tiệm Trang Sức Tần Quốc"}),
	({"Cổ Đằng Hài","Chủ Tiệm Trang Sức Tề Quốc"}),({"Ngọc Lộ Hài","Chủ Tiệm Trang Sức Tề Quốc"}),({"Cổ Giáp Hài","Chủ Tiệm Trang Sức Ngụy Quốc"}),({"Truyện Phong Lý","Chủ Tiệm Trang Sức Ngụy Quốc"}),({"Bì Cách Yêu Đới","Chủ Tiệm Trang Sức Triệu Quốc"}),({"Ti Trù Yêu Đới","Chủ Tiệm Trang Sức Triệu Quốc"}),
	({"Thanh Liễu Yêu Đới","Chủ Tiệm Trang Sức Yên Quốc"}),({"Bích Long Yêu Đới","Chủ Tiệm Trang Sức Yên Quốc"}),({"Sa Trường Yêu Đới","Chủ Tiệm Trang Sức Chu Quốc"}),({"Cuồng Chiến Yêu Đới","Chủ Tiệm Trang Sức Chu Quốc"}),({"Tuỳ Phong Yêu Đới","Chủ Tiệm Trang Sức Hàn Quốc"}),({"Thiên Thuỷ Yêu Đới","Chủ Tiệm Trang Sức Hàn Quốc"}),
	({"Tế Ma Yêu Đới","Chủ Tiệm Trang Sức Tần Quốc"}),
	({"Thanh Long Yêu Đới","Chủ Tiệm Trang Sức Tần Quốc"}),({"Cổ Đằng Yêu Đới","Chủ Tiệm Trang Sức Tề Quốc"}),({"Ngọc Lộ Yêu Đới","Chủ Tiệm Trang Sức Tề Quốc"}),({"Cổ Giáp Yêu Đới","Chủ Tiệm Trang Sức Ngụy Quốc"}),({"Truyện Phong Yêu Đới","Chủ Tiệm Trang Sức Ngụy Quốc"}),
   }),
4:({
	({"Trảm Mã Đao","Chủ Tiệm Vũ Khí Yên Quốc"}),({"Trọng Linh Thương","Chủ Tiệm Vũ Khí Chu Quốc"}),({"Nghênh Phong Trảm","Chủ Tiệm Vũ Khí Yên Quốc"}),({"Khu Ma Côn","Chủ Tiệm Vũ Khí Chu Quốc"}),({"Tinh Cương Quyền Sáo","Chủ Tiệm Vũ Khí Triệu Quốc"}),({"Tinh Cương Tiêu","Chủ Tiệm Vũ Khí Hàn Quốc"}),
	({"Xích Dương Kiếm","Chủ Tiệm Vũ Khí Tề Quốc"}),({"Triều Dương Kiếm","Chủ Tiệm Vũ Khí Tần Quốc"}),({"Xích Đảm Kiếm","Chủ Tiệm Vũ Khí Ngụy Quốc"}),({"Lục Thanh Y","Chủ Tiệm Giáp Trụ  Triệu Quốc"}),({"Lục Thanh Quần","Chủ Tiệm Giáp Trụ  Triệu Quốc"}),({"Vũ Thiên Y","Chủ Tiệm Giáp Trụ  Yên Quốc"}),
	({"Vũ Thiên Quần","Chủ Tiệm Giáp Trụ  Yên Quốc"}),({"Phá Địch Bào","Chủ Tiệm Giáp Trụ  Chu Quốc"}),({"Phá Địch Tố Quần","Chủ Tiệm Giáp Trụ  Chu Quốc"}),({"Lý Ngư Y","Chủ Tiệm Giáp Trụ  Hàn Quốc"}),({"Lý Ngư Quần","Chủ Tiệm Giáp Trụ  Hàn Quốc"}),({"Tuyên Minh Bào","Chủ Tiệm Giáp Trụ  Tần Quốc"}),
	({"Tuyên Minh Tố Quần","Chủ Tiệm Giáp Trụ  Tần Quốc"}),({"Hoán Vân Bào","Chủ Tiệm Giáp Trụ  Tề Quốc"}),({"Hoán Vân Tố Quân","Chủ Tiệm Giáp Trụ  Tề Quốc"}),({"Hồn Sương Y","Chủ Tiệm Giáp Trụ  Ngụy Quốc"}),({"Hồn Sương Quần","Chủ Tiệm Giáp Trụ  Ngụy Quốc"}),({"Lục Thanh Mão","Chủ Tiệm Giáp Trụ  Triệu Quốc"}),
	({"Lục Thanh Đầu Cân","Chủ Tiệm Giáp Trụ  Triệu Quốc"}),({"Vũ Thiên Quán","Chủ Tiệm Giáp Trụ  Yên Quốc"}),({"Vũ Thiên Cân Mão","Chủ Tiệm Giáp Trụ  Yên Quốc"}),({"Phá Địch Mão","Chủ Tiệm Giáp Trụ  Chu Quốc"}),({"Phá Địch Đầu Cân","Chủ Tiệm Giáp Trụ  Chu Quốc"}),({"Lý Ngư Mão","Chủ Tiệm Giáp Trụ  Hàn Quốc"}),
	({"Lý Ngư Đầu Cân","Chủ Tiệm Giáp Trụ  Hàn Quốc"}),({"Tuyên Minh Mão","Chủ Tiệm Giáp Trụ  Tần Quốc"}),({"Tuyên Minh Đầu Cân","Chủ Tiệm Giáp Trụ  Tần Quốc"}),({"Hoán Vân Mão","Chủ Tiệm Giáp Trụ  Tề Quốc"}),({"Hoán Vân Đầu Cân","Chủ Tiệm Giáp Trụ  Tề Quốc"}),({"Hồn Sương Quán","Chủ Tiệm Giáp Trụ  Ngụy Quốc"}),
	({"Hồn Sương Đầu Cân","Chủ Tiệm Giáp Trụ  Ngụy Quốc"}),({"Lục Thanh Hài","Chủ Tiệm Trang Sức Triệu Quốc"}),({"Vũ Thiên Lý","Chủ Tiệm Trang Sức Yên Quốc",}),({"Phá Địch Hài","Chủ Tiệm Trang Sức Chu Quốc",}),({"Lý Ngư Hài","Chủ Tiệm Trang Sức Hàn Quốc",}),({"Tuyên Minh Hài","Chủ Tiệm Trang Sức Tần Quốc",}),({"Hoán Vân Hài","Chủ Tiệm Trang Sức Tề Quốc",}),
	({"Hồn Sương Lý","Chủ Tiệm Trang Sức Ngụy Quốc",}),({"Lục Thanh Yêu Đới","Chủ Tiệm Trang Sức Triệu Quốc",}),({"Vũ Thiên Yêu Đới","Chủ Tiệm Trang Sức Yên Quốc",}),({"Phá Địch Yêu Đới","Chủ Tiệm Trang Sức Chu Quốc",}),({"Lý Ngư Yêu Đới","Chủ Tiệm Trang Sức Hàn Quốc",}),({"Tuyên Minh Yêu Đới","Chủ Tiệm Trang Sức Tần Quốc",}),
	({"Hoán Vân Yêu Đới","Chủ Tiệm Trang Sức Tề Quốc",}),({"Hồn Sương Yêu Đới","Chủ Tiệm Trang Sức Ngụy Quốc",}),

   }),
]); 
//任务的概率
mapping mpTaskRate = 
([
	1 : ({0 ,5,5 ,40,10,40,0 ,0 ,0 ,0 ,0,0 ,0 }),
	2 : ({15,5,15,30,10,20,0 ,5 ,0 ,0 ,0,0 ,0 }),
	3 : ({15,5,5 ,20,10,25,0 ,10,10,0 ,0,0 ,0 }),
	4 : ({15,0,5 ,10,10,25,0 ,10,10,10,0,5 ,0 }),
	5 : ({10,0,10,0 ,10,20,0 ,10,10,10,0,10,10}),
	6 : ({0 ,0,0 ,0 ,10,20,0 ,15,15,20,0,10,10}),
	7 : ({0 ,0,0 ,0 ,10,20,0 ,15,15,20,0,10,10}),
	

]);
string get_random_quest4(int level)
{
	mapping quest = ([]);
	int i, ret, target;
	string name, result;
	level /= 10;
	if (level>12) level = 12;
	if (level<1) level = 1;
	i = random100();
	target = level;
	if (i<5) target -= 4;
	else
	if (i<15) target -= 3;
	else
	if (i<30) target -= 2;
	else
	if (i<50) target -= 1;
	if (target<1) target = level;
	name = sprintf("%d", target);
	i = sizeof(LevelTarget[name]);
	ret = LevelTarget[name][random(i)];
	if (ret<1000)
	        result = sprintf("/item/%d/%d", ret/10, (ret%10)*1000+ target * 10);
        else
                result = sprintf("/item/%d/%d", ret/100, ret);
	return result;
}

string get_random_quest1(int level)
{
	string name;
	if (level>114) level = 114;
        if (level<1) level = 1;
	name = sprintf("%d", level );
	if (LevelNpc[name]!=0) return LevelNpc[name];
	level --;
	while (level>=0)
	{
		name = sprintf("%d", level );
		if (LevelNpc[name]!=0) return LevelNpc[name];
		level --;
	}
	return "Gà Núi";
}

string get_manager_name(string family)
{
        if (managername[family]!=0) return managername[family];
        else return "Tư Khố";
}

string *get_random_quest2(int level)
{
	string *result,name;
	int i;
	mapping mpTmp1;
	
	if ( level > 149 )
		level = 110;
	level /= 5;
	i = random100();
	if ( i < 15 && level >= 2 )
		level -= 2;
	else if ( i < 40 && level >= 1 )
		level -= 1;
	mpTmp1 = levelNPC1[level];
	if ( !mapp(mpTmp1) )
		return ({"Gà Núi","Tân Thủ Thôn có thể bắt được Gà Núi"});
	result = keys(mpTmp1);
	if ( !arrayp(result) )
		return ({"Gà Núi","Tân Thủ Thôn có thể bắt được Gà Núi"});
	name = result[random(sizeof(result))];
	return ({name,mpTmp1[name]});
}

string *get_random_quest3(int level)
{
	int i;
	mapping mpTmp;
	string *keys,name; 
	
	if ( level > 110 )
		level = 110;
	level /= 5;
	i = random100();
	if ( i < 20 && level > 3 )
		level -= 2 ;
	else if ( i < 45 && level > 2 )
		level -= 1 ;
	if ( level < 2 )
		level = 2;	
	mpTmp = LevelTarget1[level];
	if ( !mapp(mpTmp) )
		return ({"Phá Tổn Đầu Khôi" , "Sở Phương Thành đánh Sở Quân Đao Binh sẽ có Phá Tổn Đầu Khôi"});
	keys = keys(mpTmp);
	name = keys[random(sizeof(keys))];	
	return ({name,mpTmp[name]});
}
//Tư Khố采购物品
string *get_random_siku(int iFlag)
{
	mixed *nTmp;
	if ( iFlag < 1 || iFlag > 4 )
		return ({"Trái quýt","Chủ Tửu Lâu"});
	nTmp = mpSiku[iFlag];
	return nTmp[random(sizeof(nTmp))];
}
//随机获取师门任务类别
int get_random_task(object player)
{
	int level, rate,i,size,type,*nRate;	
	level = player->get_level();
	if (level<10) level = 10;
	if (level>150) level = 150;
	switch ( level / 10 )
	{
	default:
	case 1..2:
		type = 1;
		break;			
	case 3..4:
		type = 2;					
		break;	
	case 5..6:
		type = 3;	
		break;							
	case 7..8:
		type = 4;						
		break;	
	case 9..10:
		type = 5;
		break;	
	case 11..12:
		type = 6;
		break;
	case 13..15:
		type = 7;
		break;	
	}
	rate = random100();
	nRate = mpTaskRate[type];
	for(i=0,size=sizeof(nRate);i<size;i++)
	{
		if ( rate < nRate[i] )
			break;
		rate -= nRate[i];	
	}
	type = i+1;		
	if ( type > 10 )
		type = 1;
	return type;
}
//随机取一个NPC
string *get_random_quest5(int level)
{
	string *result,name;
	int i;
	mapping mpTmp1;
	
	if ( level > 110 )
		level = 110;
	level /= 5;
	mpTmp1 = levelNPC1[level];
	if ( !mapp(mpTmp1) )
		return ({"Gà Núi","Tân Thủ Thôn có thể bắt được Gà Núi"});
	result = keys(mpTmp1);
	if ( !arrayp(result) )
		return ({"Gà Núi","Tân Thủ Thôn có thể bắt được Gà Núi"});
	name = result[random(sizeof(result))];
	return ({name,mpTmp1[name]});
}

//任务链收集师门物品
string *get_random_quest6(int level)
{
	int i;
	mapping mpTmp;
	string *keys,name; 
	
	if ( level > 110 )
		level = 110;
	level /= 5;
	level = level - (random(4)+1);
	mpTmp = LevelTarget1[level];
	if ( !mapp(mpTmp) )
		return ({"Phá Tổn Đầu Khôi" , "Sở Phương Thành Sở Quân Đao Binh có Phá Tổn Đầu Khôi"});
	keys = keys(mpTmp);
	name = keys[random(sizeof(keys))];	
	return ({name,mpTmp[name]});
}

int test100()
{
	int i,j,size,*nTmp,sum;
	
	for(i=1;i<8;i++)
	{
		nTmp = mpTaskRate[i];
		sum=0;
		for(j=0,size=sizeof(nTmp);j<size;j++)
		{
			sum += nTmp[j];	
		}
		if ( sum != 100)
			return i;
	}	
	return 0;
}