//=============================================================================
// Copyright © 2008 Point Grey Research, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of Point
// Grey Research, Inc. ("Confidential Information").  You shall not
// disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with PGR.
//
// PGR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. PGR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
//=============================================================================
// $Id: AsyncTriggerEx.cpp,v 1.21 2010-07-22 22:51:51 soowei Exp $
//=============================================================================
#define WIN32_LEAN_AND_MEAN


#include "stdafx.h"

#include "FlyCapture2.h"
#include "Set_CamPara.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
//#include <Windows.h>
#include <direct.h>
#include <conio.h>
#include <ctime>

//server include file
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")



#define DEFAULT_BUFLEN 1
#define DEFAULT_PORT "27015"


using namespace FlyCapture2;
using namespace std;

void PrintBuildInfo()
{
	FC2Version fc2Version;
	Utilities::GetLibraryVersion( &fc2Version );

	ostringstream version;
	version << "FlyCapture2 library version: " << fc2Version.major << "." << fc2Version.minor << "." << fc2Version.type << "." << fc2Version.build;
	cout << version.str() <<endl;

	ostringstream timeStamp;
	timeStamp << "Application build date: " << __DATE__ << " " << __TIME__;
	cout << timeStamp.str() << endl << endl;
}

void PrintCameraInfo( CameraInfo* pCamInfo )
{
	cout << endl;
	cout << "*** CAMERA INFORMATION ***" << endl;
	cout << "Serial number -" << pCamInfo->serialNumber << endl;
	cout << "Camera model - " << pCamInfo->modelName << endl;
	cout << "Camera vendor - " << pCamInfo->vendorName << endl;
	cout << "Sensor - " << pCamInfo->sensorInfo << endl;
	cout << "Resolution - " << pCamInfo->sensorResolution << endl;
	cout << "Firmware version - " << pCamInfo->firmwareVersion << endl;
	cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl << endl;

}

void PrintFormat7Capabilities( Format7Info fmt7Info )
{
	cout << "Max image pixels: (" << fmt7Info.maxWidth << ", " << fmt7Info.maxHeight << ")" << endl;
	cout << "Image Unit size: (" << fmt7Info.imageHStepSize << ", " << fmt7Info.imageVStepSize << ")" << endl;
	cout << "Offset Unit size: (" << fmt7Info.offsetHStepSize << ", " << fmt7Info.offsetVStepSize << ")" << endl;
	cout << "Pixel format bitfield: 0x" << fmt7Info.pixelFormatBitField << endl;

}

void PrintError( Error error )
{
	error.PrintErrorTrace();
}



bool PollForTriggerReady( Camera* pCam )
{
	const unsigned int k_softwareTrigger = 0x62C;
	Error error;
	unsigned int regVal = 0;

	do
	{
		error = pCam->ReadRegister( k_softwareTrigger, &regVal );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return false;
		}

	} while ( (regVal >> 31) != 0 );

	return true;
}



void GrabImages( Camera *ptCam, Image* Image_seq)
{
	FlyCapture2::Error error;

	error = ptCam->RetrieveBuffer( Image_seq);	

	
}

void GrabImages_unused( Camera *ptCam)
{
	FlyCapture2::Error error;
	Image imageTemp;

	error = ptCam->RetrieveBuffer( &imageTemp);	
	if (error != PGRERROR_OK)
	{
		printf("capture error\n");
		return;
	}
}



void GrabImages_rest( Camera *ptCam)
{
	FlyCapture2::Error error;
	Image imageTemp;
	while(1)
	{
		error = ptCam->RetrieveBuffer( &imageTemp);	
		if (error != PGRERROR_OK)
		{
			break;
		}
		else
		{
			cout << "still have image in buffer" << endl;
		}
	}
}


string ZeroPadNumber(int num, int zero_num)
{
    std::ostringstream ss;
    ss << std::setw( zero_num ) << std::setfill( '0' ) << num;
    return ss.str();
}

void pad(char *s, int n, int c) 
{
    char *p = s + n - strlen(s);
    strcpy(p, s);
    p--;
    while (p >= s) 
	{ 
		p[0] = c; 
		p--; 
	}
}

