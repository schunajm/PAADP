/*#####################################################################
#
#     Physical Activity Accelerometer Data Processor (PAADP)
#
#     Copyright (C) 2023 by John M. Schuna Jr.
#
#     John M. Schuna Jr.
#     johnschuna@yahoo.com
#
#####################################################################*/

///////////////////////////////////////////////////////////////////////
// Library headers - all not necessary - full set prototyping 
///////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <direct.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Builder
///////////////////////////////////////////////////////////////////////

GtkBuilder *builder;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Main Window
///////////////////////////////////////////////////////////////////////

GtkWidget *window;
GtkWidget *quit1;
GtkWidget *about1;
GtkWidget *timestamp1;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Main Window: Notebook - Resample Raw Data
///////////////////////////////////////////////////////////////////////

GtkWidget *rsbutton1;
GtkWidget *rsbutton2;
GtkWidget *rsbutton3;
GtkWidget *rsentry1;
GtkWidget *rsentry2;
GtkWidget *rsentry3;
GtkWidget *rsspin1;
GtkWidget *rsspin2;
GtkWidget *rsspin3;
GtkWidget *rsspin4;
GtkWidget *rsspin5;
GtkWidget *rsspin6;
GtkWidget *rsspin7;
GtkWidget *rsspin8;
GtkWidget *rsspin9;
GtkWidget *rsspin10;
GtkWidget *rscheck1;
GtkWidget *rscheck2;
GtkWidget *rscheck3;
GtkWidget *rscheck4;
GtkWidget *rscheck5;
GtkWidget *rsradio1;
GtkWidget *rsradio2;
GtkWidget *rsradio3;
GtkWidget *rsradio4;
GtkWidget *rsradio5;
GtkWidget *rsradio6;
GtkWidget *rsradio7;
GtkWidget *rsradio8;
GtkWidget *rsradio9;
GtkWidget *rsradio10;
GtkWidget *rscombo1;
GtkWidget *rscombo2;
GtkWidget *rscombo3;
GtkWidget *rscombo4;
GtkWidget *rscombo5;
GtkWidget *rsfilechooserbutton;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Main Window: Notebook - Raw Data
///////////////////////////////////////////////////////////////////////

GtkWidget *rdbutton1;
GtkWidget *rdbutton2;
GtkWidget *rdbutton3;
GtkWidget *rdentry1;
GtkWidget *rdentry2;
GtkWidget *rdentry3;
GtkWidget *rdspin1;
GtkWidget *rdspin2;
GtkWidget *rdspin3;
GtkWidget *rdspin4;
GtkWidget *rdspin5;
GtkWidget *rdspin6;
GtkWidget *rdspin7;
GtkWidget *rdspin8;
GtkWidget *rdspin9;
GtkWidget *rdspin10;
GtkWidget *rdcheck1;
GtkWidget *rdcheck2;
GtkWidget *rdcheck3;
GtkWidget *rdcheck4;
GtkWidget *rdcheck5;
GtkWidget *rdcheck6;
GtkWidget *rdcheck7;
GtkWidget *rdcheck8;
GtkWidget *rdcheck9;
GtkWidget *rdcheck10;
GtkWidget *rdcheck11;
GtkWidget *rdcheck12;
GtkWidget *rdcheck13;
GtkWidget *rdcheck14;
GtkWidget *rdcheck15;
GtkWidget *rdcheck16;
GtkWidget *rdcheck17;
GtkWidget *rdcheck18;
GtkWidget *rdcheck19;
GtkWidget *rdcheck20;
GtkWidget *rdcheck21;
GtkWidget *rdcheck22;
GtkWidget *rdradio1;
GtkWidget *rdradio2;
GtkWidget *rdradio3;
GtkWidget *rdradio4;
GtkWidget *rdradio5;
GtkWidget *rdradio6;
GtkWidget *rdradio7;
GtkWidget *rdradio8;
GtkWidget *rdcombo1;
GtkWidget *rdcombo2;
GtkWidget *rdcombo3;
GtkWidget *rdcombo4;
GtkWidget *rdcombo5;
GtkWidget *rdcombo6;
GtkWidget *rdfilechooserbutton;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Main Window: Notebook - Epoch Data
///////////////////////////////////////////////////////////////////////

GtkWidget *edbutton1;
GtkWidget *edbutton2;
GtkWidget *edbutton3;
GtkWidget *edentry1;
GtkWidget *edentry2;
GtkWidget *edentry3;
GtkWidget *edentry4;
GtkWidget *edentry5;
GtkWidget *edentry6;
GtkWidget *edentry7;
GtkWidget *edspin1;
GtkWidget *edspin2;
GtkWidget *edspin3;
GtkWidget *edspin4;
GtkWidget *edspin5;
GtkWidget *edspin6;
GtkWidget *edspin7;
GtkWidget *edspin8;
GtkWidget *edspin9;
GtkWidget *edcheck1;
GtkWidget *edcheck2;
GtkWidget *edcheck3;
GtkWidget *edcheck4;
GtkWidget *edcheck5;
GtkWidget *edcheck6;
GtkWidget *edcheck7;
GtkWidget *edcheck8;
GtkWidget *edradio1;
GtkWidget *edradio2;
GtkWidget *edradio3;
GtkWidget *edradio4;
GtkWidget *edradio5;
GtkWidget *edradio6;
GtkWidget *edcombo1;
GtkWidget *edcombo2;
GtkWidget *edcombo3;
GtkWidget *edcombo4;
GtkWidget *edcombo5;
GtkWidget *edcombo6;
GtkWidget *edcombo7;
GtkWidget *edcombo8;
GtkWidget *edcombo9;
GtkWidget *edcombo10;
GtkWidget *edcombo11;
GtkWidget *edfilechooserbutton;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Main Window: Notebook - File Viewer
///////////////////////////////////////////////////////////////////////

GtkWidget *fvbutton1;
GtkWidget *fventry1;
GtkWidget *fvcombo1;
GtkWidget *fvcombo2;
GtkWidget *fvfilechooserbutton;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Main Window: Notebook - Variable Defs
///////////////////////////////////////////////////////////////////////

GtkWidget *vdcombo1;
GtkWidget *vdentry1;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the File Chooser 1
///////////////////////////////////////////////////////////////////////

GtkWidget *filechooser1;
GtkWidget *fc1button1;
GtkWidget *fc1button2;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the File Chooser 2
///////////////////////////////////////////////////////////////////////

GtkWidget *filechooser2;
GtkWidget *fc2button1;
GtkWidget *fc2button2;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the File Chooser 3
///////////////////////////////////////////////////////////////////////

GtkWidget *filechooser3;
GtkWidget *fc3button1;
GtkWidget *fc3button2;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Calendar 1
///////////////////////////////////////////////////////////////////////

GtkWidget *calwindow1;
GtkCalendar *calendar1;
GtkCalendar *calendar1button1;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Calendar 2
///////////////////////////////////////////////////////////////////////

GtkWidget *calwindow2;
GtkCalendar *calendar2;
GtkCalendar *calendar2button1;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Calendar 3
///////////////////////////////////////////////////////////////////////

GtkWidget *calwindow3;
GtkCalendar *calendar3;
GtkCalendar *calendar3button1;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the About Dialog
///////////////////////////////////////////////////////////////////////

GtkWidget *aboutwindow1;
GtkWidget *buttonbox1;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Timestmap Dialog
///////////////////////////////////////////////////////////////////////

GtkWidget *timestampdialog1;
GtkWidget *timestampbutton1;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Resample Process Dialogs
///////////////////////////////////////////////////////////////////////

GtkWidget *resampledialog1;
GtkWidget *resampledialog2;
GtkWidget *resampledialogbutton1;
GtkWidget *resampledialogbutton2;
GtkWidget *rsdentry1;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Raw Data Processing Dialogs
///////////////////////////////////////////////////////////////////////

GtkWidget* rawdialog1;
GtkWidget* rawdialog2;
GtkWidget* rawdialogbutton1;
GtkWidget* rawdialogbutton2;
GtkWidget* rddentry1;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the Epoch Data Processing Dialogs
///////////////////////////////////////////////////////////////////////

GtkWidget* epochdialog1;
GtkWidget* epochdialog2;
GtkWidget* epochdialogbutton1;
GtkWidget* epochdialogbutton2;
GtkWidget* eddentry1;

///////////////////////////////////////////////////////////////////////
// Make the widgets global for the File Viewer Dialog
///////////////////////////////////////////////////////////////////////

GtkWidget* fvdialog1;
GtkWidget* fvdialogbutton1;
GtkWidget* fvdentry1;

///////////////////////////////////////////////////////////////////////
// Export Signals Main Window & MenuBar Signals
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void	on_quit1_activate(GtkMenuItem *b);
G_MODULE_EXPORT void	on_about1_activate(GtkMenuItem *b);
G_MODULE_EXPORT void	on_buttonbox1_button_release_event(GtkButtonBox *b);
G_MODULE_EXPORT void	on_timestamp1_activate(GtkMenuItem *b);
G_MODULE_EXPORT void	on_timestampbutton1_clicked(GtkButton *b);

///////////////////////////////////////////////////////////////////////
// Export Signals Main Window - Resample
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void    on_rsbutton1_clicked(GtkButton *b);
G_MODULE_EXPORT void	on_rsbutton2_clicked(GtkButton *b);
G_MODULE_EXPORT void	on_rsbutton3_clicked(GtkButton *b);
G_MODULE_EXPORT void	on_rscheck1_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rscheck2_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rscheck3_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rscheck4_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rscheck5_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rsradio1_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rsradio2_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rsradio3_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rsradio4_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rsradio5_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rsradio6_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rsradio7_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rsradio8_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rsradio9_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rsradio10_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rsfilechooserbutton_file_set(GtkFileChooserButton *b);

///////////////////////////////////////////////////////////////////////
// Export Signals Main Window - Raw Data
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void	on_rdbutton1_clicked(GtkButton *b);
G_MODULE_EXPORT void	on_rdbutton2_clicked(GtkButton *b);
G_MODULE_EXPORT void	on_rdbutton3_clicked(GtkButton *b);
G_MODULE_EXPORT void	on_rdcheck1_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck1_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck2_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck3_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck4_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck5_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck6_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck7_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck8_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck9_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck10_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck11_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck12_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck13_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck14_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck15_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck16_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck17_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck18_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck19_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck20_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck21_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdcheck22_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_rdradio1_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rdradio2_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rdradio3_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rdradio4_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rdradio5_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rdradio6_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rdradio7_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rdradio8_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_rdfilechooserbutton_file_set(GtkFileChooserButton *b);

///////////////////////////////////////////////////////////////////////
// Export Signals Main Window - Epoch Data
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void	on_edbutton1_clicked(GtkButton *b);
G_MODULE_EXPORT void	on_edbutton2_clicked(GtkButton *b);
G_MODULE_EXPORT void	on_edbutton3_clicked(GtkButton *b);
G_MODULE_EXPORT void	on_edcheck1_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_edcheck1_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_edcheck2_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_edcheck3_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_edcheck4_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_edcheck5_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_edcheck6_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_edcheck7_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_edcheck8_toggled(GtkCheckButton *b);
G_MODULE_EXPORT void	on_edradio1_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_edradio2_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_edradio3_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_edradio4_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_edradio5_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_edradio6_toggled(GtkRadioButton *b);
G_MODULE_EXPORT void	on_edcombo5_changed(GtkComboBoxText *b);
G_MODULE_EXPORT void	on_edcombo6_changed(GtkComboBoxText *b);
G_MODULE_EXPORT void	on_edcombo10_changed(GtkComboBoxText* b);
G_MODULE_EXPORT void	on_edcombo11_changed(GtkComboBoxText* b);
G_MODULE_EXPORT void	on_edfilechooserbutton_file_set(GtkFileChooserButton *b);

///////////////////////////////////////////////////////////////////////
// Export Signals Main Window - File Viewer
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void	on_fvbutton1_clicked(GtkButton *b);
G_MODULE_EXPORT void	on_fvfilechooserbutton_file_set(GtkFileChooserButton *b);

///////////////////////////////////////////////////////////////////////
// Export Signals Main Window - Variable Definitions
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void	on_vdcombo1_changed(GtkComboBoxText *b);

///////////////////////////////////////////////////////////////////////
// Export Signals File Chooser 1
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void    on_fc1button1_clicked(GtkButton *b);
G_MODULE_EXPORT void	on_fc1button2_clicked(GtkButton *b);

///////////////////////////////////////////////////////////////////////
// Export Signals File Chooser 2
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void    on_fc2button1_clicked(GtkButton *b);
G_MODULE_EXPORT void	on_fc2button2_clicked(GtkButton *b);

///////////////////////////////////////////////////////////////////////
// Export Signals File Chooser 3
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void    on_fc3button1_clicked(GtkButton* b);
G_MODULE_EXPORT void	on_fc3button2_clicked(GtkButton* b);

///////////////////////////////////////////////////////////////////////
// Export Signals Calednar 1
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void    on_calendar1_day_selected_double_click(GtkCalendar *b);
G_MODULE_EXPORT void	on_calendar1button1_clicked(GtkButton *b);

///////////////////////////////////////////////////////////////////////
// Export Signals Calednar 2
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void    on_calendar2_day_selected_double_click(GtkCalendar *b);
G_MODULE_EXPORT void	on_calendar2button1_clicked(GtkButton *b);

///////////////////////////////////////////////////////////////////////
// Export Signals Calednar 3
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void    on_calendar3_day_selected_double_click(GtkCalendar* b);
G_MODULE_EXPORT void	on_calendar3button1_clicked(GtkButton* b);

///////////////////////////////////////////////////////////////////////
// Export Signals Resample Process Dialogs
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void	on_resampledialogbutton1_clicked(GtkButton* b);
G_MODULE_EXPORT void	on_resampledialogbutton2_clicked(GtkButton* b);

///////////////////////////////////////////////////////////////////////
// Export Signals Raw Data Processing Dialogs
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void	on_rawdialogbutton1_clicked(GtkButton* b);
G_MODULE_EXPORT void	on_rawdialogbutton2_clicked(GtkButton* b);

///////////////////////////////////////////////////////////////////////
// Export Signals Epoch Data Processing Dialogs
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void	on_epochdialogbutton1_clicked(GtkButton* b);
G_MODULE_EXPORT void	on_epochdialogbutton2_clicked(GtkButton* b);

///////////////////////////////////////////////////////////////////////
// Export Signals File Viewer Dialog
///////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void	on_fvdialogbutton1_clicked(GtkButton* b);

