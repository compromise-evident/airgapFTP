/// LED - airgap FTP at 345B/s using                                            Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
///       LED & photoresistor.


//Do "apt install sox" on both machines.

#include <fstream>
#include <iostream>
using namespace std;

int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	//Checks if sox present.
	system("mkdir temp -p");
	char garbage_byte;
	system("sox --version > temp/sox_presence.txt");
	system("clear"); system("clear");
	in_stream.open("temp/sox_presence.txt");
	in_stream.get(garbage_byte);
	if(in_stream.eof() == true)
	{	system("clear"); system("clear");
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
	{	//Gets path to file from user.
		cout << "Drop/enter file:\n";
		
		//..........Gets path then fixes it if drag-n-dropped, regardless of single-quote presence and "enter"
		//..........not being cleared, meaning you can have options before this, where the user presses enter.
		char path_to_file[10000] = {'\0'};
		{	for(int a = 0; a < 10000; a++) {path_to_file[a] = '\0';}
			cin.getline(path_to_file, 10000);
			if(path_to_file[0] == '\0')
			{	for(int a = 0; a < 10000; a++) {path_to_file[a] = '\0';}
				cin.getline(path_to_file, 10000);
			}
			if(path_to_file[0] == '\0') {cout << "\nNo path given.\n"; return 0;}
			
			//..........Removes last space in path_to_file[].
			bool existence_of_last_space = false;
			for(int a = 9999; a > 0; a--)
			{	if(path_to_file[a] != '\0')
				{	if(path_to_file[a] == ' ') {path_to_file[a] = '\0'; existence_of_last_space = true;}
					break;
				}
			}
			
			//..........Removes encapsulating single-quotes in path_to_file[].
			bool existence_of_encapsulating_single_quotes = false;
			if(path_to_file[0] == '\'')
			{	for(int a = 0; a < 9999; a++)
				{	path_to_file[a] = path_to_file[a + 1];
					if(path_to_file[a] == '\0') 
					{	if(path_to_file[a - 1] != '\'') {cout << "\nBad path.\n"; return 0;}
						path_to_file[a - 1] = '\0';
						existence_of_encapsulating_single_quotes = true;
						break;
					}
				}
			}
			
			//..........Replaces all "'\''" with "'" in path_to_file[].
			int single_quote_quantity = 0;
			for(int a = 0; a < 10000; a++)
			{	if(path_to_file[a] == '\'') {single_quote_quantity++;}
			}
			
			if((single_quote_quantity                     >    0)
			&& (existence_of_last_space                  == true)
			&& (existence_of_encapsulating_single_quotes == true))
			{	if((single_quote_quantity % 3) != 0) {cout << "\nBad path.\n"; return 0;}
				
				for(int a = 0; a < 9997; a++)
				{	if(path_to_file[a] == '\'')
					{	int temp = (a + 1);
						for(; temp < 9997; temp++)
						{	path_to_file[temp] = path_to_file[temp + 3];
						}
					}
				}
			}
		}
		
		//Checks if file exists (failure can be bad path info as well.)
		in_stream.open(path_to_file);
		if(in_stream.fail() == true) {in_stream.close(); cout << "\n\nNo such file or directory.\n";             return 0;}
		char sniffed_one_file_character;
		in_stream.get(sniffed_one_file_character);
		if(in_stream.eof() == true) {in_stream.close();  cout << "\n\nNothing to process, the file is empty.\n"; return 0;}
		in_stream.close();
		
		//Encodes. (An opposite-bit is appended to each data-bit so LED brightness remains constant!)
		in_stream.open(path_to_file);
		out_stream.open("temp/encoded.raw");
		for(int a = 0; a < 11025; a++) //..........4s of '1' bits: 1s to normalize LED brightness, 3s for timing tolerance. (176400 / 16 = 11025.)
		{	out_stream.put(-1); for(int a = 0; a < 5; a++) {out_stream.put(127);} //..........Spike, short wait
			out_stream.put(-1); for(int a = 0; a < 9; a++) {out_stream.put(127);} //..........Spike, long  wait = 1
		}
		
		out_stream.put(-1); for(int a = 0; a < 9; a++) {out_stream.put(127);} //..........Spike, long  wait
		out_stream.put(-1); for(int a = 0; a < 5; a++) {out_stream.put(127);} //..........Spike, short wait = 0     Signifies data beginning.
		
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	//..........Converts file byte to (0 to 255.)
			int temp_file_byte_normal = garbage_byte;
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
			
			//..........Writes 1 byte based on binary[].
			for(int a = 0; a < 8; a++)
			{	if(binary[a] == 0)
				{	out_stream.put(-1); for(int a = 0; a < 9; a++) {out_stream.put(127);} //..........Spike, long  wait
					out_stream.put(-1); for(int a = 0; a < 5; a++) {out_stream.put(127);} //..........Spike, short wait = 0
				}
				else
				{	out_stream.put(-1); for(int a = 0; a < 5; a++) {out_stream.put(127);} //..........Spike, short wait
					out_stream.put(-1); for(int a = 0; a < 9; a++) {out_stream.put(127);} //..........Spike, long  wait = 1
				}
			}
			
			in_stream.get(garbage_byte);
		}
		
		//'0' end-of-stream (extra long wait.)
		out_stream.put(-1); for(int a = 0; a <   9; a++) {out_stream.put(127);} //..........Spike, long  wait
		out_stream.put(-1); for(int a = 0; a < 45000; a++) {out_stream.put(127);} //..........Spike, VERY LONG WAIT = end
		in_stream.close();
		out_stream.close();
		
		//Convert raw audio (any file) to .wav using sox:
		system("sox -r 44100 -e unsigned -b 8 -c 1 temp/encoded.raw -t wav Send.wav");
		
		//Get length of .wav file in seconds using sox:
		system("sox Send.wav -n stat 2>&1 | grep 'Length' > temp/seconds.txt");
		
		//Sets volume to 75%.
		system("amixer -q set Master 100%");
		
		//Tells user # of seconds to enter on receiving machine.
		cout << "\nVolume set to 100%. Type \"";
		
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
		
		for(; in_stream.eof() == false;) //..........Finds first garbage header '1'.
		{	if(garbage_byte <= 95) {break;}
			in_stream.get(garbage_byte);
		}
		if(in_stream.eof() == true)
		{	cout << "\n\n\nNo noise detected.\n\n\n";
			in_stream.close();
			out_stream.close();
			return 0;
		}
		
		char cache[3] = {'#', '#', '#'}; //..........Looks for " ##" string.
		for(int a = 0; a < 20; a++)
		{	in_stream.get(garbage_byte);
			if(in_stream.eof() == true)
			{	cout << "\n\n\nRecording is too short.\n\n\n";
				in_stream.close();
				out_stream.close();
				return 0;
			}
			
			cache[0] = cache[1];
			cache[1] = cache[2];
			if(garbage_byte > 95) {cache[2] = '#';}
			else                  {cache[2] = ' ';}
			
			if((cache[0] == ' ')
			&& (cache[1] == '#')
			&& (cache[2] == '#')) {break;}
			
			if(a == 19)
			{	cout << "\n\n\nRecording corrupted.\n\n\n";
				in_stream.close();
				out_stream.close();
				return 0;
			}
		}
		
		int temp_pound_counter = 0; //..........Identifies next bit.
		for(int a = 0; a < 20; a++)
		{	in_stream.get(garbage_byte);
			if(in_stream.eof() == true)
			{	cout << "\n\n\nRecording is too short.\n\n\n";
				in_stream.close();
				out_stream.close();
				return 0;
			}
			
			cache[0] = cache[1];
			cache[1] = cache[2];
			if(garbage_byte > 95) {cache[2] = '#'; temp_pound_counter++;}
			else                  {cache[2] = ' ';                      }
			
			if((cache[0] == ' ')
			&& (cache[1] == '#')
			&& (cache[2] == '#')) {break;}
			
			if(a == 19)
			{	cout << "\n\n\nRecording corrupted.\n\n\n";
				in_stream.close();
				out_stream.close();
				return 0;
			}
		}
		
		if(temp_pound_counter < 12) //..........Skips the appended opposite bit if current bit is '1'.
		{	for(int a = 0; a < 20; a++)
			{	in_stream.get(garbage_byte);
				if(in_stream.eof() == true)
				{	cout << "\n\n\nRecording is too short.\n\n\n";
					in_stream.close();
					out_stream.close();
					return 0;
				}
				
				cache[0] = cache[1];
				cache[1] = cache[2];
				if(garbage_byte > 95) {cache[2] = '#';}
				else                  {cache[2] = ' ';}
				
				if((cache[0] == ' ')
				&& (cache[1] == '#')
				&& (cache[2] == '#')) {break;}
				
				if(a == 19)
				{	cout << "\n\n\nRecording corrupted.\n\n\n";
					in_stream.close();
					out_stream.close();
					return 0;
				}
			}
		}
		
		bool permission_to_read_data = false; //..........Decodes.   Helps find zero signifying data stream beginning.
		int binary[8];
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
			
			//..........Skips the appended opposite bit.
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
			{	cout << "\n\n\nRecording corrupted.\n\n\n";
				
				in_stream.close();
				out_stream.close();
				return 0;
			}
			
			//..........Silence of 50 or more pound symbols means no new bit-header is visible; this cuts the input stream early.
			if(pound_counter > 50) {break;}
			
			//..........Tests if the zero data header is found.
			if(permission_to_read_data == false)
			{	if(pound_counter > 12)
				{	permission_to_read_data = true;
					pound_counter = 0;
					continue;
				}
				else
				{	pound_counter = 0;
					continue;
				}
			}
			
			//..........Retrieves one bit of data.
			if(pound_counter > 12) {binary[binary_write_bookmark] = 0;}
			else                   {binary[binary_write_bookmark] = 1;}
			
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
				
				//..........Writes byte to file.
				if(extracted_byte < 128) {out_stream.put(extracted_byte      );}
				else                     {out_stream.put(extracted_byte - 256);}
			}
		}
		in_stream.close();
		out_stream.close();
		
		system("clear"); system("clear");
		cout << "\nSee file \"Received.\"\n\n\n";
	}
}
