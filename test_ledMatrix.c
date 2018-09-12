
#include "test_ledMatrix.h"
/*** GLOBAL VARIABLE ***/
/* GPIO PATH */
#define GPIO_PATH "/sys/class/gpio/"

/* GPIO Pins Definition */
#define RED1_PIN 66      // UPPER
#define GREEN1_PIN 67
#define BLUE1_PIN 69
#define RED2_PIN 68     // LOWER
#define GREEN2_PIN 45
#define BLUE2_PIN 44
#define CLK_PIN 27      // Arrival of each data
#define LATCH_PIN 65    // End of a row of data
#define OE_PIN 22       // Transition from one row to another
#define A_PIN 23        // Row select
#define B_PIN 26
#define C_PIN 47

#define S_IWRITE "S_IWUSR"

/* TIMING */
#define DELAY_IN_US 5

/* LED Screen Values */
int screen[32][16];

/* FILES HANDLER */
int fileDesc_red1;
int fileDesc_blue1;
int fileDesc_green1;
int fileDesc_red2;
int fileDesc_blue2;
int fileDesc_green2;
int fileDesc_clk;
int fileDesc_latch;
int fileDesc_oe;
int fileDesc_a;
int fileDesc_b;
int fileDesc_c;

/**
 * exportAndOut
 * Export a pin and set the direction to output
 * @params
 *  int pinNum: the pin number to be exported and set for output
 */
void exportAndOut(int pinNum)
{
        // Reset the screen
    memset(screen, 0, sizeof(screen));
    // Export the gpio pins
    FILE *gpioExP = fopen(GPIO_PATH "export", "w");
    if ( gpioExP == NULL ){
        printf("ERROR: Unable to open export file.\n");
        exit(-1);
    }
    fprintf(gpioExP, "%d", pinNum);
    fclose(gpioExP);

    // Change the direction into out
    char fileNameBuffer[1024];
    sprintf(fileNameBuffer, GPIO_PATH "gpio%d/direction", pinNum);

    FILE *gpioDirP = fopen(fileNameBuffer, "w");
    fprintf(gpioDirP, "out");
    fclose(gpioDirP);

    return;
}

/**
 * ledMatrix_setupPins
 * Setup the pins used by the led matrix, by exporting and set the direction to out
 */
void ledMatrix_setupPins(void)
{
    // !-   Change GPIO number here
    //          fileDesc_<wire> = open("/sys/class/gpio/gpio<gpio_number>/value", O_WRONLY, S_IWRITE);

    // Upper led
    exportAndOut(RED1_PIN);
    fileDesc_red1 = open("/sys/class/gpio/gpio66/value", O_WRONLY, S_IWRITE);
    exportAndOut(GREEN1_PIN);
    fileDesc_green1 = open("/sys/class/gpio/gpio67/value", O_WRONLY, S_IWRITE);
    exportAndOut(BLUE1_PIN);
    fileDesc_blue1 = open("/sys/class/gpio/gpio69/value", O_WRONLY, S_IWRITE);

    // Lower led
    exportAndOut(RED2_PIN);
    fileDesc_red2 = open("/sys/class/gpio/gpio68/value", O_WRONLY, S_IWRITE);
    exportAndOut(GREEN2_PIN);
    fileDesc_green2 = open("/sys/class/gpio/gpio45/value", O_WRONLY, S_IWRITE);
    exportAndOut(BLUE2_PIN);
    fileDesc_blue2 = open("/sys/class/gpio/gpio44/value", O_WRONLY, S_IWRITE);

    // Timing
    exportAndOut(CLK_PIN);
    fileDesc_clk = open("/sys/class/gpio/gpio27/value", O_WRONLY, S_IWRITE);
    exportAndOut(LATCH_PIN);
    fileDesc_latch = open("/sys/class/gpio/gpio65/value", O_WRONLY, S_IWRITE);
    exportAndOut(OE_PIN);
    fileDesc_oe = open("/sys/class/gpio/gpio22/value", O_WRONLY, S_IWRITE);

    // Row Select
    exportAndOut(A_PIN);
    fileDesc_a = open("/sys/class/gpio/gpio23/value", O_WRONLY, S_IWRITE);
    exportAndOut(B_PIN);
    fileDesc_b = open("/sys/class/gpio/gpio26/value", O_WRONLY, S_IWRITE);
    exportAndOut(C_PIN);
    fileDesc_c = open("/sys/class/gpio/gpio47/value", O_WRONLY, S_IWRITE);

    return;
}
/**
 * ledMatrix_writeGpioValue
 * Write the gpio value to the pin selected
 * @params:
 *  int pinNum: GPIO pin to write to
 *  int value: Value to be written to the pin
 *
 */
void ledMatrix_writeGpioValue(int pinNum, int value)
{
    char fileNameBuffer[1024];
    sprintf(fileNameBuffer, GPIO_PATH "gpio%d/value", pinNum);

    FILE *gpioValP = fopen(fileNameBuffer, "w");
    fprintf(gpioValP, "%d", value);
    fclose(gpioValP);

    return;
}
/**
 *  ledMatrix_clock
 *  Generate the clock pins
 */
void ledMatrix_clock(void)
{
    // Bit-bang the clock gpio
    lseek(fileDesc_clk, 0, SEEK_SET);
    write(fileDesc_clk, "1", 1);
    lseek(fileDesc_clk, 0, SEEK_SET);
    write(fileDesc_clk, "0", 1);

    return;
}

/**
 *  ledMatrix_latch
 *  Generate the latch pins
 */
