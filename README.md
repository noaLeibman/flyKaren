# Exercise 3 - Flight Simulator Controller

This is a program that connects to "FlightGear" flight simulator and interprets a text file with instructions to commands that activate the simulator.

## Installation

First install "FlightGear" on linux (through the software manager or command line).  
Make sure you have g++ compiler installed.  
After "FlightGear" is installed, add the XML file "generic_small.xml" to "Protocol" folder in the flightgear directory.  

## Usage
Open the terminal in the directory that contains the project files and compile using this command:

```bash
g++ *.cpp -pthread
```
Then run the executable with the following command:
```bash
./a.out <text_file_name_here.txt>
```
Then open "FlightGear" application and click on "fly" at the bottom left side. Make sure you have inserted these settings in the additional settings section:
```bash
--telnet=socket,in,10,127.0.0.1,5402,tcp
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
```


## Contributing
https://github.com/noaLeibman/flyKaren

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
Please make sure to update tests as appropriate.

