This project demonstrates a use of the Cmod S7-25's Spartan 7 FPGA's analog-to-digital core (referred to as the XADC). This is a Microblaze demo, and uses Xilinx SDK to program the bitstream onto the board and to build and deploy a C application. Ten times per second, the voltage on each of the Cmod S7-25's DIP header's analog inputs is read and printed to a connected serial terminal. The readings are accurate to two decimal places. Take care not to apply a voltage greater than 3.5 Volts to the analog pins. Any voltages less than 0 Volts or greater than 3.3 Volts are read as those instead.

To receive messages from the demo, the Cmod S7 must be connected to a host PC using a micro USB cable. A serial terminal application, such as [TeraTerm](https://ttssh2.osdn.jp/index.html.en), should be used to view these messages. The UART connection is configured as 9600 baud, 2 stop bits, no parity.

WARNING!!! This project is only supported in the 2017.4 version of Vivado.

In order to program the project onto an FPGA:

1. 	Download the most recent release ZIP archive (not the source ZIP) from the repo's [releases page](https://github.com/Digilent/Cmod-S7-25-XADC/releases).

2. 	Extract the downloaded ZIP. Find and double-click on the "Cmod-S7-25-XADC.xpr" file in the "vivado" subfolder of the extracted archive. This will launch an archived version of the project, in which a bitstream has already been generated.

3.  Select File -> Export -> Export Hardware from the bar at the top of the Vivado GUI. Select <Local to Project> as the location to export to and make sure that the Include bitstream box is checked, then click OK.

4.  Select File -> Launch SDK from the bar at the top of the Vivado GUI. Select <Local to Project> as the workspace location and exported location, then click OK.

5.  Vivado SDK will open and the hardware platform created by Vivado will be imported. Select File -> New -> Application Project from the bar at the top of the SDK GUI. Give the application project a name without spaces. Leave all other settings default, then click Next.

6.  From the list of template applications, select "Empty Application", then click Finish.

7.  Copy all of the files from the "sdk" subfolder of the extracted archive into the "src" subfolder of your new application project. If SDK does not automatically rebuild the project, select Project -> Build All from the bar at the top of the SDK GUI.

8. 	Select Xilinx -> Program FPGA from the menu at the top of the Xilinx SDK GUI. Click OK.

9.  Right click on the application project in the Project Explorer to the left, then select Run As -> Launch on Hardware (System Debugger).

10.  The application will now be running on your Cmod. It can be interacted with as described in the first paragraph of this README.

For more information on how this project is version controlled, see the [digilent-vivado-scripts repo](https://github.com/artvvb/digilent-vivado-scripts), which contains several Python and TCL scripts for maintaining a Vivado project on Github.
