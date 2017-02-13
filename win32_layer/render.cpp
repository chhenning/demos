#include "app_state.h"

struct offscreen_buffer
{
	int* _memory = nullptr;
	int _width = 0;
	int _height = 0;
};


inline
int32_t round_float_int32(float x)
{
    int32_t result = (int32_t) roundf(x);

    return result;
}

inline
uint32_t round_float_uint32(float x)
{
    uint32_t result = (uint32_t)roundf(x);
    
    return result;
}

/*
	1) round coordinates
	2) draw rectangle from min_x, min_y to max_x-1, max_y-1

	The max values are truncated so that adjacent rectangle don't overlap.
	E.g. (0,0)->(20,20) should not overlap (20,20)->(40,40)

	The memory is ARGB with 8 bits per channel

	color are normalized to 0->1
*/
void draw_rectangle(offscreen_buffer& display_buffer
	, float min_x, float min_y, float max_x, float max_y
	, float red, float green, float blue, float alpha = 1.f
	)
{
	assert(alpha >= 0.0 && alpha <= 1.0);
	assert(red >= 0.0 && red <= 1.0);
	assert(green >= 0.0 && green <= 1.0);
	assert(blue >= 0.0 && blue <= 1.0);


	uint32_t color = round_float_uint32(alpha * 255.f) << 24
		| round_float_uint32(red * 255.f) << 16
		| round_float_uint32(green * 255.f) << 8
		| round_float_uint32(blue * 255.f);


	assert(min_x <= max_x);
	assert(min_y <= max_y);

	int32_t start_x = round_float_int32(min_x);
	int32_t start_y = round_float_int32(min_y);
	int32_t end_x   = round_float_int32(max_x);
	int32_t end_y   = round_float_int32(max_y);

	start_x = (start_x < 0) ? 0 : start_x;
	start_y = (start_y < 0) ? 0 : start_y;

	// this is correct since we only draw up to end_x, excluding end_x
	end_x = (end_x > display_buffer._width ) ? display_buffer._width  : end_x;
	end_y = (end_y > display_buffer._height) ? display_buffer._height : end_y;

	int32_t bytes_per_pixel = 4;
	int32_t pitch = bytes_per_pixel * display_buffer._width;
	
	uint8_t* row = (uint8_t*)display_buffer._memory + start_x * bytes_per_pixel + start_y * pitch;

	for (int y = start_y; y < end_y; ++y)
	{
		uint32_t* pixel = (uint32_t*)row;

		for (int x = start_x; x < end_x; ++x)
		{
			*pixel++ = color;
		}

		row += pitch;
	}
}



void render()
{
    offscreen_buffer ob;
    ob._width = app_globals._wob._width;
    ob._height = app_globals._wob._height;
    ob._memory = app_globals._wob._memory;

    for(int y = 0; y < ob._height; ++y)
    {
        float r = ((float) y) / ob._height;
        
        draw_rectangle(ob, 0, y, ob._width, ob._height, r, 0, 0);
    }
}