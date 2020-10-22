CrowBox Software (CrOS)
=======================

The programmable computer brain that controls the CrowBox is the Arduino UNO microcontroller board.

We'll go through the steps to download the source code for the CrOS software and get it uploaded to an Arduino UNO board, which can then be used to control your CrowBox.

The CrOS software is fully open-source and we encourage you to make changes and improvements to the code and the machine's training protocol.

The Arduino is an extremely popular platform for makers and experimental electronics worldwide. This means that there are a great deal of resources available to help you learn more about the Arduino hardware, the Arduino IDE software, and how to program and modify programs for these great little boards.

If you run into trouble following the instructions on this page, feel free to open an issue, or check out one of these resources for more information:

- [Getting Started with Arduino](https://www.arduino.cc/en/Guide)
- [Arduino UNO Guide](https://www.arduino.cc/en/Guide/ArduinoUno)
- [CrowBox Google Group](http://groups.google.com/group/CrowBoxKit)

### Table of contents

- [Step 1: Download and Install the Arduino IDE Software](#step-1-download-and-install-the-arduino-ide-software)
- [Step 2: Download and Extract the CrOS Software](#step-2-download-and-extract-the-cros-software)
- [Step 3: Load CrOS Software into the Arduino IDE](#step-3-load-cros-software-into-the-arduino-ide)
- [Step 4: Connect the Arduino UNO Board](#step-4-connect-the-arduino-uno-board)
- [Step 5: Upload the CrOS Software to the Arduino UNO Board](#step-5-upload-cros-software-to-arduino-uno-board)


## Step 1: Download and Install the Arduino IDE Software

To install the CrOS Software onto your Arduino UNO microcontroller board, you'll need a computer, a USB (A to B) cable, and the Arduino IDE software, which is available for free download. IDE stands for Integrated Development Environment, but that's not an important detail right now.

Let's get started! First, follow the official instructions at the Arduino website to download and install the version of the Arduino IDE software that matches your computer's operating system:

- [Windows](https://www.arduino.cc/en/Guide/Windows)
- [Mac OSX](https://www.arduino.cc/en/Guide/MacOSX)
- [Linux](https://www.arduino.cc/en/Guide/Linux)


## Step 2: Download and Extract the CrOS Software

In order to get your CrowBox functional, you'll need to download our CrOS software and install it on your Arduino UNO board.

Download the [latest version of the CrOS software].

After you've downloaded this file you should extract the archive, which you can do by double-click the .zip file you've downloaded.

The archive should create a folder named cros which contains the CrOS source code files, which have extensions like .h, .cpp, and a file named cros.ino.


## Step 3: Load CrOS Software into the Arduino IDE

Launch the Arduino IDE software that you downloaded and installed in the previous steps.

From the Arduino menu, select FILE → OPEN. In the file dialog window that appears, navigate to the 'cros_source' folder from step three and select the file named cros.ino then click Open.

The CrOS project files will be loaded and you will see some tabs containing filenames that begin with 'cros'. You can click through these tabs to view the various source code files, or just ignore them if you're not interested.

It's possible that at some point a window will appear near the bottom of the Arduino IDE which says "Updates are available for some of your boards and libraries". It's a good idea to accept these updates, but you may also click the `X` to dismiss this message and ignore the updates.


## Step 4: Connect the Arduino UNO Board

Plug the 'B' end (The big square end) of your USB A to B cable into the square USB socket on your Arduino UNO board. Plug the other end of the USB cable into a free USB port on your computer.

Allow a moment for your operating system to detect the new device. On Windows operating systems, drivers may begin to install. If so, allow this process to finish before proceeding.

In the Arduino IDE menu, select TOOLS → BOARD → ARDUINO/GENUINO UNO.

The details of the next step depend on your operating system:

### Windows

In the Arduino IDE menu, select TOOLS → PORT → and then look for a COM port numbered 3 or higher which is also labeled (Arduino/Genuino Uno) and select it.

Examples: COM6 (Arduino/Genuino Uno) or COM3 (Arduino/Genuino Uno)

### Mac OSX

In the Arduino IDE menu, select TOOLS → PORT → and then select the port named starting with /dev/tty.usbmodem or /dev/tty.usbserial. The port name will probably end with an unusual alphanumeric string.

### Linux

We have no instructions for this step at present! If you are familiar with the Arduino IDE on Linux, please contribute to this section.


## Step 5: Upload CrOS Software to Arduino UNO Board

At the top left of the Arduino IDE window you'll see two round buttons. Locate the round button with an arrow facing to the right. This is the Upload button.

Click the Upload button.

The CrOS software will compile on your computer and then be uploaded to the Arduino UNO board which you've connected to your computer with the USB cable. If you receive an error message, the best place to turn for help is the issues, or the [CrowBox Google Group](http://groups.google.com/group/CrowBoxKit)

Once the upload is complete, leave the Arduino UNO board connected to your computer for 30 seconds before disconnecting the USB cable.

Your CrowBox software should now be ready to operate!