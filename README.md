# 3004FinalProject-CES DEVICE
Team 18: TA Deen
Authors:
Julien Rougerie 101067032
Rinith Anand    100906754
Aaron Saville   101117379
Andrew Hall     101156505

Files Included:
QT: mainwindow.ui, CESDEVICE.pro, AlphaTest.pro, AlphaTest.pro.user, guiAssets.qrc
Headers: mainwindow.h, battery.h, countdownclock.h, record.h
CPP: main.cpp, mainwindow.cpp, countdownclock.cpp, battery.cpp, record.cpp.
Special Files: 12 sequence diagrams, 1 UML diagram, this readme, testcases pdf, usecases pdf, 2 Traceability Matrix pdfs.
auto_off_SequenceDiagram.pdf, batteryDrain_SequenceDiagram.pdf, lockSequence_SequenceDiagram.pdf, OverLoadShutoff_SequenceDiagram.pdf, record_therapy_SequenceDiagram.pdf, SelectFrequencySequenceDiagram.pdf, select_wavelength_SequenceDiagram.pdf, set_current_SequenceDiagram.pdf, StartSession_SequenceDiagram.pdf, TherapyTimer_SequenceDiagram.pdf, turn_Device_off_SequenceDiagram.pdf, turn_device_on_SequenceDiagram.pdf,
UML_CRA_F.pdf

This project was a joint collaboration, almost all the files were touched by everyone at one point in time as implementations were created, changed and refined. 
Specific assignments were chosen by members via website trello which is decently accurate:
https://trello.com/invite/b/85Esv1RZ/0635d05e16dac009ed82425acf6f98a7/comp-3004
You can check the github changelog for more info as well.

The files found in the main folder represents all of the Qt and c++ code. 
The Documentation Folder holds all documentation raws and the Folders with assets in the name hold all assets for the CRA-Device.
Documentation pdfs holds the pdf files of the required documentation.
Tested Scenarios:
See the included test cases file.

Notes: 
You will notice there are two power modes with a checkbox labeled "realistic power draw", this is
designed as to allow every therapy to be completed at least once without the device running out of power.
If you uncheck this box the device will not function as intended as the power draw will be unrealistically high.
This feature was included just for the demo so the TA could watch the power decrease faster.

You will also notice that our device drains power even when there is not a therapy active, this was a design decision to be more realistic. Undergoing a therapy will however increase the amount of power being drained at any given time as required.

We opted for the therapy history to store the last active current used in the therapy.

The autoshut off is set to 30 seconds instead of 30mins so as to not waste your time.

A power overload will put the device in an irrecoverable state and you will need to relaunch the program if 
you want to continue after an overload. This was intended as the device is being simulated to have shorted itself internally.

Therapies are recorded and saved only for each instance, if the program is closed they are not saved, nor are they shared if you launch multiple versions of the same program.




