UnoArduSimV2.0 README

HOST SITE: https://www.sites.google.com/site/unoardusim/home

I. WINDOWS DEFENDER FALSE DETECTION -- RESOLVED??

Windows Defender HAD BEEN falsely detecting some bit pattern from Trojan:Win32/Azden.A!cl somewhere inside the downloaded and extracted UnoArduSim.exe V2.0 file on Dec 31. 2017. THIS WAS A FALSE POSITIVE -- Windows Defender had scanned the executable and zip file as COMPLETELY CLEAN on my machine before I had zipped it and uploaded and posted it, and only declared a (false) detection after I downloaded it from the UnoArduSim Downloads page EVEN THOUGHN THE ORIGINAL UnoArduSim.exe AND THE DOWLOADED/UNZIPPED UnoArduSim.exe WERE BYTE_FOR_BYTE IDENTICAL. 

A small tweak and recompile seems to have solved this issue (as of Jan 2, 2018) BUT IF IT POPS UP AGAIN, you would need to tell Windows Defender to Restore UnoArduSim.exe from Quaranatine and to allow it to run on your machine (and copy back the Help files it may have also removed!). For peace of mind, you can submit the restored UnoArduSim.exe file (or the entire downloaded zip file) to www.virustotal.com for checking before you run it. I have made a submission to Microssoft to report this problem.

II. PORT TO QtCreator:

UnoArduSim's source code files have been extensively revised (and cleaned up) for the port QtCreator. Depl;oyment and distribution of UnoArduSim V2.0 (and higher) is under the GNU LGPLV3 public license option provided by Qt. See the LICENSE.txt file for details on this.

The new QtCreator version requires a number of Qt DLL's and support files, all of which are included in the posted UnoArduSimV2.0.zip file -- all of these extra files and folders must stay in the same directory as UnoArduSim.exe. No installation is necessary -- just unzip all to your desired directory and place a shortcut to UnoArduSim.exe  on the desktop. In case the revisions for the port have somehow broken something, I have also posted a final UnoArduSimV1.7.3.zip as a backup (it has all the same bug fixes made as version 2.0 does). 

III. INTERNATIONALIZATION:

As of version 2.0, UnoArduSim now has support for multiple languages through its Configure | Preferences menu. The desired language is represented by a two-Latin-character code 'xx' (the ISO-639-1 standard code, where for example 'xx' is 'en' for English). English can always be selected under Preferences, as can the 'xx' language for the user's locale (as long as a corresponding UnoArduSim_xx.qm translation file is present inside the 'translations' folder of the UnoArduSim.exe directory). In addition, regardless of your locale, you can also specify your preferred language using its two-letter code 'xx' as the very first line of the myArduPrefs.txt file. If the needed translation file is absent, UnoArduSim reverts to English.

When you Load and Save your Preferences and I/O Device configurations, they are loaded and saved using translations for the current language. If you have these files in English, you can switch temporarily from your preferred language back to 'en' (under Configure | Preferences), Load them in English, then switch back to 'xx', and Save to get them in your preferred language.

I must create all the desired *.qm translation files from the source code using the supplied QtLinguist support tools. I do this with the aid of "Google Translator Toolkit" and a small set of custom utility programs I have created for this purpose. If you would like to see a new translation added for your locale, and you are willing to put the effort into checking and editing the results from Google Translator Toolkit, please send me an email at the address listed on the host web site Translations page, and I will send you the necessary files for editing. Be forwarned, this is no simple task as there are over 950 phrases to be translated for UnoArduSim.exe alone, not to mention the Full and Quick help files which will also need translations. You must be willing to share your translations with all other users. and I will need your full name and country/city so I can give you credit on the download page for your contribution. I will add new translation files to the Translations page as users help me to create them.

IV. INTRODUCTION TO UnoArduSim:

When you first run UnoArduSim.exe, you will see a default set of I/O devices (one of each of eight of nine available "big" I/O devices, and several of each of the "small" I/O devices), and a dummy "simple.ino" default program which you can immediately run.  

You can use the Configure menu to adjust the set of I/O devices, and from the provided dialog "Save" that configuration for next time (as a named text file). That file name will be automatically added to the myArduPrefs.txt file that gets loaded at the next program startup -- to go back to the default startup configuration, delete the “IODevs File Name” line in the myArduPrefs.txt file (or just delete that entire file).

When ready, you can load and try out the provided DemoProg1.ino demonstration program -- that program needs to have a particular set of I/O devices attached, so use "Configure->IO Devices" and "Load" the myUnoDevs_DemoProg1.txt file. That will load the devices (with pre-set pin connections and settings and values) that are needed by the DemoProg1.ino program. Run it to see the IO devices and program in action. Try double-clicking (or right-clicking) on the SERIAL I/O device to see an associated larger window pop up for easier monitoring/setting of RX/TX bytes/chars (SOFTSER, SPISLV, I2CSLV, and SD_DRV devices also have that popup window functionality). During execution, drag the new I/O Values Scaler slider found on the main toolbar to control the driven DC motor's speed.

You can then try out a more complex (and fun) program DemoProg2.ino that has musical playback and I/O devices moving to the music (my acknowledgement to the animated TV program, the Simpsons, for that one). This second demo program also shows that you can split your code (and included data) between multiple files for better viewing and navigation.

Finally, DemoProg3.ino demonstrates the newer 1SHOT I/O device, and generates waveforms which can be viewed in the Digital Waveforms window. Load DemoProg3.ino and then the myUnoDevs_DemoProg3.txt file. Now left-click on pins 2,3,4, and 5 in turn on the border of the Uno board -- four waveforms will be showing. Run the program to see the waveforms created by a loop() instruction repeatedly triggering the first 1SHOT device. You can manually trigger the second 1SHOT at any time by pressing and then releasing the PUSH I/O Device attached to pin 3 to cause a rising edge. You can halt the program at any point and use the blue and red cursors inside the Digital Waveforms window to measure the produced pulse widths and delays.

