#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50;
int N;
/*
x1 + 2x2 + 5x3 + x4 = 4
3x1 - 4x2 + 3x3 - 2x4 = 7
4x1 + 3x2 + 2x3 - x4 = 1
x1 - 2x2 - 4x3 - x4 = 2
*/

map<pair<string,int>, double> var_to_coeff;
map<string, int> var_to_idx;
map<int, string> idx_to_var;
double coeff_arr[MAXN][MAXN];
double coeff_arr2[MAXN][MAXN];

bool is_char(char c)
{
    if((c>='A' && c<='Z') || (c>='a' && c<='z')) return true;
    return false;
}

bool is_operator(char c)
{
    if(c=='+' || c=='-' || c=='=') return true;
    return false;
}

bool is_minus(char c)
{
    return c=='-'?true:false;
}


void matrix_constructor()
{
    map<pair<string,int>,double>::iterator it;

    int var_no = 0;
    for (it=var_to_coeff.begin(); it!=var_to_coeff.end(); ++it)
    {
        if(it->first.first!="cons")
        {
            if(var_to_idx.find(it->first.first)==var_to_idx.end())
            {
                var_to_idx[it->first.first] = var_no;
                idx_to_var[var_no] = it->first.first;
                var_no++;
            }
        coeff_arr[it->first.second][var_to_idx[it->first.first]] = it->second;
        }

    }
    for (it=var_to_coeff.begin(); it!=var_to_coeff.end(); ++it)
    {

        if(it->first.first=="cons")
        {
            if(var_to_idx.find(it->first.first)==var_to_idx.end())
            {
                var_to_idx[it->first.first] = var_no;
                idx_to_var[var_no] = it->first.first;
                var_no++;
            }
            coeff_arr[it->first.second][var_to_idx[it->first.first]] = it->second;
        }

    }

}
void variable_parser(string s, int equation_no)
{
    int i=0;
    string coeff = "";
    string var_name = "";
    char ch[10];

    bool is_neg = is_minus(s[0]);
    bool is_cons = ((s[0]=='=')?true:false);
    if(is_cons)
    {
        is_neg = is_minus(s[1]);
        while(is_char(s[i])==false && i<s.size())
        {
            if(is_operator(s[i]))
            {
                i++;
                continue;
            }
            coeff += s[i];
            i++;
        }
        var_name = "cons";
        //cout<<"cons "<<coeff<<endl;
    }
    else
    {
        while(is_char(s[i])==false && i<s.size())
        {
            if(is_operator(s[i]))
            {
                i++;
                continue;
            }
            coeff += s[i];
            i++;
        }

        while(i<s.size())
        {
            var_name += s[i];
            i++;
        }

    }
    if(coeff!="")
    {
        for(int j=0; j<coeff.size(); j++)
        {
            ch[j] = coeff[j];
        }
    }
    else
    {
        ch[0] = '1';
    }
    double coeff_val = atof(ch);
    if(is_neg) coeff_val *= -1;

    //variable mapping
    var_to_coeff[make_pair(var_name,equation_no)] = coeff_val;

}

void parser(string s, int equation_no)
{

    string temp = "";
    for(int i=0; i<s.size(); i++)
    {
        if(is_operator(s[i]))
        {
            //cout<<temp<<endl;
            variable_parser(temp,equation_no);
            temp = "";
            temp += s[i];
        }
        else if(s[i]==' ')
        {
            continue;
        }
        else
        {
            temp += s[i];
        }

    }
    if(temp!="")
    {
        //cout<<temp<<endl;
        string temp2 = "";
        if(temp[0]!='=')
            temp2 = '=' + temp;
        else temp2 = temp;
        variable_parser(temp2,equation_no);
    }
}

void parser_util()
{
    string s;
    int equation_no = 0;
    while(getline(cin, s))
    {
        parser(s,equation_no);
        equation_no++;
    }
    N = equation_no;
    matrix_constructor();

}

void getCofactor(double mat[][MAXN], double temp[][MAXN], int p, int q, int n)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double determinantOfMatrix(double mat[][MAXN], int n)
{
    double D = 0.0;
    if (n == 1)
        return mat[0][0];

    double temp[MAXN][MAXN];

    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
        sign = -sign;
    }

    return D;
}

void display(double mat[MAXN][MAXN], int row, int col)
{
    cout<<"The augmented matrix is: "<<endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            cout<<mat[i][j]<<" ";
        cout<<endl;
    }
}

void print_answer(vector<double>ans)
{
    cout<<"Soultions :"<<endl;
    for(int i=0;i<N;i++)
    {
        cout<<idx_to_var[i]<<" = "<<ans[i]<<endl;
    }
}


vector<double> cramers_rule(double coeff_arr[][MAXN])
{
    double constant[MAXN];
    double ans[MAXN];
    vector<double>ret;

    for(int i = 0; i < N; i++)
        for(int j =0; j < N; j++)
            coeff_arr2[i][j] = coeff_arr[i][j];

    display(coeff_arr,N, N+1);
    for(int i=0;i<N;i++)
    {
        constant[i] = coeff_arr[i][N];
    }



    int A = determinantOfMatrix(coeff_arr, N);
    //cout<<A<<endl;


    int k = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            coeff_arr2[j][k] = constant[j];
        }

        ans[i] = determinantOfMatrix(coeff_arr2, N) / A;

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                coeff_arr2[i][j] = coeff_arr[i][j];

        k++;
    }
    for(int i=0;i<N;i++)
    {
        ret.push_back(ans[i]);
    }
    return ret;
}
int main()
{
    freopen("in2.txt","r", stdin);
    parser_util();
    vector<double>ans = cramers_rule(coeff_arr);
    print_answer(ans);
    return 0;
}

