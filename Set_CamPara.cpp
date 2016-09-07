#include "Set_CamPara.hpp"





void loadConfig_fl_1(string configName, float* shutterTime, 
	float* brightVal, float* gammaVal, float* gainVal, 
	unsigned int* sharpVal, unsigned int* redVal, unsigned int* blueVal, 
	float* satuVal )
{
	ifstream in;
	string str;

	in.open(configName);

	string kk;

	while (!in.eof())
	{
		while (getline(in,str))
		{
			string::size_type begin = str.find_first_not_of(" \f\t\v");
			//Skips black lines
			if( begin == string::npos)
				continue;
			string firstWord;
			try {
				firstWord = str.substr(0, str.find(" "));
			}
			catch (std::exception &e) {
				firstWord = str.erase(str.find_first_of(" "), str.find_first_not_of(" "));
			}
			transform(firstWord.begin(), firstWord.end(), firstWord.begin(), ::toupper);

			if (firstWord == "SHUTTER_SPEED")
				*shutterTime = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "BRIGHT_VALUE_F")
				*brightVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "GAMMA_VALUE_F")
				*gammaVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "GAIN_VALUE_F")
				*gainVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SHARP_VALUE_F")
				*sharpVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "RED_VALUE_F_1")
				*redVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "BLUE_VALUE_F_1")
				*blueVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SATU_VALUE_F")
				*satuVal = stof(str.substr(str.find(" ") + 1, str.length()));
		}
	}
}

void loadConfig_fl_2(string configName, float* shutterTime, 
	float* brightVal, float* gammaVal, float* gainVal, 
	unsigned int* sharpVal, unsigned int* redVal, unsigned int* blueVal, 
	float* satuVal )
{
	ifstream in;
	string str;

	in.open(configName);

	string kk;

	while (!in.eof())
	{
		while (getline(in,str))
		{
			string::size_type begin = str.find_first_not_of(" \f\t\v");
			//Skips black lines
			if( begin == string::npos)
				continue;
			string firstWord;
			try {
				firstWord = str.substr(0, str.find(" "));
			}
			catch (std::exception &e) {
				firstWord = str.erase(str.find_first_of(" "), str.find_first_not_of(" "));
			}
			transform(firstWord.begin(), firstWord.end(), firstWord.begin(), ::toupper);

			if (firstWord == "SHUTTER_SPEED")
				*shutterTime = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "BRIGHT_VALUE_F")
				*brightVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "GAMMA_VALUE_F")
				*gammaVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "GAIN_VALUE_F")
				*gainVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SHARP_VALUE_F")
				*sharpVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "RED_VALUE_F_2")
				*redVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "BLUE_VALUE_F_2")
				*blueVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SATU_VALUE_F")
				*satuVal = stof(str.substr(str.find(" ") + 1, str.length()));
		}
	}
}

void loadConfig_gh(string configName, float* shutterTime, 
	float* brightVal, float* gammaVal, float* gainVal, 
	unsigned int* sharpVal, unsigned int* redVal, unsigned int* blueVal, 
	float* satuVal )
{
	ifstream in;
	string str;

	in.open(configName);

	string kk;

	while (!in.eof())
	{
		while (getline(in,str))
		{
			string::size_type begin = str.find_first_not_of(" \f\t\v");
			//Skips black lines
			if( begin == string::npos)
				continue;
			string firstWord;
			try {
				firstWord = str.substr(0, str.find(" "));
			}
			catch (std::exception &e) {
				firstWord = str.erase(str.find_first_of(" "), str.find_first_not_of(" "));
			}
			transform(firstWord.begin(), firstWord.end(), firstWord.begin(), ::toupper);

			if (firstWord == "SHUTTER_SPEED")
				*shutterTime = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "BRIGHT_VALUE_G")
				*brightVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "GAMMA_VALUE_G")
				*gammaVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "GAIN_VALUE_G")
				*gainVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SHARP_VALUE_G")
				*sharpVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "RED_VALUE_G")
				*redVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "BLUE_VALUE_G")
				*blueVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SATU_VALUE_G")
				*satuVal = stof(str.substr(str.find(" ") + 1, str.length()));
		}
	}
}

void loadConfig_sn(string configName, unsigned int *seq_num, char* server_addr, char* folder_path)
{

	ifstream in;
	string str;

	in.open(configName);

	string kk;
	string server_tmp;
	string file_folder_tmp;

	

	while (!in.eof())
	{
		while (getline(in,str))
		{
			string::size_type begin = str.find_first_not_of(" \f\t\v");
			//Skips black lines
			if( begin == string::npos)
				continue;
			string firstWord;
			try {
				firstWord = str.substr(0, str.find(" "));
			}
			catch (std::exception &e) {
				firstWord = str.erase(str.find_first_of(" "), str.find_first_not_of(" "));
			}
			transform(firstWord.begin(), firstWord.end(), firstWord.begin(), ::toupper);

			if (firstWord == "SEQ_NUM")
				*seq_num = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SERVER_IP")
			{
				server_tmp = (str.substr(str.find(" ") + 1, str.length()));
				strcpy(server_addr, server_tmp.c_str());
			}
			if (firstWord == "FOLDER_PATH")
			{
				file_folder_tmp = (str.substr(str.find(" ") + 1, str.length()));
				strcpy(folder_path, file_folder_tmp.c_str());
			}

		}
	}
}


