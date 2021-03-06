const int stripClock = D2;
const int stripData = D3;
int stripLen = 48;
bool animateBool = false;

typedef struct _PIXEL_VALUES {
	byte Green;
	byte Red;
	byte Blue;
} PIXEL_VALUES, *PPIXEL_VALUES;

// Array of stored Pixel values
PIXEL_VALUES *Pixels;
PIXEL_VALUES *PixelsMax;

// Custom Functions for working with the RGB Pixel Strip
int scaleColor(int color);
void changeSize(String command);
void SetPixel(int pixel, byte Red, byte Green, byte Blue);
void ShiftPixel(int pixel);
void ShiftAllPixels();
void SetPixelAltered(int pixel, byte Red, byte Green, byte Blue);

void setup()
{
	Pixels = new PIXEL_VALUES[stripLen];
	PixelsMax = new PIXEL_VALUES[stripLen];

    // Defining Spark Variables
    Spark.variable("animateBool", &animateBool, INT);

    // Defining Spark Functions
    Spark.function("switchColor", switchColor);
    Spark.function("seahawks", seahawksColors); // can't be longer than 12 characters
    Spark.function("animate", animateColors);

	// Set pins to outputs
	pinMode(stripClock, OUTPUT);
	pinMode(stripData, OUTPUT);
	digitalWrite(stripClock, LOW);
	digitalWrite(stripData, LOW);

	// Reset all the pixels
	for (int i = 0; i < stripLen; i++)
	{
		SetPixel(i, 127, 127, 127);
	}
	ShiftAllPixels();
}

void loop()
{
	if (animateBool == true)
	{
		for (int j = 0; j <= 100; j++)
		{
			for (int i = 0; i < stripLen; i++)
			{
				int red = (PixelsMax[i].Red * j / 100);
				int green = (PixelsMax[i].Green * j / 100);
				int blue = (PixelsMax[i].Blue * j / 100);
				SetPixelAltered(i, (scaleColor(red) & 0x7F), (scaleColor(green) & 0x7F), (scaleColor(blue) & 0x7F));
			}
			ShiftAllPixels();
		}
		for (int j = 100; j >= 0; j--)
		{
			for (int i = 0; i < stripLen; i++)
			{
			    int red = (PixelsMax[i].Red * j / 100);
				int green = (PixelsMax[i].Green * j / 100);
				int blue = (PixelsMax[i].Blue * j / 100);
				SetPixelAltered(i, (scaleColor(red) & 0x7F), (scaleColor(green) & 0x7F), (scaleColor(blue) & 0x7F));
			}
			ShiftAllPixels();
		}
	}
}

int scaleColor(int color)
{
	return (double) color / 255 * 127;
}

void changeSize(String command)
{
	String length = command;
	length.remove(3);
	int l = length.toInt();
	if (l != stripLen)
	{

		// Reset all the pixels prior to resetting it
		for (int i = l; i < stripLen; i++)
		{
			SetPixel(i, 0, 0, 0);
		}
		ShiftAllPixels();

		stripLen = l;

		Pixels = new PIXEL_VALUES[stripLen];
		PixelsMax = new PIXEL_VALUES[stripLen];
	}
}

int switchColor(String command)
{
	// command will be of format 048,127,127,127,100,100,100,100,100
	// R,G,B,BottomBrightness,RightBrightness,BackBrightness,LeftBrightness,TopBrightness
	// any values less than 127 will be filled with spaces
	// The strip is divided into groups of 4 per side. First 4 are bottom, Next 4 are right, etc.

	changeSize(command);

	command.remove(0, 4);

	String red = command;
	String green = command;
	String blue = command;
	red.remove(3);
	green.remove(0, 4);
	green.remove(3);
	blue.remove(0, 8);
	blue.remove(3);
	int redInt = scaleColor(red.toInt());
	int greenInt = scaleColor(green.toInt());
	int blueInt = scaleColor(blue.toInt());

	String bottom = command;
	String right = command;
	String back = command;
	String left = command;
	String top = command;
	bottom.remove(0, 12);
	bottom.remove(3);
	right.remove(0, 16);
	right.remove(3);
	back.remove(0, 20);
	back.remove(3);
	left.remove(0, 24);
	left.remove(3);
	top.remove(0, 28);
	int bottomInt = bottom.toInt();
	int rightInt = right.toInt();
	int backInt = back.toInt();
	int leftInt = left.toInt();
	int topInt = top.toInt();

	int pixelsPerSide = stripLen / 5;
	for (int i = 0; i < stripLen; i++)
	{
		if (i < pixelsPerSide)
		{
			SetPixel(i, ((redInt * bottomInt / 100) & 0x7F), ((greenInt  * bottomInt / 100) & 0x7F), ((blueInt * bottomInt / 100) & 0x7F));
		}
		else if (i < (pixelsPerSide * 2))
		{
			SetPixel(i, ((redInt * rightInt / 100) & 0x7F), ((greenInt  * rightInt / 100) & 0x7F), ((blueInt * rightInt / 100) & 0x7F));
		}
		else if (i < (pixelsPerSide * 3))
		{
			SetPixel(i, ((redInt * backInt / 100) & 0x7F), ((greenInt  * backInt / 100) & 0x7F), ((blueInt * backInt / 100) & 0x7F));
		}
		else if (i < (pixelsPerSide * 4))
		{
			SetPixel(i, ((redInt * leftInt / 100) & 0x7F), ((greenInt  * leftInt / 100) & 0x7F), ((blueInt * leftInt / 100) & 0x7F));
		}
		else if (i < (pixelsPerSide * 5))
		{
			SetPixel(i, ((redInt * topInt / 100) & 0x7F), ((greenInt  * topInt / 100) & 0x7F), ((blueInt * topInt / 100) & 0x7F));
		}
		else
		{
			SetPixel(i, (redInt & 0x7F), (greenInt & 0x7F), (blueInt & 0x7F));
		}
	}
	ShiftAllPixels();

	return 1;
}

int seahawksColors(String command)
{
	changeSize(command);

	// Set the pixels to Green
	for (int i = 0; i < stripLen; i++)
	{
		if (i % 2 == 0)
		{
			SetPixel(i, 0, (i & 0x7F), 0);
		}
		else
		{
			SetPixel(i, 0, 0, (i & 0x7F));
		}
	}
	ShiftAllPixels();

	return 1;
}

int animateColors(String command)
{
	changeSize(command);

	animateBool = !animateBool;
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

		PixelsMax[pixel].Red = Red | 0x80;
		PixelsMax[pixel].Green = Green | 0x80;
		PixelsMax[pixel].Blue = Blue | 0x80;
	}
}

void SetPixelAltered(int pixel, byte Red, byte Green, byte Blue)
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
