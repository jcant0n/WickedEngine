#include "wiInitializer.h"
#include "wiRenderer.h"
#include "wiImage.h"
#include "wiLensFlare.h"
#include "wiResourceManager.h"
#include "wiFrameRate.h"
#include "wiBackLog.h"
#include "wiCpuInfo.h"
#include "wiSound.h"
#include "wiOcean.h"
#include "wiHelper.h"

using namespace std;

namespace wiInitializer
{

	void InitializeComponents()
	{
		wiBackLog::Initialize();
		wiFrameRate::Initialize();
		wiCpuInfo::Initialize();

		wiRenderer::SetUpStaticComponents();
		wiLensFlare::Initialize();

		wiImage::Load();

		wiFont::Initialize();
		wiFont::SetUpStaticComponents();

		wiOcean::SetUpStatic();

		if (FAILED(wiSoundEffect::Initialize()) || FAILED(wiMusic::Initialize()))
		{
			stringstream ss("");
			ss << "Failed to Initialize Audio Device!";
			wiHelper::messageBox(ss.str());
		}
	}
}