#ifndef _FFT_GENERATOR_H_
#define _FFT_GENERATOR_H_

#include "CommonInclude.h"
#include "wiGraphicsAPI.h"


//Memory access coherency (in threads)
#define COHERENCY_GRANULARITY 128


///////////////////////////////////////////////////////////////////////////////
// Common types
///////////////////////////////////////////////////////////////////////////////

typedef struct CSFFT_512x512_Data_t
{
	static wiGraphicsTypes::ComputeShader* pRadix008A_CS;
	static wiGraphicsTypes::ComputeShader* pRadix008A_CS2;

	// More than one array can be transformed at same time
	UINT slices;

	// For 512x512 config, we need 6 constant buffers
	wiGraphicsTypes::GPUBuffer* pRadix008A_CB[6];

	// Temporary buffers
	wiGraphicsTypes::GPUBuffer* pBuffer_Tmp;
	wiGraphicsTypes::GPUUnorderedResource* pUAV_Tmp;
	wiGraphicsTypes::GPUResource* pSRV_Tmp;

	static void LoadShaders();
} CSFFT512x512_Plan;

////////////////////////////////////////////////////////////////////////////////
// Common constants
////////////////////////////////////////////////////////////////////////////////
#define TWO_PI 6.283185307179586476925286766559

#define FFT_DIMENSIONS 3U
#define FFT_PLAN_SIZE_LIMIT (1U << 27)

#define FFT_FORWARD -1
#define FFT_INVERSE 1


void fft512x512_create_plan(CSFFT512x512_Plan* plan, UINT slices);
void fft512x512_destroy_plan(CSFFT512x512_Plan* plan);

void fft_512x512_c2c(CSFFT512x512_Plan* fft_plan,
	wiGraphicsTypes::GPUUnorderedResource* pUAV_Dst,
	wiGraphicsTypes::GPUResource* pSRV_Dst,
	wiGraphicsTypes::GPUResource* pSRV_Src, 
	GRAPHICSTHREAD threadID);


#endif // _FFT_GENERATOR_H_
