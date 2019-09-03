// WinToastWrapper.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "wintoastlib.h"

using namespace WinToastLib;

using namespace std;

class CustomHandler : public IWinToastHandler {
public:

	using ::IWinToastHandler::toastActivated;

	void toastActivated() const {
		::IWinToastHandler;
		std::wcout << L"The user clicked in this toast" << std::endl;
		exit(0);
	}

	void toastActivated(int actionIndex) const {
		std::wcout << L"The user clicked on action #" << actionIndex << std::endl;
		//exit(16 + actionIndex);
	}

	void toastDismissed(WinToastDismissalReason state) const {
		switch (state) {
		case UserCanceled:
			std::wcout << L"The user dismissed this toast" << std::endl;
			exit(1);
			break;
		case TimedOut:
			std::wcout << L"The toast has timed out" << std::endl;
			exit(2);
			break;
		case ApplicationHidden:
			std::wcout << L"The application hid the toast using ToastNotifier.hide()" << std::endl;
			exit(3);
			break;
		default:
			std::wcout << L"Toast not activated" << std::endl;
			exit(4);
			break;
		}
	}

	void toastFailed() const {
		::WinToastLib::IWinToastHandler;
		std::wcout << L"Error showing current toast" << std::endl;
		exit(5);
	}
};


enum Results {
	ToastClicked,					// user clicked on the toast
	ToastDismissed,					// user dismissed the toast
	ToastTimeOut,					// toast timed out
	ToastHided,						// application hid the toast
	ToastNotActivated,				// toast was not activated
	ToastFailed,					// toast failed
	SystemNotSupported,				// system does not support toasts
	UnhandledOption,				// unhandled option
	MultipleTextNotSupported,		// multiple texts were provided
	InitializationFailure,			// toast notification manager initialization failure
	ToastNotLaunched				// toast could not be launched
};
int main()
{
	std::wstring appName = L"Console",
		appUserModelID = L"My.Console.Example",
		text = L"Test";

	WinToast::instance()->setAppName(appName);
	WinToast::instance()->setAppUserModelId(appUserModelID);

	if (!WinToast::instance()->initialize()) {
		std::wcerr << L"Error, your system in not compatible!" << std::endl;
		return -1;
	}

	WinToastTemplate templ(WinToastTemplate::ImageAndText02);
	//templ.setTextField(text, WinToastTemplate::FirstLine);
	//templ.addAction(L"Action");
	templ.setDuration(WinToastTemplate::Duration::Short);
	templ.LoadStringToXml(L"<toast><visual><binding template=\"ToastGeneric\"><text>Downloadingyourweeklyplaylist...</text><progress title=\"Weeklyplaylist\" value=\"{aavalue}\" valueStringOverride=\"{dj}\" status=\"Downloading...\"/></binding></visual></toast>");
	templ.addAction(L"Action");

	std::map<winrt::hstring, winrt::hstring> initmap = {
			{L"dj",L"12/44 2"}
	};
	templ.setInitNotificationData(initmap);
	WinToast::instance()->setAppTag(L"ffff");
	WinToast::instance()->setAppGroup(L"hhhh");
	WinToast::instance()->showToast(templ, new CustomHandler());
	Sleep(1000);
	std::map<winrt::hstring, winrt::hstring> map = {
			{L"aavalue",L"0.1"}
	};
	int dddd =0;
	NotificationUpdateResult reslt=WinToast::instance()->update(map, (WinToast::WinToastError*)&dddd);
	std::wcout << dddd << std::endl;
	std::wcout << reslt << std::endl;
	Sleep(15000);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
