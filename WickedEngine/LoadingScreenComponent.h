#pragma once
#include "RenderableComponent.h"
#include <atomic>

class LoadingScreenComponent :
	public RenderableComponent
{
private:
	struct LoaderTask
	{
		function< void() > functionBody;
		atomic_bool active;

		LoaderTask(function< void() > functionBody) :functionBody(functionBody)
		{
			active.store(false);
		}
	};
	vector< LoaderTask > loaders;
	void doLoadingTasks();

	void waitForFinish();
	function<void()> finish;
	thread worker;
public:
	LoadingScreenComponent();
	~LoadingScreenComponent();

	//Add a loading task which should be executed
	//use std::bind( YourFunctionPointer )
	void addLoadingFunction(function<void()> loadingFunction);
	//Set a function that should be called when the loading finishes
	//use std::bind( YourFunctionPointer )
	void onFinished(function<void()> finishFunction);
	//Get percentage of finished loading tasks (values 0-100)
	int getPercentageComplete();
	//See if the loading is currently running
	bool isActive();
	
	//Start Executing the tasks and mark the loading as active
	virtual void Start();
	//Remove all tasks
	virtual void Unload();
};
