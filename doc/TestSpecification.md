# Test Specification - State Machine Generator Application
## 1 Introduction
This document is intended to elaborate the verification/validation of the application.
---
## 2 Test Cases
### Test Case 1
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
### Test Case 2
1. Brief description: Start the application on Linux.
2. Reason for test: Establish that GUI correctly integrated into the application.
3. Type: System
4. Map to user story: [KAN-7 Start GUI](https://jde-psu.atlassian.net/browse/KAN-7)
5. Steps:
- Copy application executable to accessible directory.
- Single-click application icon. (Note that the test is designed for a 32-bit Linux kernel 4.10 using Kubuntu 17.04 as a window manager. Linux systems can also be configured to use double-clicks for opening applications.)
6. Expected results: The application window opens in a non-minimized state.
---
### Test Case 3



