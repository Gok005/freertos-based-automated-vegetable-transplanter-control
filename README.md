# FreeRTOS-Based Automated Vegetable Transplanter

**Deterministic Motor Control & Sequencing System**

## Overview

This project implements a **real-time motor control system** for an **automated vegetable transplanter** using **FreeRTOS**.
The machine coordinates multiple actuators—servo, pickup arm, leadscrew, and conveyor—under strict timing and sequencing constraints to ensure **accurate, repeatable, and safe transplanting** of saplings.

The core challenge addressed is **synchronous control of multiple motors with deterministic behavior**, something that becomes unreliable with a simple super-loop architecture. FreeRTOS is used to manage concurrency, task prioritization, and inter-task synchronization in a structured and scalable way.

---

## Why RTOS?

A traditional `while(1)` loop becomes fragile when:

* Multiple motors must run **simultaneously**
* Certain actions must **wait** for others to complete
* Timing violations can cause **mechanical damage**
* Batch-based logic (cycle counting and direction reversal) is required

FreeRTOS enables:

* Deterministic task scheduling
* Clean separation of responsibilities
* Safe inter-task communication
* Predictable system behavior under load

---

## System Architecture

### Major Components

* **Microcontroller** – Runs FreeRTOS scheduler and control logic
* **Servo Motor** – Controls gripper open/close
* **Pickup Arm Motor** – Forward and backward motion for sapling handling
* **Leadscrew Motor** – Controls linear positioning and depth
* **Conveyor Motor** – Advances sapling tray after batch completion
* **Sensors** – Limit switches / encoders for positional feedback

Each actuator is controlled by an **independent RTOS task**, coordinated through synchronization primitives.

---

## Task Design

### 1. Servo Task

* Controls gripper open and close operation
* Executes at defined points in the transplant cycle
* Must complete before pickup arm retraction

**RTOS Role:**
Blocking task triggered by synchronization events

---

### 2. Pickup Arm Task

* Handles forward motion to place sapling
* Handles backward motion after release
* Operates in coordination with servo and leadscrew

**RTOS Role:**
Time-sensitive task synchronized using semaphores / event flags

---

### 3. Leadscrew Task

* Runs in parallel with pickup arm during planting
* Direction reverses after a fixed number of cycles
* Remains idle during pickup retraction phase

**RTOS Role:**
State-driven task with cycle counter logic

---

### 4. Conveyor Task

* Activates only after completion of a full batch
* Advances tray to next sapling position

**RTOS Role:**
Lowest-priority task, event-triggered

---

## Operational Sequence (State Flow)

The system follows a deterministic state sequence:

1. Servo closes gripper
2. Pickup arm moves forward
3. Leadscrew moves simultaneously
4. Servo opens gripper
5. Pickup arm retracts
6. Steps 1–5 repeat **7 cycles**
7. Conveyor advances once
8. Leadscrew direction reverses
9. Next 7 cycles execute
10. Conveyor advances again
11. System repeats continuously

This sequence is implemented as a **state-driven control flow**, not delay-based logic.
---
## Motion Control & Timing Design
Stepper motor speed in this system is controlled by the frequency of STEP pulses delivered to the motor driver.
Each STEP pulse advances the motor by one discrete step.

The motor speed is therefore inversely proportional to the inter-pulse delay:

Speed ∝ 1 / pulse_delay

By dynamically adjusting the time delay between successive STEP pulses, smooth acceleration and deceleration are achieved without relying on blocking delays or busy loops.

Acceleration Using Time-Domain Pulse Scheduling
Acceleration is implemented by gradually reducing the inter-pulse delay during motor operation.
Each motor task maintains a time-domain delay variable (currentDelayUs) that is updated incrementally on every step:

Large delay → low speed (start)

Small delay → high speed (cruise)

This approach ensures:
* Deterministic timing
* Smooth acceleration
* No missed scheduler deadlines
  Example acceleration profile:
2000 µs → 1800 µs → 1600 µs → … → 500 µs

RTOS-Safe Pulse Generation (Why HAL_Delay Is Not Used)
Traditional delay-based loops using HAL_Delay() are avoided, as they block the RTOS scheduler and introduce timing jitter.

Instead, each motor task uses vTaskDelayUntil(), which allows precise periodic execution while yielding control back to the scheduler.

This ensures that:
* Other tasks continue to run
* Timing remains deterministic under load
* Parallel motor operation is reliable

Motion Profiles (Separation of Behavior and Execution)
Motor acceleration parameters are defined using motion profiles, which are passed from the Sequencer task to individual motor tasks.

A motion profile defines:
* Initial delay (start speed)
* Minimum delay (maximum speed)
* Acceleration rate

This separation allows the system to:
* Reuse acceleration logic across motors
* Modify behavior without changing motor task code
* Maintain a clean separation between what the machine does and how motors execute it

Parallel and Sequential Motion Coordination
The system supports both parallel and sequential motor operation:
* Pickup arm and leadscrew run in parallel during planting
* Pickup retracts while the leadscrew remains idle
* Conveyor advances only after completion of a batch

Synchronization is enforced using FreeRTOS Event Groups, ensuring that each phase completes before the next begins.

Timing Responsibility Breakdown
| Layer          | Responsibility                   |
| -------------- | -------------------------------- |
| Sequencer Task | Decides *when* motors start/stop |
| Motor Tasks    | Execute motion with acceleration |
| Motion Profile | Defines speed & acceleration     |
| RTOS Scheduler | Guarantees timing determinism    |
| HAL            | Handles GPIO / timer hardware    |

This motion control approach ensures smooth acceleration, deterministic timing, and safe multi-motor coordination while remaining fully RTOS-compliant.
The design closely mirrors industrial motion-control systems used in CNC machines, robotics, and agricultural automation equipment.
---

## Inter-Task Communication & Synchronization

The system uses:

* **Binary semaphores** for task synchronization
* **Event flags / notifications** for phase completion
* **Shared state variables** protected by RTOS primitives

Design goals:

* No busy-waiting
* No unsafe global variable access
* Clear ownership of hardware resources

---

## Safety & Fault Handling

Basic safety mechanisms are incorporated:

* Power-on safe state (all motors disabled)
* Emergency stop handling
* Timeout detection for motor motion
* Limit switch validation
* Controlled task shutdown on fault detection

These mechanisms prevent:

* Mechanical jamming
* Over-travel
* Continuous motor stalling

---

## Code Structure

```
/Core
 ├── Src
 │   ├── main.c
 │   ├── freertos.c
 │   ├── servo_task.c
 │   ├── pickup_task.c
 │   ├── leadscrew_task.c
 │   └── conveyor_task.c
 └── Inc
     ├── system_state.h
     ├── motor_control.h
     └── task_config.h

/Drivers
/docs
README.md
```

Each source file has **single responsibility** and minimal coupling.

---

## Key Engineering Concepts Demonstrated

* FreeRTOS task scheduling and prioritization
* Real-time synchronization using semaphores and events
* State-machine-based control design
* Motor sequencing under timing constraints
* Embedded safety and fault handling principles

---

## Future Improvements

* Encoder-based closed-loop motor control
* PID control for leadscrew positioning
* Non-volatile storage of cycle count
* Watchdog-based fault recovery
* Modular HAL abstraction layer

---

## Author

**Gokul Shanmugam**
Electronics & Communication Engineering
Focus: Embedded Systems, RTOS, Motor Control

---

