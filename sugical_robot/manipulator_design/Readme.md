

## 论文说明

2-Technical review of the da Vinci surgical telemanipulator：达芬奇手术机器人专利

3-A novel pich grip design：设计了一种权衡手指捏握和手柄的grip

4-DaVinCi_patent：达芬奇手术机器人专利

5-hand_fitague_research：很早的一篇文章（1979），研究了手部在几种状态下肌肉震颤情况，量化的方式是通过记录什么肌电图

6- 一篇解剖学相关的文章，论述了手部的两种姿态

7- 一篇关于pincher grip的专利

8-一篇介绍仅紧凑master manipulator设计的论文

9-[哈工大一遍优化主端手术机器人的文章](https://ieeexplore.ieee.org/abstract/document/8848374)

10-[稍后再看](https://link.springer.com/article/10.1186/s12938-018-0601-6?fromPaywallRec=false)

11-[一篇把gripper讲明白了的IROS](https://ieeexplore.ieee.org/document/8202159)

12-[还有专门研究gripper的？](https://www.researchgate.net/publication/271547893_Effect_of_load_force_feedback_on_grip_force_control_during_teleoperation_A_preliminary_study)

13-[很捞但至少它是真的做gripper的](https://ieeexplore.ieee.org/abstract/document/7177760)

14-[一篇和我做的很像的all-joint-control的master device](https://link.springer.com/article/10.1007/s11548-016-1352-0)

15-[一种圆柱体gripper？](https://ieeexplore.ieee.org/abstract/document/7759149)

16-[4DOF抓手力反馈研究](https://ieeexplore.ieee.org/abstract/document/4145189)

17-[MIS抓手力反馈实现](https://ieeexplore.ieee.org/document/10058553)

18-[自己做一台达芬奇](https://ieeexplore.ieee.org/abstract/document/6907809)

19- [master_console_review.pdf](master_console_review.pdf) 

### combined-grip-handle grips design

这篇文章讨论了目前主流的两种grips——pinch类型（以达芬奇手术机器人为代表）和power类型（以sigma7）为代表分别存在优缺点，前者精度更高，但是使用时更加费力；后者则刚好相反，因此作者通过一些设计权衡两者之间的优缺点

首先提出了将pinch安装在handle上的概念，通过一个转动副和一个移动副连接（被动的没，相当于一个调节的作用），通过设计对照试验，验证了有这个自由度好一点

整篇论文大部分时间都在介绍实验以及实验结果，通过多组对照组，得出时间相关的结论



### Prehensile Movement of HUman hand

该文研究了人类手部的可动性能力，包括不同类型的握持方式和手腕的运动。该文的主要结论是，手部的握持方式和手腕的运动是根据任务目标来选择的，任务的要求可以分为力量和精度两个方面，而手部的可动性能力可以满足这些任务的要求。此外，该文还指出，人类手部的简单和通用性质是其进化的结果，而过度专门化会限制手部的其他可能用途。





## Hamlyn CRM: a compact master manipulator for surgical robot remote control

introduce：该部分先介绍了主流手术机器人主要由三部分组成：a master control console with interactive manipulators, a slave surgical robot with articulated instruments and a feedback system with vision and other sensing modalities.；之后介绍了主从结构的特点，但是不够紧凑，所以这篇文章用了传感器融合技术；同时重点介绍了他们手术机器人模型的映射策略

* 机械结构

  通过matlab的运动简图可以看出大致原理，三个正交轴实现手朝向的变化，一个线性轴+万向节实现空间位置改变

* 运动学

  运动学较为简单

* 传感器融合

  * 两个imu+两个霍尔传感器
  * 如何进行处理传感器数据

* 末端添加光标，结合NDI光学跟踪系统验证末端精度

* 主从映射策略

  * 主从系统那个图做的很好，很具有借鉴价值
  * 所有传感器信息使用到了ROS发布
  * 介绍了 主-视觉坐标系-从坐标系之间的变化（由于还没有研究视觉坐标系，这里先跳过）
  * 映射模式：位置模式采用P模式，姿态采用绝对（直觉映射）和增量控制两种模式，两者各有优势
  * 

  

## 11-Master manipulator designed for highly articulated robotic instruments in single access surgery

**introduce**：因为主从机器人的性能很大程度取决于master device 的性能，这个设计是为了解决工作空间不匹配，以及缺乏重要关节被限制的信息（可能他就是想说明同构关节的好处，能够让操纵者知道哪个关节受到了限制）；关节处设计一个力传感器主意挺不错，可以通过力的方向判断运动方向，结合电机辅助操纵者运动

introduce: 先介绍了手术机器人主从系统的被广泛应用的原因；后面介绍为什么要注重主端的设计：

An advanced slave system composed of highly dexterous instruments will ultimately not perform to its full potential if paired with an inadequate master system.

然后提出目前主流的手术机器人都是基于task space去设计，这样的缺点是 mismatch ，以及一些缺点

所以,the use of a dvice-specific master manipulator commanding the slave robot is **joint space** can be an attactive alternative。

后面介绍了几种joint-control的主端设备，但是缺点竟然是关节都是被动的？

**manipulator design:**

具体介绍了机械结构

**Workspace Analysis：**

绘制了主从工作空间的灵活程度（我是不是应该也分析一下？

Control system：

* 为了提示操纵者每个关节快到边界了，添加一些阻力
* 自身重力补偿
* 摩擦力补偿，这个等到自己要做的时候再仔细的看



## 12-研究gripper握力的文章

这篇会议论文刚好就是我现在在做的东西，可以带着critical thinking的眼观来审视这篇论文

文章主要想解决的问题是目前手术机器人的抓取严重依赖视觉反馈，力太大夹伤了，力太小又容易脱落。所以这篇文章就是研究如何控制握力

之前的工作是证明人手在抓取时手指的窝里和手上的载荷相关；视觉仅能进行预估，不如触觉准确；还有一些别人做的实验，说明平移的反馈了不如抓取的反馈力，这不是废话吗



## 16

1. **研究目的**：文章旨在确定在执行远程操作任务时，握力反馈与笛卡尔（平移）力反馈对操作者的影响。
2. **系统开发**：研究者开发了一个系统，为3自由度（DOF）的Phantom触觉设备主机增加了额外的握力反馈DOF，并且在Phantom触觉设备从机的每个“手指”上增加了6-DOF力/扭矩传感。
3. **实验设计**：用户在执行一个软性插孔任务时，会接触到不同的力反馈条件：(1) 全力反馈，(2) 仅平移力反馈，(3) 仅握力反馈，以及 (4) 无力反馈。实验结果显示，在增加握力反馈的3-DOF远程操作器中，平移和握力的施加水平是解耦的，这可能是由于内部和外部手部力的动力学是解耦的。
4. **远程操作器的挑战**：当前的远程操作器，包括手术远程操作器，并不向用户提供完整的力反馈。力传感器的尺寸、消毒和生物相容性限制了在手术环境中使用从机器上完整的力感应的可行性。
5. **实验方法**：五名右手受试者使用4-DOF远程操作器执行简单的操作任务，即抓取一个矩形泡沫“插孔”并将其插入泡沫块中的矩形孔中。实验中提供了四种不同的力反馈条件，每种条件都由受试者随机顺序重复五次。
6. **实验结果**：方差分析（ANOVA）表明，力反馈显著影响平均施加的平移力和平均施加的握力（p < 0.0001），但对完成任务的时间没有显著影响（p = 0.144）。实验不支持假设1和假设2，即平移力反馈不会显著影响施加的握力，反之亦然。
7. **结论**：文章提出了一个使用两个Phantom触觉设备的4-DOF远程操作器，该设备具有可附加的夹持机构，能够提供4个DOF的力反馈。研究表明，在没有提供力反馈的DOFs中，平移力反馈和握力反馈在调节力的能力上是解耦的。在需要最小化Cartesian力反馈和握力反馈的情况下，显然需要全反馈。
8. **未来工作**：未来的研究将包括对能量观测器和环境建模的研究，以减少部分力反馈对用户的负面影响，并确保具有传感器/执行器不对称性的远程操作器的稳定性。

文章的研究对于理解和改进远程操作器，特别是在手术远程操作领域的力反馈设计具有重要意义。



### 商用手术机器人

根据搜索结果，以下是一些国外与达芬奇手术机器人类似的腹腔镜手术机器人：

1. **图迈®腔镜手术机器人系统**：由上海微创医疗机器人（集团）股份有限公司研发，已获得欧盟CE认证，可用于泌尿外科、普通外科、胸外科、妇科内窥镜手术。该机器人具备力觉感知呈现组件、多层安全防护架构和先进的成像系统，提供10倍光学放大的高清视野，实现裸眼3D成像 1。
2. **MIRA 微型手术机器人**：由Virtual Incision Corporation推出，是首个用于腹腔镜手术的微型机器人，重量仅有900克，通过肚脐内的单个切口完成手术。MIRA平台专注于微创结直肠和下消化道手术，具有一次性末端执行器仪器、双极抓手和单极剪刀，以及柔性尖端机器人相机 2。
3. **美敦力的Hugo**：美敦力公司推出的Hugo手术机器人，获得CE批准上市，专为泌尿科和妇科手术设计。Hugo是一个模块化的多象限手术平台，结合了腕式器械、3D可视化和Touch Surgery Enterprise，旨在降低成本和使用障碍，提高外科手术机器人的普及率 9。
4. **Medrobotics公司的Flex Robotic System**：该系统可以导航接近180度的路径到达具有挑战性的手术目标，外科医生可以从稳定的手术平台部署3毫米铰接器械，扩大执行手术范围。该系统已于2014年获得欧洲CE标识，2015年获得FDA批准 2。
5. **TransEnterix公司的Senhance数字腹腔镜手术系统**：具有压力感知和触觉反馈系统，通过压力警报增强医生的感知。该系统在欧洲和日本获批上市，并已提交FDA审查 2。
