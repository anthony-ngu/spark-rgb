const int stripClock = D2;
const int stripData = D3;
const int stripLen = 48;

typedef struct _PIXEL_VALUES {
    byte Green;
    byte Red;
    byte Blue;
} PIXEL_VALUES, *PPIXEL_VALUES;

// Array of stored Pixel values
PIXEL_VALUES Pixels[stripLen];

// Custom Functions for working with the RGB Pixel Strip
void SetPixel(int pixel, byte Red, byte Green, byte Blue);
void ShiftPixel(int pixel);
void ShiftAllPixels();

void setup()
{
    Spark.function("switchColor", switchColor);
    Spark.function("turnOff", turnOff);
    // Set pins to outputs
    pinMode(stripClock, OUTPUT);
    pinMode(stripData, OUTPUT);
    digitalWrite(stripClock, LOW);
    digitalWrite(stripData, LOW);

    // Reset all the pixels
    for (int i = 0; i < stripLen; i++)
    {
        SetPixel(i, 0, 0, 0);
    }
    ShiftAllPixels();
}

void loop()
{
    /*int i;

    // Set the pixels to Red
    for (i = 0; i < stripLen; i++)
    {
        SetPixel(i, (i & 0x7F), 0, 0);
    }
    ShiftAllPixels();

    // Set the pixels to Green
    for (i = 0; i < stripLen; i++)
    {
        SetPixel(i, 0, (i & 0x7F), 0);
    }
    ShiftAllPixels();

    // Set the pixels to Blue
    for (i = 0; i < stripLen; i++)
    {
        SetPixel(i, 0, 0, (i & 0x7F));
    }
    ShiftAllPixels();

    // Set the pixels to White
    for (i = 0; i < stripLen; i++)
    {
        SetPixel(i, (i & 0x7F), (i & 0x7F), (i & 0x7F));
    }
    ShiftAllPixels();

    // Set the pixels to gradient from Yellow to Cyan
    for (i = 0; i < stripLen; i++)
    {
        SetPixel(i, ((stripLen - i) & 0x7F), ((128 + (stripLen / 2) + i) & 0x7F), (i & 0x7F));
    }
    ShiftAllPixels();

    // Set the pixels to random colors
    for (i = 0; i < stripLen; i++)
    {
        SetPixel(i, (byte) random(0, 40), (byte) random(0, 40), (byte) random(0, 40));
    }
    ShiftAllPixels();

    // Turn the pixels off
    for (i = 0; i < stripLen; i++)
    {
        SetPixel(i, 0, 0, 0);
    }
    ShiftAllPixels();*/
}

int scaleColor(int color)
{
    return (double)color / 255 * 127;
}

int switchColor(String command)
{
    // command will be of format 127,127,127
    // any values less than 127 will be filled with spaces
    String red = command;
    String green = command;
    String blue = command;
    red.remove(3);
    green.remove(0,4);
    green.remove(3);
    blue.remove(0,8);

    int redInt = scaleColor(red.toInt());
    int greenInt = scaleColor(green.toInt());
    int blueInt = scaleColor(blue.toInt());

    int i;
    // Set the pixels to White
    for (i = 0; i < stripLen; i++)
    {
        SetPixel(i, (redInt & 0x7F), (greenInt & 0x7F), (blueInt & 0x7F));
    }
    ShiftAllPixels();

    return 1;
}

int turnOff(String command)
{
    int i;
    for (i = 0; i < stripLen; i++)
    {
        SetPixel(i, 0, 0, 0);
    }
    ShiftAllPixels();

    return 1;
}

// Sets the pixel color in our array
void SetPixel(int pixel, byte Red, byte Green, byte Blue)
{
    if (pixel < stripLen)
    {
        Pixels[pixel].Red = Red | 0x80;
        Pixels[pixel].Green = Green | 0x80;
        Pixels[pixel].Blue = Blue | 0x80;
    }
}

// Sends the color of a pixel to the strip
void ShiftPixel(int pixel)
{
    PPIXEL_VALUES PixelValues = &Pixels[pixel];
    byte bit;
    int i;

    for (i = 7; i >= 0; i--)
    {
        bit = (PixelValues->Green >> i) & 0x01;
        digitalWrite(stripData, bit);
        digitalWrite(stripClock, HIGH);
        digitalWrite(stripClock, LOW);
    }
    for (i = 7; i >= 0; i--)
    {
        bit = (PixelValues->Red >> i) & 0x01;
        digitalWrite(stripData, bit);
        digitalWrite(stripClock, HIGH);
        digitalWrite(stripClock, LOW);
    }
    for (i = 7; i >= 0; i--)
    {
        bit = (PixelValues->Blue >> i) & 0x01;
        digitalWrite(stripData, bit);
        digitalWrite(stripClock, HIGH);
        digitalWrite(stripClock, LOW);
    }
}

// Sends all the pixel colors to the strip
void ShiftAllPixels()
{
    int i;

    digitalWrite(stripData, 0);
    for (i = 0; i < 8; i++)
    {
        digitalWrite(stripClock, HIGH);
        digitalWrite(stripClock, LOW);
    }
    for (i = 0; i < 8; i++)
    {
        digitalWrite(stripClock, HIGH);
        digitalWrite(stripClock, LOW);
    }
    for (i = 0; i < 8; i++)
    {
        digitalWrite(stripClock, HIGH);
        digitalWrite(stripClock, LOW);
    }

    for (i = 0; i < stripLen; i++)
    {
        ShiftPixel(i);
    }

    digitalWrite(stripData, 0);
    for (i = 0; i < 8; i++)
    {
        digitalWrite(stripClock, HIGH);
        digitalWrite(stripClock, LOW);
    }
    for (i = 0; i < 8; i++)
    {
        digitalWrite(stripClock, HIGH);
        digitalWrite(stripClock, LOW);
    }
    delay(100);
}
