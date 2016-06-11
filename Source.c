#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"

const char g_szClassName[] = "proiect tp";
#define ID_button1 1000
#define ID_button2 1001
#define ID_button3 1002
#define ID_combo 1003

typedef struct nodcateg
{
	char nume[20];
	//struct nodarbprod *pr;
	struct nodcateg *next;
}nodcateg;

typedef struct nodsite
{
	char nume_site[20];
	struct nodsite* next;
	struct nodcateg* p;
}nodsite; 

nodsite *prim = NULL, *ultim = NULL;

void ad_nod_site(char *numesite)
{
	nodsite *nou;
	nou = (nodsite*)malloc(sizeof(nodsite));
	nou->next = NULL;
	strcpy(nou->nume_site, numesite);
	if (prim == NULL)
	{
		prim = nou;
		ultim = nou;
	}
	else
	{
		ultim->next = nou;
		ultim = nou;
	}
}

int gasit(char *numesite)
{
	nodsite *p=prim;
	while (p != NULL)
	{
		if (strcmp(p->nume_site, numesite) == 0) return 1;
	}
	return 0;
}


BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
		{
							char *nume_site,fissite[20];
							FILE *f;
							int lungime_sir_nume_site;
							lungime_sir_nume_site = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT1));
							if (lungime_sir_nume_site == 0) MessageBox(hwnd, "Nu ai introdus nimic!", "Atentionare", MB_OK);
							else
							{
								nume_site = (char*)malloc(lungime_sir_nume_site + 1);
								GetDlgItemText(hwnd, IDC_EDIT1, nume_site, lungime_sir_nume_site + 1);
								strcpy(fissite, nume_site);
								strcat(fissite, ".txt");
								f = fopen(fissite, "r");
								if (f != NULL && !gasit(nume_site))
								{
									ad_nod_site(nume_site);
									EndDialog(hwnd, 0);
								}
								else MessageBox(hwnd, "Siteul nu exista sau a fost deja introdus", "Atentionare", MB_OK);
							}
		}
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, IDD_DIALOG1);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND h;
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			{
				case ID_button1:
				{
								   int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AboutDlgProc);
								   if (ret == -1) MessageBox(hwnd, "Eroare creare dialog", "Eroare", MB_OK | MB_ICONERROR);
				}
				case ID_combo:
				{
								 
				}
			}
		default:
			break;
		}
	case WM_CREATE:
	{
					  ////////Buton adaugare site
					  h = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Adauga site", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 90, 40, hwnd, (HMENU)ID_button1, NULL, NULL);
					  if (h == NULL) MessageBox(hwnd, "Butonul1 nu a fost creat", "Eroare", MB_OK | MB_ICONERROR);

					  /////////////Buton afisare site
					  h = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Afiseaza site", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 60, 90, 40, hwnd, (HMENU)ID_button2, NULL, NULL);
					  if (h == NULL) MessageBox(hwnd, "Butonul2 nu a fost creat", "Eroare", MB_OK | MB_ICONERROR);

					  /////////////Buton cautare produs
					  h = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Cauta produs", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 110, 90, 40, hwnd, (HMENU)ID_button3, NULL, NULL);
					  if (h == NULL) MessageBox(hwnd, "Butonul3 nu a fost creat", "Eroare", MB_OK | MB_ICONERROR);

					  ///COMBOBOX
					  h = CreateWindowEx(WS_EX_WINDOWEDGE, "COMBOBOX", "", WS_VISIBLE | WS_CHILD|CBS_DROPDOWNLIST | LBS_COMBOBOX, 150, 70, 200, 250, hwnd, (HMENU)ID_combo, NULL, NULL);
					  if (h == NULL) MessageBox(hwnd, "Combobox nu a fost creat", "Eroare", MB_OK | MB_ICONERROR);

	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"proiect",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 700, 300,
		NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
