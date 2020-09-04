using namespace std;
#include<bits/stdc++.h>
#define random(a,b) (rand()%(b-a+1))+a
ofstream mycout("out.txt",ios::out);
struct pig
{
	int species; //����Ϊ1 С����Ϊ2 ��׻���Ϊ3 
	int id; 	//���
	int styid;  //��Ȧ��� 
	int gday; 	//�ɳ�����(һ���°�30���) 
	int infected=0; //����ȾΪ1��û����ȾΪ0 
	double weight; //���� 
	pig *next;
};
class pigsty
{
	private:
		pig *head=NULL;
		int isblack=0; //��ȦΪ����ȦΪ1���Ǻ�Ϊ0 
		int sum=0;
		int isinfected=0; //��Ȧ�и�Ⱦ��Ϊ1, û��Ϊ0
		int infectsum=0; 
	public:
		pigsty();				//��ʼ�� 
		int getspecies(int i);	//��ȡ������Ϣ 
		int getgday(int i);		//��ȡ�ɳ�������Ϣ 
		double getweight(int i);//��ȡ���� 
		double getprice();		//��ȡ��Ǯ
		void addpig(pig*p);		//������Ҫ���ڳ�ʼ��
		void insert(int i,int j);      //������Ҫ���ڹ������ 
		void clear();	             //���ָ�Ⱦ���뿪������Ȧ����ȫ����� 
		int getsumspecies(int i);	//��ȡĳ��������� 
		int getsum()
		{
			return sum;
		}
		int getisblack()
		{
			return isblack;
		}
		int getisinfect()
		{
			return isinfected;
		}
		int getinfectsum()
		{
			return infectsum;	
		}                
		pig* gethead()
		{
			return head;
		}
		void setsum(int i)
		{
			sum=i;
		}
		void sethead(pig *p)
		{
			head=p;
		}
		void setisblack(int i)//���ú���Ȧ,1Ϊ����Ȧ��0Ϊ�Ǻ���Ȧ
		{
			isblack=i;
		}
		void setisinfect(int i)
		{
			isinfected=i;
		}
		void infectgame()
		{
			if(head==NULL)
			return;
			isinfected=1;
			infectsum++;
			pig *p;
			p=head;
			p->infected=1;
		}
		void addinfect()
		{
			srand((unsigned)time(0));
			pig *p;
			p=head;
			while(p)
			{
				if(p->infected!=1)
				{
					if(random(1,100)<=50)
					{
						p->infected=1;
						infectsum++;
					}
				}
				p=p->next;
			}
		}
};
pigsty ps[100];
pigsty::pigsty()
{
	int sum=0;
	int isblack=0;
	head=NULL;
}
int pigsty::getspecies(int i) 
{
	pig *p=head;
	for(int k=0;k<i&&p!=NULL;k++)
	{
		p=p->next;
	}
	return p->species;
}
int pigsty::getgday(int i)
{
	pig *p=head;
	for(int k=0;k<i&&p!=NULL;k++)
	{
		p=p->next;
	}
	return p->gday;
}
double pigsty::getweight(int i)
{
	pig *p=head;
	for(int k=0;k<i&&p!=NULL;k++)
	{
		p=p->next;
	}
	return p->weight;
}
double pigsty::getprice()
{
	double sellprice=0;
	if(head==0)
	return 0;
	int day,flag=0;
	pig*p=head,*p1=p;
	while(p)
	{
		day=p->gday;
		if(day>=360||p->weight>75)
		{
			if(sum==1)
			{
			setisblack(0);
			head=NULL;
			delete p;
			sum--;
			break;
			}
			if(p->species==1)
			{
				sellprice+=30*p->weight;
			}
			if(p->species==2)
			{
				sellprice+=14*p->weight;
			}
			if(p->species==3)
			{
				sellprice+=12*p->weight;
			}
			p1->next=p->next;
			delete p;
			p=p1->next;
			sum--;
			continue;
		}
		else if(flag==0)
		{
			flag=1;
			head=p;
		}
		p1=p;
		p=p1->next;
	}
	return sellprice;
}
void pigsty::addpig(pig *p)
{
	sum++;
	p->next=NULL;
	if(head==NULL)
	{
		head=p;
	}
	else 
	{
		pig*p1=head;
		while(p1->next)
		{
			p1=p1->next;
		}
	p1->next=p;
	}
}
int pigsty::getsumspecies(int i)
{
	int count=0;
	pig *p=head;
	for(int k=0;k<sum&&p!=NULL;k++)
	{
		if(p->species==i)
		count++;
		p=p->next;
	}
	return count;
}
void pigsty::clear()
{
	if(head==NULL)
	{
		return;
	}
	else 
	{
		pig*p=head;
		pig*p1=p;
		sum=0;
		setisblack(0);
		head=NULL;
		while(p)
		{
			p1=p;
			p=p->next;
			delete p1;
		}
		delete p;
	}
}
int getallpig(pigsty ps[])
{
	int count=0;
	for(int i=0;i<100;i++)
	{
		count+=ps[i].getsum();
	}
	return count;
}
int getallinfectpig(pigsty ps[])
{
	int count=0;
	for(int i=0;i<100;i++)
	{
		count+=ps[i].getinfectsum();
	}
	return count;
}
int getallpig1(pigsty ps[])
{
	int count=0;
	for(int i=0;i<100;i++)
	{
		count+=ps[i].getsumspecies(1);
	}
	return count;
}
int getallpig2(pigsty ps[])
{
	int count=0;
	for(int i=0;i<100;i++)
	{
		count+=ps[i].getsumspecies(2);
	}
	return count;
}
int getallpig3(pigsty ps[])
{
	int count=0;
	for(int i=0;i<100;i++)
	{
		count+=ps[i].getsumspecies(3);
	}
	return count;
}
void buypig(pigsty ps[])
{
	srand((unsigned)time(0));
	int pig1=random(0,15);
	int pig2=random(0,15);
	int pig3=random(0,15);
	mycout<<"����"<<pig1<<"ֻ����"<<pig2<<"ֻС����"<<pig3<<"ֻ�󻨰���"<<endl; 
	while(pig1--)
	{
		for(int i=0;i<100;i++)
		{
			if(ps[i].getisblack()==1&&ps[i].getsum()<10)
			{
				ps[i].insert(1,i);
				break; 
			}
			if(ps[i].gethead()==NULL)
			{
				ps[i].insert(1,i);
				ps[i].setisblack(1);
				break;
			}
		}		
	}	
	
	while(pig2--)
	{
		int ave=getallpig(ps)/100+1;
		for(int i=0;i<100;i++)
		{
			if(ps[i].getisblack()==0&&ps[i].getsum()<=ave)
			{
				ps[i].insert(2,i);
				break; 
			}
			if(ps[i].gethead()==NULL)
			{
				ps[i].insert(2,i);
				ps[i].setisblack(0);
				break;
			}
		}
	}
	while(pig3--)
	{
		int ave=getallpig(ps)/100+1;
		for(int i=0;i<100;i++)
		{
			if(ps[i].getisblack()==0&&ps[i].getsum()<=ave)
			{
				ps[i].insert(3,i);
				break; 
			}
			if(ps[i].gethead()==NULL)
			{
				ps[i].insert(3,i);
				ps[i].setisblack(0);
				break;
			}
		}
	}
}
void start(pigsty ps[])//����ʼ����Ȧ��ʼ�� 
{
	int count=1000;	//��ʼ�ȷ�400ֻ�� 
	pig *p;
	srand((unsigned)time(0));
	while(count--)
	{
		p=new pig;
		p->species=random(1,3);
		p->weight=random(20,50);
		p->gday=0;
		for(int i=0;i<100;i++)
		{
			if(p->species==1&&(ps[i].getisblack()==1||ps[i].gethead()==NULL)&&ps[i].getsum()<4)
			{
				p->id=ps[i].getsum();
				p->styid=i;
				ps[i].addpig(p);
				ps[i].setisblack(1);
				break;
			}
			if(p->species!=1&&ps[i].getisblack()==0&&ps[i].getsum()<4)
			{
				p->id=ps[i].getsum();
				p->styid=i;
				ps[i].addpig(p);
				break;
			}
		}
	}
}
void pigsty::insert(int i,int j) 
{
	srand((unsigned)time(0));
	pig*p=new pig;
	p->species=i;
	p->styid=j;		
	p->weight=random(20,30);	
	p->gday=0;
	if(head==NULL)
	{
		p->id=0;
		p->next=NULL;
		head=p;
		sum++;
		return;
	}
	if(head->id!=0)
	{
		p->id=0;
		p->next=head;
		head=p;
		sum++;
		return;
	}
	else 
	{
	pig*p1=head,*p2=p1;
	int k=0;
	while(p1->id==k&&p1->next)
	{
		k++;
		p2=p1;
		p1=p1->next;
	}
	if(p1->next==NULL)
	{
		p->id=sum;
		p->next=NULL;
		p1->next=p;
	}
	else
	{
		p->id=k;
		p2->next=p;
		p->next=p1;
	}
	sum++;
	} 
}
void oneday(pigsty ps[])
{
	srand((unsigned)time(0));
	for(int i=0;i<100;i++)
	{
		pig *p;
		p=ps[i].gethead();
		while(p)
		{
			int w1=random(0,12);
			double w2=double(w1)/10.0;
			p->weight+=w2;
			p->gday++;
			p=p->next;
		}	
	} 
}
double getsumprice(pigsty ps[])
{
	double sumprice;
	for(int i=0;i<100;i++)
	{
		sumprice+=ps[i].getprice();
	}
	return sumprice;
}
void searchsty(pigsty ps[],int i)
{
	int sum,isblack;
	pig *p; 
	sum=ps[i].getsum();
	isblack=ps[i].getisblack();
	p=ps[i].gethead();
	if(p==NULL)
	{
		cout<<"��ȦΪ��!"<<endl;
		return;
	}
	if(isblack==1)
	{
		cout<<"����Ȧ�Ǻ���Ȧ��������"<<sum<<"ͷ����"<<endl; 
	}
	else
	{
		cout<<"����ȦΪ�Ǻ���Ȧ��������"<<sum<<"ͷ��"<<endl;
		int pig2=0,pig3=0;
		while(p)
		{
			if(p->species==2)
			pig2++;
			if(p->species==3)
			pig3++;
			p=p->next;
		}
		cout<<"����С������"<<pig2<<"ͷ��"<<"�󻨰�����"<<pig3<<"ͷ��"<<endl; 
	}
}
void searchpig(pigsty ps[],int i,int j)
{
	pig *p;
	p=ps[i].gethead();
	if(p==NULL)
	{
		cout<<"��ȦΪ�գ��޷����ң�"<<endl; 
	}
	int sp,gd,flag=0;
	double w;
	while(p)
	{
		if(p->id==j)
		{
			flag=1;
			break;
		}
		p=p->next;
	}
	if(flag==1)
	{
		sp=p->species;
		gd=p->gday;
		w=p->weight;
		cout<<"�����Ʒ���ǣ�";
		if(sp==1)
		cout<<"����"<<endl;
		if(sp==2)
		cout<<"С����"<<endl;
		if(sp==3)
		cout<<"�󻨰���"<<endl;
		cout<<"�������������Ϊ��"<<gd<<"�졣"<<endl;
		cout<<"���������Ϊ"<<w<<"ǧ�ˡ�"<<endl;
	}
	else
	{
		cout<<"���޴���"<<endl;
	}
}
void printallsty(pigsty ps[])
{
	int allpig1=0,allpig2=0,allpig3=0;
	int w1=0,w2=0,w3=0,w4=0;//w1����0-25��w2����25-50��w3����50-75��w4����>75 
	int d1=0,d2=0,d3=0,d4=0;//d1����0-30��d2����31-60��d3����61-90��d4����>90
	cout<<"������"<<getallpig(ps)<<"ֻ��"<<endl;
	for(int i=0;i<100;i++)
	{
		pig *p=ps[i].gethead();
		while(p)
		{
			int sp,gd;
			double w;
			sp=p->species;
			gd=p->gday;
			w=p->weight;
			if(sp==1)allpig1++;
			if(sp==2)allpig2++;
			if(sp==3)allpig3++;
			if(gd>=0&&gd<=30)d1++;
			if(gd>30&&gd<=60)d2++;
			if(gd>60&&gd<=90)d3++;
			if(gd>90)d4++;
			if(w>=0&&w<=25)w1++;
			if(w>25&&w<=50)w2++;
			if(w>50&&w<=75)w3++;
			if(w>75)w4++;
			p=p->next; 
		}
	}
	cout<<"������"<<allpig1<<"ֻ����"<<allpig2<<"ֻС����"<<allpig3<<"ֻ�󻨰���"<<endl;
	cout<<"���طֲ������ 0-25��"<<w1<<endl;
	cout<<"              25-50��"<<w2<<endl;
	cout<<"              50-75��"<<w3<<endl;
	cout<<"                >75��"<<w4<<endl;
	cout<<"�ɳ������ֲ������ 0-30��"<<d1<<endl;
	cout<<"                  31-60��"<<d2<<endl;
	cout<<"                  61-90��"<<d3<<endl;
	cout<<"                    >90��"<<d4<<endl;
}
void fend(pigsty ps[])
{
	ofstream myycout("read.txt",ios::out);
	myycout<<getallpig(ps)<<endl;
	for(int i=0;i<100;i++)
	{
		pig *p=ps[i].gethead();
		while(p)
		{
			myycout<<p->styid<<" "<<p->id<<" "<<p->gday<<" "<<p->species<<" "<<p->weight<<endl;
			p=p->next;
		}
	}
	myycout.close();
}
void fstart(pigsty ps[])
{
	ifstream myycin("read.txt",ios::in);
	int allpig;
	myycin>>allpig;
	int myid,mygday,mysp,mystyid;
	double myweight;
	pig *p;	
	for(int i=0;i<allpig;i++)
	{
		p=new pig;
		myycin>>mystyid>>myid>>mygday>>mysp>>myweight;
		p->species=mysp;
		p->weight=myweight;
		p->styid=mystyid;
		p->id=myid;
		p->gday=mygday; 
		ps[mystyid].addpig(p);
		if(mysp==1)
		{
			ps[mystyid].setisblack(1);
		}
		else
		{
			ps[mystyid].setisblack(0);
		}
	}
	myycin.close();
}
void infectday(pigsty ps[])
{
	srand((unsigned)time(0));
	for(int i=0;i<100;i++)
	{
		if(ps[i].getisinfect()==1&&ps[i].gethead()!=NULL)
		{
			if(ps[i-1].getisinfect()!=1&&(i-1)>=0)
			{
				int chance=random(1,100);
				if(chance<=50)
				{
					ps[i-1].infectgame();
				}
			}
			if(ps[i+1].getisinfect()!=1&&(i+1)<=99)
			{
				int chance=random(1,100);
				if(chance<=50)
				{
					ps[i+1].infectgame();
				}	
			}
			ps[i].addinfect();
		}
	}
	
}
int main()
{
	
	cout<<"��ο�ʼ��Ϸ��"<<endl;
	cout<<"1:��ʼ������Ϸ"<<endl;
	cout<<"2:�����ļ�����ʼ��Ϸ"<<endl;
	int game;
	cin>>game;
	if(game==1)
	{
		start(ps);
		cout<<"��ʼ���ɹ�����ʼ��Ϸ��"<<endl;
	}
	else
	{
		fstart(ps);
		cout<<"�����ļ��ɹ�����ʼ��Ϸ��"<<endl;
	}
	int sday=0;
	int chujuanc=0;
	while(true)
	{
		int n;
		cout<<endl;
		cout<<"��ѡ������Ҫ�Ĳ���"<<endl; 
		cout<<"0:�˳�"<<endl;
		cout<<"1:������Ȧ"<<endl;
		cout<<"2:������"<<endl;
		cout<<"3:�����ͳ����Ϣ"<<endl;
		cout<<"4:��������"<<endl;
		cout<<"5:���浱ǰ��Ϣ���˳�"<<endl;
		cout<<"6:��Ⱦģʽ"<<endl;
		cin>>n;
		cout<<endl;
		if(n==0)
			break;
		if(n==1)
		{
			int m;
			cout<<"������������ҵ���Ȧ��ţ�";
			cin>>m; 
			searchsty(ps,m);
		}
		if(n==2)
		{
			int m;
			cout<<"������������ҵ���Ȧ��ţ�";
			cin>>m;
			int q;
			cout<<"������������ҵ���ı�ţ�";
			cin>>q; 
			searchpig(ps,m,q);
		}
		if(n==3)
		{
			printallsty(ps);
		}
		if(n==4)
		{
			int day; 
			cout<<"����������ɹ���������";
			cin>>day;
			sday+=day;
			for(int i=0;i<day;i++)
			{
				oneday(ps);
			}
			if(sday>=90)
			{
				double sumprice=0;
				int sellpig1,sellpig2; 
				int qianpig1,qianpig2,qianpig3;
				int houpig1,houpig2,houpig3; 
				sday-=90;
				chujuanc++;
				mycout<<"��"<<chujuanc<<"�γ�Ȧ/����"<<endl;
				sellpig1=getallpig(ps);
				qianpig1=getallpig1(ps);
				qianpig2=getallpig2(ps);
				qianpig3=getallpig3(ps);
				for(int i=0;i<100;i++)
				{
					sumprice+=ps[i].getprice();
				}
				cout<<"���������½��Զ�����һ����"<<endl;
				sellpig2=getallpig(ps);
				houpig1=getallpig1(ps);
				houpig2=getallpig2(ps);
				houpig3=getallpig3(ps);
				mycout<<"����"<<qianpig1-houpig1<<"ֻ����"<<qianpig2-houpig2<<"ֻС����"<<qianpig3-houpig3<<"ֻ�󻨰���"<<endl; 
				cout<<"��Ȧ�ɹ������Ƴ���"<<sellpig1-sellpig2<<"ֻ��,"<<"�õ�"<<sumprice<<"Ԫ��"<<endl; 
				cout<<"���������½��Զ����һ����"<<endl;
				buypig(ps);
				cout<<"��Ȧ�ɹ���"<<endl; 
			}
		}
		if(n==5)
		{
			fend(ps);
			break;
		}
		if(n==6)
		{
			cout<<"��ѡ������Ҫ�Ĳ�����"<<endl;
			cout<<"1:���̽��д�ʩ���з���"<<endl;
			cout<<"2:ģ�ⲻ��ȡ�κδ�ʩ�����ڶ������ȫ����Ⱦ"<<endl;
			int q;
			cin>>q;
			if(q==1)
			{
				srand((unsigned)time(0));
				int j=0;
				while(true)
				{
					int i=random(0,99);
					if(ps[i].gethead()!=NULL)
					{ 
					cout<<"��"<<i<<"����Ȧ����Ⱦ���ѽ�����Ȧ��������գ�"<<endl; 
					ps[i].clear();
					break;
					}
				}
			}
			if(q==2)
			{
				srand((unsigned)time(0));
				int j=0;
				while(true)
				{
					int i=random(0,99);
					if(ps[i].gethead()!=NULL)
					{ 
						ps[i].infectgame();
						break;
					}
				}
				while(true)
				{
					if(getallpig(ps)==getallinfectpig(ps))
					{
						break;
					}
					infectday(ps);
					j++;
				}
				cout<<"�������ȡ�����ʩ�Ļ�����"<<j<<"���ȫ������Ⱦ��"<<endl;
				cout<<"���ѱ�ȫ����Ⱦ����Ϸ������"<<endl;
				break;
			}
		}
	}
	mycout.close(); 
	return 0;
}
