#include "tesseractocr.h"

bool Compare_Mat_Text(cv::Mat mat, QString text, bool fight_jiaozhun, bool is_black)
{
	cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);
	cv::subtract(mat, cv::Scalar(100, 100, 100), mat);
	cv::imwrite(".\\temp.png", mat);
	//myShellExecute(TEXT("runas"), TEXT("cmd"), TEXT("/c tesseract temp.png output -l chi_sim"), SW_HIDE);
	if (!fight_jiaozhun)
	{
		ShellExecute(NULL, TEXT("runas"), TEXT("cmd"), TEXT("/c tesseract temp.png output -l chi_sim"), NULL, SW_HIDE);
	}
	else
	{
		ShellExecute(NULL, TEXT("runas"), TEXT("cmd"), TEXT("/c tesseract temp.png output -l chi_sim fight"), NULL, SW_HIDE);
	}
	std::ifstream ifs("output.txt", std::ios::in);
	std::string buf;
	std::getline(ifs, buf);
	ifs.close();
	if (text == QString(buf.data()))
	{
		/*qDebug() << buf.c_str();
		qDebug() << text;*/
		return true;
	}
	else
	{
		/*qDebug() << 1;
		qDebug() << buf.c_str();
		qDebug() << text;*/
		return false;
	}
}

void Get_Mat_Number(cv::Mat mat, long(&arr)[3])
{
	cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);
	cv::subtract(mat, cv::Scalar(100, 100, 100), mat);
	cv::imwrite(".\\temp.png", mat);
	//ShellExecute(NULL, TEXT("runas"), TEXT("cmd"), TEXT("/c tesseract temp.png output digits"), NULL, SW_HIDE);
	myShellExecute(TEXT("runas"), TEXT("cmd"), TEXT("/c tesseract temp.png output digits"), SW_HIDE);
	std::ifstream ifs("output.txt", std::ios::in);
	std::string buf;
	int i = 0;
	while (std::getline(ifs, buf)&& i<3)
	{
		qDebug() << QString(buf.data());
		std::istringstream ss(buf);
		ss >> arr[i];
		qDebug() << arr[i];
		i++;
	}
}

void myShellExecute(LPCTSTR lpOperation, LPCTSTR lpFile, LPCTSTR lpParameters, INT nShowCmd)
{
	SHELLEXECUTEINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cbSize = sizeof(si);
	si.fMask = SEE_MASK_NOCLOSEPROCESS;//see mask nocloseprocess
	si.lpVerb = lpOperation;
	si.lpFile = lpFile;
	si.nShow = nShowCmd;
	si.lpParameters = lpParameters;

	ShellExecuteEx(&si);

	DWORD dwExitCode;
	GetExitCodeProcess(si.hProcess, &dwExitCode);
	while (dwExitCode == STILL_ACTIVE)
	{
		Sleep((DWORD)5);
		GetExitCodeProcess(si.hProcess, &dwExitCode);
	}

	CloseHandle(si.hProcess);
}