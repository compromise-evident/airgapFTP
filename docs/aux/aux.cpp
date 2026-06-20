/*One-way FTP at 1.1kB/s using typical aux cord (3.5mm TRS).                    Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
Do "apt install sox" on both machines. */

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	//Checks if sox present.
	system("mkdir temp -p");
	char garbage_byte;
	system("sox --version > temp/sox_presence.txt");
	std::cout << "\033[2J\033[3J\033[1;1H"; //Clears screen, erasing history.
	in_stream.open("temp/sox_presence.txt");
	in_stream.get(garbage_byte);
	if(in_stream.eof() == true)
	{	std::cout << "\033[2J\033[3J\033[1;1H"; //Clears screen, erasing history.
		cout << "\nDo \"apt install sox\"\n";
		in_stream.close();
		return 0;
	}
	in_stream.close();
	
	cout << "\nSender? y/n: ";
	char user_option; cin >> user_option;
	if((user_option != 'y') && (user_option != 'n')) {cout << "\nInvalid.\n"; return 0;}
	
	
	
	
	
	//______________________________________________________Encode____________________________________________________//
	if(user_option == 'y')
	{	//Gets path (files & folders).
		std::cout << "\nDrop/enter file:\n";
		std::string path; std::getline(std::cin, path); if(path[0] == '\0') {std::getline(std::cin, path);}
		if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();} //Fixes path if drag-n-dropped.
		in_stream.open(path); if(!in_stream) {std::cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
		
		//Checks if file is empty.
		unsigned long long size = std::filesystem::file_size(path);
		if(size == 0) {std::cout << "\nEmpty file.\n"; return 0;}
		
		//Encodes.
		in_stream.open(path);
		out_stream.open("temp/encoded.raw");
		for(int a = 0; a < 176400; a++) {out_stream.put(127);} //..........4s silence (44100 * 4 = 176400.)
		int temp_file_byte_normal;
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
			for(int a = 0; a < 8; a++)
			{	if(binary[a] == 0)
				{	out_stream.put(-126); for(int a = 0; a < 6; a++) {out_stream.put(127);} //..........Spike, long  wait = 0
				}
				else
				{	out_stream.put(-126); for(int a = 0; a < 2; a++) {out_stream.put(127);} //..........Spike, short wait = 1
				}
			}
			
			in_stream.get(garbage_byte);
		}
		out_stream.put(-126); for(int a = 0; a < 100; a++) {out_stream.put(127);} //..........Spike, VERY LONG WAIT = end.
		for(int a = 0; a < 10000; a++) {out_stream.put(127);} //..........Ending-silence.
		in_stream.close();
		out_stream.close();
		
		//Convert raw audio (any file) to .wav using sox:
		system("sox -r 44100 -e unsigned -b 8 -c 1 temp/encoded.raw -t wav Send.wav");
		
		//Get length of .wav file in seconds using sox:
		system("sox Send.wav -n stat 2>&1 | grep 'Length' > temp/seconds.txt");
		
		//Sets volume to 75%.
		system("amixer -q set Master 75%");
		
		//Tells user # of seconds to enter on receiving machine.
		cout << "\nVolume set to 75%. Type \"";
		
		in_stream.open("temp/seconds.txt");
		for(int a = 0; a < 17; a++) {in_stream.get(garbage_byte);}
		for(int a = 0; a < 7; a++)
		{	in_stream.get(garbage_byte);
			if(garbage_byte != ' ') {cout << garbage_byte;}
		}
		in_stream.close();
		
		cout <<                                        "\" on receiving machine and leave it."
		     << "\nOpen Send.wav but play it while pressing enter on receiving machine.\n\n\n";
	}
	
	
	
	
	
	//______________________________________________________Decode____________________________________________________//
	if(user_option == 'n')
	{	cout << "Seconds to record: ";
		char seconds[100] = {0};
		cin >> seconds;
		
		//Creates sox command with "seconds".
		char sox_rec[10000] = {"rec -r 44100 -c 2 -b 8 -e unsigned-integer -t raw temp/recorded.raw trim 0 OVERWRITE_ME_IN_SECONDS"};
		int  sox_rec_command_bookmark = 75;
		for(int a = 0; seconds[a] != '\0'; a++)
		{	sox_rec[sox_rec_command_bookmark] = seconds[a];
			sox_rec_command_bookmark++;
		}
		sox_rec[sox_rec_command_bookmark] = '\0';
		
		//Records as raw audio using sox.
		system("sleep 2"); //..........Delays recording by 2s.
		system(sox_rec);
		
		//Decodes recording.
		in_stream.open("temp/recorded.raw");
		out_stream.open("Received");
		for(int a = 0; a < 100000; a++) //..........Skips first 100kB.
		{	in_stream.get(garbage_byte);
			if(in_stream.eof() == true)
			{	cout << "\n\n\nFile is too short.\n\n\n";
				in_stream.close();
				out_stream.close();
				return 0;
			}
		}
		
		char cache[3] = {'#', '#', '#'}; //..........Looks for " ##" string.
		for(; in_stream.eof() == false;)
		{	in_stream.get(garbage_byte);
			
			cache[0] = cache[1];
			cache[1] = cache[2];
			if(garbage_byte > 95) {cache[2] = '#';}
			else                  {cache[2] = ' ';}
			
			if((cache[0] == ' ')
			&& (cache[1] == '#')
			&& (cache[2] == '#')) {break;}
		}
		
		if(in_stream.eof() == true)
		{	cout << "\n\n\nNo substance detected.\n\n\n";
			in_stream.close();
			out_stream.close();
			return 0;
		}
		
		int binary[8]; //..........Decodes.
		int binary_write_bookmark = 0;
		for(int pound_counter = 0;;)
		{	//..........Reads until the next " ##" string and counts pound symbols.
			for(; in_stream.eof() == false;)
			{	in_stream.get(garbage_byte);
				
				cache[0] = cache[1];
				cache[1] = cache[2];
				if(garbage_byte > 95) {cache[2] = '#'; pound_counter++;}
				else                  {cache[2] = ' ';                 }
				
				if((cache[0] == ' ')
				&& (cache[1] == '#')
				&& (cache[2] == '#')) {break;}
			}
			
			//..........Silence of 38 or more pound symbols means no new bit-header is visible; this cuts the input stream early.
			if(pound_counter > 45) {break;}
			
			if(in_stream.eof() == true)
			{	cout << "\n\n\nRecording corrupted.\n\n\n";
				
				in_stream.close();
				out_stream.close();
				return 0;
			}
			
			//..........Retrieves one bit of data.
			if(pound_counter > 6) {binary[binary_write_bookmark] = 0;}
			else                  {binary[binary_write_bookmark] = 1;}
			
			//..........Resetting & updating.
			binary_write_bookmark++;
			pound_counter = 0;
			
			//..........Extracts one byte if data if binary[] is full.
			if(binary_write_bookmark == 8)
			{	binary_write_bookmark = 0; //..........Resetting.
				
				//..........Converts from 8 binary bits to an integer.
				int extracted_byte = 0;
				int place_value = 128;
				for(int a = 0; a < 8; a++)
				{	if(binary[a] == 1) {extracted_byte += place_value;}
					
					place_value /= 2;
				}
				
				if(extracted_byte < 128) {out_stream.put(extracted_byte      );} //..........Writes byte to file.
				else                     {out_stream.put(extracted_byte - 256);}
			}
		}
		in_stream.close();
		out_stream.close();
		
		std::cout << "\033[2J\033[3J\033[1;1H"; //Clears screen, erasing history.
		cout << "\nSee file \"Received.\"\n\n\n";
	}
}
