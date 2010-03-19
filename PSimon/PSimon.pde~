#include <Servo.h>
#include <PButton.h>
#include <PBuzzer.h>
#include <PDirector.h>
#include <PLed.h>
#include <PShifter595.h>
#include <PTask.h>
#include <PTimer.h>
#include <P7Segments.h>

// Pins
#define LED1_PIN 2
#define LED2_PIN 3
#define LED3_PIN 4
#define LED4_PIN 5

#define BUTTON1_PIN 8
#define BUTTON2_PIN 9
#define BUTTON3_PIN 10
#define BUTTON4_PIN 11

#define S595CLOCK_PIN 6
#define S595LATCH_PIN 7
#define S595DATA_PIN 14

#define BUZZER_PIN 12

#define SERVO_PIN 16

// Other definitions
#define NCOLORS 4
#define MAXSTEPS 100
#define DEBOUNCINGMILLIS 10

#define WAITINTERSTEPS 50
#define WAITINTERSERIES 200
#define WAITFORNEXTGAME 5000

#define MIN_SERVO 179
#define MAX_SERVO 1

// 7 segment animation while the user is listening
#define PLAYCOUNT 6
#define ANIMATIONTIMER 175
byte playAnimation[] = {B00000001, B00000010, B00000100, B00001000, B00010000, B00100000};

// Countdown to guess a step
#define COUNTDOWNCOUNT 7
// This could be configurable
int countDownStep = 200;
byte countDownAnimation[] = {B01111111, B00111111, B00101111, B00100111, B00100011, B00100001, B00100000};

int tones[NCOLORS] = {1915, 1700, 1519, 1432};

// Object creation
PButton* buttons[NCOLORS];
PLed* leds[NCOLORS];

PLed led1(LED1_PIN), led2(LED2_PIN), led3(LED3_PIN), led4(LED4_PIN);
PShifter595 shifter(S595CLOCK_PIN, S595LATCH_PIN, S595DATA_PIN);

PButton b1(BUTTON1_PIN, DEBOUNCINGMILLIS), b2(BUTTON2_PIN, DEBOUNCINGMILLIS), b3(BUTTON3_PIN, DEBOUNCINGMILLIS), b4(BUTTON4_PIN, DEBOUNCINGMILLIS);
// Timer for the waiting state
PTimer timer;
// Timer to wait some timer at the end of game
PTimer finalTimer;
PBuzzer buzzer(12);
PTask *tasks[8];
P7Segments counter(&shifter);
PDirector director(tasks, 8);

Servo servo;
byte servopos;

byte steps[MAXSTEPS];
int currStep = 0;
int playingStep = 0;

int stepLength = 400;

// Pointer to function to return after PlayNextStepState
void *onExitTimer;

// Not a define but a variable
// Just in case we want to setup it in anyway at the beggining
boolean bUseServo = false;

void setup()
{
  if (bUseServo)
    servo.attach(SERVO_PIN);
  
  leds[0] = &led1;
  leds[1] = &led2;
  leds[2] = &led3;
  leds[3] = &led4;
  
  buttons[0] = &b1;
  buttons[1] = &b2;
  buttons[2] = &b3;
  buttons[3] = &b4;
  
  for (int i = 0; i < NCOLORS; i++)
    director.AddTask(buttons[i]);  

  director.AddTask(&timer);
  director.AddTask(&buzzer);
  director.AddTask(&counter);
  director.AddTask(&finalTimer);

  for (int i = 0; i < NCOLORS; i++)
    leds[i]->Setup();

  shifter.Setup();
  director.Setup(RestartState);
}

void loop()
{
  director.Loop();
}

// Preparation for new game.
// Executed just once to clear data for new game and jump to InitialState
void *RestartState()
{
  if (bUseServo)
    servo.write(MIN_SERVO);
  
  counter.SendData(B10000000);
  
  // All leds high
  for (int i = 0; i < NCOLORS; i++)
    leds[i]->GoHigh();

  // No steps
  currStep = 0;
  return (void *)InitialState;
}

// Returns the index of the first button pressed or -1 if none
int FirstButtonPressed()
{
  for (int i = 0; i < NCOLORS; i++)
    if (buttons[i]->GoneHigh())
      return i;
  return -1;
}

// Waits until some button is pressed and starts a new game
void *InitialState()
{
  if (FirstButtonPressed() != -1) {
    randomSeed(millis());
    AddStep();
    for(int i = 0; i < NCOLORS; i++)
      leds[i]->GoLow();
    return (void *)PlayNextStepState;
  }
  
  return (void *)InitialState;
}

// Adds a step to the game
void AddStep()
{
  if (bUseServo)
    servo.write(MIN_SERVO);
    
  steps[currStep++] = random(NCOLORS);
  playingStep = 0;
  counter.SendData(playAnimation, PLAYCOUNT, ANIMATIONTIMER, true);
}

