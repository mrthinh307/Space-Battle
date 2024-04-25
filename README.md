# SPACE BATTLE

## **Introduction** 

+ Họ và tên: Hoàng Duy Thịnh - K68J - UET

+ Mã sinh viên: 23020708 

+ Bài tập lớn: Space Battle (INT2215_52 - Lập trình nâng cao) 

# Introducing the game

Space Battle thuộc vào thể loại game hành động (action game). Trong game này, người chơi điều khiển một phi cơ và sử dụng vũ khí và các chiêu thức để bắn hạ các kẻ địch để đạt được thời gian sinh tồn cùng số lượng kẻ địch đã bị tiêu diệt nhiều nhất.

- Game có đầy đủ các chức năng hỗ trợ người chơi trong việc thoát game, bắt đầu lại trò chơi. mô tả cách chơi, ngoài sử dụng bàn phím và chuột đơn thuần còn có thể sử dụng Tay cầm để trải nghiệm trò chơi, sử dụng phím ESC để dừng game...

- Có âm thanh sinh động mô tả các chức năng và hành động của trò chơi.

- Thử nghiệm game: 

- [A. Ways to download game](#a-ways-to-download-game)
    * [1. Method 1: No code included.](#a-cách-1-không-bao-gồm-code)
    * [2. Method 2: Include code and compilable.](#b-cách-2-bao-gồm-code-và-có-thể-biên-dịch)
- [B. Instrucsion and Start Game](#b-instrucsion-and-start-game)
- [C. Select Level](#c-select-level)
- [D. Components In Game](#d-components-in-game)
- [E. Way To Play](#e-way-to-play)
- [F. Supplemt](#f-supplemt)
- [Soure code & Reference source](#soure-code--reference-source)
- [Development & Conclusion](#development--conclusion)

# A. Ways to download game

## 1. Method 1: No code included.

Tải game (được nén thành .zip) tại link sau:
 
Cách này tiết kiệm bộ nhớ và thời gian tải đi rất nhiều.

Giải nén game vào một thư mục và bật run.exe lên và chơi.

## 2. Method 2: Include code and compilable.

**Step 1:** Clone repo này về môi trường **Visual Studio Code**: [Link Repository](https://github.com/mrthinh307/TankGme)


![image](./images/Readme/repo.png)


**Step 2:** Mở **Terminal** dẫn đến file của game (có thể sử dụng tổ hợp phím **Ctrl + ALt + N**) điền chữ **make** sau đó nhấn **Enter**, chờ khoảng 10s và trải nghiệm trò chơi.

![image](./images/Readme/makefile.png)

# B. Instrucsion and Start Game

- Sau khi mở trò chơi thành công, sẽ xuất hiện màn hình chờ của game:
![image](./images/Backgrounds/menu.jpg)

**1. PLAY**

- Khi người chơi nhấn vào nút **PLAY** - có nghĩa rằng xác nhận tham gia trò chơi, màn hình sẽ dẫn người chơi đến phần chọn chức năng điều khiển.

- Trò chơi cung cấp cho người chơi 2 sự lựa chọn trong chức năng điều khiển cho phi cơ gồm:
    + **Bàn phím và Chuột**.
    + **Tay cầm (XBox, PS4, PS5...)** ( dưới đây là hướng dẫn nút điều khiển cho tay cầm thuộc họ **XBox**, các loại tay cầm khác điều khiển tương tự) .

### *Control + Shoot ( Điều khiển và Bắn đạn)* 

| Control | Keyboard | Gamepads | 
|---------|----------|----------|
| UP      |     W    |Joysticks |
| DOWN    |     S    |Joysticks |
| LEFT    |     A    |Joysticks |
| RIGHT   |     D    |Joysticks |

|  Shoot  | Mouse    | Gamepads | 
|---------|----------|----------|
| Normal  |LeftMouse |    (A)   |
| Util    |RightMouse|    (B)   |

- Người chơi chọn chức năng điều khiển nào thì nhấn chuột vào **thanh mô tả** của chức năng đó:

- VÀO GAME

- Người chơi sẽ điều khiển nhân vật được xuất hiện ở giữa màn hình:

![image](./images/Readme/tank.png)

</div>

**2. EXIT**

- Khi người chơi nhấn vào nút **EXIT** - cửa sổ trò chơi được đóng lại và trò chơi kết thúc.

# C. Select Level

- Người chơi điền số kẻ địch ban đầu mà mình muốn đối đầu. Tùy theo độ khó mà người chơi muốn trải nghiệm.


# D. Components In Game

-    Tank Object ![image](./images/Readme/tank.png)
     : là đối tượng người chơi điều khiển 

-    Mini Enemy ![image](./images/Readme/minienemy.png)
     : là đối tượng kẻ địch con, sẽ tăng thêm 1 đối tượng sau 30s đầu tiên của game, và sau lần xuất hiện đầu tiên của Boss sẽ là 60s cho mỗi lần tăng thêm.

-   ***Boss*** ![image](./images/Readme/boss.png): là đối tượng kẻ địch mạnh. Sẽ xuất hiện lại sau mỗi 60s.

    - ***Blood bar of boss***![image](./images/Readme/0.png) : là thanh máu của Boss, giảm 1 đơn vị máu khi boss trúng đạn **Normal** và 2 đơn vị máu khi là **Util**.
    
- ***Timer*** (Bộ đếm thời gian) ![image](./images/Readme/timer.png): Ghi lại thời gian sinh tồn của người chơi.

- ***Killed enemy icon*** (Số lượng kẻ địch bị tiêu diệt) ![image](./images/Readme/killenemy.png): Ghi lại số lượng kẻ địch đã bị người chơi tiêu diệt

- ***Util***(Rocket) ![image](./images/Backgrounds/rocket.png): số lượng Rocket người chơi có( tăng thêm 1 sau mỗi 5 kẻ địch bị tiêu diệt). Khác với đạn thường Rocket có khả năng xuyên thấu kẻ địch, ngoại trừ **Boss** nhưng cũng có sát thương lên Boss cao hơn.

- ***Heart***(Mạng): ![image](./images//Backgrounds/heart.png): số lượng mạng của phi cơ ( -1 <=> va chạm với kẻ địch).

- ***Pause Button*** (Nút dừng game): Nếu muốn tạm dừng trò chơi hoặc chơi lại khi đang trong trò chơi, người chơi có thể ấn nút **ESC**, cửa sổ game sẽ hiện lên trang Setting:

![image](./images/Backgrounds/setting0.png)
- Ấn chuột vào mục **HOME** sẽ đưa người chơi về cửa sổ MENU ban đầu. Người chơi có thể nhấn PLAY để chôi lại.
- Ấn chuột vào mục **RESUME** để tiếp tục trò chơi đang tạm dừng,

- Cùng một số thành phần khác...

- Bố cục game cơ bản:

<div style="text-align: center;">

![image](./images/Readme/struct.png)
</div>

- Nếu như bạn đang thắc mắc những biểu tượng màu sắc xuất hiện trong cửa số trên là gì? Thì đó chính là tính năng giúp người chơi cảm thấy thỏa mãn với bộ hơn 20 skills (có phát triển thêm trong tương lai) cho nhân vật chính, tất cả các skill đều kèm theo hiệu ứng hình ảnh cùng âm thanh phù hợp để người chơi có thể cảm nhận chân thực.

![image](./images/Readme/ex.png)
- example : Skill làm trói làm choáng kẻ địch

</div>


# E. Way To Play

Tấn công kẻ địch bằng đạn hoặc sử dụng các skill, không cho kẻ địch chạm vào phi cơ. Nếu chạm vào số mạng sống sẽ giảm đi 1 (góc trái bên dưới cửa sổ trò chơi). Mặc định ban đầu khi bắt đầu trò chơi người chơi sở hữu 3 mạng. <br/>

Trò chơi kết thúc khi số mạng của người chơi còn **0**.

## 1. Some Skills(Một số loại Skills)

Icon của skill xuất hiện random với tỉ lệ ngẫu nhiên sau khi tiêu diệt kẻ địch ( có thể có có thể không). Người chơi di chuyển phi chạm vào icon tự động kích hoạt Skill:

|                                                                             | Tên cây	     | Chức năng                                                                                                                    |
|-----------------------------------------------------------------------------|--------------|------------------------------------------------------------------------------------------------------------------------------|
| <img src="images/Utils/gift/4dan.png" width=50>  | Straight Beam	  | Đường đạn thay đổi thành một chùm đạn gồm 4 cột đạn thẳng hàng (30S).                                                                                             |
| <img src="images/Utils/gift/booster.png" width=50>    | Booster	   | Tăng gấp đôi tốc độ cho phi cơ (10s).                                                                                              |
| <img src="images/Utils/gift/dan4phia.png" width=50>          | Wall-nut	    | Đạn bắn ra từ 4 phía của phi cơ mỗi viên lệch nhau 90 độ (30s).                                                    |
| <img src="images/Utils/gift/danloang.png" width=50>        | Đạn Loang 	    | Đạn bắn ra theo 3 đường xiên hướng từ đầu của phi cơ đi ra(30s). |
| <img src="images/Utils/gift/default.png" width=50> | Default Mode  | Đưa phi cơ về chế độ mặc định, xóa mọi skills hiện có(10s).                                                               |
| <img src="images/Utils/gift/hp.png" width=50>  | HP	 | Ngay lập tức cộng một mạng sống cho phi cơ.      
| <img src="images/Utils/gift/new1.png" width=50>  | Green Diamond Bullet	 | Đạn của phi cơ được nâng cấp / chuyển đổi sang dạng mới.      
| <img src="images/Utils/gift/new2.png" width=50>  | Green Diamond Bullet	 | Đạn của phi cơ được nâng cấp / chuyển đổi sang dạng mới.  
| <img src="images/Utils/gift/phitieu.png" width=50>  | Green Diamond Bullet	 | Đạn của phi cơ được nâng cấp / chuyển đổi sang dạng mới.  
| <img src="images/Utils/gift/plusrocket.png" width=50>  | Add Rocket	 | Số Rocket (Utils) được cộng thêm.  
| <img src="images/Utils/gift/preventenemy.png" width=50>  | Magnet	 | Thỏi nam châm trong không gian sẽ  hút tất các các skill tồn tại trên màn hình trò chơi(30s).  
| <img src="images/Utils/gift/rocket2.png" width=50>  | Upgrade Rocket	 | Chiêu thức Rocket(Util) của phi cơ được nâng cấp lên dạng mới nhanh hơn, sát thương diện rộng hơn.                                                            |
| <img src="images/Utils/gift/shield.png" width=50>  | Shield	 | Trói buộc kẻ địch, gây choáng và không thể di chuyển(5s).                                                            |
| <img src="images/Utils/gift/stunned.png" width=50>  | Stun 	 | Chiêu thức Rocket(Util) của phi cơ được nâng cấp lên dạng mới nhanh hơn, sát thương diện rộng hơn.                                                            |
| <img src="images/Utils/gift/superbullet.png" width=50>  | Super Bullet | Đúng như cái tên của nó, đường đạn bắn ra vô cùng ảo ma Canada =)).                                                            |
| <img src="images/Utils/gift/teleport.png" width=50>  | Teleport	 | Dúng như cái tên của nó, 1 vị trí bất kì trong cửa số trò chơi được lựa chọn và phi cơ sẽ teleport đến vị trí đó.                                                            |
| <img src="images/Utils/gift/ziczac.png" width=50>  | Trap Bullet	 | Đạn được bắn ra sẽ xoay tròn tại vị trí đó, tạo lên bẫy khiến kẻ địch chạm phải.                                                            |
| <img src="images/Utils/gift/treasure.png" width=50>  | Icon Ruby Nói Chung	 | Người chơi thu thập Ruby để tích lũy kinh nghiệm.                                                            |

- Và một số skill thú vị khác, người chơi sẽ được trải nghiệm khi tham gia trò chơi.

- P/s: Sau khi xuất hiện, các icon skill sẽ vỡ tan (mất đi) nếu sau 1 khoảng thời gian đã set mặc định hoặc khi kẻ địch va chạm.

# F. Supplement

## See Also

### *Các kỹ thuật sử dụng*
- Thư viện SDL2.0.

- Sử dụng nhiều class, vector, tách file, kế thừa....

- Tối ưu việc tạo nhiều đối tượng bằng cách reset random vị trí của kẻ địch di chuyển từ sau 4 phía màn hình sau khi bị hạ, đạn của kẻ địch cũng xử lý tương tự.

- Vận dụng kiến thức toán học để tính toán được góc xoay, sự di chuyển của các kẻ địch hướng về phía người chơi nhưng không di chuyển chồng lên nhau. Set cho đường đạn của kẻ địch hướng một cách tương đối về hướng phi cơ, vừa tạo ra độ khó, độ bất ngờ nhưng cũng giữ được mức độ cân bằng cho trò chơi. Tính toán sự di chuyển và xuất hiện cho đạn của phi cơ góp phần tạo nên các skill bắn đạn độc đáo.

- Xử lý thời gian, thao tác chuột và bàn phím, tay cầm, âm thanh, hình ảnh chuyển động, chữ. 

- Tạo menu và các nút ấn di chuyển giữa các menu. 

### Soure code & Reference source

#### 1. Source code :
- Trình bày thông qua clip demo game.
#### 2. Nguồn tham khảo:
- Cách sử dụng, cài đặt SDL2.0 trên môi trường VSCODE và CodeBlock.

- Cách sử dụng thư viện SDL2.0, quản lý chương trình: Tham khảo trên lazyfoo và các video của cô Trần Thị Minh Châu, Stack Overflow, kênh youtube: Phát triển phần mềm AZ123, codegopher, Let's Make Games,...

- Hình ảnh: Tìm kiếm trên Google kết hợp tự design.
- Âm thanh: Tra trên Google

# Development & Conclusion

## Hướng phát triển:

- Không chỉ người chơi mà kẻ địch cũng có thể ăn những skill rơi ra, phù hợp với đối tượng kẻ địch mà update tính năng skill đó lên kẻ địch làm trò chơi trở nên thú vị hơn.

- Cập nhật tính năng bảng xếp hạng, sau mỗi lần chơi người chơi sẽ được nhập tên để lưu lại kết quả chơi của mình.

- Phát triển nốt tính năng còn lại trên thanh MENU ghi lại kỉ lục và tăng cấp độ LEVEL khi thu thập đủ số Ruby, lên Level mới người chơi sẽ được trải nghiệm Phi cơ mới.

- Phát triển tính năng Multiplayer:
    + 2 PLAYERS VERSUS ENEMY( Đua nhau về số kẻ địch hạ gục or Thời gian sinh tồn (Có xử lý va chạm giữa 2 players)/ Cùng phe(không xử lý va chạm))
    + SOLO BETWEEN 2 PLAYERS(Thiết lập thanh blood_bar như boss, xử lý va chạm như, ăn skill và chiến đấu lẫn nhau.)

- Update thêm những skills mới.

## Sau khoảng hơn 1 tháng làm bài tập lớn:

- Em thấy mình đã cải thiện được rất nhiều kỹ năng trong việc tư duy thuật toán và viết code, khả năng lên ý tưởng, xây dựng kế hoạch và thực hiện từng bước một.

- Học được cách setup môi trường, sử dụng thư viện ngoài. 

- Chương trình rất dễ để refactor cũng như update tính năng. 

- Vận dụng các kiến thức các môn đại cượng vào chương trình.

- Học cách thực hiện nhiệm vụ cá nhân một cách hiệu quả.

- Hoàn thànhmột chương trình hoàn chỉnh do chính bản thân tạo ra.

<div style="text-align: center;">

***THANKS FOR READING MY README.***

