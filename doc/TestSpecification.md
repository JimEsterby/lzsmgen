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
1. GUI: Component immediately appears in the edit section of the application window.
2. Back-end: Component is added to the appropriate back-end container. Now this container is the Diagram class.

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
| Brief description | A "create" action when the edit area is empty. |
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

| Test Case 13 | |
| --- | --- |
| Brief description | A "create" action when model data has been saved. |
| Reason for test | Check expected use of the "create" action. |
| Type | **System** |
| Map to user story | [KAN-11 Create diagram](https://jde-psu.atlassian.net/browse/KAN-11) |
#### Steps
1. Load a model. Note: [KAN-10](https://jde-psu.atlassian.net/browse/KAN-10) is required to be implemented for this.
2. Select "New" command from application menu.
#### Expected results
1. No dialog appears.
2. Model file is unloaded.
3. Edit area is cleared.

---

| Test Case 14 | |
| --- | --- |
| Brief description | Move component within editing area. |
| Reason for test | Check move functionality. |
| Type | **Unit** |
| Map to user story | [KAN-13 Move component](https://jde-psu.atlassian.net/browse/KAN-13) |
#### Steps
1. Add component to editing area. Note: [KAN-12](https://jde-psu.atlassian.net/browse/KAN-12) is required to be implemented.
2. Select component with mouse cursor.
3. While holding mouse button down, move component around the editing area.

#### Expected results
1. At step 2, some indication of selection shows (highlighting?)
2. During step 3, the component moves with the mouse cursor.
3. Note: If the component is moved beyond the editing area, scroll bars appear.

---

| Test Case 15 | |
| --- | --- |
| Brief description | Resize component within editing area. |
| Reason for test | Check resize functionality. |
| Type | **Unit** |
| Map to user story | [KAN-13 Move component](https://jde-psu.atlassian.net/browse/KAN-13) |
#### Steps
1. Add component to editing area. Note: [KAN-12](https://jde-psu.atlassian.net/browse/KAN-12) is required to be implemented.
2. Select component with mouse cursor on a vertical edge.
3. Move the mouse with mouse button pressed.

#### Expected results
1. At step 2, some indication of selection shows (highlighting?)
2. During step 3, the component changes width with the mouse cursor.

---

| Test Case 16 | |
| --- | --- |
| Brief description | Resize component within editing area. |
| Reason for test | Check resize functionality. |
| Type | **Unit** |
| Map to user story | [KAN-13 Move component](https://jde-psu.atlassian.net/browse/KAN-13) |
#### Steps
1. Add component to editing area. Note: [KAN-12](https://jde-psu.atlassian.net/browse/KAN-12) is required to be implemented.
2. Select component with mouse cursor on a horizontal edge.
3. Move the mouse with mouse button pressed.

#### Expected results
1. At step 2, some indication of selection shows (highlighting?)
2. During step 3, the component changes height with the mouse cursor.

---

| Test Case 17 | |
| --- | --- |
| Brief description | Resize component within editing area. |
| Reason for test | Check resize functionality. |
| Type | **Unit** |
| Map to user story | [KAN-13 Move component](https://jde-psu.atlassian.net/browse/KAN-13) |
#### Steps
1. Add component to editing area. Note: [KAN-12](https://jde-psu.atlassian.net/browse/KAN-12) is required to be implemented.
2. Select component with mouse cursor on a corner.
3. Move the mouse with mouse button pressed.

#### Expected results
1. At step 2, some indication of selection shows (highlighting?)
2. During step 3, the component changes width and height with the mouse cursor.

---

| Test Case 18 | |
| --- | --- |
| Brief description | Resize transition component within editing area. |
| Reason for test | Check transition resize functionality. |
| Type | **Unit** |
| Map to user story | [KAN-13 Move component](https://jde-psu.atlassian.net/browse/KAN-13) |
#### Steps
1. Add transition component to editing area. Note: [KAN-12](https://jde-psu.atlassian.net/browse/KAN-12) is required to be implemented.
2. Select transition with mouse cursor on an end-point vertex.
3. Move the mouse with mouse button pressed.

#### Expected results
1. At step 2, some indication of selection shows (highlighting?)
2. During step 3, the transition changes length and angle with the mouse cursor.

---

| Test Case 19 | |
| --- | --- |
| Brief description | Save newly created diagram to file |
| Reason for test | Check saving to new file |
| Type | **System** |
| Map to user story | [KAN-6 Diagram file save](https://jde-psu.atlassian.net/browse/KAN-6) |
#### Steps
1. Add components to editing area. Note: [KAN-12](https://jde-psu.atlassian.net/browse/KAN-12) is required to be implemented.
2. Select "Save" command from the menu.
3. Enter unique file name into dialog box that appears.
4. Select "OK" in dialog box.

#### Expected results
1. At step 2, a "File save as" dialog appears.
2. A file with the entered file name exists on the computer media.

---

| Test Case 20 | |
| --- | --- |
| Brief description | Save previously opened diagram |
| Reason for test | Check saving to file |
| Type | **System** |
| Map to user story | [KAN-6 Diagram file save](https://jde-psu.atlassian.net/browse/KAN-6) |
#### Steps
1. Copy a diagram file to a new name. On the Windows console, copy *diagram.json* *diagram2.json*.
2. Load diagram.json (need [KAN-10](https://jde-psu.atlassian.net/browse/KAN-10)).
2. Change the size of a component in the edit section.
3. Select "Save" command from the menu.

#### Expected results
1. *diagram.json* is different from *diagram2.json*.
2. The application provides an indication of saving.

---

| Test Case 21 | |
| --- | --- |
| Brief description | Save diagrams |
| Reason for test | Check saving to file |
| Type | **User Acceptance** |
| Map to user story | [KAN-6 Diagram file save](https://jde-psu.atlassian.net/browse/KAN-6) |
#### Steps
The "Save" menu command is selected under various conditions.

#### Expected results
Files are saved and the user receives notice of overwriting at appropriate times.

---

| Test Case 22 | |
| --- | --- |
| Brief description | Editing new component |
| Reason for test | Check for appropriate dialog pop-up |
| Type | **Unit** |
| Map to user story | [KAN-14 Edit component](https://jde-psu.atlassian.net/browse/KAN-14) |
#### Steps
Perform all steps for each component
1. Add component to edit area
2. Double click component

#### Expected results
The dialog unique to the component pops up.

---

| Test Case 23 | |
| --- | --- |
| Brief description | Editing component multiple times |
| Reason for test | Check for information retention |
| Type | **System** |
| Map to user story | [KAN-14 Edit component](https://jde-psu.atlassian.net/browse/KAN-14) |
#### Steps
Perform all steps for each component
1. Add component to edit area
2. Double click component
3. Enter values into dialog
4. Close with dialog "OK" button
5. Double click component again

#### Expected results
The second time the dialog pops up, its fields are already populated with the values entered the first time the dialog appeared.

---

| Test Case 24 | |
| --- | --- |
| Brief description | Editing component from a previously created diagram |
| Reason for test | Check for information retention |
| Type | **System** |
| Map to user story | [KAN-14 Edit component](https://jde-psu.atlassian.net/browse/KAN-14) |
#### Steps
After loading a diagram file, double click each unique component.

#### Expected results
Components fields are already populated with the values stored in the diagram file.

---

| Test Case 25 | |
| --- | --- |
| Brief description | Generate code from correct diagram |
| Reason for test | Main function of the application. |
| Type | **User Acceptance** |
| Map to user story | [KAN-19 Code generation](https://jde-psu.atlassian.net/browse/KAN-19) |
#### Steps
1. Create simple diagram with 2 states with 1 transition connecting the states.
2. Save as diagram file.
3. Select the "Generate code" command.
 
#### Expected results
1. Resulting C-code files should compile without errors.
2. If the C-code is linked with a driver program, the resulting application should operate in accordance with the diagram.

| Test Case 26 | |
| --- | --- |
| Brief description | Generate code from unsaved diagram |
| Reason for test | Check user prompt |
| Type | **System** |
| Map to user story | [KAN-19 Code generation](https://jde-psu.atlassian.net/browse/KAN-19) |
#### Steps
1. Create simple diagram with 2 states with 1 transition connecting the states. Do not save.
2. Select the "Generate code" command.

#### Expected results
A prompt to save the diagram pops up.

---

| Test Case 27 | |
| --- | --- |
| Brief description | Response to incorrect diagram |
| Reason for test | Check that application handles incorrect diagrams gracefully. |
| Type | **User Acceptance** |
| Map to user story | [KAN-19 Code generation](https://jde-psu.atlassian.net/browse/KAN-19) |
#### Steps
1. Create simple diagram with 2 states and no transitions.
2. Save as diagram file.
3. Select the "Generate code" command.

#### Expected results
1. No files are generated.
2. The user is informed of a problem with the diagram.

---

| Test Case 28 | |
| --- | --- |
| Brief description | Component deletion. |
| Reason for test | Check component deletion. |
| Type | **System** |
| Map to user story | [KAN-12 Add component](https://jde-psu.atlassian.net/browse/KAN-12) |
#### Steps
1. Select component with mouse.
2. Select "delete" command
#### Expected results
1. GUI: Component no longer shows on the application.
2. Back-end: Component is removed from the appropriate back-end container. Now this container is the Diagram class.

---

| Test Case 29 | Automated |
| --- | --- |
| Brief description | Application behavior if scripting not working. |
| Reason for test | Assure no crash if script is not loadable |
| Type | **Unit** |
| Map to user story | [KAN-7 Start GUI](https://jde-psu.atlassian.net/browse/KAN-7) |
| File | [test_model.cpp](../test/test_model.cpp) |
| Name | failed_script001 |

If the base script cannot be loaded, the method "file_exists" (class Model) which relies on the script should return false.

---

| Test Case 30 | Automated |
| --- | --- |
| Brief description | Application behavior if scripting not working. |
| Reason for test | Means for informing user of scripting failure is available. |
| Type | **Unit** |
| Map to user story | [KAN-7 Start GUI](https://jde-psu.atlassian.net/browse/KAN-7) |
| File | [test_model.cpp](../test/test_model.cpp) |
| Name | failed_script002 |

If the base script cannot be loaded, a flag in the Model class may be used to inform the user.

---

| Test Case 31 | Automated |
| --- | --- |
| Brief description | Successful opening of a diagram file. |
| Reason for test | Diagram files may be opened. |
| Type | **Unit** |
| Map to user story | [KAN-10 Open diagram](https://jde-psu.atlassian.net/browse/KAN-10) |
| File | [test_model.cpp](../test/test_model.cpp) |
| Name | opensuccess001 |

Checks the normal operation of a user opening a file for the Model class.

---

| Test Case 32 | Automated |
| --- | --- |
| Brief description | Attempt to open "nothing" |
| Reason for test | Check for graceful failure if method open_file called without a file name. |
| Type | **Unit** |
| Map to user story | [KAN-10 Open diagram](https://jde-psu.atlassian.net/browse/KAN-10) |
| File | [test_model.cpp](../test/test_model.cpp) |
| Name | openfailure001 |

Checks the case of a user opening "NULL" for the Model class. There may be some GUI code to prevent this, but it's better not to rely on it.

---

| Test Case 33 | Automated |
| --- | --- |
| Brief description | Attempt to open non-existent file |
| Reason for test | Check for graceful failure if method open_file called with bogus file name. |
| Type | **Unit** |
| Map to user story | [KAN-10 Open diagram](https://jde-psu.atlassian.net/browse/KAN-10) |
| File | [test_model.cpp](../test/test_model.cpp) |
| Name | openfailure002 |

Checks the case of a user opening a non-existent file for the Model class.

---

| Test Case 34 | Automated |
| --- | --- |
| Brief description | Check default module for code generation |
| Reason for test | Check that module base names are determined correctly from the diagram file name |
| Type | **Unit** |
| Map to user story | [KAN-19 Open diagram](https://jde-psu.atlassian.net/browse/KAN-19) |
| File | [test_model.cpp](../test/test_model.cpp) |
| Name | basename001 |

Check for normal module base name determination by the Model class using convention diagram file name.

---

| Test Case 35 | |
| --- | --- |
| Brief description | Editing the dependencies of previously created diagram |
| Reason for test | Check for information retention |
| Type | **System** |
| Map to user story | [KAN-22 Externals in generated code](https://jde-psu.atlassian.net/browse/KAN-22) |
#### Steps
1. Load the file, "thermostat.json", located in the demos directory.
2. Select "Metadata" in the application menu.

#### Expected results
The text, "#include "sensors.h", is displayed in the Dependencies edit area of the popup dialog that appears.

---

| Test Case 36 | Automated |
| --- | --- |
| Brief description | Dependency code generation |
| Reason for test | Check that dependencies are properly written to C source code |
| Type | **Unit** |
| Map to user story | [KAN-22 Externals in generated code](https://jde-psu.atlassian.net/browse/KAN-22) |
| File | [test_filecallback.cpp](../test/test_filecallback.cpp) |
| Name | Dep_001 |

This is a text comparision of expected vs. actual text written.

---

| Test Case 37 | |
| --- | --- |
| Brief description | Editing the internal variables of previously created diagram |
| Reason for test | Check for information retention |
| Type | **System** |
| Map to user story | [KAN-86 Enable adding state variables](https://jde-psu.atlassian.net/browse/KAN-86) |
#### Steps
1. Load the file, "thermostat.json", located in the demos directory.
2. Select "Metadata" in the application menu.

#### Expected results
The text, "static uint16_t timer;", is displayed in the Internals edit area of the popup dialog that appears.

---

| Test Case 38 | Automated |
| --- | --- |
| Brief description | Internal variable code generation |
| Reason for test | Check that internal variables are properly written to C source code |
| Type | **Unit** |
| Map to user story | [KAN-86 Enable adding state variables](https://jde-psu.atlassian.net/browse/KAN-86) |
| File | [test_filecallback.cpp](../test/test_filecallback.cpp) |
| Name | Internal_001 |

This is a text comparision of expected vs. actual text written.

---

| Test Case 39 | |
| --- | --- |
| Brief description | Editing and saving the internal variables |
| Reason for test | Check that variables are saved to file |
| Type | **System** |
| Map to user story | [KAN-86 Enable adding state variables](https://jde-psu.atlassian.net/browse/KAN-86) |
#### Steps
1. Select "New" in the application menu to create a new diagram.
2. Add two states and one transition.
3. Select "Metadata".
4. In the dialog that appears, type "This is my variable" in the Dependencies edit area.
5. Select Ok on the dialog.
6. Save the diagram as a JSON file.
7. Open the saved JSON file and check for the typed text in the "internals" field.

#### Expected results
The text, "internals": "This is my variable", should be contained in the JSON file.

---

| Test Case 40 | |
| --- | --- |
| Brief description | Editing and saving the dependencies |
| Reason for test | Check that dependencies are saved to file |
| Type | **System** |
| Map to user story | [KAN-22 Externals in generated code](https://jde-psu.atlassian.net/browse/KAN-22) |
#### Steps
1. Select "New" in the application menu to create a new diagram.
2. Add two states and one transition.
3. Select "Metadata".
4. In the dialog that appears, type "#include "interface.h"" in the Dependencies edit area.
5. Select Ok on the dialog.
5. Save the diagram as a JSON file.
6. Open the saved JSON file and check for the typed text in the "dependencies" field.

#### Expected results
The text, "dependencies": "#include \"interface.h\"", should be contained in the JSON file.

---

| Test Case 41 | |
| --- | --- |
| Brief description | User is provided opportunity to cancel application exit |
| Reason for test | Check that dialog appears and the user may cancel if changes have not been saved. |
| Type | **User Acceptance** |
| Map to user story | [KAN-26 Unsaved changes](https://jde-psu.atlassian.net/browse/KAN-26) |
#### Steps
1. Open application.
2. Add two states and one transition.
3. Select "Exit" on the menu
4. When/if the dialog appears select "Cancel" on the dialog.

#### Expected results
Dialog appears when the user selects "Exit" and the application remains active after the user cancels. The dialog closes.

---

| Test Case 42 | |
| --- | --- |
| Brief description | User is provided opportunity to cancel application exit |
| Reason for test | Check that dialog appears and the user may save changes. |
| Type | **User Acceptance** |
| Map to user story | [KAN-26 Unsaved changes](https://jde-psu.atlassian.net/browse/KAN-26) |
#### Steps
1. Open application.
2. Add two states and one transition.
3. Select "Exit" on the menu.
4. When/if the dialog appears select "Save File" on the dialog.
5. When/if the file save dialog appears, save the file as tc42.json.

#### Expected results
Dialog appears when the user selects "Exit". The file tc42.json exists on the system and contains the state and transition data. 

---

| Test Case 43 | |
| --- | --- |
| Brief description | User is not provided opportunity to cancel application exit if there are not unsaved changes  |
| Reason for test | Check that dialog does not appear. |
| Type | **User Acceptance** |
| Map to user story | [KAN-26 Unsaved changes](https://jde-psu.atlassian.net/browse/KAN-26) |
#### Steps
1. Open application.
2. Open existing valid file (The file from test case 42, tc42.json, could be used).
3. Select "Exit" on the menu.

#### Expected results
Application exits normally with no dialog appearing. 

---

| Test Case 44 | |
| --- | --- |
| Brief description | User is provided opportunity to cancel application exit  |
| Reason for test | Check that user can choose to lose changes. |
| Type | **User Acceptance** |
| Map to user story | [KAN-26 Unsaved changes](https://jde-psu.atlassian.net/browse/KAN-26) |
#### Steps
1. Open application.
2. Open existing valid file (The file from test case 42, tc42.json, could be used).
3. Use the "Save As" menu command to save the file under a new name.
4. Resize one of the states.
5. Select "Exit" on the menu.
6. When/if dialog appears, select "Lose changes".

#### Expected results
Application exits. The original file from step 2 is identical to the new file created in step 3. (This can be checked quickly with a file compare tool like "fc" or "diff")

---

| Test Case 45 | Automated |
| --- | --- |
| Brief description | Destination state for a given transition |
| Reason for test | Check that code generation selects the correct destination state for a transition. |
| Type | **Unit** |
| Map to user story | [KAN-19 Code generation](https://jde-psu.atlassian.net/browse/KAN-19) |
| File | [test_diagram.cpp](../test/test_diagram.cpp) |
| Name | transition_dest001 |

Typical example from adaptive cruise control demo.

---

| Test Case 46 | Automated |
| --- | --- |
| Brief description | Destination state for a given transition |
| Reason for test | Check that code generation selects the correct destination state for a transition. |
| Type | **Unit** |
| Map to user story | [KAN-19 Code generation](https://jde-psu.atlassian.net/browse/KAN-19) |
| File | [test_diagram.cpp](../test/test_diagram.cpp) |
| Name | transition_dest002 |

Nested default states.

---

| Test Case 47 | Automated |
| --- | --- |
| Brief description | Destination state for a given transition |
| Reason for test | Check that code generation selects the correct destination state for a transition. |
| Type | **Unit** |
| Map to user story | [KAN-19 Code generation](https://jde-psu.atlassian.net/browse/KAN-19) |
| File | [test_diagram.cpp](../test/test_diagram.cpp) |
| Name | transition_dest003 |

Nested states.

---


