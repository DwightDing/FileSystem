//
//  FileSystem.cpp
//
//  Created by DwightDing on 16/6/13.
//  Copyright © 2016年 Ding Chenguang. All rights reserved.
//
#include"FileSystem.h"
#include"FileAndDir.h"
#include"UserMenu.h"

FileSystem::FileSystem()     //初始化函数
{
	root=new Dir();//新建用户后，默认一个目录为用户根目录，文件夹名为root
	root->dirname="root";
	currentDir=root;//当前目录为根目录
	tempfile=0;//文件数量为0
	tempdir=0;//文件夹数量为0
}

FileSystem::~FileSystem()  //虚构函数，删除
{
	delete currentDir;
	delete root;
	delete tempfile;
	delete tempdir;
}

Dir* FileSystem::newDir()   //函数：新建目录
{
	time_t t=time(0);      //创建目录时间
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));//存入系统时间

	Dir *p=new Dir();      //指针指向新建目录
	cin>>p->dirname;       //输入新建目录名
	if(currentDir!=NULL)//如果该目录链表指针不为空
	{
		if(currentDir->dirptr==NULL)//该目录为父目录下的第一个文件夹
		{
			currentDir->dirptr=p;
			p->preDir=currentDir;

			p->dircreatetime=tmp;
			p->altertime=tmp;
		}
		else//该目录下目录链表指针不为空
		{
			Dir *q;//该指针用于遍历
			q=currentDir->dirptr;
			while(q->nextDir!=NULL)//遍历一遍，排除文件夹重名
			{
				if(!strcmp(p->dirname.c_str(),q->dirname.c_str()))//文件夹同名
				{
					cout<<"同级目录不能重名！"<<endl;
				    cout<<"同级目录不能重名999！"<<endl;
					return 0;
				}

				q=q->nextDir;
			}
			if(!strcmp(p->dirname.c_str(),q->dirname.c_str()))////比较最后一个文件名
			{
				cout<<"同级目录不能重名！"<<endl;
				return 0;
			}
			q->nextDir=p;
			p->preDir=currentDir;
			p->dircreatetime=tmp;
			p->altertime=tmp;
		}
		cout<<"目录创建成功！"<<endl;
	}
	else
	{
		cout<<"不能在空目录下创建文件!！"<<endl;
	}
	return currentDir;
}
int FileSystem::newFile()//新建文件
{
	time_t t=time(0);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));
	string ct;

	File *p=new File();
	cin>>p->filename;
	if(currentDir!=NULL)
	{
		//检查有无同名文件
		if(currentDir->fileptr==NULL)//该目录下没有文件
		{
			currentDir->fileptr=p;
			p->fcreatetime=tmp;
			p->altertime=tmp;

		}
		else
		{
			File *q=new File();
			q=currentDir->fileptr;//该目录下存在文件
			while(q->nextFile!=NULL)
			{
				if(!strcmp(p->filename.c_str(),q->filename.c_str()))//同名
				{
					cout<<"该文件已创建，无需重新创建!"<<endl;
					return 0;
				}
				q=q->nextFile;//下一个文件为q所指向文件

			}
			if(!strcmp(p->filename.c_str(),q->filename.c_str()))//同名
			{
				cout<<"该文件已创建，无需重新创建!"<<endl;
				return 0;
			}
			q->nextFile=p;
			p->fcreatetime=tmp;
			p->altertime=tmp;
		}
		cout<<"文件创建成功！"<<endl;
	}
	else
	{
		cout<<"不能在空目录下创建文件!"<<endl;
	}
	return 1;
}
int FileSystem::showDir() //显示当前目录的内容
{
	int dirsize1=0,dirsize2=0;
	Dir *d = new Dir();
	d=currentDir->dirptr;//d表示当前目录下的目录 
	File *f = new File();
	f=currentDir->fileptr;//f表示当前目录下的文件 
	char buf[10];
	string str;
	if (d == NULL && f == NULL) { 
		cout << "当前目录下无任何目录和文件" << endl;
		return 0; 
	}                                                                   
	Dir *d1=new Dir();
	File *d2=new File();

	//遍历当前目录
	cout<<"********************* 当前目录信息 *********************"<<endl;
	cout<<endl;

	cout<<" 目录名称      "<<"此目录下内容数量        "<<"     创建时间"<<"            修改时间"<<endl;
	cout<<endl;
	while (d != NULL) { 

		d1=d->dirptr;
		d2=d->fileptr;

		while(d1!=NULL)
		{
			dirsize1++;//指的是目录的个数
			d1=d1->nextDir;
		}
		while(d2!=NULL)
		{
			dirsize2++;//指的是文件的个数
			d2=d2->nextFile;
		}
		d->dirsize=(dirsize1+dirsize2);//该目录下文件和目录的个数
		itoa(d->dirsize,buf,10);
		str=buf;

		cout<<"    "<<d->dirname<<string(16-(d->dirname.length()),' ')<<d->dirsize<<string(16-str.length(),' ')<<d->dircreatetime<<"    "<<d->altertime<<endl;
		d = d->nextDir; 
		dirsize1=0;
		dirsize2=0;
	} 

	cout<<endl;
	cout<<" 文件名称        "<<"大 小            "<<"创建时间"<<"            修改时间"<<"          文件属性"<<endl;
	cout<<endl; 

	//遍历当前文件指针
	while(f!=NULL)
	{
		itoa(f->filesize,buf,10);
		str=buf;
		if(f->rw)
			cout<<"    "<<f->filename<<string(14-(f->filename.length()),' ')<<f->filesize<<string(10-str.length(),' ')<<f->fcreatetime<<"    "<<f->altertime<<"   可读"<<endl;
		else
			cout<<"    "<<f->filename<<string(14-(f->filename.length()),' ')<<f->filesize<<string(10-str.length(),' ')<<f->fcreatetime<<"    "<<f->altertime<<"   可读可写"<<endl;
		f=f->nextFile;
	}
	return 1;
}

