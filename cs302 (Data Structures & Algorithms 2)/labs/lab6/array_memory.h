/*
 * Memory Helper Functions
 *
 * Description:
 *     Provides 4 functions for dynamically allocating multi-dimensional memory
 *     in C... 2D and 3D. This mimics C++ "templates" by allowing the user to
 *     pass in a type for each function. The following guarantees are made:
 *
 *       - allocate_2d will return a 2D array of size (sx, sy)
 *       - allocate_3d will return a 3D array of size (sx, sy, sz)
 *       - Both allocate functions will return memory "zero'd out" (calloc).
 *       - free_2d and free_3d will free arrays if given the proper sizes.
 *
 * Author:
 *     Clara Nguyen
 */

#ifndef __CN_MEMORY__
#define __CN_MEMORY__

/*
 * allocate_2d
 *
 * Allocates a 2D array with all memory set to 0. It's a "define" because, in
 * C, we can't use templates. So a "workaround" is to use macros to force a
 * type as an argument (e.g. "type" here).
 *
 * void allocate_2d(type** var, type T, int sx, int sy);
 */

#define allocate_2d(var, type, sx, sy) { \
	int _i;                                          \
	var = (type **) calloc(sx, sizeof(type *));      \
	for (_i = 0; _i < sx; _i++)                      \
		var[_i] = (type *) calloc(sy, sizeof(type)); \
}

/*
 * allocate_3d
 *
 * Allocates a 3D array with all memory set to 0. It's a "define" because, in
 * C, we can't use templates. So a "workaround" is to use macros to force a
 * type as an argument (e.g. "type" here).
 *
 * void allocate_3d(type*** var, type T, int sx, int sy, int sz);
 */

#define allocate_3d(var, type, sx, sy, sz) { \
	int _i, _j;                                              \
	var = (type ***) calloc(sx, sizeof(type **));            \
	for (_i = 0; _i < sx; _i++) {                            \
		var[_i] = (type **) calloc(sy, sizeof(type *));      \
		for (_j = 0; _j < sy; _j++)                          \
			var[_i][_j] = (type *) calloc(sz, sizeof(type)); \
	}                                                        \
}

/*
 * free_2d
 *
 * Frees a 2D array. It's a "define" because a custom type is used.
 *
 * void free_2d(type** var, type T, int sx, int sy);
 */

#define free_2d(var, type, sx, sy) { \
	int _i;                     \
	for (_i = 0; _i < sx; _i++) \
		free(var[_i]);          \
	free(var);                  \
}

/*
 * free_3d
 *
 * Frees a 3D array. It's a "define" because a custom type is used.
 *
 * void free_3d(type*** var, type T, int sx, int sy, int sz);
 */

#define free_3d(var, type, sx, sy, sz) { \
	int _i, _j;                     \
	for (_i = 0; _i < sx; _i++) {   \
		for (_j = 0; _j < sy; _j++) \
			free(var[_i][_j]);      \
		free(var[_i]);              \
	}                               \
	free(var);                      \
}

#endif
