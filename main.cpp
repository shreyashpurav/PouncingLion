#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <string.h>
#include <FEHSD.h>
#include <stdio.h>
#include <time.h>

// DEFAULT MOTOR PERCENT
#define motor_percent 30

// Declarations for encoders & motors
FEHMotor right_motor(FEHMotor::Motor1, 9.0);
FEHMotor left_motor(FEHMotor::Motor0, 9.0);
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
AnalogInputPin CdS_Cell(FEHIO::P3_1);

// Start
void start()
{
    while ((CdS_Cell.Value() > 0.6))
    {
        right_motor.SetPercent(0);
        left_motor.SetPercent(0);
    }
}

// fd = forward, bk = backward, rt = right, lt = left, fdr = forward turning right, fdl = forward turning left
void fd(int counts)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(motor_percent);
    left_motor.SetPercent(motor_percent);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts)
    {
        if (left_encoder.Counts() > right_encoder.Counts())
        {
            right_motor.SetPercent(motor_percent + 2);
            left_motor.SetPercent(motor_percent - 2);
        }
        else if (left_encoder.Counts() < right_encoder.Counts())
        {
            right_motor.SetPercent(motor_percent - 2);
            left_motor.SetPercent(motor_percent + 2);
        }
    }
    right_motor.Stop();
    left_motor.Stop();
    Sleep(1.0);
}

void fd(int counts, int speed)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(speed);
    left_motor.SetPercent(speed);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts)
    {
        if (left_encoder.Counts() > right_encoder.Counts())
        {
            right_motor.SetPercent(speed + 2);
            left_motor.SetPercent(speed - 2);
        }
        else if (left_encoder.Counts() < right_encoder.Counts())
        {
            right_motor.SetPercent(speed - 2);
            left_motor.SetPercent(speed + 2);
        }
    }
    right_motor.Stop();
    left_motor.Stop();
    Sleep(1.0);
}

void bk(int counts)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(-motor_percent);
    left_motor.SetPercent(-motor_percent);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts)
    {
        if (left_encoder.Counts() > right_encoder.Counts())
        {
            right_motor.SetPercent(-motor_percent - 2);
            left_motor.SetPercent(-motor_percent + 2);
        }
        else if (left_encoder.Counts() < right_encoder.Counts())
        {
            right_motor.SetPercent(-motor_percent + 2);
            left_motor.SetPercent(-motor_percent - 2);
        }
    }
    right_motor.Stop();
    left_motor.Stop();
    Sleep(1.0);
}

void bk(int counts, int speed)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(-speed);
    left_motor.SetPercent(-speed);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts)
    {
        if (left_encoder.Counts() > right_encoder.Counts())
        {
            right_motor.SetPercent(-speed - 2);
            left_motor.SetPercent(-speed + 2);
        }
        else if (left_encoder.Counts() < right_encoder.Counts())
        {
            right_motor.SetPercent(-speed + 2);
            left_motor.SetPercent(-speed - 2);
        }
    }
    right_motor.Stop();
    left_motor.Stop();
    Sleep(1.0);
}

void rt(int counts)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(-motor_percent);
    left_motor.SetPercent(motor_percent);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts)
        ;
    right_motor.Stop();
    left_motor.Stop();
    Sleep(1.0);
}

void rt(int counts, int speed)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(-speed);
    left_motor.SetPercent(speed);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts)
        ;
    right_motor.Stop();
    left_motor.Stop();
    Sleep(1.0);
}

void lt(int counts)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(motor_percent);
    left_motor.SetPercent(-motor_percent);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts)
        ;
    right_motor.Stop();
    left_motor.Stop();
    Sleep(1.0);
}

void lt(int counts, int speed)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(speed);
    left_motor.SetPercent(-speed);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts)
        ;
    right_motor.Stop();
    left_motor.Stop();
    Sleep(1.0);
}

void bkr(int counts, int right)
{
    int d;
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(-motor_percent + right);
    left_motor.SetPercent(-motor_percent - right);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts)
        ;
    right_motor.Stop();
    left_motor.Stop();
    Sleep(1.0);
}

void spback(int counts, int right)
{
    int l_counts;
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(-motor_percent + right);
    left_motor.SetPercent(-motor_percent - right);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts)
    {
        l_counts = left_encoder.Counts();
        Sleep(0.05);
        if (left_encoder.Counts() - l_counts == 0)
        {
            right_motor.Stop();
            left_motor.Stop();
            Sleep(0.1);
            left_motor.SetPercent(motor_percent);
            right_motor.SetPercent(motor_percent);
            Sleep(0.2);
            right_motor.Stop();
            left_motor.Stop();
            Sleep(0.1);
            right_motor.SetPercent(-motor_percent + right);
            left_motor.SetPercent(-motor_percent - right);
        }
    }
    right_motor.Stop();
    left_motor.Stop();
    Sleep(1.0);
}

void fdr(int counts, int right)
{
    int d;
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(motor_percent - right);
    left_motor.SetPercent(motor_percent + right);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts)
        ;
    right_motor.Stop();
    left_motor.Stop();
    Sleep(1.0);
}

int main(void)
{
    float x, y;
    LCD.Clear(YELLOW);
    LCD.SetFontColor(RED);
    LCD.WriteLine("Press to Start");

    while (!LCD.Touch(&x, &y))
        ;
    while (LCD.Touch(&x, &y))
        ;

    LCD.Clear(RED);
    LCD.SetFontColor(YELLOW);
    LCD.WriteLine("Waiting to Pounce");
    // 100 counts at 15 speed is 6 inches

    start();

    LCD.Clear(BLUE);
    LCD.SetFontColor(GREEN);
    LCD.WriteLine("Processing");
    LCD.WriteLine("Primary Points");
    bk(20);
    fd(200);
    lt(158);
    bk(290);
    bkr(110, 10);
    fd(225);

    Sleep(0.5);
    LCD.Clear(YELLOW);
    LCD.SetFontColor(RED);
    LCD.WriteLine("Now get ready for");
    LCD.WriteLine("The Mighty Pouncing Lion!");
    Sleep(2.5);

    LCD.Clear(BLUE);
    LCD.SetFontColor(GREEN);
    LCD.WriteLine("Processing");
    LCD.WriteLine("Bonus");

    bk(100);
    fdr(60, 5);
    fdr(100, 20); // turn out
    fd(100);
    lt(80);
    fd(225); // go to ramp
    lt(80);  // turn to ramp
    fd(448); // ramp
    lt(79);
    fd(270);
    bk(280);
    rt(80);
    bk(500);
    bkr(100, 5);

    LCD.Clear(BLUE);
    LCD.SetFontColor(WHITE);
    LCD.WriteLine("Fin");

    return 0;
}
