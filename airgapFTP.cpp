/// airgapFTP - fully automated airgap FTP at 1B/s                              Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
///             using keyboard guts & photoresistors.
///             Keep dropping files in folder "Send".


/* Version 2.0.0
1kB in 17 minutes. Max file size: 12.49 MB (1,157 days to transfer.) */

#include <fstream>
#include <iostream>
using namespace std;

int main()
{	//                               user knobs
	
	/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\  /////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    ////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\      ///////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\        //////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\            ////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\              ///////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\                  /////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\                      ///////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\                              ///////////////////////
	\\\\\\\\\\\\\\\\\\                                        ////////////////*/
	
	char time_consumption[100] = {"sleep 0.056"}; //DEFAULT = "sleep 0.056"
	//                           Increase for slower boxes. Decrease for faster.
	//                           If mechanical keyboard, make it lightning-fast.
	
	/*////////////////                                        \\\\\\\\\\\\\\\\\\
	///////////////////////                              \\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////                      \\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////                  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////              \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////////////////            \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////        \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////////      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////////////////////    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////////////  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
	
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
	     << "                ~50%. Sender?  y/n: ";
	
	char user_option; cin >> user_option;
	if((user_option != 'y') && (user_option != 'n')) {cout << "\nInvalid.\n"; return 0;}
	
	
	
	
	
	//_______________________________________________________Send_____________________________________________________//
	if(user_option == 'y')
	{	system("mkdir Send -p");
		system("mkdir Done -p");
		system("mkdir temp -p");
		
		char garbage_byte;
		for(long long files_sent = 0;;)
		{	system("clear"); system("clear");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n" << files_sent << " sent. Keep dropping files in folder \"Send\"...\n";
			
			//Waits for files in folder "Send".
			for(;;)
			{	system("sleep 5");
				system("ls Send > temp/file_names_in_Send");
				in_stream.open("temp/file_names_in_Send");
				in_stream.get(garbage_byte);
				if(in_stream.eof() == false) {in_stream.close(); break;}
				in_stream.close();
			}
			
			//Makes path to first file in folder "Send".
			char path_to_file[10000] = {"Send/"};
			int path_to_file_null_bookmark = 5;
			in_stream.open("temp/file_names_in_Send");
			in_stream.get(garbage_byte);
			for(; garbage_byte != '\n';) {path_to_file[path_to_file_null_bookmark] = garbage_byte; in_stream.get(garbage_byte); path_to_file_null_bookmark++;}
			in_stream.close();
			
			//Copies file to folder "Done" but renames it to       "2024-01-28_23:06:58___Sun_Jan_28_11:06:58_PM_MST_2024___your-file-name".
			char path_to_Done[10000] = {"Done/"};
			int path_to_Done_null_bookmark = 5;
			
			system("date --rfc-3339=seconds > temp/last_time");
			in_stream.open("temp/last_time");
			for(int a = 0; a < 19; a++)
			{	in_stream.get(garbage_byte);
				if(garbage_byte == 32) {path_to_Done[path_to_Done_null_bookmark] = '_'         ;}
				else                   {path_to_Done[path_to_Done_null_bookmark] = garbage_byte;}
				path_to_Done_null_bookmark++;
			}
			in_stream.close();
			
			path_to_Done[path_to_Done_null_bookmark    ] = '_';
			path_to_Done[path_to_Done_null_bookmark + 1] = '_';
			path_to_Done[path_to_Done_null_bookmark + 2] = '_';
			path_to_Done_null_bookmark += 3;
			
			system("date > temp/last_time");
			in_stream.open("temp/last_time");
			for(int a = 0; a < 31; a++)
			{	in_stream.get(garbage_byte);
				if(garbage_byte == 32) {path_to_Done[path_to_Done_null_bookmark] = '_'         ;}
				else                   {path_to_Done[path_to_Done_null_bookmark] = garbage_byte;}
				path_to_Done_null_bookmark++;
			}
			in_stream.close();
			
			path_to_Done[path_to_Done_null_bookmark    ] = '_';
			path_to_Done[path_to_Done_null_bookmark + 1] = '_';
			path_to_Done[path_to_Done_null_bookmark + 2] = '_';
			path_to_Done_null_bookmark += 3;
			
			path_to_file_null_bookmark = 5;
			for(; path_to_file[path_to_file_null_bookmark] != '\0';)
			{	path_to_Done[path_to_Done_null_bookmark] = path_to_file[path_to_file_null_bookmark];
				path_to_Done_null_bookmark++;
				path_to_file_null_bookmark++;
			}
			
			in_stream.open(path_to_file);
			out_stream.open(path_to_Done);
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;) {out_stream.put(garbage_byte); in_stream.get(garbage_byte);}
			in_stream.close();
			out_stream.close();
			
			//Gets file size in bits.
			long long total_bits = 0;
			in_stream.open(path_to_file);
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;)
			{	in_stream.get(garbage_byte);
				total_bits++;
			}
			total_bits *= 8;
			in_stream.close();
			
			//Adds to total_bits the size of file name +1.
			int total_bits_supplement = 0;
			path_to_file_null_bookmark = 5;
			for(; path_to_file[path_to_file_null_bookmark] != '\0';)
			{	total_bits_supplement++;
				path_to_file_null_bookmark++;
			}
			total_bits_supplement++;
			total_bits += (total_bits_supplement * 8);
			
			//Creates file "metadata" (# of bits.)
			out_stream.open("temp/metadata");
			long long place = 10;
			for(int a = 0; a < 7; a++)
			{	if(total_bits < place) {out_stream << "0";}
				place *= 10;
			}
			out_stream << total_bits;
			out_stream.close();
			
			//Compresses file "metadata" in half via custom hex. (Hex-to-Bin here.)
			in_stream.open("temp/metadata");
			out_stream.open("temp/send_metadata_compressed");
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;)
			{	int temp_file_byte_normal = garbage_byte; //..........Converts file byte to int (0 to 255.)
				if(temp_file_byte_normal < 0) {temp_file_byte_normal += 256;}
				
				if     (temp_file_byte_normal < 58) {temp_file_byte_normal -= 48;} //..........0-9
				else if(temp_file_byte_normal < 85) {temp_file_byte_normal -= 72;} //..........RST
				else                                {temp_file_byte_normal -= 75;} //..........XYZ
				int first_nibble = temp_file_byte_normal;
				
				in_stream.get(garbage_byte);
				temp_file_byte_normal = garbage_byte; //..........Converts its pair byte to int (0 to 255.)
				if(temp_file_byte_normal < 0) {temp_file_byte_normal += 256;}
				
				if     (temp_file_byte_normal < 58) {temp_file_byte_normal -= 48;} //..........0-9
				else if(temp_file_byte_normal < 85) {temp_file_byte_normal -= 72;} //..........RST
				else                                {temp_file_byte_normal -= 75;} //..........XYZ
				int second_nibble = temp_file_byte_normal;
				
				bool binary[8] = {0}; //..........Converts first nibble to bin.
				int place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(first_nibble >= place_value)
					{	binary[a] = 1;
						first_nibble -= place_value;
					}
					place_value /= 2;
				}
				
				bool binary_first_nibble_copy[8]; for(int a = 0; a < 8; a++) {binary_first_nibble_copy[a] = binary[a];}
				for(int a = 0; a < 8; a++) {binary[a] = 0;} //..........Converts second nibble to bin.
				place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(second_nibble >= place_value)
					{	binary[a] = 1;
						second_nibble -= place_value;
					}
					place_value /= 2;
				}
				for(int a = 0; a < 4; a++) {binary[a] = binary_first_nibble_copy[a + 4];}
				
				int extracted_byte = 0; //..........Converts from 8 binary bits to int.
				place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(binary[a] == 1) {extracted_byte += place_value;}
					
					place_value /= 2;
				}
				
				if(extracted_byte < 128) {out_stream.put(extracted_byte      );} //..........Writes byte to file.
				else                     {out_stream.put(extracted_byte - 256);}
				
				in_stream.get(garbage_byte);
			}
			in_stream.close();
			out_stream.close();
			
			//Creates file "send_file" (concatenates file name with file substance.)
			out_stream.open("temp/send_file");
			path_to_file_null_bookmark = 5;
			for(; path_to_file[path_to_file_null_bookmark] != '\0';) {out_stream << path_to_file[path_to_file_null_bookmark]; path_to_file_null_bookmark++;}
			out_stream << "\n";
			out_stream.close();
			
			in_stream.open(path_to_file);
			out_stream.open("temp/send_file", ios::app);
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;) {out_stream.put(garbage_byte); in_stream.get(garbage_byte);}
			in_stream.close();
			out_stream.close();
			
			//Gets file size of "send_metadata_compressed" in bits.
			total_bits = 0;
			in_stream.open("temp/send_metadata_compressed");
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;)
			{	in_stream.get(garbage_byte);
				total_bits++;
			}
			total_bits *= 8;
			in_stream.close();
			
			//Sends file "send_metadata_compressed".
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
			int  temp_file_byte_normal;
			in_stream.open("temp/send_metadata_compressed");
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;)
			{	//..........Converts file byte to (0 to 255.)
				temp_file_byte_normal = garbage_byte;
				if(temp_file_byte_normal < 0) {temp_file_byte_normal += 256;}
				
				//..........Converts file byte to binary of 00000000 to 11111111.
				bool binary[8] = {0};
				int place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(temp_file_byte_normal >= place_value)
					{	binary[a] = 1;
						temp_file_byte_normal -= place_value;
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
				
				in_stream.get(garbage_byte);
			}
			in_stream.close();
			
			for(int a = 0; a < 10; a++)
			{	cout << "\n\n\n";
				system(time_consumption);
			}
			
			//Gets file size of "send_file" in bits.
			total_bits = 0;
			long long total_bits_copy;
			in_stream.open("temp/send_file");
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;)
			{	in_stream.get(garbage_byte);
				total_bits++;
			}
			total_bits *= 8;
			total_bits_copy = total_bits;
			in_stream.close();
			
			//Sends file "send_file".
			bit_count = 1;
			in_stream.open("temp/send_file");
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;)
			{	//..........Converts file byte to (0 to 255.)
				temp_file_byte_normal = garbage_byte;
				if(temp_file_byte_normal < 0) {temp_file_byte_normal += 256;}
				
				//..........Converts file byte to binary of 00000000 to 11111111.
				bool binary[8] = {0};
				int place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(temp_file_byte_normal >= place_value)
					{	binary[a] = 1;
						temp_file_byte_normal -= place_value;
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
				
				in_stream.get(garbage_byte);
			}
			in_stream.close();
			
			for(int a = 0; a < 10; a++)
			{	cout << "\n\n\n";
				system(time_consumption);
			}
			
			//Done, next.
			remove(path_to_file);
			if(total_bits_copy > 16000000) {system("sleep 10");}
			files_sent++;
		}
	}
	
	
	
	
	
	//______________________________________________________Receive___________________________________________________//
	if(user_option == 'n')
	{	//First received: 33-bit header, of which first bit is '0' (right eye blinks.) This way, keyboard
		//keys used by the photoresistors are "binary." This header is # of bits to expect next:
		//Each file is a concatenation of its name + substance, separated by '\n'.
		
		system("mkdir temp           -p");
		system("mkdir Saved_as_files -p");
		out_stream.open("Saved_as_text", ios::app); out_stream.close();
		
		//A bash file is created, its permissions set, and is called upon by this C++.
		//This is done because "read -n" is a broken option on KDE using Geany???!!!
		out_stream.open("temp/bash.txt");
		out_stream << "#!/bin/bash\n"                 ; //..........Bash header.
		out_stream << "read -n 00000033 var\n"        ; //..........Automatically presses return after n char entered in terminal.
		out_stream << "echo \"$var\" > temp/entered\n"; //..........Writes entire entered string (33-bit metadata) to file "entered".
		out_stream.close();
		system("chmod 0777 temp/bash.txt");
		
		char garbage_byte;
		for(long long files_saved = 0;;)
		{	system("clear"); system("clear");
			cout << "\n" << files_saved << " saved...\n\n";
			
			//Reads 33-bit header from keyboard.
			system("./temp/bash.txt"); cout << "   (33-bit header)\n\n";
			
			//Infers which keyboard key is bit '0'.
			char keyboard_key_representing_bit_0;
			in_stream.open("temp/entered");
			in_stream.get(garbage_byte);
			keyboard_key_representing_bit_0 = garbage_byte;
			in_stream.close();
			
			//Creates file "metadata_binary_text" from file "entered". (Keyboard keys to binary-text.)
			in_stream.open("temp/entered");
			out_stream.open("temp/metadata_binary_text");
			in_stream.get(garbage_byte); //..........Skips header header.
			in_stream.get(garbage_byte);
			for(int a = 0; a < 32; a++)
			{	if(garbage_byte == keyboard_key_representing_bit_0) {out_stream << "0";}
				else                                                {out_stream << "1";}
				
				in_stream.get(garbage_byte);
			}
			in_stream.close();
			out_stream.close();
			
			//Creates file "metadata_binary". (Binary text to binary.)
			in_stream.open("temp/metadata_binary_text");
			out_stream.open("temp/metadata_binary");
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;)
			{	bool binary[8] = {0}; //..........Grabs 8 text-bits.
				for(int a = 0; a < 8; a++)
				{	if(garbage_byte == '0') {binary[a] = 0;}
					else                    {binary[a] = 1;}
					
					in_stream.get(garbage_byte);
				}
				
				int extracted_byte = 0; //..........Converts from 8 binary bits to an integer.
				int place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(binary[a] == 1) {extracted_byte += place_value;}
					
					place_value /= 2;
				}
				
				if(extracted_byte < 128) {out_stream.put(extracted_byte      );} //..........Writes byte to file.
				else                     {out_stream.put(extracted_byte - 256);}
			}
			in_stream.close();
			out_stream.close();
			
			//Decompresses metadata from file "entered". (Bin-to-hex here.)
			in_stream.open("temp/metadata_binary");
			out_stream.open("temp/metadata_decompressed");
			in_stream.get(garbage_byte);
			for(int md = 0; md < 4; md++)
			{	int temp_file_byte_normal = garbage_byte; //..........Converts file byte to int (0 to 255.)
				if(temp_file_byte_normal < 0) {temp_file_byte_normal += 256;}
				
				bool binary[8] = {0}; //..........Converts file byte to bin.
				int place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(temp_file_byte_normal >= place_value)
					{	binary[a] = 1;
						temp_file_byte_normal -= place_value;
					}
					place_value /= 2;
				}
				
				int first_nibble = 0; //..........Converts first 4 bits to int.
				place_value = 8;
				for(int a = 0; a < 4; a++)
				{	if(binary[a] == 1) {first_nibble += place_value;}
					place_value /= 2;
				}
				
				int second_nibble = 0; //..........Converts last 4 bits to int.
				place_value = 8;
				for(int a = 4; a < 8; a++)
				{	if(binary[a] == 1) {second_nibble += place_value;}
					place_value /= 2;
				}
				
				if     (first_nibble < 10) {first_nibble += 48;} //..........0-9
				else if(first_nibble < 13) {first_nibble += 72;} //..........RST
				else                       {first_nibble += 75;} //..........XYZ
				
				if(first_nibble < 128)  {out_stream.put(first_nibble       );} //..........Writes hex byte to file.
				else                    {out_stream.put(first_nibble  - 256);}
				
				if     (second_nibble < 10) {second_nibble += 48;} //..........0-9
				else if(second_nibble < 13) {second_nibble += 72;} //..........RST
				else                        {second_nibble += 75;} //..........XYZ
				
				if(second_nibble < 128) {out_stream.put(second_nibble      );} //..........Writes hex byte to file.
				else                    {out_stream.put(second_nibble - 256);}
				
				in_stream.get(garbage_byte);
			}
			in_stream.close();
			out_stream.close();
			
			//Creates new file "bash_dynamic.txt" with n keyboard keys to read. (n comes from file "metadata_decompressed".)
			//A bash file is created, its permissions set, and is called upon by this C++.
			//This is done because "read -n" is a broken option on KDE using Geany???!!!
			in_stream.open("temp/metadata_decompressed");
			out_stream.open("temp/bash_dynamic.txt");
			out_stream << "#!/bin/bash\n"                      ; //..........Bash header.
			out_stream << "read -n "                           ;
			
			for(int a = 0; a < 8; a++) {in_stream.get(garbage_byte); out_stream << garbage_byte;}
			
			out_stream << " var\n"                             ; //..........Automatically presses return after n char entered in terminal.
			out_stream << "echo \"$var\" > temp/entered_file\n"; //..........Writes entire entered string (file name + file substance) to file "entered_file".
			in_stream.close();
			out_stream.close();
			system("chmod 0777 temp/bash_dynamic.txt");
			
			//Reads n-key file from keyboard.
			system("./temp/bash_dynamic.txt");
			
			//Gets file size of "entered_file" without the '\n' at the end.
			int total_bytes = 0;
			in_stream.open("temp/entered_file");
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;)
			{	in_stream.get(garbage_byte);
				total_bytes++;
			}
			in_stream.close();
			
			total_bytes--;
			total_bytes /= 8;
			
			//Creates file "extracted_file" from file "entered_file".
			in_stream.open("temp/entered_file");
			out_stream.open("temp/extracted_file");
			in_stream.get(garbage_byte);
			for(int substance = 0; substance < total_bytes; substance++)
			{	bool binary[8] = {0}; //..........Grabs 8 text-bits.
				for(int a = 0; a < 8; a++)
				{	if(garbage_byte == keyboard_key_representing_bit_0) {binary[a] = 0;}
					else                                                {binary[a] = 1;}
					
					in_stream.get(garbage_byte);
				}
				
				int extracted_byte = 0; //..........Converts from 8 binary bits to an integer.
				int place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(binary[a] == 1) {extracted_byte += place_value;}
					
					place_value /= 2;
				}
				
				if(extracted_byte < 128) {out_stream.put(extracted_byte      );} //..........Writes byte to file.
				else                     {out_stream.put(extracted_byte - 256);}
			}
			in_stream.close();
			out_stream.close();
			
			//Makes proper file name for saving substance from file "extracted_file" to folder "Saved_as_files".
			char path_to_Saved_as_files[10000] = {"Saved_as_files/"}; //Appended: "2024-01-30_02:04:17___Tue_Jan_30_02:04:17_AM_MST_2024___your-file-name".
			int path_to_Saved_as_files_null_bookmark = 15;
			
			system("date --rfc-3339=seconds > temp/last_time");
			in_stream.open("temp/last_time");
			for(int a = 0; a < 19; a++)
			{	in_stream.get(garbage_byte);
				if(garbage_byte == 32) {path_to_Saved_as_files[path_to_Saved_as_files_null_bookmark] = '_'         ;}
				else                   {path_to_Saved_as_files[path_to_Saved_as_files_null_bookmark] = garbage_byte;}
				path_to_Saved_as_files_null_bookmark++;
			}
			in_stream.close();
			
			path_to_Saved_as_files[path_to_Saved_as_files_null_bookmark    ] = '_';
			path_to_Saved_as_files[path_to_Saved_as_files_null_bookmark + 1] = '_';
			path_to_Saved_as_files[path_to_Saved_as_files_null_bookmark + 2] = '_';
			path_to_Saved_as_files_null_bookmark += 3;
			
			system("date > temp/last_time");
			in_stream.open("temp/last_time");
			for(int a = 0; a < 31; a++)
			{	in_stream.get(garbage_byte);
				if(garbage_byte == 32) {path_to_Saved_as_files[path_to_Saved_as_files_null_bookmark] = '_'         ;}
				else                   {path_to_Saved_as_files[path_to_Saved_as_files_null_bookmark] = garbage_byte;}
				path_to_Saved_as_files_null_bookmark++;
			}
			in_stream.close();
			
			path_to_Saved_as_files[path_to_Saved_as_files_null_bookmark    ] = '_';
			path_to_Saved_as_files[path_to_Saved_as_files_null_bookmark + 1] = '_';
			path_to_Saved_as_files[path_to_Saved_as_files_null_bookmark + 2] = '_';
			path_to_Saved_as_files_null_bookmark += 3;
			
			in_stream.open("temp/extracted_file");
			in_stream.get(garbage_byte);
			int name_length = 0;
			for(; garbage_byte != '\n';)
			{	path_to_Saved_as_files[path_to_Saved_as_files_null_bookmark] = garbage_byte;
				path_to_Saved_as_files_null_bookmark++;
				name_length++;
				in_stream.get(garbage_byte);
			}
			in_stream.close();
			name_length++; //..........To skips file name + '\n'.
			
			//Saves substance from file "extracted_file" to folder "Saved_as_files".
			in_stream.open("temp/extracted_file");
			out_stream.open(path_to_Saved_as_files);
			for(int a = 0; a < name_length; a++) {in_stream.get(garbage_byte);}
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;) {out_stream.put(garbage_byte); in_stream.get(garbage_byte);}
			in_stream.close();
			out_stream.close();
			
			//Saves substance from file "extracted_file" to file "Saved_as_text" where each line is dated.
			in_stream.open("temp/extracted_file");
			out_stream.open("Saved_as_text", ios::app);
			for(int a = 15; path_to_Saved_as_files[a] != '\0'; a++) //..........Just for date.
			{	out_stream << path_to_Saved_as_files[a];
			}
			out_stream << "___";
			
			for(int a = 0; a < name_length; a++) {in_stream.get(garbage_byte);}
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;)
			{	if     ( garbage_byte ==   9)  {out_stream << " \\t "     ;}
				else if( garbage_byte ==  10)  {out_stream << " \\n "     ;}
				else if( garbage_byte ==  13)  {out_stream << " \\r "     ;}
				else if((garbage_byte  >  31)
				     && (garbage_byte  < 127)) {out_stream << garbage_byte;}
				else                           {                           }
				
				in_stream.get(garbage_byte);
			}
			out_stream << "\n";
			in_stream.close();
			out_stream.close();
			
			files_saved++;
		}
	}
}