Dir* FileSystem::openDir()//打开目录
{
	Dir *d=new Dir();
	cin>>d->dirname;
	int flag=0;
	FileSystem *fs=new FileSystem;

	if(currentDir==NULL)
	{
		cout<<"当前路径为空，无法进入!"<<endl;
	}
	else
	{
		if(currentDir->dirptr==NULL)//当前目录下没有目录，就不用搜索了
		{
			cout<<"请先创建一个目录!"<<endl;
		}
		else
		{

			Dir *q=new Dir();
			q=currentDir->dirptr;
			while(q!=NULL)
			{
				if(!strcmp(d->dirname.c_str(),q->dirname.c_str()))//找到要进入的目录
				{

					//currentDir->dirptr=q;
					currentDir=q;
					//	cout<<currentDir->dirname;
					flag++;
					break;
				}
				//cout<<q->dirname<<endl;
				q=q->nextDir;

			}
			//cout<<root->dirname;
			if(!flag)
			{
				cout<<"该目录不存在"<<endl;
			}
		}

	}
	return currentDir;
}

Dir* FileSystem::goback()//返回上一级目录
{

	int flag=0;
	if(currentDir!=NULL)
	{
		if(currentDir==root)
		{
			cout<<"当前目录为根目录，无前继目录可以返回!"<<endl;
		}
		else
		{
			currentDir=currentDir->preDir;
		}
	}
	else
	{
		cout<<"无前继目录可以返回!"<<endl;
	}

	return currentDir;
}

void  FileSystem::display()//显示当前路径
{
	vector<Dir*> v;
	int flag=0;
	ifstream in;
	in.open("username_login.txt");
	string username;
	in>>username;
	Dir*p=new Dir();
	p=root;
	if(p==currentDir)
	{
		cout << "DwightDingdeMacBook - Pro:"<<username<<">"<<p->dirname<<"\\";}
	else
	{
		cout<<"user:"<<username<<">";
		Dir *q=new Dir();
		q=currentDir;
		while(q!=NULL)
		{
			v.push_back(q);
			q=q->preDir;
		}
		for(int i=0;i<v.size();i++)
		{
			cout<<v[v.size()-1-i]->dirname<<"\\";
		}

	}
	v.clear();
	in.close();
}