// Plays the next step and waits for stepLength time
// If end is reached, goes to CheckStepsState to wait user input
// If a button is pressed => FAIL
void *PlayNextStepState()
{
  // Last step reached?
  if (playingStep == currStep) {
    playingStep = 0;
    counter.SendData(countDownAnimation, COUNTDOWNCOUNT, countDownStep, false);
    return (void *)CheckStepsState;
  }
  
  // You can't press any button while you're listening!
  if (FirstButtonPressed() != -1)
    return (void *)EndState;
    
  if (bUseServo)
    servo.write(map(playingStep + 1, 0, currStep, MIN_SERVO, MAX_SERVO));
    
  // Light the convenient led and play tone
  leds[steps[playingStep]]->GoHigh();
  buzzer.PlayTone(tones[steps[playingStep]]);
  
  // Prepare waiting state
  timer.SetTimer(stepLength);
  onExitTimer = (void *)WaitInterStepState;
  return (void *)WaitForTimerState;
}

// Waits for WAITINTERSTEPS between steps
// If a button is pressed => FAIL
void *WaitInterStepState()
{
  // You can't press any button while you're listening!
  if (FirstButtonPressed() != -1)
    return (void *)EndState;
  
  // Turn off led and speaker
  leds[steps[playingStep]]->GoLow();
  playingStep++;
  buzzer.Quiet();
  
  // Prepare waiting state
  timer.SetTimer(WAITINTERSTEPS);
  onExitTimer = (void *)PlayNextStepState;
  return (void *)WaitForTimerState;
}

// Loop to wait for some time 
// If a button is pressed => FAIL
void *WaitForTimerState()
{
  if (timer.IsFired())
    return onExitTimer;

  if (FirstButtonPressed() != -1)
    return (void *)EndState;
    
  return (void *)WaitForTimerState;
}

// Plays a step when the user is right in a step
void PlayStep(byte nStep)
{
  if (nStep - 1) StopStep(nStep - 1);
  buzzer.PlayTone(tones[steps[nStep]]);
  leds[steps[nStep]]->GoHigh();
  timer.SetTimer(stepLength);
  counter.SendData(countDownAnimation, COUNTDOWNCOUNT, countDownStep, false);
}

// Stops a playing step
void StopStep(byte nStep)
{
  buzzer.Quiet();
  leds[steps[nStep]]->GoLow();
}

// Main state for the user turn
// If the last step is over, adds a step and restart the playing loop
// If a button is pressed, processes the next step of fail without waiting for the prior step to end
void *CheckStepsState()
{
  // If timer fired, stop buzzer
  if (timer.IsFired()) {
    if (playingStep > 0) StopStep(playingStep - 1);
    // And if it's the last, advance
    if (playingStep == currStep) {
      AddStep();
      timer.SetTimer(WAITINTERSERIES);
      onExitTimer = (void *)PlayNextStepState;     
      return (void *)WaitForTimerState;
    }
  }

  // If animation is over => FAIL
  if (!counter.IsActive())
    return (void*)EndState;
  // If no button pressed, continue
  int but = FirstButtonPressed();
  if (but == -1)
    return (void*)CheckStepsState;
    
  // Button pressed: fail or advance step
  // Check error
  if (playingStep == currStep || but != steps[playingStep])
    return (void *)EndState;

  // No error: play step or delay if interrupting
  if (bUseServo)
    servo.write(map(playingStep + 1, 0, currStep, MAX_SERVO, MIN_SERVO));
    
  // The user pressed the button before the prior step ended
  if (timer.IsActive()) {
    StopStep(playingStep - 1);
    timer.SetTimer(WAITINTERSTEPS);
    return (void *)ButtonInterruptingState;
  }
    
  PlayStep(playingStep++);
  return (void *) CheckStepsState;
}

// Ends the current step playing and plays the next one
// Used to pause between steps if the user don't let the step to finish
void *ButtonInterruptingState()
{
  if (!timer.IsFired())
    return (void *)ButtonInterruptingState;
    
  PlayStep(playingStep++);
  return (void *) CheckStepsState;  
}

// When the user fails the result is shown in the shifter and go to blinking
byte result[2];
void *EndState()
{
  finalTimer.SetTimer(WAITFORNEXTGAME);
  StopStep(playingStep);
  timer.SetTimer(WAITINTERSTEPS);

  // Show result
  currStep--; // To have the right steps done
  if (currStep < 10)
    counter.SendData(PShifter595::digits09[currStep] | B10000000);
  else {
    result[0] = PShifter595::digits09[currStep / 10];
    result[1] = PShifter595::digits09[currStep % 10] | B10000000;
    counter.SendData(result, 2, stepLength * 3, true);
  }
  return (void *)EndBlinkState;
}

// Restarts the main game when the user presses a button after the security time WAITINTERSTEPS is over
boolean high = true;
void *EndBlinkState()
{
  // Restart only if finalTimer has already been fired to prevent unwanted strokes
  if (!finalTimer.IsActive() && FirstButtonPressed() != -1)
    return (void *)RestartState;
    
  if (timer.IsFired()) {
    if (high) {
      // Manage led
      leds[steps[playingStep]]->GoHigh();
      timer.SetTimer(stepLength);
    }
    else {
      // Manage led
      leds[steps[playingStep]]->GoLow();
      timer.SetTimer(WAITINTERSTEPS);
    }
    high = !high;
  }
  
  return (void *)EndBlinkState;
}

