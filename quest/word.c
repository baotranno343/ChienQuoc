
#include <ansi.h>
#include <task.h>

mapping NomalWordTable = ([

	"0001"   :  "Nếu vật phẩm trên người ngươi quá nhiều, và ngươi tin tưởng ở lão phu thì ngươi có thể để lại những thứ dư thừa ở chỗ của ta, ta sẽ không thu một xu phí nào. Đương nhiên nếu muốn lấy lại vật phẩm cũng phải thông qua ta!", 
	"1001"  : "Lão phu năm nay sáu mươi sáu, làm hiệu cầm đồ lão bản cũng có hơn - ba mươi cái lâu lắm rồi, nếu ngươi mang bên mình mang theo gì đó nhiều lắm, ta nhưng lấy giúp ngươi tồn tại, thủ thời gian cũng rất phương tiện!",
	"2001"  : "Cầm tự nguyện, lấy lại liberdade, già trẻ không gạt, đây là ta nhất quán phục vụ tôn chỉ, qua nhiều năm như vậy cho tới bây giờ không thay đổi qua, khách quan có cái gì tài cán ngài phục vụ sao? Có dùng được chỗ của ta cứ việc nói!",
	"3001"  : "Gần nhất thế đạo không nhiều Thái Bình, nếu ngươi phải ra khỏi cửa đích nói, tốt nhất là đem quý trọng vật phẩm tồn tại, miễn cho nửa đường gặp được thổ phỉ đạo tặc, bị mất có thể sẽ không tốt, nghe lão phu khuyên, cho phép đúng vậy!",
	"4001"  : "Người khác nói tâm rộng thể béo, ngươi nhìn ta này hình thể, cần phải hiểu ta đối nhân xử thế rộng bao nhiêu dung, ta chưa bao giờ sẽ vì bất cứ chuyện gì cùng bất luận kẻ nào phát sinh khắc khẩu, lui từng bước trời cao biển rộng, xả xa, ha ha, ngươi xem ngươi cần tồn tại chút gì đó?",
	"5001"  : "Ta đây có thể cho ngươi miễn phí tồn tại thủ đồ vật này nọ, giao cho ta ngươi cứ yên tâm đi, từng bước đúng chỗ, tuyệt đối an toàn, hơn nữa có thể ở thế giới các nơi mặc cho quân tồn tại thủ, cam đoan sẽ không ra bán một chút lầm lỗi.",
	"6001"  : "Nghe nói Tề quốc có một cái kêu nhà thuỷ tạ hoa đều địa phương phong cảnh thập phần tú lệ, chờ vội hoàn này tra, khi nào thì ta cũng đi xem, cửa hàng sự liền giao cho ta nhi tử tốt lắm, cũng tới rèn luyện hắn thời gian.",
	"7001"  : "Ta nhưng là một lòng nhiệt tình, thường xuyên trợ giúp người khác, hơn nữa làm tốt sự chưa bao giờ lưu danh. Ngươi nếu là có cái gì mang không dưới gì đó, giao cho ta bảo quản tốt lắm, cam đoan không sơ hở. Hơn nữa ngươi có thể tùy thời tới lấy, thực phương tiện.",
	"8001"   :  "Đối với người nhiệt tình, thành thật giữ chữ tín là tôn chỉ phục vụ của ta. Chỉ cần ngươi có vấn đề gì, trực tiếp đến tìm ta, ta nhất định sẽ tận lực giúp ngươi, hôm nay ngươi đến gửi đồ hay lấy đồ?", 
	 
	"0002"   :  "Xin chào, ta là Chủ Tiệm Tạp Hoá trong thôn, nếu ngươi muốn mua các loại tạp hoá như giấy điểm phù, đến tìm ta là đúng rồi! Nếu ngươi muốn bán các vật phẩm thu thập được, cũng có thể đến tìm ta!", 
	"1002"   :  "Thực vật thuốc bổ, nam bắc tạp hoá, muốn mua liền tới tìm ta! Cam đoan vật đẹp giá rẻ, vật vượt qua chỗ đáng, trừ bỏ mua đồ ngoại, ở chỗ này của ta, còn thu về các ngươi không cần tạp hoá, nếu có trong lời nói, cũng có thể lấy ra bán cho ta!", 
	"2002"  : "Các vị hương thân phụ lão, không có việc gì tới bổn điếm nhìn một cái, tuyển nhất tuyển, giống phồn đa, nói không chừng có gì đó vừa vặn ngươi hữu dụng, nói không chừng ngươi tìm thật lâu gì đó ngay tại bổn điếm.",
	"3002"  : "Đừng nhìn ta mở ra nhà này nho nhỏ không chớp mắt tiệm tạp hóa, nếu xa cách ta này gian tiệm tạp hóa, các ngươi cũng thật không như vậy phương tiện, muốn mua điểm đồ vật này nọ hoặc là bán điểm đồ vật này nọ đều phải chạy rất xa đâu.",
	"4002"  : "Ta vốn là Ngụy Quốc nhỏ bé thảo dân, sau lại bởi vì gia phụ qua đời lưu lại chút tiền, mở này nhà hàng tạp hóa, coi như là cuộc sống có điểm bảo đảm, ít nhất không cần vì sinh kế ưu sầu, còn có thể dư chút tiền trinh để lại cho ta nhi tử, coi như là vừa lòng cuộc sống bây giờ.",
	"5002"  : "Ta đây trẻ gì đó đều có thể nhà khác mua không được, là ta trời nam biển bắc chạy rất nhiều địa phương thu mua tới, nếu ngươi cần nói, không cần lo lắng nhiều lắm, ta cam đoan cho ngươi mua sẽ không cảm thấy được hối hận.",
	"6002"  : "Ngươi phát hiện không? Ở ta Sở quốc, theo ta này nhất nhà hàng tạp hóa, kỳ thật vốn là có mấy nhà, sau lại bởi vì bán hàng giả, chỉ còn lại ta đây gia, cho nên, ngươi có thể phóng một trăm hai mươi cái tâm, chỗ này của ta tuyệt không hàng giả, giả nhất phạt thập.",
	"7002"  : "Ngươi là chuẩn bị xuất môn làm việc sao? Nhìn xem có hay không ít đeo cái gì vậy, một khi xuất môn sẽ không rất phương tiện tiếp tế, sớm làm chuẩn bị thật là tốt. Còn có, trên người đồ vật này nọ nhiều lắm cũng bất lợi với chạy đi, có cái gì không cần có thể bán cho ta, đổi thành cũng đủ địa bàn triền.",
	"8002"  : "Ngươi muốn mua chút gì đó? Hoặc là muốn bán chút gì đó? Chỗ này của ta cũng có thể giúp ngươi, chỉ cần ngươi trở ra lên giá tiền, ngươi có thể mua được chính mình thỏa mản vật phẩm, đương nhiên, trên người ngươi không đủ tiền cũng không sao, ngươi trước tiên có thể bán điểm đồ không cần cho ta.",
	 
	"0003"  : "Trăng có khi mờ khi tỏ khi tròn khi khuyết, ng chen đẩy có sinh lão bệnh tử, ai chẳng có lúc sinh bệnh, nói xem ngươi không khoẻ chỗ nào? Ta đảm bảo thuốc đến bệnh khỏi, nhanh chóng phục hồi sức khoẻ.",
	"1003"  : "Bản nhân có được tổ truyền bài thuốc gia truyền, truyền nam không truyền nữ gia tộc tuyệt học, chỉ cần có người bệnh để van cầu y, ta đều cũng nhất nhất trợ giúp bọn hắn, thẳng đến bọn hắn hoàn toàn khôi phục khỏe mạnh, hơn nữa ta thu phí cũng không quý, chỉ cần tốn chút tiền trinh, là có thể y hảo bệnh của mình.",
	"2003"  : "Đương quy cùng quy linh có dưỡng nhan công hiệu? Ta như thế nào không nghe nói qua đây? Trước kia sư phó cũng không dạy qua ta nha, y học thật là uyên thâm a, xem ra ta phải nhiều đọc đó sách thuốc, nhiều học tập học tập.",
	"3003"  : "Trường sanh bất lão thuốc ngươi nghe nói qua sao? Trên đời thực sự loại này thuốc sao? Nghe nói hoàng đế lão nhân nào có chuyên gia phụ trách luyện chế loại này thuốc, nếu thật là có nói, ta cũng muốn thử đi luyện xuống.",
	"4003"  : "Làm thầy thuốc phải làm lấy cứu sống, tế thế tế dân làm nhiệm vụ của mình, ta cuộc đời thống hận nhất đúng là này hám lợi thầy thuốc, được kêu là lợi dụng lúc người ta gặp khó khăn, không là một thầy thuốc nên có hành động.",
	"5003"  : "Này rối loạn, khi nào thì chiến tranh nói đến là đến, ai, mấy ngày hôm trước chúng ta cái này đại chiến một hồi, bị thương không ít người a, vẫn là mua điểm thuốc phóng ở nhà so sánh bảo hiểm a.",
	"6003"  : "Đau đầu y đầu, đau chân y chân, đây là thầy thuốc chẩn bệnh tối kỵ. Lấy việc phải học được học một biết mười, loại suy. Xem bệnh lấy thuốc nhất định phải chú ý, không nên bị lang băm sở lầm.",
	"7003"  : "Gần nhất cầu thầy người càng ngày càng nhiều, đầu năm nay a, chiến tổn thương người nhiều lắm, thế nào trong nhà cũng phải bị điểm thường dùng thuốc đi, giống hành quân tán, lung lay hoàn, chính khí tán linh tinh, loại này thuốc cũng không quý, thời điểm mấu chốt có thể tạo được đại tác dụng nha.",
	"8003"  : "Tệ nhân hành nghề y đã hơn 40 năm, đã thấy đủ các chứng bệnh, nếu ngươi có gì không hiểu cứ đến tìm ta thỉnh giáo! Chỗ của ta còn bán một số dược vật thông thường, đều do ta tự bào chế, vừa rẻ vừa tốt.",
	 
	"0004"  : "Chà, có khách rồi, khách quan muốn mua gì? Nhìn dáng ngươi ra vẻ một kẻ hành quân tác chiến, loại vũ khí sắc bén đối với các ng chen đẩy là rất quan trọng! Chỗ của ta có rất nhiều thứ mà ngươi dùng tốt, xin cứ tự nhiên xem qua.",
	"1004"  : "Nhĩ hảo, ta là Tề quốc vũ khí điếm lão bản, ta đây trẻ vũ khí giống đầy đủ, giá cả vừa phải, Tề quốc các dũng sĩ đều là ở ta đây mua vũ khí, còn có rất nhiều nơi khác người cũng mộ danh tiến đến, không mua ngươi sẽ hối hận.",
	"2004"  : "Ta là bảo kiếm đồ đệ, bảo kiếm ngươi nghe nói qua sao? Hắn thật ra tạo ra thần binh tông sư, tay nghề của ta ngươi còn dùng hoài nghi? Làm sao vậy? Không tin? Ta nói mạnh miệng? Không tin ngươi tìm ta làm một phen cho ngươi xem.",
	"3004"  : "Mười tám món binh khí ta mọi thứ đều cũng tạo ra, không có ta sẽ không làm, chỉ có ngươi không thể tưởng được, ngươi cứ nói yêu cầu của ngươi đi! Ta tuyệt đối sẽ dựa theo yêu cầu của ngươi tạo ra một thanh cho ngươi không thể xoi xét binh khí.",
	"4004"  : "Ta nghe nói có thể kiệt lực phụ tá chủ nhân tên người thanh hiển hách, công lao cao nhân thân phân tôn sùng, quản lý quốc gia chính sự nhân quyền lợi lớn, tín thành nguyện trung thành lấy mình làm gương người nhân dân kính phục, ta Ngụy Quốc tướng sĩ đẫm máu giết địch, làm như vậy là để vua thống nhất giang sơn sự thống trị, làm cho người ta tôn kính, ta tự nhiên cũng muốn ra một phần lực.",
	"5004"  : "Coi trộm một chút, nhìn một cái, không mua không sao cả. Ta đây có vũ khí tốt nhất, đều là chính mình rèn, đây là ta sư phó dạy cho của ta tuyệt sống, không có hơn mười hai mươi năm rất khó luyện liền, vị khách quan kia, ngươi muốn hay không nhìn một cái?",
	"6004"  : "Ta nghe nói tài đức sáng suốt vua đối với hắn nhân dân, là áp dụng toàn diện giáo dục cũng giáo cho bọn hắn các loại kỹ năng phương pháp tiến hành quản lý, ta đây tạo ra binh khí đích tay nghề liền là cha mẹ của chúng ta quan gọi ta đi học.",
	"7004"  : "Có chắc chắn phòng cụ, ngươi còn cần trang bị vũ khí tốt nhất. Đến ta đây nhìn xem đi, tất cả đều là ta theo thế giới các nơi lục soát tìm thấy vũ khí tốt, ngươi cứ việc chọn, chọn một cái ngươi thỏa mản, ta tiện nghi điểm tính cho ngươi, thái độ làm người phục vụ tôn chỉ chính là bao quân vừa lòng.",
	"8004"  : "Muốn đánh tạo một thanh hảo vũ khí, chỉ có một thân cậy mạnh không thể được, còn cần phi thường thuần thục kỹ thuật, phi thường tinh tế ý nghĩ, phi thường nhanh nhẹn phản ứng, hơn nữa tính nhẫn nại cũng là thiết yếu nha.",
	
	"0005"  : "Không thể mang lòng hại ng chen đẩy, nhưng đề phòng ng chen đẩy cũng không thể thiếu! Khách quan hãy mua một bộ trang bị. trang bị tốt vừa có thể bảo vệ ngươi ít chịu thương tổn mà còn giúp ngươi trở nên mạnh mẽ hơn.",
	"1005"  : "Hảo phòng cụ hoà thuận vũ khí giống nhau trọng yếu! Ta chuyên doanh nam trang, bán được chính là Tề quốc tốt nhất phòng cụ nga! Nếu ngươi không tin ta theo như lời nói, có thể ở Tề quốc chung quanh nhìn xem hỏi một chút, xem ta có hay không lừa ngươi.",
	"1006"  : "Tiền nào đồ nấy, chuyên doanh các loại nữ tính chức nghiệp bộ đồ, lại xinh đẹp lại tiện nghi. Các vị nghiệp dư nữ hiệp nhóm đều đến xem, cam đoan sẽ có ngươi thỏa mản chức nghiệp bộ đồ.",
	"2005"  : "Mấy năm nay, mưa gió hợp thời hợp lễ, mưa thuận gió hoà, nông dân nhóm ngũ cốc được mùa, cất vào kho sung túc, cảm thấy vạn phần vui sướng, cũng có điểm tiền nhàn rỗi làm người nhà mình mua thêm quần áo, việc buôn bán của ta cũng là càng ngày càng ... hơn náo nhiệt.",
	"2006 "	 : "Nhìn xem này đó vật phẩm trang sức, đều có thể ta tinh khiêu tế tuyển. Khách quan không mua chính là ngươi có hại a ~",
	"3005"  : "Làm một món đồ tốt nhất quần áo, không chỉ cần kỹ càng tài nghệ, còn cần tốt nhất vải dệt, hai người kết hợp hoàn mỹ mới là. Ta đây mới vừa cấu quay về một đám tốt nhất vải dệt, ngươi xem này bố sắc, ngươi xem này khuynh hướng cảm xúc, cần ta làm cho ngươi một món đồ sao?",
	"3006" 	 : "Người dựa vào giả bộ, mã dựa vào yên. Không hảo hảo giả dạng chính mình một chút như thế nào được? Ăn mặc ngăn nắp tâm tình tự nhiên cũng sẽ hảo.",
	"4005"  : "Người dựa vào quần áo, mã dựa vào yên. Không hảo hảo giả dạng chính mình một chút như thế nào đi ra ngoài gặp người? Tuy rằng chỉ có rất ít người sẽ trông mặt mà bắt hình dong, nhưng là ăn mặc ngăn nắp điểm mình cũng hiểu ý chuyện tốt hơn nhiều. Ở ta đây chọn mua một món đồ đi.",
	"4006 "	 : "Tiền nào đồ nấy, chuyên doanh Y Sinh bộ đồ, lại tiện nghi lại xinh đẹp. Các vị đều đến xem a, cam đoan sẽ có ngươi thỏa mản.",
	"5005"  : "Vị đại hiệp này, người xem xem ta thứ này, nhìn xem này nguyên liệu vải, nhìn xem này thợ khéo, thật tốt! Muốn hay không mua bộ, hoặc là ngài trước thử xem, hài lòng ngài tiếp tục mua, nếu không ngươi tựu giữ giòn hàng so với Tam gia, ta cam đoan ngài sẽ quay đầu lại ta đây!",
	"5006"  : "Mở này điếm đã lâu như vậy, ngày hôm nay chính là bận rộn nhất một ngày, ta cũng giống như con quay giống nhau, tuy rằng mệt điểm, nhưng là trong lòng vẫn là rất cao hứng, làm người làm ăn mà nói, sinh ý hảo ai không thích nha, mệt điểm, giá trị nha!",
	"6005"  : "Ta bình sinh coi trọng nhất, là thay người khác sắp xếp ưu giải nạn mà không đòi lấy báo thù thiên hạ danh sĩ, nếu như nói thu thù lao, vậy cùng chúng ta thương gia không có gì khác nhau, nếu có một ngày ta có thể làm được như vậy, cũng không uổng cuộc đời này a!",
	"7005"  : "Đi qua đi qua không cần bỏ qua! Vốn phòng cụ điếm chuyên trong doanh sa hoa phòng cụ, Yến quốc chỉ này một nhà, già trẻ không gạt, mọi người yên tâm mua, chỉ cần là ngươi có thể nghĩ đến, chỗ này của ta liền cái gì cần có đều có. Nhường ngài chọn cái đủ!",
	"7006 "	 : "Khách quan, cần chút gì đó sao? Chỗ này của ta thợ khéo chính là nhất lưu. Rất nhiều quan lớn nhân vật nổi tiếng đều cũng đến bổn điếm mua sắm vật phẩm trang sức đâu ~",
	"8005"  : "Đại hiệp, ngươi xem xem này đó, này nhưng đều là ta tinh khiêu tế tuyển, chúng ta có chính quy nhập hàng con đường, có cố định cung ứng thương gia, có hùng hậu kinh tế thực lực ủng hộ. Ngươi mua ta đây gì đó cứ việc yên tâm.",
	"8006"  : "Mỗi ngày đều đứng ở này, nhìn thấy người đến người đi, nội tâm lại vô hạn cô độc, kiếm nhiều hơn nữa tiền thì phải làm thế nào đây, tiền tài là đổi không trở về hạnh phúc, trượng phu qua đời được sớm, ta một nữ nhân, chống đỡ lên cái nhà này, thực vất vả, cách vách nhà đó điếm, mỗi ngày Tề nhạc vui hòa, để cho ta không ngừng hâm mộ.",
	 
	"1020"  : "Ta chạy rất nhiều địa phương, mới tìm được này bảo thạch mảnh nhỏ, nghe nói nó có thần kỳ công hiệu, có thể đem không trọn vẹn bảo thạch biến thành hoàn mỹ bảo thạch! Ta chưa thử qua, không biết rốt cuộc có thể hay không, ngươi mua đi thử qua sau, đem kết quả nói cho ta biết thành sao?",
	"2020"  : "Đừng nhìn ta chung quanh lưu lạc, Nhưng ta làm sinh ý không đơn giản! Không thấy ta ở mua bán bảo thạch sao? Bảo thạch giống có thể hơn, chỉ từ nhan sắc thượng muốn phân rất nhiều loại đi ra, như: đen bảo thạch, lục bảo thạch, Hồng Bảo Thạch từ từ.",
	"3020"  : "Ngươi nghĩ rằng ta và ngươi bán ra bảo thạch mảnh nhỏ đan là vì tiền sao? Ngươi lý giải sai lầm rồi, lý tưởng của ta là trở thành một gã thành công bảo thạch thương nhân. Nhưng là hiện tại tỉ lệ phi thường tốt bảo thạch sinh ý ta làm không dậy nổi, nhưng thu mua bán ra một ít không trọn vẹn bảo thạch, ta còn là có tin tưởng.",
	"4020"  : "Vì thu thập này đó bảo thạch mảnh nhỏ, ta đã đem hết trí tuệ của mình cùng lực lượng, hiện tại ta cũng không có khí lực đi chung quanh lưu lạc, thầm nghĩ bán đi bọn hắn, tránh điểm tiền trinh, sau đó tìm một chỗ an định lại.",
	"5020"  : "Ngươi không biết, lúc trước ta tìm được này có thể đem không trọn vẹn bảo thạch biến thành hoàn mỹ bảo thạch bảo thạch mảnh nhỏ thì hạ bao nhiêu công phu, ta thiếu chút nữa bị này quái vật giết chết, sau lại lại bị người đuổi giết lên thưởng này bảo thạch mảnh nhỏ, cửu tử nhất sinh ta mới chạy thoát trở về.",
	"6020"  : "Ta từ trước liền thích có chứa không trọn vẹn đẹp gì đó, tuy rằng không ít bị người mắng bệnh thần kinh, nhưng là ta còn là kiên trì quan điểm của mình, ta tại đây bán ra này đó bảo thạch mảnh nhỏ, kỳ thật cũng chính là muốn tìm đến một cái tri âm, có thể thưởng thức ta thưởng thức gì đó.",
	"7020"  : "Mấy năm nay ta chung quanh lưu lạc, tuy rằng cuộc sống khổ điểm, nhưng là cũng không phải thường có ý nghĩa, đi qua rất nhiều phong cảnh tú lệ địa phương, gặp được rất nhiều kỳ quái chuyện tình, khiến nhân sinh của ta lịch duyệt cũng phong phú rất nhiều, sau tới một người dạo chơi nói người tống ta đây đồng bảo thạch mảnh nhỏ, hắn dặn dò ta tìm được một vị người hữu duyên, mới có thể phát huy này tác dụng!",
	 
	"0007"  : "Các ngươi đại khái vẫn chưa biết chỗ ta làm gì phải không, thấy chưa? Thuộc tính của đồ dùng có một độ bền, nếu độ bền không đủ, đồ dùng sẽ hư hỏng, lúc này ngươi nên mang đến chỗ ta sửa chữa.",
	"1007"  : "Hoa mai hương chuốc khổ hàn, bảo kiếm phong theo ma luyện ra. Dù cho vũ khí đều cần định ngày kiểm tra, mới có thể bảo trì nó tính năng không chịu ảnh hưởng, ân, nhìn xem, vật của ngươi là nên sửa chữa sửa chữa.",
	"2007"  : "Nhà của ta có lão mẫu thân, gia cảnh bần hàn. Du đãng tha hương, trà trộn cho tàn sát cẩu giết heo trong đám người, mở một gian sửa chữa điếm, chỉ là muốn có thể mỗi ngày là mẫu thân phụng dưỡng một phần ngon miệng đồ ăn. Tuy rằng vất vả, nhưng là ta cũng tự đắc này vui.",
	"3007"  : "Người khác nói ham món lợi nhỏ lợi mà chuốc lấy tai hoạ, cho nên làm người hay là muốn chân thành điểm thật là tốt, không cần lão nhớ lên có thể coi là kế người khác, có thể ngươi đang ở đây tính kế trong quá trình đã muốn bị mất càng đẹp đồ tốt, ta buôn bán có thể là phi thường phúc hậu.",
	"4007"  : "Gừng càng già càng cay, những lời này quả thực chính là để hình dung của ta, ha ha, ta mở sửa chữa điếm nhiều năm như vậy, qua tay phòng cụ vũ khí đã muốn vô số kể, kỹ thuật đã muốn phi thường chu đáo.",
	"5007"  : "Làm như một gã xuất sắc sửa chữa sư, Tần quốc có thể không thể thiếu ta! Rất nhiều quan lại quyền quý phòng cụ đều là đến ta đây sửa chữa, ta đây chẳng những giá cả vừa phải, sửa chữa hiệu quả cũng tuyệt đối sẽ làm cho ngươi vừa lòng nga,, cho ta xem, của ngươi trang bị làm sao vậy.",
	"6007"  : "Tục ngữ nói, tôn kính người khác người, người khác mới sẽ tôn kính ngươi. Tuy rằng ta việc làm không có nhiều làm cho người ta tôn kính, nhưng là tới khách nhân, ta đều phi thường tôn trọng ý nguyện của bọn họ, cho nên người khác đối với ta đánh giá cũng tương đương hảo, điều này cũng làm cho của ta sửa chữa sinh ý càng ngày càng tốt.",
	"7007"  : "Vợ về nhà mẹ đẻ hảo vài ngày, này những ngày sau này là rối tinh rối mù a, ta mỗi ngày lại muốn trông tiệm lại muốn nấu cơm, may mắn ta này lão khách hàng không có làm khó ta, lấy ra sửa chữa vật phẩm có thể hơi chút từ nay về sau áp áp, thật sự là cảm kích bọn hắn, sau khi nhất định phải cấp khách nhân cung cấp muốn hảo phục vụ!",
	"8007"  : "Nghe nói Chu Quốc mới mở một tiệm sửa chữa, đây chưa hẳn tốt, ta phải nghĩ cách, không để hắn giành chuyện làm ăn của ta, ta phải nâng cao chất lượng phục vụ, sau đó hạ thấp giá cả một chút, như thế chắc sẽ không bị mất khách!",
	 
	"0010"  : "Hoan nghênh ngươi đến thế giới thần kỳ, ngươi đã quen thuộc với Tân Thủ Thôn, bây giờ có phải muốn ra ngoài thăm dò thế giới bên ngoài? Ta sẽ cho ngươi một phần dũng cảm để thăm dò thế giới bên ngoài.",
	"1010"  : "Ta lúc này trạm dịch phụ trách đón vận công việc đã lâu, phàm là có công văn mật hàm chưa bao giờ mất đi qua; quan lại phái tặng, cũng chưa bao giờ không may xuất hiện. Ngươi có phải hay không cảm thấy được ta thực làm hết phận sự đây?",
	"1011"  : "Ta không chỉ có nhân viên phụ trách phương diện đón vận, cũng có thể cho ngươi vận chuyển hàng hóa. Đến nỗi chi ngân lượng cũng đều giống nhau, sẽ không ngoài định mức thu. Ngươi còn có cái gì yêu cầu đây?",
	"2010"  : "Gần nhất các lộ chư hầu phân tranh càng ngày càng lợi hại, xem ra một hồi đại chiến không thể tránh được. Không lâu này trạm dịch sẽ công việc lu bù lên, rất nhiều khẩn cấp chiến báo, tin tức quan trọng văn kiện mật đều được từ nay về sau truyền phát ra đi.",
	"2011"  : "Làm mọi người phụ trách đón vận chở, là trách nhiệm của ta cùng nghĩa vụ. Chỉ cần có thể làm khách quan mang đến phương tiện, ta sẽ tương đương thỏa mãn. Nếu ngươi muốn đi nơi khác, cứ việc nói cho ta biết đi!",
	"3010"  : "Trạm dịch là quốc gia làm truyền lại khẩn cấp tình báo, mật hàm công văn mà thành lập làm việc cơ cấu. Bất quá ta chính là phụ trách người bình thường viên đón vận, nếu ngươi cần muốn đi quốc gia nào, ta cũng có thể trợ giúp ngươi.",
	"3011"  : "Ở trạm dịch công tác, ta cảm thấy được là một loại quang vinh. Đối với mình thuộc bổn phận việc, ta từ trước đến nay làm hết phận sự hết thủ, không dám có nửa điểm sai lầm. Không tin? Ngươi cứ việc đến hỏi xung quanh dân chúng, xem bọn hắn là như thế nào đánh giá của ta!",
	"4010"  : "Nhìn ngươi hành tẩu vội vàng như thế, hay không có chuyện quan trọng vội vã đi làm? Trạm dịch tuy nói là nhà nước cơ cấu, nhưng ngươi chỉ cần thường phó nhất định ngân lượng, ta cũng rất vui phục vụ cho ngươi.",
	"4011"  : "Khách quan, có cái gì có thể trợ giúp của ngươi sao? Bản lãnh của ta có thể lớn đâu! Trời nam biển bắc ta đều có thể phụ trách đem ngươi đưa đến, không tin? Ngươi liền thử xem xem.",
	"5010"  : "Trạm dịch mặc dù là triều đình bố trí ở chỗ này đón vận cơ cấu, nhưng là có ngoại lệ, ngươi chỉ cần chi nhất định ngân lượng, ta liền có thể đem ngươi chở đến bất kỳ một cái nào quốc gia.",
	"5011"  : "Làm sự tình cần chú ý hiệu suất, nếu ngươi muốn đi chỗ rất xa, vẫn là ta tới trợ giúp ngươi chứ ta sẽ dùng thời gian ngắn nhất đem ngươi tặng đã qua, thường thử một chút ngươi sẽ biết.",
	"6010"  : "Sở quốc vốn là Đông Nam Tây Bắc chi giao thông yếu đạo, bất luận ai ngờ tranh bá thiên hạ, cần phải từ nay về sau thông qua, từ xưa đến nay nơi đây liền vốn là binh gia vùng giao tranh. Có thể suy nghĩ là biết, trạm dịch lúc này phát huy tầm quan trọng.",
	"6011"  : "Ta mặc dù phụ trách vận chuyển thủ tục, nhưng ta một vốn một lời quốc sản vật vẫn là tương đương hiểu biết, có ... hay không nghĩ tới theo nước nhà buôn đó hạt sen đi ra ngoài bán đây? Hạt sen chính là nước nhà đặc sản nga!",
	"7010"  : "Nhìn ngươi đi như thế vất vả, ngươi sẽ không nghĩ tới mượn những phương pháp khác đến trợ giúp chính mình? Ngươi không biết ta là một chuyên trách chở nhân viên sao? Nói, ngươi muốn đi thế nào?",
	"7011"  : "Theo người hộ dần dần tăng nhiều, trạm dịch tác dụng có thể càng lúc càng lớn. Ta mỗi ngày ở trong này không biết cần vận chuyển bao nhiêu người cùng vật, cơ hồ đều hết hơi.",
	"8010"  : "Thân là Đại Chu trạm dịch chở viên, ta cảm thấy cao hứng phi thường cùng quang vinh, hi vọng sự trợ giúp của ta có thể cho ngươi mang đến phương tiện, xin hỏi ngươi muốn đến chỗ nào? Ta có thể sử dụng tốc độ nhanh nhất đem ngươi tặng đã qua.",
	 
	"0015"  : "Khách quan muốn dùng gì? bổm tiểm có rất nhiều món ngon vật lạ, còn cung cấp chỗ ở, hay ngươi chỉ muốn đổi Thực phẩm? Có gì cần cứ đến tìm ta, ta sẽ giúp ngươi sắp xếp thoả đáng.",
	"1015"  : "Ngày đó có một cái người thật kỳ quái, nói muốn đi Sở quốc, còn mua rất nhiều thực vật cất giữ, ta hoài nghi hắn là thích khách linh tinh người, nghĩ tại vùng ngoại ô trốn tránh, thừa dịp nguyệt hắc phong cao khi gây án.",
	"1016"  : "Mấy ngày nay là kín người hết chỗ a, không biết huynh đệ của ta chỗ ấy sinh ý như thế nào, mấy ngày hôm trước còn nghe hắn nói có một cái người thật kỳ quái, giống thích khách, ta đây trẻ thông thường chỉ có dân chúng bình thường thăm, khi nào thì ta cũng gặp gỡ cái thích khách thì tốt rồi, coi như là giải buồn.",
	"2015"  : "Ta nghe nói qua nói như vậy, có một số việc ngài không có thể biết, mà có chút ngài không thể không biết; có chút ngàn vạn lần không thể nào quên, mà có chút lại phi quên mất không thể. Khách sạn chính là phi nhiều, phải làm đến điểm ấy còn thật là khó khăn.",
	"2016"  : "Ta đây trẻ có thể tất cả đều là địa phương khác ăn không đến đất đặc sản, giống linh bảo đại tảo, phong Khâu Thạch lưu, Đỗ Khang rượu, Hoài Dương cây kim châm, Hoàng Hà cá chép đợi, những điều này là do chúng ta chiêu bài đồ ăn.",
	"3015"  : "Nghe người ta nói mong đều cây ớt cùng gà trạch cây ớt nổi danh nhất, đáng tiếc ta đây trẻ không có, xem ra ta phải sai người xuất môn một chuyến, tiến cử này đó nổi tiếng vật phẩm, như vậy mới có thể càng hấp dẫn khách nhân tiến đến.",
	"3016"  : "Nghe nói nổi danh tùng thai rượu nầy đây Hoa Bắc đặc sản hồng cao lương làm nguyên liệu, dùng tiểu mạch chế khúc, đạo da chỉ phó nguyên liệu, áp dụng cực nóng chế khúc, quay về phôi lên men, từng nhóm chưng đốt nhưỡng chế ra, có rảnh ta cũng chính mình học một ít ủ, sau đó bán cho khách nhân, nhìn xem hưởng ứng như thế nào.",
	"4015"  : "Yên tĩnh nhét cắt giấy, hoa thơm cỏ lạ mẫu thân. Tộc người chi hồn, Ngụy Quốc có thể tìm ra. Đây là đối cắt giấy đánh giá, ta có không cũng phải đi học học, không vì cái gì khác, bởi vì trang sức hạ ta đây khách sạn cửa sổ, dọn dẹp được thoải mái khách nhân tự nhiên sẽ thêm.",
	"4016"  : "Rượu Phần, nghe nói qua đi, khẳng định không uống qua! Đây chính là phi thường quý báu, người bình thường uống không hơn. Gần nhất bổn điếm tới một đám hàng, trong đó còn có hai hang rượu Phần, ta chuẩn bị lưu trữ bán cho trở ra lên giá tiền người, coi như là tiểu kiếm một số.",
	"5015"  : "Chúng ta đất này trẻ người nha, đặc xoi xét, phải làm hảo rượu này điếm sinh ý rất không cho phép dễ dàng nha, ta phải muốn tốt hơn giọt hấp dẫn bọn hắn, ách, có thể được chuẩn bị đó đặc sắc đồ ăn, các nơi đặc sản linh tinh, như vậy mới có mánh lới nha!",
	"5016"  : "Hôm qua Thiên phu nhân đặc chế một cái hương bao, dặn dò ta nhất định phải đeo, kỳ thật không cần nàng dặn dò, ta cũng sẽ đeo ở trên người, mỗi ngày ở bên ngoài vội vàng sinh ý, nhìn thấy nhang này bao, liền nhớ lại phu nhân, đi theo ta ăn không ít khổ a.",
	"6015"  : "Nghe nói chúng ta Sở quốc Trương Nghi là một cơ trí người, hắn đang Sở Vương bên người vì nó bày mưu tính kế, lời nói sắc bén nhạy cảm duệ, ta nghe nói một ít sự tích của hắn sau, chính là rất bội phục hắn, chỉ hy vọng có một ngày có thể tại...này tự tửu điếm nhỏ chiêu đãi hắn, ta cũng thoả mãn.",
	"6016"  : "Chúng ta Sở quốc ranh giới diện tích, đặc sản dồi dào, nhân tài tập trung, đặc biệt 'Bao mao' vốn là sở 'Kinh sơn' chi đặc sản, tiểu điếm may mắn được đến mấy hồ, có thể nói là quý trọng lại quý trọng a.",
	"7015"  : "Không cần coi khinh ta đây gia khách sạn, phàm là đi vào ta Yến quốc khách nhân, đều cũng đến ta đây trẻ nghỉ chân một chút đâu! Việc buôn bán của ta được không, có rảnh đừng quên đến ta đây ngồi một chút.",

	"7016"  : "Mặt trời lặn phía tây, trời chiều vô hạn hảo. Lại qua một ngày, lui tới, rất nhiều người xuất môn, cũng có rất nhiều người trở về, mặc kệ xuất môn thời gian có bao nhiêu lâu, khoảng cách có xa lắm không, chung quy đều là muốn trở về, xem như mệt mỏi điểu về đi.",

	"8015"  : "Vị khách quan kia, nhìn ngươi cảnh tượng vội vàng bộ dạng, ngươi là ra ngoài làm việc đi, đường xá xa xôi, không bằng ở ta đây mua nhiều điểm lương khô mang theo, để tránh trên đường đói khát mà khuyết thiếu đỡ đói thực vật!",

	"8016"  : "Từ mở này gian khách sạn, mỗi ngày có vô số người ở ta đây ăn cơm uống rượu nói chuyện phiếm, trong lòng cố gắng hâm mộ, khi nào thì ta cũng có thể nghỉ ngơi thật tốt, tận tình hưởng thụ một chút người khác phục vụ.",
	 	 
	"1088"  : "Nhà của ta đời đời đều là thương nhân, hiện tại làm thương nhân có thể ăn thơm, đã có thể chính mình kiếm chút đỉnh tiền đến dưỡng gia hồ khẩu, còn có thể vì quốc gia làm cống hiến bắt được chia hoa hồng, cớ sao mà không làm đâu!",
	"2088"  : "Gần nhất qua Ngụy Quốc đi Tề quốc phiến đó hoa quả khô trở về bán, cái gì hoa quả khô đây? Tề quốc sản xuất nhiều đại tảo, nơi đó khí hậu tương đối so sánh khô ráo, cho nên thực thích hợp sinh trưởng này đó bụi cây loại thực vật, ta lần này phiến rất nhiều trở về, hy vọng có thể kiếm lớn một số.",
	"3088"  : "Gần nhất sinh ý không tốt làm a! Chiến tranh liên miên không ngừng, ta đều không dám tùy tiện đi ra ngoài buôn bán, hay là đang nước nhà nội làm điểm tiểu vốn mua bán, trước tiên đem trong khoảng thời gian này sống quá đi làm tiếp sau khi tính toán đi!",
	"4088"  : "Không biết ai quy định, quốc gia từ trước đến nay đều không coi trọng thương nhân địa vị, mặc kệ Chu thiên tử, vẫn là chư hầu vương đô áp dụng 'Nặng nông nén xuống thương' chính sách, ta sẽ nghĩ mãi mà không rõ, không có chúng ta thương nhân gánh vác đại lượng thuế má, này đó đế vương dựa vào cái gì đến duy trì quốc gia.",
	"5088"  : "Nếu Đại vương có thể đem ranh giới khuếch trương lớn chút nữa, đồ đạc của ta là có thể bán cho càng nhiều là người, hắc hắc... Muốn là nghĩ như vậy, nhưng là phải đem sinh ý làm tốt, vẫn là được dựa vào cố gắng của mình nha.",
	"6088"  : "Ta tính toán đem việc làm ăn của mình phạm vi cùng quy mô mở rộng, luôn làm loại này tiểu vốn sinh ý, sau khi rất khó có lớn hơn nữa phát triển tiền đồ, nếu muốn đề cao địa vị của mình cùng danh dự, nhất định làm được phú khả địch quốc.",
	"7088"  : "Buôn bán khó khăn a, mỗi ngày đi sớm về tối, vất vả. Qua một thời gian ngắn phiến điểm hạt dẻ, sơn tra, cây nho mấy thứ này tiền lời, nhìn xem nguồn tiêu thụ thế nào, nghe người ta nói quốc gia khác đối với chúng ta Yến quốc này đó đặc sản thực cảm thấy hứng thú nha.",

]);

