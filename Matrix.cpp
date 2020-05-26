#include <iostream>
#include <cmath>
using namespace std;
double hls(double **D,int n);



/*
*以下两部分内容参考b站教程：
*拷贝赋值函数部分https://www.bilibili.com/video/BV1H4411P7yg?p=100
*通过友元重载>>运算符https://www.bilibili.com/video/BV1H4411P7yg?p=102
*/

class Matrix {
private:
	int row, col;//行数row、列数col
	double **matrix;//二维动态数组matrix用于存放矩阵值
	void initmatrix();//初始化矩阵（为数组matrix分配row*col内存）
public:
	Matrix(int, int);//构造函数1:全0
	Matrix(int, int, double);//构造函数2:全value
	Matrix(const Matrix & that);//拷贝构造函数
	Matrix& operator=(const Matrix&);//拷贝赋值1:右操作数为Matrix
	Matrix& operator=(double *);//拷贝赋值2:右操作数为数组
	virtual ~Matrix();//析构函数应当是虚函数，除非此类不用做基类
	
	const Matrix operator+(const Matrix & m)const;//重载+
	const Matrix operator-(const Matrix & m)const;//重载-
	const Matrix operator*(const Matrix & m)const;//重载*（点乘）
	const Matrix operator*(const double & m)const;//重载*（数乘，数在后）
	const friend Matrix operator*(const double & m,const Matrix & n);//重载*（数乘，数在前）
	friend std::istream& operator>>(std::istream&, Matrix&);//重载>>实现矩阵的输入

	int getrows() const;//求矩阵行数
	int getcols() const;//求矩阵列数
	void printmatrix() const;//打印矩阵
	double getpoint(int, int)const;//打印矩阵r行c列的值
	void changepoint(int, int, double);//更改第i行j列的值
	static Matrix eye(int);//制造一个单位矩阵
	Matrix spilt(int, int, int, int)const;//拆分矩从阵a行b列到c行d列
	
	void swapRows(int, int);//行变换
	Matrix T()const;//求转置矩阵
	double det()const;//求矩阵的行列式
	Matrix inv();//求矩阵的逆矩阵
	Matrix Doolittle()const;//Doolittle三角分解

};


//初始化矩阵大小
void Matrix::initmatrix(){
	matrix = new double*[row];//动态内存分配
	for (int i = 0; i < row; ++i) {
		matrix[i] = new double[col];
	}
}
//构造函数1:声明一个row*col全0矩阵
Matrix::Matrix(int r, int c)
{
	row = r;
	col = c;
	initmatrix();
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = 0;
		}
	}
}
//构造函数2:声明一个值全部为value的矩阵
Matrix::Matrix(int r, int c, double value)
{
	row = r;
	col = c;
	initmatrix();
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = value;
		}
	}
}
//拷贝构造函数
Matrix::Matrix(const Matrix & that){
	if (this != &that) {
		row = that.row;
		col = that.col;
		initmatrix();
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				matrix[i][j] = that.matrix[i][j];
			}
		}
	}
	
}
//拷贝赋值1:右操作数为Matrix
Matrix& Matrix::operator=(const Matrix& m)
{
	if (this == &m) {
		return *this;
	}
	else{
		if (row != m.row || col != m.col) {
			for (int i = 0; i < row; ++i) {
				delete[] matrix[i];
			}
			delete[] matrix;
			row = m.row;
			col = m.col;
			initmatrix();
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				matrix[i][j] = m.matrix[i][j];
			}
		}
		return *this;
	}	
}
//拷贝赋值2:右操作数为数组(要求矩阵已经初始化过且大小和矩阵相同)
Matrix& Matrix::operator=(double *a){
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			matrix[i][j]= *(a+i*col+j);
		}
	}
	return *this;
}
//析构函数
Matrix::~Matrix() {
 for (int i = 0; i < row; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}


//重载+
const Matrix Matrix::operator+(const Matrix& m)const{
	if(row!=m.row || col!=m.col){
		cout<<"矩阵不符合相加要求"<<endl;
		abort();//退出
	}
	Matrix Madded(row,m.col,0.0);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Madded.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
		}
	}
	return Madded;
}
//重载-
const Matrix Matrix::operator-(const Matrix& m)const{
	if(row!=m.row || col!=m.col){
		cout<<"矩阵不符合相减要求"<<endl;
		abort();//退出
	}
	Matrix Mines(row,m.col,0.0);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Mines.matrix[i][j] = matrix[i][j] - m.matrix[i][j];
		}
	}
	return Mines;
}
//重载点乘
const Matrix Matrix::operator*(const Matrix & m)const{
	if(col!=m.row){
		cout<<"矩阵不符合相乘要求"<<endl;
		abort();//退出
	}
	Matrix M(row,m.col,0.0);
	for(int i=0;i<row;i++){
		for(int j=0;j<m.col;j++){
			for(int k=0;k<col;k++){
				M.matrix[i][j]+=(matrix[i][k]*m.matrix[k][j]);
			}
		}
	}
	return M;
}
//重载数乘:数在后
const Matrix Matrix::operator*(const double & m)const{
	Matrix M(row,col,0.0);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
				M.matrix[i][j]=m*matrix[i][j];
		}
	}
	return M;
}
//重载数乘:数在前
const Matrix operator*(const double & m,const Matrix & n){
	Matrix M(n.row,n.col,0.0);
	for(int i=0;i<n.row;i++){
		for(int j=0;j<n.col;j++){
				M.matrix[i][j]=m*n.matrix[i][j];
		}
	}
	return M;
}
//重载>>:实现矩阵的输入
istream & operator>>(istream& is, Matrix& m)
{
	for (int i = 0; i < m.row; i++) {
		for (int j = 0; j < m.col; j++) {
			is >> m.matrix[i][j];
		}
	}
	return is;
}