void write_out_image(Camera *ptCam, Image Image_data, int cam_num, int seq_num, char* bayerType, char* sn_num, char * folder)
{
	FlyCapture2::Error error;

	//FlyCapture2::Image image_temp;
	//CameraInfo camInfo;
	//error = ptCam->GetCameraInfo( &camInfo );

	//Image_data.Convert(PIXEL_FORMAT_BGR, &image_temp);

		
	//unsigned int rowBytes = (double)image_temp.GetReceivedDataSize()/(double)image_temp.GetRows();       
	//cv::Mat disp_image = cv::Mat(image_temp.GetRows(), image_temp.GetCols(), CV_8UC3, image_temp.GetData(),rowBytes);

	char fn[30];
	strcpy(fn,folder);
	strcat(fn,"//");
	char preidx[10] = "img_";
	strcat(fn,preidx);
	char id_num[20];

	/*if (camInfo.bayerTileFormat == BGGR)
	{
		strcat(fn,"BGGR");
		strcat(fn,"_");
	}
	else if (camInfo.bayerTileFormat == GBRG)
	{
		strcat(fn,"GBRG");
		strcat(fn,"_");
	}
	else if (camInfo.bayerTileFormat == GRBG)
	{
		strcat(fn,"GRBG");
		strcat(fn,"_");
	}
	else if (camInfo.bayerTileFormat == RGGB)
	{
		strcat(fn,"RGGB");
		strcat(fn,"_");
	}*/

	strcat(fn,bayerType);
	strcat(fn,"_");
	//char cam_num[10];
	//_itoa(camInfo.serialNumber,id_num,10);

	strcat(fn,sn_num);
	strcat(fn,"_");

	//char img_num[20];
	string img_num = ZeroPadNumber(seq_num,4);
	//_itoa(seq_num,img_num,10);
	//pad(img_num, 4, '0');


	strcat(fn,img_num.c_str());
	strcat(fn,".bmp");


	error = Image_data.Save( fn );

	
}


