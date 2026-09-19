# ESP32 Secure Safe / Lock System (ESP-IDF)

A secure electronic lock and password validation system developed using **ESP-IDF** and raw **C** for the ESP32 microcontroller. This project focuses on low-level embedded systems development, direct GPIO configuration, pointer-based array manipulation, and hardware-software integration.

## 🚀 Features
* **ESP-IDF Framework:** Developed natively using Espressif components and FreeRTOS task delays without Arduino abstractions.
* **Low-Level C Implementation:** Utilizes pointer arithmetic to efficiently traverse and validate user button inputs against stored password arrays.
* **Internal Pull-Up Configuration:** Configures GPIO input modes with internal pull-up resistors, eliminating the need for external hardware resistors.
* **Visual Feedback System:** Dual-LED status indicators for correct (Green) and incorrect (Red) password combinations.

---

## 📌 Hardware Pinout

| Component | GPIO Pin | Configuration |
| :--- | :--- | :--- |
| **Button 1** | GPIO 18 | Input (Internal Pull-Up Enabled) |
| **Button 2** | GPIO 19 | Input (Internal Pull-Up Enabled) |
| **Green LED (LED_1)** | GPIO 21 | Output |
| **Red LED (LED_2)** | GPIO 23 | Output |

*Note: The push buttons are connected between the specified GPIO pins and **GND**.*

---

## 🛠️ Code Architecture & Logic
* **Password Verification:** User inputs are captured via button polling, stored in a temporary buffer, and compared using pointer-based array traversal (`*ui != *pi`) to verify sequence accuracy.
* **Debounce & Timing:** Polling delay integration using FreeRTOS ticks (`vTaskDelay`) to handle simple contact bounce and ensure reliable trigger detection.

---
