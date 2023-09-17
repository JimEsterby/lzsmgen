# Test Specification - State Machine Generator Application
## 1 Introduction

This document is intended to elaborate the verification/validation of the application.
---
## 2 Test Cases
| Test Case 1 | |
| --- | --- |
| Brief description | Start the application on Microsoft Windows. |
| Reason for test | Establish that GUI correctly integrated into the application. |
| Type | **System** |
| Map to user story | [KAN-7 Start GUI](https://jde-psu.atlassian.net/browse/KAN-7) |
#### Steps
1. Copy application executable to accessible directory.
2. Double-click application icon. |
#### Expected results
The application window opens in a non-minimized state.

---

| Test Case 2 | |
| --- | --- |
| Brief description | Start the application on Linux. |
| Reason for test | Establish that GUI correctly integrated into the application. |
| Type | **System** |
| Map to user story | [KAN-7 Start GUI](https://jde-psu.atlassian.net/browse/KAN-7) |
#### Steps
1. Copy application executable to accessible directory.
2. Single-click application icon. (Note that the test is designed for a 32-bit Linux kernel 4.10 using Kubuntu 17.04 as a window manager. Linux systems can also be configured to use double-clicks for opening applications.)
#### Expected results
The application window opens in a non-minimized state.

---

| Test Case 3 | |
| --- | --- |
| Brief description | Close the application on Microsoft Windows. |
| Reason for test | Establish that GUI correctly integrated into the application. |
| Type | **System** |
| Map to user story | [KAN-17 Program termination](https://jde-psu.atlassian.net/browse/KAN-17) |
#### Steps
On an open application window, click the 'X' icon in the upper right corner.

#### Expected results
The window disappears from the screen.

---

| Test Case 4 | |
| --- | --- |
| Brief description | Close the application on Linux. |
| Reason for test | Establish that GUI correctly integrated into the application. |
| Type | **System** |
| Map to user story | [KAN-17 Program termination](https://jde-psu.atlassian.net/browse/KAN-17) |
#### Steps
On an open application window, click the 'X' icon in the upper right corner.

#### Expected results
The window disappears from the screen.

---

| Test Case 5 | |
| --- | --- |
| Brief description | Check main window resizing behavior. |
| Reason for test | Ensure correct layout. |
| Type | **Unit** |
| Map to user story | [KAN-12 Add component](https://jde-psu.atlassian.net/browse/KAN-12) |
#### Steps
1. Capture lower right corner of the application window with the mouse.
2. Move the mouse (while holding the mouse button down).
#### Expected results
1. Editing section changes its width and height.
2. Palette section of window changes height, but does not change width until after the editing section has reached its minimum width.
3. Menu section only changes width, never height. 

---

| Test Case 6 | |
| --- | --- |
| Brief description | Check main window tile. |
| Reason for test | Ensure correct layout. |
| Type | **Unit** |
| Map to user story | [KAN-12 Add component](https://jde-psu.atlassian.net/browse/KAN-12) |
#### Steps
1. Capture ridge between the palette and editing section with the mouse.
2. Move the mouse (while holding the mouse button down).
#### Expected results
1. Editing section reduces its width by the same amount that the palette section increases width.
2. Editing section increases its width by the same amount that the palette section reduces width.
3. Menu section does not change. 

---