///////////////////////////////////////////////////////////////////////
// Int Main Instance
///////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {

	gtk_init(&argc, &argv); // init Gtk

	///////////////////////////////////////////////////////////////////////
	// establish contact with xml code used to adjust widget settings
	///////////////////////////////////////////////////////////////////////

	builder = gtk_builder_new_from_file("PAADP.glade");

	GtkCssProvider* cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(cssProvider, "gtk.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	///////////////////////////////////////////////////////////////////////
	// File Chooser - Resampling
	///////////////////////////////////////////////////////////////////////

	filechooser1 = GTK_WIDGET(gtk_builder_get_object(builder, "filechooser1"));
		GtkFileFilter *filter = gtk_file_filter_new();
			gtk_file_filter_set_name(filter, "CSV (Comma delimited) (*.csv)");
				gtk_file_filter_add_pattern(filter, "*.csv");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser1), filter);
		filter = gtk_file_filter_new();
			gtk_file_filter_set_name(filter, "TAB (Tab delimited) (*.tab)");
				gtk_file_filter_add_pattern(filter, "*.tab");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser1), filter);
		filter = gtk_file_filter_new();
			gtk_file_filter_set_name(filter, "Text (delimited) (*.txt)");
				gtk_file_filter_add_pattern(filter, "*.txt");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser1), filter);
		filter = gtk_file_filter_new();
			gtk_file_filter_set_name(filter, "DAT (delimited) (*.dat)");
				gtk_file_filter_add_pattern(filter, "*.dat");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser1), filter);
		filter = gtk_file_filter_new();
			gtk_file_filter_set_name(filter, "Excel Workbook (*.xlsx)");
				gtk_file_filter_add_pattern(filter, "*.xlsx");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser1), filter);
		filter = gtk_file_filter_new();
			gtk_file_filter_set_name(filter, "Excel 97-2003 Workbook (*.xls)");
				gtk_file_filter_add_pattern(filter, "*.xls");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser1), filter);
		filter = gtk_file_filter_new();
			gtk_file_filter_set_name(filter, "GT3X (ActiGraph) (*.gt3x)");
				gtk_file_filter_add_pattern(filter, "*.gt3x");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser1), filter);
		filter = gtk_file_filter_new();
			gtk_file_filter_set_name(filter, "BIN (GENEActiv) (*.bin)");
				gtk_file_filter_add_pattern(filter, "*.bin");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser1), filter);
		filter = gtk_file_filter_new();
			gtk_file_filter_set_name(filter, "CWA (Axivity) (*.cwa)");
				gtk_file_filter_add_pattern(filter, "*.cwa");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser1), filter);

	///////////////////////////////////////////////////////////////////////
	// File Chooser - Raw Data Processing
	///////////////////////////////////////////////////////////////////////
	
	filechooser2 = GTK_WIDGET(gtk_builder_get_object(builder, "filechooser2"));
		GtkFileFilter *filter2 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter2, "CSV (Comma delimited) (*.csv)");
				gtk_file_filter_add_pattern(filter2, "*.csv");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser2), filter2);
		filter2 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter2, "TAB (Tab delimited) (*.tab)");
				gtk_file_filter_add_pattern(filter2, "*.tab");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser2), filter2);
		filter2 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter2, "Text (delimited) (*.txt)");
				gtk_file_filter_add_pattern(filter2, "*.txt");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser2), filter2);
		filter2 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter2, "DAT (delimited) (*.dat)");
				gtk_file_filter_add_pattern(filter2, "*.dat");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser2), filter2);
		filter2 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter2, "Excel Workbook (*.xlsx)");
				gtk_file_filter_add_pattern(filter2, "*.xlsx");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser2), filter2);
		filter2 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter2, "Excel 97-2003 Workbook (*.xls)");
				gtk_file_filter_add_pattern(filter2, "*.xls");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser2), filter2);
		filter2 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter2, "GT3X (ActiGraph) (*.gt3x)");
				gtk_file_filter_add_pattern(filter2, "*.gt3x");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser2), filter2);
		filter2 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter2, "BIN (GENEActiv) (*.bin)");
				gtk_file_filter_add_pattern(filter2, "*.bin");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser2), filter2);
		filter2 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter2, "CWA (Axivity) (*.cwa)");
				gtk_file_filter_add_pattern(filter2, "*.cwa");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser2), filter2);

	///////////////////////////////////////////////////////////////////////
	// File Chooser - Epoch Data Processing
	///////////////////////////////////////////////////////////////////////	

	filechooser3 = GTK_WIDGET(gtk_builder_get_object(builder, "filechooser3"));
		GtkFileFilter *filter3 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter3, "CSV (Comma delimited) (*.csv)");
				gtk_file_filter_add_pattern(filter3, "*.csv");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser3), filter3);
		filter3 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter3, "TAB (Tab delimited) (*.tab)");
				gtk_file_filter_add_pattern(filter3, "*.tab");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser3), filter3);
		filter3 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter3, "Text (delimited) (*.txt)");
				gtk_file_filter_add_pattern(filter3, "*.txt");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser3), filter3);
		filter3 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter3, "DAT (delimited) (*.dat)");
				gtk_file_filter_add_pattern(filter3, "*.dat");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser3), filter3);
		filter3 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter3, "Excel Workbook (*.xlsx)");
				gtk_file_filter_add_pattern(filter3, "*.xlsx");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser3), filter3);
		filter3 = gtk_file_filter_new();
			gtk_file_filter_set_name(filter3, "Excel 97-2003 Workbook (*.xls)");
				gtk_file_filter_add_pattern(filter3, "*.xls");
				gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filechooser3), filter3);
			
	///////////////////////////////////////////////////////////////////////
	// Main Window - Initialization & Connection to Signals
	///////////////////////////////////////////////////////////////////////

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
		gtk_builder_connect_signals(builder, NULL);

	///////////////////////////////////////////////////////////////////////
	// Main Window Declare All the Widgets & About & Timestamp
	///////////////////////////////////////////////////////////////////////
		
	quit1 = GTK_WIDGET(gtk_builder_get_object(builder, "quit1"));
	about1 = GTK_WIDGET(gtk_builder_get_object(builder, "about1"));
	timestamp1 = GTK_WIDGET(gtk_builder_get_object(builder, "timestamp1"));
	buttonbox1 = GTK_WIDGET(gtk_builder_get_object(builder, "buttonbox1"));
	timestampbutton1 = GTK_WIDGET(gtk_builder_get_object(builder, "timestampbutton1"));

	///////////////////////////////////////////////////////////////////////
	// Main Window Declare All the Widgets - Resample
	///////////////////////////////////////////////////////////////////////

	rsbutton1 = GTK_WIDGET(gtk_builder_get_object(builder, "rsbutton1"));
	rsbutton2 = GTK_WIDGET(gtk_builder_get_object(builder, "rsbutton2"));
	rsbutton3 = GTK_WIDGET(gtk_builder_get_object(builder, "rsbutton3"));
	rsentry1 = GTK_WIDGET(gtk_builder_get_object(builder, "rsentry1"));
	rsentry2 = GTK_WIDGET(gtk_builder_get_object(builder, "rsentry2"));
	rsentry3 = GTK_WIDGET(gtk_builder_get_object(builder, "rsentry3"));
	rsspin1 = GTK_WIDGET(gtk_builder_get_object(builder, "rsspin1"));
	rsspin2 = GTK_WIDGET(gtk_builder_get_object(builder, "rsspin2"));
	rsspin3 = GTK_WIDGET(gtk_builder_get_object(builder, "rsspin3"));
	rsspin4 = GTK_WIDGET(gtk_builder_get_object(builder, "rsspin4"));
	rsspin5 = GTK_WIDGET(gtk_builder_get_object(builder, "rsspin5"));
	rsspin6 = GTK_WIDGET(gtk_builder_get_object(builder, "rsspin6"));
	rsspin7 = GTK_WIDGET(gtk_builder_get_object(builder, "rsspin7"));
	rsspin8 = GTK_WIDGET(gtk_builder_get_object(builder, "rsspin8"));
	rsspin9 = GTK_WIDGET(gtk_builder_get_object(builder, "rsspin9"));
	rsspin10 = GTK_WIDGET(gtk_builder_get_object(builder, "rsspin10"));
	rscheck1 = GTK_WIDGET(gtk_builder_get_object(builder, "rscheck1"));
	rscheck2 = GTK_WIDGET(gtk_builder_get_object(builder, "rscheck2"));
	rscheck3 = GTK_WIDGET(gtk_builder_get_object(builder, "rscheck3"));
	rscheck4 = GTK_WIDGET(gtk_builder_get_object(builder, "rscheck4"));
	rscheck5 = GTK_WIDGET(gtk_builder_get_object(builder, "rscheck5"));
	rsradio1 = GTK_WIDGET(gtk_builder_get_object(builder, "rsradio1"));
	rsradio2 = GTK_WIDGET(gtk_builder_get_object(builder, "rsradio2"));
	rsradio3 = GTK_WIDGET(gtk_builder_get_object(builder, "rsradio3"));
	rsradio4 = GTK_WIDGET(gtk_builder_get_object(builder, "rsradio4"));
	rsradio5 = GTK_WIDGET(gtk_builder_get_object(builder, "rsradio5"));
	rsradio6 = GTK_WIDGET(gtk_builder_get_object(builder, "rsradio6"));
	rsradio7 = GTK_WIDGET(gtk_builder_get_object(builder, "rsradio7"));
	rsradio8 = GTK_WIDGET(gtk_builder_get_object(builder, "rsradio8"));
	rsradio9 = GTK_WIDGET(gtk_builder_get_object(builder, "rsradio9"));
	rsradio10 = GTK_WIDGET(gtk_builder_get_object(builder, "rsradio10"));
	rscombo1 = GTK_WIDGET(gtk_builder_get_object(builder, "rscombo1"));
	rscombo2 = GTK_WIDGET(gtk_builder_get_object(builder, "rscombo2"));
	rscombo3 = GTK_WIDGET(gtk_builder_get_object(builder, "rscombo3"));
	rscombo4 = GTK_WIDGET(gtk_builder_get_object(builder, "rscombo4"));
	rscombo5 = GTK_WIDGET(gtk_builder_get_object(builder, "rscombo5"));
	rsfilechooserbutton = GTK_WIDGET(gtk_builder_get_object(builder, "rsfilechooserbutton"));

	///////////////////////////////////////////////////////////////////////
	// Main Window Declare All the Widgets - Raw Data
	///////////////////////////////////////////////////////////////////////

	rdbutton1 = GTK_WIDGET(gtk_builder_get_object(builder, "rdbutton1"));
	rdbutton2 = GTK_WIDGET(gtk_builder_get_object(builder, "rdbutton2"));
	rdbutton3 = GTK_WIDGET(gtk_builder_get_object(builder, "rdbutton3"));
	rdentry1 = GTK_WIDGET(gtk_builder_get_object(builder, "rdentry1"));
	rdentry2 = GTK_WIDGET(gtk_builder_get_object(builder, "rdentry2"));
	rdentry3 = GTK_WIDGET(gtk_builder_get_object(builder, "rdentry3"));
	rdspin1 = GTK_WIDGET(gtk_builder_get_object(builder, "rdspin1"));
	rdspin2 = GTK_WIDGET(gtk_builder_get_object(builder, "rdspin2"));
	rdspin3 = GTK_WIDGET(gtk_builder_get_object(builder, "rdspin3"));
	rdspin4 = GTK_WIDGET(gtk_builder_get_object(builder, "rdspin4"));
	rdspin5 = GTK_WIDGET(gtk_builder_get_object(builder, "rdspin5"));
	rdspin6 = GTK_WIDGET(gtk_builder_get_object(builder, "rdspin6"));
	rdspin7 = GTK_WIDGET(gtk_builder_get_object(builder, "rdspin7"));
	rdspin8 = GTK_WIDGET(gtk_builder_get_object(builder, "rdspin8"));
	rdspin9 = GTK_WIDGET(gtk_builder_get_object(builder, "rdspin9"));
	rdspin10 = GTK_WIDGET(gtk_builder_get_object(builder, "rdspin10"));
	rdcheck1 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck1"));
	rdcheck2 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck2"));
	rdcheck3 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck3"));
	rdcheck4 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck4"));
	rdcheck5 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck5"));
	rdcheck6 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck6"));
	rdcheck7 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck7"));
	rdcheck8 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck8"));
	rdcheck9 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck9"));
	rdcheck10 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck10"));
	rdcheck11 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck11"));
	rdcheck12 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck12"));
	rdcheck13 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck13"));
	rdcheck14 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck14"));
	rdcheck15 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck15"));
	rdcheck16 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck16"));
	rdcheck17 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck17"));
	rdcheck18 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck18"));
	rdcheck19 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck19"));
	rdcheck20 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck20"));
	rdcheck21 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck21"));
	rdcheck22 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcheck22"));
	rdradio1 = GTK_WIDGET(gtk_builder_get_object(builder, "rdradio1"));
	rdradio2 = GTK_WIDGET(gtk_builder_get_object(builder, "rdradio2"));
	rdradio3 = GTK_WIDGET(gtk_builder_get_object(builder, "rdradio3"));
	rdradio4 = GTK_WIDGET(gtk_builder_get_object(builder, "rdradio4"));
	rdradio5 = GTK_WIDGET(gtk_builder_get_object(builder, "rdradio5"));
	rdradio6 = GTK_WIDGET(gtk_builder_get_object(builder, "rdradio6"));
	rdradio7 = GTK_WIDGET(gtk_builder_get_object(builder, "rdradio7"));
	rdradio8 = GTK_WIDGET(gtk_builder_get_object(builder, "rdradio8"));
	rdcombo1 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcombo1"));
	rdcombo2 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcombo2"));
	rdcombo3 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcombo3"));
	rdcombo4 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcombo4"));
	rdcombo5 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcombo5"));
	rdcombo6 = GTK_WIDGET(gtk_builder_get_object(builder, "rdcombo6"));
	rdfilechooserbutton = GTK_WIDGET(gtk_builder_get_object(builder, "rdfilechooserbutton"));

	///////////////////////////////////////////////////////////////////////
	// Main Window Declare All the Widgets - Epoch Data
	///////////////////////////////////////////////////////////////////////

	edbutton1 = GTK_WIDGET(gtk_builder_get_object(builder, "edbutton1"));
	edbutton2 = GTK_WIDGET(gtk_builder_get_object(builder, "edbutton2"));
	edbutton3 = GTK_WIDGET(gtk_builder_get_object(builder, "edbutton3"));
	edentry1 = GTK_WIDGET(gtk_builder_get_object(builder, "edentry1"));
	edentry2 = GTK_WIDGET(gtk_builder_get_object(builder, "edentry2"));
	edentry3 = GTK_WIDGET(gtk_builder_get_object(builder, "edentry3"));
	edentry4 = GTK_WIDGET(gtk_builder_get_object(builder, "edentry4"));
	edentry5 = GTK_WIDGET(gtk_builder_get_object(builder, "edentry5"));
	edentry6 = GTK_WIDGET(gtk_builder_get_object(builder, "edentry6"));
	edentry7 = GTK_WIDGET(gtk_builder_get_object(builder, "edentry7"));
	edspin1 = GTK_WIDGET(gtk_builder_get_object(builder, "edspin1"));
	edspin2 = GTK_WIDGET(gtk_builder_get_object(builder, "edspin2"));
	edspin3 = GTK_WIDGET(gtk_builder_get_object(builder, "edspin3"));
	edspin4 = GTK_WIDGET(gtk_builder_get_object(builder, "edspin4"));
	edspin5 = GTK_WIDGET(gtk_builder_get_object(builder, "edspin5"));
	edspin6 = GTK_WIDGET(gtk_builder_get_object(builder, "edspin6"));
	edspin7 = GTK_WIDGET(gtk_builder_get_object(builder, "edspin7"));
	edspin8 = GTK_WIDGET(gtk_builder_get_object(builder, "edspin8"));
	edspin9 = GTK_WIDGET(gtk_builder_get_object(builder, "edspin9"));
	edcheck1 = GTK_WIDGET(gtk_builder_get_object(builder, "edcheck1"));
	edcheck2 = GTK_WIDGET(gtk_builder_get_object(builder, "edcheck2"));
	edcheck3 = GTK_WIDGET(gtk_builder_get_object(builder, "edcheck3"));
	edcheck4 = GTK_WIDGET(gtk_builder_get_object(builder, "edcheck4"));
	edcheck5 = GTK_WIDGET(gtk_builder_get_object(builder, "edcheck5"));
	edcheck6 = GTK_WIDGET(gtk_builder_get_object(builder, "edcheck6"));
	edcheck7 = GTK_WIDGET(gtk_builder_get_object(builder, "edcheck7"));
	edcheck8 = GTK_WIDGET(gtk_builder_get_object(builder, "edcheck8"));
	edradio1 = GTK_WIDGET(gtk_builder_get_object(builder, "edradio1"));
	edradio2 = GTK_WIDGET(gtk_builder_get_object(builder, "edradio2"));
	edradio3 = GTK_WIDGET(gtk_builder_get_object(builder, "edradio3"));
	edradio4 = GTK_WIDGET(gtk_builder_get_object(builder, "edradio4"));
	edradio5 = GTK_WIDGET(gtk_builder_get_object(builder, "edradio5"));
	edradio6 = GTK_WIDGET(gtk_builder_get_object(builder, "edradio6"));
	edcombo1 = GTK_WIDGET(gtk_builder_get_object(builder, "edcombo1"));
	edcombo2 = GTK_WIDGET(gtk_builder_get_object(builder, "edcombo2"));
	edcombo3 = GTK_WIDGET(gtk_builder_get_object(builder, "edcombo3"));
	edcombo4 = GTK_WIDGET(gtk_builder_get_object(builder, "edcombo4"));
	edcombo5 = GTK_WIDGET(gtk_builder_get_object(builder, "edcombo5"));
	edcombo6 = GTK_WIDGET(gtk_builder_get_object(builder, "edcombo6"));
	edcombo7 = GTK_WIDGET(gtk_builder_get_object(builder, "edcombo7"));
	edcombo8 = GTK_WIDGET(gtk_builder_get_object(builder, "edcombo8"));
	edcombo9 = GTK_WIDGET(gtk_builder_get_object(builder, "edcombo9"));
	edcombo10 = GTK_WIDGET(gtk_builder_get_object(builder, "edcombo10"));
	edcombo11 = GTK_WIDGET(gtk_builder_get_object(builder, "edcombo11"));
	edfilechooserbutton = GTK_WIDGET(gtk_builder_get_object(builder, "edfilechooserbutton"));

	///////////////////////////////////////////////////////////////////////
	// Main Window Declare All the Widgets - File Viewer
	///////////////////////////////////////////////////////////////////////

	fvbutton1 = GTK_WIDGET(gtk_builder_get_object(builder, "fvbutton1"));
	fvcombo1 = GTK_WIDGET(gtk_builder_get_object(builder, "fvcombo1"));
	fvcombo2 = GTK_WIDGET(gtk_builder_get_object(builder, "fvcombo2"));
	fventry1 = GTK_WIDGET(gtk_builder_get_object(builder, "fventry1"));
	fvfilechooserbutton = GTK_WIDGET(gtk_builder_get_object(builder, "fvfilechooserbutton"));

	///////////////////////////////////////////////////////////////////////
	// Main Window Declare All the Widgets - Variable Definitions
	///////////////////////////////////////////////////////////////////////

	vdcombo1 = GTK_WIDGET(gtk_builder_get_object(builder, "vdcombo1"));
	vdentry1 = GTK_WIDGET(gtk_builder_get_object(builder, "vdentry1"));

	///////////////////////////////////////////////////////////////////////
	// File Chooser 1 Declare All the Widgets
	///////////////////////////////////////////////////////////////////////
	
	fc1button1 = GTK_WIDGET(gtk_builder_get_object(builder, "fc1button1"));
	fc1button2 = GTK_WIDGET(gtk_builder_get_object(builder, "fc1button2"));

	///////////////////////////////////////////////////////////////////////
	// File Chooser 2 Declare All the Widgets
	///////////////////////////////////////////////////////////////////////

	fc2button1 = GTK_WIDGET(gtk_builder_get_object(builder, "fc2button1"));
	fc2button2 = GTK_WIDGET(gtk_builder_get_object(builder, "fc2button2"));

	///////////////////////////////////////////////////////////////////////
	// File Chooser 3 Declare All the Widgets
	///////////////////////////////////////////////////////////////////////

	fc3button1 = GTK_WIDGET(gtk_builder_get_object(builder, "fc3button1"));
	fc3button2 = GTK_WIDGET(gtk_builder_get_object(builder, "fc3button2"));

	///////////////////////////////////////////////////////////////////////
	// Resample Dialogs Declare All the Widgets
	///////////////////////////////////////////////////////////////////////

	resampledialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "resampledialog1"));
	resampledialog2 = GTK_WIDGET(gtk_builder_get_object(builder, "resampledialog2"));
	resampledialogbutton1 = GTK_WIDGET(gtk_builder_get_object(builder, "resampledialogbutton1"));
	resampledialogbutton2 = GTK_WIDGET(gtk_builder_get_object(builder, "resampledialogbutton2"));
	rsdentry1 = GTK_WIDGET(gtk_builder_get_object(builder, "rsdentry1"));

	///////////////////////////////////////////////////////////////////////
	// Raw Dialogs Declare All the Widgets
	///////////////////////////////////////////////////////////////////////

	rawdialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "rawdialog1"));
	rawdialog2 = GTK_WIDGET(gtk_builder_get_object(builder, "rawdialog2"));
	rawdialogbutton1 = GTK_WIDGET(gtk_builder_get_object(builder, "rawdialogbutton1"));
	rawdialogbutton2 = GTK_WIDGET(gtk_builder_get_object(builder, "rawdialogbutton2"));
	rddentry1 = GTK_WIDGET(gtk_builder_get_object(builder, "rddentry1"));

	///////////////////////////////////////////////////////////////////////
	// Epoch Dialogs Declare All the Widgets
	///////////////////////////////////////////////////////////////////////

	epochdialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "epochdialog1"));
	epochdialog2 = GTK_WIDGET(gtk_builder_get_object(builder, "epochdialog2"));
	epochdialogbutton1 = GTK_WIDGET(gtk_builder_get_object(builder, "epochdialogbutton1"));
	epochdialogbutton2 = GTK_WIDGET(gtk_builder_get_object(builder, "epochdialogbutton2"));
	eddentry1 = GTK_WIDGET(gtk_builder_get_object(builder, "eddentry1"));

	///////////////////////////////////////////////////////////////////////
	// File Viewer Dialogs Declare All the Widgets
	///////////////////////////////////////////////////////////////////////

	fvdialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "fvdialog1"));
	fvdialogbutton1 = GTK_WIDGET(gtk_builder_get_object(builder, "fvdialogbutton1"));
	fvdentry1 = GTK_WIDGET(gtk_builder_get_object(builder, "fvdentry1"));

	///////////////////////////////////////////////////////////////////////
	// Call the Main Window
	///////////////////////////////////////////////////////////////////////

	gtk_widget_show(window);
	gtk_main();

	return EXIT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// Callback Functions
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// Main Window Callbacks - Menubar
///////////////////////////////////////////////////////////////////////

