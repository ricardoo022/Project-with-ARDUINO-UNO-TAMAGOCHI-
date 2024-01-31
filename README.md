# Project-with-ARDUINO-UNO-TAMAGOCHI-
When the Arduino is turned on, the Tamagotchi should consider itself just "born", starting to count the time.
• Every 4 minutes (more or less 60s, this margin being random), the pet needs to eat, which should be signaled by turning on the green LED. To satisfy this need, the user must press the corresponding button.
• Every 3 minutes (more or less 60s, this margin being random), the Tamagotchi needs attention, which should be signaled by turning on the yellow LED. To satisfy this need, the user must press the corresponding button.
• After 10 minutes of being awake (more or less 60s, this margin being random), or if the average of the last ambient light measurements is above 2/3 of the ADC range, (whichever happens first) the Tamagotchi should ask to put it to sleep, turning on the red LED. Once the sleep button is pressed, the Tamagotchi will sleep for 5 minutes, not generating any events during this period and resuming the normal routine after waking up (in both cases - sleeping and waking up
- you must print an informative message about the event).
• The pet's health status will be determined by a penalty counter. Penalties will be added according to the time it takes the user to satisfy Tamagotchi's demands, which are 5 points for each complete minute - however, if the user reacts during the first 15s after the notification, there must be a bonus (subtraction) of 5 points in this counter (if it is equal to zero it will remain zero).
• Every minute that passes, the value of the penalty counter must be printed.
The Tamagotchi will die if the total number of penalties exceeds 25 points, stopping the program from running - a message must be printed informing you when this happens.
To measure the average light intensity values, they must store a sample in a vector, every minute, taking the average of 6 samples.
