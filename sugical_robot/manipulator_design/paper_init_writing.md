# 论文撰写—一种应用于NOTES手术机器人的外骨骼式主操作台设计

## 摘要

这篇文章主要介绍一种应用于自然孔腔手术(NOTES)手术机器人的外骨骼式操纵台的设计。手术机器人系统整体采用主从式驱动映射策略，设计该结构的目的，力求保证手术医生手臂舒适、不影响手术医生手部自由运动的情况下，将手术医生手臂与手动作以直觉的方式映射到从端手术机器人。文章主要介绍该装置在结构上的创新性，舒适性，及其可行性。并从软件和硬件两个方面介绍了该装置在消除手术过程中手部颤抖的贡献；根据预期的直觉映射策略，推导主端驱动空间到从端构型空间的映射关系，并在仿真中验证了映射的可行性。



**3-8：结建立的动力学模型 of master console，我们使用我们的设备对手部生理震颤提出了评估，and address the hand tremor from both software and hardware perspectives** 

通过分析主从端的运动学模型，我们建立了合适的mapping strategy, which showcases the system's intuitive operation.

## Introduce

_____

​		自然孔腔内窥镜手术是一种借由内窥镜通过人体的自然孔腔到达病灶位置的外科手术，自1957年第一台光纤内窥镜成功完成诊断手术以来[1]，内窥镜技术得到广泛关注和发展，19世纪70年代人们开始设想借助内窥镜完成一些简易手术，1980年  Michael W.L. 首次对12名儿童和19名成人描述了“无需剖腹手术的胃造口术”(**这里改成英文**)[2]，验证了内窥镜手术的可行性，由此学者开始尝试使用内窥镜完成更复杂的手术，并于2005年被正式提出NOTES的概念[3]。相较于开放的剖腹手术，NOTES存在诸多优点，可以避免开放手术带来的伤口感染和切口疝的问题[4]，因此可以实现更快的术后恢复，减轻患者术后疼痛等问题。

​		早期的NOTES通过内窥镜及其配备的简易活检设备实现，只能进行简单活检和组织切除手术，为了完成更为复杂的手术，学者们设计了多种用于NOTES的手术机器人，它们通常具有相同的配置，集成摄像头的内窥镜主轴和从远端分支的两个手术臂 ，如  EndoSAMURAI[5]，Cobra[6], K-flex[7]。操作三角测量在柔性内窥镜手术中的灵巧检查和操作中起着至关重要的作用，该角度可以定义为两个仪器之间的远端姿势向量[8]，受限于结构，上述手术臂为单段连续体通常不具有良好的三角测量性，ANUBIScope[9], A flexible endoscopic surgical system[10] 将出口展开提供被动的三角测量性。

