Lanos 中文文档
======================================================================
本文档采用知识共享署名·相同方式共享 3.0 Unported 许可协议进行许可。<br>
反版权所有 (CC) 哆啦比猫(兰威举), 2010-2011.

简介
------------------------------------------------------------
Lanos 是一个 32 位不全保护模式非 UNIX 克隆的操作系统
(32-bit not-so-protected non-UNIX-clone OS)。Lanos 将
尽早实现实用功能（如，在完成屏幕管理模块后就立即实现了 printf）。
Lanos 将提供 OpenGL、数字音频(digital audio)、高分辨率、
鼠标/键盘/（可能还有）手柄驱动、多线程单进程
(single process with multi-threads)的支持。Lanos _可能_会提供
文件操作的支持，且所有应用程序（目前）必须硬编码(hard-coded)于内核。

Lanos 是一个给 hackers 的玩具。Lanos 可用于制作可引导实时（三维）动画
(bootable demoscene).

目录结构
------------------------------------------------------------
在 src/ 中（其中，带“·”的项目表示要先完成）：

 * · base/
 * · video/
 *   audio/
 * · misc/
 * · keyboard/
 *   mouse/
 * · include/
 *   gl/
 * · app/
 * · math/