int FileSystem::delete_Dir(Dir *dir) //目录删除子函数①，删除要删除目录下的目录
{
	if(dir->dirptr!=NULL)//不为空
	{

		delete_Dir(dir->dirptr);//把该目录删除掉
	}
	if(dir->nextDir!=NULL)//下一目录不为空
	{
		delete_Dir(dir->nextDir);//把该目录的下一目录也删除掉，递归
	}
	delete dir;
	return 1;
}

int FileSystem::deleteFileInDir(Dir *dir) //目录删除子函数②，删除要删除目录下的文件
{

	if(dir->fileptr!=NULL)
	{
		dir->fileptr=NULL;
	}

	return 1;
}

int FileSystem::deleteDir()//删除目录
{
	Dir *p=new Dir();
	cin>>p->dirname;
	int flag=0;
	if(currentDir->dirptr==NULL)
	{
		cout<<"当前路径下不存在目录!"<<endl;
	}
	else
	{
		Dir *q=new Dir();
		q=currentDir->dirptr;
		if(q->nextDir==NULL)
		{
			if(q->dirname==p->dirname)//如果当前遍历的目录名==需要删除的目录名
			{
				if(q->dirptr==NULL)//如果目录里面没有子目录
				{
					deleteFileInDir(q);//删除文件
					currentDir->dirptr=NULL;
				}
				else//如果目录里面有子目录
				{
					deleteFileInDir(q);//删除文件
					delete_Dir(q->dirptr);//删除子目录
					q->dirptr=NULL;
					currentDir->dirptr=NULL;
				}
				flag++;
			}
		}
		else//下一目录不为空。
		{
			if(q->dirname==p->dirname)//如果当前遍历的目录名==需要删除的目录名
			{
				flag++;
				if(q->dirptr==NULL)
				{
					deleteFileInDir(q);
					currentDir->dirptr=q->nextDir;
				}
				else
				{
					deleteFileInDir(q);
					delete_Dir(q->dirptr);
					q->dirptr=NULL;
					//delete q->dirptr;
					currentDir->dirptr=q->nextDir;
				}
			}
			else//如果当前遍历的目录名！==需要删除的目录名
			{
				while(q->nextDir!=NULL)//遍历
				{
					if(q->nextDir->dirname==p->dirname)//如果下一遍历的目录名==需要删除的目录名
					{
						if(q->nextDir->dirptr==NULL)
						{
							deleteFileInDir(q->nextDir);
							q->nextDir=q->nextDir->nextDir;
						}
						else
						{
							deleteFileInDir(q->nextDir);
							delete_Dir(q->nextDir->dirptr);
							q->nextDir->dirptr=NULL;
							q->nextDir=q->nextDir->nextDir;
						}
						flag++;//判断删除是否成功
						break;
					}
					q=q->nextDir;
				}
			}
		}
		if(flag)
		{
			cout<<"目录删除成功！"<<endl;
		}
		else
		{
			cout<<"不存在指定要删除的目录!"<<endl;
		}
	}


	return 1;

}

int FileSystem::deleteFile() //删除文件
{
	File *p=new File();
	cin>>p->filename;
	int flag=0;
	if(currentDir->fileptr==NULL)
		cout<<"当前路径下不存在文件!"<<endl;
	else
	{
		File *q=new File();
		q=currentDir->fileptr;
		if(q->nextFile==NULL)//下一文件为空
		{
			if(q->filename==p->filename)//判断是否为需要删除的文件
			{
				currentDir->fileptr=NULL;
				flag++;
			}
		}
		else
		{
			if(q->filename==p->filename)
			{
				currentDir->fileptr=q->nextFile;
				flag++;
			}
			else
			{
				while(q->nextFile!=NULL)
				{
					if(q->nextFile->filename==p->filename)
					{
						q->nextFile=q->nextFile->nextFile;
						flag++;
						break;
					}
					q=q->nextFile;
				}
			}
		}
		if(flag)
			cout<<"文件删除成功！"<<endl;
		else
			cout<<"不存在指定要删除的文件!"<<endl;

	}
	return 1;
}

