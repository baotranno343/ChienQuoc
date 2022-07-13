
#include <ansi.h>
#include <task.h>

// 数组：非本师门的回答
mapping AnswerTable = ([

        "Cấm Vệ Quân 1" :  "Tìm ta có chuyện gì cứ nói, hiện tại Bổn tướng quân không đếm xỉa tới ngươi.",

	"Cấm Vệ Quân 2" :  "Bá Vương Thương pháp cùng Phong Ma Côn Pháp cùng do triều đại khai quốc đại nguyên soái Tam Nhãn Lang Quân Dương Tiễn tướng quân sáng chế, thuật bắn súng sắc bá đạo, hung như ác điểu lợi trảo. Côn pháp hào khí vạn trượng, bài sơn đảo hải. Chỉ cần có được hai loại tài nghệ này, nhất định có thể lấy một địch trăm, kinh sợ võ lâm! Nếu ngươi muốn học nghệ thì hãy gia nhập vào môn hạ của Quân Giáo Đầu.",

	"Cấm Vệ Quân 3" :  "Cấm vệ quân tương đương am hiểu thương cùng côn sử dụng, chẳng những có thể đem này hai loại vũ khí múa may tự nhiên, trải qua nghiêm khắc rèn luyện cấm vệ quân, tại chiến trường bên trong còn có vạn phu đừng địch chi dũng.",

	"Cấm Vệ Quân 4" :  "Gần nhất tới tân binh càng ngày càng không giống nói, mới học điểm da lông nhập môn võ công, liền tự đại. Đừng nói ra chiến trường, kết quả là tựu liên tên côn đồ cũng đánh không thắng. Nhất định lần nữa đối những tân binh này hảo hảo mài luyện mài luyện!",

	"Cấm Vệ Quân 5" :  "Cấm vệ quân là trực thuộc ở đại chu thiên tử quân cận vệ đội, chủ yếu chức trách là bảo hộ thiên tử an toàn.",

	"Cấm Vệ Quân 6" :  "Quân doanh trọng địa không là một trò đùa địa phương, hi vọng các hạ chú trọng mình ở nơi này mỗi tiếng nói cử động. Nếu muốn học nghệ trong lời nói trước tiên có thể bái phỏng một chút quân giáo đầu.",

	"Cấm Vệ Quân 7" :  "Chỉ thương tiếc đương triều thiên tử yếu đuối vô năng, đành phải cho cố chấp Tần dưới. Chẳng lẽ Đại Chu thật sự vận số đã hết...",

	"Cấm Vệ Quân 8" :  "Quân doanh trọng địa không là một trò đùa địa phương, hi vọng các hạ chú ý mình ở trong này mỗi tiếng nói cử động.",

	"Thục Sơn 1" :  "Thục Sơn võ công của chia làm Phục Ma đao pháp cùng phi tiên kiếm pháp hai loại, hai đường võ công đều có đều tự bộ sách võ thuật cùng chiêu số. Hai người hỗ trợ tương xung, làm sao có thể đem hai đường chiêu số thông hiểu đạo lí, hai loại binh khí huy sái tự nhiên, đây mới là người tập võ sở theo đuổi cảnh giới cao nhất.",

	"Thục Sơn 2" :  "Tiên gia đạo pháp là Thục Sơn đệ tử thiết yếu tu hành một trong. Thông qua thiền tư minh tưởng, là được đem người thể trăm trải qua trong vòng Hỗn Nguyên chân khí dẫn, kích phát ra nhân loại vô hạn tiềm năng.",

	"Thục Sơn 3" :  "Tiên gia đạo pháp là Thục Sơn đệ tử thiết yếu tu hành một trong. Thông qua thiền tư minh tưởng, là được đem người thể trăm trải qua trong vòng Hỗn Nguyên chân khí dẫn, kích phát ra nhân loại vô hạn tiềm năng.",

	"Thục Sơn 4" :  "Thục Sơn võ công của chia làm Phục Ma đao pháp cùng phi tiên kiếm pháp hai loại, hai đường võ công đều có đều tự bộ sách võ thuật cùng chiêu số. Hai người hỗ trợ tương xung, làm sao có thể đem hai đường chiêu số thông hiểu đạo lí, hai loại binh khí huy sái tự nhiên, đây mới là người tập võ sở theo đuổi cảnh giới cao nhất.",

	"Thục Sơn 5" :  "Linh điện chi đường nhàn tạp nhân đẳng một mực không được đi vào!",

	"Thục Sơn 6" :  "Ngàn năm trước, Thục Sơn phái hai vị khai sơn tổ sư Thái Hư chân nhân cùng một lòng đạo trưởng bởi vì hiệp lực chém giết bàn theo Thục Sơn ngàn... nhiều năm yêu ma xương ức tinh mà nổi tiếng thiên hạ, về sau hai vị liền ở chỗ này sáng lập hiện tại Thục Sơn phái. Bởi vậy hàng yêu Phục Ma, vì dân trừ hại là chúng ta mỗi một cái Thục Sơn đệ tử nhất định kết thúc trách nhiệm.",

	"Thục Sơn 7" :  "Năm đó tổ sư Thái Hư chân nhân sở trì vũ khí là một phen tên là Thiên Địa Huyền Hoàng bảo đao, mà một lòng đạo trưởng còn lại là sử dụng một phen tên là 'Thất Tinh' bảo kiếm. Đúng là mượn dùng này hai kiện thần binh cùng tổ sư phi phàm công lực, mới thành công đem xương ức tinh tiêu diệt. Chỉ thương tiếc con cháu không cười, tổ sư năm đó lưu lại hai kiện thần binh đến nay chỉ còn lại có 'Thất Tinh bảo kiếm' vẫn phụng dưỡng ở linh đường trong vòng, mà đổi thành nhất cây bảo đao 'Thiên Địa Huyền Hoàng' lại bởi vì mấy chục năm lúc trước tràng đại hỏa mà không biết tung tích...",

	"Thục Sơn 8" :  "Các hạ nếu cần bái sư trong lời nói trước tiên có thể bái phỏng tử hằng sư thúc, tân nhập môn đệ tử đều là do hắn dạy.",

	"Đào Hoa nguyên 1" :  "... Khụ khụ... Không thấy được ta muốn đi ngủ sao? Tránh ra!",

	"Đào Hoa nguyên 2" :  "Vị này tiểu bằng hữu tìm ta lão thái bà này có chuyện gì? Lão bà tử ta nhưng là rất bận rộn, thực có cái gì chuyện quan trọng trong lời nói trước tìm hai tên đồ đệ của ta đi.",

	"Đào Hoa nguyên 3" :  "Thái cổ thần quyền chính là một môn uyên thâm võ công của nhé, nếu muốn học trong lời nói tốt nhất trước theo cơ bản bắt đầu. Đi tìm sư đệ của ta vô nhớ lại đi. Ngươi nhất định sẽ có điều thu hoạch.",

	"Đào Hoa nguyên 4" :  "Thái cổ thần quyền là vốn thôn tổ tông nhiều thế hệ tương truyền nhất bộ quyền pháp, chú ý chính là 'Khí ', tu luyện chính là 'Thể', cương nhu cũng tế, hình thần hợp nhất. Nếu như có thể đạt tới thượng thừa công lực, càng có thể dễ dàng lấy 'Khí ' đả thương người.",

	"Đào Hoa nguyên 5" :  "Nghĩ đến bái sư học nghệ sao? Ngươi có thể đến đối địa phương, không cần coi khinh chúng ta này chỗ hẻo lánh thôn trang nhỏ, nơi này thôn dân đều có thể mỗi người tập võ, mỗi người đều gọn gàng một thân quyền cước hảo công phu. Nhất là trong thôn vô gã trường lão, chẳng những công phu quyền cước còn gì nữa, hơn nữa nội gia công lực tu vi thập phần hùng hậu. Trong thôn đích thanh niên đều khát vọng có thể bái kỳ môn hạ vi sư. Chính là trưởng lão tính tình có điểm cô độc thích, thật khó khăn ở chung.",

	"Đào Hoa nguyên 6" :  "Trong mười năm này thôn trang nhỏ biến hóa cũng thật lớn a, cần là không có Sở quốc thương nhân đến vậy thông thương giao dịch, có lẽ bọn còn trải qua nghèo khổ cuộc sống đi?",

	"Đào Hoa nguyên 7" :  "Này thôn trang nhỏ đã cùng ngoại giới ngăn cách mấy trăm năm, cho tới nay đều là trải qua bần khổ bình thản ngày. Nếu không phải ba mươi năm thiên Thạch rơi xuống, phá hủy phong cách thôn cùng ngoại người đời kết giới, cái thôn này mọi người vẫn là trải qua cái loại này cuộc sống đi... Hết thảy đều là thiên ý a...",

	"Đào Hoa nguyên 8" :  "Đào nguyên thôn chính là một sự yên lặng cùng bình thôn trang nhỏ, hi vọng các hạ tận lực không cần phá hư nơi này tường hòa không khí, khiến cho một ít không cần thiết rối loạn.",

	"Đường Môn 1" :  "...",

	"Đường Môn 2" :  "Đường gia võ công của cũng không thích hợp cận thân chiến đấu, khắc địch chế thắng mấu chốt chính là nhất định cùng địch nhân bảo trì khoảng cách nhất định, tìm kiếm thời cơ tốt nhất đối với địch nhân làm ra một kích trí mạng. Cần là không có phi phàm khinh công thân pháp, cần đạt tới này cảnh giới có thể nói là khó sống lên trời.",

	"Đường Môn 3" :  "So sánh với lão ca, ta càng chú trọng cho tập trung lực cùng tốc độ tu luyện. Nếu như không có siêu nhân trúng mục tiêu dẫn cùng tránh tốc độ, coi như ở tiểu đao thượng đồ đầy kịch độc, không thể chuẩn xác trúng mục tiêu mục tiêu yếu hại cũng như vậy không hề ý nghĩa.",

	"Đường Môn 4" :  "Không nên xem thường cái chuôi...này không chớp mắt tiểu phi đao, chỉ cần ở trên mũi đao đồ thượng chúng ta Đường Môn bí chế độc dược, giống nhau có thể nháy mắt lấy tánh mạng người ta.",

	"Đường Môn 5" :  "Đường Môn ám khí độc bộ thiên hạ, có thể nháy mắt lấy tánh mạng người ta ở vô hình. Nếu ngươi cũng muốn bắt chước trong lời nói tốt nhất trước bái phỏng một chút công tử nhà ta, còn hơn lão gia, công tử nhà ta cùng tiểu thư đều là tương đương vui tươi người.",

	"Đường Môn 6" :  "Hi vọng các hạ ở trong này cần bảo trì tuyệt đối im lặng, lão gia nhà ta thập phần chán ghét người khác lớn tiếng tiếng động lớn làm. Nếu các hạ làm tánh mạng của mình suy nghĩ, vẫn là chú ý nhiều hơn tuân thủ nơi này quy định.",

	"Đường Môn 7" :  "Gần nhất khách nhân thật đúng là nhiều a. Thật sự là đem ta cái lão bà tử này cấp vội phá hủy.",

	"Đường Môn 8" :  "Nơi này là tư nhân nơi ở, nếu không có gì chuyện quan trọng trong lời nói tốt nhất mau ly khai.",

	"Côn Luân 1" :  "Bổn tiên gia người tu đạo cũng không nên nhúng tay thế gian việc, nhưng thiên Thạch rơi xuống cùng Trường Bình chi dịch đã lay động cả Tiên giới. Nếu chính như đồn đãi giống nhau Cửu Lê Ma tộc cùng Xi Vưu lại sống lại trong lời nói, Côn Luân chúng tiên tuyệt đối sẽ không bàng quan tọa thị không để ý tới.",

	"Côn Luân 2" :  "Bổn phái sở tu pháp thuật đều là tiên gia phương pháp. Là vì hàng yêu trừ ma mà tồn tại, tuyệt đối không cho phép đem bổn phái pháp thuật dùng cho lăng nhục nhỏ yếu, nối giáo cho giặc việc thượng!",

	"Côn Luân 3" :  "Trừ bỏ thiên sư phù chú, Càn Khôn mượn tiền cùng kim cương pháp chú cũng là bổn phái bắt buộc hai môn Đạo học. Này hai môn học thuyết đối sau khi cùng yêu ma quỷ quái lúc tác chiến tất sẽ có rất lớn giúp ích. Nếu ngươi có tâm học nghệ trong lời nói có thể trước bái phỏng sư đệ của ta Văn Xương chân quân.",

	"Côn Luân 4" :  "Côn Luân pháp thuật cơ bản lấy tính  công kích pháp thuật là việc chính, theo cơ bản nhất Phục Ma quyết đến uy lực vô cùng lôi Long quyết, phải học được thực dễ dàng, nhưng là cần tinh thông cũng linh hoạt vận dụng, nhất định phải phải đi qua thời gian dài khắc khổ tu luyện mới có thể được chính quả.",

	"Côn Luân 5" :  "Ta vốn là này Thiên Trụ người thủ hộ, hết thảy nhàn tạp nhân đẳng nghiêm cấm tới gần.",

	"Côn Luân 6" :  "Gần nhất giống như dưới chân núi xảy ra chuyện gì đại sự, sư bá các sư huynh đều thập phần khẩn trương. Ta tới nơi này tu luyện hai mươi năm vẫn là lần đầu gặp được loại tình huống này.",

	"Côn Luân 7" :  "Bổn tiên gia người tu đạo cũng không nên nhúng tay thế gian việc, nhưng thiên Thạch rơi xuống cùng Trường Bình chi dịch đã lay động cả Tiên giới. Nếu chính như đồn đãi giống nhau Cửu Lê Ma tộc cùng Xi Vưu lại sống lại trong lời nói, Côn Luân chúng tiên tuyệt đối sẽ không bàng quan tọa thị không để ý tới.",

	"Côn Luân 8" :  "Ngày hôm nay hạ yêu ma hoành hành, của ta rất nhiều sư huynh đều xuống núi trảm yêu trừ ma, vì dân trừ hại. Nếu không phải cần thủ hộ nơi đây, ta cũng nhiều sao hi vọng đi theo các sư huynh cùng nhau xuống núi a.",

	"Mao Sơn 1" :  "Gần nhất như thế nào nhiều như vậy tà hồn yêu mỵ theo âm phủ chạy đến... Diêm vương lão tử rốt cuộc đang làm cái gì quỷ a...",

	"Mao Sơn 2" :  "Gần nhất nơi nơi yêu mỵ hoành hành, Địa phủ giống như xảy ra chuyện gì đại sự, chúng ta cũng vô pháp cùng với lấy được gì liên hệ. Đại sư huynh chưa kịp việc này phiền não không thôi.",

	"Mao Sơn 3" :  "Nghịch thiên pháp chú là phái Mao Sơn thượng thừa nhất đạo thuật, thuần thục vận dùng thuật này người, liền có thể khống chế quỷ quái quấn quanh địch nhân, khiến cho thống khổ không chịu nổi. Trong lúc thuật tu luyện tới lô hỏa thuần thanh nông nỗi sau, càng có thể gọi thiên tôn Phụ Thể, cùng thuật giả hình thần hợp nhất, được đến vô cùng thần lực!",

	"Mao Sơn 4" :  "Cũng không phải là vốn nói khoe khoang, bổn phái pháp thuật tuyệt đối là đệ nhất thiên hạ! Khu ma gọi quỷ không cần phải nói, còn có thể gọi về thiên binh thần tướng. Chỉ cần có này đó cường đại người giúp đỡ, chiến đấu còn có cái gì phải sợ!",

	"Mao Sơn 5" :  "Hí... Tê tê...",

	"Mao Sơn 6" :  "Nơi đây vốn là làm âm dương nhị giới hoà vào nhau chỗ, vô số oan hồn quỷ quái cũng sẽ ở này xuyên toa vu nhân thế cùng quỷ giới trong lúc đó. Bởi vậy ở trong này gặp được cái gì âm hồn quỷ quái cũng không phải là cái gì kỳ quái chuyện tình.",

	"Mao Sơn 7" :  "Coi như ta đã chết đi nhiều năm, nhưng là ta hiện tại giống nhau quả thật rất khoái hoạt.",

	"Mao Sơn 8" :  "Hiện tại ta đã có thể tự nhiên gọi về quỷ binh đi ra, qua không được bao lâu ta nhất định có thể đem cao hơn tầng thiên binh triệu hoán đi ra!",

	"Vân Mộng Cốc 1" :  "Lão phu mở cửa thụ đồ cũng không phải vì gì danh lợi, mà là hi vọng lão phu sở thụ hết thảy có thể cứu vớt này phân chiến thiên hạ, chấm dứt này náo động thời đại.",

	"Vân Mộng Cốc 2" :  "Trừ bỏ luyện đan chế dược, chúng ta còn nắm giữ các loại kỳ môn trận pháp, tâm trí mê hoặc thuật. Tin tưởng này đó học thức nhất định có thể tại chiến trường trung đại phái công dụng.",

	"Vân Mộng Cốc 3" :  "Thầy cô giáo chẳng những đối các loại linh dược có khắc sâu hiểu biết, hơn nữa đối đủ loại độc vật cũng có khắc sâu nghiên cứu. Các loại dược vật luyện chế phương pháp thầy cô giáo đều truyền thụ ta chúng ta Tam sư huynh đệ. Nếu ngươi có hứng thú học trong lời nói trước tiên có thể bái phỏng một chút sư đệ của ta Tô Tần.",

	"Vân Mộng Cốc 4" :  "Cứ việc y thuật của ta so ra kém hai vị sư huynh của ta, nhưng nếu các hạ cố ý muốn học, ta cũng chắc chắn hết sức đem bình sanh học toàn bộ tương thụ.",

	"Vân Mộng Cốc 5" :  "Tôn Tẫn, Bàng Quyên, Tô Tần ba vị sư thúc đều là sư thừa cho Quỷ Cốc tử tổ sư môn hạ tam đại đắc ý môn đồ.",

	"Vân Mộng Cốc 6" :  "Phổ cứu chúng sinh, làm nghề y tế thế là chúng ta làm nghề y người ứng làm hết phận sự trách.",

	"Vân Mộng Cốc 7" :  "Cứu người cùng giết người chỉ để ý nghĩ sai thì hỏng hết. Nếu giết một người có thể cứu trăm người trong lời nói, này cảm giác không phải là một món đồ công đức đây?",

	"Vân Mộng Cốc 8" :  "...",


]);

// 函数：获得非本师门的回答
string get_answer( string family, int order ) 
{ 
        string name;
        name = sprintf("%s%d", family, order);
        if ( AnswerTable[name] == 0) return "Chào các hạ.";
        else return AnswerTable[name];
}
