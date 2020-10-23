/*
 * Copyright (c) 2020, Vertexcom Technologies, Inc.
 * All rights reserved.
 *
 * NOTICE: All information contained herein is, and remains
 * the property of Vertexcom Technologies, Inc. and its suppliers,
 * if any. The intellectual and technical concepts contained
 * herein are proprietary to Vertexcom Technologies, Inc.
 * and may be covered by U.S. and Foreign Patents, patents in process,
 * and protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Vertexcom Technologies, Inc.
 *
 * Authors: Darko Pancev <darko.pancev@vertexcom.com>
 */

#include <vcdrivers/assert.h>
#include <vcdrivers/periph/tim.h>

typedef struct
{
    volatile uint32_t FLASHWC;              /* (0x0000) Flash wait cycle register */
    volatile uint32_t CLKSEL;               /* (0x0004) Clock selection register */
    volatile uint32_t CLKDIVH;              /* (0x0008) AHB clock divider control register */
    volatile uint32_t CLKDIVP;              /* (0x000C) APB clock divider control register */
    volatile uint32_t HCLKEN;               /* (0x0010) AHB clock enable control register */
    volatile uint32_t PCLKEN;               /* (0x0014) APB clock enable control register */
    volatile const uint32_t  RESERVED[4];
    volatile uint32_t CLKEN_UNLOCK;         /* (0x0028) HCLK, PCLK pass register */
    volatile const uint32_t  RESERVED1;
    volatile uint32_t  HSOFTRST;            /* (0x0030) HCLK individual module software reset */
    volatile uint32_t  PSOFTRST;            /* (0x0034) PCLK individual module software reset */
    volatile uint32_t SOFTRST_UNLOCK;       /* (0x0038) HCLK, PCLK pass register */
    volatile const uint32_t  RESERVED2;
    volatile uint32_t PWRUPDLY;             /* (0x0040) Power up delay control register */
} VC_MISC2_Type;

typedef struct
{
    volatile uint32_t CTL;                  /* (0x0000) PWM timer control register */
    volatile const uint32_t  TAR;           /* (0x0004) PWM timer current count register */
    volatile uint32_t CCTL[3];              /* (0x0008 - 0x0010) PWM timer compare/capture control register 0 - 3 */
    volatile uint32_t CCR[3];               /* (0x0014 - 0x001C) PWM timer compare/capture data register 0 - 3 */
} VC_PWM_Type;

#define VC_PWM0_BASE 0x40045100UL
#define VC_PWM1_BASE 0x40045140UL
#define VC_PWM2_BASE 0x40045180UL
#define VC_PWM3_BASE 0x400451C0UL
#define VC_MISC2_BASE 0x40047000UL

#define VC_PWM(x) ((VC_PWM_Type *)((x * (VC_PWM1_BASE - VC_PWM0_BASE)) + VC_PWM0_BASE))
#define VC_MISC2 ((VC_MISC2_Type *)VC_MISC2_BASE)

#define MISC2_PCLKEN_TIMER_Pos (15UL)
#define MISC2_PCLKEN_TIMER_Msk (1UL << MISC2_PCLKEN_TIMER_Pos)
#define MISC2_PCLKEN_TIMER_Disabled (0UL << MISC2_PCLKEN_TIMER_Pos)
#define MISC2_PCLKEN_TIMER_Enabled (1UL << MISC2_PCLKEN_TIMER_Pos)

/* MISC2_CLKEN_UNLOCK register */
#define MISC2_CLKEN_UNLOCK_UNLOCK_Pos (0UL)
#define MISC2_CLKEN_UNLOCK_UNLOCK_Msk (0x1UL << MISC2_CLKEN_UNLOCK_UNLOCK_Pos)
#define MISC2_CLKEN_UNLOCK_UNLOCK_KEY (0x55AAAA55 << MISC2_CLKEN_UNLOCK_UNLOCK_Pos)

/* -------------------------------------------------------------------------- */
/* PWM controller */
/* -------------------------------------------------------------------------- */

/* PWM_CTL register */
#define PWM_CTL_IFG_Pos (0UL)
#define PWM_CTL_IFG_Msk (0x1UL << PWM_CTL_IFG_Pos)

#define PWM_CTL_IE_Pos (1UL)
#define PWM_CTL_IE_Msk (0x1UL << PWM_CTL_IE_Pos)

#define PWM_CTL_CLR_Pos (2UL)
#define PWM_CTL_CLR_Msk (0x1UL << PWM_CTL_CLR_Pos)
#define PWM_CTL_CLR_Disabled (0UL << PWM_CTL_CLR_Pos)
#define PWM_CTL_CLR_Enabled (1UL << PWM_CTL_CLR_Pos)