void	on_quit1_activate(GtkMenuItem *b) {
	gtk_main_quit();
}

void	on_about1_activate(GtkMenuItem* b) {
	aboutwindow1 = GTK_WIDGET(gtk_builder_get_object(builder, "aboutwindow1"));
	gtk_widget_show(aboutwindow1);
}

void	on_buttonbox1_button_release_event(GtkButtonBox *b) {
	gtk_widget_hide(aboutwindow1);
}

void	on_timestamp1_activate(GtkMenuItem *b) {
	timestampdialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "timestampdialog1"));
	gtk_widget_show(timestampdialog1);
}

void	on_timestampbutton1_clicked(GtkButton* b) {
	gtk_widget_hide(timestampdialog1);
}

///////////////////////////////////////////////////////////////////////
// Main Window Callbacks - Resample Raw Data
///////////////////////////////////////////////////////////////////////

void	on_rsbutton1_clicked(GtkButton *b) {
		gtk_widget_show(filechooser1);
}

void	on_rscheck1_toggled(GtkCheckButton* b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T)
	{
		gtk_widget_set_sensitive(rsspin7, TRUE);
		gtk_widget_set_sensitive(rsspin4, FALSE);
		gtk_widget_set_sensitive(rsspin5, FALSE);
		gtk_widget_set_sensitive(rsspin6, FALSE);
	}
	else
	{
		gtk_widget_set_sensitive(rsspin7, FALSE);
		gtk_widget_set_sensitive(rsspin4, TRUE);
		gtk_widget_set_sensitive(rsspin5, TRUE);
		gtk_widget_set_sensitive(rsspin6, TRUE);
	}
}

void	on_rsbutton2_clicked(GtkButton* b) {
	calwindow1 = GTK_WIDGET(gtk_builder_get_object(builder, "calwindow1"));
	calendar1 = GTK_CALENDAR(gtk_builder_get_object(builder, "calendar1"));
	gtk_widget_show(calwindow1);
}

void on_rsradio1_toggled(GtkRadioButton* b) {
	gboolean T1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T1)
	{
		gtk_widget_set_sensitive(rsspin8, TRUE);
		gtk_widget_set_sensitive(rscombo1, TRUE);
		gtk_widget_set_sensitive(rsspin9, FALSE);
		gtk_widget_set_sensitive(rscombo2, FALSE);
		gtk_widget_set_sensitive(rsspin10, FALSE);
		gtk_widget_set_sensitive(rscombo3, FALSE);
		gtk_widget_set_sensitive(rsentry2, TRUE);
		gtk_widget_set_sensitive(rsentry3, TRUE);
		gtk_widget_set_sensitive(rsbutton2, TRUE);
	}
}

void on_rsradio2_toggled(GtkRadioButton* b) {
	gboolean T1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T1)
	{
		gtk_widget_set_sensitive(rsspin8, FALSE);
		gtk_widget_set_sensitive(rscombo1, FALSE);
		gtk_widget_set_sensitive(rsspin9, TRUE);
		gtk_widget_set_sensitive(rscombo2, TRUE);
		gtk_widget_set_sensitive(rsspin10, TRUE);
		gtk_widget_set_sensitive(rscombo3, TRUE);
		gtk_widget_set_sensitive(rsentry2, FALSE);
		gtk_widget_set_sensitive(rsentry3, FALSE);
		gtk_widget_set_sensitive(rsbutton2, FALSE);
	}
}

void on_rsradio3_toggled(GtkRadioButton* b) {
	gboolean T1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T1)
	{
		gtk_widget_set_sensitive(rsspin8, FALSE);
		gtk_widget_set_sensitive(rscombo1, FALSE);
		gtk_widget_set_sensitive(rsspin9, FALSE);
		gtk_widget_set_sensitive(rscombo2, FALSE);
		gtk_widget_set_sensitive(rsspin10, FALSE);
		gtk_widget_set_sensitive(rscombo3, FALSE);
		gtk_widget_set_sensitive(rsentry2, TRUE);
		gtk_widget_set_sensitive(rsentry3, TRUE);
		gtk_widget_set_sensitive(rsbutton2, TRUE);
	}
}

void on_rsradio4_toggled(GtkRadioButton* b) {
	gboolean T1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T1)
	{
		gtk_widget_set_sensitive(rsspin8, FALSE);
		gtk_widget_set_sensitive(rscombo1, FALSE);
		gtk_widget_set_sensitive(rsspin9, FALSE);
		gtk_widget_set_sensitive(rscombo2, FALSE);
		gtk_widget_set_sensitive(rsspin10, FALSE);
		gtk_widget_set_sensitive(rscombo3, FALSE);
		gtk_widget_set_sensitive(rsentry2, FALSE);
		gtk_widget_set_sensitive(rsentry3, FALSE);
		gtk_widget_set_sensitive(rsbutton2, FALSE);
	}
}

// Structure to store input data
typedef struct {
	gchar* combo_text1;
	gchar* combo_text2;
	gchar* combo_text3;
	gchar* combo_text4;
	gchar* combo_text5;
	const gchar* entry_text1;
	const gchar* entry_text2;
	const gchar* entry_text3;
	gdouble spin_value1;
	gdouble spin_value2;
	gdouble spin_value3;
	gdouble spin_value4;
	gdouble spin_value5;
	gdouble spin_value6;
	gdouble spin_value7;
	gdouble spin_value8;
	gdouble spin_value9;
	gdouble spin_value10;
	gboolean toggle_value1;
	gboolean toggle_value2;
	gboolean toggle_value3;
	gboolean toggle_value4;
	gboolean toggle_value5;
	gboolean radio_value1;
	gboolean radio_value2;
	gboolean radio_value3;
	gboolean radio_value4;
	gboolean radio_value5;
	gboolean radio_value6;
	gboolean radio_value7;
	gboolean radio_value8;
	gboolean radio_value9;
	gboolean radio_value10;
	gchar* file_chooser_path;
} InputData;

