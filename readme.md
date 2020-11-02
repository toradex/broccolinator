# Broccolinator

This is a demo used for two webinars in Set/Nov 2020.

In the first webinar we introduced the concept of containers and explained how a complex application could be splitted in multiple containers, using different tools, languages etc.  
In the second one we illustrated the code and showed how it could be built, deployed and debugged using the Torizon extension for Visual Studio Code.

## broccolinator-hw

C++ application used to access hardware (scale, LEDs and switches) using libgpiod

## broccolinator-ml-tflite

Python/Flask service exposing a webapi and using a TensorFlowLite model to recognize images. Code is taken from TFLite samples.

## broccolinator_bl_net

.NET application managing the businness logic with the whole recognition/weight process and storage of information in a database and information provided to the UI clients

## broccolinator-qt-clients

Qt5 application used as main UI for the system

# tflite-model

Python script and images used to generate the tflite model.
