//
// Created by fenteale on 2/24/21.
//

#ifndef OFLAUNCHER_STAINLESS_OFSRUNEXE_H
#define OFLAUNCHER_STAINLESS_OFSRUNEXE_H

#include <OFFilesystem.h>

#if WIN32

#include <Windows.h>
#define EXENAME	"oflauncher.exe"

void RunLauncher(fs::path ptl) {
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcessA (
		ptl.string().c_str(),
		"-force-run",
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
		);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}


#else
#include <unistd.h>

#define EXENAME "oflauncher"

void RunLauncher(fs::path ptl) {
	execl(ptl.string().c_str(), "-force-run", nullptr);
}
#endif

#endif // OFLAUNCHER_STAINLESS_OFSRUNEXE_H
