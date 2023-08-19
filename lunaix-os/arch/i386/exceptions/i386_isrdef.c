/* Generated from i386_isrdef.c.j2. Do NOT modify */

#include <lunaix/types.h>
#include <sys/i386_intr.h>

#define IDT_INTERRUPT 0x70
#define KERNEL_CS 0x8
#define IDT_ATTR(dpl, type) (((type) << 5) | ((dpl & 3) << 13) | (1 << 15))
#define IDT_ENTRY 256

#define DECLARE_ISR(iv) extern void _asm_isr##iv();

#define ISR_INSTALL(idt, iv, isr, dpl)                                   \
    _idt[iv] = ((ptr_t)isr & 0xffff0000) | IDT_ATTR(dpl, IDT_INTERRUPT); \
    _idt[iv] <<= 32;                                                     \
    _idt[iv] |= (KERNEL_CS << 16) | ((ptr_t)isr & 0x0000ffff);           \

u64_t _idt[IDT_ENTRY];
u16_t _idt_limit = sizeof(_idt) - 1;

DECLARE_ISR(0)
DECLARE_ISR(1)
DECLARE_ISR(2)
DECLARE_ISR(3)
DECLARE_ISR(4)
DECLARE_ISR(5)
DECLARE_ISR(6)
DECLARE_ISR(7)
DECLARE_ISR(8)
DECLARE_ISR(9)
DECLARE_ISR(10)
DECLARE_ISR(11)
DECLARE_ISR(12)
DECLARE_ISR(13)
DECLARE_ISR(14)
DECLARE_ISR(15)
DECLARE_ISR(16)
DECLARE_ISR(17)
DECLARE_ISR(18)
DECLARE_ISR(19)
DECLARE_ISR(20)
DECLARE_ISR(21)
DECLARE_ISR(22)
DECLARE_ISR(23)
DECLARE_ISR(24)
DECLARE_ISR(25)
DECLARE_ISR(26)
DECLARE_ISR(27)
DECLARE_ISR(28)
DECLARE_ISR(29)
DECLARE_ISR(30)
DECLARE_ISR(31)
DECLARE_ISR(32)
DECLARE_ISR(33)
DECLARE_ISR(34)
DECLARE_ISR(35)
DECLARE_ISR(36)
DECLARE_ISR(37)
DECLARE_ISR(38)
DECLARE_ISR(39)
DECLARE_ISR(40)
DECLARE_ISR(41)
DECLARE_ISR(42)
DECLARE_ISR(43)
DECLARE_ISR(44)
DECLARE_ISR(45)
DECLARE_ISR(46)
DECLARE_ISR(47)
DECLARE_ISR(48)
DECLARE_ISR(49)
DECLARE_ISR(50)
DECLARE_ISR(51)
DECLARE_ISR(52)
DECLARE_ISR(53)
DECLARE_ISR(54)
DECLARE_ISR(55)
DECLARE_ISR(56)
DECLARE_ISR(57)
DECLARE_ISR(58)
DECLARE_ISR(59)
DECLARE_ISR(60)
DECLARE_ISR(61)
DECLARE_ISR(62)
DECLARE_ISR(63)
DECLARE_ISR(64)
DECLARE_ISR(65)
DECLARE_ISR(66)
DECLARE_ISR(67)
DECLARE_ISR(68)
DECLARE_ISR(69)
DECLARE_ISR(70)
DECLARE_ISR(71)
DECLARE_ISR(72)
DECLARE_ISR(73)
DECLARE_ISR(74)
DECLARE_ISR(75)
DECLARE_ISR(76)
DECLARE_ISR(77)
DECLARE_ISR(78)
DECLARE_ISR(79)
DECLARE_ISR(80)
DECLARE_ISR(81)
DECLARE_ISR(82)
DECLARE_ISR(83)
DECLARE_ISR(84)
DECLARE_ISR(85)
DECLARE_ISR(86)
DECLARE_ISR(87)
DECLARE_ISR(88)
DECLARE_ISR(89)
DECLARE_ISR(90)
DECLARE_ISR(91)
DECLARE_ISR(92)
DECLARE_ISR(93)
DECLARE_ISR(94)
DECLARE_ISR(95)
DECLARE_ISR(96)
DECLARE_ISR(97)
DECLARE_ISR(98)
DECLARE_ISR(99)
DECLARE_ISR(100)
DECLARE_ISR(101)
DECLARE_ISR(102)
DECLARE_ISR(103)
DECLARE_ISR(104)
DECLARE_ISR(105)
DECLARE_ISR(106)
DECLARE_ISR(107)
DECLARE_ISR(108)
DECLARE_ISR(109)
DECLARE_ISR(110)
DECLARE_ISR(111)
DECLARE_ISR(112)
DECLARE_ISR(113)
DECLARE_ISR(114)
DECLARE_ISR(115)
DECLARE_ISR(116)
DECLARE_ISR(117)
DECLARE_ISR(118)
DECLARE_ISR(119)
DECLARE_ISR(120)
DECLARE_ISR(121)
DECLARE_ISR(122)
DECLARE_ISR(123)
DECLARE_ISR(124)
DECLARE_ISR(125)
DECLARE_ISR(126)
DECLARE_ISR(127)
DECLARE_ISR(128)
DECLARE_ISR(129)
DECLARE_ISR(130)
DECLARE_ISR(131)
DECLARE_ISR(132)
DECLARE_ISR(133)
DECLARE_ISR(134)
DECLARE_ISR(135)
DECLARE_ISR(136)
DECLARE_ISR(137)
DECLARE_ISR(138)
DECLARE_ISR(139)
DECLARE_ISR(140)
DECLARE_ISR(141)
DECLARE_ISR(142)
DECLARE_ISR(143)
DECLARE_ISR(144)
DECLARE_ISR(145)
DECLARE_ISR(146)
DECLARE_ISR(147)
DECLARE_ISR(148)
DECLARE_ISR(149)
DECLARE_ISR(150)
DECLARE_ISR(151)
DECLARE_ISR(152)
DECLARE_ISR(153)
DECLARE_ISR(154)
DECLARE_ISR(155)
DECLARE_ISR(156)
DECLARE_ISR(157)
DECLARE_ISR(158)
DECLARE_ISR(159)
DECLARE_ISR(160)
DECLARE_ISR(161)
DECLARE_ISR(162)
DECLARE_ISR(163)
DECLARE_ISR(164)
DECLARE_ISR(165)
DECLARE_ISR(166)
DECLARE_ISR(167)
DECLARE_ISR(168)
DECLARE_ISR(169)
DECLARE_ISR(170)
DECLARE_ISR(171)
DECLARE_ISR(172)
DECLARE_ISR(173)
DECLARE_ISR(174)
DECLARE_ISR(175)
DECLARE_ISR(176)
DECLARE_ISR(177)
DECLARE_ISR(178)
DECLARE_ISR(179)
DECLARE_ISR(180)
DECLARE_ISR(181)
DECLARE_ISR(182)
DECLARE_ISR(183)
DECLARE_ISR(184)
DECLARE_ISR(185)
DECLARE_ISR(186)
DECLARE_ISR(187)
DECLARE_ISR(188)
DECLARE_ISR(189)
DECLARE_ISR(190)
DECLARE_ISR(191)
DECLARE_ISR(192)
DECLARE_ISR(193)
DECLARE_ISR(194)
DECLARE_ISR(195)
DECLARE_ISR(196)
DECLARE_ISR(197)
DECLARE_ISR(198)
DECLARE_ISR(199)
DECLARE_ISR(200)
DECLARE_ISR(201)
DECLARE_ISR(202)
DECLARE_ISR(203)
DECLARE_ISR(204)
DECLARE_ISR(205)
DECLARE_ISR(206)
DECLARE_ISR(207)
DECLARE_ISR(208)
DECLARE_ISR(209)
DECLARE_ISR(210)
DECLARE_ISR(211)
DECLARE_ISR(212)
DECLARE_ISR(213)
DECLARE_ISR(214)
DECLARE_ISR(215)
DECLARE_ISR(216)
DECLARE_ISR(217)
DECLARE_ISR(218)
DECLARE_ISR(219)
DECLARE_ISR(220)
DECLARE_ISR(221)
DECLARE_ISR(222)
DECLARE_ISR(223)
DECLARE_ISR(224)
DECLARE_ISR(225)
DECLARE_ISR(226)
DECLARE_ISR(227)
DECLARE_ISR(228)
DECLARE_ISR(229)
DECLARE_ISR(230)
DECLARE_ISR(231)
DECLARE_ISR(232)
DECLARE_ISR(233)
DECLARE_ISR(234)
DECLARE_ISR(235)
DECLARE_ISR(236)
DECLARE_ISR(237)
DECLARE_ISR(238)
DECLARE_ISR(239)
DECLARE_ISR(240)
DECLARE_ISR(241)
DECLARE_ISR(242)
DECLARE_ISR(243)
DECLARE_ISR(244)
DECLARE_ISR(245)
DECLARE_ISR(246)
DECLARE_ISR(247)
DECLARE_ISR(248)
DECLARE_ISR(249)
DECLARE_ISR(250)
DECLARE_ISR(251)
DECLARE_ISR(252)
DECLARE_ISR(253)
DECLARE_ISR(254)
DECLARE_ISR(255)

