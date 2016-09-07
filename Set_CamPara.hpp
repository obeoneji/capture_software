#include "FlyCapture2.h"
#include <fstream>
#include <algorithm>


#include "stdafx.h"

using namespace std;
using namespace FlyCapture2;

int setCameraShutterSpd( Camera *ptCam, float shutter_time );
int setCameraBrightness( Camera *ptCam, float brightVal);
int setCameraAutoExpo( Camera *ptCam);
int setCameraGamma(Camera *ptCam, float gammaVal);
int setCameraGain( Camera *ptCam, float gainVal);
int setCameraSharpness( Camera *ptCam, unsigned int sharpVal);
int setCameraWB( Camera *ptCam, unsigned int redVal, unsigned int blueVal);
int setCameraSaturation( Camera *ptCam, float satuVal);
void PrintError_setPara( Error error );
void loadConfig_fl_1(string configName, float* shutterTime, 
	float* brightVal, float* gammaVal, float* gainVal, 
	unsigned int* sharpVal, unsigned int* redVal, unsigned int* blueVal, 
	float* satuVal );
void loadConfig_fl_2(string configName, float* shutterTime, 
	float* brightVal, float* gammaVal, float* gainVal, 
	unsigned int* sharpVal, unsigned int* redVal, unsigned int* blueVal, 
	float* satuVal );
void loadConfig_gh(string configName, float* shutterTime, 
	float* brightVal, float* gammaVal, float* gainVal, 
	unsigned int* sharpVal, unsigned int* redVal, unsigned int* blueVal, 
	float* satuVal );
void loadConfig_sn(string configName, unsigned int *seq_num, char* server_addr, char* folder_path);

