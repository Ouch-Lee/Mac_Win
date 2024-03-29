		自然孔腔内窥镜手术是一种通过内窥镜经人体自然孔道到达病变部位进行的外科手术。自从1957年首台光纤内窥镜成功进行诊断手术以来，内窥镜技术得到了广泛的关注和发展。20世纪70年代开始，人们开始设想利用内窥镜进行一些简单的手术。1980年，Michael W.L.首次描述了一种“无需腹部切口的胃造口术”的方法，证实了内窥镜手术的可行性。这一里程碑验证了内窥镜手术的可行性，从而激发了学者们尝试更复杂手术的兴趣，并于2005年正式提出了NOTES的概念。相较于传统的开放剖腹手术，NOTES具有诸多优点，例如能够避免开放手术带来的伤口感染和切口疝等问题，从而实现更快的术后康复，减轻患者术后疼痛等不适。

​		在早期，NOTES主要通过内窥镜及其配备的简易活检设备实现，只能进行简单活检和组织切除手术。为了完成更为复杂的手术，学者们开始设计用于NOTES的多种手术机器人。这些机器人通常具有相似的配置，包括集成摄像头的内窥镜主轴和从远端分支出的两个手术臂，如EndoSAMURAI，Cobra，K-flex等。在柔性内窥镜手术中，操作三角测量起着至关重要的作用，它可以定义为两个仪器之间的远端姿势向量。然而，受限于结构，上述手术臂通常为相隔很近的单段连续体，不具备良好的三角测量性。因此，诸如ANUBIScope和A flexible endoscopic surgical system等系统通过出口展开来提供被动的三角测量性。
​		尽管NOTES手术机器人已经成为医疗设备领域的热门研究对象，但关于其操作台的介绍文章相对较少。目前，商业主流的操作台如达芬奇手术机器人和Hugo等均具有6自由度，而大多数NOTES手术机器人只具备4自由度，导致两者之间存在不兼容的情况。为了避免自由度冗余，早期类似于EndoSAMURAI和Cobra的手术机器人采用了纯机械式的摇杆操作，然而在实际手术中需要多个人配合操纵，过于简单的操作界面使得医生使用体验不佳，从而影响手术效率和安全性。设计不良的操作界面会降低外科医生的人体工程学效率，并可能阻碍机器人的接受度，这一点在微创手术机器人设计中已经得到验证。KFLEX设计了一种简易的三联杆结构用于柔性臂的控制，旨在实现更容易接受的“直觉控制”，然而该结构设计过于简单，未考虑到人体工程学问题，也未解决操作三角性的难题。

​		受到前人工作的启发，我们提出了一种能够控制三角测量性的内窥镜双通道手术机器人模型。该模型由远近两段连续体组成，近端的偏转提供主动的三角测量性，同时增加了手术的灵活性，使得近端和远端可以协同完成手术动作。根据该模型自由度的设计，我们开发了一种外骨骼式的手术机器人操作台，可以利用人体手臂的其中5个自由度一对一地控制手术机器人的关节，实现高效的直觉控制。在进行第一版样机测试时，我们发现操纵者手部存在明显的生理抖动，为了改善抖动引起的末端震颤，我们提出了硬件和软件层面的改进方法。通过建立主端和两端的运动学模型，我们推导了从操作台的驱动空间到末端执行器构型空间之间的映射关系，并在Matlab中验证了映射关系的正确性。

​		本文的结构安排如下：第二节介绍了主从两端自由度分布，以及操作台的机械结构设计；第三节着重讨论了NOTES手术机器人主端震颤过滤的方法；第四节推导了操作台到柔性手术臂之间的运动学映射关系；第五节对全文进行了总结。



## 2

