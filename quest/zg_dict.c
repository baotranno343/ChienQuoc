/*----------------------------------------------------------------------------------*\
	战国宝典的控制文件，包含一些通用功能的控制处理
	由 cjxx 于 2007-09-14 创建
\*----------------------------------------------------------------------------------*/
#include <ansi.h>

/*------------------------------------预定义变量---------------------------------------*/
#define PLAYER_GET_PRIZE "can_get_prize"
#define PLAYER_BE_GALA "can_be_gala"
#define ZGDICT_ITEM "item/01/7600"
#define _DEBUG(str) ; //if(objectp(find_char("1"))) {tell_user(find_char("1"),str);}
/*---------------------------------------完毕------------------------------------------*/

/*------------------------------------类私有变量---------------------------------------*/
//	MAPPING 结构：1层->起始等级，2层->结束等级，3层->对应信息
private
static mapping lv_user_info = ([0:([9:({
										  "◇    Ở Tân Thủ Thôn, U Cốc, Thanh Khê có một số nhân vật sứ mệnh và vật phẩm sứ mệnh, chỉ cần đánh bại nhân vật sứ mệnh hoặc nhặt được sứ mệnh vật phẩm giao lại cho Vệ Đội Trưởng, sẽ có thể nhận được phần thưởng bất ngờ!",
										  "◇    Ngươi có nhìn thấy dấu hỏi trên đầu của các bá tánh không? Đó là biểu hiện đang cần được giúp đỡ, hãy mau đến hỏi thăm họ đi!",
										  "◇    Ở Tân Thủ Thôn, U Cốc, Thanh Khê và Ba Khâu là nơi thích hợp cho ngươi luyện cấp.",
										  "◇    Dã ngoại quái vật có phải hay không thực đáng yêu! Đi tiệm tạp hóa mua mấy Càn Khôn thằng, sau đó sử dụng 'Sủng vật bắt giữ' kỹ năng liền có một chút xác suất đem quái vật lần làm sủng vật nga!",
									  }),
									   //		29 : ({
									   //			"◇    找到师父了吗？如果还没有找到就赶快去孟子那里去申请吧！找个师父帮你熟悉战国环境。",}),
									   50:({
											  "◇    Ở Vệ Đội Trưởng hiện đang thiếu người để bảo vệ trị an, nếu ngươi chịu đến giúp hắn ta sẽ có thể nhận được phần thưởng rất phong phú!",
										  }),
									  150:({
											  "◇    Thần Tiên Gia Gia mỗi tuần đều cung cấp cho ngươi 4 giờ nhân đôi kinh nghiệm, đương nhiên, nếu như ngươi trở thành VIP sẽ còn được nhiều thời gian nhân đôi kinh nghiệm để nhận nữa, hãy nhanh chân tìm Thần Tiên Gia Gia nhận nhân đôi kinh nghiệm nào!",
										  }),
]),
							   10:([10:({
										   "◇    Còn không có gia nhập môn phái sao? Nhanh tìm môn phái chiêu mộ đi! Bọn hắn có thể đem ngươi trực tiếp rơi vào tay môn phái nơi đóng quân, gia nhập môn phái sau có thể học được rất lợi hại kỹ năng nga!",
									   }),
									  14:({
											 "◇    Nếu ngươi hiện tại có thời gian có thể đi Sở quốc đi dạo, nơi đó dân chúng đang cùng đợi trợ giúp của ngươi đâu!",
											 "◇   Sở phương thành 1, sở phương thành 2, sở phương thành 3, thượng dung quan, Hoa Sơn, Đào Hoa nguyên, Triêu Dương phong đúng là thích hợp ngươi luyện cấp địa phương.",
										 }),
									  20:({
											 "◇    Ở Chu quốc chợ phía bên phải có một chút cuộc sống kỹ năng đạo sư, ngươi có thể đi nơi đó hướng bọn hắn thỉnh giáo cuộc sống kỹ năng, mặt khác còn có một cái đại chúng hoá phó cuộc sống kỹ năng cần ở chợ bên trái ngự trù nơi đó mới có thể học được",
										 }),
									  30:({
											 "◇    Nghe nói Vương Bộ Đầu ở nha môn của nước Chu hiện đang cần người tài, ngươi có thời gian thì hãy đến giúp ông ấy nhé!",
										 }),
]),
							   11:([150:({
											"◇    Trong Nha Phủ lúc nào cũng cần người tài đức, ngươi hãy tìm Sư Gia để hỏi nhé! Nhiệm vụ trước 20 sẽ được rất nhiều phần thưởng phong phú! Và còn có thể nhận được những nhiệm vụ Ẩn Tàng đặc biệt nữa đó.",
										}),
]),
							   15:([19:({
										   "◇    Thủ Dương Sơn, Thúy Hoa sơn cùng Hàm Cốc quan đúng là thích hợp ngươi hướng cấp địa phương, muốn luyện cấp hãy mau đi những chỗ này đi!",
									   }),
									  24:({
											 "◇    Nếu ngươi hữu thời gian liền đi xem đi Hàn Quốc đi! Nơi đó dân chúng đang trông mong cùng đợi ngươi đi trợ giúp bọn hắn đâu",
										 }),
]),
							   20:([24:({
										   "◇    Lấy ngươi hiện tại cấp bậc, đề nghị ngươi đi dưới mấy cái địa phương luyện cấp: Vô Định hà 1, Vô Định hà 2, Vô Định hà bờ, tương đồi, mã đồi nói, con ngựa trắng trang cùng với mã đạp hồ.",
									   }),
									  29:({
											 "◇    Ngụy Quốc có rất nhiều người đã ở chờ đợi lên ngươi đến, ngươi tìm cái thời gian đi xem đi!",
										 }),
]),
							   25:([30:({
										   "◇    Hổ Lao quan, ki quan, cự lộc, Trác lộc, Dịch Thủy, quế đồi, Mục dã, Thái Hành Sơn, Tấn Dương, bình nguyên, Nhạn Môn quan cùng với Trường Bình đều là thích hợp hiện tại đẳng cấp luyện cấp bản đồ.",
									   }),
]),
							   30:([34:({
										   "◇    Sở quốc có rất nhiều dân chúng đang cùng đợi trợ giúp của ngươi, tìm cái thời gian đi xem đi!",
									   }),
									  150:({
											  "◇    Nếu ngươi thiếu tiền, có thể đi Chu quốc tiêu cục tìm Úy Trì lão tiêu đầu, giúp hắn vận tiêu, hắn sẽ cho ngươi dày báo thù.",
											  "◇    Luyện cấp luôn luôn sử dụng thuốc có phải hay không cảm thấy được có chút không tính? Không sao, mỗi ngày 12 có một chút 24 có một chút trừ Chu quốc ngoại trừ các quốc gia ngoài thành vườn trồng trọt chỗ, tìm tới đó nông phu, tiến hành nông sản sản xuất, làm thành thực vật thực tính.",
										  }),
]),
							   31:([40:({
										   "◇    Đầm lầy bên cạnh, đầm lầy mảnh đất, Đại Biệt sơn chân, Đại Biệt sơn, Vu Sơn, Bà Dương Hồ, Xích Bích, Thái Hồ, Thái Sơn chân núi, Thái Sơn những điều này là do hiện giai đoạn luyện cấp nơi tốt.",
									   }),
]),
							   35:([39:({
										   "◇    Tề quốc dân chúng đối diện ngươi trông mong lấy phán đâu! Ngươi hãy tìm cái thời gian trôi qua nhìn xem thật là tốt.",
									   }),
									  150:({
											  "◇    Biết tả thu minh sao? Hắn đang ở mộ binh dũng sĩ đi trước phong yêu kính tiêu diệt yêu ma, chỉ cần ngươi cho hắn một món đồ 15 cấp đã ngoài quý hiếm trang bị, hắn là có thể mở ra phong yêu thông đạo. Chỉ cần đem bên trong yêu ma tiêu diệt 85% đã ngoài còn có một con BOSS đi ra, sẽ rơi xuống quý hiếm trang bị nga!",
										  }),
]),
							   40:([45:({"◇    Ngươi hiện tại hữu thời gian không ngại đi chuyến Tần quốc, tìm Tần quốc dân chúng tâm sự, tin tưởng ngươi nhất định sẽ có thu hoạch."}),
									  50:({"◇    Đi qua Yến quốc sao? Đi tìm Yến quốc dân chúng tâm sự đi, bọn hắn giống như có rất nhiều chuyện cùng với ngươi nói."}),
									  60:({"◇    Hiện tại ngươi đã có đủ thực lực đến sáng lập bang phái, nếu ngươi muốn sáng lập bang phái, kia hãy mau đi tuyển một quốc gia đi ( trừ Chu quốc ngoại ), tìm được nên quốc bang phái tổng quản, là có thể lĩnh xây bang nhiệm vụ, nhưng là, ta còn muốn bổ sung một chút, hay là tại chế tạo 'Vương chi kèn' thời gian nhưng là phải tiêu phí 100 vạn tiền vàng nga!",
										   "◇    Ngươi có thể thông qua Tần quốc quân doanh đòi nghịch tướng quân tiến vào thành kiểu quân doanh, chỉ cần đả bại BOSS liền có một chút xác suất đạt được màu tím bộ đồ bộ phận lắp ráp, nhưng là phải cẩn thận nga! Bên trong quái vật rất lợi hại nga!"}),
]),
							   41:([50:({//			"◇    以你现在的实力，已经有资格做新人的师父了，快去新手村找一个30级以下的新人吧，组队去找孟子。把徒弟带出师后有丰厚的奖励哦！",
										 "◇    Đông Hải Ngư Thôn, Bờ Đông Hải, Hải Tân 1, Hải Tân 2, Đông Hải Đảo, Kênh Trịnh Quốc 1, Kênh Trịnh Quốc 2, Kênh Trịnh Quốc 3 đều là nơi luyện cấp tốt nhất của ngươi hiện giờ.",
										 "◇    Nghe nói từng hai ngày, ở Đông Hải đều có một kêu khuyển Thái Lang gia hỏa tuần tiễu. Theo Đông Hải ngư dân nói, này khuyển Thái Lang phi thường lợi hại, ngươi cần thập phần cẩn thận a!"}),
]),
							   50:([54:({
										   "◇    	Trường Bạch sơn, Thiên Trụ Phong, Trường Bạch thiên trì, Bạch Vân ngọn núi, võ đồi bí đạo, Hành Sơn bí đạo, Lôi Phong sơn bí đạo đều là luyện cấp nơi tốt.",
									   }),
									  55:({
											 "◇    Triệu quốc một mực chống cự lại Hung Nô tiến công, đi xem Triệu quốc dân chúng đi! Tin tưởng ngươi nhất định có không ít thu hoạch.",
										 }),
									  70:({
											 "◇    Ngươi có thể tổ đội đi Thúy Hoa sơn (139,117) tìm được 'Trốn chết khổ dịch' tiến vào Ly Sơn lăng mộ, bên trong có không ít thứ tốt, nhưng là phải cẩn thận nga! Bên trong quái vật phi thường lợi hại, người bình thường ta không nói cho hắn.",
										 }),
]),
							   55:([59:({"◇    Yến Trường Thành 1, Yến Trường Thành 2, Yến Trường Thành 3 cùng âm sơn thảo nguyên, âm sơn, cự thú đảo đúng là hiện tại thích hợp luyện cấp điểm."}),
]),
							   60:([64:({

										   "◇  Triệu Trường Thành 1, Triệu Trường Thành 2, Triệu Trường Thành 3, Kỳ Liên sơn thảo nguyên, Kỳ Liên sơn, Địa Ngục động ma 1 tầng đúng là trước mắt luyện cấp thật là tốt nơi đi.",
									   }),
]),

							   65:([

									  69:({

											 "◇  Tần Trường Thành 1, Tần Trường Thành 2, Tần Trường Thành 3, Trung Nguyên bí đạo, Tung Sơn bí đạo, Lang Gia bí đạo, Mang Sơn bí đạo, thiên ngoại ảo cảnh 1 tầng đúng là trước mắt luyện cấp thật là tốt nơi đi.",
										 }),
]),

							   70:([

									  74:({

											 "◇  loan nói 1, loan nói 2, loan nói 3, hoằng nông, Mạnh Tân, Địa Ngục động ma 2 tầng đúng là trước mắt luyện cấp thật là tốt nơi đi.",
										 }),
]),

							   75:([

									  79:({

											 "◇  Linh Cốc động 1 tầng, Linh Cốc động 2 tầng, Linh Cốc động 3 tầng, hồ quan, dễ dàng kinh, thiên ngoại ảo cảnh 2 tầng đúng là trước mắt luyện cấp thật là tốt nơi đi.",
										 }),
]),

							   80:([

									  84:({

											 "◇  vạn người hố 1 tầng, vạn người hố 2 tầng, vạn người hố 3 tầng, vạn người hố 4 tầng, vạn người hố 5 tầng, ô giang, Quảng Lăng, Địa Ngục động ma 3 tầng đúng là trước mắt luyện cấp thật là tốt nơi đi.",
										 }),
]),

							   85:([

									  89:({

											 "◇  tướng quân mộ 1 tầng, tướng quân mộ 2 tầng, tướng quân mộ 3 tầng, tướng quân mộ 4 tầng, tướng quân mộ 5 tầng, ngàn thừa lúc, cao Đường, thiên ngoại ảo cảnh 3 tầng đúng là trước mắt luyện cấp thật là tốt nơi đi.",
										 }),
]),

							   90:([

									  94:({

											 "◇  Khốn Ma trận, Khốn Ma trận 1 tầng, Khốn Ma trận 2 tầng, Khốn Ma trận 3 tầng, vui đồi, Tức Mặc, Địa Ngục động ma 4 tầng đúng là trước mắt luyện cấp thật là tốt nơi đi.",
										 }),
]),

							   95:([

									  99:({

											 "◇  hư đồi động, Huyền Chân động, Tử Vân động, tử buổi trưa cốc, Hán Trung, thiên ngoại ảo cảnh 4 tầng đúng là trước mắt luyện cấp thật là tốt nơi đi.",
										 }),
]),

							  100:([

									  104:({

											  "◇  cầu cửu khúc 1, cầu cửu khúc 2, cầu cửu khúc 3, Dương Bình quan, tây thành đúng là trước mắt luyện cấp thật là tốt nơi đi.",
										  }),
]),

							  105:([

									  109:({

											  "◇  Thiên Môn trận 1 tầng, Thiên Môn trận 2 tầng, Thiên Môn trận 3 tầng, Bình Dương, Thượng Đảng đúng là trước mắt luyện cấp thật là tốt nơi đi.",
										  }),
]),

							  110:([

									  120:({

											  "◇  Tru Tiên Trận 1 tầng, Tru Tiên Trận 2 tầng, Tru Tiên Trận 3 tầng, Đồng Quan, Vũ Quan đúng là trước mắt luyện cấp thật là tốt nơi đi.",
										  }),
]),
]);
//	MAPPING 结构：	1层->起始等级，2层->结束等级，3层->奖品等级，
//			4层->道具信息,这里有些道具做了特殊格式的处理 如果是
//				1 金钱 cash <价值>
//				2 物品 <物品位置> <物品颜色> <物品个数>
private
static mapping lv_rock_item = ([0:([9:([0:({
											  "cash 10000",
											  "/item/60/0010 2",
											  "/item/65/0010 2",
											  "/item/88/0010 2",
											  "/item/87/1010 2",
										  }),
										  1:({
												"cash 5000",
												"/item/product/64001",
												"/item/product/64002",
												"/item/product/62001",
												"/item/product/62002",
												"/item/product/66001",
												"/item/product/66002",
												"/item/product/63001",
												"/item/product/63002",
												"/item/product/65001",
												"/item/product/65002",
											}),
										  2:({
												"cash 1000",
												"/item/91/9100 0 10",
												"/item/91/9101 0 10",
												"/item/91/9110 0 10",
												"/item/91/9111 0 10",
												"/item/std/5210 0 10",
												"/item/31/3150 0 10",
												"/item/32/3282 0 10",
												"/item/final/33/1700 0 10",
												"/item/final/33/1701 0 10",
												"/item/final/33/1702 0 10",
												"/item/final/33/1703 0 10",
												"/item/final/33/1750 0 10",
												"/item/std/0401 0 30",
												"/item/49/4900 0 10",
												"/item/std/0407 0 10",
												"/item/std/0409 0 10",
												"/item/44/4403 0 10",
											}),
]),
]),
							   10:([29:([0:({
											   "cash 30000",
											   "/item/72/1020 2",
											   "/item/74/1020 2",
											   "/item/72/1030 2",
											   "/item/74/1030 2",
											   "/item/76/1020 2",
											   "/item/76/1030 2",
											   "/item/75/1020 2",
											   "/item/75/1030 2",
											   "/item/70/1020 2",
											   "/item/70/1030 2",
											   "/item/71/1020 2",
											   "/item/71/1030 2",
											   "/item/77/1020 2",
											   "/item/77/1030 2",
											   "/item/78/1020 2",
											   "/item/78/1030 2",
											   "/item/79/1020 2",
											   "/item/79/1030 2",
											   "/item/std/8000",
										   }),
										   1:({
												 "cash 20000",
												 "/item/95/0211 1",
												 "/item/95/0221 1",
												 "/item/95/0231 1",
												 "/item/95/0251 1",
												 "/item/95/0261 1",
												 "/item/95/0414 1",
												 "/item/95/0423 1",
												 "/item/95/0511 1",
												 "/item/95/0109 1",
												 "/item/95/0401 1",
												 "/item/95/0404 1",
												 "/item/95/0405 1",
												 "/item/95/0111 1",
												 "/item/95/0121 1",
												 "/item/95/0131 1",
												 "/item/95/0141 1",
												 "/item/95/0151 1",
												 "/item/95/0161 1",
												 "/item/95/0202 1",
												 "/item/60/1025 1",
												 "/item/61/1025 1",
												 "/item/60/2025 1",
												 "/item/61/2025 1",
												 "/item/60/3025 1",
												 "/item/61/3025 1",
												 "/item/60/4025 1",
												 "/item/61/4025 1",
												 "/item/60/6025 1",
												 "/item/61/6025 1",
												 "/item/60/5025 1",
												 "/item/61/5025 1",
												 "/item/60/7025 1",
												 "/item/61/7025 1",
											 }),
										   2:({
												 "cash 10000",
												 "/item/91/9102 0 20",
												 "/item/91/9112 0 20",
												 "/item/final/33/1772 0 20",
												 "/item/final/33/1754 0 20",
												 "/item/final/33/1756 0 20",
												 "/item/final/33/1764 0 20",
												 "/item/product/64025 0",
												 "/item/product/64026 0",
												 "/item/product/64027 0",
												 "/item/product/64025 0",
												 "/item/product/64029 0",
												 "/item/product/64030 0",
												 "/item/product/64031 0",
												 "/item/product/64032 0",
												 "/item/product/64033 0",
												 "/item/49/4900 0 30",
												 "/item/std/0409 0 30",
												 "/item/std/0410 0 30",
												 "/item/std/0401 0 90",
												 "/item/44/4406 0 30",
											 }),
]),
]),
							   30:([59:([0:({
											   "cash 100000",
											   "/item/93/9301 1",
											   "/item/93/9302 1",
											   "/item/93/9304 1",
											   "/item/93/9309 1",
											   "/item/93/9306 1",
											   "/item/93/9305 1",
											   "/item/93/9303 1",
											   "/item/93/9307 1",
											   "/item/93/9308 1",
											   "/item/93/9310 1",
											   "/item/std/8001 1",
											   "/item/std/8002 1",
											   "/item/std/8003 1",
											   "/item/std/8004 1",
										   }),
										   1:({
												 "cash 50000",
												 "/item/44/4488 1",
												 "/item/44/4405 1 10",
												 "/item/86/1050 1",
												 "/item/86/2050 1",
												 "/item/86/3050 1",
												 "/item/86/4050 1",
												 "/item/86/6050 1",
												 "/item/86/5050 1",
												 "/item/86/7050 1",
											 }),
										   2:({
												 "cash 20000",
												 "/item/95/0317 1",
												 "/item/95/0222 1",
												 "/item/95/0349 1",
												 "/item/95/0364 1",
												 "/item/95/0271 1",
												 "/item/95/0418 1",
												 "/item/95/0425 1",
												 "/item/95/0501 1",
												 "/item/95/0111 1",
												 "/item/95/0121 1",
												 "/item/95/0131 1",
												 "/item/95/0141 1",
												 "/item/95/0151 1",
												 "/item/95/0161 1",
												 "/item/95/0202 1",
												 "/item/95/0402 1",
												 "/item/95/0403 1",
												 "/item/std/8000 0 20",
												 "/item/91/9112 0 20",
												 "/item/91/9120 0 20",
												 "/item/std/5216 0 20",
												 "/item/31/3152 0 20",
												 "/item/31/3151 0 20",
												 "/item/32/3281 0 20",
												 "/item/33/3320 0 20",
												 "/item/std/0409 0 30",
												 "/item/std/0413 0 30",
												 "/item/std/0591 0 30",
												 "/item/98/9871 0 30",
											 }),
]),
]),
							   60:([89:([0:({
											   "cash 150000",
											   "/item/std/9511 2",
											   "/item/std/9521 2",
											   "/item/std/9541 2",
											   "/item/std/9561 2",
											   "/item/std/9571 2",
											   "/item/std/9581 2",
											   "/item/96/0211 2",
											   "/item/96/0221 2",
											   "/item/96/0231 2",
											   "/item/96/0251 2",
											   "/item/96/0241 2",
											   "/item/96/0261 2",
											   "/item/96/0414 2",
											   "/item/96/0424 2",
											   "/item/96/0511 2",
											   "/item/96/0404 2",
											   "/item/96/0405 2",
										   }),
										   1:({
												 "cash 80000",
												 "/item/95/0610",
												 "/item/95/0640",
												 "/item/95/0660",
												 "/item/95/0670",
												 "/item/95/0630",
												 "/item/95/0650",
												 "/item/95/0620",
												 "/item/95/0680",
												 "/item/std/8000",
												 "/item/product/62311.c 1",
												 "/item/product/62311.c 1",
												 "/item/product/62313.c 1",
												 "/item/product/62314.c 1",
												 "/item/product/62315.c 1",
												 "/item/product/62316.c 1",
												 "/item/product/62317.c 1",
												 "/item/product/62318.c 1",
												 "/item/product/62319.c 1",
												 "/item/product/62320.c 1",
												 "/item/product/62321.c 1",
												 "/item/product/62322.c 1",
												 "/item/product/62323.c 1",
												 "/item/product/62324.c 1",
												 "/item/product/62325.c 1",
												 "/item/product/62326.c 1",
												 "/item/product/62327.c 1",
												 "/item/product/62328.c 1",
												 "/item/product/62329.c 1",
											 }),
										   2:({
												 "cash 50000",
												 "/item/stuff/0055",
												 "/item/stuff/0056",
												 "/item/stuff/0079",
												 "/item/stuff/0057",
												 "/item/stuff/0080",
												 "/item/stuff/0062",
												 "/item/stuff/0063",
												 "/item/stuff/0064",
												 "/item/stuff/0078",
												 "/item/stuff/0079",
												 "/item/stuff/0080",
												 "/item/stuff/0081",
												 "/item/stuff/0082",
												 "/item/stuff/0083",
												 "/item/stuff/0084",
												 "/item/stuff/0085",
												 "/item/stuff/0086",
												 "/item/stuff/0087",
												 "/item/44/4488",
												 "/item/final/16/1600",
												 "/item/final/16/1607",
												 "/item/final/16/1612",
												 "/item/final/16/1605",
												 "/item/final/16/1626",
												 "/item/final/16/1610",
												 "/item/final/16/1614",
												 "/item/final/16/1609",
												 "/item/98/0245",
												 "/item/final/16/1603",
												 "/item/final/16/1604",
												 "/item/final/16/1608",
											 }),
]),
]),
							   90:([119:([0:({
												"cash 300000",
												"/item/44/4489",
												"/item/std/9502",
												"/item/std/9512",
												"/item/std/9522",
												"/item/std/9542",
												"/item/std/9562",
												"/item/std/9572",
											}),
											1:({
												  "cash 150000",
												  "/item/72/1090 2",
												  "/item/72/1100 2",
												  "/item/74/1090 2",
												  "/item/74/1100 2",
												  "/item/76/1090 2",
												  "/item/76/1100 2",
												  "/item/75/1090 2",
												  "/item/75/1100 2",
												  "/item/70/1090 2",
												  "/item/70/1100 2",
												  "/item/71/1090 2",
												  "/item/71/1100 2",
												  "/item/77/1090 2",
												  "/item/76/1130 2",
												  "/item/78/1090 2",
												  "/item/78/1100 2",
												  "/item/79/1090 2",
												  "/item/79/1100 2",
												  "/item/91/9125",
												  "/item/91/9150",
												  "/item/91/9160",
												  "/item/91/9161",
												  "/item/91/9162",
												  "/item/91/9163",
												  "/item/91/9164",
												  "/item/91/9165",
												  "/item/std/0088",
												  "/item/93/9301",
												  "/item/93/9302",
												  "/item/93/9304",
												  "/item/93/9309",
												  "/item/93/9306",
												  "/item/93/9305",
												  "/item/93/9303",
												  "/item/93/9307",
												  "/item/93/9308",
												  "/item/93/9310",
											  }),
											2:({
												  "cash 100000",
												  "/item/std/8000",
												  "/item/38/3801",
												  "/item/38/3802",
												  "/item/38/3803",
												  "/item/38/3804",
												  "/item/38/3805",
												  "/item/38/3806",
												  "/item/38/3807",
												  "/item/38/3808",
												  "/item/38/3809",
												  "/item/97/9715",
												  "/item/97/9713",
												  "/item/97/9717",
												  "/item/97/9716",
												  "/item/97/9714",
												  "/item/97/9710",
												  "/item/97/9711",
												  "/item/97/9712",
												  "/item/97/9720",
												  "/item/97/9721",
												  "/item/97/9722",
												  "/item/97/9723",
												  "/item/97/9724",
												  "/item/97/9725",
												  "/item/97/9726",
												  "/item/97/9727",
												  "/item/97/9728",
												  "/item/97/9729",
												  "/item/97/9731",
												  "/item/97/9732",
												  "/item/97/9733",
												  "/item/97/9733",
												  "/item/stuff/0055",
												  "/item/stuff/0056",
												  "/item/stuff/0079",
												  "/item/stuff/0057",
												  "/item/stuff/0080",
												  "/item/stuff/0062",
												  "/item/stuff/0063",
												  "/item/stuff/0064",
												  "/item/stuff/0078",
												  "/item/stuff/0079",
												  "/item/stuff/0080",
												  "/item/stuff/0081",
												  "/item/stuff/0082",
												  "/item/stuff/0083",
												  "/item/stuff/0084",
												  "/item/stuff/0085",
												  "/item/stuff/0086",
												  "/item/stuff/0087",
											  }),
]),
]),
							  120:([150:([0:({
												"cash 500000",
												"/item/72/1120 2",
												"/item/76/1120 2",
												"/item/74/1120 2",
												"/item/75/1120 2",
												"/item/70/1120 2",
												"/item/71/1120 2",
												"/item/77/1120 2",
												"/item/78/1120 2",
												"/item/79/1120 2",
												"/item/61/7120 2",
												"/item/60/7120 2",
												"/item/61/5120 2",
												"/item/60/5120 2",
												"/item/61/6120 2",
												"/item/60/6120 2",
												"/item/61/4120 2",
												"/item/60/4120 2",
												"/item/61/3120 2",
												"/item/60/3120 2",
												"/item/61/2120 2",
												"/item/60/2120 2",
												"/item/61/1120 2",
												"/item/60/1120 2",
											}),
											1:({
												  "cash 300000",
												  "/item/61/7120 1",
												  "/item/60/7120 1",
												  "/item/61/5120 1",
												  "/item/60/5120 1",
												  "/item/61/6120 1",
												  "/item/60/6120 1",
												  "/item/61/4120 1",
												  "/item/60/4120 1",
												  "/item/61/3120 1",
												  "/item/60/3120 1",
												  "/item/61/2120 1",
												  "/item/60/2120 1",
												  "/item/61/1120 1",
												  "/item/60/1120 1",
												  "/item/86/7120 1",
												  "/item/86/5120 1",
												  "/item/86/6120 1",
												  "/item/86/4120 1",
												  "/item/86/3120 1",
												  "/item/86/2120 1",
												  "/item/86/1120 1",
												  "/item/87/7120 1",
												  "/item/87/5120 1",
												  "/item/87/6120 1",
												  "/item/87/4120 1",
												  "/item/87/3120 1",
												  "/item/87/2120 1",
												  "/item/87/1120 1",
												  "/item/66/7120 1",
												  "/item/65/7120 1",
												  "/item/66/5120 1",
												  "/item/65/5120 1",
												  "/item/66/6120 1",
												  "/item/65/6120 1",
												  "/item/66/4120 1",
												  "/item/65/4120 1",
												  "/item/66/3120 1",
												  "/item/65/3120 1",
												  "/item/66/2120 1",
												  "/item/65/2120 1",
												  "/item/66/1120 1",
												  "/item/65/1120 1",
											  }),
											2:({
												  "cash 150000",
												  "/item/95/0610",
												  "/item/95/0640",
												  "/item/95/0660",
												  "/item/95/0670",
												  "/item/95/0630",
												  "/item/95/0650",
												  "/item/95/0620",
												  "/item/95/0680",
												  "/item/91/9125",
												  "/item/91/9150",
												  "/item/91/9160",
												  "/item/91/9161",
												  "/item/91/9162",
												  "/item/91/9163",
												  "/item/91/9164",
												  "/item/91/9165",
												  "/item/std/0088",
												  "/item/std/8000",
												  "/item/38/3801",
												  "/item/38/3802",
												  "/item/38/3803",
												  "/item/38/3804",
												  "/item/38/3805",
												  "/item/38/3806",
												  "/item/38/3807",
												  "/item/38/3808",
												  "/item/38/3809",
												  "/item/97/9715",
												  "/item/97/9713",
												  "/item/97/9717",
												  "/item/97/9716",
												  "/item/97/9714",
												  "/item/97/9710",
												  "/item/97/9711",
												  "/item/97/9712",
												  "/item/97/9720",
												  "/item/97/9721",
												  "/item/97/9722",
												  "/item/97/9723",
												  "/item/97/9724",
												  "/item/97/9725",
												  "/item/97/9726",
												  "/item/97/9727",
												  "/item/97/9728",
												  "/item/97/9729",
												  "/item/97/9731",
												  "/item/97/9732",
												  "/item/97/9733",
												  "/item/97/9733",
											  }),
]),
]),
]);
//	MAPPING 结构：收费道具的奖励列表
private
static string *lv_sell_item = ({
	//	0-9
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	//	10-19
	"/item/bind/54/0951",
	"/item/bind/54/0952",
	"/item/bind/54/0953",
	"/item/bind/54/1100",
	"/item/bind/54/4143",
	"/item/bind/54/1050",
	"/item/bind/54/1102",
	"/item/bind/54/1051",
	"/item/bind/54/1052",
	"/item/bind/54/4145",
	//	20-29
	"/item/bind/08/0003",
	"/item/bind/08/0004",
	"/item/bind/08/0003",
	"/item/bind/08/0004",
	"/item/bind/08/0003",
	"/item/bind/08/0004",
	"/item/bind/08/0003",
	"/item/bind/08/0004",
	"/item/bind/08/0003",
	"/item/bind/08/0004",
	//	30-39
	"/item/bind/08/0001",
	"/item/bind/sell/0041",
	"/item/bind/08/0001",
	"/item/bind/sell/0041",
	"/item/bind/08/0001",
	"/item/bind/sell/0041",
	"/item/bind/08/0001",
	"/item/bind/sell/0041",
	"/item/bind/08/0001",
	"/item/bind/sell/0041",
	//	40-49
	"/item/bind/sell/0044",
	"/item/bind/01/0006",
	"/item/bind/sell/0044",
	"/item/bind/01/0006",
	"/item/bind/sell/0044",
	"/item/bind/01/0006",
	"/item/bind/sell/0044",
	"/item/bind/01/0006",
	"/item/bind/sell/0044",
	"/item/bind/01/0006",
	//	50-59
	"/item/bind/std/6002",
	"/item/bind/sell/0045",
	"/item/bind/sell/0050",
	"/item/bind/sell/0031",
	"/item/bind/sell/0012",
	"/item/bind/sell/0045",
	"/item/bind/sell/0040",
	"/item/bind/sell/0032",
	"/item/bind/sell/0032",
	"/item/bind/sell/0032",
	//	60-69
	"/item/bind/08/0002",
	"/item/bind/sell/0006",
	"/item/bind/08/0003 0 2",
	"/item/bind/08/0002",
	"/item/bind/sell/0006",
	"/item/bind/08/0003  0 2",
	"/item/bind/08/0002",
	"/item/bind/sell/0006",
	"/item/bind/08/0003 0 2",
	"/item/bind/08/0002",
	//	70-79
	"/item/bind/sell/0006",
	"/item/bind/08/0003 0 2",
	"/item/bind/sell/0007",
	"/item/bind/sell/0201",
	"/item/bind/sell/0009",
	"/item/bind/sell/0201",
	"/item/bind/sell/0007",
	"/item/bind/91/9166",
	"/item/bind/sell/0200",
	"/item/bind/sell/0009",
	//	80-89
	"/item/bind/sell/0200",
	"/item/bind/08/0002",
	"/item/bind/08/0004 0 2",
	"/item/bind/08/0002",
	"/item/bind/08/0004 0 2",
	"/item/bind/08/0002",
	"/item/bind/08/0004 0 2",
	"/item/bind/08/0002",
	"/item/bind/08/0004 0 2",
	"/item/bind/08/0002",
	//	90-99
	"/item/bind/sell/0002",
	"/item/bind/sell/0060",
	"/item/bind/sell/0002",
	"/item/bind/sell/0060",
	"/item/bind/sell/0002",
	"/item/bind/sell/0060",
	"/item/bind/sell/0002",
	"/item/bind/sell/0060",
	"/item/bind/sell/0002",
	"/item/bind/sell/0060",
	//	100-109
	"/item/bind/sell/0030",
	"/item/bind/sell/0041 0 2",
	"/item/bind/sell/0030",
	"/item/bind/sell/0041 0 2",
	"/item/bind/sell/0030",
	"/item/bind/sell/0041 0 2",
	"/item/bind/sell/0030",
	"/item/bind/sell/0041 0 2",
	"/item/bind/sell/0030",
	"/item/bind/sell/0041 0 2",
	//	110-119
	"/item/bind/01/0006 0 2",
	"/item/bind/sell/0045 0 2",
	"/item/bind/01/0006 0 2",
	"/item/bind/sell/0045 0 2",
	"/item/bind/01/0006 0 2",
	"/item/bind/sell/0045 0 2",
	"/item/bind/sell/0032 0 2",
	"/item/bind/08/0002",
	"/item/bind/sell/0008",
	"/item/bind/sell/0032 0 2",
	//	120-129
	"/item/bind/08/0002",
	"/item/bind/sell/0008",
	"/item/bind/sell/0032 0 2",
	"/item/bind/08/0002",
	"/item/bind/sell/0008",
	"/item/bind/sell/0010",
	"/item/bind/08/0002",
	"/item/bind/sell/0008",
	"/item/bind/sell/0010",
	"/item/bind/08/0002",
	//	130-139
	"/item/bind/sell/0041",
	"/item/bind/sell/0010",
	"/item/bind/08/0002",
	"/item/bind/sell/0041 0 2",
	"/item/bind/sell/0010",
	"/item/bind/sell/0030 0 2",
	"/item/bind/sell/0041 0 2",
	"/item/bind/08/0002 0 2",
	"/item/bind/sell/0060 0 2",
	"/item/bind/sell/0002 0 2",
	//	140-149
	"/item/bind/sell/0041 0 2",
	"/item/bind/sell/0002 0 2",
	"/item/bind/sell/0060 0 2",
	"/item/bind/sell/0002 0 2",
	"/item/bind/sell/0041 0 2",
	"/item/bind/sell/0002 0 2",
	"/item/bind/sell/0060 0 2",
	"/item/bind/sell/0002 0 2",
	"/item/bind/sell/0041 0 2",
	"/item/bind/sell/0060 0 2",
	//	150
	"/item/bind/sell/0002 0 2",
});
/*---------------------------------------完毕------------------------------------------*/

