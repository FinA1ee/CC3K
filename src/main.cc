#include "floor.h"
#include "hero.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]) {
  string race;
  int floor;
  bool isDead = false; // Whether the hero is dead
  bool isRead = false; // Whether a floor file is provided
  ifstream floorFile;
  Floor f;  // Create a floor object
  
  if(argc == 2){isRead = true;}  // Indicate there is a command line option	

  while(true){
	cout << "Please select a race. Press q to quit" << endl;	
	Hero *myHero = nullptr;
	while(true){
	  // Promopt the user to selece a race 
	  cin >> race;
	  if (race == "s" || race == "t" || 
	    race == "d" || race == "v" || race == "g"){
	      if (race == "s")  myHero = new Hero(125, 25, 25, "Shade");
		  if (race == "d" ) myHero = new Hero(150, 25, 15, "Drow");
		  if (race == "v")  myHero = new Hero(50, 25, 25, "Vampire");
		  if (race == "t")  myHero = new Hero(120, 25, 15, "Troll");
		  if (race == "g")  myHero = new Hero(110, 15, 20, "Goblin");
		  break;
	  } else if (race == "q" || cin.eof()){
		  // Quit program
		  cout << "GAME OVER" << endl;
		  delete myHero;
		  return 0;
		}
	}
	f.setHero(myHero);    // Pass the pointer to floor 
	floor = 1;
	isDead = false;       // Reset death state
	string cmd;

	while(floor < 6){
	  if(floor != 1){f.clearBoard();}   // Clear the board every level
	  myHero->resetState();             // Reset Hero states
	  if(isRead){
	    floorFile.open(argv[1]);
		f.readFloor(floorFile,floor);
		floorFile.close();
	  } else {
		floorFile.open("emptyFloor.txt");
		f.readFloor(floorFile, 1);
		floorFile.close();
	    f.generateAll();
	  }
	  f.printFloor();
	  while(true) {
	    cin >> cmd;
		if(cmd == "u"){            // Use potion
 		  cin >> cmd;
	      f.heroTakePotion(cmd);
		  f.checkAround();
		  f.printFloor();
		  if(myHero->isDead()){isDead = true;break;}
		  continue;
		}
				
	    if(cmd == "a"){			   // Attact enemy
		  cin >> cmd;
		  f.heroAttack(cmd);
		  f.checkAround();
		  if(myHero->isDead()){isDead = true; break;}
		  f.printFloor();
		  continue;
		}
				
		if(cmd == "f"){		
		  f.frozeEnemy();
		  f.printFloor();
		  continue;
		}
				
		if(cmd == "r"){            // Restart and display score
 		  f.displayScore();
		  break;
		}
				
		if(cmd == "q"){	           // Admit defeat and quit, display score
		  f.displayScore();
		  cout << "GAME OVER" << endl;
		  delete myHero;
		  f.clearBoard();
		  return 0;
		}
				
		else{					   // Normal move
		  f.heroMove(cmd,false);
		  if(f.reachStair()) {floor++;break;}
		  f.checkAround();
		  if(myHero->isDead()){isDead = true; break;}
		  f.printFloor();
		}
	  }
	  if(cmd == "r"){break;}   
	  if(isDead){break;}		  
    }
 	if(cmd == "r"){
	  delete myHero;
	  f.clearBoard();
	  continue;
	}
	if(isDead){
	  string cmd;
	  f.displayScore();
	  cout << "Sorry, You are defeated." << endl;
	  cout << "Press R to restart, Q to quit." << endl;
	  cin >> cmd;
	  if(cmd == "r"){
		delete myHero;
		isDead = false;
		f.clearBoard();
		continue;
	  }
	  if(cmd == "q"){
		delete myHero;
		f.clearBoard();
		break;
	  }
	}
	else {
	  cout << "Congratulartions! You Win! Enjoy Freedom!" << endl;
	  f.clearBoard();
	  continue;
	} 	// Win after reach end of 5th floor
  }
}
	
	
	
	
	
	
	