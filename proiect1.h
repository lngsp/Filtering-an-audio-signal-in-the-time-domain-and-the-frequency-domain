/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  FREQ_PANEL                       1
#define  FREQ_PANEL_IDC_SWITCH_PANEL      2       /* control type: binary, callback function: OnSwitchPanelCB */
#define  FREQ_PANEL_GRAPH_FREQ_FILTRED    3       /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_GRAPH_FREQ            4       /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_COMMANDBUTTON_NEXT_2  5       /* control type: command, callback function: OnSwitchButtonFreq */
#define  FREQ_PANEL_COMMANDBUTTON_PREV_2  6       /* control type: command, callback function: OnSwitchButtonFreq */
#define  FREQ_PANEL_COMMANDBUTTON_FILT    7       /* control type: command, callback function: OnAplicareFiltre */
#define  FREQ_PANEL_COMMANDBUTTON_SPC     8       /* control type: command, callback function: OnSpectru */
#define  FREQ_PANEL_COMMANDBUTTON_IMG_SPC 9       /* control type: command, callback function: OnSpectruImagine */
#define  FREQ_PANEL_NUMERIC_STOP_2        10      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_NUMERIC_START_2       11      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_NUMERIC_POWER_PEAK    12      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_NUMERIC_FREQ_PEAK     13      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_NUMERIC_NPOINTS       14      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_RING_FILTRU_TIP_FER   15      /* control type: ring, callback function: (none) */
#define  FREQ_PANEL_RING_FILTRU_FREQ      16      /* control type: ring, callback function: (none) */
#define  FREQ_PANEL_COMMANDBUTTON_EXIT    17      /* control type: command, callback function: OnExit */
#define  FREQ_PANEL_COMMANDBUTTON_IMG     18      /* control type: command, callback function: OnGenerateImg */
#define  FREQ_PANEL_DECORATION            19      /* control type: deco, callback function: (none) */
#define  FREQ_PANEL_DECORATION_2          20      /* control type: deco, callback function: (none) */
#define  FREQ_PANEL_DECORATION_3          21      /* control type: deco, callback function: (none) */
#define  FREQ_PANEL_DECORATION_4          22      /* control type: deco, callback function: (none) */
#define  FREQ_PANEL_DECORATION_5          23      /* control type: deco, callback function: (none) */

#define  MAIN_PANEL                       2       /* callback function: OnMainPanel */
#define  MAIN_PANEL_GRAPH_FILTRED_DATA    2       /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_GRAPH_RAW_DATA        3       /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_COMMANDBUTTON_APLICA  4       /* control type: command, callback function: OnButtonAplica */
#define  MAIN_PANEL_COMMANDBUTTON_NEXT    5       /* control type: command, callback function: OnSwitchButton */
#define  MAIN_PANEL_COMMANDBUTTON_PREV    6       /* control type: command, callback function: OnSwitchButton */
#define  MAIN_PANEL_NUMERIC_STOP          7       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_START         8       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_RING_FILTRU           9       /* control type: ring, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_MINIM_INDEX   10      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_MAXIM_INDEX   11      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_MEAN_INDEX    12      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_MINIM         13      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_DISPERSIA     14      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_ZERO          15      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_SAMPLERATE    16      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_NPOINTS       17      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_MEDIANA       18      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_MAXIM         19      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_MEAN          20      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_COMMANDBUTTON_LOAD    21      /* control type: command, callback function: OnButtonLoad */
#define  MAIN_PANEL_GRAPH_HIST_2          22      /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_GRAPH_HIST            23      /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_ALFA          24      /* control type: numeric, callback function: OnAlfa */
#define  MAIN_PANEL_NUMERIC_LEFT_RANK     25      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_DECORATION_2          26      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION            27      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_COMMANDBUTTON_EXIT    28      /* control type: command, callback function: OnExit */
#define  MAIN_PANEL_COMMANDBUTTON_ANVELOP 29      /* control type: command, callback function: OnAnvelopa */
#define  MAIN_PANEL_TEXTMSG               30      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_IDC_SWITCH_PANEL      31      /* control type: binary, callback function: OnSwitchPanelCB */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnAlfa(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnAnvelopa(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnAplicareFiltre(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnButtonAplica(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnButtonLoad(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnExit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnGenerateImg(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnMainPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnSpectru(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnSpectruImagine(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnSwitchButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnSwitchButtonFreq(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnSwitchPanelCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
