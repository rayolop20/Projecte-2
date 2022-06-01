#pragma once
#define PI 3.14159265359

class EasingFunctions {
public:
	float t, b, c, d;

public:

	static float linearEaseNull(float t, float b, float c, float d);

	static float quadEaseIn(float t, float b, float c, float d);
	static float quadEaseOut(float t, float b, float c, float d);
	static float quadEaseInOut(float t, float b, float c, float d);

	static float cubicEaseIn(float t, float b, float c, float d);
	static float cubicEaseOut(float t, float b, float c, float d);
	static float cubicEaseInOut(float t, float b, float c, float d);

	static float quartEaseIn(float t, float b, float c, float d);
	static float quartEaseOut(float t, float b, float c, float d);
	static float quartEaseInOut(float t, float b, float c, float d);

	static float quintEaseIn(float t, float b, float c, float d);
	static float quintEaseOut(float t, float b, float c, float d);
	static float quintEaseInOut(float t, float b, float c, float d);

	static float sineEaseIn(float t, float b, float c, float d);
	static float sineEaseOut(float t, float b, float c, float d);
	static float sineEaseInOut(float t, float b, float c, float d);

	static float expoEaseIn(float t, float b, float c, float d);
	static float expoEaseOut(float t, float b, float c, float d);
	static float expoEaseInOut(float t, float b, float c, float d);

	static float circEaseIn(float t, float b, float c, float d);
	static float circEaseOut(float t, float b, float c, float d);
	static float circEaseInOut(float t, float b, float c, float d);

	static float backEaseIn(float t, float b, float c, float d);
	static float backEaseOut(float t, float b, float c, float d);
	static float backEaseInOut(float t, float b, float c, float d);

	static float elasticEaseIn(float t, float b, float c, float d);
	static float elasticEaseOut(float t, float b, float c, float d);
	static float elasticEaseInOut(float t, float b, float c, float d);

	static float bounceEaseIn(float t, float b, float c, float d);
	static float bounceEaseOut(float t, float b, float c, float d);
	static float bounceEaseInOut(float t, float b, float c, float d);
};

