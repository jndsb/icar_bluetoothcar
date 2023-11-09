    材料准备
这里有详细图文讲解：https://www.bilibili.com/read/cv27607507/

软件篇

    做到这里而且能亮的话，恭喜你，已经完成了硬件上的工作，现在开始软件部分

我在这篇教程已经介绍过如何配置platformio

这个代码我是在platformio写的，所以本代码就在platformio打开

打开方法也在这个教程的软件篇的platformio部分介绍过，就不重复说了

我们介绍一下代码

在代码中我也尽量注释每一行代码


    #define M1A 27 // 左侧电机正转

    #define M1B 26 // 左侧电机反转

    #define M2A 25 // 右侧电机正转

    #define M2B 33 // 右侧电机反转

    #define scl 19

    #define sda 18


这几句是定义引脚输出，后面的数字是定义的引脚，如果有需要接到其他引脚，可以在这里修改


     SerialBT.begin("iCar"); // 初始化蓝牙串口，并设置设备名称为"iCar"


这句括号里面的英文字母可以改成自己喜欢的蓝牙名字，后面手机控制的时候可以找到你设置的名字


     Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &I2Cone);


128, 64指的是oled的屏幕是128x64的尺寸，如果你是其他尺寸的OLED也可以改成其他尺寸


     display.print("I'm iCar");


这句就是在oled中你想让他显示的文字，当然当然，你也可以让oled显示图片，但是我最近心思花在两款小车上，就暂时不弄这个了，感兴趣的同学可以自己找教程学。。。

