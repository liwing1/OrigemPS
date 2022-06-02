# Origem Selective Process!

## Implemented Features:
 - Classes:
   - Battery:
     - Stores the SoC value, UID and which Host it is attatched with.
			
   - Motorcycle:
     - Stores the value of Speed, Plate, and its current state (accelerating, braking, or stand by).
     - When attatched to a battery, it can accelerate up to a maximum of 60km/h
     - It can change their own speed, and the battery SoC.

   - Charging Point (CP):
     - Stores its own state and which battery it is associated with.
     
   - Battery Exchange Station (ETB):
     - Manages the charging of CPs, attatching and releasing new batteries.
     - They increase SoC value of attatched batteries after charge starts up to 100%.
    
    - Host:
      - Abstract Class for Motorcycle and CP.

 - Simulation:
   - The route of the motoboy was simulated using a state machine that progresses according to the challenge instructions.
   - If the state machine is in a state transition the simulation does not perform the dynamic model processing.
   - Every 10 seconds the Motorcycle and ETB attribute information is printed on the screen.
  

## Program Compilation and Execution Instructions:
  - With g++ and Make installed run:
   
   ```
   $ make
   ```
  - It will generate a file called ```a.out```.
  - To execute the program just run:
   ```
   $ ./a.out
   ```
   
## Development Environment
  - C++ version used was 17.
  - The text editor used was Visual Studio Code running on Windows OS.
  - Compilation and execution of the program was done on WSL.