int FileSystem::renameDir()//目录重命名
{
	time_t t=time(0);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));

	//renamedir 原来的名字 新的名字
	Dir *p=new Dir();//旧名字
	cin>>p->dirname;
	Dir *q=new Dir();
	cin>>q->dirname;//新名字
	int flag=0,flag1=0;
	if(currentDir->dirptr==NULL)
		cout<<"当前路径下不存在目录!"<<endl;
	else
	{
		Dir *ptr=new Dir();
		ptr=currentDir->dirptr;
		Dir *ptr1=new Dir();
		ptr1=currentDir->dirptr;
		while(ptr!=NULL)
		{
			if(ptr->dirname==p->dirname)//当前路径下存在要重命名的目录
			{
				flag++;
				while(ptr1!=NULL)
				{
					if(ptr1->dirname==q->dirname)//重命名后的目录名字与原来存在的目录相同
					{
						flag1++;
						break;
					}
					ptr1=ptr1->nextDir;
				}
				if(!flag1)
				{
					ptr->dirname=q->dirname;
					ptr->altertime=tmp;
				}
				break;
			}

			ptr=ptr->nextDir;
		}

		if(!flag)
			cout<<"不存在指定要重命名的目录!"<<endl;
		if(flag)
		{
			if(flag1)
				cout<<"无效重命名，新目录名与原有目录名重名!"<<endl;
			else
				cout<<"目录重命名成功！"<<endl;
		}
	}
	return 1;
}

int FileSystem::renameFile()//重命名文件
{
	time_t t=time(0);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));
	//renamef 原来的名字 新的名字
	File *p=new File();//旧名字
	cin>>p->filename;
	File *q=new File();
	cin>>q->filename;//新名字
	int flag=0,flag1=0;
	if(currentDir->fileptr==NULL)
		cout<<"当前路径下不存在文件!"<<endl;
	else
	{
		File *ptr=new File();
		ptr=currentDir->fileptr;
		File *ptr1=new File();
		ptr1=currentDir->fileptr;
		while(ptr!=NULL)
		{
			if(ptr->filename==p->filename)//当前路径下存在要重命名的目录
			{
				flag++;
				while(ptr1!=NULL)
				{
					if(ptr1->filename==q->filename)//重命名后的目录名字与原来存在的目录相同
					{
						flag1++;
						break;
					}
					ptr1=ptr1->nextFile;
				}
				if(!flag1)
				{
					ptr->filename=q->filename;
					ptr->altertime=tmp;
				}
				break;
			}

			ptr=ptr->nextFile;
		}

		if(!flag)
			cout<<"不存在指定要重命名的文件!"<<endl;
		if(flag)
		{
			if(flag1)
				cout<<"无效重命名，新文件名与原有文件名重名!"<<endl;
			else
				cout<<"文件重命名成功！"<<endl;
		}
	}
	return 1;
}

int FileSystem::readFile()//读出文件,显示文件内容
{
	File *p=new File();
	cin>>p->filename;
	int flag=0;
	if(currentDir->fileptr==NULL)
		cout<<"当前路径下不存在文件!"<<endl;
	else
	{
		File *q=new File();
		q=currentDir->fileptr;
		while(q!=NULL)
		{
			if(q->filename==p->filename)
			{
				cout<<"文件"<<q->filename<<":"<<q->filecontent<<endl;
				cout<<"文件读出成功！"<<endl;
				flag++;
				break;
			}
			q=q->nextFile;
		}
		if(!flag)
			cout<<"不存在指定要打开的文件!"<<endl;

	}
	return 1;
}

int FileSystem::writeFile()//编辑文件
{
	time_t t=time(0);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));

	File *p=new File();
	cin>>p->filename;
	string s;//要编辑的内容
	int flag=0;
	getline(cin,s);
	if(currentDir->fileptr==NULL)
		cout<<"当前路径下不存在文件!"<<endl;
	else
	{
		File *q=new File();
		q=currentDir->fileptr;
		while(q!=NULL)
		{
			if(q->filename==p->filename)
			{

				if(q->rw==false)
				{

					q->filecontent=s;
					q->filesize=s.length()-1;
					q->altertime=tmp;
					flag++;
					cout<<"文件写入成功！"<<endl;
					break;
				}
				else
				{
					cout<<"该文件为只读文件，不能写入!"<<endl;
					return 0;
				}

			}
			q=q->nextFile;
		}
		if(!flag)
			cout<<"不存在指定要编辑的文件!"<<endl;

	}
	return 1;
}

