#include <luminous.h>

luminous hii;

void setup()
{
	Serial.begin(115200);
	while (!Serial)
		;

	Serial.println("LUMINOUS - Serial print TEST");

	// (sclk, miso, mosi, ss0, ss1);
	hii.begin(13, 12, 11, 10, 9);
}

void loop()
{
	for (int Ch = 0; Ch < 16; Ch++)
	{
		Serial.print(hii.read(Ch));
		Serial.print("\t");
	}
	Serial.print("\n");

	// delay(100);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~