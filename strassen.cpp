#include <iostream>
#include <vector>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <time.h>

#define lu(x) printf("%lu\n",x);
#define d(x) printf("%d\n",x);
#define f(x) printf("%.2f\t",x);
#define loop0(i,n) for(int i=0;i<n;i++)
#define loop(i,m,n) for(int i=m;i<n;i++)

#define MAX 100 // maximum size of float value
using namespace std;

class subMatrix{
    public:
    float **m;
    int row,col,size;
    subMatrix(float **a,int r,int c,int n){
        m=a;
        row=r;
        col=c;
        size=n;
    }
};

void strassen(int);
float** init(int);
subMatrix multiply(const subMatrix a,const subMatrix b,int n);
void clear(float **a,int n);
void generate(float **a,int n);
void add(subMatrix c,subMatrix a,subMatrix b,int n);
void sub(subMatrix c,subMatrix a,subMatrix b,int n);

double time_elapsed(struct timespec start, struct timespec end) {
    double t;
    t = (end.tv_sec - start.tv_sec); //diff of tv_sec
    t += (end.tv_nsec - start.tv_nsec) * 0.000000001; //add diff of tv_nsec too
    return t;
}


int main(){
    srand(time(NULL));
    int n;
    cin>>n;
    strassen(n);
    return 0;
}

//Function to create a matrix in heap
float** init(int n){
    float **a=new float*[n];
    loop0(i,n){
        a[i]=new float[n];
    }
    return a;
}

//clearing memory allocated to arrays
void clear(float **a,int n){
    loop0(i,n){
        delete(a[i]);
    }
    delete(a);
}

//Function to fill a matrix with random values
void generate(float **a,int n){
    
    loop0(i,n){
        loop0(j,n){
            cin>>a[i][j];
        }
    }

}
//Divide and Conquer
void strassen(int n){
    struct timespec start,end;
    float **m1=init(n);
    float **m2=init(n);
    generate(m1,n);
    generate(m2,n);
    subMatrix mat1 = subMatrix(m1,0,0,n);
    subMatrix mat2 = subMatrix(m2,0,0,n);
    clock_gettime(CLOCK_REALTIME,&start);
    subMatrix res = multiply(mat1,mat2,n);
    clock_gettime(CLOCK_REALTIME,&end);
    cout<<time_elapsed(start,end)<<"\n";
}

//Add arrays
void add(subMatrix c,subMatrix a,subMatrix b,int n){
    loop0(i,n){
        loop0(j,n){
            c.m[c.row+i][c.col+j]=a.m[a.row+i][a.col+j]+b.m[b.row+i][b.col+j];
        }
    }
}
//Subtract arrays
void sub(subMatrix c,subMatrix a,subMatrix b,int n){
    loop0(i,n){
        loop0(j,n){
            c.m[c.row+i][c.col+j]=a.m[a.row+i][a.col+j]-b.m[b.row+i][b.col+j];
        }
    }
}

//recurssive multiply function
subMatrix multiply(const subMatrix a,const subMatrix b,int n){
    float **c = init(n);
    subMatrix cm = subMatrix(c,0,0,n);
    if(n<9){
        loop0(i,n){
            loop0(j,n){
                int sum = 0;
                loop0(k,n){
                    sum +=a.m[a.row+i][a.col+k]*b.m[b.row+k][b.col+j];
                }
                cm.m[cm.row+i][cm.col+j]=sum;
            }
        }
    }
    else{
        subMatrix a11 = subMatrix(a.m,0,0,n/2);
        subMatrix a12 = subMatrix(a.m,0,n/2,n/2);
        subMatrix a21 = subMatrix(a.m,n/2,0,n/2);
        subMatrix a22 = subMatrix(a.m,n/2,n/2,n/2);
        subMatrix b11 = subMatrix(b.m,0,0,n/2);
        subMatrix b12 = subMatrix(b.m,0,n/2,n/2);
        subMatrix b21 = subMatrix(b.m,n/2,0,n/2);
        subMatrix b22 = subMatrix(b.m,n/2,n/2,n/2);
        subMatrix a1122 = subMatrix(init(n/2),0,0,n/2);
        subMatrix b1122 = subMatrix(init(n/2),0,0,n/2);
        add(a1122,a11,a22,n/2);
        add(b1122,b11,b22,n/2);
        subMatrix m1=multiply(a1122,b1122,n/2);
        subMatrix a2122 = subMatrix(init(n/2),0,0,n/2);
        add(a2122,a21,a22,n/2);
        subMatrix m2=multiply(a2122,b11,n/2);
        subMatrix b1222 = subMatrix(init(n/2),0,0,n/2);
        sub(b1222,b12,b22,n/2);
        subMatrix m3=multiply(a11,b1222,n/2);
        subMatrix b2111 = subMatrix(init(n/2),0,0,n/2);
        sub(b2111,b21,b11,n/2);
        subMatrix m4=multiply(a11,b2111,n/2);
        subMatrix a1112 = subMatrix(init(n/2),0,0,n/2);
        add(a1112,a11,a12,n/2);
        subMatrix m5=multiply(a1112,b22,n/2);
        subMatrix a2111 = subMatrix(init(n/2),0,0,n/2);
        subMatrix b1112 = subMatrix(init(n/2),0,0,n/2);
        sub(a2111,a21,a11,n/2);
        add(b1112,b11,b12,n/2);
        subMatrix m6=multiply(a2111,b1112,n/2);
        subMatrix a1222 = subMatrix(init(n/2),0,0,n/2);
        subMatrix b2122 = subMatrix(init(n/2),0,0,n/2);
        sub(a1222,a12,a22,n/2);
        add(b2122,b21,b22,n/2);
        subMatrix m7=multiply(a1222,b2122,n/2);
        subMatrix c11 = subMatrix(c,0,0,n);
        subMatrix c21 = subMatrix(c,n/2,0,n);
        subMatrix c12 = subMatrix(c,0,n/2,n);
        subMatrix c22 = subMatrix(c,n/2,n/2,n);
        add(c11,m1,m4,n/2);
        add(c11,c11,m7,n/2);
        sub(c11,c11,m5,n/2);
        add(c12,m3,m5,n/2);
        add(c21,m2,m4,n/2);
        add(c22,m3,m6,n/2);
        add(c22,c22,m1,n/2);
        sub(c22,c22,m2,n/2);
        clear(a1222.m,n/2);
        clear(b2122.m,n/2);
        clear(b1112.m,n/2);
        clear(a2111.m,n/2);
        clear(b2111.m,n/2);
        clear(a1112.m,n/2);
        clear(a1122.m,n/2);
        clear(b1122.m,n/2);
        clear(a2122.m,n/2);
        clear(b1222.m,n/2);
        clear(m1.m,n/2);
        clear(m2.m,n/2);
        clear(m3.m,n/2);
        clear(m4.m,n/2);
        clear(m5.m,n/2);
        clear(m6.m,n/2);
        clear(m7.m,n/2);
    }
    return cm;
}
