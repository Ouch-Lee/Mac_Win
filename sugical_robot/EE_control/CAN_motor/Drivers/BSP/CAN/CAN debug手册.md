# CAN debug手册

can_1-20 是基于学长提供代码修改的，可以成功向电机发送连续指令，但是无法接收消息；因此进行备份，回退到之前正点原子代码







## can滤波器

滤波器有很多参数，说实话看不懂，等哪天真的懂了再回来看这个吧

在CAN通信中，过滤器(Filter)是用于过滤接收的CAN消息的重要组件。通过配置CAN过滤器，你可以选择只接收特定标识符(ID)或一定范围的CAN消息，从而过滤掉其他不需要的消息。以下是一些与CAN过滤器相关的重要参数：

1. **过滤器模式 (Filter Mode):**
   - CAN过滤器可以工作在两种模式下：
     - **单个标识符模式 (Single Identifier Mode):** 只接收特定的标识符的CAN消息。
     - **范围标识符模式 (List Identifier Mode):** 接收标识符在一个范围内的CAN消息。

2. **标识符 (Identifier):**
   - 对于单个标识符模式，你需要配置一个具体的标识符，只有带有该标识符的CAN消息才会被接收。
   - 对于范围标识符模式，你需要配置一个范围，只有在该范围内的标识符的CAN消息才会被接收。

3. **IDE (Identifier Extension):**
   - 标识符扩展位，表示标识符的类型。在CAN2.0A协议中，标准标识符占用11位，而扩展标识符占用29位。IDE为0时，表示标准标识符；IDE为1时，表示扩展标识符。

4. **RTR (Remote Transmission Request):**
   - 表示是否接收远程帧。远程帧用于请求其他节点发送数据帧。

5. **掩码 (Mask):**
   - 对于单个标识符模式，掩码用于匹配标识符的每一位。只有与掩码相与的结果与配置的标识符相等时，CAN消息才会被接收。
   - 对于范围标识符模式，掩码用于匹配标识符的一部分，从而确定范围。

6. **过滤器编号 (Filter Bank Number):**
   - CAN控制器通常有多个过滤器（过滤器银行）。你需要选择使用哪个过滤器银行来配置过滤器。

具体例子分析：

这段代码是配置一个CAN过滤器的相关参数，具体参数配置如下：

1. **FilterBank (过滤器银行):**
   - `sFilterConfig.FilterBank = 0;`
   - 表示使用过滤器银行0。对于CAN1，STM32通常支持多个过滤器银行，你可以根据需求选择合适的银行。

2. **FilterMode (过滤器模式):**
   - `sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;`
   - 表示过滤器工作在标识符掩码模式。在这个模式下，标识符和掩码进行按位与运算，匹配结果用于过滤CAN消息。

3. **FilterScale (过滤器规模):**
   - `sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;`
   - 表示过滤器使用32位的标识符和掩码。

4. **FilterIdHigh 和 FilterIdLow (标识符):**
   - `sFilterConfig.FilterIdHigh = 0x0000;`
   - `sFilterConfig.FilterIdLow = 0x0000;`
   - 标识符的高位和低位。在这里设置为0x0000，你可能需要根据你实际的CAN标识符来设置。

5. **FilterMaskIdHigh 和 FilterMaskIdLow (掩码):**
   - `sFilterConfig.FilterMaskIdHigh = 0x0000;`
   - `sFilterConfig.FilterMaskIdLow = 0x0000;`
   - 控制标识符的掩码的高位和低位。同样，你可能需要根据实际需求设置。

6. **FilterFIFOAssignment (过滤器FIFO分配):**
   - `sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;`
   - 表示匹配的CAN消息将被分配到FIFO0。在CAN模块中，FIFO用于缓存接收到的CAN消息，这里将其分配到FIFO0。

7. **FilterActivation (过滤器激活):**
   - `sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;`
   - 表示启用过滤器。只有当这个参数设置为 `CAN_FILTER_ENABLE` 时，过滤器才会生效。

8. **SlaveStartFilterBank (从属起始过滤器银行):**
   - `sFilterConfig.SlaveStartFilterBank = 14;`
   - 如果你在CAN控制器中使用了多个过滤器银行，并且配置了从属过滤器银行，该参数表示从属过滤器银行的起始编号。在这里，表示从属过滤器银行从14开始。

请确保以上参数的设置符合你的具体通信需求和CAN网络配置。在实际应用中，你可能需要根据你的CAN消息的标识符和掩码进行更准确的配置。