// 国家通用对话
mapping CountryWordTable = ([
	"1001"  : "Lần trước Bổn Vương tin lầm sứ Tần Trương nghi, hại bổn vương không liên minh được với Triệu, hiện nay Triệu đã bị Tần đánh bại đành xưng thần. mục tiêu kế đến của Tần có thể là bổn vương, phải làm thế nào đây!",
	"2001"  : "Bọn ngươi tìm bổn vương có chuyện gì? Nếu không đại sự vả lại chớ phiền nhiễu bổn vương, không cảm thấy hiện giờ Thất Hùng cùng tồn tại kết quả mặt? Bổn vương mỗi ngày có rất nhiều sự phải xử lý, hơn nữa mọi chuyện đều được thâm lo, nghĩ lại mà làm sau!",
	"3001"  : "Chúng ái khanh có thể tận lực vì nước nhà, làm tốt chức trách của mình, bổn vương cảm thấy rất vui! Nếu cứ tiếp tục phát triển ưu thế như thế thì việc dân giàu nước mạnh chỉ là chuyện sớm muộn, không lâu sau xem ai còn dám bắt nạp Bổn Vương yếm thế.",
	"4001"  : "Quanh thân chư hầu như lang như hổ, này dã tâm mọi người đều biết, mặt ngoài không tranh sự đời, âm thầm cùng ở chiêu binh mãi mã, súc tích lực lượng, bổn vương có thể phải đề phòng, bằng không sẽ hối hận không kịp.",
	"5001"  : "Bổn vương sở hạt nơi có thể cường đại như thế, may mắn được thương thầy thuốc thực hiện tân pháp lệnh, cách rụng rất nhiều bất lợi với lớn mạnh chi tai hại. Như thế phát triển, tiêu diệt còn lại lục lộ chư hầu tất sắp tới!",
	"6001"  : "Khuất thầy thuốc vốn là nước nhà lương phụ chi tài, bổn vương thật là tin hắn, hiện giờ quyết định, bái khuất thầy thuốc làm đầu khanh, toàn bộ đề cập nội chính ngoại giao việc, toàn bộ giao phó cho khuất ái khanh thống trị.",
	"7001"  : "Đông chư hầu trung, bổn vương thực lực nhỏ nhất, cho nên tu muốn nhất sách lược vẹn toàn ở quanh thân cường quyền bên trong giữ tròn xuống dưới. Tần vốn là hổ lang chi bang, không thể tin, chỉ có liên minh mặt khác chư hầu đến cộng đồng chống cố chấp Tần.",
	"8001"  : "Thế đạo biến hóa, bổn vương phong hạ các chư hầu lại một vốn một lời Vương bỏ mặc, hiện giờ bổn vương ban bố pháp lệnh ở các chư hầu hạt ấp nội không hề uy tín đáng nói, Đại Chu ở bổn vương tay thành như thế hiện trạng, thật là hổ thẹn!",

	"1002"  : "Thân là Đại tướng quân, tay cầm triều đình binh quyền, chịu triều đình tín nhiệm, bị trao tặng quan to lộc hậu, Bổn tướng quân sẽ đến chết không đổi hiệu trung với Đại vương, thời khắc nghe theo Đại vương điều khiển, dùng cái này để báo đáp Đại vương ơn tri ngộ.",
	"2002"  : "Chiến trường cát điểm binh, da ngựa bọc thây còn, tức giận cái gì thế Bổn tướng quân chưa thấy qua, nhớ năm đó bản tướng suất lĩnh thiên quân vạn mã, rong ruổi chiến trường, vung đao cho mười bước trong vòng thủ địch đứng đầu cấp, uy chấn quần hùng, có từng gặp qua.",
	"3002"  : "Phong vân thời khắc biến ảo, xem loại này tình thế, chiến tranh không thể tránh né, chúng tướng nghe lệnh, kể từ hôm nay, cần tăng cường đề phòng, như có cải lệnh tự tiện tạm rời cương vị công tác người, định trảm không buông tha.",
	"4002"  : "Chỉ cần Đại vương ra lệnh một tiếng, bản tướng đem không thể chối từ xông pha chiến đấu, gương cho binh sĩ, lấy cái chết đền đáp Đại vương, định chém tới phạm chi địch, quyết không lùi bước, lấy lộ  bản tướng lòng son dạ sắt.",
	"5002"  : "Bổn tướng quân hiện đã làm tốt hết thảy sắp xếp, lương thảo ngựa cùng đã chuẩn bị thoả đáng, tùy thời có thể chờ đợi Đại vương điều khiển. Nếu lệnh vua hạ xuống, Bổn tướng quân ổn thoả toàn lực ứng phó trợ Đại vương thực hiện sự thống trị.",
	"6002"  : "Trấn thủ biên ải, bảo vệ quốc gia, là làm thần tử ứng hết gốc rể phân, ngươi không cần khích lệ, Đại vương tin cậy, dân chúng kính yêu, khiến bản tướng càng thêm cảm thấy trách nhiệm trọng đại, bản tướng nhất định sẽ khác làm hết phận sự thủ.",
	"7002"  : "Bản tướng gần nhất ở nghiên tập binh pháp, bởi vì thực lực đối với mặt khác chư hầu yếu kém, cho nên dụng binh cần ở chỗ tinh, làm được thắng vì đánh bất ngờ, bằng thiếu binh lực thắng thủ lớn nhất thắng lợi, bảo đảm chắc chắn nước nhà an bình.",

	"1003"  : "Nước nhà chính trị trong sáng, Đại vương cổ vũ dân chúng tự chủ chọn nghiệp, thế cho nên nước nhà tài chính thu vào sung túc, gần đây Đại vương cố ý thêm gẩy ngân lượng gia cố Trường Thành, mở rộng quân đội, dùng cái này đến lớn mạnh nước nhà lực lượng quân sự.",
	"2003"  : "Gần đây tài chính thu vào tương đối giảm bớt, hiện đã nhập bất phu xuất, loại này trạng huống là mấy năm gần đây chinh chiến sẽ tạo thành, chiếu này phát triển thêm nữa, nước nhà đem không chịu nổi gánh nặng, dân chúng cũng sẽ sống lang thang.",
	"3003"  : "Bổn quan gần nhất rất là buồn rầu, Đại vương dục sửa chữa và chế tạo cung điện, chi quá nhiều, hiện giờ nước nhà ở nông nghiệp, quân sự cần dùng gấp tiền, không biết ai muốn đi khuyên giản một chút Đại vương, không cần làm như thế hao tài tốn của cử chỉ.",
	"4003"  : "Đối với nước nhà tài chính thuế má, thu vào chi Bổn quan nhất thanh nhị sở, không tin ngươi có thể thi Bổn quan. Ha ha... Tin chưa ~! Ta làm tài chính quan đã có hơn hai mươi năm, có thể nói phải nhìn rõ mọi việc.",
	"5003"  : "Bởi vì thương thầy thuốc biến cách, cách rụng nước nhà dĩ vãng bất lợi phương pháp lệnh, khiến cho nước nhà kinh tế trạng huống có rõ ràng thay đổi, tài chính thu vào có vẻ theo đề cao, Đại vương rất là cao hứng, bởi vì Đại vương gần nhất định dùng binh.",
	"6003"  : "Ngân khố quốc gia tràn đầy là quốc gia cường, bách tính an cư lạc nghiệp chi bảo đảm, nếu như không đủ đủ chi tồn tại ngân, ở phát sinh chiến sự cùng thiên tai là lúc, liền gặp rất khó ứng phó, hậu quả đem khó lường.",
	"7003"  : "Nước nhà tài chính thu vào ổn định, ngoài ra Đại vương Vô Ý cùng quần hùng tranh giành, cho nên sẽ không tiêu phí đại lượng tiền vốn, nhân lực, vật lực đi tiến hành quân sự chuẩn bị, nhưng vì cầu tự bảo vệ mình, Bổn quan mong rằng Đại vương tiến hành cần phải chuẩn bị.",

	"1004"  : "Nước nhà nội chính hoa văn rõ ràng, này dựa vào Đại vương dùng người thích đáng, thưởng phạt phân minh, khiến cho vua tôi đồng tâm, lại trị trong sáng, đủ loại quan lại đều có thể làm hết phận sự hết thủ, như thế đi xuống, nước nhà định có thể xưng bá quần hùng.",
	"2004"  : "Tục ngữ nói: 'Quan thanh liêm khó khăn đoạn việc nhà', nội chính không phải là Đại vương việc nhà sao? Có một số việc Bổn quan sao dám tự tiện làm chủ? Thật đúng là nhường Bổn quan buồn rầu, hơi có sơ xuất, Đại vương liền gặp giáng tội.",
	"3004"  : "Gần đây việc chính trị phồn đa, Bổn quan đã muốn rất khó ứng phó lại đây, bọn ngươi nếu vì một ít sự cũng đừng có đến làm phiền Bổn quan, trực tiếp đi tìm nên cấp dưới quan chức đi xử lý, bọn hắn chắc chắn theo lẽ công bằng công việc.",
	"4004"  : "Nội chính đại sự, nhàn tạp nhân đẳng thỉnh chớ chê trách, chê trách triều chính vốn là phạm pháp cử chỉ, bọn ngươi có thể nhớ lao? Mỗi tiếng nói cử động cùng cần thận trọng, miễn cho đưa tới lao ngục tai ương rồi sau đó hối hận không kịp.",
	"5004"  : "Đại vương tôn trọng pháp gia tư tưởng, lấy nghiêm khắc luật hình đến thống trị quốc gia, lúc này loại dưới chế độ, không có ai dám tai nạn và rắc rối triều chính, cho nên Bổn quan ở thống trị nội chính thượng cũng có vẻ phi thường thuận buồm xuôi gió.",
	"6004"  : "Nội chính tuy rằng rườm rà, nhưng Bổn quan nhất nhất định sẽ tận dụng hết khả năng đem nội chính thống trị ngay ngắn trật tự, nhường nước nhà các bộ hợp lý nhịp nhàng vận chuyển, dùng cái này đến đề cao nước nhà quan chức năng lực làm việc.",
	"7004"  : "Bổn quan từng mặc cho qua nội vụ phủ y, đối nội chính sự nghi có chút quen thuộc. Hiện giờ Đại vương mạng ta tiếp nhận chức vụ nội chính quan chức, chính hợp ý ta, Bổn quan định vì triều đình cúc cung tận tụy, chết rồi sau đó đã.",

	"1005"  : "Gần đây muốn làm một cuộc thanh tra nhân hộ cho bổn quốc, tra xem bổn quốc có bao nhiêu hộ dân, thuận tiện phân chia loại hình mà bá tánh làm ghi chép rõ ràng, tiện cho việc chế định pháp lệnh sẽ có căn cứ hợp lý.",
	"2005"  : "Chẳng lẽ ngươi không phát giác gần nhất người lớn lại tăng thêm rất nhiều, còn đây là quốc gia yên ổn, dân chúng lạc nghiệp chi kết quả, vẫn là thái bình thịnh thế tốt! Người lớn thịnh vượng, quốc gia phồn vinh hưng thịnh, ha ha!",
	"3005"  : "Gần nhất dân chúng di chuyển quy mô khá lớn, từ đó làm cho hộ tịch quản lý hỗn loạn, việc này nhường Bổn quan đau đầu, Bổn quan được mau chóng xử lý tốt, nếu không Đại vương trách móc xuống dưới, Bổn quan có thể ăn tiêu không được.",
	"4005"  : "Gần nhất phát giác nước nhà người bên ngoài hộ càng ngày càng nhiều, còn đây là chuyện tốt, thuyết minh nước nhà chính trị trong sáng, nhưng cần hảo hảo tiến hành thống trị, bằng không sẽ cho nước nhà các nghành thống trị tạo thành rất nặng gánh nặng.",
	"5005"  : "Đại vương cổ vũ dân chúng sinh con trai nhập hộ, bởi vì người lớn là nguồn mộ lính chi cam đoan, như thế loạn thế, dụng binh đánh giặc là chuyện thường, vô luận tại chiến khi hoặc chiến hậu, nguồn mộ lính nhất định có sung túc bảo đảm, cho nên Bổn quan ở dân cư quản lý thượng chế định rất nhiều thưởng cho biện pháp.",
	"6005"  : "Hộ tịch quản lý việc, quan hệ đến nước nhà chính cơ có không ổn định, Đại vương từ trước đến nay coi trọng này sở hạt nơi hộ tịch trạng huống. Cho nên Bổn quan đem đem hết toàn lực làm tốt thuộc bổn phận việc.",
	"7005"  : "Gia nhập nước nhà hộ tịch, tất tới trước Bổn quan nơi này công việc nên thủ tục, bởi vì Bổn quan chưởng quản nước nhà dân chúng hộ tịch rót vào cùng tiêu trừ. Bọn ngươi là tới nước nhà nhập hộ sao?",

	"1006"  : "Ngươi có cái gì tham quan tội thần manh mối sao? Nếu có chút liền thượng tấu triều đình, nếu cảm thấy được không tiện, xin mời trần thuật cấp Bổn quan, do Bổn quan thay ngươi tấu minh Đại vương đối tham quan tội thần tiến hành trừng trị, quyết sẽ không có cá lọt lưới.",
	"2006"  : "Gần nhất làm tra một món đồ bàn dài lại phải tội rất nhiều người, Ngự Sử không tốt làm a! Có đôi khi bàn dài tra xuống dưới, tra được chính mình thân thích hoặc là bằng hữu, muốn làm việc thiên tư nhưng lại sợ chấp pháp phạm pháp bị người phát hiện, thật không biết nên làm thế nào cho phải.",
	"3006"  : "Muốn hối lộ Bổn quan, khuyên ngươi không cần có này ý tưởng, nếu không vốn Ngự Sử sẽ ngay cả ngươi cùng nhau thượng tấu, nếu ngươi thực phạm phải tội gì đi tối hảo chính mình chủ động đi tìm Đại vương xin được trị tội, có lẽ Đại vương sẽ ngoài định mức khai ân.",
	"4006"  : "Làm quan chi đạo ở chỗ làm dân, tục ngữ nói: làm quan không vì dân làm chủ, không bằng về nhà bán khoai lang. Bổn quan chắc chắn thể nghiệm và quan sát dân tình, thay dân giải oan, giám sát quan chức hành động, quét sạch nước nhà lại trị.",
	"5006"  : "Ở nước nhà, Đại vương phi thường coi trọng Bổn quan, bởi vì Bổn quan chưởng quản định tội phương pháp lệnh căn cứ cùng thước đo, gì phạm quan đều tất trước đi qua Bổn quan tiến hành thẩm tra xử lí, lúc sau lại vừa tấu minh Đại vương định tội.",
	"6006"  : "Giám sát đủ loại quan lại vốn là Bổn quan chức trách chỗ, buộc tội tham quan tội thần ô lại định sẽ không nương tay, ngươi nếu biết đầu mối gì thỉnh nói cho Bổn quan, Bổn quan chắc chắn theo lẽ công bằng công việc, trị này nên hình phạt, quyết sẽ không xuất hiện cá lọt lưới.",
	"7006"  : "Nước nhà lại trị coi như so sánh trong sáng, chính là ngẫu nhiên ra một ít tham quan, khắp cả quốc gia mà nói cũng không lo ngại, nhưng Bổn quan cũng sẽ không thả lỏng đối đủ loại quan lại giám sát, cần đề phòng cẩn thận, tục ngữ nói: ngàn dậm chi đê, vỡ cho ổ kiến.",

	"1007"  : "Bổn quan lần này đi sứ Triệu, định muốn thuyết phục Triệu vương cùng nước nhà kết minh, bằng không phòng ngự Tần liền có vẻ thực gian nan, ở Triệu vương trước mặt cần bỏ qua này ở giữa lợi và hại quan hệ, tin tưởng bằng bản sứ tam tấc không nát miệng lưỡi, định có thể thuyết phục cho hắn.",
	"2007"  : "Tần đã sớm một vốn một lời quốc nhất tòa thành trì thùy tiên tam xích (thèm thuồng), Đại vương muốn cho ty chức thuyết phục Tề cùng nước nhà kết minh, cấu trúc một cái quân sự phòng tuyến, dùng cái này đến ngăn chặn Tần dã tâm, tránh nước nhà xuất hiện bị gồm thâu tình cảnh.",
	"3007"  : "Đại vương lại tán thưởng ta, nói vi thần đi sứ thực thành công, bởi vì Bổn quan thành công thuyết phục Ngụy cự tuyệt đáp ứng Tần xuất binh mượn đường yêu cầu, bởi vậy Tần cũng không dám xằng bậy, làm gốc quốc chuẩn bị chiến tranh tranh thủ đến thời gian.",
	"4007"  : "Một vốn một lời quan mà nói đi sứ nước ngoài có ích rất nhiều, đã hoàn thành Đại vương phó thác sứ mệnh, tăng tiến hai nước hữu nghị, Bổn quan cũng nhận thức kết giao rất nhiều bằng hữu. Có thể nói là vừa mới nhị được a! Ha ha. . .",
	"5007"  : "Đại vương muốn nhất thống thiên hạ, nhưng này lục liên minh quốc tế tung, như thế liền gây trở ngại thống nhất nghiệp lớn, Đại vương nhường vi thần tìm đi phá hư lục liên minh quốc tế tung, việc này mặc dù không dễ làm, nhưng bản sứ sẽ có biện pháp hoàn thành Đại vương sứ mệnh.",
	"6007"  : "Đi sứ nước ngoài, thân thiện hữu hảo hai nước quan hệ, việc này rất trọng yếu, bởi vì ở tình thế nguy cấp là lúc, có thể thỉnh cầu liên bang trợ giúp nước nhà, coi như không viện trợ ít nhất sẽ không uy hiếp nước nhà, còn đây là bố trí bản sứ chi nguyên nhân.",
	"7007"  : "Đại vương viết một lá thư, mạng trời ạ đêm đi gấp giao cho hắn làm Triệu vương. Chắc là quan hệ quốc gia an nguy việc, bản sứ không dám lãnh đạm. Bọn ngươi nếu có chút sự, ngày sau bàn lại, hoàn vọng kiến lượng.",
	
	"1008"  : "Giết người thì thường mạng, phạm tội đền tội, việc này không có gì thương lượng đường sống, ngươi nếu là mạo phạm nước nhà luật hình, Bổn quan định sẽ không pháp ngoại lưu tình, mong ngươi không cần phạm pháp, Bổn quan trước cảnh cáo ở phía trước.",
	"2008"  : "Ngục giam bỏ tù người càng ngày càng ít, nói không chừng khi nào ngục giam thật không có người bỏ tù, như thế nhường Bổn quan quên chức quy ẩn cũng cam tâm tình nguyện, bởi vì nước nhà yên ổn đoàn kết, nơi nơi dào dạt một mảnh tường hòa bầu không khí.",
	"3008"  : "Ngươi nếu phạm pháp bị bắt, nhưng đừng hướng Bổn quan cầu tình, Bổn quan chỉ phụ trách bỏ tù phạm nhân. Xử trí như thế nào, cũng không phải là Bổn quan có khả năng định đoạt, thanh giả tự thanh, trọc lên từ trọc, Bổn quan chỉ có thể như thế công đạo.",
	"4008"  : "Ngươi nếu phạm pháp vào tù, muốn an tâm bị tù, hảo hảo tư qua, không cần có dù may mắn ý tưởng, thậm chí muốn vượt ngục trốn đi, còn đây là chỉ biết tăng thêm hình phạt, ngươi định sẽ hối hận không kịp.",
	"5008"  : "Nước nhà luật hình vốn là Đại vương sở định, Đại vương tôn trọng pháp gia, chủ trương theo nếp trị quốc, cho nên nước nhà luật hình tương đương nghiêm khắc, hi vọng bọn ngươi không cần lấy thân thử nghiệm, cần tự trọng nga!",
	"6008"  : "Thiên tử phạm pháp cùng thứ dân cùng tội, bộ luật vô tình, hi vọng ngươi có thể tự giác thủ pháp, không cần lấy thân thử nghiệm tới khiêu chiến pháp lệnh quyền uy, không tin Bổn quan, cuối cùng chịu khổ bị giày vò chắc chắn là ngươi.",
	"7008"  : "Nước nhà pháp lệnh điều mục tuy ít, nhưng chấp hành phi thường nghiêm minh, đối với tai nạn và rắc rối triều cương, nguy hại dân chúng người quyết không nương tay, hi vọng bọn ngươi tự hạn chế, không cần làm loạn kỷ trái pháp luật việc.",

	"1010"  : "Đến nước nhà có gì muốn làm? Là tới buôn bán vẫn là đến dò hỏi tình báo, khuyên ngươi tốt nhất làm bổn phận người, nếu ở nước nhà xằng bậy, ta nhưng cần đuổi đi ngươi xuất ngoại, không chỉ nói ta không cảnh cáo ngươi.",
	"2010"  : "Qua lại người cùng vật chờ giống nhau cần nhận kiểm tra, lại vừa tiến ra khỏi cửa thành, hi vọng mọi người tự giác phối hợp vốn thủ vệ lệ hành kiểm tra! Như có tự tiện xông vào môn người, làm theo như nước nhà luật hình tăng thêm trừng phạt, hi vọng ngươi tự thu xếp ổn thoả.",
	"3010"  : "Nếu không lệnh bài, không lịch sự đặc biệt cho phép, tự tiện xông vào cửa thành người, quất roi ba trăm, còn đây là Đại vương tân định ra pháp lệnh, mong mọi người tự hạn chế, như thế cũng là làm minh đang pháp lệnh, giữ gìn Đại vương quyền uy.",
	"4010"  : "Mặc kệ gió thổi mưa lâm ngày sái, khí hậu như thế nào tồi tệ, ta lúc này môn thủ vệ chưa từng câu oán hận, chưa từng tự tiện rời đi qua cương vị, còn đây là ta chức trách chỗ, ta chắc chắn kiên trì tới cùng.",
	"5010"  : "Không cần cho rằng ta là một thủ môn tiểu tốt, liền không hề chí hướng, ta mộng muốn trở thành một gã tướng quân, bởi vậy, tất trước làm tốt thuộc bổn phận việc, như thế tương lai mới có thể gánh vác trọng trách.",
	"6010"  : "Bảo vệ tốt cửa thành, đứng vững tiếu đồi là bản nhân phân nội việc, thỉnh không cần cảm thấy được ta vất vả, lấy triều đình bổng lộc, sẽ vì triều đình làm hảo kém, bảo nhất phương bình an. Như thế mới không phụ triều đình cùng dân chúng sở mong.",
	"7010"  : "Hoan nghênh ngươi tới đến nước nhà, chỉ cần ngươi không làm phạm pháp việc, nước nhà nhân dân chắc chắn bạn thân đối đãi ngươi, nếu của ngươi hành động không hợp với nước nhà ích lợi, xin hãy hi vọng nhanh chóng rời đi.",
	
	"1011"  : "Đứng ở chỗ này thủ, ta là rất có ý tưởng, bản nhân chưa thụ tinh một thân khát vọng, lại chỉ tài năng ở này làm một thủ môn tiểu binh, thật sự là có tài nhưng không gặp thời a! Hy vọng có thể gặp được có biết chi sĩ, đem ta trêu chọc đi.",
	"2011"  : "Ta lúc này môn đã thủ vệ tám năm có thừa, hi vọng triều đình có thể chú ý tới ta, đem ta trọng dụng, chẳng lẽ ta không đủ xứng chức? Còn hơn tướng quân ta làm dễ dàng sẽ thiếu? Xem ra đều là thân phận nguyên nhân.",
	"3011"  : "Nếu ngươi có quý trọng vật phẩm, hi vọng không cần mang ở trên người, để tránh xuất hiện sơ xuất. Trải qua bản nhân nhiều năm thủ vệ lịch duyệt, đã muốn tận mắt nhìn thấy rất nhiều việc này, mong ngươi vẫn là cẩn thận cho thỏa đáng.",
	"4011"  : "Nhìn ngươi ở cửa thành ngoại bồi hồi không chừng, hay không gặp gỡ phiền toái gì, nếu có người khi dễ ngươi, ta chắc chắn thay ngươi làm chủ, đừng nhìn ta chỉ là một thủ vệ tiểu tốt, gặp gỡ loại này sự định sẽ không bỏ mặc.",
	"5011"  : "Không cần cho rằng ta là một thủ môn tiểu tốt, liền không hề chí hướng, ta mộng muốn trở thành một gã tướng quân. Bởi vậy, tất trước làm tốt thuộc bổn phận việc, như thế tương lai mới có thể gánh vác trọng trách.",
	"6011"  : "Phàm Tần quốc dân chúng, thương nhân vào thành, không được vượt qua bốn canh giờ, còn đây là Đại vương tân lệnh. Nếu có chút lừa gạt người, làm theo như gian tế chi tội trừng phạt, đến nỗi nguyên nhân không thể trả lời.",
	"7011"  : "Tuần trong thành quân đã đồng ý ta, chỉ cần tiếp tục thủ vệ nơi đây một năm không xuất sai lầm. Hắn đem tấu minh Đại vương, thăng nhiệm ta làm cửa thành vệ trưởng, ta tin tưởng tuần trong thành quân sẽ không gạt ta.",
	"8011"  : "Dưới chân thiên tử, không được làm ẩu, còn đây là trọng địa, mỗi tiếng nói cử động, đều phải chú ý, miễn cho rước lấy tội họa trên người, đến lúc đó không chỉ nói bản nhân không để cho ngươi tình cảm, hi vọng ngươi tự thu xếp ổn thoả.",

	"1012"  : "Ngươi là tiến đến nước nhà du ngoạn? Này cũng không hay lo liệu, bổn thành phạm vi to lớn như thế, ngươi mạo muội vào thành sẽ thực dễ dàng bị lạc phương hướng, bất quá ngươi sau khi đi vào tốt nhất hỏi nhiều hỏi trong thành dân chúng, bọn hắn sẽ trợ giúp ngươi.",
	"2012"  : "Ta ở trong này thủ vệ nhiều năm, đối với nước nhà một ít sản vật vẫn là hiểu biết một ít, nói thí dụ như: Hỏa Long quả, còn có dược liệu cỏ linh chi, này đó ở nước nhà đều là thực phụ nổi danh.",
	"3012"  : "Gần nhất trong thành đã xuất thần trộm, rất nhiều nhà giàu tài vật đều bị cướp sạch không còn, loại tình huống này đã muốn liên tục thời gian rất lâu, tuần thành quan rất là căm tức, đem khí  đều rơi tại trên người của ta, nói ta không thấy hảo cửa thành.",
	"4012"  : "Đứng nhiều năm như vậy đồi, ta đã luyện nhìn thoáng một cái đều có thể phân rõ ai là người tốt ai là người xấu bản lĩnh, làm sao vậy? Ngươi không tin, ngươi có thể đi hỏi một chút bên cạnh ta huynh đệ.",
	"5012"  : "Mới vừa nhận được tin tức, có một hải tặc vượt ngục chạy trốn, tuần thành quan ra lệnh, phàm ra khỏi cửa thành người, chính là đi theo vật phẩm, giống nhau cần nhận kiểm tra, quyết không thể nhường cái kia đạo tặc đào thoát rụng.",
	"6012"  : "Ta vừa rồi nghe một đám tiến ra khỏi cửa thành thương nhân nói 'Nước nhà hạt sen khi hắn quốc giá bán rất cao.' năm nay nước nhà hạt sen mùa thu hoạch, ngươi có nghĩ tới hay không đi phiến một ít hạt sen đi quanh thân quốc gia đi bán đây?",
	"7012"  : "Nếm qua nước nhà vịt quay không có? Kia hương vị thật đúng là đẹp, tuy rằng ta chỉ là một thủ vệ binh, nhưng mỗi khi lĩnh bổng lộc là lúc, ta đều cũng mời bằng hữu đi ăn một hồi, ha ha...",

	"1013"  : "Nước nhà phòng giữ chế độ thật là hoàn thiện, mỗi ngày trao đổi ba lượt cương vị, trao đổi thời gian không chừng, nhân viên cũng không định, cho nên hữu hiệu chặn đứng này đó ý đồ thừa dịp chúng ta đổi đồi khi chạy trốn đắc tội phạm.",
	"2013"  : "Ta lúc này môn đã thủ vệ tám năm có thừa, hi vọng triều đình có thể chú ý tới ta, đem ta trọng dụng, chẳng lẽ ta không đủ xứng chức? Còn hơn tướng quân ta làm dễ dàng sẽ thiếu? Xem ra đều là thân phận nguyên nhân.",
	"3013"  : "Đến nước nhà du ngoạn làm việc nhất định phải mua đó bản địa đặc sản, tỷ như cây tần bì gai Trung Quốc, cao lương vân vân, còn có một chút hàng mỹ nghệ: giống chạm ngọc linh tinh ở địa phương khác đều là thực nổi danh.",
	"4013"  : "Ta cho năm trước hưởng ứng lệnh triệu tập nhập ngũ, vốn định rong ruổi sa trường, giết địch đền nợ nước, kết quả lại được an bài không sai làm một cái thủ vệ tiểu binh, thật sự là cảm thấy thất vọng, không biết còn có hay không cơ hội ra chiến trường.",
	"5013"  : "Ta cảm thấy được đứng ở chỗ này đồi không riêng gì vì Đại vương thống trị ổn định, càng là vì gia nhân của ta cùng nước nhà dân chúng có thể vượt qua yên ổn hài hoà cuộc sống. Ngươi cho rằng ý nghĩ của ta đúng không?",
	"6013"  : "Bảo vệ tốt cửa thành, đứng vững tiếu đồi là ta phân nội việc, thỉnh không cần cảm thấy được ta vất vả, lấy triều đình bổng lộc, muốn làm hảo triều đình kém, bảo nhất phương bình an, như vậy mới không phụ dân chúng sở mong.",
	"7013"  : "Chúng ta Đại vương rất là bảo vệ dân chúng, đây là ta ở trong này trông nhiều năm như vậy đồi vệ, qua lại người đi đường sở phản ánh, bọn hắn đều nói chúng ta Đại vương là một minh quân, sở chọn dùng chính sách đều là làm dân chúng lo lắng.",
	"8013"  : "Ta gần nhất giam Hàn Quốc thương nhân một đám ra khỏi thành nhân sâm, bọn hắn không có trải qua nước nhà phê chuẩn, tự tiện buôn quý trọng thuốc. Nếu ngươi tới nước nhà buôn vật phẩm tốt nhất trước hiểu biết nước nhà pháp lệnh chế độ.",
	
	"1014"  : "Ta muốn theo thấp nhất chức vụ làm lên, ta muốn thực hiện tướng quân của ta mộng, tục ngữ nói: không muốn làm tướng quân binh không phải hảo binh, ta chắc chắn bảo vệ tốt mỗi một ban cương vị, là thật hiện tướng quân của ta mộng chuẩn bị sẵn sàng.",
	"2014"  : "Không cần cho rằng ta bất hạnh, kỳ thật làm một cái thủ vệ tiểu binh cũng là có bản chức nhiệm vụ cần hoàn thành, ta sẽ đứng vững mỗi một ban cương vị, tận lực làm rất tốt, sẽ không để cho dân chúng thất vọng.",
	"3014"  : "Ở trong này thủ cửa thành có thể lao đến không ít ưu đãi nga! Nói thí dụ như: có thương nhân muốn tư vận văn bản rõ ràng cấm hàng hóa ra khỏi thành, này thương nhân nhất định phải cho ta rất nhiều chỗ tốt, ta mới chịu đáp ứng bọn hắn.",
	"4014"  : "Buổi tối muốn tiến ra khỏi cửa thành, nhất định giữ tuần thành quan phóng ra đặc biệt giấy thông hành, nếu ngươi không đúng sự thật, hãy cứ mời trở về, đợi cho sáng ngày thứ hai mở thành là lúc lại đến.",
	"5014"  : "Xem ta như vậy phụ trách thủ cửa thành, ngươi có phải hay không cảm thấy được có một loại cảm giác an toàn đây? Làm hết phận sự hết thủ đó là ta thuộc bổn phận việc, các ngươi xuất nhập bình an mới nói minh trách nhiệm của ta tận tâm tận lực.",
	"6014"  : "Ngày hôm qua Tần quốc hướng nước tôi mượn đường xuất binh, ta làm sao biết? Ngày hôm qua chính là ta ở đồi thì nhận được mặt trên mệnh lệnh, cấp Tần binh vào thành cho đi, ta nhưng thực làm Đại vương thực hiện lo lắng a!",
	"7014"  : "Thủ cửa thành, thực nhàm chán, mỗi ngày đứng ở chỗ này, muốn liberdade hoạt động một chút cũng không thành, thường thường còn phải bị thủ trưởng quở mắng một trận, không phải nói quân ta dung bất chính, nói đúng là ta quần áo không ngay ngắn.",

	"1015"  : "Đến nước nhà là làm chuyện gì? Là tới buôn bán vẫn là đến dò hỏi tình báo? Khuyên ngươi tốt nhất làm bổn phận người, nếu ở nước nhà làm ẩu, ta nhưng cần đuổi đi ngươi ra nước nhà.",
	"2015"  : "Qua lại người cùng vật chờ giống nhau cần nhận kiểm tra, lại vừa tiến ra khỏi cửa thành, hi vọng bản thân ngươi thấy phối hợp chúng ta lệ hành kiểm tra! Như có tự tiện phá cửa người, làm theo như nước nhà luật hình tăng thêm trừng phạt, hi vọng ngươi tự thu xếp ổn thoả.",
	"3015"  : "Lập tức sắp đổi đồi, tâm tình thực khoan khoái, đổi hoàn đồi kêu lên mấy huynh đệ đi trong thành mới mở cái kia gia đổ phường chơi vài cái, đã lâu không chơi, trong lòng thẳng ngứa, không biết nay thiên vận may như thế nào.",
	"4015"  : "Mặc kệ gió thổi mưa lâm ngày sái, khí hậu điều kiện bao nhiêu tồi tệ, chúng ta chưa từng câu oán hận, chưa từng tự tiện rời đi qua chính mình thủ cương vị, không để cho một cái tội phạm theo chúng ta sở thủ cửa thành chạy thoát.",
	"5015"  : "Có chưa từng gặp qua một cái Tây Vực thương nhân? Có nhận được tin tức, nghe nói kia Tây Vực thương nhân là Tây Bắc tộc người Bộ Lạc phái tới mật thám, đặc biệt đến dò hỏi nước nhà quân sự cơ mật, nếu ngươi nhìn thấy tốt nhất báo cho ta xuống.",
	"6015"  : "Muốn làm binh sao? Sở Vương sáng nay hạ lệnh ở cửa thành chỗ dán lên bố cáo: mặt hướng các quốc gia dân chúng chiêu mộ binh lính. Nếu ngươi muốn vì nước tôi dốc sức trong lời nói, nhanh hộ tịch quan nơi đó trước nhập nước nhà quốc tịch.",
	"7015"  : "Hoan nghênh ngươi tới đến nước nhà, chỉ cần ngươi không làm phạm pháp việc, chúng ta nhất định sẽ bạn thân đối đãi ngươi, nhưng nếu của ngươi hành động không hợp với nước nhà ích lợi, xin hãy hi vọng ngươi nhanh chóng rời đi.",
	"8015"  : "Ra vào bổn thành, đi cửa thành là duy nhất cách, trừ phi ngươi có thể võ nghệ cao cường, bất quá ta là không tin trên đời này thực sự như thế bản lĩnh người, ngươi còn muốn cái gì, mau tới đây nhận kiểm tra đi!",
	
	"1018"  : "Có hứng thú để cho ta giới thiệu cho ngươi  một chút chức nghiệp sao? Ngươi đi vắng đi, nói không chừng chính ngươi sẽ chọn sai, vẫn là hi vọng nhĩ hảo hảo suy nghĩ một chút, vấn đề này rất trọng yếu nga!",
	"2018"  : "Ba trăm sáu mươi đi, chuyên gia. Đối với chức nghiệp vấn đề này không cần quá để ý, chỉ cần ngươi làm hảo, làm tinh, ngươi làm theo sẽ có lấy được thành công một ngày, chẳng lẽ ta nói sai rồi sao?",
	"3018"  : "Giới thiệu cho ngươi  cái chức nghiệp đi! Không thu ngân lượng. Vì cái gì ta làm như vậy? Ha ha, làm mọi người phục vụ nha, giới thiệu cho ngươi  chức nghiệp thành công, ta cũng rất có cảm giác thành tựu, ha ha...",
	"4018"  : "Chức nghiệp vô giá cả thế nào chi phân, ngươi cần lý trí đối đãi vấn đề này, không cần cảm thấy được có chút chức nghiệp rất cao quý, có chút chức nghiệp thực hèn mọn, ngàn vạn lần không cần loại nghĩ gì này, bằng không ngươi làm cái gì công tác cũng làm không tốt.",
	"5018"  : "Chức nghiệp vấn đề không nên nhìn rất ngai ban, như vậy bất lợi với ngươi sau khi phát triển, đối với chức nghiệp vấn đề này ngươi cần thận trọng, nhưng là không cần quá để ý, kỳ thật mỗi người mỗi vẻ.",
	"6018"  : "Tục ngữ nói: nam sợ nhập sai đi, nữ sợ gả sai lang. Lựa chọn chức nghiệp cần thận trọng a! Ngàn vạn lần không cần từ nào đó chính mình tính khí, đến lúc đó ngươi làm chính mình không có hứng thú chức nghiệp, vậy ngươi đã có thể hối hận.",
	"7018"  : "Có phải hay không cảm thấy được ở vấn đề này thượng do dự? Kia để cho ta tới cho ngươi một ít đề nghị đi! Lựa chọn chính mình cảm thấy hứng thú, đây là không còn gì tốt hơn, như vậy sẽ đối với ngươi sau khi phát triển rất có trợ giúp.",
	
	"1019"  : "Cái gì chức nghiệp hảo, cái gì chức nghiệp kém, vấn đề này không phải ta định đoạt, ta hi vọng ngươi có cách nhìn của chính mình, hảo cùng kém là muốn dựa vào thời gian để chứng minh, không biết ngươi có thể hiểu hay không.",
	"2019"  : "Chức nghiệp không sao cả tốt xấu, liền xem có hay không tận tâm, bình thường chức vị thượng cũng có thể làm ra kiêu người công trạng, ngươi không tin sao? Kia chỉ có thể nói rõ ngươi không tận tâm, không tin ngươi thử xem xem.",
	"3019"  : "Ba mươi năm Hà Đông, ba mươi năm Hà Tây, không cần vì thế khi chức nghiệp không bị coi trọng mà buồn rầu, tục ngữ nói: phong thủy luân chuyển, hiện tại không bị coi trọng, không được bao lâu liền sẽ phải chịu mọi người chú ý.",
	"4019"  : "Chức nghiệp vấn đề này khó mà nói, tìm cái thời gian chậm rãi cùng ngươi nói chuyện. Ngươi không nên hiện tại đàm? Vậy được rồi! Ngươi trước hết lựa chọn một cái chức nghiệp tận tâm đi làm, tự nhiên sẽ có nên thu hoạch.",
	"5019"  : "Chức nghiệp vấn đề có trọng yếu như vậy sao? Ta không biết là, chính là chính ngươi quá để ý, đem vấn đề này muốn phức tạp, chẳng lẽ ta nói không phải sao? Chỉ cần chính ngươi cảm thấy được cao hứng là được.",
	"6019"  : "Ngươi đối với ngươi hiện tại sở làm chức nghiệp hài lòng không? Nếu không hài lòng, tốt nhất đi đổi một loại chính mình cảm thấy hứng thú chức nghiệp, bằng không ngươi là rất khó làm được tận tâm tận lực.",
	"7019"  : "Để cho ta cho ngươi phân tích hạ nghề nghiệpcủa ngươi đi! Có mấy lời khó mà nói, chỉ có thể dựa vào chính mình đi lý giải, cũng không cần quá để ý cái nhìn của ta, chỉ cần ngươi muốn mở, cái gì phiền não đều cũng biến mất?",

	"1020"  : "Nghe đồn lại muốn đánh giặc, tuy rằng nước nhà ven biển chỗ bên cạnh, nhưng cũng không có thể không định? Đại vương kêu gọi chúng ta đi xây dựng công sự ta là phi thường nguyện ý, làm như vậy cũng là vì chính mình có một yên ổn cuộc sống!",
	"2020"  : "Nghe đồn Đại vương vì phòng bị Tần đánh lén, chuẩn bị lại xây dựng Trường Thành, không biết Đại vương lần này chuẩn bị từ đâu bắt đầu xây dựng. Ta phỏng chừng sẽ theo sở Ngụy trong lúc đó xây dựng một cái, bởi vì nơi đó là Tần đánh lén nước nhà phải qua đường.",
	"3020"  : "Chiến tranh cùng nhau, khổ chính là ai? Còn không phải chúng ta này đó nhân dân, hưng vong thành bại không sẽ ảnh hưởng bọn họ xa xỉ tiêu xài, tục ngữ nói: hứng, dân chúng khổ. Vong, dân chúng khổ. Mạnh yếu tuần hoàn không phải là đạo lý này?",
	"4020"  : "Ngươi gặp qua Trịnh quốc cừ sao? Cái kia công trình thuỷ lợi coi như tiếp qua một ngàn năm cũng có thể nói là thế giới kỳ tích, vì cái gì như ta vậy nói đi? Ta chính là trong đó xây dựng người một trong, trận kia mặt, thật sự là to lớn đồ sộ.",
	"5020"  : "Gần nhất Đại vương không biết tại sao, đột nhiên muốn tu một tòa hoàng cung, giống như kêu A Phòng cung, này không biết cần lãng phí nhiều ít tiền vốn vật lực, Đại vương căn bản là không đi nhận thức cảm thụ của chúng ta!",
	"6020"  : "Hôm kia làm quê nhà sửa chữa và chế tạo phòng ốc xuất hiện vết rách, ta phải lập tức đã qua biết rõ nguyên nhân, bằng không có thể phá hủy thanh danh của ta. Ta sửa chữa và chế tạo phòng ốc đã có nhiều năm, sao sẽ xuất hiện loại tình huống này?",
	"7020"  : "Ta sửa chữa và chế tạo nhà ngươi ở qua sao? Kia kết cấu cùng chất lượng thật sự là không nói, đây cũng không phải là ta thổi, không tin ngươi đi hỏi hỏi cái kia đó ngụ ở ta sửa chữa và chế tạo nhà người, bọn hắn tuyệt đối sẽ nói 'Hảo', không tin ngươi đi hỏi?",

	"1021"  : "Có một môn tay nghề ở trên người, tựu cũng không quá lo lắng ăn, mặc, ở, đi lại chờ vấn đề, ngươi có thể dùng chính mình nắm giữ đích tay nghề vì chính mình sáng tạo của cải. Hơn nữa tay nghề ngươi thường dùng nó, liền gặp tinh ranh hơn thông nó, nên sáng tạo của cải liền gặp càng nhiều.",
	"2021"  : "Lần này đi thon dài thành nhất định phải thuận tiện cấp nhi đồng mang chút ăn ngon gì đó, nghe nói Hàn Quốc nam bộ sản xuất nhiều khoai lang, đối với hài tử của ta, bọn hắn đã phi thường thỏa mãn, tốt nhất còn có thể mang chút những vật khác.",
	"3021"  : "Nhà của ta có tam con trai, bọn hắn cũng đã lập gia đình, ha ha... Hỏi ta vì cái gì không hưởng phúc? Chính mình có một thân thủ nghệ ở trên người, vì cái gì không cần xử dụng đây? Dù sao cũng không phải làm cố sức việc.",
	"4021"  : "Nghe nói lần trước ta cấp Đại vương tu trong hoa viên loại rất nhiều quý báu hoa loại, có Mẫu Đan, Đại Lý hoa lan, kim Hải Đường vân vân, dù sao rất nhiều, ai... Bọn hắn này đó quý nhân cũng thật biết hưởng thụ.",
	"5021"  : "Lần trước bị trêu chọc đi mở lấy mà thành Trịnh quốc cừ, nghe nói hiện tại đã muốn phát huy rất lớn tác dụng, trừ bỏ khơi thông đường sông ở ngoài còn tưới vạn mẫu ruộng tốt, ha ha. . . Như loại này con đường càng nhiều càng tốt.",
	"6021"  : "Đại vương sai người ở chỗ cửa thành thiếp hạ bố cáo: treo giải thưởng thiên kim nặng sính người giỏi tay nghề một người, vì nó tạc điêu ngai vàng. Ta thật sự muốn đi thường thử một chút, thiên kim a! Thật sự là mê người.",
	"7021"  : "Tuổi trẻ thời gian không có hảo hảo đi học tay nghề, hiện tại cho người khác sửa chữa và chế tạo nhà thì cảm giác có nhiều thứ làm không được, cần không phải là tạo không hợp với nhân ý, xem ra ta là được đổi nghề đổi nghiệp.",
	
	"1022"  : "Ta chỉ biết sửa chữa và chế tạo phòng ốc nga! Nếu muốn làm cái khác ta nhưng là không còn biện pháp, bất quá ta có thể hướng ngươi giới thiệu một chút trong thành cửa hàng đại khái phương vị, ngươi có thể dựa theo cần muốn đi tìm cầu nên trợ giúp.",
	"2022"  : "Gần nhất Đại vương lại muốn xây dựng công sự, ta cũng không muốn lại đi, lần trước thiếu chút nữa là ở chỗ này xảy ra sự cố, làm sao bây giờ đây? Ta phải muốn cái biện pháp đào thoát rụng, đi trước ngoài thành thân thích gia trốn một chút đi!",
	"3022"  : "Đại vương phái người theo Côn Lôn Sơn chở về một khối to lớn Ngọc Thạch, muốn tìm mấy người giỏi tay nghề đem khối ngọc này Thạch cân nhắc thành một cái ngọc sàng. Ta thật sự muốn đi tiếp nhận chuyện này, nghe nói có thể được đến dày thù lao.",
	"4022"  : "Thường xuyên xuất môn bên ngoài sửa chữa và chế tạo phòng ốc, trong nhà mình nhất mẫu ba phần sẽ không người trông giữ, hiện tại mảnh đất kia bụi cỏ dại sinh, xem ra là được tìm cái thời gian hảo hảo đi tu sửa hạ xuống, ta cảm thấy được mảnh đất kia sau khi sẽ hữu dụng.",
	"5022"  : "Đều nói chúng ta Tần quốc sản xuất nhiều làm bằng bạc dụng cụ, Nhưng ta ở Tần quốc làm nhiều năm như vậy thợ thủ công cũng không còn thấy có mấy người dùng qua, xem đến sử dụng làm bằng bạc dụng cụ đều là đó Phú Quý người ta, giống như ta vậy thợ thủ công đừng hy vọng dùng tới.",
	"6022"  : "Con ta bị nắm đi sung quân, ai. . . Này có thể như thế nào cho phải, ta nhưng liền này môt đứa con trai, còn trông cậy vào hắn kéo dài hương khói. Trên chiến trường đao kiếm không có mắt, vạn nhất xuất hiện ngoài ý muốn, ta như thế nào hướng tổ tiên công đạo.",
	"7022"  : "Ta sửa chữa và chế tạo nhà ngươi ở qua sao? Kia kết cấu cùng chất lượng thật sự là không nói, đây cũng không phải là ta thổi. Không tin ngươi đi hỏi hỏi cái kia đó ngụ ở ta tạo nhà người, bọn hắn tuyệt đối sẽ nói ta tạo thật là tốt, không tin ngươi đi hỏi?",

	"1023"  : "Trong nhà phải dựa vào ta bên ngoài làm điểm thợ thủ công sống đến duy trì gia kế, ai ~? Ở tình thế này, liền thuận theo tình thế này phát triển thêm nữa, đến lúc đó có thể theo quốc gia nơi đó được đó tiền liền đã thỏa mãn.",
	"2023"  : "Lần này đi thon dài thành nhất định phải thuận tiện cấp nhi đồng mang chút ăn ngon gì đó. Nghe nói Hàn Quốc nam bộ sản xuất nhiều khoai lang, đối với hài tử của ta, bọn hắn đã cao hứng phi thường, tranh thủ lần này ở mang chút những vật khác.",
	"3023"  : "Ta nghĩ thu cái đồ đệ, tư chất cùng thiên phú đều cần tốt lắm, ta nghĩ đem tay nghề của ta truyền thụ cho hắn. Như vậy ta tuổi già rời đi nhân thế, cũng không có cái gì tiếc nuối, ngươi nguyện ý làm đồ đệ của ta sao?",
	"4023"  : "Ngươi tìm ta có việc sao? Muốn tạo một tòa nhà? Thật không đúng dịp, ta đã bị người dự hẹn ước. Đó là một rất lớn công trình, này cần phải chờ thật lâu, nếu ngươi cảm thấy được thờì gian quá dài ngươi hay là đi tìm người khác đi!",
	"5023"  : "Gần nhất Đại vương không biết vì sao, hứng động trăm vạn người, ở ly sơn sửa chữa và chế tạo công sự. Nghe nói cả ly sơn đã bị đào rỗng, bên trong kiến tạo như Vương Cung thông thường, hay là nơi đó đó là Vương mộ nơi.",
	"6023"  : "Thật là làm cho người buồn rầu, ta nghĩ đem gia truyền tay nghề truyền cho con ta, có thể hắn cả ngày si mê cho đánh bạc, căn bản không đi vì tương lai tính toán, này có thể như thế nào cho phải? Ngươi có thể có pháp để cho hắn từ bỏ đổ nghiện?",
	"7023"  : "Đừng tưởng rằng ta là thợ thủ công, chỉ đối với sửa chữa và chế tạo kiến trúc tinh thông, đối với nước nhà y thuật, ta cũng có chút nghiên cứu. Trước kia ta tổ tiên đều là làm nghề y người, ha ha. . . Đối với y thuật nhiều ít ta cũng hiểu được điểm.",

	"1084"  : "Nay mỗi ngày khí  tốt như vậy, làm cho lòng người chuyện khoan khoái, ta riêng đi ra chuyển vừa chuyển, nhìn một cái, mới vừa nghe nói 'Muối biển lại đại lấy được mùa thu hoạch', ha ha... Thật là một ngày lành, cái này chúng ta dân chúng cuộc sống sống dễ chịu hơn.",
	"2084"  : "Đầu năm nay đại tảo không tốt bán a, nước nhà dân chúng, hàng năm chính là dựa vào này duy trì sinh kế. Hi vọng triều đình không cần lão là muốn đánh giặc, cũng cho chúng ta dân chúng ngẫm lại, săn sóc một chút chúng ta khó khăn.",
	"3084"  : "Nước nhà chạm ngọc kỹ thuật có thể nói là nhất tuyệt, không tin, ngươi đi trên đường nhìn xem, nhìn xem có bao nhiêu gia chạm ngọc cửa hàng; chỗ này của ta còn có hoa tiêu thứ này đây? Đây cũng là nước nhà đặc sản, ngươi trước tiên có thể thử dùng xuống.",
	"4084"  : "Nước nhà đặc sản ngươi nếm qua sao? Chính là bánh quả hồng, đây chính là nước nhà đặc hữu, bánh quả hồng là làm như thế nào nơi này đừng nói, có cơ hội ngươi có thể mua một ít mang về cấp người trong nhà nếm thử.",
	"5084"  : "Bằng hữu, vừa xong nước nhà đi! Xem nước nhà náo nhiệt như thế, có phải hay không nghĩ đến chỗ chuyển vừa chuyển đây? Ngươi tốt nhất mua đó chúng ta nơi này ngân khí, kia ngân khí tạo công tay nghề có thể nói 'Thiên hạ nhất tuyệt' .",
	"6084"  : "Nhà của ta hàng năm phiêu bạc ở trên nước, ha ha. . . Không tin đi? Bản nhân lấy thuyền làm gia, dựa vào đánh cá sống bằng nghề, chúng ta kia dân chúng đều là như thế cuộc sống, ngươi có phải hay không muốn đi xem?",
	"7084"  : "Biết hạt dẻ là vật gì sao? Chưa thấy qua đi! Đây chính là nước nhà sở chỉ có, ngươi ngàn vạn lần không nên nhìn nó ngoại hình nghĩ đến vật kia sinh trưởng ở trong đất, hạt dẻ chính là trường trên tàng cây nga!",
	
	"8020"  : "Ta đây tiểu điếm, đều là một ít việc nhà đồ ăn, bất quá khách quan nhóm đối tay nghề của ta vẫn là có rất cao đánh giá.",
	
	"8021"  : "Ta đối các quốc gia mỹ thực đều có tốt lắm nghiên cứu, Chu vương cũng rất thưởng thức. Thế nào, muốn cùng ta học một chút tay nghề sao? Ta nhưng không dễ dàng thụ đồ nha.",
//	"80221"  : "传闻又要打仗，虽然本国靠海地处边缘，但也不能不准备？大王号召我们去修筑工事我是非常愿意，这样做也是为自己有一个安定生活！", 
//	"80222"  : "传闻大王为了防备秦偷袭，准备再次修筑长城，不知道大王这次准备从哪开始修筑。我估计会从楚魏之间修筑一条，因为那里是秦偷袭本国必经之路。", 
//	"80223"  : "战争一起，苦的是谁？还不是我们这些老百姓，兴亡成败不会影响他们的奢侈挥霍，俗话说：兴，百姓苦。亡，百姓苦。强弱循环不就是这个道理？", 
//	"80224"  : "你见过郑国渠吗？那个水利工程就算再过一千年也可谓是世界奇迹，为什么我这样说呢？我就是其中的修筑者之一，那场面，真是宏伟壮观。", 
//	"80225"  : "最近大王不知为什么，突然想修一座皇宫，好像叫阿房宫，这不知道要浪费多少财力物力，大王根本就不去体会我们的感受！", 
//	"80226"  : "前日为邻里修造的房屋出现裂痕，我得马上过去弄清原因，不然可坏了我的名声。我修造房屋已有多年，怎会出现这种情况？", 
//	"80227"  : "我修造的房子你住过吗？那结构和质量真是没的说，这可不是我吹，不信你去问问那些住我修造房子的人，他们绝对会说‘好’，不信你去问？", 

]);

