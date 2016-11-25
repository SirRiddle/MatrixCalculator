#include "Task.h"

Matrix::Matrix()
{
	rows = columns = 1000;
	mat = new double*[rows];
	valid = 0, aug = 1;
	for (int i = 0; i < rows; i++)
	{
		mat[i] = new double[columns];
	}
}

istream &operator>> (istream &get, Matrix &m)
{
	cout << "Enter No. of rows & columns :\n";
	cin >> m.rows >> m.columns;
	cout << "Enter " << m.rows << " x " << m.columns << " Matrix\n";
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.columns; j++)
		{
			get >> m.mat[i][j];
		}
	}
	return get;
}

ostream &operator<< (ostream &print, Matrix &m)
{
	cout << "Here's Your Result\n";
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.columns; j++)
		{
			print << m.mat[i][j] << " ";
		}
		cout << endl;
	}
	return print;
}

int Matrix::getrows()
{
	return rows;
}

int Matrix::getcolumns()
{
	return columns;
}

double ** Matrix::getmat()
{
	return mat;
}

bool Matrix::isValid()
{
	return valid;
}

bool Matrix::isAug()
{
	return aug;
}

Matrix Matrix::operator+(Matrix m)
{
	if (rows != m.rows || columns != m.columns)
	{
		return m;
	}
	Matrix res;
	res.rows = m.rows;
	res.columns = m.columns;
	res.valid = "SirRiddle";
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.columns; j++)
		{
			res.mat[i][j] = m.mat[i][j] + mat[i][j];
		}
	}
	return Matrix(res);
}

Matrix Matrix::operator-(Matrix m)
{
	if (rows != m.rows || columns != m.columns)
	{
		return m;
	}
	Matrix res;
	res.rows = m.rows;
	res.columns = m.columns;
	res.valid = "SirRiddle";
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.columns; j++)
		{
			res.mat[i][j] = mat[i][j] - m.mat[i][j];
		}
	}
	return Matrix(res);
}

Matrix Matrix::operator*(Matrix m)
{
	if (columns != m.rows)
	{
		return m;
	}
	Matrix res;
	res.rows = rows;
	res.columns = m.columns;
	res.valid = "SirRiddle";
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.columns; j++)
		{
			res.mat[i][j] = 0;
			for (int k = 0; k < columns; k++)
			{
				res.mat[i][j] += mat[i][k] * m.mat[k][j];
			}
		}
	}
	return Matrix(res);
}

Matrix Matrix::operator*(int x)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mat[i][j] *= x;
		}
	}
	return *(this);
}

Matrix Matrix::operator^(int x)
{
	Matrix res = *this;
	for (int i = 1; i < x; i++)
	{
		res = (*this)*res;
	}
	return Matrix(res);
}

Matrix Matrix::transpose()
{
	Matrix m;
	m.rows = columns; m.columns = rows;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			m.mat[j][i] = mat[i][j];
		}
	}
	return m;
}

Matrix Matrix::Echelon()
{
	int i, j, k;
	for (i = 0; i < rows; i++)                    //Pivotisation
	{
		for (k = i + 1; k < rows; k++)
		{
			if (mat[i][i] == 0)
				for (j = 0; j < columns; j++)
				{
					swap(mat[i][j], mat[k][j]);
				}
		}
	}
	cout << "\nThe matrix after Pivotisation is:\n";
	for (i = 0; i < rows; i++)            //print the new matrix
	{
		for (j = 0; j < columns; j++)
		{
			cout << mat[i][j] << " ";
		}
		cout << "\n";
	}
	for (i = 0; i < columns - 1; i++)            //loop to perform the gauss elimination
	{
		for (k = i + 1; k < rows; k++)
		{
			double div = mat[i][i];
			if (div != 0)
			{
				double t = mat[k][i] / mat[i][i];
				for (j = 0; j <= rows; j++)
					mat[k][j] -= (t* mat[i][j]);    //make the elements below the pivot elements equal to zero or elimnate the variables
			}
		}
	}
	cout << "\n\nThe matrix after gauss-elimination is as follows:\n";
	for (i = 0; i < rows; i++)            //print the new matrix
	{
		for (j = 0; j < columns; j++)
		{
			cout << mat[i][j] << " ";
		}
		cout << "\n";
	}
	int free = 0, basic = 0;
	for (int j = 0; j < columns - 1; j++)
	{
		if (mat[j][j] != 0)
		{
			cout << "x" << j + 1 << " is basic" << endl;
			basic++;
		}
		else
		{
			cout << "x" << j + 1 << " is free" << endl;
			free++;
		}
	}
	if (basic == columns - 1)
	{
		cout << "Consistent : Has one solution\n";
	}
	else if (basic == columns - 2)
	{
		cout << "Consistent : has many solutions\n";
	}
	else
	{
		cout << "Inconsistent\n";
	}

	return Matrix(*this);
}

