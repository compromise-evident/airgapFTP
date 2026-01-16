//YOUR CONTROLS:                                                                Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
char time_consumption[] = {"sleep 0.056"}; //Smaller = faster boxes.

/*Version 3.0.1 - Fully automated airgap FTP at 1B/s using keyboard
guts & photoresistors. Keep dropping files in folder "Send". */

/*Max file size to send: 4,294,967,295 bits.
Empty files will be ignored and deleted.
All files will be renamed, for example:
"2025-10-19_20:34:55___Sun_Oct_19_08:34:55_PM_MDT_2025"
This same date precedes each line in "Saved_as_text". */

#include <fstream>
#include <iostream>
using namespace std;
int main()
{	int raw_byte;
	char file_byte;
	ifstream in_stream;
	ofstream out_stream;
	
	system("clear"); system("clear");
	cout << "\n"
	     << "        ███████████              ███████████\n"
	     << "        ██       ██              ██       ██\n"
	     << "        ██       ██              ██       ██\n"
	     << "        ██       ██              ██       ██\n"
	     << "        ██████████1              ██████████0\n\n"
	
	     << "                         ██\n\n"
	
	     << "     \\o-,.._                            _..,-o/\n"
	     << "      Set terminal to 80x24, \"White on black\".\n"
	     << "         Tape one photoresistor to each eye\n"
	     << "            thoroughly. Set brightness to\n"
	     << "                ~20%. Sender?  y/n: ";
	
	char user_option; cin >> user_option;
	if((user_option != 'y') && (user_option != 'n')) {cout << "\nInvalid.\n"; return 0;}
	
	
	
	
	
	//_______________________________________________________Send_____________________________________________________//
	if(user_option == 'y')
	{	system("mkdir Send -p");
		system("mkdir temp -p");
		
		for(long long files_sent = 0;;)
		{	system("clear"); system("clear");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n" << files_sent << " sent. Keep dropping files in folder \"Send\"...\n";
			
			//Waits for files in folder "Send".
			for(;;)
			{	system("sleep 5");
				system("ls -t -r Send > temp/f");
				in_stream.open("temp/f");
				in_stream.get(file_byte);
				if(in_stream.eof() == false) {in_stream.close(); break;}
				in_stream.close();
			}
			
			//Makes path to oldest file in folder "Send".
			char path_to_file[10000] = {"Send/"};
			int path_to_file_null_bookmark = 5;
			in_stream.open("temp/f");
			in_stream.get(file_byte);
			for(; file_byte != '\n'; path_to_file_null_bookmark++) {path_to_file[path_to_file_null_bookmark] = file_byte; in_stream.get(file_byte);}
			in_stream.close();
			
			//Gets file size in bits.
			long long total_bits = 0;
			in_stream.open(path_to_file);
			in_stream.get(file_byte);
			for(; in_stream.eof() == false;)
			{	in_stream.get(file_byte);
				total_bits++;
			}
			total_bits *= 8;
			in_stream.close();
			
			//Delete file if empty.
			if(total_bits == 0) {remove(path_to_file); continue;}
			
			//Creates file "metadata".
			out_stream.open("temp/metadata");
			long long temp = total_bits; for(int a = 0; a < 4; a++) {out_stream.put(temp % 256); temp /= 256;} //Writes the number of bits in the file to be sent. Always writes 4 bytes. For example, if file to be sent is 3 bytes, then bytes in file "metadata" are 24,0,0,0. In binary, that's 00011000000000000000000000000000. Now flip it horizontally, that's 24. 00000000000000000000000000011000
			out_stream.close();
			
			//Sends file "metadata".
			system("clear"); system("clear");
			for(int a = 0; a < 10; a++) //..........Rolls blank.
			{	cout << "\n\n\n";
				system(time_consumption);
			}
			
			cout << "                                   ███████          \n"
			     << "                                   ███████          header\n"
			     << "                                   ███████          \n"; //..........Applies header (0 bit so decoder then knows which key represents 0.)
			system(time_consumption);
			cout << "\n\n\n";
			system(time_consumption);
			
			long long bit_count = 1;
			long long metadata_total_bits = 32;
			in_stream.open("temp/metadata");
			in_stream.get(file_byte);
			for(; in_stream.eof() == false;)
			{	//..........Converts file byte to (0 to 255.)
				raw_byte = file_byte;
				if(raw_byte < 0) {raw_byte += 256;}
				
				//..........Converts file byte to binary of 00000000 to 11111111.
				bool binary[8] = {0};
				int place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(raw_byte >= place_value)
					{	binary[a] = 1;
						raw_byte -= place_value;
					}
					
					place_value /= 2;
				}
				
				//..........Writes 1 byte to file based on binary[].
				for(int bit = 0; bit < 8; bit++)
				{	if(binary[bit] == 0)
					{	cout << "                                   ███████          " << bit_count << " of " << metadata_total_bits << "\n"
						     << "                                   ███████          " << bit_count << " of " << metadata_total_bits << "\n"
						     << "                                   ███████          " << bit_count << " of " << metadata_total_bits << "\n";
						system(time_consumption);
					}
					else
					{	cout << "          ███████                                   " << bit_count << " of " << metadata_total_bits << "\n"
						     << "          ███████                                   " << bit_count << " of " << metadata_total_bits << "\n"
						     << "          ███████                                   " << bit_count << " of " << metadata_total_bits << "\n";
						system(time_consumption);
					}
					
					//..........Blank
					if(bit_count < metadata_total_bits)
					{	for(int a = 0; a < 3; a++) {cout << "                                                    " << bit_count << " of " << metadata_total_bits << "\n";}
						system(time_consumption);
					}
					else {cout << "\n\n\n"; system(time_consumption);}
					
					bit_count++;
				}
				
				in_stream.get(file_byte);
			}
			in_stream.close();
			
			for(int a = 0; a < 10; a++)
			{	cout << "\n\n\n";
				system(time_consumption);
			}
			
			//Sends file.
			bit_count = 1;
			in_stream.open(path_to_file);
			in_stream.get(file_byte);
			for(; in_stream.eof() == false;)
			{	//..........Converts file byte to (0 to 255.)
				raw_byte = file_byte;
				if(raw_byte < 0) {raw_byte += 256;}
				
				//..........Converts file byte to binary of 00000000 to 11111111.
				bool binary[8] = {0};
				int place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(raw_byte >= place_value)
					{	binary[a] = 1;
						raw_byte -= place_value;
					}
					
					place_value /= 2;
				}
				
				//..........Writes 1 byte to file based on binary[].
				for(int bit = 0; bit < 8; bit++)
				{	if(binary[bit] == 0)
					{	cout << "                                   ███████          " << bit_count << " of " << total_bits << "\n"
						     << "                                   ███████          " << bit_count << " of " << total_bits << "\n"
						     << "                                   ███████          " << bit_count << " of " << total_bits << "\n";
						system(time_consumption);
					}
					else
					{	cout << "          ███████                                   " << bit_count << " of " << total_bits << "\n"
						     << "          ███████                                   " << bit_count << " of " << total_bits << "\n"
						     << "          ███████                                   " << bit_count << " of " << total_bits << "\n";
						system(time_consumption);
					}
					
					//..........Blank
					if(bit_count < total_bits)
					{	for(int a = 0; a < 3; a++) {cout << "                                                    " << bit_count << " of " << total_bits << "\n";}
						system(time_consumption);
					}
					else {cout << "\n\n\n"; system(time_consumption);}
					
					bit_count++;
				}
				
				in_stream.get(file_byte);
			}
			in_stream.close();
			
			for(int a = 0; a < 10; a++)
			{	cout << "\n\n\n";
				system(time_consumption);
			}
			
			//Done, next.
			remove(path_to_file);
			if(total_bits > 16000000) {system("sleep 10");}
			files_sent++;
		}
	}
	
	
	
	
	
	//______________________________________________________Receive___________________________________________________//
	if(user_option == 'n')
	{	system("mkdir temp           -p");
		system("mkdir Saved_as_files -p");
		out_stream.open("Saved_as_text", ios::app); out_stream.close();
		
		//A bash file is created, its permissions set, and is called upon by this C++.
		//This is done because "read -n" is a broken option on KDE using Geany???!!!
		out_stream.open("temp/bash_to_get_metadata.txt");
		out_stream << "#!/bin/bash\n"                           ; //..........Bash header.
		out_stream << "read -n 33 var\n"                        ; //..........Automatically presses return after 33 char entered in terminal.
		out_stream << "echo \"$var\" > temp/received_metadata\n"; //..........Writes entire entered string (33-bit metadata) to file "received_metadata".
		out_stream.close();
		system("chmod 0777 temp/bash_to_get_metadata.txt");
		
		for(long long files_saved = 0;;)
		{	system("clear"); system("clear");
			cout << "\n" << files_saved << " saved...\n\n";
			
			//Reads 33 keys from keyboard.
			//First bit is always '0' (right eye blinks so we know which keyboard character
			//is 1 and which is 0.) This header is # of keyboard characters to expect next.
			system("./temp/bash_to_get_metadata.txt"); cout << "   (33-bit header)\n\n";
			
			//Infers which keyboard key is bit '0'.
			char keyboard_key_representing_bit_0;
			in_stream.open("temp/received_metadata");
			in_stream.get(file_byte);
			keyboard_key_representing_bit_0 = file_byte;
			in_stream.close();
			
			//Creates file "metadata".
			in_stream.open("temp/received_metadata");
			out_stream.open("temp/metadata");
			in_stream.get(file_byte); //Skips first byte. !!!IMPORTANT!!!
			for(int loop = 0; loop < 4; loop++)
			{	bool binary[8] = {0}; //..........Grabs 8 bytes, they represent 8 bits.
				for(int a = 0; a < 8; a++)
				{	in_stream.get(file_byte);
					if(file_byte == keyboard_key_representing_bit_0) {binary[a] = 0;}
					else                                             {binary[a] = 1;}
				}
				
				raw_byte = 0; //..........Converts 8 bits to integer.
				int place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(binary[a] == 1) {raw_byte += place_value;}
					place_value /= 2;
				}
				
				if(raw_byte < 128) {out_stream.put(raw_byte      );} //..........Writes byte to file.
				else               {out_stream.put(raw_byte - 256);}
			}
			in_stream.close();
			out_stream.close();
			
			//Reads file "metadata".
			long long bits_to_receive = 0;
			in_stream.open("temp/metadata");
			long long table[4]; for(int a = 0; a < 4; a++) {in_stream.get(file_byte); raw_byte = file_byte; if(raw_byte < 0) {raw_byte += 256;} table[a] = raw_byte;}
			in_stream.close();
			bits_to_receive += (table[0] *        1);
			bits_to_receive += (table[1] *      256);
			bits_to_receive += (table[2] *    65536);
			bits_to_receive += (table[3] * 16777216);
			
			//Creates new file "bash_to_get_file.txt" with n keyboard keys to read. (n comes from file "metadata".)
			//A bash file is created, its permissions set, and is called upon by this C++.
			//This is done because "read -n" is a broken option on KDE using Geany???!!!
			out_stream.open("temp/bash_to_get_file.txt");
			out_stream << "#!/bin/bash\n"                          ; //..........Bash header.
			out_stream << "read -n " << bits_to_receive << " var\n"; //..........Automatically presses return after n char entered in terminal.
			out_stream << "echo \"$var\" > temp/received_file\n"   ; //..........Writes entire entered string (file substance) to file "received_file".
			out_stream.close();
			system("chmod 0777 temp/bash_to_get_file.txt");
			
			//Reads n keys from keyboard.
			system("./temp/bash_to_get_file.txt");
			
			//Creates file "file".
			in_stream.open("temp/received_file");
			out_stream.open("temp/file");
			for(int loop = 0; loop < (bits_to_receive / 8); loop++)
			{	bool binary[8] = {0}; //..........Grabs 8 bytes, they represent 8 bits.
				for(int a = 0; a < 8; a++)
				{	in_stream.get(file_byte);
					if(file_byte == keyboard_key_representing_bit_0) {binary[a] = 0;}
					else                                             {binary[a] = 1;}
				}
				
				raw_byte = 0; //..........Converts 8 bits to integer.
				int place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(binary[a] == 1) {raw_byte += place_value;}
					place_value /= 2;
				}
				
				if(raw_byte < 128) {out_stream.put(raw_byte      );} //..........Writes byte to file.
				else               {out_stream.put(raw_byte - 256);}
			}
			in_stream.close();
			out_stream.close();
			
			//Gets military time.
			system("date --rfc-3339=seconds > temp/military_time");
			in_stream.open("temp/military_time"); char military_time[50] = {'\0'}; in_stream.getline(military_time, 50); in_stream.close();
			military_time[10] = '_'; military_time[19] = '\0';
			
			//Gets civilian time.
			system("date > temp/civilian_time");
			in_stream.open("temp/civilian_time"); char civilian_time[50] = {'\0'}; in_stream.getline(civilian_time, 50); in_stream.close();
			for(int a = 0; a < 50; a++) {if(civilian_time[a] == ' ') {civilian_time[a] = '_';}}
			
			//Makes a file name like "Saved_as_files/2026-01-15_18:03:14___Thu_Jan_15_06:03:14_PM_MST_2026".
			string temporal_name = "Saved_as_files/"; temporal_name += military_time; temporal_name += "___"; temporal_name += civilian_time;
			
			//Copies file to folder "Saved_as_files".
			in_stream.open("temp/file");
			out_stream.open(temporal_name);
			in_stream.get(file_byte);
			for(; in_stream.eof() == false;) {out_stream.put(file_byte); in_stream.get(file_byte);}
			in_stream.close();
			out_stream.close();
			
			//Copies file to file "Saved_as_text".
			in_stream.open("temp/file");
			out_stream.open("Saved_as_text", ios::app);
			out_stream << military_time; out_stream << "___"; out_stream << civilian_time; out_stream << "___";
			
			in_stream.get(file_byte);
			for(; in_stream.eof() == false;)
			{	if     ( file_byte ==   9)  {out_stream << " \\t ";  }
				else if( file_byte ==  10)  {out_stream << " \\n ";  }
				else if( file_byte ==  13)  {out_stream << " \\r ";  }
				else if((file_byte  >  31)
				     && (file_byte  < 127)) {out_stream << file_byte;}
				
				in_stream.get(file_byte);
			}
			out_stream << "\n";
			in_stream.close();
			out_stream.close();
			
			files_saved++;
		}
	}
}