#define PWM_CTL_TSEL_Pos (3UL)
#define PWM_CTL_TSEL_Msk (0x1UL << PWM_CTL_TSEL_Pos)
#define PWM_CTL_TSEL_PCLK_DIV128 (0UL << PWM_CTL_TSEL_Pos)
#define PWM_CTL_TSEL_PCLK (1UL << PWM_CTL_TSEL_Pos)

#define PWM_CTL_MC_Pos (4UL)
#define PWM_CTL_MC_Msk (0x3UL << PWM_CTL_MC_Pos)
#define PWM_CTL_MC_Stop (0UL << PWM_CTL_MC_Pos)
#define PWM_CTL_MC_Up (1UL << PWM_CTL_MC_Pos)
#define PWM_CTL_MC_Continous (2UL << PWM_CTL_MC_Pos)
#define PWM_CTL_MC_UpDown (3UL << PWM_CTL_MC_Pos)

#define PWM_CTL_ID_Pos (6UL)
#define PWM_CTL_ID_Msk (0x7UL << PWM_CTL_ID_Pos)
#define PWM_CTL_ID_CLKDIV1 (0UL << PWM_CTL_ID_Pos)
#define PWM_CTL_ID_CLKDIV2 (1UL << PWM_CTL_ID_Pos)
#define PWM_CTL_ID_CLKDIV4 (2UL << PWM_CTL_ID_Pos)
#define PWM_CTL_ID_CLKDIV8 (3UL << PWM_CTL_ID_Pos)
#define PWM_CTL_ID_CLKDIV16 (4UL << PWM_CTL_ID_Pos)
#define PWM_CTL_ID_CLKDIV32 (5UL << PWM_CTL_ID_Pos)
#define PWM_CTL_ID_CLKDIV64 (6UL << PWM_CTL_ID_Pos)
#define PWM_CTL_ID_CLKDIV128 (7UL << PWM_CTL_ID_Pos)

/* PWM_CCTL register */
#define PWM_CCTL_CCIFG_Pos (0UL)
#define PWM_CCTL_CCIFG_Msk (0x1UL << PWM_CCTL_CCIFG_Pos)

#define PWM_CCTL_COV_Pos (1UL)
#define PWM_CCTL_COV_Msk (0x1UL << PWM_CCTL_COV_Pos)

#define PWM_CCTL_OUT_Pos (2UL)
#define PWM_CCTL_OUT_Msk (0x1UL << PWM_CCTL_OUT_Pos)

#define PWM_CCTL_CCI_Pos (3UL)
#define PWM_CCTL_CCI_Msk (0x1UL << PWM_CCTL_CCI_Pos)

#define PWM_CCTL_CCIE_Pos (4UL)
#define PWM_CCTL_CCIE_Msk (0x1UL << PWM_CCTL_CCIE_Pos)
#define PWM_CCTL_CCIE_Disabled (0UL << PWM_CCTL_CCIE_Pos)
#define PWM_CCTL_CCIE_Enabled (1UL << PWM_CCTL_CCIE_Pos)

#define PWM_CCTL_OUTMOD_Pos (5UL)
#define PWM_CCTL_OUTMOD_Msk (0x7UL << PWM_CCTL_OUTMOD_Pos)

#define PWM_CCTL_CAL_Pos (8UL)
#define PWM_CCTL_CAL_Msk (0x1UL << PWM_CCTL_CAL_Pos)

#define PWM_CCTL_OUTEN_Pos (9UL)
#define PWM_CCTL_OUTEN_Msk (0x1UL << PWM_CCTL_OUTEN_Pos)

#define PWM_CCTL_SCCI_Pos (10UL)
#define PWM_CCTL_SCCI_Msk (0x1UL << PWM_CCTL_SCCI_Pos)

#define PWM_CCTL_OUT_HRES_Pos (11UL)
#define PWM_CCTL_OUT_HRES_Msk (0x1UL << PWM_CCTL_OUT_HRES_Pos)

#define PWM_CCTL_CM_Pos (14UL)
#define PWM_CCTL_CM_Msk (0x3UL << PWM_CCTL_CM_Pos)

/* PWM_CCR register */
#define PWM_CCR_CCR_Pos (0UL)
#define PWM_CCR_CCR_Msk (0xFFFFUL << PWM_CCR_CCR_Pos)

/* PWM_O_SEL register */
#define PWM_O_SEL_SEL0_Pos (0UL)
#define PWM_O_SEL_SEL0_Msk (0xFUL << PWM_O_SEL_SEL0_Pos)

#define PWM_O_SEL_SEL1_Pos (4UL)
#define PWM_O_SEL_SEL1_Msk (0xFUL << PWM_O_SEL_SEL1_Pos)

