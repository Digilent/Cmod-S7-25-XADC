/*
 * This is the demo main file for the Cmod S7-25 XADC demo.
 *
 * Changelog:
 * 06/07/2018 (ArtVVB): Created
 *
 * */

#include "xparameters.h"
#include "xsysmon.h"
#include "xil_printf.h"
#include "xil_cache.h"
#include "sleep.h"

#define XADC_DEVICE_ID (XPAR_XADC_WIZ_0_DEVICE_ID)

// TODO: create an "xadc/" subdirectory of project src. make as portable to other boards/xadc configs as possible
typedef struct XadcInfo {
	int NumChannels;
	int Channels[2];
	int ChannelIsDiff[2];
	char *ChannelNames[2];
} XadcInfo;

typedef struct Xadc_ChannelInfo {
	int SequencerIndex;
	int IsDiff;
	char *Name;
} Xadc_ChannelInfo;


void Xadc_Init(XSysMon *InstancePtr, const Xadc_ChannelInfo DeviceInfo[], const int NumChannels, const u32 DeviceId);
void Xadc_ReadData(XSysMon *InstancePtr, const Xadc_ChannelInfo DeviceInfo[], const int NumChannels, u16 RawData[]);
void EnableCaches();
void DisableCaches();

// Initialize the XADC Wizard IP
void Xadc_Init(XSysMon *InstancePtr, const Xadc_ChannelInfo DeviceInfo[], const int NumChannels, const u32 DeviceId) {
	u32 ChannelsMask;
	u32 InputModeMask;
	int i;
	XSysMon_Config *xadc_cfg_ptr;
	xadc_cfg_ptr = XSysMon_LookupConfig(DeviceId);
	XSysMon_CfgInitialize(InstancePtr, xadc_cfg_ptr, xadc_cfg_ptr->BaseAddress);

	ChannelsMask = 0;
	InputModeMask = 0;
	for (i = 0; i < NumChannels; i++) {
		ChannelsMask |= 1 << DeviceInfo[i].SequencerIndex;
		if (DeviceInfo[i].IsDiff)
			InputModeMask |= 1 << DeviceInfo[i].SequencerIndex;
	}
	// Disable the Channel Sequencer before configuring the Sequence registers.
	XSysMon_SetSequencerMode(InstancePtr, XSM_SEQ_MODE_SAFE);

	// Leave alarm enables default
	// Leave channel averaging default

	// Set single-ended input mode for all channels
	XSysMon_SetSeqInputMode(InstancePtr, InputModeMask);

	// Leave acquisition time default
	XSysMon_SetSeqAcqTime(InstancePtr, ChannelsMask);
	// Enable all channels
	XSysMon_SetSeqChEnables(InstancePtr, ChannelsMask);

	// Leave the ADCCLK frequency default
	// Leave calibration default

	// Enable the Channel Sequencer in continuous sequencer cycling mode
	XSysMon_SetSequencerMode(InstancePtr, XSM_SEQ_MODE_CONTINPASS);
}

// Captures Data from each XADC Channel
void Xadc_ReadData(XSysMon *InstancePtr, const Xadc_ChannelInfo DeviceInfo[], const int NumChannels, u16 RawData[]) {
	//TODO: implement timeout on status check
	int i;

	// Clear the Status
	XSysMon_GetStatus(InstancePtr);

	// Wait until the End of Sequence occurs
	while ((XSysMon_GetStatus(InstancePtr) & XSM_SR_EOS_MASK) != XSM_SR_EOS_MASK);

	//Capture data from each channel, return via RawData
	for (i = 0; i < NumChannels; i++) {
		RawData[i] = XSysMon_GetAdcData(InstancePtr, DeviceInfo[i].SequencerIndex);
	}

	return;
}

int main() {
	const int NumChannels = 2;
	const Xadc_ChannelInfo CmodS7_XadcInfo[2] = {
		{21, 0, "AIN_32"}, // VAUX_5
		{28, 0, "AIN_33"}  // VAUX_12
	};
	const int Xadc_VoltageScaler_SingleEnded = (0xFFFF) / (100 * 3.3);

	XSysMon Xadc_Ctrl;
	u16 Xadc_RawData[2];
	int Xadc_Voltage; // x100 from actual value. Two decimal point precision.
	int Xadc_VoltageRemainder;
	int i;

	EnableCaches();
	xil_printf("Initializing Cmod S7-25 XADC Demo...\n\r");
	Xadc_Init(&Xadc_Ctrl, CmodS7_XadcInfo, NumChannels, XADC_DEVICE_ID);
	xil_printf("Demo Initialized\n\r");

	while (1) {
		Xadc_ReadData(&Xadc_Ctrl, CmodS7_XadcInfo, NumChannels, Xadc_RawData);
		for (i = 0; i < NumChannels; i++) {
			// Convert raw data in this channel to an int in the range 0 to 330, representing
			// the voltage on that input channel multiplied by 100
			Xadc_Voltage = ((int)Xadc_RawData[i] / Xadc_VoltageScaler_SingleEnded);
			Xadc_VoltageRemainder = Xadc_Voltage % 100;
			Xadc_Voltage = (Xadc_Voltage/100) % 10;

			// Print the name of the channel, followed by the voltage
			xil_printf("%s: %01d.%02dV    ",
					CmodS7_XadcInfo[i].Name,
					Xadc_Voltage,
					Xadc_VoltageRemainder
			);
		}
		xil_printf("\n\r");
		usleep(100000); // wait 100ms
	}
	DisableCaches();

	return 0;
}

void EnableCaches() {
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_DCACHE
   Xil_DCacheEnable();
#endif
#ifdef XPAR_MICROBLAZE_USE_ICACHE
   Xil_ICacheEnable();
#endif
#endif
}

void DisableCaches() {
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_DCACHE
   Xil_DCacheDisable();
#endif
#ifdef XPAR_MICROBLAZE_USE_ICACHE
   Xil_ICacheDisable();
#endif
#endif
}

