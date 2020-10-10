#ifndef COMPONENTES_H_INCLUDED
#define COMPONENTES_H_INCLUDED
#include <windows.h>
#include <tlhelp32.h>
#include "../Biblioteca/CBibliotecaDeComponentes.h"
#include "../Biblioteca/CFuncaoComponentes.h"
#include <gdiplus.h>

#define OFFSET 2

DWORD idProcess;
//Addressbase + EntryPoint
intptr_t baseAddr = 0x00400000+0x63D50;

CEstilos(LPARAM cor){
	if(cor == CObterID(2) || cor == CObterID(21) || cor == CObterID(26) || cor == CObterID(32)){
		CMFP(61, 135, 200);
		CMCP(255,255,255);
	}else if(cor == CObterID(41)){
		CMCB(41,0,0,0);
	}else{
		CFundoT();
		CMCP(255,255,255);				
	}
}

getId(){
	HWND snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 ps32;
	ps32.dwSize = sizeof(PROCESSENTRY32);
	if(snap){
		do{
			if(strcmp(CObterItem(40),ps32.szExeFile) == 0)
				break;
		}while(Process32Next(snap, &ps32));
	}
	
	idProcess = (DWORD) ps32.th32ProcessID;
}

setValues(unsigned int offset[OFFSET], WORD value){
	int i;
	intptr_t addressFinal = baseAddr;
	HWND process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, idProcess);
	if(process){
		for(i=0;i<OFFSET;i++){
			ReadProcessMemory(process,(LPCVOID)addressFinal, &addressFinal, sizeof(addressFinal), NULL);
			addressFinal += offset[i];
		}
		WriteProcessMemory(process,(LPVOID)addressFinal,&value,sizeof(value),NULL);
		CloseHandle(process);
	}
}

getValues(int compId, unsigned int offset[OFFSET]){
	int i;
	char life[255];
	intptr_t addressFinal = baseAddr;
	HWND process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, idProcess);
	if(process){
		for(i=0;i<OFFSET;i++){
			ReadProcessMemory(process,(LPCVOID)addressFinal,&addressFinal,sizeof(addressFinal),NULL);
			addressFinal += offset[i];
		}
	}
	DWORD qtdLife;
	ReadProcessMemory(process,(LPCVOID)addressFinal,&qtdLife,sizeof(DWORD),NULL);
	itoa(qtdLife,life,10);
	CAlterarTexto(compId,life);
	CloseHandle(process);
}

WINAPI refresh(){
	while(TRUE){
		unsigned int vida[OFFSET] = {0x2B530,0x17B4};	
		getValues(4,vida);
		unsigned int saude[OFFSET] = {0x2B530,0x17B8};	
		getValues(8,saude);
		unsigned int poder[OFFSET] = {0x2B530,0x17BC};	
		getValues(12,poder);
		unsigned int ponto[OFFSET] = {0x2B530,0x17C0};		
		getValues(16,ponto);
		unsigned int lifeBruxa[OFFSET] = {0x272*0x4+0x2b538,0x17B8};		
		getValues(30,lifeBruxa);
		unsigned int posx[OFFSET] = {0x2B530,0x1720};		
		getValues(43,posx);
		unsigned int posy[OFFSET] = {0x2B530,0x1724};		
		getValues(46,posy);
		Sleep(700);
	}
} 

WINAPI attMemory(){
	while(1){
		if(CObterCheck(20)){
			unsigned int pulo[OFFSET] = {0x2B530,0x172B};
			setValues(pulo,60);
		}
		
		if(CObterCheck(19)){
			unsigned int imortal[OFFSET] = {0x2B530,0x17D3};
			setValues(imortal,64);
		}
		
		if(CObterCheck(23)){
			unsigned int verde[OFFSET] = {0x2B530,0x17E0};
			setValues(verde,1);
		}
		
		if(CObterCheck(24)){
			unsigned int amarela[OFFSET] = {0x2B530,0x17DC};
			setValues(amarela,1);
		}
		
		if(CObterCheck(25)){
			unsigned int azul[OFFSET] = {0x2B530,0x17E4};
			setValues(azul,1);
		}
		
		if(CObterCheck(26)){
			unsigned int vermelha[OFFSET] = {0x2B530,0x17DA};
			setValues(vermelha,1);
		}
		
		if(CObterCheck(34)){
			unsigned int semRec[OFFSET] = {0x272*0x4+0x2b538,0x17D3};
			setValues(semRec,0);
		}
	}
}

preencherLista(){
	HWND snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 ps32;
	ps32.dwSize = sizeof(PROCESSENTRY32);
	if(snap){
		do{
			if(strcmp(ps32.szExeFile,"svchost.exe") != 0){
				SendMessageA(hcomp[Construtora][40],CB_ADDSTRING, (WPARAM)NULL, (LPARAM) ps32.szExeFile);
			}
		}while(Process32Next(snap, &ps32));
	}
	SendMessage(hcomp[Construtora][40],CB_DELETESTRING,(WPARAM) 0,(LPARAM)NULL);
	SendMessage(hcomp[Construtora][40],CB_SETCURSEL,(WPARAM)0,(LPARAM)NULL);
}