mapping FamilyWordTable = ([
	"Đào Hoa Nguyên":"Đào Hoa Nguyên là tông sư của phe phái Quyền Pháp, toàn bộ chú trọng về sự tu luyện khí, thể, hình, nội công rất thâm hậu. Có thể trực tiếp dùng Hỗn Nguyên Chân Khí trong người để xâm nhập phá huỷ kinh mạch, lục phủ ngũ tạng trong người đối thủ. Kiến nghi phối điểm: Thể Lực, Nại Lực; Vũ khí môn phái: Quyền Pháp",

	"Cấm Vệ Quân":"Tương truyền rằng Bá Vương Thương Pháp và Phong Ma Côn Pháp đều do lang quân 3 mắt Đại Tướng Quân triều nhà Chu Dương Tiễn lúc khai quốc sáng lập. Thương pháp sắc bén không gì so sánh, hung như Mãnh Cầm Lợi trảo. Côn Pháp hào khí vạn trượng, cuồng xích Bài Sơn Đảo Hải. Chỉ cần cùng lúc dùng 2 loại kỹ thuật, đã có thể lấy một địch trăm, làm chấn động võ lâm!Ngoài sự truyền dạy thương pháp và côn pháp ra, luyện tập quân sự nghiêm khắc khiến cho mỗi đệ tử Cấm Vệ Quân có được 1 thể lực cường tráng và 1 ý chí thật dẻo dai. Nếu không có niềm tin tất thắng, chú ý đừng tùy tiện làm kẻ địch với Cấm Vệ Quân! Kiến nghị phân phối điểm:Thể Chất, Cường Lực; Vũ khí môn phái: Thương, Bổng.",

	"Mao Sơn":"Hiểu thiên cơ, lệnh quỷ thần, trên có thể thông Thiên Đinh Quảng Lăng, dưới có thể thông Âm Ty Địa Phủ. Triệu quỷ thần, sử Thần Tôn, vì những kĩ năng đặc biệt kinh ngạc, sự tồn tại của Mao Sơn trước giờ làm cho thế nhân khiếp sợ. Nhưng mà làm Mao Sơn Đệ Ngũ Đại Chưởng Môn Mao Chân Nhân, ngược lại hy vọng có thể phá đi cái nhìn của tập tục thế nhân, tận tâm tận lực phát triển và làm rạng danh Mao Sơn. Dưới sự cố gắng của Mao Chân Nhân, rất nhiều thanh niên dần dần có hứng thú với môn phái truyền kỳ này, và bái lại làm lễ nhập môn Mao Chân Nhân. Kiến nghị phối điểm: Tinh Thần, Thể Chất; Vũ khí môn phái: Kiếm.",

	"Thục Sơn":"Mấy ngàn năm trước, vẫn là yêu ma hoành hoành, thời đại hoang mang của ác quỷ tác quái. Hai vị tổ sư mở núi của phái Thục Sơn là Thái Hư Chân Nhân và Nhất Tâm Đạo Trưởng vì cứu vớt thiên hạ trăm họ, sau khi trải qua bao nhiêu gian khổ cuối cùng hợp sức nhau giết chết yêu ma Long Cốt Tinh chiếm cứ Thục Sơn hàng ngàn năm nay. Về sau, 2 vị đại sư thu nạp đệ tử rất nhiều, dốc hết sức những gì học được từ cuộc sống trao tặng mọi người. Thục Sơn phái vang danh thiên hạ là từ đó. Thục Sơn Chủ tu Kiếm Pháp kiến nghị phối điểm: Tinh Thần; Chủ tu Đao Pháp kiến nghị phối điểm: Thể Chất, Cường Lực; Vũ khí môn phái: Đao, Kiếm.",

	"Vân Mộng Cốc":"Để trốn tránh chiến loạn, Quỷ Cốc Tử ở ẩn trong 1 địa trạch. Hơn 50 năm đào sâu nghiên cứu, Quỷ Cốc Tử không những nắm vững học thuyết về dược lý , độc vật độc tính, mà còn lĩnh ngộ được thuật Tâm Trí Mê Hoặc và Kỳ Môn Trận Giáp vô cùng huyền diệu. Về sau, Quỷ Cốc Tử thu nhận 3 đồ đệ Tôn Tẫn, Bàng Quyên và Tô Tần, lúc này dang tiếng của Vân Mộng Cốc Quỷ Cốc Tử dần dần lan ra khắp thiên hạ, ngày càng có nhiều người ngưỡng mộ đến bái ông ta làm sư phụ. Môn phái mới Vân Mộng Cốc từ đó hình thành. Kiến nghị phối điểm: Tinh Thần, Thể Chất; Vũ khí môn phái: Pháp Kiếm.",

	"Đường Môn":"Đường Môn, tên thần bí này được lưu truyền trên giang hồ . 1 tổ chức bí mật ẩn tàng nơi hắc ám, nhờ vào kỹ xảo dùng độc và ám khí đặc biệt, đã mai táng vô số giang hồ hiệp sĩ. Đến sau khi Đại Chưởng Môn Nhân thứ 24 của Đường Môn Đường Hổ tiếp nhận chức Chưởng Môn, Tương truyền mấy đời bộ mặt thật của việc ám sát Thế Gia mới được bày ra trước mặt người đời. Đường Môn nổi tiếng là dùng kỹ xảo ám khí có độc, có thể cướp đi mạng sống 1 người trong nháy mắt. Trong lịch sử dài lâu của Chu Quốc, Đường Gia rất có lợi cho nhà Chu, Ám Trung vì thiên tử mà giết rất nhiều người. Điểm kiến nghị thêm: Cường Lực, Mẫn Tiệp ; Vũ khí môn phái: Ám khí.",

	"Côn Luân":"Đông phương Bồng Lai tây phương Côn Luân, ngàn năm trở lại đây 1 trong nguồn gốc truyền thuyết của dân gian được lưu truyền rằng -- Tây phương Côn Luân, đỉnh núi Côn Luân Sơn nằm ở phía tây của trường thành nhà Tần. Bất luận là thần thoại trường sinh bất lão, hay là pháp thuật có thể hô phong hoán vũ, triệu hoán thần long, ma lực của Côn Luân Sơn vẫn mãi mãi hấp dẫn vô số người cầu đạo. Dù là thế, nếu người tu luyện tiên thuật không lĩnh ngộ năng lực của người thường, không có tinh thần tin tưởng kiên định, sẽ rất khó thành chính quả. Kiến nghị phối điểm: Tinh Thần, Mẫn Tiệp; Vũ khí môn phái: Kiếm.",
]);	

mapping FamilyLocateTable = ([
	"Đào Hoa Nguyên":	({ 289,80,54, }),
	"Cấm Vệ Quân":	({ 080,185,74, }),
	"Mao Sơn":		({ 269,266,183, }),
	"Thục Sơn":		({ 273,205,158, }),
	"Vân Mộng Cốc": 	({ 165,103,26, }),
	"Đường Môn":		({ 324,92,117, }),
	"Côn Luân":	({ 054,111,137, }),
]);

// 函数：显示说话(标准)
string get_normal_word( object me ) 
{ 
        string id;
        id = get_file_name(me);
        if (!NomalWordTable[id[<4..]]) return "";
        else return NomalWordTable[id[<4..]];
}

// 函数：显示说话(国家)
string get_country_word( object me ) 
{ 
        string id;
        id = get_file_name(me);
        if (!CountryWordTable[id[<4..]]) return "";
        else return CountryWordTable[id[<4..]];
}

string get_family_word(string fam)
{
	return FamilyWordTable[fam];
}

int * get_family_locate(string fam)
{
	return FamilyLocateTable[fam];
}