FreeRTOS-Based Automated Vegetable Transplanter
Deterministic Motor Control & Sequencing System

Overview

This project implements a **real-time motor control system** for an **automated vegetable transplanter** using **FreeRTOS**.
The machine coordinates multiple actuators—servo, pickup arm, leadscrew, and conveyor—under strict timing and sequencing constraints to ensure **accurate, repeatable, and safe transplanting** of saplings.

The core challenge addressed is **synchronous control of multiple motors with deterministic behavior**, something that becomes unreliable with a simple super-loop architecture. FreeRTOS is used to manage concurrency, task prioritization, and inter-task synchronization in a structured and scalable way.

---

Why RTOS?

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

System Architecture

Major Components
* Microcontroller – Runs FreeRTOS scheduler and control logic
* Servo Motor – Controls gripper open/close
* Pickup Arm Motor – Forward and backward motion for sapling handling
* Leadscrew Motor – Controls linear positioning and depth
* Conveyor Motor – Advances sapling tray after batch completion
* Sensors – Limit switches / encoders for positional feedback

Each actuator is controlled by an **independent RTOS task**, coordinated through synchronization primitives.

---

Task Design

1. Servo Task
* Controls gripper open and close operation
* Executes at defined points in the transplant cycle
* Must complete before pickup arm retraction

RTOS Role
Blocking task triggered by synchronization events

---

2. Pickup Arm Task
* Handles forward motion to place sapling
* Handles backward motion after release
* Operates in coordination with servo and leadscrew

RTOS Role
Time-sensitive task synchronized using semaphores / event flags

---

3. Leadscrew Task
* Runs in parallel with pickup arm during planting
* Direction reverses after a fixed number of cycles
* Remains idle during pickup retraction phase

RTOS Role
State-driven task with cycle counter logic

---

4. Conveyor Task
* Activates only after completion of a full batch
* Advances tray to next sapling position

RTOS Role:
Lowest-priority task, event-triggered

---

Operational Sequence (State Flow)

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

Inter-Task Communication & Synchronization

The system uses:
* Tasks notifications for scheduling
* Shared state variables protected by RTOS primitives

Design goals:
* No busy-waiting
* No unsafe global variable access
* Clear ownership of hardware resources

---

Safety & Fault Handling

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

Code Structure

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

Key Engineering Concepts Demonstrated

* FreeRTOS task scheduling and prioritization
* Real-time synchronization using semaphores and events
* State-machine-based control design
* Motor sequencing under timing constraints
* Embedded safety and fault handling principles

---

Future Improvements

* Encoder-based closed-loop motor control
* PID control for leadscrew positioning
* Non-volatile storage of cycle count
* Watchdog-based fault recovery
* Modular HAL abstraction layer

---
Author
Gokul Shanmugam
Electronics & Communication Engineering
Focus: Embedded Systems, RTOS, Motor Control
