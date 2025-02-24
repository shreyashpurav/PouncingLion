#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>

// Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
FEHMotor right_motor(FEHMotor::Motor0, 9.0);
FEHMotor left_motor(FEHMotor::Motor1, 9.0);

void move_forward(int percent, int counts) // using encoders
{
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    // Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    // While the average of the left and right encoder is less than counts,
    // keep running motors and adjust motors to keep motion straight
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
    {
        if (left_encoder.Counts() < right_encoder.Counts())
        {
            left_motor.SetPercent(percent + 2);
            right_motor.SetPercent(percent - 2);
        }
        else
        {
            left_motor.SetPercent(percent - 2);
            right_motor.SetPercent(percent + 2);
        }
    }

    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_right(int percent, int counts)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-1 * percent);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
        ;
    right_motor.Stop();
    left_motor.Stop();
}

void turn_left(int percent, int counts)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(-1 * percent);
    left_motor.SetPercent(percent);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
        ;
    right_motor.Stop();
    left_motor.Stop();
}

int main(void)
{
    int motor_percent = 20;   // Input power level here
    int straight_counts = 41; // Input straight motion counts per inch
    int turn_counts = 210;    // Input turn motion counts per 90 degree turn
    float x, y;               // for touch screen

    // Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);

    LCD.WriteLine("Shaft Encoder Go Wheeeeeee");
    LCD.WriteLine("Touch the screen");
    while (!LCD.Touch(&x, &y))
        ; // Wait for screen to be pressed
    while (LCD.Touch(&x, &y))
        ; // Wait for screen to be unpressed

    move_forward(motor_percent, straight_counts * 14); // 14 inches
    turn_left(motor_percent, turn_counts);             // turn left 90 degrees
    move_forward(motor_percent, straight_counts * 10); // 10 inches
    turn_right(motor_percent, turn_counts);            // turn right 90 degrees
    move_forward(motor_percent, straight_counts * 4);  // 4 inches

    return 0;
}