// Callback function to handle button click and write inputs to a text file
void on_rsbutton3_clicked(GtkButton* b) {
	// Retrieve data from widgets
	InputData input_data;

	// Retrieve data from GtkComboBoxText objects
	input_data.combo_text1 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rscombo1));
	input_data.combo_text2 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rscombo2));
	input_data.combo_text3 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rscombo3));
	input_data.combo_text4 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rscombo4));
	input_data.combo_text5 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rscombo5));

	// Retrieve data from GtkEntry objects
	input_data.entry_text1 = gtk_entry_get_text(GTK_ENTRY(rsentry1));
	input_data.entry_text2 = gtk_entry_get_text(GTK_ENTRY(rsentry2));
	input_data.entry_text3 = gtk_entry_get_text(GTK_ENTRY(rsentry3));

	// Retrieve data from GtkSpinButton objects
	input_data.spin_value1 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rsspin1));
	input_data.spin_value2 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rsspin2));
	input_data.spin_value3 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rsspin3));
	input_data.spin_value4 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rsspin4));
	input_data.spin_value5 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rsspin5));
	input_data.spin_value6 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rsspin6));
	input_data.spin_value7 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rsspin7));
	input_data.spin_value8 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rsspin8));
	input_data.spin_value9 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rsspin9));
	input_data.spin_value10 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rsspin10));

	// Retrieve data from GtkToggleButton objects
	input_data.toggle_value1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rscheck1));
	input_data.toggle_value2 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rscheck2));
	input_data.toggle_value3 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rscheck3));
	input_data.toggle_value4 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rscheck4));
	input_data.toggle_value5 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rscheck5));

	// Retrieve data from GtkRadioButton objects
	input_data.radio_value1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rsradio1));
	input_data.radio_value2 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rsradio2));
	input_data.radio_value3 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rsradio3));
	input_data.radio_value4 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rsradio4));
	input_data.radio_value5 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rsradio5));
	input_data.radio_value6 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rsradio6));
	input_data.radio_value7 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rsradio7));
	input_data.radio_value8 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rsradio8));
	input_data.radio_value9 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rsradio9));
	input_data.radio_value10 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rsradio10));

	// Retrieve data from GtkFileChooserButtons
	input_data.file_chooser_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(rsfilechooserbutton));

	// Remove any existing file in the directory //
	FILE* filecheck = fopen("commands/resample/resample_output.txt", "r");
	if (filecheck != NULL) {
		fclose(filecheck);
		remove("commands/resample/resample_output.txt");
	}
	else {
		//file doesn't exists or cannot be opened (es. you don't have access permission)
	}

	// Open the file in append mode and write the inputs
	FILE* file = fopen("commands/resample/resample_output.txt", "a");
	if (file != NULL) {
		fprintf(file, "Timestamp Form: %s\n", input_data.combo_text1);
		fprintf(file, "Date Form: %s\n", input_data.combo_text2);
		fprintf(file, "Time Form: %s\n", input_data.combo_text3);
		fprintf(file, "ADC Bits: %s\n", input_data.combo_text4);
		fprintf(file, "Dyn Range: %s\n", input_data.combo_text5);
		fprintf(file, "Files Selected: %s\n", input_data.entry_text1);
		fprintf(file, "Start Date: %s\n", input_data.entry_text2);
		fprintf(file, "Start Time: %s\n", input_data.entry_text3);
		fprintf(file, "Sample Rate: %.2f\n", input_data.spin_value1);
		fprintf(file, "Resample Rate: %.2f\n", input_data.spin_value2);
		fprintf(file, "Data Start Row: %.2f\n", input_data.spin_value3);
		fprintf(file, "X-Axis Column: %.2f\n", input_data.spin_value4);
		fprintf(file, "Y-Axis Column: %.2f\n", input_data.spin_value5);
		fprintf(file, "Z-Axis Column: %.2f\n", input_data.spin_value6);
		fprintf(file, "VM Column: %.2f\n", input_data.spin_value7);
		fprintf(file, "Timestamp Column: %.2f\n", input_data.spin_value8);
		fprintf(file, "Date Row: %.2f\n", input_data.spin_value9);
		fprintf(file, "Time Row: %.2f\n", input_data.spin_value10);
		fprintf(file, "VM Data Only: %s\n", input_data.toggle_value1 ? "True" : "False");
		fprintf(file, "CSV Output: %s\n", input_data.toggle_value2 ? "True" : "False");
		fprintf(file, "TAB Output: %s\n", input_data.toggle_value3 ? "True" : "False");
		fprintf(file, "TXT Output: %s\n", input_data.toggle_value4 ? "True" : "False");
		fprintf(file, "XLSX Output: %s\n", input_data.toggle_value5 ? "True" : "False");
		fprintf(file, "In Column: %s\n", input_data.radio_value1 ? "True" : "False");
		fprintf(file, "In Header: %s\n", input_data.radio_value2 ? "True" : "False");
		fprintf(file, "User Input: %s\n", input_data.radio_value3 ? "True" : "False");
		fprintf(file, "None: %s\n", input_data.radio_value4 ? "True" : "False");
		fprintf(file, "Retain Yes: %s\n", input_data.radio_value5 ? "True" : "False");
		fprintf(file, "Retain No: %s\n", input_data.radio_value6 ? "True" : "False");
		fprintf(file, "ADC Yes: %s\n", input_data.radio_value7 ? "True" : "False");
		fprintf(file, "ADC No: %s\n", input_data.radio_value8 ? "True" : "False");
		fprintf(file, "Multi Yes: %s\n", input_data.radio_value9 ? "True" : "False");
		fprintf(file, "Multi No: %s\n", input_data.radio_value10 ? "True" : "False");
		fprintf(file, "File Chooser Path: %s\n", input_data.file_chooser_path);
		fprintf(file, "------------------------\n");

		// Close the file
		fclose(file);
	}
	else {
		g_print("Error: Unable to open the file for writing.\n");
	}
	// Free allocated memory
	g_free(input_data.combo_text1);
	g_free(input_data.combo_text2);
	g_free(input_data.combo_text3);
	g_free(input_data.combo_text4);
	g_free(input_data.combo_text5);
	g_free((char*)input_data.entry_text1);
	g_free((char*)input_data.entry_text2);
	g_free((char*)input_data.entry_text3);
	g_free(input_data.file_chooser_path);

	// Function to replace back-slashes with forward-slashes
	void replaceBackslashes(char* str) {
		while (*str) {
			if (*str == '\\') {
				*str = '/';
			}
			str++;
		}
	}
	// Task 1: Detect current working directory
	char Astring[256];
	if (getcwd(Astring, sizeof(Astring)) == NULL) {
		perror("getcwd() error");
		return;
	}

	// Task 1B: Replace back-slashes with forward-slashes in Astring
	replaceBackslashes(Astring);

	// Task 2: Declare second string
	char Bstring[] = "/R/R-4.3.3/bin/Rscript.exe ";

	// Task 3: Declare third string
	char Cstring[] = "/commands/resample_r/resample_script.R";

	// Task 4: Concatenate strings
	char finalString[512];
	snprintf(finalString, sizeof(finalString), "%s%s%s%s", Astring, Bstring, Astring, Cstring);

	// Task 5: Execute system call
	char systemCommand[512];
	snprintf(systemCommand, sizeof(systemCommand), "\"%s\"\n", finalString);
	system(systemCommand);

	// Function to check if a file exists
	const gchar* filename = "errors/resample/errors.txt";
	gboolean file_exists(const gchar* filename) {
		FILE* errfile = fopen(filename, "r");
		if (errfile) {
			fclose(errfile);
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

	if (file_exists(filename)) {
		// File exists, read its contents
		GError* error = NULL;
		gchar* contents = NULL;
		// Dialog #2 - Processing Completed with Errors
		resampledialog2 = GTK_WIDGET(gtk_builder_get_object(builder, "resampledialog2"));
		GtkTextView* rsdentry2 = GTK_TEXT_VIEW(rsdentry1);

		if (g_file_get_contents(filename, &contents, NULL, &error)) {
			// Display the contents in the GtkTextView
			GtkTextBuffer* bufferrsd = gtk_text_view_get_buffer(rsdentry2);
			gtk_text_buffer_set_text(bufferrsd, contents, -1);

			// Free allocated memory for contents
			g_free(contents);
		}
		else {
			// Error handling if reading fails
			g_printerr("Error reading file: %s\n", error->message);
			g_error_free(error);
		}
		gtk_widget_show(resampledialog2);
	}
	else {
		// Dialog #1 - Processing Complete
		resampledialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "resampledialog1"));
		gtk_widget_show(resampledialog1);
	}
}

///////////////////////////////////////////////////////////////////////
// File Chooser 1 Callbacks
///////////////////////////////////////////////////////////////////////

void	on_fc1button1_clicked(GtkButton* b) {
	GSList *files, *temp;
	gchar *file_names = NULL;
	files = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(filechooser1));
	temp = files;
	while (temp != NULL) {
		gchar* file_path = g_shell_quote(temp->data);
		file_names = g_strdup_printf("%s \"%s\"", file_names ? file_names : "", file_path);
		g_free(file_path);
		temp = g_slist_next(temp);
	}
	g_slist_free(files);
	gtk_entry_set_text(GTK_ENTRY(rsentry1), file_names);
	gtk_widget_hide(filechooser1);
}

void	on_fc1button2_clicked(GtkButton* b) {
		gtk_entry_set_text(GTK_ENTRY(rsentry1), "No File(s) Selected");
		gtk_widget_hide(filechooser1);
}

///////////////////////////////////////////////////////////////////////
// Main Window Callbacks - Raw Data Processing
///////////////////////////////////////////////////////////////////////

void	on_rdbutton1_clicked(GtkButton* b) {
	gtk_widget_show(filechooser2);
}

void	on_rdcheck1_toggled(GtkCheckButton* b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T)
	{
		gtk_widget_set_sensitive(rdspin2, TRUE);
	}
	else
	{
		gtk_widget_set_sensitive(rdspin2, FALSE);
	}
}

void	on_rdcheck3_toggled(GtkCheckButton* b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T)
	{
		gtk_widget_set_sensitive(rdspin7, TRUE);
		gtk_widget_set_sensitive(rdspin4, FALSE);
		gtk_widget_set_sensitive(rdspin5, FALSE);
		gtk_widget_set_sensitive(rdspin6, FALSE);
	}
	else
	{
		gtk_widget_set_sensitive(rdspin7, FALSE);
		gtk_widget_set_sensitive(rdspin4, TRUE);
		gtk_widget_set_sensitive(rdspin5, TRUE);
		gtk_widget_set_sensitive(rdspin6, TRUE);
	}
}

void	on_rdbutton2_clicked(GtkButton* b) {
	calwindow2 = GTK_WIDGET(gtk_builder_get_object(builder, "calwindow2"));
	calendar2 = GTK_CALENDAR(gtk_builder_get_object(builder, "calendar2"));
	gtk_widget_show(calwindow2);
}

void on_rdradio1_toggled(GtkRadioButton* b) {
	gboolean T1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T1)
	{
		gtk_widget_set_sensitive(rdspin8, TRUE);
		gtk_widget_set_sensitive(rdcombo2, TRUE);
		gtk_widget_set_sensitive(rdspin9, FALSE);
		gtk_widget_set_sensitive(rdcombo3, FALSE);
		gtk_widget_set_sensitive(rdspin10, FALSE);
		gtk_widget_set_sensitive(rdcombo4, FALSE);
		gtk_widget_set_sensitive(rdentry2, TRUE);
		gtk_widget_set_sensitive(rdentry3, TRUE);
		gtk_widget_set_sensitive(rdbutton2, TRUE);
	}
}

void on_rdradio2_toggled(GtkRadioButton* b) {
	gboolean T1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T1)
	{
		gtk_widget_set_sensitive(rdspin8, FALSE);
		gtk_widget_set_sensitive(rdcombo2, FALSE);
		gtk_widget_set_sensitive(rdspin9, TRUE);
		gtk_widget_set_sensitive(rdcombo3, TRUE);
		gtk_widget_set_sensitive(rdspin10, TRUE);
		gtk_widget_set_sensitive(rdcombo4, TRUE);
		gtk_widget_set_sensitive(rdentry2, FALSE);
		gtk_widget_set_sensitive(rdentry3, FALSE);
		gtk_widget_set_sensitive(rdbutton2, FALSE);
	}
}

void on_rdradio3_toggled(GtkRadioButton* b) {
	gboolean T1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T1)
	{
		gtk_widget_set_sensitive(rdspin8, FALSE);
		gtk_widget_set_sensitive(rdcombo2, FALSE);
		gtk_widget_set_sensitive(rdspin9, FALSE);
		gtk_widget_set_sensitive(rdcombo3, FALSE);
		gtk_widget_set_sensitive(rdspin10, FALSE);
		gtk_widget_set_sensitive(rdcombo4, FALSE);
		gtk_widget_set_sensitive(rdentry2, TRUE);
		gtk_widget_set_sensitive(rdentry3, TRUE);
		gtk_widget_set_sensitive(rdbutton2, TRUE);
	}
}

void on_rdradio4_toggled(GtkRadioButton* b) {
	gboolean T1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T1)
	{
		gtk_widget_set_sensitive(rdspin8, FALSE);
		gtk_widget_set_sensitive(rdcombo2, FALSE);
		gtk_widget_set_sensitive(rdspin9, FALSE);
		gtk_widget_set_sensitive(rdcombo3, FALSE);
		gtk_widget_set_sensitive(rdspin10, FALSE);
		gtk_widget_set_sensitive(rdcombo4, FALSE);
		gtk_widget_set_sensitive(rdentry2, FALSE);
		gtk_widget_set_sensitive(rdentry3, FALSE);
		gtk_widget_set_sensitive(rdbutton2, FALSE);
	}
}

// Structure to store input data
typedef struct {
	gchar* combo_text1;
	gchar* combo_text2;
	gchar* combo_text3;
	gchar* combo_text4;
	gchar* combo_text5;
	gchar* combo_text6;
	const gchar* entry_text1;
	const gchar* entry_text2;
	const gchar* entry_text3;
	gdouble spin_value1;
	gdouble spin_value2;
	gdouble spin_value3;
	gdouble spin_value4;
	gdouble spin_value5;
	gdouble spin_value6;
	gdouble spin_value7;
	gdouble spin_value8;
	gdouble spin_value9;
	gdouble spin_value10;
	gboolean toggle_value1;
	gboolean toggle_value2;
	gboolean toggle_value3;
	gboolean toggle_value4;
	gboolean toggle_value5;
	gboolean toggle_value6;
	gboolean toggle_value7;
	gboolean toggle_value8;
	gboolean toggle_value9;
	gboolean toggle_value10;
	gboolean toggle_value11;
	gboolean toggle_value12;
	gboolean toggle_value13;
	gboolean toggle_value14;
	gboolean toggle_value15;
	gboolean toggle_value16;
	gboolean toggle_value17;
	gboolean toggle_value18;
	gboolean toggle_value19;
	gboolean toggle_value20;
	gboolean toggle_value21;
	gboolean toggle_value22;
	gboolean radio_value1;
	gboolean radio_value2;
	gboolean radio_value3;
	gboolean radio_value4;
	gboolean radio_value5;
	gboolean radio_value6;
	gboolean radio_value7;
	gboolean radio_value8;
	gchar* file_chooser_path;
} InputDataRaw;

