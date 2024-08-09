# Summer_log

目前的工作是新一版的主从控制实现，映射公式只差从常曲率关节空间到驱动空间了

硬件方面；角度都读取，也能够发送，下一步，将映射后的数据发过去，而不是电机驱动空间

* [x] 在c#中实现matlab已有的功能，将其整合到原来的project，有时间优化一下原来project，[参考](https://github.com/SJTU-RoboMaster-Team/Electronic-control-code-specification)
* [x] debug
* [ ] 主从通讯调试
* [ ] 两种模式==> 增量模式和绝对模式

## 主从映射公式推导

推导了【朝向和位置】满足【直觉映射】的公式，具体内容见

[mapping2.0](E:\GitHub\Mac_win\Mac_Win\sugical_robot\mapping_strategy\mapping_strategy2.0.md)

## 完善主从通讯

[嵌入式调试手册](E:\GitHub\Mac_win\Mac_Win\sugical_robot\EE_control\embedded_testing_log)