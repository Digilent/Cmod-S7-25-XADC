Cmod S7-25 XADC Demo
====================

Description
-----------

This project demonstrates how to use the Cmod S7-25's Spartan 7 FPGA's analog-to-digital core (referred to as the XADC) with a Microblaze processor. Vivado is used to build the demo's hardware platform, and Xilinx SDK is used to program the bitstream onto the board and to build and deploy a C application.

To use this demo, the Cmod S7 must be connected to a computer over MicroUSB, which must be running a serial terminal. For more information on how to set up and use a serial terminal, such as Tera Term or PuTTY, refer to [this tutorial](https://reference.digilentinc.com/vivado/installing-vivado/start).

As long as the demo is running, ten times per second, the voltages on each of the Cmod S7-25's DIP header's analog input pins (AIN32 and AIN33) are read and printed to a connected serial terminal. The readings are accurate to two decimal places. Take care not to apply a voltage greater than 3.5 Volts to the analog pins. Any voltages less than 0 Volts or greater than 3.3 Volts are read as those instead.

Requirements
------------
* **Cmod S7-25**: To purchase a Cmod S7, see the [Digilent Store](https://store.digilentinc.com/cmod-s7-breadboardable-spartan-7-fpga-module/).
* **Vivado 2020.1 Installation with Xilinx SDK**: To set up Vivado, see the [Installing Vivado and Digilent Board Files Tutorial](https://reference.digilentinc.com/vivado/installing-vivado/start).
* **Serial Terminal Emulator**: 
* **MicroUSB Cable**
* **Wires and a Circuit to Measure**

Demo Setup
----------

**Note:** *Other releases may require other steps be taken to use them. Make sure to check the version of this README found in the commit associated with that release's tag for instructions.*

1. Download the most recent release ZIP archive ("Cmod-S7-25-XADC-2020.1-*.zip") from the repo's [releases page](https://github.com/Digilent/Cmod-S7-25-XADC/releases).
2. Open Vivado 2020.1.
3. Open the XPR project file, found at \<archive extracted location\>/vivado-proj/hw.xpr, included in the extracted hardware release in Vivado 2020.1.
4. No additional steps are required within Vivado. The project can be viewed, modified, and rebuilt, and a new platform can be exported, as desired.
5. Open Vitis 2020.1. Choose an empty folder as the *Workspace* to launch into.
6. With Vitis opened, click the **Import Project** button, under **PROJECT** in the welcome screen.
7. Choose *Vitis project exported zip file* as the Import type, then click **Next**.
8. **Browse** -sdk_appsrc- folder (found in the downloaded archive) **Open** it.
9. Make sure that all boxes are checked in order to import each of the projects present in the archive will be imported, then click **Finish**.
10. Connect the CMOD A7 to your computer via the MicroUSB programming cable, make sure the power source select jumper is set to USB or WALL (depending on whether you are using an external supply), then power on the board by flipping the power switch to the ON position.
11. Open a serial terminal application (such as TeraTerm or PuTTY) and connect it to the CMOD-S7-25's serial port, using a baud rate of 9600.
12. In the *Assistant* pane at the bottom left of the Vitis window, right click on the project marked `[System]`, and select **Run** -> **Launch Hardware**. When the demo is finished launching, messages will be able to be seen through the serial terminal, and the buttons can be used as described in this document's *Description* section, above.

<Note for maintainers: This project does not require any additional configuration of application or bsp projects. Projects that require any of this configuration should have the steps required to do so described here.>

16. Plug in a test circuit to the Cmod S7-25's analog input pins.
17. Open a serial terminal application (such as TeraTerm FIXME LINK) and connect it to the Cmod S7's serial port, using a baud rate of 9600.
18. In the toolbar at the top of the Vitis window, select **Xilinx -> Program FPGA**. Leave all fields as their defaults and click "Program".
19. In the Project Explorer pane, right click on the "Cmod-S7-25-XADC" application project and select "Run As -> Launch on Hardware (System Debugger)".
20. The application will now be running on the Cmod S7. It can be interacted with as described in the first section of this README.

Next Steps
----------
This demo can be used as a basis for other projects by modifying the hardware platform in the Vivado project's block design or by modifying the SDK application project.

Check out the Cmod S7's [Resource Center](https://reference.digilentinc.com/reference/programmable-logic/cmod-s7/start) to find more documentation, demos, and tutorials.

For technical support or questions, please post on the [Digilent Forum](forum.digilentinc.com).

Additional Notes
----------------
For more information on how this project is version controlled, refer to the [digilent-vivado-scripts repo](https://github.com/digilent/digilent-vivado-scripts).