// Callback function to handle button click and write inputs to a text file
void on_rdbutton3_clicked(GtkButton* b) {
	// Retrieve data from widgets
	InputDataRaw input_dataraw;

	// Retrieve data from GtkComboBoxText objects
	input_dataraw.combo_text1 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rdcombo1));
	input_dataraw.combo_text2 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rdcombo2));
	input_dataraw.combo_text3 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rdcombo3));
	input_dataraw.combo_text4 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rdcombo4));
	input_dataraw.combo_text5 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rdcombo5));
	input_dataraw.combo_text6 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rdcombo6));

	// Retrieve data from GtkEntry objects
	input_dataraw.entry_text1 = gtk_entry_get_text(GTK_ENTRY(rdentry1));
	input_dataraw.entry_text2 = gtk_entry_get_text(GTK_ENTRY(rdentry2));
	input_dataraw.entry_text3 = gtk_entry_get_text(GTK_ENTRY(rdentry3));

	// Retrieve data from GtkSpinButton objects
	input_dataraw.spin_value1 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rdspin1));
	input_dataraw.spin_value2 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rdspin2));
	input_dataraw.spin_value3 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rdspin3));
	input_dataraw.spin_value4 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rdspin4));
	input_dataraw.spin_value5 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rdspin5));
	input_dataraw.spin_value6 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rdspin6));
	input_dataraw.spin_value7 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rdspin7));
	input_dataraw.spin_value8 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rdspin8));
	input_dataraw.spin_value9 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rdspin9));
	input_dataraw.spin_value10 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(rdspin10));

	// Retrieve data from GtkToggleButton objects
	input_dataraw.toggle_value1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck1));
	input_dataraw.toggle_value2 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck2));
	input_dataraw.toggle_value3 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck3));
	input_dataraw.toggle_value4 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck4));
	input_dataraw.toggle_value5 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck5));
	input_dataraw.toggle_value6 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck6));
	input_dataraw.toggle_value7 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck7));
	input_dataraw.toggle_value8 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck8));
	input_dataraw.toggle_value9 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck9));
	input_dataraw.toggle_value10 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck10));
	input_dataraw.toggle_value11 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck11));
	input_dataraw.toggle_value12 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck12));
	input_dataraw.toggle_value13 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck13));
	input_dataraw.toggle_value14 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck14));
	input_dataraw.toggle_value15 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck15));
	input_dataraw.toggle_value16 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck16));
	input_dataraw.toggle_value17 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck17));
	input_dataraw.toggle_value18 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck18));
	input_dataraw.toggle_value19 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck19));
	input_dataraw.toggle_value20 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck20));
	input_dataraw.toggle_value21 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck21));
	input_dataraw.toggle_value22 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdcheck22));

	// Retrieve data from GtkRadioButton objects
	input_dataraw.radio_value1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdradio1));
	input_dataraw.radio_value2 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdradio2));
	input_dataraw.radio_value3 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdradio3));
	input_dataraw.radio_value4 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdradio4));
	input_dataraw.radio_value5 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdradio5));
	input_dataraw.radio_value6 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdradio6));
	input_dataraw.radio_value7 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdradio7));
	input_dataraw.radio_value8 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rdradio8));

	// Retrieve data from GtkFileChooserButtons
	input_dataraw.file_chooser_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(rdfilechooserbutton));

	// Remove any existing file in the directory //
	FILE* filecheck = fopen("commands/raw/raw_output.txt", "r");
	if (filecheck != NULL) {
		fclose(filecheck);
		remove("commands/raw/raw_output.txt");
	}
	else {
		//file doesn't exists or cannot be opened (es. you don't have access permission)
	}

	// Open the file in append mode and write the inputs
	FILE* file = fopen("commands/raw/raw_output.txt", "a");
	if (file != NULL) {
		fprintf(file, "Input Units: %s\n", input_dataraw.combo_text1);
		fprintf(file, "Timestamp Form: %s\n", input_dataraw.combo_text2);
		fprintf(file, "Date Form: %s\n", input_dataraw.combo_text3);
		fprintf(file, "Time Form: %s\n", input_dataraw.combo_text4);
		fprintf(file, "Output Units: %s\n", input_dataraw.combo_text5);
		fprintf(file, "Epoch Length: %s\n", input_dataraw.combo_text6);
		fprintf(file, "Files Selected: %s\n", input_dataraw.entry_text1);
		fprintf(file, "Start Date: %s\n", input_dataraw.entry_text2);
		fprintf(file, "Start Time: %s\n", input_dataraw.entry_text3);
		fprintf(file, "Sample Rate: %.2f\n", input_dataraw.spin_value1);
		fprintf(file, "Resample Rate: %.2f\n", input_dataraw.spin_value2);
		fprintf(file, "Data Start Row: %.2f\n", input_dataraw.spin_value3);
		fprintf(file, "X-Axis Column: %.2f\n", input_dataraw.spin_value4);
		fprintf(file, "Y-Axis Column: %.2f\n", input_dataraw.spin_value5);
		fprintf(file, "Z-Axis Column: %.2f\n", input_dataraw.spin_value6);
		fprintf(file, "VM Column: %.2f\n", input_dataraw.spin_value7);
		fprintf(file, "Timestamp Column: %.2f\n", input_dataraw.spin_value8);
		fprintf(file, "Date Row: %.2f\n", input_dataraw.spin_value9);
		fprintf(file, "Time Row: %.2f\n", input_dataraw.spin_value10);
		fprintf(file, "Resample: %s\n", input_dataraw.toggle_value1 ? "True" : "False");
		fprintf(file, "Calibration: %s\n", input_dataraw.toggle_value2 ? "True" : "False");
		fprintf(file, "VM Data Only: %s\n", input_dataraw.toggle_value3 ? "True" : "False");
		fprintf(file, "SVM: %s\n", input_dataraw.toggle_value4 ? "True" : "False");
		fprintf(file, "SVMgs: %s\n", input_dataraw.toggle_value5 ? "True" : "False");
		fprintf(file, "ENMO: %s\n", input_dataraw.toggle_value6 ? "True" : "False");
		fprintf(file, "LFENMO: %s\n", input_dataraw.toggle_value7 ? "True" : "False");
		fprintf(file, "BFEN: %s\n", input_dataraw.toggle_value8 ? "True" : "False");
		fprintf(file, "HFEN: %s\n", input_dataraw.toggle_value9 ? "True" : "False");
		fprintf(file, "HFEN+: %s\n", input_dataraw.toggle_value10 ? "True" : "False");
		fprintf(file, "MAD: %s\n", input_dataraw.toggle_value11 ? "True" : "False");
		fprintf(file, "MIMS: %s\n", input_dataraw.toggle_value12 ? "True" : "False");
		fprintf(file, "COUNTS: %s\n", input_dataraw.toggle_value13 ? "True" : "False");
		fprintf(file, "COUNTS LF: %s\n", input_dataraw.toggle_value14 ? "True" : "False");
		fprintf(file, "SED SPHERE: %s\n", input_dataraw.toggle_value15 ? "True" : "False");
		fprintf(file, "Waist*: %s\n", input_dataraw.toggle_value16 ? "True" : "False");
		fprintf(file, "Waist: %s\n", input_dataraw.toggle_value17 ? "True" : "False");
		fprintf(file, "Wrist: %s\n", input_dataraw.toggle_value18 ? "True" : "False");
		fprintf(file, "CSV Output: %s\n", input_dataraw.toggle_value19 ? "True" : "False");
		fprintf(file, "TAB Output: %s\n", input_dataraw.toggle_value20 ? "True" : "False");
		fprintf(file, "TXT Output: %s\n", input_dataraw.toggle_value21 ? "True" : "False");
		fprintf(file, "XLSX Output: %s\n", input_dataraw.toggle_value22 ? "True" : "False");
		fprintf(file, "In Column: %s\n", input_dataraw.radio_value1 ? "True" : "False");
		fprintf(file, "In Header: %s\n", input_dataraw.radio_value2 ? "True" : "False");
		fprintf(file, "User Input: %s\n", input_dataraw.radio_value3 ? "True" : "False");
		fprintf(file, "None: %s\n", input_dataraw.radio_value4 ? "True" : "False");
		fprintf(file, "Retain Yes: %s\n", input_dataraw.radio_value5 ? "True" : "False");
		fprintf(file, "Retain No: %s\n", input_dataraw.radio_value6 ? "True" : "False");
		fprintf(file, "Multi Yes: %s\n", input_dataraw.radio_value7 ? "True" : "False");
		fprintf(file, "Multi No: %s\n", input_dataraw.radio_value8 ? "True" : "False");
		fprintf(file, "File Chooser Path: %s\n", input_dataraw.file_chooser_path);
		fprintf(file, "------------------------\n");

		// Close the file
		fclose(file);
	}
	else {
		g_print("Error: Unable to open the file for writing.\n");
	}
	// Free allocated memory
	g_free(input_dataraw.combo_text1);
	g_free(input_dataraw.combo_text2);
	g_free(input_dataraw.combo_text3);
	g_free(input_dataraw.combo_text4);
	g_free(input_dataraw.combo_text5);
	g_free(input_dataraw.combo_text6);
	g_free((char*)input_dataraw.entry_text1);
	g_free((char*)input_dataraw.entry_text2);
	g_free((char*)input_dataraw.entry_text3);
	g_free(input_dataraw.file_chooser_path);

	// Function to replace back-slashes with forward-slashes
	void replaceBackslashes(char* str) {
		while (*str) {
			if (*str == '\\') {
				*str = '/';
			}
			str++;
		}
	}
	// Task 1: Detect current working directory
	char Astring[256];
	if (getcwd(Astring, sizeof(Astring)) == NULL) {
		perror("getcwd() error");
		return;
	}

	// Task 1B: Replace back-slashes with forward-slashes in Astring
	replaceBackslashes(Astring);

	// Task 2: Declare second string
	char Bstring[] = "/R/R-4.3.3/bin/Rscript.exe ";

	// Task 3: Declare third string
	char Cstring[] = "/commands/raw_r/raw_script.R";

	// Task 4: Concatenate strings
	char finalString[512];
	snprintf(finalString, sizeof(finalString), "%s%s%s%s", Astring, Bstring, Astring, Cstring);

	// Task 5: Execute system call
	char systemCommand[512];
	snprintf(systemCommand, sizeof(systemCommand), "\"%s\"\n", finalString);
	system(systemCommand);

	// Function to check if a file exists
	const gchar* filename = "errors/raw/errors.txt";
	gboolean file_exists(const gchar * filename) {
		FILE* errfile = fopen(filename, "r");
		if (errfile) {
			fclose(errfile);
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

if (file_exists(filename)) {
	// File exists, read its contents
	GError* error = NULL;
	gchar* contents = NULL;
	// Dialog #2 - Processing Completed with Errors
	rawdialog2 = GTK_WIDGET(gtk_builder_get_object(builder, "rawdialog2"));
	GtkTextView* rddentry2 = GTK_TEXT_VIEW(rddentry1);

	if (g_file_get_contents(filename, &contents, NULL, &error)) {
		// Display the contents in the GtkTextView
		GtkTextBuffer* bufferrdd = gtk_text_view_get_buffer(rddentry2);
		gtk_text_buffer_set_text(bufferrdd, contents, -1);

		// Free allocated memory for contents
		g_free(contents);
	}
	else {
		// Error handling if reading fails
		g_printerr("Error reading file: %s\n", error->message);
		g_error_free(error);
	}
	gtk_widget_show(rawdialog2);
}
else {
	// Dialog #1 - Processing Complete
	rawdialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "rawdialog1"));
	gtk_widget_show(rawdialog1);
}
}



///////////////////////////////////////////////////////////////////////
// File Chooser 2 Callbacks
///////////////////////////////////////////////////////////////////////

void	on_fc2button1_clicked(GtkButton* b) {
	GSList* files, * temp;
	gchar* file_names = NULL;
	files = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(filechooser2));
	temp = files;
	while (temp != NULL) {
		gchar* file_path = g_shell_quote(temp->data);
		file_names = g_strdup_printf("%s \"%s\"", file_names ? file_names : "", file_path);
		g_free(file_path);
		temp = g_slist_next(temp);
	}
	g_slist_free(files);
	gtk_entry_set_text(GTK_ENTRY(rdentry1), file_names);
	gtk_widget_hide(filechooser2);
}

void	on_fc2button2_clicked(GtkButton* b) {
	gtk_entry_set_text(GTK_ENTRY(rdentry1), "");
	gtk_widget_hide(filechooser2);
}

///////////////////////////////////////////////////////////////////////
// Main Window Callbacks - Epoch Data Processing
///////////////////////////////////////////////////////////////////////

void	on_edbutton1_clicked(GtkButton* b) {
	gtk_widget_show(filechooser3);
}

void	on_edbutton2_clicked(GtkButton* b) {
	calwindow3 = GTK_WIDGET(gtk_builder_get_object(builder, "calwindow3"));
	calendar3 = GTK_CALENDAR(gtk_builder_get_object(builder, "calendar3"));
	gtk_widget_show(calwindow3);
}

void on_edradio1_toggled(GtkRadioButton* b) {
	gboolean T1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T1)
	{
		gtk_widget_set_sensitive(edspin2, TRUE);
		gtk_widget_set_sensitive(edcombo2, TRUE);
		gtk_widget_set_sensitive(edspin3, FALSE);
		gtk_widget_set_sensitive(edcombo3, FALSE);
		gtk_widget_set_sensitive(edspin4, FALSE);
		gtk_widget_set_sensitive(edcombo4, FALSE);
		gtk_widget_set_sensitive(edentry2, TRUE);
		gtk_widget_set_sensitive(edentry3, TRUE);
		gtk_widget_set_sensitive(edbutton2, TRUE);
	}
}

void on_edradio2_toggled(GtkRadioButton* b) {
	gboolean T1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T1)
	{
		gtk_widget_set_sensitive(edspin2, FALSE);
		gtk_widget_set_sensitive(edcombo2, FALSE);
		gtk_widget_set_sensitive(edspin3, TRUE);
		gtk_widget_set_sensitive(edcombo3, TRUE);
		gtk_widget_set_sensitive(edspin4, TRUE);
		gtk_widget_set_sensitive(edcombo4, TRUE);
		gtk_widget_set_sensitive(edentry2, FALSE);
		gtk_widget_set_sensitive(edentry3, FALSE);
		gtk_widget_set_sensitive(edbutton2, FALSE);
	}
}

void on_edradio3_toggled(GtkRadioButton* b) {
	gboolean T1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T1)
	{
		gtk_widget_set_sensitive(edspin2, FALSE);
		gtk_widget_set_sensitive(edcombo2, FALSE);
		gtk_widget_set_sensitive(edspin3, FALSE);
		gtk_widget_set_sensitive(edcombo3, FALSE);
		gtk_widget_set_sensitive(edspin4, FALSE);
		gtk_widget_set_sensitive(edcombo4, FALSE);
		gtk_widget_set_sensitive(edentry2, TRUE);
		gtk_widget_set_sensitive(edentry3, TRUE);
		gtk_widget_set_sensitive(edbutton2, TRUE);
	}
}

void on_edradio4_toggled(GtkRadioButton* b) {
	gboolean T1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T1)
	{
		gtk_widget_set_sensitive(edspin2, FALSE);
		gtk_widget_set_sensitive(edcombo2, FALSE);
		gtk_widget_set_sensitive(edspin3, FALSE);
		gtk_widget_set_sensitive(edcombo3, FALSE);
		gtk_widget_set_sensitive(edspin4, FALSE);
		gtk_widget_set_sensitive(edcombo4, FALSE);
		gtk_widget_set_sensitive(edentry2, FALSE);
		gtk_widget_set_sensitive(edentry3, FALSE);
		gtk_widget_set_sensitive(edbutton2, FALSE);
	}
}

void	on_edcheck1_toggled(GtkCheckButton* b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T)
	{
		gtk_widget_set_sensitive(edcombo7, TRUE);
	}
	else
	{
		gtk_widget_set_sensitive(edcombo7, FALSE);
	}
}

void	on_edcheck2_toggled(GtkCheckButton* b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T)
	{
		gtk_widget_set_sensitive(edcombo8, TRUE);
		gtk_widget_set_sensitive(edcombo9, TRUE);
	}
	else
	{
		gtk_widget_set_sensitive(edcombo8, FALSE);
		gtk_widget_set_sensitive(edcombo9, FALSE);
	}
}

void on_edcombo5_changed(GtkComboBoxText *b){
	gchar* selected_item = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo5));

	GtkComboBoxText* edcombo10f = GTK_COMBO_BOX_TEXT(edcombo10);
	gtk_combo_box_text_remove_all(edcombo10f);

	if (selected_item == NULL) {
		g_print("Select A Variable.\n");
	}
	else {
		gtk_combo_box_text_remove_all(edcombo10f);
		if (g_strcmp0(selected_item, "None") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "No Variable Selected");
		}
		else if (g_strcmp0(selected_item, "Custom") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "STEPS") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "Tudor-Locke (2011) - 60s");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "SED SPHERE") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "SED SPHERE");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "COUNTS") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "Freedson (1998) - 60s");
			gtk_combo_box_text_append_text(edcombo10f, "Troiano (2008) - 60s");
			gtk_combo_box_text_append_text(edcombo10f, "Treuth (2004) - 60s");
			gtk_combo_box_text_append_text(edcombo10f, "Evenson (2008) - 15s");
			gtk_combo_box_text_append_text(edcombo10f, "Mattocks (2005) - 60s");
			gtk_combo_box_text_append_text(edcombo10f, "Pate (2006) - 15s");
			gtk_combo_box_text_append_text(edcombo10f, "Freedson (2011) VM - 15s");
			gtk_combo_box_text_append_text(edcombo10f, "Romanzini (2014) VM - 15s");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "COUNTS LF") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "Freedson (1998) - 60s");
			gtk_combo_box_text_append_text(edcombo10f, "Troiano (2008) - 60s");
			gtk_combo_box_text_append_text(edcombo10f, "Treuth (2004) - 60s");
			gtk_combo_box_text_append_text(edcombo10f, "Evenson (2008) - 15s");
			gtk_combo_box_text_append_text(edcombo10f, "Mattocks (2005) - 60s");
			gtk_combo_box_text_append_text(edcombo10f, "Pate (2006) - 15s");
			gtk_combo_box_text_append_text(edcombo10f, "Freedson (2011) VM - 15s");
			gtk_combo_box_text_append_text(edcombo10f, "Romanzini (2014) VM - 15s");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "MIMS") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "MIMS");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "MAD") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "Vaha-Ypya (2015) - 5s");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "HFEN+") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "HFEN+");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "HFEN") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "HFEN");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "BFEN") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "BFEN");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "LFENMO") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "LFENMO");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "ENMO") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "Hildebrand (2014) - 5s");
			gtk_combo_box_text_append_text(edcombo10f, "Schaefer (2014) - 5s");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "SVMgs") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "SVMgs");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		else if (g_strcmp0(selected_item, "SVM") == 0) {
			gtk_combo_box_text_append_text(edcombo10f, "Phillips (2013) - 5s");
			gtk_combo_box_text_append_text(edcombo10f, "Custom");
		}
		g_free((gchar*)selected_item);
	}
}