#define PWM_O_SEL_SEL2_Pos (8UL)
#define PWM_O_SEL_SEL2_Msk (0xFUL << PWM_O_SEL_SEL2_Pos)

#define PWM_O_SEL_SEL3_Pos (12UL)
#define PWM_O_SEL_SEL3_Msk (0xFUL << PWM_O_SEL_SEL3_Pos)

/* PWM_I_SELO1 register */
#define PWM_I_SELO1_SEL00_Pos (0UL)
#define PWM_I_SELO1_SEL00_Msk (0x3UL << PWM_I_SELO1_SEL00_Pos)

#define PWM_I_SELO1_SEL01_Pos (2UL)
#define PWM_I_SELO1_SEL01_Msk (0x3UL << PWM_I_SELO1_SEL01_Pos)

#define PWM_I_SELO1_SEL02_Pos (4UL)
#define PWM_I_SELO1_SEL02_Msk (0x3UL << PWM_I_SELO1_SEL02_Pos)

#define PWM_I_SELO1_SEL10_Pos (16UL)
#define PWM_I_SELO1_SEL10_Msk (0x3UL << PWM_I_SELO1_SEL10_Pos)

#define PWM_I_SELO1_SEL11_Pos (18UL)
#define PWM_I_SELO1_SEL11_Msk (0x3UL << PWM_I_SELO1_SEL11_Pos)

#define PWM_I_SELO1_SEL12_Pos (20UL)
#define PWM_I_SELO1_SEL12_Msk (0x3UL << PWM_I_SELO1_SEL12_Pos)

/* PWM_I_SEL23 register */
#define PWM_I_SEL23_SEL20_Pos (0UL)
#define PWM_I_SEL23_SEL20_Msk (0x3UL << PWM_I_SEL23_SEL20_Pos)

#define PWM_I_SEL23_SEL21_Pos (2UL)
#define PWM_I_SEL23_SEL21_Msk (0x3UL << PWM_I_SEL23_SEL21_Pos)

#define PWM_I_SEL23_SEL22_Pos (4UL)
#define PWM_I_SEL23_SEL22_Msk (0x3UL << PWM_I_SEL23_SEL22_Pos)

#define PWM_I_SEL23_SEL30_Pos (16UL)
#define PWM_I_SEL23_SEL30_Msk (0x3UL << PWM_I_SEL23_SEL30_Pos)

#define PWM_I_SEL23_SEL31_Pos (18UL)
#define PWM_I_SEL23_SEL31_Msk (0x3UL << PWM_I_SEL23_SEL31_Pos)

#define PWM_I_SEL23_SEL32_Pos (20UL)
#define PWM_I_SEL23_SEL32_Msk (0x3UL << PWM_I_SEL23_SEL32_Pos)


#define TIM_NUMOF (4U)
#define TIM_CHAN_NUMOF (3U)

static int _tim_irqn[TIM_NUMOF] = { 18, 19, 20, 21 }; /* Pwm0_IRQn, Pwm1_IRQn, Pwm2_IRQn, Pwm3_IRQn */

static vctim_isr_context_t _isr_tim_ctx[TIM_NUMOF];

extern void cpu_end_of_isr(void);