Matrix Matrix::ReducedEchelon()
{
	int lead = 0;
	for (int r = 0; r < rows; r++)
	{
		if (columns <= lead)
		{
			break;
		}
		int i = r;
		while (mat[i][lead] == 0)				// c = (i) , (r) = i
		{
			i++;
			if (rows == i)
			{
				i = r;
				lead++;
				if (lead == columns)
				{
					lead--;
					break;
				}
			}
		}
		for (int j = 0; j < columns; j++)
		{
			swap(mat[r][j], mat[i][j]);
		}
		double no1 = mat[r][lead];
		if (no1 != 0)
		{
			for (int b = 0; b < columns; b++)
			{
				mat[r][b] /= no1;
			}
			for (int t = 0; t < rows; t++)
			{
				if (t != r)
				{
					double no = mat[t][lead];
					for (int o = 0; o < columns; o++)
					{
						mat[t][o] -= (no * mat[r][o]);
					}
				}
			}
			lead++;
		}
	}
	if (aug)
	{

	}

	return (*this);
}

void Matrix::Add_I()
{
	aug = 0;
	if (rows != columns)
	{
		valid = 0;
		return;
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = columns; j < columns * 2; j++)
		{
			if ((i + columns) == j)
			{
				mat[i][j] = 1;
			}
			else
			{
				mat[i][j] = 0;
			}
		}
	}
	columns *= 2;
}

Matrix Matrix::Inverse()
{
	Add_I();
	ReducedEchelon();

	return (*this);
}

double det(int r, double **mat)
{
	double d = 0;
	int subi, subj;
	double **submat = new double *[r];
	for (int i = 0; i < r; i++)
	{
		submat[i] = new double[r];
	}
	if (r == 2)
	{
		return ((mat[0][0])*mat[1][1] - (mat[1][0] * mat[0][1]));
	}
	else
	{
		for (int i = 0; i < r; i++)
		{
			subi = 0;
			for (int j = 0; j < r; j++)
			{
				subj = 0;
				for (int k = 0; k < r; k++)
				{
					if (k != i)
					{
						submat[subi][subj] = mat[j][k];
						subj++;
					}
				}
				subi++;
			}
			d += pow(-1, i)*mat[0][i] * det(r - 1, submat);
		}
	}
	return d;
}

void Run(Matrix m1, Matrix m2)
{
	bool cont = 1;
	while (cont)
	{
		cout << "\t\t        Welcome To My Matrix Calculator\n\n";
		int h;
		cin >> m1;
		cout << "\n1- To Transpose \n2- To Add on it another matrix \n3- To Subtract another matrix from it \n4- Multiply with another matrix\n5- To raise the matrix to the power of(N)\n6- Multiply your matrix with a constant\n7- To solve it using Echelon/reduced echelon from\n8- To get determinant\n9- To get inverse matrix\n";
		char x;
		while ("SirRiddle")
		{
			cin >> x;
			switch (x)
			{
			case '1':
				cout << m1.transpose();
				break;
			case '2':
				cin >> m2;
				//cout << m1 + m2;
				if ((m1 + m2).isValid())
					cout << (m1 + m2);
				else
					cout << "You can't add 2 matrices of different sizes\n";
				break;
			case '3':
				cin >> m2;
				if ((m1 - m2).isValid())
					cout << m1 - m2;
				else
					cout << "You can't subtract 2 matrices of different sizes\n";
				break;
			case '4':
				cin >> m2;
				if ((m1*m2).isValid())
					cout << m1*m2;
				else
					cout << "You can't do that , NxM * MxB = NxB\n";
				break;
			case '5':
				cout << "Enter the power of the matrix : \n";
				cin >> h;
				m2 = m1^h;
				cout << m2;
				break;
			case'6':
				cout << "Enter your constant : \n";
				cin >> h;
				cout << m1*h;
				break;
			case '7':
				m1.Echelon();
				cout << m1.ReducedEchelon();
				break;
			case '8':
				cout << "Determinant = ";
				cout << det(m1.getrows(), m1.getmat()) << endl;
				break;
			case '9':
				if (m1.Inverse().isValid() || det(m1.getrows(), m1.getmat()))
					cout << m1.Inverse();
				else
					cout << "the size of matrix should be square OR determinant = 0\n";
				break;
			default:
				cout << "Wrong no,\n";
				continue;
			}
			break;
		}
		char k;
		cout << "Would you like to repeat ? (y for yes or n for no)\n";
		cin >> k;

		k == 'n' ? cont = 0 : system("cls");
	}
}
