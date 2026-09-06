.syntax unified
.cpu cortex-m3
.thumb

.global Reset_Handler
.global _estack

/* ---------------- Vector Table ---------------- */
.section .isr_vector, "a", %progbits
.type g_pfnVectors, %object

g_pfnVectors:
    .word _estack             /* Initial stack pointer */
    .word Reset_Handler       /* Reset handler */
    .word Default_Handler     /* NMI */
    .word Default_Handler     /* HardFault */
    .word Default_Handler     /* MemManage */
    .word Default_Handler     /* BusFault */
    .word Default_Handler     /* UsageFault */
    .word 0
    .word 0
    .word 0
    .word 0
    .word Default_Handler     /* SVCall */
    .word Default_Handler     /* DebugMon */
    .word 0
    .word Default_Handler     /* PendSV */
    .word Default_Handler     /* SysTick */

.size g_pfnVectors, .-g_pfnVectors


/* ---------------- Reset Handler ---------------- */
.section .text.Reset_Handler, "ax", %progbits
.type Reset_Handler, %function

Reset_Handler:
    /* Set stack pointer */
    ldr sp, =_estack

    /* Call main */
    bl main

    /* main should not return, but if it does, stay here */
1:
    b 1b

.size Reset_Handler, .-Reset_Handler


/* ---------------- Default Handler ---------------- */
.section .text.Default_Handler, "ax", %progbits
.type Default_Handler, %function

Default_Handler:
1:
    b 1b

.size Default_Handler, .-Default_Handler
