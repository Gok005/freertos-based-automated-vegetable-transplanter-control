/**
 * @file leadscrew_task.c
 * @brief FreeRTOS task for leadscrew motor control
 */

#include "leadscrew_task.h"

/* RTOS objects */
TaskHandle_t LeadscrewTaskHandle = NULL;

/* Internal state */
static system_state_t currentState = SYSTEM_INIT;

/* Control flags */
static volatile uint8_t leadscrewRunRequested = 0;
static volatile uint8_t leadscrewStopRequested = 0;
static volatile uint8_t leadscrewReverseRequested = 0;

void LeadscrewTask(void *argument)
{
    for (;;)
    {
        /* Block until a control request is received */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        if (leadscrewReverseRequested)
        {
            /* TODO: Reverse motor direction */
            leadscrewReverseRequested = 0;
            currentState = LEADSCREW_DIRECTION_CHANGE;
        }

        if (leadscrewRunRequested)
        {
            /* TODO: Start leadscrew motion */
            leadscrewRunRequested = 0;
        }

        if (leadscrewStopRequested)
        {
            /* TODO: Stop leadscrew motion */
            leadscrewStopRequested = 0;
        }
    }
}

/* API used by other tasks */

void Leadscrew_RequestStart(void)
{
    leadscrewRunRequested = 1;
    xTaskNotifyGive(LeadscrewTaskHandle);
}

void Leadscrew_RequestStop(void)
{
    leadscrewStopRequested = 1;
    xTaskNotifyGive(LeadscrewTaskHandle);
}

void Leadscrew_ReverseDirection(void)
{
    leadscrewReverseRequested = 1;
    xTaskNotifyGive(LeadscrewTaskHandle);
}

if (leadscrewReverseRequested)
{
    /* TODO: Reverse motor direction */
    leadscrewReverseRequested = 0;
    currentState = LEADSCREW_DIRECTION_CHANGE;

    xEventGroupSetBits(SystemEventGroup, EVT_LEADSCREW_DONE);
}

if (leadscrewRunRequested)
{
    /* TODO: Start leadscrew motion */
    leadscrewRunRequested = 0;

    xEventGroupSetBits(SystemEventGroup, EVT_LEADSCREW_DONE);
}