int FileSystem::copyFile()
{
	File *p=new File();
	cin>>p->filename;
	int flag=0;
	tempfile=new File();
	if(currentDir->fileptr==NULL)       //当前目录下没有文件就直接走了
		cout<<"当前路径下不存在文件!"<<endl;
	else							   //当前目录下有文件，就从current->ptr开始查询到相同的
	{
		File *q=new File();
		q=currentDir->fileptr;

		while(q->nextFile!=NULL)
		{
			if(q->nextFile->filename==p->filename)
			{
				tempfile=q->nextFile;

				flag++;
				break;
			}
			else{}
			q=q->nextFile;
		}
		if(currentDir->fileptr->filename==p->filename)//首相
		{
			tempfile=currentDir->fileptr;
			flag++;
		}
		if(flag)//flag=1就是找到了咯
			cout<<"文件复制成功！"<<endl;
		else
			cout<<"不存在指定要复制的文件!"<<endl;
	}

	return 1;
}

int FileSystem::pasteFile()//粘贴文件
{
	int flag=0;
	if(tempfile==NULL) //没复制..就走
	{
		cout<<"不存在复制文件，不能粘贴!"<<endl;
		return 0;
	}

	if(currentDir->fileptr==NULL)//1.复制了 2.当前fileptr空的，直接paste进来
	{
		//currentDir->fileptr=tempfile;
		currentDir->fileptr=new File();
		currentDir->fileptr->fcreatetime=tempfile->fcreatetime;
		currentDir->fileptr->filecontent=tempfile->filecontent;
		currentDir->fileptr->filename=tempfile->filename;
		currentDir->fileptr->filesize=tempfile->filesize;
		cout<<"粘贴文件成功!"<<endl;
	}
	else  //当前fileptr有货，就找nextnext...
	{

		File *q=new File();
		q=currentDir->fileptr;

		while(q->nextFile!=NULL)//直到为空
		{
			if(q->filename==tempfile->filename)
			{
				flag++;
				break;
			}
			q=q->nextFile;
			if(q->nextFile==NULL && q->filename==tempfile->filename)//检验 给flag
			{
				flag++;
			}
		}
		if(currentDir->fileptr->filename==tempfile->filename)//判断链表第一个文件是否与要粘贴的同名
		{
			flag++;
		}

		if(!flag )
		{

			//q->nextFile=tempfile;
			//最后节点交给temp
			q->nextFile=new File();
			q->nextFile->fcreatetime=tempfile->fcreatetime;
			q->nextFile->filecontent=tempfile->filecontent;
			q->nextFile->filename=tempfile->filename;
			q->nextFile->filesize=tempfile->filesize;
			cout<<"文件粘贴成功！"<<endl;

		}
		else
			cout<<"当前文件已存在!"<<endl;



	}


	return 1;
}

int FileSystem::copyDir()//复制目录    
{
	Dir *p=new Dir();
	cin>>p->dirname;
	int flag=0;
	//tempdir=new Dir();
	if(currentDir->dirptr==NULL)//没有目录就不复制了
		cout<<"当前路径下不存在目录!"<<endl;
	else//有 查到放到temp
	{
		Dir *q=new Dir();
		q=currentDir->dirptr;
		while(q!=NULL)
		{
			if(q->dirname==p->dirname)
			{
				tempdir=q;
				flag++;
				break;
			}
			q=q->nextDir;
		}
		if(flag)
			cout<<"目录复制成功！"<<endl;
		else
			cout<<"不存在指定要复制的目录!"<<endl;
	}
	return 1;
}