void on_edcombo6_changed(GtkComboBoxText* b) {
	gchar* selected_item = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo6));

	GtkComboBoxText* edcombo11f = GTK_COMBO_BOX_TEXT(edcombo11);
	gtk_combo_box_text_remove_all(edcombo11f);

	if (selected_item == NULL) {
		g_print("Select A Variable.\n");
	}
	else {
		gtk_combo_box_text_remove_all(edcombo11f);
		if (g_strcmp0(selected_item, "None") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "No Variable Selected");
		}
		else if (g_strcmp0(selected_item, "Custom") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "STEPS") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "Tudor-Locke (2011) - 60s");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "SED SPHERE") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "SED SPHERE");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "COUNTS") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "Freedson (1998) - 60s");
			gtk_combo_box_text_append_text(edcombo11f, "Troiano (2008) - 60s");
			gtk_combo_box_text_append_text(edcombo11f, "Treuth (2004) - 60s");
			gtk_combo_box_text_append_text(edcombo11f, "Evenson (2008) - 15s");
			gtk_combo_box_text_append_text(edcombo11f, "Mattocks (2005) - 60s");
			gtk_combo_box_text_append_text(edcombo11f, "Pate (2006) - 15s");
			gtk_combo_box_text_append_text(edcombo11f, "Freedson (2011) VM - 60s");
			gtk_combo_box_text_append_text(edcombo11f, "Romanzini (2014) VM - 15s");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "COUNTS LF") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "Freedson (1998) - 60s");
			gtk_combo_box_text_append_text(edcombo11f, "Troiano (2008) - 60s");
			gtk_combo_box_text_append_text(edcombo11f, "Treuth (2004) - 60s");
			gtk_combo_box_text_append_text(edcombo11f, "Evenson (2008) - 15s");
			gtk_combo_box_text_append_text(edcombo11f, "Mattocks (2005) - 60s");
			gtk_combo_box_text_append_text(edcombo11f, "Pate (2006) - 15s");
			gtk_combo_box_text_append_text(edcombo11f, "Freedson (2011) VM - 60s");
			gtk_combo_box_text_append_text(edcombo11f, "Romanzini (2014) VM - 15s");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "MIMS") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "MIMS");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "MAD") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "Vaha-Ypya (2015) - 5s");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "HFEN+") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "HFEN+");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "HFEN") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "HFEN");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "BFEN") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "BFEN");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "LFENMO") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "LFENMO");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "ENMO") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "Hildebrand (2014) - 5s");
			gtk_combo_box_text_append_text(edcombo11f, "Schaefer (2014) - 5s");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "SVMgs") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "SVMgs");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		else if (g_strcmp0(selected_item, "SVM") == 0) {
			gtk_combo_box_text_append_text(edcombo11f, "Phillips (2013) - 5s");
			gtk_combo_box_text_append_text(edcombo11f, "Custom");
		}
		g_free((gchar*)selected_item);
	}
}

void	on_edcombo10_changed(GtkComboBoxText* b) {
	gchar* selected_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo10));

	GtkTextView* edentry4f = GTK_TEXT_VIEW(edentry4);
	GtkTextView* edentry6f = GTK_TEXT_VIEW(edentry6);

	GtkTextBuffer* buffer4 = gtk_text_view_get_buffer(edentry4f);
	GtkTextBuffer* buffer6 = gtk_text_view_get_buffer(edentry6f);

	if (selected_text != NULL) {
		if (g_strcmp0(selected_text, "No Variable Selected") == 0) {
			gtk_text_buffer_set_text(buffer4, "N/A", -1);
			gtk_text_buffer_set_text(buffer6, "N/A", -1);
		}
		else if (g_strcmp0(selected_text, "Custom") == 0) {
			gtk_text_buffer_set_text(buffer4, "Input Labels", -1);
			gtk_text_buffer_set_text(buffer6, "Input Cut-Points", -1);
		}
		else if (g_strcmp0(selected_text, "Freedson (1998) - 60s") == 0) {
			gtk_text_buffer_set_text(buffer4, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0-99, 100-1951, 1952-5724, 5725+, 1952+", -1);
		}
		else if (g_strcmp0(selected_text, "Troiano (2008) - 60s") == 0) {
			gtk_text_buffer_set_text(buffer4, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0-99, 100-2019, 2020-5998, 5999+, 2020+", -1);
		}
		else if (g_strcmp0(selected_text, "Treuth (2004) - 60s") == 0) {
			gtk_text_buffer_set_text(buffer4, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0-99, 100-2999, 3000-5200, 5201+, 3000+", -1);
		}
		else if (g_strcmp0(selected_text, "Evenson (2008) - 15s") == 0) {
			gtk_text_buffer_set_text(buffer4, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0-25, 26-573, 574-1002, 1003+, 574+", -1);
		}
		else if (g_strcmp0(selected_text, "Mattocks (2005) - 60s") == 0) {
			gtk_text_buffer_set_text(buffer4, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0-100, 101-3580, 3581-6129, 6130+, 3581+", -1);
		}
		else if (g_strcmp0(selected_text, "Pate (2006) - 15s") == 0) {
			gtk_text_buffer_set_text(buffer4, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0-37, 38-419, 420-841, 842+, 420+", -1);
		}
		else if (g_strcmp0(selected_text, "Freedson (2011) VM - 60s") == 0) {
			gtk_text_buffer_set_text(buffer4, "LPA, MPA, VPA, VVPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0-2690, 2691-6166, 6167-9642, 9643+, 2691+", -1);
		}
		else if (g_strcmp0(selected_text, "Romanzini (2014) VM - 15s") == 0) {
			gtk_text_buffer_set_text(buffer4, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0-179, 180-756, 757-1111, 1112+, 757+", -1);
		}
		else if (g_strcmp0(selected_text, "Tudor-Locke (2011) - 60s") == 0) {
			gtk_text_buffer_set_text(buffer4, "NM, IM, SM, PS, SW, MW, BW, FM, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0, 1-19, 20-39, 40-59, 60-79, 80-99, 100-119, 120+, 100+", -1);
		}
		else if (g_strcmp0(selected_text, "Phillips (2013) - 5s") == 0) {
			gtk_text_buffer_set_text(buffer4, "!MVPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0-274 mg, 275-750 mg, 751+ mg, 275+ mg", -1);
		}
		else if (g_strcmp0(selected_text, "Hildebrand (2014) - 5s") == 0) {
			gtk_text_buffer_set_text(buffer4, "!MVPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0-191 mg, 192-695 mg, 696+ mg, 192+ mg", -1);
		}
		else if (g_strcmp0(selected_text, "Schaefer (2014) - 5s") == 0) {
			gtk_text_buffer_set_text(buffer4, "!MVPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0-313 mg, 314-998 mg, 999+ mg, 314+ mg", -1);
		}
		else if (g_strcmp0(selected_text, "Vaha-Ypya (2015) - 5s") == 0) {
			gtk_text_buffer_set_text(buffer4, "!MVPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer6, "0-90 mg, 91-413 mg, 414+ mg, 91+ mg", -1);
		}
		else {
			// Handle other options or no selection
			gtk_text_buffer_set_text(buffer4, "N/A", -1);
			gtk_text_buffer_set_text(buffer6, "N/A", -1);
		}
		g_free(selected_text);
	}
}

void	on_edcombo11_changed(GtkComboBoxText* b) {
	gchar* selected_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo11));

	GtkTextView* edentry5f = GTK_TEXT_VIEW(edentry5);
	GtkTextView* edentry7f = GTK_TEXT_VIEW(edentry7);

	GtkTextBuffer* buffer5 = gtk_text_view_get_buffer(edentry5f);
	GtkTextBuffer* buffer7 = gtk_text_view_get_buffer(edentry7f);

	if (selected_text != NULL) {
		if (g_strcmp0(selected_text, "No Variable Selected") == 0) {
			gtk_text_buffer_set_text(buffer5, "N/A", -1);
			gtk_text_buffer_set_text(buffer7, "N/A", -1);
		}
		else if (g_strcmp0(selected_text, "Custom") == 0) {
			gtk_text_buffer_set_text(buffer5, "Input Labels", -1);
			gtk_text_buffer_set_text(buffer7, "Input Cut-Points", -1);
		}
		else if (g_strcmp0(selected_text, "Freedson (1998) - 60s") == 0) {
			gtk_text_buffer_set_text(buffer5, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0-99, 100-1951, 1952-5724, 5725+, 1952+", -1);
		}
		else if (g_strcmp0(selected_text, "Troiano (2008) - 60s") == 0) {
			gtk_text_buffer_set_text(buffer5, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0-99, 100-2019, 2020-5998, 5999+, 2020+", -1);
		}
		else if (g_strcmp0(selected_text, "Treuth (2004) - 60s") == 0) {
			gtk_text_buffer_set_text(buffer5, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0-99, 100-2999, 3000-5200, 5201+, 3000+", -1);
		}
		else if (g_strcmp0(selected_text, "Evenson (2008) - 15s") == 0) {
			gtk_text_buffer_set_text(buffer5, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0-25, 26-573, 574-1002, 1003+, 574+", -1);
		}
		else if (g_strcmp0(selected_text, "Mattocks (2005) - 60s") == 0) {
			gtk_text_buffer_set_text(buffer5, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0-100, 101-3580, 3581-6129, 6130+, 3581+", -1);
		}
		else if (g_strcmp0(selected_text, "Pate (2006) - 15s") == 0) {
			gtk_text_buffer_set_text(buffer5, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0-37, 38-419, 420-841, 842+, 420+", -1);
		}
		else if (g_strcmp0(selected_text, "Freedson (2011) VM - 60s") == 0) {
			gtk_text_buffer_set_text(buffer5, "LPA, MPA, VPA, VVPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0-2690, 2691-6166, 6167-9642, 9643+, 2691+", -1);
		}
		else if (g_strcmp0(selected_text, "Romanzini (2014) VM - 15s") == 0) {
			gtk_text_buffer_set_text(buffer5, "SED, LPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0-179, 180-756, 757-1111, 1112+, 757+", -1);
		}
		else if (g_strcmp0(selected_text, "Tudor-Locke (2011) - 60s") == 0) {
			gtk_text_buffer_set_text(buffer5, "NM, IM, SM, PS, SW, MW, BW, FM, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0, 1-19, 20-39, 40-59, 60-79, 80-99, 100-119, 120+, 100+", -1);
		}
		else if (g_strcmp0(selected_text, "Phillips (2013) - 5s") == 0) {
			gtk_text_buffer_set_text(buffer5, "!MVPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0-274 mg, 275-750 mg, 751+ mg, 275+ mg", -1);
		}
		else if (g_strcmp0(selected_text, "Hildebrand (2014) - 5s") == 0) {
			gtk_text_buffer_set_text(buffer5, "!MVPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0-191 mg, 192-695 mg, 696+ mg, 192+ mg", -1);
		}
		else if (g_strcmp0(selected_text, "Schaefer (2014) - 5s") == 0) {
			gtk_text_buffer_set_text(buffer5, "!MVPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0-313 mg, 314-998 mg, 999+ mg, 314+ mg", -1);
		}
		else if (g_strcmp0(selected_text, "Vaha-Ypya (2015) - 5s") == 0) {
			gtk_text_buffer_set_text(buffer5, "!MVPA, MPA, VPA, MVPA", -1);
			gtk_text_buffer_set_text(buffer7, "0-90 mg, 91-413 mg, 414+ mg, 91+ mg", -1);
		}
		else {
			// Handle other options or no selection
			gtk_text_buffer_set_text(buffer5, "N/A", -1);
			gtk_text_buffer_set_text(buffer7, "N/A", -1);
		}
		g_free(selected_text);
	}
}

// Structure to store input data
typedef struct {
	gchar* combo_text1;
	gchar* combo_text2;
	gchar* combo_text3;
	gchar* combo_text4;
	gchar* combo_text5;
	gchar* combo_text6;
	gchar* combo_text7;
	gchar* combo_text8;
	gchar* combo_text9;
	gchar* combo_text10;
	gchar* combo_text11;
	const gchar* entry_text1;
	const gchar* entry_text2;
	const gchar* entry_text3;
	gchar* entry_text4;
	gchar* entry_text5;
	gchar* entry_text6;
	gchar* entry_text7;
	gdouble spin_value1;
	gdouble spin_value2;
	gdouble spin_value3;
	gdouble spin_value4;
	gdouble spin_value5;
	gdouble spin_value6;
	gdouble spin_value7;
	gdouble spin_value8;
	gdouble spin_value9;
	gboolean toggle_value1;
	gboolean toggle_value2;
	gboolean toggle_value3;
	gboolean toggle_value4;
	gboolean toggle_value5;
	gboolean toggle_value6;
	gboolean toggle_value7;
	gboolean toggle_value8;
	gboolean radio_value1;
	gboolean radio_value2;
	gboolean radio_value3;
	gboolean radio_value4;
	gboolean radio_value5;
	gboolean radio_value6;
	gchar* file_chooser_path;
} InputDataEpoch;

// Callback function to handle button click and write inputs to a text file
void on_edbutton3_clicked(GtkButton* b) {
	// Retrieve data from widgets
	InputDataEpoch input_dataepoch;

	// Retrieve data from GtkComboBoxText objects
	input_dataepoch.combo_text1 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo1));
	input_dataepoch.combo_text2 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo2));
	input_dataepoch.combo_text3 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo3));
	input_dataepoch.combo_text4 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo4));
	input_dataepoch.combo_text5 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo5));
	input_dataepoch.combo_text6 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo6));
	input_dataepoch.combo_text7 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo7));
	input_dataepoch.combo_text8 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo8));
	input_dataepoch.combo_text9 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo9));
	input_dataepoch.combo_text10 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo10));
	input_dataepoch.combo_text11 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(edcombo11));

	// Retrieve data from GtkEntry objects
	input_dataepoch.entry_text1 = gtk_entry_get_text(GTK_ENTRY(edentry1));
	input_dataepoch.entry_text2 = gtk_entry_get_text(GTK_ENTRY(edentry2));
	input_dataepoch.entry_text3 = gtk_entry_get_text(GTK_ENTRY(edentry3));

	// Retrieve data from GtkTextView objects
				// Get the buffer from the text view
				GtkTextBuffer *buffer4 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(edentry4));
				GtkTextBuffer *buffer5 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(edentry5));
				GtkTextBuffer *buffer6 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(edentry6));
				GtkTextBuffer *buffer7 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(edentry7));

				// Get the start and end iterators of the buffer
				GtkTextIter start4, end4;
				gtk_text_buffer_get_start_iter(buffer4, &start4);
				gtk_text_buffer_get_end_iter(buffer4, &end4);

				// Get the text from the buffer
				input_dataepoch.entry_text4 = gtk_text_buffer_get_text(buffer4, &start4, &end4, FALSE);

				// Get the start and end iterators of the buffer
				GtkTextIter start5, end5;
				gtk_text_buffer_get_start_iter(buffer5, &start5);
				gtk_text_buffer_get_end_iter(buffer5, &end5);

				// Get the text from the buffer
				input_dataepoch.entry_text5 = gtk_text_buffer_get_text(buffer5, &start5, &end5, FALSE);

				// Get the start and end iterators of the buffer
				GtkTextIter start6, end6;
				gtk_text_buffer_get_start_iter(buffer6, &start6);
				gtk_text_buffer_get_end_iter(buffer6, &end6);

				// Get the text from the buffer
				input_dataepoch.entry_text6 = gtk_text_buffer_get_text(buffer6, &start6, &end6, FALSE);

				// Get the start and end iterators of the buffer
				GtkTextIter start7, end7;
				gtk_text_buffer_get_start_iter(buffer7, &start7);
				gtk_text_buffer_get_end_iter(buffer7, &end7);

				// Get the text from the buffer
				input_dataepoch.entry_text7 = gtk_text_buffer_get_text(buffer7, &start7, &end7, FALSE);

	// Retrieve data from GtkSpinButton objects
	input_dataepoch.spin_value1 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(edspin1));
	input_dataepoch.spin_value2 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(edspin2));
	input_dataepoch.spin_value3 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(edspin3));
	input_dataepoch.spin_value4 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(edspin4));
	input_dataepoch.spin_value5 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(edspin5));
	input_dataepoch.spin_value6 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(edspin6));
	input_dataepoch.spin_value7 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(edspin7));
	input_dataepoch.spin_value8 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(edspin8));
	input_dataepoch.spin_value9 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(edspin9));

	// Retrieve data from GtkToggleButton objects
	input_dataepoch.toggle_value1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edcheck1));
	input_dataepoch.toggle_value2 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edcheck2));
	input_dataepoch.toggle_value3 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edcheck3));
	input_dataepoch.toggle_value4 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edcheck4));
	input_dataepoch.toggle_value5 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edcheck5));
	input_dataepoch.toggle_value6 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edcheck6));
	input_dataepoch.toggle_value7 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edcheck7));
	input_dataepoch.toggle_value8 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edcheck8));

	// Retrieve data from GtkRadioButton objects
	input_dataepoch.radio_value1 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edradio1));
	input_dataepoch.radio_value2 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edradio2));
	input_dataepoch.radio_value3 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edradio3));
	input_dataepoch.radio_value4 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edradio4));
	input_dataepoch.radio_value5 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edradio5));
	input_dataepoch.radio_value6 = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edradio6));

	// Retrieve data from GtkFileChooserButtons
	input_dataepoch.file_chooser_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(edfilechooserbutton));

	// Remove any existing file in the directory //
	FILE* filecheck = fopen("commands/epoch/epoch_output.txt", "r");
	if (filecheck != NULL) {
		fclose(filecheck);
		remove("commands/epoch/epoch_output.txt");
	}
	else {
		//file doesn't exists or cannot be opened (es. you don't have access permission)
	}

	// Open the file in append mode and write the inputs
	FILE* file = fopen("commands/epoch/epoch_output.txt", "a");
	if (file != NULL) {
		fprintf(file, "Epoch Input Seconds: %s\n", input_dataepoch.combo_text1);
		fprintf(file, "Timestamp Form: %s\n", input_dataepoch.combo_text2);
		fprintf(file, "Date Form: %s\n", input_dataepoch.combo_text3);
		fprintf(file, "Time Form: %s\n", input_dataepoch.combo_text4);
		fprintf(file, "Variable One: %s\n", input_dataepoch.combo_text5);
		fprintf(file, "Variable Two: %s\n", input_dataepoch.combo_text6);
		fprintf(file, "Epoch Output Seconds: %s\n", input_dataepoch.combo_text7);
		fprintf(file, "Sleep-Wake-Wear Algorithm: %s\n", input_dataepoch.combo_text8);
		fprintf(file, "Wear Algorithm: %s\n", input_dataepoch.combo_text9);
		fprintf(file, "V1 Cutpoint Set: %s\n", input_dataepoch.combo_text10);
		fprintf(file, "V2 Cutpoint Set: %s\n", input_dataepoch.combo_text11);
		fprintf(file, "Files Selected: %s\n", input_dataepoch.entry_text1);
		fprintf(file, "Start Date: %s\n", input_dataepoch.entry_text2);
		fprintf(file, "Start Time: %s\n", input_dataepoch.entry_text3);
		fprintf(file, "V1 Labels: %s\n", input_dataepoch.entry_text4);
		fprintf(file, "V2 Labels: %s\n", input_dataepoch.entry_text5);
		fprintf(file, "V1 Cutpoint Values: %s\n", input_dataepoch.entry_text6);
		fprintf(file, "V2 Cutpoint Values: %s\n", input_dataepoch.entry_text7);
		fprintf(file, "Data Start Row: %.2f\n", input_dataepoch.spin_value1);
		fprintf(file, "Timestamp Column: %.2f\n", input_dataepoch.spin_value2);
		fprintf(file, "Date Row: %.2f\n", input_dataepoch.spin_value3);
		fprintf(file, "Time Row: %.2f\n", input_dataepoch.spin_value4);
		fprintf(file, "V1 Column: %.2f\n", input_dataepoch.spin_value5);
		fprintf(file, "V2 Column: %.2f\n", input_dataepoch.spin_value6);
		fprintf(file, "Min Non-Missing Minutes: %.2f\n", input_dataepoch.spin_value7);
		fprintf(file, "Min Wear Minutes: %.2f\n", input_dataepoch.spin_value8);
		fprintf(file, "Min Valid Days: %.2f\n", input_dataepoch.spin_value9);
		fprintf(file, "Integrate: %s\n", input_dataepoch.toggle_value1 ? "True" : "False");
		fprintf(file, "Wear Mark: %s\n", input_dataepoch.toggle_value2 ? "True" : "False");
		fprintf(file, "Daily Summary: %s\n", input_dataepoch.toggle_value3 ? "True" : "False");
		fprintf(file, "Total Summary: %s\n", input_dataepoch.toggle_value4 ? "True" : "False");
		fprintf(file, "CSV Output: %s\n", input_dataepoch.toggle_value5 ? "True" : "False");
		fprintf(file, "TAB Output: %s\n", input_dataepoch.toggle_value6 ? "True" : "False");
		fprintf(file, "TXT Output: %s\n", input_dataepoch.toggle_value7 ? "True" : "False");
		fprintf(file, "XLSX Output: %s\n", input_dataepoch.toggle_value8 ? "True" : "False");
		fprintf(file, "In Column: %s\n", input_dataepoch.radio_value1 ? "True" : "False");
		fprintf(file, "In Header: %s\n", input_dataepoch.radio_value2 ? "True" : "False");
		fprintf(file, "User Input: %s\n", input_dataepoch.radio_value3 ? "True" : "False");
		fprintf(file, "None: %s\n", input_dataepoch.radio_value4 ? "True" : "False");
		fprintf(file, "Multi Yes: %s\n", input_dataepoch.radio_value5 ? "True" : "False");
		fprintf(file, "Multi No: %s\n", input_dataepoch.radio_value6 ? "True" : "False");
		fprintf(file, "File Chooser Path: %s\n", input_dataepoch.file_chooser_path);
		fprintf(file, "------------------------\n");

		// Close the file
		fclose(file);
	}
	else {
		g_print("Error: Unable to open the file for writing.\n");
	}
	// Free allocated memory
	g_free(input_dataepoch.combo_text1);
	g_free(input_dataepoch.combo_text2);
	g_free(input_dataepoch.combo_text3);
	g_free(input_dataepoch.combo_text4);
	g_free(input_dataepoch.combo_text5);
	g_free(input_dataepoch.combo_text6);
	g_free(input_dataepoch.combo_text7);
	g_free(input_dataepoch.combo_text8);
	g_free(input_dataepoch.combo_text9);
	g_free(input_dataepoch.combo_text10);
	g_free(input_dataepoch.combo_text11);
	g_free((char*)input_dataepoch.entry_text1);
	g_free((char*)input_dataepoch.entry_text2);
	g_free((char*)input_dataepoch.entry_text3);
	g_free(input_dataepoch.entry_text4);
	g_free(input_dataepoch.entry_text5);
	g_free(input_dataepoch.entry_text6);
	g_free(input_dataepoch.entry_text7);
	g_free(input_dataepoch.file_chooser_path);

	// Function to replace back-slashes with forward-slashes
	void replaceBackslashes(char* str) {
		while (*str) {
			if (*str == '\\') {
				*str = '/';
			}
			str++;
		}
	}
	// Task 1: Detect current working directory
	char Astring[256];
	if (getcwd(Astring, sizeof(Astring)) == NULL) {
		perror("getcwd() error");
		return;
	}

	// Task 1B: Replace back-slashes with forward-slashes in Astring
	replaceBackslashes(Astring);

	// Task 2: Declare second string
	char Bstring[] = "/R/R-4.3.3/bin/Rscript.exe ";

	// Task 3: Declare third string
	char Cstring[] = "/commands/epoch_r/epoch_script.R";

	// Task 4: Concatenate strings
	char finalString[512];
	snprintf(finalString, sizeof(finalString), "%s%s%s%s", Astring, Bstring, Astring, Cstring);

	// Task 5: Execute system call
	char systemCommand[512];
	snprintf(systemCommand, sizeof(systemCommand), "\"%s\"\n", finalString);
	system(systemCommand);

	// Function to check if a file exists
	const gchar* filename = "errors/epoch/errors.txt";
	gboolean file_exists(const gchar * filename) {
		FILE* errfile = fopen(filename, "r");
		if (errfile) {
			fclose(errfile);
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

	if (file_exists(filename)) {
		// File exists, read its contents
		GError* error = NULL;
		gchar* contents = NULL;
		// Dialog #2 - Processing Completed with Errors
		epochdialog2 = GTK_WIDGET(gtk_builder_get_object(builder, "epochdialog2"));
		GtkTextView* eddentry2 = GTK_TEXT_VIEW(eddentry1);

		if (g_file_get_contents(filename, &contents, NULL, &error)) {
			// Display the contents in the GtkTextView
			GtkTextBuffer* bufferedd = gtk_text_view_get_buffer(eddentry2);
			gtk_text_buffer_set_text(bufferedd, contents, -1);

			// Free allocated memory for contents
			g_free(contents);
		}
		else {
			// Error handling if reading fails
			g_printerr("Error reading file: %s\n", error->message);
			g_error_free(error);
		}
		gtk_widget_show(epochdialog2);
	}
	else {
		// Dialog #1 - Processing Complete
		epochdialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "epochdialog1"));
		gtk_widget_show(epochdialog1);
	}
}

