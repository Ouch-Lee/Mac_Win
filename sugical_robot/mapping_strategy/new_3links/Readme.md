# Readme

* get_continuum_T: 求单个连续体末端相对于base的其次变换矩阵
* extended_two_links: 用于求解添加extended坐标系后二连杆的T（好像）
* check_two_orien: 看起来像在验证没有添加delta_x 前的映射
* check_paper_DH: 似乎添加delta_x后的映射，运行前需要先运行extended_two_links
* my_DH_matrix ： 用于求解主端运动学的其次变换矩阵







最终结果在 "Show rotation.m" 文件中展示

在运行该文件前，需要先运行“extended_two_links”+“check_paper_DH”







### STM32串口数据处理

* 传输的数据太多了，所以先进行了简单的采样处理 sampling_array 函数
* get_end_position 传入采样后的数据
  * 需要处理一下角度
  * get_one_P中计算全是整数的问题，将sym计算得到的数换到另外一个T_matix里面就行
  * 

