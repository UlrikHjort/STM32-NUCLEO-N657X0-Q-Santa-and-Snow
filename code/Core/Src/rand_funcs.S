/**************************************************************************
 --                 STM32N6 Misc random functions
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
@ Global PRNG state
    .data
    .align 2
    .global rand_state
rand_state:
    .word   123456789

    .text
    .syntax unified
    .cpu cortex-m4
    .thumb

@ ============================================================================
@ uint32_t random32(void)
@ Returns a 32-bit random number using xorshift32
@ ============================================================================
    .global random32
    .type random32, %function

random32:
    @ Load current state
    ldr     r1, =rand_state
    ldr     r0, [r1]            @ r0 = rand_state

    @ x ^= x << 13
    lsl     r2, r0, #13         @ r2 = x << 13
    eor     r0, r0, r2          @ x ^= (x << 13)

    @ x ^= x >> 17
    lsr     r2, r0, #17         @ r2 = x >> 17
    eor     r0, r0, r2          @ x ^= (x >> 17)

    @ x ^= x << 5
    lsl     r2, r0, #5          @ r2 = x << 5
    eor     r0, r0, r2          @ x ^= (x << 5)

    @ Store new state
    str     r0, [r1]            @ rand_state = x

    @ Return value already in r0
    bx      lr

    .size random32, .-random32


@ ============================================================================
@ int32_t random_range(int32_t LIMIT)
@ r0 = LIMIT
@ Returns: (LIMIT/2) - (random % (LIMIT+1))
@ ============================================================================
    .global random_range
    .type random_range, %function

random_range:
    push    {r4, r5, lr}        @ Save registers

    mov     r4, r0              @ r4 = LIMIT (save it)

    @ --- xorshift32 PRNG ---
    ldr     r1, =rand_state
    ldr     r0, [r1]            @ r0 = rand_state

    @ x ^= x << 13
    lsl     r2, r0, #13
    eor     r0, r0, r2

    @ x ^= x >> 17
    lsr     r2, r0, #17
    eor     r0, r0, r2

    @ x ^= x << 5
    lsl     r2, r0, #5
    eor     r0, r0, r2

    @ Store new state
    str     r0, [r1]            @ rand_state = x

    @ --- compute modulo (LIMIT + 1) ---
    @ r0 = x (random value)
    @ r4 = LIMIT

    add     r5, r4, #1          @ r5 = LIMIT + 1

    @ Perform signed division: r0 / r5
    @ Result: r0 = quotient, r1 = remainder
    sdiv    r1, r0, r5          @ r1 = x / (LIMIT + 1)
    mls     r0, r1, r5, r0      @ r0 = x - (quotient * (LIMIT + 1)) = x % (LIMIT + 1)

    @ mod = r0
    @ if (mod < 0) mod += (LIMIT + 1)
    cmp     r0, #0
    bge     .L_mod_ok
    add     r0, r0, r5          @ mod += (LIMIT + 1)

.L_mod_ok:
    @ r0 = mod (now guaranteed non-negative)
    @ r4 = LIMIT

    @ Compute (LIMIT / 2) - mod
    @ Need to load 2 into a register for division
    mov     r2, #2
    sdiv    r1, r4, r2          @ r1 = LIMIT / 2 (signed division)
    sub     r0, r1, r0          @ r0 = (LIMIT / 2) - mod

    pop     {r4, r5, pc}        @ Restore and return

    .size random_range, .-random_range
