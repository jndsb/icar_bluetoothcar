/*哔哩哔哩：这是江宁，我在那里发布了很多教程，当然你也可以在各大音乐平台搜JNing江宁，那也是我*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BluetoothSerial.h>

// 定义蓝牙对象
BluetoothSerial SerialBT;

#define M1A 27 // 左侧电机正转
#define M1B 26 // 左侧电机反转
#define M2A 25 // 右侧电机正转
#define M2B 33 // 右侧电机反转
#define scl 19
#define sda 18

// 新建iic对象以及显示屏对象
TwoWire I2Cone = TwoWire(0);
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &I2Cone);
// 定义遥控车的状态变量
int state = 0;      // 0: 停止，1: 前进，2: 后退，3: 左转，4: 右转
int last_state = 0; // 记录上一次的状态

void setup()
{
  // 设置电机引脚为输出模式
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);

  I2Cone.begin(sda, scl, 400000);
  // 初始化显示屏
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // 清屏
  display.clearDisplay();
  // 设置字体大小
  display.setTextSize(2);
  display.setTextColor(INVERSE);
  // 初始化蓝牙串口，并设置设备名称为"iCar"
  SerialBT.begin("iCAR");
  Serial.begin(115200);
}

// 定义遥控车的动作函数
void stop() // 停止
{
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);
}

void forward() // 前进
{
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);
}

void backward() // 后退
{
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, HIGH);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, HIGH);
}

void left() // 左转
{
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, HIGH);
  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);
}

void right() // 右转
{
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, HIGH);
}

void loop()
{
  display.setTextColor(WHITE); // 开像素点发光
  display.setCursor(0, 19);
  display.print("I'm iCar");
  display.display();
  // 如果有数据可读
  if (SerialBT.available())
  {
    // 读取一个字节的数据，并转换为整数
    state = SerialBT.read() - '0';
    // 如果和上一次的状态相同，就停止遥控车
    if (state == last_state)
    {
      stop();
    }
    // 否则，更新状态并执行相应的动作
    else
    {
      last_state = state;
      switch (state)
      {
      case 0: // 停止
        stop();
        break;
      case 1: // 前进
        forward();
        break;
      case 2: // 后退
        backward();
        break;
      case 3: // 左转
        left();
        break;
      case 4: // 右转
        right();
        break;
      default: // 其他情况，停止
        stop();
        break;
      }
    }
  }
}