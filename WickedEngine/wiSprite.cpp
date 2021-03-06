#include "wiSprite.h"
#include "wiResourceManager.h"
#include "wiImageEffects.h"
#include "wiImage.h"
#include "wiRenderer.h"

using namespace wiGraphicsTypes;


wiSprite::wiSprite(wiResourceManager* contentHolder) :ContentHolder(contentHolder)
{
	Init();
}
wiSprite::wiSprite(const std::string& newTexture, const std::string& newMask, const std::string& newNormal, wiResourceManager* contentHolder) : ContentHolder(contentHolder)
{
	Init();
	CreateReference(newTexture,newMask,newNormal);
}
wiSprite::wiSprite(const std::string& newTexture, const std::string& newMask, wiResourceManager* contentHolder) : ContentHolder(contentHolder)
{
	Init();
	CreateReference(newTexture,newMask,"");
}
wiSprite::wiSprite(const std::string& newTexture, wiResourceManager* contentHolder) : ContentHolder(contentHolder)
{
	Init();
	CreateReference(newTexture,"","");
}
void wiSprite::Init(){
	if (ContentHolder == nullptr)
	{
		ContentHolder = wiResourceManager::GetGlobal();
	}
	texture="";
	mask="";
	normal="";
	name="";
	texturePointer=maskPointer=normalPointer=nullptr;
	effects=wiImageEffects();
	anim=Anim();
}
void wiSprite::CreateReference(const std::string& newTexture, const std::string& newMask, const std::string& newNormal){
	if(newTexture.length()) {
		texture = newTexture;
		texturePointer = (Texture2D*)ContentHolder->add(newTexture);
	}
	if(newMask.length()) {
		maskPointer = (Texture2D*)ContentHolder->add(newMask);
		effects.setMaskMap( maskPointer );
		mask = newMask;
	}
	if(newNormal.length()) {
		normalPointer = (Texture2D*)ContentHolder->add(newNormal);
		//effects.setNormalMap( normalPointer );
		normal = newNormal;
	}
}
void wiSprite::CleanUp(){
	ContentHolder->del(texture);
	ContentHolder->del(normal);
	ContentHolder->del(mask);
}

void wiSprite::Draw(Texture2D* refracRes, GRAPHICSTHREAD threadID){
	if(effects.opacity>0 && ((effects.blendFlag==BLENDMODE_ADDITIVE && effects.fade<1) || effects.blendFlag!=BLENDMODE_ADDITIVE) ){
		effects.setRefractionSource(refracRes);
		wiImage::Draw(texturePointer,effects,threadID);
	}
}
void wiSprite::Draw(GRAPHICSTHREAD threadID){
	wiSprite::Draw(nullptr, threadID);
}
void wiSprite::DrawNormal(GRAPHICSTHREAD threadID){
	if(normalPointer && effects.opacity>0 && ((effects.blendFlag==BLENDMODE_ADDITIVE && effects.fade<1) || effects.blendFlag!=BLENDMODE_ADDITIVE)){
		//effects.setRefractionMap(refracRes);

		wiImageEffects effectsMod(effects);
		effectsMod.blendFlag=BLENDMODE_ADDITIVE;
		effectsMod.extractNormalMap=true;
		wiImage::Draw(normalPointer,effectsMod,threadID);
	}
}

void wiSprite::Update(float gameSpeed){
	effects.pos.x+=anim.vel.x*gameSpeed;
	effects.pos.y+=anim.vel.y*gameSpeed;
	effects.pos.z+=anim.vel.z*gameSpeed;
	effects.rotation+=anim.rot*gameSpeed;
	effects.scale.x+=anim.scaleX*gameSpeed;
	effects.scale.y+=anim.scaleY*gameSpeed;
	effects.opacity+=anim.opa*gameSpeed;
		if(effects.opacity>=1) {
			if(anim.repeatable) {effects.opacity=0.99f; anim.opa*=-1;}
			else				effects.opacity=1;
		}
		else if(effects.opacity<=0){
			if(anim.repeatable) {effects.opacity=0.01f; anim.opa*=-1;}
			else				effects.opacity=0;
		}
	effects.fade+=anim.fad*gameSpeed;
		if(effects.fade>=1) {
			if(anim.repeatable) {effects.fade=0.99f; anim.fad*=-1;}
			else				effects.fade=1;
		}
		else if(effects.fade<=0){
			if(anim.repeatable) {effects.fade=0.01f; anim.fad*=-1;}
			else				effects.fade=0;
		}
		
	effects.texOffset.x+=anim.movingTexAnim.speedX*gameSpeed;
	effects.texOffset.y+=anim.movingTexAnim.speedY*gameSpeed;
	
	if(anim.drawRecAnim.elapsedFrames>=anim.drawRecAnim.onFrameChangeWait){
		effects.drawRec.x+=effects.drawRec.z*anim.drawRecAnim.jumpX;
		effects.drawRec.y+=effects.drawRec.w*anim.drawRecAnim.jumpY;

		if(anim.drawRecAnim.currentFrame>=anim.drawRecAnim.frameCount){
			effects.drawRec.z-=anim.drawRecAnim.sizX*anim.drawRecAnim.frameCount;
			effects.drawRec.w-=anim.drawRecAnim.sizY*anim.drawRecAnim.frameCount;
			anim.drawRecAnim.currentFrame=0;
		}
		else{
			effects.drawRec.z+=anim.drawRecAnim.sizX;
			effects.drawRec.w+=anim.drawRecAnim.sizY;
			anim.drawRecAnim.currentFrame++;
		}
		anim.drawRecAnim.elapsedFrames=0;
	}
	else anim.drawRecAnim.elapsedFrames+=gameSpeed;
}
void wiSprite::Update(){
	Update(1);
}