//求矩阵行数
int Matrix::getrows() const{
	return row;
}
//求矩阵列数
int Matrix::getcols() const{
	return col;
}
//打印矩阵
void Matrix::printmatrix()const {
	//cout << row <<" "<<col<< endl;//显示矩阵的行数和列数
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
//打印矩阵第i行第j列的数
double Matrix::getpoint(int r, int c) const{
	return matrix[r][c];
}
//将第i行j列的值改为k
void Matrix::changepoint(int i, int j, double k){
	matrix[i][j] = k;
}
//创建一个nxn单位矩阵
Matrix Matrix::eye(int n){
	Matrix A(n,n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			A.matrix[i][j] = i==j?1:0;
		}
	}
	return A;
}
//拆分矩从阵a行b列到c行d列
Matrix Matrix::spilt(int a, int b, int c, int d)const{
	if((a>c)||(b>d)||(c>=row)||(d>=col)){
		cout<<"无法拆分"<<endl;
		abort();
	}
	Matrix A(c-a+1,d-b+1);
	for(int i=a;i<c+1;i++){
		for(int j=b;j<d+1;j++){
			A.matrix[i-a][j-b] = matrix[i][j];
		}
	}
	return A;
}

//实现行变换
void Matrix::swapRows(int a, int b)
{
	a--;
	b--;
	double *temp = matrix[a];
	matrix[a] = matrix[b];
	matrix[b] = temp;
}
//求转置矩阵
Matrix Matrix::T()const{
	int c=col;
	int r=row;
	Matrix mt(c, r);
	for (int i = 0; i <r; i++) {
		for (int j = 0; j <c; j++) {
			mt.matrix[j][i] = matrix[i][j];
		}
	}
	return mt;
}
//计算矩阵行列式的值
double Matrix::det()const{
	if(row!=col){//非方阵时
		cout<<"矩阵不符合求行列式要求"<<endl;
		abort();
	}
	int n = col; 
	double ** D;//动态建立一个新数组用于计算
	D=new double *[row];//为矩阵申请内存
	for(int i=0;i<row;i++){
		D[i]=new double[col];
	}  
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			D[i][j]=matrix[i][j];
		}
	}
	double result = 0;
	result =  hls(D,n);//调用行列式计算函数
	 for (int i = 0; i < row; ++i) {//释放内存
		delete[] D[i];
	}
	delete[] D;
	return result;
}
/*计算行列式函数
由于递归传参的需要，将此功能独立写在类之外*/
double hls(double **D,int n){//输入二维数组、矩阵维数
	double d = 0;
	// 一阶二阶直接计算
	if(n == 1){
        d = D[0][0];
    }
	else if(n == 2){
        d = D[0][0]*D[1][1] - D[0][1]*D[1][0];
    }
	else{
        for(int k=0;k<n;k++){
            double **M;// 为代数余子式申请内存
			M=new double *[n-1];//为矩阵申请内存
			for(int i=0;i<n-1;i++){
				M[i]=new double[n-1];
			} 
            for(int i=0;i<n-1;i++){// 为余子式赋值
                for(int j=0;j<n-1;j++){
                    M[i][j]=D[i+1][j<k?j:j+1];
                }	
            }	
            if(D[0][k]){
                d+=D[0][k]*hls(M,n-1)*(((2+k)%2)?-1:1);
            }// 按第一行展开，递归计算行列式
			for (int i = 0; i < n-1; ++i) {//释放内存
				delete[] M[i];
			}
			delete[] M;
            }
	}
	return d;                   
}
//求矩阵的逆矩阵
Matrix Matrix::inv(){
	if((row!=col)||(this->det()==0)){//不是方阵或行列式为0时
		std::cout<<"不符合求逆阵要求"<<std::endl;
		std::abort();
	}
	int n = this->col;
	double  M[2*n][n];//避免改动原矩阵，新建一个行列式计算 
	for(int i=0;i<n;i++){//this存入M的1-n列
		for(int j=0;j<col;j++){
			M[i][j]=matrix[i][j];
		}
	}
	for(int i=n; i<2*n; i++){//将E存入M的n-2n列
		for(int j=0; j<n; j++){
			if(i-n == j)M[i][j] = 1;
			else M[i][j] = 0;
		}	
	} 
	int k = 0;      
	for(int j=0; j<n; j++){//this对应部分矩阵变为对角元素为1的下三角阵
		double dj = 1;//用于记录对角元素
		if(M[j][j]!=0){//当对角元素不为0
			dj = M[j][j];
			for(int r = j; r<2*n; r++){
				M[r][j] = M[r][j]/dj;//此列所有元素分别除以对角元素
			}
		}
		else if(M[j][j]==0){//当对角元素为0
			for(int s = j+1;s<n;s++){
					if(M[j][s]!=0)k = s;//找同一行上不为0的元素，记所在的列为k
			}
			for(int r = j; r<2*n; r++){
				M[r][j] = M[r][j]+M[r][k]/M[j][k];//此列所有元素分别加上k列元素处以M[j][k]
			}
		}
		double sy = 1;//用于记录对角元素右侧各列最上方非零元素值
		for(int s = j+1; s<n; s++){//s从j+1列开始（对角元素右侧第一列）
			sy = M[j][s];//记录该列最上方非零元素值
			for(int i = j; i<2*n; i++){//第s列各元素分别减去sy*第j列对应元素
				M[i][s] = M[i][s]-sy*M[i][j];
			}
		}
	}
	/*//测试：
	for(int i = 0;i<2*n; i++){
		for(int j= 0;j<n;j++){
			cout<<M[i][j]<<" ";
		}
		cout<<endl;
	}*/
	double sy = 1.0;//化为单位阵
	for(int j = n; j>-1; j--){//列变换，从第n行开始将除对角元素外的部分化为0
		for(int s = j-1; s>-1; s--){
			sy = M[j][s];
			for(int i = j; i<2*n; i++){
				M[i][s] = M[i][s]- sy*M[i][j];
			}
		}
	}
	Matrix m(n,n,0.0);
	for (int i = n; i < 2*n; i++) {
		for (int j = 0; j < n; j++) {
			m.matrix[i-n][j] = M[i][j];
		}
	}
	return m;
}
//Doolittle分解为一个LU矩阵
Matrix Matrix::Doolittle()const{
	int c = col;
	int r = row;
	Matrix md(r,c);
	for (int k = 0; k <r; k++) {
		for (int j = k; j <c; j++) {//上三角第k行各元素
			md.matrix[k][j] = matrix[k][j];
			for(int y = 0; y < k; y++){
				md.matrix[k][j] -= md.matrix[k][y]*md.matrix[y][j];
			}
		}
		for (int i = k+1; i <r; i++) {//下三角第k列各元素
			md.matrix[i][k] = matrix[i][k];
			for(int x = 0; x < k; x++){
				md.matrix[i][k] -= md.matrix[i][x]*md.matrix[x][k];
			}
			md.matrix[i][k] = md.matrix[i][k]/md.matrix[k][k];
		}
	}
	return md;
}
