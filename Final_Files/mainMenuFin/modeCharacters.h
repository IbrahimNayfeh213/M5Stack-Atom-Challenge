/*
 * Arrays of numbers displayed in the main menu
 * 
 * Creates a shape matrix to display numebers 1 through 5
 * Pixels listed as 0 are black and those listed as 1 are white
 * 
 * Inspired by Mike Klepper
 * Patrio Geek blog
 * ATOM Matrix: Using the MPU6886 Accelerometer - 
 *  Detect a Shake and Roll a Die, aka AccelerometerTest03.ino
 * 
 */

//Color values
int C_black (0x000000), C_white (0xffffff);
int palette[] = {C_black, C_white};



int one[25] =   { 0, 0, 1, 0, 0,
                  0, 1, 1, 0, 0,
                  0, 0, 1, 0, 0,
                  0, 0, 1, 0, 0,
                  0, 1, 1, 1, 0,
                };
int two[25] =   { 0, 1, 1, 1, 0,
                  0, 0, 0, 1, 0,
                  0, 1, 1, 1, 0,
                  0, 1, 0, 0, 0,
                  0, 1, 1, 1, 0,
                };
int three[25] = { 0, 1, 1, 1, 0,
                  0, 0, 0, 1, 0,
                  0, 1, 1, 1, 0,
                  0, 0, 0, 1, 0,
                  0, 1, 1, 1, 0,
                };
int four[25] =  { 0, 1, 0, 1, 0,
                  0, 1, 0, 1, 0,
                  0, 1, 1, 1, 0,
                  0, 0, 0, 1, 0,
                  0, 0, 0, 1, 0,
                };
int five[25] =  { 0, 1, 1, 1, 0,
                  0, 1, 0, 0, 0,
                  0, 1, 1, 1, 0,
                  0, 0, 0, 1, 0,
                  0, 1, 1, 1, 0,
                };
