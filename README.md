# SPACE BATTLE

## **Introduction** 

+ Name: Hoàng Duy Thịnh - K68J - UET
+ Student ID: 23020708 
+ Major Project: Space Battle (INT2215_52 - Advanced Programming) 

# Introducing the game

Space Battle is an action game. In this game, players control a spaceship and use weapons and various tactics to shoot down enemies to achieve the longest survival time and the highest number of eliminated enemies.

- The game includes full support functions for players to exit the game, restart the game, game instructions. Besides using basic keyboard and mouse controls, players can also use controllers for the gaming experience, use ESC key to pause the game...

- Features dynamic sound effects that describe the game's functions and actions.
- Video demo of gameplay & general source code explanation: [Game Demo Link](https://www.youtube.com/watch?v=98tJ5wg-Tzo)
- (Additional) Video of pure gameplay experience: [Additional Link](https://www.youtube.com/watch?v=ivZyJ3Bxwww)

- [A. Ways to download game](#a-ways-to-download-game)
    * [1. Method 1: No code included.](#1-method-1-no-code-included)
    * [2. Method 2: Include code and compilable.](#2-method-2-include-code-and-compilable)
- [B. Instructions and Start Game](#b-instructions-and-start-game)
- [C. End Game](#c-end-game)
- [D. Components In Game](#d-components-in-game)
- [E. Skill Items In Game](#e-skill-items-in-game)
- [F. Supplement](#f-supplement)
- [Source code & Reference source](#source-code--reference-source)
- [Development & Conclusion](#development--conclusion)

# A. Ways to download game

## 1. Method 1: No code included.

Download the game (compressed as .zip) from this repository.

Extract the game to a folder and run run.exe to start playing.

## 2. Method 2: Include code and compilable.

**Step 1:** Clone this repository to **Visual Studio Code** environment: [Repository Link](https://github.com/mrthinh307/TankGme)

![image](./images/Readme/repo.png)

**Step 2:** Open **Terminal** and navigate to the game folder (you can use the **Ctrl + Alt + N** key combination), type **make** then press **Enter**, wait about 10 seconds and enjoy the game.

![image](./images/Readme/makefile.png)

# B. Instructions and Start Game

- After successfully opening the game, the game's waiting screen will appear:
![image](./images/Backgrounds/menu.jpg)

**1. PLAY**

- When the player clicks the **PLAY** button - confirming participation in the game, the screen will guide the player to the control function selection section.

- The game provides players with 2 choices for spaceship control functions:
    + **Keyboard and Mouse**.
    + **Controller (Xbox, PS4, PS5...)** (below is the control guide for **Xbox** family controllers, other controllers operate similarly). For controllers that support vibration features, I have also configured the **controller vibration** effect for 500ms when **colliding** with enemies.
    ![image](./images/Readme/rumble.png)

### *Control + Shoot* 

| Control | Keyboard | Gamepads | 
|---------|----------|----------|
| UP      |     W    |Joysticks |
| DOWN    |     S    |Joysticks |
| LEFT    |     A    |Joysticks |
| RIGHT   |     D    |Joysticks |

|  Shoot  | Mouse    | Gamepads | 
|---------|----------|----------|
| Normal  |Left Mouse|    (A)   |
| Ultimate|Right Mouse|   (B)   |

- Players choose their preferred control function by clicking on the **description bar** of that function:

- ENTER GAME

- Players will control the character that appears in the center of the screen:

![image](./images/Readme/tank.png)

**2. EXIT**

- When the player clicks the **EXIT** button - the game window closes and the game ends.

**3. ACHIEVEMENT** - Save function
- This function saves records of the number of enemies the player has defeated in one game session.
- The **LEVEL** function represents the game experience that the player has accumulated. Will level up when the Gold that the player accumulates through gaming sessions reaches 500.
- The update function **completely upgrades the appearance** of the Spaceship when leveling up. All spaceships have vivid **animated** sparkling light effects.
![image](./images/Readme/achieve.png)

# C. End Game
- Records achievements after a game session that the player achieved: 
+ Number of enemies the player defeated.
+ Amount of gold collected.
+ Survival time.
![image](./images/Readme/endgame.png)

# D. Components In Game

- Spaceship Object ![image](./images/Readme/tank.png): The object that the player controls 

- Mini Enemy ![image](./images/Readme/minienemy.png): Small enemy objects, **will add 1 object every 15s, no addition during boss existence time**.

- ***Boss*** ![image](./images/Readme/boss.png): Strong enemy object. Will reappear every 60s.

    - ***Boss Health Bar***![image](./images/Readme/0.png): Boss's health bar, decreases by 1 health unit when boss is hit by **Normal** bullets and 2 health units when hit by **Ultimate**.
    
- ***Timer*** ![image](./images/Readme/timer.png): Records the player's survival time.

- ***Killed Enemy Icon*** ![image](./images/Readme/killenemy.png): Records the number of enemies defeated by the player.

- ***Ultimate***(Rocket) ![image](./images/Backgrounds/rocket.png): Number of rockets the player has (increases by 1 after every 5 enemies defeated). Unlike normal bullets, rockets can penetrate enemies, except **Boss** but also deal higher damage to Boss.

- ***Heart***(Lives): ![image](./images//Backgrounds/heart.png): Number of spaceship lives (-1 when colliding with enemies / hit by enemy bullets).

- ***Controller Method***: Lets players know which control method they are using! Keyboard icon ![image](images/Readme/keyboard.png) means **Mouse and Keyboard** method, controller icon ![image](images/Readme/gamepad.png) means **Controller** method.

- ***Pause Button***: If you want to pause the game or restart while in the game, players can press **ESC**, the game window will show the Settings page:

![image](./images/Backgrounds/setting0.png)
- Click on **HOME** to return to the initial MENU window. Players can click PLAY to restart.
- Click on **RESUME** to continue the paused game.

- And some other components...

- Basic game layout:

![image](./images/Readme/coban.png)

- If you're wondering what those colorful icons appearing in the middle of the game screen above are? Those are features that help players enjoy a comfortable experience with over 20 skills (with future development potential) for the main character. All skills come with appropriate visual effects and sound.

![image](./images/Readme/expng.png)
- Example: Skill that binds and stuns enemies

# E. Skill Items In Game

Attack enemies with bullets or use skills, don't let enemies or enemy bullets touch the spaceship. If touched, the number of lives will decrease by 1 (bottom left corner of the game window). By default, when starting the game, players have 3 lives.

The game ends when the player's lives reach **0**.

## 1. Some Skills

Skill icons appear randomly with random probability after defeating enemies (may or may not appear). Players move the spaceship to touch the icon to automatically activate the skill:

|                                                                             | Name	     | Function                                                                                                                    |
|-----------------------------------------------------------------------------|--------------|------------------------------------------------------------------------------------------------------------------------------|
| <img src="images/Utils/gift/4dan.png" width=50>  | Straight Beam	  | Bullet path changes to a beam of 4 straight bullet columns (30s).                                                                                             |
| <img src="images/Utils/gift/booster.png" width=50>    | Booster	   | Doubles the spaceship's speed (10s).                                                                                              |
| <img src="images/Utils/gift/dan4phia.png" width=50>          | Four-Way Shot	    | Bullets shoot from 4 sides of the spaceship, each 90 degrees apart (30s).                                                    |
| <img src="images/Utils/gift/danloang.png" width=50>        | Spread Shot 	    | Bullets shoot in 3 diagonal directions from the front of the spaceship (30s). |
| <img src="images/Utils/gift/default.png" width=50> | Default Mode  | Returns spaceship to default mode, removes all current skills, disables ability to activate new skills (10s).                                                               |
| <img src="images/Utils/gift/hp.png" width=50>  | HP	 | Immediately adds one life to the spaceship.      
| <img src="images/Utils/gift/new1.png" width=50>  | Green Diamond Bullet	 | Spaceship bullets are upgraded in stats / converted to new form.      
| <img src="images/Utils/gift/new2.png" width=50>  | Ring Bullet	 | Spaceship bullets are upgraded in stats / converted to new form.  
| <img src="images/Utils/gift/phitieu.png" width=50>  | Dart | Spaceship bullets are upgraded in stats / converted to new form.  
| <img src="images/Utils/gift/plusrocket.png" width=50>  | Add Rocket	 | Number of Rockets (Ultimate) is increased by a random number <10.  
| <img src="images/Utils/gift/preventenemy.png" width=50>  | Magnet	 | The magnet in space will attract all existing skills on the game screen to the player's spaceship object (30s).  
| <img src="images/Utils/gift/rocket2.png" width=50>  | Upgrade Rocket	 | The spaceship's Rocket (Ultimate) ability is upgraded to a new form - faster and with wider area damage.                                                            |
| <img src="images/Utils/gift/shield.png" width=50>  | Shield	 | Activates divine protection, disables collision with enemies (10s).                                                            |
| <img src="images/Utils/gift/stunned.png" width=50>  | Stun 	 | Binds enemies, causes stun and inability to move (5s).                                                         |
| <img src="images/Utils/gift/superbullet.png" width=50>  | Super Bullet | As the name suggests, the bullet path is incredibly magical =)).                                                            |
| <img src="images/Utils/gift/teleport.png" width=50>  | Teleport	 | As the name suggests, a random position in the game window is selected and the spaceship will teleport to that position.                                                            |
| <img src="images/Utils/gift/ziczac.png" width=50>  | Trap Bullet	 | Bullets shot will rotate in place, creating traps that enemies run into.                                                            |
| <img src="images/Utils/gift/treasure.png" width=50>  | Ruby Icon	 | Players collect rubies to accumulate experience.                                                            |

- And some other interesting skills that players will experience when participating in the game.
- The item drop rate when defeating enemies is 50%, items will be randomly selected. All configured skills include animations and dynamic sound effects.
- After appearing, skill icons will shatter (disappear) if after a set default time period or when enemies collide with them.

# F. Supplement

## See Also

### *Technologies Used*
- SDL2.0 library.

- Uses many classes, vectors, file separation, inheritance...

- Optimizes the creation of multiple objects by resetting random positions of enemies moving from the 4 sides of the screen after being defeated, enemy bullets are handled similarly.

- Applies mathematical knowledge to calculate rotation angles and enemy movement toward the player without overlapping each other. Sets enemy bullet paths to aim relatively toward the spaceship, creating difficulty and surprise while maintaining game balance. Calculates movement and appearance for spaceship bullets, contributing to unique shooting skills.

- Handles time, mouse and keyboard operations, controllers, sound, animated images, text. Manages addresses and memory when working with variables like pointers... avoiding memory loss and leaks.

- Creates menus, pause game features, game restart, record keeping, saves necessary statistics to create Level features and unlock new spaceships, handles button presses for navigation between menus.

- Handles mouse, keyboard, controller events, controller vibration function (if available).

### Source code & Reference source

#### 1. Source code:
- Presented through game demo video.
#### 2. Reference sources:
- How to use and install SDL2.0 on VSCODE and CodeBlock environments.

- How to use SDL2.0 library, program management: Referenced from lazyfoo and videos by Ms. Tran Thi Minh Chau, Stack Overflow, YouTube channels: Software Development AZ123, codegopher, Let's Make Games,...

- Images: Google search combined with self-design.
- Sound: Google search.

# Development & Conclusion

## Development Direction:

- Adjust game difficulty: Players can choose the initial number of enemies that appear. Not only can players eat the dropped skills, but enemies can also consume those skills, appropriate to the enemy object and update that skill feature to the enemy, making the game more interesting.

- Update leaderboard feature, after each game session players will be asked to enter their name to save their game results.

- Develop Multiplayer feature:
    + 2 PLAYERS VERSUS ENEMY (Compete for number of enemies defeated or survival time (with collision handling between 2 players) / Same team (no collision handling))
    + PLAYER 1 VS PLAYER 2 (Set up blood_bar like boss, handle collisions, eat skills and fight each other.)

- Update more new skills.

## After nearly 2 months of making this game for the major project:

- I feel I have improved many skills in algorithmic thinking and coding, ideation ability, planning and step-by-step execution.

- Learned how to setup environment, use external libraries. Memory management with address variables, pointers, dynamic allocation...

- Applied knowledge from various university subjects into the program.

- Learned how to perform individual tasks, explore and learn from many sources of materials.

**The end!**

***THANKS FOR READING MY README.***
