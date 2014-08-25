#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <sstream>
#include <string>
#include <comdef.h>
#include <dxgi.h>

// Safety first.
#define SAFE_DELETE_ARRAY(x)	if (x) { delete[] x; x = nullptr; }
#define SAFE_DELETE(x)			if (x) { delete x; x = nullptr; }
#define SAFE_RELEASE(x)			if (x) { x->Release(); x = nullptr; }

// Skriver ut lite användbar information om ett HRESULT.
// Felkoder med förklarningar tagna från denna fil http://download.microsoft.com/download/9/5/E/95EF66AF-9026-4BB0-A41D-A4F81802D92C/[MS-ERREF].pdf.
inline static std::wstring GetErrorStringW(HRESULT hr)
{
	switch (hr)
	{
	case S_OK:
		return L"S_OK: No error occurred.";

	case E_OUTOFMEMORY:
		return L"E_OUTOFMEMORY: Direct3D or Direct2D could not allocate sufficient memory to complete the call.";

	case E_INVALIDARG:
		return L"E_INVALIDARG: An invalid parameter was passed to the returning function.";

	case S_FALSE:
		return L"S_FALSE: Alternate success value, indicating a successful but nonstandard completion (the precise meaning depends on context).";

	case E_NOTIMPL:
		return L"E_NOTIMPL: The method call isn't implemented with the passed parameter combination.";

	case E_FAIL:
		return L"E_FAIL: Attempted to create a device with the debug layer enabled and the layer is not installed.";

	case DXGI_ERROR_WAS_STILL_DRAWING:
		return L"DXGI_ERROR_WAS_STILL_DRAWING: The previous blit operation that is transferring information to or from this surface is incomplete.";

	case DXGI_ERROR_INVALID_CALL:
		return L"DXGI_ERROR_INVALID_CALL: The method call is invalid. For example, a method's parameter may not be a valid pointer.";

	case E_POINTER:
		return L"E_POINTER: A nullptr was passed to the returning function.";

	case E_NOINTERFACE:
		return L"E_NOINTERFACE: The specified class does not implement the requested interface, or the controlling IUnknown does not expose the requested interface.";

	case CLASS_E_NOAGGREGATION:
		return L"CLASS_E_NOAGGREGATION: This class cannot be created as part of an aggregate.";
		
	case REGDB_E_CLASSNOTREG:
		return L"REGDB_E_CLASSNOTREG: A specified class is not registered in the registration database. Also can indicate that the type of server you requested in the CLSCTX enumeration is not registered or the values for the server types in the registry are corrupt.";

	case 0x80070003L:
	case STG_E_PATHNOTFOUND:
	case ERROR_PATH_NOT_FOUND:
	case ERROR_FILE_NOT_FOUND:
		return L"ERROR_PATH_NOT_FOUND: The system cannot find the path specified.";

	default:
		return L"UNKNOWN";
	}
}

// Funktion för felsökning.
inline static void ReportError(HRESULT hr, const char* function, const char* file, UINT line)
{
	std::wstringstream wss;
	wss << "Error #" << std::hex << std::showbase << hr << std::dec << ":" << std::endl << 
		   GetErrorStringW(hr) << std::endl <<
		   "In function: " << function << std::endl <<
		   "In file: " << file << std::endl <<
		   "At line: " << line;

	MessageBox(nullptr, wss.str().c_str(), nullptr, MB_ICONERROR);
}

// Makro för felsökning. 
#define HR(x) if (FAILED(x)) 							\
{														\
	ReportError(x, __FUNCTION__, __FILE__, __LINE__);	\
	return x;											\
}

#define HR_NORET(x) if (FAILED(x)) { ReportError(x, __FUNCTION__, __FILE__, __LINE__) }