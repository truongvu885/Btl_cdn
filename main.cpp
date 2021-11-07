// Ford-Fulkerson
#include<iostream>
#include<iomanip>
#include <queue>
#include<fstream>
#include<string>
#include<graphics.h>
#include<math.h>


using namespace std;

#define V 10

int n;
int DoThi[V][V];
int x[10]= {200,400,400,600,800,800,1000,250,350,500};
int y[10]= {400,200,600,400,200,600,400,200,200,150};
int a[20] = {300,300,400,500,600,500,600,700,700,800,900,900};
int b[20] = {300,500,400,300,200,500,600,300,500,400,300,500};



bool bfs(int DoThi[V][V], int s, int t, int parent[]) {
  bool visited[V];
  memset(visited, 0, sizeof(visited));

  queue<int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v = 0; v < V; v++) {
      if (visited[v] == false && DoThi[u][v] > 0) {
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  return (visited[t] == true);
}

// Applying fordfulkerson algorithm
int fordFulkerson(int DoThi[V][V], int s, int t) {
  int u, v;

  //int rGraph[V][V];
 // for (u = 0; u < V; u++)
  //  for (v = 0; v < V; v++)
  //    rGraph[u][v] = graph[u][v];

  int parent[V];
  int max_flow = 0;

  // Updating the residual values of edges
  while (bfs(DoThi, s, t, parent)) {
    int path_flow = INT_MAX;
    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      path_flow = min(path_flow, DoThi[u][v]);
    }

    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      DoThi[u][v] -= path_flow;
      DoThi[v][u] += path_flow;
    }

    // Adding the path flows
    max_flow += path_flow;
  }

  return max_flow;
}
void nhapDoThi()
{
    cout << "Nhap so dinh cua do thi: "; cin >> n;
    cout << "Nhap cac duong di cua do thi";
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (i == j)
            {
                DoThi[i][j] = 0;
            }
            else
            {
                cout << "\nDuong di tu dinh " << i << " toi dinh " << j << " la: "; cin >> DoThi[i][j];
            }

        }
    }
    cout << "\n Do thi vua nhap la: " << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << setw(5) << DoThi[i][j] << " ";
        }
        cout << endl;
    }
}

void luuFile()
{
    ofstream f;
    f.open("Dothi.txt");
    if (f.fail())
    {
        cout << "Khong the mo file";
    }
    else {
    	f<<setw(3)<<n<<endl;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                f << setw(3) << DoThi[i][j];
            }
            f << "\n";
        }
        cout << "Ghi file thanh cong\n";
        f.close();
    }
}

void docFile(int DoThi[V][V],int &n)
{
    ifstream f;
    f.open("Dothi.txt");

    if (f.fail())
    {
        cout << "Khong the mo file";
    }

    else {
    	f>>n;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                f >> DoThi[i][j];
            }
        }
        cout<<setw(5)<<n<<endl;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cout << setw(5) << DoThi[i][j] << " ";
            }
            cout << endl;
        }
    }
    f.close();
}

void menu()
{
    cout << "\n\t-----------THUAT TOAN FORD-FULKERSON---------------" << endl;
    cout << "\t1.Nhap do thi" << endl;
    cout << "\t2.Ghi file" << endl;
    cout << "\t3.Doc file" << endl;
    cout << "\t4.Max flow" << endl;
    cout<<"\t5.Do hoa"<<endl;
    cout << "\t6.Ket thuc" << endl;
}

void CreatePeak()
{
  for(int i=1; i<=n; i++)
    {
        char kt[100];
        setcolor(0);//solor mau ve
        circle(x[i-1],y[i-1],30);//ve hinh tron 
        setfillstyle(1,10);//do mau nen, theo mau~ 1, mau` 15
        floodfill(x[i-1], y[i-1],0);//do mau theo tung diem hinh tron
        settextstyle(0,0,2);//set font, size chu
        setcolor(0);//mau chu
        itoa(i,kt,10); //ep kieu sok ve ky tu theo co so 10
        outtextxy(x[i-1]-7, y[i-1]-7,kt);//viet ky tu len duong tron 
        delay(500);
    }
}

void CreateLink()
{
    for(int i=1; i<=n; i++)
    {
        for(int j=i; j<=n; j++)
        {
        	if(DoThi[i][j]!=0)
            {
	      		setcolor(4);
                setlinestyle(0,0,2);
                moveto(x[i-1],y[i-1]);
                lineto(x[j-1],y[j-1]);
                delay(500);
            }
        }
    }
}


void CreateCapaty()
{
	char kt[100];
	int c=0;
   for(int i=0; i<=n; i++)
    {
        for(int j=0; j<=n; j++)
        {
            if(DoThi[i][j]!=0)
            {
            
	      	settextstyle(0,0,2);//set font, size chu
        	setcolor(0);//mau chu
        	 sprintf(kt, "%d\n", DoThi[i][j]);
        	outtextxy(a[c]-7, b[c]-7,kt);
        	 delay(500);
        	 c++;
            }
        }
    } 
}

void CreateMax_flow()
{
	settextstyle(0,0,2);
	setcolor(0);
	char c1[100];
	char t[100] = "Max flow = ";
	sprintf(c1,"%d\n",fordFulkerson(DoThi,1,n));
	strcat(t, c1); 
	outtextxy(400,700,t);
}

void Graphic()
{
    initwindow(1200,800);
    setbkcolor(15);//mau nen trang
    cleardevice();
   	CreatePeak();
   	CreateLink();
   	CreateCapaty();
   	CreateMax_flow();
  
   
    getch();
    closegraph();
}

	
int main() {
    int chon;
    do {
        system("cls");
        menu();
        cout << "Nhap lua chon: "; cin >> chon;
        switch (chon)
        {
        case 1:nhapDoThi();
            system("pause");
            break;
        case 2:luuFile();  system("pause"); break;

        case 3:docFile(DoThi,n); system("pause"); break;

        case 4: cout << "Max Flow: " << fordFulkerson(DoThi, 1, n) << endl; system("pause"); break;

        case 5:Graphic();getch(); break;
        case 6:cout<<"The end !!!!";break;
        default: cout << "Ban nhap sai roi...Moi nhap lai(1>5)!"; break;

        }
    } while (chon != 6);
    
}



