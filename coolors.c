/* Include Standard Libraries */
%:include <math.h>
%:include <stdio.h>
%:include <stdlib.h>
%:include <stdint.h>
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
void rgb_to_hsb(struct vec3 * hsb, struct vec3 rgb)
{
	struct vec3 b_rgb = rgb;
	b_rgb.x /= 255.;
	b_rgb.y /= 255.;
	b_rgb.z /= 255.;

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

	hsb->x = floor(hsb->x);
	hsb->y = floor(hsb->y);
	hsb->z = floor(hsb->z);
}
/* Entry Point .............. */
int main(void)
{
	// Local Variables
	struct vec3 b_rgb	= { 0., 0., 0. };
	printf("Enter RED Value: ");	scanf("%f", &b_rgb.x);
	printf("Enter GREEN Value: ");	scanf("%f", &b_rgb.y);
	printf("Enter BLUE Value: ");	scanf("%f", &b_rgb.z);
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