/*-----------------------------------公有函数接口--------------------------------------*/
int if_allow_prize(object player);					  //	查看当前玩家是否可以摇奖
void player_can_get_prize(object player, int if_can); //	设置当前玩家是否可以摇奖
void player_can_be_gala(object player, int if_can);	  //	设置当前玩家在得到提示的同时出现恭喜信息
void search_in_user(object player);					  //	查询当前玩家所应该提示的宝典信息
void search_in_level(object player, int level);		  //	提示当前玩家某一等级的信息
object *get_rock_item(object player);				  //	获取用户所在等级所对应的摇奖奖品列表
//string get_sell_item(object player);					//	获取收费道具的奖励
object *deal_with_item_info(string item_info);	  //	处理一个物品信息的描述返回一个实际物品
object want_an_zgdict(object npc, object player); //	给予玩家战国宝典的函数
/*---------------------------------------完毕------------------------------------------*/

/*------------------------------------类初始函数---------------------------------------*/
/*---------------------------------------完毕------------------------------------------*/

/*------------------------------------类私有函数---------------------------------------*/
//	返回一个范围不重复乱序的整数数组-- 这里假定乱序数字是一个连续整体且间隔为1
private
int *make_only_number(int from, int to, int len)
{
	int *original_dict = ({});
	int *result_dict = ({});
	int tmp, i, size;
	if (from > to)
	{
		tmp = to;
		to = from;
		from = tmp;
	}
	if (len <= 0)
	{
		len = from + to;
	}
	for (i = 0, size = (to - from); i < size; i++)
	{
		original_dict += ({from + i});
	}
	for (i = 0; i < len; i++)
	{
		tmp = random(size - i);
		result_dict += ({original_dict[tmp]});
		original_dict -= ({original_dict[tmp]});
	}
	return result_dict;
}
//	通过等级确定返回信息的函数
private
string get_info_from_level(int user_level)
{
	int lv_from, lv_to, i, size;
	mixed *lv_from_keys, *lv_to_keys;
	string user_get_info = "";
	user_level = range_value(user_level, 0, 30);
	lv_from_keys = keys(lv_user_info);
	if (!lv_from_keys)
	{
		return user_get_info;
	}
	foreach (lv_from in lv_from_keys)
	{
		if (user_level >= lv_from)
		{
			lv_to_keys = keys(lv_user_info[lv_from]);
			if (lv_to_keys)
			{
				foreach (lv_to in lv_to_keys)
				{
					if (user_level <= lv_to)
					{
						for (i = 0, size = sizeof(lv_user_info[lv_from][lv_to]); i < size; i++)
						{
							user_get_info += lv_user_info[lv_from][lv_to][i] + "\n\n";
						}
					}
				}
			}
		}
	}
	return user_get_info;
}
//	发送开启并显示信息的协议给用户
private
void send_info_to_user(object player, int level, string user_get_info)
{
	_DEBUG(user_get_info);
	_DEBUG(sprintf("恭喜标志-摇奖标志-等级 %d-%d-%d", player->get(PLAYER_BE_GALA), player->get_save(PLAYER_GET_PRIZE), level));
	send_user(player, "%c%c%c%c%c%s", 0xa6, 1, player->get_save(PLAYER_GET_PRIZE), player->get(PLAYER_BE_GALA), level, user_get_info);
	player_can_be_gala(player, 0);
}
//	出现不匹配情况下给予玩家默认物品
private
object get_default_item()
{
	object item;
	item = new ("/item/std/0001");
	item->set_value(1);
	return item;
}
/*---------------------------------------完毕------------------------------------------*/

