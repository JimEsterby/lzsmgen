# Test Specification - State Machine Generator Application
## 1 Introduction
### 1.1 Purpose
This document is intended to elaborate the verification/validation of the application.
### 1.2 Architecture
The application is divided into the standard model-view-controller design pattern. System tests and user acceptance tests involve 2 or more of the model, view, or controller entities. Unit tests check 1 or part of 1 entity.

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

| Test Case 7 | |
| --- | --- |
| Brief description | Check palette selection. |
| Reason for test | Ensure new selection appears in edit section. |
| Type | **Unit** |
| Map to user story | [KAN-12 Add component](https://jde-psu.atlassian.net/browse/KAN-12) |
#### Steps
Select component with mouse.
#### Expected results
Component appears in edit section.

---

| Test Case 8 | |
| --- | --- |
| Brief description | Check palette selection. |
| Reason for test | Ensure new selection communication to model. |
| Type | **System** |
| Map to user story | [KAN-12 Add component](https://jde-psu.atlassian.net/browse/KAN-12) |
#### Steps
Select component with mouse.
#### Expected results
Component appears in edit section and data is updated in the model. TODO: How is data to be checked in the model?

---

| Test Case 9 | |
| --- | --- |
| Brief description | A "create" action is cancelled. |
| Reason for test | Check response of system to cancelling a "create" action. |
| Type | **System** |
| Map to user story | [KAN-11 Create diagram](https://jde-psu.atlassian.net/browse/KAN-11) |
#### Steps
1. Add one or more components to the edit area by clicking on components in the palette area.
2. Select "New" command from application menu.
3. When a dialog appears, select "Cancel" on the dialog.
#### Expected results
1. Dialog appears after step 2.
2. The dialog closes.
3. The edit area remains as it was after step 1.
4. Model data remains as it was after step 1.

---

| Test Case 10 | |
| --- | --- |
| Brief description | A "create" action is initiated despite unsaved changes. |
| Reason for test | Check response of system to when the user elects to lose changes. |
| Type | **System** |
| Map to user story | [KAN-11 Create diagram](https://jde-psu.atlassian.net/browse/KAN-11) |
#### Steps
1. Add one or more components to the edit area by clicking on components in the palette area.
2. Select "New" command from application menu.
3. When a dialog appears, select "OK" or equivalent button on the dialog.
#### Expected results
1. Dialog appears after step 2.
2. The dialog closes.
3. The edit area clears.
4. Model data is reset.

---

| Test Case 11 | |
| --- | --- |
| Brief description | A "create" action when the edit area is empty or the model data has been saved. |
| Reason for test | Check expected use of the "create" action. |
| Type | **System** |
| Map to user story | [KAN-11 Create diagram](https://jde-psu.atlassian.net/browse/KAN-11) |
#### Steps
1. Leave the edit area blank and do not load a model.
2. Select "New" command from application menu.
#### Expected results
No dialog appears.

---

| Test Case 12 | |
| --- | --- |
| Brief description | Create action |
| Reason for test | Ensure that create action protects the user from losing data. |
| Type | **User Acceptance** |
| Map to user story | [KAN-11 Create diagram](https://jde-psu.atlassian.net/browse/KAN-11) |
#### Steps
Select the "New" command under a variety of conditions:
1. Loaded model file with no unsaved changes
2. Loaded model file with unsaved changes
3. Empty edit area, etc.
#### Expected results
The program never loses changes, except by explicit command of the user.

---