int FileSystem::pasteDir() //粘贴目录
{

	int flag=0;
	if(tempdir==NULL)
	{
		cout<<"不存在复制目录，不能粘贴!"<<endl;
		return 0;
	}

	Dir *ptr=new Dir();
	ptr=currentDir;
	while(ptr!=NULL)//绝对不能复制到本分支，保证本分支各个节点都不是tempdir
	{
		if(ptr->dirname==tempdir->dirname)//目标 current的爸爸不能是temp
		{
			cout<<"不能将父目录复制到子目录下!"<<endl;
			return 0;
		}
		ptr=ptr->preDir;//回溯
	}

	if(currentDir->dirptr==NULL)//当前目录下没有子目录
	{

		currentDir->dirptr=new Dir();

		if(tempdir->dirptr==NULL )//tempdir没有子目录 直接粘贴自己
		{
			currentDir->dirptr->dircreatetime=tempdir->dircreatetime;
			currentDir->dirptr->dirname=tempdir->dirname;
			currentDir->dirptr->dirsize=tempdir->dirsize;
			currentDir->dirptr->preDir=currentDir;

			pasteFileInDir(tempdir->fileptr,currentDir->dirptr);
		}
		else	//temp有子目录，先贴自己，再贴儿子
		{
			currentDir->dirptr->dircreatetime=tempdir->dircreatetime;
			currentDir->dirptr->dirname=tempdir->dirname;
			currentDir->dirptr->dirsize=tempdir->dirsize;
			currentDir->dirptr->preDir=currentDir;

			pasteFileInDir(tempdir->fileptr,currentDir->dirptr);
			//----自己部分结束
			//把current ptr的ptr给temp的ptr 两边子目录对接
			currentDir->dirptr->dirptr=new Dir();//子目录起始位置开始粘贴
			currentDir->dirptr->dirptr->dircreatetime=tempdir->dirptr->dircreatetime;
			currentDir->dirptr->dirptr->dirname=tempdir->dirptr->dirname;
			currentDir->dirptr->dirptr->dirsize=tempdir->dirptr->dirsize;
			currentDir->dirptr->dirptr->preDir=currentDir->dirptr;
			//子文件复制
			pasteFileInDir(tempdir->dirptr->fileptr,currentDir->dirptr->dirptr);
			//子目录
			SubPasteDir(tempdir->dirptr,currentDir->dirptr->dirptr);//把前面给后面的目标地址
		}

		cout<<"文件粘贴成功！"<<endl;
	}
	else
	{
		Dir *q=new Dir();
		q=currentDir->dirptr;

		while(q->nextDir!=NULL)
		{
			if(q->nextDir->dirname==tempdir->dirname)
			{
				flag++;
				break;
			}
			q=q->nextDir;
			if(q->nextDir==NULL && q->dirname==tempdir->dirname)//判断最后链表最后一个目录是否与要粘贴的同名
			{
				flag++;
			}
		}
		if(currentDir->dirptr->dirname==tempdir->dirname)
		{
			flag++;
		}
		if(!flag)
		{
			q->nextDir=new Dir();
			if(tempdir->dirptr==NULL)
			{
				q->nextDir->dircreatetime=tempdir->dircreatetime;
				q->nextDir->dirname=tempdir->dirname;
				q->nextDir->dirptr->dirsize=tempdir->dirsize;
				q->nextDir->preDir=currentDir;
				//复制文件
				pasteFileInDir(tempdir->fileptr,q->nextDir);

			}
			else
			{
				q->nextDir->dircreatetime=tempdir->dircreatetime;
				q->nextDir->dirname=tempdir->dirname;
				q->nextDir->dirsize=tempdir->dirsize;
				q->nextDir->preDir=currentDir;
				//复制文件
				pasteFileInDir(tempdir->fileptr,q->nextDir);

				q->nextDir->dirptr=new Dir();
				q->nextDir->dirptr->dircreatetime=tempdir->dirptr->dircreatetime;
				q->nextDir->dirptr->dirname=tempdir->dirptr->dirname;
				q->nextDir->dirptr->dirsize=tempdir->dirptr->dirsize;
				q->nextDir->dirptr->preDir=q->nextDir;
				//复制文件
				pasteFileInDir(tempdir->dirptr->fileptr,q->nextDir->dirptr);
				SubPasteDir(tempdir->dirptr,q->nextDir->dirptr);
				cout<<"粘贴目录成功!"<<endl;
			}
		}
		else
			cout<<"当前目录已存在!"<<endl;

	}

	return 1;
}