typedef struct
{
    volatile uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
    uint32_t RESERVED0[24U];
    volatile uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
    uint32_t RSERVED1[24U];
    volatile uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
    uint32_t RESERVED2[24U];
    volatile uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
    uint32_t RESERVED3[24U];
    volatile uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
    uint32_t RESERVED4[56U];
    volatile uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
    uint32_t RESERVED5[644U];
    volatile uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVIC_Type;

#define SCS_BASE    (0xE000E000UL)                            /*!< System Control Space Base Address */
#define NVIC_BASE   (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */

#define NVIC ((NVIC_Type *)NVIC_BASE)

static void TIM_NVIC_EnableIRQ(int IRQn)
{
    if ((int32_t)(IRQn) >= 0)
    {
        NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    }
}


int vctim_init(vctim_t dev, unsigned long freq, vctim_callback_func_t callback, void *arg)
{
    vcassert(dev < TIM_NUMOF);

    /* remember the interrupt context */
    _isr_tim_ctx[dev].callback = callback;
    _isr_tim_ctx[dev].arg = arg;

    /* enable the peripheral clock */
    uint32_t temp = VC_MISC2->PCLKEN;
    temp |= MISC2_PCLKEN_TIMER_Enabled;
    VC_MISC2->CLKEN_UNLOCK = MISC2_CLKEN_UNLOCK_UNLOCK_KEY;
    VC_MISC2->PCLKEN = temp;

    /* only support 1 MHz frequency base */
    vcassert(freq == 1000000ul);

    /* config pwm control register */
    temp = VC_PWM(dev)->CTL;

    temp &= ~PWM_CTL_TSEL_Msk;
    temp &= ~PWM_CTL_ID_Msk;

    temp |= PWM_CTL_TSEL_PCLK;
    temp |= PWM_CTL_ID_CLKDIV16; /* (SystemCoreClock / 2 (APBDIV)) / 16 = (39.3216 / 2) / 16 = ~1MHz */

    VC_PWM(dev)->CTL = temp;

    /* start pwm timer */
    vctim_start(dev);

    return 0;
}

int vctim_set(vctim_t dev, unsigned channel, unsigned int timeout)
{
    vcassert(dev < TIM_NUMOF && channel < TIM_CHAN_NUMOF);

    /* config capture/compare register (ccr) period */
    VC_PWM(dev)->CCR[channel] = timeout;

    /* enable capture/compare interrupt */
    uint32_t temp = VC_PWM(dev)->CCTL[channel];

    temp &= ~PWM_CCTL_CCIE_Msk;
    temp |= PWM_CCTL_CCIE_Enabled;

    VC_PWM(dev)->CCTL[channel] = temp;

    /* enable global timer interrupt */
    TIM_NVIC_EnableIRQ(_tim_irqn[dev]);

    return 0;
}

int vctim_set_absolute(vctim_t dev, unsigned channel, unsigned int value)
{
    uint16_t now = vctim_read(dev);
    uint32_t target = now + value;
    if (target > 0xffff)
    {
        target = target - 0xffff;
    }
    return vctim_set(dev, channel, target);
}

int vctim_clear(vctim_t dev, unsigned channel)
{
    vcassert(dev < TIM_NUMOF && channel < TIM_CHAN_NUMOF);

    /* clear capture/compare register period to it's default value */
    VC_PWM(dev)->CCR[channel] = (PWM_CCR_CCR_Msk);

    /* clear pwm counter */
    uint32_t temp = VC_PWM(dev)->CTL;

    temp &= ~PWM_CTL_CLR_Msk;
    temp |= PWM_CTL_CLR_Enabled;

    VC_PWM(dev)->CTL = temp;

    return 0;
}

uint32_t vctim_read(vctim_t dev)
{
    return VC_PWM(dev)->TAR;
}

void vctim_start(vctim_t dev)
{
    vcassert(dev < TIM_NUMOF);

    uint32_t temp = VC_PWM(dev)->CTL;

    temp &= ~PWM_CTL_MC_Msk;
    temp |= PWM_CTL_MC_Continous;

    VC_PWM(dev)->CTL = temp;
}

void vctim_stop(vctim_t dev)
{
    vcassert(dev < TIM_NUMOF);

    uint32_t temp = VC_PWM(dev)->CTL;

    temp &= ~PWM_CTL_MC_Msk;
    temp |= PWM_CTL_MC_Stop;

    VC_PWM(dev)->CTL = temp;
}

static void _irq_tim_handler(vctim_t dev)
{
    uint32_t temp = 0;

    if ((VC_PWM(dev)->CTL & PWM_CTL_IFG_Msk) != 0)
    {
        /* clear IFG interrupt flag */
        temp = VC_PWM(dev)->CTL;
        temp |= PWM_CTL_IFG_Msk;
        VC_PWM(dev)->CTL = temp;
        return;
    }

    for (uint8_t ch = 0; ch < TIM_CHAN_NUMOF; ch++)
    {
        if ((VC_PWM(dev)->CCTL[ch] & PWM_CCTL_CCIFG_Msk) != 0)
        {
            /* clear CCIFG interrupt flag */
            temp = VC_PWM(dev)->CCTL[ch];
            temp |= PWM_CCTL_CCIFG_Msk;
            VC_PWM(dev)->CCTL[ch] = temp;
            if (_isr_tim_ctx[dev].callback != NULL && VC_PWM(dev)->CCR[ch] != 0)
            {
                _isr_tim_ctx[dev].callback(_isr_tim_ctx[dev].arg, ch);
                cpu_end_of_isr(); /* notify app or rtos we are at the end of isr */
                break;
            }
        }
    }
}

/* PWM TIMER interrupt function entry */
void isr_pwm0(void)
{
    _irq_tim_handler(TIM_DEV(0));
}

void isr_pwm1(void)
{
    _irq_tim_handler(TIM_DEV(1));
}

void isr_pwm2(void)
{
    _irq_tim_handler(TIM_DEV(2));
}

void isr_pwm3(void)
{
    _irq_tim_handler(TIM_DEV(3));
}
