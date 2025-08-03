#ifndef KYRAGAMEENGINE_WINDOW_ABSTRACTWINDOW_HPP
#define KYRAGAMEENGINE_WINDOW_ABSTRACTWINDOW_HPP

namespace kyra {

	template<class T>
	class Recttangle {
		
		T m_Data[4];
		
		public:
		constexpr Rectangle() noexcept : m_Data{0,0,0,0} {
		
		}
		
		constexpr Rectangle(T x, T y, T width, T height) noexcept : m_Data{x,y,width,height} {
		
		}
	};
	
	template<class T>
	class Vector2 {
	
		public:
		constexpr Vector2() noexcept : m_Data{0,0} {
		
		}
		
		constexpr Vector2(T x, T y) noexcept : m_Data{x,y} {
		
		}
	
	};
	
	enum class WindowMode {
		Windowed,
		BorderlessWindowed,
		Fullscreen,
		NativeFullscreen
	};

	class AbstractWindow {
	
		public:
		virtual ~AbstractWindow() = default;
	
		virtual void setShape( const Rect<int32_t>& rectangle ) = 0;
		virtual const Rect<int32_t>& getShape() const = 0;
		virtual void move(const Vector2<int32_t>& position) = 0;
		virtual void bringToFront() = 0;
		virtual void close() = 0;
		virtual void minimize() = 0;
		virtual void maximize() = 0;
		virtual void restore() = 0;
		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void setMode(const WindowMode& mode) = 0;
		virtual WindowMode getMode() const = 0;
		virtual bool isMaximized() const = 0;
		virtual bool isMinimized() const = 0;
		virtual bool isVisible() const = 0;
		virtual bool getRestoredDimensions(Vector2<int32_t>& dimensions) = 0;
		virtual void setFocus() = 0;
		virtual void setOpacity( const float opacity) = 0;
		virtual void enable() = 0;
		virtual void disable() = 0;
		virtual bool isPointInWindow(const Vector2<int32_t>& pos) const = 0;
		virtual int32_t getBorderSize() const = 0;
		virtual int32_t getTitleBarSize() const = 0;
		virtual void* getHandle() const = 0;
		virtual bool isForegroundWindow() const = 0;
		virtual bool isFullscreenSupported() const = 0;
		virtual void setTitle(const char* title) = 0;
		virtual float getDPIScaleFactor() const = 0;
		virtual void setDPIScaleFactor() = 0;
		
	};

}

#endif