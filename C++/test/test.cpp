#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
typedef int Boole;  //�������� �洢TRUE FALSE
#define MAX 20000
bool visited[MAX];
/*
    ͼ�ı�ʾʹ���ڽӱ�ı�ʾ�����塣AcrNode_info�Ǽ�¼ͼ�бߵ���Ϣ������ʱ��
    ��ά����ʹ�õ��ǽṹ��ı�ʾ

    �����Ǻ�����˵����
    void createGraph(PGraphList G,int vernum,int arcnum,AP P[])��
    �˺��������ǹ������ǵ�ͼ����Ϊ����ͼʱΪ����ͼ����ʱ���ļ����ǰ�������ͼ���ģ�
    ����Ĭ�������ʱ���ʱ���ֵ�ǰ��ն����С�ĵ�����ڶ���Ŵ�ĵ㣬�ڹ���ͼ��ͬʱ����Ϣ
    ��¼��P������
    void CreateTree(PGraphList G,PGraphList T,int vernum)
    �˺����ǹ���������T��ͨ���������еı�������������������Ժ���һ��а���

    void createA(PGraphList T,AP P[],Matrix *A,int arcnum,int vernum)
    �˺����ǹ�����������Ҫ������A
    A���б�ʾ�� �б�ʾͼ�еı� �����ҵ��� Ȼ�󿴱��Ƿ������� �ڵĻ�������ͬΪ1 �෴Ϊ-1 ������Ϊ0

    void createtemp(Matrix *temp5,Matrix *A,Matrix *C,int arcnum,int vernum)
    ����������Ҫ�ó���һ������ Ҳ����I-At(AAt)-1A

    bool ArcIsinGraph(PGraphList G,int i,int j)�жϱ�ij�Ƿ���ͼ��

    void InitialMatrix(Matrix *T,int m,int n)��ʼ���ṹ��

    void inverse(Matrix *c)�����c�������

    bool ISInGraph(PGraphList G,int j,int vernum)ͼ���Ƿ���ڶ����Ϊj����

    int LocateVex(PGraphList G,int v)���㶨λ

    void over(AP P[],Matrix *temp,int arcnum)���������ÿ����������ʱ����ֵ��P

    void printarray(Matrix *sample)��ӡ����

    void printFloor(ALGrph T)��ӡ����������Ĳ���

    void printP(AP m[],int arcnum)��ӡͼ�бߵ���Ϣ

    void PrintUDG(ALGrph G)��ӡͼ

    void test(Matrix *A,AP P[],int arcnum,int vernum)���Ի����Ƿ�Ϊ��

    void trans(Matrix *A,Matrix *C,int arcnum,int vernum)�����ת��

*/
typedef struct AcrNode_info{
    int begin;//�ߵ���ʼ��
    int end;//�ߵ��յ�
    float time;
}AP;
typedef struct {//��ά���鶨��Ľṹ��
    double **mat;
    int rows;//����
    int cols;//����
}Matrix;
typedef struct AcrNode{ //�߱���
    int adjvex;
    float detal_time; //�ߵ�ʱ���
    struct AcrNode *nextarc;
}ArcNode;
typedef struct VNode{//�����Ľṹ��
    int data;//�����
    int floor;//����
    ArcNode *firstarc;
}Vnode,AdjList[MAX];
typedef struct {
    int vernum;
    int arcnum;
    AdjList vertices;
}ALGrph,*PGraphList;

