/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012,2013 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes ChibiOS/RT, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

/**
 * @file    templates/chcore.h
 * @brief   Port related template macros and structures.
 * @details This file is a template of the system driver macros provided by
 *          a port.
 *
 * @addtogroup core
 * @{
 */

#ifndef _CHCORE_H_
#define _CHCORE_H_

/*===========================================================================*/
/* Port constants.                                                           */
/*===========================================================================*/
#define SIMULATOR

/*===========================================================================*/
/* Port macros.                                                              */
/*===========================================================================*/

/*===========================================================================*/
/* Port configurable parameters.                                             */
/*===========================================================================*/

/**
 * @brief   Stack size for the system idle thread.
 * @details This size depends on the idle thread implementation, usually
 *          the idle thread should take no more space than those reserved
 *          by @p PORT_INT_REQUIRED_STACK.
 */
#ifndef PORT_IDLE_THREAD_STACK_SIZE
#define PORT_IDLE_THREAD_STACK_SIZE     0
#endif

/**
 * @brief   Per-thread stack overhead for interrupts servicing.
 * @details This constant is used in the calculation of the correct working
 *          area size.
 *          This value can be zero on those architecture where there is a
 *          separate interrupt stack and the stack space between @p intctx and
 *          @p extctx is known to be zero.
 */
#ifndef PORT_INT_REQUIRED_STACK
#define PORT_INT_REQUIRED_STACK         0
#endif

/*===========================================================================*/
/* Port derived parameters.                                                  */
/*===========================================================================*/

/*===========================================================================*/
/* Port exported info.                                                       */
/*===========================================================================*/

/**
 * @brief   Unique macro for the implemented architecture.
 */
#define CH_ARCHITECTURE_XXX

/**
 * @brief   Name of the implemented architecture.
 */
#define CH_ARCHITECTURE_NAME            ""

/**
 * @brief   Name of the architecture variant (optional).
 */
#define CH_ARCHITECTURE_VARIANT_NAME    ""

/**
 * @brief   Name of the compiler supported by this port.
 */
#define CH_COMPILER_NAME                "GCC"

/**
 * @brief   Port-specific information string.
 */
#define CH_PORT_INFO                    ""

/*===========================================================================*/
/* Port implementation part.                                                 */
/*===========================================================================*/

/**
 * @brief   Base type for stack and memory alignment.
 */
typedef uint8_t stkalign_t;

/**
 * @brief   Interrupt saved context.
 * @details This structure represents the stack frame saved during a
 *          preemption-capable interrupt handler.
 */
struct extctx {
};

/**
 * @brief   System saved context.
 * @details This structure represents the inner stack frame during a context
 *          switching.
 */
struct intctx {
};

/**
 * @brief   Platform dependent part of the @p Thread structure.
 * @details This structure usually contains just the saved stack pointer
 *          defined as a pointer to a @p intctx structure.
 */
struct context {
  struct intctx *sp;
};

/**
 * @brief   Platform dependent part of the @p chThdCreateI() API.
 * @details This code usually setup the context switching frame represented
 *          by an @p intctx structure.
 */
#define SETUP_CONTEXT(workspace, wsize, pf, arg) {                          \
}

/**
 * @brief   Enforces a correct alignment for a stack area size value.
 */
#define STACK_ALIGN(n) ((((n) - 1) | (sizeof(stkalign_t) - 1)) + 1)

/**
 * @brief   Computes the thread working area global size.
 */
#define THD_WA_SIZE(n) STACK_ALIGN(sizeof(Thread) +                         \
                                   sizeof(struct intctx) +                  \
                                   sizeof(struct extctx) +                  \
                                   (n) + (PORT_INT_REQUIRED_STACK))

/**
 * @brief   Static working area allocation.
 * @details This macro is used to allocate a static thread working area
 *          aligned as both position and size.
 */
#define WORKING_AREA(s, n) stkalign_t s[THD_WA_SIZE(n) / sizeof(stkalign_t)]

/**
 * @brief   IRQ prologue code.
 * @details This macro must be inserted at the start of all IRQ handlers
 *          enabled to invoke system APIs.
 */
#define PORT_IRQ_PROLOGUE()

/**
 * @brief   IRQ epilogue code.
 * @details This macro must be inserted at the end of all IRQ handlers
 *          enabled to invoke system APIs.
 */
#define PORT_IRQ_EPILOGUE()

/**
 * @brief   IRQ handler function declaration.
 * @note    @p id can be a function name or a vector number depending on the
 *          port implementation.
 */
#define PORT_IRQ_HANDLER(id) void id(void)

/**
 * @brief   Fast IRQ handler function declaration.
 * @note    @p id can be a function name or a vector number depending on the
 *          port implementation.
 * @note    Not all architectures support fast interrupts, in this case this
 *          macro must be omitted.
 */
#define PORT_FAST_IRQ_HANDLER(id) void id(void)

/**
 * @brief   Managed RAM size.
 * @details Size of the RAM area to be managed by the OS. If set to zero
 *          then the whole available RAM is used. The core memory is made
 *          available to the heap allocator and/or can be used directly through
 *          the simplified core memory allocator.
 *
 * @note    In order to let the OS manage the whole RAM the linker script must
 *          provide the @p __heap_base__ and @p __heap_end__ symbols.
 * @note    Requires @p CH_USE_MEMCORE.
 */
#ifdef CH_MEMCORE_SIZE
 #undef CH_MEMCORE_SIZE
#endif
#define CH_MEMCORE_SIZE                 0x40000

/**
 * @brief   Debug option, stack checks.
 * @details If enabled then a runtime stack check is performed.
 *
 * @note    The default is @p FALSE.
 * @note    The stack check is performed in a architecture/port dependent way.
 *          It may not be implemented or some ports.
 * @note    The default failure mode is to halt the system with the global
 *          @p panic_msg variable set to @p NULL.
 */
#ifdef CH_DBG_ENABLE_STACK_CHECK
 #undef CH_DBG_ENABLE_STACK_CHECK
#endif
#define CH_DBG_ENABLE_STACK_CHECK       FALSE

#ifdef __cplusplus
extern "C" {
#endif
  void port_init(void);
  void port_lock(void);
  void port_unlock(void);
  void port_lock_from_isr(void);
  void port_unlock_from_isr(void);
  void port_disable(void);
  void port_suspend(void);
  void port_enable(void);
  void port_wait_for_interrupt(void);
  void port_halt(void);
  void port_switch(Thread *ntp, Thread *otp);
#ifdef __cplusplus
}
#endif

#endif /* _CHCORE_H_ */

/** @} */
