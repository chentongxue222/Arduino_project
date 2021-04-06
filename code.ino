#include <DS1302.h>   //DS1302头文件
#include <Wire.h>     //Wire头文件
#include <LiquidCrystal_I2C.h> //引用I2C通讯的LCD1602库
int sensonpin=5;   //定义红外传感器引脚
DS1302 rtc(2, 3, 4); //对应DS1302的RST,DAT,CLK
LiquidCrystal_I2C lcd(0x27,16,2);//设置LCD1602设备地址，一般为0x3F、0x20、0x27，可以查看硬件手册
char buf1[50];  //定义字符1
char buf2[50];  //定义字符2
void initRTCTime(void)//初始化RTC时钟
{
  rtc.writeProtect(false);   //关闭写保护
  rtc.halt(false);           //清除时钟停止标志
  Time tt(2021, 1, 22, 22, 34, 30, 6); //创建时间对象，参数7为星期数据，周日为1，周一为2以此类推
  rtc.time(tt);//向DS1302设置时间数据
}

void printTime()//打印时间数据
{
  Time tim = rtc.time(); //从DS1302获取时间数据
  snprintf(buf1, sizeof(buf1), "%04d-%02d-%02d",tim.yr, tim.mon, tim.date);   //字符1为年月日数据
  snprintf(buf2, sizeof(buf2), "%02d:%02d:%02d",tim.hr, tim.min, tim.sec);    //字符2为时分秒数据
  Serial.println(buf1);   //串口打印数据
  Serial.println(buf2);
}
void setup() 
{
  Serial.begin(9600);   //设置串口波特率
  pinMode(sensonpin,INPUT_PULLUP);
  lcd.init();           // 初始化LCD
  lcd.backlight();      //设置LCD背景等亮
  initRTCTime();
  //新模块上电需要设置一次当前时间，
  //下载完成后需屏蔽此函数再次下载，否则每次上电都会初始化时间数据

}

void loop()
 {
  printTime();    //打印时间子函数
  if(digitalRead(sensonpin)==LOW)
  {
    lcd.backlight();
    lcd.setCursor(0,0);  //设置显示位置
    lcd.print(buf1);     //输出字符
    lcd.setCursor(0,1);
    lcd.print(buf2);  
  }
  else if(digitalRead(sensonpin)==HIGH)
  lcd.noBacklight();

}