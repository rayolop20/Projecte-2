#include "EasingFunctions.h"
#define PI 3.14159265359

#include <cmath>



float EasingFunctions::linearEaseNull(float t, float b, float c, float d)
{
	return c * t / d + b;
}


//

float EasingFunctions::quadEaseIn(float t, float b, float c, float d)
{
	t /= d;
	return c * t * t + b;
}

float EasingFunctions::quadEaseOut(float t, float b, float c, float d)
{
	t /= d;
	return -c * t * (t - 2) + b;
}

float EasingFunctions::quadEaseInOut(float t, float b, float c, float d)
{
	t /= d / 2;
	if (t < 1) {
		return c / 2 * t * t + b;
	}
	t--;
	return -c / 2 * (t * (t - 2) - 1) + b;
}


//

float EasingFunctions::cubicEaseIn(float t, float b, float c, float d)
{
	t /= d;
	return c * t * t * t + b;
}

float EasingFunctions::cubicEaseOut(float t, float b, float c, float d)
{
	t /= d;
	t--;
	return c * (t * t * t + 1) + b;
}

float EasingFunctions::cubicEaseInOut(float t, float b, float c, float d)
{
	t /= d / 2;
	if (t < 1) {
		return c / 2 * t * t * t + b;
	}
	t -= 2;
	return c / 2 * (t * t * t + 2) + b;
}


//

float EasingFunctions::quartEaseIn(float t, float b, float c, float d)
{
	t /= d;
	return c * t * t * t * t + b;
}

float EasingFunctions::quartEaseOut(float t, float b, float c, float d)
{
	t /= d;
	t--;
	return -c * (t * t * t * t - 1) + b;
}

float EasingFunctions::quartEaseInOut(float t, float b, float c, float d)
{
	t /= d / 2;
	if (t < 1) return c / 2 * t * t * t * t + b;
	t -= 2;
	return -c / 2 * (t * t * t * t - 2) + b;
}


//

float EasingFunctions::quintEaseIn(float t, float b, float c, float d)
{
	t /= d;
	return c * t * t * t * t * t + b;
}

float EasingFunctions::quintEaseOut(float t, float b, float c, float d)
{
	t /= d;
	t--;
	return c * (t * t * t * t * t + 1) + b;
}

float EasingFunctions::quintEaseInOut(float t, float b, float c, float d)
{
	t /= d / 2;
	if (t < 1) return c / 2 * t * t * t * t * t + b;
	t -= 2;
	return c / 2 * (t * t * t * t * t + 2) + b;
}


//

float EasingFunctions::sineEaseIn(float t, float b, float c, float d) {
	return -c * cos(t / d * (PI / 2)) + c + b;
}

float EasingFunctions::sineEaseOut(float t, float b, float c, float d) {
	return c * sin(t / d * (PI / 2)) + b;
}

float EasingFunctions::sineEaseInOut(float t, float b, float c, float d) {
	return -c / 2 * (cos(PI * t / d) - 1) + b;
}


//

float EasingFunctions::expoEaseIn(float t, float b, float c, float d) {
	return c * pow(2, 10 * (t / d - 1)) + b;
}

float EasingFunctions::expoEaseOut(float t, float b, float c, float d) {
	return c * (-pow(2, -10 * t / d) + 1) + b;
}

float EasingFunctions::expoEaseInOut(float t, float b, float c, float d) {
	t /= d / 2;
	if (t < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
	t--;
	return c / 2 * (-pow(2, -10 * t) + 2) + b;
}


//

float EasingFunctions::circEaseIn(float t, float b, float c, float d) {
	t /= d;
	return -c * (sqrt(1 - t * t) - 1) + b;
}

float EasingFunctions::circEaseOut(float t, float b, float c, float d) {
	t /= d;
	t--;
	return c * sqrt(1 - t * t) + b;
}

float EasingFunctions::circEaseInOut(float t, float b, float c, float d) {
	t /= d / 2;
	if (t < 1) return -c / 2 * (sqrt(1 - t * t) - 1) + b;
	t -= 2;
	return c / 2 * (sqrt(1 - t * t) + 1) + b;
}


//

float EasingFunctions::backEaseIn(float t, float b, float c, float d) {
	float s = 1.70158;
	return c * (t /= d) * t * ((s + 1) * t - s) + b;
}

float EasingFunctions::backEaseOut(float t, float b, float c, float d) {
	float s = 1.70158;
	return c * ((t = t / d - 1) * t * ((s + 1) * t + s) + 1) + b;
}

float EasingFunctions::backEaseInOut(float t, float b, float c, float d) {
	float s = 1.70158f;
	if ((t /= d / 2) < 1) return c / 2 * (t * t * (((s *= (1.525)) + 1) * t - s)) + b;
	return c / 2 * ((t -= 2) * t * (((s *= (1.525)) + 1) * t + s) + 2) + b;
}


//

float EasingFunctions::elasticEaseIn(float t, float b, float c, float d) {
	if (t == 0)
		return b;
	if ((t /= d) == 1)
		return b + c;
	float p = d * .3f;
	float a = c;
	float s = p / 4;
	return -(a * pow(2, 10 * (t -= 1)) * sin((t * d - s) * (2 * PI) / p)) + b;
}

float EasingFunctions::elasticEaseOut(float t, float b, float c, float d) {
	if (t == 0) return b;
	if ((t /= d) == 1) return b + c;
	float p = d * .3f;
	float a = c;
	float s = p / 4;
	return (a * pow(2, -10 * t) * sin((t * d - s) * (2 * PI) / p) + c + b);
}

float EasingFunctions::elasticEaseInOut(float t, float b, float c, float d) {
	if (t == 0)
		return b;
	if ((t /= d / 2) == 2)
		return b + c;
	float p = d * (.3f * 1.5f);
	float a = c;
	float s = p / 4;
	if (t < 1)
		return -.5f * (a * pow(2, 10 * (t -= 1)) * sin((t * d - s) * (2 * PI) / p)) + b;
	return a * pow(2, -10 * (t -= 1)) * sin((t * d - s) * (2 * PI) / p) * .5f + c + b;
}


//

float EasingFunctions::bounceEaseIn(float t, float b, float c, float d) {
	return c - EasingFunctions::bounceEaseOut(d - t, 0, c, d) + b;
}

float EasingFunctions::bounceEaseOut(float t, float b, float c, float d) {
	if ((t /= d) < (1 / 2.75)) {
		return c * (7.5625 * t * t) + b;
	}
	else if (t < (2 / 2.75)) {
		return c * (7.5625 * (t -= (1.5 / 2.75)) * t + .75) + b;
	}
	else if (t < (2.5 / 2.75)) {
		return c * (7.5625 * (t -= (2.25 / 2.75)) * t + .9375) + b;
	}
	else {
		return c * (7.5625 * (t -= (2.625 / 2.75)) * t + .984375) + b;
	}
}

float EasingFunctions::bounceEaseInOut(float t, float b, float c, float d) {
	if (t < d / 2) return EasingFunctions::bounceEaseIn(t * 2, 0, c, d) * .5 + b;
	return EasingFunctions::bounceEaseOut(t * 2 - d, 0, c, d) * .5 + c * .5 + b;
}