CComponentesGraficos(){
	CModIcone("icone.ico");
	CImagem("Banner.bmp",0,0,273,135);
	CGroupBox(1,1,145,273,140);
	CTexto(2,"Ronald",12,137,50,15);
	CTexto(3,"Vida:",15,155,50,15);
	CTexto(4,"000000000",50,155,100,15);
	CCaixaDeTextoB(5,12,170,90,20);
	CBotaoImagem(6,"Apply.ico",15,15,101,171,25,19);
	CTexto(7,"Saúde:",147,155,50,15);
	CTexto(8,"000000000",193,155,100,15);
	CCaixaDeTextoB(9,148,170,90,20);
	CBotaoImagem(10,"Apply.ico",15,15,237,171,25,19);
	CTexto(11,"Poder:",12,200,50,15);
	CTexto(12,"000000000",55,200,100,15);
	CCaixaDeTextoB(13,12,215,90,20);
	CBotaoImagem(14,"Apply.ico",15,15,101,216,25,19);
	CTexto(15,"Ponto:",148,200,80,15);
	CTexto(16,"000000000",190,201,100,15);
	CCaixaDeTextoB(17,148,215,90,20);
	CBotaoImagem(18,"Apply.ico",15,15,237,216,25,19);
	CCheckBox(19,"Imortal",60,250,80,20);
	CCheckBox(20,"Super pulo",150,250,100,20);
	CGroupBox(21,1,295,273,40);
	CTexto(22,"Chaves",12,286,50,15);
	CCheckBox(23,"Verde",5,305,60,20);
	CCheckBox(24,"Amarelo",65,305,80,20);
	CCheckBox(25,"Azul",140,305,60,20);
	CCheckBox(26,"Vermelho",191,305,80,20);
	CGroupBox(27,1,345,273,52);
	CTexto(28,"Bruxa",12,336,45,15);
	CTexto(29,"Vida:",17,352,45,15);
	CTexto(30,"000000000",52,352,100,15);
	CCaixaDeTextoB(32,15,367,90,20);
	CBotaoImagem(33,"Apply.ico",15,15,101,368,25,19);
	CCheckBox(34,"Sem recuperação",135,360,150,20);
	CGroupBox(35,1,407,273,40);
	CTexto(36,"Teletransporte",12,398,150,15);
	CBotao(37,"Atravessar parede",5,417,130,23);
	CBotao(38,"Final da fase",140,417,130,23);
	CTexto(39,"Processo:",20,458,80,15); 
	CLSuspensa(40,1,NULL,90,455,150,150);
	CGroupBox(41,-2,490,280,50);
	CTexto(42,"POS X:",50,493,80,15);
	CTexto(43,"000",98,493,80,15);  
	CTexto(44,"|",130,493,80,15);
	CTexto(45,"POS Y:",141,493,80,15);
	CTexto(46,"000",188,493,80,15);
	preencherLista();
	CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) refresh,NULL,0,NULL);
	CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) attMemory, NULL,0,NULL);	  
}

CComandos(WPARAM id){
		switch(id){
			case 6:{
				unsigned int vida[OFFSET] = {0x2B530,0x17B4};
				setValues(vida,atoi(CObterTexto(5)));
				SetWindowText(hcomp[Construtora][5],"");		
				break;
			}
			case 10:{
				unsigned int vida[OFFSET] = {0x2B530,0x17B8};
				setValues(vida,atoi(CObterTexto(9)));
				SetWindowText(hcomp[Construtora][9],"");		
				break;
			}
			case 14:{
				unsigned int vida[OFFSET] = {0x2B530,0x17BC};
				setValues(vida,atoi(CObterTexto(13)));
				SetWindowText(hcomp[Construtora][13],"");		
				break;
			}
			case 18:{
				unsigned int vida[OFFSET] = {0x2B530,0x17C0};
				setValues(vida,atoi(CObterTexto(17)));
				SetWindowText(hcomp[Construtora][17],"");		
				break;
			}
			case 33:{
				unsigned int vida[OFFSET] = {0x272*0x4+0x2b538,0x17B8};
				setValues(vida,atoi(CObterTexto(32)));
				SetWindowText(hcomp[Construtora][32],"");		
				break;
			}
			case 19:{
				CCheck(19);
				break;
			}
			case 20:{
				CCheck(20);
				break;
			}
			case 23:{
				CCheck(23);
				break;
			}
			case 24:{
				CCheck(24);
				break;
			}
			case 25:{
				CCheck(25);
				break;
			}
			case 26:{
				CCheck(26);
				break;
			}
			case 34:{
				CCheck(34);
				break;
			}
			case 37:{
				unsigned int atravessa[OFFSET] = {0x2B530,0x1720};
				setValues(atravessa,atoi(CObterTexto(43))+3);
				break;
			}
			case 38:{
				unsigned int finalFaseX[OFFSET] = {0x2B530,0x1720};
				setValues(finalFaseX,370);
				unsigned int finalFaseY[OFFSET] = {0x2B530,0x1724};
				setValues(finalFaseY,58);
				break;
			}
			default:{
				break;
			}
		}
		if(HIWORD(id) == CBN_SELCHANGE){
			getId();
		}
}
#endif
