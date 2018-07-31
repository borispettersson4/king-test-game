King game test submission 	July 30th, 2018

Crush Miner by Boris Ruiz Pettersson 
email : borispettersson4@gmail.com
cell  : +1-787-407-5043

Project Started  : 24/07/2018
Project Finished : 30/07/2018 

File Contents -----------------------------------------

	- Game : Folder containing the executable of the latest build of the Crush Miner game as well as it's assets and .dll files.

	- Project: Folder containing the entire project built using the provided libraries and original code with Visual Studio 2017.

Game Description --------------------------------------

	- The game consists of an 8x8 grid composed of randomly generated gems that the player can select and swap gems in order
	to re-arrange the board. 3 gems or more of the same type ordered horizontally or vertically are removed from the game and
	new gems are fall down from the top of the board that fall down to fill the gaps created. Swaps that are made by the player
	that does not result in a match will cause the swapped gems to swap back to the original position. The player has 60 seconds
	per game session to collect the most points as possible. Multiple gems matched simutaniously result in more points for the
	player. 

	-The game consists of 3 screens. The title screen showing the title of the game, the main game that contains the core
	experience, and the score screen. The score screen shows the player's final score of the game session and compares it
	with the best score acheived from a game session and the option to play another game session. The best score resets upon 
	closing the program.

Controls ----------------------------------------------

	- When prompted, click anywhere on the screen to start the game in the intro screen.

	- Click on a gem to select a gem to move.

	- Click on the adjacent(top,bottom,left,right) of the selected gem to swap it's position

	- Drag on the direction of a desired gem to swap with the adjacent gem.

	- If the selected gem is not the desired gem, select a non-adjacent gem to make it the new selected gem.

	- When the game is finished, click anywhere on the screen to restart the game.
		
Design Choices ----------------------------------------

	- Game menu's are created and executed exclusively in the main.cpp

	- The main grid mechanic is composed of four components:

		Grid : contains an X amount of Columns
		Columns : contains an X amount of slots
		Slots : contains a reference to a Gem
		Gem : object containing gem textures and defined coordinates.

	- The Grid was designed with modularity in mind, thus it can be instantiated with an X by X configuration of the user's liking	
	and retain it's functionaltiy. For the purpose of this test, it has been instantiated in the main.cpp as a 8x8 grid.

	- Slots are designed to act as an abstract grid that contain the reference of the nearest gem and stores it's information
	rather than copying the entire object. This method saves more resources from memory and avoids unesessary instantiation.

	- Columns are the vertical configuration of Slots that are defined by the Grid. The columns are in charge of providing structure
	for the Slots that hold the gems in place and make sure that gems above a gap fall down and randomly generate a new gem on top. 

	- Gems that match vertically or horizontally with 3 or more gems sharing it's texture are placed in a queue for deletion and 
	are deleted one at a time per column. This was done to create a positive visual feedback on the player.

	- Gems that fall down on top of each other overlap their vertical space by 5 pixels to then move back to the original position.
	This was done to create the illusion that the gems are bouncing upon falling to improve visual feedback.

	- The STL Vector class was used as an array replacement solution to store the array Columns, Slots, and Gems.

	- The STL Chrono and clock_t class was used in the main.cpp to create the in-game timer.

Commentary ----------------------------------------------

	- The game Midas Miner Speed (the provided reference) was the main reference used in the creation of game mechanics 
	and presentation for the game.

	- The game should run indefinitely without any problems concerning memory. The Diagnostics Tool in Visual Stuido 2017
	was used to monitor changes in the heap and memory. This game was tested in a 15 minute session without anything to
	report from the memory or slow downs to the game's performance.

	- The code structure is as optimized and modular as it can be for practical functionality given the time frame. However, 
	with time or using this project for the future, further optimizations can be made to make the code more compact and add
	extra features.

	- There is one known issue that allows the player to perform multiple swaps at once and can only be triggered if the 
	user holds the mouse down and performs a circling motion on the grid for a short period of time. This can be fixed
	with aditional time and investigation as well with any other bugs that might occur in the future.

	- To modify the gameplay experience while openning the project in the main.cpp , you can do the following :

		1. Change the value of "gameTimeLimit" to extend or decrease the gameplay time.
		2. Change the value of "retryTimeLimit" to increase or decrease the waiting time to restart.
		3. Change the X and Y coordinates of the Grid to change it's position in the screen.
		4. Change the grid dimension value which is set to 8 to create a larger or smaller grid. Ex. 12 = 12x12 grid.
		5. Use Grid.setSpeed(x) to change the speed of gems falling down.

	- Any questions pertaining this test project may be addressed via given contact information.