#include "pch.h"

extern "C" IMAGE_DOS_HEADER __ImageBase;

extern "C"
{
	HRESULT __stdcall OS_RoGetActivationFactory(HSTRING classId, GUID const& iid, void** factory) noexcept;
}

#ifdef _M_IX86
#pragma comment(linker, "/alternatename:_OS_RoGetActivationFactory@12=_RoGetActivationFactory@12")
#else
#pragma comment(linker, "/alternatename:OS_RoGetActivationFactory=RoGetActivationFactory")
#endif

bool starts_with(std::wstring_view value, std::wstring_view match) noexcept
{
	return 0 == value.compare(0, match.size(), match);
}

HRESULT __stdcall WINRT_RoGetActivationFactory(HSTRING classId, GUID const& iid, void** factory) noexcept
{
	*factory = nullptr;
	std::wstring_view name{ WindowsGetStringRawBuffer(classId, nullptr), WindowsGetStringLen(classId) };
	HMODULE library{ nullptr };

	if (starts_with(name, L"Microsoft.Graphics."))
	{
		library = LoadLibraryW(L"Microsoft.Graphics.Canvas.dll");
	}
	else
	{
		return OS_RoGetActivationFactory(classId, iid, factory);
	}

	if (!library)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	using DllGetActivationFactory = HRESULT __stdcall(HSTRING classId, void** factory);
	auto call = reinterpret_cast<DllGetActivationFactory*>(GetProcAddress(library, "DllGetActivationFactory"));

	if (!call)
	{
		HRESULT const hr = HRESULT_FROM_WIN32(GetLastError());
		WINRT_VERIFY(FreeLibrary(library));
		return hr;
	}

	winrt::com_ptr<winrt::Windows::Foundation::IActivationFactory> activation_factory;
	HRESULT const hr = call(classId, activation_factory.put_void());

	if (FAILED(hr))
	{
		WINRT_VERIFY(FreeLibrary(library));
		return hr;
	}

	if (iid != winrt::guid_of<winrt::Windows::Foundation::IActivationFactory>())
	{
		return activation_factory->QueryInterface(iid, factory);
	}

	*factory = activation_factory.detach();
	return S_OK;
}

using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Composition::Desktop;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::Foundation::Numerics;

template <typename T>
struct DesktopWindow
{
	static T* GetThisFromHandle(HWND const window) noexcept
	{
		return reinterpret_cast<T *>(GetWindowLongPtr(window, GWLP_USERDATA));
	}

	static LRESULT __stdcall WndProc(HWND const window, UINT const message, WPARAM const wparam, LPARAM const lparam) noexcept
	{
		WINRT_ASSERT(window);

		if (WM_NCCREATE == message)
		{
			auto cs = reinterpret_cast<CREATESTRUCT *>(lparam);
			T* that = static_cast<T*>(cs->lpCreateParams);
			WINRT_ASSERT(that);
			WINRT_ASSERT(!that->m_window);
			that->m_window = window;
			SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(that));

			EnableNonClientDpiScaling(window);
		}
		else if (T* that = GetThisFromHandle(window))
		{
			return that->MessageHandler(message, wparam, lparam);
		}

		return DefWindowProc(window, message, wparam, lparam);
	}

	LRESULT MessageHandler(UINT const message, WPARAM const wparam, LPARAM const lparam) noexcept
	{
		switch (message) {
		case WM_DPICHANGED:
		{
			return HandleDpiChange(m_window, wparam, lparam);
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		}

		return DefWindowProc(m_window, message, wparam, lparam);
	}

	// DPI Change handler. on WM_DPICHANGE resize the window
	LRESULT HandleDpiChange(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		HWND hWndStatic = GetWindow(hWnd, GW_CHILD);
		if (hWndStatic != nullptr)
		{
			UINT uDpi = HIWORD(wParam);

			// Resize the window
			auto lprcNewScale = reinterpret_cast<RECT*>(lParam);

			SetWindowPos(hWnd, nullptr, lprcNewScale->left, lprcNewScale->top,
				lprcNewScale->right - lprcNewScale->left, lprcNewScale->bottom - lprcNewScale->top,
				SWP_NOZORDER | SWP_NOACTIVATE);

			if (T* that = GetThisFromHandle(hWnd))
			{
				that->NewScale(uDpi);
			}
		}
		return 0;
	}

	void NewScale(UINT dpi) {

	}

protected:

	using base_type = DesktopWindow<T>;
	HWND m_window = nullptr;
	
};

struct Window : DesktopWindow<Window>
{
	Window() noexcept
	{
		WNDCLASS wc{};
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hInstance = reinterpret_cast<HINSTANCE>(&__ImageBase);
		wc.lpszClassName = L"XAML island in Win32";
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		RegisterClass(&wc);
		WINRT_ASSERT(!m_window);

		WINRT_VERIFY(CreateWindow(wc.lpszClassName,
			L"XAML island in Win32",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			nullptr, nullptr, wc.hInstance, this));

		WINRT_ASSERT(m_window);

		m_scale = InitXaml(m_window);
	}

	const Windows::UI::Xaml::Media::ScaleTransform & InitXaml(HWND wind) {
		Windows::UI::Xaml::Hosting::WindowsXamlManager::InitializeForCurrentThread();

		static DesktopWindowXamlSource source;
		auto interop = source.as<IDesktopWindowXamlSourceNative>();
		check_hresult(interop->AttachToWindow(wind));
		HWND h = nullptr;
		interop->get_WindowHandle(&h);
		SetWindowPos(h, 0, 0, 0, 600, 300, SWP_SHOWWINDOW);

		static Windows::UI::Xaml::Media::ScaleTransform st;
		st.ScaleX(3.0);
		st.ScaleY(3.0);

		Windows::UI::Xaml::Controls::Button b;
		b.RenderTransform(st);
		b.Width(200);
		b.Height(30);

		Windows::UI::Xaml::Controls::TextBlock tb;
		tb.Text(L"Hello Win32 love XAML xx");
		b.Content(tb);

		source.Content(b);
		return st;
	}

	LRESULT MessageHandler(UINT const message, WPARAM const wparam, LPARAM const lparam) noexcept
	{
		// TODO: handle messages here...

		return base_type::MessageHandler(message, wparam, lparam);
	}

	void NewScale(UINT dpi) {

		auto scaleFactor = (float)dpi / 100;

		m_scale.ScaleX(scaleFactor);
		m_scale.ScaleY(scaleFactor);
	}


private:

	DesktopWindowTarget m_target{ nullptr };
	Windows::UI::Xaml::Media::ScaleTransform m_scale = nullptr;
};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	init_apartment(apartment_type::single_threaded);

	Window window;
	
	MSG message;

	while (GetMessage(&message, nullptr, 0, 0))
	{
		DispatchMessage(&message);
	}
}