void ledMatrix_latch(void)
{
    lseek(fileDesc_latch, 0, SEEK_SET);
    write(fileDesc_latch, "1", 1);
    lseek(fileDesc_latch, 0, SEEK_SET);
    write(fileDesc_latch, "0", 1);

    return;
}

/**
 *  ledMatrix_bitsFromInt
 *  Convert integer passed on into bits and put in array
 *  @params:
 *      int * arr: pointer to array to be filled with bits
 *      int input: integer to be converted to bits
 */
void ledMatrix_bitsFromInt(int * arr, int input)
{
    arr[0] = input & 1;

    arr[1] = input & 2;
    arr[1] = arr[1] >> 1;

    arr[2] = input & 4;
    arr[2] = arr[2] >> 2;

    return;
}

/**
 *  ledMatrix_setRow
 *  Set LED Matrix row
 *  @params:
 *      int rowNum: the rowNumber to be inputted to row pins
 */
void ledMatrix_setRow(int rowNum)
{
    // Convert rowNum single bits from int
    int arr[3] = {0, 0, 0};
    ledMatrix_bitsFromInt(arr, rowNum);

    // Write on the row pins
    char a_val[2];
    sprintf(a_val, "%d", arr[0]);
    lseek(fileDesc_a, 0, SEEK_SET);
    write(fileDesc_a, a_val, 1);

    char b_val[2];
    sprintf(b_val, "%d", arr[1]);
    lseek(fileDesc_b, 0, SEEK_SET);
    write(fileDesc_b, b_val, 1);

    char c_val[2];
    sprintf(c_val, "%d", arr[2]);
    lseek(fileDesc_c, 0, SEEK_SET);
    write(fileDesc_c, c_val, 1);


    return;
}

/**
 *  ledMatrix_setColourTop
 *  Set the colour of the top part of the LED
 *  @params:
 *      int colour: colour to be set
 */
void ledMatrix_setColourTop(int colour)
{
    int arr[3] = {0, 0, 0};
    ledMatrix_bitsFromInt(arr, colour);

    // Write on the row pins
    char red1_val[2];
    sprintf(red1_val, "%d", arr[0]);
    lseek(fileDesc_red1, 0, SEEK_SET);
    write(fileDesc_red1, red1_val, 1);

    char green1_val[2];
    sprintf(green1_val, "%d", arr[1]);
    lseek(fileDesc_green1, 0, SEEK_SET);
    write(fileDesc_green1, green1_val, 1);

    char blue1_val[2];
    sprintf(blue1_val, "%d", arr[2]);
    lseek(fileDesc_blue1, 0, SEEK_SET);
    write(fileDesc_blue1, blue1_val, 1);

    return;
}

/**
 *  ledMatrix_setColourBottom
 *  Set the colour of the bottom part of the LED
 *  @params:
 *      int colour: colour to be set
 */
void ledMatrix_setColourBottom(int colour)
{
    int arr[3] = {0,0,0};
    ledMatrix_bitsFromInt(arr, colour);

    // Write on the row pins
    char red2_val[2];
    sprintf(red2_val, "%d", arr[0]);
    lseek(fileDesc_red2, 0, SEEK_SET);
    write(fileDesc_red2, red2_val, 1);

    char green2_val[2];
    sprintf(green2_val, "%d", arr[1]);
    lseek(fileDesc_green2, 0, SEEK_SET);
    write(fileDesc_green2, green2_val, 1);

    char blue2_val[2];
    sprintf(blue2_val, "%d", arr[2]);
    lseek(fileDesc_blue2, 0, SEEK_SET);
    write(fileDesc_blue2, blue2_val, 1);

    return;
}
/**
 *  ledMatrix_refresh
 *  Fill the LED Matrix with the respective pixel colour
 */
void ledMatrix_refresh(void)
{
    for ( int rowNum = 0; rowNum < 8; rowNum++ ) {
        lseek(fileDesc_oe, 0, SEEK_SET);
        write(fileDesc_oe, "1", 1);
        ledMatrix_setRow(rowNum);
        for ( int colNum = 0; colNum < 32;  colNum++) {
            ledMatrix_setColourTop(screen[colNum][rowNum]);
            ledMatrix_setColourBottom(screen[colNum][rowNum+8]);
            ledMatrix_clock();
        }
        ledMatrix_latch();
        lseek(fileDesc_oe, 0, SEEK_SET);
        write(fileDesc_oe, "0", 1);
        sleep_usec(DELAY_IN_US); // Sleep for delay
    }
    return;
}
/**
 *
 *  Fill the LED Matrix screen with the pixel colour
 *  @params:
 *      int x1: start of the x pixel
 *      int y1: start of the y pixel
 *      int x2: end of the x pixel
 *      int y2: end of the y pixel
 *      int colour: colour of the matrix
 */
void ledMatrix_fillRectangle(int x1, int y1, int x2, int y2, int colour)
{
    for ( int x = x1; x < x2; x++) {
        for ( int y = y1; y < y2; y++) {
            screen[y][x] = colour;
        }
    }

    return;
}

/**
 *  ledMatrix_setPixel
 *  Set the pixel selected on LED MAtrix with the colour selected
 *  @params:
 *      int x: x-axis
 *      int y: y-axis
 *      int colour: colour selected
 */
void ledMatrix_setPixel(int x, int y, int colour)
{
    screen[y][x] = colour;

    return;
}

/**
 *  ledMatrix_printBoard
 *  Print the LED Matrix Board pattern
 */
void ledMatrix_printBoard()
{
    for ( int x = 0; x < 16 ; x++ ) {
        for ( int y = 0; y < 32; y++) {
            printf("%d ", screen[y][x]);
        }
        printf("\n");
   }

}
