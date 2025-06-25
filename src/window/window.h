#pragma once

class Window
{
public:

	static Window& Get()
	{
		static Window s_window;
		return s_window;
	}
	/*Retrns window width WITHOUT scale*/
	static int Width() { return Get().IWidth(); }    
	/*Retrns window height WITHOUT scale*/
	static int Height() { return Get().IHeight(); }
	static int Scale() { return Get().IScale(); }
	/*Retrns window width with scale*/
	static int WidthWS() { return Get().IWidthWS(); }
	/*Retrns window height with scale*/
	static int HeightWS() { return Get().IHeightWS(); }
	static void SetScale(int scale) { Get().ISetScale(scale); }

private:
	int IWidth() { return windowWidth; }
	int IHeight() { return windowHeight; }
	int IScale() { return windowScale; }
	int IWidthWS() { return windowWidthWithScale; }
	int IHeightWS() { return windowHeightWithScale; }
	void ISetScale(int scale) 
	{ 
		windowScale = scale;
		windowWidthWithScale = windowWidth * windowScale;
		windowHeightWithScale = windowHeight * windowScale;
	}
	Window& operator= (const Window&) = delete;
	Window(const Window&) = delete;
	Window()
		:windowWidth(120), windowHeight(160), windowScale(6), windowWidthWithScale(windowWidth * windowScale), windowHeightWithScale(windowHeight * windowScale)
	{}

	int windowWidth;
	int windowHeight;
	int windowScale;
	int windowWidthWithScale;
	int windowHeightWithScale;

};

