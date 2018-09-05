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
* **Vivado 2018.2 Installation with Xilinx SDK**: To set up Vivado, see the [Installing Vivado and Digilent Board Files Tutorial](https://reference.digilentinc.com/vivado/installing-vivado/start).
* **Serial Terminal Emulator**: 
* **MicroUSB Cable**
* **Wires and a Circuit to Measure**

Demo Setup
----------

1. Download the most recent release ZIP archive ("Cmod-S7-25-XADC-2018.2-*.zip") from the repo's [releases page](https://github.com/Digilent/Cmod-S7-25-XADC/releases).
2. Extract the downloaded ZIP.
3. Open the XPR project file, found at \<archive extracted location\>/vivado_proj/Cmod-S7-25-XADC.xpr, included in the extracted release archive in Vivado 2018.2.
4. In the toolbar at the top of the Vivado window, select **File -> Export -> Export Hardware**. Select **\<Local to Project\>** as the Exported Location and make sure that the **Include bitstream** box is checked, then click **OK**.
5. In the toolbar at the top of the Vivado window, select **File -> Launch SDK**. Select **\<Local to Project\>** as both the workspace location and exported location, then click **OK**.
6. With Vivado SDK opened, wait for the hardware platform exported by Vivado to be imported.
7. In the toolbar at the top of the SDK window, select **File -> New -> Application Project**.
8. Fill out the fields in the first page of the New Application Project Wizard as in the table below. Most of the listed values will be the wizard's defaults, but are included in the table for completeness.

| Setting                                 | Value                             |
| --------------------------------------- | --------------------------------- |
| Project Name                            | Cmod S7-25-XADC                   |
| Use default location                    | Checked box                       |
| OS Platform                             | standalone                        |
| Target Hardware: Hardware Platform      | design_1_wrapper_hw_platform_0    |
| Target Hardware: Processor              | microblaze_0                      |
| Target Software: Language               | C                                 |
| Target Software: Board Support Package  | Create New (Cmod-S7-25-XADC_bsp)  |

9. Click **Next**.
10. From the list of template applications, select "Empty Application", then click **Finish**.
11. In the Project Explorer pane to the left of the SDK window, expand the new application project (named "Cmod-S7-25-XADC").
12. Right click on the "src" subdirectory of the application project and select **Import**.
13. In the "Select an import wizard" pane of the window that pops up, expand **General** and select **File System**. Then click **Next**.
14. Fill out the fields of the "File system" screen as in the table below. Most of the listed values will be the defaults, but are included in the table for completeness.

| Setting                                                | Value                                      |
| -                                                      | -                                          |
| From directory                                         | \<archive extracted location\>/sdk_appsrc  |
| Files to import pane: sdk_appsrc                       | Checked box                                |
| Into folder                                            | Cmod-S7-25-XADC/src                        |
| Options: Overwrite existing resources without warning  | Checked box                                |
| Options: Create top-level folder                       | Unchecked box                              |

15. Click **Finish**.

<Note for maintainers: This project does not require any additional configuration of application or bsp projects. Projects that require any of this configuration should have the steps required to do so described here.>

16. Plug in a test circuit to the Cmod S7-25's analog input pins.
17. Open a serial terminal application (such as TeraTerm FIXME LINK) and connect it to the Cmod S7's serial port, using a baud rate of 9600.
18. In the toolbar at the top of the SDK window, select **Xilinx -> Program FPGA**. Leave all fields as their defaults and click "Program".
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