///////////////////////////////////////////////////////////////////////
// File Chooser 3 Callbacks
///////////////////////////////////////////////////////////////////////

void	on_fc3button1_clicked(GtkButton* b) {
	GSList* files, * temp;
	gchar* file_names = NULL;
	files = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(filechooser3));
	temp = files;
	while (temp != NULL) {
		gchar* file_path = g_shell_quote(temp->data);
		file_names = g_strdup_printf("%s \"%s\"", file_names ? file_names : "", file_path);
		g_free(file_path);
		temp = g_slist_next(temp);
	}
	g_slist_free(files);
	gtk_entry_set_text(GTK_ENTRY(edentry1), file_names);
	gtk_widget_hide(filechooser3);
}

void	on_fc3button2_clicked(GtkButton* b) {
	gtk_entry_set_text(GTK_ENTRY(edentry1), "");
	gtk_widget_hide(filechooser3);
}

///////////////////////////////////////////////////////////////////////
// Main Window Callbacks - File Viewer
///////////////////////////////////////////////////////////////////////

// Structure to store input data
typedef struct {
	gchar* combo_text1;
	gchar* combo_text2;
	gchar* file_chooser_path;
} InputDataFv;

// Callback function to handle button click and write inputs to a text file
void on_fvbutton1_clicked(GtkButton* b) {
	// Retrieve data from widgets
	InputDataFv input_datafv;

	// Retrieve data from GtkComboBoxText objects
	input_datafv.combo_text1 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(fvcombo1));
	input_datafv.combo_text2 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(fvcombo2));

	// Retrieve data from GtkFileChooserButtons
	input_datafv.file_chooser_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fvfilechooserbutton));

	// Remove any existing file in the directory //
	FILE* filecheck = fopen("commands/fv/fv_output.txt", "r");
	if (filecheck != NULL) {
		fclose(filecheck);
		remove("commands/fv/fv_output.txt");
	}
	else {
		//file doesn't exists or cannot be opened (es. you don't have access permission)
	}

	// Open the file in append mode and write the inputs
	FILE* file = fopen("commands/fv/fv_output.txt", "a");
	if (file != NULL) {
		fprintf(file, "Starting Row: %s\n", input_datafv.combo_text1);
		fprintf(file, "Ending Row: %s\n", input_datafv.combo_text2);
		fprintf(file, "File Chooser Path: %s\n", input_datafv.file_chooser_path);
		fprintf(file, "------------------------\n");

		// Close the file
		fclose(file);
	}
	else {
		g_print("Error: Unable to open the file for writing.\n");
	}
	// Free allocated memory
	g_free(input_datafv.combo_text1);
	g_free(input_datafv.combo_text2);
	g_free(input_datafv.file_chooser_path);

	// Function to replace back-slashes with forward-slashes
	void replaceBackslashes(char* str) {
		while (*str) {
			if (*str == '\\') {
				*str = '/';
			}
			str++;
		}
	}
	// Task 1: Detect current working directory
	char Astring[256];
	if (getcwd(Astring, sizeof(Astring)) == NULL) {
		perror("getcwd() error");
		return;
	}

	// Task 1B: Replace back-slashes with forward-slashes in Astring
	replaceBackslashes(Astring);

	// Task 2: Declare second string
	char Bstring[] = "/R/R-4.3.3/bin/Rscript.exe ";

	// Task 3: Declare third string
	char Cstring[] = "/commands/fv_r/fv_script.R";

	// Task 4: Concatenate strings
	char finalString[512];
	snprintf(finalString, sizeof(finalString), "%s%s%s%s", Astring, Bstring, Astring, Cstring);

	// Task 5: Execute system call
	char systemCommand[512];
	snprintf(systemCommand, sizeof(systemCommand), "\"%s\"\n", finalString);
	system(systemCommand);

	// Function to check if a file exists
	const gchar* filename = "errors/fv/errors.txt";
	gboolean file_exists(const gchar * filename) {
		FILE* errfile = fopen(filename, "r");
		if (errfile) {
			fclose(errfile);
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

	if (file_exists(filename)) {
		// File exists, read its contents
		GError* error = NULL;
		gchar* contents = NULL;
		// Dialog #2 - Processing Completed with Errors
		fvdialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "fvdialog1"));
		GtkTextView* fvdentry2 = GTK_TEXT_VIEW(fvdentry1);

		if (g_file_get_contents(filename, &contents, NULL, &error)) {
			// Display the contents in the GtkTextView
			GtkTextBuffer* bufferfvd = gtk_text_view_get_buffer(fvdentry2);
			gtk_text_buffer_set_text(bufferfvd, contents, -1);

			// Free allocated memory for contents
			g_free(contents);
		}
		else {
			// Error handling if reading fails
			g_printerr("Error reading file: %s\n", error->message);
			g_error_free(error);
		}
		gtk_widget_show(fvdialog1);
	}
	else {
		// Show Nothing
	}

	//Function to Grab Sample File Read-In & Display It Back to GUI ////
	const gchar* filename2 = "commands/fv_written/fvwri_output.txt";
	gboolean file_exists2(const gchar* filename2) {
		FILE* checkfile = fopen(filename2, "r");
		if (checkfile) {
			fclose(checkfile);
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

	if (file_exists2(filename2)) {
		// File exists, read its contents
		GError* errorsamp = NULL;
		gchar* contentssamp = NULL;
		// Initialize a mirrored object
		// Dialog #2 - Processing Completed with Errors
		fventry1 = GTK_WIDGET(gtk_builder_get_object(builder, "fventry1"));
		GtkTextView* fventry2 = GTK_TEXT_VIEW(fventry1);

		if (g_file_get_contents(filename2, &contentssamp, NULL, &errorsamp)) {
			// Display the contents in the GtkTextView
			GtkTextBuffer* bufferfvactual = gtk_text_view_get_buffer(fventry2);
			gtk_text_buffer_set_text(bufferfvactual, contentssamp, -1);

			// Free allocated memory for contents
			g_free(contentssamp);
		}
		else {
			// Error handling if reading fails
			g_printerr("Error reading file: %s\n", errorsamp->message);
			g_error_free(errorsamp);
		}
	}
	else {
		// Keep Processing
	}
}

///////////////////////////////////////////////////////////////////////
// Main Window Callbacks - Variable Definitions
///////////////////////////////////////////////////////////////////////

void	on_vdcombo1_changed(GtkComboBoxText* b) {
	// Get the selected text from the combo box
	gchar* selected_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(vdcombo1));

	// Get the GtkTextView widget from user_data
	GtkTextView* vdentryfinal = GTK_TEXT_VIEW(vdentry1);

	// Create a buffer to set the text in the TextView
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(vdentryfinal);

	if (selected_text != NULL) {
		if (g_strcmp0(selected_text, "Choose a variable...") == 0) {
			gtk_text_buffer_set_text(buffer, "Nothing Selected", -1);
		}
		else if (g_strcmp0(selected_text, "Signal Vector Magnitude (SVM)") == 0) {
			gtk_text_buffer_set_text(buffer, "Signal Vector Magnitude (SVM) is defined as the mean Euclidean Norm [sqrt(x^2 + y^2 + z^2)] in g-units. "
											 "Traditionally calculated over 5-second epochs, but can be quantified over any user-specified interval. "
											 "----------------------------------------------------------------------------------------------------------------------------------------------"
											 "SVM = sqrt(x^2 + y^2 + z^2)", - 1);
		}
		else if (g_strcmp0(selected_text, "Signal Vector Magnitude gs (SVMgs)") == 0) {
			gtk_text_buffer_set_text(buffer, "Signal Vector Magnitude (SVM) is defined as the sum of the Euclidean Norm [sqrt(x^2 + y^2 + z^2)] in g-units. "
											 "Traditionally calculated over 5-second epochs, but can be quantified over any user-specified interval. "
											 "This metric is sampling frequency dependent and the first usage of this metric summarized raw data collected at 100 Hz. "
											 "-------------------------------------------------------------------------------------------------------------------------------------------------"
											 "SVM = sqrt(x^2 + y^2 + z^2) "
											 "-------------------------------------------------------------------------------------------------------------------------------------------------" 
											 "Esliger, D.W., Rowlands, A. N., Hurst, T. L., Catt, M., Murrary, P., & Eston, R. G. (2011). Validation of the GENEA accelerometer. "
											 "Med Sci Sports Exerc. 43(6):1085-1093. https://doi.org/10.1249/MSS.0b013e31820513be", -1);
		}
		else if (g_strcmp0(selected_text, "Euclidean Norm Minus One (ENMO)") == 0) {
		gtk_text_buffer_set_text(buffer, "The Euclidean Norm Minus One (ENMO) is the mean of the Euclidean Norm [sqrt(x^2 + y^2 + z^2)] minus gravity (1g). "
										 "Traditionally calculated over 5-second epochs, but can be quantified over any user-specified interval. "
										 "------------------------------------------------------------------------------------------------------------------------------------------------------"
										 "ENMO = sqrt(x^2 + y^2 + z^2) - 1 "
										 "------------------------------------------------------------------------------------------------------------------------------------------------------"
										 "van Hees, V. T., Fang, Z., Langford, J., et al. (2014). Autocalibration of accelerometer data for free-living physical activity assessment using local gravity and temperature: an evaluation on four continents. "
										 "J Appl Physiol. 117(7):738-744. https://doi.org/japplphysiol.00421.2014", -1);
		}
		else if (g_strcmp0(selected_text, "Low-Pass Filtered Euclidean Norm Minus One (LFENMO)") == 0) {
			gtk_text_buffer_set_text(buffer, "The Low-Pass Filtered Euclidean Norm Minus One (LFENMO) is the Euclidean Norm [sqrt(x^2 + y^2 + z^2)] de-noised with a 20 Hz cut-off 4th order Butterworth low pass filter and with gravity subtracted (1g). "
											 "Traditionally calculated over 5-second epochs, but can be quantified over any user-specified interval. "
											 "---------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "LFENMO = sqrt(x^2 + y^2 + z^2) - 1 -> where the input Euclidean Norm has been digitally filtered. "
											 "---------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "Doherty, A., Jackson, D., Hammerla, N., et al. (2017). Large scale population assessment of physical activity using wrist worn accelerometers: The UK Biobank Study. "
											 "PLoS One. 12(2):e0169649. https://doi.org/10.1371/journal.pone.0169649", -1);
		}
		else if (g_strcmp0(selected_text, "Band-Pass Filtered Euclidean Norm (BFEN)") == 0) {
			gtk_text_buffer_set_text(buffer, "The Band-Pass Filtered Euclidean (BFEN) is the Euclidean Norm [sqrt(x^2 + y^2 + z^2)] of de-noised triaxial accelerometer data (4th order Butterworth band pass filter). "
											 "Typically the band pass filter has utilized -3 db cut-off frequencies of 0.2 and 15 Hz. "
											 "Traditionally calculated over 5-second epochs, but can be quantified over any user-specified interval. "
											 "---------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "BFEN = sqrt(x^2 + y^2 + z^2) -> where the input x, y, and z have been digitally filtered. "
											 "---------------------------------------------------------------------------------------------------------------------------------------------------------"
										     "van Hees, V. T., Gorzelniak, L., Leon, E. C. D, et al. (2013). Separating movement and gravity components in an acceleration signal and implications "
											 "for the assessment of human daily physical activity. "
											 "PLoS One. 8(4):e61691. https://doi.org/10.1371/journal.pone.0061691", -1);
		}
		else if (g_strcmp0(selected_text, "High-Pass Filtered Euclidean Norm (HFEN)") == 0) {
			gtk_text_buffer_set_text(buffer, "The High-Pass Filtered Euclidean (HFEN) is the Euclidean Norm [sqrt(x^2 + y^2 + z^2)] of de-noised triaxial accelerometer data (4th order Butterworth high pass filter). "
											 "Typically the high pass filter has utilized a -3 db cut-off frequency of 0.2 Hz. "
											 "Traditionally calculated over 5-second epochs, but can be quantified over any user-specified interval. "
											 "---------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "HFEN = sqrt(x^2 + y^2 + z^2) -> where the input x, y, and z have been digitally filtered. "
											 "---------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "van Hees, V. T., Gorzelniak, L., Leon, E. C. D, et al. (2013). Separating movement and gravity components in an acceleration signal and implications "
											 "for the assessment of human daily physical activity. "
											 "PLoS One. 8(4):e61691. https://doi.org/10.1371/journal.pone.0061691", -1);
		}
		else if (g_strcmp0(selected_text, "High-Pass Filtered Euclidean Norm + (HFEN+)") == 0) {
			gtk_text_buffer_set_text(buffer, "The High-Pass Filtered Euclidean plus (HFEN+) is the sum of HFEN - Euclidean Norm [sqrt(x^2 + y^2 + z^2)] of de-noised triaxial accelerometer data (4th order Butterworth high pass filter) - "
											 "plus the Euclidean Norm [sqrt(x^2 + y^2 + z^2)]} of three low-pass filtered signals (4th order Butterworth low pass filter) minus one (1g). "
											 "Typically the high- and low-pass filters have utilized -3 db cut-off frequencies of 0.2 Hz. "
											 "Traditionally calculated over 5-second epochs, but can be quantified over any user-specified interval. "
											 "-------------------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "HFEN+ = (sqrt(x1^2 + y2^2 + z3^2) + (sqrt(x2^2 + y2^2 + z3^2) - 1)) -> with x1, y1, and z1 high-pass filtered. "
											 "And x2, y2, and z2 low-pass filtered. "
											 "-------------------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "van Hees, V. T., Gorzelniak, L., Leon, E. C. D, et al. (2013). Separating movement and gravity components in an acceleration signal and implications "
											 "for the assessment of human daily physical activity. "
											 "PLoS One. 8(4):e61691. https://doi.org/10.1371/journal.pone.0061691", -1);
		}
		else if (g_strcmp0(selected_text, "Mean Amplitude Deviation (MAD)") == 0) {
			gtk_text_buffer_set_text(buffer, "The Mean Amplitude Deivation (MAD) describes the mean distance of data points about the mean, where n is the number of samples in the epoch, ri the ith resultant sample "
											 "within the epoch and rbar is the mean resultant value of the epoch. "
											 "Traditionally calculated over 5-second epochs, but can be quantified over any user-specified interval. "
											 "-------------------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "MAD = (1/n) * SUM(|ri - rbar|). For each r, calculate the Euclidean Norm --> sqrt(x^2 + y^2 + z^2)  "
											 "-------------------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "Vaha-Ypya, H., Vasankari, T., Husu, P., Suni, J., & Sievanen, H. (2015). A universal, accurate intensity-based classification of different physical activities  "
											 "using raw data of accelerometer. "
											 "Clin Physiol Funct Imaging. 35(1):64-70. https://doi.org/10.1111/cpf.12127", -1);
		}
		else if (g_strcmp0(selected_text, "Monitor Independent Movement Summaries (MIMS)") == 0) {
			gtk_text_buffer_set_text(buffer, "Monitor independent movement summary units (MIMS units) are calculated as follows: 1) raw signal harmonization to eliminate inter-device variability, "
											 "2) bandpass filtering to eliminate non-human movement, and 3) signal aggregation to reduce data to simplify visualization and summarization. "
											 "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "MIMS Calculation - See Citation Below. "
											 "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "John, D., Tang, Q., Albinali, F., & Intille, S. (2019). An open-source monitor-independent movement summary for accelerometer data processing. "
											 "J Meas Phys Behav. 2(4):268-281. https://doi.org/10.1123/jmpb.2018-0068", -1);
		}
		else if (g_strcmp0(selected_text, "Counts") == 0) {
			gtk_text_buffer_set_text(buffer, "Counts (often called 'activity counts') are the sum of post-filtered accelerometer data over user-specified epochs (intervals). "
											 "Although this metric is common across numerous devices, its calculation varies significantly typically dependent upon device manufacturer. "
											 "The most common 'counts' in physical activity assessment research are those calculated via ActiGraph devices. "
											 "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "Counts - See Citation Below. "
											 "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "ActiGraph, LLC. (2018). What are counts? "
											 "https://actigraphcorp.my.site.com/support/s/article/What-are-counts "
											 "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "ActiGraph, LLC. agcounts - A python package for extracting actigraphy counts from accelerometer data. "
											 "https://github.com/actigraph/agcounts", -1);
		}
		else if (g_strcmp0(selected_text, "Low-Frequency Extension Counts (COUNTS LF)") == 0) {
			gtk_text_buffer_set_text(buffer, "Counts (often called 'activity counts') are the sum of post-filtered accelerometer data over user-specified epochs (intervals). "
											 "Although this metric is common across numerous devices, its calculation varies significantly typically dependent upon device manufacturer. "
											 "The most common 'counts' in physical activity assessment research are those calculated via ActiGraph devices. "
											 "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "Counts - See Citation Below. "
											 "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "ActiGraph, LLC. (2018). What are counts? "
											 "https://actigraphcorp.my.site.com/support/s/article/What-are-counts "
											 "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "ActiGraph, LLC. agcounts - A python package for extracting actigraphy counts from accelerometer data. "
											 "https://github.com/actigraph/agcounts", -1);
				}
		else if (g_strcmp0(selected_text, "Sedentary Sphere (SED SPHERE)") == 0) {
			gtk_text_buffer_set_text(buffer, "The Sedentary Sphere (SED SPHERE) is calculated from signal vector magnitude and estimated wrist position with respect to the gravity vector. "
											 "From these data points, inferences are made about wrist and overall body position. "
											 "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "Sedentary Sphere Calculation - See Citation Below "
											 "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
											 "Rowlands, A. V., Olds, T. S., Hillsdon, M., et al. (2014). Assessing sedentary behavior with the GENEActiv: Introducing the sedentary sphere. "
											 "Med Sci Sports Exerc. 46(6):1235-1247. https://doi.org/10.1249/MSS.0000000000000224", -1);
		}
		else {
			// Handle other options or no selection
			gtk_text_buffer_set_text(buffer, "No text to display.", -1);
		}
		g_free(selected_text);
	}
}