int main(int /*argc*/, char** /*argv*/)
{
	//load config file
	unsigned int seq_num;
	float shutter_time;
	float brightVal_f, gammaVal_f, gainVal_f, satuVal_f;
	unsigned int sharpVal_f, redVal_f_1, blueVal_f_1, redVal_f_2, blueVal_f_2;
	string configFile = "config.ini";
	string configSeqNum = "seqnum.ini";
	char server_ip[60];
	char folder_path[60];


	loadConfig_sn(configSeqNum, &seq_num, server_ip,folder_path);
	char output_path[80];
	char output_fd[15]= "output_raw";
	strcpy(output_path,folder_path);
	strcat(output_path,output_fd);
	_mkdir(output_path);

	loadConfig_fl_1(configFile, &shutter_time, &brightVal_f, &gammaVal_f, &gainVal_f, &sharpVal_f, &redVal_f_1, &blueVal_f_1, &satuVal_f);
	cout << "flea3_lres_shutter_Speed is " << shutter_time << endl;
	cout << "flea3_lres_bright_Value is " << brightVal_f << endl;
	cout << "flea3_lres_gamma_Value is " << gammaVal_f << endl;
	cout << "flea3_lres_gain_Value is " << gainVal_f << endl;
	cout << "flea3_lres_sharp_Value is " << sharpVal_f << endl;
	cout << "flea3_lres_red_Value is " << redVal_f_1 << endl;
	cout << "flea3_lres_blue_Value is " << blueVal_f_1 << endl;
	cout << "flea3_lres_satu_Value is " << satuVal_f << endl;

	loadConfig_fl_2(configFile, &shutter_time, &brightVal_f, &gammaVal_f, &gainVal_f, &sharpVal_f, &redVal_f_2, &blueVal_f_2, &satuVal_f);
	cout << "flea3_rres_shutter_Speed is " << shutter_time << endl;
	cout << "flea3_rres_bright_Value is " << brightVal_f << endl;
	cout << "flea3_rres_gamma_Value is " << gammaVal_f << endl;
	cout << "flea3_rres_gain_Value is " << gainVal_f << endl;
	cout << "flea3_rres_sharp_Value is " << sharpVal_f << endl;
	cout << "flea3_rres_red_Value is " << redVal_f_2 << endl;
	cout << "flea3_rres_blue_Value is " << blueVal_f_2 << endl;
	cout << "flea3_rres_satu_Value is " << satuVal_f << endl;

	float brightVal_g, gammaVal_g, gainVal_g, satuVal_g;
	unsigned int sharpVal_g, redVal_g, blueVal_g;
	loadConfig_gh(configFile, &shutter_time, &brightVal_g, &gammaVal_g, &gainVal_g, &sharpVal_g, &redVal_g, &blueVal_g, &satuVal_g);
	cout << "gh3_shutter_Speed is " << shutter_time << endl;
	cout << "gh3_bright_Value is " << brightVal_g << endl;
	cout << "gh3_gamma_Value is " << gammaVal_g << endl;
	cout << "gh3_gain_Value is " << gainVal_g << endl;
	cout << "gh3_sharp_Value is " << sharpVal_g << endl;
	cout << "gh3_red_Value is " << redVal_g << endl;
	cout << "gh3_blue_Value is " << blueVal_g << endl;
	cout << "gh3_satu_Value is " << satuVal_g << endl;

	////////// *STEP 1* initialize Winsock
	WSADATA wsaData;

	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	////////// *STEP 2* creating a socket for the client
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port (using the 1st parameter from the Command Arguments)
	iResult = getaddrinfo(server_ip, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// create Socket object
	SOCKET ConnectSocket = INVALID_SOCKET;

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) 
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		////////// *STEP 3* Connect to server
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) 
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}






	/////////////////////////////////////////////
	PrintBuildInfo();

	const int pre_Image_cap = 6;

	Error error;

	BusManager busMgr;
	unsigned int numCameras;
	error = busMgr.GetNumOfCameras(&numCameras);
	if (error != PGRERROR_OK)
	{
		PrintError( error );
		return -1;
	}

	cout << "Number of cameras detected: " << numCameras <<endl;

	if ( numCameras < 1 )
	{
		cout << "Insufficient number of cameras... exiting" << endl;
		return -1;
	}

	// new space for image
	FlyCapture2::Image* Image_temp = new FlyCapture2::Image[numCameras];

	//FlyCapture2::Image** Image_Seq = new FlyCapture2::Image* [numCameras];
	/*for ( unsigned int i = 0; i < numCameras; i++)
	{
		Image_Seq[i] = new FlyCapture2::Image [seq_num];
	}*/




	//Camera cam;
	Camera** ppCameras = new Camera*[numCameras];
	char** bayerType = new char *[numCameras];
	char** sn_num = new char * [numCameras];

	for ( unsigned int i = 0; i < numCameras; i++)
	{
		ppCameras[i] = new Camera();
		PGRGuid guid;
		error = busMgr.GetCameraFromIndex(i, &guid);
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		// Connect to a camera
		error = ppCameras[i]->Connect( &guid );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		CameraInfo camInfo;
		error = ppCameras[i]->GetCameraInfo( &camInfo );
		bayerType[i] = new char [10];
		if (camInfo.bayerTileFormat == BGGR)
		{
			strcpy(bayerType[i],"BGGR");
			//strcat(bayerType[i],"_");
		}
		else if (camInfo.bayerTileFormat == GBRG)
		{
			strcpy(bayerType[i],"GBRG");
			//strcat(bayerType[i],"_");
		}
		else if (camInfo.bayerTileFormat == GRBG)
		{
			strcpy(bayerType[i],"GRBG");
			//strcat(bayerType[i],"_");
		}
		else if (camInfo.bayerTileFormat == RGGB)
		{
			strcpy(bayerType[i],"RGGB");
			//strcat(bayerType[i],"_");
		}
		sn_num[i] = new char[15];
		_itoa(camInfo.serialNumber,sn_num[i],10);

	}

	const unsigned int k_cameraMemory = 0x618;
	unsigned int regMemVal = 0xDEAFBEEF;
	for ( unsigned int i = 0; i < numCameras; i++)
	{
		error  = ppCameras[i]->WriteRegister( k_cameraMemory, regMemVal );
		printf("Restore to Factory setting!\n");
	}


	// Power on the camera
	const unsigned int k_cameraPower = 0x610;
	const unsigned int k_powerVal = 0x80000000;
	const unsigned int millisecondsToSleep = 100;
	unsigned int regVal = 0;
	unsigned int retries = 10;
	
	for ( unsigned int i = 0; i < numCameras; i++)
	{
		
		error  = ppCameras[i]->WriteRegister( k_cameraPower, k_powerVal );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		// Wait for camera to complete power-up
		do
		{

			Sleep(millisecondsToSleep);

			error = ppCameras[i]->ReadRegister(k_cameraPower, &regVal);
			if (error == PGRERROR_TIMEOUT)
			{
				// ignore timeout errors, camera may not be responding to
				// register reads during power-up
			}
			else if (error != PGRERROR_OK)
			{
				PrintError( error );
				return -1;
			}

			retries--;
		} while ((regVal & k_powerVal) == 0 && retries > 0);

		// Check for timeout errors after retrying
		if (error == PGRERROR_TIMEOUT)
		{
			PrintError( error );
			return -1;
		}
	}




	// Set the camera capture parameters
	for ( unsigned int i = 0; i < numCameras; i++)
	{
		// Get the camera information
		CameraInfo camInfo;
		error = ppCameras[i]->GetCameraInfo(&camInfo);
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		
		float brightVal, gammaVal, gainVal, satuVal;
		unsigned int sharpVal, redVal, blueVal;

		if (camInfo.modelName[0] == 'G')
		{
			brightVal = brightVal_g;
			gammaVal = gammaVal_g;
			gainVal = gainVal_g;
			satuVal = satuVal_g;
			sharpVal = sharpVal_g;
			redVal = redVal_g;
			blueVal = blueVal_g;
		}
		else if(camInfo.modelName[0] == 'F' && camInfo.modelName[13] == '2')
		{
			brightVal = brightVal_f;
			gammaVal = gammaVal_f;
			gainVal = gainVal_f;
			satuVal = satuVal_f;
			sharpVal = sharpVal_f;
			redVal = redVal_f_2;
			blueVal = blueVal_f_2;

		}
		else if(camInfo.modelName[0] == 'F' && camInfo.modelName[13] == '1')
		{
			brightVal = brightVal_f;
			gammaVal = gammaVal_f;
			gainVal = gainVal_f;
			satuVal = satuVal_f;
			sharpVal = sharpVal_f;
			redVal = redVal_f_1;
			blueVal = blueVal_f_1;

		}
		else
		{

			cout<< "some model is not assigned!!! Camera model is " << camInfo.modelName << endl;
		}

		PrintCameraInfo(&camInfo);

		int setError;
		setError = setCameraBrightness( ppCameras[i], brightVal);
		if (setError != 0)
		{
			return -1;
		}

		setError = setCameraSaturation( ppCameras[i], satuVal );
		if (setError != 0)
		{
			return -1;
		}

		setError = setCameraShutterSpd( ppCameras[i], shutter_time );
		if (setError != 0)
		{
			return -1;
		}

		setError = setCameraAutoExpo( ppCameras[i] );
		if (setError != 0)
		{
			return -1;
		}

		setError = setCameraGamma( ppCameras[i], gammaVal );
		if (setError != 0)
		{
			return -1;
		}

		setError = setCameraGain( ppCameras[i], gainVal );
		if (setError != 0)
		{
			return -1;
		}

		setError = setCameraWB( ppCameras[i], redVal, blueVal );
		if (setError != 0)
		{
			return -1;
		}

		setError = setCameraSharpness( ppCameras[i], sharpVal );
		if (setError != 0)
		{
			return -1;
		}
	}


	// custom image mode
	const Mode k_fmt7Mode = MODE_0;
	const PixelFormat k_fmt7PixFmt = PIXEL_FORMAT_RAW8;
	Format7Info fmt7Info;
	bool supported;
	fmt7Info.mode = k_fmt7Mode;
	for ( unsigned int i = 0; i < numCameras; i++)
	{
		error = ppCameras[i]->GetFormat7Info( &fmt7Info, &supported );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		PrintFormat7Capabilities( fmt7Info );

		if ( (k_fmt7PixFmt & fmt7Info.pixelFormatBitField) == 0 )
		{
			// Pixel format not supported!
			cout << "Pixel format is not supported" << endl;
			return -1;
		}
	}

	Format7ImageSettings fmt7ImageSettings;


	bool valid;
	Format7PacketInfo fmt7PacketInfo;
	for ( unsigned int i = 0; i < numCameras; i++)
	{

		error = ppCameras[i]->GetFormat7Info( &fmt7Info, &supported );
		fmt7ImageSettings.mode = k_fmt7Mode;
		fmt7ImageSettings.offsetX = 0;
		fmt7ImageSettings.offsetY = 0;
		fmt7ImageSettings.width = fmt7Info.maxWidth;
		fmt7ImageSettings.height = fmt7Info.maxHeight;
		fmt7ImageSettings.pixelFormat = k_fmt7PixFmt;

		// Validate the settings to make sure that they are valid
		error = ppCameras[i]->ValidateFormat7Settings(
				&fmt7ImageSettings,
				&valid,
				&fmt7PacketInfo );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		if ( !valid )
		{
			// Settings are not valid
			cout << "Format7 settings are not valid" << endl;
			return -1;
		}

		// Set the settings to the camera
		error = ppCameras[i]->SetFormat7Configuration(
				&fmt7ImageSettings,
				fmt7PacketInfo.recommendedBytesPerPacket );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}
	}


	// Set Buffer for image sequence
	// need to be modified for RAID 
	for ( unsigned int i = 0; i < numCameras; i++ )
	{
		FC2Config BufferFrame;
		error = ppCameras[i]->GetConfiguration( &BufferFrame );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		BufferFrame.numBuffers = 200;
		//BufferFrame.numBuffers = seq_num+1;
		BufferFrame.grabMode = BUFFER_FRAMES;
		BufferFrame.highPerformanceRetrieveBuffer = true;
		error = ppCameras[i]->SetConfiguration( &BufferFrame );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}
	}



	
	// Check for external trigger support
	// Trigger
	TriggerMode triggerMode;
	
	for ( unsigned int i = 0; i < numCameras; i++)
	{
		TriggerModeInfo triggerModeInfo;
		error = ppCameras[i]->GetTriggerModeInfo( &triggerModeInfo );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		if ( triggerModeInfo.present != true )
		{
			cout << "Camera does not support external trigger! Exiting..." << endl;
			return -1;
		}


		// Get current trigger settings
		
		error = ppCameras[i]->GetTriggerMode( &triggerMode );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		// Set camera to trigger mode 0
		triggerMode.onOff = true;
		triggerMode.mode = 0;
		triggerMode.parameter = 0;
		triggerMode.source = 2;

		error = ppCameras[i]->SetTriggerMode( &triggerMode );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		// Poll to ensure camera is ready
		bool retVal = PollForTriggerReady( ppCameras[i] );
		if( !retVal )
		{
			cout << endl;
			cout << "Error polling for trigger ready!" << endl;
			return -1;
		}
	

		// Get the camera configuration
		FC2Config config;
		error = ppCameras[i]->GetConfiguration( &config );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}



		// Set the grab timeout to 100 seconds
		config.grabTimeout = 100000;

		// Set the camera configuration
		error = ppCameras[i]->SetConfiguration( &config );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		cout << "Camera " << i << "External trigger is set! ..." << endl;
	}



	
	
	
	

	cout << "Trigger the camera by sending a trigger pulse to GPIO" << triggerMode.source << endl;
	
	


	////////// *STEP 4* Sending & Receiving Data on the Client
	int recvbuflen = DEFAULT_BUFLEN;

	char *sendbuf_p = "=";
	char *sendbuf_n = "s";
	char* recvbuf = new char[1];

	// send an initial buffer
	iResult = send(ConnectSocket, sendbuf_p, (int)strlen(sendbuf_p), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	printf("Bytes Sent: %ld\n", iResult);
	// Receive until the server closes the connection
	do {

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

		if (recvbuf[0] == 'p')
		{
			printf("receive p signal.\n");
			break;
		}

	} while (iResult > 0);



	for ( unsigned int i = 0; i < numCameras; i++ )
	{
		// Camera is ready, start capturing images
		error = ppCameras[i]->StartCapture();
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}
	}



	// Retrieve frame rate property
	for ( unsigned int i = 0; i < numCameras; i++ )
	{
		Property frmRate;
		frmRate.type = FRAME_RATE;
		error = ppCameras[i]->GetProperty( &frmRate );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		cout << "Camera " << i << "'s frame rate is " << frmRate.absValue << " fps" << endl;


		Property shutterSpeed;
		shutterSpeed.type = SHUTTER;
		error = ppCameras[i] ->GetProperty(&shutterSpeed);
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}

		cout << "Camera " << i << "'s shutter Speed is " << shutterSpeed.absValue << " ms" << endl;
	}

	// send an new buffer
	iResult = send(ConnectSocket, sendbuf_n, (int)strlen(sendbuf_n), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	printf("Bytes Sent: %ld\n", iResult);
	// shutdown the send half of the connection since no more data will be sent
	// the client can still use the ConnectSocket for receiving data
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}



	// idle capture unused
	std::clock_t seq_start;
	seq_start = std::clock();
	while(1)
	{
		for ( unsigned int i = 0; i < numCameras; i++ )
		{
			GrabImages_unused( ppCameras[i]);
		}
		
		std::clock_t seq_end;
		double duration;
		seq_end = std::clock();

		duration = ( seq_end - seq_start ) / (double) CLOCKS_PER_SEC;

		if(duration < 0.25)
		{
			printf("start sync cap\n");
			break;
		}

		seq_start = seq_end;
	}




	// start capture all the frames
	// need to be modified for RAID 
	std::clock_t start;
	double duration;

	start = std::clock();

	for( int imageCount=0; imageCount < seq_num; imageCount++)
	{
#pragma omp parallel for
		for (  int i = 0; i < numCameras; i++ )
		{

			GrabImages( ppCameras[i], &Image_temp[i]);
			write_out_image(ppCameras[i], Image_temp[i], i, imageCount, bayerType[i],sn_num[i], output_path);
		}
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC * 1000.0;
		
		cout << " ." << imageCount << ". frame rate is " << duration << "ms per frame! " << endl;
		start = std::clock();
	}



	cout << "Capture Finished!" << endl;
	cout << "write all the image to disk. " << endl;


	// write all the images to disk after finished capture
	// need to be modified for RAID 
	//for( int imageCount= seq_num-1; imageCount >= 0 ; imageCount--)
	//{

	//	for ( int cam_num = numCameras-1; cam_num >= 0 ; cam_num-- )
	//	{
	//		write_out_image(ppCameras[cam_num], Image_Seq[cam_num][imageCount], cam_num, imageCount, output_fd);
	//		
	//		//delete Image_Seq[cam_num][imageCount];
	//	}
	//	cout << imageCount << " for all image is saved" << endl;

	//	
	//}

	/*for ( int cam_num = numCameras-1; cam_num >= 0 ; cam_num-- )
	{
		delete [] Image_Seq[cam_num];
	}*/


	delete [] Image_temp;


	////////// *STEP 5* Disconnecting the Client
	closesocket(ConnectSocket);
	WSACleanup();




	// Turn trigger mode off.
	triggerMode.onOff = false;
	for ( unsigned int i = 0; i < numCameras; i++)
	{
	
		error = ppCameras[i]->SetTriggerMode( &triggerMode );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}
		cout << "Camera " << i << " trigger has been turn off" << endl;
	}

	
	for ( unsigned int i = 0; i < numCameras; i++)
	{
		error  = ppCameras[i]->WriteRegister( k_cameraMemory, regMemVal );
		printf("Restore to Factory setting!\n");
	}
	

	for ( int i = numCameras-1; i >= 0 ; i-- )
	{
		CameraInfo camInfo;
		error = ppCameras[i]->GetCameraInfo( &camInfo );

		cout << "set Camera " << camInfo.serialNumber << " to stop " << endl;

		//ppCameras[i]->StopCapture();
		//ppCameras[i]->Disconnect();
		delete ppCameras[i];

		cout << "Camera " << camInfo.serialNumber << " is stopped!" << endl;
	}

	delete [] ppCameras;

	cout << "Done! Press Enter to exit..." << endl;
	cin.ignore();

	return 0;
}
