/* YuseiIto/stm32-blink | MIT License | https://github.com/YuseiIto/stm32-blink/blob/master/LICENSE */

#include <stdint.h>
#define mem(ADDR) *((volatile uint32_t *)(ADDR))

#define GPIOB_PORT_BASE 0x40020400U
#define GPIOB_MODER (GPIOB_PORT_BASE + (uint32_t)0x00)
#define GPIOB_OTYPER (GPIOB_PORT_BASE + (uint32_t)0x04)
#define GPIOB_PUPDR (GPIOB_PORT_BASE + (uint32_t)0x0C)
#define GPIOB_ODR (GPIOB_PORT_BASE + (uint32_t)0x14)

#define RCC_BASE 0x40023800U
#define RCC_AHBENR RCC_BASE + (uint32_t)0x30

int main(void)
{
  mem(RCC_AHBENR) |= (1 << 1);
  mem(GPIOB_MODER) = (0b01 << 2 * 7); // Set '01' to GPIOB port 7
  mem(GPIOB_OTYPER) = 0x0000;         // All-push pull
  mem(GPIOB_PUPDR) = 0x000000000;     // No pullup-pulldown

  int i = 1;

  while (1)
  {
    if (i > 500000)
    {
      i = 0;

      if (mem(GPIOB_ODR) & (1 << 7))
      {
        mem(GPIOB_ODR) &= ~(1 << 7);
      }
      else
      {
        mem(GPIOB_ODR) |= (1 << 7);
      }
    }
    i++;
  }
  return 0;
}