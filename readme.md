# Broccolinator

This is a demo used for two webinars in Set/Nov 2020.

In the first webinar we introduced the concept of containers and explained how a complex application could be splitted in multiple containers, using different tools, languages etc.  
In the second one we illustrated the code and showed how it could be built, deployed and debugged using the Torizon extension for Visual Studio Code.

## broccolinator-hw

C++ application used to access hardware (scale, LEDs and switches) using libgpiod
When opening the folder for the first time don't open it inside container.
First:
- execute "Download/update base containers" and wait until the operation is completed
- execute "Torizon: Rebuild SDK and reload in container"
- if the project is not loaded inside a container, run "Remote-Containers: rebuild and reload in container"

## broccolinator-ml-tflite

Python/Flask service exposing a webapi and using a TensorFlowLite model to recognize images. Code is taken from TFLite samples.
You need to install the python extension for vscode.

## broccolinator_bl_net

.NET application managing the businness logic with the whole recognition/weight process and storage of information in a database and information provided to the UI clients
This requires the .NET SDK installed on your PC and the omnisharp extension for vs-code.

## broccolinator-qt-clients

Qt5 application used as main UI for the system.
When opening the folder for the first time don't open it inside container.
First:
- execute "Download/update base containers" and wait until the operation is completed
- execute "Torizon: Rebuild SDK and reload in container"
- if the project is not loaded inside a container, run "Remote-Containers: rebuild and reload in container"

## tflite-model

Python script and images used to generate the tflite model.
Requires python 3.8 and tensor flow installed on your development machine.

## zerotohero

Slides from the webinar about Visual Studio Code extension for Torizon

**Please notice that the application configuration folders contain RSA keys. Those are used during debugging and won't be included in release containers, we anyway suggest to create new projects if you plan to re-use some of the code of this demo, avoiding re-usage of those keys.**
