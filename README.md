# mqtt-smart-socket
來2022/12/2益師傅的MQTT智能插座程式修改來的
新增WiFiManager，NTPClient，OTA，FS支援<br>
<h3>注意，此範例Library是修該過的，請使用範例提供的Library</h3>

<h3><a href="https://github.com/Yue0911/mqtt-smart-socket#%E5%AE%89%E8%A3%9D-arduino-1">安裝-Arduino</a><br>
<h3><a href="https://github.com/Yue0911/mqtt-smart-socket#%E5%AE%89%E8%A3%9D-platformio-1">安裝-PlatformIO</a><br>
<h3><a href="https://github.com/Yue0911/mqtt-smart-socket#%E4%BD%BF%E7%94%A8%E6%96%B9%E5%BC%8F-1">使用方式</a><br>
<h3><a href="https://github.com/Yue0911/mqtt-smart-socket#%E8%B3%87%E6%96%99%E6%96%87%E4%BB%B6-1">資料文件</a><br>
<h3><a href="https://github.com/Yue0911/mqtt-smart-socket#%E5%91%BD%E4%BB%A4-1">命令</a><br>
<h3><a href="https://github.com/Yue0911/mqtt-smart-socket#%E5%91%BD%E4%BB%A4%E5%9B%9E%E5%82%B3%E5%80%BC-1">命令回傳值</a><br>
<h3><a href="https://github.com/Yue0911/mqtt-smart-socket#ota%E6%9B%B4%E6%96%B0-1">OTA更新</a><br>

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

<h1>!!警告!! !!請勿更新Library!!</h1><br>

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

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_12.png" width="600" height="270" alt="Open_Project"/><br/>

選擇platformIO資料夾，解壓縮完後的資料夾

點選src，開啟main.cpp

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_13.png" width="500" height="300" alt="開啟main_cpp"/><br/>

點選左下角"打勾圖示"開始編譯程式

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_14.png" width="500" height="100" alt="編譯"/><br/>

之後點選左下角"箭頭圖示"開始上傳程式

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_15.png" width="500" height="100" alt="上傳"/><br/>

# 使用方式
通電後開啟手機WIFI連接畫面，選擇ESP12_XXXX熱點

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_16.png" width="500" height="270" alt="WIFI連接畫面"/><br/>

輸入熱點密碼(預設:12345678)

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_17.png" width="500" height="270" alt="輸入熱點密碼"/><br/>

輸入完後，會自動轉跳畫面(如果沒有轉跳，請至瀏覽器輸入192.168.4.1)<br>
出現下方畫面後，按"設置WiFi"

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_18.png" width="350" height="450" alt="輸入熱點密碼"/><br/>

輸入SSID，Password，MQTTServer IP，完成後按"儲存"，完成設置

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_19.png" width="350" height="450" alt="輸入熱點密碼"/><br/>
  
# 資料文件

設置熱點名稱 : ESP_XXXX
設置熱點密碼 : 12345678
MQTT-Publish : tele/ESP12_XXXX<br>
MQTT-Subscriptions : cmnd/ESP12_XXXX<br>
ESP_XXXX -> XXXX是ESP8266的MAC後四碼，請記錄下來<br>
  
# 命令

led_on  ->開啟板上LED<br>
led_off ->關閉板上LED<br>
ip      ->查詢開發板IP<br>
On      ->開啟Relay<br>
Off     ->關閉Relay<br>
RESET   ->重置開發板<br>
Relay   ->查詢Relay狀態<br>
<h2>!!警告，RESET會重置WIFI連線資料以及MQTT資料!!</h2><br>
  
# 命令回傳值

對"cmnd/ESP12_XXXX"傳入命令"ip"<br>
"tele/ESP12_XXXX"輸出格式"{"Date":"xxxx-xx-xx xx:xx:xx","ip":"xxx.xxx.xxx.xxx"}"<br>
範例 : "{"Date":"2022-12-04 19:37:26","ip":"192.168.5.105"}"<br>

對"cmnd/ESP12_XXXX"傳入命令"Relay"<br>
"tele/ESP12_XXXX"輸出格式"{"Date":"xxxx-xx-xx xx:xx:xx","Relay_state":"Off"}"<br>
範例 : "{"Date":"2022-12-04 19:40:18","Relay_state":"Off"}"<br>
範例 : "{"Date":"2022-12-04 19:40:18","Relay_state":"On"}"<br>
!!此程式每五分鐘會自動輸出Relay狀態!!
  
# OTA更新

!!請使用PlatformIO來編譯!!<br>
編譯完後請至專案資料夾尋找.pio\build\d1_mini裡的firmware.bin<br>
開啟瀏覽器輸入設備IP/update(範例 : 192.168.5.105/update)開啟更新畫面，點選Firmware的選擇檔案，選擇firmware.bin<br>

<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_20.png" width="350" height="150" alt="OTA更新1"/><br/>
  
選擇完後點選"Update Firmware"，完成更新
  
<img src="https://github.com/Yue0911/ph-readme/blob/main/mqtt-smart-socket/IMG_21.png" width="350" height="150" alt="OTA更新2"/><br/>

  
  