int LocateVex(PGraphList G,int v){//��λ����
    int i;
	for(i=0;i<G->vernum;i++){
		if(v==G->vertices[i].data)return i;
	}
	return -1;
}
void InitialMatrix(Matrix *T,int m,int n){
	int i;
	T->mat=(double**)malloc(m*sizeof(double*));
	for(i=0;i<m;i++)
		T->mat[i]=(double*)malloc(n*sizeof(double));
	T->rows=m;				// m��
	T->cols=n;				// n��
}
//����ͼ
void createGraph(PGraphList G,int vernum,int arcnum,AP P[], ArcNode * memory){
    ArcNode *p,*q;
    G->vernum=vernum,G->arcnum=arcnum;
    int i,k;
    for(i=0;i<G->vernum;i++){
        G->vertices[i].data=i;
        G->vertices[i].firstarc=NULL;//��ÿ���ڽӱ������һ���ڵ㸳ֵΪ��
	}
	//printf("�ֱ���������ߵ����������Լ�ʱ�ӣ�\n");
	int test[arcnum*2];
	int count=0;
	srand(time(NULL));
	int sub=0;
   for(k=0;k<G->arcnum;k++){
        if(k<vernum){
            if(k!=vernum-1){
                float time=rand() /(double)(RAND_MAX/10);
                //printf("%d   %d   %f\n",k,k+1,time);
                //ʱ�ӵ������ǰ��ն����С������ڶ���Ŵ��ʱ��
                test[count++]=k,test[count++]=k+1;
                P[k].begin=k;P[k].end=k+1;P[k].time=time;
                int i=LocateVex(G,k);
                int j=LocateVex(G,k+1);
                //ͷ�巨��������
                p=&memory[sub++];//����һ���߱�ڵ�
                //printf("%d\n",sizeof(p));
                p->adjvex=j;p->detal_time=time;p->nextarc=NULL;  //��ֵ
                p->nextarc=G->vertices[i].firstarc;//���ӽ��
                G->vertices[i].firstarc=p;//���ӽ��

                q=&memory[sub++];//����һ���߱�ڵ�
                q->adjvex=i;q->detal_time=-time;q->nextarc=NULL;  //��ֵ
                q->nextarc=G->vertices[j].firstarc;//���ӽ��
                G->vertices[j].firstarc=q;//���ӽ��
            }else{
                float time=rand() /(double)(RAND_MAX/10);
                //printf("%d   %d   %f\n",vernum-1,0,time);
                //ʱ�ӵ������ǰ��ն����С������ڶ���Ŵ��ʱ��
                test[count++]=0,test[count++]=vernum-1;
                P[k].begin=0;P[k].end=vernum-1;P[k].time=time;
                int i=LocateVex(G,0);
                int j=LocateVex(G,vernum-1);
                //ͷ�巨��������
                p=&memory[sub++];//����һ���߱�ڵ�
                p->adjvex=j;p->detal_time=time;p->nextarc=NULL;  //��ֵ
                p->nextarc=G->vertices[i].firstarc;//���ӽ��
                G->vertices[i].firstarc=p;//���ӽ��
                q=&memory[sub++];//����һ���߱�ڵ�
                q->adjvex=i;q->detal_time=-time;q->nextarc=NULL;  //��ֵ
                q->nextarc=G->vertices[j].firstarc;//���ӽ��
                G->vertices[j].firstarc=q;//���ӽ��
            }
            continue;
        }
        bool t=false;
        int v1=rand()%vernum,v2=rand()%vernum;
        if(v1==v2 || v1==(v2+1) || v2==v1+1){
            t=true;
        }
        for(i=0;i<arcnum*2;i+=2){
            if( (v1==test[i]&&v2==test[i+1]) || (v1==test[i+1]&&v2==test[i]) ){
                t=true;
                break;

            }
        }
        if(t==true){
            k--;
            continue;
        }else{
        float time=rand() /(double)(RAND_MAX/10);
        //printf("%d   %d   %f\n",v1,v2,time);
        test[count++]=v1,test[count++]=v2;
        //ʱ�ӵ������ǰ��ն����С������ڶ���Ŵ��ʱ��
        if(v1<v2){
             P[k].begin=v1;P[k].end=v2;P[k].time=time;
        }else{
             P[k].begin=v2;P[k].end=v1;P[k].time=time;
        }
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        if(i<j){
        //ͷ�巨��������
        p=&memory[sub++];//����һ���߱�ڵ�
        p->adjvex=j;p->detal_time=time;p->nextarc=NULL;  //��ֵ
        p->nextarc=G->vertices[i].firstarc;//���ӽ��
		G->vertices[i].firstarc=p;//���ӽ��
		q=&memory[sub++];//����һ���߱�ڵ�
        q->adjvex=i;q->detal_time=-time;q->nextarc=NULL;  //��ֵ
        q->nextarc=G->vertices[j].firstarc;//���ӽ��
		G->vertices[j].firstarc=q;//���ӽ��
        }else{
            //ͷ�巨��������
        p=&memory[sub++];//����һ���߱�ڵ�
        p->adjvex=j;p->detal_time=-time;p->nextarc=NULL;  //��ֵ
        p->nextarc=G->vertices[i].firstarc;//���ӽ��
		G->vertices[i].firstarc=p;//���ӽ��
		q=&memory[sub++];//����һ���߱�ڵ�
        q->adjvex=i;q->detal_time=time;q->nextarc=NULL;  //��ֵ
        q->nextarc=G->vertices[j].firstarc;//���ӽ��
		G->vertices[j].firstarc=q;//���ӽ��
        }
    }
   }
}
//�жϱ��Ƿ���ͼ��
bool ArcIsinGraph(PGraphList G,int i,int j){
    int m;
    for(m=0;m<G->vernum;m++){
        ArcNode *p;
        p=G->vertices[i].firstarc;
        while(p!=NULL){
                if((i==m&&j==p->adjvex) || (i==j&&i==p->adjvex))
                    return true;
            p=p->nextarc;
        }
    }
    return false;
}
//�ж϶����Ƿ���ͼ��
bool ISInGraph(PGraphList G,int j,int vernum){
    int i;
    for(i=0;i<vernum;i++){
        if(j==G->vertices[i].data)
            return true;
    }
    return false;
}