///////////////////////////////////////////////////////////////////////
// Calendar 1 Callbacks
///////////////////////////////////////////////////////////////////////

void	on_calendar1_day_selected_double_click(GtkCalendar *b) {
	// Get the selected date from the calendar
	guint year, month, day;
	gtk_calendar_get_date(GTK_CALENDAR(calendar1), &year, &month, &day);

	// Convert the date to a string in the desired format
	char date_string[11]; // Y-m-d format plus null terminator
	snprintf(date_string, sizeof(date_string), "%04d-%02d-%02d", year, month + 1, day); // month is zero-indexed
	
	// Set the text of the entry to the selected date
	gtk_entry_set_text(GTK_ENTRY(rsentry2), date_string);
	gtk_widget_hide(calwindow1);
}

void	on_calendar1button1_clicked(GtkButton* b) {
	gtk_entry_set_text(GTK_ENTRY(rsentry2), "");
	gtk_widget_hide(calwindow1);
}

///////////////////////////////////////////////////////////////////////
// Calendar 2 Callbacks
///////////////////////////////////////////////////////////////////////

void	on_calendar2_day_selected_double_click(GtkCalendar* b) {
	// Get the selected date from the calendar
	guint year, month, day;
	gtk_calendar_get_date(GTK_CALENDAR(calendar2), &year, &month, &day);

	// Convert the date to a string in the desired format
	char date_string[11]; // Y-m-d format plus null terminator
	snprintf(date_string, sizeof(date_string), "%04d-%02d-%02d", year, month + 1, day); // month is zero-indexed

	// Set the text of the entry to the selected date
	gtk_entry_set_text(GTK_ENTRY(rdentry2), date_string);
	gtk_widget_hide(calwindow2);
}

void	on_calendar2button1_clicked(GtkButton* b) {
	gtk_entry_set_text(GTK_ENTRY(rdentry2), "");
	gtk_widget_hide(calwindow2);
}

///////////////////////////////////////////////////////////////////////
// Calendar 3 Callbacks
///////////////////////////////////////////////////////////////////////

void	on_calendar3_day_selected_double_click(GtkCalendar* b) {
	// Get the selected date from the calendar
	guint year, month, day;
	gtk_calendar_get_date(GTK_CALENDAR(calendar3), &year, &month, &day);

	// Convert the date to a string in the desired format
	char date_string[11]; // Y-m-d format plus null terminator
	snprintf(date_string, sizeof(date_string), "%04d-%02d-%02d", year, month + 1, day); // month is zero-indexed

	// Set the text of the entry to the selected date
	gtk_entry_set_text(GTK_ENTRY(edentry2), date_string);
	gtk_widget_hide(calwindow3);
}

void	on_calendar3button1_clicked(GtkButton* b) {
	gtk_entry_set_text(GTK_ENTRY(edentry2), "");
	gtk_widget_hide(calwindow3);
}

///////////////////////////////////////////////////////////////////////
// Resample Dialog Callbacks
//////////////////////////////////////////////////////////////////////

void	on_resampledialogbutton1_clicked(GtkButton* b) {
	gtk_widget_hide(resampledialog1);
}

void	on_resampledialogbutton2_clicked(GtkButton* b) {
	gtk_widget_hide(resampledialog2);
}

///////////////////////////////////////////////////////////////////////
// Raw Dialog Callbacks
//////////////////////////////////////////////////////////////////////

void	on_rawdialogbutton1_clicked(GtkButton* b) {
	gtk_widget_hide(rawdialog1);
}

void	on_rawdialogbutton2_clicked(GtkButton* b) {
	gtk_widget_hide(rawdialog2);
}

///////////////////////////////////////////////////////////////////////
// Epoch Dialog Callbacks
//////////////////////////////////////////////////////////////////////

void	on_epochdialogbutton1_clicked(GtkButton* b) {
	gtk_widget_hide(epochdialog1);
}

void	on_epochdialogbutton2_clicked(GtkButton* b) {
	gtk_widget_hide(epochdialog2);
}

///////////////////////////////////////////////////////////////////////
// File Viewr Dialog Callbacks
//////////////////////////////////////////////////////////////////////

void	on_fvdialogbutton1_clicked(GtkButton* b) {
	gtk_widget_hide(fvdialog1);
}
