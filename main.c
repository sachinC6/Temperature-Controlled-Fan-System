// Temperature-Controlled Fan System - Embedded C for STM32 Nucleo
// Based on NIELIT Course: C basics, control structures, arrays, Embedded C, GPIO/ADC (Days 1-5)
// Developed by Sachin Chandra, Batch-31

#include "stm32g4xx.h"
#include "stm32g4xx_hal.h"

// Pin Definitions (Day 5: GPIO/ADC basics)
#define TEMP_SENSOR_PIN GPIO_PIN_0  // PA0 - ADC input for LM35
#define RED_LED_PIN GPIO_PIN_0      // PB0 - Output (hot status)
#define GREEN_LED_PIN GPIO_PIN_1    // PB1 - Output (cool status)
#define FAN_PWM_CHANNEL TIM_CHANNEL_1  // TIM2 CH1 for PWM (e.g., PA5)

// Global Variables (Day 1-2: Variables, datatypes)
#define NUM_READINGS 10
volatile uint16_t tempReadings[NUM_READINGS];  // Array for averaging (Day 3: Arrays)
volatile int currentIndex = 0;
volatile int fanSpeed = 0;  // PWM duty cycle (0-100%)
volatile float tempThresholdHot = 30.0f;  // Celsius

ADC_HandleTypeDef hadc1;  // ADC handle
TIM_HandleTypeDef htim2;  // PWM timer handle

// Function to initialize peripherals (Day 5: GPIO/ADC drivers)
void SystemInit_Custom() {
    // GPIO Init
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // Outputs for LEDs
    GPIO_InitStruct.Pin = RED_LED_PIN | GREEN_LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // ADC Init (configure in STM32CubeIDE: ADC1, PA0 continuous)
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.ContinuousConvMode = ENABLE;
    HAL_ADC_Init(&hadc1);

    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_5;  // PA0 is CH5 on G4
    sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // PWM Init (TIM2 CH1, configure in IDE: 1kHz freq)
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 80 - 1;  // For 1MHz timer clock
    htim2.Init.Period = 1000 - 1;   // For 1kHz PWM
    HAL_TIM_PWM_Init(&htim2);
    HAL_TIM_PWM_Start(&htim2, FAN_PWM_CHANNEL);
}

// Function to read and average temperature (Day 3: Arrays, Day 2: Loops)
float readAverageTemp() {
    uint32_t sum = 0;
    for (int i = 0; i < NUM_READINGS; i++) {  // Loop (Day 2)
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        tempReadings[currentIndex] = HAL_ADC_GetValue(&hadc1);
        sum += tempReadings[currentIndex];
        currentIndex = (currentIndex + 1) % NUM_READINGS;
    }
    float avg = (sum / NUM_READINGS) * 3.3 / 4096 * 100;  // LM35: 10mV/°C, 12-bit ADC
    return avg;
}

// Function to control fan and LEDs (Day 1-2: Functions, Day 2: Control structures)
void controlSystem(float temp) {
    if (temp > tempThresholdHot) {  // Conditional flow (Day 2)
        fanSpeed = 100;  // Full speed
        HAL_GPIO_WritePin(GPIOB, RED_LED_PIN, GPIO_PIN_SET);   // Red on
        HAL_GPIO_WritePin(GPIOB, GREEN_LED_PIN, GPIO_PIN_RESET); // Green off
    } else {
        fanSpeed = 20;   // Low speed
        HAL_GPIO_WritePin(GPIOB, RED_LED_PIN, GPIO_PIN_RESET);   // Red off
        HAL_GPIO_WritePin(GPIOB, GREEN_LED_PIN, GPIO_PIN_SET);   // Green on
    }
    __HAL_TIM_SET_COMPARE(&htim2, FAN_PWM_CHANNEL, (fanSpeed * 10));  // Set PWM duty (0-1000)
}

int main(void) {
    HAL_Init();
    SystemClock_Config();  // Generate in STM32CubeIDE for clock stability
    SystemInit_Custom();   // Setup ADC/PWM/GPIO

    while (1) {  // Infinite loop (Day 2: Loop control - while)
        float currentTemp = readAverageTemp();  // Read sensor (Day 5: ADC input)
        controlSystem(currentTemp);             // Apply logic

        HAL_Delay(1000);  // Poll every second (adjust for real-time)
    }
}
