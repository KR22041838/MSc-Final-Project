# MSc-Final-Project
#                                             ‘Randy the rabbit’


My thesis is part of a project to develop a horror arcade game featuring an animatronic games master instead of the typical screen-based setup.

The horror in the project comes from the game-master robot innocently asking you to play and then forcing you to continue to play, and only winning the difficult memory game sets you free.

The project draws inspiration from retro arcade games and the popular game franchise 'Five Nights at Freddy’s'. My game will have a creepy animatronic character, Randy the Rabbit, who’s designed to create an eerie atmosphere similar to the unsettling atmosphere of Freddy’s characters.
Figure 1.1 Image of ‘Five Night’s At Freddy’s’ Animatronic Characters. [34], Eye mechanism, Robot. 

The animatronic I have made is an early-stage Arduino-based prototype of games-master 'Randy the Rabbit. Made of papier-mâche, servo motors, wooden dowel and a 3D printed articulated eye mechanism that I have designed and developed over the course of the project.

I had a lot of issues along the way with designing the eye mechanism as the separate servos powering the Up/Down and Left/Right motions will move independently but when combined they interfere with each other and put too much tension on the mechanism, breaking it. The current mechanism is very delicate but works and I am happy with how the final eye movement looks. 

Another issue I’ve been having with the Arduino circuit is feedback from the servos the joysticks will rotate the two eye servos and one eyebrow servo efficiently however the final eyebrow servo will only work in time with adjacent’s eyebrow for a limited amount of time before the feedback makes it continually jitter. I managed to get round this with code while filming footage by connecting the left/right eye movement and eyebrows to one joystick giving me a range of expression, however I could not use the full I articulation which was a shame. 

I also ran out of time trying to connect DF player into the circuit to allow Randy to talk through a speaker rather than through the laptop. 

Time was also not on my time when it came to making making Randy’s face. I was originally going to sculpt it in blender and 3D print it, however I did not have time to learn how to use the program to a high enough standard to do it. I then sculpted the face out of clay and with the intention of 3D scanning with Kiri Engine and 3D print. This brought many logistical difficulties with defining the final CAD model from the scan and I did not have time to fix it. I settled on using papier-mâche and used the clay sculpture as a mould. I also experimented with making latex skin for the robot which created an interesting effect but as I was going to paint the papier-mâche further experiments with the latex would not be time efficient.

I am happy with how the robot face came out but I think it will be cool to incorporate movable latex skin onto the robot in future iterations to see how it enhances the creepiness/disgust factor. 

When designing Randy I researched into uncanny valley which states that realistic but not quite human eyes and eyebrows expression is one of the main factor in creating the uneasy uncanny valley feeling you get when looking at a robot. Therefore I focused on creating fully articulated, human-like eyes and expressive eyebrows for the robot to create Randy’s unsettling look.

For the final arcade game I want to create an ‘alternative controller’ that requires manipulation and fine motor skills to operate. Since the Rubik’s cube has these features, it will act as a stand in controller for this project. 

During the experiment I found evidence of the CASA paradigm where people apply human social rules to interacting with  robots. But I did not find evidence the Mood contagion phenomenon which describes how people take on and mirror the mood of those around them (including robots). 

I found during the experiments negative encouragement establishes a competitive, high-pressure environment, giving the robot a frustrating yet amusing persona for interaction and made the player question their memory and skill. The positive encouragement fosters a friendly and motivating atmosphere, characterized by a likeable and supportive robot persona and a false sense of confidence in their performance. 

In future experiments I would like to build upon these psychological findings and the physical mechanics of the arcade game to balance difficulty with entertainment, engagement and stress allowing for player manipulation by the Games-master. 


# Final Codes: 

# Final_Expression_Code:
MSc-Final-Project/Randy The Rabbit Code/Final_Expression_Code/Final_Expression_Code.ino at main · KR22041838/MSc-Final-Project (github.com) 

This 'Final Expression Code' controls the animatronic eyes of games-master 'Randy the Rabbit' to rotate about the x and y axis, to give fully articulated eye motion and is controlled using a joystick. A second joystick controls the rotation of the eyebrows. 

This code has issues with feedback connecting to the 4th 'eyebrow' servo, the code will work initially to give full control over the facial expression of the animatronic, however after a minuet of so the eyebrow connect to servo 'ebServo2' will start to jitter, rotate on its own or stop rotating at all.

I have not managed to fix this in time so the code used for the exhibition has been adapted to get round this issue. See code: Expression_Exhibition_Code. 


# Expression_Exhibition_Code:
MSc-Final-Project/Randy The Rabbit Code/Expression_Exhibition_Code at main · KR22041838/MSc-Final-Project (github.com) 

 This is the code to be used in the exhibition environment and when filming footage to the 
 animatronic games-master Randy the Rabbit working. This code has been adapted to overcome 
 the servo feedback issues I was having in the Final_Expression_Code. 

 To get round this issue, I have combined the motion of the eyes and rotation of the eyebrows,
 assigning it to one joystick instead of being controlled by two separate joysticks. 
 
 This means I have had to drop the rotation about the x axis for the eyes meaning they 
 only rotate left to right. However it has fixed the issues I was having with the eyebrow servo
 jittering and rotating incorrectly. 

 The reduction of the x axis motion reduces the overall effectiveness of the animatronics facial 
 expression and I will be looking to bring this back in, in the future. However it is suitable
 for exhibition purposes. 


# Expression_Audio_Combined_Code:
MSc-Final-Project/Randy The Rabbit Code/Expression_Audio_Combined_Code/Expression_Audio_Combined_Code.ino at main · KR22041838/MSc-Final-Project (github.com) 

This is the code to be expands upon Final_Expression_Code for the Animatronic games-master 
'Randy the Rabbit'. This code integrates a third joystick, a DFplayer and speaker into the existing code to give Randy a speaking voice. 
 
The code is a work in progress and currently unfinished, but the aim is to replace the Final_Exhibition_Code with this to create an expressive, talking robot who can react to the players game performance. The three elements of eyebrow expression, eyes movement and talking audio will be controlled by three corresponding joysticks. 
