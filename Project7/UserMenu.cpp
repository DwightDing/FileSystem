//
//  UserMenu.cpp
//
//  Created by DwightDing on 16/6/13.
//  Copyright © 2016年 Ding Chenguang. All rights reserved.
//

#include"UserMenu.h"
#include"FileAndDir.h"
#include"FileSystem.h"
#include <windows.h>

UserMenu::UserMenu()
{

}
UserMenu::~UserMenu()
{

}

void UserMenu::MainMenu()  //欢迎界面
{
	UserMenu usermenu;     //用UserMenu类定义的类型
	string s;
	while (1)
	{
		system("cls");         //清屏函数
		cout << "欢迎使用用户文件系统\n";
		cin >> s;
		if (s == "login")
		{
			usermenu.Login();
		}
		else if (s == "version")
		{
			cout << "Version 1.0 Ding Chenguang 201326811305\nCopyright(C)dwightding.cn All rights reserve\n";
			system("pause");
		}
	}

}

void UserMenu::Login()//用户登录界面
{
	UserMenu menu;
	string username, password;
	string readusername, readpassword;
	int flag = 0;
	cin >> username;
	if (username == "#BACKTOMAIN")
	{
		menu.MainMenu();
	}
	cin >> password;
	if (password == "#BACKTOMAIN")
	{
		menu.MainMenu();
	}

	while (!flag)
	{
		ifstream inFile;
		inFile.open("user_info.txt");
		inFile >> readusername >> readpassword;
		while (!inFile.eof())
		{
			if (readusername == username && readpassword == password)
			{
				flag++;
				break;
			}
			else
			{
				inFile >> readusername >> readpassword;
			}
		}
		if (!flag)//flag==0
		{
			cout << "login error invalid username or password please try again" << endl;
			cout << "username：";
			cin >> username;
			if (username == "#BACKTOMAIN")
			{
				menu.MainMenu();
			}
			cout << "password：";
			cin >> password;
			if (password == "#BACKTOMAIN")
			{
				menu.MainMenu();
			}

		}
		ofstream out;//保存用
		out.open("username_login.txt");
		if (flag)
		{
			out << username << endl;
		}
		out.close();
		inFile.close();

	}

	Sleep(500);
	menu.FunctionMenu();//进入功能界面
}
void UserMenu::FunctionMenu()//功能界面
{
	FileSystem fs;
	UserMenu menu;
	string s;
	time_t t = time(0);      //创建目录时间
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));//存入系统时间
	cout << "Welcome To FileSystem Powered By Ding Chenguang|" << tmp << endl;
	while (1)
	{

		fs.display();
		while (cin >> s)
		{
			if (s == "mkdir")
				fs.newDir();
			else if (s == "mk")
				fs.newFile();
			else if (s == "ls")
				fs.showDir();
			else if (s == "cd")
				fs.openDir();
			else if (s == "cls")
				system("cls");
			else if (s == "logout")
				menu.MainMenu();
			else if (s == "cd..")
				fs.goback();
			else if (s == "exit")
				exit(0);
			else if (s == "back")
				menu.FunctionMenu();
			else  if (s == "-help" || s == "-h")
			{
				//输出帮助文档
				menu.HelpWord();
				menu.FunctionMenu();
			}
			else if (s == "rmdir")
				fs.deleteDir();
			else if (s == "rm")
				fs.deleteFile();
			else if (s == "renamedir")
				fs.renameDir();
			else if (s == "renamefile")
				fs.renameFile();
			else if (s == "read")
				fs.readFile();
			else if (s == "vi")
				fs.writeFile();
			else if (s == "copydir")
				fs.copyDir();
			else if (s == "pastedir")
				fs.pasteDir();
			else if (s == "copyfile")
				fs.copyFile();
			else if (s == "pastefile")
				fs.pasteFile();
			else if (s == "alterfile")
				fs.filerw();

			//各指令使用方式
			else if (s == "mkdir+?")
				cout << "创建一个目录: mkdir 目录名 (例:mkdir a)" << endl;
			else if (s == "mk+?")
				cout << "创建一个文件: mk   文件名 (例:mk   a)" << endl;
			else if (s == "ls+?")
				cout << "显示当前路径下的目录和文件: ls " << endl;
			else if (s == "cd+?")
				cout << "进入下级目录: cd 目录名 (例:cd a)" << endl;
			else if (s == "cls+?")
				cout << "清 屏: cls " << endl;
			else if (s == "logout+?")
				cout << "注 销(返回欢迎界面): logout " << endl;
			else if (s == "cd..+?")
				cout << "返回上级目录: cd.. " << endl;
			else if (s == "exit+?")
				cout << "退出系统: exit" << endl;
			else if (s == "back+?")
				cout << "返回上级菜单: back " << endl;
			else if (s == "-help+?")
				cout << "显示帮助文档: -help" << endl;
			else if (s == "rmdir+?")
				cout << "删除一个目录: rmdir 目录名 (例:rmdir a)" << endl;
			else if (s == "rm+?")
				cout << "删除一个文件: rm   文件名 (例:rm   a)" << endl;
			else if (s == "renamedir+?")
				cout << "重命名目录: renamedir 旧目录名 新目录名 (例:renamedir a b)" << endl;
			else if (s == "renamefile+?")
				cout << "重命名文件: renamefile   旧文件名 新文件名 (例:renamefile   a b)" << endl;

			else if (s == "read+?")
				cout << "读出文件: read 文件名 (例:read a)" << endl;
			else if (s == "vi+?")
				cout << "写入文件: vi 文件名 编辑内容 (例:vi a content)" << endl;

			else if (s == "copydir+?")
				cout << "复制目录: copydir 目录名 (例:copydir a)" << endl;
			else if (s == "pastedir+?")
				cout << "粘贴目录: pastedir " << endl;
			else if (s == "copyfile+?")
				cout << "复制文件: copyfile 文件名 (例:copyfile a)" << endl;
			else if (s == "pastfile+?")
				cout << "粘贴文件: pastfile " << endl;
			else if (s == "alterfile+?")
				cout << "修改文件读写属性: alterfile 文件名  (例:alterfile a)" << endl;
			else
			{
				cout << "找不到对应指令,请重新输入" << endl;
			}


			fs.display();

		}



	}
}

void UserMenu::HelpWord()//帮助文档
{
	cout << "你可能需要以下帮助：" << endl;
	cout << "	目录操作:\n"
		<< "		mkdir		新建目录\n"
		<< "		rmdir			删除目录      \n"
		<< "		renamedir	重命名目录    \n"
		<< "		copydir		复制目录      \n"
		<< "		pastedir		粘贴目录      \n"
		<< "		ls			显示当前路径下的文件夹和文件\n"
		<< "		opendir		打开目录      \n"
		<< "		cd..		返回上一级目录\n"
		<< "	文件操作:\n"
		<< "		mk			新建文件\n"
		<< "		rm			删除文件\n"
		<< "		renamefile	重命名文件\n"
		<< "		copyfile	复制文件\n"
		<< "		pastefile	粘贴文件\n"
		<< "		read		打开文件\n"
		<< "		vi			编辑文件\n"
		<< "		alertfile	修改文件属性\n"
		<< "	系统指令:\n"
		<< "		clear		清屏\n"
		<< "		cancel		注销\n"
		<< "		exit		直接退出      \n"
		<< "		back		返回上一级菜单\n";
}

