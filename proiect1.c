#include <analysis.h>
#include <utility.h>
#include <formatio.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "proiect1.h"

static int panelHandle;
static int acqPanel;
static int imgPanel;

//==============================================================================
// Constants
#define SAMPLE_RATE		0
#define NPOINTS			1


//==============================================================================
// Global variables		

int waveInfo[2]; //waveInfo[0] = sampleRate
				 //waveInfo[1] = number of elements
double sampleRate = 0.0;
int npoints = 0;
int nrpoints = 0;
double *waveData = 0;
double *filtredData = 0;
double *filtredData2 = 0;

double axis[10000];
ssize_t hist[10000];


double axis2[10000];
ssize_t hist2[10000];

int buton = 0;
int buton_freq = 0;
int stopVal = 0;
int startVal = 0;
int stopVal_freq = 0;
int startVal_freq = 0;

double alfa;

double *envelope = 0;

int tipFereastra = 0;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "proiect1.uir",MAIN_PANEL)) < 0)
		return -1;
	if ((acqPanel = LoadPanel (0, "proiect1.uir",FREQ_PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}



int CVICALLBACK OnButtonLoad (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	
	double maxVal = 0.0;
	double minVal = 0.0;
	int maxIndex = 0;
	int minIndex = 0;
	double mean = 0.0; 
	double mediana = 0.0;
	double dispersia = 0.0;
 	double zerouri = 0.0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			//executa script python pentru conversia unui fisierului .wav in .txt
			LaunchExecutable("python main.py");
			
			//astept sa fie generate cele doua fisiere (modificati timpul daca este necesar
			Delay(2);
			
			//incarc informatiile privind rata de esantionare si numarul de valori
			FileToArray("wafeInfo.txt", waveInfo, VAL_INTEGER, 2, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			sampleRate = waveInfo[SAMPLE_RATE];
			npoints = waveInfo[NPOINTS];  
			
			//alocare memorie pentru numarul de puncte
			waveData = (double *) calloc(npoints, sizeof(double));
			
			//incarcare din fisierul .txt in memorie (vector)
			FileToArray("waveData.txt", waveData, VAL_DOUBLE, npoints, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			
			//afisare pe grapf
			PlotY(panel,MAIN_PANEL_GRAPH_RAW_DATA, waveData, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_DK_MAGENTA);
			
			
		
			MaxMin1D(waveData, npoints, &maxVal, &maxIndex, &minVal, &minIndex);	//min si max
			Mean(waveData, npoints, &mean);			 //medie
			Median(waveData, npoints, &mediana);	//mediana
			StdDev(waveData, npoints, &mean, &dispersia);
			
			
			SetCtrlVal(panel, MAIN_PANEL_NUMERIC_MINIM, minVal);
			SetCtrlVal(panel, MAIN_PANEL_NUMERIC_MAXIM, maxVal); 
			SetCtrlVal(panel, MAIN_PANEL_NUMERIC_MEAN, mean);  
			
			
			SetCtrlVal(panel, MAIN_PANEL_NUMERIC_MINIM_INDEX, (double)minIndex);
			SetCtrlVal(panel, MAIN_PANEL_NUMERIC_MAXIM_INDEX, (double)maxIndex); 
			
			
			SetCtrlVal(panel, MAIN_PANEL_NUMERIC_MEDIANA, mediana);
			SetCtrlVal(panel, MAIN_PANEL_NUMERIC_DISPERSIA, dispersia);
			
			SetCtrlVal(panel, MAIN_PANEL_NUMERIC_NPOINTS, (double)npoints);
			SetCtrlVal(panel,MAIN_PANEL_NUMERIC_SAMPLERATE, sampleRate);
			
			
			// HIstograma raw data
			
			Histogram(waveData,npoints, minVal, maxVal, hist, axis , 20);  
			PlotXY (panel, MAIN_PANEL_GRAPH_HIST, axis, hist, 10000, VAL_DOUBLE, VAL_SSIZE_T, VAL_VERTICAL_BAR, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_DK_MAGENTA);
			
			
			for(int j = 0; j< npoints - 1; j++)
			{
				if(waveData[j]*waveData[j+1]<0)
				{
					
					 zerouri++;
				}
			}
	
			SetCtrlVal(panel, MAIN_PANEL_NUMERIC_ZERO, zerouri);
			
			break;
	}
	return 0;
}


int CVICALLBACK OnAlfa (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				 GetCtrlVal(panel, MAIN_PANEL_NUMERIC_ALFA, &alfa);
				
			break;
	}
	return 0;
}



int CVICALLBACK OnButtonAplica (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{  
	double maxVal = 0.0;
	double minVal = 0.0;
	int maxIndex = 0;
	int minIndex = 0;
	ssize_t leftRank  = 0;
	int filtru = 0;
	
	
	filtredData = (double *) calloc(npoints, sizeof(double));

	
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal(panel, MAIN_PANEL_RING_FILTRU, &filtru);
			
			if(filtru == 1)  //Mediere
			{
				DeleteGraphPlot(panel, MAIN_PANEL_GRAPH_FILTRED_DATA, -1,VAL_DELAYED_DRAW);
				
					GetCtrlVal(panel, MAIN_PANEL_NUMERIC_LEFT_RANK, &leftRank);
					
					MedianFilter(waveData, npoints, leftRank, 0, filtredData);
					
					PlotY(panel,MAIN_PANEL_GRAPH_FILTRED_DATA, filtredData, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_DK_GREEN);
				
			}
			if(filtru == 2)  //Ordin 1
			{
				DeleteGraphPlot(panel, MAIN_PANEL_GRAPH_FILTRED_DATA, -1,VAL_DELAYED_DRAW); 
				filtredData[0] = 0;
				for(int i = 1; i<npoints; i++)
				{
					filtredData[i] = (1-alfa)*filtredData[i-1] + alfa*waveData[i];
				}
				PlotY(panel,MAIN_PANEL_GRAPH_FILTRED_DATA, filtredData, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_DK_GREEN);
			}
			
			//Histograma filtred data
			DeleteGraphPlot(panel, MAIN_PANEL_GRAPH_HIST_2, -1, VAL_DELAYED_DRAW); 
			MaxMin1D(filtredData, npoints, &maxVal, &maxIndex, &minVal, &minIndex);  	
			Histogram(filtredData,npoints, minVal, maxVal, hist2, axis2 , 20);
			PlotXY (panel, MAIN_PANEL_GRAPH_HIST_2, axis2, hist2, 10000, VAL_DOUBLE, VAL_SSIZE_T, VAL_VERTICAL_BAR, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_DK_GREEN);
			
			
		
			if(buton == 1) {
			GetCtrlVal(panel, MAIN_PANEL_NUMERIC_START, &startVal);
			GetCtrlVal(panel, MAIN_PANEL_NUMERIC_STOP, &stopVal); 
					
			double *vect = filtredData + (int)(startVal * sampleRate);
				
			DeleteGraphPlot(panel, MAIN_PANEL_GRAPH_FILTRED_DATA, -1, VAL_DELAYED_DRAW);
			PlotY(panel, MAIN_PANEL_GRAPH_FILTRED_DATA, vect,(stopVal - startVal)*sampleRate, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_DK_GREEN);
			buton =0;
			}
			
			
			break;
	}
	return 0;
}




int CVICALLBACK OnMainPanel (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
				 QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK OnSwitchButton (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	int valoare =(int) npoints/sampleRate;
	
	int valStart = 0;
	int valStop =0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			switch (control)
			{
				case MAIN_PANEL_COMMANDBUTTON_PREV:
					switch (event)
					{
						case EVENT_COMMIT:
							buton = 1; 
							GetCtrlVal(panel, MAIN_PANEL_NUMERIC_START, &valStart);
							GetCtrlVal(panel, MAIN_PANEL_NUMERIC_STOP, &valStop);
							if(valStart > 0 && valStop <= valoare)
							{
								SetCtrlVal(panel, MAIN_PANEL_NUMERIC_START, valStart -1);
								SetCtrlVal(panel, MAIN_PANEL_NUMERIC_STOP, valStop - 1); 
								OnButtonAplica(panel, MAIN_PANEL_COMMANDBUTTON_PREV, EVENT_COMMIT, 0, 0, 0);
							}
							 
							break;	
					}
					break;
				
				case MAIN_PANEL_COMMANDBUTTON_NEXT:
					 switch (event)
					{
						case EVENT_COMMIT:
							buton = 1; 
							GetCtrlVal(panel, MAIN_PANEL_NUMERIC_START, &valStart);
							GetCtrlVal(panel, MAIN_PANEL_NUMERIC_STOP, &valStop);  
							if(valStart >= 0 && valStop < valoare)
							{
								SetCtrlVal(panel, MAIN_PANEL_NUMERIC_START, valStart +1);
								SetCtrlVal(panel, MAIN_PANEL_NUMERIC_STOP, valStop +1); 
								OnButtonAplica(panel, MAIN_PANEL_COMMANDBUTTON_NEXT, EVENT_COMMIT, 0, 0, 0);         
							}
	
							break;	
					}
					break;
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnExit (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(ConfirmPopup ("Quit", "Do you Really want to quit ?"))
			{
				QuitUserInterface (0);
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnAnvelopa (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			LaunchExecutable("python anvelopa.py");
			
			//astept sa fie generate cele doua fisiere (modificati timpul daca este necesar
			Delay(2);
			
			envelope = (double *) calloc(npoints, sizeof(double));   
			
			
			FileToArray("anvelope.txt", envelope, VAL_DOUBLE, npoints, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			
		
			PlotY(panel, MAIN_PANEL_GRAPH_RAW_DATA, envelope, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_BLACK); 
		
			break;
	}
	return 0;
}



int CVICALLBACK OnSwitchPanelCB (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			if(panel == panelHandle)
			{
				SetCtrlVal(acqPanel, FREQ_PANEL_IDC_SWITCH_PANEL, 1);
				DisplayPanel(acqPanel);
				HidePanel(panel);
			}
			else
			{
				SetCtrlVal(panelHandle, MAIN_PANEL_IDC_SWITCH_PANEL, 0);
				DisplayPanel(panelHandle);
				HidePanel(panel);
			}
			break;
	}
	return 0;
}
	 

int CVICALLBACK OnSpectru (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	GetCtrlVal(acqPanel, FREQ_PANEL_NUMERIC_NPOINTS, &nrpoints); 
	double temp[nrpoints];
	double autoSpectrum[nrpoints/2];
	double dt = 1.0/sampleRate;
	double convertedSpectrum[nrpoints/2]; 
	double powerPeak = 0.0;
	double freqPeak = 0.0;  
	double df = 0.0;
	int i;
	char unit[32] = "V";
	
													 
	
	switch (event)
	{
		case EVENT_COMMIT:

			GetCtrlVal(acqPanel, FREQ_PANEL_RING_FILTRU_TIP_FER, &tipFereastra);
			
			for(i=0; i<nrpoints;i++)
			{
				temp[i] = waveData[i];
			}
			
			WindowConst winConst;
			
			if(tipFereastra == 1) //Hanning
			{
				ScaledWindowEx(temp, nrpoints, HANNING, 0, &winConst); 
			}
			if(tipFereastra == 2) //Blackman
			{
				ScaledWindowEx(temp, nrpoints, BLKMAN, 0, &winConst); 
			}

			AutoPowerSpectrum(temp, nrpoints, dt, autoSpectrum, &df);
			
			PowerFrequencyEstimate(autoSpectrum, nrpoints/2, -1, winConst, df, 7, &freqPeak, &powerPeak);
	
			//afisez pe interfata valorile determinate
			SetCtrlVal( acqPanel, FREQ_PANEL_NUMERIC_FREQ_PEAK, freqPeak);
			SetCtrlVal( acqPanel, FREQ_PANEL_NUMERIC_POWER_PEAK, powerPeak);
			//Functia converteste spectrul de intrare (care este puterea, amplitudinea sau amplificarea) 
			//în formate alternative (linear, logarithmic, dB) ce permit o reprezentare grafica mai convenabila.

			
			SpectrumUnitConversion(autoSpectrum, nrpoints/2, SPECTRUM_POWER, SCALING_MODE_LINEAR, DISPLAY_UNIT_VRMS, df, winConst, convertedSpectrum, unit);

			//sterg graph-ul unde urmeaza sa plotez spectrul semnalului
			DeleteGraphPlot (acqPanel, FREQ_PANEL_GRAPH_FREQ, -1, VAL_IMMEDIATE_DRAW);	
			//plotez spectrul semnalului
			PlotWaveform( acqPanel, FREQ_PANEL_GRAPH_FREQ, convertedSpectrum, nrpoints/2 ,VAL_DOUBLE, 1.0, 0.0, 0.0, df,
                                VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID,  VAL_CONNECTED_POINTS, VAL_DK_CYAN);
			
			break;
	}
	return 0;
}

   

	
int CVICALLBACK OnAplicareFiltre (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	//aplicam filtru pe semnalul in domeniul timp si apoi ii facem spectrul
	GetCtrlVal(acqPanel, FREQ_PANEL_NUMERIC_NPOINTS, &nrpoints); 
	double temp[nrpoints];
	double autoSpectrum[nrpoints/2];
	double dt = 1.0/sampleRate;
	double convertedSpectrum[nrpoints/2]; 
	double powerPeak = 0.0;
	double freqPeak = 0.0;  
	double df = 0.0;
	
	int i;
	char unit[32] = "V";
    int filtru = 0;
	
	double coef[55];
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			filtredData2 = (double *) calloc(npoints, sizeof(double));
	
			 GetCtrlVal(acqPanel, FREQ_PANEL_RING_FILTRU_FREQ, &filtru);
			 
			 if(filtru == 1) //Kaiser	- Hanning
			{
				Ksr_LPF(sampleRate, 1000, 55, coef, 3.86); //beta = 3.86 -> Hanning
				Convolve(waveData, nrpoints,coef, 55, filtredData2);
				PlotY(acqPanel,FREQ_PANEL_GRAPH_FREQ_FILTRED, filtredData2, nrpoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_DK_GREEN); 
			}
			if(filtru == 2) //Kaiser	- Blackman
			{
				Ksr_LPF(sampleRate, 1000, 55, coef, 7.04); //beta = 7.04 -> Blackman
				Convolve(waveData, nrpoints,coef, 55, filtredData2);
				PlotY(acqPanel,FREQ_PANEL_GRAPH_FREQ_FILTRED, filtredData2, nrpoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_DK_GREEN); 
			}
			if(filtru == 3) //Butterworth 
			{
				Bw_LPF(waveData, nrpoints, sampleRate, 1000, 6,  filtredData2);
				PlotY(acqPanel,FREQ_PANEL_GRAPH_FREQ_FILTRED, filtredData2, nrpoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_DK_GREEN);	
			}
			
			for(i=0; i<nrpoints;i++)
			{
				temp[i] = filtredData2[i];
			}
			
			WindowConst winConst;
			
			
			GetCtrlVal(acqPanel, FREQ_PANEL_RING_FILTRU_TIP_FER, &tipFereastra);
			
	
			if(tipFereastra == 1) //Hanning
			{
				ScaledWindowEx(temp, nrpoints, HANNING, 0, &winConst); 
			}
			if(tipFereastra == 2) //Blackman
			{
				ScaledWindowEx(temp, nrpoints, BLKMAN, 0, &winConst);
			}

			AutoPowerSpectrum(temp, nrpoints, dt, autoSpectrum, &df);
			
			PowerFrequencyEstimate(autoSpectrum, nrpoints/2, -1, winConst, df, 7, &freqPeak, &powerPeak);
	
			//afisez pe interfata valorile determinate
			SetCtrlVal( acqPanel, FREQ_PANEL_NUMERIC_FREQ_PEAK, freqPeak);
			SetCtrlVal( acqPanel, FREQ_PANEL_NUMERIC_POWER_PEAK, powerPeak);
			//Functia converteste spectrul de intrare (care este puterea, amplitudinea sau amplificarea) 
			//în formate alternative (linear, logarithmic, dB) ce permit o reprezentare grafica mai convenabila.

			
			SpectrumUnitConversion(autoSpectrum, nrpoints/2, SPECTRUM_POWER, SCALING_MODE_LINEAR, DISPLAY_UNIT_VRMS, df, winConst, convertedSpectrum, unit);

			//sterg graph-ul unde urmeaza sa plotez spectrul semnalului
			DeleteGraphPlot (acqPanel, FREQ_PANEL_GRAPH_FREQ_FILTRED, -1, VAL_IMMEDIATE_DRAW);	
			//plotez spectrul semnalului
			PlotWaveform( acqPanel, FREQ_PANEL_GRAPH_FREQ_FILTRED, convertedSpectrum, nrpoints/2 ,VAL_DOUBLE, 1.0, 0.0, 0.0, df,
                                VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID,  VAL_CONNECTED_POINTS, VAL_DK_YELLOW);
			
			
			if(buton_freq == 1) 
			{
				GetCtrlVal(acqPanel, FREQ_PANEL_NUMERIC_START_2, &startVal_freq);
				GetCtrlVal(acqPanel, FREQ_PANEL_NUMERIC_STOP_2, &stopVal_freq); 
					
				double *vect2 = convertedSpectrum + (int)(startVal_freq * df);
				
				DeleteGraphPlot(acqPanel, FREQ_PANEL_GRAPH_FREQ_FILTRED, -1, VAL_DELAYED_DRAW);
				PlotY(acqPanel, FREQ_PANEL_GRAPH_FREQ_FILTRED, vect2,(stopVal_freq - startVal_freq)*df, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_DK_YELLOW);
				buton_freq =0;
			}	  
			
			
			break;
	}
	return 0;
}

int CVICALLBACK OnSwitchButtonFreq (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	GetCtrlVal(panel, FREQ_PANEL_NUMERIC_NPOINTS, &nrpoints);
	int valoare =(int) nrpoints/4;
	
	int valStart = 0;
	int valStop =0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			switch (control)
			{
				case FREQ_PANEL_COMMANDBUTTON_PREV_2:
					switch (event)
					{
						case EVENT_COMMIT:
							buton_freq = 1; 
							GetCtrlVal(acqPanel, FREQ_PANEL_NUMERIC_START_2, &valStart);
							GetCtrlVal(acqPanel, FREQ_PANEL_NUMERIC_STOP_2, &valStop);
							if(valStart > 0 && valStop <= valoare)
							{
								SetCtrlVal(acqPanel, FREQ_PANEL_NUMERIC_START_2, valStart -1);
								SetCtrlVal(acqPanel, FREQ_PANEL_NUMERIC_STOP_2, valStop - 1); 
								OnAplicareFiltre(acqPanel, FREQ_PANEL_COMMANDBUTTON_PREV_2, EVENT_COMMIT, 0, 0, 0);
							}
							 
							break;	
					}
					break;
				
				case FREQ_PANEL_COMMANDBUTTON_NEXT_2:
					 switch (event)
					{
						case EVENT_COMMIT:
							buton_freq = 1; 
							GetCtrlVal(acqPanel, FREQ_PANEL_NUMERIC_START_2, &valStart);
							GetCtrlVal(acqPanel, FREQ_PANEL_NUMERIC_STOP_2, &valStop);  
							if(valStart >= 0 && valStop < valoare)
							{
								SetCtrlVal(acqPanel, FREQ_PANEL_NUMERIC_START_2, valStart +1);
								SetCtrlVal(acqPanel, FREQ_PANEL_NUMERIC_STOP_2, valStop +1); 
								OnAplicareFiltre(acqPanel, FREQ_PANEL_COMMANDBUTTON_NEXT_2, EVENT_COMMIT, 0, 0, 0);         
							}
	
							break;	
					}
					break;
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnGenerateImg (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	int filtru = 0;
	int tipFereastra = 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal(acqPanel, FREQ_PANEL_RING_FILTRU_FREQ, &filtru); 
			GetCtrlVal(acqPanel, FREQ_PANEL_RING_FILTRU_TIP_FER, &tipFereastra);
			
			
			if(tipFereastra == 1 && filtru == 1) //Fereastra Hanning  & Filtru Kaiser	- Hanning
			{
				GetCtrlDisplayBitmap(acqPanel, FREQ_PANEL_GRAPH_FREQ_FILTRED,1,&imgPanel);
				SaveBitmapToJPEGFile(imgPanel, "Hanning_KaiserHanning.jpeg", JPEG_INTERLACE, 100);
				DiscardBitmap(imgPanel); 
			}
			if(tipFereastra == 1 && filtru == 2) //Fereastra Hanning  & Filtru Kaiser	- Blackman      
			{
				GetCtrlDisplayBitmap(acqPanel, FREQ_PANEL_GRAPH_FREQ_FILTRED,1,&imgPanel);
				SaveBitmapToJPEGFile(imgPanel, "Hanning_KaiserBlackman.jpeg", JPEG_INTERLACE, 100);
				DiscardBitmap(imgPanel);  
			}
			if(tipFereastra == 1 && filtru == 3) //Fereastra Hanning & Filtru Butterworth 
			{
				GetCtrlDisplayBitmap(acqPanel, FREQ_PANEL_GRAPH_FREQ_FILTRED,1,&imgPanel);
				SaveBitmapToJPEGFile(imgPanel, "Hanning_Butterworth.jpeg", JPEG_INTERLACE, 100);
				DiscardBitmap(imgPanel); 
			}
			if(tipFereastra == 2 && filtru == 1) //Fereastra Blackman  & Filtru Kaiser	- Hanning
			{
				GetCtrlDisplayBitmap(acqPanel, FREQ_PANEL_GRAPH_FREQ_FILTRED,1,&imgPanel);
				SaveBitmapToJPEGFile(imgPanel, "Blackman_KaiserHanning.jpeg", JPEG_INTERLACE, 100);
				DiscardBitmap(imgPanel); 
			}
			if(tipFereastra == 2 && filtru == 2) //Fereastra Blackman  & Filtru Kaiser	- Blackman      
			{
				GetCtrlDisplayBitmap(acqPanel, FREQ_PANEL_GRAPH_FREQ_FILTRED,1,&imgPanel);
				SaveBitmapToJPEGFile(imgPanel, "Blackman_KaiserBlackman.jpeg", JPEG_INTERLACE, 100);
				DiscardBitmap(imgPanel);  
			}
			if(tipFereastra == 2 && filtru == 3) //Fereastra Blackman & Filtru Butterworth 
			{
				GetCtrlDisplayBitmap(acqPanel, FREQ_PANEL_GRAPH_FREQ_FILTRED,1,&imgPanel);
				SaveBitmapToJPEGFile(imgPanel, "Blackman_Butterworth.jpeg", JPEG_INTERLACE, 100);
				DiscardBitmap(imgPanel); 
			}
			
			
			break;
	}
	return 0;
}

int CVICALLBACK OnSpectruImagine (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlDisplayBitmap(acqPanel, FREQ_PANEL_GRAPH_FREQ,1,&imgPanel);
				SaveBitmapToJPEGFile(imgPanel, "36WAV_Spectru.jpeg", JPEG_INTERLACE, 100);
				DiscardBitmap(imgPanel);
			break;
	}
	return 0;
}
