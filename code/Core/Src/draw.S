/**************************************************************************
 --  STM32N6 3.5inch Arduino 8BIT Module MAR3501 Draw xbm pixmap
 --
 --           Copyright (C) 2025 By Ulrik Hørlyk Hjort
 --
 --  This Program is Free Software; You Can Redistribute It and/or
 --  Modify It Under The Terms of The GNU General Public License
 --  As Published By The Free Software Foundation; Either Version 2
 --  of The License, or (at Your Option) Any Later Version.
 --
 --  This Program is Distributed in The Hope That It Will Be Useful,
 --  But WITHOUT ANY WARRANTY; Without Even The Implied Warranty of
 --  MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See The
 --  GNU General Public License for More Details.
 --
 -- You Should Have Received A Copy of The GNU General Public License
 -- Along with This Program; if not, See <Http://Www.Gnu.Org/Licenses/>.
***************************************************************************/


@ void draw_xbm_pixmap(uint32_t x0, uint32_t y0, uint8_t *px_buf,
@                  uint32_t height, uint32_t width, uint32_t color)
@ r0 = x0
@ r1 = y0
@ r2 = px_buf
@ r3 = height
@ [sp, #0] = width
@ [sp, #4] = color

    .syntax unified
    .thumb
    .global draw_xbm_pixmap
    .type draw_xbm_pixmap, %function

.equ LCD_HEIGHT, 320
.equ LCD_WIDTH, 480


draw_xbm_pixmap:
   push    {r4-r11, lr}           @ Save registers
    sub     sp, sp, #24            @ Allocate stack space for locals

    @ Load width and color from stack (adjusted for pushed registers)
    ldr     r4, [sp, #60]          @ r4 = width (24 + 36 = 60)
    ldr     r5, [sp, #64]          @ r5 = color

    @ Store arguments on our local stack
    str     r0, [sp, #0]           @ x0
    str     r1, [sp, #4]           @ y0
    str     r2, [sp, #8]           @ px_buf
    str     r3, [sp, #12]          @ height
    str     r4, [sp, #16]          @ width
    str     r5, [sp, #20]          @ color

    @ Check if height or width is 0
    cmp     r3, #0
    beq     .L_exit
    cmp     r4, #0
    beq     .L_exit

    mov     r6, #0                 @ byte_index = 0
    mov     r7, #0                 @ y = 0

.L_outer_loop:                     @ for (y = 0; y < height; y++)
    ldr     r3, [sp, #12]          @ Load height
    cmp     r7, r3
    bge     .L_exit

    ldr     r4, [sp, #16]          @ Load width
    lsr     r8, r4, #3             @ r8 = width / 8
    mov     r9, #0                 @ bx = 0

.L_middle_loop:                    @ for (bx = 0; bx < width/8; bx++)
    cmp     r9, r8
    bge     .L_next_y

    @ Load byte from px_buf
    ldr     r2, [sp, #8]           @ Load px_buf
    ldrb    r10, [r2, r6]          @ r10 = px_buf[byte_index]
    add     r6, r6, #1             @ byte_index++

    mov     r11, #0                @ bit = 0

.L_inner_loop:                     @ for (bit = 0; bit < 8; bit++)
    cmp     r11, #8
    bge     .L_next_bx

    @ Check if bit is set: b & (1 << bit)
    mov     r0, #1
    lsl     r0, r0, r11            @ r0 = (1 << bit)
    tst     r10, r0                @ Test b & (1 << bit)
    beq     .L_next_bit            @ Skip if bit is 0

    @ Calculate x = bx * 8 + bit
    lsl     r0, r9, #3             @ r0 = bx * 8
    add     r0, r0, r11            @ r0 = bx * 8 + bit

    @ Calculate x_ = x0 + x
    ldr     r1, [sp, #0]           @ Load x0
    add     r0, r1, r0             @ x_ = x0 + x

    @ Clamp x_ to LCD_WIDTH - 1
    ldr     r1, =LCD_WIDTH
    cmp     r0, r1
    blo     .L_x_ok
    sub     r0, r1, #1             @ if x_ >= LCD_WIDTH, x_ = LCD_WIDTH - 1
.L_x_ok:
    uxth    r0, r0                 @ Convert to uint16_t

    @ Calculate y_ = y0 + y
    ldr     r1, [sp, #4]           @ Load y0
    add     r1, r1, r7             @ y_ = y0 + y

    @ Clamp y_ to LCD_HEIGHT - 1
    ldr     r2, =LCD_HEIGHT
    cmp     r1, r2
    blo     .L_y_ok
    sub     r1, r2, #1             @ if y_ >= LCD_HEIGHT, y_ = LCD_HEIGHT - 1
.L_y_ok:
    uxth    r1, r1                 @ Convert to uint16_t

    @ Load color
    ldr     r2, [sp, #20]          @ r2 = color

    @ Call lcd_draw_pixel_fast(x_, y_, color)
    push    {r6-r11}               @ Save loop variables
    bl      lcd_draw_pixel
    pop     {r6-r11}               @ Restore loop variables

.L_next_bit:
    add     r11, r11, #1           @ bit++
    b       .L_inner_loop

.L_next_bx:
    add     r9, r9, #1             @ bx++
    b       .L_middle_loop

.L_next_y:
    add     r7, r7, #1             @ y++
    b       .L_outer_loop

.L_exit:
    add     sp, sp, #24            @ Deallocate stack space
    pop     {r4-r11, pc}           @ Restore and return

    .size draw_xbm_pixmap, .-draw_xbm_pixmap