void DFS(PGraphList,int,PGraphList,ArcNode*);
int num;
//������
void CreateTree(PGraphList G,PGraphList T,int vernum,ArcNode * memory){
    int i,j;
    T->vertices[0].floor=1;
    for(i=0;i<G->vernum;i++){
        visited[i]=false;
    }
    for (i = 0; i < G->vernum; i++) {
		T->vertices[i].data = i;
		T->vertices[i].firstarc = NULL;//��ÿ���ڽӱ������һ���ڵ㸳ֵΪ��
	}
    for(i=0;i<vernum;i++){
        if(visited[i]==false){
            DFS(G,i,T,memory);

        }
    }
    T->arcnum=G->vernum-1; T->vernum=G->vernum;
}

void DFS(PGraphList G,int i,PGraphList T,ArcNode * memory){
    ArcNode *p,*m,*n;
    visited[i]=true;
    p=G->vertices[i].firstarc;

    while(p!=NULL){
        if(!visited[p->adjvex]){
                if(p->adjvex!=0)
                    T->vertices[p->adjvex].floor=T->vertices[i].floor+1;

                T->vertices[i].data=i; T->vertices[p->adjvex].data=p->adjvex;

                m=&memory[num++];//����һ���߱�ڵ�
                m->adjvex=p->adjvex ;m->nextarc=NULL;  //��ֵ
                m->nextarc=T->vertices[i].firstarc;//���ӽ��
                T->vertices[i].firstarc=m;//���ӽ��

                n=&memory[num++];//����һ���߱�ڵ�
                n->adjvex=i;n->nextarc=NULL;  //��ֵ
                n->nextarc=T->vertices[p->adjvex].firstarc;//���ӽ��
                T->vertices[p->adjvex].firstarc=n;//���ӽ��

                DFS(G,p->adjvex,T,memory);
        }
        p=p->nextarc;
    }
}
//����ڽӱ�
void PrintUDG(ALGrph G){
    int i,j;
	for(i=0;i<G.vernum;i++){
		printf("%d",i);
		ArcNode *p;
		p=G.vertices[i].firstarc;
		while(p!=NULL){
			printf("->%d  =%f",p->adjvex,p->detal_time);
			p=p->nextarc;
		}
		printf("\n");
	}
}
void printP(AP m[],int arcnum){
    int i;
    for(i=0;i<arcnum;i++){
        printf("%d  %d  %f \n",m[i].begin,m[i].end,m[i].time);
    }
}
void printFloor(ALGrph T){
    int i;
    for(i=0;i<T.vernum;i++)
        printf("%d    %d\n",T.vertices[i].data,T.vertices[i].floor);
}
//�����A����
void createA(PGraphList T,AP P[],Matrix *A,int arcnum,int vernum){
    InitialMatrix(A,arcnum-vernum+1,arcnum);
    int i,m,n,j,count=0,l,h,x;
    for(i=0;i<arcnum;i++){

        if(!ArcIsinGraph(T,P[i].begin,P[i].end)){
            m=T->vertices[P[i].begin].floor;
            n=T->vertices[P[i].end].floor;
            //printf("%d   %d \n",m,n);
           AP temp[arcnum];
            for(x=0;x<arcnum;x++){
                temp[x].begin=0;
                temp[x].end=0;
            }
            int k=0;
            if(m<n){
                int de=n-m;
                int tempdate=T->vertices[P[i].end].data;
                int tempdate2=T->vertices[P[i].begin].data;
                int tempfloor=T->vertices[P[i].end].floor;
                int tempfloor2=T->vertices[P[i].begin].floor;
                while(de>0){
                    for(j=0;j<T->vernum;j++){
                        if(ArcIsinGraph(T,tempdate,T->vertices[j].data)&&T->vertices[j].floor==(tempfloor-1)){
                            temp[k].begin=tempdate;
                            temp[k].end=T->vertices[j].data;
                            tempdate=T->vertices[j].data;
                            tempfloor--;
                            k++;
                            break;
                        }
                    }
                    de--;
                }
                while(tempdate!=tempdate2){
                        for(j=0;j<T->vernum;j++){
                            if(ArcIsinGraph(T,tempdate,T->vertices[j].data)&&T->vertices[j].floor==(tempfloor-1)){
                                temp[k].begin=tempdate;
                                temp[k].end=T->vertices[j].data;
                                tempdate=T->vertices[j].data;
                                tempfloor--;
                                k++;
                                break;
                            }
                        }
                         for(j=0;j<T->vernum;j++){
                            if(ArcIsinGraph(T,tempdate2,T->vertices[j].data)&&T->vertices[j].floor==(tempfloor2-1)){
                                temp[k].end=tempdate2;
                                temp[k].begin=T->vertices[j].data;
                                tempdate2=T->vertices[j].data;
                                tempfloor2--;
                                k++;
                                break;
                            }
                        }
                    }

                    temp[k].begin=T->vertices[P[i].begin].data;
                    temp[k].end=T->vertices[P[i].end].data;

            }else if(m>n){
                int de=m-n;
                int tempdate2=T->vertices[P[i].end].data;
                int tempdate=T->vertices[P[i].begin].data;
                int tempfloor2=T->vertices[P[i].end].floor;
                int tempfloor=T->vertices[P[i].begin].floor;
                while(de>0){
                    for(j=0;j<T->vernum;j++){
                        if(ArcIsinGraph(T,tempdate,T->vertices[j].data)&&T->vertices[j].floor==(tempfloor-1)){
                            temp[k].begin=tempdate;
                            temp[k].end=T->vertices[j].data;
                            tempdate=T->vertices[j].data;
                            tempfloor--;
                            k++;
                            break;
                        }
                    }
                    de--;
                }
                   while(tempdate!=tempdate2){
                        for(j=0;j<T->vernum;j++){
                            if(ArcIsinGraph(T,tempdate,T->vertices[j].data)&&T->vertices[j].floor==(tempfloor-1)){
                                temp[k].begin=tempdate;
                                temp[k].end=T->vertices[j].data;
                                tempdate=T->vertices[j].data;
                                tempfloor--;
                                k++;
                                break;
                            }
                        }
                         for(j=0;j<T->vernum;j++){
                            if(ArcIsinGraph(T,tempdate2,T->vertices[j].data)&&T->vertices[j].floor==(tempfloor2-1)){
                                temp[k].end=tempdate2;
                                temp[k].begin=T->vertices[j].data;
                                tempdate2=T->vertices[j].data;
                                tempfloor2--;
                                k++;
                                break;
                            }
                        }
                    }
                    temp[k].begin=T->vertices[P[i].end].data;
                    temp[k].end=T->vertices[P[i].begin].data;
            }else{
                int tempdate=T->vertices[P[i].end].data;
                int tempdate2=T->vertices[P[i].begin].data;
                int tempfloor=T->vertices[P[i].end].floor;
                int tempfloor2=T->vertices[P[i].begin].floor;
                while(tempdate!=tempdate2){
                        for(j=0;j<T->vernum;j++){
                            if(ArcIsinGraph(T,tempdate,T->vertices[j].data)&&T->vertices[j].floor==(tempfloor-1)){
                                temp[k].begin=tempdate;
                                temp[k].end=T->vertices[j].data;
                                tempdate=T->vertices[j].data;
                                tempfloor--;
                                k++;
                                break;
                            }
                        }
                         for(j=0;j<T->vernum;j++){
                            if(ArcIsinGraph(T,tempdate2,T->vertices[j].data)&&T->vertices[j].floor==(tempfloor2-1)){
                                temp[k].end=tempdate2;
                                temp[k].begin=T->vertices[j].data;
                                tempdate2=T->vertices[j].data;
                                tempfloor2--;
                                k++;
                                break;
                            }
                        }
                    }
                    temp[k].begin=T->vertices[P[i].begin].data;
                    temp[k].end=T->vertices[P[i].end].data;
            }
//            //��ӡ���ҵ��Ļ�
//            for(j=0;j<=k;j++){
//                        printf("%d   %d   ",temp[j].begin,temp[j].end);
//                    }
//                printf("\n");
            //A����ĸ�ֵ
            for(l=0;l<arcnum;l++){
                for(h=0;h<=k;h++){
                    if((P[l].begin==temp[h].begin)&&(P[l].end==temp[h].end)){
                            A->mat[count][l]=1;
                            break;
                    }
                    if((P[l].begin==temp[h].end)&&(P[l].end==temp[h].begin)){
                            A->mat[count][l]=-1;
                            break;
                    }
                }
            }
            count++;
        }

    }
}
//ת�þ��� ��A��ת�þ���ֵ��C
void trans(Matrix *A,Matrix *C,int arcnum,int vernum){
    InitialMatrix(C,arcnum,arcnum-vernum+1);
    int i,j;
    for(i=0;i<arcnum-vernum+1;i++){
        for(j=0;j<arcnum;j++){
            C->mat[j][i]=A->mat[i][j];
        }
    }
}
//��ӡ����ĺ���
void printarray(Matrix *sample){
    int i,j;
    for(i=0;i<sample->rows;i++){
        for(j=0;j<sample->cols;j++)
            printf("%f  ",sample->mat[i][j]);
        printf("\n");
    }
    printf("\n");
}
void inverse(Matrix *c){
    Matrix L,U;
    int i,j,k;
    InitialMatrix(&L,c->rows,c->cols);
    InitialMatrix(&U,c->rows,c->cols);
    for(i=0;i<c->rows;i++){
        for(j=0;j<c->cols;j++){
            L.mat[i][j]=0;
            U.mat[i][j]=0;
        }
    }
    //for(i=0;i<c->rows;i++)
        //c->mat[0][i]=c->mat[0][i];
    for(i=1;i<c->cols;i++)
        c->mat[i][0]=c->mat[i][0]/c->mat[0][0];
    for(k=1;k<c->rows;k++){
        for(j=k;j<c->cols;j++){
            double s=0;
            for (i=0;i<k;i++)
                s=s+c->mat[k][i]*c->mat[i][j];   //�ۼ�

            c->mat[k][j]=c->mat[k][j]-s; //����U���������Ԫ��
        }
        for(i=k+1;i<c->rows;i++){
            double t=0;
            for(j=0;j<k;j++)
                t=t+c->mat[i][j]*c->mat[j][k];   //�ۼ�
            c->mat[i][k]=(c->mat[i][k]-t)/c->mat[k][k];    //����L���������Ԫ��
        }
    }
    for(i=0;i<c->rows;i++)
        for(j=0;j<c->cols;j++){
                if(i>j){
                    L.mat[i][j]=c->mat[i][j];
                    U.mat[i][j]=0;
                }//���i>j��˵���д����У��������������ǲ��֣��ó�L��ֵ��U��//Ϊ0
                else{
                    U.mat[i][j]=c->mat[i][j];
                if(i==j)
                    L.mat[i][j]=1;  //�������i<j��˵����С���У��������������ǲ��֣��ó�U��//ֵ��L��Ϊ0
                else
                    L.mat[i][j]=0;
                }
    }
    Matrix u,r;
    InitialMatrix(&u,c->rows,c->cols);
    InitialMatrix(&r,c->rows,c->cols);
    for(i=0;i<c->rows;i++){
        for(j=0;j<c->cols;j++){
            u.mat[i][j]=0;
            r.mat[i][j]=0;
        }
    }
    for (i=0;i<c->rows;i++) /*�����U���� */
    {
        u.mat[i][i]=1/U.mat[i][i];//�Խ�Ԫ�ص�ֵ��ֱ��ȡ����
        for (k=i-1;k>=0;k--){
            double s=0;
            for (j=k+1;j<=i;j++)
                s=s+U.mat[k][j]*u.mat[j][i];
            u.mat[k][i]=-s/U.mat[k][k];//�������㣬���е������εõ�ÿһ��ֵ��
        }
    }
    for (i=0;i<c->rows;i++) //�����L����
    {
        r.mat[i][i]=1; //�Խ�Ԫ�ص�ֵ��ֱ��ȡ����������Ϊ1
        for (k=i+1;k<c->rows;k++){
            for (j=i;j<=k-1;j++)
                r.mat[k][i]=r.mat[k][i]-L.mat[k][j]*r.mat[j][i];   //�������㣬����˳�����εõ�ÿһ��ֵ
        }
    }
    for(i=0;i<c->rows;i++){
        for(j=0;j<c->cols;j++){
                c->mat[i][j]=0;
        }
    }
    //�������
    for(i=0;i<c->rows;i++){
        for(j=0;j<c->cols;j++){
            for(k=0;k<c->rows;k++){
                c->mat[i][j]+=u.mat[i][k]*r.mat[k][j];
            }
        }
    }
}
void createtemp(Matrix *temp5,Matrix *A,Matrix *C,int arcnum,int vernum){
    int i,j,m;
    Matrix *temp1;
    InitialMatrix(temp1,arcnum-vernum+1,arcnum-vernum+1);
    for(i=0;i<temp1->rows;i++){
        for(j=0;j<temp1->cols;j++)
        {
            double sum=0;
            for(m=0;m<arcnum;m++)
                sum+=A->mat[i][m]*C->mat[m][j];
            temp1->mat[i][j]=sum;
        }
    }
   // printf("%s\n","A*Aת:");
    //printarray(temp1);
    Matrix c;
    InitialMatrix(&c,arcnum-vernum+1,arcnum-vernum+1);
    //��temp(A*At)���鸳ֵ��c����
     for(i=0;i<arcnum-vernum+1;i++){
        for(j=0;j<arcnum-vernum+1;j++)
        {
            c.mat[i][j]=temp1->mat[i][j];
        }
    }
    //printarray(&c);
    inverse(&c);
    //printf("%s\n","��:");
    //printarray(&c);
    //printf("\n");
    //printf("%s\n","��֤������Ƿ���ȷ:");
    int k;
    double sum1=0;
    for(i=0;i<arcnum-vernum+1;i++){
        for(j=0;j<arcnum-vernum+1;j++){
            for(k=0;k<arcnum-vernum+1;k++)
                sum1+=c.mat[i][k]*temp1->mat[k][j];
            //printf("%f    ",sum1);
            sum1=0;
        }
       // printf("\n");
    }
    //printf("\n");
    Matrix temp2;
    InitialMatrix(&temp2,arcnum-vernum+1,arcnum-vernum+1);
    for(i=0;i<arcnum-vernum+1;i++){
        for(j=0;j<arcnum-vernum+1;j++)
            temp2.mat[i][j]=c.mat[i][j];
    }
    Matrix temp3;
    InitialMatrix(&temp3,arcnum,arcnum-vernum+1);
    //At*(AAt)-1
     //printf("%s\n","At*(AAt)-1:");
    for(i=0;i<arcnum;i++){
        for(j=0;j<arcnum-vernum+1;j++){
                sum1=0;
            for(k=0;k<arcnum-vernum+1;k++)
                sum1+=(C->mat[i][k]*temp2.mat[k][j]);
            temp3.mat[i][j]=sum1;
           // printf("%f   ",temp3.mat[i][j]);

        }
       // printf("\n");
    }
    Matrix temp4;
    InitialMatrix(&temp4,arcnum,arcnum-vernum+1);
     for(i=0;i<arcnum;i++){
        for(j=0;j<arcnum-vernum+1;j++)
            temp4.mat[i][j]=temp3.mat[i][j];
    }
   // printf("\n");
    InitialMatrix(temp5,arcnum,arcnum);
   // printf("%s\n","At*(AAt)-1A:");
    for(i=0;i<arcnum;i++){
        for(j=0;j<arcnum;j++){
            sum1=0;
            for(k=0;k<arcnum-vernum+1;k++)
                sum1+=temp4.mat[i][k]*A->mat[k][j];
            temp5->mat[i][j]=sum1;
            //printf("%f   ",temp5->mat[i][j]);
        }
        //printf("\n");

    }
    //printf("\n");
    //printf("%s\n","I-At*(AAt)-1A:");
    for(i=0;i<arcnum;i++){
        for(j=0;j<arcnum;j++){
            if(i==j)
                temp5->mat[i][j]=1-temp5->mat[i][j];
            else
                temp5->mat[i][j]=-temp5->mat[i][j];
            //printf("%f   ",temp5->mat[i][j]);
        }
        //printf("\n");
    }
}
void over(AP P[],Matrix *temp,int arcnum){
   int i,j,k;
    AP temp5[arcnum];
   for(k=0;k<arcnum;k++){
        temp5[k].begin=P[k].begin;
        temp5[k].end=P[k].end;
        temp5[k].time=P[k].time;
   }
   double sum;
   for(i=0;i<arcnum;i++){
        sum=0;
    for(j=0;j<arcnum;j++){
        sum+=temp->mat[i][j]*temp5[j].time;
    }
    P[i].time=sum;
   }
}
void test(Matrix *A,AP P[],int arcnum,int vernum){
    // printf("%s\n","��֤���ĺͣ�");
    int i,j;
    for(i=0;i<arcnum-vernum+1;i++){
        double sum=0;
        for(j=0;j<arcnum;j++)
        sum+=A->mat[i][j]*P[j].time;
        // printf("%s%d%s%.5e\n","��",i,"���ĺ�Ϊ��",sum);
        if(sum>=1) printf("��%d�λ���Ϊ%.7e\n",i,sum);
    }
}
int main(){
    int i;
    int vernum=80;
    int arcnum=400;
    ArcNode* memoryG;
	ArcNode* memoryT;
	memoryG = (ArcNode*)malloc(sizeof(ArcNode)*(2*arcnum));
	memoryT = (ArcNode*)malloc(sizeof(ArcNode)*((vernum-1)*2));

    ALGrph G,T;
    AP P[20000];
    Matrix A;//������
    Matrix C;//A��ת�þ���
    Matrix temp;//A*Aת�õ���
    //freopen("out.txt", "w", stdout);
    for(i=0;i<200;i++){
    num=0;
    //printf("%d   %d\n",vernum,arcnum);
   // int i,j;
    //printf("�����붥�����ͱ�����\n");
    //scanf("%d%d",&vernum,&arcnum);
    //G P ��ʼ�����
    createGraph(&G,vernum,arcnum,P,memoryG);
    //printP(P,arcnum);
    //PrintUDG(G);
    CreateTree(&G,&T,vernum,memoryT);
    //printf("%s%d\n","numΪ��",num);
    //printf("%d  %d",T.vernum,T.arcnum);
    //printf("\n");
    //PrintUDG(T);
   // printf("\n");

    //printFloor(T);

    //A��ʼ�����
    createA(&T,P,&A,arcnum,vernum);
     //printarray(&A);
    //C��ʼ�����
    trans(&A,&C,arcnum,vernum);

    //printarray(&C);
    //printf("\n");
    //temp��ʼ�����
    createtemp(&temp,&A,&C,arcnum,vernum);

   // printP(P,arcnum);
   // printf("\n");
    over(P,&temp,arcnum);
    //printP(P,arcnum);
    test(&A,P,arcnum,vernum);
    printf("%s%d%s","��",i,"�γɹ���\n");
    }
	return 0;
}