int FileSystem::SubPasteDir(Dir *dir1,Dir *dir2)//粘贴子函数  1是复制了的目录     2是要复制到的目录
{

	if(dir1->dirptr!=NULL)//1不空，把1放到2里面
	{
		dir2->dirptr=new Dir();
		dir2->dirptr->dircreatetime=dir1->dirptr->dircreatetime;
		dir2->dirptr->dirname=dir1->dirptr->dirname;
		dir2->dirptr->dirsize=dir1->dirptr->dirsize;
		dir2->dirptr->preDir=dir2;
		//文件复制
		pasteFileInDir(dir1->dirptr->fileptr,dir2->dirptr);
		//递归
		SubPasteDir(dir1->dirptr,dir2->dirptr);
	}

	if(dir1->nextDir!=NULL)//1有同级后续 继续复制
	{
		dir2->nextDir=new Dir();
		dir2->nextDir->dircreatetime=dir1->nextDir->dircreatetime;
		dir2->nextDir->dirname=dir1->nextDir->dirname;
		dir2->nextDir->dirsize=dir1->nextDir->dirsize;
		dir2->nextDir->preDir=dir2->preDir;
		//文件复制
		pasteFileInDir(dir1->nextDir->fileptr,dir2->nextDir);


		SubPasteDir(dir1->nextDir,dir2->nextDir);
	}

	return 1;
}

int FileSystem::pasteFileInDir(File *file,Dir *dir)//file要复制的文件，dir复制到的目录
{
	File *file1=new File();
	file1=file;
	Dir *dir1=new Dir();
	dir1=dir;
	if(dir1->fileptr!=NULL)//有
	{
		File *ptr=new File();
		ptr=dir1->fileptr;
		while(ptr->nextFile!=NULL) //同级后续文件复制
		{
			ptr=ptr->nextFile;
		}
		ptr->nextFile=new File();
		ptr->nextFile->fcreatetime=file1->fcreatetime;
		ptr->nextFile->filecontent=file1->filecontent;
		ptr->nextFile->filename=file1->filename;
		ptr->nextFile->filesize=file->filesize;

	}
	else 
	{
		if (file == NULL){
			dir->fileptr = file1;
		}
		else{
		File *ptr = new File();
		ptr = file1;
		File *tempfile = new File();
		tempfile->fcreatetime = file1->fcreatetime;
		tempfile->filecontent = file1->filecontent;
		tempfile->filename = file1->filename;
		tempfile->filesize = file1->filesize;
		ptr = tempfile;
		while (file1->nextFile!=NULL)
		{
			File *tempfile2 = new File();
			tempfile->fcreatetime = file1->fcreatetime;
			tempfile->filecontent = file1->filecontent;
			tempfile->filename = file1->filename;
			tempfile->filesize = file1->filesize;
			ptr->nextFile = tempfile2;
			ptr = ptr->nextFile;
			
		}
		dir->fileptr=tempfile;
		}
	}
	return 1;

}

int FileSystem::filerw()//修改文件属性为可读
{
	time_t t=time(0);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));

	File *p=new File();
	cin>>p->filename;
	int flag=0;

	if(currentDir->fileptr==NULL)
		cout<<"当前路径下不存在文件!"<<endl;
	else
	{
		File *q=new File();
		q=currentDir->fileptr;
		while(q!=NULL)
		{
			if(q->filename==p->filename)
			{

				cout<<"选择修改的属性: 0为可读可写 1为只读"<<endl;
				bool a;
				cin>>a;
				while(q->rw==a)
				{
					cout<<"该文件已为该属性，无需修改!"<<endl;
					cout<<"请重新选择:"<<endl;
					cin>>a;

				}

				if(q->rw==false)
				{
					q->altertime=tmp;
					q->rw=a;
					cout<<"文件已修改为只读!"<<endl;
				}
				else
				{
					q->altertime=tmp;
					q->rw=a;
					cout<<"文件已修改为可读可写!"<<endl;
				}

				flag++;
				break;
			}
			q=q->nextFile;
		}
		if(!flag)
			cout<<"不存在指定要编辑的文件!"<<endl;

	}
	return 1;
}