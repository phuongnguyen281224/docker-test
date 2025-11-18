.syntax unified
.thumb

.global v_v_reset_handler
.global v_v_nmi_handler
.global v_v_hard_fault_handler
.global v_v_mem_manage_handler
.global v_v_bus_fault_handler
.global v_v_usage_fault_handler
.global v_v_svc_handler
.global v_v_debug_mon_handler
.global v_v_pendsv_handler
.global v_v_sys_tick_handler

.word _stack_top           // 0x0000 0000 - Stack Pointer
.word v_v_reset_handler    // 0x0000 0004 - Reset
.word v_v_nmi_handler      // 0x0000 0008 - NMI
.word v_v_hard_fault_handler // 0x0000 000C - Hard Fault
.word v_v_mem_manage_handler // 0x0000 0010 - Memory Management Fault
.word v_v_bus_fault_handler  // 0x0000 0014 - Bus Fault
.word v_v_usage_fault_handler// 0x0000 0018 - Usage Fault
.word 0                    // 0x0000 001C - Reserved
.word 0                    // 0x0000 0020 - Reserved
.word 0                    // 0x0000 0024 - Reserved
.word 0                    // 0x0000 0028 - Reserved
.word v_v_svc_handler      // 0x0000 002C - SVCall
.word v_v_debug_mon_handler// 0x0000 0030 - Debug Monitor
.word 0                    // 0x0000 0034 - Reserved
.word v_v_pendsv_handler   // 0x0000 0038 - PendSV
.word v_v_sys_tick_handler // 0x0000 003C - SysTick

.section .text

v_v_reset_handler:
    // Copy .data section from FLASH to RAM
    ldr r0, =_data_flash
    ldr r1, =_data_ram
    ldr r2, =_data_end
    bl prv_v_memcpy

    // Zero out .bss section
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    mov r2, #0
    bl prv_v_memset

    // Call main
    bl main

    // Infinite loop
loop:
    b loop

prv_v_memcpy:
    cmp r1, r2
    bhs prv_v_memcpy_end
    ldrb r3, [r0], #1
    strb r3, [r1], #1
    b prv_v_memcpy
prv_v_memcpy_end:
    bx lr

prv_v_memset:
    cmp r0, r1
    bhs prv_v_memset_end
    strb r2, [r0], #1
    b prv_v_memset
prv_v_memset_end:
    bx lr

.weak v_v_nmi_handler
.thumb_set v_v_nmi_handler, v_v_default_handler

.weak v_v_hard_fault_handler
.thumb_set v_v_hard_fault_handler, v_v_default_handler

.weak v_v_mem_manage_handler
.thumb_set v_v_mem_manage_handler, v_v_default_handler

.weak v_v_bus_fault_handler
.thumb_set v_v_bus_fault_handler, v_v_default_handler

.weak v_v_usage_fault_handler
.thumb_set v_v_usage_fault_handler, v_v_default_handler

.weak v_v_svc_handler
.thumb_set v_v_svc_handler, v_v_default_handler

.weak v_v_debug_mon_handler
.thumb_set v_v_debug_mon_handler, v_v_default_handler

.weak v_v_pendsv_handler
.thumb_set v_v_pendsv_handler, v_v_default_handler

.weak v_v_sys_tick_handler
.thumb_set v_v_sys_tick_handler, v_v_default_handler

v_v_default_handler:
    b .
