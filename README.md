# F407-LVGL-Watch

# 1.Preface

本项目是基于STM32F407ZGT6开发板的智能手表~~（大号款）~~，中间件是**hal、rtos、lvgl**，功能目前包括日历、计算器、计步、闹钟、蓝牙通信、NFC（待实现）、环境光测量、温湿度测量、血氧检测等，目前手头并没有手表的一些测量传感器，更多功能待开发和完善。后续如有机会会添加气压测量、心率测量、指南针、蓝牙升级等等功能。

<img src="D:\2024710Embeded Learn\My FreeRtos\F407-LVGL-Watch\assets\IMG_20241012_17245195.jpeg" alt="IMG_20241012_17245195" style="zoom: 25%;" />

Pending Task

- [ ] 闹钟提醒
- [ ] NFC功能
- [ ] 蓝牙OTA
- [ ] 血氧测量
- [ ] 音乐功能

# 2.Designing scheme

## 1.Hardware bom

- stm32f407zgt6

- 2.8 inch TFT (ili9431)
- mpu6050
- rc522
- key
- led
- hc06
- dth11/AHT20
- temt6000
- at24cxx
- buzzer
- MAX03201

## 2.Software

基于stm32cubeMx的rtos（cmsis-os）

# 3.Function design

## 1.~~alarm sort（插入排序（旧方法，已摒弃））~~

下面通过**7:00、8:00、6:00 和 10:00** 的顺序逐步讲解**插入排序**链表的过程

假设每个节点的 `alarmTotalTime` 是它对应时间（以分钟计算）：

- **7:00 AM** = 420 分钟
- **8:00 AM** = 480 分钟
- **6:00 AM** = 360 分钟
- **10:00 AM** = 600 分钟

**1.初始化总链表**

```
Node1 (7:00 AM = 420) -> Node2 (8:00 AM = 480) -> Node3 (6:00 AM = 360) -> Node4 (10:00 AM = 600) -> NULL
```

**2.目标链表**

```
Node3 (6:00 AM = 360) -> Node1 (7:00 AM = 420) -> Node2 (8:00 AM = 480) -> Node4 (10:00 AM = 600) -> NULL
```

**3.步骤详解**

 **3.1 检查链表状态**

```
   /*if list is null or only one element in list, no need to sort*/
    if (*head == NULL || (*head)->next == NULL)
    {
        return 1;
    }
```

 **3.2 第一步sorted必是空的**

`current` 指向 `Node1`，即 7:00 AM (420 分钟)。

因为 `sorted` 链表是空的，`Node1` 被直接插入到 `sorted` 链表中。

```
if (sorted == NULL || current->alarmTotalTime < sorted->alarmTotalTime) {
    current->next = sorted;
    sorted = current;
}
```

`current->next` 是 `Node1->next`,此时`sorted`是`NULL`,调整后

```
Node1 (7:00 AM = 420) -> NULL
```

**3.3 处理第二个节点**

`current` 指向 `Node2`，即 8:00 AM (480 分钟)。

保存 `Node3`（6:00 AM = 360 分钟）为 `nextNode`，以免丢失未排序的剩余链表。

`Node2` 的时间比 `Node1` 的时间晚，因此我们需要将 `Node2` 插入到 `Node1` 的后面。

```
AlarmNode *temp = sorted;
while (temp->next != NULL && temp->next->alarmTotalTime < current->alarmTotalTime) {
    temp = temp->next;
}//上面进了就退出，因为sorted只有一个7，后面是NULL
current->next = temp->next;把8的next指向了7的NULL
temp->next = current;7的原来的NULL被指向了8
```

`temp` 指向 `sorted` 链表的头部（即 `Node1`）。

由于 `Node1` 的时间比 `Node2` 小，所以 `while` 循环结束。

将 `Node2` 插入到 `Node1` 后面，更新指针。

**3.4 处理第三个节点**

`current` 指向 `Node3`，即 6:00 AM (360 分钟)。

保存 `Node4`（10:00 AM = 600 分钟）为 `nextNode`，以免丢失未排序的剩余链表。

`Node3` 的时间比 `sorted` 链表的所有节点（`Node1` 和 `Node2`）的时间都早，需要将 `Node3` 插入到 `sorted` 链表的最前面。

```
if (sorted == NULL || current->alarmTotalTime < sorted->alarmTotalTime) {
    current->next = sorted;//将当前6的next指向sorted
    sorted = current;然后sorted的指针指向6的头
}
```

**3.5 处理四个节点**

同3.3

## 2.Calculator

![image-20241010195622321](D:\2024710Embeded Learn\My FreeRtos\F407-LVGL-Watch\assets\image-20241010195622321.png)
