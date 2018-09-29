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


int main()
{
    freopen("in2.txt","r", stdin);
    parser_util();
    display(coeff_arr,N,N+1);
    return 0;
}