​		尽管NOTES手术机器人已经成了医疗设备领域的热门研究对象，但现有关于其操纵台介绍的文章较少。目前商业主流的操纵台，如达芬奇手术机器人[11]和Hugo[12]，其操作台均为6自由度，而大多NOTES手术机器人有4自由度，两者存在不兼容的情况。为了避免自由度冗余，早期类似于EndoSAMURAI和Cobra的手术机器人采用纯机械式的摇杆（[下图](https://link.springer.com/article/10.1007/s00464-012-2173-z/figures/1)），在实际手术中需要多个人配合操纵，过于简单的操纵台使得医生使用体验不佳，这样导致手术效率低，安全得不到保障。设计不良的界面会降低外科医生的人体工程学效果，并会阻碍机器人的接受度[13]，这一点在微创手术机器人设计中已经验证。   [KFLEX](https://onlinelibrary.wiley.com/doi/abs/10.1002/rcs.2078) 设计了一种简易的三联杆结构用于柔性臂的控制，可以实现更易让操纵者接收的“直觉控制”，但是结构设计过于简单，没有考虑人体工程学的问题，且没有考虑操作三角性的问题。

​	受前人工作的启发，我们提出了一种可以控制三角测量性的内窥镜双通道手术机器人模型，它由远近两段连续体组成，近端的偏转提供主动的三角测量性，同时可以增加手术时的灵活性，近端和远端协作完成手术动作；并根据该模型自由度设计了一种外骨骼式的手术机器人操纵台，可以利用人体手臂的其中5个自由度一对一控制手术机器人的关节，实现高效的直觉控制。在进行第一版样机测试时发现操纵者手部存在明显的生理抖动，为了改善抖动引起的末端震颤，我们在硬件和软件层面提出了改善方法；通过建立主端两端运动学模型，我们推导了从操纵台的驱动空间到末端执行器构型空间之间的映射关系，并在matlab中验证了映射关系的正确性。

​	本文的结构如下：在第二节阐述了主从两端自由度分布，以及对操作台的机械结构设计进行介绍；第三节主要关注在NOTES手术机器人在主端震颤过滤的东线；第四节推导了操纵台到柔性手术臂之间的运动学映射；第五节对全文进行了总结。



Flexible instruments with steerable heads and multi-instrument flexible devices are difficult to control manually using a single operator.[13](https://ieeexplore.ieee.org/abstract/document/9779312)

##  MECHANICAL DESIGN

### 主从端自由度配置

设想的从端手术机器人配置如下（Fig2(a)）：柔性机械臂搭载在双通道的内窥镜上，其近端连续体由同向的单元连接而成，在一对cable的驱动下可以朝两侧弯曲，以增大远端连续体之间的间距，提供较好的三角测量性；远端连续体相邻的单元正交排布，由两对cable驱动，具有两个方向偏转自由度，末端器械通过微型轴承连接在远端连续体上，具有绕轴旋转和开合的自由度。

主端操纵台的功能是精准捕捉并映射操纵者控制指令，力求满足人体工程学设计，避免影响手术医生上肢自由运动。合理的映射策略能够使得外科医生直观的进行操作，以减少学习曲线并提高手术的安全可靠性[]。在自由度布局上，末端执行器的自由度分布与人体手臂自由度[Fig.2(b)]极为类似，为了和人体手臂有较好的适配性，同时提供简单的映射策略，我们对操纵台的关节进行了初步的布局如下图Fig2(c)。

三者之间自由度的联系如下：操纵者将手肘“固定”在“搭载台”上以后，利用肩关节和手肘关节配合实现前后和内外翻转运动，并驱动操纵台“搭载台”下的两个正交的平动关节，对应手术机器人末端的前后伸缩，以及负责调控三角测量性近端连续体的偏转；手指握在pincher formation处，配合手腕的关节实现yaw,pitch, rolling 三个方向的运动，驱动操纵台前端三轴交于一点的“三连杆”对应的旋转关节，实现执行端前端连续体的两个方向偏转及其末端手术器械的绕轴旋转。



备注：

2-26：自己修改了一遍，没有经过gpt润色

### 设备实现

___

操纵台两个正交方向的平动均由两根平行的**导轨滑块**（MGW9，中国江苏）实现，相对于K-FLEX中单个导轨的设计，间隔一定距离的平行导轨可以避免手臂搭载时压力产生的倾覆力矩，每对导轨上的板子多采用铝合金材料，通过验证可以满足强度校验；导轨带来顺滑移动的同时，也带来了系统不稳定的问题，轻微的扰动即可导致末端出现预期以外的运动，因此在上述结构基础上，每个方向的平动都使用连接了**无刷电机**（KMTECH，中国上海），并使用齿条齿轮机构作为传动机构。相对于编码器，在每个关节处配置无刷电机的好处是，关节抗外界干扰能力更强，同时电机能够实现更为复杂的控制，使得操纵台不仅是一个运动采集机构，同时也能实现一些交互控制，例如较为成熟的变阻抗控制，使得平动的关节的可以灵活的改变。

与hand交互的三连杆，在原理上它与K-FLEX一样，但在此基础上我们做出了许多修改：首先我们额外增加了两条镜像连杆以及一些**“配重砝码**”，这样使得外部更美观，更重要的是增加结构的平衡性和稳定性，除此之外，更好的力量传递和控制是双边结构相对于单边结构的一个重要优势，双边结构可以实现分布式力量传递，即将力量从两侧均匀传递到目标区域，是可以让操纵者的操纵更加顺滑。

前人设计的“finger gripper”结构通常是搭载在rolling连杆上的一个钳子形状的gripper，一般操纵者使用大拇指和食指握住以控制末端器械如镊子的开合，这使得其他手指则处于蜷缩的空闲状态没有被利用，我们提出了一种创新的【pincher formation】结构(Fig3(b))，给剩余三个手指提供抓握的同时，将它们利用起来完成其它的任务。这是一个类似于手枪把手的结构，操纵者可以使用中指扣住【扳机】，控制一些功能的开关，如手术时所必须的冲洗，吸收积液，充气等操作，为了灵活切换上述功能，在把手下端设置了一个【轮盘】来切换上述功能。上述零件受力较小，因此我们使用光造型树脂作为材料并以3D打印的方式制作，这种材料具有高精度、表面光滑、细节丰富、打印速度快以及可用于复杂结构的优点。

上述整个结构可以简化为串联的五连杆，Serial kinematic configurations的优点包括：机械结构更简单，有利于制造并减少潜在故障点，从而减少所需的维护量[ ]，同时运动学模型和动力学模型较为简单，为后续人机交互控制降低难度。

无刷电机的内部集成了驱动板，使得整体结构更为紧凑，且驱动板内部集成FOC算法，仅需向其发送指令即可实现多种模式的控制，包括增量位置控制，绝对位置控制，速度控制和力矩控制；同时电机还集成了精度为18bit的绝对值磁编码器；我们使用STM32嵌入式单片机作为控制板，通过CAN通信协议控制和读取电机的状态。

Here are the translations for the phrases you provided, suitable for use in a table and aiming for a natural and concise English expression:

yaw link rotation



- 肘部前后运动: Elbow Flexion/Extension
- 肘部左右摆动: Elbow Abduction/Adduction
- 手腕左右偏转: Wrist Ulnar/Radial Deviation
- 手腕上下偏转: Wrist Flexion/Extension
- 手腕绕轴转动: Wrist Pronation/Supination
- 底座前后平移: Base Anteroposterior Translation
- 底座左右平移: Base Lateral Translation
- 手术臂伸缩: Surgical Arm Extension/Retraction
- 近端展开: **Proximal Unfolding**  双臂展开怀抱和对应的反义词用英语怎么说
- 远端左右偏转: Distal Lateral Deviation
- 远端上下偏转: Distal Vertical Deviation
- 手术器械绕轴转动: Instrument Rotation
- 手术器械开合: Instrument Articulation/Open-Close

These terms are succinct and are commonly used in descriptions of mechanical movements, particularly in the context of robotics and biomechanics.

## 手部震颤抑制

震颤过滤是所有遥操纵的手术机器人需要共同面对的问题，在设备性能优良的情况下，操纵者手部的震颤成为了震颤的主要来源。这种震颤被称为生理性震颤（Physiologic Tremor），一种生理性现象，正常情况下每个人都会经历的微弱的震颤或颤动。这种震颤的频率在8-12Hz之间，通常肉眼通常无法感知，但在手术的条件下，生理性震颤是不可忽视的不利因素，The trend towards the use of ‘minimally invasive surgery’ also tends to amplify tremor effects, due to the longer lever-arm action of typical laparoscopic instruments[3-1].

Tremor mitigation is a critical challenge in teleoperated surgical robotics. When the equipment performance is excellent, the tremor of the operator's hand becomes the main source of tremor. This tremor, known as Physiologic Tremor, is a physiological phenomenon that everyone normally experiences as a weak tremor or flutter. The frequency of this tremor is between 8-12Hz and is usually invisible to the naked eye. However, under surgical conditions, physiological tremor is a disadvantage that cannot be ignored. The tremor effects are amplified, due to the longer lever-arm action of typical laparoscopic instruments.



为了对surgeon的手部Physiologic Tremor进行evaluation，首先需要记录震颤活动，通常 accelerometry, electromyography (EMG), and other signals (such as force or gyroscopic measurements) are acquired, digitized through an analog-to-digital board and analyzed. 这种方法的问题是设备测量精度不够高，不能直接反应手部震颤的效果。在这里我们让surgeon手握"finger gripper"，通过记录各个关节的位置信息，结合master console的正向运动学，计算末端在空间中位置的变化，从而记录手部的震颤。



【图片1：初步震颤】【图片2：悬空15min后震颤结果】





为了减弱指端生理震颤为手术带来的的影响，首先我们引入了卡尔曼滤波算法，在软件层面上削弱震颤信号的波形

### 自适应卡尔曼滤波

单个电机的角度信号可以看作一阶系统，建立其状态方程及其对应的参数如下：
$$
\begin{cases}
x_k = x_{k-1} \\
        y_k = x_k
\end{cases}
$$

$$
F_k = 1; \quad H_k = 1; \quad G_k = 0; \quad u_k = 0;
$$

$$
公式1；
$$
借助卡尔曼滤波算法进行迭代，可以较为明显的平滑由于生理震颤产生的抖动信号；
$$
公式2
$$
卡尔曼滤波作为最为人知的滤波算法具有适应性强、有效地处理噪声和不确定性、计算效率高的优点[ ]。但是该算法存在两个最缺点，首先它像PID控制一样，需要对公式2中的参数Q与R进行手动调试；其次该算法无法兼顾精度和滤波效果，Q与R的比值会影响滤波结果，比值越小表示预测值的权重越大，最终结果抗干扰越强，但是会丢失一定精度；反之，比值越大越靠近标准值，滤波的效果越不明显。对前一个问题，前人已经提出了许多改进的自适应卡尔曼滤波算法，对于后一个问题，我们在这里提供了一种简单的模型，通过记录前后两次采样角度差值的方法，简易的区分操纵波形和噪声，并根据差值实时修改Q与R：

**简化后：**

卡尔曼滤波可以有效的处理噪声，并具有计算高效的优点[ ]，但是该算法也存在两个问题，一方面公式2中的参数Q和R需要通过经验调试，另一方面滤波在平滑噪声的抖动时也会使得正常的操纵动作失真，（Fig_）；我们提出了一种自适应的改进KF算法模型，可以有效的避免上述情况；
$$
公式3
$$
其中avg为经验值，通过记录多次噪声取平均值而得，因此diff 与avg的比值表示信号振幅的大小，较大时表示操纵波形，较小时为噪声。图---对比了传统卡尔曼滤波与改良后自适应卡尔曼滤波的效果，图中可以明显看到改良后滤波算法即避免了传统滤波算法引起的失真，又达到了消除抖动信号目的：由于操纵指令和震颤的幅度相差很大，印使用$\alpha$ 记录前后两次位置的差值，差值小表示抖动，通过减小Q和增大R增强滤波效果，反之差值大时避免滤波影响输入指令，对应模型的结果展示在图_ 中。

图

The angular signal from an individual motor is modeled as a first-order system, with its state equation and related parameters detailed subsequently.

Employing the Kalman filter algorithm iteratively allows for the noticeable smoothing of jitter signals induced by physiological tremors. Renowned for its adaptability, effective handling of noise and uncertainties, and computational efficiency, the Kalman filter, however, faces two significant limitations. Firstly, akin to PID control, it necessitates manual adjustment of parameters Q and R, as delineated in equation 2. Secondly, achieving a balance between precision and filtering efficacy proves challenging. The filtering outcome is influenced by the Q-to-R ratio, where a lower ratio signifies a greater emphasis on the forecast value, enhancing interference resistance but sacrificing accuracy. In contrast, a higher ratio approximates the standard value more closely but diminishes the filter's effectiveness. While numerous adaptive Kalman filter enhancements have been proposed to overcome the first limitation, we address the second by introducing a straightforward model. This model easily differentiates between control waveforms and noise by recording the angular difference between two successive samples, thereby allowing for the real-time adjustment of Q and R based on this discrepancy.

### 搭载式

生理抖动产生的一个原因是手部悬空[ref]。通过观察可以发现，相较于手臂悬空状态，手臂被托举时操纵者手指末端的抖动幅度和频率更小，因此商业微创手术机器人的操纵台大多都设计了小臂托衬结构，该设计的另外一个优点是缓解手术时手臂维持长时间悬臂的疲劳。我们通过采集两种状态下电机的角度信息，计算出操纵台末端位置信息，并将其可视化在图中。

【这里需要实物，实验和分析】

手臂长时间滞空导致的肌肉疲劳会加剧生理抖动，这也是为什么大多商业的微创手术机器人的操纵台配备了小臂托衬结构，这里我们设计了一个肘部托举结构，其作用除了托举操纵者手部，同时也作为一个“操纵杆”用于控制操纵器在正交导轨上的位置。为了防止操纵者在移动手肘的过程中不产生相对滑动导致脱落，这里设计了一个“紧固”结构，其工作原理如下：在操纵者将手肘搭载在“carrying disc”上后，在重力的压迫下，“carrying disc”随直线轴承向下运动，该运动由连杆传递到sliders，并通过连杆使一端固定的“four link”产生变形，该变形的最终结果是“elbow protector”向内收缩，从而加紧操纵者的肘部，当操纵者想脱离该结构时，将肘部竖直向上抽离即可。这样就做到了肘部在“穿戴”与“抽离”之间的自由切换。

有一个致命的问题是，目前第二代的样机仍在搭建中，虽然能通过肉眼很直观的察觉到托举结构对手部震颤的改善，但缺少严谨的实验和实验结果来论证该结论，但这个空缺会在短期内完善。



Muscle fatigue caused by the arm being suspended in the air for a long time will aggravate physiological jitter. This is why most commercial minimally invasive surgical robot consoles are equipped with a forearm support structure. Here we have designed an elbow support structure, whose function is in addition to lifting. The operator's hand also serves as a "joystick" to control the position of the manipulator on the orthogonal guide rail. In order to prevent the operator from relative sliding and falling off when moving the elbow, a "fastening" structure is designed here. Its working principle is as follows: after the operator places the elbow on the "carrying disc",  under the pressure from the gravity of arm, the "carrying disc" moves downward with the linear bearing. This movement is transmitted to the sliders by the connecting rod, and deforms the "four link" fixed at one end through the connecting rod. The final result of this deformation is that the "elbow protector" moves toward Contraction inward to tighten the operator's elbow. When the operator wants to escape from the structure, he can pull the elbow straight up and away. In this way, the elbow can be freely switched between "wearing" and "taking off".

A fatal problem is that the second-generation prototype is still under construction. Although the improvement of hand tremor by the lifting structure can be intuitively detected with the naked eye, there is a lack of rigorous experiments and experimental results to prove this conclusion. This vacancy will be completed shortly.



## mapping strategy

这一部分主要介绍从主端操纵台的驱动空间[theta 1 ... theta 5] 到从端构型空间的映射策略，也即在检测到操纵者输入的控制指令后，从端柔性臂应该调整到什么位型。在手术机器人领域，目前主流的主从映射策略是保持主从两端姿态和位置相同：通过主端正运动学计算目标位姿，再使用从端逆运动学求解从端驱动空间。但是由于目前结构为5自由度，**为欠驱动状态（**Underactuated），因此主流方法不适用。我们采取的映射策略是保证主从两端的姿态保持一致同时伸缩按比例缩放，实现较好的“直觉操纵”。为了简化映射的复杂度，我们采用解耦的方法，将整体映射策略分远近两段的子映射，这个方法是可行的，在保证每个子映射策略符合“直觉操纵”的情况下，整体依然符合“直觉操纵”。

Fig.3 显示了主从系统的integrated kinematic drawing。对于主端刚性连杆结构，我们沿用DH标准为每个关节配置了坐标系，并构建了对应的DH table；

对于从端柔性连续体，使用常规的DH会带来巨大的计算复杂度，这里我们采用更适用于连续体建模的常曲率模型[ ]。在常曲率模型中，使用ks描述连续体偏离轴心的偏转角度，使用phi描述因为两个正交偏转叠加后产生的绕轴转动角度。对于如近端单自由度的连续体，phi可以是视作0不变。

前面两个自由度的运动较为简单，且两个映射完全解耦，因此分别进行简单的线性映射即可：

主端console纵向平动与从端柔性臂的“伸缩“，以及主端横向的平动与柔性臂”近端偏转“的映射可以完全解耦，分别进行简单的线性映射即可：
$$
公式
$$
其中theta_max为近端连续体偏转的量程，dmax为导轨移动量程；

为了保证主端R-P-Y“三连杆”与近端连续体姿态相同，一种方法是保证两者末端在其各自base坐标系旋下描述姿态的转矩阵R相同。 该问题通过代数直接求解的方法不仅计算量大，同时还会存在无解的情况，因此这里引入几何法对其进行求解。首先我们描述一组Fig(  )中的运动：初始坐标系O经过绕y_0旋转θ_3和绕x_1旋转θ_4后形成坐标系O_2；另一方面，初始坐标系经过绕z_0旋转ϕ后形成坐标系O_1^a，再经过绕y_1^a旋转ks后得到坐标系O_2^a，观察两次坐标变换所得坐标系的z轴重合。实际上前者就是描述的三连杆转动yaw和rolling方向上关节对应的坐标变化，而后者是连续体在绳子驱动下偏转后产生的坐标变化，z轴重合代表两者末端朝向一致，不过两个坐标系在x-y轴平面上存在一个偏置(Fig)；

同样的，我们将图(a)中)O2 和 Oa2提取出来，构建新的几何关系。只需要求解上述两个空间夹角，即可得到了映射函数，对于这两个问题均可使用【三余弦定理】，这是一种通过构建投影求解空间夹角的方法，具体的求解过程在附件A中给出。
$$
公式
$$
由此可得最终映射关系：
$$
公式
$$

根据公式(9)推导的函数，我们使用matlab在同一个坐标系下分别绘制主从两端的坐标系Fig6(c)，符合我们的预期，也即z轴重合，x-y平面存在偏执，再结合公式(10-13)求解的x，得到Fig6(d)的结果——两个坐标系完全重合，证明映射的合理性。

## 结论

在这篇文章中，我们提出了一种可以提供主动三角测量性的内窥镜的手术机械臂模型，并设计了一种适配于该类型手术机器人的穿戴式操纵台。在调试的过程中发现末端存在较为显著的震颤，并提出了两种方法改善生理抖动产生的震颤，为了之后主从遥操作做准备，推导了主从之间的映射函数。在后续的工作中会对样机的实体进行迭代，并完成空缺的实验，人机交互的控制策略正在研究中，致力于研发精准且舒适的主端操纵台。





## Reference

[1] Rosin, R. D. (Ed.). (1993). *Minimal access medicine and surgery: principles and techniques* (Vol. 1). Scovill-Paterson.

[2] Gauderer, M. W., Ponsky, J. L., & Izant Jr, R. J. (1980). Gastrostomy without laparotomy: a percutaneous endoscopic technique. *Journal of pediatric surgery*, *15*(6), 872-875.

[3] Rattner, D., & Kalloo, A. (2006). ASGE/SAGES Working Group on natural orifice translumenal endoscopic surgery: October 2005. *Surgical Endoscopy and Other Interventional Techniques*, *20*(2), 329-333.

[4] Giday SA, Kantsevoy SV, Kalloo AN. Principle and history of natural orifice translumenal endoscopic surgery (NOTES). *Minim Invasive Ther Allied Technol*. 2006;15:373–377.

[5] Fuchs, K. H., & Breithaupt, W. (2012). Transgastric small bowel resection with the new multitasking platform EndoSAMURAI™ for natural orifice transluminal endoscopic surgery. *Surgical endoscopy*, *26*, 2281-2287.





[9] Dallemagne, B., & Marescaux, J. (2010). The ANUBIS™ project. *Minimally Invasive Therapy & Allied Technologies*, *19*(5), 257-261.

[10] Kobayashi, T., Lemoine, S., Sugawara, A., Tsuchida, T., Gotoda, T., Oda, I., ... & Kakizoe, T. (2005). A flexible endoscopic surgical system: first report on a conceptual design of the system validated by experiments. *Japanese journal of clinical oncology*, *35*(11), 667-671.





[2-1] Kuniholm, J. F., Buckner, G. D., Nifong, W., & Orrico, M. (2005). Automated knot tying for fixation in minimally invasive, robot-assisted cardiac surgery.





## 一些细节+ 最终调整

* 到底叫console好还是manipulator好





* [ ] 修改tremor部分
  * [ ] 文字修改
  * [ ] 绘制FK模型，编写绘制末端位置的脚本，通过实验收集数据，得到xyz3维度图像
  * [ ] 添加KF后的结果的图像
  * [ ] 
* [x] 
