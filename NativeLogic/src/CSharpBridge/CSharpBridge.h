#ifndef __CSHARP_BRIDGE__
#define __CSHARP_BRIDGE__

extern "C"
{
	// The update method, where we handle all of game logic, update the object...
	__declspec(dllexport)
		void __stdcall update(double deltaTime);

	// The game draw method, this method will be invoked once Native App step into Draw phase.
	__declspec(dllexport)
		void __stdcall draw(){}
}

#endif //__CSHARP_BRIDGE__