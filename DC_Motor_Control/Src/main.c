#include <stm32f4xx.h>

#define GPIOAEN (1U<<0)  // Activation horloge GPIOA
#define TIM2EN  (1U<<0)  // Activation horloge TIM2
#define TIM4EN  (1U<<2)  // Activation horloge TIM4

void gpio_init(void);
void TIM2_PWM_init(void);
void TIM4_ms_Delay(uint16_t delay);

void gpio_init(void) {
    // Activer l'horloge pour GPIOA
    RCC->AHB1ENR |= GPIOAEN;

    // PA2 en mode Alternate Function (TIM2_CH3)
    GPIOA->MODER &= ~(3U << 4); // Clear
    GPIOA->MODER |=  (2U << 4); // Mode AF (10 en binaire)

    // Configurer PA2 en Alternate Function 1 (AF1 pour TIM2)
    GPIOA->AFR[0] &= ~(0xF << 8); // Efface AF
    GPIOA->AFR[0] |= (1U << 8);   // PA2 -> AF1 (TIM2_CH3)
}

void TIM2_PWM_init(void) {
    // Activer l'horloge pour TIM2
    RCC->APB1ENR |= TIM2EN;

    // Régler la fréquence du PWM
    TIM2->PSC = 16 - 1;    // Divise 16MHz par 16 = 1MHz
    TIM2->ARR = 1000 - 1;  // 1 kHz (période 1ms)

    // Initialisation du compteur
    TIM2->CNT = 0;

    // Configurer le mode PWM sur CH3 (PA2)
    TIM2->CCMR2 &= ~(7U << 4);  // Effacer les bits de mode (4-6)
    TIM2->CCMR2 |= (6U << 4);   // PWM Mode 1 (110 en binaire)
    TIM2->CCMR2 |= (1U << 3);   // Activer le preload sur CCR3

    // Activer la sortie CH3
    TIM2->CCER |= (1U << 8);

    // Initialisation à 50% de PWM
    TIM2->CCR3 = 500;

    // Activer le timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM4_ms_Delay(uint16_t delay) {
    RCC->APB1ENR |= TIM4EN;  // Activer TIM4
    TIM4->PSC = 16000 - 1;   // 16MHz / 16000 = 1kHz (1ms)
    TIM4->ARR = delay;
    TIM4->CNT = 0;
    TIM4->CR1 |= 1;          // Démarrer
    while (!(TIM4->SR & TIM_SR_UIF)) {}  // Attendre overflow
    TIM4->SR &= ~(1U << 0);  // Reset flag
}

int main(void) {
    gpio_init();
    TIM2_PWM_init();

    while (1) {
        TIM2->CCR3 = 200;  // 20% PWM - LED faible
        TIM4_ms_Delay(2000);

        TIM2->CCR3 = 500;  // 50% PWM - LED moyenne
        TIM4_ms_Delay(2000);

        TIM2->CCR3 = 900;  // 90% PWM - LED forte
        TIM4_ms_Delay(2000);
    }

    return 0;
}
