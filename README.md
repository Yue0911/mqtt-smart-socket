# mqtt-smart-socket
來2022/12/2益師傅的MQTT智能插座程式修改來的
新增WiFiManager，NTPClient，OTA支援
# WiFiManager
<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_1.png" width="200" height="350" alt="主頁面"/><br/>
<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_2.png" width="200" height="350" alt="wifi設定"/><br/>
<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_3.png" width="200" height="350" alt="資料頁面"/><br/>
# OTA
<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_4.png" width="350" height="150" alt="OTA頁面"/><br/>
# 安裝-Arduino
下載ZIP檔

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_5.png" width="300" height="300" alt="下載ZIP"/><br/>
解壓縮ZIP

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_6.png" width="400" height="150" alt="解壓縮ZIP"/><br/>

開啟library資料夾，把裡面的ZIP檔解壓縮到Arduino\libraries裡

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_7.png" width="400" height="150" alt="安裝LIB"/><br/>

之後開啟Arduino_IDE\MQTT_Switch裡的MQTT_Switch.ino

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_8.png" width="500" height="400" alt="MQTT_Switch"/><br/>

<h1>!!警告!! !!請勿更新Library!!</h1>

選擇ESP8266 D1

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_9.png" width="700" height="400" alt="ESP8266_D1"/><br/>

選擇端口後編譯上傳

# 安裝-PlatformIO
下載ZIP檔

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_5.png" width="300" height="300" alt="下載ZIP"/><br/>
解壓縮ZIP

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_6.png" width="400" height="150" alt="解壓縮ZIP"/><br/>

開啟platformIO資料夾，把裡面的ZIP檔解壓縮

開啟VS code，選擇左方"延伸模組"，上方搜尋"PlatformIO"，安裝PlatformIO

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_10.png" width="400" height="150" alt="安裝PlatformIO"/><br/>

安裝完畢後選擇左方PlatformIO，後點選open，在點選Platform，在點選Embedded，搜尋esp，安裝Espressif 8266

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_11.png" width="600" height="400" alt="安裝Espressif_8266"/><br/>

安裝完後，點選Home，點選Open Project

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_12.png" width="600" height="300" alt="Open_Project"/><br/>

選擇platformIO資料夾，解壓縮完後的資料夾

點選src，開啟main.cpp

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_13.png" width="500" height="300" alt="開啟main_cpp"/><br/>

點選左下角"打勾圖示"開始編譯程式

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_14.png" width="500" height="100" alt="編譯"/><br/>

之後點選左下角"箭頭圖示"開始上傳程式

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_15.png" width="500" height="100" alt="上傳"/><br/>

