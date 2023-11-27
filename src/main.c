#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>

#define P 3.14159265

#define W 50	// Width of the render canvas
#define H 50	// Height of the render canvas

#define SX 25	// x-value of the globe position on canvas
#define SY 25	// y-value of the globe position on canvas
#define SR 20	// Radius of the globe

#define LX 1	// x-Value of the light source position
#define LY -1	// y-Value of the light source position
#define LZ -1	// z-Value of the light source position

// Texture of the globe
const uint64_t texture[32] = {
	0x0000000000000000, 0x0000f7fc00000000, 0x001207f000307080, 0x1c1df3f0002ffff0,
	0x3fff31883dffffff, 0x19fe38006fffff88, 0x00fdbc037fffff80, 0x003f7601ffffff80,
	0x003f2003b9fffe00, 0x003fe00081fffe80, 0x001fc003effffc00, 0x00060007fd9ff800,
	0x00060007ffc63000, 0x00008007fe846400, 0x00007803ff804000, 0x00003e003f004800,
	0x00003f803e002880, 0x00003fc03a000800, 0x00003f803e000340, 0x00000f803c8007c0,
	0x00001e001c000fe0, 0x00001e0018000f60, 0x00001c0000000060, 0x0000180000000002,
	0x0000100000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
	0x0000180007f7fff8, 0x03fff01ffffffff8, 0x07fff07ffffffff8, 0xffffffffffffffff,
};

// Characters used for illumination (More detailed: .'`^\",:;Il!i<>~+_-?[]{}1()|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$)
const char illu_char[] = ".,-~:;=!*#$@";

double nx, ox, ny, nz, lx, ly, lz, nm, lm, illu, a, ca, sa;
int x, y, u, v, char_i;

int main(void){
	for (;;){
		printf("\033[0;0H");
		a -= 0.008;
		for (y = 0; y < H; y++){										// Loop through all 'pixels'
			for (x = 0; x < W; x++){
				if (sqrt((x - SX) * (x - SX) + (y - SY) * (y - SY)) <= SR){
					nx = x - SX; ny = y - SY;							// x- and y-position relative to center of globe
					nz = -sqrt(SR * SR - ny * ny - nx * nx);			// Calculate z-position of current pixel
					nm = sqrt(nx * nx + ny * ny + nz * nz);
					lm = sqrt(LX * LX + LY * LY + LZ * LZ);
					nx /= nm; ny /= nm; nz /= nm;						// Normalize current position on globe
					illu = nx * LX / lm + ny * LY / lm + nz * LZ / lm;	// Calculate illumination
					ca = cos(a); sa = sin(a); ox = nx;
					nx = nx * ca + nz * sa;								// Calculate x-position after rotation
					nz = ox * -sa + nz * ca;							// Calculate z-position after rotation
					nm = sqrt(nx * nx + ny * ny + nz * nz);
					nx /= nm; ny /= nm; nz /= nm;						// Normalize rotated position
					u = (atan2(nz, nx) / (2 * P) + 0.5) * 63;			// Calculate uv-coordinate on texture
					v = (asin(ny) / P + 0.5) * 31;						// using uv-mapping
					illu = (double)((texture[v] >> (63 - u)) & 1) * illu;
					char_i = floor((illu >= 0 ? illu : 0) * (sizeof(illu_char) / sizeof(char) - 1));
					putchar(illu_char[char_i]);
				} else putchar(' ');
				putchar(' ');
			}
			putchar('\n');
		}
		usleep(10000);
	}
	return 0;
}
