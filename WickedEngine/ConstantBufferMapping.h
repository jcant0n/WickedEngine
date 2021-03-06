#ifndef _CONSTANTBUFFER_MAPPING_H_
#define _CONSTANTBUFFER_MAPPING_H_

// Slot matchings:
////////////////////////////////////////////////////

// Persistent buffers:
// These are bound once and are alive forever
#define CBSLOT_RENDERER_WORLD					0
#define CBSLOT_RENDERER_FRAME					1
#define CBSLOT_RENDERER_CAMERA					2
#define CBSLOT_RENDERER_MISC					3

#define CBSLOT_IMAGE_IMAGE						4
#define CBSLOT_IMAGE_POSTPROCESS				5

#define CBSLOT_API								6


// On demand buffers:
// These are bound on demand and alive until another is bound at the same slot
#define CBSLOT_RENDERER_MATERIAL				7
#define CBSLOT_RENDERER_CUBEMAPRENDER			8
#define CBSLOT_RENDERER_VOLUMELIGHT				8
#define CBSLOT_RENDERER_DECAL					8
#define CBSLOT_RENDERER_TESSELLATION			8
#define CBSLOT_RENDERER_DISPATCHPARAMS			8
#define CBSLOT_RENDERER_VOXELIZER				8

#define CBSLOT_OTHER_EMITTEDPARTICLE			8
#define CBSLOT_OTHER_HAIRPARTICLE				8
#define CBSLOT_OTHER_LENSFLARE					8
#define CBSLOT_OTHER_FFTGENERATOR				8
#define CBSLOT_OTHER_OCEAN_SIMULATION_IMMUTABLE	8
#define CBSLOT_OTHER_OCEAN_SIMULATION_PERFRAME	9
#define CBSLOT_OTHER_OCEAN_RENDER				8



#endif // _CONSTANTBUFFER_MAPPING_H_
