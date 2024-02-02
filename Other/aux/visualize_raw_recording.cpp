//Displays recorded raw audio file that is to be decoded by LED.cpp and aux.cpp.
//Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.

#include <fstream>
#include <iostream>
using namespace std;

int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	in_stream.open("untitled.raw");
	out_stream.open("VISUALIZATION.txt");
	if(in_stream.fail() == true) {cout << "\nMissing your file \"untitled.raw\"\n"; return 0;}
	char temp_file_byte;
	in_stream.get(temp_file_byte);
	for(; in_stream.eof() == false;)
	{	in_stream.get(temp_file_byte);
		
		//..........See this filter?
		if(temp_file_byte > 95) {out_stream << "#";}
		else                    {out_stream << " ";}
	}
	in_stream.close();
	out_stream.close();
	
	cout << "\nCreated file \"VISUALIZATION.txt\"\n";
}
