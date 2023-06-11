/* Include Standard Libraries */
%:include <math.h>
%:include <stdio.h>
%:include <stdlib.h>
%:include <stdint.h>
%:include <assert.h>
/* Define and Macros ........ */
#define max(x, y)			((x) > (y) ? (x) : (y))
#define min(x, y)			((x) < (y) ? (x) : (y))
#define max_vec3(x, y, z)	max(max(x, y), z)
#define min_vec3(x, y, z)	min(min(x, y), z)
/* Structures ............... */
struct vec3
{
	float x;	// Red - Hue
	float y;	// Green - Saturation
	float z;	// Blue	- Brightness
};
/* Functions ................ */
void ask_float(const char * msg, float * v, float max)
{
	(void)printf(msg); scanf("%f", v);
	assert(*v < max && "Value shouldn't be bigger than 255.");
}
void normalize_rgb(struct vec3 * rgb)
{
	rgb->x /= 255.;
	rgb->y /= 255.;
	rgb->z /= 255.;
}
void rgb_to_hsb(struct vec3 * hsb, struct vec3 rgb)
{
	struct vec3 b_rgb = rgb;
	normalize_rgb(&b_rgb);		// Normalize RGB Values

	// Here I don't know what is happening... -_-;
	float max_val = max_vec3(b_rgb.x, b_rgb.y, b_rgb.z);
	float min_val = min_vec3(b_rgb.x, b_rgb.y, b_rgb.z);

	hsb->z = max_val;

	if (max_val == 0)	hsb->y = 0;
	else				hsb->y = (max_val - min_val) / max_val;

	if (max_val == min_val)
		hsb->x = 0;
	else if (max_val == b_rgb.x)
		hsb->x = (b_rgb.y - b_rgb.z) / (max_val - min_val);
	else if (max_val == b_rgb.y)
		hsb->x = 2 + (b_rgb.z - b_rgb.x) / (max_val - min_val);
	else
		hsb->x = 4 + (b_rgb.x - b_rgb.y) / (max_val - min_val);
	
	hsb->x *= 60;
	if (hsb->x < 0)
		hsb->x += 360;

	hsb->y *= 100;
	hsb->z *= 100;
	// Here I don't what is happening
	hsb->x = floor(hsb->x);
	hsb->y = floor(hsb->y);
	hsb->z = floor(hsb->z);
}
/* Entry Point .............. */
int main(void)
{
	// Local Variables
	struct vec3 b_rgb	= { 0., 0., 0. };
	// Set RGB Value	
	(void)printf("Enter RED Value: ");		// Red Value
	scanf("%f", &b_rgb.x);
	assert(b_rgb.x < 256 && "Value shouldn't be bigger than 255.");
	(void)printf("Enter GREEN Value: ");	// Green Value
	scanf("%f", &b_rgb.y);
	assert(b_rgb.y < 256 && "Value shouldn't be bigger than 255.");
	(void)printf("Enter BLUE Value: ");		// Blue Value
	scanf("%f", &b_rgb.z);
	assert(b_rgb.z < 256 && "Value shouldn't be bigger than 255.");
	// RGB to HSB
	struct vec3 g_hsb	= { 0., 0., 0. };
	rgb_to_hsb(&g_hsb, b_rgb);
	(void)printf("---------------------------------\n");	
	(void)printf("Hue: %f\n", g_hsb.x);
	(void)printf("Sat: %f\n", g_hsb.y);
	(void)printf("Bri: %f\n", g_hsb.z);
	return 0;
}
/* .......................... */