/*------------------------------------类公有函数---------------------------------------*/
//	查看当前玩家是否可以摇奖
int if_allow_prize(object player)
{
	if (player->get_level() >= 30)
	{
		return 0;
	}
	return player->get_save(PLAYER_GET_PRIZE);
}
//	设置当前玩家是否可以摇奖
void player_can_get_prize(object player, int if_can)
{
	if (if_can)
	{
		player->set_save(PLAYER_GET_PRIZE, 1);
	}
	else if (player->get_save(PLAYER_GET_PRIZE "2"))
	{
		player->set_save(PLAYER_GET_PRIZE, 1);
		player->delete_save(PLAYER_GET_PRIZE "2");
	}
	else
	{
		player->set_save(PLAYER_GET_PRIZE, 0);
	}
}
//	设置当前玩家在得到提示的同时出现恭喜信息
void player_can_be_gala(object player, int if_can)
{
	player->set(PLAYER_BE_GALA, if_can ? 1 : 0);
	if (if_can)
	{
		player_can_get_prize(player, 1);
		if (objectp(present("Chiến Quốc Bảo Điển", player, 1, MAX_CARRY * 4)) & player->get_level() < 10)
		{
			send_user(player, "%c%c%d%d%s", 0xa6, 6, 1017, 9008, "zgdict open");
			if (player->get_2("zgdict.status") == 1)
			{
				player->set_save(PLAYER_GET_PRIZE "2", 1);
			}
		}
	}
}
//	查询当前玩家所应该提示的宝典信息
void search_in_user(object player)
{
	send_info_to_user(player, player->get_level(), get_info_from_level(player->get_level()));
}
//	提示当前玩家某一等级的信息
void search_in_level(object player, int level)
{
	send_info_to_user(player, level, get_info_from_level(level));
}
//	获取用户所在等级所对应的摇奖奖品列表
object *get_rock_item(object player)
{
	int user_level, lv_from, lv_to, i, j, size, size1, size2, size3, *only_random;
	mixed *lv_from_keys, *lv_to_keys, *item_lv_keys, user_item_arr;
	string item_info;
	object *items, *allitem = ({});
	user_level = player->get_level();
	lv_from_keys = keys(lv_rock_item);
	if (!lv_from_keys)
	{
		return allitem;
	}
	foreach (lv_from in lv_from_keys)
	{
		if (user_level >= lv_from)
		{
			lv_to_keys = keys(lv_rock_item[lv_from]);
			if (lv_to_keys)
			{
				user_item_arr = lv_rock_item[lv_from][lv_to_keys[0]];
				item_lv_keys = keys(user_item_arr);
				if (member_array(0, item_lv_keys) == -1 || member_array(1, item_lv_keys) == -1 || member_array(2, item_lv_keys) == -1)
				{
					return allitem;
				}
				size1 = sizeof(user_item_arr[0]);
				if (size1 < 1)
				{
					return allitem;
				}
				size2 = sizeof(user_item_arr[1]);
				if (size2 < 2)
				{
					return allitem;
				}
				size3 = sizeof(user_item_arr[2]);
				if (size3 < 5)
				{
					return allitem;
				}
				only_random = make_only_number(0, size1, 1);
				//	取一个0级物品描述
				item_info = user_item_arr[0][only_random[0]];
				items = deal_with_item_info(item_info);
				allitem += ({items[0]});
				for (j = 1, size = sizeof(items); j < size; j++)
				{
					destruct(items[j]);
				}
				only_random = make_only_number(0, size2, 2);
				for (i = 0; i < 2; i++)
				{
					//	取一个1级物品描述
					item_info = user_item_arr[1][only_random[i]];
					items = deal_with_item_info(item_info);
					allitem += ({items[0]});
					for (j = 1, size = sizeof(items); j < size; j++)
					{
						destruct(items[j]);
					}
				}
				only_random = make_only_number(0, size3, 5);
				for (i = 0; i < 5; i++)
				{
					//	取一个2级物品描述
					item_info = user_item_arr[2][only_random[i]];
					items = deal_with_item_info(item_info);
					allitem += ({items[0]});
					for (j = 1, size = sizeof(items); j < size; j++)
					{
						destruct(items[j]);
					}
				}
			}
			return allitem;
		}
	}
	return allitem;
}
//	获取收费道具的奖励
//string get_sell_item(object player) {
//	int user_level;
//	string item_info;
//	user_level= player->get_level();
//	item_info = lv_sell_item[range_value(user_level,0,150)];
//	return item_info;
//}
//	处理一个物品信息的描述返回一个实际物品 处理物品的格式:<物品位置/cash> <颜色/金钱数量> <物品数量>
object *deal_with_item_info(string item_info)
{
	int size_desc, color, num, i;
	string *item_seg_desc;
	object item, *allitem = ({});
	if (!item_info || item_info == "")
	{
		_DEBUG(sprintf("没有找到 %s", item_info));
		return ({get_default_item()});
	}
	item_seg_desc = explode(item_info, " ");
	size_desc = sizeof(item_seg_desc);
	if (size_desc == 2 && item_seg_desc[0] == "cash" && to_int(item_seg_desc[1]) > 0)
	{
		item = new ("/item/std/0001");
		item->set_value(to_int(item_seg_desc[1]));
		return ({item});
	}
	else
	{
		item = new (item_seg_desc[0]);
		if (!objectp(item))
		{
			_DEBUG(sprintf("没有找到 %s", item_seg_desc[0]));
			destruct(item);
			return ({get_default_item()});
		}
		if (size_desc >= 2)
		{
			color = to_int(item_seg_desc[1]);
			if (color > 0)
			{
				switch (color)
				{
				case 1:
					ITEM_EQUIP_D->init_equip_prop_1(item);
					break;
				case 2:
					ITEM_EQUIP_D->init_equip_prop_3(item);
					break;
				}
			}
			if (size_desc >= 3)
			{
				num = to_int(item_seg_desc[2]);
				if (num > 0)
				{
					if (item->is_combined())
					{
						if (num > item->get_max_combined())
						{
							item->set_amount(item->get_max_combined());
							allitem += ({item});
							num = num - item->get_max_combined();
							while (num > 0)
							{
								item = new (item_seg_desc[0]);
								if (color > 0)
								{
									switch (color)
									{
									case 1:
										ITEM_EQUIP_D->init_equip_prop_1(item);
										break;
									case 2:
										ITEM_EQUIP_D->init_equip_prop_3(item);
										break;
									}
								}
								if (num > item->get_max_combined())
								{
									item->set_amount(item->get_max_combined());
									allitem += ({item});
									num = num - item->get_max_combined();
								}
								else
								{
									item->set_amount(num);
									allitem += ({item});
									num = 0;
								}
							}
						}
						else
						{
							item->set_amount(num);
							allitem += ({item});
						}
					}
					else
					{
						allitem += ({item});
						for (i = 0; i < num - 1; i++)
						{
							item = new (item_seg_desc[0]);
							if (color > 0)
							{
								switch (color)
								{
								case 1:
									ITEM_EQUIP_D->init_equip_prop_1(item);
									break;
								case 2:
									ITEM_EQUIP_D->init_equip_prop_3(item);
									break;
								}
							}
							allitem += ({item});
						}
					}
				}
				else
				{
					allitem += ({item});
				}
			}
			else
			{
				allitem += ({item});
			}
			return allitem;
		}
		else
		{
			return ({item});
		}
	}
	return ({get_default_item()});
}
//	给予玩家战国宝典的函数
object want_an_zgdict(object npc, object player)
{
	if (USER_INVENTORY_D->count_empty_carry(player) < 1)
	{
		send_user(player, "%c%s", '!', "Hành trang không đủ 1 ô trống");
		return 0;
	}
	if (objectp(present("Chiến Quốc Bảo Điển", player, 1, MAX_CARRY * 4)))
	{
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s : \n Trên người của ngươi có một cuốn 《Chiến Quốc Bảo Điển》, không cần phải nhận lần nữa.\n" ESC "Thoát", npc->get_name()));
		return 0;
	}
	return new (ZGDICT_ITEM);
}
/*---------------------------------------完毕------------------------------------------*/