void
exception_install_handler()
{
    ISR_INSTALL(_idt, 0, _asm_isr0, 0)
    ISR_INSTALL(_idt, 1, _asm_isr1, 0)
    ISR_INSTALL(_idt, 2, _asm_isr2, 0)
    ISR_INSTALL(_idt, 3, _asm_isr3, 0)
    ISR_INSTALL(_idt, 4, _asm_isr4, 0)
    ISR_INSTALL(_idt, 5, _asm_isr5, 0)
    ISR_INSTALL(_idt, 6, _asm_isr6, 0)
    ISR_INSTALL(_idt, 7, _asm_isr7, 0)
    ISR_INSTALL(_idt, 8, _asm_isr8, 0)
    ISR_INSTALL(_idt, 9, _asm_isr9, 0)
    ISR_INSTALL(_idt, 10, _asm_isr10, 0)
    ISR_INSTALL(_idt, 11, _asm_isr11, 0)
    ISR_INSTALL(_idt, 12, _asm_isr12, 0)
    ISR_INSTALL(_idt, 13, _asm_isr13, 0)
    ISR_INSTALL(_idt, 14, _asm_isr14, 0)
    ISR_INSTALL(_idt, 15, _asm_isr15, 0)
    ISR_INSTALL(_idt, 16, _asm_isr16, 0)
    ISR_INSTALL(_idt, 17, _asm_isr17, 0)
    ISR_INSTALL(_idt, 18, _asm_isr18, 0)
    ISR_INSTALL(_idt, 19, _asm_isr19, 0)
    ISR_INSTALL(_idt, 20, _asm_isr20, 0)
    ISR_INSTALL(_idt, 21, _asm_isr21, 0)
    ISR_INSTALL(_idt, 22, _asm_isr22, 0)
    ISR_INSTALL(_idt, 23, _asm_isr23, 0)
    ISR_INSTALL(_idt, 24, _asm_isr24, 0)
    ISR_INSTALL(_idt, 25, _asm_isr25, 0)
    ISR_INSTALL(_idt, 26, _asm_isr26, 0)
    ISR_INSTALL(_idt, 27, _asm_isr27, 0)
    ISR_INSTALL(_idt, 28, _asm_isr28, 0)
    ISR_INSTALL(_idt, 29, _asm_isr29, 0)
    ISR_INSTALL(_idt, 30, _asm_isr30, 0)
    ISR_INSTALL(_idt, 31, _asm_isr31, 0)
    ISR_INSTALL(_idt, 32, _asm_isr32, 0)
    ISR_INSTALL(_idt, 33, _asm_isr33, 3)
    ISR_INSTALL(_idt, 34, _asm_isr34, 0)
    ISR_INSTALL(_idt, 35, _asm_isr35, 0)
    ISR_INSTALL(_idt, 36, _asm_isr36, 0)
    ISR_INSTALL(_idt, 37, _asm_isr37, 0)
    ISR_INSTALL(_idt, 38, _asm_isr38, 0)
    ISR_INSTALL(_idt, 39, _asm_isr39, 0)
    ISR_INSTALL(_idt, 40, _asm_isr40, 0)
    ISR_INSTALL(_idt, 41, _asm_isr41, 0)
    ISR_INSTALL(_idt, 42, _asm_isr42, 0)
    ISR_INSTALL(_idt, 43, _asm_isr43, 0)
    ISR_INSTALL(_idt, 44, _asm_isr44, 0)
    ISR_INSTALL(_idt, 45, _asm_isr45, 0)
    ISR_INSTALL(_idt, 46, _asm_isr46, 0)
    ISR_INSTALL(_idt, 47, _asm_isr47, 0)
    ISR_INSTALL(_idt, 48, _asm_isr48, 0)
    ISR_INSTALL(_idt, 49, _asm_isr49, 0)
    ISR_INSTALL(_idt, 50, _asm_isr50, 0)
    ISR_INSTALL(_idt, 51, _asm_isr51, 0)
    ISR_INSTALL(_idt, 52, _asm_isr52, 0)
    ISR_INSTALL(_idt, 53, _asm_isr53, 0)
    ISR_INSTALL(_idt, 54, _asm_isr54, 0)
    ISR_INSTALL(_idt, 55, _asm_isr55, 0)
    ISR_INSTALL(_idt, 56, _asm_isr56, 0)
    ISR_INSTALL(_idt, 57, _asm_isr57, 0)
    ISR_INSTALL(_idt, 58, _asm_isr58, 0)
    ISR_INSTALL(_idt, 59, _asm_isr59, 0)
    ISR_INSTALL(_idt, 60, _asm_isr60, 0)
    ISR_INSTALL(_idt, 61, _asm_isr61, 0)
    ISR_INSTALL(_idt, 62, _asm_isr62, 0)
    ISR_INSTALL(_idt, 63, _asm_isr63, 0)
    ISR_INSTALL(_idt, 64, _asm_isr64, 0)
    ISR_INSTALL(_idt, 65, _asm_isr65, 0)
    ISR_INSTALL(_idt, 66, _asm_isr66, 0)
    ISR_INSTALL(_idt, 67, _asm_isr67, 0)
    ISR_INSTALL(_idt, 68, _asm_isr68, 0)
    ISR_INSTALL(_idt, 69, _asm_isr69, 0)
    ISR_INSTALL(_idt, 70, _asm_isr70, 0)
    ISR_INSTALL(_idt, 71, _asm_isr71, 0)
    ISR_INSTALL(_idt, 72, _asm_isr72, 0)
    ISR_INSTALL(_idt, 73, _asm_isr73, 0)
    ISR_INSTALL(_idt, 74, _asm_isr74, 0)
    ISR_INSTALL(_idt, 75, _asm_isr75, 0)
    ISR_INSTALL(_idt, 76, _asm_isr76, 0)
    ISR_INSTALL(_idt, 77, _asm_isr77, 0)
    ISR_INSTALL(_idt, 78, _asm_isr78, 0)
    ISR_INSTALL(_idt, 79, _asm_isr79, 0)
    ISR_INSTALL(_idt, 80, _asm_isr80, 0)
    ISR_INSTALL(_idt, 81, _asm_isr81, 0)
    ISR_INSTALL(_idt, 82, _asm_isr82, 0)
    ISR_INSTALL(_idt, 83, _asm_isr83, 0)
    ISR_INSTALL(_idt, 84, _asm_isr84, 0)
    ISR_INSTALL(_idt, 85, _asm_isr85, 0)
    ISR_INSTALL(_idt, 86, _asm_isr86, 0)
    ISR_INSTALL(_idt, 87, _asm_isr87, 0)
    ISR_INSTALL(_idt, 88, _asm_isr88, 0)
    ISR_INSTALL(_idt, 89, _asm_isr89, 0)
    ISR_INSTALL(_idt, 90, _asm_isr90, 0)
    ISR_INSTALL(_idt, 91, _asm_isr91, 0)
    ISR_INSTALL(_idt, 92, _asm_isr92, 0)
    ISR_INSTALL(_idt, 93, _asm_isr93, 0)
    ISR_INSTALL(_idt, 94, _asm_isr94, 0)
    ISR_INSTALL(_idt, 95, _asm_isr95, 0)
    ISR_INSTALL(_idt, 96, _asm_isr96, 0)
    ISR_INSTALL(_idt, 97, _asm_isr97, 0)
    ISR_INSTALL(_idt, 98, _asm_isr98, 0)
    ISR_INSTALL(_idt, 99, _asm_isr99, 0)
    ISR_INSTALL(_idt, 100, _asm_isr100, 0)
    ISR_INSTALL(_idt, 101, _asm_isr101, 0)
    ISR_INSTALL(_idt, 102, _asm_isr102, 0)
    ISR_INSTALL(_idt, 103, _asm_isr103, 0)
    ISR_INSTALL(_idt, 104, _asm_isr104, 0)
    ISR_INSTALL(_idt, 105, _asm_isr105, 0)
    ISR_INSTALL(_idt, 106, _asm_isr106, 0)
    ISR_INSTALL(_idt, 107, _asm_isr107, 0)
    ISR_INSTALL(_idt, 108, _asm_isr108, 0)
    ISR_INSTALL(_idt, 109, _asm_isr109, 0)
    ISR_INSTALL(_idt, 110, _asm_isr110, 0)
    ISR_INSTALL(_idt, 111, _asm_isr111, 0)
    ISR_INSTALL(_idt, 112, _asm_isr112, 0)
    ISR_INSTALL(_idt, 113, _asm_isr113, 0)
    ISR_INSTALL(_idt, 114, _asm_isr114, 0)
    ISR_INSTALL(_idt, 115, _asm_isr115, 0)
    ISR_INSTALL(_idt, 116, _asm_isr116, 0)
    ISR_INSTALL(_idt, 117, _asm_isr117, 0)
    ISR_INSTALL(_idt, 118, _asm_isr118, 0)
    ISR_INSTALL(_idt, 119, _asm_isr119, 0)
    ISR_INSTALL(_idt, 120, _asm_isr120, 0)
    ISR_INSTALL(_idt, 121, _asm_isr121, 0)
    ISR_INSTALL(_idt, 122, _asm_isr122, 0)
    ISR_INSTALL(_idt, 123, _asm_isr123, 0)
    ISR_INSTALL(_idt, 124, _asm_isr124, 0)
    ISR_INSTALL(_idt, 125, _asm_isr125, 0)
    ISR_INSTALL(_idt, 126, _asm_isr126, 0)
    ISR_INSTALL(_idt, 127, _asm_isr127, 0)
    ISR_INSTALL(_idt, 128, _asm_isr128, 0)
    ISR_INSTALL(_idt, 129, _asm_isr129, 0)
    ISR_INSTALL(_idt, 130, _asm_isr130, 0)
    ISR_INSTALL(_idt, 131, _asm_isr131, 0)
    ISR_INSTALL(_idt, 132, _asm_isr132, 0)
    ISR_INSTALL(_idt, 133, _asm_isr133, 0)
    ISR_INSTALL(_idt, 134, _asm_isr134, 0)
    ISR_INSTALL(_idt, 135, _asm_isr135, 0)
    ISR_INSTALL(_idt, 136, _asm_isr136, 0)
    ISR_INSTALL(_idt, 137, _asm_isr137, 0)
    ISR_INSTALL(_idt, 138, _asm_isr138, 0)
    ISR_INSTALL(_idt, 139, _asm_isr139, 0)
    ISR_INSTALL(_idt, 140, _asm_isr140, 0)
    ISR_INSTALL(_idt, 141, _asm_isr141, 0)
    ISR_INSTALL(_idt, 142, _asm_isr142, 0)
    ISR_INSTALL(_idt, 143, _asm_isr143, 0)
    ISR_INSTALL(_idt, 144, _asm_isr144, 0)
    ISR_INSTALL(_idt, 145, _asm_isr145, 0)
    ISR_INSTALL(_idt, 146, _asm_isr146, 0)
    ISR_INSTALL(_idt, 147, _asm_isr147, 0)
    ISR_INSTALL(_idt, 148, _asm_isr148, 0)
    ISR_INSTALL(_idt, 149, _asm_isr149, 0)
    ISR_INSTALL(_idt, 150, _asm_isr150, 0)
    ISR_INSTALL(_idt, 151, _asm_isr151, 0)
    ISR_INSTALL(_idt, 152, _asm_isr152, 0)
    ISR_INSTALL(_idt, 153, _asm_isr153, 0)
    ISR_INSTALL(_idt, 154, _asm_isr154, 0)
    ISR_INSTALL(_idt, 155, _asm_isr155, 0)
    ISR_INSTALL(_idt, 156, _asm_isr156, 0)
    ISR_INSTALL(_idt, 157, _asm_isr157, 0)
    ISR_INSTALL(_idt, 158, _asm_isr158, 0)
    ISR_INSTALL(_idt, 159, _asm_isr159, 0)
    ISR_INSTALL(_idt, 160, _asm_isr160, 0)
    ISR_INSTALL(_idt, 161, _asm_isr161, 0)
    ISR_INSTALL(_idt, 162, _asm_isr162, 0)
    ISR_INSTALL(_idt, 163, _asm_isr163, 0)
    ISR_INSTALL(_idt, 164, _asm_isr164, 0)
    ISR_INSTALL(_idt, 165, _asm_isr165, 0)
    ISR_INSTALL(_idt, 166, _asm_isr166, 0)
    ISR_INSTALL(_idt, 167, _asm_isr167, 0)
    ISR_INSTALL(_idt, 168, _asm_isr168, 0)
    ISR_INSTALL(_idt, 169, _asm_isr169, 0)
    ISR_INSTALL(_idt, 170, _asm_isr170, 0)
    ISR_INSTALL(_idt, 171, _asm_isr171, 0)
    ISR_INSTALL(_idt, 172, _asm_isr172, 0)
    ISR_INSTALL(_idt, 173, _asm_isr173, 0)
    ISR_INSTALL(_idt, 174, _asm_isr174, 0)
    ISR_INSTALL(_idt, 175, _asm_isr175, 0)
    ISR_INSTALL(_idt, 176, _asm_isr176, 0)
    ISR_INSTALL(_idt, 177, _asm_isr177, 0)
    ISR_INSTALL(_idt, 178, _asm_isr178, 0)
    ISR_INSTALL(_idt, 179, _asm_isr179, 0)
    ISR_INSTALL(_idt, 180, _asm_isr180, 0)
    ISR_INSTALL(_idt, 181, _asm_isr181, 0)
    ISR_INSTALL(_idt, 182, _asm_isr182, 0)
    ISR_INSTALL(_idt, 183, _asm_isr183, 0)
    ISR_INSTALL(_idt, 184, _asm_isr184, 0)
    ISR_INSTALL(_idt, 185, _asm_isr185, 0)
    ISR_INSTALL(_idt, 186, _asm_isr186, 0)
    ISR_INSTALL(_idt, 187, _asm_isr187, 0)
    ISR_INSTALL(_idt, 188, _asm_isr188, 0)
    ISR_INSTALL(_idt, 189, _asm_isr189, 0)
    ISR_INSTALL(_idt, 190, _asm_isr190, 0)
    ISR_INSTALL(_idt, 191, _asm_isr191, 0)
    ISR_INSTALL(_idt, 192, _asm_isr192, 0)
    ISR_INSTALL(_idt, 193, _asm_isr193, 0)
    ISR_INSTALL(_idt, 194, _asm_isr194, 0)
    ISR_INSTALL(_idt, 195, _asm_isr195, 0)
    ISR_INSTALL(_idt, 196, _asm_isr196, 0)
    ISR_INSTALL(_idt, 197, _asm_isr197, 0)
    ISR_INSTALL(_idt, 198, _asm_isr198, 0)
    ISR_INSTALL(_idt, 199, _asm_isr199, 0)
    ISR_INSTALL(_idt, 200, _asm_isr200, 0)
    ISR_INSTALL(_idt, 201, _asm_isr201, 0)
    ISR_INSTALL(_idt, 202, _asm_isr202, 0)
    ISR_INSTALL(_idt, 203, _asm_isr203, 0)
    ISR_INSTALL(_idt, 204, _asm_isr204, 0)
    ISR_INSTALL(_idt, 205, _asm_isr205, 0)
    ISR_INSTALL(_idt, 206, _asm_isr206, 0)
    ISR_INSTALL(_idt, 207, _asm_isr207, 0)
    ISR_INSTALL(_idt, 208, _asm_isr208, 0)
    ISR_INSTALL(_idt, 209, _asm_isr209, 0)
    ISR_INSTALL(_idt, 210, _asm_isr210, 0)
    ISR_INSTALL(_idt, 211, _asm_isr211, 0)
    ISR_INSTALL(_idt, 212, _asm_isr212, 0)
    ISR_INSTALL(_idt, 213, _asm_isr213, 0)
    ISR_INSTALL(_idt, 214, _asm_isr214, 0)
    ISR_INSTALL(_idt, 215, _asm_isr215, 0)
    ISR_INSTALL(_idt, 216, _asm_isr216, 0)
    ISR_INSTALL(_idt, 217, _asm_isr217, 0)
    ISR_INSTALL(_idt, 218, _asm_isr218, 0)
    ISR_INSTALL(_idt, 219, _asm_isr219, 0)
    ISR_INSTALL(_idt, 220, _asm_isr220, 0)
    ISR_INSTALL(_idt, 221, _asm_isr221, 0)
    ISR_INSTALL(_idt, 222, _asm_isr222, 0)
    ISR_INSTALL(_idt, 223, _asm_isr223, 0)
    ISR_INSTALL(_idt, 224, _asm_isr224, 0)
    ISR_INSTALL(_idt, 225, _asm_isr225, 0)
    ISR_INSTALL(_idt, 226, _asm_isr226, 0)
    ISR_INSTALL(_idt, 227, _asm_isr227, 0)
    ISR_INSTALL(_idt, 228, _asm_isr228, 0)
    ISR_INSTALL(_idt, 229, _asm_isr229, 0)
    ISR_INSTALL(_idt, 230, _asm_isr230, 0)
    ISR_INSTALL(_idt, 231, _asm_isr231, 0)
    ISR_INSTALL(_idt, 232, _asm_isr232, 0)
    ISR_INSTALL(_idt, 233, _asm_isr233, 0)
    ISR_INSTALL(_idt, 234, _asm_isr234, 0)
    ISR_INSTALL(_idt, 235, _asm_isr235, 0)
    ISR_INSTALL(_idt, 236, _asm_isr236, 0)
    ISR_INSTALL(_idt, 237, _asm_isr237, 0)
    ISR_INSTALL(_idt, 238, _asm_isr238, 0)
    ISR_INSTALL(_idt, 239, _asm_isr239, 0)
    ISR_INSTALL(_idt, 240, _asm_isr240, 0)
    ISR_INSTALL(_idt, 241, _asm_isr241, 0)
    ISR_INSTALL(_idt, 242, _asm_isr242, 0)
    ISR_INSTALL(_idt, 243, _asm_isr243, 0)
    ISR_INSTALL(_idt, 244, _asm_isr244, 0)
    ISR_INSTALL(_idt, 245, _asm_isr245, 0)
    ISR_INSTALL(_idt, 246, _asm_isr246, 0)
    ISR_INSTALL(_idt, 247, _asm_isr247, 0)
    ISR_INSTALL(_idt, 248, _asm_isr248, 0)
    ISR_INSTALL(_idt, 249, _asm_isr249, 0)
    ISR_INSTALL(_idt, 250, _asm_isr250, 0)
    ISR_INSTALL(_idt, 251, _asm_isr251, 0)
    ISR_INSTALL(_idt, 252, _asm_isr252, 0)
    ISR_INSTALL(_idt, 253, _asm_isr253, 0)
    ISR_INSTALL(_idt, 254, _asm_isr254, 0)
    ISR_INSTALL(_idt, 255, _asm_isr255, 0)
}