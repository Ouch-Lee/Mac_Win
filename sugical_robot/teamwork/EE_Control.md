# EE_Control

主端需要发送一系列信号到从端，包括：

* 五个角度
* 开合信号



关于五个角度，首先需要定义初始位置以及正负号（这个很好定义，基本上确定了，最好写一个文档规定好，方便团队之间看得懂）；一个初始位置（初始位置好定义，但是希望每次上电的时候能够自动回到初始位置）

* 如何让电机上电就达到设定的初始位置；首先电机肯定可以位置模式，电机的位置控制有两种模式，一种是绝对位置控制，（绝对位置还分四种，这里稍微记录一下，multi loop 角度可以超过360°，而且可以正反转；但是single loop只能在360°以内，且只能正转，不推荐；1和2的区别就是可以调速度，推荐2），另一种就是增量控制；可以先物理标记电机的零位，使得零位和