void PrintError_setPara( Error error )
{
	error.PrintErrorTrace();
}

int setCameraShutterSpd( Camera *ptCam, float shutter_time )
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property shutterSpd;
	//Define the property to adjust.
	shutterSpd.type = SHUTTER;
	//Ensure the property is on.
	shutterSpd.onOff = true;
	//Ensure auto-adjust mode is off.
	shutterSpd.autoManualMode = false;
	//Ensure the property is set up to use absolute value control.
	shutterSpd.absControl = true;
	//Set the absolute value of shutter to 20 ms.
	shutterSpd.absValue = shutter_time;
	//Set the property.
	error = ptCam->SetProperty( &shutterSpd );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}

int setCameraBrightness( Camera *ptCam, float brightVal)
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property brightness;
	//Define the property to adjust.
	brightness.type = BRIGHTNESS;
	//Ensure the property is set up to use absolute value control.
	brightness.absControl = true;
	//Set the absolute value of brightness to 0.5.
	brightness.absValue = brightVal;
	//Set the property.
	error = ptCam->SetProperty( &brightness );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;

}

int setCameraAutoExpo( Camera *ptCam)
{
	FlyCapture2::Error error;

	Property autoExpo;
	//Define the property to adjust.
	autoExpo.type = AUTO_EXPOSURE;
	//Ensure the property is on.
	autoExpo.onOff = false;
	//Ensure auto-adjust mode is off.
	autoExpo.autoManualMode = false;
	//Ensure the property is set up to use absolute value control.
	autoExpo.absControl = true;
	//Set the property.
	error = ptCam->SetProperty( &autoExpo );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}

int setCameraGamma(Camera *ptCam, float gammaVal)
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property gammaProp;
	//Define the property to adjust.
	gammaProp.type = GAMMA;
	//Ensure the property is on.
	gammaProp.onOff = true;
	//Ensure the property is set up to use absolute value control.
	gammaProp.absControl = true;
	//Set the absolute value of gain to 1 dB.
	gammaProp.absValue = gammaVal;
	//Set the property.	

	error = ptCam->SetProperty( &gammaProp );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}

int setCameraGain( Camera *ptCam, float gainVal)
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property gainProp;
	//Define the property to adjust.
	gainProp.type = GAIN;
	//Ensure auto-adjust mode is off.
	gainProp.autoManualMode = false;
	//Ensure the property is set up to use absolute value control.
	gainProp.absControl = true;
	//Set the absolute value of gain to 1 dB.
	gainProp.absValue = gainVal;
	//Set the property.	

	error = ptCam->SetProperty( &gainProp );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}

int setCameraSharpness( Camera *ptCam, unsigned int sharpVal)
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property sharp;
	//Define the property to adjust.
	sharp.type = SHARPNESS;
	//Ensure the property is on.
	sharp.onOff = true;
	//Ensure auto-adjust mode is off.
	sharp.autoManualMode = false;
	//Set the value of sharpness to 1500.
	sharp.valueA = sharpVal;
	//Set the property.
	error = ptCam->SetProperty( &sharp );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}


int setCameraWB( Camera *ptCam, unsigned int redVal, unsigned int blueVal)
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property WBprop;
	//Define the property to adjust.
	WBprop.type = WHITE_BALANCE;
	//Ensure the property is on.
	WBprop.onOff = true;
	//Ensure auto-adjust mode is off.
	WBprop.autoManualMode = false;
	//Set the white balance red channel to 500.
	WBprop.valueA = redVal;
	//Set the white balance blue channel to 750.
	WBprop.valueB = blueVal;
	//Set the property.
	error = ptCam->SetProperty( &WBprop );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}

int setCameraSaturation( Camera *ptCam, float satuVal)
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property saturation;
	//Define the property to adjust.
	saturation.type = SATURATION;
	//Ensure the property is on.
	saturation.onOff = true;
	//Ensure auto-adjust mode is off.
	saturation.autoManualMode = false;
	//Ensure the property is set up to use absolute value control.
	saturation.absControl = true;
	//Set the value of saturation to 75.0.
	saturation.absValue = satuVal;
	//Set the property.
	error = ptCam->SetProperty( &saturation );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}